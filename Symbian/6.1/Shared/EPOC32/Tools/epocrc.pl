# epocrc.pl
#
# Copyright (c) 2000 Symbian Ltd.  All rights reserved.
#

# Wrapper to support the EPOC Resource Compiler

use Cwd;

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
  epocrc [options] srcfile [-o outputfile] [-h headerfile]   

Compile an EPOC resource file, optionally generating a compiled resource 
file and an associated header file.

The available options are

   -Dxxx, -Ixxx      -- C++ preprocessor arguments
   -u                -- compile for use with Unicode EPOC
   -t tmpdir         -- specify a directory for temporary files

The resource file is first passed through the C++ preprocessor, using any 
specified preprocessor arguments, and then compiled with RCOMP.EXE to 
generate a compiled resource and the associated header file. 

All intermediate files are generated into a temporary directory.

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
my $unicode=0;
my $opt_v=0;

my $cpp_spec= "cpp -undef -C ";	    # preserve comments

my $errors = 0;
while (@ARGV)
	{
	my $arg = shift @ARGV;
	if ($arg =~ /^-D(.*)$/)
		{
		if ($1 eq "")
		    {
		    $arg = shift @ARGV;
		    $cpp_spec .= "-D \"$arg\" ";
		    }
		else
		    {
		    $cpp_spec .= "$arg ";
		    }
		next;
		}
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
	if ($arg =~ /^-u$/)
		{
		$unicode =1;
		next;
		}
	if ($arg =~ /^-o(.*)$/)
		{
		$opt_o =$1;
		next;
		}
	if ($arg =~ /^-h(.*)$/)
		{
		$opt_h =$1;
		next;
		}
	if ($arg =~ /^-t(.*)\\?$/)
		{
		$tmpdir ="$1\\";
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

if ($errors || $sourcefile eq "")
	{
	print_usage();
	exit 1;
	}

use File::Basename;
my $rss_base = basename($sourcefile);
my ($rssfile) = split(/\./, $rss_base);	    # remove extension
my $rpp_name = $tmpdir. $rssfile . ".rpp";
my $outputfile=$opt_o;	
my $headerfile=$opt_h;

if ($opt_v)
	{
	print "* Source file:   $sourcefile\n";
	print "* Resource file: $outputfile\n" if ($outputfile ne "");
	print "* Header file:   $headerfile\n" if ($headerfile ne "");
	}

$opt_o = "-o\"$outputfile\"" if ($outputfile ne "");
$opt_h = "-h\"$headerfile\"" if ($headerfile ne "");

#-------------------------------------------------------
# Run the preprocessor
#

$cpp_spec .= "-D_UNICODE " if ($unicode);
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
# Copy rpp files to epoc32\localisation
#

my $outfile = basename($outputfile);
chomp($outfile);

if($outfile ne "AIF.RSC")
	{
	if (-e "$epocroot\\epoc32\\localisation\\$rssfile.rpp") 
		{
		unlink("$epocroot\\epoc32\\localisation\\$rssfile.rpp");
		}
	print "* copy $rpp_name $epocroot\\epoc32\\localisation\\$rssfile.rpp\n" if ($opt_v);
	system("copy $rpp_name $epocroot\\epoc32\\localisation\\$rssfile.rpp");
	}


#-------------------------------------------------------
# Run the resource compiler
#

my $rcomp_spec = "rcomp ";
$rcomp_spec .= "-u " if ($unicode);
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

