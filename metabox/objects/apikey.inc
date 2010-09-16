<?php

class apikey extends turboObject{
	
	public $image;
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
	
}


