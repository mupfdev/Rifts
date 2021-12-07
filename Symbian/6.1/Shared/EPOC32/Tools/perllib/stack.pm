#!/usr/bin/perl
################################################################################
#
# module: stack.pm
#
# module implements stack object
#
# Copyright (c) 1999 Symbian Ltd.  All rights reserved
#
# Date Thu Sep 30 10:15 1999
#
################################################################################
package CStack;

use log;

################################################################################
#
# Function New
#
# Function creates a new perl object
#
# Function takes: no arguments 
#
# Function Returns: the created object
#
# Function Uses:
#
# Notes:
################################################################################
sub New()
    {
    my $templ = shift;
    $class = ref($templ) || $templ;
    
    my $self = {};    # Not a hash
    bless ($self, $class);

    $self->_iLog(New CLog());
    $self->_iStack([]);
    
    # Return our object
    return $self;
    }

################################################################################
#
# Function _iLog _iStack
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
#
# Modification history
#
################################################################################
sub _iLog
    {
    my $self = shift;
    if (@_) { $self->{LOG} = shift }
    return $self->{LOG};
    }

sub _iStack
    {
    my $self = shift;
    if (@_) { $self->{STACK} = shift }
    return $self->{STACK};
    }

################################################################################
#
# Function Push
#
# Function puts ('pushes') the specified value onto the stack
#
# Function takes: The value to push
#
# Function Returns:
#
# Function Uses:
#
# Notes:
################################################################################
sub Push($)
    {
    my $self = shift;
    my ($aValue) = @_;
    
    push(@{$self->_iStack}, $aValue);
    }

################################################################################
#
# Function Pop
#
# Function retrieves and removes ('pops') the value on the top of the stack
#
# Function takes:
#
# Function Returns: The value popped
#
# Function Uses:
#
# Notes: Produces undef if the stack is empty; the IsEmpty method is provided if
#        you need to tell the difference between an undef popped from the stack,
#        and the end of the stack.
################################################################################
sub Pop
    {
    my $self = shift;
    
    return(pop(@{$self->_iStack}));
    }

################################################################################
#
# Function Top
#
# Function retreives the value from the top of the stack
#
# Function takes:
#
# Function Returns: The value at the top of the stack
#
# Function Uses:
#
# Notes: This is like Popping, but without actually removing the value. Useful
#          if the stack represents a nested state; top returns 'where I am now'
#        Produces undef if the stack is empty; the IsEmpty method is provided if
#          you need to tell the difference between an undef popped from the
#          stack, and the end of the stack.
################################################################################
sub Top
    {
    my $self = shift;
    
    # get the top index of the list
    my $index = $#{$self->_iStack}; 
    
    return $self->_iStack->[$index];
    }

################################################################################
#
# Function Bottom
#
# Function retreives the value from the bottom of the stack
#
# Function takes:
#
# Function Returns: The value at the bottom of the stack
#
# Function Uses:
#
# Notes: This is an extension to the ordinary stack behaviour, and so is only
#          really useful under some circumstances.
#        Produces undef if the stack is empty; the IsEmpty method is provided if
#          you need to tell the difference between an undef popped from the stack,
#          and the end of the stack.
#################################################################################
sub Bottom
    {
    my $self = shift;
    
    return $self->_iStack->[0]; # Return the first (bottom) value
    }

################################################################################
#
# Function IsEmpty
#
# Function checks to see if the stack is empty or not
#
# Function takes:
#
# Function Returns: 1 if empty, 0 if not
#
# Function Uses:
#
# Notes: Useful if you need to distinguish between a undef result because of an
#          empty stack, and an undef result because of a real undef value in the
#          stack.
#################################################################################
sub IsEmpty
    {
    my $self = shift;
    
    # If the length of the stack is 0, return 1
    
    if (scalar(@{$self->_iStack}) == 0)
        {return 1;}
    else
        {return 0;}
    }

################################################################################
#
# Function TEST
#
# Function test the stack object
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub TEST()
    {
    my $self = shift;
    
    $self->Push(["a","b","c"]);
    $self->Push(1.30);
    $self->Push("Sheila");

    $self->PRINT();

    $self->_iLog->Log($self->Pop());
    $self->_iLog->Log($self->Top());
    $self->_iLog->Log($self->Pop());
    $self->_iLog->Log($self->IsEmpty());
    $self->_iLog->Log($self->Pop());
    $self->_iLog->Log($self->IsEmpty());
    }

################################################################################
#
# Function PRINT
#
# Function prints out the current state of the stack object
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

    $self->_iLog->Log("Stack content (Top first)");
    
    #get the top index
    my $topIndex = $#{$self->_iStack};

    # loop through the stack
    while($topIndex > 0)
		{
		$self->_iLog->Log($self->_iStack->[$index]);
		$topIndex--;
		}
    }

1;





