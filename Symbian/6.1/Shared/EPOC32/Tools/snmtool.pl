# SNMTOOL.PL
#
# Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
#

use strict;
use integer;

BEGIN
	{
	my $perlScriptPath=$0;
	$perlScriptPath=~s/\//\\/g; # replace any forward-slashes with back-slashes
	$perlScriptPath=~s/(\\?)[^\\]+$/$1/; # get rid of this Perl-script's file-name
	unshift(@INC, $perlScriptPath); # can't do "use lib $perlScriptPath" here as "use lib" only seems to work with *hard-coded* directory names
	}
use PARSER;
use WRITER;

$|=1; # ensures that any progress information sent to the screen is displayed immediately and not buffered
if ((@ARGV==0) || ($ARGV[0]=~/\?/i) || ($ARGV[0]=~/-h/i) || ($ARGV[0]=~/\/h/i) || ($ARGV[0]=~/help/i))
	{
	die("\nVersion 021\n\nCharacter-set standard-names and MIB-enums tool\nCopyright (c) 2000 Symbian Ltd\n\nUsage:\n\n\tsnmtool <input-file> <output-file>\n\n");
	}
my $inputFileName=shift;
my $outputFileName=shift;
print "Generating $outputFileName...\n";
open(INPUT_FILE, "< $inputFileName") or die("Error: could not open \"$inputFileName\" for reading\n");
my %characerSets=();
&readInputFile(\*INPUT_FILE, $inputFileName, \%characerSets);
close(INPUT_FILE) or die("Error: could not close \"$inputFileName\"\n");
open(OUTPUT_FILE, "> $outputFileName") or die("Error: could not open \"$outputFileName\" for writing\n");
binmode OUTPUT_FILE;
&writeOutputFile(\*OUTPUT_FILE, \%characerSets);
close(OUTPUT_FILE) or die("Error: could not close \"$outputFileName\"\n");
print "complete\n\n";

sub readInputFile
	{
	my $fileHandle=shift;
	my $fileName=shift;
	my $characerSets=shift;
	my $line;
	my $strippedDownLine;
	my $identifier="";
	for (;;)
		{
		($line, $strippedDownLine)=&nextNonEmptyStrippedDownLine($fileHandle);
		if ($strippedDownLine eq "")
			{
			last;
			}
		if ($strippedDownLine=~/^CharacterSet\s+0x([0-9a-f]+)$/i)
			{
			$identifier=lc($1);
			$characerSets->{$identifier}=[[], []];
			}
		else
			{
			if ($identifier eq "")
				{
				close($fileHandle);
				die("Error: unexpected line in \"$fileName\":\n    $line\n");
				}
			if ($strippedDownLine=~/^StandardName\s+"(.*)"$/i)
				{
				push @{$characerSets->{$identifier}->[0]}, $1;
				}
			elsif ($strippedDownLine=~/^MibEnum\s+([0-9]+)$/i)
				{
				push @{$characerSets->{$identifier}->[1]}, $1;
				}
			else
				{
				close($fileHandle);
				die("Error: unexpected line in \"$fileName\":\n    $line\n");
				}
			}
		}
	}

sub writeOutputFile
	{
	my $fileHandle=shift;
	my $characerSets=shift;
	&writeUids($fileHandle, 0x1000589b, 0, 0);
	my $characerSetIdentifier;
	my $identifier;
	my $data;
	while (($identifier, $data)=each(%$characerSets))
		{
		&write32($fileHandle, hex($identifier));
		&writePositiveIntegerCompacted15($fileHandle, scalar(@{$data->[0]}));
		&writePositiveIntegerCompacted15($fileHandle, scalar(@{$data->[1]}));
		my $standardName;
		foreach $standardName (@{$data->[0]})
			{
			&writePositiveIntegerCompacted15($fileHandle, length($standardName));
			&writeString($fileHandle, $standardName);
			}
		my $mibEnum;
		foreach $mibEnum (@{$data->[1]})
			{
			&writePositiveIntegerCompacted30($fileHandle, $mibEnum);
			}
		}
	}

