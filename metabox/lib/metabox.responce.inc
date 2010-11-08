<?php 

class metaboxResponce{
	public $status;
	public $statusString;
	public $query;
	public $user;
	public $image;
	public $data;
	public $debugArray;
	
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
		if(is_object($this->data) || is_array($this->data)){
			
			foreach($this->data as $elem){
				if(is_object($elem)){
					$this->responce['data'][]			= $elem->getSimpleObject();
				}else{
					$this->responce['data'][]			= $elem;
				}
			}
		}
		if($_POST['debug'] == 'ON'){
			$this->responce['debugArray'] = $this->debugArray;
		}
		
		if($_POST['debug'] == 'ON'){
			$this->responce['processingTime'] = microtime(true) - START_MTIME;
			global $svn_version;
			$this->responce['version'] = $svn_version;
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
