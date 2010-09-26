<?php 

class metaboxResponce{
	public $status;
	public $statusString;
	public $query;
	public $user;
	public $image;
	
	public $responce;
	
	function __construct(){
		$this->status 			= 'unknown';
		$this->statusString		= '';
		$this->query['post'] 	= $_POST;
		$this->query['get'] 	= $_GET;
	}
	function crunch(){
		global $availablePlugins;
		$this->responce['server']			= CLUSTER_NODE;
		$this->responce['status'] 			= $this->status;
		$this->responce['status_string'] 	= $this->statusString;
		if($_POST['debug'] == "ON"){
			$this->responce['query'] 			= $this->query;
			$this->responce['plugins']			= $availablePlugins;
		}
		if(is_object($this->user)){
			$this->responce['user'] 			= $this->user->getSimpleObject();
		}
		if(is_object($this->image)){
			$this->responce['image']			= $this->image->getSimpleObject();
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