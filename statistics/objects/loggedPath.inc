<?php
class loggedPath extends turboObject{
	
	protected $arrTable;
	
	public function __construct(){
		$this->arrTable = array(
			"id" => array(
				"type"			=> "int",
				"isKey"			=> TRUE
			),
			"path" => array(
				"type"	=> "text",
				"length" => STR_LEN_INF,
				"force-escape" => true
			),
			"handler" => array(
				"type"	=> "text",
				"length" => STR_LEN_INF,
				"force-escape" => true
			),
			"userid" => array(
				"type"	=> "int"
			)
		);
		parent::__construct('loggedPaths',$this->arrTable);
	}
}
