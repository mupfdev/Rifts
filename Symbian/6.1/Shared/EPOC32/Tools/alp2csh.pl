#!perl
################################################################################
#
# Program: alp2csh.pl
#
# Program
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved
#
#
use constant VERSION => "version 002";
#
use constant PROGHELP => "
alp2csh.pl ".VERSION."
alp2csh <.alp project file> [-lf:<logfile>]

The program is passed the name of the aleppo file to process, and optionally a
log file to write output to.
";
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved
#
# Date Wed Nov 10 10:37 1999
#
################################################################################

# Set up libraries for the current directory and others on this drive
use FindBin;
use lib $FindBin::Bin."/perllib","$FindBin::Bin";
use lib $FindBin::Bin."/alp2csh/perl";

use Args;
use strict;
use log;
use projfile;
use alp2csh;

use constant KEpocToolsRoot => $FindBin::Bin;
Main();

sub Main
    {
    my $CliCracker;

    # Create our CLI cracker, and give it the error subroutine

    $CliCracker = CArgs -> New( \&CliError );

    # Specify the command line to crack

    $CliCracker -> AddArgsSpec
      ("source",undef,"^(?![-/]lf:)(.*)\$",[],1,0); # Find something not beginning with '-lf:'
    $CliCracker -> AddArgsSpec
      ("log",undef,"^[-/]lf:(.*)\$",[],0,0);

    # Get the parameters
    
    my $parameters = $CliCracker -> ParseCommandLine(\@ARGV);

    my $source = $parameters->ParamItem("source")->Value()."\n";

    chomp($source);

    my $logfile = $parameters->ParamItem("log")->Value();
    my $log = New CLog( $logfile );

    my $converter = New CAlp2CshConverter;

    $converter->Convert($source);
    }

sub CliError()
    {
    my $log = New CLog();
    
    $log->Log(PROGHELP);
    $log->LogDie("Invalid parameters - program terminating");
    }






