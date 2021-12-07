# EMKDIR.PL
#
# Copyright (c) 1999 Symbian Ltd.  All rights reserved.
#

use File::Path;


# THE MAIN PROGRAM SECTION
{
	unless (@ARGV) {
		&Usage();
	}

#	temp hack for old perl
	foreach (@ARGV) {
		s-\\-\/-go;
	}
	mkpath([@ARGV]);
}

sub Usage () {
	print <<ENDHERESTRING;
Usage : perl emkdir.pl list_of_directories

  Creates the directories listed
ENDHERESTRING

	exit 1;
}
