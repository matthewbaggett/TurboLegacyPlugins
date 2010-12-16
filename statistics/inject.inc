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
require_once("objects/movements.inc");

//Bind plugin routes...
PluginController::bind('statistics',				array('statisticsModule','default'));
PluginController::bind('destroy_session',			array('statisticsModule','destroy_session'));

//Add plugin events...
if(turbo_get_setting("GEOIP_HTML5") == "ENABLED"){
	EVENTS::addEvent_EveryTime_Start(					array('statisticsModule','log_this_request'));
}
EVENTS::addEvent_EveryTime_Start(					array('statisticsModule','track_movement'));

EVENTS::addEvent('cron_day',array(
		'module'=>'statisticsModule',
		'function'=>'action_clear_logs'
	)
);

$nav = new NaviPage("Statistics",			false,'plugins');
$nav->addChild(new NaviPage("Page Views",	"plugin_statistics_pageviews"));

PluginController::addAdminNavigation($nav);

chdir($oldcwd);	//Move back to the old cwd.
