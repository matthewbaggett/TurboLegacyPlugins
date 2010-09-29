<?php
class statisticsBackendModule{
	
	public function __construct(){
	}
	
	function action_default(){
		echo "default action";
	}
	
	function action_pageviews(){
		$sql = "
				SELECT count(p.id), p.*
				FROM loggedpaths p
				GROUP BY p.path
				";
		$results = DB::Query($sql,"Statistics Plugin - Action pageviews");
		exit;
	}
}




