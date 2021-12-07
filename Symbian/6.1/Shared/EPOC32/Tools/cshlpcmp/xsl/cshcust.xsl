<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
<!--
###################################################################################
#
# XSL file to convert CS-Help customization files to HTML
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved
#
# Date 31-8-99
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

<!-- cshcust node match -->
<xsl:template match = "cshcust">
<HTML>
<HEAD>
<TITLE>CS-Help customization file</TITLE>
</HEAD>
<BODY>
<H1>CS-Help customisation file</H1>
<xsl:apply-templates/>
</BODY>
</HTML>
</xsl:template>

'handle the titlestyle'
<xsl:template match="titlestyle">
<h2>TitleStyle</h2>
<p><b>fontstyle: </b><xsl:value-of select="@fontstyle"/></p>
<p><b>size: </b><xsl:value-of select="@size"/></p>
</xsl:template>

'handle the bodystyle'
<xsl:template match="bodystyle">
<h2>BodyStyle</h2>
<p><b>bodystyle: </b><xsl:value-of select="@fontstyle"/></p>
<p><b>size: </b><xsl:value-of select="@size"/></p>
</xsl:template>

'handle the lists'
<xsl:template match="lists">
<h2>Lists</h2>
<p><b>leftindent: </b><xsl:value-of select="@leftindent"/></p>
</xsl:template>

'handle the listbullet1style'
<xsl:template match="listbullet1style">
<h2>ListBullet1Style</h2>
<p><b>bulletchar: </b><xsl:value-of select="@bulletchar"/></p>
</xsl:template>

'handle the listbullet2style'
<xsl:template match="listbullet2style">
<h2>ListBullet2Style</h2>
<p><b>bulletchar: </b><xsl:value-of select="@bulletchar"/></p>
</xsl:template>

'handle the noteeffects'
<xsl:template match="noteeffects">
<h2>NoteEffects</h2>
<p><b>text: </b><xsl:apply-templates/></p>
<p><b>leftindent: </b><xsl:value-of select="@leftindent"/></p>
<p><b>archive: </b><xsl:value-of select="@archive"/></p>
<p><b>name: </b><xsl:value-of select="@name"/></p>
</xsl:template>

'handle the tipeffects'
<xsl:template match="tipeffects">
<h2>TipEffects</h2>
<p><b>text: </b><xsl:apply-templates/></p>
<p><b>leftindent: </b><xsl:value-of select="@leftindent"/></p>
<p><b>archive: </b><xsl:value-of select="@archive"/></p>
<p><b>name: </b><xsl:value-of select="@name"/></p>
</xsl:template>

'handle parastyles'
<xsl:template match="parastyle">
<h2>Paragraph style '<xsl:value-of select="@name"/>'</h2>
<p><b>font: </b><xsl:value-of select="@font"/>
<b>, size: </b><xsl:value-of select="@size"/>
<b>, style: </b><xsl:value-of select="@style"/>
<b>, color: </b><xsl:value-of select="@color"/></p>
<p><b>justification: </b><xsl:value-of select="@justify"/></p>
<p><b>line spacing: </b><xsl:value-of select="@spacing"/></p>
<p><b>left spacing: </b><xsl:value-of select="@left"/>
<b>, right: </b><xsl:value-of select="@right"/>
<b>, before: </b><xsl:value-of select="@before"/>
<b>, after: </b><xsl:value-of select="@after"/></p>
<p><b>image: </b><xsl:value-of select="@image"/></p>
<p><b>leading text: </b><xsl:apply-templates/></p>
</xsl:template>

'handle charstyles'
<xsl:template match="charstyle">
<h2>Character style '<xsl:value-of select="@name"/>'</h2>
<p><b>font: </b><xsl:value-of select="@font"/></p>
<p><b>font size: </b><xsl:value-of select="@size"/></p>
<p><b>font style: </b><xsl:value-of select="@style"/></p>
<p><b>font color: </b><xsl:value-of select="@color"/></p>
</xsl:template>

'handle the importanteffects'
<xsl:template match="importanteffects">
<h2>ImportantEffects</h2>
<p><b>text: </b><xsl:apply-templates/></p>
<p><b>leftindent: </b><xsl:value-of select="@leftindent"/></p>
<p><b>archive: </b><xsl:value-of select="@archive"/></p>
<p><b>name: </b><xsl:value-of select="@name"/></p>
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

'raw text'
<xsl:template match="text()">
<xsl:value-of select="."/>
</xsl:template>

</xsl:stylesheet>














