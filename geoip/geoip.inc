<?php 
//YQL: select * from pidgets.geoip where ip='128.100.100.128'

class GEOIP{
	static function seek($ip){
		$result = YQL::query("select * from pidgets.geoip where ip='{$ip}'");
		return YQL::fetch_object($result);
	}
}

