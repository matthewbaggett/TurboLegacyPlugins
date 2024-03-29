<?php 
//plugin injection script. This gets run just after all the turbo componants are loaded.
//we need to change the current working directory, then put it back afterwards...

$oldcwd = getcwd();	//Where is cwd now...
$myLocation = dirname(__FILE__);	//Move to where we are right now...
chdir($myLocation);

require_once("includes/timemachine.inc");
require_once("includes/timemachine_actions.inc");

chdir($oldcwd);	//Move back to the old cwd.

//Bind plugin routes...
PluginController::bind('timemachine',				array('timemachineModule','default'));
PluginController::bind('timemachine/list/(.*)',		 	array("timemachineModule",'version_list'));
PluginController::bind('timemachine/version/(.*)/(.*)', 	array("timemachineModule",'version_get'));
