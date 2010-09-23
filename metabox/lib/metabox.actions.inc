<?php
class metaboxModule{
	private $blogController;
	
	public function __construct(){
		$this->blogController = new blogController();
	}
	
	function action_default(){
		
	}
	
	function action_search_by_author($variables){
		
	}
	function action_push(){
		if($oUser = self::checkApiKey($_POST['apiKey'])){
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
				
				$oStor = $this->writeImageToDisk($fileData,$fileName);
				//If writing failed, we'd have got a metaboxResponce back
				if(get_class($oStor) == 'metaboxResponce'){
					return $oStor;
				}
			}elseif($isAFileUpload){
				//TODO: Do the file upload logic here
				$fileData = 'dookie!';
				$fileName = "somefile.png";
				$fileSource = "upload";
				return self::failure("File uploads not supported yet");
			}else{
				return self::failure("No file to process");
			}
			$md5 		= hash("MD5",	$fileData);
			$sha 		= hash("SHA1",	$fileData);
			$size 		= strlen($fileData);
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
			//Commit the image to the DB
			$image->save();
			
			if(TURBO::PluginAvailable("Twitter")){
				$oTweet = new Tweet();
				$oTweet->message = "New image uploaded: ".basename($fileName).".";
				$oTweet->tweet();
			}
			//return the responce:
			return $responce->crunch();
		}else{
			return self::failure("Invalid APIKEY");
		}
	}
	
	static private function writeImageToDisk($data,$originalFileName){
		$name = basename($originalFileName);
		if(touch(STORAGE_S3_DIRECTORY."/touch")){
			$storagePath = "%s/%s/%s/%s";
			$storagePath 
		}else{
			return self::failure("Cannot connect to S3/S3-alike");
		}
	}
	
	static private function failure($failure){
		$responce = new metaboxResponce();
		$responce->status = "FAIL";
		$responce->errorString = $failure;
		return $responce->crunch();
	}
	
	static private function checkApiKey($key){
		$oKey = new apikey();
		return $oKey->loadByKey($key);
	}
	

}




