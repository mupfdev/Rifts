# INSTCOL.PL
#
# Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
#

# Install color or black-and-white resources


use Getopt::Long;
use File::Copy;

my $opt_v;
GetOptions("v" => \$opt_v);	# -v for verbose


if (@ARGV!=1 || ! ($ARGV[0] =~ /^(bw|cl)$/i))
	{
#........1.........2.........3.........4.........5.........6.........7.....
	print <<USAGE_EOF;

Syntax is "instcol bw" or "instcol cl"

USAGE_EOF
	exit 1;
	}

# Check for EPOCROOT

my $epocroot = $ENV{EPOCROOT};
die "ERROR: Must set the EPOCROOT environment variable\n" if (!defined($epocroot));
$epocroot =~ s-/-\\-go;	# for those working with UNIX shells
die "ERROR: EPOCROOT must not include a drive letter\n" if ($epocroot =~ /^.:/);
die "ERROR: EPOCROOT must be an absolute path without a drive letter\n" if ($epocroot !~ /^\\/);
die "ERROR: EPOCROOT must not be a UNC path\n" if ($epocroot =~ /^\\\\/);
die "ERROR: EPOCROOT must end with a backslash\n" if ($epocroot !~ /\\$/);
die "ERROR: EPOCROOT must specify an existing directory\n" if (!-d $epocroot);

my $pattern = lc $ARGV[0];
my $wins_udeb_z = $epocroot."epoc32\\release\\wins\\udeb\\z";
my $wins_urel_z = $epocroot."epoc32\\release\\wins\\urel\\z";

# To do: 
#
# One day, build the resources into \epoc32\data\Z and install them from there
# using something like
#
# my $data_z      = $epocroot."epoc32\\Data\\z";
# install($data_z, "\\.m$pattern\$", $wins_udeb_z, ".mbm");

print "Installing all *.m$pattern files as *.mbm\n";
install($wins_udeb_z, "\\.m$pattern\$", $wins_udeb_z, ".mbm");
install($wins_urel_z, "\\.m$pattern\$", $wins_urel_z, ".mbm");

print "Installing all *.a$pattern files as *.aif\n";
install($wins_udeb_z, "\\.a$pattern\$", $wins_udeb_z, ".aif");
install($wins_urel_z, "\\.a$pattern\$", $wins_urel_z, ".aif");

print "Installing wsini.i$pattern as wsini.ini\n";
install("$wins_udeb_z\\System\\Data", "^wsini\.i$pattern\$", "$wins_udeb_z\\System\\Data", "wsini.ini");
install("$wins_urel_z\\System\\Data", "^wsini\.i$pattern\$", "$wins_urel_z\\System\\Data", "wsini.ini");

exit(0);

sub install
    {
    my ($sourcedir, $pattern, $destdir, $replacement) = @_;
    if (! -d $sourcedir)
	{
	print "* missing source directory $sourcedir\n" if ($opt_v);
	return;
	}

    print "* Checking $sourcedir for $pattern\n" if ($opt_v);

    do_install($sourcedir, $pattern, $destdir, $replacement);
    }

sub do_install
    {
    my ($sourcedir, $pattern, $destdir, $replacement) = @_;

    # Read all of the directory entries except . and .. in to a local list.

    opendir SOURCEDIR, $sourcedir or print "Cannot read directory $sourcedir\n" and return;
    my @list = grep !/^\.\.?$/, readdir SOURCEDIR;
    closedir SOURCEDIR;

    my @files;
    my $entry;
    foreach $entry (@list)
	{
	if (-d "$sourcedir\\$entry")
	    {
	    # recurse over subdirectories
	    do_install("$sourcedir\\$entry", $pattern, "$destdir\\$entry", $replacement);
	    next;
	    }
	if ($entry =~ /$pattern/i)
	    {
	    push @files, $entry;
	    }
	}

# To do: 
#   It will be necessary to generate destination directories is working from
#   data_z, in which case this code may be useful.
#
#    if (! @files)
#	{
#	print "* no files matching $pattern in $sourcedir\n" if ($opt_v);
#	return;
#	}
#
#   # create destination directory if necessary
#
#   if (! -d $destdir)
#	{
#	print "* creating destination directory $destdir\n" if ($opt_v);
#	my $path = $destdir;
#	$path =~ s-\\-\/-go;	# mkpath requires UNIX-style directory separators
#	mkpath ([$path], $opt_v);
#	}

    # copy and rename the files

    foreach $entry (@files)
	{
	my $destname = $entry;
	$destname =~ s/$pattern/$replacement/i;

	print "*   copy $sourcedir\\$entry\n*   to   $destdir\\$destname\n" if ($opt_v);
	copy ("$sourcedir\\$entry", "$destdir\\$destname");
	}

    return;
    }




