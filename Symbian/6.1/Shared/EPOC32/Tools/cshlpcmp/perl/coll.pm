#!perl
################################################################################
#
# module: coll.pm
#
# module implements the collection object
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved
#
# Date Fri Aug 20 16:42:55 1999
#
################################################################################
package CCollection;

use Carp;
use strict;

use devtools;
use log;

################################################################################
#
# Function New
#
# Function creates a new collection object
#
# Function takes: none
#
# Function Returns: the created object
#
# Function Uses:
#
# Notes: 
#################################################################################
sub New
    {
    my $proto = shift;
    my $class = ref($proto) || $proto;

    my $self  = {};
    bless($self, $class);

    $self->_iLog(New CLog());
    $self->_iNextIndex(0);
    $self->_iNumItems(0);
    $self->_iContent({});

    return $self;
    }

################################################################################
#
# Function _iLog _iNextIndex _iNumItems _iContent 
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

sub _iNextIndex
    {
    my $self = shift;
    if (@_) { $self->{NEXTINDEX} = shift }
    return $self->{NEXTINDEX};
    }

sub _iNumItems
    {
    my $self = shift;
    if (@_) { $self->{NUMITEMS} = shift }
    return $self->{NUMITEMS};
    }

sub _iContent
    {
    my $self = shift;
    if (@_) { $self->{CONTENT} = shift }
    return $self->{CONTENT};
    }

################################################################################
#
# Function AddItem
#
# Function adds an item to the collection
#
# Function takes: the key of the data to add and optinally the data to store 
# with this key and the index to use for the item
#
# Function Returns: none
#
# Function Uses:
#
# Notes: dies if the key is not unique for the collection. calling function 
# has the responsibility to ensure the key is unique, index if given is not
# checked for uniqueness
#################################################################################
sub AddItem($$$)
    {
    my $self = shift;
    my($aKey,$aData,$aIndex)=@_;

    my $data = [];

    my $key="";

    #check if the given key is empty
    if($aKey eq "")
		{
		$key=$self->_iNextIndex;
		}
    else
		{
		$key=$aKey;
		}
		
    #check that the key does not already exist
    if($self->Exists($key))
	   {
	   $self->_iLog->LogDie("AddItem(\"$key\"...) failed because the key already exists in the collection");
	   }

    #add the index and the aData to the data array
    if($aIndex)
		{
		$data->[0]=$aIndex;
		}
    else
		{
		$data->[0]=$self->_iNextIndex;
		}

    $data->[1]=$aData;

    #store the data
    $self->_iContent->{$key}=$data;

    # if an index was given and it's > _iNextIndex
    if($aIndex && ($aIndex > $self->_iNextIndex))
		{
		$self->_iNextIndex($aIndex+1);
		}
    else
		{
		$self->_iNextIndex($self->_iNextIndex+1);
		}

    $self->_iNumItems($self->_iNumItems+1);
    }

################################################################################
#
# Function Keys
#
# Function gets all the hash keys of the contents
#
# Function takes: none
#
# Function Returns: A reference to the array containing the keys from the
# collection
#
# Function Uses:
#
# Notes:
#################################################################################
sub Keys
    {
    my $self = shift;

    return [keys(%{$self->_iContent})];
    }

################################################################################
#
# Function KeysOrderByKey
#
# Function gets all the hash keys of the contents in alphabetical order
#
# Function takes: none
#
# Function Returns: A reference to the array containing the keys sorted
# alphabetically by key
#
# Function Uses:
#
# Notes:
#################################################################################
sub KeysOrderByKey
    {
    my $self = shift;

    # get the keys from the collection
    my $keys = $self->Keys();

    #return a reference to the sorted keys array
    return [sort(@$keys)];
    }

################################################################################
#
# Function KeysOrderByIndex
#
# Function gets all the hash keys of the contents in index number order
#
# Function takes: none
#
# Function Returns: A reference to the array containing the keys sorted
# by index number
#
# Function Uses:
#
# Notes:
#################################################################################
sub KeysOrderByIndex
    {
    my $self = shift;

    # get the keys from the collection
    my $keys = $self->Keys();

    # sort the keys acoding to the index value
    my $sortedKeys = [sort({$self->Index($a) <=> $self->Index($b)} @$keys)];

    #return a reference to the sorted keys array
    return $sortedKeys;

    }

################################################################################
#
# Function Exists
#
# Function Checks if a key exists in the content 
#
# Function takes: the key to check
#
# Function Returns: true if the key exists. false if not
#
# Function Uses: 
#
# Notes:
#################################################################################
sub Exists($)
    {
    my $self = shift;
    my($aKey)=@_;

    #check for the existance of the key
    return exists($self->_iContent->{$aKey});
    }

################################################################################
#
# Function Index
#
# Function returns the index for a given key value
#
# Function takes: the key to get the index value for
#
# Function Returns: the index value
#
# Function Uses: 
#
# Notes:
#################################################################################
sub Index($)
    {
    my $self = shift;
    my($aKey)=@_;

    #check for the existance of the key
    return $self->_iContent->{$aKey}->[0];
    }

################################################################################
#
# Function Data
#
# Function returns the data for a given key value
#
# Function takes: the key to get the data for
#
# Function Returns: the data
#
# Function Uses: 
#
# Notes:
#################################################################################
sub Data($)
    {
    my $self = shift;
    my($aKey)=@_;

    #check for the existance of the key
    return $self->_iContent->{$aKey}->[1];
    }

################################################################################
#
# Function TEST
#
# Function the test code for the collection object
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
    $self->_iLog->Log("adding");

    $self->AddItem("Hello");
    $self->AddItem("you","string",1);
    $self->AddItem("there","another string",4);
    $self->AddItem("nice","yet another string",87);
    $self->AddItem("","this is a string");
    $self->AddItem("have");
    $self->AddItem("met");

    #try to add a added item

    # get the keys in different orders
    my $keys = $self->Keys;
    my $keys = $self->KeysOrderByKey;
    my $keys = $self->KeysOrderByIndex;

    $self->PRINT();
    }

################################################################################
#
# Function PRINT
#
# Function prints out the current contents of the collection object
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

    $self->_iLog->Log("The collection contains ". $self->_iNumItems ." Items ");
    $self->_iLog->Log("The next index is ". $self->_iNextIndex);
    
    # check if the collection is empty
    if($self->_iNumItems == 0)
		{
		$self->_iLog->Log("The collection is EMPTY");
		}
    else
		{
		$self->_iLog->Log("The contents in collection order");
		
		for my $key (@{$self->Keys()})
			    {
			    $self->_iLog->Log($key." index ".$self->Index($key)." ".$self->Data($key));
			    }		

		$self->_iLog->Log("The contents ordered alphabetically by key");
		
		for my $key (@{$self->KeysOrderByKey()})
			    {
			    $self->_iLog->Log($key." index ".$self->Index($key)." ".$self->Data($key));
			    }		

		$self->_iLog->Log("The contents ordered by index");
		
		for my $key (@{$self->KeysOrderByIndex()})
			    {
			    $self->_iLog->Log($key." index ".$self->Index($key)." ".$self->Data($key));
			    }		
		}
}

1;

















