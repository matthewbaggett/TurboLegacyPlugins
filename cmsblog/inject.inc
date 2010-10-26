<?php 
//plugin injection script. This gets run just after all the turbo componants are loaded.
//we need to change the current working directory, then put it back afterwards...

$oldcwd = getcwd();	//Where is cwd now...
$myLocation = dirname(__FILE__);	//Move to where we are right now...
chdir($myLocation);

require_once("includes/blog.inc");
require_once("includes/blog.controller.inc");
require_once("includes/blog_actions.inc");
require_once("includes/blog.backend.inc");

chdir($oldcwd);	//Move back to the old cwd.

//Bind plugin routes...
PluginController::bind('blog',						array('blogModule','default'));
PluginController::bind('blog/rss',					array('blogModule','rss'));
PluginController::bind('blog/rss.xml',				array('blogModule','rss'));
PluginController::bind('blog/post/([0-9]+)_(.*)',	array('blogModule','read_one'));
PluginController::bind('blog/author/(.*)', 			array("blogModule",'search_by_author'));

//Assemble Admin navigation elements
$nav = new NaviPage("Blog",false, 'pages');
$nav->addChild(new NaviPage("New Post","plugin_blog_new"));
$nav->addChild(new NaviPage("List Posts","plugin_blog_list"));

PluginController::addAdminNavigation($nav);

