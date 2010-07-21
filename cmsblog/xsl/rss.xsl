<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"    
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    exclude-result-prefixes="xsl">

<xsl:output 
		omit-xml-declaration="yes"
		indent="yes" />
		
	<xsl:template match="/">
		
		<rss version="2.0" xmlns:media="http://search.yahoo.com/mrss/" xmlns:atom="http://www.w3.org/2005/Atom">
			<channel>
				<title><xsl:value-of select="/XML/Settings/Setting[name='siteTitle']/value"/> RSS feed</title>
				<link><xsl:value-of select="/XML/Turbo/Rootpath"/><xsl:text> </xsl:text></link>
				<copyright><xsl:value-of select="/XML/Settings/Setting[name='copyright']/value"/><xsl:text> </xsl:text></copyright>
				<ttl>15</ttl>
				<atom:link href="{/XML/ThisPath}" rel="self" type="application/rss+xml" />
				<xsl:apply-templates select="/XML/Page/Blogs/Blog"/>
					
			</channel>
		</rss>
		
	</xsl:template>
	<xsl:template match="Blog">
		<xsl:variable name="url"><xsl:value-of select="/XML/Turbo/Rootpath"/>plugin/blog/post/<xsl:value-of select="URL"/></xsl:variable>
		<item>
			<title><xsl:value-of select="title"/><xsl:text> </xsl:text></title>
			<description><xsl:value-of select="substring(article,0,300)"/><xsl:text> </xsl:text></description>
			<link><xsl:value-of select="$url"/></link>
			<guid isPermaLink="true"><xsl:value-of select="$url"/></guid>
			<pubDate><xsl:value-of select="PublicationDate/RFC_2822"/></pubDate>
		</item>
	</xsl:template>
	
</xsl:stylesheet>