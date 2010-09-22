<?php

class metabox_image extends turboObject{
	
	public $image;
	public $user;
	protected $arrTable;
	
	public function __construct(){
		$this->arrTable = array(
			"id" => array(
				"type"			=> "int",
				"isKey"			=> TRUE
			),
			"uuid"	=> array(
				"type"			=> "string",
				"length"		=> 40
			),
			"userid" => array(
				"type"	=> "int"
			),
			"source" => array(
				"type"	=> "text",
				"length" => STR_LEN_INF
			),
			"md5" => array(
				"type"			=> "string",
				"length"		=> 40
			),
			"sha1" => array(
				"type"			=> "string",
				"length"		=> 40
			),
			"size" => array(
				"type"			=> "int",
			),
		);
		parent::__construct('mimages',$this->arrTable);
	}
	
	public function loadByUUID($uuid){
		try{
			$this->loadBySpecial('uuid',$uuid);
		}catch(Exception $e){
			return false;
		}
		$this->loadMyUser();
		
		return $this;
	}
	
	private function loadMyUser(){
		if($this->getUserID()){
			$this->user = new User();
			$this->user->loadByID($this->getUserID());
		}
	}
	
	public function uuidGenerate(){
		return uuid();
	}
}


