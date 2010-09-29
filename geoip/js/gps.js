function success(position){
	alert("Position found: " + position.coords.latitude + " by " + position.coords.longitude);
}
function error(error){
	if(typeof msg == 'string'){
		alert("err: " + error);
	}else{
		alert("Error happened, non-string");
	}
}
$(document).ready(function(){
	alert("dookie");
	if (navigator.geolocation) {
		navigator.geolocation.getCurrentPosition(success, error);
		alert("supported");
	} else {
		alert('not supported');
	}

});
