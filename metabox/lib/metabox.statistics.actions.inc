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
	function action_daily_statistics(){
		$sql_count['searches_today'] 	= "SELECT count(id) as count FROM `log_access` WHERE path LIKE 'search%' AND constructedat > ".strtotime("1 day ago");
		$sql_count['searches_thisweek'] = "SELECT count(id) as count FROM `log_access` WHERE path LIKE 'search%' AND constructedat > ".strtotime("7 days ago");
		$sql_count['searches_alltime']	= "SELECT count(id) as count FROM `log_access` WHERE path LIKE 'search%'";
		
		$sql_count['pushes_today'] 	= "SELECT count(id) as count FROM `log_access` WHERE path LIKE 'push%' AND constructedat > ".strtotime("1 day ago");
		$sql_count['pushes_thisweek'] 	= "SELECT count(id) as count FROM `log_access` WHERE path LIKE 'push%' AND constructedat > ".strtotime("7 days ago");
		$sql_count['pushes_alltime']	= "SELECT count(id) as count FROM `log_access` WHERE path LIKE 'push%'";
		
		$sql_count['gets_today']	= "SELECT count(id) as count FROM `log_access` WHERE path LIKE 'get%' AND constructedat > ".strtotime("1 day ago");
		$sql_count['gets_thisweek'] 	= "SELECT count(id) as count FROM `log_access` WHERE path LIKE 'get%' AND constructedat > ".strtotime("7 days ago");
		$sql_count['gets_alltime']	= "SELECT count(id) as count FROM `log_access` WHERE path LIKE 'get%'";
		
		foreach($sql_count as $name => &$sql){
			$result = DB::Query($sql);
			$row = DB::result_object($result);
			$sql = $row->count;
		}
		//print_r_html($sql_count);
		$oTweet = new Tweet();
		$oTweet->message = "Access information: GETS: (%d/%d/%d) SEEKS: (%d/%d/%d) PUSHES: (%d/%d/%d) ... (Today/Week/All time)";
		$oTweet->message = sprintf(
			$oTweet->message,
			$sql_count['gets_today'],
			$sql_count['gets_thisweek'],
			$sql_count['gets_alltime'],
			
			$sql_count['searches_today'],
			$sql_count['searches_thisweek'],
			$sql_count['searches_alltime'],
			
			$sql_count['pushes_today'],
			$sql_count['pushes_thisweek'],
			$sql_count['pushes_alltime']
		);
		$oTweet->tweet();
	}	
}
