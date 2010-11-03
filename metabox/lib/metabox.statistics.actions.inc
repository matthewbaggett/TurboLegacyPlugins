<?php 
class metaboxStatisticsModule{
	function action_upload_statistics(){
		//Try to tweet!
		$sql_count_images 	= "SELECT count(id) as count FROM `mimages`";
		$sql_count_tags 	= "SELECT count(id) as count FROM `mtags`";
		$sql_count_users	= "SELECT count(id) as count FROM `users`";
		
		$result_count_images 	= DB::query($sql_count_images);
		$result_count_tags 		= DB::query($sql_count_tags);
		$result_count_users 	= DB::query($sql_count_users);
		
		$row_count_images		= DB::result_array($result_count_images);
		$row_count_tags			= DB::result_array($result_count_tags);
		$row_count_users		= DB::result_array($result_count_users);
		
		$images 	= $row_count_images['count'];
		$tags 		= $row_count_tags['count'];
		$users 		= $row_count_users['count'];
		
		if(TURBO::PluginAvailable("Twitter")){
			$connection = new TwitterOAuth(TWITTER_CONSUMER_KEY, TWITTER_CONSUMER_SECRET, TWITTER_OAUTH_TOKEN, TWITTER_OAUTH_TOKEN_SECRET);
			$myTimeline = $connection->get('statuses/user_timeline');

			$oTweet = new Tweet();
			$oTweet->message = "There are {$images} items in the DB, with {$tags} pieces of metadata over {$users} users.";
			if($myTimeline[0]->text != $oTweet->message){
				$oTweet->tweet();
			}
		}
	}	
}
