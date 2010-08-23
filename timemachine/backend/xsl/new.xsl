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
			<div class="prettyforms">
				<h2 class="heading">Create a new Blog Post</h2>
				<form class="prettyform" action="{$RootPath}plugin_blog_edit" method="post">
					<input type="hidden" name="nextaction" value="new_blog_entry"/>
					<div class="formrow">
						<span class="label">Title</span>
						<input class="text" name="title"/>
					</div>
					<div class="formrow">
						<span class="label">Author</span>
						<select class="select" name="author">
							<option value="">Select an Author</option>
							<xsl:for-each select="/XML/Page/Authors/Author">
								<option value="{id}">
									<xsl:value-of select="firstname"/>
									<xsl:text> </xsl:text>
									<xsl:value-of select="surname"/>
								</option>
							</xsl:for-each>
						</select>
		
					</div>
					<div class="formrow">
						<input class="submit" type="submit" value="Add!"/>
					</div>
					<div class="clear"><xsl:text> </xsl:text></div>
					
				</form>
			</div>
		</div>
		
	</xsl:template>
	
</xsl:stylesheet>