<?php 
//plugin injection script. This gets run just after all the turbo componants are loaded.
//we need to change the current working directory, then put it back afterwards...

$oldcwd = getcwd();	//Where is cwd now...
$myLocation = dirname(__FILE__);	//Move to where we are right now...
chdir($myLocation);

require_once("includes/blog.inc");
require_once("includes/blog.controller.inc");
require_once("includes/blog_actions.inc");

PluginController::bind("blog",array('blogModule','default'));
PluginController::bind("blog/view/(.*)",array('blogModule','getBlogPost'));

chdir($oldcwd);	//Move back to the old cwd.