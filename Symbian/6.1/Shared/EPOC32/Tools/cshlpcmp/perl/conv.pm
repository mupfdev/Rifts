#!perl
################################################################################
#
# module: conv.pm
#
# module implements the conversion object
#
# Copyright (c) 1997-1999 Symbian Ltd.	All rights reserved
#
# Date Wed Jun 28 11:46:21 1999
#
################################################################################
package CConverter;

use Carp;
use strict;

use devtools;
use log;

#objects
use rtffile;
use ptmlfile;
use csptmlfl;
use custfile;
use asptmlfl;
use cshlpfl;
 
################################################################################
#
# Function new
#
# Function creates a new rtf2Xml object
#
# Function takes: a reference to the project file
#
# Function Returns: the created object
#
# Function Uses:
#
# Notes:
#################################################################################
sub New ($)
	{
	my $proto = shift;
	my($aProjFile) = @_;

	my $class = ref($proto) || $proto;

	my $self  = {};
	bless($self, $class);

	#get a log object
	$self->_iLog(New CLog());

	$self->_iProjFile($aProjFile);
	return $self;
	}

################################################################################
#
# Function 
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

sub _iProjFile
	{
	my $self = shift;
	if (@_) { $self->{PROJFILE} = shift }
	return $self->{PROJFILE};
	}

################################################################################
#
# Function Convert
#
# Function Converts all the rtf source files to source xml files 
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub Convert()
	{
	my $self = shift;

	#convert all source rtf files to ptml
	$self->_RtfToPtml();

	#convert all the source ptml files to Csptml
	$self->_PtmlToCsptml();

	#convert all the source Csptml file to Asptml
	$self->_CsptmlToAsptml();

	#convert any customization file to CsHlp file
	my $custFile = $self->_CustToCsHlp;

	#convert all asptml files to a cshlp file
	$self->_AsptmlToCsHlp($custFile);

	#convert the the cshlp file to an epoc help file
	$self->_CsHlpToEPOCHelp
	
	}


################################################################################
#
# Function _RtfToPtml
#
# Function converts all the rtf source files in the project into ptml files.
# These files are located in the working directory 
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _RtfToPtml
	{
	my $self = shift;

	$self->_iLog->Log("Converting rtf files to .ptml.xml\n");

#convert all the source rtf files to -ptml.xml files
	for my $rtfFile (@{$self->_iProjFile->SourceFiles()})
		{

		#get the base file name
		my $rtfFileNoExt = ExtractFileNameNoExt($rtfFile);
		
		#construct a new rtfFile
		my $theRtfFile = New CRtfFile ($self->_iProjFile->InputDir.$rtfFile,
						   $self->_iProjFile->WorkingDir.$rtfFileNoExt.".ptml.xml");
		
		#convert
		$theRtfFile->ToPtml();

		#$theRtfFile->TEST();
		}
		
	}

################################################################################
#
# Function _PtmlToCsptml
#
# Function converts all the ptml source files in the project into csptml files.
# These files are located in the working directory 
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _PtmlToCsptml
	{
	my $self = shift;

	$self->_iLog->Log("Converting .ptml.xml files to .csptml.xml\n");

	#convert all the source -ptml.xml files to -csptml.xml
	for my $rtfFile (@{$self->_iProjFile->_iSourceFiles()})
		{

		#get the base file name
		my $rtfFileNoExt = ExtractFileNameNoExt($rtfFile);
		
		#construct a new ptmlFile object
		my $thePtmlFile = New CPtmlFile ($self->_iProjFile->WorkingDir.$rtfFileNoExt.".ptml.xml",
						   $self->_iProjFile->WorkingDir.$rtfFileNoExt.".csptml.xml");

		#convert
		$thePtmlFile->ToCsptml();

		#$thePtmlFile->TEST();
		}
		
	}

################################################################################
#
# Function _CSptmlToAsptml
#
# Function converts all the csptml source files in the project into asptml files.
# These files are located in the working directory 
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _CsptmlToAsptml
	{
	my $self = shift;

	$self->_iLog->Log("Converting .csptml.xml files to .asptml.xml\n");

	#convert all the source .csptml.xml files to .aptml.xml
	for my $rtfFile (@{$self->_iProjFile->SourceFiles()})
		{

		#get the base file name
		my $rtfFileNoExt = ExtractFileNameNoExt($rtfFile);
		
		#construct a new csptmlFile object
		my $theCsptmlFile = New CCsptmlFile ($self->_iProjFile->WorkingDir.$rtfFileNoExt.".csptml.xml",
						   $self->_iProjFile->WorkingDir.$rtfFileNoExt.".asptml.xml",
						   $self->_iProjFile->GraphicDir);

		#convert
		$theCsptmlFile->ToAsptml;

		#$theCsptmlFile->TEST();
		#$theCsptmlFile->PRINT();
		}
		
	}

################################################################################
#
# Function _CustToCsHlp
#
# Function prepares the customization file for the project.
#
# Function takes: none
#
# Function Returns: The CCustFile object (containing style definitions and
#                   a cshlp DOM)
#
# Function Uses:
#
# Notes:
################################################################################
sub _CustToCsHlp
	{
	my $self = shift;

	$self->_iLog->Log("Converting .cust.xml file to .cshlp.xml\n");

	#construct a new CCustFile object
	my $theCustFile = New CCustFile ($self->_iProjFile->CustomizationFile,$self->_iProjFile->HelpFileUID,$self->_iProjFile->GraphicDir);
	return $theCustFile;
	}
		
################################################################################
#
# Function _AsptmlToCsHlp
#
# Function converts all the asptml source files in the project into a single CsHlp.
# These files are located in the working directory 
#
# Function takes: The CCustFile object for the custiomization file
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _AsptmlToCsHlp($)
	{
	my $self = shift;

	my ($aCustFile) = @_;

	$self->_iLog->Log("Converting .asptml.xml files to .cshlp.xml\n");
	# get the output FileName
	my $outputFile = $self->_iProjFile->WorkingDir.ExtractFileNameNoExt($self->_iProjFile->DestFile).".cshlp.xml";
	
	#check if the output file exists
	if(-e $outputFile)
		{
		#delete the output
		if(!unlink($outputFile))
				{
				$self->_iLog->LogDie("Sorry: I cannot delete $outputFile. Please check that it is not read only or inuse.\n");
				}
		}

	#construct a new asptmlFile object
	my $theAsptmlFiles = New CAsptmlFile(
	  $outputFile, $self->_iProjFile->HelpFileUID, $aCustFile, $self->_iProjFile->_iGraphicDir);

	#convert all the source .asptml.xml files to .cshlp.xml

	for my $xmlFile (@{$self->_iProjFile->XmlFiles()})
		{
		$theAsptmlFiles->LoadAsptml($self->_iProjFile->InputDir.$xmlFile);
		}

	for my $rtfFile (@{$self->_iProjFile->SourceFiles()})
		{

		#get the base file name
		my $rtfFileNoExt = ExtractFileNameNoExt($rtfFile);

		# Load + convert
		$theAsptmlFiles->LoadAsptml($self->_iProjFile->WorkingDir.$rtfFileNoExt.".asptml.xml");

		#$theAsptmlFile->TEST;
		#$theAsptmlFile->PRINT;
		}
	
	#write it out
	$theAsptmlFiles->ToCsHlp;
	}


################################################################################
#
# Function _CsHlpToEPOCHelp
#
# Function converts the cshlp file into an EPOC help file.
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _CsHlpToEPOCHelp
	{
	my $self = shift;

	$self->_iLog->Log("Converting cshlp file to EPOCHelp file\n");
	
	my $inputFile = $self->_iProjFile->WorkingDir.ExtractFileNameNoExt($self->_iProjFile->DestFile).".cshlp.xml";

	#get the output file name
	my $outputFile = $self->_iProjFile->OutputDir.$self->_iProjFile->DestFile;

#get the header file name without an extension
	my $headerFiles = $self->_iProjFile->HeadersDir.$self->_iProjFile->DestFile;
		
	#construct a new CCsHlpFile
	my $theCsHlp = New CCsHlpFile ($inputFile,$outputFile,$headerFiles);

	#convert
	$theCsHlp->ToEPOCHelp();
	
	}

################################################################################
#
# Function TEST
#
# Function the test code for the converter object
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

	#this should probably call each of the tests on each of the convertors
	
	$self->PRINT;
	}

################################################################################
#
# Function PRINT
#
# Function prints out the current contents of the projfile object
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

	# nothing really to print
	}


1;

















