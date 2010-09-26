<?php

class failureLog extends turboObject{
	
	public $image;
	public $user;
	protected $arrTable;
	
	public function __construct(){
		$this->arrTable = array(
			"id" => array(
				"type"			=> "int",
				"isKey"			=> TRUE
			),
			"message" => array(
				"type"	=> "text",
				"length" => STR_LEN_INF
			)
		);
		parent::__construct('failures',$this->arrTable);
	}
	
	
}


