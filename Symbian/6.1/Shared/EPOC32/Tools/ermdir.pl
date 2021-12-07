# ERMDIR.PL
#
# Copyright (c) 1999 Symbian Ltd.  All rights reserved.
#

use File::Path;


# THE MAIN PROGRAM SECTION
{
	unless (@ARGV) {
		&Usage();
	}

	rmtree([@ARGV]);
}

sub Usage () {
	print <<ENDHERESTRING;
Usage : perl ermdir.pl list_of_directories

  Removes the directories listed
ENDHERESTRING

	exit 1;
}
