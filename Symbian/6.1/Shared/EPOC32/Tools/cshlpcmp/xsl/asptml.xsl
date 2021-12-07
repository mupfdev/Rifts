<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
<!--
###################################################################################
#
# XSL file to convert ASPTML documents to HTML
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved
#
# Date 18-08-99
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

<!-- asptml node match -->
<xsl:template match = "asptml">
<HTML>
<HEAD>
<TITLE>Asptml source file</TITLE>
</HEAD>
<BODY>
<xsl:apply-templates/>
</BODY>
</HTML>
</xsl:template>

'handle topics'
<xsl:template match='topic'>
<hr/>
<h3>Category: <xsl:value-of select="category[text()]"/></h3>
<h3>Category UID (decimal):<xsl:value-of select="@categoryUID"/></h3>
<xsl:apply-templates/>
</xsl:template>

'handle topic title'
<xsl:template match='topictitle'>
<h3>Title: <xsl:apply-templates/></h3>
</xsl:template>

'handle the contexts'
<xsl:template match='context'>
<p><b>Context:</b> <xsl:value-of select="@contextUID"/>
 <font color="green"><xsl:value-of select="@comment"/></font></p>
</xsl:template>

'handle the indexes'
<xsl:template match='index'>
<p><b>Index:</b> <xsl:apply-templates/></p>
</xsl:template>

'handle the synonyms'
<xsl:template match='synonyms'>
<p><b>Synonyms:</b> <font color="darkred"><xsl:value-of select="text()"/></font></p>
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

'plain text'
<xsl:template match="p">
<p><xsl:if test='.[@style!=""]'><b>style:<xsl:value-of
select="@style"/></b> </xsl:if>
<xsl:apply-templates/></p>
</xsl:template>

'graphics'
<xsl:template match="graphic">
<xsl:element name="img">
<xsl:attribute name="src"><xsl:value-of
select="@htmlfilename"/></xsl:attribute>
</xsl:element>
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


























