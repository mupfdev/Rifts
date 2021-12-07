#!perl
################################################################################
#
# module: strlist.pm
#
# module implements perl object CStringList
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved
#
# Date Mon Jan 09 16:59 1999
#
# Version 002
#
################################################################################
#
# Modification history
#
# version 001 - Initial version
#
# version 002 - Corrected some comments
#
################################################################################
package CStringList;

# Standard libraries
use Carp;
use strict;
use log;

# Constants

# Globals

################################################################################
#
# Function New
#
# Function creates a new CStringList object
#
# Function takes: No parameters
#
# Function Returns: The new CStringList object
#
# Function Uses: Nothing
#
# Notes:
#################################################################################

sub New()
    {
    my $templ = shift;
    my $class = ref($templ) || $templ;

    # Create object
    my $self = {};
    bless($self,$class);

    # Initialise object
    $self->SetUndef;
    $self->_iLog( New CLog );

    # Return object
    return $self;
    }

################################################################################
#
# Function Private member data
#
# Functions _iList _iLog
#
# Function takes: (Optionally) the value to set the data to
#
# Function Returns: The (new) value of the data
#
# Function Uses: Nothing
#
# Notes:
#################################################################################

sub _iList
    {
    my $self = shift;
    return $self->_iGetSet('LIST',@_);
    }

sub _iLog
    {
    my $self = shift;
    return $self->_iGetSet('LOG',@_);
    }

sub _iGetSet
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
# Function AddString
#
# Function adds a string to the string list
#
# Function takes: The string value
#
# Function Returns: No results
#
# Function Uses: Nothing
#
# Notes:
#################################################################################

sub AddString($)
    {
    my $self = shift;
    my ($aString) = @_;

    if (!ref($self->_iList))
	{
	$self->SetDef;
	}

    push @{$self->_iList}, $aString;
    }

################################################################################
#
# Function SetDef
#
# Function sets the string list to a defined empty list
#
# Function takes: No arguments
#
# Function Returns: No results
#
# Function Uses: Nothing
#
# Notes:
#################################################################################

sub SetDef()
    {
    my $self = shift;

    $self->_iList( [] );
    }

################################################################################
#
# Function SetUndef
#
# Function sets the string list to undef
#
# Function takes: No argument
#
# Function Returns: No results
#
# Function Uses: Nothing
#
# Notes:
#################################################################################

sub SetUndef()
    {
    my $self = shift;

    $self->_iList( "" );
    }

################################################################################
#
# Function IsUndef
#
# Function determines whether the string list is undefined or not
#
# Function takes: No arguments
#
# Function Returns: 1 if it is undef, 0 if not
#
# Function Uses: Nothing
#
# Notes:
#################################################################################

sub IsUndef()
    {
    my $self = shift;

    if ( ref($self->_iList) )
	{ return 0; }
    else
	{ return 1; }
    }

################################################################################
#
# Function GetNumItems
#
# Function finds the number of items in the list
#
# Function takes: No arguments
#
# Function Returns: The number of items (0 for undef or for empty list)
#
# Function Uses: Nothing
#
# Notes:
#################################################################################

sub GetNumItems
    {
    my $self = shift;

    my $numItems = 0;
    if (ref($self->_iList))
	{
	$numItems = scalar(@{$self->_iList});
	}
    return $numItems;
    }
    
################################################################################
#
# Function GetString
#
# Function gets the data of the list as a plain string
#
# Function takes: The string seperator to use (if we have more than one string)
#
# Function Returns: The string formed
#
# Function Uses: Nothing
#
# Notes: If you care the difference between undef and an empty string, test with
#        IsUndef first
#################################################################################

sub GetString($)
    {
    my $self = shift;
    my ($aListsep) = @_;

    my $string = "";

    if ( ref($self->_iList) )
	{
	$string = join($aListsep, @{$self->_iList});
	}

    return $string;
    }

################################################################################
#
# Function GetStringList
#
# Function gets the data as a perl list (array)
#
# Function takes: No arguments
#
# Function Returns: The list
#
# Function Uses: Nothing
#
# Notes: Returns an empty list for undef; if you care about the difference between
#        undef and an empty list, test with IsUndef first
#################################################################################

sub GetStringList()
    {
    my $self = shift;

    my $listRef = [];

    if ( ref($self->_iList) )
	{
	$listRef = $self->_iList;
	}

    return @$listRef;
    }

################################################################################
#
# Function PRINT
#
# Function prints the contents of the object
#
# Function takes: No arguments
#
# Function Returns: No arguments
#
# Function Uses:
#
# Notes:
#################################################################################

sub PRINT()
    {
    my $self = shift;

    if ($self->IsUndef)
        {
	$self->_iLog->Log( 'undefined' );
	}
    else
	{
	if ($self->GetNumItems == 0)
	    {
	    $self->_iLog->Log( '[]' );
	    }
	else
	    {
	    $self->_iLog->Log( '["'.$self->GetString('","').'"]' );
	    }
	}
    }

################################################################################
#
# Function TEST
#
# Function tests the operation of the class
#
# Function takes: No arguments
#
# Function Returns: No results
#
# Function Uses:
#
# Notes:
#################################################################################

sub TEST
    {
    my $self = shift;

    $self->SetUndef;

    my $numItems = $self->GetNumItems;
    my $test1 = !($self->IsUndef);
    my $test2 = ($numItems != 0);
    if ( $test1 || $test2 )
	{
	$self->_iLog->Log("SetUndef test FAILED!");
	
	if ( $test1 ^ $test2 )
	    {
	    if ($test1)
		{ $self->_iLog->Log("(IsUndef failed)"); }
	    else
		{ $self->_iLog->Log("(GetNumItems failed - $numItems)"); }
	    }
	}
    else
	{
	$self->_iLog->Log("SetUndef test passed");
	$self->PRINT;
	}

    $self->AddString("");

    $numItems = $self->GetNumItems;
    $test1 = ($self->IsUndef);
    $test2 = ($numItems != 1);
    if ( $test1 || $test2 )
	{
	$self->_iLog->Log("Add(Empty)String test FAILED!");
	
	if ( $test1 ^ $test2 )
	    {
	    if ($test1)
		{ $self->_iLog->Log("(IsUndef failed)"); }
	    else
		{ $self->_iLog->Log("(GetNumItems failed - $numItems)"); }
	    }
	}
    else
	{
	$self->_iLog->Log("Add(Empty)String test passed");
	$self->PRINT;
	}

    $self->SetUndef();

    $numItems = $self->GetNumItems;
    $test1 = !($self->IsUndef);
    $test2 = ($numItems != 0);
    if ( $test1 || $test2 )
	{
	$self->_iLog->Log("Re-SetUndef test FAILED!");
	
	if ( $test1 ^ $test2 )
	    {
	    if ($test1)
		{ $self->_iLog->Log("(IsUndef failed)"); }
	    else
		{ $self->_iLog->Log("(GetNumItems failed - $numItems)"); }
	    }
	}
    else
	{
	$self->_iLog->Log("Re-SetUndef test passed");
	$self->PRINT;
	}

    $self->SetDef;

    $numItems = $self->GetNumItems;
    $test1 = ($self->IsUndef);
    $test2 = ($numItems != 0);
    if ( $test1 || $test2 )
	{
	$self->_iLog->Log("SetDef test FAILED!");
	
	if ( $test1 ^ $test2 )
	    {
	    if ($test1)
		{ $self->_iLog->Log("(IsUndef failed)"); }
	    else
		{ $self->_iLog->Log("(GetNumItems failed - $numItems)"); }
	    }
	}
    else
	{
	$self->_iLog->Log("SetDef test passed");
	$self->PRINT;
	}

    for (my $i=0; $i<10; $i++)
	{
	$self->AddString("Item $i");
	}

    $numItems = $self->GetNumItems;
    $test1 = ($self->IsUndef);
    $test2 = ($numItems != 10);
    if ( $test1 || $test2 )
	{
	$self->_iLog->Log("AddString-10 test FAILED!");
	
	if ( $test1 ^ $test2 )
	    {
	    if ($test1)
		{ $self->_iLog->Log("(IsUndef failed)"); }
	    else
		{ $self->_iLog->Log("(GetNumItems failed - $numItems)"); }
	    }
	}
    else
	{
	$self->_iLog->Log("AddString-10 test passed");
	$self->PRINT;
	}

    for (my $i=10; $i<1000; $i++)
	{
	$self->AddString("Item $i");
	}

    $numItems = $self->GetNumItems;
    $test1 = ($self->IsUndef);
    $test2 = ($numItems != 1000);
    if ( $test1 || $test2 )
	{
	$self->_iLog->Log("AddString-1000 test FAILED!");
	
	if ( $test1 ^ $test2 )
	    {
	    if ($test1)
		{ $self->_iLog->Log("(IsUndef failed)"); }
	    else
		{ $self->_iLog->Log("(GetNumItems failed - $numItems)"); }
	    }
	}
    else
	{
	$self->_iLog->Log("AddString-1000 test passed");
	}

    my $passed = 1;

    for( my $i=0; $i<500; $i++)
	{
	my $val = int(rand(1000-0.01)); # Random number from 0-999

	if (($self->GetStringList)[$val] ne "Item $val")
	    {
	    $passed = 0;
	    }
	}

    if ($passed)
	{
	$self->_iLog->Log("GetStringList test passed");
	}
    else
	{
	$self->_iLog->Log("GetStringList test FAILED!");
	}
    }
1;
