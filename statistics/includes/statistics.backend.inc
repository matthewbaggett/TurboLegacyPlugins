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
				SELECT path, count(id) as freq FROM `loggedpaths` GROUP BY path ORDER BY count(id) DESC LIMIT 15
				";
		$results = DB::Query($sql,"Statistics Plugin - action_pageviews");
		
		while($row = DB::result_object($results)){
			$pageViewsPopularity[] = $row;
		}
		
		$g = new graph();

		// Spoon sales, March 2007
		$g->title( 'Spoon sales '. date("Y"), '{font-size: 26px;}' );
		
		$g->set_data( $data );
		// label each point with its value
		$g->set_x_labels( array('Most Popular','2nd','3rd','4th','5th','6th','7th','8th','9th','10th','11th','12th','13th','14th','15th' ) );
		
		// set the Y max
		$g->set_y_max( 60 );
		// label every 20 (0,20,40,60)
		$g->y_label_steps( 6 );
		
		// display the data
		
		
		$pageViewsXML = CreateTag("PageViewsPopulatity", $g->render());
		
		$responce->xml.= CreateTag("Statistics",$pageViewsXML);
		
		return $responce;
		
	}
}




