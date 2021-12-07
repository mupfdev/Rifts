# GENBUILD.PL
#
# Copyright (c) 1999-2000 Symbian Ltd.  All rights reserved.
#

# Given a baseline list of components, generate scripts to do the build

use strict;

if (@ARGV!=1 || ! -e $ARGV[0])
	{
#........1.........2.........3.........4.........5.........6.........7.....
	print <<USAGE_EOF;

Usage:
  genbuild complist     -- generate build scripts

Given a list of components, generate the scripts necessary to
build them all using the automated build system. The scripts 
will be named after the component list, so

  genbuild \\batch\\build\\somename.txt

will generate the following scripts:

  somename_bldfiles.cmd    - run "bldmake bldfiles" on every component
  somename_export.cmd      - run "abld export" on every component
  somename_makefile.cmd    - run "abld makefile" on every component
  somename_library.cmd     - run "abld library" on every component
  somename_resource.cmd    - run "abld resource" on every component
  somename_target.cmd      - run "abld target" on every component
  somename_final.cmd       - run "abld final" on every component
  somename_check.cmd       - run "abld -check build" on every component
  somename_what.cmd        - run "abld -what build" on every component

  somename_build.cmd       - use appropriate combination of above scripts
  somename_pbuild.cmd      - alternative build script for multi-machine builds

The somename_build.cmd script is controlled by options specified in the
list of components, and calls the other scripts in the correct sequence.

USAGE_EOF
	exit 1;
	}

# Check for EPOCROOT
# It's not used directly by GENBUILD, but this is a good early stage at which
# to discover that it hasn't been set...

my $epocroot = $ENV{EPOCROOT};
die "ERROR: Must set the EPOCROOT environment variable\n" if (!defined($epocroot));
$epocroot =~ s-/-\\-go;	# for those working with UNIX shells
die "ERROR: EPOCROOT must not include a drive letter\n" if ($epocroot =~ /^.:/);
die "ERROR: EPOCROOT must be an absolute path without a drive letter\n" if ($epocroot !~ /^\\/);
die "ERROR: EPOCROOT must not be a UNC path\n" if ($epocroot =~ /^\\\\/);
die "ERROR: EPOCROOT must end with a backslash\n" if ($epocroot !~ /\\$/);
die "ERROR: EPOCROOT must specify an existing directory\n" if (!-d $epocroot);

my $basename = $ARGV[0];
if ($basename =~ /^.*\\([^\\]+)$/)
	{
	$basename = $1;		# lose the leading path, if any
	}
if ($basename =~ /^([^.]+)\..*$/)
	{
	$basename = $1;		# lose the trailing extensions, if any
	}


my @components;
my %arm_assplist;
my $savespace="";
my $keepgoing="";
my $build_tools=0;
my $build_winc=0;
my $build_thumb=0;
my $build_arm3=0;
my $build_wd2=0;
my $build_noarm4=0;
my $build_noarmi=0;
my $epoc_only=0;

open FILE, "< $ARGV[0]" or die "Can't read $ARGV[0]\n";
while (<FILE>)
	{
	s/\s*#.*$//;
	s/^\s*//;
	my $line = lc $_;
	if ($line =~ /^$/)
		{
		next;
		}

	if ($line =~ /<option (\w+)\s*(.*)>/)
		{
		my $option = $1;
		my $optargs= $2;
		if ($option =~ "savespace")
			{
			$savespace = "-savespace";
			next;
			}
		if ($option =~ "keepgoing")
			{
			$keepgoing = "-keepgoing";
			next;
			}
		if ($option =~ "tools")
			{
			$build_tools = 1;
			next;
			}
		if ($option =~ "winc")
			{
			$build_winc = 1;
			next;
			}
		if ($option =~ "epoconly")
			{
			$build_winc = 0;
			$epoc_only = 1;
			next;
			}
		if ($option =~ "thumb")
			{
			$build_thumb = 1;
			next;
			}
		if ($option =~ "arm3")
			{
			$build_arm3 = 1;
			next;
			}
		if ($option =~ "wd2")
			{
			$build_wd2 = 1;
			next;
			}
		if ($option =~ "noarm4")
			{
			$build_noarm4 = 1;
			next;
			}
		if ($option =~ "noarmi")
			{
			$build_noarmi = 1;
			next;
			}
		if ($option =~ "arm_assp")
			{
			$arm_assplist{$optargs} = 1;
			next;
			}
		print "Option $1 not yet implemented\n";
		next;	
		}
	if ($line =~ /^([^<]\S+)\s+(\S+)/)
	    {
	    if (!-e "$2\\bld.inf")
		{
		print STDERR "MISSING COMPONENT $1: can't find $2\\bld.inf\n";
		next;
		}
	    }

	push @components, $line;
	}

my %specials = (
    "bldfiles e32toolp" =>
	"cd \\e32toolp\\group\n".
	"call setupprj\n".
	"call bld rel\n"
    );

print_batch("bldfiles",	"cd \\%2\\%3\n", "call bldmake bldfiles $keepgoing");
print_batch("export",	"cd \\%2\\%3\n", "call abld export");
print_batch("makefile",	"cd \\%2\\%3\n", "call abld makefile $keepgoing %arg1% %arg2% %arg3%");
print_batch("library",	"cd \\%2\\%3\n", "call abld library  $keepgoing %arg1% %arg2% %arg3%");
print_batch("resource",	"cd \\%2\\%3\n", "call abld resource $keepgoing %arg1% %arg2% %arg3%");
print_batch("target",	"cd \\%2\\%3\n", "call abld target   $keepgoing $savespace %arg1% %arg2% %arg3%");
print_batch("final",	"cd \\%2\\%3\n", "call abld final    $keepgoing %arg1% %arg2% %arg3%");
print_batch("check",	"cd \\%2\\%3\n", "call abld -check build %arg1% %arg2% %arg3%");
print_batch("what",	"cd \\%2\\%3\n", "call abld -what build %arg1% %arg2% %arg3%");
print_batch("clean",	"cd \\%2\\%3\n", "call abld clean %arg1% %arg2% %arg3%");
print_batch("reallyclean",	"cd \\%2\\%3\n", "call abld reallyclean %arg1% %arg2% %arg3%");

print_control("build");
print_pcontrol("pbuild");

#--------------------------------------------------------------------

sub print_batch
	{
	my ($label, @actions) = @_;

	my $scriptbase = $basename."_".$label;
	open FILE, ">$scriptbase.cmd" or die "can't create $scriptbase.cmd";
	print FILE <<HEAD_EOF;
\@echo off
setlocal
echo ===-------------------------------------------------
echo === $scriptbase %1 %2 %3
echo ===-------------------------------------------------
perl -e "\$time=localtime; print '=== ',$label,' started ', \$time"
echo .
set arg1=%1
set arg2=%2
set arg3=%3
goto :doit

:$label
echo === $label == %1 %4
setlocal

@actions

endlocal
goto :EOF

:doit

HEAD_EOF

	my $line;
	foreach $line (@components)
		{
		if ($line =~ /<special (\w+)\s+(\w+)(.*)>/)
			{
			if ($1 eq $label)
				{
				print FILE "REM special $1 $2\n";
				print FILE "echo === $label == $2\n";
				print FILE "setlocal\n\n";
				print FILE $specials{"$1 $2"};
				print FILE "\nendlocal\n\n";
				}
			next;
			}
		print FILE "call :$label $line";
		}

	print FILE <<TAIL_EOF;

perl -e "\$time=localtime; print '=== ',$label,' finished ', \$time"
echo .

TAIL_EOF

	close FILE;
	print "Created $scriptbase.cmd\n";
	}


#--------------------------------------------------------------------
# Overall build

sub print_control
	{
	my ($label) = @_;

	my $scriptbase = $basename."_".$label;
	open FILE, ">$scriptbase.cmd" or die "can't create $scriptbase.cmd";

	print FILE <<HEAD_EOF;
\@echo off
setlocal
perl -e "\$time=localtime; print '=== ',$scriptbase,' started ', \$time"
echo .

HEAD_EOF

	#--------------------------------------------------------
	# Generic stuff first

	print FILE "call ${basename}_bldfiles\n";
	print FILE "call ${basename}_export\n";
	print FILE "\n";

	#--------------------------------------------------------
	# TOOLS, if any

	if ($build_tools)
		{
		print FILE "call ${basename}_makefile tools\n";
		print FILE "call ${basename}_library  tools\n";
		print FILE "call ${basename}_target   tools rel\n\n";
		}

	#--------------------------------------------------------
	# Emulator things, WINS and WINC

	unless ($epoc_only)
		{

		# WINC uses lots of WINS libraries. 
		# Build WINC after the WINS libraries, but before the resources
		# since AIFTOOL is a WINC tool used in the resource step.
		#
		print FILE "call ${basename}_makefile wins\n";
		print FILE "call ${basename}_library  wins\n";

		if ($build_winc)
			{
			print FILE "\n";
			print FILE "call ${basename}_makefile winc\n";
			print FILE "call ${basename}_library  winc\n";
			print FILE "call ${basename}_target   winc\n";
			print FILE "\n";
			}

		print FILE "call ${basename}_resource wins\n";
		print FILE "call ${basename}_target   wins\n";
		print FILE "\n";

		# Install the colour version of the resources, in case
		# we need to run any WINS programs in the final stage
		#
		print FILE "call instcol cl\n";
		print FILE "\n";

		print FILE "call ${basename}_final    wins\n";
		print FILE "\n";

		if ($build_winc)
			{
			print FILE "call ${basename}_what     winc\n";
			print FILE "call ${basename}_check    winc\n";
			}
		print FILE "call ${basename}_what     wins\n";
		print FILE "call ${basename}_check    wins\n";
		print FILE "\n";
		}

	#--------------------------------------------------------
	# ARM things

	# Generic build(s) first, followed by the ASSPs (if any)
	#

	my $name;
	my $stage;
	my @armthings; # = ("arm4", "armi");
	if ($build_thumb)
		{
		push @armthings, "thumb";
		}
	if ($build_arm3)
		{
		push @armthings, "arm3";
		}
	if ($build_wd2)
		{
		push @armthings, "wd2";
		}
	if ($build_noarm4 == 0) # if it is not set build it.
		{
		push @armthings, "arm4";
		}
	if ($build_noarmi == 0) # if it is not set build it.
		{
		push @armthings, "armi";
		}
	push @armthings, (sort keys %arm_assplist);

	foreach $stage ("makefile", "library", "resource", "target", "final", "what", "check")
		{
		foreach $name (@armthings)
			{
			printf FILE "call ${basename}_%-8s $name\n", $stage;
			}
		print FILE "\n";
		}

	print FILE <<TAIL_EOF;

perl -e "\$time=localtime; print '=== ',$scriptbase,' finished ', \$time"
echo .

TAIL_EOF

	close FILE;
	print "Created $scriptbase.cmd\n";
	}


#--------------------------------------------------------------------
# Overall build, subdivided for multi-machine building

sub print_pcontrol
	{
	my ($label) = @_;

	my $scriptbase = $basename."_".$label;
	open FILE, ">$scriptbase.cmd" or die "can't create $scriptbase.cmd";

	print FILE <<HEAD_EOF;
\@echo off
setlocal
perl -e "\$time=localtime; print '=== ',$scriptbase,' started ', \$time"
echo .

goto build_%1

HEAD_EOF

	#========================================================
	# Getting Ready
	#
	# Building tools, include files, makefiles, resources
	# and libraries
	#
	 
	print FILE ":build_libs\n";
	print FILE "\n";

	#--------------------------------------------------------
	# Generic stuff first

	print FILE "call ${basename}_bldfiles\n";
	print FILE "call ${basename}_export\n";
	print FILE "\n";

	#--------------------------------------------------------
	# TOOLS, if any

	if ($build_tools)
		{
		print FILE "call ${basename}_makefile tools\n";
		print FILE "call ${basename}_library  tools\n";
		print FILE "call ${basename}_target   tools rel\n\n";
		}

	#--------------------------------------------------------
	# Emulator things, WINS and WINC, up to resources

	# WINC uses lots of WINS libraries. 
	# Build WINC after the WINS libraries, but before the resources
	# since AIFTOOL is a WINC tool used in the resource step.
	#
	print FILE "call ${basename}_makefile wins\n";
	print FILE "call ${basename}_library  wins\n";

	if ($build_winc)
		{
		print FILE "\n";
		print FILE "call ${basename}_makefile winc\n";
		print FILE "call ${basename}_library  winc\n";
		print FILE "call ${basename}_target   winc\n";
		print FILE "call ${basename}_what     winc\n";
		print FILE "call ${basename}_check    winc\n";
		print FILE "\n";
		}

	print FILE "call ${basename}_resource wins\n";
	print FILE "\n";

	#--------------------------------------------------------
	# ARM things

	# Generic build(s) first, followed by the ASSPs (if any)
	#

	my $name;
	my $stage;
	my @epocthings; # = ("arm4", "armi");
	if ($build_thumb)
		{
		push @epocthings, "thumb";
		}
	if ($build_arm3)
		{
		push @epocthings, "arm3";
		}
	if ($build_wd2)
		{
		push @epocthings, "wd2";
		}
	if ($build_noarm4 == 0) # if it is not set build it.
		{
		push @epocthings, "arm4";
		}
	if ($build_noarmi == 0) # if it is not set build it.
		{
		push @epocthings, "armi";
		}
	push @epocthings, (sort keys %arm_assplist);

	# For all EPOC things...

	foreach $stage ("makefile", "library", "resource")
		{
		foreach $name (@epocthings)
			{
			printf FILE "call ${basename}_%-8s $name\n", $stage;
			}
		print FILE "\n";
		}

	print FILE "goto :EOF\n";
	print FILE "\n";

	#========================================================
	# Completing the Emulator
	#
	 
	print FILE ":build_wins\n";
	print FILE "\n";

	print FILE "call ${basename}_bldfiles\n";
	print FILE "call ${basename}_target   wins\n";
	print FILE "call ${basename}_what     wins\n";
	print FILE "call ${basename}_check    wins\n";
	print FILE "goto :EOF\n";
	print FILE "\n";

	print FILE ":build_wins_final\n";
	print FILE "\n";

	# Install the colour version of the resources, in case
	# we need to run any WINS programs in the final stage
	#
	print FILE "call \\epoc32\\tools\\instcol cl\n";
	print FILE "\n";

	print FILE "call ${basename}_final    wins\n";
	print FILE "call ${basename}_what     wins\n";
	print FILE "call ${basename}_check    wins\n";
	print FILE "goto :EOF\n";
	print FILE "\n";

	#========================================================
	# Completing the ARM targets
	#
	 
	foreach $name (@epocthings)
		{
		print FILE ":build_$name\n";
		print FILE "\n";

		print FILE "call ${basename}_bldfiles\n";
		foreach $stage ("target", "final", "what", "check")
			{
			printf FILE "call ${basename}_%-8s $name\n", $stage;
			}
		print FILE "goto :EOF\n";
		print FILE "\n";
		}

	print FILE <<TAIL_EOF;

perl -e "\$time=localtime; print '=== ',$scriptbase,' finished ', \$time"
echo .

TAIL_EOF

	close FILE;
	print "Created $scriptbase.cmd\n";
	}


