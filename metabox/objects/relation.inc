<?php

class metabox_relation extends turboObject{
	
	public $image;
	public $user;
	protected $arrTable;
	
	public function __construct(){
		$this->arrTable = array(
			"id" => array(
				"type"			=> "int",
				"isKey"			=> TRUE
			),
			"imageid"	=> array(
				"type"	=> "int"
			),
			"tagid" => array(
				"type"	=> "int"
			)
		);
		parent::__construct('mrelation',$this->arrTable);
	}
	
}


