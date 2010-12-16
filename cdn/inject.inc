<?php 
//plugin injection script. This gets run just after all the turbo componants are loaded.
//we need to change the current working directory, then put it back afterwards...

$oldcwd = getcwd();	//Where is cwd now...
$myLocation = dirname(__FILE__);	//Move to where we are right now...
chdir($myLocation);
require_once("objects/cdn_hosted_file.inc");
require_once("objects/cdn_hosted_image.inc");
require_once("cdn.inc");
chdir($oldcwd);	//Move back to the old cwd.

if(turbo_get_setting("CDN_ENABLE") == "ON"){
	EVENTS		::addEvent	('cron_day',		array('cdn','action_mirror'));
	HOOKS		::bind		("CMS_IMAGE_SAVE",	array('cdn','action_mirror'));
	HOOKS		::bind		("HOOK_START",		array('cdn','action_prime'));
	HOOKS		::bind		("HOOK_START",		array('cdn','action_load_cdn_cache'));
	PluginController::bind		('force_cdn_pulldown',	array('cdn','pulldown'));
}
