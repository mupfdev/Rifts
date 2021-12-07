# memtrace.pl
#
# Copyright (c) 2000-2001 Symbian Ltd.  All rights reserved.
#

#
# Postprocess EPOC memory usage trace file
#

require 5.003_07;	# ActivePerl Build 518
no strict 'vars';
use English;
use Getopt::Long;

# Standard Symbian boilerplate to find and load E32env library
my $PerlLibPath;
BEGIN
	{
	foreach (split ';', $ENV{Path})
		{
		s-/-\\-go;	# for those working with UNIX shells
		s-^(.*[^\\])$-$1\\-o;   # ensure path ends with a backslash
		if (-e $_.'memtrace.pl')
			{
			$PerlLibPath=uc $_;
			last;
			}
		}
	}
use lib $PerlLibPath;
use Modload;
Load_SetModulePath($PerlLibPath);


my $emulproc = quotemeta("epoc[00000000]0001::");
my $apprun = quotemeta("apprun[10003a4b]");
my $ramdrive = quotemeta("TheRamDriveChunk");

my @chunknames;	# Array of chunk names, indexed by chunkid
my @traces;		# Array of chunk traces, each trace being an array
				# of (tick,chunkid,size) triples
my @chunkgroup;	# Group that a chunk belongs to, indexed by chunkid
my @groupnames;	# Array of chunk group names (normally a group==a process)
my @groups;		# Array of chunk groups, each group being an array of chunkids

my %opts;
my $result = GetOptions (\%opts, "detailed", "help");
if($result && ($opts{'help'} || $#ARGV<0))
	{
	&help;
	exit 0;
	}
if(!$result || $#ARGV>0)
	{
	&usage;
	exit 1;
	}

my $file = $ARGV[0];
open TRACE,$file or die "Error: Can't open trace file \"$file\".\n";

#
# Parse trace file
#
my %current;	# chunkids hashed by DChunk address
my $nextchunkid;
while(<TRACE>)
	{
	if (/MT:C\s+(\d+)\s+([0-9a-fA-F]+)\s+(.+)\s*$/)
		{
		$current{$2} = $nextchunkid++;
		push @chunknames, $3;
		}
	elsif (my ($tick, $addr, $size, $name) =
		   (/MT:A\s+(\d+)\s+([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+(.+)\s*$/))
		{
		my $chunkid = $current{$addr};
		die "Error: Parsing failure - is trace file complete ?"
			unless (defined $chunkid);
		push @traces, [0+$tick, $chunkid, hex($size)];

		# Check whether chunk has been renamed to something more useful
		$chunknames[$chunkid] = $name
			if (($chunknames[$chunkid] =~ /^$emulproc/io) ||
				($chunknames[$chunkid] =~ /^$apprun/io));
		}
	elsif (/MT:D\s+(\d+)\s+([0-9a-fA-F]+)\s+(.+)\s*$/)
		{
		die "Error: Parsing failure" unless (defined $current{$2});
		push @traces, [0+$1, $current{$2}, 0];
		delete $current{$2};
		}
	elsif (/(MT:.\s+.*)/)
		{
		printf "Warning: Unrecognised trace line \"$1\".\n";
		}
	}
close TRACE;
die "Error: File \"$file\" does not contain any memory traces.\n"
  unless ($#chunknames>0);
# for (0..$#chunknames) { printf "$_: $chunknames[$_]\n" };	# debug


#
# Group chunks together by name
#
for (0..$#chunknames)
	{
	my $chunkid = $_;
	my $name = $chunknames[$chunkid];
	$name = $1 if ($name =~ /($ramdrive)$/i);	# Special handling for ramdrive
	$name = $1 if ($name =~ /^$emulproc(.*)/i);	# Use thread names on Emulator
	($name) = ($name =~ /([^:]+)/);				# otherwise strip thread name

	# yuck! linear search
	my $found = 0;
	for (0..$#groupnames)
		{
		my $groupid = $_;
		if ($groupnames[$groupid] eq $name)
			{
			$found = 1;
			push @{$groups[$groupid]}, $chunkid;
			$chunkgroup[$chunkid] = $groupid;
			last;
			}
		}
	
	if (!$found)
		{
		push @groupnames, $name;
		push @groups, [$chunkid];
		$chunkgroup[$chunkid] = $#groups;
		}
	}
# for (0..$#groupnames) { printf "$groupnames[$_]: @{$groups[$_]}\n" };	# debug

# Strip instance number (if any) from group name for presentation
for (0..$#groupnames)
	{
	$groupnames[$_] = $1 if ($groupnames[$_] =~ /^([^]]+]?)/);
	}

#
# Output
#
my @chunksizes; # Array of chunk sizes, indexed by chunkid
for (0..$#chunknames) { $chunksizes[$_] = 0 };
	
if ($opts{'detailed'})
	{
	# Detailed output

	foreach my $name (@groupnames) { print ",\"$name\"" };
	print "\n";

	# Uses hacky method to determine whether on Emulator or Target
	my $tickdiv = ($chunknames[0] =~ /^$emulproc/io) ? 10 : 64;

	my ($oldtick, $minitick) = (0,0);
	my @groupsizes;
	for my $trace (@traces)
		{
		my ($tick, $chunkid, $size) = @$trace;
		if ($oldtick != $tick)
			{
			$oldtick = $tick;
			$minitick=0;
			}

		$chunksizes[$chunkid] = $size;
		my $groupid=$chunkgroup[$chunkid];
		my $groupsize = 0;
		foreach $chunkid (@{$groups[$groupid]})
			{
			$groupsize += $chunksizes[$chunkid];
			}
		$groupsizes[$groupid] = $groupsize;

		print $tick/$tickdiv + ($minitick++)/1000000;
		foreach $groupsize (@groupsizes)
			{
			if ($groupsize)
				{
				printf ",%d", $groupsize/1024;
				}
			else
				{
				print ',';		# make output prettier by omitting 0s
				}
			}
		print "\n";
		}
	}
else
	{
	# Summary output

	my @grouphighs;
	for my $trace (@traces)
		{
		my ($tick, $chunkid, $size) = @$trace;
		$chunksizes[$chunkid] = $size;
		my $groupid=$chunkgroup[$chunkid];
		my $groupsize = 0;
		foreach $chunkid (@{$groups[$groupid]})
			{
			$groupsize += $chunksizes[$chunkid];
			}
		$grouphighs[$groupid] = $groupsize
			if (!defined($grouphighs[$groupid]) ||
				($grouphighs[$groupid] < $groupsize));
# printf "$chunkid -> $groupid, $groupsize\n";	# debug
	}

	printf "\"Process\", Size [K]\n";
	for (0..$#groupnames)
		{
		printf "\"$groupnames[$_]\", %d\n", $grouphighs[$_]/1024;
		}
	}
exit 0;


sub help ()
	{
	my $build;
	
	&Load_ModuleL('E32TPVER');
	print "\nmemtrace - " .
	  "Postprocess EPOC memory usage trace (Build ", &E32tpver, ")\n";
	&usage;
	}
	
sub usage ()
	{
	print <<EOF

Usage:
  memtrace [-d] <logfile>

Where:
  <logfile>     Memory usage trace file.

Options:
  -d            Produce a detailed listing.
EOF
	;
	}
