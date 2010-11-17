<?php

require_once("../../turbo/turbo.inc");

switch($_GET['chart']){
	case 'pageviews':
		$sql = "
				SELECT path, count(id) as freq FROM `log_access` GROUP BY path ORDER BY count(id) DESC LIMIT 15
				";
		$results = DB::Query($sql,"Statistics Plugin - action_pageviews");
		
		while($row = DB::result_object($results)){
			$pageViewsPopularity[] = $row;
		}
		
		$title = new OFC_Elements_Title( date("D M d Y") );
		
		$bar = new OFC_Charts_Bar();
		$bar->set_values( array(9,8,7,6,5,4,3,2,1) );
		
		$chart = new OFC_Chart();
		$chart->set_title( $title );
		$chart->add_element( $bar );
		echo $chart->toPrettyString();
		break;
	default:
		die("oops!");
}
