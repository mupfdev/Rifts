#
# Setupcomms Launcher
#
# Copyright (c) 1999-2001 Symbian Ltd.  All rights reserved.
#
# Depends on the current working directory providing
# the drive of the currently used SDK.
#

use Cwd;

#
# Check the argument(s), if any.
#
$numArgs = $#ARGV + 1;

if($numArgs == 0) {
    &launchT_commsDb("udeb");
    exit(0);
}

if($numArgs > 1) {
    &printHelp;
    die "ERROR: Too many arguments.\n";
}

if(lc($ARGV[0]) eq "-rel") {
    &launchT_commsDb("urel");
    exit(0);
}

if(lc($ARGV[0]) eq "-help") {
    &printHelp;
    exit(0);
}

# Error, unknown argument.
&printHelp;
die "ERROR: Unknown argument " . "\"" . $ARGV[0] . "\".\n";

sub launchT_commsDb
{
    my $type = shift;
    $epocroot = &getEpocroot;
    $drive = &getDrive;
    $emu = $drive . $epocroot . "epoc32" . "\\" 
	. "release\\wins\\" . $type . "\\" . "T_editdb.exe";
    -e $emu ||
	die "ERROR: File \"$emu\" not found.\n\n" .
	    "The EPOCROOT environment variable does not identify\n" .
	    "a valid setupcomms installation on this drive.\n" . 
		"EPOCROOT must be an absolute path to an existing\n" .
		    "directory - it should have no drive qualifier and\n" .
			"must end with a backslash.\n";

	#add the stuff to use the console
	$emu.=" -MConsole --";
			
    # If the execute is successful, this never returns.
    exec($emu) || die "Failed to execute setupcomms \"$emu\": $!";
}

sub printHelp
{
    print "Setupcomms Launcher\n";
    print "Syntax :       setupcomms [-rel -help]\n";
    print "(no options)   Launch active debug setupcomms\n";
    print "-rel           Launch active release setupcomms\n";
    print "-help          Output this help message\n";
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
    if($wd =~ /^([a-zA-Z]:)/) {
	$drive = $1;
    } else {
	# Perhaps we're on a machine that has no drives.
	$drive = "";
    }
    return $drive;
}
