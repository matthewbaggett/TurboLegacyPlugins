<?php
class blogModule{
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
	
	function action_search_by_author($variables){
		$arrayOfBlogs = $this->blogController->getByAuthor($variables[1]);
		
		//Load the author's object.
		$oUser = new User();
		$oUser->loadByUsername($variables[1]);
		
		
		$responce = new PluginResponce();
		$responce->pageTitle = "Blog posts by {$oUser->getFirstname()} {$oUser->getSurname()}";
		$responce->xsl = 'blog-list.xsl';
		foreach($arrayOfBlogs as $blog){
			//print_r_html($blog);
			$blogsxml .= CreateTag("Blog",$blog->getXML());
		}
		$responce->xml.= CreateTag("Blogs",$blogsxml);
		$responce->xml.= CreateTag("BlogPageTitle","Blog posts by {$oUser->getFirstname()} {$oUser->getSurname()}");
		return $responce;
	}
	
	function action_read_one($variables){
		$blogPost = $this->blogController->getById($variables[1]);
		
		$responce = new PluginResponce();
		$responce->pageTitle = 'Blog';
		$responce->xsl = 'blog-read-one.xsl';
		$responce->xml.= CreateTag("Blog",$blogPost->getXML());
		
		return $responce;
	}
	function action_rss($variables){
		$responce = new PluginResponce();
		$responce->pageTitle = "RSS FEED";
		$responce->xsl = '../plugins/blog/xsl/rss.xsl';
		
		$arrayOfBlogs = $this->blogController->getAll(100);
		foreach($arrayOfBlogs as $blog){
			//print_r_html($blog);
			$blogsxml .= CreateTag("Blog",$blog->getXML());
		}
		$responce->xml.= CreateTag("Blogs",$blogsxml);
		return $responce;
	}
}




