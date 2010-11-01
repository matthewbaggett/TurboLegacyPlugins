<?php 
define("CONSUMER_KEY","FgEL4jVeBNDvXYSE6sqQg");
define("CONSUMER_SECRET","4z1W8tr6ESPZVstub5uzskysa0iAOgq2t4a4rFqBuY");

class Tweet{
	public $message;
	
	public function tweet(){
		return;
		$connection = $this->getConnectionWithAccessToken("94059844-xaVWoCzOk5BlUIEXHb4O0eIY4uAsY2RubNzefvF9G", "FGi8p6EXA8u0gZiWFOCvIaAcnMlQvOYFImrhRkemg");
		$connection->post(
				'statuses/update', 
				array('status' => $this->message)
			);
	}
	
	private function getConnectionWithAccessToken($oauth_token, $oauth_token_secret) {
  		$connection = new TwitterOAuth(CONSUMER_KEY, CONSUMER_SECRET, $oauth_token, $oauth_token_secret);
  		return $connection;
	}
	
	public function action_test(){
		$this->message = 'This a simple test from twitter-async at ' . date('m-d-Y h:i:s');
		print_r_html($this->tweet());
		die("tweeted");
	}
	
}
