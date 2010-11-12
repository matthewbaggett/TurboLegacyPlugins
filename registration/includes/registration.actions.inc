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
		
		$form = $this->get_registration_form(new User());
		$result->xml = $form->getXML();
		
		return $result;
	}
}
