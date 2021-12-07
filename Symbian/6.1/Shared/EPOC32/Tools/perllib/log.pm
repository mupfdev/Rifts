#!perl
################################################################################
#
# module: Log.pm
#
# module implements a logging object for perl. 
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved
#
# Date Wed Sep 27 11:49:34 1999
#
################################################################################
package CLog;
use lib "\\epoc32\\tools\\perllib";

use Carp;
use strict;
use FileHandle;

use devtools;

#class data for the CLog object
my $CLog ={};

################################################################################
#
# Function New
#
# Function creates a new CLog object. The Constructor takes two arguments
# the name of a file that messages should be written to and optionally
# a maxerror count (giving the number of errors to be logged before the program
# dies). If no filename is specified then the error messages are 
# logged to the screen only.  Otherwise a file is created and all logDie errors are
# logged to it.
#
# if New is called with no arguments the a log object is created that uses the
# the class values for logfile and maxerror count
#
# Function takes either one or two arguments 
#
# Function Returns: the created object
#
# Function Uses:
#
# Notes: 
#################################################################################
sub New($$)
    {
    my $class = shift;
    my ($aFileName, $aMaxError) = @_;
    my $self = {};	

    bless $self, $class;

    # if the filename is not defined then set it to ""
    if(!defined($self->_iFileName))
	   {
	   $self->_iFileName("");
	   }

    #only allow one error
    if(!defined($self->_iMaxError))
	{
	$self->_iMaxError(1);
	}

    #die immediately
    if(!defined($self->_iDieFlag))
       {
       $self->_iDieFlag(1);
       }

    #Don't print verbose messages
    if (!defined($self->_iVerbose))
	{
	$self->_iVerbose(0);
	}

    #If we've not been run before, we haven't errored yet
    if (!defined($self->_iHasErrored))
	{
	$self->_iHasErrored(0);
	}
    
    # if a filename was given then set iFileName to it
    if(defined($aFileName) && ($aFileName ne ""))
		{
		$self->_iFileName($aFileName);

		my $logFile = new FileHandle();
	
		# check the log file can be opened If it can be then clear the file
		$logFile->open(">".$self->_iFileName) || die ("Can not open ".$self->_iFileName." for logging\n");
		$logFile->close();
		}

    if ($aMaxError)
		{
		$self->_iMaxError($aMaxError);
		}  	
    
       return $self;
       }	

################################################################################
#
# Function _iFileName, _iDieFlag, _iMaxError, _iVerbose, _iHasErrored
#
# Functions access the data of the given object
#
# Function takes: an optional argument to assign to the given attribute.
#
# Function Returns: the value of the data
#
# Function Uses:
#
# Notes: These functions combine the traditional getter setter functions
# if there is a argument the member data is set to that value
#################################################################################
sub _iFileName	
    {
    my $self = shift;
    if (@_) { $CLog->{FILENAME} = shift; }
    return $CLog->{FILENAME};
    }

sub _iDieFlag	
    {
    my $self = shift;
    if (@_) { $CLog->{DIEFLAG} = shift }
    return $CLog->{DIEFLAG};
    }

sub _iMaxError	
    {
    my $self = shift;
    if (@_) { $CLog->{MAXERROR} = shift }
    return $CLog->{MAXERROR};
    }

sub _iVerbose
    {
    my $self = shift;
    if (@_) { $CLog->{VERBOSE} = shift; }
    return $CLog->{VERBOSE};
    }

sub _iHasErrored
    {
    my $self = shift;
    if (@_) { $CLog->{HASERRORED} = shift; }
    return $CLog->{HASERRORED};
    }

################################################################################
#
# Function Log
#
# Function logs a message to the User and a given file, if specified
#         
# Function takes: The text to display.
#
# Function Returns: None
#
# Function Uses: None
#
# Notes: This subroutine does not decrement the maxerror count.
#################################################################################
sub Log($)
    {
    my $self = shift;
    my ($aText) = @_;

    # print out the log message
    print "$aText\n";

    $self->_LogToFile($aText);
    }

###############################################################################
#
# Function _LogLethal
#
# Function logs a message to the User and a given file, if specified
#          The log to the screen goes to STDERR instead of STDOUT; this 
#          routine should be used to display messages which either are
#          or are potentially fatal.
#         
# Function takes: The text to display.
#
# Function Returns: None
#
# Function Uses: None
#
# Notes: This subroutine does not decrement the maxerror count.
###############################################################################
sub _LogLethal($)
    {
    my $self = shift;
    my ($aText) = @_;

    # print out the log message
	print STDERR "\n";
    print STDERR "$aText\n";

    $self->_LogToFile($aText);
    }

################################################################################
#
# Function _LogToFile
#
# Function attempts to log a string to the file
#
# Function takes: the string to log
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _LogToFile($)
    {

    my $self = shift;
    my ($aText) = @_;
    
    if ($self->_iFileName ne "")    
		{
		
		my $logFile = new FileHandle();

		$logFile->open(">>".$self->_iFileName) || die ("Can not open ".$self->_iFileName." for logging\n");

		print $logFile "$aText\n";

		$logFile->close();
		}	
    }

################################################################################
#
# Function _LogDate
#
# Function logs a the data and time to the logfile, if specified.
#         
# Function takes: nothing.
#
# Function Returns: None
#
# Function Uses: None
#
# Notes:
#################################################################################
sub _LogDate($)
    {
    my $self = shift;
    my($aText)=@_;

    my $dateTime = AscTime(time());

    $self->_LogToFile($aText." at ".$dateTime);
    }

################################################################################
#
# Function LogVerbose
#
# Function Logs a verbose message which will be written to the log file. Depending
#          on the setting of the verbose flag, it may also appear on the screen.
#
# Function takes: the message to log
#
# Function Returns: None
#
# Function Uses:
#
# Notes:
#################################################################################

sub LogVerbose($)
    {
    my $self = shift;
    my ($aMessage) = @_;

    $self->_LogToFile($aMessage);

    if ($self->_iVerbose)
	{ print STDOUT $aMessage."\n"; }
    }

####################################################################################
#
# Function LogError
#
# Function Logs a message to the user and to an optional logfile if the maximum
# number of errors has been reached and the iDieFlag is true the program dies.
#
# Function takes: the text to display and write into the log file
#
# Function Returns: none
#
# Function Uses: 
#
# Notes: 
#
####################################################################################
sub LogError($)
    {
    my $self = shift;
    my($aText)=@_;

    # log the text and the date
    $self->_LogLethal($aText);
    $self->_LogDate("");

    $self->_iMaxError($self->_iMaxError-1);
    $self->_iHasErrored(1);

    # check if we are to die
    if($self->_iDieFlag)
		{
		#check if the max number of errors has been exceeded
		if($self->_iMaxError<=0)
			    {
			    $self->_LogDate("Maximum number of errors reached");
			    croak("\nMaximum number of errors reached");
			    }
		}
    }

################################################################################
#
# Function LogDie
#
# Function logs a message to the User and a given file, if specified. If the
# iDieFlag state is true then the program will attempt to die regardless of the 
# max number of errors
#         
# Function takes: The text to display.
#
# Function Returns: None
#
# Function Uses: None
#
# Notes:
#################################################################################
sub LogDie($)
    {
    my $self = shift;
    my ($aText) =@_;

    # log the text
    $self->_LogLethal($aText);
    $self->_LogDate("");

    $self->_iHasErrored(1);

    # check if we are to die
    if($self->_iDieFlag)
		{
		$self->_LogDate("Critical Error");
		croak("\nCritical Error");
		}
    }

################################################################################
#
# Function LogFatal
#
# Function logs a message to the User and a given file, if specified. Log Fatal
# dies regardless of the number of errors or the setting of the iDieFlag
#         
# Function takes: the text to display.
#
# Function Returns: None
#
# Function Uses: None
#
# Notes:
#################################################################################
sub LogFatal($)
    {
    my $self = shift;
    my ($aText) = @_;

    $self->_iHasErrored(1);

    $self->_LogLethal($aText);
    $self->_LogDate("Fatal Error:");
    croak("\nFatal Error");
    }

################################################################################
#
# Function DieOnError
#
# Function sets the state of the DIEFLAG so that if max number of errors has
# been reached the program will die.
#         
# Function takes: None
#
# Function Returns: None
#
# Function Uses: None
#
# Notes:
#################################################################################
sub DieOnError
    {
    my $self = shift;
    $self->_iDieFlag(1);
    }

################################################################################
#
# Function NoDieOnError
#
# Function sets the state of the DIEFLAG so that if max number of errors has
# been reached the program will not die.
#         
# Function takes: None
#
# Function Returns: None
#
# Function Uses: None
#
# Notes:
#################################################################################
sub NoDieOnError
    {
    my $self = shift;
    $self->_iDieFlag(0);
    }

################################################################################
#
# Functions NoVerbose, Verbose
#
# Functions clear or set the verbose flag; if set, verbose logs will appear on
#          the screen; if clear, verbose logs go to the file only
#
# Function takes: None
#
# Function Returns: None
#
# Function Uses: None
#
# Notes:
#################################################################################
sub NoVerbose()
    {
    my $self = shift;
    $self->_iVerbose(0);
    }

sub Verbose()
    {
    my $self = shift;
    $self->_iVerbose(1);
    }

################################################################################
#
# Function TEST
#
# Function to test code for the object
#
# Function takes: None
#
# Function Returns: None
#
# Function Uses: None
#
# Notes: TEST cannot perform all the test code as an intrinsic part of the CLog
# class is that it dies when instructed to  
#################################################################################
sub TEST
    {
    my $self = shift;
    
    # uncomment which test you wish to run
    #test ctors and iDieFlag status

    # Comment this out when testing. Remember to put it back afterwards
    print "You must edit log.pm to run the tests\n";

    #$self->Test1();

    # test logging functions
    #$self->Test2();

    # test logging functions with no log file 
    #$self->Test3();

    # test use of class data from one private log object to another
    #$self->Test4();

    # test that the the function dies when it should do so
    #$self->Test5();

    # test that the program dies if the number of log errors exceeds the max number 
    # while dieing is turned off
    #$self->Test6();

    # test that verbose works both on and off
    #$self->Test7();

    # test that the system error level is set if the max number of log errors is
    # not reached
    #$self->Test8();
    }

# Test ctors and taggling iDieFlag status
sub Test1	
    {
    my $self = shift;

    print"\nTest 1";

    #create a log object
    my $obj = New CLog("logfile.txt",5);
    print "Logging to logfile.txt max 5 errors \n";
    $obj->PRINT();

    # change the status of the iDieFlag
    print "Change the status of the iDieFlag\n";
    $obj->NoDieOnError();

    $obj->PRINT;
 
    print "Change the status of the iDieFlag back\n";
    $obj->DieOnError();

    $obj->PRINT;

    print "create a new object logfile.txt no max error count\n";
    $obj = New CLog("logfile.txt");

    $obj->PRINT;

    print "create a new log object no log file or max error count\n";
    print "should be the same as the previous one\n";
    my $newObj = New CLog();

    $newObj->PRINT;

    print "create a log object on a file that cannot be opened, should die\n";
    $newObj = New CLog("..");
    }

# Test all logging functions but only die on a log fatal
sub Test2	
    {
    my $self = shift;

    print"\nTest 2";

    #create a loging object
    my $obj = New CLog("logfile.txt",5);

    print "\nInitial status of object\n";
    $obj->PRINT();

    #Nothing should die except for the final LogFatal 
    $obj->NoDieOnError();

    #perform 10 logs
    for my $count (1..10)
		{
		$obj->Log("This is log number ".$count);
		}

    #perform 10 log errors
    for my $count (1..10)
		{
		$obj->LogError("This is log error ".$count);
		}

    #perform 10 log dies
    for my $count (1..10)
		{
		$obj->LogDie("This is log die ".$count);
		}

    # this is a logfatal
    $obj->LogFatal("This is a log fatal");
    }

# Test all logging functions no log file only die on a log fatal
sub Test3	
    {
    my $self = shift;

    print"\nTest 3";

    #create a loging object
    my $obj = New CLog("",10);

    print "\nInitial status of object\n";
    $obj->PRINT();

    #Nothing should die excpet for the final LogFatal 
    $obj->NoDieOnError();

    #perform 10 logs
    for my $count (1..10)
		{
		$obj->Log("This is log number ".$count);
		}

    #perform 10 log errors
    for my $count (1..10)
		{
		$obj->LogError("This is log error ".$count);
		}

    #perform 10 log dies
    for my $count (1..10)
		{
		$obj->LogDie("This is log die ".$count);
		}

    # this is a logfatal
    $obj->LogFatal("This is a log fatal");
    }

# Test all logging functions no log file only die on a log fatal
sub Test4	
    {
    my $self = shift;

    print"\nTest 4";

    #create a loging object
    my $obj = New CLog("logfile",10);

    print "\nInitial status of object\n";
    $obj->PRINT();

    $obj->Log("Logged from Function Test 4 using its private log function");

    $self->Test4a();
    }

sub Test4a
    {
    my $self = shift;

    print "\nCreate a log object using the same data as in Test4\n";
    #create a loging object
    my $obj = New CLog();

    $obj->PRINT();

    $obj->Log("These logs are from func Test4a using it's log object");
    #perform 10 logs
    for my $count (1..10)
		{
		$obj->Log("This is log number ".$count);
		}
   }

# Test that the program dies when the max number of errors has been reached
sub Test5	
    {
    my $self = shift;

    print"\nTest 5";

    #create a loging object
    my $obj = New CLog("logfile.txt",5);

    print "\nInitial status of object\n";
    $obj->PRINT();

    #perform 10 logs
    for my $count (1..10)
		{
		$obj->Log("This is log number ".$count);
		}

    print "Program should die after 5 log errors\n";

    #perform 10 log errors
    for my $count (1..10)
		{
		$obj->LogError("This is log error ".$count);
		}
    }

# Test that the program dies when the max number of errors is exceeded even if the 
# the NoDieOnError is set has been reached
sub Test6	
    {
    my $self = shift;

    print"\nTest 6";

    #create a loging object
    my $obj = New CLog("logfile.txt",5);

    print "\nInitial status of object\n";
    $obj->PRINT();

    #perform 10 logs
    for my $count (1..10)
		{
		$obj->Log("This is log number ".$count);
		}

    $self->NoDieOnError();

    print "Program should not die after 20 log errors\n";

    #perform 10 log errors
    for my $count (1..20)
		{
		$obj->LogError("This is log error ".$count);
		}

    print "Program should now die on the next log error\n";
    $self->DieOnError();

    $obj->LogError("This should tbe the 21 log error");
    }

# Test the verbose logging
# (program should not die)
sub Test7
    {
    my $self = shift;

    print "\nTest7\n";
    my $log = New CLog("logfile.txt");

    print "Setting verbose off; the following should go to the file only\n";
    $log->NoVerbose;
    $log->LogVerbose("You shouldn't see this on the screen, but it should be in the file");

    print "Now turning verbose on; you should see the following, and it should be in the file\n";
    $log->Verbose;
    $log->LogVerbose("This is a verbose message which appears on the screen. This should be the second log in the file, but the first on screen.");
    }

# Test the system error level is set if an error occurred
# even if the log didn't die (max number wan't reached)
sub Test8
    {
    my $self = shift;
    print "\nTest 8\n";
    my $log = New CLog("",10);

    print "'Die'ing three times; shouldn't die, but should set DOS %ERRORLEVEL% or equivalent\n";
    $log->LogError("Log error 1");
    $log->LogError("Log error 2");
    
    print "\nLog shouldn't have died yet. Now, check the system error level";
    CLog->SetSystemErrorLevel;
    }

################################################################################
#
# Function PRINT
#
# Function prints out the current contents of the object
#
# Function takes: None
#
# Function Returns: None
#
# Function Uses: None
#
# Notes: 
#################################################################################
sub PRINT
    {
    my $self = shift;
    print "Filename: \"". $self->_iFileName ."\"\n";
    print "Current MaxErrors: ". $self->_iMaxError ."\n";
    print "Die Flag Status: ". $self->_iDieFlag ."\n";
    }

################################################################################
#
# Function SetSystemErrorLevel
#
# Function will exit with an error condition if an error has previously occurred
#          (but didn't cause an exit then). Use this at the end of the main
#          script to return an error code to the calling process.
#
# Function takes: None
#
# Function Returns: Only if no errors occurred during processing
#
# Function Uses: None
#
# Notes: Function can be called as a package method (CLog->SetSystemErrorLevel)
#        or a class method ($log->SetSystemErrorLevel)
#################################################################################

sub SetSystemErrorLevel()
    {
    my $self=shift; # May be self, or package name; ignore it

    if ( $CLog->{HASERRORED} )
       {
       exit 255;
       }
    }

1;	







