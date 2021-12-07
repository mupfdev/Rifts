#
# Pjava_g Launcher
#
# Copyright (c) 1999-2001 Symbian Ltd.  All rights reserved.
#

use Cwd;

$numArgs = $#ARGV + 1;

$epocroot = &getEpocroot;
$drive = &getDrive;
$pjava_g = $drive . $epocroot . "epoc32" . "\\" . "release\\wins\\udeb\\pjava_g.exe";

-e $pjava_g || die 	"ERROR: File \"$pjava_g\" not found.\n\n" .
	    			"The EPOCROOT environment variable does not identify\n" .
	    			"a valid pjava_g.exe installation on this drive.\n" . 
					"EPOCROOT must be an absolute path to an existing\n" .
		    		"directory - it should have no drive qualifier and\n" .
					"must end with a backslash.\n";

# Append any command line arguments
for ($i = 0; $i < $numArgs; $i++)
	{
	$pjava_g .= " \"" . $ARGV[$i] ."\"";
	}

# Run pjava_g
system ($pjava_g);


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
