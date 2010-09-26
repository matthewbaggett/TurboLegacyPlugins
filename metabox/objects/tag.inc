<?php

class metabox_tag extends turboObject{
	
	public $image;
	public $user;
	protected $arrTable;
	
	public function __construct($value = null){
		$this->arrTable = array(
			"id" => array(
				"type"			=> "int",
				"isKey"			=> TRUE
			),
			"value"	=> array(
				"type"	=> "text",
				"length"=> 40
			),
			"description" => array(
				"type"	=> "text",
				"length" => STR_LEN_INF
			)
		);
		parent::__construct('mtags',$this->arrTable);
		
		if($value != null){
			try{
				$this->loadByValue($value);
			}catch(Exception $e){
				//There is no tag by this value yet, so add one
				$this->setValue($value);
				$this->setDescription("Add a value for the tag '{$value}'");
				$this->save();
				$this->reload();
			}
		}
	}
	
	public function loadByValue($value){
		return $this->loadBySpecial('value',$value);
	}
	
	public function setValue($value){
		//Special processing for the Value
		$args[0] = strtolower($value);
		return $this->doTurboObjectCall('setValue', $args);
	}
	
}


