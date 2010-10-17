<?php 
//Where is cwd now...
$oldcwd_mbox = getcwd();	
//Move to where we are right now...
chdir(dirname(__FILE__));	
//Require in the files we want
require_once("./metabox.curl.inc");
//Move back to the old cwd.
chdir($oldcwd_mbox);	

class METABOX{
	//The server to make the API accesses to
	static public $server = "http://api.indexi.eu.org/";
	//The key with which to login
	static public $api_key = "NOKEY";
	//Weather or not to use debug mode.
	static public $debug = "OFF";

	static public function upload($imageFile,$imageTags){
		$curl = new METABOX_CURL(self::$server."push/");
		$postArray = array(
			'apiKey' 		=> self::$api_key,
			'imageFile' 	=> $imageFile,
			'imageTags' 	=> implode(",",$imageTags),
			'debug'			=> self::$debug
		);
		$curl->setPost($postArray);
		$curl->go();
		
		if($responce = json_decode($curl->__tostring())){
			return $responce;
		}else{
			fb::error("Responce from METABOX::UPLOAD not JSON");
			fb::group("Responce");
			fb::log($curl->__tostring());
			fb::groupEnd();
			throw new exception("Responce from METABOX::UPLOAD not JSON");
		}
	}
	
	static public function get_file($imageFile){
		$curl = new METABOX_CURL(self::$server."get/file/");
		$postArray = array(
			'apiKey' 		=> self::$api_key,
			'imageFile' 	=> $imageFile,
			'imageTags' 	=> json_encode($imageTags)
		);
		$curl->setPost($postArray);
		$curl->go();
		echo "\n\nMETABOX RESPONCE:\n";		
		echo $curl;
		echo "\n\n\n";
	}
	
	static public function search($keywords){
		fb::group("Metabox - Search (".implode(", ",$keywords).")");
		$curl = new METABOX_CURL(self::$server."search?apiKey=".self::$api_key."&search".implode(",",$keywords));
		$postArray = array(
			'debug'			=> self::$debug
		);
		$curl->setPost($postArray);
		$curl->go();
		if($responce = json_decode($curl->__tostring())){
			return $responce;
		}else{
			fb::error("Responce from METABOX::SEARCH not JSON");
			fb::group("Responce");
			fb::log($curl->__tostring());
			fb::groupEnd();
			throw new exception("Responce from METABOX::SEARCH not JSON\n\n\n"."<pre>{$curl->__tostring()}</pre>");
		}
		fb::groupEnd();
	}
}
