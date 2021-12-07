#!perl
################################################################################
#
# module: args.pm
#
# module implements an args object for perl. 
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved
#
# Date: Thu Oct 14 11:55:32 1999
#
################################################################################
use lib "\\epoc32\\tools\\perllib";

use Carp;
use strict;

use params;
use log;
use devtools;

################################################################################
package CArgs;

BEGIN
    {
    import CArgsSpec;
    import CArgsSpecArray;
    import CParams;
    import CParamItem;
    }

################################################################################
#
# Function New
#
# Function creates a new CArgs object. New can take a reference to a
# CArgsSpecArray object. If no array is given then the arg object is created but 
# the ArgSpecArray must be added by the calling program before parsing the 
# command line 
#
# Function takes a reference to a function that will be called if parsing the 
# arguments fails and optionally  a refererence to a CArgsSpecArray 
#
# Function Returns: the created object
#
# Function Uses:
#
# Notes: It is intended that the function reference passed will be to a function 
# that displays the usage of the program to the user
#################################################################################
sub New
    {
    my $class = shift;
    my($aHelp, $aArgsSpecArray) = @_;

    my $self = {};	

    bless $self, $class;

    # create a log object for this object
    $self->_iLog(New CLog());
    
    # store the arguments specification array if given
    if($aArgsSpecArray)
	{
	$self->_iArgsSpecArray($aArgsSpecArray);
	}
    else
		{
		$self->_iArgsSpecArray(New CArgsSpecArray());
		}

    $self->_iParams(undef);
    $self->_iHelp($aHelp);

    return $self;
    }	

################################################################################
#
# Function _iLog _iArgsSpecArray _iParams _iHelp 
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
sub _iLog
    {
    my $self = shift;
    if (@_) { $self->{LOGOBJ} = shift; }
    return $self->{LOGOBJ};
    }

sub _iArgsSpecArray
    {
    my $self = shift;
    if (@_) { $self->{ARGSSPECARRAY} = shift; }
    return $self->{ARGSSPECARRAY};
    }

sub _iParams
    {
    my $self = shift;
    if (@_) { $self->{PARAMS} = shift; }
    return $self->{PARAMS};
    }
sub _iHelp
    {
    my $self = shift;
    if (@_) { $self->{HELP} = shift; }
    return $self->{HELP};
    }


################################################################################
#
# Function AddArgsSpec
#
# Function Adds an argument spec to the ArgsSpecArray
#
# Function takes: The name of the argument, The default value, a pettern to match
# the argument, a reference to an array of exclusions, a flag indicating that the 
# argument is manditory and a flag indicating that an argument may be repeated
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub AddArgsSpec($$$$$$)
    {
    my $self = shift;
    my ($aName, $aDefault, $aPattern, $aExclusions, $aMandatory, $aRepeatable) =@_;

    # add the given ArgSpec to the ArgsSpecArray
    $self->_iArgsSpecArray->AddArgsSpec($aName, $aDefault, $aPattern, $aExclusions, $aMandatory, $aRepeatable);
    }

################################################################################
#
# Function ParseCommandLine
#
# Function Parses a Command line against the content of the ArgsSpec
#
# Function takes: a reference to the commandline array to parse. Called by 
# ParseCommandLine(\@ARGV)
#
# Function Returns: A reference to the created Parameters object 
#
# Function Uses:
#
# Notes: The args spec should be filled out in advance of ParseCommandLine being
# called.
#################################################################################
sub ParseCommandLine($)
    {
    my $self = shift;
    my ($aCommandLine)= @_;

    # get a new parameters object
    $self->_iParams(New CParams());

    # copy all the default values to the parameters
    $self->_CopyDefaultValues();

    # process the arguments
    $self->_ProcArgs($aCommandLine);
    
    # validate the parsed command line
    $self->_Validate();

    # return the filled out paramters
    return $self->_iParams;
    }

################################################################################
#
# Function _CopyDefaultValues
#
# Function Copys the default values contained in the ArgsSpecArray into the 
# params object
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _CopyDefaultValues($)
    {
    my $self = shift;

    #loop through all the argument specs 
    foreach my $argument (@{$self->_iArgsSpecArray->Arguments()})
		{
		# get the default value for this ArgSpec has a default value
		my $default = $self->_iArgsSpecArray->ArgsSpec($argument)->Default();
		if($default)
			    {
			    # add this to the parameters
			    $self->_iParams->AddParamItem($argument, $default, 1);
			    }
		}


    # return the filled out paramters
    return $self->_iParams;
    }

################################################################################
#
# Function _ProcArgs
#
# Function Processes the arguments contained within the command line
#
# Function takes: A reference to the args array
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _ProcArgs($)
    {
    my $self = shift;
    my($aArguments) = @_;

    #loop through all the arguments 
    foreach my $argument (@$aArguments)
		{
		# process the argument
		$self->_ProcArg($argument);
		}
    }

################################################################################
#
# Function _ProcArg
#
# Function Processes an argument. The argument is tested against the matching
# patterns in the ArgsSpec array. Once a match has been found then the   
#
# Function takes: An argument to process
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _ProcArg($)
    {
    my $self = shift;
    my($aArgument) = @_;

    # assume that no pattern will match the argument
    my $matchFound = 0;

    #loop through all the arguments 
    foreach my $argSpec (@{$self->_iArgsSpecArray->Arguments()})
		{
		# get the pattern for this $ArgSpec
		my $pattern = $self->_iArgsSpecArray->ArgsSpec($argSpec)->Pattern();

		#check if this argument matches the pattern
		if($aArgument =~ /$pattern/)
			    {
			    # store the value for this argument
			    my $value = $1;
			    
			    # validate this value for this argument
			    $self->_ValidateRepeatable($argSpec);

			    # store the value
			    $self->_iParams->AddParamItem($argSpec,$value, 0);
			    # record that a match was found
			    $matchFound = 1;
			    }
		}
    # check that a match was found
    if(!$matchFound)
		{
		$self->_iLog->Log("$aArgument is not a recognised command line argument");
		# execute the help function
		$self->_ExecHelp();
		}
    }

################################################################################
#
# Function _Validate
#
# Function Validates a given argument   
#
# Function takes: The argument to validate
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _Validate($)
    {
    my $self = shift;
    my($aArgument) = @_;

    # validate that the argument is not excluded by any other parameter
    $self->_ValidateExclusion();

    # validate maditory
    $self->_ValidateMandatory();
    
    }

################################################################################
#
# Function _ValidateRepeatable
#
# Function Validates that an already stored paramter may have more than one value
#
# Function takes: The argument to validate
#
# Function Returns: none
#
# Function Uses:
#
# Notes: If the ArgsSpec is not validated then the function calles the function 
# referenced in the _iHelp member
#################################################################################
sub _ValidateRepeatable($)
    {
    my $self = shift;
    my($aArgsSpec) = @_;

    # check that we are trying to store this parameter more than once
    if($self->_iParams->ParamItem($aArgsSpec)->NumberNonDefaultItems()>0)
		{
		# check that the argument is repeatable
		if(!$self->_iArgsSpecArray->ArgsSpec($aArgsSpec)->Repeatable())
			    {
			    $self->_iLog->Log("$aArgsSpec may only be specified once on the command line");
			    # exec the help function
			    $self->_ExecHelp();
			    }
		}
    }

################################################################################
#
# Function _ValidateExclusion
#
# Function Validates all stored parameters have no exclusions
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes: If the parameters cannot be validated then the function calls the function
# contained in the _iHelp member
#################################################################################
sub _ValidateExclusion
    {
    my $self = shift;

    # loop through all the stored parameters
    foreach my $parameter (@{$self->_iParams->Parameters()})
		{
		# loop through the exclusions for each of these parameters
		foreach my $exclusion(@{$self->_iArgsSpecArray->ArgsSpec($parameter)->Exclusions()})
			    {
			    # check if this parameter was stored
			    if($self->_iParams->Exists($exclusion))
					{
					$self->_iLog->Log("Cannot specify $parameter and $exclusion together");
					# exec the help function
					$self->_ExecHelp();
					}
			    }
		}
    }

################################################################################
#
# Function _ValidateMandatory
#
# Function Validates that all mandatory paramaters have been specified
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes: If the parameters cannot be validated then the function calls the function
# contained in the _iHelp member
#################################################################################
sub _ValidateMandatory
    {
    my $self = shift;

    # loop through the exclusions for each of these parameters
    foreach my $argument(@{$self->_iArgsSpecArray->Arguments()})
		{
		# check if this argument is mandatory
		if($self->_iArgsSpecArray->ArgsSpec($argument)->Mandatory())
			    {
			    # check if this parameter was not stored
			    if(!$self->_iParams->ParamItem($argument)->NumberNonDefaultItems())
					{
					$self->_iLog->Log("$argument must be given on the command line");
					# exec the help function
					$self->_ExecHelp();
					}
			    }
		}
    }

################################################################################
#
# Function _ExecHelp
#
# Function Executes the help finction contained in the _iHelp member
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _ExecHelp($)
    {
    my $self = shift;
    #get the function to execute
    my $func = $self->_iHelp;

    #execute the function
    &$func;
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
# Notes:   
#################################################################################
sub TEST
    {
    my $self = shift;

    $self->_iLog->Log("\nTest 1 add a spec for a repeating group");

    my $obj1 = New CArgs();

    # set up the help function for testing
    $obj1->_iHelp(sub{print("Help Displayed");
		      });

    # set up the ArgsSpec
    $obj1->AddArgsSpec("Arg1", "Default value", "^(.*)\$", ["test5"], 1, 1);

    # set up a fake args array
    my $arguments = ["test1","test2","test3"];

    my $parameters = $obj1->ParseCommandLine($arguments);

    $obj1->_iLog->Log("\nParameters extracted from commandline \"test1 test2 test3\"");
    $parameters->PRINT();

    # test trying to store repeating argument when spec is non repeating
    $self->_iLog->Log("\nTest 2 add a spec for a non repeating group");

    $obj1 = New CArgs();

    # set up the help function for testing
    $obj1->_iHelp(sub{print("Help Displayed");
		      });
	       
    # set up the ArgsSpec
    $obj1->AddArgsSpec("Arg1", "Default value", "^(.*)\$", [], 1, 0);

    # set up a fake args array
    $arguments = ["test1","test2","test3"];

    $parameters = $obj1->ParseCommandLine($arguments);

    $self->_iLog->Log("\nTest 3 try parsing a command line with more complicated patterns");
    
    $obj1 = New CArgs();

    # set up the help function for testing
    $obj1->_iHelp(sub{print("Help Displayed");
		      });

    # set up the ArgsSpec
    $obj1->AddArgsSpec("Arg1", "Default value", "^-a(.*)\$", [], 0, 1);
    $obj1->AddArgsSpec("Arg2", "Default value", "^-b(.*)\$", ["arg1"], 0, 1);
    $obj1->AddArgsSpec("Arg3", "Default value", "^-cde(.*)hij\$", ["test2", "test3", "test4"], 0, 1);

    # set up a fake args array
    $arguments = ["-atest1","-cdetest2hij","-cdetest3"];

    $parameters = $obj1->ParseCommandLine($arguments);

    $obj1->_iLog->Log("\nParameters extracted from commandline \"-atest1 -cdetest2hij -cdetest3\"");
    $parameters->PRINT();

    # test trying to store argument when exclusions
    $self->_iLog->Log("Test 4 try and add parameter where exclusions forbid it");

    $obj1 = New CArgs();

    # set up the help function for testing
    $obj1->_iHelp(sub{print("Help Displayed");
		      });
	       
    # set up the ArgsSpec with the exclusion
    $obj1->AddArgsSpec("Arg1", "Default value", "^-a(.*)\$", [], 0, 1);
    $obj1->AddArgsSpec("Arg2", "Default value", "^-b(.*)\$", ["Arg1"], 0, 1);

    # set up a fake args array
    $arguments = ["-btest2","-atest2"];

    $parameters = $obj1->ParseCommandLine($arguments);

    $self->_iLog->Log("\nTest 5 try parsing where Arg2 is  mandatory and missing");

    $obj1 = New CArgs();

    # set up the help function for testing
    $obj1->_iHelp(sub{print("Help Displayed");
		      });
	       
    # set up the ArgsSpec with the mandatory arguments
    $obj1->AddArgsSpec("Arg1", "Default value", "^-a(.*)\$", [], 1, 1);
    $obj1->AddArgsSpec("Arg2", "Default value", "^-b(.*)\$", [], 1, 1);
    $obj1->AddArgsSpec("Arg3", "Default value", "^-c(.*)\$", [], 0, 1);

    # set up a fake args array
    $arguments = ["-atest2"];

    $parameters = $obj1->ParseCommandLine($arguments);

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
    $self->_iArgsSpecArray->PRINT();
    $self->_iParams->PRINT();
    $self->_iLog->Log("The following function will for invalid arguments");
    $self->_ExecHelp();
    }

################################################################################
package CArgsSpecArray;

BEGIN
    {
    import CArgsSpec;
    }

################################################################################
#
# Function New
#
# Function creates a new CArgsSpecArray object.
#
# Function takes none
#
# Function Returns: the created object
#
# Function Uses:
#
# Notes: 
#################################################################################
sub New
    {
    my $class = shift;
    my $self = {};	

    bless $self, $class;
    # create a log object for this object
    $self->_iLog(New CLog());

    $self->_iSpecArray({});
    
    return $self;
    }	

################################################################################
#
# Function _iLog _iSpecArray 
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
sub _iLog
    {
    my $self = shift;
    if (@_) { $self->{LOGOBJ} = shift; }
    return $self->{LOGOBJ};
    }

sub _iSpecArray
    {
    my $self = shift;
    if (@_) { $self->{SPECARRAY} = shift; }
    return $self->{SPECARRAY};
    }

################################################################################
#
# Function AddArgsSpec
#
# Function Adds an argument spec to the SpecArray
#
# Function takes: The name of the argument, The default value, a pettern to match
# the argument, a reference to an array of exclusions, a flag indicating that the 
# argument is manditory and a flag indicating that an argument may be repeated
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub AddArgsSpec($$$$$$)
    {
    my $self = shift;
    my ($aName, $aDefault, $aPattern, $aExclusions, $aMandatory, $aRepeatable)= @_;

    # check that this name has not been added already
    if($self->ArgsSpec($aName))
		{
		$self->_iLog->LogError("Attribute $aName has already been added to the Argument specifications");
		}

    # add the given ArgSpec to the SpecArray under the name of the argument
    $self->_iSpecArray->{$aName}= New CArgsSpec($aName, $aDefault, $aPattern, $aExclusions, $aMandatory, $aRepeatable);
    }

################################################################################
#
# Function Arguments
#
# Function gets all the arguments in the of the SpecArray
#
# Function takes: none
#
# Function Returns: A reference to the array containing the arguments from the
# SpecArray
#
# Function Uses:
#
# Notes:
#################################################################################
sub Arguments
    {
    my $self = shift;
    return [keys(%{$self->_iSpecArray})];
    }

################################################################################
#
# Function ArgsSpec
#
# Function gets the ArgSpec from the Spec array with a matching Argument name
#
# Function takes: none
#
# Function Returns: A reference to the Argument spec
#
# Function Uses:
#
# Notes:
#################################################################################
sub ArgsSpec($)
    {
    my $self = shift;
    my($aName) = @_;

    return $self->_iSpecArray->{$aName};
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
# Notes:   
#################################################################################
sub TEST
    {
    my $self = shift;

    # argument spec to the array
    $self->_iLog->Log("Test 1 add some Argument Specs to the array");

    $self->AddArgsSpec("TestArg1", "Default value", "\\w*", ["this", "that", "theother"], 1, 1);
    $self->AddArgsSpec("TestArg2", "Another Default value", "\\w*", ["this", "that", "theother"], 1, 1);
    $self->AddArgsSpec("TestArg3", "", "^(\\w*)\$", [], 1, 1);
    $self->AddArgsSpec("TestArg4", "Default value", "\\w*", ["this", "that", "theother"], 0, 1);
    $self->AddArgsSpec("TestArg5", "Default value", "\\w*", ["this", "that", "theother"], 1, 0);

    $self->PRINT();

    $self->_iLog->Log("Test 2 get some Arg Specs from the array by key");
    $self->_iLog->Log("The Arg spec for Test1 is ".$self->ArgsSpec("TestArg1")->Name()."\n");
    $self->_iLog->Log("The Arg spec for Test2 is ".$self->ArgsSpec("TestArg2")->Name()."\n");
    $self->_iLog->Log("The Arg spec for Test3 is ".$self->ArgsSpec("TestArg3")->Name()."\n");
    $self->_iLog->Log("The Arg spec for Test4 is ".$self->ArgsSpec("TestArg4")->Name()."\n");
    $self->_iLog->Log("The Arg spec for Test5 is ".$self->ArgsSpec("TestArg5")->Name()."\n");


    # turn off the dieing on a log error
    $self->_iLog->NoDieOnError();
    $self->_iLog->Log("Test 3 Attempt to add a ArgsSpec with an existing key");

    $self->AddArgsSpec("TestArg1", "Default value", "\\w*", ["this", "that", "theother"], 1, 1);
    # turn dieing back on
    $self->_iLog->DieOnError();
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

    $self->_iLog->Log("The ArgsSpec array contains:");

    # print out the content of the Spec array
    for my $name (@{$self->Arguments()})
		{
		$self->_iLog->Log("\n***************");
		$self->ArgsSpec($name)->PRINT();
		}
    }

################################################################################
package CArgsSpec;
################################################################################
#
# Function New
#
# Function creates a new CArgsSpec object.
#
# Function takes the name of the argument, default value, pattern that matches
# the argument, an array of names of arguments that exclude this argument, a
# flag indicating that this argument is maditory and a flag that indicates if
# the argument can be repeated. 
#
# Function Returns: the created object
#
# Function Uses:
#
# Notes: 
#################################################################################
sub New($$$$$$)
    {
    my $class = shift;
    my ($aName, $aDefault, $aPattern, $aExclusions, $aMandatory, $aRepeatable) =@_;
    my $self = {};	

    bless $self, $class;

    # create a log object for this object
    $self->_iLog(New CLog());

    $self->_iName($aName);
    $self->_iDefault($aDefault);
    $self->_iPattern($aPattern);
    $self->_iExclusions($aExclusions);
    $self->_iMandatory($aMandatory);
    $self->_iRepeatable($aRepeatable);
    
    return $self;
    }	

################################################################################
#
# Function _iLog iName iDefault iPattern iExcusions iMandatory iRepeatable 
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
sub _iLog
    {
    my $self = shift;
    if (@_) { $self->{LOGOBJ} = shift; }
    return $self->{LOGOBJ};
    }

sub _iName
    {
    my $self = shift;
    if (@_) { $self->{NAME} = shift; }
    return $self->{NAME};
    }

sub _iDefault
    {
    my $self = shift;
    if (@_) { $self->{DEFAULT} = shift; }
    return $self->{DEFAULT};
    }

sub _iPattern
    {
    my $self = shift;
    if (@_) { $self->{PATTERN} = shift; }
    return $self->{PATTERN};
    }

sub _iExclusions
    {
    my $self = shift;
    if (@_) { $self->{EXCLUSIONS} = shift; }
    return $self->{EXCLUSIONS};
    }

sub _iMandatory
    {
    my $self = shift;
    if (@_) { $self->{MANDATORY} = shift; }
    return $self->{MANDATORY};
    }

sub _iRepeatable
    {
    my $self = shift;
    if (@_) { $self->{REPEATABLE} = shift; }
    return $self->{REPEATABLE};
    }

################################################################################
#
# Function Name
#
# Function Gets the name for a given ArgsSepc
#
# Function takes: None
#
# Function Returns: the name
#
# Function Uses: None
#
# Notes:   
#################################################################################
sub Name
    {
    my $self = shift;

    return($self->_iName);
    }


################################################################################
#
# Function Default
#
# Function Gets the Default value for a given ArgsSepc
#
# Function takes: None
#
# Function Returns: the default value
#
# Function Uses: None
#
# Notes:   
#################################################################################
sub Default
    {
    my $self = shift;

    return($self->_iDefault);
    }

################################################################################
#
# Function Pattern
#
# Function Gets the matching pattern for a given ArgsSepc
#
# Function takes: None
#
# Function Returns: the Matching pattern
#
# Function Uses: None
#
# Notes:   
#################################################################################
sub Pattern
    {
    my $self = shift;

    return($self->_iPattern);
    }

################################################################################
#
# Function Exclusions
#
# Function Returns a reference to the array containing the exclusions for this 
# ArgSpec
#
# Function takes: none
#
# Function Returns: a reference to the array containing the exclusions
#
# Function Uses: None
#
# Notes:   
#################################################################################
sub Exclusions
    {
    my $self = shift;

    return($self->_iExclusions);
    }

################################################################################
#
# Function Repeatable
#
# Function Returns the value of the repeatable flag
#
# Function takes: none
#
# Function Returns: the state of the repeatable flag
#
# Function Uses: None
#
# Notes:   
#################################################################################
sub Repeatable
    {
    my $self = shift;

    return($self->_iRepeatable);
    }

################################################################################
#
# Function Mandatory
#
# Function Returns the state of the mandatory flag
#
# Function takes: none
#
# Function Returns: Returns the state of the mandatory flag
#
# Function Uses: None
#
# Notes:   
#################################################################################
sub Mandatory
    {
    my $self = shift;

    return($self->_iMandatory);
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

    $self->_iLog->Log("Name: ".$self->Name);
    $self->_iLog->Log("Default: ".$self->Default);
    $self->_iLog->Log("Pattern: ".$self->Pattern);
    $self->_iLog->Log("Exclusions: ");
    foreach my $exclusion (@{$self->Exclusions()})
		{
		$self->_iLog->Log($exclusion);
		}
    $self->_iLog->Log("Mandatory: ".$self->Mandatory);
    $self->_iLog->Log("Repeatable: ".$self->Repeatable);

    }

1;	










