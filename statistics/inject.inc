<?php 
//plugin injection script. This gets run just after all the turbo componants are loaded.
//we need to change the current working directory, then put it back afterwards...

$oldcwd = getcwd();	//Where is cwd now...
$myLocation = dirname(__FILE__);	//Move to where we are right now...
chdir($myLocation);

require_once("includes/statistics.inc");
require_once("includes/statistics.actions.inc");
require_once("includes/statistics.backend.inc");

require_once("objects/loggedPath.inc");

//Bind plugin routes...
PluginController::bind('statistics',				array('statisticsModule','default'));

//Add plugin events...
EVENTS::addEvent_EveryTime_Start(					array('statisticsModule','logThisRequest'));
EVENTS::addEvent('cron_day',array(
		'module'=>'statisticsModule',
		'function'=>'action_clear_logs'
	)
);

$nav = new NaviPage("Statistics",			false,'plugins');
$nav->addChild(new NaviPage("Page Views",	"plugin_statistics_pageviews"));

PluginController::addAdminNavigation($nav);

chdir($oldcwd);	//Move back to the old cwd.