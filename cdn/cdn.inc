<?php

class cdn{
	static $cdn_cache;
	//Get the CDN cache. This is the contents of a table that explains what is in the cache already.
	public function action_load_cdn_cache(){
		$query = new TurboQuery("SELECT","cache_cdn");
		$results = $query->execute();
		$results_keyed = array();
		if(count($results) > 0){
			foreach($results as $result){
				$results_keyed[$result->path] = $result;
			}
		}
		cdn::$cdn_cache = $results_keyed;
	}
	//Prime various componants before use...
	public function action_prime(){
		//Prime the connection to the metabox...
		METABOX::$server 	= turbo_get_setting("METABOX_SERVER");
		METABOX::$api_key	= turbo_get_setting("METABOX_API_KEY");
		METABOX::$dataset	= turbo_get_setting("METABOX_DATASET");
		METABOX::$debug		= "ON";
		
		cdn::$cdn_cache = array();
	}
	//Check that the CDN is a mirror of our /data directory
	public function action_mirror(){
		$directory_listing = $this->scan_directory("../data/files");
		fb::warn($directory_listing);
		foreach($directory_listing as $file){
			if(isset(cdn::$cdn_cache[$file])){
				//file is in CDN
			}else{
				//file is not in CDN
				$this->push_to_cdn($file);
			}
		}
		
		foreach(cdn::$cdn_cache as $cache_file){
			$obj = unserialize($cache_file->object);
		}
	}
	public function action_pulldown(){
		foreach(cdn::$cdn_cache as $cdn_cache_item){
			$cdn_cache_item->object_unpacked = unserialize($cdn_cache_item->object);
			print_r_html($cdn_cache_item);
			echo "Testing to see if {$cdn_cache_item->path} exists...";
			if(file_exists($cdn_cache_item->path)){
//				echo "Nothing to do, file present<br />";
			}else{
				echo "Pull down, file missing... <br />";
				$file = "http://static.indexi.eu.org/{$cdn_cache_item->object_unpacked->file}";
				echo "Pulling from '$file'... ";
				$data = curl_file_get_contents($file);

				if(strlen($data) > 0){
					echo strlen($data)." bytes OK<br />\n";
					echo "In ".getcwd()."<br />\n";
					@mkdir(dirname($cdn_cache_item->path),0777,true);
					file_put_contents($cdn_cache_item->path,$data);
				}else{
					echo "FAIL! Cannot download file!<br />";
				}
			}
		}
	}
	
	public function push_to_cdn($file){
		HOOKS::call("CDN_PUSH_TO_CDN");
		$m_responce = METABOX::upload_file($file);
		if($m_responce->status != 'OKAY'){
			throw new exception("There was a CDN fault :( Contact Grey/Matt");
		}else{
			$oFile = new File();
			$oFile->loadBySpecial('disklocation',$file);
			$oImage = new Image();
			$oImage->loadBySpecial('fileobjectid',$oFile->getId());
			$cdn_obj = $m_responce->image;
			$cdn_obj_serialized = serialize($cdn_obj);
			$sql = "INSERT INTO `cache_cdn` (`image_id`, `path`, `object`) VALUES ('{$oImage->getId()}', '{$file}', '{$cdn_obj_serialized}')";
			DB::Query($sql);
		}
	}
	
	public function is_file_available($md5){
		if(isset($cdn_cache[$md5])){
			return $cdn_cache[$md5];
		}else{
			return FALSE;
		}
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
	
	private function scan_directory($directory, $recursive = true,$exclude_folders_from_listing = true) {
		$array_items = array();
		if ($handle = opendir($directory)) {
			while (false !== ($file = readdir($handle))) {
				if ($file != "." && $file != "..") {
					if (is_dir($directory. "/" . $file)) {
						if($recursive) {
							$array_items = array_merge($array_items, $this->scan_directory($directory. "/" . $file, $recursive,$exclude_folders_from_listing));
						}
						$file = $directory . "/" . $file;
						if($exclude_folders_from_listing == false){
							$array_items[] = preg_replace("/\/\//si", "/", $file);
						}
					} else {
						$file = $directory . "/" . $file;
						$array_items[] = preg_replace("/\/\//si", "/", $file);
					}
				}
			}
			closedir($handle);
		}
		return $array_items;
	}
}

