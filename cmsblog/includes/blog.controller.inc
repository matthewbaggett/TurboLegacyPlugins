<?php 
class blogController extends genericController{
	public function __construct(){
		parent::__construct('blogPost');
	}
	public function latestBlogs($num = 5){
		
		$this->populateFromSQL("SELECT * FROM blogposts ORDER BY published_date, title LIMIT $num");
		$arrayOfBlogs =  $this->getObjectArray();
		
		return $arrayOfBlogs;
	}

	public function getByIDFromDB($id){
		$this->populateFromSQL(
			sprintf(
				"SELECT * FROM blogposts WHERE id = '%d'",
				$id
			)
		);
	}
	public function getByAuthor($auth){
		$this->clearStore();
		$this->populateFromSQL(
			sprintf(
				"
					SELECT bp.*
					FROM blogposts bp
					JOIN users u
					  ON u.id = bp.userid
					WHERE u.username = '%s'
				",
				$auth
			)
		);
	
		return $this->objectStore;
	}
}

