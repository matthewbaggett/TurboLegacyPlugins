<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"    
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    exclude-result-prefixes="xsl">

<xsl:output method="xml" 
			omit-xml-declaration="yes"
			indent="yes"
			encoding="utf-8"/>

	<xsl:template match="/XML" mode="extrahead">
		<link rel="stylesheet" href="{$RootPath}/../plugins/blog/backend/css/blog.backend.css" type="text/css" media="all"/>
	</xsl:template>
</xsl:stylesheet>