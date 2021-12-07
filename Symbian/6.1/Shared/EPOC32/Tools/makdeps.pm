# MAKDEPS.PM
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
#


# Module which wraps the dependency information provided the preprocessor when invoked with certain switches
# so that dependency information rather than preprocessing information is produced.

package Makdeps;
require Exporter;
@ISA=qw(Exporter);
@EXPORT=qw(
	Deps_InitL
	Deps_SetVerbose
	Deps_SetUserHdrsOnly
	Deps_SetSysIncPaths
	Deps_SetUserIncPaths
	Deps_SetPlatMacros
	Deps_SetStdIncSysIncPaths
	Deps_GenDependsL
);

use Checkgcc;
use Pathutl;

my $ChopSysDecoyPath;
my $EPOCIncPath;
my @StdPaths;
my %Mode;
my @PlatMacros;
my $SysDecoyPath;
my @SysFlags;
my @SysPaths;
my @UserFlags;
my @UserPaths;

# special variable used in pattern-matching - special characters nullified
my $S_SysDecoyPath;

BEGIN {	# NB don't initialise essential items to be provided later by calling module, then will cause errors with undef
	$Mode{'Verbose'}=0;
	$Mode{'UserHdrsOnly'}=0;
	@PlatMacros=();
	# note -MG option assumes missing user headers live in 1st userincpath and missing sys headers in 1st sysdir
	@SysPaths=();
	@UserPaths=();
	@StdPaths=();
	@SysFlags=();
	@UserFlags=();
	$S_SysDecoyPath=$SysDecoyPath=&Path_WorkPath."TEMPMAKSYSDECOY\\";
	$S_SysDecoyPath=~s-\\-\\\\-go;
	$ChopSysDecoyPath=&Path_Chop($SysDecoyPath);
}

sub Deps_InitL ($@) {	# abs Generated Hdr dir, StdIncsysdir (with drive letter if required)
# set up a decoy system include path, and set which path will contain generated headers, eg .RSG files, and which
# paths are the standard system include paths for the compiler used - eg \MSDEV\INCLUDE
	($EPOCIncPath,@StdPaths)=@_;

# remove the decoy directory then try to make it again - if it contains files rmdir won't work, so mkdir won't
# work and the user will have to sort it out.  If it doesn't contain files and has been left lying around
# because someone has killed the program half-way through, then rmdir will remove it and mkdir will work OK
	rmdir $ChopSysDecoyPath if -d $ChopSysDecoyPath;
	mkdir $ChopSysDecoyPath,2 or die "ERROR: Can't make temp dir \"$ChopSysDecoyPath\"\nIf it already exists, please remove it\n";
}
sub Deps_SetVerbose {
	$Mode{'Verbose'}=1;
}
sub Deps_SetUserHdrsOnly {
# allow calling program to dictate that only listings of user headers, not system headers, be produced
	$Mode{'UserHdrsOnly'}=1;
}
sub Deps_SetSysIncPaths (@) {	# takes list abs paths
# set the system include paths where we'll look for system included files, and
# for user included files if these are not found in the user include directories
	return unless @_;
	@SysPaths=@_;
	@SysFlags=&Path_Chop(&Path_RltToWork(@SysPaths)); # newer gcc doesn't like trailing backslash
	my $Flag;
	foreach $Flag (@SysFlags) {
		$Flag=~s/^(.*)$/-I "$1"/o;
	}
}
sub Deps_SetUserIncPaths (@) {	# takes list of abs paths
# set the user include paths to find user included files in
	return unless @_;
	@UserPaths=@_;
	@UserFlags=&Path_Chop(&Path_RltToWork(@UserPaths)); # newer gcc doesn't like trailing backslash
	my $Flag;
	foreach $Flag (@UserFlags) {
		$Flag=~s/^(.*)$/-I "$1"/o;
	}
}
sub Deps_SetPlatMacros (@) {
# set the macros to be defined by the preprocessor
	return unless @_;
	@PlatMacros=@_;
	my $Flag;
	foreach $Flag (@PlatMacros) {
		$Flag=~s/^(.*)$/-D$1/o;
	}
}

sub Deps_GenDependsL ($@) {	# takes abs source filepath and list of Build Macros

#	Set any more macros the preprocessor needs to be defined for the source file
#	to be preprocessed.
#	Call preprocessor and produce the dependency listing.

	my ($Src,@BldMacros)=@_;

	if (not -e $Src) {
		warn "WARNING: \"",$Src,"\" not found!\n";
		return;
	}

# 	Always put the source path at the head of the user path list
#	and take it out at the end of this function
	unshift @UserPaths, &Path_Split('Path',$Src);

	my $RTWSrc=&Path_RltToWork($Src);
	my $RTWSysDecoyPath=&Path_Chop(&Path_RltToWork($SysDecoyPath)); # newer gcc doesn't like trailing backslash
	my $MacroFlag;
	foreach $MacroFlag (@BldMacros) {
		$MacroFlag=~s/^(.*)$/-D$1/o;
	}
	undef $MacroFlag;

	my $RTWSrcPath=&Path_Chop(&Path_Split('Path',$RTWSrc)); # newer gcc doesn't like trailing backslash
	if ($Mode{'Verbose'}) {
		print "CPP.EXE -M -MG -nostdinc -I \"$RTWSrcPath\" @UserFlags -I- @SysFlags @PlatMacros @BldMacros \"$RTWSrc\"\n";
	}
	open CPPPIPE,"CPP.EXE -M -MG -nostdinc -I \"$RTWSrcPath\" @UserFlags -I- -I \"$RTWSysDecoyPath\" @SysFlags @PlatMacros @BldMacros \"$RTWSrc\" |" or die "ERROR: Can't invoke CPP.EXE\n";
	my @RTWDepList;
	while (<CPPPIPE>) {
		$_ = uc $_;
		while (/\s(\S\S+)/go) {
			# preprocessor will crash here if spaces in long filenames - but can search for \<space> for spaces in filenames
			# or will be able to with new gcc build perhaps
			# get the elements of cpp's output, not the first - avoided by requiring the space in front of each element
			push @RTWDepList,$1;
		}
	}
	close CPPPIPE or die "ERROR: CPP.EXE failure\n";

	# drop the second element of preprocessor's output
	shift @RTWDepList;

	foreach (@RTWDepList) {
	# replace its forward slashes with backward slashes
		s-/-\\-go;
	}

# make all paths absolute
	my @DepList=&Path_AbsToWork(@RTWDepList);
	undef @RTWDepList;

# test the dependencies
	eval { @DepList=&TestDepends($Src,@DepList); };
	die $@ if $@;
	
	my @SortedDepList;
# get just those headers found in the user include path if user headers only specified
	if (not $Mode{'UserHdrsOnly'}) {
		@SortedDepList=sort @DepList;
	}
	else {
		my @UserDepList=();
		my $Dep;
		my $UserPath;
		DEPLOOP: foreach $Dep (@DepList) {
			foreach $UserPath (@UserPaths) {
				if ($UserPath eq &Path_Split('Path',$Dep)) {
					push @UserDepList, $Dep;
					next DEPLOOP;
				}
			}
		}
		@SortedDepList=sort @UserDepList;
	}

# take the source path out of the user path list
	shift @UserPaths;

	@SortedDepList;
} 


sub TestDepends (@) { # takes source list of absolute dependencies - called by GenDepends
# check that the dependencies exist or are to be generated later, because gcc with the -MG switch
# will assume that missing system headers live in the first system include path specified (the decoy
# directory in our case), and the missing user headers live in the current working directory

	my ($Src,@DepList)=@_;

	my @BadSysList;
	my @BadUserList;
	my $Dep;
	my @GoodList;
	my $SrcPath=&Path_Split('Path',$Src);

	my $Path;
	my $File;
	DEPLOOP: foreach $Dep (@DepList) { # system dependencies not found
		$Path=&Path_Split('Path',$Dep);
		if ($Dep=~/^$S_SysDecoyPath(.*)$/o) { # allow things like "#include <sys\stats.h>"
# any files listed as existing in the system decoy directory will be missing system include files
			$File=$1;
# change any missing generated header entries so that they are thought to be in $EPOCIncPath, where they will be generated to
			if ($File=~/\.(RSG|MBG)$/o) {
				push @GoodList, "$EPOCIncPath$File";
				next DEPLOOP;
			}
# remove missing system include files from the list if they actually exist in standard directories - since the makefiles can't handle
# files which may be on a different drive - we don't mind this because if we're using MSVC then we can assume
# the MSVC include files will exist
			my $LR;
			foreach $LR (@StdPaths) {	# tackle MSDEV include dir on diff drive
				if (-e "$LR$File") {	# don't put MSDEV includes in dep list - drive letter would end up in makefile
					next DEPLOOP;
				}
			}
# put any other missing system files on the bad list
			push @BadSysList, $File;
			next DEPLOOP;
		}
# preprocessor lists any missing user headers as existing in the current directory,
# and, if no userinclude paths are specified,
# searches to path containing the source file for user headers by default
		if ($Path eq &Path_WorkPath) { # possible missing user headers
			$File=&Path_Split('File',$Dep);
			# does the userinclude path contain the current working directory?
			my $LoopPath;
			my $WorkPathInUserPaths=0;
			foreach $LoopPath (@UserPaths) {
				if ($LoopPath eq &Path_WorkPath) {
					$WorkPathInUserPaths=1;
					next;
				}
			}
			if ($WorkPathInUserPaths) { # the user include path contains the current working directory
				if (-e $Dep) {
					push @GoodList,$Dep;	# file found in specified userinclude path, OK
					next DEPLOOP;
				}
			}
			push @BadUserList, $File;	# file not found in specified userinclude path, bad
			next DEPLOOP;
		}
		push @GoodList, $Dep;
	}

	my $Bad;
	if (@BadSysList) {
		warn	"\nWARNING: Can't find following headers in System Include Path\n";
		foreach $Bad (@BadSysList) {
			print STDERR " <$Bad>";
		}
		print STDERR "\n(Sys Inc Paths";
		foreach $Path (@SysPaths,@StdPaths) {
			print STDERR " \"$Path\"";
		}
		warn
			")\nDependency list for \"$Src\" may be incomplete\n",
			"\n"
		;
	}
	if (@BadUserList) {
		warn "\nWARNING: Can't find following headers in User or System Include Paths\n";
		my $GenHdr=0;
		foreach $Bad (@BadUserList) {
			print STDERR " \"$Bad\"";
			if ($File=~/\.(RSG|MBG)$/o) {
				$GenHdr=1;
			}
		}
		print STDERR "\n(User Inc Paths";
		foreach $Path (@UserPaths) {
			print STDERR " \"$Path\"";
		}
		warn
			")\nDependency list for \"$Src\" may be incomplete\n",
			"\n"
		;
		if ($GenHdr) {
			warn
				"Note that generated headers should be system-included with angle brackets <>\n",
				"\n"
			;
		}
	}

	@GoodList;
}


END {
	# remove the dependency decoy directories
	if (-d "$ChopSysDecoyPath") {
		rmdir "$ChopSysDecoyPath" or warn "Please remove temp dir \"$ChopSysDecoyPath\"\n";
	}
}

1;
