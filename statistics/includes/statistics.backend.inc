<?php
class statisticsBackendModule{
	
	public function __construct(){
	}
	
	function action_default(){
		echo "default action";
	}
	
	function action_pageviews(){
		
		$responce = new PluginResponce();
		$responce->pageTitle = "Statistics - Page views";
		
		$sql = "
				SELECT count(p.id), p.*
				FROM loggedpaths p
				GROUP BY p.path
				ORDER BY count(p.id) DESC
				";
		$results = DB::Query($sql,"Statistics Plugin - action_pageviews");
		
		while($row = DB::result_object($results)){
		//	print_r($row);
		}
		
		$pageViewsXML = "Hi";
		
		$responce->xml.= CreateTag("Statistics",$pageViewsXML);
		
		return $responce;
		
	}
}




