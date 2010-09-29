<?php 
//plugin injection script. This gets run just after all the turbo componants are loaded.
//we need to change the current working directory, then put it back afterwards...

$oldcwd = getcwd();	//Where is cwd now...
$myLocation = dirname(__FILE__);	//Move to where we are right now...
chdir($myLocation);

require_once("lib/twitter-api.inc");
require_once("twitter.inc");

chdir($oldcwd);	//Move back to the old cwd.

//Bind plugin routes...
PluginController::bind('test-twitter',								array('Tweet','test'));

//Assemble Admin navigation elements
$nav = new NaviPage("Twitter",false);
$nav->addChild(new NaviPage("Feeds","plugin_twitter_feeds"));
$nav->addChild(new NaviPage("Followers","plugin_twitter_list_followers"));
$nav->addChild(new NaviPage("Configuration","plugin_twitter_config"));

PluginController::addAdminNavigation($nav);