<?php 

class imagecache{
	function action_fetch($var){
		$process_name = $var[1];
		
		$file_request = ltrim($var[2],"/");
		$bits = explode("/",$file_request);
		$uuid = end($bits);
		$oImage = new Image();
		$oImage->loadByDisplayID($uuid);
		$oImage->loadMyFileObject();
		$diskLocation = "../data/" . $oImage->file->getDisklocation();
		
		$oDim = new imagecache_dimention($process_name);
		print_r_html($oDim->arrOfValues);
		$oChromatica = new chromaticaImage();
		
		$oChromatica->addLayer(new chromaticaLayer($diskLocation), CHROMATICA_TOP_LEFT, 0,0);
		$oChromatica->crunch();
		$oChromatica->scale($oDim->getX(),$oDim->getY());
		$output = $oChromatica->crunch();
		header("Content-type: {$oChromatica->mime}");
		echo $output;
	}
}