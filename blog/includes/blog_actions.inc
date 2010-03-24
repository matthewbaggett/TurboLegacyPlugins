<?php
class blogModule{
	function action_default(){
		global $strPageXSL;
		$actionResponce = new ActionResponce();
		$actionResponce->xsl = 'blog.xsl';
		$blogController = new blogController();
		$blogController->latestBlog();
		$blogPosts = $blogController->latestBlog(10);
		$blogXML = CreateTag("BlogPosts",arrayToXML($blogPosts));
		
		return $actionResponce;
	}
}