<?php

class apikey extends turboObject{
	
	public $image;
	public $user;
	protected $arrTable;
	
	public function __construct(){
		$this->arrTable = array(
			"id" => array(
				"type"			=> "int",
				"isKey"			=> TRUE
			),
			"userid" => array(
				"type"	=> "int",
			),
			"apikey" => array(
				"type"	=> "text",
				"length" => STR_LEN_INF,
			)
		);
		parent::__construct('apikeys',$this->arrTable);
	}
	
	public function loadByKey($key){
		try{
			$this->loadBySpecial('apikey',$key);
		}catch(Exception $e){
			return false;
		}
		$this->loadMyUser();
		
		return $this->user;
	}
	
	private function loadMyUser(){
		$this->user = new User();
		$this->user->loadByID($this->getUserID());
	}
	
}


