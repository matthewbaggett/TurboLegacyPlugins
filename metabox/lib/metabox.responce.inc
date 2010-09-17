<?php 

class metaboxResponce{
	public $status;
	public $query;
	public $responce;
	
	function __construct(){
		$this->status 			= 'unknown';
		$this->query['post'] 	= $_POST;
		$this->query['get'] 	= $_GET;
	}
	function crunch(){
		$this->responce['status'] = $this->status;
		$this->responce['query'] = $this->query;
	}
	function getXML(){
		$this->crunch();
		//XMLify code
		return;
	}
	function getJSON(){
		$this->crunch();
		return json_encode($this->responce);
	}
	function get(){
		if(isset($_POST['method'])){
			if(strtoupper($_POST['method']) == "JSON"){
				return $this->getJSON();
			}
		}elseif(isset($_GET['method'])){
			if(strtoupper($_GET['method']) == "JSON"){
				return $this->getJSON();
			}
		}else{
			return $this->getXML();
		}
	}
}