#!perl
################################################################################
#
# module: custfile.pm
#
# module implements the customization file object
#
# Copyright (c) 1997-1999 Symbian Ltd.	All rights reserved
#
# Date Tue Aug 31 11:14:04 1999
#
################################################################################
package CCustFile;

use Carp;
use strict;

use devtools;
use log;
use stack;
use coll;
use charstyle;
use parastyle;

################################################################################
#
# Function New
#
# Function creates a new custfile object
#
# Function takes: the path / filename of the source file the path/ filename
# of the destination file and the uif of the help file from the project
#
# Function Returns: the created object
#
# Function Uses:
#
# Notes:
################################################################################
sub New ($$$)
	{
	my $proto = shift;
	my($aCustFile,$aHelpFileUID, $aGraphicDir) = @_;

	my $class = ref($proto) || $proto;

	my $self  = {};
	bless($self, $class);
	$self->_iLog(New CLog());

	$self->_iCustFile($aCustFile);
	$self->_iHelpFileUID($aHelpFileUID);
	$self->_iGraphicDir($aGraphicDir);
	
	$self->_iCustDom(undef);
	$self->_iCsHlpDom(undef);

	# initialise storage for new styles
	$self->_iParastyles({});
	$self->_iCharstyles({});
	$self->_iBodyStyle(undef);

	# initialise monitors for old styles
	$self->_iImportantStyleSet(undef);
	$self->_iTipStyleSet(undef);
	$self->_iNoteStyleSet(undef);

	$self->_iStack(New CStack());

	# create the storage for the mbmlist
	$self->_iMbmList(New CCollection());

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
################################################################################
sub DESTROY
	{
	my $self = shift;

	$self->_iCustDom->dispose();
	$self->_iCsHlpDom->dispose();
	}

################################################################################
#
# Function _iLog _iCustFile _iHelpFileUID _iGraphicDir _iCustDom
# _iCsHlpDom _iStack _iMbmList _iCurrNode
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
################################################################################
sub _iLog
	{
	my $self = shift;
	if (@_) { $self->{LOG} = shift }
	return $self->{LOG};
	}

sub _iCustFile
	{
	my $self = shift;
	if (@_) { $self->{CUSTFILE} = shift }
	return $self->{CUSTFILE};
	}

sub _iHelpFileUID
	{
	my $self = shift;
	if (@_) { $self->{HELPFILEUID} = shift }
	return $self->{HELPFILEUID};
	}

sub _iGraphicDir
	{
	my $self = shift;
	if (@_) { $self->{GRAPHICDIR} = shift }
	return $self->{GRAPHICDIR};
	}

sub _iMbmList
	{
	my $self = shift;
	if (@_) { $self->{MBMLIST} = shift }
	return $self->{MBMLIST};
	}

sub _iCustDom
	{
	my $self = shift;
	if (@_) { $self->{CUSTDOM} = shift }
	return $self->{CUSTDOM};
	}

sub _iCsHlpDom
	{
	my $self = shift;
	if (@_) { $self->{CSHLPDOM} = shift }
	return $self->{CSHLPDOM};
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

# Hashes for paragraph and character styles
sub _iParastyles
	{
	my $self = shift;
	if (@_) { $self->{PARASTYLES} = shift }
	return $self->{PARASTYLES};
	}

sub _iCharstyles
	{
	my $self = shift;
	if (@_) { $self->{CHARSTYLES} = shift }
	return $self->{CHARSTYLES};
	}

sub _iBodyStyle
	{
	my $self = shift;
	if (@_) { $self->{BODYSTYLE} = shift }
	return $self->{BODYSTYLE};
	}
	
sub _iImportantStyleSet
	{
	my $self = shift;
	if (@_) { $self->{IMPORTANTSTYLESET} = shift }
	return $self->{IMPORTANTSTYLESET};
	}
	
sub _iNoteStyleSet
	{
	my $self = shift;
	if (@_) { $self->{NOTESTYLESET} = shift }
	return $self->{NOTESTYLESET};
	}
	
sub _iTipStyleSet
	{
	my $self = shift;
	if (@_) { $self->{TIPSTYLESET} = shift }
	return $self->{TIPSTYLESET};
	}

################################################################################
#
# Function ToCsHlp
#
# Function converts the Customization file to CsHlp
#
# Function takes: none
#
# Function Returns: the CsHlp DOM
#
# Function Uses:
#
# Notes:
################################################################################
sub ToCsHlp
	{
	my $self = shift;

	# check  customisation file was specified
	if($self->_iCustFile eq "")
		{
		$self->_iLog->LogDie("The project file must specify a customization file.");
		}
	#check if there is a customization file
	elsif(! -e $self->_iCustFile)
		{
		$self->_iLog->LogDie("Sorry: Can not find customization file at ".$self->_iCustFile.".");
		}
	else
		{
		# process the customisation file
		# initilise the Cust dom
		$self->_InitiliseCust;

		$self->_Parse;
		}

	return $self->_iCsHlpDom;
	}

################################################################################
#
# Function _InitiliseCust
#
# Function initilises the Cust dom
#
# Function takes: nothing
#
# Function Returns: nothing
#
# Function Uses:
#
# Notes:
################################################################################
sub _InitiliseCust
	{
	my $self = shift;

	#load the Cust file
	my $parser = new XML::DOM::Parser();

	$self->_iLog->Log("processing" . $self->_iCustFile);

	my $dom = $parser->parsefile($self->_iCustFile);
	#store the Cust dom
	$self->_iCustDom($dom);
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
################################################################################
sub _Parse
	{
	my $self = shift;

	my $dom = $self->_iCustDom;

	#validate the doctype
	$self->_ValidateDocType($dom->getDoctype());

	#get the nodes in the source file
	my $nodes=$dom->getElementsByTagName("cshcust");

	if(!$nodes->item(0))
		{
		$self->_iLog->LogDie("Customization file must contain a cshcust tag");
		}

	#prime the current node
	$self->_iCurrNode($nodes->item(0)->getFirstChild());

	#initilise the CsHlp Dom
	$self->_InitiliseCsHlp();

	$self->_ProcNodes();

	# add the stored  mbmlist
	$self->_AddStoredInfo();

	#pop the cshlp node
	$self->_iStack->Pop();

	#check that the stack has not been currupted
	if($self->_iStack->Top()!=$self->_iCsHlpDom)
		{
		$self->_iLog->LogDie("Corrupted Node stack");
		}

	#pop the doc back off the iNode
	$self->_iStack->Pop();
	}

################################################################################
#
# Function _NormaliseStyles
#
# Function fully specifies any (deprecated) effects, adds app text and key name # styles if not defined. Writes out body tag.
#
# Function takes: nothing
#
# Function Returns: nothing
#
# Function Uses:
#
# Notes: Dies if there's a problem. Must be called when the customization tag
#        is on the top of the stack.
################################################################################
sub _NormaliseStyles()
	{
	my $self = shift;

	my $normalStyle = $self->_iParastyles->{$self->_iBodyStyle()};

	if ($normalStyle == undef)
		{
		$self->_iLog->LogDie("Customization file: Must contain a body style declaration. Use <body style=\"...\"/> to use a parastyle for body text, lists, and any leading text.\n");
		}

	# write out a body style tag
	my $bodyelement = $self->_iCsHlpDom->createElement("body");

	$normalStyle->AddAttributes($bodyelement);
	
	$self->_iStack->Top()->appendChild($bodyelement);

	# normalise effect styles
	if ($self->_iImportantStyleSet)
		{
		$self->_iParastyles->{"important"}->Base($normalStyle);
		}
	if ($self->_iTipStyleSet)
		{
		$self->_iParastyles->{"tip"}->Base($normalStyle);
		}
	if ($self->_iNoteStyleSet)
		{
		$self->_iParastyles->{"note"}->Base($normalStyle);
		}
	
	if (!defined($self->_iCharstyles->{"app text"}))
		{
		$self->_iCharstyles->{"app text"} = New CCharstyle("default app text", undef, "bold", undef, undef);
		}
	if (!defined($self->_iCharstyles->{"key name"}))
		{
		$self->_iCharstyles->{"key name"} = New CCharstyle("default key name", undef, "bold", undef, undef);
		}
	}
################################################################################
#
# Function _InitiliseCsHlp
#
# Function initilises the CsHlp dom
#
# Function takes: nothing
#
# Function Returns: nothing
#
# Function Uses:
#
# Notes:
################################################################################
sub _InitiliseCsHlp
	{
	my $self = shift;

	#create an empty CsHlp dom
	$self->_CreateCsHlpDom();
	}

################################################################################
#
# Function _CreateCsHlpDom
#
# Function creates the CsHlp dom
#
# Function takes: nothing
#
# Function Returns: nothing
#
# Function Uses:
#
# Notes:
################################################################################
sub _CreateCsHlpDom
	{

	my $self = shift;

	#create an empty CsHlp dom
	my $doc = new XML::DOM::Document();
	$doc->setXMLDecl($doc->createXMLDecl("1.0"));
	$doc->setDoctype($doc->createDocumentType("cshlp",$self->_GetDTDUrl()));

	#store the CsHlp dom
	$self->_iCsHlpDom($doc);

	# add a processing instruction for the stylesheet
	my $pi=$doc->createProcessingInstruction("xml:stylesheet","href=\"".$self->_GetXSLUrl()."\" title=\"cshlp\" type=\"text/xsl\"");	

	$self->_iCsHlpDom->appendChild($pi);
	
	#push the CsHlp Dom onto the iNode
	$self->_iStack->Push($self->_iCsHlpDom);

	#add a CsHlp node to the CsHlp dom and push this onto iNode
	$self->_AddCsHlp($self->_iHelpFileUID);
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
################################################################################
sub _GetDTDUrl
	{
	my $self = shift;

	# check that the dtd and the xsl files for this file exists
	my $dtdUrl = $main::params->ParamItem("DTDLoc")->Value()."/cshlp.dtd";

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
################################################################################
sub _GetXSLUrl
	{
	my $self = shift;

	my $xslUrl = $main::params->ParamItem("XSLLoc")->Value()."/cshlp.xsl";
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
# Function _AddStoredInfo
#
# Function adds all the stored info to the cshlp file
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _AddStoredInfo
	{
	my $self=shift;

	# add the mbmlist
	$self->_AddText("\n");
	$self->_AddTag("mbmlist");
	$self->_AddStoredNodes($self->_iMbmList);
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
################################################################################
sub _ProcNodes
	{
	my $self=shift;

	#add a customization tag
	$self->_AddCust();

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
			
			#handle bodystyle
			if($tagName eq "bodystyle")
				{
				#process the bodystyle node
				$self->_ProcBodystyleNode();
				next;
				}
			#handle titlestyle
			if($tagName eq "titlestyle")
				{
				#just copy the style node
				$self->_CopyNode();
				next;
				}
			#handle lists
			if($tagName eq "lists")
				{
				#just copy the list node
				$self->_CopyNode();
				next;
				}
			#handle listbullet1style
			if($tagName eq "listbullet1style")
				{
				#just copy the style node
				$self->_CopyNode();
				next;
				}
			#handle listbullet2style
			if($tagName eq "listbullet2style")
				{
				#just copy the style node
				$self->_CopyNode();
				next;
				}

			#handle tipeffect
			if($tagName eq "tipeffects")
				{
				#process the effect node
				if (defined($self->_iTipStyleSet))
					{ $self->_iLog->LogDie("Customization file: <tipeffects> cannot be defined twice.\n"); }
				
				$self->_ProcEffectNode("tip");
				$self->_iTipStyleSet("tip");
				next;
				}
			#handle noteeffect
			if($tagName eq "noteeffects")
				{
				#process the note effect
				if (defined($self->_iNoteStyleSet))
					{ $self->_iLog->LogDie("Customization file: <noteeffects> cannot be defined twice.\n"); }

				$self->_ProcEffectNode("note");
				$self->_iNoteStyleSet("note");
				next;
				}
			#handle importanteffect
			if($tagName eq "importanteffects")
				{
				#process the effect
				if (defined($self->_iImportantStyleSet))
					{ $self->_iLog->LogDie("Customization file: <importanteffects> cannot be defined twice.\n"); }
					
				$self->_ProcEffectNode("important");
				$self->_iImportantStyleSet("important");
				next;
				}
			#handle parastyle
			if($tagName eq "parastyle")
				{
				#process the parastyle definition
				$self->_ProcParastyleNode();
				next;
				}
			#handle charstyle
			if($tagName eq "charstyle")
				{
				#process the charstyle definition
				$self->_ProcCharstyleNode();
				next;
				}
			#handle body
			if($tagName eq "body")
				{
				#process the body (style=) definition
				$self->_ProcBodyNode();
				next;
				}
			}
		$self->_iLog->LogDie("Customization file can only contain <parastyle>, <charstyle>, <listbullet1style> and <listbullet2style> tags, or <bodystyle>, <titlestyle>, <tipeffects>, <noteeffects> and <importantanteffect> tags\nCurrently:- ".$self->_iCurrNode->toString()."\n");
		}
	
	$self->_NormaliseStyles();

	#pop the customization tag
	$self->_iStack->Pop();
	}

################################################################################
#
# Function _ProcParastyleNode
#
# Function processes all the parastyle nodes
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _ProcParastyleNode
	{
	my $self=shift;

	my $name=lc($self->_ConvertEmptyToNull($self->_iCurrNode()->getAttribute("name")));
	my $font=$self->_ConvertEmptyToNull($self->_iCurrNode()->getAttribute("font"));
	my $style=$self->_ConvertEmptyToNull($self->_iCurrNode()->getAttribute("style"));
	my $size=$self->_ConvertEmptyToNull($self->_iCurrNode()->getAttribute("size"));
	my $color=$self->_ConvertEmptyToNull($self->_iCurrNode()->getAttribute("color"));
	my $justify=$self->_ConvertEmptyToNull($self->_iCurrNode()->getAttribute("justify"));
	my $spacing=$self->_ConvertEmptyToNull($self->_iCurrNode()->getAttribute("spacing"));
	my $before=$self->_ConvertEmptyToNull($self->_iCurrNode()->getAttribute("before"));
	my $after=$self->_ConvertEmptyToNull($self->_iCurrNode()->getAttribute("after"));
	my $left=$self->_ConvertEmptyToNull($self->_iCurrNode()->getAttribute("left"));
	my $right=$self->_ConvertEmptyToNull($self->_iCurrNode()->getAttribute("right"));
	my $image=$self->_ConvertEmptyToNull($self->_iCurrNode()->getAttribute("image"));
	my $mbmID=undef;
	my $text = undef;

	my $copynode = $self->_iCurrNode()->getFirstChild();

	while ($copynode && ($copynode->getNodeType() == XML::DOM::COMMENT_NODE))
		{
		$copynode = $copynode->getNextSibling();
		}

	if ($copynode)
		{
		$text = new XML::DOM::DocumentFragment();
		$text->setOwnerDocument($self->_iCsHlpDom());
		}
	
	while ($copynode)
		{
		my $copiednode = $copynode->cloneNode(1);
		$copiednode->setOwnerDocument($self->_iCsHlpDom());
		$text->appendChild($copiednode);
		do
			{
			$copynode = $copynode->getNextSibling();
			} while ($copynode && ($copynode->getNodeType() == XML::DOM::COMMENT_NODE))
		}

	if ($image ne "")
		{
		my $fileName=$self->_iGraphicDir;
		if ( ($fileName !~ /[\\\/]$/) && ($fileName ne "") )
			{ $fileName = $fileName."\\"; }
		
		$fileName = $fileName.$image;
		$fileName =~ s/\//\\/g;

		$mbmID = $self->_GetGraphicID($fileName);
		}

	if ($name eq "normal")
		{
		$self->_iLog->LogDie("Customization file: A style named 'normal' cannot be defined. Use <body style=\"...\"> to set the style on 'normal' text.\n");
		}
	elsif
	  ( ($name eq "comment")
	  ||($name eq "synonyms")
	  ||($name eq "category uid")
	  ||($name eq "context")
	  ||($name eq "index") )
		{
		$self->_iLog->LogDie("Customization file: A paragraph style named '$name' cannot be defined. Paragraphs of this style are treated specially by the compiler.\n");
		}
	
	if (defined($name))
		{
		if (!defined($self->_iParastyles()->{$name}))
			{
			$self->_iParastyles()->{$name} =
			  New CParastyle($name, $font, $style, $size, $color, $justify, $spacing, $before, $after, $left, $right, $mbmID, $text);
			}
		else
			{
			if (($name eq "important") && (defined($self->_iImportantStyleSet)))
				{ $self->_iLog->LogDie("Customization file: Paragraph style 'important' and tag <importanteffects> cannot both be defined (use style 'important' only).\n"); }
			elsif (($name eq "tip") && (defined($self->_iTipStyleSet)))
				{ $self->_iLog->LogDie("Customization file: Paragraph style 'tip' and tag <tipeffects> cannot both be defined (use style 'tip' only).\n"); }
			elsif (($name eq "note") && (defined($self->_iNoteStyleSet)))
				{ $self->_iLog->LogDie("Customization file: Paragraph style 'note' and tag <noteeffects> cannot both be defined (use style 'note' only).\n"); }
			else
				{ $self->_iLog->LogDie("Customization file: Paragraph style '$name' cannot be defined twice\n"); }
			}
		}
	else
		{
		$self->_iLog->LogDie("Customization file: <parastyle> tag must contain a name attribute ('name=')\n");
		}
	#move on to the next sibling to the parastyle node
	$self->_iCurrNode($self->_iCurrNode->getNextSibling());
	}

################################################################################
#
# Function _ProcCharstyleNode
#
# Function processes all the charstyle nodes
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _ProcCharstyleNode
	{
	my $self=shift;

	my $name=lc($self->_ConvertEmptyToNull($self->_iCurrNode()->getAttribute("name")));
	my $font=$self->_ConvertEmptyToNull($self->_iCurrNode()->getAttribute("font"));
	my $style=$self->_ConvertEmptyToNull($self->_iCurrNode()->getAttribute("style"));
	my $size=$self->_ConvertEmptyToNull($self->_iCurrNode()->getAttribute("size"));
	my $color=$self->_ConvertEmptyToNull($self->_iCurrNode()->getAttribute("color"));

	if
	  ( ($name eq "graphic link")
	  ||($name eq "context comment") )
		{
		$self->_iLog->LogDie("Customization file: A character style named '$name' cannot be defined. Text styled in '$name' is treated specially by the compiler.\n");
		}

	if (defined($name))
		{
		if (!defined($self->_iCharstyles()->{$name}))
			{
			$self->_iCharstyles()->{$name} =
			  New CCharstyle($name, $font, $style, $size, $color);
			}
		else
			{
			$self->_iLog->LogDie("Customization file: Character style '$name' cannot be defined twice");
			}
		}
	else
		{
		$self->_iLog->LogDie("Customization file: <charstyle> tag must contain a name attribute ('name=')");
		}
	#move on to the next sibling to the charstyle node
	$self->_iCurrNode($self->_iCurrNode->getNextSibling());
	}

################################################################################
#
# Function _ProcBodyNode
#
# Function processes the body nodes
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _ProcBodyNode
	{
	my $self=shift;

	my $style=$self->_ConvertEmptyToNull($self->_iCurrNode()->getAttribute("style"));

	if (defined($style))
		{
		if (!defined($self->_iBodyStyle))
			{
			$self->_iBodyStyle($style);
			}
		else
			{
			$self->_iLog->LogDie("Customization file: <body style=\"...\"> is defined twice");
			}
		}
	else
		{
		$self->_iLog->LogDie("Customization file: <body> tag must contain a name attribute ('style=\"...\"')");
		}
	#move on to the next sibling to the body node
	$self->_iCurrNode($self->_iCurrNode->getNextSibling());
	}

################################################################################
#
# Function _ConvertEmptyToNull
#
# Function changes supplied empty strings into undef, and returns the value
#
# Function takes: the supplied parameter
#
# Function Returns: the converted parameter
#
# Function Uses:
#
# Notes:
################################################################################
sub _ConvertEmptyToNull
	{
	my $self = shift;
	my ($arg) = @_;

	if ($arg eq "")
		{ return undef; }
	else
		{ return $arg; }
	}
	
################################################################################
#
# Function _ProcBodystyleNode
#
# Function processes the bodystyle node
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _ProcBodystyleNode
	{
	my $self=shift;

	my $font=$self->_ConvertEmptyToNull($self->_iCurrNode()->getAttribute("fontstyle"));
	my $size=$self->_ConvertEmptyToNull($self->_iCurrNode()->getAttribute("size"));
	
	if (!defined($self->_iParastyles()->{"normal"}))
		{
		# Set up the 'normal' paragraph style
		$self->_iParastyles()->{"normal"} =
		  New CParastyle("bodystyle", $font, "normal", $size, undef, undef, undef, undef, undef, undef, undef, undef, undef);
		  
		if (!defined($self->_iBodyStyle))
			{
			$self->_iBodyStyle("normal");
			}
		else
			{
			$self->_iLog->LogDie("Customization file: Cannot contain both <bodystyle> tags and <body style=\"...\"> tags.\n");
			}
		}
	else
		{
		$self->_iLog->LogDie("Customization file: <bodystyle> cannot be defined twice\n");
		}
	#move on to the next sibling to the effect node
	$self->_iCurrNode($self->_iCurrNode->getNextSibling());
	}

################################################################################
#
# Function _ProcEffectNode
#
# Function processes all the note, tip and important effect nodes
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _ProcEffectNode($)
	{
	my $self=shift;
	my ($stylename) = @_;
	#get the graphic reference if any
	my $archive = $self->_iCurrNode->getAttribute("archive");
	my $name = $self->_iCurrNode->getAttribute("name");
	my $leftindent = $self->_iCurrNode->getAttribute("leftindent");

	my $mbmID = undef;
	
	my $copynode = $self->_iCurrNode()->getFirstChild();
	
	my $text = undef;
	
	while ($copynode && ($copynode->getNodeType() == XML::DOM::COMMENT_NODE))
		{
		$copynode = $copynode->getNextSibling();
		}

	if ($copynode)
		{
		$text = new XML::DOM::DocumentFragment();
		$text->setOwnerDocument($self->_iCsHlpDom());
		}
	
	while ($copynode)
		{
		my $copiednode = $copynode->cloneNode(1);
		$copiednode->setOwnerDocument($self->_iCsHlpDom());
		$text->appendChild($copiednode);
		do
			{
			$copynode = $copynode->getNextSibling();
			} while ($copynode && ($copynode->getNodeType() == XML::DOM::COMMENT_NODE))
		}

	#check if the node has a graphic reference
	if(($archive ne "") || ($name ne ""))
		{
		#create the graphic filename (adding dir separators as needed)
		my $fileName=$self->_iGraphicDir;
		if ( ($fileName !~ /[\\\/]$/) && ($fileName ne "") )
			{ $fileName = $fileName."\\"; }
		$fileName = $fileName.$archive;
		if ( ($fileName !~ /[\\\/]$/) && ($fileName ne "") )
			{ $fileName = $fileName."\\"; }
		$fileName = $fileName.$name;

		$fileName =~ s/\//\\/g;

		#add the graphic tag
		$mbmID = $self->_GetGraphicID($fileName);
		}

	if (!defined($self->_iParastyles->{$stylename}))
		{
		$self->_iParastyles->{$stylename} = New CParastyle($stylename, "serif", "normal", "10", undef, undef, undef, undef, undef, $leftindent, undef, $mbmID, $text); # Rest to be filled in at the end
		}
	else
		{
		$self->_iLog->LogDie("Customization file: Paragraph style '$stylename' and tag <".$stylename."effects> cannot both be defined (use paragraph style '$stylename' only).\n");
		}

	#move on to the next sibling to the effect node
	$self->_iCurrNode($self->_iCurrNode->getNextSibling());
	}

################################################################################
#
# Function _GetGraphicID
#
# Function finds the MbmID for a graphic file. New bitmap files are first
# added to the mbmlist, and 
#
# Function takes: the base filename of the graphic file
#
# Function Returns: The assigned MbmID
#
# Function Uses:
#
# Notes:
################################################################################
sub _GetGraphicID($)
	{
	my $self=shift;

	my($aFileName) = @_;

	# get the epoc filename for the graphic
	my($epocFileName)=$aFileName.".mbm";
		
	#check that the mbm graphic file exists and is not zero size
	if(! -s $epocFileName)
		{
		$self->_iLog->LogDie("Sorry $epocFileName does not exist (or is empty). Please check that the project file gives the right graphics directory and that the graphic link has been specified correctly in the customization file.");
		}

	# convert the mbm file to jpg for html proofing
	my $mbmConv = New CConvMbm($aFileName.".mbm");
	$mbmConv->Convert();

	#check if this mbm has already been stored
	if(!$self->_iMbmList->Exists($epocFileName))
		{
		#create a new graphic node
		my $graphicNode = $self->_CreateGraphicNode($aFileName);
		
		#store this mbm graphic
		$self->_iMbmList->AddItem($epocFileName,$graphicNode);
		# get the id that this was stored under
		my $mbmID = $self->_iMbmList->Index($epocFileName);
		
		# add this mbmID to the stored node
		$self->_iMbmList->Data($epocFileName)->setAttribute("mbmID",$mbmID);
		}

	#return the mbmId for this graphic
	return $self->_iMbmList->Index($epocFileName);
	}

################################################################################
#
# Function _CreateGraphicNode
#
# Function Create a graphic node
#
# Function takes: the base filename of the graphic file
#
# Function Returns: the created graphic node
#
# Function Uses:
#
# Notes:
################################################################################
sub _CreateGraphicNode($)
	{
	my $self=shift;
	my($aGraphicFileName)=@_;

	#create the graphic tag
	my $element = $self->_iCsHlpDom->createElement("graphic");
	$element->setAttribute("epocfilename",$aGraphicFileName.".mbm");
	$element->setAttribute("htmlfilename",$aGraphicFileName.".jpg");

	# return the created graphic node
	return $element;
	}

################################################################################
#
# Function _AddStoredNodes
#
# Function Adds the contents of a stored table to the CsHlp Dom
#
# Function takes: the table to add
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _AddStoredNodes($)
	{
	my $self=shift;
	my($aTable)=@_;

	#loop through all the stored nodes
	for my $key (@{$aTable->KeysOrderByIndex()})
		{
		# add the stored node to the CsHlp dom
		$self->_iStack->Top()->appendChild($aTable->Data($key));
		$self->_AddText("\n");
		}
	}

################################################################################
#
# Function _AddText
#
# Function Adds text to the cs-help file
#
# Function takes: the text to add
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _AddText($)
	{
	my $self=shift;
	my($aText)=@_;

	# create a text node
	my $text = $self->_iCsHlpDom->createTextNode($aText);
	#add the text to the document
	$self->_iStack->Top()->appendChild($text);
	}

################################################################################
#
# Function _AddCsHlp
#
# Function Adds an CsHlp Item to the CsHlp doc
#
# Function takes: The uid of the help file
#
# Function Returns: none
#
# Function Uses:
#
# Notes: This code is duplicated in the Asptmlfl.pm object
#################################################################################
sub _AddCsHlp($)
	{
	my $self=shift;

	my($aHelpFileUID) = @_;

	my $helpFileUID = $aHelpFileUID;

	# Does it have the hex prefix?

	if ($helpFileUID =~ /^ *0x/i)
		{
		# Validate hex
		if ($helpFileUID =~ /^ *0x[0-9A-F]* *$/i)
			{
			# Convert to decimal
			$helpFileUID = oct(lc($helpFileUID));
			}
		else
			{ $self->_iLog->LogDie("Sorry, the project UID is badly formed. \"".$helpFileUID."\" isn't a valid hexadecimal number"); }
		}
	else
		{
		# Validate decimal
		if ($helpFileUID !~ /^ *[0-9]* *$/)
			{
			if ($helpFileUID =~ /^ *[0-9A-F]* *$/i)
				{
				$self->_iLog->LogDie("Sorry, the project UID is badly formed. If it is a hexadecimal number, it should start with '0x'");
				}
			else
				{
				$self->_iLog->LogDie("Sorry, the project UID is badly formed. \"".$helpFileUID."\" should be a decimal number, or a hexadecimal number starting with '0x'");
				}
			}
		}

	#create the asptml tag
	$self->_AddTag("cshlp");
	$self->_iStack->Top()->setAttribute("helpfileUID",$helpFileUID);
	}

################################################################################
#
# Function _AddCust
#
# Function Adds a customization element to the CsHlp doc
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _AddCust
	{
	my $self=shift;

	#create the customization tag
	$self->_AddTag("customization");
	}

################################################################################
#
# Function _AddTag
#
# Function Adds a tag layer to the CsHlp
#
# Function takes: the tag name
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _AddTag($)
	{
	my $self=shift;
	my($aTag)=@_;
	#create the required tag
	my $element = $self->_iCsHlpDom->createElement($aTag);
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
#################################################################################
sub _CopyNode
	{
	my $self=shift;

	#make a deep copy of the node
	my $node = $self->_iCurrNode->cloneNode(1);

	$node->setOwnerDocument($self->_iCsHlpDom);

	#add this to the current CsHlp element
	$self->_iStack->Top()->appendChild($node);

	#move on to the next node
	$self->_iCurrNode($self->_iCurrNode->getNextSibling()); 
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
		if($aNode->getName() ne "cshcust")
				{
				$self->_iLog->LogDie($aNode->getName().$self->_iCsptmlFile." is not a Cs-help customization file");
				}
		}
	else
		{
		$self->_iLog->Log("No DOCTYPE present assuming file is a Cs-Help customization file\n");
		}
	}

################################################################################
#
# Function GetParastyle
#
# Function gets the named paragraph style 
#
# Function takes: The name of the style
#
# Function Returns: The correct CParastyle object
#
# Function Uses: none
#
# Notes: Returns undef if style not found
################################################################################
sub GetParastyle($)
	{
	my $self = shift;
	my ($stylename) = @_;

	if (defined($self->_iParastyles->{lc($stylename)}))
		{
		return $self->_iParastyles->{lc($stylename)};
		}
	else
		{
		return undef;
		}
	}

################################################################################
#
# Function GetCharstyle
#
# Function gets the named paragraph style 
#
# Function takes: The name of the style
#
# Function Returns: The correct CCharstyle object
#
# Function Uses: none
#
# Notes: Returns undef if style not found
################################################################################
sub GetCharstyle($)
	{
	my $self = shift;
	my ($stylename) = @_;

	if (defined($self->_iCharstyles->{lc($stylename)}))
		{
		return $self->_iCharstyles->{lc($stylename)};
		}
	else
		{
		return undef;
		}
	}

################################################################################
#
# Function GetBodystyle
#
# Function gets the normal body style
#
# Function takes: none 
#
# Function Returns: The CParastyle object for the body style
#
# Function Uses: none
#
# Notes: Returns undef if old-style bodystyle is being used
################################################################################
sub GetBodystyle($)
	{
	my $self = shift;

	if (defined($self->_iBodyStyle))
		{
		return $self->_iParastyles->{$self->_iBodyStyle};
		}
	else
		{
		return undef;
		}
	}

################################################################################
#
# Function TEST
#
# Function the test code for the Asptml file object
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
	$self->_iCustFile("the input Cust file");
	$self->_iHelpFileUID("the HelpFileUID");
	$self->_iGraphicDir("the GraphicDir");

	$self->_iLog->Log("Recovering data");

	$self->PRINT();

	$self->_iLog->Log("#######################");
	$self->_iLog->Log("Test2 store cust file into the cust dom and parse it");

	#clear the category and the iUID
	$self->_iHelpFileUID("0x1234567");
	$self->_iGraphicDir("\\cshlpcmp\\frontend\\test\\");

	my $parser = new XML::DOM::Parser;
	my $doc = $parser->parse ("<?xml version=\"1.0\"?>
<!DOCTYPE cshcust SYSTEM \"/cshlpcmp/dtd/CSHcust.dtd\">
<?xml:stylesheet href=\"/cshlpcmp/xsl/cshcust.xsl\" title=\"CS-Help customization\" type=\"text/xsl\"?>
<cshcust>
<bodystyle fontstyle=\"sansserif\" size=\"10\"/>
<titlestyle fontstyle=\"sansserif\" size=\"14\"/>
<listbullet1style bulletchar=\"149\"/>
<listbullet2style bulletchar=\"45\"/>
<tipeffects text=\"Tip:\" bold=\"yes\" leftindent=\"36\"/>
<noteeffects archive=\"pictures\" name=\"exit\" leftindent=\"36\"/>
<importanteffects archive=\"pictures\" name=\"full-but\" text=\"Important:\" bold=\"yes\" leftindent=\"60\"/>
</cshcust>");

	$self->_iCustDom($doc);

	$self->_Parse;
	}

################################################################################
#
# Function PRINT
#
# Function prints out the current contents of the custfile object
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
	$self->_iLog->Log("the input cust file | ". $self->_iCustFile);
	$self->_iLog->Log("the Help file UID |". $self->_iHelpFileUID);
	$self->_iLog->Log("the Graphic Dir |". $self->_iGraphicDir);
	
	$self->_iLog->Log("The current content of the CUSTDOM is ");
	if($self->_iCustDom)
		{
		$self->_iLog->Log("\n". $self->_iCustDom->toString());
		}
	else
		{
		$self->_iLog->Log("EMPTY");
		}

	$self->_iLog->Log("The current content of the CSHLPDOM is ");
	if($self->_iCsHlpDom)
		{
		$self->_iLog->Log("\n". $self->_iCsHlpDom->toString());
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

	$self->_iLog->Log("The current content of the mbmList table is");
	$self->_iMbmList->PRINT();
	
	my $stylename;
	$self->_iLog->Log("The defined paragraph styles are:\n");
	my $styles = $self->_iParastyles();
	foreach $stylename (keys %$styles)
		{
		my $style = $self->_iParastyles->{$stylename};
		$self->_iLog->Log($stylename.":".$style->ToCshlp($self->_iCsHlpDom())->toString()."\n");
		}

	$self->_iLog->Log("The defined character styles are:\n");
	$styles = $self->_iCharstyles();
	foreach $stylename (keys %$styles)
		{
		my $style = $self->_iCharstyles->{$stylename};
		$self->_iLog->Log($stylename.":".$style->ToCshlp($self->_iCsHlpDom())->toString());
		}
	}
1;









