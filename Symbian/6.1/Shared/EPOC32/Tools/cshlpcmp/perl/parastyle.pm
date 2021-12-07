#!perl
################################################################################
#
# module: parastyle.pm
#
# module implements the charstyle object
#
# Copyright (c) 2001 Symbian Ltd.	All rights reserved
#
# Date Jan 2001
#
################################################################################
package CParastyle;

use Carp;
use strict;

use devtools;
use log;
use XML::DOM;

################################################################################
#
# Function New
#
# Function creates a new parastyle object
#
# Function takes: the style name, font name, style, size, color, justification
# line spacing, before, after, left and right spacing, image ID and the
# leading text (as an asptml styled XML::DOM::DocumentFragment).
#
# Function Returns: the created object
#
# Function Uses:
#
# Notes: Style name is not retained; users of this class must keep their own
#        reference to the name.
################################################################################
sub New($$$$$$$$$$$)
	{
	my $proto = shift;
	my($aName, $aFont, $aStyle, $aSize, $aColour, $aJustify, $aSpacing, $aBefore, $aAfter, $aLeft, $aRight, $aImage, $aText) = @_;

	my $class = ref($proto) || $proto;

	my $self = {};
	bless($self, $class);
	$self->_iLog(New CLog());

	my $style = $aStyle;
	$style = "normal" if (!defined($style));
	my $colour = $aColour;
	$colour = "foreground" if (!defined($colour));
	my $justify = lc($aJustify) if (defined($aJustify));
	$justify = "left" if (!defined($justify));
	my $spacing = $aSpacing;
	$spacing = 0 if (!defined($spacing));
	$spacing += $aSize;
	my $before = $aBefore;
	$before = ($aSize / 2) if (!defined($before));
	$before = sprintf("%d",$before); # round to integer
	my $after = $aAfter;
	$after = 0 if (!defined($after));
	my $left = $aLeft;
	$left = 0 if (!defined($left));
	my $right = $aRight;
	$right = 0 if (!defined($right));

	if (!defined($aFont))
		{
		$self->_iLog->LogDie("In definition of style '$aName': Font name must be supplied ('font=')");
		}
	elsif (!defined($aSize))
		{
		$self->_iLog->LogDie("In definition of style '$aName': Font size must be supplied ('size=')");
		}
	else
		{
		$self->_iCharstyle(New CCharstyle($aName, $aFont, $style, $aSize, $colour));
		}

	$justify = "center" if ($justify eq "centre");
	
	if (($justify ne "left")
	  &&($justify ne "right")
	  &&($justify ne "center")
	  &&($justify ne "full"))
	  	{
		$self->_iLog->LogDie("In definition of style '$aName': '$justify' is not a valid justification type");
		}
		
	if ($spacing !~ /^[0-9]+$/) # must be in decimal
		{
		$self->_iLog->LogDie("In definition of style '$aName': '$spacing' is not a valid line spacing");
		}
	
	if ($before !~ /^[0-9]+$/) # must be in decimal
		{
		$self->_iLog->LogDie("In definition of style '$aName': '$before' is not a valid before paragraph spacing");
		}
	
	if ($after !~ /^[0-9]+$/) # must be in decimal
		{
		$self->_iLog->LogDie("In definition of style '$aName': '$after' is not a valid after paragraph spacing");
		}
		
	if ($left !~ /^[0-9]+$/) # must be in decimal
		{
		$self->_iLog->LogDie("In definition of style '$aName': '$left' is not a valid left spacing");
		}
		
	if ($right !~ /^[0-9]+$/) # must be in decimal
		{
		$self->_iLog->LogDie("In definition of style '$aName': '$right' is not a valid right spacing");
		}
	
	if (defined($aText) || defined($aImage))
		{
		if ( ($justify eq "right") || ($justify eq "center") )
			{
			$self->_iLog->LogDie("In definition of style '$aName': Styles with leading text or images must have left justification or full justification, not $justify.");
			}
		}
	
	$self->_iJustify($justify);
	$self->_iSpacing($spacing);
	$self->_iBefore($before);
	$self->_iAfter($after);
	$self->_iLeft($left);
	$self->_iRight($right);
	$self->_iImage($aImage);
	$self->_iText($aText);

	return $self;
	}

################################################################################
#
# Function DESTROY
#
# Function disposes of the text nodes to allow them to be garbage collected.
#
# Function takes:
#
# Function Returns:
#
# Function Uses:
#
# Notes:
################################################################################
sub DESTROY
	{
	my $self = shift;

	$self->_iText()->dispose();
	}
	
################################################################################
#
# Function _iLog _iCharstyle _iJustify _iSpacing _iBefore _iAfter _iLeft _iRight _iImage
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

sub _iCharstyle
	{
	my $self = shift;
	if (@_) { $self->{CHARSTYLE} = shift }
	return $self->{CHARSTYLE};
	}

sub _iJustify
	{
	my $self = shift;
	if (@_) { $self->{JUSTIFY} = shift }
	return $self->{JUSTIFY};
	}

sub _iSpacing
	{
	my $self = shift;
	if (@_) { $self->{SPACING} = shift }
	return $self->{SPACING};
	}

sub _iBefore
	{
	my $self = shift;
	if (@_) { $self->{BEFORE} = shift }
	return $self->{BEFORE};
	}

sub _iAfter
	{
	my $self = shift;
	if (@_) { $self->{AFTER} = shift }
	return $self->{AFTER};
	}

sub _iLeft
	{
	my $self = shift;
	if (@_) { $self->{LEFT} = shift }
	return $self->{LEFT};
	}

sub _iRight
	{
	my $self = shift;
	if (@_) { $self->{RIGHT} = shift }
	return $self->{RIGHT};
	}

sub _iImage
	{
	my $self = shift;
	if (@_) { $self->{IMAGE} = shift }
	return $self->{IMAGE};
	}

sub _iText
	{
	my $self = shift;
	if (@_) { $self->{TEXT} = shift }
	return $self->{TEXT};
	}

################################################################################
#
# Function ToCshlp
#
# Function creates a cshlp paragraph element of this style
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

	my $element = $dom->createElement("p");
	$self->AddAttributes($element);
	
	return $element;
	}
	
################################################################################
#
# Function AddAttributes
#
# Function adds style attributes to (e.g) a cshlp paragraph element
#
# Function takes: The element to style
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

	$self->_iCharstyle->AddAttributes($element);
	$element->setAttribute("justify", $self->_iJustify());
	$element->setAttribute("spacing", $self->_iSpacing());
	$element->setAttribute("before", $self->_iBefore());
	$element->setAttribute("after", $self->_iAfter());
	$element->setAttribute("left", $self->_iLeft());
	$element->setAttribute("right", $self->_iRight());

	if (defined($self->_iImage))
		{
		$element->setAttribute("mbmID", $self->_iImage());
		}

	if (defined($self->_iText))
		{
		my $dom = $element->getOwnerDocument();
		my $text = $self->_iText()->cloneNode(1);
		$text->setOwnerDocument($dom);
		my $leading = $dom->createElement("leading");
		$leading->appendChild($text);
		$element->appendChild($leading);
		}
	}
	
################################################################################
#
# Function Base
#
# Function modifies this style to base it on the supplied CParastyle
#
# Function takes: A CParastyle
#
# Function Returns: none
#
# Function Uses:
#
# Notes: For use with old-style effects (replaces everything except for the
#        left indent, image and text)
################################################################################

sub Base($)
	{
	my $self = shift;
	my ($basis) = @_;

	$self->_iCharstyle($basis->_iCharstyle()->Copy());
	$self->_iJustify($basis->_iJustify());
	$self->_iSpacing($basis->_iSpacing());
	$self->_iBefore($basis->_iBefore());
	$self->_iAfter($basis->_iAfter());
	$self->_iRight($basis->_iRight());
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

	$self->_iCharstyle()->PRINT();
	print "Align : ".$self->_iJustify().", Spacing : ".$self->_iSpacing().", Above : ".$self->_iBefore().", Below : ".$self->_iAfter().", Left : ".$self->_iLeft().", Right : ".$self->_iRight().", Image : ".$self->_iImage()."\n";
	}
	
sub TEST()
	{
	my $test = New CParastyle( "name", "font", "roman", "3", "0x123456", "right", "10", "11", "12", "13", "14", "image");
	$test->PRINT();
	$test = New CParastyle( "name", "font", undef, "3", undef, undef, undef, undef, undef, undef, undef, undef);
	$test->PRINT();
	}
1;
