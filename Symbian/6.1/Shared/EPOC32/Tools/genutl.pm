# GENUTL.PM
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
#


# Contains utility subroutines for MAKMAKE and associated scripts

package Genutl;

require Exporter;
@ISA=qw(Exporter);

@EXPORT=qw(
	Genutl_AnyToHex
);


sub Genutl_AnyToHex ($) {
# changes decimal and hexadecimal numbers to the required hexadecimal format
	my $Num=$_[0];
	$Num=lc $Num;	# lower casing the x specifying hexadecimal essential
	if ($Num=~/^(\d{1,10}|0x[\dabcdef]{1,8})$/o) { # this isn't perfect
		$Num=oct $Num if $Num=~/^0x/o;
		return sprintf "0x%.8lx", $Num;
	}
	return undef;
}

