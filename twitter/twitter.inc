<?php 


class Tweet{
	public $message;
	
	public function tweet(){
		$twitter = new TwitterApi('metaboxupdates','omegaomega');
		
		// Update your status
		return json_decode($twitter->updateStatus($this->message,null,'json'));
	}
	public function action_test(){
		$this->message = "Test! abcdefghijklmnopqrstuvwxyz";
		print_r_html($this->tweet());
	}
	
}