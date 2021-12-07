<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
<!--
###################################################################################
#
# XSL file to convert CSHLP documents to HTML
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved
#
# Date 27-08-99
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

<!-- cshlp node match -->
<xsl:template match = "cshlp">
<HTML>
<HEAD>
<TITLE>cshlp source file</TITLE>
</HEAD>
<BODY>
<h1>Help File UID (decimal):<font color="blue"><xsl:value-of select="@helpfileUID"/></font></h1>
<xsl:apply-templates select="uid"/>
<xsl:apply-templates select="topic"/>
</BODY>
</HTML>
</xsl:template>

'handle the uid'
<xsl:template match="uid">
<h2>Category UID (decimal):<font color="blue"><xsl:value-of select="@value"/></font></h2>
</xsl:template>

'handle topics'
<xsl:template match='topic'>
<hr/>
<h3>Category UID (decimal):<xsl:value-of select="@categoryUID"/></h3>
<h3>Category: <xsl:value-of select="category[text()]"/></h3>
<xsl:apply-templates
select='/cshlp/context[@topicID=context()/@topicID]'/>

<xsl:apply-templates select='/cshlp/indexlink[@topicID=context()/@topicID]'/>

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

'handle the indexlink'
<xsl:template match='indexlink'>
<xsl:apply-templates
select='/cshlp/index[@indexID=context()/@indexID]'/>
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
<xsl:choose>
<xsl:when test='.[@value!=""]'>
  <xsl:element name="li">
    <xsl:attribute name="value"><xsl:value-of select="@value"/></xsl:attribute>
    <xsl:apply-templates/>
  </xsl:element></xsl:when>
<xsl:otherwise><li><xsl:apply-templates/></li></xsl:otherwise>
</xsl:choose>
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

<xsl:template match="leading">
<xsl:apply-templates/>
</xsl:template>

'text'
<xsl:template match="p">
<p>
<!-- process any graphic -->
<xsl:apply-templates
  select='/cshlp/mbmlist/graphic[@mbmID=context()/@mbmID]'/>
<!-- process any style -->
<xsl:choose>
<xsl:when test='.[@style="bold"]'>
	<b><xsl:apply-templates/></b>
</xsl:when>
<xsl:when test='.[@style="bolditalic"]'>
	<b><i><xsl:apply-templates/></i></b>
</xsl:when>
<xsl:when test='.[@style="italic"]'>
	<i><xsl:apply-templates/></i>
</xsl:when>
<xsl:when test='.[@style="normal"]'>
	<xsl:apply-templates/>
</xsl:when>
</xsl:choose>
</p>
</xsl:template>

'handle the graphiclink'
<xsl:template match='graphiclink'>
<xsl:apply-templates
select='/cshlp/mbmlist/graphic[@mbmID=context()/@mbmID]'/>
</xsl:template>

'graphics'
<xsl:template match="graphic">
<xsl:element name="img">
<xsl:attribute name="src"><xsl:value-of
select="@htmlfilename"/></xsl:attribute>
</xsl:element>
</xsl:template>

' handle the effect texts
<xsl:template match="noteeffects">
<xsl:apply-templates/>
</xsl:template>

<xsl:template match="tipeffects">
<xsl:apply-templates/>
</xsl:template>

<xsl:template match="importanteffects">
<xsl:apply-templates/>
</xsl:template>

'allowed manual formatting'
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
<xsl:choose>
<xsl:when test='.[@style="bold"]'>
	<b><xsl:apply-templates/></b>
</xsl:when>
<xsl:when test='.[@style="bolditalic"]'>
	<b><i><xsl:apply-templates/></i></b>
</xsl:when>
<xsl:when test='.[@style="italic"]'>
	<i><xsl:apply-templates/></i>
</xsl:when>
<xsl:when test='.[@style="normal"]'>
	<xsl:apply-templates/>
</xsl:when>
<xsl:otherwise>
    <b>style:<xsl:value-of select="@style"/></b>
    (<xsl:apply-templates/>)
</xsl:otherwise>
</xsl:choose>
</xsl:template>

'raw text'
<xsl:template match="text()">
<xsl:value-of select="."/>
</xsl:template>

</xsl:stylesheet>


























