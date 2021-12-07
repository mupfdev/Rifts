#!perl
################################################################################
#
# module: asptmlfl.pm
#
# module implements the asptml file object
#
# Copyright (c) 1997-1999 Symbian Ltd.	All rights reserved
#
# Date Mon Aug 23 10:50:56 1999
#
################################################################################
package CAsptmlFile;

use Carp;
use strict;

use devtools;
use log;
use stack;
use coll;

################################################################################
#
# Function New
#
# Function creates a new asptmlfile object
#
# Function takes: the path / filename of the source file the path/ filename
# of the destination file and the helpfileUID from the project file
#
# Function Returns: the created object
#
# Function Uses:
#
# Notes:
################################################################################
sub New ($$$$)
	{
	my $proto = shift;
	my($aCsHlpFile, $aHelpFileUID, $aCustFile, $aGraphicDir) = @_;

	my $class = ref($proto) || $proto;

	my $self  = {};

	bless($self, $class);

	$self->_iLog(New CLog());
	$self->_iCsHlpFile($aCsHlpFile);
	$self->_iHelpFileUID($aHelpFileUID);
	$self->_iCustFile($aCustFile);
	$self->_iGraphicDir($aGraphicDir);

	$self->_iNextTopicID(1);
	
	$self->_iAsptmlDom(undef);
	$self->_iCsHlpDom(undef);

	$self->_iStack(New CStack());

	#create the collections to store the UIDs, contexts, indexes, indexlinks, 
	#customisation, mbmlist and uids
	$self->_iUid(New CCollection());
	$self->_iContext(New CCollection());
	$self->_iIndex(New CCollection());
	$self->_iIndexLink(New CCollection());

	$self->_iCustomize(New CCollection());
	$self->_iMbmList(New CCollection());

	#initilise the CsHlp Dom
	$self->_InitiliseCsHlp();

	return $self;
	}

################################################################################
#
# Function DESTROY
#
# Function Destructor for the object ensures that the PtmlDom and CptmlDom
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

	$self->_iAsptmlDom->dispose();
	$self->_iCsHlpDom->dispose();
	}

################################################################################
#
# Function _iLog _iAsptmlFile _iCsHlpFile _iHelpFileUID _iNextTopicID _iAsptmlDom
# _iCsHlpDom _iStack _iUID _iContext _iIndex _iIndexLink _iCustomize _iMbmList 
# _iCurrNode _iGraphicDir _iTopicIndexLinks
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

sub _iAsptmlFile
	{
	my $self = shift;
	if (@_) { $self->{ASPTMLFILE} = shift }
	return $self->{ASPTMLFILE};
	}

sub _iCsHlpFile
	{
	my $self = shift;
	if (@_) { $self->{CSHLPFILE} = shift }
	return $self->{CSHLPFILE};
	}

sub _iHelpFileUID
	{
	my $self = shift;
	if (@_) { $self->{HELPFILEUID} = shift }
	return $self->{HELPFILEUID};
	}

sub _iNextTopicID
	{
	my $self = shift;
	if (@_) { $self->{NEXTTOPICID} = shift }
	return $self->{NEXTTOPICID};
	}

sub _iUid
	{
	my $self = shift;
	if (@_) { $self->{UID} = shift }
	return $self->{UID};
	}

sub _iAsptmlUid
	{
	my $self = shift;
	if (@_) { $self->{ASPTMLUID} = shift }
	return $self->{ASPTMLUID};
	}

sub _iContext
	{
	my $self = shift;
	if (@_) { $self->{CONTEXT} = shift }
	return $self->{CONTEXT};
	}

sub _iIndex
	{
	my $self = shift;
	if (@_) { $self->{INDEX} = shift }
	return $self->{INDEX};
	}

sub _iIndexLink
	{
	my $self = shift;
	if (@_) { $self->{INDEXLINK} = shift }
	return $self->{INDEXLINK};
	}

sub _iCustomize
	{
	my $self = shift;
	if (@_) { $self->{CUSTOMIZE} = shift }
	return $self->{CUSTOMIZE};
	}

sub _iMbmList
	{
	my $self = shift;
	if (@_) { $self->{MBMLIST} = shift }
	return $self->{MBMLIST};
	}

sub _iAsptmlDom
	{
	my $self = shift;
	if (@_) { $self->{ASPTMLDOM} = shift }
	return $self->{ASPTMLDOM};
	}

sub _iCsHlpDom
	{
	my $self = shift;
	if (@_) { $self->{CSHLPDOM} = shift }
	return $self->{CSHLPDOM};
	}

sub _iTopicIndexLinks
	{
	my $self = shift;
	if (@_) { $self->{TOPICINDEXLINK} = shift }
	return $self->{TOPICINDEXLINK};
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

sub _iCustFile
	{
	my $self = shift;
	if (@_) { $self->{CUSTFILE} = shift }
	return $self->{CUSTFILE};
	}

sub _iGraphicDir
	{
	my $self = shift;
	if (@_) { $self->{GRAPHICDIR} = shift }
	return $self->{GRAPHICDIR};
	}

################################################################################
#
# Function LoadAsptml
#
# Function loads an Asptml file (and stores it in cshlp format)
#
# Function takes: the asptml filename
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub LoadAsptml($)
	{
	my $self = shift;

	my ($aAsptmlFile) = @_;
	
	$self->_iAsptmlFile($aAsptmlFile);

	# initilise the Asptml dom
	$self->_InitiliseAsptml();

	$self->_Parse();
	}
	
################################################################################
#
# Function ToCsHlp
#
# Function writes out the CsHlp file
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub ToCsHlp
	{
	my $self = shift;

	# add the stored information (customization, mbmlist, contexts, indexlinks and indexes
	$self->_AddStoredInfo();

	#pop the cshlp node
	$self->_iStack->Pop();

	#check that the stack has not been corrupted
	if($self->_iStack->Top()!=$self->_iCsHlpDom)
		{
		$self->_iLog->LogDie("Corrupted Node stack");
		}

	#pop the doc back off the iNode
	$self->_iStack->Pop();

	# set up the compression types for the tags
	# this is needed to cope with the rather floppy
	# xml parser used by cshlpwtr
	XML::DOM::setTagCompression (\&_GetTagCompression);

	#write out the created dom
	$self->_iCsHlpDom->printToFile($self->_iCsHlpFile);
	}

################################################################################
#
# Function _GetTagCompression
#
# Function sets the tag compression level for the customisation tags
#
# Function takes: the tagname and and the element being printed
#
# Function Returns: the tag compression level required
# Style 0 
# <empty/> or <empty attr="val"/>
# Style 1 
# <empty></empty> or <empty attr="val"></empty>
# Style 2 
# <empty /> or <empty attr="val" />
#
# Function Uses:
#
# Notes:
################################################################################
sub _GetTagCompression
	{
	#my $self = shift;
	my ($tag, $elem) = @_;

	my $result = 0;

	#check the tag name 
	if($tag =~ /^(body)$/)
		{
		$result = 1;
		}
	elsif ($tag =~ /^leading$/)
		{
		$result = 1;
		}
	return $result;
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
################################################################################
sub _InitiliseAsptml
	{
	my $self = shift;

	#load the Asptml file
	my $parser = new XML::DOM::Parser();

	$self->_iLog->Log("processing" . $self->_iAsptmlFile);

	my $dom = $parser->parsefile($self->_iAsptmlFile);
	#store the Asptml dom
	$self->_iAsptmlDom($dom);

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

	my $dom = $self->_iAsptmlDom;

	$self->_iAsptmlUid(undef);
	$self->_iTopicIndexLinks([]);
	
	#validate the doctype
	$self->_ValidateDocType($dom->getDoctype());

	#get the nodes in the source file
	my $nodes=$dom->getElementsByTagName("asptml");

	if(!$nodes->item(0))
		{
		$self->_iLog->LogDie("asptml file must contain an <asptml> tag");
		}

	#prime the current node
	$self->_iCurrNode($nodes->item(0)->getFirstChild());

	$self->_ProcNodes();

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
# Notes: The function assumes that a CsHlpDom will have been created by the 
# the custfile class
#################################################################################
sub _InitiliseCsHlp
	{
	my $self = shift;

	#read the current CsHlpDom
	my $dom = $self->_iCustFile()->ToCsHlp();

	#store the CsHlp dom
	$self->_iCsHlpDom($dom);

	#push the CsHlp Dom onto the iNode
	$self->_iStack->Push($self->_iCsHlpDom);

	# make the cshlp node the output layer
	$self->_iStack->Push($dom->getElementsByTagName("cshlp"));

	# grab the customization file from the DOM
	$self->_LoadCustomization();

	# grab any mbmIDs using the the customization file
	$self->_LoadMbmList();
	}

################################################################################
#
# Function _LoadCustomization
#
# Function Loads all the customizations into the customize collection
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _LoadCustomization
	{
	my $self=shift;

	# get all the customization nodes in the CsHlp document
	my $customizationNode = $self->_iCsHlpDom->getElementsByTagName ("customization");

	#check that there is a customization section
	if($customizationNode->item(0))
		{
		# get all the children of the customization node
		my $custNodes = $customizationNode->item(0)->getChildNodes();
		my $numNodes = $custNodes->getLength();

		# loop through all the customisation nodes
		for (my $i = 0; $i < $numNodes; $i++)
			{
			my $custNode = $custNodes->item($i);

			#check if this is just a text node
			if($custNode->getNodeType() == XML::DOM::TEXT_NODE())
				{
				next;
				}
			elsif($custNode->getNodeType() == XML::DOM::COMMENT_NODE)
				{
				next;
				}

			#put it into, into the collection
			$self->_iCustomize->AddItem("",$custNode);
			}
		#remove the customization node from the CsHlp dom
		$self->_iStack->Top()->removeChild($customizationNode->item(0));
		}
	}

################################################################################
#
# Function _LoadMbmList
#
# Function Loads all the mbmlist into the mbmlist collection
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _LoadMbmList
	{
	my $self=shift;

	# get all the mbmlist nodes in the CsHlp document
	my $mbmListNode = $self->_iCsHlpDom->getElementsByTagName ("mbmlist");

	#check that there is a mbmlist section
	if($mbmListNode->item(0))
		{
		# get all the children of the mbmlist node
		my $mbmNodes = $mbmListNode->item(0)->getChildNodes();
		my $numNodes = $mbmNodes->getLength();

		# loop through all the customisation nodes
		for (my $i = 0; $i < $numNodes; $i++)
			{
			my $mbmNode = $mbmNodes->item ($i);

			#check if this is just a text node
			if($mbmNode->getNodeType() == XML::DOM::TEXT_NODE())
				{
				next;
				}

			my $mbmID = $mbmNode->getAttribute("mbmID");
			my $epocFileName = $mbmNode->getAttribute("epocfilename");

			#put it into the collection
			$self->_iMbmList->AddItem($epocFileName,$mbmNode,$mbmID);
			}

		#remove the mbmlist node from the CsHlp dom
		$self->_iStack->Top()->removeChild($mbmListNode->item(0));
		}
	}

################################################################################
#
# Function _AddStoredInfo
#
# Function adds all tha stored info to the cshlp file
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

	#add the stored nodes
	$self->_AddStoredNodes($self->_iUid);
	$self->_AddStoredNodes($self->_iContext);
	$self->_AddStoredNodes($self->_iIndexLink);
	$self->_AddStoredNodes($self->_iIndex);

	# add the customization
	$self->_AddText("\n");
	$self->_AddTag("customization");
	$self->_AddStoredNodes($self->_iCustomize);
	$self->_iStack->Pop();

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
		elsif($self->_iCurrNode->getNodeType() == XML::DOM::COMMENT_NODE)
			{
			$self->_iCurrNode($self->_iCurrNode->getNextSibling()); 
			next;
			}
					
		#check if this is an element node
		if($self->_iCurrNode->getNodeType() == XML::DOM::ELEMENT_NODE())
			{
			my $tagName = $self->_iCurrNode->getTagName();
		
			#handle uid
			if($tagName eq "uid")
				{
				#process the UID node
				$self->_ProcUidNode();
				last;
				}
			}
		$self->_iLog->LogDie("asptml file must start with a <uid> tag\nCurrently:- ".$self->_iCurrNode->toString()."\n");
		}
	#process the topic nodes
	$self->_ProcTopicNodes();

	#convert all graphics to use mbmIDs contained in the mbm list
	$self->_ProcGraphicNodes();
	}

################################################################################
#
# Function _ProcTopicNodes
#
# Function processes all the topic nodes asptml dom
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _ProcTopicNodes
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
		elsif($self->_iCurrNode->getNodeType() == XML::DOM::COMMENT_NODE)
			{
			$self->_iCurrNode($self->_iCurrNode->getNextSibling()); 
			next;
			}

		#check if this is an element node
		if($self->_iCurrNode->getNodeType() == XML::DOM::ELEMENT_NODE())
			{
			my $tagName = $self->_iCurrNode->getTagName();

			#handle topic
			if($tagName eq "topic")
				{
				$self->_ProcTopicNode();
				next;
				}
			}
		$self->_iLog->LogDie("<uid> tag may only be followed by <topic> tags\nCurrently:- ".$self->_iCurrNode->toString()."\n");
		}
	}

################################################################################
#
# Function _ProcTopicNode
#
# Function processes a topic node
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _ProcTopicNode
	{
	my $self=shift;

	$self->_iTopicIndexLinks([]);

	#remember this topic node
	my $topicNode = $self->_iCurrNode;
	#process all the nodes of this topic
	$self->_iCurrNode($topicNode->getFirstChild());

	if (!defined($self->_iAsptmlUid))
		{
		$self->_iLog->LogDie("asptml file must start with a <uid> tag\n");
		}
	#add a topic node to the output
	$self->_AddTopic($self->_iNextTopicID, $self->_iAsptmlUid);

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
		elsif($self->_iCurrNode->getNodeType() == XML::DOM::COMMENT_NODE)
			{
			$self->_iCurrNode($self->_iCurrNode->getNextSibling()); 
			next;
			}

		#check if this is an element node
		if($self->_iCurrNode->getNodeType() == XML::DOM::ELEMENT_NODE())
			{
			my $tagName = $self->_iCurrNode->getTagName();

			#handle the category
			if($tagName eq "category")
				{
				$self->_CopyNode();
				next;
				}

			#handle the topictitle
			if($tagName eq "topictitle")
				{
				$self->_CopyNode();
				next;
				}

			#handle synonyms
			if($tagName eq "synonyms")
				{
				$self->_CopyNode();
				next;
				}

			#handle paragraphs
			if($tagName eq "p")
				{
				$self->_ProcParaNode();
				next;
				}
			#handle Lists
			if($tagName eq "list")
				{
				$self->_ProcTextNode();
				next;
				}

			#handle Definition Lists
			if($tagName eq "deflist")
				{
				$self->_ProcTextNode();
				next;
				}

			#handle context
			if($tagName eq "context")
				{
				$self->_ProcContextNode();
				next;
				}

			#handle index
			if($tagName eq "index")
				{
				$self->_ProcIndexNode();
				next;
				}
			}
		$self->_iLog->LogDie("<topic category=\"...> tag may only contain <topictitle>, <context>, <index>, <p [style=\"...\"]> and <list style=\"...\"> tags\nCurrently:- ".$self->_iCurrNode->toString()."\n");
		}

	#pop the topic node
	$self->_iStack->Pop();

	#move on to the next sibling to this topic
	$self->_iCurrNode($topicNode->getNextSibling());
	}

################################################################################
#
# Function _ProcParaNode
#
# Function processes this <p> element node
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses: CCustFile to get parastyle definitions
#
# Notes:
################################################################################
sub _ProcParaNode
	{
	my $self = shift;
	
	my $style = undef;
	my $stylename = lc($self->_iCurrNode()->getAttribute("style"));

	if ($stylename eq "")
		{
		# Body style
		$style = $self->_iCustFile->GetBodystyle();
		}
	else
		{
		# Not body style
		$style = $self->_iCustFile->GetParastyle($stylename);

		if (!defined($style))
			{
			$self->_iLog->Log("Warning: Paragraph style '$stylename' not defined. Using body style instead.");
			$style = $self->_iCustFile->GetBodystyle();
			}
		}
	
	if (!defined($style))
		{
		$self->_iLog->LogDie("Compiler integrity failed: Customization must have a body style\n");
		}

	# Create the fully styled element
	my $element = $style->ToCshlp($self->_iCsHlpDom);

	# add this to the document
	$self->_iStack->Top()->appendChild($element);
	# make this the current context
	$self->_iStack->Push($element);

	my $paraNode = $self->_iCurrNode();
	
	#process all the cs elements of this paragraph
	$self->_iCurrNode($paraNode->getFirstChild());
	
	while($self->_iCurrNode)
		{
		#check if this is an element node
		if($self->_iCurrNode->getNodeType() == XML::DOM::ELEMENT_NODE())
			{
			my $tagName = $self->_iCurrNode->getTagName();

			#handle the character styling
			if($tagName eq "cs")
				{
				$self->_ProcCsNode();
				next;
				}
			}
		$self->_CopyNode();
		}
		
	#pop the p node
	$self->_iStack->Pop();
	# Move on to the next node
	$self->_iCurrNode($paraNode->getNextSibling());
	}

################################################################################
#
# Function _ProcTextNode
#
# Function processes this text containing node
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _ProcTextNode
	{
	my $self = shift;

	if ($self->_iCurrNode->getNodeType() == XML::DOM::ELEMENT_NODE())
		{
		my $tagName = $self->_iCurrNode->getTagName();
		
		#handle the character styling
		if($tagName eq "cs")
			{
			$self->_ProcCsNode();
			}
		else
			{
			my $outnode = $self->_iCurrNode->cloneNode(0);
			
			$outnode->setOwnerDocument($self->_iCsHlpDom);

			# add this new element to the document
			$self->_iStack->Top()->appendChild($outnode);
			# make this the current context
			$self->_iStack->Push($outnode);

			my $textNode = $self->_iCurrNode();
			$self->_iCurrNode($textNode->getFirstChild());
		
			while($self->_iCurrNode)
				{
				$self->_ProcTextNode();
				}
		
			#pop the text node
			$self->_iStack->Pop();
			# Move on to the next node
			$self->_iCurrNode($textNode->getNextSibling());
			}
		}
	else
		{
		$self->_CopyNode();
		}
	}
	

################################################################################
#
# Function _ProcCsNode
#
# Function processes this <cs> element node
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses: CCustFile to get charstyle definitions
#
# Notes:
################################################################################
sub _ProcCsNode
	{
	my $self = shift;
	
	my $style = undef;
	my $stylename = lc($self->_iCurrNode()->getAttribute("style"));
	my $element;

	if ($stylename eq "")
		{
		$self->_Log->LogDie("A <cs> tag must contain a 'style=' attribute. Currently:-".$self->_iCurrNode()->toString()."\n");
		}
	else
		{
		$style = $self->_iCustFile->GetCharstyle($stylename);

		if (!defined($style))
			{
			$self->_iLog->Log("Warning: Character style '$stylename' not defined. Styling ignored");
			$style = undef;
			$stylename = "";
			}
		}
	
	my $csNode = $self->_iCurrNode();

	if (!defined($style))
		{
		# Style to be ignored; just copy the *contents* of the cs tag
		$self->_iCurrNode($csNode->getFirstChild());
		while($self->_iCurrNode)
			{ $self->_CopyNode(); }
		}
	else
		{
		# Create the fully styled element
		$element = $style->ToCshlp($self->_iCsHlpDom);
		# add this new element to the document
		$self->_iStack->Top()->appendChild($element);
		# make this the current context
		$self->_iStack->Push($element);
		
		# copy the contents of this element
		$self->_iCurrNode($csNode->getFirstChild());
		while($self->_iCurrNode)
			{ $self->_CopyNode(); }
	
		#pop the cs node
		$self->_iStack->Pop();
		}
		
	# Move on to the next node
	$self->_iCurrNode($csNode->getNextSibling());
	}
	
################################################################################
#
# Function _ProcUidNode
#
# Function processes this uid
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _ProcUidNode
	{
	my $self=shift;

	#get the value
	my $value = $self->_iCurrNode->getAttribute("value");

	my $uid = $self->_StringToInt($value);
	
	#remember it
	$self->_iAsptmlUid($uid);

	#check if the uid alreadiy exists
	if(!$self->_iUid->Exists($uid))
		{
		# make a replacement element
		my $element = $self->_iCsHlpDom->createElement("uid");
		$element->setAttribute("value", $uid);

		# add the uid to the uid table
		$self->_iUid->AddItem($uid,$element);
		}

	#move on to the next sibling to this uid
	$self->_iCurrNode($self->_iCurrNode->getNextSibling());
	}

##############################################################################
#
# Function _StringToInt
#
# Function converts a string to an integer, taking care of the hex 0x prefix
#
# Function takes: The string to convert, a string describing what that
#				  string represents (for error reporting)
#
# Function Returns: An integer
#
# Function Uses:
#
# Notes:
#
##############################################################################

sub _StringToInt($$)
	{
	my $self = shift;
	my ($aUid, $aDesc) = @_;
	my $value;

	# Does it have the hex prefix?

	if ($aUid =~ /^ *0x/i)
		{
		# Validate hex
		if ($aUid =~ /^ *0x[0-9A-F]* *$/i)
			{
			$value = oct(lc($aUid));
			}
		else
			{
			$self->_iLog->LogDie("Sorry, ".$aDesc." is badly formed. \"".$aUid."\" isn't a valid hexidecimal number");
			}
		}
	else
		{
		# Validate decimal
		if ($aUid =~ /^ *[0-9]* *$/)
			{
			$value = $aUid;
			}
		else
			{
			if ($aUid =~ /^ *[0-9A-F]* *$/i)
				{
				$self->_iLog->LogDie("Sorry, ".$aDesc." is badly formed. If it is a hexadecimal number, it should start with '0x'");
				}
			else
				{
				$self->_iLog->LogDie("Sorry, ".$aDesc." is badly formed. \"".$aUid."\" should be a decimal number, or a hexadecimal number starting with '0x'");
				}
			}
		}
		
	return $value;
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
#################################################################################
sub _ProcContextNode
	{
	my $self=shift;

	#get the contextUID
	my $contextUID = $self->_iCurrNode->getAttribute("contextUID");

	#check if the context alreadiy exists
	if($self->_iContext->Exists($contextUID))
				{
				$self->_iLog->LogDie("Context has already been assigned to a topic \nCurrently:- ".$self->_iCurrNode->toString()."\n");
				}

	#copy the context node
	my $node=$self->_iCurrNode->cloneNode(1);
	$node->setOwnerDocument($self->_iCsHlpDom);

	# add the topicID of the containing topic to the context node
	$node->setAttribute("topicID",$self->_iStack->Top()->getAttribute("topicID"));

	# add the context to the context table
	$self->_iContext->AddItem($contextUID,$node);

	#move on to the next sibling to this context
	$self->_iCurrNode($self->_iCurrNode->getNextSibling());
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
# Notes: The structure of the function is a bit forced when it's a new index
# we wish to add it to the index store. which assigns a generated indexID.
# but we also wish to add the indexID to the stored index node to simplify
# writing out the indexes after the asptml file has been processed. So we add it
# then retrive the indexID, retrive the stored node and modify it. We then
# retrive the indexID again so that we can create a indexlink element
#################################################################################
sub _ProcIndexNode
	{
	my $self=shift;

	#get the indexUID
	my $indexUID=$self->_ChildrenToString($self->_iCurrNode);

	# check if the indexUID exits
	if(!$self->_iIndex->Exists($indexUID))
				{
				#copy the index node
				my $node=$self->_iCurrNode->cloneNode(1);
				$node->setOwnerDocument($self->_iCsHlpDom);

				# add the indexUID
				$self->_iIndex->AddItem($indexUID,$node);
				
				#now get the indexID that the node was stored with
				my $indexID = $self->_iIndex->Index($indexUID);

				# add this to the stored node as the indexID
				$self->_iIndex->Data($indexUID)->setAttribute("indexID",$indexID);
				}

	#get the indexID of the existing index
	my $indexID = $self->_iIndex->Index($indexUID);

	# add a index link for this topic
	my $topicId = $self->_iStack->Top()->getAttribute("topicID");
	my $categoryUID = $self->_iStack->Top()->getAttribute("categoryUID");

	# make of copy of the topictitle of the topic containing this index
	my $topicTitles = $self->_iStack->Top()->getElementsByTagName("topictitle");
	my $topicTitle = $topicTitles->item(0);

	my $repeated = 0;
	my $indexLinks = $self->_iTopicIndexLinks();
	
	foreach my $index (@$indexLinks)
		{
		if ($index == $indexID)
			{
			$repeated = 1;
			}
		}

	if ($repeated == 1)
		{
		$self->_iLog->Log("Warning: Index '$indexUID' repeated in topic\n");
		}
	else
		{
		$indexLinks->[scalar(@$indexLinks)] = $indexID;
		$self->_AddIndexLink($self->_iStack->Top()->getAttribute("topicID"),
							$indexID, $categoryUID, $topicTitle);
		}
	
	#move on to the next sibling to this node
	$self->_iCurrNode($self->_iCurrNode->getNextSibling());
	}

################################################################################
#
# Function _ProcGraphicNodes
#
# Function processes all the graphic nodes in the asptml dom. new bitmap files
# are added to the mbmlist and the graphic tag is altered to contain the
# coresponding mbmID
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes: The structure of the function is a bit forced when it's a new graphic
# we wish to add it to the mbmlist. which assigns a generated mbmID.
# but we also wish to add the mbmID to the stored graphic node to simplify
# writing out the mbmlist after the asptml file has been processed. So we add
# the node then retrive the mbmID retrive the stored node and modify it.
# Then we retrive the mbmID again so that we can add to the graphic tag within
# the topic. The graphic tag within the document is changed to a graphiclink tag
#################################################################################
sub _ProcGraphicNodes
	{
	my $self=shift;

	# get all the graphic nodes in the CsHlp document
	my $graphicNodes = $self->_iCsHlpDom->getElementsByTagName("graphic");
	my $numNodes = $graphicNodes->getLength();

	# loop through all the graphic nodes
	for (my $i = 0; $i < $numNodes; $i++)
				{
				my $graphicNode = $graphicNodes->item($i);
				#get the epoc filename for the graphic
				my $fileName = $self->_iGraphicDir(). $graphicNode->getAttribute("filename");
				my $epocFileName = $fileName.".mbm";
				my $htmlFileName = $fileName.".jpg";
				
				#check if this mbm has already been stored
				if(!$self->_iMbmList->Exists($epocFileName))
							{
							#make a copy of the graphic node
							my $graphicNodeCopy = $graphicNode->cloneNode(1);
							
							$graphicNodeCopy->removeAttribute("filename");
							$graphicNodeCopy->setAttribute("epocfilename",$epocFileName);
							$graphicNodeCopy->setAttribute("htmlfilename",$htmlFileName);
							
							#store this mbm graphic
							$self->_iMbmList->AddItem($epocFileName,$graphicNodeCopy);
							# get the id that this was stored under
							my $mbmID = $self->_iMbmList->Index($epocFileName);

							# add this mbmID to the stored node
							$self->_iMbmList->Data($epocFileName)->setAttribute("mbmID",$mbmID);
							}

				#get the mbmId for this graphic
				my $mbmID = $self->_iMbmList->Index($epocFileName);

				# convert the mbm file to jpg for html proofing
				my $mbmConv = New CConvMbm($epocFileName);
				$mbmConv->Convert();

				# remove the filename from the graphic node
				$graphicNode->removeAttribute("filename");

				# add the mbmID
				$graphicNode->setAttribute("mbmID",$mbmID);

				#change the tag name to graphiclink
				$graphicNode->setTagName("graphiclink");
				}
	}

################################################################################
#
# Function _AddTopic
#
# Function Adds a topic layer to the CsHlp
#
# Function takes: the topicID and the category for this topic, and the
#				  category UID
#
# Function Returns: none
#
# Function Uses:
#
# Notes:This increments the topicID counter
#################################################################################
sub _AddTopic($$)
	{
	my $self=shift;
	my($aTopicID,$aCatUID)=@_;

	#add the topic tag
	$self->_AddTag("topic");
	$self->_iStack->Top()->setAttribute("topicID",$aTopicID);
	$self->_iStack->Top()->setAttribute("categoryUID",$aCatUID);

	#inc the topic id
	$self->_iNextTopicID($self->_iNextTopicID+1);
	}

################################################################################
#
# Function _AddIndexLink
#
# Function Adds an Indexlink to the CsHlp
#
# Function takes: the Indexlink to add
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _AddIndexLink($$$$)
	{
	my $self=shift;
	my($aTopicID,$aIndexID,$aCategoryUID,$aTopicTitle)=@_;

	#create the indexlink tag
	my $element = $self->_iCsHlpDom->createElement("indexlink");
	$element->setAttribute("topicID",$aTopicID);
	$element->setAttribute("indexID",$aIndexID);
	$element->setAttribute("categoryUID",$aCategoryUID);

	# add the topic title to this element
	# loop through all the nodes in the topic title
	my $nodes = $aTopicTitle->getChildNodes();
	my $numNodes = $nodes->getLength();

	# loop through all the indexlink nodes
	for (my $i = 0; $i < $numNodes; $i++)
		{
		my $node = $nodes->item($i);
		$element->appendChild($node->cloneNode(1));
		}

	# store this link in the index link table
	$self->_iIndexLink->AddItem("",$element);
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

	#loop through all the stored nodes in order of index
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
################################################################################
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
# Function _ChildrenToString
#
# Function makes a string containing all the children of a given node
#
# Function takes: the node to make the string from
# 
# Function Returns: the string created from the children
#
# Function Uses: none
#
# Notes:
#################################################################################
sub _ChildrenToString($)
	{
	my $self=shift;

	my($parent)=@_;

	my $string="";

	# get all the children
	my $nodes = $parent->getChildNodes();
	my $n = $nodes->getLength();

	#loop through all the children
	for (my $i = 0; $i < $n; $i++)
				{
				# add this child to the string
				$string=$string.$nodes->item($i)->expandEntityRefs($nodes->item($i)->toString());
				}
	return $string;
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
				if($aNode->getName ne "asptml")
							{
							$self->_iLog->LogDie($aNode->getName().$self->_iCsptmlFile." is not an asptml file!");
							}
				}
	else
				{
				$self->_iLog->Log("No DOCTYPE present assuming file is an asptml file\n");
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
	$self->_iAsptmlFile("the input Asptml file");

	$self->_iNextTopicID(20);
	$self->_iHelpFileUID("the HelpFileUID");

	$self->_iLog->Log("Recovering data");

	$self->PRINT;

	$self->_iLog->Log("#######################");
	$self->_iLog->Log("Test2 store asptml file into the asptml dom and parse it");

	#clear the category and the iUID
	$self->_iNextTopicID(1);
	$self->_iHelpFileUID("0x1234567");

	my $parser = new XML::DOM::Parser();
	my $doc = $parser->parse (
"<?xml version=\"1.0\"?>
<!DOCTYPE asptml SYSTEM \"file:///h:/cshlpcmp/dtd/asptml.dtd\">
<?xml:stylesheet href=\"file:///h:/cshlpcmp/xsl/asptml.xsl\" title=\"asptml\" type=\"text/xsl\"?>
<asptml>
<uid>0x01000000</uid>
<topic category=\"Boss Puzzle\"><topictitle>Boss puzzle: quick start</topictitle>
<context contextUID=\"test context1\" comment=\"this is a comment for this context\"/>
<context contextUID=\"test context2\" comment=\"this is another context comment\"/>
<context contextUID=\"test context3\"/>
<index>test this is &amp;amp;the index 1</index>
<index>this is the index 2</index>
<index>test this is the index 3</index>
<synonyms>start begin activate run</synonyms>
<p>The Boss Puzzle was popularized in the late 1800s by Samuel Lloyd, an American businessman. It consists of a 4x4 grid of tiles, one of which is missing.</p>
<p><graphic epocfilename=\"\\cshlpcmp\\fetsrc\\board.mbm\" htmlfilename=\"\\cshlpcmp\\fetsrc\\board.jpg\"/></p>
<p>The tiles are numbered 1-15. In the original form, tiles 14 and 15 were swapped round.</p>
<p>With the Boss Puzzle application you can:</p>
<list style=\"list bullet\"><listitem>move tiles on this board <graphic epocfilename=\"\\cshlpcmp\\fetsrc\\board.mbm\" htmlfilename=\"\\cshlpcmp\\fetsrc\\board.jpg\"/></listitem>
<listitem>pointing with the pointer</listitem>
<listitem>move them using the arrow keys</listitem>
<listitem>deal the game either fully ordered or Boss ordered</listitem>
<listitem>save games as files</listitem>
<listitem>save games as embedded objects</listitem>
<p>Which is a really useful thing to do</p>
</list></topic><topic category=\"Boss Puzzle\"><topictitle>Building the &amp;amp;Boss Puzzle</topictitle>
<p>All instructions in this refer to the full EIKON versions of the Boss Puzzle.  Full instructions for building are contained in the EPOC32 C++ SDK, in the <b>Practical Guide</b>.  For a very quick start, try</p>
<list style=\"list number\"><listitem>cd \\boss\\group\\</listitem>
<listitem>ebld eik7 wins deb</listitem>
</list><p>and then invoke the WINS emulator.  You should see that the Boss Puzzle is available on the Extras bar.</p>
<deflist>
<term>The term</term>
<definition>This is the definition of the term</definition>
<p style=\"comment\">This is the comment in the middle of a definition list</p>
<term>The term</term>
<p style=\"comment\">This is the comment in the middle of a definition list</p>
<definition>This is the definition of the term</definition>
</deflist>
</topic>
</asptml>");

	$self->_iAsptmlDom($doc);

	$self->_Parse();
	}

################################################################################
#
# Function PRINT
#
# Function prints out the current contents of the Asptmlfile object
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
	$self->_iLog->Log("the input Asptml file | ". $self->_iAsptmlFile);
	$self->_iLog->Log("the output CsHlp file | ". $self->_iCsHlpFile);
	$self->_iLog->Log("the NextTopicID |". $self->_iNextTopicID);
	$self->_iLog->Log("the Help file UID |". $self->_iHelpFileUID);

	$self->_iLog->Log("The current content of the ASPTMLDOM is ");
	if($self->_iAsptmlDom)
				{
				$self->_iLog->Log("\n". $self->_iAsptmlDom->toString());
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

				$temp=$self->_iStack->pop();
				}

	$self->_iLog->Log("The current content of the uid table is");
	$self->_iUid->PRINT();

	$self->_iLog->Log("The current content of the context table is");
	$self->_iContext->PRINT();

	$self->_iLog->Log("The current content of the indexLink table is");
	$self->_iIndexLink->PRINT();

	$self->_iLog->Log("The current content of the index table is");
	$self->_iIndex->PRINT();

	$self->_iLog->Log("The current content of the customize table is");
	$self->_iCustomize->PRINT();

	$self->_iLog->Log("The current content of the mbmList table is");
	$self->_iMbmList->PRINT();
	}
1;




