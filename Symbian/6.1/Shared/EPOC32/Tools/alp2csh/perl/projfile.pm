#!perl
################################################################################
#
# module: projfile.pm
#
# module implements perl object CHelpProjectFile, CParamPermissions
#
# Copyright (c) 1999 Symbian Ltd.  All rights reserved
#
# Date Thu Sep 30 09:29 1999
#
################################################################################
#
# Modification history
#
# version 001 - Initial version
#
# Version 002 - Corrected some naming of constants
#
################################################################################
package CHelpProjectFile;

# use libraries
use XML::DOM;
use log;
use strlist;

# Constants
# Format...        keyword                          can take list? required?
#                  |                                             | |
my %KKeywords = ( "uid"               => [ undef ,
					   New CParamPermissions(0,1) ],
                  "inputdirectory"    => [ New CParamPermissions(0,1) ,
					   New CParamPermissions(0,1) ],
                  "outputdirectory"   => [ New CParamPermissions(0,1) ,
					   New CParamPermissions(0,1) ],
                  "outputfile"        => [ New CParamPermissions(0,1) ,
					   New CParamPermissions(0,1) ],
                  "sourcefile"        => [ New CParamPermissions(1,1) ,
					   New CParamPermissions(1,1) ],
                  "orderfile"         => [ New CParamPermissions(0,0) ,
					   New CParamPermissions(0,0) ],
                  "graphicsdirectory" => [ New CParamPermissions(0,1) ,
					   New CParamPermissions(0,1) ],
                  "workingdirectory"  => [ New CParamPermissions(0,0) ,
					   New CParamPermissions(0,0) ],
                  "customizationfile" => [ New CParamPermissions(0,0) ,
					   New CParamPermissions(0,0) ],
		);

# Which permissions entry is which?
my $KAleppo = 0;
my $KCSHelp = 1;

################################################################################
#
# Function New
#
# Function creates a new perl object
#
# Function takes: no arguments 
#
# Function Returns: the created object
#
# Function Uses: CStringList
#
# Notes:
################################################################################

sub New()
    {
    my $templ = shift;
    my $class = ref($templ) || $templ;
    
    # Create our object
    my $self = {};
    bless ($self, $class);
    
    # Load values
    $self->_iFileData({});
    for my $keyword ( keys(%KKeywords) )
        {
        $self -> _iFileData -> {$keyword} = New CStringList;
	$self -> _SetUndef($keyword);
        }
    $self->_iLog( New CLog );
    
    # Return our object
    return $self;
    }

################################################################################
#
# Function Private member data
#
# Functions _iCurrentNode _iFileData _iLog
#
# Function takes:
#
# Function Returns:
#
# Notes:
#################################################################################

sub _iCurrentNode
    {
    my $self = shift;
    
    return $self->_GetSet('CURRENTNODE',@_);
    }

sub _iFileData
    {
    my $self = shift;

    return $self->_GetSet('FILEDATA',@_);
    }

sub _iLog
    {
    my $self = shift;
    
    return $self->_GetSet('LOG',@_);	
    }

sub _GetSet
    {
    my $self = shift;
    my $var = shift;

    if (@_)
	{
	$self -> {$var} = shift;
	}
    
    return $self -> {$var};
    }

# Object methods

################################## Public ######################################

################################################################################
#
# Function LoadAleppoFile
#
# Function loads in an Aleppo project file (*.alp)
#
# Function takes: The filename to load
#
# Function Returns:
#
# Function Uses:
#
# Notes: The function validates the data after loading, and will terminate if
#        it is invalid. Note that valid for an Aleppo file isn't the same as
#        valid for a CSHelp file, and SaveCSHelp will perform it's own validation
#        before saving.
#################################################################################

sub LoadAleppoFile($)
    {
    my $self = shift;
    my ($aFilename) = @_;
    
    for my $keyword ( keys(%KKeywords) )
        {
	$self -> _SetUndef($keyword);
        }

    # Open the file for input
        
    open( ALEPPO, $aFilename) or $self->_iLog->LogDie("Can't find '$aFilename' (project) file! Does it exist?");
        
    # Process the lines from the file
        
    while ( my $line = <ALEPPO> )
        {
        chomp($line);

	# Is it a blank line?

	if ($line =~ /^[ \t]*$/)
	    {
	    $self->_iLog->Log("Warning: Blank line found in project file; ignoring it");
	    }

	else
	    {
	    # Split the line by words into 'attribute value [value]*'

	    my ($attribute, $value) = split( /\W/, $line, 2);
            
	    # Have we already come across this?

	    if (!exists($KKeywords{$attribute}) )
		{
		$self->_iLog->LogDie("In file $aFilename: '$attribute' isn't a recognised keyword");
		}

	    if (!$self->IsUnset($attribute))
		{
		$self->_iLog->Log("Warning: Multiple '$attribute' lines found; ignoring all but last one");
		}

	    # Prime the store
	    if ( $self->_SetDef($attribute) == 0 )
		{
		$self->_iLog->LogDie("Internal error; CStringList object not set up for '$attribute'");
		}

	    # Store the data

	    foreach my $item (split( /[ ,]/, $value))
		{
		if ( $self->Add($attribute, $item) == 0 )
		    {
		    $self->_iLog->LogDie("Internal error; CStringList object not set up for '$attribute'");
		    }
		}
	    }
        }
    close( ALEPPO );

    if (!$self->ValidateAleppo)
	{
	exit 2;
	}
    }

################################################################################
#
# Function SaveCSHelpFile
#
# Function saves a CSHelp (XML format) project file
#
# Function takes: The filename to save
#
# Function Returns:
#
# Function Uses:
#
# Notes: The function validates the data before attempting to write it. This is
#          quite harsh, and will die if data isn't valid. An additional method
#          'ValidateCSHelp' is provided so that the user can check first and handle
#          appropriately.
#################################################################################

sub SaveCSHelpFile($)
    {
    my $self = shift;
    my ($aFilename) = @_;

    # Force the data to be CSHelp valid

    if ( $self->IsUnset('uid') )
	{
	$self -> Set('uid',"#FILLIN");
	}

    # Check the data is OK to write out
    if (!$self->ValidateCSHelp)
	{
	exit 2;
	}
        
    open( XML, ">$aFilename") or $self->_iLog->LogDie("Can't create $aFilename (CSHelp project) file!\nIs there already a locked file or directory of that name?");
        
    # Make the file using DOM
        
    my $xmlDoc = new XML::DOM::Document;
    
    # Maintain the current node for navigation purposes
        
    $self -> _iCurrentNode($xmlDoc);

    # XML Prologue
    
    $self -> _XMLPrologue;

    # Build XML
    
    $self -> _XMLOpenTag( 'cshproj' );
    $self -> _XMLAddText( "\n" );
    
    # Build 'helpfileUID' node

    $self -> _WriteUID;

    # Build the directory elements
    
    $self -> _WriteCSHelpDirectories;

    # Build the file elements
    
    $self -> _WriteCSHelpFiles;

    # Save file

    $xmlDoc -> printToFileHandle( \*XML );
    close( XML );
    }
    
################################################################################
#
# Function Set
#
# Function sets a parameter of the project file
#
# Function takes: Two arguments; keyword, value
#
# Function Returns: 1 if success, 0 if keyword not recognised
#
# Function Uses: CStringList
#
# Notes: The function doesn't error if there's a problem, but returns 0 only.
#        Users should test for this and behave accordingly.
#################################################################################

sub Set($$)
    {
    my $self = shift;
    my ($aKeyword, $aValue) = @_;

    my $data = $self->_iFileData;
    $aKeyword = lc($aKeyword);
    
    if ( exists( $KKeywords{$aKeyword} ) )
        {
	$self -> _SetDef ($aKeyword);
        $data -> {$aKeyword} -> AddString($aValue);
        return 1;
        }
    else
        {
        return 0;
        }
    }

################################################################################
#
# Function Add
#
# Function adds an item to a parameter of the project file
#
# Function takes: Two arguments; keyword, value
#
# Function Returns: 1 if success, 0 if keyword not recognised
#
# Function Uses: CStringList
#
# Notes:
#################################################################################

sub Add($$)
    {
    my $self = shift;
    my ($aKeyword, $aValue) = @_;

    my $data = $self->_iFileData;
    $aKeyword = lc($aKeyword);
    
    if ( exists( $KKeywords{$aKeyword} ) )
        {
        $data -> {$aKeyword} -> AddString($aValue);
        return 1;
        }
    else
        {
        return 0;
        }
    }

################################################################################
#
# Function Get
#
# Function gets the value of a keyword
#
# Function takes: The keyword to get
#
# Function Returns: The value of that keyword
#
# Function Uses: CStringList
#
# Notes: This function does not distinguish between undef and the empty string
#        (use IsUndef for that). In addition, if multiple values are stored this
#        will die. Check first with IsMultiple, or use GetList if you really
#        want a list of those multiple values.
#################################################################################

sub Get($)
    {
    my $self = shift;
    my ($aKeyword) = @_;
    
    my $data = $self->_iFileData;
    
    if ( exists( $KKeywords{$aKeyword} ) )
        {
	if ( ($data -> {$aKeyword} -> GetNumItems) > 1 )
	    {
	    $self->_iLog->LogDie("Internal error: Found multiple values in '$aKeyword'");
	    }
	else
	    {
	    return $data -> {$aKeyword} -> GetString(',');
	    }
        }
    else
        {
        $self->_iLog->LogDie("Internal error: parameter '$aKeyword' not recognised");
        }
    }

################################################################################
#
# Function GetMultiple
#
# Function gets the values of a keyword
#
# Function takes: The keyword to get
#
# Function Returns: The list of values of that keyword
#
# Function Uses: CStringList
#
# Notes: 
#################################################################################

sub GetMultiple($)
    {
    my $self = shift;
    my ($aKeyword) = @_;
    
    if (!exists( $KKeywords{$aKeyword} ) )
        {
        $self->_iLog->LogDie
	  ("Internal error: parameter '$aKeyword' not recognised");
        }

    my $data = $self->_iFileData;
    
    return $data -> {$aKeyword} -> GetStringList;
    }

################################################################################
#
# Function IsMultiple
#
# Function checks whether the keyword stores multiple items or not
#
# Function takes:The keyword to check
#
# Function Returns: 1 if multiple, 0 is single or unset
#
# Function Uses: CStringList
#
# Notes:
#################################################################################

sub IsMultiple($)
    {
    my $self = shift;
    my ($aKeyword) = @_;

    if (!exists( $KKeywords{$aKeyword} ) )
        {
        $self->_iLog->LogDie
	  ("Internal error: parameter '$aKeyword' not recognised");
        }

    my $data = $self->_iFileData;

    if ($data->{$aKeyword}->GetNumItems > 1)
	{ return 1; }
    else
	{ return 0; }
    }

################################################################################
#
# Function IsUnset
#
# Function checks if the value of a keyword is not set
#
# Function takes: The keyword to check
#
# Function Returns: 1 if unset, 0 if set
#
# Function Uses: CStringList
#
# Notes: 
#################################################################################

sub IsUnset($)
    {
    my $self = shift;
    my ($aKeyword) = @_;
    
    my $data = $self->_iFileData;
    
    if ( exists( $KKeywords{$aKeyword} ) )
        {
        return $data -> {$aKeyword} -> IsUndef;
        }
    else
        {
        $self->_iLog->LogDie("Internal error: parameter '$aKeyword' not recognised");
        }
    }

################################################################################
#
# Function ValidateAleppo
#
# Function checks the values of keywords in the object to ensure they constitute a
#          valid Aleppo project file
#
# Function takes: No parameters
#
# Function Returns: 1 if valid, 0 if not.
#
# Function Uses:
#
# Notes: Checks that required keywords are present, and that keywords which should
#          only contain single values (not lists) really do.
#################################################################################

sub ValidateAleppo()
    {
    my $self = shift;

    return $self->_Validate($KAleppo);
    }

################################################################################
#
# Function ValidateCSHelp
#
# Function checks the values of keywords in the object to ensure they constitute a
#          valid CSHelp project file
#
# Function takes: No parameters
#
# Function Returns: 1 if valid, 0 if not.
#
# Function Uses:
#
# Notes: Checks that required keywords are present, and that keywords which should
#          only contain single values (not lists) really do.
#################################################################################

sub ValidateCSHelp()
    {
    my $self = shift;

    return $self->_Validate($KCSHelp);
    }

################################################################################
#
# Function PRINT
#
# Function prints the contents of the object
#
# Function takes: No parameters
#
# Function Returns: No results
#
# Function Uses:
#
# Notes:
#################################################################################

sub PRINT()
    {
    my $self = shift;

    for my $attrib ( keys(%KKeywords) )
	{
	if ($self->IsUnset($attrib))
	    {
	    $self->_iLog->Log("$attrib => Unset");
	    }
	else
	    {
	    my @value = $self -> GetMultiple($attrib);
	    $self->_iLog->Log("$attrib => ".join(",",map('"'.$_.'"',@value)));
	    }
	}
    }

################################################################################
#
# Function TEST
#
# Function tests the methods of the class
#
# Function takes:
#
# Function Returns:
#
# Function Uses:
#
# Notes: Check boss.csp.xml after running
#################################################################################
sub TEST
    {
    my $self = shift;

    my $testObj = New CHelpProjectFile;

    $self->_iLog->Log("- Loading...");
    $testObj->LoadAleppoFile('boss.alp');
    
    # Print out our values

    $testObj->PRINT;

    # Save our test file out

    $self->_iLog->Log("- Saving...");
    $testObj->SaveCSHelpFile('boss.csp.xml');

    # Some set/get tests

    $testObj->Set('outputfile','frederick');
    $testObj->Set('sourcefile','james');
    $testObj->Add('sourcefile','sheila');
    $testObj->Set('outputfile','bill');
    $testObj->Set('workingdirectory','dave');

    if
      ( ($testObj->Get('outputfile') ne 'bill')
      ||(($testObj->GetMultiple('sourcefile'))[0] ne 'james')
      ||(($testObj->GetMultiple('sourcefile'))[1] ne 'sheila')
      ||($testObj->Get('workingdirectory') ne 'dave')
      )
	{
	$self->_iLog->Log("- Set/Add/Get test FAILED!");

	$self->_iLog->Log("- Diagnostics:");
	$self->_iLog->Log($testObj->Get('outputfile'));
	$self->_iLog->Log(($testObj->GetMultiple('sourcefile'))[0]);
	$self->_iLog->Log(($testObj->GetMultiple('sourcefile'))[1]);
	$self->_iLog->Log($testObj->Get('workingdirectory'));
	}
    else
	{
	$self->_iLog->Log("- Set/Get/Add test passed");
	}
    
    # Invalidating tests

    $testObj->Set('outputfile','one');
    $testObj->Add('outputfile','two');
    if ($testObj->ValidateCSHelp)
	{
	$self->_iLog->Log("- Invalid list test FAILED!");
	}
    else
	{
	$testObj->Set('outputfile','just one');
	if (!$testObj->ValidateCSHelp)
	    {
	    $self->_iLog->Log("- Re-valid test FAILED!");
	    }
	else
	    {
	    $self->_iLog->Log("- Invalidating tests passed");
	    }
	}

    # Failing tests
    $self->_iLog->Log("- About to fail");

    $testObj->Get('fake parameter');
    }

################################## Private #####################################


################################################################################
#
# Function Private _ParamMultiple
#
# Function determines whether a parameter can take a list of values or not
#
# Function takes: The parameter keyword, and the file format (constant) to check
#                 against
#
# Function Returns: 1 if the parameter can take a list, 0 if not
#
# Function Uses: CParamPermissions
#
# Notes: This will crash if the parameter is not allowed in the format
#################################################################################

sub _ParamMultiple($$)
    {
    my $self = shift;
    my ($aKeyword, $aFormat) = @_;
    
    my $parameters = $KKeywords { $aKeyword }; # A reference to the list of
                    # different CParamPermissions objects (for different formats)
    return $parameters -> [$aFormat] -> IsListTaker;
    }

################################################################################
#
# Function Private _ParamRequired
#
# Function determines whether a parameter is mandatory or not
#
# Function takes: The parameter keyword, and the file format (constant) to check
#                 against
#
# Function Returns: 1 if the parameter is required, 0 if not
#
# Function Uses: CParamPermissions
#
# Notes: This will crash of the parameter is not allowed in the format
#################################################################################

sub _ParamRequired($$)
    {
    my $self = shift;
    my ($aKeyword, $aFormat) = @_;
    
    my $parameters = $KKeywords { $aKeyword }; # A reference to the list of
                    # different CParamPermissions objects (for different formats)
    return $parameters -> [$aFormat] -> IsRequired;
    }

################################################################################
#
# Function Private _ParamAllowed
#
# Function determines whether a parameter is allowed or not
#
# Function takes: The parameter keyword, and the file format (constant) to check
#	 	  against
#
# Function Returns: 1 if the parameter is allowed, 0 if not
#
# Function Uses: CParamPermissions
#
# Notes:
#################################################################################

sub _ParamAllowed($$)
    {
    my $self = shift;
    my ($aKeyword, $aFormat) = @_;
    
    if (exists($KKeywords { $aKeyword }) )
	{
	if ( ( ($KKeywords{$aKeyword}) -> [$aFormat] ) ne undef )
	    { return 1; }
	}
    
    return 0;
    }

################################################################################
#
# Function Private _SetUndef
#
# Function unsets the specified file data item
#
# Function takes: The keyword of the item to unset
#
# Function Returns: 0 if the keyword does not exist, 1 if OK
#
# Function Uses: CStringList
#
# Notes: This can't be done with Set(foo,undef), since this is equivalent to
#        Set(foo,"").
#################################################################################

sub _SetUndef($)
    {
    my $self = shift;
    my ($aKeyword) = @_;

    if ( exists( $self -> _iFileData -> {$aKeyword} ) )
	{
        $self -> _iFileData -> {$aKeyword} -> SetUndef;
	return 1;
	}
    else
	{
	return 0;
	}
    }

################################################################################
#
# Function Private _SetDef
#
# Function defines the specified file data item (as an empty list)
#
# Function takes: The keyword of the item to define
#
# Function Returns: 0 if the keyword does not exist, 1 if OK
#
# Function Uses: CStringList
#
# Notes: This can't be done with Set(foo,""), since this enters an empty string
#        item in the list
#################################################################################

sub _SetDef($)
    {
    my $self = shift;
    my ($aKeyword) = @_;

    if ( exists( $self -> _iFileData -> {$aKeyword} ) )
	{
        $self -> _iFileData -> {$aKeyword} -> SetDef;
	return 1;
	}
    else
	{
	return 0;
	}
    }

################################################################################
#
# Function Private _Validate
#
# Function checks the values of keywords in the object to ensure they constitute a
#          valid project file
#
# Function takes: The file format (constant) to use
#
# Function Returns: 1 if valid, 0 if not.
#
# Function Uses:
#
# Notes: Checks that required keywords are present, and that keywords which should
#          only contain single values (not lists) really do.
#################################################################################

sub _Validate($)
    {
    my $self = shift;
    my ($aFormat) = @_;
    
    my $valid = 1;

    # Check each keyword in turn

    for my $keyword ( keys %KKeywords )
        {
	if ( $self->_ParamAllowed($keyword, $aFormat) )
	    {
	    # Check that those that should be there, are there.
    
	    if ( $self->_ParamRequired($keyword, $aFormat) )
		{
		if ( $self->IsUnset($keyword) )
		    {
		    $self->_iLog->Log("Project file must contain a '$keyword' field.");
		    $valid = 0;
		    }
		}
	    # Check they haven't got multiple values if they're not allowed to.
	    
	    if ( !($self->_ParamMultiple($keyword, $aFormat) ) )
		{
		if ( $self->IsMultiple($keyword) )
		    {
		    $self->_iLog->Log("Project file must contain only one entry per '$keyword' field.");
		    $valid = 0;
		    }
		}
            }
	else
	    {
	    # If param is not allowed for this format, make sure it's not there
	    if ( ! $self->IsUnset($keyword) )
		{
		$self->_iLog->Log("Project file must not contain a '$keyword' entry");
		$valid = 0;
		}
	    }
        }
    
    # Return 1 if no problems were found
    return $valid;
    }

################################################################################
#
# Function Private _WriteCSHelpDirectories
#
# Function writes the <directories> element in the CSHelp project file
#
# Function takes: No parameters
#
# Function Returns: No results
#
# Function Uses: _XML methods
#
# Notes:
#################################################################################

sub _WriteCSHelpDirectories()
    {
    my $self = shift;

    # Build 'directories' node
    
    $self -> _XMLAddText( '  ' );
    $self -> _XMLOpenTag( 'directories' );
    $self -> _XMLAddText( "\n" );
    
    # (and subnodes)
    $self -> _WriteSimpleElement( 'input', $self -> Get('inputdirectory'), '    ' );
    
    $self -> _WriteSimpleElement( 'output', $self -> Get('outputdirectory'), '    ' );
    
    $self -> _WriteSimpleElement( 'graphics', $self -> Get('graphicsdirectory'), '    ' );

    if (!$self->IsUnset('workingdirectory'))
	{
	$self -> _WriteSimpleElement(
          'working',
          $self -> Get('workingdirectory'),
          '    '
          );
	}
    
    $self -> _XMLAddText( '  ' );
    $self -> _XMLCloseTag;
    $self -> _XMLAddText( "\n" );
    }

################################################################################
#
# Function Private _WriteCSHelpFiles
#
# Function writes the <files> element in the CSHelp project file
#
# Function takes: No parameters
#
# Function Returns: No results
#
# Function Uses: _XML methods
#
# Notes:
#################################################################################

sub _WriteCSHelpFiles()
    {
    my $self = shift;

    # Build 'files' node
    
    $self -> _XMLAddText( '  ' );
    $self -> _XMLOpenTag( 'files' );
    $self -> _XMLAddText( "\n" );
    
    # ( and subnodes )
    
    $self -> _WriteListingElement( 'source', 'file', 'sourcefile', '    ' );
    
    $self -> _WriteSimpleElement( 'destination', $self->Get('outputfile'), '    ');
    
    if (!$self->IsUnset('customizationfile'))
	{
	$self -> _WriteSimpleElement(
	   'customization',
	   $self->Get('customizationfile'),
	   '    '
	   );
	}

    $self -> _XMLAddText( '  ' );
    $self -> _XMLCloseTag;
    $self -> _XMLAddText( "\n" );
    }

################################################################################
#
# Function Private _WriteListingElement
#
# Function builds an XML element which can contain more than one entry, each
#          in individual sub-elements
#
# Function takes: The name of the element, name of the sub-elements, the
#                 name of the data item to go in, and a string to indent all
#		  the tags by.
#
# Function Returns: No results
#
# Function Uses: _XML methods, _WriteSimpleElement
#
# Notes:
#################################################################################

sub _WriteListingElement($$$$)
    {
    my $self = shift;
    my ($aName, $aSubName, $aData, $aIndent) = @_;

    $self -> _XMLAddText( $aIndent );
    $self -> _XMLOpenTag( $aName );
    $self -> _XMLAddText( "\n" );

    # ( build repeating elements )

    for my $file ( $self->GetMultiple($aData) )
        {
	$self -> _WriteSimpleElement( $aSubName, $file, $aIndent."  " );
        }

    $self -> _XMLAddText( $aIndent );
    $self -> _XMLCloseTag;
    $self -> _XMLAddText( "\n" );
    }

################################################################################
#
# Function Private _WriteSimpleElement
#
# Function writes a element containing a single data item
#
# Function takes: The name of the data item to write (tag name), and the value
#                 to write, and a string to indent the line with (usually spaces)
#
# Function Returns: No results
#
# Function Uses:
#
# Notes: Validation must have ensured this is not a multiple data item
#################################################################################

sub _WriteSimpleElement($$$)
    {
    my $self = shift;
    my ($aName, $aValue, $aIndent) = @_;

    $self -> _XMLAddText( $aIndent );
    $self -> _XMLAddTextOnlyElement( $aName, $aValue );
    $self -> _XMLAddText( "\n" );
    }

################################################################################
#
# Function Private _WriteUID
#
# Function writes the <helpfileUID> element to the currently open CSHelp file
#
# Function takes: No parameters (all data is taken from the object)
#
# Function Returns: No values
#
# Function Uses: _XMLOpenTag/CloseTag, _XMLAddText/Comment
#
# Notes: Validation must have ensured that the UID is not a multiple data item
#################################################################################

sub _WriteUID()
    {
    my $self = shift;
    
    $self -> _XMLAddText( '  ' );

    $self -> _XMLOpenTag( 'helpfileUID' );
    if ( $self->Get('uid') ne "#FILLIN" )
        {
        $self -> _XMLAddText( $self->Get('uid') );
        }
    else
        {
        $self -> _XMLAddComment( 'Insert UID here' );
        }
    $self -> _XMLCloseTag;
    $self -> _XMLAddText( "\n" );
    }

################################################################################
#
# Function Private _XMLAddComment
#
# Function simulates writing a comment tag
#
# Function takes: The comment
#
# Function Returns:
#
# Function Uses: XML::DOM
#
# Notes: 
#################################################################################

sub _XMLAddComment($)
    {
    my $self = shift;
    my ($aComment) = @_;
    
    my $currentNode = $self->_iCurrentNode;
    my $xmlDoc = $self->_XMLOwnerDocument($currentNode);

    my $newObject = new XML::DOM::Comment( $xmlDoc, $aComment );
    $currentNode -> appendChild( $newObject );
    }

################################################################################
#
# Function Private _XMLAddText
#
# Function simulates writing text to the end of the current element
#
# Function takes: Text to be written
#
# Function Returns:
#
# Function Uses: XML::DOM
#
# Notes:
#################################################################################

sub _XMLAddText($)
    {
    my $self = shift;
    my ($aText) = @_;
    
    my $currentNode = $self->_iCurrentNode;
    
    $currentNode -> addText( $aText );
    }

################################################################################
#
# Function Private _XMLAddTextOnlyElement
#
# Function simulates writing an element containing only simple text (i.e. no
#          sub-elements)
#
# Function takes: The element name, and the text to put in it
#
# Function Returns:
#
# Function Uses: XML::DOM
#
# Notes: This is a shortcut. Performing _XMLOpenTag, _XMLAddText then
#          _XMLCloseTag would generate the same result, but less efficiently.
#################################################################################

sub _XMLAddTextOnlyElement($$)
    {
    my $self = shift;
    my ($aElementName, $aText) = @_;

    if (ref($aText))
	{ $aText=join($aText,''); } # Special case
    
    my $currentNode = $self->_iCurrentNode;
    my $xmlDoc = $self->_XMLOwnerDocument($currentNode);
    
    # Build our new element...
    my $newObject = new XML::DOM::Element( $xmlDoc, $aElementName );
    $newObject -> addText( $aText );

    # ...and put it in the tree
    $currentNode -> appendChild( $newObject );
    }

################################################################################
#
# Function Private _XMLCloseTag
#
# Function simulates closing the current tag (by jumping out a level)
#
# Function takes:
#
# Function Returns:
#
# Function Uses: 
#
# Notes: You don't need to close a tag for its own sake; if you've nothing
#          further to add, simply finish using the document and it will be closed
#          in the correct place.
#################################################################################

sub _XMLCloseTag($)
    {
    my $self = shift;
    
    $self->_iCurrentNode( $self->_iCurrentNode->getParentNode );
    }

################################################################################
#
# Function Private _XMLOpenTag
#
# Function simulates writing an open tag by generating an element and moving
#          inside that
#
# Function takes: Tag name
#
# Function Returns:
#
# Function Uses: XML::DOM
#
# Notes: 
#################################################################################

sub _XMLOpenTag($)
    {
    my $self = shift;
    my ($aElementName) = @_;
    
    my $currentNode = $self->_iCurrentNode;

    my $xmlDoc = $self->_XMLOwnerDocument($currentNode);

    my $newObject = new XML::DOM::Element( $xmlDoc, $aElementName );
    my $newNode = $currentNode -> appendChild( $newObject );
    $self->_iCurrentNode($newNode);
    }

################################################################################
#
# Function Private _XMLOwnerDocument
#
# Function finds the owner document of a node, or itself if it is a document
#
# Function takes: The DOM node
#
# Function Returns: The DOM document
#
# Function Uses: XML::DOM
#
# Notes:
#################################################################################

sub _XMLOwnerDocument($)
    {
    my $self = shift;
    my ($aNode) = @_;

    my $xmlDoc;

    if ($aNode->getNodeType eq DOCUMENT_NODE)
        {
	$xmlDoc = $aNode;
	}
    else
	{
        $xmlDoc = $aNode->getOwnerDocument;
	}

    return $xmlDoc;
    }

################################################################################
#
# Function Private _XMLPrologue
#
# Function writes the XML prologue
#
# Function takes: No arguments
#
# Function Returns: No results
#
# Function Uses: _iCurrentNode
#
# Notes: This must be run as the first thing after setting up _iCurrentNode
#################################################################################

sub _XMLPrologue()
    {
    my $self = shift;

    my $xmlDoc = $self->_iCurrentNode;

    $xmlDoc -> setXMLDecl( $xmlDoc->createXMLDecl("1.0", undef, undef) );
    $xmlDoc -> setDoctype( $xmlDoc->createDocumentType( "cshproj", "SYSTEM", "file:///".main::KEpocToolsRoot()."/cshlpcmp/dtd/CSHproj.dtd" ) );
    $xmlDoc -> appendChild( new XML::DOM::ProcessingInstruction( $xmlDoc, "xml:stylesheet", 'href="file:///'.main::KEpocToolsRoot().'/cshlpcmp/xsl/CSHproj.xsl" title="CS-Help project" type="text/xsl"' ) );
    }

################################################################################
#
# Object CParamPermissions
#
################################################################################
#
# Modification history
#
# version 001 - Initial version
#
################################################################################

package CParamPermissions;

# Standard libraries
use Carp;
use strict;

# Constants

# Globals

################################################################################
#
# Function New
#
# Function creates a new CParamPermissions
#
# Function takes: Two booleans; can the parameter take a list, and is the
#                 parameter required
#
# Function Returns: The new CParamPermissions object
#
# Function Uses:
#
# Notes:
#################################################################################

sub New($$)
    {
    my $templ = shift;
    my ($aListable, $aRequired) = @_;
    my $class = ref($templ) || $templ;

    # Create our object
    my $self = {};
    bless($self, $class);

    # Load values
    $self->_iListable($aListable);
    $self->_iRequired($aRequired);

    # Return our object
    return $self;
    }

################################################################################
#
# Function Private member data
#
# Functions _iListable, _iRequired
#
# Function takes: (optional) a value to set to
#
# Function Returns: The (new) value of the data
#
# Function Uses:
#
# Notes: Use without a parameter for get, with for set.
#################################################################################

sub _iListable
    {
    my $self = shift;

    return $self -> _GetSet('LISTABLE',@_);
    }

sub _iRequired
    {
    my $self = shift;
    
    return $self -> _GetSet('REQUIRED',@_);
    }

sub _GetSet
    {
    my $self = shift;
    my $var = shift;

    if (@_)
	{
	$self -> {$var} = shift;
	}

    return $self -> {$var};
    }

################################################################################
#
# Function IsListTaker
#
# Function determines whether the parameter can take a list or not
#
# Function takes: No arguments
#
# Function Returns: 1 if it can take a list, 0 if it can only take a single item
#
# Function Uses:
#
# Notes:
#################################################################################

sub IsListTaker()
    {
    my $self = shift;

    if ($self->_iListable)
	{ return 1; }
    else
	{ return 0; }
    }

################################################################################
#
# Function IsRequired
#
# Function determines whether the parameter in question is mandatory
#
# Function takes: No arguments
#
# Function Returns: 1 if it is required, 0 if it is optional
#
# Function Uses:
#
# Notes:
#################################################################################

sub IsRequired()
    {
    my $self = shift;
    
    if ($self->_iRequired)
	{ return 1; }
    else
	{ return 0; }
    }

################################################################################
#
# Function PRINT
#
# Function prints the contents of the object
#
# Function takes: No arguments
#
# Function Returns: No results
#
# Function Uses: Nothing
#
# Notes:
#################################################################################

sub PRINT
    {
    my $self = shift;
    
    my $required;
    my $listable;

    if ($self->IsRequired)
        { $required = 'required'; }
    else
	{ $required = 'optional'; }

    if ($self->IsListTaker)
	{ $listable = 'can'; }
    else
	{ $listable = 'cannot'; }

    print STDOUT "Parameter is $required and $listable take a list\n";
    }

################################################################################
#
# Function TEST
#
# Function tests the operation of the class
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

    for ( my $req=0; $req<=1; $req++ )
	{
	for ( my $list=0; $list<=1; $list++ )
	    {
            my $test = New CParamPermissions($list,$req);
            if
	      ( ($test->IsListTaker)^$list
	      ||($test->IsRequired)^$req
	      )
	        { print STDERR "$list,$req test FAILED!\n"; }
            else
	        { print STDERR "$list,$req test passed\n"; }
            $test->PRINT;
            undef $test;
	    }
	}
    }
1;
