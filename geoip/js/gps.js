function turboGPSsuccess(position){
	//console.info("Position found: " + position.coords.latitude + " by " + position.coords.longitude);
	$('.location_cell')
		.empty()
		.append("Position found: " + position.coords.latitude + " by " + position.coords.longitude + ". ");
	$.post(
		gps_feed_location, 
		{
			lat: position.coords.latitude, 
			long: position.coords.longitude, 
			requestid: request_id
		},
		function(dataJSON){
			var data = jQuery.parseJSON(dataJSON);
			console.group("GPS Logged OK.");
			console.log(data);
			console.groupEnd();
			alert(data);
			$('.location_cell')
				.append("Access: #" + "");
		}
	);
	//alert("GPS success! At: " + position.coords.latitude + " by " + position.coords.longitude)
}
function turboGPSerror(error){
	if(typeof msg == 'string'){
		turboGPSfireerror("Error: \"" + error + "\"");
	}else{
		turboGPSfireerror("Error happened, non-string");
	}
	
}
function turboGPSfireerror(error){
	$.post(
			root_path + "/log-position", 
			{
				error: error,  
				requestid: request_id
			}
		);
	//console.warn(error);
}
$(document).ready(function(){
	
	if (navigator.geolocation) {
		navigator.geolocation.getCurrentPosition(turboGPSsuccess, turboGPSerror);
		//console.info("HTML5's geolocation supported");
	} else {
		turboGPSerror("HTML5 gelocation unsupported");
	}

});
