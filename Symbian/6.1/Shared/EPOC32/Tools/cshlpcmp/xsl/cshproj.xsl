<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
<!--
###################################################################################
#
# XSL file to convert CS-Help project files to HTML
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved
#
# Date 22-06-99
#
####################################################################################
#
# Modification history
#
####################################################################################
-->

<!-- root node match -->
<xsl:template match = "/">
<xsl:apply-templates/>
</xsl:template>

<!-- cshproj node match -->
<xsl:template match = "cshproj">
<HTML>
<HEAD>
<TITLE>CS-Help project file</TITLE>
</HEAD>
<BODY>
<H1>CS-Help project file</H1>
<H2>Help file UID</H2>
<xsl:apply-templates select="helpfileUID"/>
<H2>Directories</H2>
<xsl:apply-templates select="directories"/>
<H2>Files</H2>
<xsl:apply-templates select="files"/>
</BODY>
</HTML>
</xsl:template>

'handle the helpfileUID'
<xsl:template match="helpfileUID">
<p><xsl:value-of select="text()"/></p>
</xsl:template>


'handle the directories'
<xsl:template match="directories">
<p><b>Input:</b><xsl:value-of select="input"/></p>
<p><b>Ouput:</b><xsl:value-of select="output"/></p>
<p><b>Graphics:</b><xsl:value-of select="graphics"/></p>
<p><b>Working:</b><xsl:value-of select="working"/></p>
</xsl:template>

'handle the directories'
<xsl:template match="files">
<xsl:apply-templates select="source"/>

<p><b>Ouput help file:</b><xsl:value-of select="destination"/></p>
<p><b>Customization:</b><xsl:value-of select="customization"/></p>
</xsl:template>

'handle the source files'
<xsl:template match="source">
<h3>Source files are</h3>
<xsl:apply-templates select="file"/>
</xsl:template>

'handle the source file'
<xsl:template match="file">
<p><xsl:value-of select="text()"/></p>
</xsl:template>


</xsl:stylesheet>














