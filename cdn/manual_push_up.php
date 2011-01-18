<?php
define("SERVER_OVERRIDE",true);
define("SERVER","live");
require_once("../../turbo/turbo.inc");
$cdn = new cdn();
$cdn->action_pushup();
