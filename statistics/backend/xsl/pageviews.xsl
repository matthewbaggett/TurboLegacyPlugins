<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"    
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    exclude-result-prefixes="xsl">

<xsl:output method="xml" 
			omit-xml-declaration="yes"
			indent="yes"
			encoding="utf-8"/>

<xsl:include href="../../../../turbo/xsl/header.xsl"/>


<!-- start the stylesheet -->
	<xsl:template match="/">
		<xsl:call-template name="HeaderWrapper"/>
	</xsl:template>

	<!-- xml tempate -->
	<xsl:template match="XML">
		<div class="prettycontainer">
			<div class="prettyforms super-wide">
				<h2 class="heading">Page view statistics</h2>
				<div id="pageviews_chart"><span id="chart-replace">Chart would go here if you had flash!</span></div>
			</div>
		</div>
		
	</xsl:template>
</xsl:stylesheet>