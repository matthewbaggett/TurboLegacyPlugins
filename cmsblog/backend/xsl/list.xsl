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
				<h2 class="heading">List of blog posts</h2>
				<form class="prettyform" >
					
					<div class="formrow">
						<ul>
							<xsl:for-each select="Page/Blogs/Blog">
								<li>
									<a href="./plugin_blog_edit?id={id}">
										<xsl:value-of select="title"/>
									</a>
								</li>
							</xsl:for-each>
						</ul>
					</div>
					<div class="formrow">
						<a href="./plugin_blog_new">New blog post</a>
					</div>
					<div class="clear"><xsl:text> </xsl:text></div>
					
				</form>
			</div>
		</div>
		
	</xsl:template>
	
</xsl:stylesheet>