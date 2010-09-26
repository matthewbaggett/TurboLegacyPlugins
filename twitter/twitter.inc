<?php 


class Tweet{
	public $message;
	
	public function tweet(){
		
	}
	public function action_test(){
		$this->message = 'This a simple test from twitter-async at ' . date('m-d-Y h:i:s');
		print_r_html($this->tweet());
	}
	
}