#!perl
################################################################################
#
# module: ptmlfile.pm
#
# module implements the ptml file object
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved
#
# Date Mon July 5 10:46:21 1999
#
################################################################################
package CPtmlFile;

use Carp;
use strict;

use devtools;
use stack;
 
################################################################################
#
# Function New
#
# Function creates a new ptmlfile object
#
# Function takes: the path / filename of the source file and the path/ filename
# of the destination file
#
# Function Returns: the created object
#
# Function Uses:
#
# Notes:
#################################################################################
sub New ($$)
    {
    my $proto = shift;
    my($aPtmlFile,$aCsptmlFile) = @_;

    my $class = ref($proto) || $proto;

    my $self  = {};
    bless($self, $class);

    $self->_iLog(New CLog());

    $self->_iPtmlFile($aPtmlFile);
    $self->_iCsptmlFile($aCsptmlFile);

    $self->_iPtmlDom(undef);
    $self->_iCsptmlDom(undef);

    $self->_iStack(New CStack());

    return $self;
    }

################################################################################
#
# Function DESTROY
#
# Function Destructor for the object ensures that the PtmlDom and CsptmlDom
# objects are disposed
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub DESTROY
    {
    my $self = shift;

    $self->_iPtmlDom->dispose();
    $self->_iCsptmlDom->dispose();
    }

################################################################################
#
# Function _iLog _iPtmlFile _iCSptmlfile _iPtmlDom _iCsptmlDom _iCurrNode _iStack
#
# Function access the data of the given object
#
# Function takes:
#
# Function Returns: the value of the data
#
# Function Uses:
#
# Notes:
#################################################################################
sub _iLog
    {
    my $self = shift;
    if (@_) { $self->{LOG} = shift }
    return $self->{LOG};
    }

sub _iPtmlFile
    {
    my $self = shift;
    if (@_) { $self->{PTMLFILE} = shift }
    return $self->{PTMLFILE};
    }

sub _iCsptmlFile
    {
    my $self = shift;
    if (@_) { $self->{CSPTMLFILE} = shift }
    return $self->{CSPTMLFILE};
    }

sub _iPtmlDom
    {
    my $self = shift;
    if (@_) { $self->{PTMLDOM} = shift }
    return $self->{PTMLDOM};
    }

sub _iCsptmlDom
    {
    my $self = shift;
    if (@_) { $self->{CSPTMLDOM} = shift }
    return $self->{CSPTMLDOM};
    }

#stores the current ptml node to process
sub _iCurrNode
    {
    my $self = shift;
    if (@_) { $self->{CURRNODE} = shift }
    return $self->{CURRNODE};
    }

sub _iStack
    {
    my $self = shift;
    if (@_) { $self->{STACK} = shift }
    return $self->{STACK};
    }

################################################################################
#
# Function ToCsptml
#
# Function converts the ptml file to csptml
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub ToCsptml
    {
    my $self = shift;

    # initilise the Ptml dom
    $self->_InitilisePtml();

    $self->_Parse;

    #write out the created dom
    $self->_iCsptmlDom->printToFile($self->_iCsptmlFile);
    }

################################################################################
#
# Function _InitilisePtml
#
# Function initilises the Ptml dom
#
# Function takes: nothing
#
# Function Returns: nothing
#
# Function Uses:
#
# Notes:
#################################################################################
sub _InitilisePtml
    {
    my $self = shift;

    #load the ptml file
    my $parser = new XML::DOM::Parser();

    $self->_iLog->Log("Processing" . $self->_iPtmlFile);

    my $dom = $parser->parsefile($self->_iPtmlFile);
    #store the ptml dom
    $self->_iPtmlDom($dom);

    }

################################################################################
#
# Function InitiliseCsptml
#
# Function initilises the CSptml dom
#
# Function takes: nothing
#
# Function Returns: nothing
#
# Function Uses:
#
# Notes:
#################################################################################
sub _InitiliseCsptml
    {
    my $self = shift;

    #create an empty csptml dom
    my $doc = new XML::DOM::Document();
    $doc->setXMLDecl($doc->createXMLDecl("1.0"));
    $doc->setDoctype($doc->createDocumentType("csptml",$self->_GetDTDUrl()));
    #store the csptmldom
    $self->_iCsptmlDom($doc);
    # add a processing instruction for the stylesheet
    my $pi=$doc->createProcessingInstruction("xml:stylesheet","href=\"".$self->_GetXSLUrl()."\" title=\"csptml\" type=\"text/xsl\"");    

    $self->_iCsptmlDom->appendChild($pi);

    }

################################################################################
#
# Function _GetDTDUrl
#
# Function checks that the path to the dtd is a valid url and adds the protocol 
# to the url
#
# Function takes: none
#
# Function Returns: the validated url to the dtd files
#
# Function Uses: the globale reference to the parameters
#
# Notes:
#################################################################################
sub _GetDTDUrl
    {
    my $self = shift;

    # check that the dtd and the xsl files for this file exists
    my $dtdUrl = $main::params->ParamItem("DTDLoc")->Value()."/csptml.dtd";

    if(! -e $dtdUrl)
		{
		$self->_iLog->LogDie("Sorry but the file $dtdUrl does not exist. Please check that if CSHLPDTD has been set in your environment, it has been set to the right location.");
		}

    # add the protocol to the url
    $dtdUrl = "file:///$dtdUrl";

    return $dtdUrl;
    }

################################################################################
#
# Function _GetXSLUrl
#
# Function checks that the path to the xsl is a valid url and adds the protocol 
# to the url
#
# Function takes: none
#
# Function Returns: the validated url to the dtd files
#
# Function Uses: the globale reference to the parameters
#
# Notes:
#################################################################################
sub _GetXSLUrl
    {
    my $self = shift;

    my $xslUrl = $main::params->ParamItem("XSLLoc")->Value()."/csptml.xsl";
    if(! -e $xslUrl)
		{
		$self->_iLog->LogDie("Sorry but the file $xslUrl does not exist. Please check that if CSHLPXSL has been set in your environment, it has been set to the right location.");
		}

    # add the protocol
    $xslUrl = "file:///$xslUrl";

    return $xslUrl;
    }

################################################################################
#
# Function _Parse
#
# Function parses the doc 
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _Parse
    {
    my $self = shift;

    my $dom = $self->_iPtmlDom;

    #validate the doctype
    $self->_ValidateDocType($dom->getDoctype);

    # remove all the unallowed manual formating from the ptmlDom
    $self->_RemoveUnallowedManualFormatting();

    #get the nodes in the source file
    my $nodes=$dom->getElementsByTagName("ptml");

    if(!$nodes->item(0))
		{
		$self->_iLog->LogDie("ptml file must contain a ptml tag");
		}

    #initilise the Csptml Dom
    $self->_InitiliseCsptml;

    #push the csptmlDom onto the iNode
    $self->_iStack->Push($self->_iCsptmlDom);

    #prime the current node
    $self->_iCurrNode($nodes->item(0)->getFirstChild);

    #add a csptml node to the csptml dom and push this onto the stack
    my $element = $self->_iCsptmlDom->createElement("csptml");
    $self->_iStack->Top()->appendChild($element);
    $self->_iStack->Push($element);

    #process all the nodes
    $self->_AddSection(0);
    $self->_ProcNodes;

    #clean up the list nodes and the table nodes
    $self->_CleanLists;
    $self->_CleanTables;

    #pop the csptml node
    $self->_iStack->Pop();

    #check that the stack has not been currupted
    if($self->_iStack->Top()!=$self->_iCsptmlDom)
		{
		$self->_iLog->Log("Currupted Node stack");
		}

    #pop the doc back off the iNode
    $self->_iStack->Pop();
    }

################################################################################
#
# Function _RemoveUnallowedManualFormatting();
#
# Function promotes all the nodes contained in <manual> tags to the parent
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _RemoveUnallowedManualFormatting
    {
    my $self = shift;

    # get all the manual elements
    my $nodes = $self->_iPtmlDom->getElementsByTagName ("manual");
    my $n = $nodes->getLength();

    #loop through all the manual nodes
    for (my $i = 0; $i < $n; $i++)
		{
		#get all the child nodes for this node
		my $childNodes = $nodes->item($i)->getChildNodes();

		#loop through all the child nodes
		my $noChildNodes = $childNodes->getLength();

		for(my $j = 0; $j < $noChildNodes; $j++)
			    {
			    # deep copy the child node
			    my $copyNode= $childNodes->item($j)->cloneNode(1);
			    #insert this child node into the parent before the manual node being removed
			    $nodes->item($i)->getParentNode()->insertBefore($copyNode,$nodes->item($i));
			    }

		#all children of manual node promoted delete the promoted node
		$nodes->item($i)->getParentNode()->removeChild($nodes->item($i));
 		}
    }

################################################################################
#
# Function _ProcNodes
#
# Function processes all the nodes in a section
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _ProcNodes
    {
    my $self=shift;

    #loop though all the sibling nodes
    while($self->_iCurrNode)
		{
		#check if this is just a text node
		if($self->_iCurrNode->getNodeType == XML::DOM::TEXT_NODE())
			    {
			    #handle the text node
			    $self->_ProcTextNode;
			    next;
			    }
		    
		#check if this is an element node
		if($self->_iCurrNode->getNodeType == XML::DOM::ELEMENT_NODE())
			    {
			    my $tagName = $self->_iCurrNode->getTagName;
			    my $style = $self->_iCurrNode->getAttribute("style");
			    
			    #handle headings
			    if(($tagName eq "p") and ($style =~ /heading (\d)/i))
					{
					my $level=$1;
					#get the current level of the section
					my $currLevel=$self->_iStack->Top()->getAttribute("level");
					
					#check if this is a sub heading or not
					if($level > $currLevel)
						    {
						    #it's a sub heading
						    $self->_AddSection($level);
						    $self->_ProcHeadingNode();
						    $self->_ProcNodes();
						    }
					else
						    {
						    #get out of the loop
						    last;
						    }
					#continue the loop
					next;
					}

			    #handle a trow
			    if($tagName eq "trow")
					{
					#process the table
					$self->_ProcTableNodes();
					next;
					}

			    #handle a list
			    if(($tagName eq "p") and ($style =~ /^list/i))
					{
					#process the list
					$self->_ProcListNodes();
					next;
					}

			    #handle a definition list
			    if(($tagName eq "p") and ($style =~ /^definition/i))
					{
					#process the list
					$self->_ProcDefinitionListNodes();
					next;
					}

			    #handle plain paragraphs 
			    if($tagName eq "p")
					{
					$self->_ProcPlainParagraphNode();
					next;
					}

			    #otherwise it is not allowed in ptml
			    $self->_iLog->LogDie("Tag is not permitted in ptml\nCurrently:- ".$self->iCurrNode->toString()."\n");
			    }
		}
    #pop the current section
    $self->_iStack->Pop();
    }




################################################################################
#
# Function _AddSection
#
# Function Adds a section layer to the Csptml
#
# Function takes: the level of the section to add
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _AddSection($)
    {
    my $self=shift;

    my($aSecLevel)=@_;

    my $element = $self->_iCsptmlDom->createElement("section");
    $element->setAttribute("level",$aSecLevel);
    $self->_iStack->Top()->appendChild($element);
    $self->_iStack->Push($element);

    }

################################################################################
#
# Function _ProcPlainParagraphNode
#
# Function processes the plain paragraph node
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _ProcPlainParagraphNode
    {
    my $self=shift;

    #make a deep copy of the plain paragraph node
    my $paragraph = $self->_iCurrNode->cloneNode(1);

    $paragraph->setOwnerDocument($self->_iCsptmlDom);

    #add this to the current csptml element
    $self->_iStack->Top()->appendChild($paragraph);

    # move onto the next node
    $self->_iCurrNode($self->_iCurrNode->getNextSibling());
    }

################################################################################
#
# Function _ProcHeadingNode
#
# Function processes heading node
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _ProcHeadingNode
    {
    my $self=shift;

    #make a deep copy of the heading paragraph node
    my $paragraph = $self->_iCurrNode->cloneNode(1);
    $paragraph->setOwnerDocument($self->_iCsptmlDom);

    #remove the style attribute from the paragraph
    $paragraph->removeAttribute("style");
    #change the p tag to heading
    $paragraph->setTagName("heading");

    #add this to the current csptml element
    $self->_iStack->Top()->appendChild($paragraph);

    # move onto the next node
    $self->_iCurrNode($self->_iCurrNode->getNextSibling());
    }

################################################################################
#
# Function _ProcTableNodes
#
# Function processes all the table nodes
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _ProcTableNodes
    {
    my $self=shift;

    #add a table node
    $self->_AddTable($self->_iCurrNode->getAttribute("cwidths"));

    #loop though all the sibling nodes
    while($self->_iCurrNode)
		{
		#check if this is just a text node
		if($self->_iCurrNode->getNodeType() == XML::DOM::TEXT_NODE())
			    {
			    #handle the text node
			    $self->_ProcTextNode();
			    next;
			    }

		#check if this is an element node
		if($self->_iCurrNode->getNodeType() == XML::DOM::ELEMENT_NODE())
			    {
			    my $tagName = $self->_iCurrNode->getTagName();
			    
			    #handle a trow
			    if($tagName eq "trow")
					{
					#get the cwidths of the current node
					my $cwidths = $self->_iCurrNode->getAttribute("cwidths");
					
					#get the current cwidths
					my $currCwidths=$self->_iStack->Top()->getAttribute("cwidths");
					
					#check if this trow belongs to this table
					if($cwidths eq $currCwidths)
						    {
						    #process the row
						    $self->_ProcRowNodes();
						    }
					else
						    {
						    # break the loop
						    last;
						    }
					#continue the loop
					next
					}
			    }
		#otherwise break the loop
		last
		}
    #pop the table
    $self->_iStack->Pop();
    return;
    }

################################################################################
#
# Function _AddTable
#
# Function Adds a table node
#
# Function takes: the cwidths of the table
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _AddTable($)
    {
    my $self=shift;

    my ($aCwidths) = @_;

    #add a table to the document
    my $element = $self->_iCsptmlDom->createElement("table");
    #add the cwidths
    $element->setAttribute("cwidths",$aCwidths);
    $self->_iStack->Top()->appendChild($element);
    $self->_iStack->Push($element);
    }

################################################################################
#
# Function _ProcRowNodes
#
# Function processes the row nodes
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _ProcRowNodes
    {
    my $self=shift;

    #add a row node
    $self->_AddRow();

    #remember this row node
    my $rowNode = $self->_iCurrNode;

    #loop through all the children nodes
    $self->_iCurrNode($rowNode->getFirstChild());

    #loop though all the  nodes
    while($self->_iCurrNode)
		{
		#check if this is just a text node
		if($self->_iCurrNode->getNodeType() == XML::DOM::TEXT_NODE())
			    {
			    #handle the text node
			    $self->_ProcTextNode();
			    next;
			    }

		#check if this is an element node
		if($self->_iCurrNode->getNodeType() == XML::DOM::ELEMENT_NODE())
			    {
			    my $tagName = $self->_iCurrNode()->getTagName();
			    
			    #handle a cell
			    if($tagName eq "cell")
					{
					#process the cell nodes
					$self->_ProcCellNodes();
					#continue the loop
					next
					}
			    }
		#otherwise break the loop
		last
		}
    #pop the row
    $self->_iStack->Pop();

    #move on to the next sybling to this row node
    $self->_iCurrNode($rowNode->getNextSibling());

    return;
    }

################################################################################
#
# Function -AddRow
#
# Function Adds a Row node
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _AddRow
    {
    my $self = shift;

    #add a row to the document
    my $element = $self->_iCsptmlDom->createElement("row");
    $self->_iStack->Top()->appendChild($element);
    $self->_iStack->Push($element);
    }


################################################################################
#
# Function _ProcCellNodes
#
# Function processes the cell nodes
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _ProcCellNodes
    {
    my $self=shift;

    #add a row node
    $self->_AddCell();

    #remember this cell node
    my $cellNode = $self->_iCurrNode;

    #loop through all the children nodes
    $self->_iCurrNode($cellNode->getFirstChild());

    #loop though all the  nodes
    while($self->_iCurrNode)
		{
		#check if this is just a text node
		if($self->_iCurrNode->getNodeType() == XML::DOM::TEXT_NODE())
			    {
			    #handle the text node
			    $self->_ProcTextNode();
			    next;
			    }

		#check if this is an element node
		if($self->_iCurrNode->getNodeType() == XML::DOM::ELEMENT_NODE())
			    {
			    my $tagName = $self->_iCurrNode->getTagName();
			    my $style = $self->_iCurrNode->getAttribute("style");
			    
			    #handle a list
			    if(($tagName eq "p") and ($style =~ /list/i))
					{
					#process the list
					$self->_ProcListNodes();
					#continue the loop
					next;
					}

			    #handle a definition list
			    if(($tagName eq "p") and ($style =~ /^definition/i))
					{
					#process the list
					$self->_ProcDefinitionListNodes();
					next;
					}

			    #handle a plain paragraph
			    if($tagName eq "p")
					{
					#process the plain paragraph
					$self->_ProcPlainParagraphNode();
					#continue the loop
					next;
					}


			    #otherwise it is not allowed in a table
			    $self->_iLog->LogDie("Tag is not permitted in a table cell\nCurrently:- ".$self->iCurrNode->toString()."\n");
			    }
		#otherwise break the loop
		last
		}
    #pop the row
    $self->_iStack->Pop();

    #move on to the next sybling to this row node
    $self->_iCurrNode($cellNode->getNextSibling());

    return;
    }

################################################################################
#
# Function _AddCell
#
# Function Adds a Cell node
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub AddCell
    {
    my $self = shift;

    #add a row to the document
    my $element = $self->_iCsptmlDom->createElement("cell");
    $self->_iStack->Top()->appendChild($element);
    $self->_iStack->Push($element);
    }

################################################################################
#
# Function _ProcListNodes
#
# Function processes all the list nodes
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _ProcListNodes
    {
    my $self=shift;

    #extract the style and the level of this list from the paragraph style
    my $style = $self->_GetListStyle($self->_iCurrNode->getAttribute("style"));
    my $level = $self->_GetListLevel($style);

    #add a list node
    $self->_AddList($style);

    #loop though all the sibling nodes
    while($self->_iCurrNode)
		{
		#check if this is just a text node
		if($self->_iCurrNode->getNodeType() == XML::DOM::TEXT_NODE())
			    {
			    #handle the text node
			    $self->_ProcTextNode();
			    next;
			    }

		#check if this is an element node
		if($self->_iCurrNode->getNodeType() == XML::DOM::ELEMENT_NODE())
			    {
			    my $tagName = $self->_iCurrNode->getTagName();
    			    my $style = $self->_iCurrNode->getAttribute("style");

			    #handle a trow
			    if($tagName eq "trow")
					{
					#process the table
					$self->_ProcTableNodes();
					next;
					}

			    # check for list paragraph
			    if(($tagName eq "p") and ($style =~ /^list/i))
					{
					# get the level and style of this list
					my $level = $self->_GetListLevel($style);
					$style = $self->_GetListStyle($style);

					#get the style and level of the current list
					my $currStyle = $self->_iStack->Top()->getAttribute("style");
					my $currLevel = $self->_iStack->Top()->getAttribute("level");

				   	#handle same level
					if(($currStyle eq $style) and  ($currLevel == $level))
						    {
						    #process the list item
						    $self->_ProcListItemNode();
						    next;
						    }

					#handle same style nested list
					if(($currStyle eq $style) and  ($level > $currLevel))
						    {
						    #process the list item
						    $self->_ProcListNodes();
						    next;
						    }
					
					#handle same list type but down a level
					if(($currStyle eq $style) and ($level < $currLevel))
						    {
						    #get out of the loop
						    last;
						    }

					#handle different list style
					if($currStyle ne $style)
						    {
						    #get out of the loop
						    last;
						    }
					}
			    }
		#otherwise break the loop
		last;
		}
    #pop the list
    $self->_iStack->Pop();
    return;
    }

################################################################################
#
# Function _GetListLevel
#
# Function extracts the level of a list from the paragraph style
#
# Function takes: the style
#
# Function Returns: the level of the style
#
# Function Uses:
#
# Notes:
#################################################################################
sub _GetListLevel($)
    {
    my $self = shift;
    
    my($aStyle) = @_;

    #get the ending number if there is one
    $aStyle =~ /(\d+)$/; 
    my $level = $1;
    #if there is no ending number make this list level 1
    if(!$level)
		{
		$level = 1;
		}
    return $level;
    }

################################################################################
#
# Function _GetListStyle
#
# Function extracts the style of a list from the paragraph style
#
# Function takes: the style
#
# Function Returns: the extracted style
#
# Function Uses:
#
# Notes: list continue paragraphs are coerced to have a list bullet style
#################################################################################
sub _GetListStyle($)
    {
    my $self = shift;
    
    my($aStyle) = @_;
    my $style = $aStyle;

    #get the style
    if($style =~ /list (.+) (\d+)$/i)
		{
		# its a style with a number
		$style = $1;
		}
    else
		{
		#its just a plain list style
		$style =~ /list (.+)$/i;
		$style=$1;
		}

    # check if this is a list continue
    if($style eq "continue")
		{
		#if we are contained in a list then set the style to the same as the containing list
		if($self->_iStack->Top()->getTagName() eq "list")
			    {
			    #get the style and level of the current list
			    $style = $self->_iStack->Top()->getAttribute("style");
			    }
		else
			    {
			    # default to a bulleted list
			    $style = "bullet";
			    }
		}
    return $style;
    }

################################################################################
#
# Function _AddList
#
# Function Adds a list node
#
# Function takes: the style of the list
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _AddList($)
    {
    my $self=shift;
    my($aStyle)=@_;

    #add a list to the document
    my $element = $self->_iCsptmlDom->createElement("list");
    #add the style
    $element->setAttribute("style",$aStyle);
    #add the level 1 more than the current list level
    if($self->_iStack->Top()->getTagName() eq "list")
		{
		$element->setAttribute("level",$self->_iStack->Top()->getAttribute("level")+1);
		}
    else
		{
		$element->setAttribute("level","1");
		}
    $self->_iStack->Top()->appendChild($element);
    $self->_iStack->Push($element);
    }

################################################################################
#
# Function _ProcListItemNode
#
# Function processes the list item node
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes: list continue paragraphs are emitted as <p>paragraph content</p>
#################################################################################
sub _ProcListItemNode
    {
    my $self=shift;

    #make a copy of the List node
    my $listitem = $self->_iCurrNode->cloneNode(1);
    $listitem->setOwnerDocument($self->_iCsptmlDom);

    #get the style
    my $style = $listitem->getAttribute("style");

    #remove the styleattribute
    $listitem->removeAttribute("style");

    #change the tag name according to the style
    if($style =~ /list continue/i)
		{
		#change tag name to listitem
		$listitem->setTagName("p");
		}
    else
		{
		#change tag name to listitem
		$listitem->setTagName("listitem");
		}

    #if its a manual list
    if($self->_iStack->Top()->getAttribute("style") eq "manual")
		{
		#get the node list of all the children
		my $childNode = $listitem->getChildNodes();

		# check that the second node is a &tab;
		if(!($childNode->item(1) && ($childNode->item(1)->toString() eq "&tab;")))
			    {
			    $self->_iLog->LogDie("Manual list item must have a number optionally followed by a punctuation mark [.)-,] then a tab\nCurrently:- ".$listitem->toString()."\n");
			    }

		#get the number into the value
		$listitem->setAttribute("value",$self->_GetListItemValue($childNode->item(0)->toString()));
		#remove the list item value node and the tab node the nodelist is 
		# live so we remove the first node twice
		$listitem->removeChild($childNode->item(0));		
		$listitem->removeChild($childNode->item(0));
		}
		
    #add the listitem to the current csptml element
    $self->_iStack->Top()->appendChild($listitem);

    #move on to the next node
    $self->_iCurrNode($self->_iCurrNode->getNextSibling()); 
    }

################################################################################
#
# Function _GetListItemValue
#
# Function obtains a value from a string following the following pattern
# ^\b+ *[.-),]?$
#
# Function takes: the string to extract the item tag from
#
# Function Returns: the item tag
#
# Function Uses:
#
# Notes: if the string follows ^\d+ *[.-),]$ then the number without the
# punctuation is returned else the string passed is returned
#################################################################################
sub _GetListItemValue($)
    {
    my $self=shift;
    my($aString)=@_;

    my $string = $aString;

    #remove any trailing punctuation
    $string =~ s/[,-.)]$//;

    #check if the string is not a number
    if(!($string =~ /^\d+ *$/))
                {
		$self->_iLog->LogDie("Items in a manual list must start with a number\nCurrently:- ".$self->_iCurrNode->toString()."\n");
		}
    return $string;
    }

################################################################################
#
# Function _ProcDefinitionListNodes
#
# Function processes all the definition list nodes
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _ProcDefinitionListNodes
    {
    my $self=shift;

    #add a definition list node
    $self->_AddDefinitionList();

    #loop though all the sibling nodes
    while($self->_iCurrNode)
		{
		#check if this is just a text node
		if($self->_iCurrNode->getNodeType() == XML::DOM::TEXT_NODE())
			    {
			    #handle the text node
			    $self->_ProcTextNode();
			    next;
			    }

		#check if this is an element node
		if($self->_iCurrNode->getNodeType() == XML::DOM::ELEMENT_NODE())
			    {
			    my $tagName = $self->_iCurrNode->getTagName();
    			    my $style = $self->_iCurrNode->getAttribute("style");

			    # check for definition term
			    if(($tagName eq "p") and ($style eq "definition term"))
					{
					#process the definition term
					$self->_ProcDefinitionTermNode();
					next;
					}

			    # check for definition definition
			    if(($tagName eq "p") and ($style eq "definition definition"))
					{
					#process the definition definition
					$self->_ProcDefinitionDefinitionNode();
					next;
					}

			    # check for paragraph style="comment"
			    if(($tagName eq "p") and ($style eq "comment"))
					{
					#process the comment
					$self->_ProcPlainParagraphNode();
					next;
					}
			    }
		#otherwise break the loop
		last;
		}
    #pop the list
    $self->_iStack->Pop();
    return;
    }

################################################################################
#
# Function _AddDefinitionList
#
# Function Adds a Definitionlist node
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _AddDefinitionList
    {
    my $self=shift;

    #add a Definition list to the document
    my $element = $self->_iCsptmlDom->createElement("deflist");
    $self->_iStack->Top()->appendChild($element);
    $self->_iStack->Push($element);
    }

################################################################################
#
# Function _ProcDefinitionTermNode
#
# Function processes all the definition term node
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _ProcDefinitionTermNode
    {
    my $self=shift;

    #make a copy of the term node
    my $term = $self->_iCurrNode->cloneNode(1);
    $term->setOwnerDocument($self->_iCsptmlDom);

    #remove the styleattribute
    $term->removeAttribute("style");

    #change tag name to term
    $term->setTagName("term");
		
    #add this to the current csptml element
    $self->_iStack->Top()->appendChild($term);

    #move on to the next node
    $self->_iCurrNode($self->_iCurrNode->getNextSibling()); 
    return;
    }

################################################################################
#
# Function _ProcDefinitionDefinitionNode
#
# Function processes all the definition definition node
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _ProcDefinitionDefinitionNode
    {
    my $self=shift;

    #make a copy of the definition node
    my $definition = $self->_iCurrNode->cloneNode(1);
    $definition->setOwnerDocument($self->_iCsptmlDom);

    #remove the styleattribute
    $definition->removeAttribute("style");

    #change tag name to definition
    $definition->setTagName("definition");
		
    #add this to the current csptml element
    $self->_iStack->Top()->appendChild($definition);

    #move on to the next node
    $self->_iCurrNode($self->_iCurrNode->getNextSibling()); 
    return;
    }

################################################################################
#
# Function _ProcTextNode
#
# Function processes the text node
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _ProcTextNode
    {
    my $self=shift;

    #make a copy of the text node
    my $text = $self->_iCurrNode->cloneNode();

    $text->setOwnerDocument($self->_iCsptmlDom);

    #add this to the current csptml element
    $self->_iStack->Top()->appendChild($text);

    #move on to the next node
    $self->_iCurrNode($self->_iCurrNode->getNextSibling()); 
    }

################################################################################
#
# Function _CleanLists
#
# Function removes the level attribute from all the list nodes in the document
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _CleanLists
    {
    my $self=shift;

    # get all the list elements
    my $nodes = $self->_iCsptmlDom->getElementsByTagName ("list");
    my $n = $nodes->getLength();

    #loop through all the list nodes
    for (my $i = 0; $i < $n; $i++)
		{
		#remove the level attribute from each list node
		$nodes->item($i)->removeAttribute("level");
		}
    }

################################################################################
#
# Function _CleanTables
#
# Function removes the cwidths attribute from all the table nodes in the document
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _CleanTables
    {
    my $self=shift;

    # get all the table elements
    my $nodes = $self->_iCsptmlDom->getElementsByTagName ("table");
    my $n = $nodes->getLength();

    #loop through all the table nodes
    for (my $i = 0; $i < $n; $i++)
		{
		#remove the cwidths attribute from each list node
		$nodes->item($i)->removeAttribute("cwidths");
		}
    }


################################################################################
#
# Function _ValidateDocType
#
# Function validates the doc type 
#
# Function takes: the doctype node
#
# Function Returns: none
#
# Function Uses: none
#
# Notes:
#################################################################################
sub _ValidateDocType
    {
    my $self = shift;
    my($aNode) = @_;

    #check that a doc type is given
    if($aNode)
		{
		#check that the doctype is correct
		if($aNode->getName() ne "ptml")
			    {
			    $self->_iLog->logDie($self->iPtmlFile." is not a ptml file");
			    }
		}
    else
		{
		$self->_iLog->Log("No DOCTYPE present assuming file is a ptml file\n");
		}
    }

################################################################################
#
# Function TEST
#
# Function the test code for the ptml file object
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub TEST
    {
    my $self = shift;

    $self->_iLog->Log("#######################");
    $self->_iLog->Log("Test1 store object data");
    
    $self->_iLog->Log("filling up the data");
    $self->_iPtmlFile("the input ptml file");
    $self->_iCsptmlFile("the output csptml file");

    $self->_iLog->Log("Recovering data");

    $self->PRINT;

    $self->_iLog->Log("#######################");
    $self->_iLog->Log("Test2 store ptml file into the ptml dom and parse it");

    my $parser = new XML::DOM::Parser();
    my $doc = $parser->parse (
"<?xml version=\"1.0\"?>
<?xml:stylesheet href=\"file:///h:/cshlpcmp/xsl/ptml.xsl\" title=\"PTML\" type=\"text/xsl\"?>
<!DOCTYPE ptml SYSTEM \"file:///h:/cshlpcmp/dtd/ptml.dtd\">
<ptml>
<p style=\"comment\">Author:Symbian Ltd.</p>
<p style=\"comment\">Date:January 1999</p>
<p style=\"comment\">Version:1.0</p>
<p style=\"heading 1\">Boss Puzzle</p>
<p style=\"category uid\">0x01000000</p>
<p style=\"heading 2\">Boss puzzle: quick start</p>
<p style=\"context\">context1 <cs style=\"context comment\">this is a comment for this context</cs></p>
<p style=\"context\">context2 <cs style=\"context comment\">this is another context comment</cs></p>
<p style=\"context\">context3</p>
<p style=\"index\">this is &amp;the index 1</p>
<p style=\"index\">this is the index 2</p>
<p style=\"index\">this is the index 3</p>
<p style=\"synonyms\">start begin activate run</p>
<p>The Boss Puzzle was popularized in the late 1800s by Samuel Lloyd, an American businessman. It consists of a 4x4 grid of tiles, one of which is missing.</p>
<p><cs style=\"graphic link\">archive=fetsrc name=board</cs></p>
<p>The tiles are numbered 1-15. In the original form, tiles 14 and 15 were swapped round.</p>
<p>With the Boss Puzzle application you can:</p>
<p style=\"list bullet\">move tiles on this board <cs style=\"graphic link\">archive=fetsrc name=board</cs></p>
<p style=\"list bullet\">pointing with the pointer</p>
<p style=\"list bullet\">move them using the arrow keys</p>
<p style=\"list bullet\">deal the game either fully ordered or Boss ordered</p>
<p style=\"list bullet\">save games as files</p>
<p style=\"list bullet\">save games as embedded objects</p>
<p style=\"list continue\">Which is a really useful thing to do</p>
<p style=\"heading 2\">Building the &amp;Boss Puzzle</p>
<p>All instructions in this refer to the full EIKON versions of the Boss Puzzle.  Full instructions for building are contained in the EPOC32 C++ SDK, in the <b>Practical Guide</b>.  For a very quick start, try</p>
<p style=\"list number\">cd \\boss\\group\\</p>
<p style=\"list number\">ebld eik7 wins deb</p>
<p>and then invoke the WINS emulator.  You should see that the Boss Puzzle is available on the Extras bar.</p>
<p style=\"heading 2\">Starting the game</p>
<p style=\"synonyms\">invoking initializing invoke initialize</p>
<p>You can start the game by selecting its icon from the Extras bar, or by selecting a file from the Shell, or by selecting or creating an embedded object from a document.</p>
<p style=\"heading 2\">Resetting the game</p>
<p>You can reset the game to fully ordered using <cs style=\"graphic link\">archive=fetsrc name=full-but</cs>, or to Boss ordered using <cs style=\"graphic link\">archive=fetsrc name=boss-but</cs>.</p>
<p style=\"heading 2\">Playing the game</p>
<p style=\"synonyms\">keyboard</p>
<p>To play the game, use the pointer to select and move tiles.  Alternatively, use the arrow keys to move tiles in the direction you want to.</p>
<p>In order to show how to use simple menus, menu support for moving is also provided.  But this is not a very convenient way to play the game.</p>
<p style=\"note\">This is a note paragraph.</p>
<p style=\"tip\">This is a tip paragraph</p>
<p style=\"important\">This is an important paragraph</p>
<p style=\"heading 2\">Embedding objects</p>
<p>You can embed a Boss Puzzle game into other documents.  For instance, from Word, try</p>
<p style=\"list number\">insert object (<b>CTRL+SHIFT+O</b>)</p>
<p style=\"list number\">select <b>Boss Puzzle</b> as the &ldquote;from program&rdquote;</p>
<p style=\"list number\">select <b>Ok</b></p>
<p style=\"list number 2\">This is a list within a list</p>
<p style=\"list number 2\">this is more of a list within a list</p>
<p style=\"list number 2\">and yet more</p>
<p style=\"list number\">make a few moves in the Boss Puzzle game</p>
<p style=\"list number\">exit the embedded Boss Puzzle game</p>
<p>The Boss Puzzle is then displayed in Word, using the glass door capability.  The Boss Puzzle supports zooming: try zooming the word document in and out using <b>CTRL+M</b> and <b>CTRL+SHIFT+M</b>.</p>
<p style=\"heading 2\">Manual and definition list test topic</p>
<p>This is a manually numbered list the list items must be proceeded with a number followed optionally by a period, which must be followed by a tab.</p>
<p style=\"list manual\">1.&tab;This is list item 1</p>
<p style=\"list manual\">5.&tab;This is list item 2</p>
<p style=\"list manual\">8.&tab;This is list item 3</p>
<p>This is a definition list</p>
<p style=\"definition term\">Aleppo</p>
<p style=\"definition definition\">First Epoc Help</p>
<p style=\"comment\">This is a comment in a definition list</p>
<p style=\"definition term\">This is another term</p>
<p style=\"definition definition\">This is the definition for the term</p>
<p style=\"definition term\">Aleppo</p>
<p style=\"definition definition\">The first Epoc Help compiler. This was used as the bases for the CS-help compiler.</p>
<p style=\"definition term\">Samaria</p>
<p style=\"definition definition\">Symbian&rquote;s HTML authoring tool.</p>
<p>The end of the definition list</p>
</ptml>");

    $self->_iPtmlDom($doc);

    $self->_Parse;
    }

################################################################################
#
# Function PRINT
#
# Function prints out the current contents of the Ptmlfile object
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub PRINT
    {
    my $self = shift;
    $self->_iLog->Log("the input ptml file | ". $self->_iPtmlFile);
    $self->_iLog->Log("the output csptml file | ". $self->_iCsptmlFile);

    $self->_iLog->Log("The current content of the PTMLDOM is ");
    if($self->_iPtmlDom)
		{
		$self->_iLog->Log("\n". $self->_iPtmlDom->toString());
		}
    else
		{
		$self->_iLog->Log("EMPTY");
		}

    $self->_iLog->Log("The current content of the CSPTMLDOM is ");
    if($self->_iCsptmlDom)
		{
		$self->_iLog->Log("\n". $self->_iCsptmlDom->toString());
		}
    else
		{
		$self->_iLog->Log("EMPTY");
		}

    $self->_iLog->Log("The current content of the node stack is");
    my $temp = $self->_iStack->Pop();
    while($temp)
		{
		$self->_iLog->Log("$temp");

		$temp=$self->_iStack->Pop();
		}
    }
1;












