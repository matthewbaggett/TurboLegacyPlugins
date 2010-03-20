<?php
class blogModule{
	function action_default(){
		global $strPageXSL;
		$strPageXSL = 'blog.xsl';
		$blogController = new blogController();
		$blogController->latestBlog();
		$blogPosts = $blogController->latestBlog(10);
		$blogXML = CreateTag("BlogPosts",arrayToXML($blogPosts));
		return $blogXML;
	}
}