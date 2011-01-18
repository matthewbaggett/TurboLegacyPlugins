<?php
define("SERVER_OVERRIDE","live");
require_once("../../turbo/turbo.inc");
$cdn = new cdn();
$cdn->action_pushup();
