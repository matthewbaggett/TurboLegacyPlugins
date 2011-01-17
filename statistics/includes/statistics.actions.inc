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
	
	function action_log_this_request($args = null){
		global $oFUser;	//Grab the FrontendUser object.
		
		$path 		= ltrim($_SERVER['REQUEST_URI'],"/");
		$handler 	= ltrim($_SERVER['SCRIPT_NAME'],"/");
		
		switch($handler){
			case 'turbo/cron.php':
				break;
			default:
				$oRequest 	= new loggedPath();
				$oRequest->setPath($path);
				$oRequest->setHandler($handler);
				
				//Make this set the user id when user is logged in.
				if(is_object($oFUser)){
					$oRequest->setUserId($oFUser->getId());
				}
				
				//Add the IP to the request
				$oRequest->setIP($_SERVER['REMOTE_ADDR']);
				
				//TODO: If possible, use HTML5 to get the location information
				
				//Save & Reload the object.
				$oRequest->save(); 
				$oRequest->reload();
				
				//Some debug about this request
				fb::log("Logging this request... Request #{$oRequest->getID()} from {$oRequest->getIP()}");
				
				//If the GEOIP plugin is installed, add the geoip tracker JS
				if(TURBO::PluginAvailable('geoip')){
					TURBO::add_js_var('request_id',$oRequest->getID());
					TURBO::add_js_var('gps_feed_location',ROOTPATH."plugin/geoip_locate_html5");
					TURBO::add_js_file("/plugins/geoip/js/gps.js");
				}
		}
		
	}
	
	public function action_track_movement(){
		try{
			fb::log("movement tracking");
			if(class_exists("visitor")){
				$visitor = visitor::$user_object;
			}else{
				$visitor = null;
			}
			$this->do_tracking_action(
				array(
					'request' 	=> $_SERVER['REQUEST_URI'],
					'time'		=> microtime(true),
					'post'		=> $_POST,
					'get'		=> $_GET,
					'user'		=> $visitor
				)
			);
		}catch(Exception $e){
			fb::error($e, "There was an exception encountered while logging this user");
		}
	}
	
	public function action_destroy_session(){
		//print_r_html($_SERVER);die();
		$this->do_tracking_action(
			array(
				'request' 	=> $_SERVER['REQUEST_URI'],
				'time'		=> microtime(true),
				'destroy_requested' => "YES"
			)
		);
		session_destroy();
		echo "SESSION DESTROYED";
	}
	
	private function do_tracking_action($action){
		if(isset($_SESSION['session_id'])){
			$oMovement = new Movements($_SESSION['session_id']);
		}else{
			$oMovement = new Movements();
		}
		$_SESSION['movements'][] = $action;
		$oMovement->setMovements(serialize($_SESSION['movements']));
		$oMovement->save();
		$_SESSION['session_id'] = $oMovement->getId();
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
		TURBO::sendEmail($admins,"cron@".TURBO::getDomain(),$subject,$message);
	}
	
}
