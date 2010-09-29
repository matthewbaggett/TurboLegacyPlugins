<?php 
//plugin injection script. This gets run just after all the turbo componants are loaded.
//we need to change the current working directory, then put it back afterwards...

$oldcwd = getcwd();	//Where is cwd now...
$myLocation = dirname(__FILE__);	//Move to where we are right now...
chdir($myLocation);

require_once("geoip.inc");
require_once("geoip.actions.inc");


chdir($oldcwd);	//Move back to the old cwd.

EVENTS::addEvent('cron_quarter',array(
	'module'=>'geoipModule',
	'function'=>'action_locate_ips')
);


PluginController::bind('geoip_locate_html5', 	array('geoipModule','locate_html5'));
PluginController::bind('geoip_locate_ips',		array('geoipModule','locate_ips'));