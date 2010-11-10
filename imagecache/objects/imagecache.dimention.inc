<?php

class imagecache_dimention extends turboObject{
	
	public $image;
	public $user;
	protected $arrTable;
	protected $schema;
	
	public function __construct($name = null){
		$this->schema = '
			{
				"id": {
					"type":		"int",
					"isKey":	true
				},
				"name": {
					"type":		"text",
					"length":	40
				},
				"x": {
					"type":		"int"
				},
				"y": {
					"type":		"int"
				},
				"description": {
					"type":		"text",
					"length":	-1
				},
				"effects": {
					"type":		"text",
					"length":	-1
				}
			}
		';
		$this->arrTable = json_decode($this->schema,true);
		parent::__construct('imagecache_dimention',$this->arrTable);
		if($name != null){
			try{
				$this->loadBySpecial("name",$name);
			}catch(Exception $e){
				//There is no tag by this value yet, so add one
				$this->setName($name);
				$this->setDescription("Add a description for the dimention record '{$name}'");
				$this->save();
				$this->reload();
			}
		}
	}
	
	public function setName($name){
		//Special processing for the Value
		$args[0] = strtolower($name);
		return $this->doTurboObjectCall('setname', $args);
	}
	
}


