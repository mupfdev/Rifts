<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
<!--
###################################################################################
#
# XSL file to convert CSPTML documents to HTML
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved
#
# Date 01-07-99
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

<!-- ptml node match -->
<xsl:template match = "csptml">
<HTML>
<HEAD>
<TITLE>Csptml source file</TITLE>
</HEAD>
<BODY>
<xsl:apply-templates/>
</BODY>
</HTML>
</xsl:template>

'handle the section'
<xsl:template match="section">
<xsl:apply-templates/>
</xsl:template>

'handle headings'
<xsl:template match='heading'>
<xsl:choose>
<xsl:when test='ancestor(section)[@level="0"]'>
	  <h1><xsl:apply-templates/></h1>
</xsl:when>
<xsl:when test='ancestor(section)[@level="1"]'>
	  <h1><xsl:apply-templates/></h1>
</xsl:when>
<xsl:when test='ancestor(section)[@level="2"]'>
	  <h2><xsl:apply-templates/></h2>
</xsl:when>
<xsl:when test='ancestor(section)[@level="3"]'>
	  <h3><xsl:apply-templates/></h3>
</xsl:when>
<xsl:when test='ancestor(section)[@level="4"]'>
	  <h4><xsl:apply-templates/></h4>
</xsl:when>
<xsl:when test='ancestor(section)[@level="5"]'>
	  <h5><xsl:apply-templates/></h5>
</xsl:when>
<xsl:when test='ancestor(section)[@level="6"]'>
	  <h6><xsl:apply-templates/></h6>
</xsl:when>
<xsl:otherwise>
    <p><xsl:apply-templates/></p>
</xsl:otherwise>
</xsl:choose>
</xsl:template>

'lists'
<xsl:template match='list'>
<xsl:choose>
<xsl:when test='.[@style="bullet"]'>
	  <ul><xsl:apply-templates/></ul>
</xsl:when>
<xsl:when test='.[@style="number"]'>
	  <ol><xsl:apply-templates/></ol>
</xsl:when>
<xsl:when test='.[@style="manual"]'>
	  <ol><xsl:apply-templates/></ol>
</xsl:when>
</xsl:choose>
</xsl:template>

'list items'
<xsl:template match='listitem'>
<li>
<xsl:if test='.[@value!=""]'><xsl:value-of select="@value"/>. </xsl:if>
<xsl:apply-templates/></li>
</xsl:template>

'handle deflist'
<xsl:template match='deflist'>
<dl><xsl:apply-templates/></dl>
</xsl:template>

'handle term'
<xsl:template match='term'>
<dt><xsl:apply-templates/></dt>
</xsl:template>

'handle definition'
<xsl:template match='definition'>
<dd><xsl:apply-templates/></dd>
</xsl:template>

'tables'
<xsl:template match='table'>
<table border="1"><xsl:apply-templates/></table>
</xsl:template>

'rows'
<xsl:template match='row'>
<tr><xsl:apply-templates/></tr>
</xsl:template>

'cells'
<xsl:template match='cell'>
<td><xsl:apply-templates/></td>
</xsl:template>

'plain text'
<xsl:template match="p">
<p><xsl:if test='.[@style!=""]'><b>style:<xsl:value-of
select="@style"/></b> </xsl:if>
<xsl:apply-templates/></p>
</xsl:template>

'comments'
<xsl:template match="p[@style='comment']">
<font color="green"><p><xsl:apply-templates/></p></font>
</xsl:template>

'symbols'
<xsl:template match="symbol">
<font color="red" face="symbol"><xsl:value-of select="@codepoint"/></font>
</xsl:template>

'allowed manual formating'
<xsl:template match="b">
<b><xsl:apply-templates/></b>
</xsl:template>

<xsl:template match="i">
<i><xsl:apply-templates/></i>
</xsl:template>

<xsl:template match="sup">
<sup><xsl:apply-templates/></sup>
</xsl:template>

<xsl:template match="sub">
<sub><xsl:apply-templates/></sub>
</xsl:template>

'character style formating'
<xsl:template match='cs'>
<b>&lt;style:<xsl:value-of select="@style"/></b>
<xsl:apply-templates/><b>&gt;</b>
</xsl:template>

'raw text'
<xsl:template match="text()">
<xsl:value-of select="."/>
</xsl:template>

</xsl:stylesheet>


























