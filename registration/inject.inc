<?php 
//plugin injection script. This gets run just after all the turbo componants are loaded.
//we need to change the current working directory, then put it back afterwards...

$oldcwd = getcwd();	//Where is cwd now...
$myLocation = dirname(__FILE__);	//Move to where we are right now...
chdir($myLocation);

require_once("includes/login.actions.inc");
require_once("includes/registration.actions.inc");

//Bind plugin routes...
PluginController::bind('register',					array('registrationModule','default'));
PluginController::bind('register/submit',				array('registrationModule','submit'));
PluginController::bind('register/thankyou',				array('registrationModule','thankyou'));

PluginController::bind("login",						array('loginModule','login'));
PluginController::bind('login/submit',					array('loginModule','login_do'));
PluginController::bind('logout',					array('loginModule','logout_do'));

EVENTS::addEvent_EveryTime_Start(					array('loginModule','login_check'));

chdir($oldcwd);	//Move back to the old cwd.
