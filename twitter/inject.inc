<?php 
//plugin injection script. This gets run just after all the turbo componants are loaded.
//we need to change the current working directory, then put it back afterwards...

$oldcwd = getcwd();	//Where is cwd now...
$myLocation = dirname(__FILE__);	//Move to where we are right now...
chdir($myLocation);

require_once("lib/twitter-api.inc");
require_once("twitter.inc");

chdir($oldcwd);	//Move back to the old cwd.

PluginController::bind('test-twitter',								array('Tweet','test'));
