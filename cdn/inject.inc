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

EVENTS::addEvent('cron_day',array(
		'module'=>'cdn',
		'function'=>'action_mirror'
	)
);
