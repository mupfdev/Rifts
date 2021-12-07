# epocaif.pl
#
# Copyright (c) 2001 Symbian Ltd.  All rights reserved.
#

# Wrapper to support the EPOC AIF Compiler


use FindBin;		# for FindBin::Bin
use File::Copy;		# for copy()
use Cwd;		# for cwd
use File::Basename;	# for basename()

my $PerlBinPath;    # fully qualified pathname of the directory containing this script

BEGIN {
# check user has a version of perl that will cope
	require 5.005_03;
# establish the path to the Perl binaries
	$PerlBinPath = $FindBin::Bin;	# X:/epoc32/tools
	$PerlBinPath =~ s/\//\\/g;	# X:\epoc32\tools
	use lib $PerlBinPath;
}

my $uppath="x";	    # will be initialised when first needed

my $epocroot = $ENV{EPOCROOT};
die "ERROR: Must set the EPOCROOT environment variable\n" if (!defined($epocroot));
$epocroot =~ s-/-\\-go;	# for those working with UNIX shells
die "ERROR: EPOCROOT must not include a drive letter\n" if ($epocroot =~ /^.:/);
die "ERROR: EPOCROOT must be an absolute path without a drive letter\n" if ($epocroot !~ /^\\/);
die "ERROR: EPOCROOT must not be a UNC path\n" if ($epocroot =~ /^\\\\/);
die "ERROR: EPOCROOT must end with a backslash\n" if ($epocroot !~ /\\$/);
die "ERROR: EPOCROOT must specify an existing directory\n" if (!-d $epocroot);

$epocroot=~ s-\\$--;		# chop trailing \\


sub print_usage
	{
#........1.........2.........3.........4.........5.........6.........7.....
	print <<USAGE_EOF;

Usage:
  epocaif [options] srcfile [-o outputfile] [-t tmpdir] [-b "bmps" | -m mbm]


The available options are

   -Ixxx  -- C++ preprocessor arguments
   -o	  -- output AIF file name including path
   -t	  -- tempory directory for intermediate files
   -b	  -- list of bitmaps Eg., "-b/c8\\location\\bmp1 /c8\\location\\bmp2.."
   -m	  -- compiled MBM file (alternative to -b)

The aif resource file is then passed through the C++ preprocessor, using any 
specified preprocessor arguments, and then compiled with RCOMP.EXE to 
generate a compiled resource.
The -m or -b option is used to generate a suitable MBM file, if required.
AIFTOOL then uses the MBM and the compiled resource to produce an AIF file


USAGE_EOF
	}

#-------------------------------------------------------
# Process commandline arguments
#
# Can't use the Getopt package because it doesn't like the -D and -I style options
#
my $sourcefile="";
my $opt_o="";
my $opt_h="";	
my $tmpdir="";
my $opt_v=0;
my $opt_b="";
my $opt_l="";
my $opt_m="";
my $TrgPath;

my $cpp_spec= "cpp -undef -C ";	    # preserve comments

my $errors = 0;
while (@ARGV)
	{
	my $arg = shift @ARGV;

	if ($arg =~ /^-I(.*)$/)
		{
		$cpp_spec .= "-I ";
		if ($1 eq "")
		    {
		    $arg = shift @ARGV;
		    }
		else
		    {
		    $arg = $1;
		    }
		$cpp_spec .= quoted_relative_path($arg)." ";
		next;
		}
	if ($arg =~ /^-v$/)
		{
		$opt_v =1;
		next;
		}
	if ($arg =~ /^-o(.*)$/)
		{
		$opt_o =$1;
		$TrgPath = $opt_o;
		next;
		}

	if ($arg =~ /^-t(.*)\\?$/)
		{
		$tmpdir =$1;
		next;
		}
	if ($arg =~ /^-b(.*)$/)
		{
		$opt_b =$1;
		next;
		}	
	if ($arg =~ /^-m(.*)$/)
		{
		$opt_m =$1;
		next;
		}	
	if ($arg =~ /^-l(.*)$/)
		{
		$opt_l =$1;
		next;
		}	

	if ($arg =~ /^-/)
		{
		print "Unknown arg: $arg\n";
		$errors++;
		next;
		}
	$sourcefile=$arg;
	}

if ($opt_m ne "" && $opt_b ne "")
	{
	print "Can't specify both -m and -b\n";
	$errors++;
	}

if ($errors || $sourcefile eq "")
	{
	print_usage();
	exit 1;
	}

my $rss_base = basename($sourcefile);
my ($rssfile) = split(/\./, $rss_base);	    # remove extension
my $rpp_name = "$tmpdir\\$rssfile.rpp";
my $outputfile="$tmpdir\\AIF.RSC";	
my $headerfile=$opt_h;

if ($opt_v)
	{
	print "* Source file:   $sourcefile\n";
	print "* Resource file: $outputfile\n" if ($outputfile ne "");
	}

$opt_o = "-o\"$outputfile\"" if ($outputfile ne "");
$opt_h = "-h\"$headerfile\"" if ($headerfile ne "");


#-------------------------------------------------------
# Run the preprocessor
#

$cpp_spec .= "-I $PerlBinPath\\..\\include ";	# extra path to support shared tools
$cpp_spec .= "-D_UNICODE ";
$cpp_spec .= "<\"$sourcefile\"";

print "* $cpp_spec > $rpp_name\n" if ($opt_v);

open RPP, ">$rpp_name" or die "* Can't write to $rpp_name";
open CPP, "$cpp_spec |" or die "* Can't execute cpp";
my $line;
while ($line=<CPP>)
	{
	print RPP $line;
	}
close RPP;
close CPP;
my $cpp_status = $?;
die "* cpp failed\n" if ($cpp_status != 0);

#-------------------------------------------------------
# Run the resource compiler
#

my $rcomp_spec = "rcomp -u ";
$rcomp_spec .= "$opt_o $opt_h -s\"$rpp_name\" -i\"$sourcefile\"";

print "* $rcomp_spec\n" if ($opt_v);
system($rcomp_spec);
if ($? != 0)
	{
	print "* RCOMP failed - deleting output files\n";
	unlink $outputfile if ($outputfile ne "");
	unlink $headerfile if ($headerfile ne "");
	exit 1;
	}
print "* deleting $rpp_name\n" if ($opt_v);
unlink $rpp_name;

#-------------------------------------------------------
# Run bmconv, if needed
#

if ($opt_b ne "")
	{
	print "* bmconv /q $tmpdir\\AIF.MBM $opt_b\n" if ($opt_v);
	system("bmconv /q $tmpdir\\AIF.MBM $opt_b");
	}
elsif ($opt_m ne "")
	{
	print "* copy $opt_m $tmpdir\\AIF.MBM\n" if ($opt_v); 
	copy($opt_m, "$tmpdir\\AIF.MBM"); 
	}
else
	{
	# no bitmap specified - this is legitimate
	unlink("$tmpdir\\AIF.MBM");
	}

#-------------------------------------------------------
# Run Aiftool
# Use a path relative to PerlBinPath, to allow for shared WINC tools
#

$PerlBinPath =~ /^(.*)\\/;
my $aiftool = "$1\\release\\winc\\urel\\aiftool.exe";
print "* $aiftool $tmpdir\\ \n" if ($opt_v);
system("$aiftool $tmpdir\\");
if ($? != 0)
	{
	print "* AIFTOOL failed\n";
	exit 1;
	}

print "* copy $tmpdir\\out.aif $TrgPath\n" if ($opt_v);
copy("$tmpdir\\out.aif", "$TrgPath");

unlink("$tmpdir\\aif.rsc");
unlink("$tmpdir\\aif.mbm");
unlink("$tmpdir\\out.aif");
exit 0;

#-------------------------------------------------------
# Subroutine: convert possibly absolute path into relative path
#

sub quoted_relative_path
    {
    my ($arg) = @_;
    return "\"$arg\"" if ($arg !~ /^\\/);	# not an absolute path
    if ($uppath eq "x")
	{
	$uppath=cwd;
	$uppath=~s-/-\\-go;		    # separator from Perl 5.005_02+ is forward slash
	$uppath=~s-^(.*[^\\])$-$1\\-o;	    # ensure path ends with a backslash
	$uppath=~s-\\([^\\]+)-\\..-og;	    # convert directories into ..
	$uppath=~s-^.:\\--o;		    # remove drive letter and leading backslash
	}
    $arg=~s-^\\--o;	# remove leading backslash from original path
    return "\"$uppath$arg\"";
    }

