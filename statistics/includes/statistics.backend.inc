<?php

class statisticsBackendModule{
	
	public function __construct(){
	}
	
	function action_default(){
		echo "default action";
	}
	
	function action_pageviews(){
		if(PluginController::pluginAvailable("graph")){
			echo "You're trying to use functionality from the GRAPH plugin.. It is not installed :(";
			return;
		}else{
			$responce = new PluginResponce();
			$responce->pageTitle = "Statistics - Page views";
			
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
			
			TURBO::add_js('file', '/turbo/js/json2.js');
			TURBO::add_js('file', '/turbo/js/swfobject.js');
			TURBO::add_js('inline', 'swfobject.embedSWF("http://assets.turbocrms.com/open-flash-chart.swf", "pageviews_chart", "350", "200", "9.0.0");');
			TURBO::add_js_var('pageviews_chart_json', $chart->toPrettyString(),true);
			TURBO::add_js('inline',
				'
				function ofc_ready()
				{
					alert("ofc_ready");
				}
 
				function open_flash_chart_data()
				{
					alert("reading data");
					return JSON.stringify(data_1);
				}
				 
				function load_1()
				{
				  tmp = findSWF("pageviews_chart");
				  tmp = $("#pageviwes_chart");
				  x = tmp.load( pageviews_chart_json );
				}
				 
				function load_2()
				{
				  alert("loading data_2");
				  tmp = findSWF("pageviews_chart");
				  x = tmp.load( JSON.stringify(data_2) );
				}
				 
				function findSWF(movieName) {
				  if (navigator.appName.indexOf("Microsoft")!= -1) {
				    return window[movieName];
				  } else {
				    return document[movieName];
				  }
				}
				$(document).ready(function(){
				load_1();
				});
				
				'
			);			
			$pageViewsXML = CreateTag("Chart", $chart->toPrettyString());
			
			$responce->xml.= CreateTag("Statistics",$pageViewsXML);
			
			return $responce;
			
		}
	}
}




