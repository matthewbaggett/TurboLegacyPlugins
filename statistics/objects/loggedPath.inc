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
			),
			"ip" => array(
				"type"		=> "string",
				"length"	=> 15
			),
			'countryCode'	=> array(
				"type"		=> "string",
				"length"	=> 3
			),
			'countryName'	=> array(
				"type"		=> "string",
				"length"	=> 30
			),
			'region'	=> array(
				"type"		=> "string",
				"length"	=> 30
			),
			'city'	=> array(
				"type"		=> "string",
				"length"	=> 30
			),
			'postalCode'	=> array(
				"type"		=> "string",
				"length"	=> 30
			),
			'latitude'	=> array(
				"type"		=> "string",
				"length"	=> 30
			),
			'longitude'	=> array(
				"type"		=> "string",
				"length"	=> 30
			),
			'geoipProcessed' => array(
				"type"		=> "int",
				"length"	=> 1
			)
		);
		parent::__construct('loggedPaths',$this->arrTable);
	}
}
