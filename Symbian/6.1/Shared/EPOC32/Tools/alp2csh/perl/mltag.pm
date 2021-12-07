#!perl
################################################################################
#
# module: MLtag.pm
#
# module implements perl object CMarkupTag
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved
#
# Date Tue Dec 14 17:12:59 1999
#
################################################################################
#
# Modification history
#
# version 001 - Initial version
#
# Version 002 - Corrected 'sub New' parameter declaration
#
################################################################################

# Standard libraries
use Carp;
use strict;
use log;

# Constants

# Globals

package CMarkupTag;

################################################################################
#
# Function New
#
# Function creates a new CMarkupTag object
#
# Function takes: The tag name, and whether the tag is an end tag (1) or not (0)
#
# Function Returns: The new CMarkupTag object
#
# Function Uses: Nothing
#
# Notes:
#################################################################################

sub New($$)
    {
    my $templ = shift;
    my $class = ref($templ) || $templ;
    my ($aName, $aIsEndTag) = @_;

    # Create class
    my $self = {};
    bless( $self, $class );

    # Initialise
    $self->_iLog( New CLog );
    $self->_iName( $aName );
    $self->_iIsEndTag( $aIsEndTag );
    $self->_iAttName( [] );
    $self->_iAttValue( [] );

    # Return
    return $self;
    }

################################################################################
#
# Function Private member data
#
# Functions _iIsEndTag _iName, _iAttName, _iAttValue
#
# Function takes: (optional) the value to set to
#
# Function Returns: The (new) value of the data
#
# Function Uses: Nothing
#
# Notes: Use with the parameter as a Set function, without as a Get function.
#################################################################################

sub _iIsEndTag
    {
    my $self = shift;
    return $self->_GetSet('ISENDTAG',@_);
    }

sub _iName
    {
    my $self = shift;
    return $self->_GetSet('NAME',@_);
    }

sub _iAttName
    {
    my $self = shift;
    return $self->_GetSet('ATTNAME',@_);
    }

sub _iAttValue
    {
    my $self = shift;
    return $self->_GetSet('ATTVALUE',@_);
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
	$self->{$var} = shift;
	}
    return $self->{$var};
    }

################################################################################
#
# Function AddAttribute
#
# Function adds an argument name, value pair
#
# Function takes: The argument name, and value
#
# Function Returns: No results
#
# Function Uses: Nothing
#
# Notes:
#################################################################################

sub AddAttribute($$)
    {
    my $self = shift;
    my ($aName, $aValue) = @_;

    $aName =~ tr/[A-Z]/[a-z]/;
    push @{$self->_iAttName}, $aName;
    push @{$self->_iAttValue}, $aValue;
    }

################################################################################
#
# Function GetName
#
# Function finds the name of the tag
#
# Function takes: No parameters
#
# Function Returns: The name of the tag
#
# Function Uses: Nothing
#
# Notes:
#################################################################################

sub GetName()
    {
    my $self = shift;
    return $self->_iName;
    }

################################################################################
#
# Function IsEndTag
#
# Function finds whether the tag is an end tag or not
#
# Function takes: No parameters
#
# Function Returns: 1 if it is an end tag, 0 if not
#
# Function Uses: Nothing
#
# Notes:
#################################################################################

sub IsEndTag()
    {
    my $self = shift;
    if ($self->_iIsEndTag)
	{ return 1; }
    else
	{ return 0; }
    }

################################################################################
#
# Function GetNumAttribs
#
# Function finds the number of attributes stored in the tag
#
# Function takes: No parameters
#
# Function Returns: The number of attributes
#
# Function Uses: Nothing
#
# Notes:
#################################################################################

sub GetNumAttribs()
    {
    my $self = shift;

    return scalar(@{$self->_iAttName});
    }

################################################################################
#
# Function GetAttribName
#
# Function finds the name of the attribute
#
# Function takes: The index of the attribute (1...NumAttribss)
#
# Function Returns: The name
#
# Function Uses: Nothing
#
# Notes:
#################################################################################

sub GetAttribName($)
    {
    my $self=shift;
    my ($index)=@_;

    return $self->_iAttName->[$index-1];
    }

################################################################################
#
# Function GetAttribValue
#
# Function finds the value of the attribute
#
# Function takes: The index of the attribute (1...NumAttribs)
#
# Function Returns: The value
#
# Function Uses: Nothing
#
# Notes:
#################################################################################

sub GetAttribValue($)
    {
    my $self=shift;
    my ($index)=@_;

    return $self->_iAttValue->[$index-1];
    }

################################################################################
#
# Function IsAttrib
#
# Function finds whether the attribute named exists in this tag
#
# Function takes: The name of the attribute
#
# Function Returns: 1 if found, 0 if not
#
# Function Uses: Nothing
#
# Notes:
#################################################################################

sub IsAttrib($)
    {
    my $self = shift;
    my ($aName) = @_;
    $aName =~ tr/[A-Z]/[a-z]/;

    for (my $i=1; $i<=$self->GetNumAttribs; $i++)
	{
	if ($self->GetAttribName($i) eq $aName)
	    {
	    return 1;
	    }
	}
    return 0;
    }

################################################################################
#
# Function PRINT
#
# Function prints the contents of the tag (object)
#
# Function takes: No parameters
#
# Function Returns: No results
#
# Function Uses: Nothing
#
# Notes:
#################################################################################

sub PRINT()
    {
    my $self = shift;
    my $message = "";

    if ($self->IsEndTag)
	{ $message="EndTag - "; }

    $message = $message."Name:".$self->GetName;

    for (my $i=1; $i<=$self->GetNumAttribs; $i++)
	{
	$message = $message."...".$self->GetAttribName($i)."->".$self->GetAttribValue($i);
	}
    $self->_iLog->Log($message);
    }

################################################################################
#
# Function TEST
#
# Function tests the classes operation
#
# Function takes: No parameters
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

    my $test = New CMarkupTag("Tag ending",1);

    $test->AddAttribute("This tag","No more");
    $test->AddAttribute("Health","Not breathing");
    $test->AddAttribute("Status","Just resting");
    $test->AddAttribute("Class","Norweigan Blue");

    $test->PRINT;

    undef $test;

    my $test = New CMarkupTag("test name",0);

    $test->AddAttribute("argument","value");
    $test->AddAttribute("time","five minute");
    $test->AddAttribute("time","full half hour");
    $test->AddAttribute("Me","Not here");
    $test->AddAttribute("Purpose","An argument");
    $test->AddAttribute("Agreement","Negative");

    $test->PRINT;

    if ($test->IsAttrib("Me") && $test->IsAttrib("PuRpOsE")
       && $test->IsAttrib("agreement") && $test->IsAttrib("ARGUMENT") )
	{ $self->_iLog->Log("Attrib test 1 passed"); }
    else
	{ $self->_iLog->Log("Attrib test 1 FAILED"); }

    if ($test->IsAttrib("TIME") )
	{ $self->_iLog->Log("Attrib test 2 passed"); }
    else
	{ $self->_iLog->Log("Attrib test 2 FAILED"); }
    }

1;
