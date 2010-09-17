<?php
class metaboxModule{
	private $blogController;
	
	public function __construct(){
		$this->blogController = new blogController();
	}
	
	function action_default(){
		
	}
	
	function action_search_by_author($variables){
		
	}
	function action_push(){
		if(self::checkApiKey($_POST['apiKey'])){
			print_r($_POST);
		}else{
			return self::failure("Invalid APIKEY");
		}
	}
	static function failure($failure){
		$responce = metaboxResponce();
		$responce->
	}
	

}




