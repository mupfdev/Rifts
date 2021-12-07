#!perl
###############################################################################
#
# module: custfile.pm
#
# module implements perl object CCustomisationFile
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved
#
# Date Wed Dec 15 10:02:46 1999
#
###############################################################################

package CHelpCustomisationFile;

# Standard libraries
use Carp;
use strict;
use log;
use MLtag;
use devtools;
use XML::DOM;

# Constants

# (strings must be lower-case)
my %KStyles =
  ('bodystyle'        => ['fontstyle', 'size'],
   'titlestyle'       => ['fontstyle', 'size'],
   'listbullet1style' => ['bulletchar'],
   'listbullet2style' => ['bulletchar'],
   'tipeffects'       => ['text', 'bold', 'leftindent', 'archive', 'name'],
   'noteeffects'      => ['text', 'bold', 'leftindent', 'archive', 'name'],
   'importanteffects' => ['text', 'bold', 'leftindent', 'archive', 'name']
  );
my %KRequiredAttribs = ( 'listbullet1style' => 'bulletchar',
                         'listbullet2style' => 'bulletchar' );
my %KTagContent = ( 'tipeffects' => 'text',
                    'noteeffects' => 'text',
                    'importanteffects' => 'text' );
my %KContentStyle = ( 'bold' => 'b' );

# Globals

################################################################################
#
# Function New
#
# Function created a new CCustomisationFile
#
# Function takes: No arguments
#
# Function Returns: The new CCustomisationFile object
#
# Function Uses: Nothing
#
# Notes:
#################################################################################

sub New()
    {
    my $templ = shift;
    my $class = ref($templ) || $templ;
    
    # Create our object
    my $self = {};

    # Initialise it
    bless($self,$class);
    $self->_iLog(New CLog);

    # Return it
    return $self;
    }

################################################################################
#
# Function Private member data
#
# Function _iLog _iLine _iCol _iEOF _iTags _iCurrentNode
#
# Function takes: (optional) a value to set the data to
#
# Function Returns: The (new) value of the data
#
# Function Uses: Nothing
#
# Notes:
#################################################################################

sub _iLog
    {
    my $self = shift;
    return $self->_GetSet('LOG',@_);
    }

sub _iLine
    {
    my $self = shift;
    return $self->_GetSet('LINE',@_);
    }

sub _iCol
    {
    my $self = shift;
    return $self->_GetSet('COL',@_);
    }

sub _iEOF
    {
    my $self = shift;
    return $self->_GetSet('EOF',@_);
    }

sub _iTags
    {
    my $self = shift;
    return $self->_GetSet('TAGS',@_);
    }

sub _iCurrentNode
    {
    my $self = shift;
    return $self->_GetSet('CURRENTNODE',@_);
    }

sub _GetSet
    {
    my $self = shift;
    my $var = shift;

    if (@_)
	{
	$self->{$var} = shift;
	}

    return $self->{$var};
    }

################################################################################
#
# Function LoadAleppoFile
#
# Function reads in an Aleppo format customisation file
#
# Function takes: The filename to load
#
# Function Returns: No results
#
# Function Uses: _ReadFiller, _ReadTag, _ParseTag, CMarkupTag
#
# Notes:
#################################################################################

sub LoadAleppoFile($)
    {
    my $self = shift;
    my ($aFilename) = @_;

    open(FILEH, $aFilename) or $self->_iLog->LogDie("Can't find '$aFilename' (customisation) file!\nDoes it exist?");

    $self->_iEOF(0);
    $self->_iLine(1);
    $self->_iCol(0);

    $self->_iTags( [] );

    $self -> _ReadFiller(*FILEH);

    while (!$self->_iEOF)
	{
	my $string = $self->_ReadTag(*FILEH);
	my $tag = $self->_ParseTag($string);

	if (!$tag)
	    {
	    $self->_iLog->LogDie("Internal error; didn't expect undef tag");
	    }
	elsif (!$self->_ValidateTag($tag))
	    {
	    $self->_LogParseWarning("Ignoring invalid tag: '<$string>'");
	    }
	else
	    {
	    push @{$self->_iTags}, $tag;
	    }
	}
    }

################################################################################
#
# Function SaveCSHelpFile
#
# Function saves a CSHelp (XML format) customisation file
#
# Function takes: The filename to save
#
# Function Returns: No results
#
# Function Uses: CMarkupTag
#
# Notes:
#################################################################################

sub SaveCSHelpFile($)
    {
    my $self = shift;
    my ($aFilename) = @_;

    # We do not check if the data is valid; both formats are the same in the
    # internal format, and the data was checked when it was loaded in.
    # (If we provide a Set function in the future, we'll need to validate here,
    # though)

    open( XML, ">$aFilename") or die "Can't create $aFilename (CSHelp conversion) file!\n";

    # Make the file using DOM

    my $xmlDoc = new XML::DOM::Document;

    # XML Prologue

    $self->_WriteXMLPrologue( $xmlDoc );

    # Build top XML element

    my $topElement = new XML::DOM::Element( $xmlDoc, 'cshcust' );

    $xmlDoc->appendChild($topElement);

    # Maintain the node for navigation purposes

    $self -> _iCurrentNode($topElement);

    # Write the tag data

    foreach my $tag (@{$self->_iTags})
	{
	$self->_WriteTag( $tag );
	}

    # Save to disc

    $topElement->addText("\n");

    $xmlDoc -> printToFileHandle( \*XML );
    close( XML );
    }

################################################################################
#
# Function Private _WriteXMLPrologue
#
# Function writes the XML prologue (XML declaration and stylesheet)
#
# Function takes: The XML::DOM document object to write to
#
# Function Returns: No results
#
# Function Uses: XML::DOM
#
# Notes:
#################################################################################

sub _WriteXMLPrologue($)
    {
    my $self = shift;
    my ($aXmlDoc) = @_;

    $aXmlDoc -> setXMLDecl( $aXmlDoc->createXMLDecl("1.0", undef, undef) );
    $aXmlDoc -> setDoctype( $aXmlDoc->createDocumentType( "cshcust", "SYSTEM", "file:///".main::KEpocToolsRoot()."/cshlpcmp/dtd/CSHcush.dtd" ) );
    $aXmlDoc -> appendChild( new XML::DOM::ProcessingInstruction( $aXmlDoc, "xml:stylesheet", 'href="file:///'.main::KEpocToolsRoot().'/cshlpcmp/xsl/CSHcust.xsl" title="CS-Help customisation" type="text/xsl"' ) );
    }

################################################################################
#
# Function Private _WriteTag
#
# Function writes a tag to a DOM object
#
# Function takes: The CMarkupTag object to write
#
# Function Returns: No results
#
# Function Uses: CMarkupTag
#
# Notes:
#################################################################################

sub _WriteTag($)
	{
	my $self = shift;
	my ($aTag) = @_;

	my $currentNode = $self->_iCurrentNode;

	my $xmlDoc = $currentNode->getOwnerDocument;

	$currentNode->addText("\n");

	my $element = new XML::DOM::Element( $xmlDoc, lc($aTag->GetName) );

	$currentNode->appendChild($element);

	my $content = ""; # Textual contents
	my $container = $element; # The tag the contents should go in (!)
	                          # It may be a sub-element

	for (my $i=1; $i <= $aTag->GetNumAttribs; $i++)
		{
		my $attribName = $aTag->GetAttribName($i);
		my $attribValue = $aTag->GetAttribValue($i);

		if ($KTagContent{$aTag->GetName} eq lc($attribName))
			{
			# Attribute should be turned into content on the output
			$content=$attribValue;
			}
		elsif (exists( $KContentStyle{lc($attribName)} ))
			{
			my $subElement = new XML::DOM::Element(
							   $xmlDoc,
							   $KContentStyle{ lc($attribName) }
							 );
			$container->appendChild($subElement);
			$container = $subElement;
			}
		else
			{
			$element->setAttribute( lc($attribName), $attribValue );
			}
		}

	if ($content ne "")
		{
		$container->addText( $content );
		}
	}
   
###############################################################################
#
# Function Private _ValidateTag
#
# Function Checks a tag is contains the correct information
#
# Function takes: The CMarkupTag object to check
#
# Function Returns: 1 if valid, 0 if not
#
# Function Uses: CMarkupTag
#
# Notes:
###############################################################################

sub _ValidateTag($)
	{
	my $self = shift;
	my ($aTag) = @_;

	# Check the name
	my $tagName = $aTag->GetName;
	$tagName = lc($tagName);
	if ( ! exists($KStyles{$tagName}) )
		{ return 0; }

	my $attribs = $KStyles{$tagName};

	# Check each attribute is a valid one

    for (my $i=1; $i <= $aTag->GetNumAttribs; $i++)
		{
		if (! InList( lc($aTag->GetAttribName($i)), @$attribs) )
			{ return 0; }
		}

	# Check the required attributes exist

    if ( exists($KRequiredAttribs{$tagName}) )
		{
		foreach my $reqAttrib ($KRequiredAttribs{$tagName})
			{
			if ( ! $aTag->IsAttrib($reqAttrib) )
				{ return 0; }
			}
		}
    
	# If we've passed all those...
	return 1;
    }

################################################################################
#
# Function Private _ReadFiller
#
# Function Reads the bits between tags
#
# Function takes: The filehandle to read from
#
# Function Returns: The string read in
#
# Function Uses: _CountChar
#
# Notes:
#################################################################################

sub _ReadFiller($)
    {
    my $self = shift;
    my ($FILEH) = @_;
    
    my $string;

    # Get characters until the next < or the end of the file
    my $char = getc($FILEH);
    $self->_CountChar($char);

    while ( ($char ne '<') && ($char ne undef) )
	{
	$string = $string.$char;
        $char = getc($FILEH);
	$self->_CountChar($char);
	}

    if ($char eq undef)
        { $self->_iEOF(1); }

    if (! ($string =~ /^[ \t]*$/m) )
	{
	$self->_LogParseWarning("Invalid filler between tags: '$string'");
	}

    return $string;
    }

################################################################################
#
# Function Private _ReadTag
#
# Function Reads in tag contents between the <>s
#
# Function takes: The filehandle to read from
#
# Function Returns: The tag string read in
#
# Function Uses: _CountChar
#
# Notes:
#################################################################################

sub _ReadTag($)
    {
    my $self = shift;
    my ($FILEH) = @_;

    my $char = getc($FILEH);
    $self->_CountChar($char);
    my $tag;
    my $quoted = 0;
    my $equals = 0; # Note, quotes only count round the attribute name i.e. an open
                    # quote can only be found after an =.

    # Get characters until the end of the file, or the next >
    # (or the next < if that it missing)

    while ( ($char ne '>') && ($char ne '<') && ($char ne undef) )
	{
	$tag = $tag.$char;

	# Process quotes
	if ($char eq "'")
	    {
	    # Note that single quotes don't act as quotes, but seem to act as a
	    # comment indicator. They can be put inside double quotes safely.

	    if (!$quoted)
		{
		# Comment?
		$self->_LogParseWarning("Found bare apostrophe before ...<$tag . May be error");
		$tag = substr($tag,0,-1);
		# Skip the rest
		while ( ($char ne '>') && ($char ne '<') && ($char ne undef) )
		    {
		    $char = getc($FILEH);
		    $self->_CountChar($char);
		    }
		last;
		}
	    }
	elsif ($char eq '"')
	    {
	    if ($quoted)
		{$quoted = 0;}
	    else
		{
		if ( $equals )
		    {$quoted = 1;}
		else
		    {
		    # Comment?
		    $self->_LogParseWarning("Found bare double quote before ...<$tag . May be error");
		    $tag = substr($tag,0,-1);
		    # Skip the rest
		    while ( ($char ne '>') && ($char ne '<') && ($char ne undef) )
			{
			$char = getc($FILEH);
			$self->_CountChar($char);
			}
		    last;
		    }
		}

	    }
	elsif ($char eq '=')
	    {
	    $equals = 1;
	    }

	# If we find something other than an = or whitespace, reset the flag
	# (so that quotes no longer count)
	if ($char !~ /[ \t\n=]/s)
	    {
	    $equals = 0;
	    }

	$char = getc($FILEH);

        $self->_CountChar($char);
	}

    if ($quoted)
	{
	$self->_LogParseWarning("Mismatched quotes in tag '<$tag>' ('>' cannot be quoted)");
	}
    # Make it up to the next tag
    if ( ($char ne '<') && ($char ne undef) )
	{ $self->_ReadFiller($FILEH); }
    else
	{
	$self->_LogParseWarning("Missing '>' at end of tag '<$tag'");
	}

    if ($char eq undef)
	{ $self->_iEOF(1); }

    return $tag;
    }

################################################################################
#
# Function Private _CountChar
#
# Function increments the position counters
#
# Function takes: The character just inputted
#
# Function Returns: No results
#
# Function Uses: Nothing
#
# Notes: There must be $col and $line variables in the local scope, which the
#        function will manipulate. These values must persist between calls to
#        this function (while processing a particular file).
#################################################################################

sub _CountChar($)
    {
    my $self = shift;
    my ($char) = @_;

    $self->_iCol($self->_iCol + 1);
    if ($char eq "\n") { $self->_iLine($self->_iLine + 1); $self->_iCol(0); }
    }

################################################################################
#
# Function Private _ParseTag
#
# Function parses a tag string into a tag object
#
# Function takes: The tag string
#
# Function Returns: The CMarkupTag object
#
# Function Uses: CMarkupTag
#
# Notes: If parsing fails it will generally return the tag as parsed up to that
#        point, to mimic Aleppo. Unlike Aleppo it will warn that parsing has
#        failed, however.
#################################################################################

sub _ParseTag($)
    {
    my $self = shift;
    my ($aTag) = @_;

    my $line = $self->_iLine;
    my $col = $self->_iCol;
    my $tag = $aTag;

    #Strip any (bogus) leading spaces
    $tag =~ s/^[ \t\n]+//s;

    #Take the first word as the tag name
    my $name = $tag;
    $name =~ s/[ \t\n].*$//s;
    $tag =~ s/^[^ \t\n]+//s;

    if ($name =~ /=/)
	{
	# If we find an = in the tag name, we are confused
	$self->_LogParseWarning("Found '=' in tag name '$name'; correcting and ignoring rest");
	$name =~ s/=.*$//s;
	return New CMarkupTag($name, 0);
	}

    my $tagobj = New CMarkupTag($name, 0);

    #Get the attributes
    while ($tag =~ /[^ \t\n]/s) #While there is something other than whitespace...
	{
	#Strip leading space
        $tag =~ s/^[ \t\n]+//s;

	#Take the first word as the attribute name
	my $attname = $tag;
	$attname =~ s/[ \t\n=].*$//s;
	$tag =~ s/^[^ \t\n=]+//s;

	#Strip the '='
	if ($tag =~ /^[ \t\n]*=/s)
	    {
	    $tag =~ s/^[ \t\n]*=[ \t^]*//s;
	    }
	else
	    {
	    # If we don't find the '=' then we are lost
	    $self->_LogParseWarning("Expected '=' in tag '$aTag' after the first word");
	    return $tagobj;
	    }

	my $attval;
	#Take an (optionally quoted) word as the attribute value
	if (substr($tag,0,1) eq '"')
	    {
	    my $quote = index($tag,'"',1);
	    if ($quote != -1)
		{
		$attval = substr($tag,1,$quote-1);
		$tag = substr($tag,$quote+1);
		# Note that we don't need a space after the end quote
		}
	    else
		{
		# There was no end quote. The error for mismatched quotes should
		# already have been reported; we just handle it.
		$attval = substr($tag,1);
		$tag = "";
		}
	    }
	else
	    {
	    $attval = $tag;
	    $attval =~ s/[ \t\n].*$//s;
	    $tag =~ s/^[^ \t\n]+//s;

	    if ($attval =~ /=/)
		{
		# Shouldn't have '=' here!
		$self->_LogParseWarning("Found '=' in attribute value '$attval'; correcting and ignoring rest");

		$attval =~ s/=.*$//s;
		$tagobj->AddAttribute($attname, $attval);
		return $tagobj;
		}
	    }
	
	$tagobj->AddAttribute($attname, $attval);
	}

    return $tagobj;
    }

################################################################################
#
# Function Private _LogParseWarning
#
# Function Logs a warning, noting the file position the error occurred in.
#
# Function takes: The warning message
#
# Function Returns: No results
#
# Function Uses: CLog
#
# Notes: Function uses a Log rather than a LogWarning
#        Any newlines will be converted to plain spaces.
#################################################################################

sub _LogParseWarning($)
    {
    my $self = shift;
    my ($aMessage) = @_;

    my $message = $aMessage;
    $message =~ s/\n/ /s; # Change newline to plain space
    my $line = $self->_iLine;
    my $col = $self->_iCol;

    $self->_iLog->Log("Warning: Customisation file: Line $line Column $col:\n\t$message");	
    }

################################################################################
#
# Function TEST
#
# Function tests the class methods
#
# Function takes: No parameters
#
# Function Returns: No results
#
# Function Uses: Nothing
#
# Notes:
#################################################################################

sub TEST()
    {
    my $self = shift;
    
    $self->LoadAleppoFile("UK.ALC");
    $self->SaveCSHelpFile("UK.ALC.xml");
    }
1;




