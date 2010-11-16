<?php
class Movements extends turboObject{
	
	protected $arrTable;
	
	public function __construct($id_to_load = false){
		$this->arrTable = array(
			"id" => array(
				"type"			=> "int",
				"isKey"			=> TRUE
			),
			"movements" => array(
				"type"	=> "text",
				"length" => STR_LEN_INF,
				"force-escape" => true
			),
			"userid" => array(
				"type"	=> "int"
			)
			
		);
		parent::__construct('log_movements',$this->arrTable);
		if($id_to_load !== FALSE){
			$this->loadById($id_to_load);
		}
	}
}
