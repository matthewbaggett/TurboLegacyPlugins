<?php

class registrationModule{

	private function get_registration_form($user){
		$form = new TurboForm($user);
		$form->hidden_fields[] = 'id';
		$form->hidden_fields[] = 'level';
		$form->hidden_fields[] = 'active';
		$form->hidden_fields[] = 'session';
		$form->hidden_fields[] = 'registereddate';
		$form->action = "/plugin/register/submit";
		$form->submit_text = "Register!";
		return $form;
	}
	
	public function action_default(){
		$result = new PluginResponce();
		$result->pageTitle = "Register a new user";
		//Make the welcome block
		$oWelcomeBlock = new Cblock();
		$oWelcomeBlock->setContent(
			"
				<p>Please complete the below form to register for a user account. Email address is mandatory, you may be asked to click a link in an email to verify your account.</p>
				
			");
		
		//Get the form object
		$form = $this->get_registration_form(new User());
		
		//Build up the page in code	
		$result->xml.= CreateTag("Cblock",$oWelcomeBlock->getXML());
		$result->xml.= $form->getXML();
		
		
		return $result;
	}
	
	public function action_submit(){
		$result = new PluginResponce();
		//print_r_html($_POST);
		$oUser = new User();
		foreach($_POST as $key => $value){
			$setter = "set".ucfirst($key);
			$oUser->$setter($value);
		}
		if($oUser->validate()){
			//Validation Okay
			$oUser->setPassword(hash("SHA1",$oUser->getPassword()));	
			$oUser->setLevel(1);
			$oUser->setActive(1);
			$oUser->setRegisteredDate(time());
			$oUser->save();
			header("Location: thankyou");
		}else{
			//Validation Failed
			//print_r_html($_SESSION['turbo_form_errors']);
			$result->pageTitle = "Oops! Cannot register, form incomplete";
		}

		$form = $this->get_registration_form($oUser);
	
		//Build up the page in code
		$result->xml.= $form->getXML();
		return $result;
	}
	
	public function action_thankyou(){
		$result = new PluginResponce();
		$result->pageTitle = "Thankyou :)";
		$oThankyouCblock = new Cblock();
		$oThankyouCblock->setContent(
			'
				<p>Thanks for registering!</p>
				<p>You can now <a href=/plugin/login>login in</a> to the users area.</p>
			');
		$result->xml .= CreateTag("Cblock",$oThankyouCblock->getXML());
		return $result;
	}
}
