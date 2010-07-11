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
		
		$responce = new PluginResponce();
		$responce->pageTitle = 'Blog posts by {$variables[1]}';
		$responce->xsl = 'blog-list.xsl';
		foreach($arrayOfBlogs as $blog){
			//print_r_html($blog);
			$blogsxml .= CreateTag("Blog",$blog->getXML());
		}
		$responce->xml.= CreateTag("Blogs",$blogsxml);
		$responce->xml.= CreateTag("BlogPageTitle","Blog posts by {$variables[1]}");
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
}

PluginController::bind('blog',array('blogModule','default'));
PluginController::bind('blog/post/([0-9]+)_(.*)',array('blogModule','read_one'));
PluginController::bind('blog/author/(.*)', array("blogModule",'search_by_author'));

