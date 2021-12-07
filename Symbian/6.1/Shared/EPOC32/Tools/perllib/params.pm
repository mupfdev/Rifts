#!perl
################################################################################
#
# module: params.pm
#
# module implements an params object for perl. 
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved
#
# Date: Fri Oct 15 14:57:12 1999
#
################################################################################
use lib "\\epoc32\\tools\\perllib";

use Carp;
use strict;

use log;
use devtools;

################################################################################
package CParams;

BEGIN
    {
    import CParamsEntry;
    import CParamItem;
    }

################################################################################
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

    $self->_iParamsArray({});
    
    return $self;
    }	

################################################################################
#
# Function _iLog _iParamsArray 
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

sub _iParamsArray
    {
    my $self = shift;
    if (@_) { $self->{PARAMSARRAY} = shift; }
    return $self->{PARAMSARRAY};
    }

################################################################################
#
# Function AddParamItem
#
# Function Adds an ParamItem to the ParamsArray
#
# Function takes: the name of the parameter, its value and a flag indicating
# that the parameter is the default
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub AddParamItem($$$)
    {
    my $self = shift;
    my ($aName,$aValue,$aDefault)= @_;

    #check if the parameter has already been added
    if(!$self->Exists($aName))
		{
		# it has not been added create the ParamsEntry
		my $paramsEntry = New CParamsEntry();
		$self->_iParamsArray->{$aName} = $paramsEntry;
		}

    # add the parameterItem to the ParamsEntry
    $self->_ParamsEntry($aName)->AddParamItem($aName,$aValue,$aDefault);
    }

################################################################################
#
# Function Parameters
#
# Function gets all the names of the parameter entries
#
# Function takes: none
#
# Function Returns: A reference to the array containing the Parameters from the
# ParamsArray
#
# Function Uses:
#
# Notes:
#################################################################################
sub Parameters
    {
    my $self = shift;

    return [keys(%{$self->_iParamsArray})];
    }

################################################################################
#
# Function ParamsEntry
#
# Function gets the ParamEntry from the ParamsArray with a matching Parameter name
#
# Function takes: The name of the parameter to find
#
# Function Returns: A reference to the ParamEntry
#
# Function Uses:
#
# Notes:
#################################################################################
sub _ParamsEntry($)
    {
    my $self = shift;
    my($aName) = @_;

    my $result = New CParamsEntry();

    #check that this parameter Entry exists
    if($self->Exists($aName))
		{
		$result = $self->_iParamsArray->{$aName};
		}

    return $result;
    }

################################################################################
#
# Function ParamItem
#
# Function gets the ParamItem from the ParamsArray with a matching Parameter name
#
# Function takes: The name of the parameter to find and an optional index
#
# Function Returns: A reference to the ParamsItem
#
# Function Uses:
#
# Notes: If the parameter does not exist then a empty paramItem is constructed 
# and a reference to this is returned
#################################################################################
sub ParamItem($$)
    {
    my $self = shift;
    my($aName, $aIndex) = @_;

    # make a new paramItem to use if there is not one in existance
    my $result = New CParamItem(undef,undef,undef,New CParamsEntry());
    my $index = 0;

    # if an index is given take the Param Item with this index
    if($aIndex)
		{
		$index = $aIndex;
		}

    # check that the parameter exists
    if($self->Exists($aName))
		{
		# find the coresponding ParamsEntry and get the ParamsItem from it
		my $paramItem = $self->_ParamsEntry($aName)->ParamItem($index);
		# check that it was found
		if($paramItem)
			    {
			    $result=$paramItem;
			    }
		}
    return $result;
    }

################################################################################
#
# Function Exists
#
# Function determins if the parameter name exists in the parameters
#
# Function takes: The name of the parameter to find
#
# Function Returns: True if the value returned can be found, false if not
#
# Function Uses:
#
# Notes:
#################################################################################
sub Exists($)
    {
    my $self = shift;
    my($aName) = @_;

    my $result=0;

    #try and get the ParamsEntry for this name
    if($self->_iParamsArray->{$aName})
		{
		$result=1;
		}

    return $result;
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
    $self->_iLog->Log("Test 1 add some new paramters to the parameters");
    $self->AddParamItem("TestPara1", "Default value", 1);
    $self->AddParamItem("TestPara2", "Test 2 Default value", 1);
    $self->AddParamItem("TestPara2", "value1", 0);
    $self->AddParamItem("TestPara3", "value2", 0);
    $self->AddParamItem("TestPara3", "value3", 0);
    $self->AddParamItem("TestPara3", "value4", 0);

    $self->PRINT();

    $self->_iLog->Log("Test 2 get some ParamItems depending");
    $self->_iLog->Log("Get a full ParamsEntry for TestPara3");
    $self->_ParamsEntry("TestPara3")->PRINT;

    $self->_iLog->Log("\nGet ParamItem for TestPara1");
    $self->ParamItem("TestPara1")->PRINT;

    $self->_iLog->Log("\nGet ParamItem for TestPara2");
    $self->ParamItem("TestPara2")->PRINT;

    $self->_iLog->Log("\nGet ParamItem for TestPara3 index 1");
    $self->ParamItem("TestPara3",1)->PRINT;

    $self->_iLog->Log("\nTest 3 Get values for some parameters Last two calls are to values that don't exist");
    $self->_iLog->Log("Value for TestPara1 ".$self->ParamItem("TestPara1")->Value);
    $self->_iLog->Log("Value for TestPara2 ".$self->ParamItem("TestPara2")->Value);
    $self->_iLog->Log("Value for TestPara3 ".$self->ParamItem("TestPara3",1)->Value);
    $self->_iLog->Log("Value for TestPara3 ".$self->ParamItem("TestPara3",20)->Value);
    $self->_iLog->Log("Value for TestPara4 ".$self->ParamItem("TestPara4")->Value);

    $self->_iLog->Log("\nTest 4 get the number of paraItems stored for some parameters");
    $self->_iLog->Log("Number of items for TestPara1 ".$self->ParamItem("TestPara1)")->NumberItems());
    $self->_iLog->Log("Number of items for TestPara2 ".$self->ParamItem("TestPara2")->NumberItems());
    $self->_iLog->Log("Number of items for TestPara3 ".$self->ParamItem("TestPara3")->NumberItems());
    $self->_iLog->Log("Number of items for TestPara4 ".$self->ParamItem("TestPara4")->NumberItems());

    $self->_iLog->Log("\nTest 5 get the number of non  default paraItems stored for some parameters");
    $self->_iLog->Log("Number of non default items for TestPara1 ".$self->ParamItem("TestPara1)")->NumberNonDefaultItems());
    $self->_iLog->Log("Number of non default items for TestPara2 ".$self->ParamItem("TestPara2")->NumberNonDefaultItems());
    $self->_iLog->Log("Number of non default items for TestPara3 ".$self->ParamItem("TestPara3")->NumberNonDefaultItems());
    $self->_iLog->Log("Number of non default items for TestPara4 ".$self->ParamItem("TestPara4")->NumberNonDefaultItems());

    $self->_iLog->Log("\nTest 6 check if the default value for some parameters TestPara4 does not exist");
    $self->_iLog->Log("Is default TestPara1 ".$self->ParamItem("TestPara1")->Default());
    $self->_iLog->Log("Is default TestPara2 ".$self->ParamItem("TestPara2")->Default());
    $self->_iLog->Log("Is default TestPara3 ".$self->ParamItem("TestPara3")->Default());
    $self->_iLog->Log("Is default TestPara4 ".$self->ParamItem("TestPara4")->Default());

    $self->_iLog->Log("\nTest 7 Test some parameters that exist and some that don't");
    $self->_iLog->Log("Exists TestPara1 ".$self->Exists("TestPara1"));
    $self->_iLog->Log("Exists TestPara2 ".$self->Exists("TestPara2"));
    $self->_iLog->Log("Exists Doesnot ".$self->Exists("Doesnot"));
    $self->_iLog->Log("Exists TestPara3 ".$self->Exists("TestPara3"));
    $self->_iLog->Log("Exists Dosenot2 ".$self->Exists("DoesNot2"));
    $self->_iLog->Log("Exists TestPara4 ".$self->Exists("TestPara4"));
    $self->_iLog->Log("Exists Doesnot3 ".$self->Exists("DoesNot3"));

    $self->_iLog->Log("\nTest 8 Get all the values for the testPara3 parameter into an array");
    my $valuesArray = $self->ParamItem("TestPara3")->Values;

    for my $value (@$valuesArray)
		{
		$self->_iLog->Log("Value = $value");
		}
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

    $self->_iLog->Log("The Params Array contains:");

    # print out the content of the Params array
    for my $name (@{$self->Parameters()})
		{
		$self->_iLog->Log("\n***************");
		$self->_ParamsEntry($name)->PRINT();
		}
    }

################################################################################
package CParamsEntry;

BEGIN
    {
    import CParamItem;
    }

#used by the CParams class this stores the values

################################################################################
#
# Function New
#
# Function creates a new CParamsEntry object.
#
# Function takes none 
#
# Function Returns: the created object
#
# Function Uses:
#
# Notes: 
#################################################################################
sub New()
    {
    my $class = shift;
    my $self = {};	

    bless $self, $class;

    # create a log object for this object
    $self->_iLog(New CLog());

    $self->_iParamItems([]);
    $self->_iDefaultParamItem(undef);
    
    return $self;
    }	

################################################################################
#
# Function _iLog _iNoParamItems _iParamItems _iDefaultParamItem
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

sub _iParamItems
    {
    my $self = shift;
    if (@_) { $self->{PARAMITEMS} = shift; }
    return $self->{PARAMITEMS};
    }

sub _iDefaultParamItem
    {
    my $self = shift;
    if (@_) { $self->{DEFAULTPARAMITEM} = shift; }
    return $self->{DEFAULTPARAMITEM};
    }


################################################################################
#
# Function AddParamItem
#
# Function adds a parameter item to the entry
#
# Function takes: the name of the parameter, its value and a flag indicating if
# the parameter Item contains the default value
#
# Function Returns: None
#
# Function Uses: None
#
# Notes:   
#################################################################################
sub AddParamItem
    {
    my $self = shift;
    my ($aName,$aValue,$aDefault)= @_;

    # check if the parameter item is the default
    if($aDefault)
		{
		$self->_iDefaultParamItem(New CParamItem($aName,$aValue,$aDefault,$self));
		}
    else
		{
		#add the paramItem
		push(@{$self->_iParamItems},New CParamItem($aName,$aValue,$aDefault,$self));
		}
    }

################################################################################
#
# Function ParamItem
#
# Function Gets the ParamItem from a ParamEntry
#
# Function takes: an optional index giving the ParamItem index in the paramItem 
# array 
#
# Function Returns: the stored ParamItem, if non has been stored then the 
# function returns the default ParamItem.
#
# Function Uses: None
#
# Notes: 
#################################################################################
sub ParamItem
    {
    my $self = shift;

    my ($aIndex) = @_;
    my $index = 0;

    # if an index is given take the Param Item with this index
    if($aIndex)
		{
		$index = $aIndex;
		}
		
    # get the first paramIndex
    my $result = $self->_iParamItems->[$index];

    # check if there is a non default value stored if the index is 0
    if((!$result) && ($index == 0))
		{
		$result = $self->_iDefaultParamItem;
		}

    return($result);
    }

################################################################################
#
# Function DefaultParamItem
#
# Function Gets the Default ParamItem from a ParamEntry
#
# Function takes: none 
#
# Function Returns: the default ParamItem, if non has been stored then the 
# function returns undef.
#
# Function Uses: None
#
# Notes: 
#################################################################################
sub DefaultParamItem
    {
    my $self = shift;

    return($self->_iDefaultParamItem);
    }

################################################################################
#
# Function NumberNonDefaultItems
#
# Function Gets the number of Non Default ParamItems in the ParamEntry
#
# Function takes: None
#
# Function Returns: The number of paramItems that have been stored
#
# Function Uses: None
#
# Notes: 
#################################################################################
sub NumberNonDefaultItems
    {
    my $self = shift;
    
    # get the number of non default ParamItems
    my $result = @{$self->_iParamItems};

    return($result);
    }

################################################################################
#
# Function NumberItems
#
# Function Gets the number of ParamItems in the ParamEntry
#
# Function takes: None
#
# Function Returns: The number of paramItems that have been stored. If no 
# ParamItems have been stored and there is a default value the number is
# one. If paramItems have been stored then the default value is not counted 
#
# Function Uses: None
#
# Notes: 
#################################################################################
sub NumberItems
    {
    my $self = shift;
    
    # get the number of stored ParamItems
    my $result = $self->NumberNonDefaultItems();

    # if there no ParamItems stored and there is a default ParamItem
    if(($result == 0) && $self->_iDefaultParamItem)
		{
		$result = 1;
		}

    return($result);
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

    # Add parameter item to the param entry
    $self->_iLog->Log("Test 1 store a default parameter item (stored param and default should be the same)");

    $self->AddParamItem("TestPara1", "Default value", 1);

    $self->PRINT();

    # Add parameter item to the param entry
    $self->_iLog->Log("Test 2 store another default parameter item (stored param and default should be the same)");

    $self->AddParamItem("TestPara2", "Another default value", 1);

    $self->PRINT();

    # Add a non default parameter item
    $self->_iLog->Log("Test 3 store another parameter item (stored param and default should be different)");

    $self->AddParamItem("TestPara3", "non default value", 0);

    $self->PRINT();

    # add ten paramItems to the entry
    $self->_iLog->Log("Test 4 add ten paramItes to the ParaEntry");

    for my $count (1..10)
		{
		$self->AddParamItem("TestPara$count", "non default value $count", 0);
		}

    $self->PRINT();

    # get some paramItems by index
    $self->_iLog->Log("\nTest 5 get a selection of paramItems from the entry by index");
    
    $self->ParamItem(3)->PRINT();
    $self->ParamItem(4)->PRINT();
    $self->ParamItem(9)->PRINT();
    $self->ParamItem(10)->PRINT();

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

    my $noItems = $self->NumberItems();

    $self->_iLog->Log("Number of ParamItems: ".$noItems);
    $self->_iLog->Log("Number of Non default ParamItems: ".$self->NumberNonDefaultItems());
    
    $self->_iLog->Log("Stored Parameters\n");
    my $count =0;
    while($count < $noItems)
		{
		$self->ParamItem($count)->PRINT();
		$count++;
		}

    $self->_iLog->Log("\nDefault Parameter Item:");
    #check if there is a default parameter item
    my $ParamItem = $self->_iDefaultParamItem;
    if($ParamItem)
	{
	$ParamItem->PRINT();
	}
    else
		{
		$self->_iLog->Log("There is no default value");
		}


    }

################################################################################
package CParamItem;
################################################################################
#
# Function New
#
# Function creates a new CParamItem object.
#
# Function takes the name of the parameter, value, a default flag and a reference
# to the CParamsEntry object within which this paramItem is located 
#
# Function Returns: the created object
#
# Function Uses:
#
# Notes: 
#################################################################################
sub New($$$$)
    {
    my $class = shift;
    my ($aName, $aValue, $aDefault, $aParamsEntry) =@_;
    my $self = {};	

    bless $self, $class;

    # create a log object for this object
    $self->_iLog(New CLog());

    $self->_iName($aName);
    $self->_iValue($aValue);
    $self->_iDefault($aDefault);
    $self->_iParamsEntry($aParamsEntry);
    
    return $self;
    }	

################################################################################
#
# Function _iLog _iName _iValue _iDefault _iParamsEntry
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

sub _iValue
    {
    my $self = shift;
    if (@_) { $self->{VALUE} = shift; }
    return $self->{VALUE};
    }

sub _iDefault
    {
    my $self = shift;
    if (@_) { $self->{DEFAULT} = shift; }
    return $self->{DEFAULT};
    }

sub _iParamsEntry
    {
    my $self = shift;
    if (@_) { $self->{PARAMSENTRY} = shift; }
    return $self->{PARAMSENTRY};
    }

################################################################################
#
# Function Name
#
# Function Gets the name for a given ParamItem
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
# Function Value
#
# Function Gets the value for a given ParamItem
#
# Function takes: None
#
# Function Returns: the stored value
#
# Function Uses: None
#
# Notes:   
#################################################################################
sub Value
    {
    my $self = shift;

    return($self->_iValue);
    }

################################################################################
#
# Function DefaultValue
#
# Function Gets the DefaultValue for a given ParamItem
#
# Function takes: None
#
# Function Returns: the value of the default value stored by the paramEntry that
# this param item is associated with
#
# Function Uses: None
#
# Notes:   
#################################################################################
sub DefaultValue
    {
    my $self = shift;
    my $result = undef;

    #check that this ParamItem associated with a ParamEntry
    if($self->_iParamsEntry)
		{
		my $defaultParamItem = $self->_iParamEntry->DefaultParamItem();

		if($defaultParamItem)
			    {
			    $result = $defaultParamItem->Value;
			    }
		}
    # check that the value is not a default it's self
    elsif ($self->_iDefault)
		{
		$result = $self->Value;
		}
    return($result);
    }

################################################################################
#
# Function Values
#
# Function gets the values contained in CParamsEntry object that this param item
# is associated with 
#
# Function takes: none
#
# Function Returns: A reference to an array containing the values
#
# Function Uses:
#
# Notes:
#################################################################################
sub Values
    {
    my $self = shift;

    my $result=[];
    my $count = 0;

    # check that this ParamsItem is associted with a ParamsEntry
    my $paramEntry = $self->_iParamsEntry;
    if($paramEntry)
		{
		# get the ParamItem
		my $paramItem = $paramEntry->ParamItem($count);

		# loop through all the stored values
		while($paramItem)
			    {
			    # add this value to the array
			    push(@$result,$paramItem->Value);
		
			    $count++;

			    # get the next paramItem
			    $paramItem = $paramEntry->ParamItem($count);
			    }
		}
    else
		{
		# just put this value into an array
		push(@$result,$self->Value);		
		}

    return $result;
    }

################################################################################
#
# Function Default
#
# Function tests if the paramter contains the default value
#
# Function takes: None
#
# Function Returns: true if the paramItem contans the default value
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
# Function NumberNonDefaultItems
#
# Function Gets the number of Non Default ParamItems associated with this
# ParamItem
#
# Function takes: None
#
# Function Returns: The number of non default paramItems
#
# Function Uses: None
#
# Notes: 
#################################################################################
sub NumberNonDefaultItems
    {
    my $self = shift;

    my $result = 0;

    #check if this Paramitem is associated with a ParamEntry
    if($self->_iParamsEntry)
		{
		$result = $self->_iParamsEntry->NumberNonDefaultItems();
		}
    # check if this param Item has a name and is a non default one
    elsif($self->_iName && (!$self->_iDefault))
		{
		$result = 1;
		}

    return($result);
    }

################################################################################
#
# Function NumberItems
#
# Function Gets the number of ParamItems associated with this one
#
# Function takes: None
#
# Function Returns: The number of paramItems associated with this ParamItem. If no 
# ParamItems have been stored and there is a default value the number is
# one. If paramItems have been stored then the default value is not counted 
#
# Function Uses: None
#
# Notes: 
#################################################################################
sub NumberItems
    {
    my $self = shift;
    
    my $result = 0;

    #check if this Paramitem is associated with a ParamEntry
    if($self->_iParamsEntry)
		{
		$result = $self->_iParamsEntry->NumberItems();
		}
    
    # check if this param Item has a name
    elsif($self->_iName)
		{
		$result = 1;
		}

    return($result);
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
    $self->_iLog->Log("Test 1 create a paramItem");

    my $obj1 = New CParamItem("TestPara1", "Default value", 1, undef);

    $self->_iLog->Log("Print the default value for this ParamItem (should be Default value)");
    $self->_iLog->Log("Default vlaue is ".$obj1->DefaultValue());

    $self->_iLog->Log("Test 2 create a non default paramitem");
    $obj1 = New CParamItem("TestPara1", "Value", 0, undef);

    $self->_iLog->Log("Print the default value for this ParamItem (should be undef)");
    $self->_iLog->Log("Default value is ".$obj1->DefaultValue());

    $self->_iLog->Log("Print the array of values for this ParamItem");
    foreach my $value (@{$obj1->Values()})
		{
		$self->_iLog->Log("value is $value");
		}

    $self->_iLog->Log("Print out the ParamItem");
  
    $obj1->PRINT();
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

    $self->_iLog->Log("Name: ".$self->Name());
    $self->_iLog->Log("Value: ".$self->Value());
    $self->_iLog->Log("Default: ".$self->Default());
   
    }

1;	










