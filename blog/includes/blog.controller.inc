<?php 
class blogController extends genericController{
	function __construct(){
		parent::__construct('blogPost');
	}
	function latestBlog($numberToReturn = 10){
		
		$this->populateFromSQL("SELECT * FROM blogposts ORDER BY published_date, title LIMIT $numberToReturn");
		return $this->getObjectArray();
	}
}
