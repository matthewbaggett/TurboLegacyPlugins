<?php
class timemachineModule{
	
	public function __construct(){
	}
	/*
	 * The default action
	 */
	function action_default(){
		
		$responce = new PluginResponce();
		die("Doop, time machine");
		return $responce;
	}
	/*
	 * Function to get a specific version of a specific page
	 */
	function action_version_get($variables){
		$result = new PluginResponce();
		
		$uuid = $variables[1];
		$version = $variables[2];
		print_r($variables);
		$sql = sprintf(
			"SELECT * FROM pages WHERE pageuuid = '%s' AND version = '%d' LIMIT 1",
			DB::escape_string($uuid),
			DB::escape_number($version)
		);
		echo $sql;
		$result = DB::Query($sql);
		echo "<b>Found ".DB::rows($result)." rows()</b><br />";
		if(DB::rows($result)){
			$row = DB::result_array($result);
			$oPage = new page();
			$oPage->loadByRow($row);
			$result->pageTitle = $oPage->getPageName();
			$result->xml = $oPage->getXML();
		}
		return $result;
		
	}
	
	
}




