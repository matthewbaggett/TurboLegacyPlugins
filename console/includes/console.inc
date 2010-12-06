<?php

class turboConsole{
	private $fields;

	public function __construct(){
		$fields[] = 
			'<div>'.
			'<h3>SQL</h3>'.
			'<h4>Queries: n</h4>'.
			'<h5>Read</h5>'.
			'<h5>Write</h5>'.
			'</div>';
	}
	public function crunch(){
		return $fields;
	}
	public function inject(){
		$turboConsole = new turboConsole();
		$content = $turboConsole->crunch();
		
		TURBO::add_js_var("console_values",json_encode($content));
		TURBO::add_js_file("/plugins/turboconsole/js/console.js");
		TURBO::add_css("/plugins/turboconsole/css/console.css");
	}
}
