<?php
class visitor{
	static public $user_object;
	
	static public function get(){
		return self::$user_object;
	}
}

class loginModule{

	private function get_login_form($user){
		$form = new TurboForm($user);
		$form->hidden_fields[] = 'id';
		$form->hidden_fields[] = 'level';
		$form->hidden_fields[] = 'active';
		$form->hidden_fields[] = 'session';
		$form->hidden_fields[] = 'registereddate';
		$form->hidden_fields[] = 'firstname';
		$form->hidden_fields[] = 'surname';
		$form->hidden_fields[] = 'email';
		
		$form->action = "/plugin/login/submit";
		$form->submit_text = "Login!";
		return $form;
	}

	public function action_login(){
		$result = new PluginResponce();
		$result->pageTitle = "Login:";
		
		$form = $this->get_login_form(new User());
		$result->xml.= $form->getXML();
		return $result;
	}
	
	public function action_login_do(){
		$oUser = new user();
		if($oUser->login($_POST['username'],$_POST['password'])){
			$_SESSION['logged_in_visitor'] = $oUser->getUsername();
			visitor::$user_object = $oUser;
			header("Location: /");
			exit;
		}else{
			header("Location: /plugin/login");
			exit;
		}
	}
	
	public function action_login_check(){
		if($_SESSION['logged_in_visitor']){
			visitor::$user_object = new User();
			visitor::$user_object->loadByUsername($_SESSION['logged_in_visitor']);
		}else{
			visitor::$user_object = null;
		}
	}
	
	public function action_logout(){
		$_SESSION['logged_in_visitor'] = null;
		unset($_SESSION['logged_in_visitor']);
		header("Location: /");
	}
}
