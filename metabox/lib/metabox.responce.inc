<?php 

class metaboxResponce{
	public $status;
	public $errorString;
	public $query;
	public $user;
	
	public $responce;
	
	function __construct(){
		$this->status 			= 'unknown';
		$this->errorString		= '';
		$this->query['post'] 	= $_POST;
		$this->query['get'] 	= $_GET;
	}
	function crunch(){
		$this->responce['status'] 			= $this->status;
		$this->responce['query'] 			= $this->query;
		$this->responce['error_string'] 	= $this->errorString;
		if($this->user != null){
			$this->responce['user'] 			= $this->user->getSimpleObject();
		}
		return $this->responce;
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