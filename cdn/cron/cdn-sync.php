<?php
require_once("../../../turbo/turbo.inc");
//Prevent PHP timing out.
set_time_limit(0);

$cdn = new cdn();
$responce = $cdn->action_pulldown();

print_r_html($responce);