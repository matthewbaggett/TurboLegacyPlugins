<?php

class statisticsBackendModule{
	
	public function __construct(){
	}
	
	function action_default(){
		echo "default action";
	}
	
	function action_pageviews(){
		if(!PluginController::pluginAvailable("flashgraphs")){
			echo "You're trying to use functionality from the FlashGraph plugin.. It is not Installed.";
			return;
		}else{
			$responce = new PluginResponce();
			$responce->pageTitle = "Statistics - Page views";

			TURBO::add_js('inline', 
				"</script>\n\n".
				open_flash_chart_object_str(500,300,'http://'. $_SERVER['SERVER_NAME'] .'/plugins/statistics/stats_fetch.php?chart=pageviews',true,'http://'. $_SERVER['SERVER_NAME'] .'/turbo/').
				"\n<script>"
				);
				
			$pageViewsXML = CreateTag("Chart","");
			
			$responce->xml.= CreateTag("Statistics",$pageViewsXML);
			
			return $responce;
			
		}
	}
}




