<?php

class dataset extends turboObject{
	
	public $permissions;
	protected $arrTable;
	
	public function __construct($name = false){
		$this->arrTable = array(
			"id" => array(
				"type"			=> "int",
				"isKey"			=> TRUE
			),
			"name" => array(
				"type"			=> "text",
				"length" 		=> 40
			),
		);
		parent::__construct('mdataset',$this->arrTable);
		if($name !== false){
			$this->loadBySpecial('name', $name);
		}
	}
	
	public function loadMyChildrenObjects(){
		$this->permissions = array();
		$oDatasetPermission = new datasetPermissions();
		try{
			$sql = "SELECT * FROM mdataset_permissions WHERE datasetid = '{$this->getid()}'";
			$result = DB::Query($sql);
			while($row = DB::result_array($result)){
				$oDatasetPermission = new datasetPermissions();
				$oDatasetPermission->loadByRow($row);
				$this->permissions[] = $oDatasetPermission;
			}
		}catch(Exception $e){
		}
	}
	
	public function getPermission($userid){
		//print_r_html($this->permissions);
		foreach($this->permissions as $oPermission){
			//echo "{$oPermission->getUserID()} == $userid\n";
			if($oPermission->getUserID() == $userid){
				if($oPermission->getRead()){
					$perms[] = 'read';
				}
				if($oPermission->getWrite()){
					$perms[] = 'write';
				}
				return implode(",",$perms);
			}
		}
		return "none";
	}
	public function checkPermission($oUser,$levelNeeded){
		$permissions = $this->getPermission($oUser->getID());
		if(array_search($levelNeeded,explode(",",$permissions))){
			return true;
		}
		return false;
	}
	
	
}

class datasetPermissions extends turboObject{
	
	protected $arrTable;
	
	public function __construct(){
		$this->arrTable = array(
			"id" 			=> array("type" => "int",	"isKey"	=> TRUE),
			"datasetid" 	=> array("type" => "int"),
			"userid" 		=> array("type" => "int"),
			"read"			=> array("type" => "bool"),
			"write"			=> array("type" => "bool"),
		);
		parent::__construct('mdataset_permissions',$this->arrTable);
	}	
}





