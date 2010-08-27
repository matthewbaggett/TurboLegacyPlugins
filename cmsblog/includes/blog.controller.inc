<?php 
class blogController extends genericController{
	public function __construct(){
		parent::__construct('blogPost');
	}
	public function latestBlogs($num = 5){
		
		$this->populateFromSQL("SELECT * FROM blogposts WHERE published_state = 1 ORDER BY published_date DESC, title LIMIT $num");
		$arrayOfBlogs =  $this->getObjectArray();
		
		return $arrayOfBlogs;
	}

	public function getByIDFromDB($id){
		
		$this->populateFromSQL(
			sprintf(
				"SELECT * FROM blogposts WHERE id = '%d' AND published_state = 1 ",
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
					AND published_state = 1 
				",
				$auth
			)
		);
	
		return $this->objectStore;
	}
	public function getAll($limit = 50){
		$this->clearStore();
		$this->populateFromSQL(
				"
					SELECT bp.*
					FROM blogposts bp
					WHERE bp.published_state = 1 
					ORDER BY published_date DESC
					LIMIT $limit
				"
		);
	
		return $this->objectStore;
	}
}

