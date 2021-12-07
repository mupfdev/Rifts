#!perl
###############################################################################
#
# module: alp2csh.pm
#
# module implements perl object CAlp2CshConverter
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved
#
# Date Thu Dec 16 10:45:54 1999
#
###############################################################################
#
#
# Modification history
#
# version 001 - Initial version
#
###############################################################################

package CAlp2CshConverter;

use custfile;
use projfile;

# Standard libraries
use Carp;
use strict;

# Constants

# Globals

###############################################################################
#
# Function New
#
# Function creates a new CAlp2CspConverter object
#
# Function takes: No arguments
#
# Function Returns: The new object
#
# Function Uses: Nothing
#
# Notes:
###############################################################################

sub New()
	{
	my $templ = shift;
	my $class = ref($templ) || $templ;

	# Create our object
	my $self = {};

	# Initialise it
	bless($self, $class);
	$self->_iLog(New CLog);

	# Return it
	return $self;
	}

###############################################################################
#
# Function Private member data
#
# Function _iLog
#
# Function takes: (optional) a value to set to
#
# Function Returns: the (new) value stored
#
# Function Uses: Nothing
#
# Notes:
###############################################################################

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

###############################################################################
#
# Function Convert
#
# Function converts a Aleppo project to CSHelp project
#
# Function takes: The project filename
#
# Function Returns: No results
#
# Function Uses: CHelpProjectFile, CHelpCustomisationFile
#
# Notes: Converter will error if it finds any XML files as the project file,
#        customisation file, order file, output file or source files.
#        Output project file and customisation file are the original filename
#        with .xml appended.
###############################################################################

sub Convert($)
	{
	my $self = shift;
	my ($aFilename) = @_;

	if (CheckForXML($aFilename)) {$self->_iLog->LogDie("alp2csp will not process XML files")};
	my $dest = $aFilename.'.xml';

	my $projfile = New CHelpProjectFile;

	$projfile->LoadAleppoFile($aFilename);

	if
	  ( ( CheckForXML($projfile->GetMultiple('outputfile')) )
	  ||( CheckForXML($projfile->GetMultiple('orderfile')) )
	  ||( CheckForXML($projfile->GetMultiple('customizationfile')) )
	  ||( CheckForXML($projfile->GetMultiple('sourcefile')) )
	  )
		{
		$self->_iLog->LogDie("alp2csp will not process projects containing XML files");
		}

	if (!$projfile->IsUnset('customizationfile'))
		{
		my $custFilename = $projfile->Get('customizationfile');

		my $custfile = New CHelpCustomisationFile;

		$custfile->LoadAleppoFile($custFilename);
    
		$custFilename = $custFilename.".xml";

		$custfile->SaveCSHelpFile($custFilename);

		$projfile->Set('customizationfile',$custFilename);
		}

	$projfile->SaveCSHelpFile($dest);
	}

###############################################################################
#
# Function CheckForXML
#
# Function finds whether any filenames end in .xml
#
# Function takes: Either a scalar value, or a reference to a list of scalar values.
#
# Function Returns: 1 if .xml was found, 0 if not
#
# Notes:
###############################################################################

sub CheckForXML(@)
	{
	my (@file) = @_;

	foreach my $name (@file)
		{
		if (lc($name) =~ /.xml$/)
			{ return 1; }
		}

	return 0;
	}
1;
