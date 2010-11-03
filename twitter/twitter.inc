<?php 
define("TWITTER_CONSUMER_KEY","j9YDC0nKfvQ73Ns9kMUiw");
define("TWITTER_CONSUMER_SECRET","JFbcdj5HZJ5FpKAqg0yj8bJoKcti7sjqQcOq9iTb4E");

define("TWITTER_OAUTH_TOKEN","193661288-gh4vhn71U585gcqoLVfQKNTVhetZKcxUCLRFzwS4");
define("TWITTER_OAUTH_TOKEN_SECRET","0hVveJU8KF5tBlzohZ2wYWNT40YnqyhgfdX8XtjLI");

class Tweet{
	public $message;
	
	public function tweet(){
		$connection = $this->getConnectionWithAccessToken(TWITTER_OAUTH_TOKEN, TWITTER_OAUTH_TOKEN_SECRET);
		return $connection->post(
				'statuses/update', 
				array('status' => $this->message)
			);
	}
	
	private function getConnectionWithAccessToken($oauth_token, $oauth_token_secret) {
  		$connection = new TwitterOAuth(TWITTER_CONSUMER_KEY, TWITTER_CONSUMER_SECRET, $oauth_token, $oauth_token_secret);
  		return $connection;
	}
	
	public function action_test(){
		$this->message = 'This a simple test from twitter-async at ' . date('m-d-Y h:i:s');
		print_r_html($this->tweet());
		die("tweeted");
	}
	
}
