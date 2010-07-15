<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"    
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    exclude-result-prefixes="xsl">

<xsl:output method="xml" 
			omit-xml-declaration="yes"
			indent="yes"
			encoding="utf-8"/>

<xsl:include href="blog.xsl"/>

<xsl:include href="../../../../turbo/xsl/header.xsl"/>


<!-- start the stylesheet -->
	<xsl:template match="/">
		<xsl:call-template name="HeaderWrapper"/>
	</xsl:template>

	<!-- xml tempate -->
	<xsl:template match="XML">
		<div class="prettycontainer">
			<xsl:apply-templates select="Page/Blogpost"/>
		</div>
		
	</xsl:template>
	
	<xsl:template match="Blogpost">
		<div class="prettyforms wide">
			<h2 class="heading">Editing Blog Post # <xsl:value-of select="id"/> - <xsl:value-of select="title"/></h2>
			<form class="prettyform" action="{$RootPath}/plugin_blog_edit" method="post">
				<input type="hidden" name="id" value="{id}"/>
				<div class="formrow">
					<span class="label">Title</span>
					<input class="text" name="title" value="{title}"/>
				</div>
				<div class="formrow">
					<span class="label">Author</span>
					<select class="select" name="author">
						<option value="">Select an Author</option>
						<xsl:for-each select="/XML/Page/Authors/Author">
							<option value="{id}">
								<xsl:if test="id = /XML/Page/Blogpost/Author/id">
									<xsl:attribute name="selected">true</xsl:attribute>
								</xsl:if>
								
								<xsl:value-of select="firstname"/>
								<xsl:text> </xsl:text>
								<xsl:value-of select="surname"/>
							</option>
						</xsl:for-each>
					</select>
				</div>
				<div class="formrow">
					<span class="label">Published Date</span>
					<input class="text" name="published_date" value="{PublicationDate/Friendly_Short}"/>
				</div>
				<div class="formrow">
					<span class="label">Article</span>
					<textarea class="text" name="article">
						<xsl:value-of select="article"/>
						<xsl:text> </xsl:text>
					</textarea>
				</div>
				<div class="formrow">
					<span class="label">Publish blog</span>
					<xsl:choose>
						<xsl:when test="published_state = 1">
							<input type="checkbox" class="checkbox" name="published" checked="checked"/> This blog entry is published!
						</xsl:when>
						<xsl:otherwise>
							<input type="checkbox" class="checkbox" name="published"/> Check to publish blog entry.
						</xsl:otherwise>
					</xsl:choose>
					
				</div>
				
				<div class="formrow">
					<input class="submit" type="submit" value="Save!"/>
				</div>
				<div class="clear"><xsl:text> </xsl:text></div>
				
			</form>
		</div>
	</xsl:template>
	
</xsl:stylesheet>