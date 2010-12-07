<?php

$cdn_cache = array();

class cdn{
	//Check that the CDN is a mirror of our /data directory
	public function action_mirror(){
	}
	
	public function is_file_available($md5){
		if(isset($cdn_cache[$md5])){
			return $cdn_cache[$md5];
		}else{
			return FALSE;
	}
	public function get_link_from_file($file_location){
		$md5 = md5_sum($file_location);
		$from_cdn = $this->is_file_available($md5);
		if($from_cdn !== FALSE){
			return $from_cdn->url();
		}else{
			//Whereever it is in /data
			return "wat";
		}
	}
}

