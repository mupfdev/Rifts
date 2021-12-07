# E32ENV.PM
#
# Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
#

# Contains information for makmake and associated e32tools perl programs
# within the Epoc32 Environment

package E32env;


use vars qw(%Data);

BEGIN {
	my $epocroot = $ENV{EPOCROOT};
	die "ERROR: Must set the EPOCROOT environment variable\n" if (!defined($epocroot));
	$epocroot =~ s-/-\\-go;	# for those working with UNIX shells
	die "ERROR: EPOCROOT must not include a drive letter\n" if ($epocroot =~ /^.:/);
	die "ERROR: EPOCROOT must be an absolute path without a drive letter\n" if ($epocroot !~ /^\\/);
	die "ERROR: EPOCROOT must not be a UNC path\n" if ($epocroot =~ /^\\\\/);
	die "ERROR: EPOCROOT must end with a backslash\n" if ($epocroot !~ /\\$/);
	die "ERROR: EPOCROOT must specify an existing directory\n" if (!-d $epocroot);

	$epocroot=~ s-\\$--;		# chop trailing \\

	$Data{EPOCPath} = $epocroot."\\EPOC32\\";

	$Data{EPOCIncPath} = $epocroot."\\EPOC32\\INCLUDE\\";
	$Data{BldPath} = $epocroot."\\EPOC32\\BUILD\\";
#regression hack
#	$Data{LinkPath} = $epocroot."\\EPOC32\\LIBRARY\\";
	$Data{LinkPath} = $epocroot."\\EPOC32\\RELEASE\\";
#regression hack end
	$Data{RelPath} = $epocroot."\\EPOC32\\RELEASE\\";
	$Data{EPOCToolsPath} = $epocroot."\\EPOC32\\TOOLS\\";
	$Data{RomPath} = $epocroot."\\EPOC32\\ROM\\";

	$Data{DataPath} = "Z\\SYSTEM\\DATA\\";
}

1;
