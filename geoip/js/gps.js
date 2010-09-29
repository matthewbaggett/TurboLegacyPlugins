function success(){
	alert("gps OK");
}
function error(){
	alert("error: not-supported");
}

if (navigator.geolocation) {
  navigator.geolocation.getCurrentPosition(success, error);
} else {
  error('not supported');
}