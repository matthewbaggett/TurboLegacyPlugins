<?php
class blogBackendModule{
	private $blogController;
	
	public function __construct(){
		$this->blogController = new blogController();
	}
	
	function action_default(){
		$arrayOfBlogs = $this->blogController->latestBlogs(10);
		
		$responce = new PluginResponce();
		$responce->pageTitle = 'Blog';
		$responce->xsl = 'blog-list.xsl';
		
		foreach($arrayOfBlogs as $blog){
			//print_r_html($blog);
			$blogsxml .= CreateTag("Blog",$blog->getXML());
		}
		$responce->xml = CreateTag("Blogs",$blogsxml);
		$responce->xml.= CreateTag("BlogPageTitle","Latest posts");
		return $responce;
	}
	
	function action_new(){
		$responce = new PluginResponce();
		$responce->pageTitle = "Blog Admin - New";

		$responce->xml.= $this->getAllAuthors();
		return $responce; 
	}
	function action_edit(){
		$responce = new PluginResponce();
		$responce->pageTitle = "Blog Admin - Edit";
		//print_r_html($_POST);
		if(isset($_POST['nextaction'])){
			if($_POST['nextaction'] == 'new_blog_entry'){
				$blogpost = new BlogPost();
				$blogpost->setTitle(trim($_POST['title']));
				$blogpost->setUserID($_POST['author']);
				$blogpost->setPublished_Date(time());
				$blogpost->setPublished_State(BLOG_STATE_UNPUBLISHED);
			}
		}else{
			$blogpost = new BlogPost();
			if(isset($_POST['id'])){
				$thisID = $_POST['id'];
			}else{
				$thisID = $_GET['id'];
			}
			
			$blogpost->loadByID($thisID);
			//print_r_html($blogpost);
			//die();
			if(isset($_POST['title'])){					$blogpost->setTitle(trim($_POST['title'])); 						}
			if(isset($_POST['author'])){				$blogpost->setUserID($_POST['author']);								}
			if(isset($_POST['published_date'])){		$blogpost->setPublished_Date(strtotime($_POST['published_date']));	}
			if(isset($_POST['article'])){				$blogpost->setArticle(trim($_POST['article']));						}
			//print_r_html($_POST);
			if(isset($_POST['published'])){
				if($_POST['published'] == 'on'){
					$blogpost->setPublished_State(BLOG_STATE_PUBLISHED);
				}else{
					$blogpost->setPublished_State(BLOG_STATE_UNPUBLISHED);
				}
			}
		}
		$blogpost->save();
		$responce->xml.= $this->getAllAuthors();
		$responce->xml.= CreateTag("Blogpost",$blogpost->getXml());
		return $responce;
	}
	function action_list(){
		$responce = new PluginResponce();
		$responce->pageTitle = "Blog Admin - List";
		
		$sql = "SELECT * FROM blogposts ORDER BY published_date DESC";
		$result = DB::Query($sql);
		while($row = DB::result_array($result)){
			$oBlog = new BlogPost();
			$oBlog->loadByRow($row);
			$blogsXML .= CreateTag("Blog",$oBlog->getXML());
		}
		$responce->xml.= CreateTag("Blogs",$blogsXML);
		
		return $responce;
	}
	
	function getAllAuthors(){
		//Get all Authors
		$sql = "SELECT * FROM users WHERE active = 1";
		$result = DB::Query($sql);
		while($row = DB::result_array($result)){
			$oUser = new User();
			$oUser->loadByRow($row);
			$users[] = $oUser;
		}
		foreach($users as $user){
			$usersXML.= CreateTag("Author",$user->getXML());
		}
		return CreateTag("Authors",$usersXML);
	}
}




