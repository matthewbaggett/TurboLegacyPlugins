<?php 

class TWITTER extends TwitterApi{
	
}
class Tweet{
	public $message;
	
	public function tweet(){
		$twitter = new TWITTER();
		$twitter->username = "metaboxupdates";
		$twitter->password = "omegaomega";
		// Update your status
		$twitter->update('xml',$this->message);
	}
}