#!perl
################################################################################
#
# module: csptmlfl.pm
#
# module implements the csptml file object
#
# Copyright (c) 1997-1999 Symbian Ltd.	All rights reserved
#
# Date Mon July 5 10:46:21 1999
#
################################################################################
package CCsptmlFile;

use Carp;
use strict;

use devtools;
use stack;
use convmbm;
 
################################################################################
#
# Function New
#
# Function creates a new csptmlfile object
#
# Function takes: the path / filename of the source file the path/ filename
# of the destination file and the graphic dirctory from the project file
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
	my($aCsptmlFile,$aAsptmlFile,$aGraphicsDir) = @_;

	my $class = ref($proto) || $proto;

	my $self  = {};
	bless($self, $class);

	$self->_iLog(New CLog());
	
	$self->_iCsptmlFile($aCsptmlFile);
	$self->_iAsptmlFile($aAsptmlFile);
	$self->_iGraphicsDir($aGraphicsDir);

	$self->_iCategory(undef);
	$self->_iUID(undef);
	
	$self->_iCsptmlDom(undef);
	$self->_iAsptmlDom(undef);

	$self->_iStack(New CStack());

	return $self;
	}

################################################################################
#
# Function DESTROY
#
# Function Destructor for the object ensures that the CstmlDom and AsptmlDom
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

	$self->_iCsptmlDom->dispose();
	$self->_iAsptmlDom->dispose();
	}

################################################################################
#
# Function _iLog _iCsptmlFile _iAsptmlFile _iCategory _iUid
# _iCsptmlDom _iAsptmlDom _iStack
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

sub _iCsptmlFile
	{
	my $self = shift;
	if (@_) { $self->{CSPTMLFILE} = shift }
	return $self->{CSPTMLFILE};
	}

sub _iAsptmlFile
	{
	my $self = shift;
	if (@_) { $self->{ASPTMLFILE} = shift }
	return $self->{ASPTMLFILE};
	}

sub _iGraphicsDir
	{
	my $self = shift;
	if (@_) { $self->{GRAPHICSDIR} = shift }
	return $self->{GRAPHICSDIR};
	}

sub _iCategory
	{
	my $self = shift;
	if (@_) { $self->{CATEGORY} = shift }
	return $self->{CATEGORY};
	}

sub _iUID
	{
	my $self = shift;
	if (@_) { $self->{UID} = shift }
	return $self->{UID};
	}

sub _iCsptmlDom
	{
	my $self = shift;
	if (@_) { $self->{CSPTMLDOM} = shift }
	return $self->{CSPTMLDOM};
	}

sub _iAsptmlDom
	{
	my $self = shift;
	if (@_) { $self->{PTMLDOM} = shift }
	return $self->{PTMLDOM};
	}

sub _iStack
	{
	my $self = shift;
	if (@_) { $self->{STACK} = shift }
	return $self->{STACK};
	}


#stores the current ptml node to process
sub _iCurrNode
	{
	my $self = shift;
	if (@_) { $self->{CURRNODE} = shift }
	return $self->{CURRNODE};
	}

################################################################################
#
# Function ToAsptml
#
# Function converts the csptml file to Asptml
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub ToAsptml
	{
	my $self = shift;

	# initilise the Ptml dom
	$self->_InitiliseCsptml;

	$self->_Parse;

	#write out the created dom
	$self->_iAsptmlDom->printToFile($self->_iAsptmlFile);
	}

################################################################################
#
# Function _InitiliseCsptml
#
# Function initilises the Csptml dom
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

	#load the csptml file
	my $parser = new XML::DOM::Parser();

	$self->_iLog->Log("processing " . $self->_iCsptmlFile);

	my $dom = $parser->parsefile($self->_iCsptmlFile);
	#store the csptml dom
	$self->_iCsptmlDom($dom);

	}

################################################################################
#
# Function _InitiliseAsptml
#
# Function initilises the Asptml dom
#
# Function takes: nothing
#
# Function Returns: nothing
#
# Function Uses:
#
# Notes:
#################################################################################
sub _InitiliseAsptml
	{

	my $self = shift;

	#create an empty Asptml dom
	my $doc = new XML::DOM::Document();
	$doc->setXMLDecl($doc->createXMLDecl("1.0"));
	$doc->setDoctype($doc->createDocumentType("asptml",$self->_GetDTDUrl()));
	#store the Asptmldom
	$self->_iAsptmlDom($doc);

	my $pi= $self->_iAsptmlDom->createProcessingInstruction("xml:stylesheet","href=\"".$self->_GetXSLUrl()."\" title=\"asptml\" type=\"text/xsl\"");

	$self->_iAsptmlDom->appendChild($pi);
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
	my $dtdUrl = $main::params->ParamItem("DTDLoc")->Value()."/asptml.dtd";

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

	my $xslUrl = $main::params->ParamItem("XSLLoc")->Value()."/asptml.xsl";
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

	my $dom = $self->_iCsptmlDom;

	#validate the doctype
	$self->_ValidateDocType($dom->getDoctype());

	#get the nodes in the source file
	my $nodes=$dom->getElementsByTagName("csptml");

	if(!$nodes->item(0))
		{
		$self->_iLog->LogDie("csptml file must contain a csptml tag");
		}

	#initilise the Asptml Dom
	$self->_InitiliseAsptml;

	#push the AsptmlDom onto the iNode
	$self->_iStack->Push($self->_iAsptmlDom);

	#prime the current node
	$self->_iCurrNode($nodes->item(0)->getFirstChild());

	#add a Asptml node to the Asptml dom and push this onto iNode
	$self->_AddAsptml();

	$self->_ProcNodes();

	#pop the Asptml node
	$self->_iStack->Pop();

	#check that the stack has not been currupted
	if($self->_iStack->Top()!=$self->_iAsptmlDom)
		{
		$self->_iLog->Log("Currupted Node stack");
		}

	#pop the doc back off the iNode
	$self->_iStack->Pop();
	}

################################################################################
#
# Function _ProcNodes
#
# Function processes all the nodes
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
		if($self->_iCurrNode->getNodeType() == XML::DOM::TEXT_NODE())
			{
			#handle the text node
			$self->_CopyNode();
			next;
			}
					
		#check if this is an element node
		if($self->_iCurrNode->getNodeType() == XML::DOM::ELEMENT_NODE())
			{
			my $tagName = $self->_iCurrNode->getTagName();
			#get the level for the section
			my $level=$self->_iCurrNode->getAttribute("level");
							
			#handle sections
			if(($tagName eq "section") && ($level == 0))
				{
				$self->_ProcSectionLevel0Node();
				next;
				}
			}
		$self->_iLog->LogDie("csptml file must start with a <section level=\"0\"> tag\nCurrently:- ".$self->_iCurrNode->toString()."\n");
		}
	}

################################################################################
#
# Function _ProcSectionLevel0Node
#
# Function processes all the nodes in the section level=0
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _ProcSectionLevel0Node
	{
	my $self=shift;

	#remember this section node
	my $sectionNode = $self->_iCurrNode;
	#process all the section nodes of this section
	$self->_iCurrNode($sectionNode->getFirstChild());

	#loop though all the sibling nodes
	while($self->_iCurrNode)
		{
		#check if this is just a text node
		if($self->_iCurrNode->getNodeType() == XML::DOM::TEXT_NODE())
			{
			#handle the text node
			$self->_CopyNode();
			next;
			}

		#check if this is an element node
		if($self->_iCurrNode->getNodeType() == XML::DOM::ELEMENT_NODE())
			{
			my $tagName = $self->_iCurrNode->getTagName();
			#get the level for the section
			my($level)=$self->_iCurrNode->getAttribute("level");
			#get the style for the paragraph
			my($style)=$self->_iCurrNode->getAttribute("style");

			#handle sections
			if(($tagName eq "section") && ($level == 1))
				{
				$self->_ProcSectionLevel1Node();
				next;
				}
			#handle comments
			if(($tagName eq "p") && ($style eq "comment"))
				{
				$self->_ProcCommentNode();
				next;
				}

			}
			$self->_iLog->LogDie("<Section level=\"0\"> tags may only contain <p style=\"comment\">\nand <section level=\"1\"> tags.\nCurrently:- ".$self->_iCurrNode->toString()."\n");
		}

	#move on to the next sibling to section level 0 node
	$self->_iCurrNode($sectionNode->getNextSibling());
	}

################################################################################
#
# Function _ProcSectionLevel1Node
#
# Function processes all the nodes in the section level=1
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _ProcSectionLevel1Node
	{
	my $self=shift;

	#remember this section node
	my $sectionNode = $self->_iCurrNode;
	#process all the section nodes of this section
	$self->_iCurrNode($sectionNode->getFirstChild());

	#process the section level 1 header
	$self->_ProcSectionLevel1Header();

	#add the uid to the asptml
	$self->_AddUID($self->_iUID);

	#the header must be followed by a section 2 node
	$self->_ProcSectionLevel1Level2Nodes();

	#move on to the next sibling to this section level 1 node
	$self->_iCurrNode($sectionNode->getNextSibling());
	}

################################################################################
#
# Function _ProcSectionLevel1Header
#
# Function processes the header nodes int the section level=1
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _ProcSectionLevel1Header
	{
	my $self=shift;

	#loop though all the nodes in the header
	while($self->_iCurrNode)
		{
		#check if this is just a text node
		if($self->_iCurrNode->getNodeType() == XML::DOM::TEXT_NODE())
			{
			#handle the text node
			$self->_CopyNode();
			next;
			}

		#check if this is an element node
		if($self->_iCurrNode->getNodeType() == XML::DOM::ELEMENT_NODE())
			{
			my $tagName = $self->_iCurrNode->getTagName();
			#get the style for the paragraph
			my($style)=$self->_iCurrNode->getAttribute("style");

			#handle the heading
			if($tagName eq "heading")
				{
				$self->_ProcCategoryNode();
				next;
				}

			#handle the UID
			if(($tagName eq "p") && ($style eq "category uid"))
				{
				$self->_ProcUIDNode();
				next;
				}

			#handle comments
			if(($tagName eq "p") && ($style eq "comment"))
				{
				$self->_ProcCommentNode();
				next;
				}
			}
			#tag indicates that the end of the header has been reached
			last;
			}
	#check that both the heading and the UID are present
	if(!$self->_iCategory)
		{
		$self->_iLog->LogDie("A <Section level=\"1\"> tag must contain a <heading> tag before the first <section level=\"2\"> tag.\nCurrently:- ".$self->_iCurrNode->toString()."\n");
		}
	if(!$self->_iUID)
		{
		$self->_iLog->LogDie("A <Section level=\"1\"> tag must contain a <p style=\"category uid\" > tag before the first <section level=\"2\"> tag.\nCurrently:- ".$self->_iCurrNode->toString()."\n");
		}
	}

################################################################################
#
# Function _ProcCategoryNode
#
# Function processes the first heading tag in the section level 1, This contains
# the category for the help file topics
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _ProcCategoryNode
	{
	my $self=shift;

	#check we have not seen a heading before
	if($self->_iCategory)
		{
		$self->_iLog->LogDie("<Section level=\"1\"> tag can only contain one <heading> tag.\nCurrently:- ".$self->_iCurrNode->toString()."\n");
		}

	#check that the heading contains no formatting (one text node child only)
	if(!($#{$self->_iCurrNode->getChildNodes()}==0) && ($self->_iCurrNode->getFirstChild->getNodeType() == XML::DOM::TEXT_NODE()))
		{
		$self->_iLog->LogDie("<Section level=\"1\"> <heading> tag must not contain any formatting\nCurrently:- ".$self->_iCurrNode->toString()."\n");
		}
		
	#get the string with entity refs expanded and trim any trailing spaces
	my $category = $self->_iCurrNode->getFirstChild()->expandEntityRefs($self->_iCurrNode->getFirstChild()->toString());
	$category =~ s/ *$//;

	#now just record the category
	$self->_iCategory($category);

	#move on to the next sibling to the heading node
	$self->_iCurrNode($self->_iCurrNode->getNextSibling());
	}

################################################################################
#
# Function _ProcUIDNode
#
# Function processes the first <p style="category"> tag in the section level 1
# This contains the UID for the help file topics
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _ProcUIDNode
	{
	my $self=shift;

	#check we have not seen a UID before
	if($self->_iUID)
		{
		$self->_iLog->LogDie("<Section level=\"1\"> tag can only contain one <p style=\"category UID\"> tag.\nCurrently:- ".$self->_iCurrNode->toString()."\n");
		}

	#check that the UID contains no formatting (one text node child only)
	if(!($#{$self->_iCurrNode->getChildNodes()}==0) && ($self->_iCurrNode->getFirstChild()->getNodeType() == XML::DOM::TEXT_NODE()))
		{
		$self->_iLog->LogDie("<Section level=\"1\"> <p style=\"category UID\"> tag must not contain any formatting\nCurrently:- ".$self->_iCurrNode->toString()."\n");
		}

	#just record the uid
	$self->_iUID($self->_iCurrNode->getFirstChild()->toString());

	#move on to the next sibling to the heading node
	$self->_iCurrNode($self->_iCurrNode->getNextSibling());
	}

################################################################################
#
# Function _ProcSectionLevel1Level2Nodes
#
# Function processes all the section level 2 nodes in the a section level =1 
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _ProcSectionLevel1Level2Nodes
	{
	my $self=shift;

	#loop though all the level 2 nodes
	while($self->_iCurrNode)
		{
		#check if this is just a text node
		if($self->_iCurrNode->getNodeType() == XML::DOM::TEXT_NODE())
			{
			#handle the text node
			$self->_CopyNode();
			next;
			}

		#check if this is an element node
		if($self->_iCurrNode->getNodeType() == XML::DOM::ELEMENT_NODE())
			{
			my $tagName = $self->_iCurrNode->getTagName();
			#get the level for the section
			my($level)=$self->_iCurrNode->getAttribute("level");
			#get the style for the paragraph
			my($style)=$self->_iCurrNode->getAttribute("style");
				
			#handle sections
			if(($tagName eq "section") && ($level == 2))
				{
				$self->_ProcSectionLevel2Node();
				next;
				}

			#handle duplicate heading
			if($tagName eq "heading")
				{
				$self->_iLog->LogDie("A <section level=\"1\"> tag may only contain a single <heading> tag before any <section level=\"2\"> tag.\nCurrently:- ".$self->_iCurrNode->toString()."\n");
				}
			#handle duplicate UID
			if(($tagName eq "p") && ($style eq "category UID"))
				{
				$self->_iLog->LogDie("A <section level=\"1\"> tag may only contain a single <p category UID> tag before any <section level=\"2\"> tag.\nCurrently:- ".$self->_iCurrNode->toString()."\n");
				}

			#handle comments
			if(($tagName eq "p") && ($style eq "comment"))
				{
				$self->_ProcCommentNode();
				next;
				}

			}
			$self->_iLog->LogDie("<Section level=\"1\"> tags may only contain <p style=\"comment\">\n and <section level=\"2\"> tags.\nCurrently:- ".$self->_iCurrNode->toString()."\n");
		}
	}

################################################################################
#
# Function _ProcSectionLevel2Node
#
# Function processes a section level 2 node
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _ProcSectionLevel2Node
	{
	my $self=shift;

	my $seenHeading = 0;

	#remember this section node
	my $sectionNode = $self->_iCurrNode;

	#process all the section nodes of this section
	$self->_iCurrNode($sectionNode->getFirstChild());

	#add a topic to the output
	$self->_AddTopic($self->_iCategory);

	#loop though all the level 2 nodes
	while($self->_iCurrNode)
		{

		#check if this is just a text node
		if($self->_iCurrNode->getNodeType() == XML::DOM::TEXT_NODE())
			{
			#handle the text node
			$self->_CopyNode();
			next;
			}

		#check if this is an element node
		if($self->_iCurrNode->getNodeType() == XML::DOM::ELEMENT_NODE())
			{
			my $tagName = $self->_iCurrNode->getTagName();
			#get the style for the paragraph
			my($style)=$self->_iCurrNode->getAttribute("style");

			#handle the heading
			if($tagName eq "heading")
				{
				#process the topic title
				$self->_ProcTopicTitleNode();
				next;
				}

			#handle paragraphs
			if($tagName eq "p")
				{
				$self->_ProcParagraphNode();
				next;
				}

			#handle lists
			if($tagName eq "list")
				{
				$self->_ProcListNodes();
				next;
				}

			#handle deflists
			if($tagName eq "deflist")
				{
				$self->_ProcDefListNodes();
				next;
				}

			}
			$self->_iLog->LogDie("<Section level=\"2\"> tags may only contain <heading>\n<p [style=\"...\"]> tags\n<list style=\"...\"> and <deflist> tags.\nCurrently:- ".$self->_iCurrNode->toString()."\n");
		}

	#check that we saw a heading FIXME

	#pop the topic node
	$self->_iStack->Pop();

	#move on to the next sibling to this section level 2 node
	$self->_iCurrNode($sectionNode->getNextSibling());
	}

################################################################################
#
# Function _ProcParagraphNode
#
# Function processes the paragraph node
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _ProcParagraphNode
	{
	my $self=shift;

	#get the style of the paragraph
	my($style)=$self->_iCurrNode->getAttribute("style");

	SWITCH:
		{
		#check for contexts
		if($style eq "context")
			{
			#process the context node
			$self->_ProcContextNode();
			last SWITCH;
			}

		#check for contexts
		if($style eq "index")
			{
			#process the index node
			$self->_ProcIndexNode();
			last SWITCH;
			}

		#check for comments
		if($style eq "comment")
			{
			#process the comment node
			$self->_ProcCommentNode();
			last SWITCH;
			}

		#check for synonyms
		if($style eq "synonyms")
			{
			#process the synonyms node
			$self->_ProcSynonymsNode();
			last SWITCH;
			}

		#otherwise

		#add a paragraph of the right style to node to the asptml
		$self->_AddParagraph($style);
		#process the paragraph nodes
		$self->_ProcParagraphNodes();
		#pop the paragraph node
		$self->_iStack->Pop();
		}
	}

################################################################################
#
# Function _ProcParagraphNodes
#
# Function processes all the nodes in the paragraph 
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _ProcParagraphNodes
	{
	my $self=shift;

	#remember this paragraph node
	my $paragraphNode = $self->_iCurrNode;
	#process all the nodes of this paragraph
	$self->_iCurrNode($paragraphNode->getFirstChild());

	#loop though all the paragraph's nodes
	while($self->_iCurrNode)
		{

		#check if this is just a text node
		if($self->_iCurrNode->getNodeType() == XML::DOM::TEXT_NODE())
			{
			#handle the text node
			$self->_CopyNode();
			next;
			}

		#check if this is just an entity
		if($self->_iCurrNode->getNodeType() == XML::DOM::ENTITY_REFERENCE_NODE())
			{
			#handle the entity node
			$self->_CopyNode();
			next;
			}

		#check if this is an element node
		if($self->_iCurrNode->getNodeType() == XML::DOM::ELEMENT_NODE())
			{
			# get the tag name
			my $tagName = $self->_iCurrNode->getTagName();
			#get the style of the tag
			my $style = $self->_iCurrNode->getAttribute("style");

			#check for graphic links
			if(($tagName eq "cs") && ($style eq "graphic link"))
				{
				#process the graphic link
				$self->_ProcGraphicLinkNode();
				next;
				}

			#check for character style manual formatting
			if($tagName eq "cs")
				{
				#process the manual element
				$self->_ProcManualFormatNodes();
				next;
				}
			#check for other manual formating
			if(($tagName eq "b")
			   || ($tagName eq "i")
			   || ($tagName eq "sup")
			   || ($tagName eq "sub"))
				{
				#process the manual element
				$self->_ProcManualFormatNodes();
				next;
				}
			}
		$self->_iLog->LogDie("<p [style=\"...\"]> tags may only contain <cs style=\"...\"> tags, <b>, <i>, <sup> and <sub>\nCurrently:- ".$self->_iCurrNode->toString()."\n");
		}

	#move on to the next sibling to this paragraph node
	$self->_iCurrNode($paragraphNode->getNextSibling());
	}

################################################################################
#
# Function _ProcContextNode
#
# Function processes this context
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _ProcContextNode
	{
	my $self=shift;

	my $context="";
	my $comment="";

	#remember this context node
	my $contextNode = $self->_iCurrNode;
	#process all the nodes of this paragraph
	$self->_iCurrNode($contextNode->getFirstChild());

	#check if this is a text node containing the context
	if($self->_iCurrNode->getNodeType() != XML::DOM::TEXT_NODE())
		{
		$self->_iLog->LogDie("A <p style=\"context\"> tag must start with the context \nCurrently:- ".$self->_iCurrNode->toString()."\n");
		}

	#remeber the context
	$context=$self->_iCurrNode->toString();

	#move on to the next node
	$self->_iCurrNode($self->_iCurrNode->getNextSibling);

	#check if there is anything following
	if($self->_iCurrNode)
		{
		# check if being followed by an element
		if($self->_iCurrNode->getNodeType() != XML::DOM::ELEMENT_NODE())
			{
			$self->_iLog->LogDie("A context can only be followed by a context comment \nCurrently:- ".$self->_iCurrNode->toString()."\n");
			}

		# check that the element is a p and context comment
		my $tagName = $self->_iCurrNode->getTagName();
		#get the style of the paragraph
		my $style =$self->_iCurrNode->getAttribute("style");

		if(($tagName ne "cs") || ($style ne "context comment"))
			{
			$self->_iLog->LogDie("A context can only be followed by a context comment \nCurrently:- ".$self->_iCurrNode->toString()."\n");
			}

		#check that the context format does not contain any formatting
		if(!$self->_IsTextable($self->_iCurrNode))
			{
			$self->_iLog->LogDie("<cs style\"context comment\" tag must not contain any formatting\nCurrently:- ".$self->_iCurrNode->toString()."\n");
			}

		# extract the comment
		$comment=$self->_ToText($self->_iCurrNode);
		}

	#add the context
	$self->_AddContext($context,$comment);

	#move on to the next sibling to this context
	$self->_iCurrNode($contextNode->getNextSibling());
	}

################################################################################
#
# Function _ProcIndexNode
#
# Function processes this index
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _ProcIndexNode
	{
	my $self=shift;

	my $index="";

	#remember this index node
	my $indexNode = $self->_iCurrNode;
	#process all the nodes of this paragraph
	$self->_iCurrNode($indexNode->getFirstChild());

	# add the index node to the Asptml
	$self->_AddTag("index");

	#loop through all the nodes in the index
	while($self->_iCurrNode)
		{
		#check if this is just a text node
		if($self->_iCurrNode->getNodeType() == XML::DOM::TEXT_NODE())
			{
			#handle the text node
			$self->_CopyNode();
			next;
			}

		#check if this is just an entity
		if($self->_iCurrNode->getNodeType() == XML::DOM::ENTITY_REFERENCE_NODE())
			{
			#handle the entity node
			$self->_CopyNode();
			next;
			}

		#check if this is an element node
		if($self->_iCurrNode->getNodeType() == XML::DOM::ELEMENT_NODE())
			{
			# get the tag name
			my $tagName = $self->_iCurrNode->getTagName();
			#get the style of the tag
			my $style = $self->_iCurrNode->getAttribute("style");

			#check for character style manual formatting
			if($tagName eq "cs")
				{
				#process the manual element
				$self->_ProcManualFormatNodes();
				next;
				}
			#check for other manual formating
			if(($tagName eq "b")
			   || ($tagName eq "i")
			   || ($tagName eq "sup")
			   || ($tagName eq "sub"))
				{
				#process the manual element
				$self->_ProcManualFormatNodes();
				next;
				}
			}
		$self->_iLog->LogDie("<p [style=\"index\"]> tags may only contain <cs style=\"...\"> tags, <b>, <i>, <sup> and <sub>\nCurrently:- ".$self->_iCurrNode->toString()."\n");
		}

	# pop the index node
	$self->_iStack->Pop();

	#move on to the next sibling to this index node
	$self->_iCurrNode($indexNode->getNextSibling());
	}			

################################################################################
#
# Function _ProcSynonymsNode
#
# Function processes the synonyms
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _ProcSynonymsNode
	{
	my $self=shift;

	my $synonym="";

	#remember this synonym node
	my $synonymNode = $self->_iCurrNode;
	#process all the nodes of this paragraph
	$self->_iCurrNode($synonymNode->getFirstChild());

	#check if this is a text node containing the sysnonyms
	if($self->_iCurrNode->getNodeType() != XML::DOM::TEXT_NODE())
		{
		$self->_iLog->LogDie("A <p style=\"synonym\"> tag must start with the synonyms \nCurrently:- ".$self->_iCurrNode->toString()."\n");
		}

	#add the synonyms
	$self->_AddSynonyms($self->_iCurrNode->toString());

	#move on to the next sibling to this synonym
	$self->_iCurrNode($synonymNode->getNextSibling());
	}

################################################################################
#
# Function _ProcTopicTitleNode
#
# Function processes the section 2 heading which gives the topic title
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _ProcTopicTitleNode
	{
	my $self=shift;

	#make a deep copy of the node
	my $node = $self->_iCurrNode->cloneNode(1);

	$node->setOwnerDocument($self->_iAsptmlDom);

	# change the name of the element from heading to topictitle
	$node->setTagName("topictitle");

	#add this to the current Asptml element
	$self->_iStack->Top()->appendChild($node);

	#move on to the next sibling
	$self->_iCurrNode($self->_iCurrNode->getNextSibling());
	}
################################################################################
#
# Function ProcListNodes
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
################################################################################
sub _ProcListNodes
	{
	my $self=shift;

	#remember this list node
	my $listNode = $self->_iCurrNode;

	#process all the list items list continue nodes of this list
	$self->_iCurrNode($listNode->getFirstChild());

	#add a list node
	$self->_AddList($listNode->getAttribute("style"));

	#loop though all the list item nodes
	while($self->_iCurrNode)
		{

		#check if this is just a text node
		if($self->_iCurrNode->getNodeType() == XML::DOM::TEXT_NODE())
			{
			#handle the text node
			$self->_CopyNode();
			next;
			}

		#check if this is an element node
		if($self->_iCurrNode->getNodeType() == XML::DOM::ELEMENT_NODE())
			{
			my $tagName = $self->_iCurrNode->getTagName();

			#handle a list
			if($tagName eq "list")
				{
				#process the list item
				$self->_ProcListNodes();
				next;
				}

			#handle a listItem
			if($tagName eq "listitem")
				{
				#process the list item
				$self->_ProcListItemNode();
				next;
				}

			# check for a paragraph
			if($tagName eq "p")
				{
				#process the paragraph
				$self->_ProcParagraphNode();
				next;
				}
			}
			#otherwise
			$self->_iLog->LogDie("<list> tags may only contain <listitem>  and <p> tags.\nCurrently:- ".$self->_iCurrNode->toString()."\n");				
		}

	#pop the list
	$self->_iStack->Pop();

	# move on to the next sibling
	$self->_iCurrNode($listNode->getNextSibling());

	return;
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

	# add a list item node to the asptml
	$self->_AddListItem($self->_iCurrNode->getAttribute("value"));

	# process the paragraph
	$self->_ProcParagraphNodes();

	#pop the list item off the stack
	$self->_iStack->Pop();
	}

################################################################################
#
# Function _ProcDefListNodes
#
# Function processes all the deflist nodes
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _ProcDefListNodes
	{
	my $self=shift;

	#remember this deflist node
	my $defListNode = $self->_iCurrNode;
	#process all the terms and the definitions of this deflist
	$self->_iCurrNode($defListNode->getFirstChild());

	#add a Deflist node
	$self->_AddTag("deflist");

	#loop though all the list item nodes
	while($self->_iCurrNode)
		{
		#check if this is just a text node
		if($self->_iCurrNode->getNodeType() == XML::DOM::TEXT_NODE())
			{
			#handle the text node
			$self->_CopyNode();
			next;
			}

		#check if this is an element node
		if($self->_iCurrNode->getNodeType() == XML::DOM::ELEMENT_NODE())
			{
			my $tagName = $self->_iCurrNode->getTagName();
			my $style = $self->_iCurrNode->getAttribute("style");
			#handle a list
			if($tagName eq "term")
				{
				#process the term
				$self->_ProcTermNode();
				next;
				}

			#handle a a comment
			if(($tagName eq "p") && ($style eq "comment"))
				{
				#process the list item
				$self->_ProcCommentNode();
				next;
				}

			# check for a definition without a term
			if($tagName eq "definition")
				{
				$self->_iLog->LogDie("<definitions> tags must be preceeded by a <term> tag.\nCurrently:- ".$self->_iCurrNode->toString()."\n");			
				}
			}
		#otherwise
		$self->_iLog->LogDie("<deflist> tags may only contain <term>, <definition>	and <p style=\"comment\"> tags.\nCurrently:- ".$self->_iCurrNode->toString()."\n");			
		}

	#pop the deflist
	$self->_iStack->Pop();

	# move on to the next sibling
	$self->_iCurrNode($defListNode->getNextSibling());

	return;
	}

################################################################################
#
# Function _ProcTermNode
#
# Function processes all the term nodes and its following defintion
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _ProcTermNode
	{
	my $self=shift;

	#remember this term node
	my $termNode = $self->_iCurrNode;

	#add a term node
	$self->_AddTag("term");

	#process the content of the term
	$self->_ProcParagraphNodes();

	#pop the term tag
	$self->_iStack->Pop();

	#go on to the next term
	$self->_iCurrNode($termNode->getNextSibling());

	my $seenDefinition = 0;

	#loop though all comments text nodes and one definition node
	while($self->_iCurrNode)
		{
		#check if this is just a text node
		if($self->_iCurrNode->getNodeType() == XML::DOM::TEXT_NODE())
			{
			#handle the text node
			$self->_CopyNode();
			next;
			}

		#check if this is an element node
		if($self->_iCurrNode->getNodeType() == XML::DOM::ELEMENT_NODE())
			{
			my $tagName = $self->_iCurrNode->getTagName();
			my $style = $self->_iCurrNode->getAttribute("style");
			#handle a list
			if($tagName eq "definition")
				{
				#process the term
				$self->_ProcDefinitionNode();
				$seenDefinition=1;
				last;
				}

			#handle a a comment
			if(($tagName eq "p") && ($style eq "comment"))
				{
				#process the list item
				$self->_ProcCommentNode();
				next;
				}
			}
		#otherwise
		last;
		}

	#check if we saw a definition for this term
	if(!$seenDefinition)
		{
		$self->_iLog->LogDie("<term> tags must be followed by a <definition> tag.\nCurrently:- ".$termNode->toString()."\n");			
		}
	return;
	}

################################################################################
#
# Function _ProcDefinitionNode
#
# Function processes the definition node
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _ProcDefinitionNode
	{
	my $self=shift;

	#remember this Definition node
	my $defNode = $self->_iCurrNode;

	#add a Definition node
	$self->_AddTag("definition");

	#process the content of the defintion
	$self->_ProcParagraphNodes();

	$self->_iStack->Pop();

	#go on to the next term
	$self->_iCurrNode($defNode->getNextSibling());
	}

################################################################################
#
# Function _ProcCommentNode
#
# Function processes the comment node
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _ProcCommentNode
	{
	my $self=shift;

	#move on to the next node
	$self->_iCurrNode($self->_iCurrNode->getNextSibling()); 
	}

################################################################################
#
# Function _ProcGraphiclinkNode
#
# Function processes the graphic link node
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _ProcGraphicLinkNode
	{
	my $self=shift;

	my $filename="";

	#check that the graphic link does not contain formatting
	if(!$self->_IsPure($self->_iCurrNode))
		{
		$self->_iLog->LogDie("<cs style=\"Graphic link\"> must not contain any manual formatting\nCurrently:- ".$self->_iCurrNode->toString()."\n");
		}

	my $graphicLink = $self->_iCurrNode->getFirstChild()->toString();

	#extract the archive and the picture file from the graphic link text
	$graphicLink =~ /archive *= *(.+)name *=/i;
	my $archive = $self->_GetArchive($graphicLink);
	my $name = $self->_GetName($graphicLink);
	#make the fileName 
	if ( ($archive !~ /[\\\/]$/) && ($archive ne "") )
		{
		$archive = $archive."\\";
		}
	my $fileName=$archive.$name;

	#check that the mbm graphic file exists and is not zero size
	if(! -s $self->_iGraphicsDir.$fileName.".mbm")
		{
		$self->_iLog->LogDie("Sorry ".$self->_iGraphicsDir."$fileName does not exist. Please check that the project file gives the right graphics directory and that the graphic link has been specified correctly.");
		}

	#add the graphic tag
	$self->_AddGraphic($fileName);

	#move on to the next sibling to graphic
	$self->_iCurrNode($self->_iCurrNode->getNextSibling());
	}

################################################################################
#
# Function _GetArchive
#
# Function extracts the graphic archive from a graphic link string
#
# Function takes: the graphic link string to extract from
#
# Function Returns: the extracted archive
#
# Function Uses:
#
# Notes:
################################################################################
sub _GetArchive($)
	{
	my $self = shift;
	my($aGraphicLink)=@_;
	my $archive="";

	# check if the graphic linkk follows the archive name pattern
	if($aGraphicLink =~ /archive *= *(.+)name *=/i)
		{
		$archive = $1;
		}
	else
		{
		# graphic link follows the name archive format
		$aGraphicLink =~ /archive *= *(.+)$/i;
		$archive = $1;
		}
	#trim off any trailing spaces
	$archive =~ s/ *$//;
	$archive =~ s/^\\//;
	$archive =~ s/\\$//;

	return $archive;
	}

################################################################################
#
# Function _GetName
#
# Function extracts the graphic name from a graphic link string
#
# Function takes: the graphic link string to extract from
#
# Function Returns: the extracted name
#
# Function Uses:
#
# Notes:
#################################################################################
sub _GetName($)
	{
	my $self = shift;
	my($aGraphicLink)=@_;
	my $name="";

	# check if the graphic linkk follows the name archive pattern
	if($aGraphicLink =~ /name *= *(.+)archive *=/i)
		{
		$name = $1;
		}
	else
		{
		# graphic link follows the archive name format
		$aGraphicLink =~ /name *= *(.+)$/i;
		$name = $1;
		}
	#trim off any trailing spaces
	$name =~ s/ *$//;

	return $name;
	}

################################################################################
#
# Function _ProcManualFormatNodes
#
# Function processes the manually formated nodes
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _ProcManualFormatNodes
	{
	my $self=shift;

	#remember this format node
	my $formatNode = $self->_iCurrNode;
	#process all the nodes of this format node
	$self->_iCurrNode($formatNode->getFirstChild());

	#add the format tag to asptml
	$self->_AddFormatting($formatNode->getTagName(),$formatNode->getAttribute("style"));

	#loop though all the formated nodes
	while($self->_iCurrNode)
		{
		#check if this is just an entity
		if($self->_iCurrNode->getNodeType() == XML::DOM::ENTITY_REFERENCE_NODE())
			{
			#handle the entity node
			$self->_CopyNode();
			next;
			}

		#check if this is just a text node
		if($self->_iCurrNode->getNodeType() == XML::DOM::TEXT_NODE())
			{
			#handle the text node
			$self->_CopyNode();
			next;
			}

		#check if this is an element node
		if($self->_iCurrNode->getNodeType() == XML::DOM::ELEMENT_NODE())
			{
			# get the tag name
			my $tagName = $self->_iCurrNode->getTagName();
			my $style = $self->_iCurrNode->getAttribute("style");

			# simple manual formatting
			if(($tagName eq "b")
			   || ($tagName eq "i")
			   || ($tagName eq "sup")
			   || ($tagName eq "sub"))
				{
				#process the manual element
				$self->_ProcManualFormatNodes();
				next;
				}
			#otherwise
			$self->_iLog->LogDie("Only <b>, <i>, <sup> and <sub> manual formatting is allowed\nCurrently:- ".$self->iCurrNode->toString."\n");
			}
		}
	#pop the format node from the dom
	$self->_iStack->Pop();

	#move on to the next sibling to this paragraph node
	$self->_iCurrNode($formatNode->getNextSibling());
	}


################################################################################
#
# Function _AddTopic
#
# Function Adds a topic layer to the Csptml
#
# Function takes: the category for this topic
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _AddTopic($)
	{
	my $self=shift;
	my($aCategory)=@_;

	#add the topic tag
	$self->_AddTag("topic");
	$self->_AddCategory($aCategory);
	}

################################################################################
#
# Function _AddCategory
#
# Function Adds Category to the 
#
# Function takes: string to add as the category
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _AddCategory($)
	{
	my $self=shift;
	my($aCategory)=@_;

	#create a UID tag
	$self->_AddTag("category");

	# create a text node
	my $text = $self->_iAsptmlDom->createTextNode($aCategory);
	#add the text to the document
	$self->_iStack->Top()->appendChild($text);

	#pop the category context
	$self->_iStack->Pop();
	}


################################################################################
#
# Function _AddUID
#
# Function Adds a UID tag to the asptml
#
# Function takes: the uid to add to the asptml
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _AddUID($)
	{
	my $self=shift;
	my($aUID)=@_;

	#create a UID tag
	$self->_AddTag("uid");
	$self->_iStack->Top()->setAttribute("value",$aUID);
	
	#pop the uid context
	$self->_iStack->Pop();
	}

################################################################################
#
# Function _AddParagraph
#
# Function Adds a paragraph to the Asptml
#
# Function takes: the style for this paragraph
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _AddParagraph($)
	{
	my $self=shift;
	my($aStyle)=@_;

	#create a p tag
	$self->_AddTag("p");

	#check if there is a style for this paragraph
	if($aStyle)
		{
		$self->_iStack->Top()->setAttribute("style",$aStyle);
		}
	}

################################################################################
#
# Function _AddContext
#
# Function Adds a Context to the Asptml
#
# Function takes: the context to add and the context comment
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _AddContext($$)
	{
	my $self=shift;
	my($aContextUID,$aComment)=@_;

	#creat a context tag
	$self->_AddTag("context");

	# add the context uid attribute
	$self->_iStack->Top()->setAttribute("contextUID",$self->_GenerateContextUID($aContextUID));
	
	#check if there is a comment for this context
	if($aComment)
		{
		$self->_iStack->Top()->setAttribute("comment",$aComment);
		}

	#pop the context 
	$self->_iStack->Pop();
	}

################################################################################
#
# Function _GenerateContextUID
#
# Function generates a context UID from a string
#
# Function takes: string to generate the string from
#
# Function Returns: the generated context UID
#
# Function Uses:
#
# Notes:
################################################################################
sub _GenerateContextUID($)
	{
	my $self=shift;
	my($aContext)=@_;
	my($contextUID)=$aContext;

	#replace returns with spaces
	$contextUID =~ s/\n/ /g;

	#remove all leading and trailing spaces
	$contextUID =~ s/^ //g;
	$contextUID =~ s/ $//g;

	#keep the first 30 characters
	$contextUID=substr($contextUID,0,30);

	#remove all leading and trailing spaces
	$contextUID =~ s/^ //g;
	$contextUID =~ s/ $//g;

	#replace all spaces with _
	$contextUID =~ s/ /_/g;

	return($contextUID);
	}

################################################################################
#
# Function _AddIndex
#
# Function Adds an Index to the Asptml
#
# Function takes: the Index to add
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _AddIndex($)
	{
	my $self=shift;
	my($aIndexUID)=@_;

	#create an index tag
	$self->_AddTag("index");

	#add the index uid tag
	$self->_iStack->Top()->setAttribute("indexUID",$aIndexUID);

	#pop the index context
	$self->_iStack->Pop();
	}

################################################################################
#
# Function _AddSynonym
#
# Function Adds Synonyms to the Asptml
#
# Function takes: the synonym string to add
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _AddSynonyms($)
	{
	my $self=shift;
	my($aSynonyms)=@_;

	#create an index tag
	$self->_AddTag("synonyms");

	# create a text node
	my $text = $self->_iAsptmlDom->createTextNode($aSynonyms);
	#add the text to the document
	$self->_iStack->Top()->appendChild($text);

	#pop the synonym context
	$self->_iStack->Pop();
	}

################################################################################
#
# Function _AddGraphic
#
# Function Adds an graphic to the Asptml
#
# Function takes: the filename of the graphic to add
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _AddGraphic($)
	{
	my $self=shift;
	my($aFileName)=@_;

	#create a graphic tag
	$self->_AddTag("graphic");
	
	# add the filename attributes
	$self->_iStack->Top()->setAttribute("filename",$aFileName);

	#pop the graphic
	$self->_iStack->Pop();
	}

################################################################################
#
# Function _AddFormatting
#
# Function Adds a a formatting node to the asptml
#
# Function takes: the tag name of the formatting to add and the style (if any)
#of the formatting
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _AddFormatting($$)
	{
	my $self=shift;
	my($aTagName,$aStyle)=@_;

	#create the required formatting tag
	$self->_AddTag($aTagName);

	#check if there is a style
	if($aStyle ne "")
		{
		$self->_iStack->Top()->setAttribute("style",$aStyle);
		}
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
################################################################################
sub _AddList($)
	{
	my $self=shift;
	my($aStyle)=@_;

	#create a list tag
	$self->_AddTag("list");
   
	#add the style
	$self->_iStack->Top()->setAttribute("style",$aStyle);
	}

################################################################################
#
# Function _AddListItem
#
# Function Adds a list item node
#
# Function takes: The value of the list item if any
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _AddListItem($)
	{
	my $self=shift;

	my($aValue)=@_;

	#create a listitem to the document
	$self->_AddTag("listitem");
	
	#if there is a listitem value
	if($aValue ne "")
		{
		$self->_iStack->Top()->setAttribute("value",$aValue);
		}
   }

################################################################################
#
# Function _AddAsptml
#
# Function Adds an Asptml Item to the asptml doc
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _AddAsptml
	{
	my $self=shift;

	#create the asptml tag
	$self->_AddTag("asptml");
	}

################################################################################
#
# Function _AddTag
#
# Function Adds a tag layer to the Asptml
#
# Function takes: the tag name
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _AddTag($)
	{
	my $self=shift;
	my($aTag)=@_;
	#create the required tag
	my $element = $self->_iAsptmlDom->createElement($aTag);
	# add this to the document
	$self->_iStack->Top()->appendChild($element);
	# make this the current context
	$self->_iStack->Push($element);
	}

################################################################################
#
# Function _CopyNode
#
# Function simply copies a node from the input dom to the output dom
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _CopyNode
	{
	my $self=shift;

	#make a deep copy of the node
	my $node = $self->_iCurrNode->cloneNode(1);

	$node->setOwnerDocument($self->_iAsptmlDom);

	#add this to the current Asptml element
	$self->_iStack->Top()->appendChild($node);

	#move on to the next node
	$self->_iCurrNode($self->_iCurrNode->getNextSibling()); 
	}


################################################################################
#
# Function _IsPure
#
# Function checks if the node only contains one child node that is text
#
# Function takes: the node to test
#
# Function Returns: true if the node only has one text node child
#
# Function Uses:
#
# Notes:
################################################################################
sub _IsPure($)
	{
	my $self=shift;
	my($aNode)=@_;
	
	my($result)=0;

	#check the node
	if(($#{$aNode->getChildNodes()}==0) && ($aNode->getFirstChild()->getNodeType() == XML::DOM::TEXT_NODE()))
		{
		$result=1;
		}

	return($result)
	}

################################################################################
#
# Function _IsTextable
#
# Function checks if the node only contains text and standard entities
#
# Function takes: the node to test
#
# Function Returns: true if the node can be converted to ASCII (using _ToText)
#
# Function Uses:
#
# Notes:
################################################################################
sub _IsTextable($)
	{
	my $self=shift;
	my($aNode)=@_;
	
	my($result)=1;

	foreach my $node ($aNode->getChildNodes())
		{
		if ($node->getNodeType() != XML::DOM::TEXT_NODE)
			{
			if ($node->getNodeType() == XML::DOM::ENTITY_REFERENCE_NODE)
		    	{
				my $entity = $node->getEntityName();
				if
				  ( ($entity ne "rdquote")
				  &&($entity ne "ldquote")
				  &&($entity ne "lquote")
				  &&($entity ne "rquote")
				  &&($entity ne "mdash")
				  &&($entity ne "ndash")
				  &&($entity ne "nbhyphen")
				  &&($entity ne "nbspace")
				  &&($entity ne "tab") )
				  	{
					$result = 0;
					}
				}
			else
				{
				$result = 0;
				}
			}
		}

	return($result)
	}

################################################################################
#
# Function _ToText
#
# Function returns an ASCII equivalent of the tag contents, or undef if
#          _IsTextable is not true.
#
# Function takes: the node to evaluate
#
# Function Returns: the ASCII equivalent
#
# Function Uses:
#
# Notes:
################################################################################
sub _ToText($)
	{
	my $self=shift;
	my($aNode)=@_;
	
	my $text="";

	foreach my $node ($aNode->getChildNodes())
		{
		if ($node->getNodeType() == XML::DOM::TEXT_NODE)
			{
			$text = $text.$node->getData();
			}
		elsif ($node->getNodeType() == XML::DOM::ENTITY_REFERENCE_NODE)
		    {
			my $entity = $node->getEntityName();
			if ( ($entity eq "rdquote") || ($entity eq "ldquote") )
				{
				$text = $text.'"';
				}
			elsif ( ($entity eq "lquote") || ($entity eq "rquote") )
				{
				$text = $text."'";
				}
			elsif ($entity eq "mdash")
				{
				$text = $text."---";
				}
			elsif ($entity eq "ndash")
				{
				$text = $text."--";
				}
			elsif ($entity eq "nbhyphen")
				{
				$text = $text."-";
				}
			elsif ($entity eq "nbspace")
				{
				$text = $text." ";
				}
			elsif ($entity eq "tab")
				{
				$text = $text."\t";
				}
			else
				{
				$text = undef;
				last;
				}
			}
		else
			{
			$text = undef;
			last;
			}
		}

	return $text;
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
################################################################################
sub _ValidateDocType
	{
	my $self = shift;
	my($aNode) = @_;

	#check that a doc type is given
	if($aNode)
		{
		#check that the doctype is correct
		if($aNode->getName() ne "csptml")
			{
			$self->_iLog->LogDie($aNode->getName.$self->iCsptmlFile." is not a csptml file");
			}
		}
	else
		{
		$self->_iLog->Log("No DOCTYPE present assuming file is a csptml file\n");
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
################################################################################
sub TEST
	{
	my $self = shift;

	$self->_iLog->Log("#######################");
	$self->_iLog->Log("Test1 store object data");
	
	$self->_iLog->Log("filling up the data");
	$self->_iCsptmlFile("the input csptml file");
	$self->_iAsptmlFile("the output Asptml file");

	$self->_iCategory("the category");
	$self->_iUID("the UID");

	$self->_iLog->Log("Recovering data");

	$self->_iLog->Log("#######################");
	$self->_iLog->Log("Test2 store csptml file into the csptml dom and parse it");

	#clear the category and the iUID
	$self->_iCategory("");
	$self->_iUID("");

	my $parser = new XML::DOM::Parser();
	my $doc = $parser->parse (
"<?xml version=\"1.0\"?>
<!DOCTYPE csptml SYSTEM \"file:///h:/cshlpcmp/dtd/csptml.dtd\">
<?xml:stylesheet href=\"file:///h:/cshlpcmp/xsl/csptml.xsl\" title=\"csptml\" type=\"text/xsl\"?>
<csptml><section level=\"0\"><p style=\"comment\">This is a comment</p>
<section level=\"1\"><heading>jolly good app</heading>
<p style=\"category uid\">0x1234567</p>
<section level=\"2\"><heading>Fantistic epoc app</heading>
<p style=\"synonyms\">App Application thing other</p>
<p style=\"context\">Context1</p>
<p style=\"context\"> Context2 <cs style=\"context comment\">This is a comment</cs></p>
<p style=\"comment\">This is a comment in the middle of the contexts</p>
<p style=\"context\">Context3 Which is very big and has a great number of spaces</p>
<p style=\"context\">Context4 which
is a bit messed up and has <cs style=\"context comment\"> a  context comment</cs></p>
<p style=\"index\">This is index 1</p>
<p style=\"index\">This is a very long index that goes on and on and on so it should with a little bit of luck extend further that the allowed 120 characters index 2</p>
<p style=\"index\">This is index 3</p>
<p style=\"comment\">this is a comment in the middle of the indexes</p>
<p style=\"index\">This is index 4</p>
<p>The Boss Puzzle was popularized <cs style=\"graphic link\">name	 =	  exit archive	   =	  \\pictures\\</cs>in the late 1800s by Samuel Lloyd, an American businessman. It consists of a 4x4 grid of tiles, one of which is missing.</p>
<list style=\"bullet\">
<listitem>This is a list item</listitem>
<listitem>This is another list itme</listitem>
<list style=\"numbered\">
<listitem>This is a list item in a list</listitem>
<listitem>This is another
<cs style=\"graphic link\">name=board archive=pictures</cs>
<cs style=\"graphic link\">name   =    exit archive		=	   \\pictures\\</cs>
<cs style=\"graphic link\">archive	   =	  \\pictures\\ name   =    exit-but</cs>
list item in a list</listitem>
</list>
</list>
<p>This <b>is</b> <b><i><sub><sup>a paragraph</sup></sub></i></b> with an <i>amazing</i>amount <cs style=\"key name\">of formating</cs> in it</p>
<p>This is a definition list</p>
<deflist>
<term>The term</term>
<definition>This is the definition of the term</definition>
<p style=\"comment\">This is the comment in the middle of a definition list</p>
<term>The term</term>
<p style=\"comment\">This is the comment in the middle of a definition list</p>
<definition>This is the definition of the term</definition>
</deflist>
<p style=\"important\">This is an &ldquote;important paragraph</p>
<p style=\"tip\">This is a tip paragraph</p>
<p style=\"note\">This is a note paragraph</p>

</section></section></section>
</csptml>");

	$self->_iCsptmlDom($doc);

	$self->_Parse();
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
################################################################################
sub PRINT
	{
	my $self = shift;
	$self->_iLog->Log("the input csptml file | ". $self->_iCsptmlFile);
	$self->_iLog->Log("the output asptml file | ". $self->_iAsptmlFile);
	$self->_iLog->Log("the category |". $self->_iCategory);
	$self->_iLog->Log("the UID |". $self->_iUID);

	$self->_iLog->Log("The current content of the CSPTMLDOM is ");
	if($self->_iCsptmlDom)
		{
		$self->_iLog->Log("\n". $self->_iCsptmlDom->toString());
		}
	else
		{
		$self->_iLog->Log("EMPTY");
		}

	$self->_iLog->Log("The current content of the ASPTMLDOM is ");
	if($self->_iAsptmlDom)
		{
		$self->_iLog->Log("\n". $self->_iAsptmlDom->toString());
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

