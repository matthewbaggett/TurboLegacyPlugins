<?php 
//plugin injection script. This gets run just after all the turbo componants are loaded.
//we need to change the current working directory, then put it back afterwards...

$oldcwd = getcwd();	//Where is cwd now...
$myLocation = dirname(__FILE__);	//Move to where we are right now...
chdir($myLocation);

//Load objects
require_once("objects/apikey.inc");

//Load libraries
require_once("lib/metabox.inc");
require_once("lib/metabox.actions.inc");

//Bind plugin routes...
PluginController::bind('push',								array('metaboxModule','push'));
PluginController::bind('get/(.*)/(.*)/(.*)',		 		array("metaboxModule",'get'));
PluginController::bind('batch/get', 						array("metaboxModule",'get_batch'));
/*
PluginController::bind('blog/rss',					array('blogModule','rss'));
PluginController::bind('blog/rss.xml',				array('blogModule','rss'));
PluginController::bind('blog/post/([0-9]+)_(.*)',	array('blogModule','read_one'));
PluginController::bind('blog/author/(.*)', 			array("blogModule",'search_by_author'));
*/


chdir($oldcwd);	//Move back to the old cwd.