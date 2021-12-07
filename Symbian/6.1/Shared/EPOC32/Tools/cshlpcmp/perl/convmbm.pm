#!perl
################################################################################
#
# Module: convmbm.pm
#
# Module implements perl object CConvMbm
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved
#
# Date Tue Sep 28 12:00:00 1999
#
################################################################################
package CConvMbm;

# use libraries
use Carp;
use strict;
use devtools;
use log; 
################################################################################
#
# Function New
#
# Function creates a new perl object of type ConvMbm
#
# Function Takes   : Full path/filename of an MBM file
#
# Function Returns : The created object
#
# Function Uses    :
#
# Notes:
#
################################################################################
sub New ($)
    {
    my $proto = shift;

    my ($aMbmPathAndName) = @_;
    
    my $class = ref($proto) || $proto;
    
    my $self  = {};
    bless($self, $class);
    $self->_iLog(New CLog());
    $self->_iMbmPathAndName($aMbmPathAndName);
    
    return $self;
    }


###############################################################################
#
# Function _iLog _iMbmPathAndName
#
# Function to access the data of the given object
#
# Function takes   : The filepath-name of an mbm file or nothing
#
# Function Returns : The value of the member data
#
# Function Uses    :
#
# Notes: This function combines the traditional getter setter functions
#        If there is an argument the member data is set to that value
#
###############################################################################
sub _iLog
    {
    my $self = shift;

    if (@_)
    	{
    	$self->{LOG} = shift;
    	}

    return $self->{LOG};
    }

sub _iMbmPathAndName
    {
    my $self = shift;

    if (@_)
    	{
    	$self->{MBMPATHANDNAME} = shift;
    	}

    return $self->{MBMPATHANDNAME};
    }


################################################################################
#
# Function Convert
#
# Function to convert MBM files to JPG
#
# Function Takes   : Nothing
#
# Function Returns : Nothing
#
# Function Uses    :
#
# Notes: Assumes that both Bmconv and cjpeg are in the current path 
# 
################################################################################
sub Convert
    {
    my $self = shift;

    my $mbmPathAndName = $self->_iMbmPathAndName;
    my $mbmPath = ExtractPath ($mbmPathAndName);

    # Do some existance checks on the mbm filepath and name
    if (! -e $mbmPathAndName)
		{
     		$self->_iLog->LogDie("Sorry could not find $mbmPathAndName");
		}
    
    # Obtain a temporary filename and create a jpg filename
    my $tmpBmpFile = TempFilename($mbmPath);
    my $newJpgFile = ExtractPathNoExt ($mbmPathAndName) . '.jpg';
	
    # First create an intermediate bmp from the mbm
    system ("bmconv /u \"$mbmPathAndName\" \"$tmpBmpFile\"");

    # Now create a jpg from the bmp
    system ("cjpeg \"$tmpBmpFile\" \"$newJpgFile\"");

    # Finally, delete the intermediate bmp
    unlink ("$tmpBmpFile");
    }

################################################################################
#
# Function TEST
#
# Function the test code for the object
#
# Function Takes   : Nothing
#
# Function Returns : Nothing
#
# Function Uses    :
#
# Notes:
#
################################################################################
sub TEST
    {
    my $self = shift;

    $self->_iLog->Log(" Test 1 - Store a mbm filename (given when created) and display it\n");
    $self->_iLog_>Log("Retrieving Data");
    $self->PRINT();
	
    $self->_iLog->Log("Test 2 - Conversion of the mbm to a jpeg");
    $self->_iLog->Log("Retrieving Data");
    $self->PRINT();
    $self->_iLog->Log("Converting File");
    $self->Convert();
    
    $self->_iLog->Log("Test 3 - Attempted conversion when mbm filepath-name absent or invalid");
    $self->_iLog->Log("Setting Data");
    $self->_iMbmPathAndName('');
    $self->_iLog->Log("Retrieving Data");
    $self->PRINT();
    $self->Convert();
    }

################################################################################
#
# Function PRINT
#
# Function prints out the current contents of the object
#
# Function takes   : Nothing
#
# Function Returns : Nothing
#
# Function Uses    :
#
# Notes: 
#
################################################################################
sub PRINT
    {
    my $self = shift;
    
    $self->_iLog->Log("FilePathAndName | " . $self->_iMbmPathAndName());
    }
1;


