#!perl
################################################################################
#
# module: rtffile.pm
#
# module implements the rtf file object
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved
#
# Date Wed Jun 28 11:46:21 1999
#
################################################################################
package CRtfFile;

use Carp;
use strict;

use devtools;
 
################################################################################
#
# Function New
#
# Function creates a new rtffile object
#
# Function takes: the path / file name of the source file and the path and file
# name of the destination file
#
# Function Returns: the created object
#
# Function Uses:
#
# Notes:
#################################################################################
sub New ($$)
    {
    my $proto = shift;
    my($aRtfFile,$aPtmlFile) = @_;

    my $class = ref($proto) || $proto;
    my $self  = {};
    bless($self, $class);

    $self->_iLog(New CLog());
    $self->_iRtfFile($aRtfFile);
    $self->_iPtmlFile($aPtmlFile);
    return $self;
    }

################################################################################
#
# Function _iLog _iRtfFile _iPtmlFile
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

sub _iRtfFile
    {
    my $self = shift;
    if (@_) { $self->{RTFFILE} = shift }
    return $self->{RTFFILE};
    }

sub _iPtmlFile
    {
    my $self = shift;
    if (@_) { $self->{PTMLFILE} = shift }
    return $self->{PTMLFILE};
    }

################################################################################
#
# Function ToPtml
#
# Function converts the rtf file to ptml
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub ToPtml
    {
    my $self = shift;

    #we re-extract path and filename information here as rtf2ptml has fixed filenames and paths
    my($inputDir)=ExtractPath($self->_iRtfFile);
    my($outputDir)=ExtractPath($self->_iPtmlFile);
    my($rtfFile)=ExtractFileNameNoExt($self->_iRtfFile);

    # call the rtf2ptml application to convert the rtf files to ptml
    $inputDir =~ s/([~\\\/])$/$1\//;
    $outputDir =~ s/([~\\\/])$/$1\//;
    my($command)="rtf2ptml \"-id".$inputDir."\" \"-od".$outputDir."\" \"-ox.ptml.xml\" \"-dtd".$self->_GetDTDUrl()."\" \"-xsl".$self->_GetXSLUrl()."\" \"".$rtfFile."\"";

    $self->_iLog->Log($command."\n");

    my $return=system($command);

    #check if rtf2ptml managed to run
    if($return != 0)
		{
		#check if we could execute rtf2ptml
		if($return == 256)
			    {
			    $self->_iLog->LogDie("Please check that rtf2ptml.exe is in the PATH\n");
			    }
		#some other error reported by rtf2ptml
		$self->_iLog->LogDie("Cshlpcmp Fatal Error");
		}

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
#################################################################################
sub _GetDTDUrl
    {
    my $self = shift;

    # check that the dtd and the xsl files for this file exists
    my $dtdUrl = $main::params->ParamItem("DTDLoc")->Value()."/ptml.dtd";

    if(! -e $dtdUrl)
		{
		$self->_iLog->LogDie("Sorry but the file $dtdUrl does not exist. Please check that if CSHLPDTD has been set in your environment, it has been set to the right location.");
		}

    # add the protocol to the url
    $dtdUrl = "file:///$dtdUrl";

    #return $dtdUrl; FIXME rtf2ptml is adding the dtd and xsl file names to the
    # ends of the given urls

    return "file:///".$main::params->ParamItem("DTDLoc")->Value()."/";
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
#################################################################################
sub _GetXSLUrl
    {
    my $self = shift;

    my $xslUrl = $main::params->ParamItem("XSLLoc")->Value()."/ptml.xsl";
    if(! -e $xslUrl)
		{
		$self->_iLog->LogDie("Sorry but the file $xslUrl does not exist. Please check that if CSHLPXSL has been set in your environment, it has been set to the right location.");
		}

    # add the protocol
    $xslUrl = "file:///$xslUrl";

    #return $xslUrl; FIXME rtf2ptml is adding the dtd and xsl file names to the
    # ends of the given urls

    return "file:///".$main::params->ParamItem("XSLLoc")->Value()."/";
    }

################################################################################
#
# Function TEST
#
# Function the test code for the rtf file object
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
    $self->_iRtfFile("the input rtf file");
    $self->_iPtmlFile("the output ptml file");

    $self->_iLog->Log("Recovering data");
    
    $self->PRINT;
    }

################################################################################
#
# Function PRINT
#
# Function prints out the current contents of the Rtffile object
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
    $self->_iLog->Log("the input rtf file | ". $self->_iRtfFile);
    $self->_iLog->Log("the output ptml file | ". $self->_iPtmlFile);
    }

1;

















