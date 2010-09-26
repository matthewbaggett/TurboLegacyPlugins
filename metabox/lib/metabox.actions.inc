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
			$tags 		= json_decode($_POST['imageTags']);
			print_r($tags);
			die("FUCKIT");
			
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
			
			//Try to tweet!
			if(TURBO::PluginAvailable("Twitter")){
				$oTweet = new Tweet();
				$oTweet->message = "New image uploaded: ".basename($fileName).".";
				$oTweet->tweet();
			}
			//return the responce:
			return $responce->crunch();
		}else{
			return self::failure("Invalid APIKEY",false);
		}
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
	
	static private function failure($failure, $sendEmail = true){
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




