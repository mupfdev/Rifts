#
# mtmgen 
#
# Copyright (c) 1999-2001 Symbian Ltd.  All rights reserved.
#

use Cwd;
use FindBin;

$numArgs = $#ARGV + 1;


#check if we have any arguments
if($numArgs == 0)
    {
    displayHelp();
    }
else
    {
    
    #the command switch containing the build instruction
    $buildInstLoc = 0;

    #default to running the debug version
    $targetType = "";
    $epocroot = &getEpocroot;
    $toolsRoot = &getToolsRoot;
    $drive = &getDrive;

    #determin if a specific deb rel version has been specified
    if($ARGV[0] =~/-urel/i)
		{
		$targetType="urel";
		$buildInstLoc = 1;
		}

    if($ARGV[0] =~/-udeb/i)
		{
		$targetType="udeb";
		$buildInstLoc = 1;
		}
    
    # determine what we want mtmgen to do
    if($ARGV[$buildInstLoc] =~ /-\w*[iu]/i
       || $targetType eq "urel"
       || $targetType eq "udeb")
		{
		if($targetType eq "")
			    {
			    $targetType="udeb";
			    }

		# check if it is the default udeb emulator
		if($targetType eq "udeb")
			    {
			    #tell the user how to specify the urel
			    print "The mtm will be installed / uninstalled from the udeb emulator\n";
			    print "To specify the the urel emulator use\n";
			    print "mtmgen -urel ";
			    for ($i = 0; $i < $numArgs; $i++)
					{
					print $ARGV[$i]." ";
					}
			    }
		# we are doing a install or uninstall or udeb urel was specified so call the wins version
		$mtmgen = $drive . $epocroot . "epoc32" . "\\" . "release\\wins\\$targetType\\mtmgen.exe";
		}
    else
		{
		#we are generating and -urel or -udeb not specified run winc
		$mtmgen = $toolsRoot ."\\". "epoc32" . "\\" . "release\\winc\\urel\\mtmgen.exe";
		}

    -e $mtmgen || die 	"ERROR: File \"$mtmgen\" not found.\n\n";

    # Append any command line arguments
    for ($i = 0; $i < $numArgs; $i++)
		{
		$mtmgen .= " \"" . $ARGV[$i] ."\"";
		}

    # Run mtmgen
    system ($mtmgen);

    }
#
# Obtain the absoulte path to the root of the tools
#
sub getToolsRoot()
	{
	use FindBin qw($Bin);
	my $sharedLocation = "/epoc32/tools";
	my $indexOf = index(lc($Bin),$sharedLocation);

	if ($indexOf == -1)
		{
		exit (-1);
		}

	my $toolsRoot = substr(lc($Bin),0,$indexOf);

	$toolsRoot =~ s/\//\\/g;

	return $toolsRoot;
	}

#
# Determines, validates, and returns EPOCROOT.
#
sub getEpocroot
    {
    my $epocroot = $ENV{EPOCROOT};
    die "ERROR: Must set the EPOCROOT environment variable.\n"
	if (!defined($epocroot));
    $epocroot =~ s-/-\\-go;	# for those working with UNIX shells
    die "ERROR: EPOCROOT must be an absolute path, " .
	"not containing a drive letter.\n" if ($epocroot !~ /^\\/);
    die "ERROR: EPOCROOT must not be a UNC path.\n" if ($epocroot =~ /^\\\\/);
    die "ERROR: EPOCROOT must end with a backslash.\n" if ($epocroot !~ /\\$/);
    die "ERROR: EPOCROOT must specify an existing directory.\n" 
	if (!-d $epocroot);
    return $epocroot;
    }

#
# Determines and returns the current drive, if any.
#
sub getDrive
	{
    my $wd = cwd;

    if($wd =~ /^([a-zA-Z]:)/)
    	{
		$drive = $1;
    	}
    else
    	{
		# Perhaps we're on a machine that has no drives.
		$drive = "";
    	}
    return $drive;
	}


#
# Displays the help text for mtmgen
# which mtmgen tries to write a log
# file which it does not tell the user about
#
sub displayHelp()
    {
    print "Messaging DAT file generator 1.00(0)\n\n";

    print "MTMGEN [-urel|-udeb] -<Flags> <Path of configuration file> <Path for DAT File>\n\n";
    print "Flags: u - Uninstall MTM, g - Generate DAT File, i - Install MTM\n\n";
    print "This SDK contains both wins and winc versions of the mtmgen tool.\n";
    print "The wins version of mtmgen is run if -urel of -udeb is specified.\n";
    print "The wins version will also be run in either -u or -i flags are specified.\n";
    print "The winc version of the mtmgen will be run if neither -urel of -udeb are\n";
    print "specified and only the generate (-g) flag is set.\n\n";
    print "By default MTMs are (un)installed from the udeb emulator.\n\n";
    print "During processing mtmgen writes information to a file (mtmgen.txt)\n";
    print "This file is located in the c:\\logs\\mtmgen\\ directory which must\n";
    print "be created before the log file can be written.\n\n";
    print "Note file locations used by mtmgen will be relative to the emulator if\n";
    print "the wins version is run and relative to the development PC file system\n";
    print "if the winc version is run\n";
    }







