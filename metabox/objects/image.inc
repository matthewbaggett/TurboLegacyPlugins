<?php

class metabox_image extends turboObject{
	
	public $image;
	public $user;
	public $tags;
	protected $arrTable;
	
	public function __construct(){
		$this->arrTable = array(
			"id" 		=> array("type" => "int",		"isKey" 	=> TRUE),
			"uuid"		=> array("type"	=> "string",	"length"	=> 40),
			"userid" 	=> array("type"	=> "int"),
			"datasetid"	=> array("type" => "int"),
			"source" 	=> array("type"	=> "text",		"length" 	=> STR_LEN_INF),
			"md5" 		=> array("type"	=> "string",	"length"	=> 40),
			"sha1" 		=> array("type"	=> "string",	"length"	=> 40),
			"size" 		=> array("type"	=> "int"),
			"file" 		=> array("type"	=> "text",		"length" => STR_LEN_INF	)
		);
		parent::__construct('mimages',$this->arrTable);
	}
	
	
	public function loadByUUID($uuid){
		try{
			$this->loadBySpecial('uuid',$uuid);
		}catch(Exception $e){
			return false;
		}
		return $this;
	}
	public function loadMyChildrenObjects(){
		$this->loadMyUser();
		$this->loadMyTags();
	}
	
	private function loadMyUser(){
		if($this->getUserID()){
			$this->user = new User();
			$this->user->loadByID($this->getUserID());
		}
	}
	private function loadMyTags(){
		$sql = "
			SELECT tags.*
			FROM `mrelation` relations 
			JOIN `mtags` tags
			  ON tags.id = relations.tagid
			WHERE relations.`imageid` = {$this->getID()}
			";
		$result = DB::Query($sql);
		while($row = DB::result_array($result)){
			$oTag = new metabox_tag();
			$oTag->loadByRow($row);
			$this->tags[] = $oTag;
		}
	}
	
	public function uuidGenerate(){
		return uuid();
	}
}


