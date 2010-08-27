<?php 
//plugin injection script. This gets run just after all the turbo componants are loaded.
//we need to change the current working directory, then put it back afterwards...

$oldcwd = getcwd();	//Where is cwd now...
$myLocation = dirname(__FILE__);	//Move to where we are right now...
chdir($myLocation);

require_once("includes/statistics.inc");
require_once("includes/statistics_actions.inc");

require_once("objects/loggedPath.inc");

//Bind plugin routes...
PluginController::bind('statistics',				array('statisticsModule','default'));

//Add plugin events...
EVENTS::addEvent_EveryTime_Start(					array('statisticsModule','logThisRequest'));
EVENTS::addEvent('cron_day',array(
	'module'=>'statisticsModule',
	'function'=>'action_clear_logs')
);
/*
EVENTS::addEvent('cron_minute',array(
	'module'=>'statisticsModule',
	'function'=>'action_be_pissing_annoying')
);
*/



/*
PluginController::bind('blog/rss',					array('statisticsModule','rss'));
PluginController::bind('blog/rss.xml',				array('statisticsModule','rss'));
PluginController::bind('blog/post/([0-9]+)_(.*)',	array('statisticsModule','read_one'));
PluginController::bind('blog/author/(.*)', 			array("statisticsModule",'search_by_author'));
*/

$nav = new NaviPage("Statistics",			"plugin_statistics_list");

$nav->addChild(new NaviPage("PageViews",	"plugin_statistics_pageviews_list"));

PluginController::addAdminNavigation($nav);

chdir($oldcwd);	//Move back to the old cwd.