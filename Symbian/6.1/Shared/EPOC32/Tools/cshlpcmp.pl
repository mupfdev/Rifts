#!perl
################################################################################
#
# Program: cshlpcmp 
#
# Program is the supervisor for the conversion of a set of rtf source files 
# through to a single epoc CS-Help file
#
#Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved
#
#
use 5.00503;

use constant KVersion => "Version 010";
#
use constant KProgHelp => "
\ncshlpcmp ".KVersion."
\ncshlpcmp projectfile [-lflogfile]
where
\tprojectfile is the name of the cshlpcmp project file.
\tThe file extension must be given.
\tlogfile is the name of an optional log file

If no arguments are given this help is displayed

This software is based in part on the work of the
Independent JPEG Group.
";
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved
#
# Date Tue Jun 22 16:13:31 1999
#
################################################################################
#
# Modification history
#
################################################################################

#add the local library path to the global one
use FindBin;
use lib $FindBin::Bin."\\perllib","$FindBin::Bin\\cshlpcmp\\perl";

#Standard libraries
use Carp;
use strict;

#use the DOM xml module
use XML::DOM;

# use the devtools library
use devtools;

#objects
use ProjFile;
use args;
use params;
use Conv; #rtf2Xml converter

# global reference to the commandline parameters
$main::params=undef;

#constants
use constant KPathRegExp => "([a-zA-Z]:)?[\\w\\\\\\.-~ ]+";
use constant KProjFilePattern => "^([^-]".KPathRegExp.")\$";
use constant KLogFilePattern => "-lf(".KPathRegExp.")\$";

#start the main function
main();

################################################################################
#
# Function main
#
# Function the main function
#
# Function takes: nothing
#
# Function Returns: nothing
#
# Function Uses:
#
# Notes:
#################################################################################
#
# Modification history
#
################################################################################
sub main
    {

    # Initilise cshlpcmp
    Initilise();

    my $projectFile = New CProjFile;

    $projectFile->Parse($main::params->ParamItem("projectfile")->Value());

    #create the converter object
    my $converter = New CConverter($projectFile);

    $converter->Convert();
    }

################################################################################
#
# Function Initilise
#
# Function initlises the cshlpcmp application, cracks the command line
# sets up the log object and gets from the environment the locations of the
# dtd and xsl files
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub Initilise
    {
    # set up the arguments
    my $args = New CArgs(\&DisplayHelp);

    # sepecify the arguments accepted
    #projfile the filename no exclusions manditory and non repeatable
    $args->AddArgsSpec("projectfile","",KProjFilePattern,[],1,0);

    # optional log file
    $args->AddArgsSpec("logfile","",KLogFilePattern,[],0,0);
    
    # parse the command line
    $main::params = $args->ParseCommandLine(\@ARGV);

    # if a log file was requested
    if($main::params->Exists("logFile"))
		{
		my $log = New CLog($main::params->ParamItem("logFile")->Value());
		}

	my $log = New CLog(); # So we can error in this function

    # add the location of the dtd and xsl files to the parameters
    AddDTDLocation();
    AddXSLLocation();

    # add the current version to the parameters
    $main::params->AddParamItem("Version",KVersion,0);    

    }

################################################################################
#
# Function AddDTDLocation
#
# Function adds the dtd location to the parameters
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses: the global params reference
#
# Notes:
#################################################################################
sub AddDTDLocation
    {
    # create a log object to report any errors
    my $log = New CLog();
    
    # get what is currently stored in the environment
    my $DTDLoc = $ENV{CSHLPDTD};

	# if the user has specified a CSHLPDTD, use that
	if ($DTDLoc ne "")
		{
		#remove any leading spaces
		$DTDLoc =~ s/^ +//g;
		#remove any trailing spaces
		$DTDLoc =~ s/ +$//g;
		#remove any trailing / or \
		$DTDLoc =~ s/[\/\\]$//g;
		}
	# otherwise, use the default
	else
		{
		$DTDLoc = $FindBin::Bin."/cshlpcmp/dtd";
		}
	# convert all \ to /
	$DTDLoc =~ s/\\/\//g;

    #check that the directory exists
	if (!(-d $DTDLoc))
		{
		$log->LogDie("Sorry but the directory \"$DTDLoc\" specified by
the CSHLPDTD environment setting is not a valid directory. Please set this to
the location of the cshlpcmp DTD files or unset it to use the default location.");
		}

    # add the dtd location to the parameters
    $main::params->AddParamItem("DTDLoc",$DTDLoc,0);
    }

################################################################################
#
# Function AddXSLLocation
#
# Function adds the xsl location to the parameters
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses: the global params reference
#
# Notes:
#################################################################################
sub AddXSLLocation
    {
    # create a log object to report any errors
    my $log = New CLog();
    
    # get what is currently stored in the environment
    my $XSLLoc = $ENV{CSHLPXSL};

	# if the user has specified a CSHLPXSL, use that
	if ($XSLLoc ne "")
		{
		#remove any trailing spaces
		$XSLLoc =~ s/ +$//g;
		#remove any leading spaces
		$XSLLoc =~ s/^ +//g;
		#remove any trailing / or \
		$XSLLoc =~ s/[\/\\]$//g;
		}
	# otherwise, use the default
	else
		{
		$XSLLoc = $FindBin::Bin."/cshlpcmp/xsl";
		}
	# convert all \ to /
	$XSLLoc =~ s/\\/\//g;

    #check that the directory exists
    if (!(-d $XSLLoc))
		{
		$log->LogDie("Sorry but the directory \"$XSLLoc\" specified by
the CSHLPXSL environment setting is not a valid directory. Please set this to
the location of the cshlpcmp XSL files or unset it to use the default location.");
		}

    # add the dtd location to the parameters
    $main::params->AddParamItem("XSLLoc",$XSLLoc,0);
    }

################################################################################
#
# Function DisplayHelp
#
# Function Prints out the command line help for cshlpcmp
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses: The global reference to the help text
#
# Notes: This function will be called if any of the commandline arguments
# do not corespond to the given argument specifications
#################################################################################
sub DisplayHelp
    {
    # create a new log for ouput
    my $log=New CLog();

    $log->Log(KProgHelp);
    exit;
    }































