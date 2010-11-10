<?php 

define("CACHING_ON",false);

class imagecache{
	function action_fetch($args){
		$process_name = $args[1];
		
		$file_request = ltrim($args[2],"/");
		$bits = explode("/",$file_request);
		$uuid = end($bits);
		$oImage = new Image();
		$oImage->loadByDisplayID($uuid);
		$oImage->loadMyFileObject();
		$diskLocation = "../data/" . $oImage->file->getDisklocation();
		
		$oDim = new imagecache_dimention($process_name);
		//print_r_html($oDim->arrOfValues);
		$oChromatica = new chromaticaImage();
		
		$oChromatica->addLayer(new chromaticaLayer($diskLocation), CHROMATICA_TOP_LEFT, 0,0);
		$oChromatica->crunch();
		$oChromatica->scale($oDim->getX(),$oDim->getY());
		$output = $oChromatica->crunch();
		header("Content-type: {$oChromatica->meta['mime']}");
		echo $output;
		exit;
	}
	
	function action_fetch_cdn($args){
		$process_name = $args[1];
		$cdn_file = $args[2];
		
		$cdn_cache = FS_ROOT."data/cache/image_cache/cdn/";
		
		$this_request_cache_dir = $cdn_cache.dirname($cdn_file);
		$this_request_file		= basename($cdn_file);
		
		//Check cache for the CDN file
		$this_request_cache_original = $this_request_cache_dir."/".$this_request_file;
		if(file_exists($this_request_cache_original)){
			//Load file from cache
			$image_data = file_get_contents($this_request_cache_original);
		}else{
			//Download file, save to cache
			$image_data = curl_file_get_contents("http://".$cdn_file);
			@mkdir(dirname($this_request_cache_original),0777,true);
			file_put_contents($this_request_cache_original,$image_data);
		}
		
		$this_request_cache_processed = $this_request_cache_dir."/{$process_name}/".$this_request_file;
		
		//Check cache for the processed version.
		if(file_exists($this_request_cache_processed) && CACHING_ON/*Processed version exists and caching on*/){
			//If it exists, throw it at the client.
			//header("Content-type: {$oChromatica->mime}");
			$image_data_processed = file_get_contents($this_request_cache_processed);
			echo $image_data_processed;
		}else{
			//Process the image, save to disk, throw it at the client
			//echo "doop";
			$oDim = new imagecache_dimention($process_name);
			//print_r_html($oDim->arrOfValues);
			$oChromatica = new chromaticaImage();
			
			$oChromatica->addLayer(new chromaticaLayer($this_request_cache_original), CHROMATICA_TOP_LEFT, 0,0);
			$oChromatica->crunch();
			
			
			//We're done with chromatica almost, so set it to JPG mode and crunch out the image!
			$oChromatica->outputFormat = 'jpg';
			@mkdir(dirname($this_request_cache_processed),0777,true);
			$oChromatica->scaleAndCrunch($this_request_cache_processed,$oDim->getX(),$oDim->getY());
			
			$image_data_processed = file_get_contents($this_request_cache_processed);

			header("Content-type: {$oChromatica->meta['mime']}");
			echo $image_data_processed;
		}
		exit;
	}
}