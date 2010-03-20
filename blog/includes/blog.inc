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
				"length" =>STR_LEN_INF
			),
			"published_date"=>array(
				"type" => "int",
				"length" =>10
			)
		);
		parent::__construct('blogposts',$this->arrTable);
		
	}
}
