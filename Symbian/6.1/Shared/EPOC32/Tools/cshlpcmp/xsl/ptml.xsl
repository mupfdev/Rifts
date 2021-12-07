<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
<!--
###################################################################################
#
# XSL file to convert PTML documents to HTML
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved
#
# Date 29-06-99
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
<xsl:template match = "ptml">
<HTML>
<HEAD>
<TITLE>Ptml source file</TITLE>
</HEAD>
<BODY>
<xsl:apply-templates/>
</BODY>
</HTML>
</xsl:template>

'plain text'
<xsl:template match="p">
<p><xsl:if test='.[@style!=""]'><b>style:<xsl:value-of
select="@style"/></b> </xsl:if>
<xsl:apply-templates/></p>
</xsl:template>

'trow this is a single row in a table as we don't know'
'where the table starts each row is treated as a separate table'
<xsl:template match="trow">
<table border="1"><tr><xsl:apply-templates/></tr></table>
</xsl:template>

'cell within a table row'
<xsl:template match="cell">
<td><xsl:apply-templates/></td>
</xsl:template>


'illegl manual formatting'
<xsl:template match="manual">
<b><xsl:value-of select="@formattype"/>:</b><font color="red"><xsl:apply-templates/></font>
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

'character style formatting'
<xsl:template match='cs'>
<b>&lt;style:<xsl:value-of select="@style"/></b>
<xsl:apply-templates/><b>&gt;</b>;
</xsl:template>

'raw text'
<xsl:template match="text()">
<xsl:value-of select="."/>
</xsl:template>

</xsl:stylesheet>


























