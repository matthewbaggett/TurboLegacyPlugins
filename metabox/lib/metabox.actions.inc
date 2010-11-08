<?php

function first(&$array) {
	if (!is_array($array)) return null;
	if (!count($array)) return null;
	reset($array);
	return key($array);
}

class metaboxModule{
	
	public function __construct(){

	}
	
	function action_default(){
		
	}
	
	function action_status(){
		/*
		 * Sanity checks
		 */
		
		//Get API key
		if(isset($_POST['apiKey'])){
			$oUser = self::checkApiKey($_POST['apiKey']);
		}elseif(isset($_GET['apiKey'])){
			$oUser = self::checkApiKey($_GET['apiKey']);
		}else{
			return self::failure("APIKEY UNSPECIFIED");
		}
		//Check the user is valid.
		if($oUser == false){
			return self::failure("Invalid APIKEY",false);
		}
		/*
		 * Completed sanity checks
		 */
		
		//Build the new metabox responce up...
		$responce = new metaboxResponce();
		$responce->status = "OKAY";
		$responce->statusString = "SERVER APPEARS OKAY";
		$responce->user = $oUser;
		
		$responce->data['$_SERVER'] = $_SERVER;
		
		//return the responce:
		return $responce->crunch();
	}
	function action_push(){
		/*
		 * Sanity checks
		 */
		
		//Get API key
		if(isset($_POST['apiKey'])){
			$oUser = self::checkApiKey($_POST['apiKey']);
		}elseif(isset($_GET['apiKey'])){
			$oUser = self::checkApiKey($_GET['apiKey']);
		}else{
			return self::failure("APIKEY UNSPECIFIED");
		}
		//Check the user is valid.
		if($oUser == false){
			return self::failure("Invalid APIKEY",false);
		}
		//Check the dataset is set
		if(isset($_POST['dataset'])){
			$dataset = $_POST['dataset'];
		}elseif(isset($_GET['dataset'])){
			$dataset = $_POST['dataset'];
		}else{
			$dataset = 'public-dataset';	//connect to the public dataset if dataset not set.
		}
		//Check the dataset is valid
		try{
			$oDataset = new dataset($dataset);
			$datasetValid = true;
		}catch(Exception $e){
			return $this->failure("Dataset is not valid: $dataset");
		}
		//Check the user has permission for the dataset
		$permission = $oDataset->getPermission($oUser->getID());
		if(!$oDataset->checkPermission($oUser,'write')){
			return $this->failure("User {$oUser->getUsername()} does not have the required 'write' permission to database '{$oDataset->getName()}'.");
		}
				
		/*
		 * Completed sanity checks
		 */
		
		//Build the new metabox responce up...
		$responce = new metaboxResponce();
		$responce->status = "APIKEY OKAY";
		$responce->user = $oUser;
		
		//Decide what to do with the image
		if(isset($_POST['imageFile'])){
			//We download and analyse this one
			$fileData = curl_file_get_contents($_POST['imageFile']);
			$fileName = $_POST['imageFile'];
			$fileSource = "scrape";
			
			$fileStorage = $this->writeImageToDisk($fileData,$fileName);
			//If writing failed, we'd have got a metaboxResponce back
			if(is_object($fileStorage) || is_array($fileStorage)){
				//If $fileStorage is an Object/Array, its a metaboxResponce from failure.
				return $fileStorage;
			}else{
				//Yay, file stored ok
			}
			
		
		}elseif($_POST['imageFileData']){	//File uploaded in the POST...
			$fileData = $_POST['imageFileData'];
			$fileName = $_POST['imageFileName'];
			$fileSource = "scrape";
			
			$fileStorage = $this->writeImageToDisk($fileData,$fileName);
			//If writing failed, we'd have got a metaboxResponce back
			if(is_object($fileStorage) || is_array($fileStorage)){
				//If $fileStorage is an Object/Array, its a metaboxResponce from failure.
				return $fileStorage;
			}else{
				//Yay, file stored ok
			}
		}elseif($isAFileUpload){
			//TODO: Do the file upload logic here
			$fileData = 'dookie!';
			$fileName = "somefile.png";
			$fileSource = "upload";
			return self::failure("File uploads not supported yet",true);
		}else{
			return self::failure("No file to process",false);
		}
		
		//Process the image
		$md5 		= hash("MD5",	$fileData);
		$sha 		= hash("SHA1",	$fileData);
		$size 		= strlen($fileData);
		$tags 		= explode(",",$_POST['imageTags']);
		
		//Generate the image
		$image = new metabox_image();
		$image->uuidGenerate	();
		$image->setMD5($md5);
		$image->setSHA1($sha);
		$image->setUserid($oUser->getID());
		$image->setConstructedBy($oUser->getID());
		$image->setUUID(uuid());
		$image->setSize($size);
		$image->setSource($fileSource);
		$image->setFile($fileStorage);
		$image->setDatasetID($oDataset->getID());
		//Commit the image to the DB
		$image->save();
		$responce->status = "OKAY";
		$responce->statusString = "Uploaded image is OK.";
		
		//Process the tags
		//Make an array of tag objects corresponding with the tags uploaded
		foreach($tags as $tag){
			$oTag = new metabox_tag($tag);
			$aoTags[] = $oTag;
		}
		//Cycle through each tag object and construct the relation between the tag and the image
		foreach($aoTags as $oTag){
			$relation = new metabox_relation();
			$relation->setimageid($image->getid());
			$relation->settagid($oTag->getid());
			$relation->save();
		}
		$responce->statusString = "Uploaded image is OK. Has ".count($aoTags)." tags.";
		
		//Reloat the image
		$image->reload();
		//Add the image to the responce
		$responce->image = $image;

		//return the responce:
		return $responce->crunch();
	}
	
	function action_seek(){
		/*
		 * Sanity checks
		 */
		
		//Get API key
		if(isset($_POST['apiKey'])){
			$oUser = self::checkApiKey($_POST['apiKey']);
		}elseif(isset($_GET['apiKey'])){
			$oUser = self::checkApiKey($_GET['apiKey']);
		}else{
			return self::failure("APIKEY UNSPECIFIED");
		}
		//Check the user is valid.
		if($oUser == false){
			return self::failure("Invalid APIKEY",false);
		}
		//Get keywords
		if(isset($_POST['search'])){
			$keywords = explode(",",$_POST['search']);
		}elseif(isset($_GET['search'])){
			$keywords = explode(",",$_GET['search']);
		}else{
			return self::failure("SEARCH TERMS UNSPECIFIED");
		}
		//Check the dataset is set
		if(isset($_POST['dataset'])){
			$dataset = $_POST['dataset'];
		}elseif(isset($_GET['dataset'])){
			$dataset = $_GET['dataset'];
		}else{
			$dataset = 'public-dataset';	//connect to the public dataset if dataset not set.
		}
		//Check the dataset is valid
		try{
			$oDataset = new dataset($dataset);
			$datasetValid = true;
		}catch(Exception $e){
			return $this->failure("Dataset is not valid: $dataset");
		}
		//Check the user has permission for the dataset
		$permission = $oDataset->getPermission($oUser->getID());
		if(!$oDataset->checkPermission($oUser,'read')){
			return $this->failure("User {$oUser->getUsername()} does not have the required 'read' permission to database '{$oDataset->getName()}'.");
		}
		if(!$oDataset->checkPermission($oUser,'seek')){
			return $this->failure("User {$oUser->getUsername()} does not have the required 'seek' permission to database '{$oDataset->getName()}'.");
		}
		/*
		 * Completed sanity checks
		 */
		
		//Build the new metabox responce up...
		$responce = new metaboxResponce();
		$responce->status = "APIKEY OKAY";
		$responce->user = $oUser;
		
		//Do the search for each keyword individually
		
		foreach($keywords as $keyword){
			$keywordResults[] = metaboxModule::doSingleKeywordSeek($keyword,$oDataset);
		}
		//Look for intersections
		if(count($keywords) > 1){
			while (count($keywordResults) > 1) { 
				$keywordResults[] = array_intersect_key(array_pop($keywordResults), array_pop($keywordResults));
			}
		}

		$results = $keywordResults[0];

		//Add them to the responce;
		$responce->data = $results;
		$responce->status = "OKAY";
		$responce->statusString = "Search OK, ".count($results)." results.";

		//Return it.
		return $responce->crunch();
		
	}
	
	static public function action_get_uuid($vars){
		$uuid = $vars[1];
		/*
		 * Sanity checks
		 */
		
		//Get API key
		if(isset($_POST['apiKey'])){
			$oUser = self::checkApiKey($_POST['apiKey']);
		}elseif(isset($_GET['apiKey'])){
			$oUser = self::checkApiKey($_GET['apiKey']);
		}else{
			return self::failure("APIKEY UNSPECIFIED");
		}
		//Check the user is valid.
		if($oUser == false){
			return self::failure("Invalid APIKEY",false);
		}
		//Check the dataset is set
		if(isset($_POST['dataset'])){
			$dataset = $_POST['dataset'];
		}elseif(isset($_GET['dataset'])){
			$dataset = $_GET['dataset'];
		}else{
			$dataset = 'public-dataset';	//connect to the public dataset if dataset not set.
		}
		//Check the dataset is valid
		try{
			$oDataset = new dataset($dataset);
			$datasetValid = true;
		}catch(Exception $e){
			return $this->failure("Dataset is not valid: $dataset");
		}
		//Check the user has permission for the dataset
		$permission = $oDataset->getPermission($oUser->getID());
		if(!$oDataset->checkPermission($oUser,'read')){
			return $this->failure("User {$oUser->getUsername()} does not have the required 'read' permission to database '{$oDataset->getName()}'.");
		}
		if(!$oDataset->checkPermission($oUser,'seek')){
			return $this->failure("User {$oUser->getUsername()} does not have the required 'seek' permission to database '{$oDataset->getName()}'.");
		}
		/*
		 * Completed sanity checks
		 */
		
		//Build the new metabox responce up...
		$responce = new metaboxResponce();
		$responce->status = "APIKEY OKAY";
		$responce->user = $oUser;
		
		//Get the image requested
		$image = self::doGetByUUID($uuid,$oDataset);
		
		//Add them to the responce;
		$responce->data = array($image);
		$responce->status = "OKAY";
		$responce->statusString = "GET OK";

		//Return it.
		return $responce->crunch();
		
	}
	
	static private function doGetByUUID($uuid,$oDataset){
		$uuid = DB::escape_string($uuid);
		$sql = "
			SELECT i.*
			FROM mimages i
			JOIN mrelation r
			  ON r.imageid = i.id
			JOIN mtags t
			  ON t.id = r.tagid
			WHERE i.uuid = '{$uuid}'
			  AND i.datasetid = '{$oDataset->getID()}'
			";
		$result = DB::Query($sql);
		while($row = DB::result_array($result)){
			$oImage = new metabox_image();
			$oImage->loadByRow($row);
			return $oImage;
		}
		return self::failure("More than one entry for the uuid $uuid");
	}
	static private function doSingleKeywordSeek($keyword,$oDataset){
		$sql = "
			SELECT i.*
			FROM mimages i
			JOIN mrelation r
			  ON r.imageid = i.id
			JOIN mtags t
			  ON t.id = r.tagid
			WHERE t.value= '{$keyword}'
			  AND i.datasetid = '{$oDataset->getID()}'
			";
		$result = DB::Query($sql);
		while($row = DB::result_array($result)){
			$oImage = new metabox_image();
			$oImage->loadByRow($row);
			$aoImages[$oImage->getID()] = $oImage;
		}
		return $aoImages;
	}
	
	static private function writeImageToDisk($data,$originalFileName){
		$name = basename($originalFileName);
		if(touch(STORAGE_S3_DIRECTORY."/touch")){
			$storagePath = sprintf(
				"%s/%s/%s/%s",
				dechex(rand(0,255)),
				dechex(rand(0,255)),
				dechex(rand(0,255)),
				$name
			);
			mkdir(dirname(STORAGE_S3_DIRECTORY.$storagePath),0777,true);
			file_put_contents(STORAGE_S3_DIRECTORY.$storagePath,$data);
			return $storagePath;
		}else{
			return self::failure("Cannot connect to S3/S3-alike",true);
		}
	}
	
	static public function failure($failure, $sendEmail = true){
		$loggedFail = new failureLog();
		$loggedFail->setMessage($failure);
		$failureLogNumber = $loggedFail->save();
		
		if($sendEmail){
			TURBO::sendEmail(
				TURBO::getAdminEmailsList(),
				"failure@".TURBO::getDomain(),
				"FAILURE on ".TURBO::getDomain(),
				$failure."\n\n".
				"Failure logged as fail #{$failureLogNumber}"
			);
		}
		
		$responce = new metaboxResponce();
		$responce->status = "FAIL";
		$responce->statusString = $failure;
		return $responce->crunch();
	}
	
	static private function checkApiKey($key){
		$oKey = new apikey();
		return $oKey->loadByKey($key);
	}
	

}




