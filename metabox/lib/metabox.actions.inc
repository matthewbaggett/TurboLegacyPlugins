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
				
			}elseif($isAFileUpload){
				//TODO: Do the file upload logic here
				$fileData = 'dookie!';
				return self::failure("File uploads not supported yet");
			}else{
				return self::failure("No file to process");
			}
			$md5 		= hash("MD5",	$fileData);
			$sha 		= hash("SHA1",	$fileData);
			$size 		= strlen($fileData);
			$image 		= new metabox_image();
			$image->uuidGenerate	();
			$image->setmd5			($md5);
			$image->setsha1			($sha1);
			$image->save();
			
			//return the responce:
			return $responce->crunch();
		}else{
			return self::failure("Invalid APIKEY");
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




