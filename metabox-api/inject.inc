<?php 
//plugin injection script. This gets run just after all the turbo componants are loaded.
//we need to change the current working directory, then put it back afterwards...

$oldcwd = getcwd();	//Where is cwd now...
$myLocation = dirname(__FILE__);	//Move to where we are right now...
chdir($myLocation);

require_once("lib/metabox/metabox.curl.inc");
require_once("lib/metabox/metabox.inc");

fb::info("MetaboxAPI is present");

chdir($oldcwd);	//Move back to the old cwd.
