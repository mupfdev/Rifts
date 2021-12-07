#!perl
################################################################################
#
# module: charstyle.pm
#
# module implements the charstyle object
#
# Copyright (c) 2001 Symbian Ltd.	All rights reserved
#
# Date Jan 2001
#
################################################################################
package CCharstyle;

use Carp;
use strict;

use devtools;
use log;

################################################################################
#
# Function New
#
# Function creates a new charstyle object
#
# Function takes: the style name, font name, style, size and color
#
# Function Returns: the created object
#
# Function Uses:
#
# Notes: Style name is not retained; users of this class must keep their own
#        reference to the name.
################################################################################
sub New($$$$$)
	{
	my $proto = shift;
	my($aName, $aFont, $aStyle, $aSize, $aColour) = @_;

	my $class = ref($proto) || $proto;

	my $self = {};
	bless($self, $class);
	$self->_iLog(New CLog());

	my ($style, $colour);
	
	$style=lc($aStyle) if defined($aStyle);
	
	if ($style eq "roman")
		{
		$style="normal";
		}
	else
		{
		if( ($style ne "normal")
		  &&($style ne "bold")
		  &&($style ne "italic")
		  &&($style ne "bolditalic")
		  &&(defined($style))
		  )
			{
			$self->_iLog->LogDie("In definition of style '$aName': '$aStyle' is not a valid font style");
			}
		}

	$colour = lc($aColour) if defined($aColour);
	if (($colour ne "foreground") && ($colour ne "background") && defined($colour))
		{
		$colour = oct($colour) if $colour =~ /^0/; #convert to base n to decimal

		if ($colour !~ /^[0-9]+$/) # if it still isn't in decimal
			{
			$self->_iLog->LogDie("In definition of style '$aName': '$aColour' is not a valid color (use 'foreground', 'background' or '0x...')");
			}
		}
		
	if (($aSize !~ /^[0-9]+$/) && (defined($aSize))) # must be in decimal or undef
		{
		$self->_iLog->LogDie("In definition of style '$aName': '$aSize' is not a valid font size");
		}
	
	$self->_iFont($aFont);
	$self->_iStyle($style);
	$self->_iSize($aSize);
	$self->_iColour($colour);

	return $self;
	}

################################################################################
#
# Function _iLog _iFont _iStyle _iSize _iColour
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

sub _iFont
	{
	my $self = shift;
	if (@_) { $self->{FONT} = shift }
	return $self->{FONT};
	}

sub _iStyle
	{
	my $self = shift;
	if (@_) { $self->{STYLE} = shift }
	return $self->{STYLE};
	}

sub _iSize
	{
	my $self = shift;
	if (@_) { $self->{SIZE} = shift }
	return $self->{SIZE};
	}

sub _iColour
	{
	my $self = shift;
	if (@_) { $self->{COLOUR} = shift }
	return $self->{COLOUR};
	}

################################################################################
#
# Function ToCshlp
#
# Function creates a cshlp character style element of this style
#
# Function takes: The XML::DOM::Document to base the element in
#
# Function Returns: the created element
#
# Function Uses: XML::DOM
#
# Notes: 
################################################################################

sub ToCshlp($)
	{
	my $self = shift;
	my ($dom) = @_;

	my $element = $dom->createElement("cs");
	$self->AddAttributes($element);

	return $element;
	}
	
################################################################################
#
# Function AddAttributes
#
# Function sets cshlp character style attributes of this style
#
# Function takes: The XML::DOM::Element to set the attributes on
#
# Function Returns: None
#
# Function Uses: XML::DOM
#
# Notes: 
################################################################################

sub AddAttributes($)
	{
	my $self = shift;
	my ($element) = @_;

	$element->setAttribute("font", $self->_iFont());
	$element->setAttribute("style", $self->_iStyle());
	$element->setAttribute("size", $self->_iSize());
	$element->setAttribute("color", $self->_iColour());
	}

################################################################################
#
# Function Copy
#
# Function copy constructor
#
# Function takes: none
#
# Function Returns: The new CCharstyle
#
# Function Uses:
#
# Notes: 
################################################################################

sub Copy($)
	{
	my $self = shift;

	return New CCharstyle("copy", $self->_iFont(), $self->_iStyle(), $self->_iSize(), $self->_iColour());
	}
	
################################################################################
#
# Functions PRINT, TEST
#
# Functions print status of the object, and test functionality respectively
#
# Functions take: None
#
# Functions return: None
#
# Notes: 
################################################################################

sub PRINT()
	{
	my $self = shift;
	print STDOUT "Font: ".$self->_iFont().", Style: ".$self->_iStyle().", Size: ".$self->_iSize().", Colour: ".$self->_iColour()."\n";
	}
	
sub TEST()
	{
	my $test = New CCharstyle("name", "font", "bold", "12", "foreground");
	$test->PRINT();
	$test = New CCharstyle("name", undef, undef, undef, undef);
	print STDOUT "Successfully tested minimal style\n";
	}
1;
