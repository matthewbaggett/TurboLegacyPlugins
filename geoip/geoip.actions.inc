<?php
class geoipModule{	
	function action_default(){
		
	}

	function action_locate_ips(){
		$sql = "SELECT id,ip FROM loggedpaths WHERE geoipProcessed != 1 AND ip != '127.0.0.1'";
		$result = DB::Query($sql);
		while($row = DB::result_object($result)){
			$location = GEOIP::seek($row->ip);
			
			$oLoggedPath = new LoggedPath();
			$oLoggedPath->loadByID($row->id);
			$oLoggedPath->setCountryCode($location->country_code3);
			$oLoggedPath->setCountryName($location->country_name);
			$oLoggedPath->setRegion($location->region);
			$oLoggedPath->setCity($location->city);
			$oLoggedPath->setPostalCode($location->postal_code);
			$oLoggedPath->setLatitude($location->latitude);
			$oLoggedPath->setLongitude($location->longitude);
			$oLoggedPath->setGeoIPProcessed(1);
			$oLoggedPath->save();
			
		}
	}
}
