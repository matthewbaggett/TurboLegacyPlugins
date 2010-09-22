<?php
class statisticsModule{
	
	public function __construct(){
	}
	/*
	 * The default action
	 */
	function action_default(){
		
		$responce = new PluginResponce();
		die("Doop, time machine");
		return $responce;
	}
	/*
	 * Function to get a specific version of a specific page
	 */
	function action_version_get($variables){
		/*
		 * Check if the user is an admin user
		 */
		$oAdminUser = new User();
		if(loadFromSession($oAdminUser,"backend_")){
			//Create the result object to store our responce in
			$result = new PluginResponce();
			
			//sort out the fields we want from variables we've been passed
			$uuid = $variables[1];
			$version = $variables[2];
			
			//Generate the SQL for the version lookup
			$sql = sprintf(
				"SELECT * FROM pages WHERE pageuuid = '%s' AND version = '%d' LIMIT 1",
				DB::escape_string($uuid),
				DB::escape_number($version)
			);
			
			//Do the Query...
			$result = DB::Query($sql);
			
			//Then process the results:
			if(DB::rows($result)){
				$row = DB::result_array($result);
				$oPage = new page();
				$oPage->loadByRow($row);
				$result->pageTitle = $oPage->getPageName();
				$result->xml = $oPage->getXML();
			}
			//Return the responce object
			return $result;
		}else{
			header("Location: ".ROOTPATH."/turbo");
		}
		
	}
	
	function action_logThisRequest($args = null){
		fb::log("Logging this request");
		$path 		= ltrim($_SERVER['REQUEST_URI'],"/");
		$handler 	= ltrim($_SERVER['SCRIPT_NAME'],"/");
		
		switch($handler){
			case 'turbo/cron.php':
				break;
			default:
				$oRequest 	= new loggedPath();
				$oRequest->setPath($path);
				$oRequest->setHandler($handler);
				//TODO: Make this set the user id when user is logged in.
				$oRequest->setUserId();
				$oRequest->setIP($_SERVER['REMOTE_ADDR']);
				$oRequest->setTime(time());
				$oRequest->save();
				fb::info("yo!");
		}
	}
		

	
	function action_clear_logs($args = null){
		$oRequest = new loggedPath();
		$oRequest->destroyTable();
		$to = TURBO::getAdminEmailsList();
		$subject = "CRON: Logs cleared";
		$message = "The view logs were cleared at ".date(DEFAULT_DATE_COMPACT)." automatically.";
		$this->sendCronMail($subject, $message);
	}
	
	function action_be_pissing_annoying($args = null){
		$to = TURBO::getAdminEmailsList();
		$subject = "CRON: Test cron job";
		$message = "Annoyance sent at  ".date(DEFAULT_DATE_COMPACT)." automatically.";
		$this->sendCronMail($subject, $message);
	}
	function sendCronMail($subject, $message){
		$admins = TURBO::getAdminEmailsList();
		$headers = 'From: cron@'.$_SERVER['HTTP_HOST'] . "\r\n" .
    		'Reply-To: '.$admins[0]."\r\n" .
    		'X-Mailer: PHP/' . phpversion();
		mail(TURBO::getAdminEmailsList(), $subject, $message, null);
	}
	
}
