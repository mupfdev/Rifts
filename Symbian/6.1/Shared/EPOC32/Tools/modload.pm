# MODLOAD.PM
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
#


# Runtime module-loading routine for loading e32tools modules into 'main' module


package Modload;

require Exporter;
@ISA=qw(Exporter);

@EXPORT=qw(
	Load_SetVerbose
	Load_SetModulePath
	Load_ModuleL
);


use Pathutl;

my %Mode=(
	Verbose=>0
);
my $ModulePath;

sub Load_SetVerbose () {
	$Mode{Verbose}=1;
}

sub Load_SetModulePath ($) {
	$ModulePath=$_[0];
}

sub Load_ModuleL (@) {
# Loads a module into the 'main' package, including all the functions the module defines for export

	my @ModBaseList=@_;
	my $ModBase;
	foreach $ModBase (@ModBaseList) {
		$ModBase=uc $ModBase;
		die "ERROR: Can't load \"$ModulePath$ModBase.PM\"\n" unless -e "$ModulePath$ModBase.PM";
		if ($Mode{Verbose}) {
			print "Loading Module: \"",$ModBase,".PM\"\n";
		}
		package main;
		require $ModBase.".PM" or die "ERROR: Can't load function from \"$ModulePath$ModBase.PM\"\n";
		my $Package=ucfirst lc $ModBase;
		$Package->import;
	}
}

1;
