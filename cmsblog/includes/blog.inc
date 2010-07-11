<?php 
class blogPost extends turboObject{
	public function __construct(){
		$this->arrTable = array(
			"id" => array(
				"type"			=> "int",
				"isKey"			=> TRUE
			),
			"userid" => array(
				"type"	=> "int",
				"length" =>10
			),
			"title" => array(
				"type"	=> "text",
				"length" =>255
			),
			"article" => array(
				"type"	=> "text",
				"length" =>STR_LEN_INF,
				"force-escape" => TRUE
			),
			"published_date"=>array(
				"type" => "int",
				"length" =>10
			)
		);
		parent::__construct('blogposts',$this->arrTable);
		
	}
	public function getXML($wrapperName = null,$insertedXML = null){
		$insertedXML.= CreateTag("URL",$this->getID()."_".str_replace(" ","-",$this->getTitle()));
		$oUser = new user();
		$oUser->loadByID($this->getUserID());
		$insertedXML.= CreateTag("Author",$oUser->getXML());
		return parent::getXML($wrapperName,$insertedXML);
	}
}
