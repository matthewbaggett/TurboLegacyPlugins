<?php 
//plugin injection script. This gets run just after all the turbo componants are loaded.
//we need to change the current working directory, then put it back afterwards...

$oldcwd = getcwd();	//Where is cwd now...
$myLocation = dirname(__FILE__);	//Move to where we are right now...
chdir($myLocation);

//Load objects
require_once("objects/apikey.inc");
require_once("objects/dataset.inc");
require_once("objects/failure.inc");
require_once("objects/image.inc");
require_once("objects/relation.inc");
require_once("objects/tag.inc");

//Load libraries
require_once("lib/metabox.inc");
require_once("lib/metabox.actions.inc");
require_once("lib/metabox.responce.inc");
require_once("lib/metabox.statistics.actions.inc");

//Bind plugin routes...
PluginController::bind("status",						array("metaboxModule","status"));
PluginController::bind('push',								array('metaboxModule','push'));
PluginController::bind('search',							array('metaboxModule','seek'));
PluginController::bind('get/(.*)/(.*)/(.*)',		 		array("metaboxModule",'get'));
PluginController::bind('get_uuid/(.*)',		 				array("metaboxModule",'get_uuid'));
PluginController::bind('batch/get', 						array("metaboxModule",'get_batch'));
PluginController::bind('twitter/hourly', 					array("metaboxStatisticsModule",'upload_statistics'));
PluginController::bind('twitter/daily',						array("metaboxStatisticsModule","daily_statistics"));

//Add events
EVENTS::addEvent('cron_hourly', array(
		'module'=>'metaboxStatisticsModule',
		'function'=>'upload_statistics'
	)
);
EVENTS::addEvent('cron_hour_14', array(
		'module'=>'metaboxStatisticsModule',
		'function'=>'daily_statistics'
	)
);
EVENTS::addEvent('cron_hour_2', array(
		'module'=>'metaboxStatisticsModule',
		'function'=>'daily_statistics'
	)
);

chdir($oldcwd);	//Move back to the old cwd.
