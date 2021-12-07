# CHECKGCC.PM
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
#


# module for checking gcc is set up correctly

package CheckGcc;


BEGIN {
	# die if CPP.EXE in a dodgy place in the path
	my @Paths=split ';', $ENV{Path};
	unshift @Paths,'.';	# add the current directory
	foreach (@Paths) {
		s-/-\\-go;	# for those working with UNIX shells
		s-^(.*[^\\])$-$1\\-o;   # ensure path ends with a backslash
		if ((-e $_.'CPP.EXE') or (-e $_.'CPP.BAT') or (-e $_.'CPP.CMD')) {
			unless (/\\GCC\\BIN\\$/i) {
				die
					"ERROR: First CPP executable found in path is in $_,\n",
					"but the required CPP.EXE was expected to be found in a directory\n",
					"with a name ending in \\GCC\\BIN\\, where the Cygnus tools\n",
					"this program depends upon are stored.\n",
					"Is your path set up correctly?\n"
				;
			}
			return;
		}
	}
	die "ERROR: CPP executable not found in path\n";

}

1;
