# CNVTOOL.PL
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
	die("\nVersion 021\n\nCharacter-set conversion-table generating tool\nCopyright (c) 2000 Symbian Ltd\n\nUsage:\n\n\tcnvtool <control-file> <source-file> <output-file> [options]\n\nwhere the following options are available (each has a short form and a long form which are shown below separated by a '|'):\n\n\t-s | -generateSourceCode\n\t-c | -columns(<a>: <b>, <c>)\n\t-r | -omitReplacementForUnconvertibleUnicodeCharacters\n\t-p | -cutOutAnyPrivateUseUnicodeCharacterSlotsBeingUsed\n\t-u | -sourceFilesToSubtract(<a>, <b>, ...)\n\n");
	}
my $generateSourceCode=0;
my @columns=(2, 1, 2);
my $omitReplacementForUnconvertibleUnicodeCharacters=0;
my $cutOutAnyPrivateUseUnicodeCharacterSlotsBeingUsed=0;
my @sourceFilesToSubtract=();
my $flattenHashAndSave=0; # this flag is not published for use outside of the CHARCONV component
&extractCommandLineFlags(\$generateSourceCode, \@columns, \$omitReplacementForUnconvertibleUnicodeCharacters, \$cutOutAnyPrivateUseUnicodeCharacterSlotsBeingUsed, \@sourceFilesToSubtract, \$flattenHashAndSave);
(!$omitReplacementForUnconvertibleUnicodeCharacters || $generateSourceCode) or die("Error: bad combination of flags\n");
my $controlFile=shift;
my $sourceFile=shift;
my $outputFile=shift;
print("Generating $outputFile...\n");
my $uid=0;
my $endiannessAsText='';
my $endianness=0;
my $replacementForUnconvertibleUnicodeCharacters='';
my @foreignVariableByteData=();
my @foreignToUnicodeData=();
my @unicodeToForeignData=();
my %foreignCharacterCodes=();
my %unicodeCharacterCodes=();
my %preferredForeignCharacterCodesForConflictResolution=();
my %preferredUnicodeCharacterCodesForConflictResolution=();
my %additionalSubsetTables=();
my %privateUseUnicodeCharacterSlotsUsed=();

print("    reading $controlFile...\n");
open(CONTROL_FILE, "< $controlFile") or die("Error: could not open \"$controlFile\" for reading\n");
&readHeaderFromControlFile(\*CONTROL_FILE, $controlFile, $generateSourceCode, \$uid, \$endiannessAsText, \$endianness, \$replacementForUnconvertibleUnicodeCharacters, $flattenHashAndSave);
&readForeignVariableByteDataFromControlFile(\*CONTROL_FILE, $controlFile, \@foreignVariableByteData);
&readOneDirectionDataFromControlFile(\*CONTROL_FILE, $controlFile, \@foreignToUnicodeData, \%preferredUnicodeCharacterCodesForConflictResolution, \%additionalSubsetTables, 1);
&readOneDirectionDataFromControlFile(\*CONTROL_FILE, $controlFile, \@unicodeToForeignData, \%preferredForeignCharacterCodesForConflictResolution, \%additionalSubsetTables, 0);
close(CONTROL_FILE) or die("Error: could not close \"$controlFile\"\n");

print("    reading $sourceFile...\n");
open(SOURCE_FILE, "< $sourceFile") or die("Error: could not open \"$sourceFile\" for reading\n");
&readSourceFile(\*SOURCE_FILE, $sourceFile, \%foreignCharacterCodes, \%unicodeCharacterCodes, \@columns, $cutOutAnyPrivateUseUnicodeCharacterSlotsBeingUsed, \%privateUseUnicodeCharacterSlotsUsed, 0);
close(SOURCE_FILE) or die("Error: could not close \"$sourceFile\"\n");

my $sourceFileToSubtract;
foreach $sourceFileToSubtract (@sourceFilesToSubtract)
	{
	print("    subtracting from $sourceFileToSubtract...\n");
	open(SOURCE_FILE_TO_SUBTRACT, "< $sourceFileToSubtract") or die("Error: could not open \"$sourceFileToSubtract\" for reading\n");
	&readSourceFile(\*SOURCE_FILE_TO_SUBTRACT, $sourceFileToSubtract, \%foreignCharacterCodes, \%unicodeCharacterCodes, \@columns, $cutOutAnyPrivateUseUnicodeCharacterSlotsBeingUsed, \%privateUseUnicodeCharacterSlotsUsed, 1);
	close(SOURCE_FILE_TO_SUBTRACT) or die("Error: could not close \"$sourceFileToSubtract\"\n");
	}

&warnIfAnyPrivateUseUnicodeCharacterSlotsBeingUsed(\%privateUseUnicodeCharacterSlotsUsed);
&resolveConflictsAndFlattenArraysToScalars(\%foreignCharacterCodes, \%preferredForeignCharacterCodesForConflictResolution, 'Unicode', 'foreign');
&resolveConflictsAndFlattenArraysToScalars(\%unicodeCharacterCodes, \%preferredUnicodeCharacterCodesForConflictResolution, 'foreign', 'Unicode');
&checkForeignVariableByteData($endianness, \@foreignVariableByteData, \@foreignToUnicodeData);

print("    writing $outputFile...\n");
open(OUTPUT_FILE, "> $outputFile") or die("Error: could not open \"$outputFile\" for writing\n");
if ($generateSourceCode)
	{
	my @sourceCodeOfForeignToUnicodeIndexedTables16=();
	my @sourceCodeOfForeignToUnicodeKeyedTables1616=();
	my @sourceCodeOfForeignToUnicodeKeyedTables16OfIndexedTables16_indexedEntries=();
	my @sourceCodeOfForeignToUnicodeKeyedTables16OfIndexedTables16_keyedEntries=();
	my @sourceCodeOfUnicodeToForeignIndexedTables16=();
	my @sourceCodeOfUnicodeToForeignKeyedTables1616=();
	my @sourceCodeOfUnicodeToForeignKeyedTables16OfIndexedTables16_indexedEntries=();
	my @sourceCodeOfUnicodeToForeignKeyedTables16OfIndexedTables16_keyedEntries=();
	my @sourceCodeOfTopLevelStructures=();
	&writeSourceCodeHeader(\*OUTPUT_FILE, $outputFile, $replacementForUnconvertibleUnicodeCharacters);
	&writeSourceCodeForeignVariableByteData(\@sourceCodeOfTopLevelStructures, \@foreignVariableByteData);
	&writeSourceCodeOneDirectionData(\@sourceCodeOfTopLevelStructures, \@sourceCodeOfForeignToUnicodeIndexedTables16, \@sourceCodeOfForeignToUnicodeKeyedTables1616, \@sourceCodeOfForeignToUnicodeKeyedTables16OfIndexedTables16_indexedEntries, \@sourceCodeOfForeignToUnicodeKeyedTables16OfIndexedTables16_keyedEntries, \@foreignToUnicodeData, \%unicodeCharacterCodes, 1);
	&writeSourceCodeOneDirectionData(\@sourceCodeOfTopLevelStructures, \@sourceCodeOfUnicodeToForeignIndexedTables16, \@sourceCodeOfUnicodeToForeignKeyedTables1616, \@sourceCodeOfUnicodeToForeignKeyedTables16OfIndexedTables16_indexedEntries, \@sourceCodeOfUnicodeToForeignKeyedTables16OfIndexedTables16_keyedEntries, \@unicodeToForeignData, \%foreignCharacterCodes, 0);
	&writeSourceCodeFinalStuff(\*OUTPUT_FILE, \@sourceCodeOfForeignToUnicodeIndexedTables16, \@sourceCodeOfForeignToUnicodeKeyedTables1616, \@sourceCodeOfForeignToUnicodeKeyedTables16OfIndexedTables16_indexedEntries, \@sourceCodeOfForeignToUnicodeKeyedTables16OfIndexedTables16_keyedEntries, \@sourceCodeOfUnicodeToForeignIndexedTables16, \@sourceCodeOfUnicodeToForeignKeyedTables1616, \@sourceCodeOfUnicodeToForeignKeyedTables16OfIndexedTables16_indexedEntries, \@sourceCodeOfUnicodeToForeignKeyedTables16OfIndexedTables16_keyedEntries, \@sourceCodeOfTopLevelStructures, $endiannessAsText, \%additionalSubsetTables);
	}
elsif ($flattenHashAndSave)
	{
	binmode OUTPUT_FILE;
	#instead of calling the writeBinaryHeader, just write the data I need followed by 
	# writeBinaryForeignVariableByteData...
	&write8(\*OUTPUT_FILE, $endianness);
	&write8(\*OUTPUT_FILE, length($replacementForUnconvertibleUnicodeCharacters));
	&writeString(\*OUTPUT_FILE, $replacementForUnconvertibleUnicodeCharacters);
	&writeBinaryForeignVariableByteData(\*OUTPUT_FILE, \@foreignVariableByteData);
	#choose %unicodeCharacterCodes and write the data as keypair
	my $key;
	my $rangekey;
	my $limit;
	foreach $key (keys(%unicodeCharacterCodes))
		{
		&write16(\*OUTPUT_FILE,$key);
		&write16(\*OUTPUT_FILE,$unicodeCharacterCodes{$key});
		}
	}
else
	{
	binmode OUTPUT_FILE;
	&writeBinaryHeader(\*OUTPUT_FILE, $uid, $endianness, $replacementForUnconvertibleUnicodeCharacters);
	&writeBinaryForeignVariableByteData(\*OUTPUT_FILE, \@foreignVariableByteData);
	&writeBinaryOneDirectionData(\*OUTPUT_FILE, \@foreignToUnicodeData, \%unicodeCharacterCodes, 1);
	&writeBinaryOneDirectionData(\*OUTPUT_FILE, \@unicodeToForeignData, \%foreignCharacterCodes, 0);
	}
close(OUTPUT_FILE) or die("Error: could not close \"$outputFile\"\n");
print("complete\n\n");

sub extractCommandLineFlags()
	{
	my $generateSourceCode=shift;
	my $columns=shift;
	my $omitReplacementForUnconvertibleUnicodeCharacters=shift;
	my $cutOutAnyPrivateUseUnicodeCharacterSlotsBeingUsed=shift;
	my $sourceFilesToSubtract=shift;
	my $flattenHashAndSave=shift;
	my $i;
	for ($i=0; $i<=$#ARGV;) # (i) not cache-ing $#ARGV into a variable as @ARGV may change length in this loop (ii) iterate forwards as some parameters may occupy more than one element in @ARGV
		{
		if (($ARGV[$i]=~/^-s$/i) || ($ARGV[$i]=~/^-generateSourceCode$/i))
			{
			if ($$flattenHashAndSave==1)
				{
				die ("Error: Cannot have -s and -b flags set at the same time");
				}
			else
				{
				splice(@ARGV, $i, 1);
				$$generateSourceCode=1;
				}
			}
		elsif (($ARGV[$i]=~/^-c\b(.*)$/i) || ($ARGV[$i]=~/^-columns\b(.*)$/i))
			{
			my $columnsData=$1;
			splice(@ARGV, $i, 1);
			for (;;)
				{
				if ($columnsData=~/^\s*\(\s*(\d+)\s*:\s*(\d+)\s*\,?\s*(\d+)\s*\)\s*$/)
					{
					@$columns=($1, $2, $3);
					last;
					}
				($#ARGV>=$i) or die("Error: bad \"-columns\" format\n");
				$columnsData.=(splice(@ARGV, $i, 1))[0];
				}
			}
		elsif (($ARGV[$i]=~/^-r$/i) || ($ARGV[$i]=~/^-omitReplacementForUnconvertibleUnicodeCharacters$/i))
			{
			splice(@ARGV, $i, 1);
			$$omitReplacementForUnconvertibleUnicodeCharacters=1;
			}
		elsif (($ARGV[$i]=~/^-p$/i) || ($ARGV[$i]=~/^-cutOutAnyPrivateUseUnicodeCharacterSlotsBeingUsed$/i))
			{
			splice(@ARGV, $i, 1);
			$$cutOutAnyPrivateUseUnicodeCharacterSlotsBeingUsed=1;
			}
		elsif (($ARGV[$i]=~/^-u\b(.*)$/i) || ($ARGV[$i]=~/^-sourceFilesToSubtract\b(.*)$/i))
			{
			my $sourceFilesData=$1;
			splice(@ARGV, $i, 1);
			for (;;)
				{
				if ($sourceFilesData=~/^\s*\(\s*(.+)\)\s*$/)
					{
					my $sourceFilesData=$1;
					@$sourceFilesToSubtract=split(/,/, $sourceFilesData, -1);
					my $j;
					for ($j=$#$sourceFilesToSubtract; $j>=0; --$j)
						{
						$sourceFilesToSubtract->[$j]=~s/^\s+//;
						$sourceFilesToSubtract->[$j]=~s/\s+$//;
						($sourceFilesToSubtract->[$j] ne '') or die("Error: bad \"-sourceFilesToSubtract\" format (1)\n");
						}
					last;
					}
				($#ARGV>=$i) or die("Error: bad \"-sourceFilesToSubtract\" format (2)\n");
				$sourceFilesData.=(splice(@ARGV, $i, 1))[0];
				}
			}
		elsif (($ARGV[$i]=~/^-f$/i) || ($ARGV[$i]=~/^-flattenHashAndSave$/i))
			{
			if ($$generateSourceCode==1)
				{
				die ("Error: Cannot have -s and -b flags set at the same time");
				}
			else
				{
				splice(@ARGV, $i, 1);
				$$flattenHashAndSave=1;
				}
			}
		else
			{
			++$i;
			}
		}
	}

sub algorithm
	{
	my $algorithmAsText=shift;
	if ($algorithmAsText=~/^Direct$/i)
		{
		return 0;
		}
	elsif ($algorithmAsText=~/^Offset$/i)
		{
		return 1;
		}
	elsif ($algorithmAsText=~/^IndexedTable16$/i)
		{
		return 2;
		}
	elsif ($algorithmAsText=~/^KeyedTable1616$/i)
		{
		return 3;
		}
	elsif ($algorithmAsText=~/^KeyedTable16OfIndexedTables16$/i)
		{
		return 4;
		}
	else
		{
		return -1;
		}
	}

sub hexadecimalify
	{
	my $string=shift;
	my $result='';
	my $lengthOfString=length($string);
	my $i;
	for ($i=0; $i<$lengthOfString; ++$i)
		{
		$result.=sprintf("\\x%02x", (unpack('C', substr($string, $i, 1)))[0]);
		}
	return $result;
	}

sub readSourceFile
	{
	my $fileHandle=shift;
	my $fileName=shift;
	my $foreignCharacterCodes=shift;
	my $unicodeCharacterCodes=shift;
	my $columns=shift;
	my $cutOutAnyPrivateUseUnicodeCharacterSlotsBeingUsed=shift;
	my $privateUseUnicodeCharacterSlotsUsed=shift;
	my $subtract=shift;
	my $foreignCharacterCodeProcessingCode='';
	if (!(($columns->[0]>0) && ($columns->[1]>0) && ($columns->[2]>0) && ($columns->[1]<=$columns->[0]) && ($columns->[2]<=$columns->[0]) && ($columns->[1]!=$columns->[2])))
		{
		close($fileHandle);
		die("Error: bad \"-columns\" data\n");
		}
	my $patternOfLineContainingCharacterCodes=join('\s+', ('0x([0-9a-f]+)') x $columns->[0]);
	my $line;
	my $strippedDownLine;
	for (;;)
		{
		($line, $strippedDownLine)=&nextNonEmptyStrippedDownLine($fileHandle);
		if ($strippedDownLine eq '')
			{
			last;
			}
		if ($strippedDownLine=~/^SET_FOREIGN_CHARACTER_CODE_PROCESSING_CODE\s+(.*)$/i)
			{
			$foreignCharacterCodeProcessingCode=$1;
			}
		elsif ($strippedDownLine=~/^$patternOfLineContainingCharacterCodes$/i)
			{
			no strict 'refs'; # so that we can use symbolic references for $1, $2, etc
			my $foreignCharacterCode=hex(${$columns->[1]});
			my $unicodeCharacterCode=hex(${$columns->[2]});
			use strict 'refs';
			if ($foreignCharacterCodeProcessingCode ne '')
				{
				$foreignCharacterCode=eval($foreignCharacterCodeProcessingCode);
				}
			my $handleConversionPair=1;
			if ((($unicodeCharacterCode>=0xe000) && ($unicodeCharacterCode<=0xf8ff)) || (($unicodeCharacterCode>=0xf0000) && ($unicodeCharacterCode<=0x10ffff)))
				{
				if ($cutOutAnyPrivateUseUnicodeCharacterSlotsBeingUsed)
					{
					$handleConversionPair=0;
					}
				else
					{
					if ($subtract)
						{
						delete $privateUseUnicodeCharacterSlotsUsed->{$unicodeCharacterCode};
						}
					else
						{
						$privateUseUnicodeCharacterSlotsUsed->{$unicodeCharacterCode}=1;
						}
					}
				}
			if ($handleConversionPair)
				{
				if ($subtract)
					{
					if (!defined($foreignCharacterCodes->{$unicodeCharacterCode}->{$foreignCharacterCode}))
						{
						close($fileHandle);
						die('Error: cannot subtract conversion pair ['.sprintf('foreign 0x%x, Unicode 0x%04x', $foreignCharacterCode, $unicodeCharacterCode)."] as it does not occur in \"$fileName\"\n");
						}
					if (!defined($unicodeCharacterCodes->{$foreignCharacterCode}->{$unicodeCharacterCode}))
						{
						close($fileHandle);
						die('Error: cannot subtract conversion pair ['.sprintf('Unicode 0x%04x, foreign 0x%x', $unicodeCharacterCode, $foreignCharacterCode)."] as it does not occur in \"$fileName\"\n");
						}
					delete $foreignCharacterCodes->{$unicodeCharacterCode}->{$foreignCharacterCode};
					if (keys(%{$foreignCharacterCodes->{$unicodeCharacterCode}})==0)
						{
						delete $foreignCharacterCodes->{$unicodeCharacterCode};
						}
					delete $unicodeCharacterCodes->{$foreignCharacterCode}->{$unicodeCharacterCode};
					if (keys(%{$unicodeCharacterCodes->{$foreignCharacterCode}})==0)
						{
						delete $unicodeCharacterCodes->{$foreignCharacterCode};
						}
					}
				else
					{
					if (defined($foreignCharacterCodes->{$unicodeCharacterCode}->{$foreignCharacterCode}))
						{
						close($fileHandle);
						die('Error: same conversion pair ['.sprintf('foreign 0x%x, Unicode 0x%04x', $foreignCharacterCode, $unicodeCharacterCode)."] occurs more than once in \"$fileName\"\n");
						}
					if (defined($unicodeCharacterCodes->{$foreignCharacterCode}->{$unicodeCharacterCode}))
						{
						close($fileHandle);
						die('Error: same conversion pair ['.sprintf('Unicode 0x%04x, foreign 0x%x', $unicodeCharacterCode, $foreignCharacterCode)."] occurs more than once in \"$fileName\"\n");
						}
					$foreignCharacterCodes->{$unicodeCharacterCode}->{$foreignCharacterCode}=1;
					$unicodeCharacterCodes->{$foreignCharacterCode}->{$unicodeCharacterCode}=1;
					}
				}
			}
		elsif ($line!~/^\s*0x([0-9a-f]+)\s*#\s*undefined.*$/i)
			{
			close($fileHandle);
			die("Error: unexpected line in \"$fileName\":\n    $line\n");
			}
		}
	}

sub readHeaderFromControlFile
	{
	my $fileHandle=shift;
	my $fileName=shift;
	my $generateSourceCode=shift;
	my $uid=shift;
	my $endiannessAsText=shift;
	my $endianness=shift;
	my $replacementForUnconvertibleUnicodeCharacters=shift;
	my $flattenHashAndSave=shift;
	my $line;
	my $strippedDownLine;
	($line, $strippedDownLine)=&nextNonEmptyStrippedDownLine($fileHandle);
	if ($strippedDownLine=~/^UID\s+0x([0-9a-f]+)$/i)
		{
		if ($generateSourceCode)
			{
			print(STDERR "Warning: \"UID\" keyword should not be used with \"-generateSourceCode\" flag - specify the UID in the MMP file\n");
			}
		$$uid=hex($1);
		($line, $strippedDownLine)=&nextNonEmptyStrippedDownLine($fileHandle);
		}
	else
		{
		if (!$generateSourceCode && !$flattenHashAndSave)
			{
			close($fileHandle);
			die("Error: unexpected line in \"$fileName\" (\"UID\" keyword expected):\n    $line\n");
			}
		}
	if ($strippedDownLine=~/^Name\s+"(.+?)"$/i)
		{
		print(STDERR "Warning: obsolete keyword \"Name\" used\n");
		($line, $strippedDownLine)=&nextNonEmptyStrippedDownLine($fileHandle);
		}
	if ($strippedDownLine!~/^Endianness\s+(\w+)$/i)
		{
		close($fileHandle);
		die("Error: unexpected line in \"$fileName\" (\"Endianness\" keyword expected):\n    $line\n");
		}
	$$endiannessAsText=$1;
	if ($$endiannessAsText=~/Unspecified/i)
		{
		$$endianness=0; # SCnvConversionData::EUnspecified
		}
	elsif ($$endiannessAsText=~/FixedLittleEndian/i)
		{
		$$endianness=1; # SCnvConversionData::EFixedLittleEndian
		}
	elsif ($$endiannessAsText=~/FixedBigEndian/i)
		{
		$$endianness=2; # SCnvConversionData::EFixedBigEndian
		}
	else
		{
		close($fileHandle);
		die("Error: \"$$endiannessAsText\" is not a legal value for \"Endianness\"\n");
		}
	($line, $strippedDownLine)=&nextNonEmptyStrippedDownLine($fileHandle);
	if ($strippedDownLine!~/^ReplacementForUnconvertibleUnicodeCharacters\s+(.*?)$/i)
		{
		close($fileHandle);
		die("Error: unexpected line in \"$fileName\" (\"ReplacementForUnconvertibleUnicodeCharacters\" keyword expected):\n    $line\n");
		}
	$$replacementForUnconvertibleUnicodeCharacters='';
	my $remainderOfXxx=$1;
	while ($remainderOfXxx ne '')
		{
		if ($remainderOfXxx!~/^0x([0-9a-f]{1,2})\s*(.*)$/i)
			{
			close($fileHandle);
			die("Error: unexpected line in \"$fileName\":\n    $line\n");
			}
		$$replacementForUnconvertibleUnicodeCharacters.=pack("C", hex($1));
		$remainderOfXxx=$2;
		}
	my @temp=&nextNonEmptyStrippedDownLine($fileHandle);
	if ($temp[1]=~/^ForeignCharacterCodeProcessingCode/i)
		{
		print(STDERR "Warning: obsolete keyword \"ForeignCharacterCodeProcessingCode\" used\n");
		}
	else
		{
		ungetNonEmptyStrippedDownLine(@temp)
		}
	}

sub readForeignVariableByteDataFromControlFile
	{
	my $fileHandle=shift;
	my $fileName=shift;
	my $foreignVariableByteData=shift;
	my $line;
	my $strippedDownLine;
	($line, $strippedDownLine)=&nextNonEmptyStrippedDownLine($fileHandle);
	if ($strippedDownLine!~/^StartForeignVariableByteData$/i)
		{
		close($fileHandle);
		die("Error: unexpected line in \"$fileName\":\n    $line\n");
		}
	for (;;)
		{
		($line, $strippedDownLine)=&nextNonEmptyStrippedDownLine($fileHandle);
		if ($strippedDownLine=~/^EndForeignVariableByteData$/i)
			{
			last;
			}
		if ($strippedDownLine!~/^0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+(\d+)$/i)
			{
			close($fileHandle);
			die("Error: unexpected line in \"$fileName\":\n    $line\n");
			}
		my $firstInitialByteValueInRange=hex($1);
		my $lastInitialByteValueInRange=hex($2);
		my $numberOfSubsequentBytes=$3;
		if ($firstInitialByteValueInRange>0xff)
			{
			close($fileHandle);
			die("Error: firstInitialByteValueInRange ".sprintf("0x%02x", $firstInitialByteValueInRange)." does not fit in a single byte\n");
			}
		if ($lastInitialByteValueInRange>0xff)
			{
			close($fileHandle);
			die("Error: lastInitialByteValueInRange ".sprintf("0x%02x", $lastInitialByteValueInRange)." does not fit in a single byte\n");
			}
		if ($lastInitialByteValueInRange<$firstInitialByteValueInRange)
			{
			close($fileHandle);
			die("Error: lastInitialByteValueInRange ".sprintf("0x%02x", $lastInitialByteValueInRange)." is less than firstInitialByteValueInRange ".sprintf("0x%02x", $firstInitialByteValueInRange)."\n");
			}
		push(@$foreignVariableByteData, [$firstInitialByteValueInRange, $lastInitialByteValueInRange, $numberOfSubsequentBytes]);
		}
	}

sub readOneDirectionDataFromControlFile
	{
	my $fileHandle=shift;
	my $fileName=shift;
	my $oneDirectionData=shift;
	my $preferredCharacterCodesForConflictResolution=shift;
	my $additionalSubsetTables=shift;
	my $outputIsUnicode=shift;
	my $source=$outputIsUnicode? 'foreign': 'Unicode';
	my $target=$outputIsUnicode? 'Unicode': 'foreign';
	my $middlePortionOfKeyWords=$outputIsUnicode? "ForeignToUnicode": "UnicodeToForeign";
	my $extraPatternToMatch=$outputIsUnicode? '()': '\s+(\d+)';
	my $line;
	my $strippedDownLine;
	($line, $strippedDownLine)=&nextNonEmptyStrippedDownLine($fileHandle);
	if ($strippedDownLine!~/^Start${middlePortionOfKeyWords}Data$/i)
		{
		close($fileHandle);
		die("Error: unexpected line in \"$fileName\":\n    $line\n");
		}
	my $doingConflictResolution=0;
	for (;;)
		{
		($line, $strippedDownLine)=&nextNonEmptyStrippedDownLine($fileHandle);
		if ($strippedDownLine=~/^End${middlePortionOfKeyWords}Data$/i)
			{
			last;
			}
		if ($strippedDownLine=~/^ConflictResolution$/i)
			{
			$doingConflictResolution=1;
			}
		elsif ($doingConflictResolution)
			{
			if ($strippedDownLine!~/^0x([0-9a-f]+)\s+0x([0-9a-f]+)$/i)
				{
				close($fileHandle);
				die("Error: unexpected line in \"$fileName\":\n    $line\n");
				}
			my $sourceCharacterCodeToResolve=hex($1);
			my $targetCharacterCodePreferred=hex($2);
			$preferredCharacterCodesForConflictResolution->{$sourceCharacterCodeToResolve}=$targetCharacterCodePreferred;
			}
		elsif ($strippedDownLine=~/^(Start|End)AdditionalSubsetTable\s+(.*)$/i)
			{
			my $prefix=$1;
			my $nameOfAdditionalSubsetTable=$2;
			my $index=$prefix=~(/^Start$/i)? 0: 1;
			if (!$outputIsUnicode)
				{
				$index+=2;
				}
			if (defined($additionalSubsetTables{$nameOfAdditionalSubsetTable}->[$index]))
				{
				close($fileHandle);
				die("Error: multiple redefinition of \"${prefix}AdditionalSubsetTable $nameOfAdditionalSubsetTable\"\n");
				}
			$additionalSubsetTables{$nameOfAdditionalSubsetTable}->[$index]=@$oneDirectionData;
			}
		else
			{
			if ($strippedDownLine!~/^(\d+)\s+(\d+)\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+(\w+)$extraPatternToMatch\s+\{(.*?)\}$/i)
				{
				close($fileHandle);
				die("Error: unexpected line in \"$fileName\":\n    $line\n");
				}
			my $includePriority=$1;
			my $searchPriority=$2;
			my $firstInputCharacterCodeInRange=hex($3);
			my $lastInputCharacterCodeInRange=hex($4);
			my $algorithmAsText=$5;
			my $sizeOfOutputCharacterCodeInBytes=$6;
			my $parameters=$7;
			if ($lastInputCharacterCodeInRange<$firstInputCharacterCodeInRange)
				{
				close($fileHandle);
				die("Error: lastInputCharacterCodeInRange ".sprintf("0x%02x", $lastInputCharacterCodeInRange)." is less than firstInputCharacterCodeInRange ".sprintf("0x%02x", $firstInputCharacterCodeInRange)."\n");
				}
			my $algorithm=&algorithm($algorithmAsText);
			if ($algorithm<0)
				{
				close($fileHandle);
				die("Error: unexpected algorithm \"$algorithmAsText\"\n");
				}
			my $rangeData=[$includePriority, $searchPriority, $firstInputCharacterCodeInRange, $lastInputCharacterCodeInRange, $algorithm];
			if (!$outputIsUnicode)
				{
				push(@$rangeData, $sizeOfOutputCharacterCodeInBytes);
				}
			push(@$rangeData, $parameters);
			push(@$oneDirectionData, $rangeData);
			}
		}
	}

sub warnIfAnyPrivateUseUnicodeCharacterSlotsBeingUsed
	{
	my $privateUseUnicodeCharacterSlotsUsed=shift;
	my @sortedPrivateUseUnicodeCharacterSlotsUsed=sort({$a<=>$b} keys(%$privateUseUnicodeCharacterSlotsUsed));
	if (@sortedPrivateUseUnicodeCharacterSlotsUsed>0)
		{
		my $lastPrivateUseUnicodeCharacterSlotUsed=$sortedPrivateUseUnicodeCharacterSlotsUsed[0];
		my $asText=sprintf('0x%04x', $lastPrivateUseUnicodeCharacterSlotUsed);
		my @asText=($asText);
		my $i;
		for ($i=1; $i<@sortedPrivateUseUnicodeCharacterSlotsUsed; ++$i) # this loop starts from 1 not 0 as we have already dealt with $sortedPrivateUseUnicodeCharacterSlotsUsed[0]
			{
			($sortedPrivateUseUnicodeCharacterSlotsUsed[$i]>$lastPrivateUseUnicodeCharacterSlotUsed) or die("Error: internal error 1\n");
			if ($sortedPrivateUseUnicodeCharacterSlotsUsed[$i]>$lastPrivateUseUnicodeCharacterSlotUsed+1)
				{
				$asText=sprintf('0x%04x', $lastPrivateUseUnicodeCharacterSlotUsed);
				if ($asText[-1] ne $asText)
					{
					$asText[-1].='-'.$asText;
					}
				push(@asText, sprintf('0x%04x', $sortedPrivateUseUnicodeCharacterSlotsUsed[$i]));
				}
			$lastPrivateUseUnicodeCharacterSlotUsed=$sortedPrivateUseUnicodeCharacterSlotsUsed[$i];
			}
		$asText=sprintf('0x%04x', $lastPrivateUseUnicodeCharacterSlotUsed);
		if ($asText[-1] ne $asText)
			{
			$asText[-1].='-'.$asText;
			}
		print(STDERR 'Warning: the following private-use Unicode character slots were used: ['.join(', ', @asText)."]\n");
		}
	}

sub resolveConflictsAndFlattenArraysToScalars
	{
	my $characterCodes=shift;
	my $preferredCharacterCodesForConflictResolution=shift;
	my $source=shift;
	my $target=shift;
	my $sourceCharacterCode;
	my $candidateTargetCharacterCodes;
	while (($sourceCharacterCode, $candidateTargetCharacterCodes)=each(%$characterCodes))
		{
		my @candidateTargetCharacterCodes=keys(%$candidateTargetCharacterCodes);
		if (@candidateTargetCharacterCodes<1)
			{
			die("Error: internal error 2\n");
			}
		if (@candidateTargetCharacterCodes==1)
			{
			$characterCodes->{$sourceCharacterCode}=$candidateTargetCharacterCodes[0];
			}
		else
			{
			if (!defined($preferredCharacterCodesForConflictResolution->{$sourceCharacterCode}))
				{
				die("Error: no preferred $target character code is specified for conflict resolution for the $source character code ".sprintf("0x%08x", $sourceCharacterCode)."\n");
				}
			my $preferredCharacterCodeIsNotACandidateForConflictResolution=1;
			my $candidateTargetCharacterCode;
			foreach $candidateTargetCharacterCode (@candidateTargetCharacterCodes)
				{
				if ($preferredCharacterCodesForConflictResolution->{$sourceCharacterCode}==$candidateTargetCharacterCode)
					{
					$preferredCharacterCodeIsNotACandidateForConflictResolution=0;
					last;
					}
				}
			if ($preferredCharacterCodeIsNotACandidateForConflictResolution)
				{
				die("Error: the preferred $target character code ".sprintf("0x%08x", $preferredCharacterCodesForConflictResolution->{$sourceCharacterCode})." is not a candidate for conflict resolution for the $source character code ".sprintf("0x%08x", $sourceCharacterCode)."\n");
				}
			$characterCodes->{$sourceCharacterCode}=$preferredCharacterCodesForConflictResolution->{$sourceCharacterCode};
			delete $preferredCharacterCodesForConflictResolution->{$sourceCharacterCode};
			}
		}
	my $numberOfPreferredCharacterCodesForConflictResolution=keys(%$preferredCharacterCodesForConflictResolution);
	if ($numberOfPreferredCharacterCodesForConflictResolution!=0)
		{
		print(STDERR "Warning: there are $numberOfPreferredCharacterCodesForConflictResolution $target preferred character codes specified for which there are no conflicts to resolve\n");
		}
	}

sub checkForeignVariableByteData
	{
	my $endianness=shift;
	my $foreignVariableByteData=shift;
	my $foreignToUnicodeData=shift;
	my $rangeData;
	my %initialForeignBytes=();
	foreach $rangeData (@$foreignVariableByteData)
		{
		my $initialByte;
		for ($initialByte=$rangeData->[0]; $initialByte<=$rangeData->[1]; ++$initialByte)
			{
			if (defined($initialForeignBytes{$initialByte}))
				{
				die("Error: the number of bytes subsequent to the initial foreign-byte $initialForeignBytes{$initialByte} is defined more than once\n");
				}
			$initialForeignBytes{$initialByte}=1;
			}
		}
#	if ($endianness!=0) # unfortunately, nothing can be checked if the $endianness is 0 (SCnvConversionData::EUnspecified)
#		{
#		foreach $rangeData (@$foreignToUnicodeData)
#			{
#			my $inputCharacterCode;
#			for ($inputCharacterCode=$rangeData->[2]; $inputCharacterCode<=$rangeData->[3]; ++$inputCharacterCode)
#				{
#				my $initialByte;
#				if ($endianness==1) # SCnvConversionData::EFixedLittleEndian
#					{
#					$initialByte=($inputCharacterCode&0xff);
#					}
#				elsif ($endianness==2) # SCnvConversionData::EFixedBigEndian
#					{
#					$initialByte=($inputCharacterCode&0xff00)>>8; ## this is a hard-coded hack and needs to be done properly!
#					}
#				else
#					{
#					die("Error: internal error ??\n");
#					}
#				if (!defined($initialForeignBytes{$initialByte}))
#					{
#					die("Error: no number-of-subsequent-bytes is specified for the initial byte $initialByte\n");
#					}
#				}
#			}
#		}
	}

sub writeSourceCodeHeader
	{
	my $fileHandle=shift;
	my $fileName=shift;
	my $replacementForUnconvertibleUnicodeCharacters=shift;
	while ($fileName=~/^.*\\(.*)$/i)
		{
		$fileName=$1;
		}
	print($fileHandle "// $fileName\n//\n// Copyright (c) ".(1900+(gmtime(time))[5])." Symbian Ltd.  All rights reserved.\n//\n\n");
	print($fileHandle "#include <E32STD.H>\n#include <CONVDATA.H>\n#include <CONVGENERATEDCPP.H>\n\n#define ARRAY_LENGTH(aArray) (sizeof(aArray)/sizeof((aArray)\[0\]))\n\n#pragma warning (disable: 4049) // compiler limit : terminating line number emission\n\n");
	if (!$omitReplacementForUnconvertibleUnicodeCharacters)
		{
		print($fileHandle "_LIT8(KLit8ReplacementForUnconvertibleUnicodeCharacters, \"".&hexadecimalify($replacementForUnconvertibleUnicodeCharacters)."\");\n\n");
		print($fileHandle "GLDEF_C const TDesC8& ReplacementForUnconvertibleUnicodeCharacters_internal()\n\t{\n\treturn KLit8ReplacementForUnconvertibleUnicodeCharacters;\n\t}\n\n");
		}
	}

sub writeSourceCodeForeignVariableByteData
	{
	my $sourceCodeOfTopLevelStructures=shift;
	my $foreignVariableByteData=shift;
	push(@$sourceCodeOfTopLevelStructures, "LOCAL_D const SCnvConversionData::SVariableByteData::SRange foreignVariableByteDataRanges[]=\n\t\{\n");
	my $indexOfLastRange=$#$foreignVariableByteData;
	my $i;
	for ($i=0; $i<=$indexOfLastRange; ++$i)
		{
		my $rangeData=$foreignVariableByteData->[$i];
		if (@$rangeData!=3)
			{
			die("Error: internal error 3\n");
			}
		my $firstInitialByteValueInRange=$rangeData->[0];
		my $lastInitialByteValueInRange=$rangeData->[1];
		if ($lastInitialByteValueInRange<$firstInitialByteValueInRange)
			{
			die("Error: internal error 4\n");
			}
		my $numberOfSubsequentBytes=$rangeData->[2];
		push(@$sourceCodeOfTopLevelStructures, "\t\t\{\n\t\t".sprintf("0x%02x", $firstInitialByteValueInRange).",\n\t\t".sprintf("0x%02x", $lastInitialByteValueInRange).",\n\t\t$numberOfSubsequentBytes,\n\t\t0\n\t\t\}");
		if ($i<$indexOfLastRange)
			{
			push(@$sourceCodeOfTopLevelStructures, ',');
			}
		push(@$sourceCodeOfTopLevelStructures, "\n");
		}
	push(@$sourceCodeOfTopLevelStructures, "\t\};\n\n");
	}

sub writeSourceCodeOneDirectionData
	{
	my $sourceCodeOfTopLevelStructures=shift;
	my $sourceCodeOfOneDirectionIndexedTables16=shift;
	my $sourceCodeOfOneDirectionKeyedTables1616=shift;
	my $sourceCodeOfOneDirectionKeyedTables16OfIndexedTables16_indexedEntries=shift;
	my $sourceCodeOfOneDirectionKeyedTables16OfIndexedTables16_keyedEntries=shift;
	my $oneDirectionData=shift;
	my $characterCodes=shift;
	my $outputIsUnicode=shift;
	push(@$sourceCodeOfTopLevelStructures, 'LOCAL_D const SCnvConversionData::SOneDirectionData::SRange '.($outputIsUnicode? 'foreignToUnicodeDataRanges': 'unicodeToForeignDataRanges')."[]=\n\t\{\n");
	my $formatForInputCharacters=$outputIsUnicode? '0x%02x': '0x%04x';
	my $formatForOutputCharacters=$outputIsUnicode? '0x%04x': '0x%02x';
	my $indexOfLastRange=$#$oneDirectionData;
	my $i;
	for ($i=0; $i<=$indexOfLastRange; ++$i)
		{
		my $rangeData=$oneDirectionData->[$i];
		# $rangeData is $includePriority, $searchPriority, $firstInputCharacterCodeInRange, $lastInputCharacterCodeInRange, $algorithm[, $sizeOfOutputCharacterCodeInBytes], $parameters
		if (scalar(@$rangeData)!=($outputIsUnicode? 6: 7))
			{
			die("Error: internal error 5\n");
			}
		my $firstInputCharacterCodeInRange=$rangeData->[2];
		my $lastInputCharacterCodeInRange=$rangeData->[3];
		if ($lastInputCharacterCodeInRange<$firstInputCharacterCodeInRange)
			{
			die("Error: internal error 6\n");
			}
		my $algorithmAsText=''; # set by the if-elsif stuff below
		my $sizeOfOutputCharacterCodeInBytesIfForeign=$outputIsUnicode? 0: $rangeData->[5];
		my $parameters=$rangeData->[$outputIsUnicode? 5: 6];
		my $word1=0; # set by the if-elsif stuff below
		my $word2=0; # set by the if-elsif stuff below
		my $algorithm=$rangeData->[4];
		if ($algorithm==0) # Direct
			{
			$algorithmAsText='Direct';
			my $characterCode;
			for ($characterCode=$firstInputCharacterCodeInRange; $characterCode<=$lastInputCharacterCodeInRange; ++$characterCode)
				{
				if (!defined($characterCodes->{$characterCode}))
					{
					die("Error: There is no conversion defined for ".($outputIsUnicode? 'foreign': 'Unicode')." character code ".sprintf("0x%08x", $characterCode)."\n");
					}
				if ($characterCodes->{$characterCode}!=$characterCode)
					{
					die("Error: the conversion from ".($outputIsUnicode? 'foreign': 'Unicode')." character code ".sprintf("0x%08x", $characterCode)." to ".($outputIsUnicode? 'Unicode': 'foreign')." character code ".sprintf("0x%08x", $characterCodes->{$characterCode})." is not a direct conversion\n");
					}
				delete $characterCodes->{$characterCode};
				}
			}
		elsif ($algorithm==1) # Offset
			{
			$algorithmAsText='Offset';
			my $offset=$characterCodes->{$firstInputCharacterCodeInRange}-$firstInputCharacterCodeInRange;
			delete $characterCodes->{$firstInputCharacterCodeInRange};
			my $characterCode;
			for ($characterCode=$firstInputCharacterCodeInRange+1; $characterCode<=$lastInputCharacterCodeInRange; ++$characterCode)
				{
				if (!defined($characterCodes->{$characterCode}))
					{
					die("Error: There is no conversion defined for ".($outputIsUnicode? 'foreign': 'Unicode')." character code ".sprintf("0x%08x (0x%08x-0x%08x)", $characterCode, $firstInputCharacterCodeInRange, $lastInputCharacterCodeInRange)."\n");
					}
				if ($characterCodes->{$characterCode}-$characterCode!=$offset)
					{
					die("Error: the conversion from ".($outputIsUnicode? 'foreign': 'Unicode')." character code ".sprintf("0x%08x", $characterCode)." to ".($outputIsUnicode? 'Unicode': 'foreign')." character code ".sprintf("0x%08x", $characterCodes->{$characterCode})." has a different offset from the previous one in the range\n");
					}
				delete $characterCodes->{$characterCode};
				}
			$word1="STATIC_CAST(TUint, $offset)";
			}
		elsif ($algorithm==2) # IndexedTable16
			{
			$algorithmAsText='IndexedTable16';
			my $nameOfNextOneDirectionIndexedTable16='indexedTable16_'.($outputIsUnicode? 'foreignToUnicode': 'unicodeToForeign').'_'.($#$sourceCodeOfOneDirectionIndexedTables16+2);
			my $sourceCodeOfNextOneDirectionIndexedTable16=[];
			push(@$sourceCodeOfNextOneDirectionIndexedTable16, "LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SIndexedTable16::SEntry $nameOfNextOneDirectionIndexedTable16\[\]=\n\t\{\n");
			my $characterCode;
			for ($characterCode=$firstInputCharacterCodeInRange; $characterCode<=$lastInputCharacterCodeInRange; ++$characterCode)
				{
				if (!defined($characterCodes->{$characterCode}))
					{
					die("Error: There is no conversion defined for ".($outputIsUnicode? 'foreign': 'Unicode')." character code ".sprintf("0x%08x", $characterCode)."\n");
					}
				push(@$sourceCodeOfNextOneDirectionIndexedTable16, "\t\t\{\n\t\t".sprintf($formatForOutputCharacters, $characterCodes->{$characterCode})."\n\t\t\}");
				if ($characterCode<$lastInputCharacterCodeInRange)
					{
					push(@$sourceCodeOfNextOneDirectionIndexedTable16, ',');
					}
				push(@$sourceCodeOfNextOneDirectionIndexedTable16, "\n");
				delete $characterCodes->{$characterCode};
				}
			push(@$sourceCodeOfNextOneDirectionIndexedTable16, "\t\};\n\n");
			push(@$sourceCodeOfOneDirectionIndexedTables16, $sourceCodeOfNextOneDirectionIndexedTable16);
			$word1="REINTERPRET_CAST(TUint, $nameOfNextOneDirectionIndexedTable16)";
			}
		elsif ($algorithm==3) # KeyedTable1616
			{
			$algorithmAsText='KeyedTable1616';
			my $nameOfNextOneDirectionKeyedTable1616='keyedTable1616_'.($outputIsUnicode? 'foreignToUnicode': 'unicodeToForeign').'_'.($#$sourceCodeOfOneDirectionKeyedTables1616+2);
			my $sourceCodeOfNextOneDirectionKeyedTable1616=[];
			push(@$sourceCodeOfNextOneDirectionKeyedTable1616, "LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable1616::SEntry $nameOfNextOneDirectionKeyedTable1616\[\]=\n\t\{\n");
			my @characterCodes=grep(($_>=$firstInputCharacterCodeInRange) && ($_<=$lastInputCharacterCodeInRange), sort({$a<=>$b} keys(%$characterCodes)));
			if (@characterCodes==0)
				{
				die("Error: There are no ".($outputIsUnicode? 'foreign': 'Unicode').'-to-'.($outputIsUnicode? 'Unicode': 'foreign')." characters to convert using KeyedTable1616 (range ".sprintf("$formatForInputCharacters-$formatForInputCharacters", $firstInputCharacterCodeInRange, $lastInputCharacterCodeInRange).").\n");
				}
			if ($characterCodes[0]!=$firstInputCharacterCodeInRange)
				{
				print(STDERR 'Warning: the specified start of the '.($outputIsUnicode? 'foreign': 'Unicode').' range '.sprintf("$formatForInputCharacters-$formatForInputCharacters", $firstInputCharacterCodeInRange, $lastInputCharacterCodeInRange).' could actually be '.sprintf("$formatForInputCharacters", $characterCodes[0])."\n");
				}
			if ($characterCodes[-1]!=$lastInputCharacterCodeInRange)
				{
				print(STDERR 'Warning: the specified end of the '.($outputIsUnicode? 'foreign': 'Unicode').' range '.sprintf("$formatForInputCharacters-$formatForInputCharacters", $firstInputCharacterCodeInRange, $lastInputCharacterCodeInRange).' could actually be '.sprintf("$formatForInputCharacters", $characterCodes[-1])."\n");
				}
			my $characterCode;
			foreach $characterCode (@characterCodes)
				{
				if (defined($characterCodes->{$characterCode}))
					{
					push(@$sourceCodeOfNextOneDirectionKeyedTable1616, "\t\t\{\n\t\t".sprintf($formatForInputCharacters, $characterCode).",\n\t\t".sprintf($formatForOutputCharacters, $characterCodes->{$characterCode})."\n\t\t\}");
					if ($characterCode<$characterCodes[-1])
						{
						push(@$sourceCodeOfNextOneDirectionKeyedTable1616, ',');
						}
					push(@$sourceCodeOfNextOneDirectionKeyedTable1616, "\n");
					delete $characterCodes->{$characterCode};
					}
				}
			push(@$sourceCodeOfNextOneDirectionKeyedTable1616, "\t\};\n\n");
			push(@$sourceCodeOfOneDirectionKeyedTables1616, $sourceCodeOfNextOneDirectionKeyedTable1616);
			$word1="STATIC_CAST(TUint, ARRAY_LENGTH($nameOfNextOneDirectionKeyedTable1616))";
			$word2="REINTERPRET_CAST(TUint, $nameOfNextOneDirectionKeyedTable1616)";
			}
		elsif ($algorithm==4) # KeyedTable16OfIndexedTables16
			{
			$algorithmAsText='KeyedTable16OfIndexedTables16';
			my $nameOfNextOneDirectionKeyedTables16OfIndexedTables16_keyedEntries='keyedTables16OfIndexedTables16_keyedEntries_'.($outputIsUnicode? 'foreignToUnicode': 'unicodeToForeign').'_'.($#$sourceCodeOfOneDirectionKeyedTables16OfIndexedTables16_keyedEntries+2);
			my $sourceCodeOfNextOneDirectionKeyedTables16OfIndexedTables16_keyedEntries=[];
			push(@$sourceCodeOfNextOneDirectionKeyedTables16OfIndexedTables16_keyedEntries, "LOCAL_D const SCnvConversionData::SOneDirectionData::SRange::UData::SKeyedTable16OfIndexedTables16::SKeyedEntry $nameOfNextOneDirectionKeyedTables16OfIndexedTables16_keyedEntries\[\]=\n\t\{\n");
			my @characterCodes=grep(($_>=$firstInputCharacterCodeInRange) && ($_<=$lastInputCharacterCodeInRange), sort({$a<=>$b} keys(%$characterCodes)));
			if (@characterCodes==0)
				{
				die("Error: There are no ".($outputIsUnicode? 'foreign': 'Unicode').'-to-'.($outputIsUnicode? 'Unicode': 'foreign')." characters to convert using KeyedTable16OfIndexedTables16 (range ".sprintf("$formatForInputCharacters-$formatForInputCharacters", $firstInputCharacterCodeInRange, $lastInputCharacterCodeInRange).").\n");
				}
			if ($characterCodes[0]!=$firstInputCharacterCodeInRange)
				{
				print(STDERR 'Warning: the specified start of the '.($outputIsUnicode? 'foreign': 'Unicode').' range '.sprintf("$formatForInputCharacters-$formatForInputCharacters", $firstInputCharacterCodeInRange, $lastInputCharacterCodeInRange).' could actually be '.sprintf("$formatForInputCharacters", $characterCodes[0])."\n");
				}
			if ($characterCodes[-1]!=$lastInputCharacterCodeInRange)
				{
				print(STDERR 'Warning: the specified end of the '.($outputIsUnicode? 'foreign': 'Unicode').' range '.sprintf("$formatForInputCharacters-$formatForInputCharacters", $firstInputCharacterCodeInRange, $lastInputCharacterCodeInRange).' could actually be '.sprintf("$formatForInputCharacters", $characterCodes[-1])."\n");
				}
			my @characterCodeRanges=();
			my $minimumNumberOfEntriesPerIndexedTable=($parameters ne '')? $parameters: 0;
			my $firstInputCharacterCodeInIndexedTable=$characterCodes[0];
			my $previousCharacterCode=$firstInputCharacterCodeInIndexedTable;
			my $characterCode;
			foreach $characterCode (@characterCodes)
				{
				($characterCode>=$previousCharacterCode) or die("Error: internal error 7\n");
				if ($characterCode>$previousCharacterCode+1)
					{
					if (($previousCharacterCode-$firstInputCharacterCodeInIndexedTable)+1>=$minimumNumberOfEntriesPerIndexedTable)
						{
						push(@characterCodeRanges, [$firstInputCharacterCodeInIndexedTable, $previousCharacterCode]);
						}
					$firstInputCharacterCodeInIndexedTable=$characterCode;
					}
				$previousCharacterCode=$characterCode;
				}
			push(@characterCodeRanges, [$firstInputCharacterCodeInIndexedTable, $previousCharacterCode]);
			@characterCodes=();
			my $characterCodeRange;
			foreach $characterCodeRange (@characterCodeRanges)
				{
				my $nameOfNextOneDirectionKeyedTables16OfIndexedTables16_indexedEntries='keyedTables16OfIndexedTables16_indexedEntries_'.($outputIsUnicode? 'foreignToUnicode': 'unicodeToForeign').'_'.($#$sourceCodeOfOneDirectionKeyedTables16OfIndexedTables16_indexedEntries+2);
				my $sourceCodeOfNextOneDirectionKeyedTables16OfIndexedTables16_indexedEntries=[];
				push(@$sourceCodeOfNextOneDirectionKeyedTables16OfIndexedTables16_indexedEntries, "LOCAL_D const TUint16 $nameOfNextOneDirectionKeyedTables16OfIndexedTables16_indexedEntries\[\]=\n\t\{\n");
				my $characterCode;
				my $lastInputCharacterCodeInIndexedTable=$characterCodeRange->[1];
				for ($characterCode=$characterCodeRange->[0]; $characterCode<=$lastInputCharacterCodeInIndexedTable; ++$characterCode)
					{
					if (!defined($characterCodes->{$characterCode}))
						{
						die("Error: internal error 8\n");
						}
					push(@$sourceCodeOfNextOneDirectionKeyedTables16OfIndexedTables16_indexedEntries, "\t".sprintf($formatForOutputCharacters, $characterCodes->{$characterCode}));
					if ($characterCode<$lastInputCharacterCodeInIndexedTable)
						{
						push(@$sourceCodeOfNextOneDirectionKeyedTables16OfIndexedTables16_indexedEntries, ',');
						}
					push(@$sourceCodeOfNextOneDirectionKeyedTables16OfIndexedTables16_indexedEntries, "\n");
					delete $characterCodes->{$characterCode};
					}
				push(@$sourceCodeOfNextOneDirectionKeyedTables16OfIndexedTables16_indexedEntries, "\t\};\n\n");
				push(@$sourceCodeOfOneDirectionKeyedTables16OfIndexedTables16_indexedEntries, $sourceCodeOfNextOneDirectionKeyedTables16OfIndexedTables16_indexedEntries);
				push(@$sourceCodeOfNextOneDirectionKeyedTables16OfIndexedTables16_keyedEntries, "\t\t\{\n\t\t".sprintf($formatForInputCharacters, $characterCodeRange->[0]).",\n\t\t".sprintf($formatForInputCharacters, $characterCodeRange->[1]).",\n\t\t$nameOfNextOneDirectionKeyedTables16OfIndexedTables16_indexedEntries\n\t\t\}");
				if ($characterCodeRange->[1]<$characterCodeRanges[-1]->[1])
					{
					push(@$sourceCodeOfNextOneDirectionKeyedTables16OfIndexedTables16_keyedEntries, ',');
					}
				push(@$sourceCodeOfNextOneDirectionKeyedTables16OfIndexedTables16_keyedEntries, "\n");
				}
			push(@$sourceCodeOfNextOneDirectionKeyedTables16OfIndexedTables16_keyedEntries, "\t\};\n\n");
			push(@$sourceCodeOfOneDirectionKeyedTables16OfIndexedTables16_keyedEntries, $sourceCodeOfNextOneDirectionKeyedTables16OfIndexedTables16_keyedEntries);
			$word1="STATIC_CAST(TUint, ARRAY_LENGTH($nameOfNextOneDirectionKeyedTables16OfIndexedTables16_keyedEntries))";
			$word2="REINTERPRET_CAST(TUint, $nameOfNextOneDirectionKeyedTables16OfIndexedTables16_keyedEntries)";
			}
		else
			{
			die("Error: internal error 9\n");
			}
		push(@$sourceCodeOfTopLevelStructures, "\t\t\{\n\t\t".sprintf($formatForInputCharacters, $firstInputCharacterCodeInRange).",\n\t\t".sprintf($formatForInputCharacters, $lastInputCharacterCodeInRange).",\n\t\tSCnvConversionData::SOneDirectionData::SRange::E$algorithmAsText,\n\t\t".$sizeOfOutputCharacterCodeInBytesIfForeign.",\n\t\t0,\n\t\t\t\{\n\t\t\t".$word1.",\n\t\t\t".$word2."\n\t\t\t\}\n\t\t\}");
		if ($i<$indexOfLastRange)
			{
			push(@$sourceCodeOfTopLevelStructures, ',');
			}
		push(@$sourceCodeOfTopLevelStructures, "\n");
		}
	my @characterCodes=sort({$a<=>$b} keys(%$characterCodes));
	if (@characterCodes>0)
		{
		die('The following '.($outputIsUnicode? 'foreign': 'Unicode').' characters have no conversion algorithm specified: ['.join(', ', map(sprintf($formatForInputCharacters, $_), @characterCodes))."\]\n");
		}
	push(@$sourceCodeOfTopLevelStructures, "\t\};\n\n");
	}

sub writeSourceCodeFinalStuff
	{
	my $fileHandle=shift;
	my $sourceCodeOfForeignToUnicodeIndexedTables16=shift;
	my $sourceCodeOfForeignToUnicodeKeyedTables1616=shift;
	my $sourceCodeOfForeignToUnicodeKeyedTables16OfIndexedTables16_indexedEntries=shift;
	my $sourceCodeOfForeignToUnicodeKeyedTables16OfIndexedTables16_keyedEntries=shift;
	my $sourceCodeOfUnicodeToForeignIndexedTables16=shift;
	my $sourceCodeOfUnicodeToForeignKeyedTables1616=shift;
	my $sourceCodeOfUnicodeToForeignKeyedTables16OfIndexedTables16_indexedEntries=shift;
	my $sourceCodeOfUnicodeToForeignKeyedTables16OfIndexedTables16_keyedEntries=shift;
	my $sourceCodeOfTopLevelStructures=shift;
	my $endiannessAsText=shift;
	my $additionalSubsetTables=shift;
	my $sourceCodeChunk;
	my $arrayOfSourceCodeChunks;
	foreach $arrayOfSourceCodeChunks (@$sourceCodeOfForeignToUnicodeIndexedTables16)
		{
		foreach $sourceCodeChunk (@$arrayOfSourceCodeChunks)
			{
			print($fileHandle $sourceCodeChunk);
			}
		}
	foreach $arrayOfSourceCodeChunks (@$sourceCodeOfForeignToUnicodeKeyedTables1616)
		{
		foreach $sourceCodeChunk (@$arrayOfSourceCodeChunks)
			{
			print($fileHandle $sourceCodeChunk);
			}
		}
	foreach $arrayOfSourceCodeChunks (@$sourceCodeOfForeignToUnicodeKeyedTables16OfIndexedTables16_indexedEntries)
		{
		foreach $sourceCodeChunk (@$arrayOfSourceCodeChunks)
			{
			print($fileHandle $sourceCodeChunk);
			}
		}
	foreach $arrayOfSourceCodeChunks (@$sourceCodeOfForeignToUnicodeKeyedTables16OfIndexedTables16_keyedEntries)
		{
		foreach $sourceCodeChunk (@$arrayOfSourceCodeChunks)
			{
			print($fileHandle $sourceCodeChunk);
			}
		}
	foreach $arrayOfSourceCodeChunks (@$sourceCodeOfUnicodeToForeignIndexedTables16)
		{
		foreach $sourceCodeChunk (@$arrayOfSourceCodeChunks)
			{
			print($fileHandle $sourceCodeChunk);
			}
		}
	foreach $arrayOfSourceCodeChunks (@$sourceCodeOfUnicodeToForeignKeyedTables1616)
		{
		foreach $sourceCodeChunk (@$arrayOfSourceCodeChunks)
			{
			print($fileHandle $sourceCodeChunk);
			}
		}
	foreach $arrayOfSourceCodeChunks (@$sourceCodeOfUnicodeToForeignKeyedTables16OfIndexedTables16_indexedEntries)
		{
		foreach $sourceCodeChunk (@$arrayOfSourceCodeChunks)
			{
			print($fileHandle $sourceCodeChunk);
			}
		}
	foreach $arrayOfSourceCodeChunks (@$sourceCodeOfUnicodeToForeignKeyedTables16OfIndexedTables16_keyedEntries)
		{
		foreach $sourceCodeChunk (@$arrayOfSourceCodeChunks)
			{
			print($fileHandle $sourceCodeChunk);
			}
		}
	foreach $sourceCodeChunk (@$sourceCodeOfTopLevelStructures)
		{
		print($fileHandle $sourceCodeChunk);
		}
	print($fileHandle "GLDEF_D const SCnvConversionData conversionData=\n\t\{\n\tSCnvConversionData::E$endiannessAsText,\n\t\t\{\n\t\tARRAY_LENGTH(foreignVariableByteDataRanges),\n\t\tforeignVariableByteDataRanges\n\t\t\},\n\t\t\{\n\t\tARRAY_LENGTH(foreignToUnicodeDataRanges),\n\t\tforeignToUnicodeDataRanges\n\t\t\},\n\t\t\{\n\t\tARRAY_LENGTH(unicodeToForeignDataRanges),\n\t\tunicodeToForeignDataRanges\n\t\t\},\n\tNULL,\n\tNULL\n\t\};\n\n");
	my $additionalSubsetTableName;
	my $additionalSubsetTableData;
	while (($additionalSubsetTableName, $additionalSubsetTableData)=each(%$additionalSubsetTables))
		{
		(defined($additionalSubsetTableData->[0]) && defined($additionalSubsetTableData->[1]) && defined($additionalSubsetTableData->[2]) && defined($additionalSubsetTableData->[3])) or die("Error: incomplete definition of \"$additionalSubsetTableName\"\n");
		print($fileHandle "GLREF_D const SCnvConversionData $additionalSubsetTableName;\n");
		print($fileHandle "GLDEF_D const SCnvConversionData $additionalSubsetTableName=\n\t\{\n\tSCnvConversionData::E$endiannessAsText,\n\t\t\{\n\t\tARRAY_LENGTH(foreignVariableByteDataRanges),\n\t\tforeignVariableByteDataRanges\n\t\t\},\n\t\t\{\n\t\t$additionalSubsetTableData->[1]-$additionalSubsetTableData->[0],\n\t\tforeignToUnicodeDataRanges+$additionalSubsetTableData->[0]\n\t\t\},\n\t\t\{\n\t\t$additionalSubsetTableData->[3]-$additionalSubsetTableData->[2],\n\t\tunicodeToForeignDataRanges+$additionalSubsetTableData->[2]\n\t\t\}\n\t\};\n\n");
		}
	}

sub writeBinaryHeader
	{
	my $fileHandle=shift;
	my $uid=shift;
	my $endianness=shift;
	my $replacementForUnconvertibleUnicodeCharacters=shift;
	&writeUids($fileHandle, 0x100011bd, $uid, 0);
	&write32($fileHandle, 1); # version number of the file format
	&write32($fileHandle, 0); # not currently used
	&write8($fileHandle, 0); # number of Unicode characters in the name (which is now derived from the file-name, hence why this is zero)
	&write8($fileHandle, $endianness);
	&write8($fileHandle, length($replacementForUnconvertibleUnicodeCharacters));
	&writeString($fileHandle, $replacementForUnconvertibleUnicodeCharacters);
	}

sub writeBinaryForeignVariableByteData
	{
	my $fileHandle=shift;
	my $foreignVariableByteData=shift;
	&writePositiveIntegerCompacted30($fileHandle, scalar(@$foreignVariableByteData));
	my $rangeData;
	foreach $rangeData (@$foreignVariableByteData)
		{
		if (@$rangeData!=3)
			{
			die("Error: internal error 10\n");
			}
		my $firstInitialByteValueInRange=$rangeData->[0];
		my $lastInitialByteValueInRange=$rangeData->[1];
		if ($lastInitialByteValueInRange<$firstInitialByteValueInRange)
			{
			die("Error: internal error 11\n");
			}
		&write8($fileHandle, $firstInitialByteValueInRange);
		&write8($fileHandle, $lastInitialByteValueInRange);
		&write8($fileHandle, $rangeData->[2]); # numberOfSubsequentBytes
		}
	}

sub writeBinaryOneDirectionData
	{
	my $fileHandle=shift;
	my $oneDirectionData=shift;
	my $characterCodes=shift;
	my $outputIsUnicode=shift;
	&writePositiveIntegerCompacted30($fileHandle, scalar(@$oneDirectionData));
	my $rangeData;
	foreach $rangeData (@$oneDirectionData)
		{
##		$rangeData is $includePriority, $searchPriority, $firstInputCharacterCodeInRange, $lastInputCharacterCodeInRange, $algorithm[, $sizeOfOutputCharacterCodeInBytes], $parameters
		if (scalar(@$rangeData)!=($outputIsUnicode? 6: 7))
			{
			die("Error: internal error 12\n");
			}
		my $firstInputCharacterCodeInRange=$rangeData->[2];
		my $lastInputCharacterCodeInRange=$rangeData->[3];
		if ($lastInputCharacterCodeInRange<$firstInputCharacterCodeInRange)
			{
			die("Error: internal error 13\n");
			}
		&writePositiveIntegerCompacted30($fileHandle, $firstInputCharacterCodeInRange);
		&writePositiveIntegerCompacted30($fileHandle, $lastInputCharacterCodeInRange);
		my $algorithm=$rangeData->[4];
		&write8($fileHandle, $algorithm);
		if (!$outputIsUnicode)
			{
			&write8($fileHandle, $rangeData->[5]); # sizeOfOutputCharacterCodeInBytesIfForeign
			}
		if ($algorithm==0) # Direct
			{
			my $characterCode;
			for ($characterCode=$firstInputCharacterCodeInRange; $characterCode<=$lastInputCharacterCodeInRange; ++$characterCode)
				{
				if (!defined($characterCodes->{$characterCode}))
					{
					die("Error: There is no conversion defined for ".($outputIsUnicode? 'foreign': 'Unicode')." character code ".sprintf("0x%08x", $characterCode)."\n");
					}
				if ($characterCodes->{$characterCode}!=$characterCode)
					{
					die("Error: the conversion from ".($outputIsUnicode? 'foreign': 'Unicode')." character code ".sprintf("0x%08x", $characterCode)." to ".($outputIsUnicode? 'Unicode': 'foreign')." character code ".sprintf("0x%08x", $characterCodes->{$characterCode})." is not a direct conversion\n");
					}
				delete $characterCodes->{$characterCode};
				}
			}
		elsif ($algorithm==1) # Offset
			{
			my $offset=$characterCodes->{$firstInputCharacterCodeInRange}-$firstInputCharacterCodeInRange;
			delete $characterCodes->{$firstInputCharacterCodeInRange};
			my $characterCode;
			for ($characterCode=$firstInputCharacterCodeInRange+1; $characterCode<=$lastInputCharacterCodeInRange; ++$characterCode)
				{
				if (!defined($characterCodes->{$characterCode}))
					{
					die("Error: There is no conversion defined for ".($outputIsUnicode? 'foreign': 'Unicode')." character code ".sprintf("0x%08x (0x%08x-0x%08x)", $characterCode, $firstInputCharacterCodeInRange, $lastInputCharacterCodeInRange)."\n");
					}
				if ($characterCodes->{$characterCode}-$characterCode!=$offset)
					{
					die("Error: the conversion from ".($outputIsUnicode? 'foreign': 'Unicode')." character code ".sprintf("0x%08x", $characterCode)." to ".($outputIsUnicode? 'Unicode': 'foreign')." character code ".sprintf("0x%08x", $characterCodes->{$characterCode})." has a different offset from the previous one in the range\n");
					}
				delete $characterCodes->{$characterCode};
				}
			&writeSignedIntegerCompacted29($fileHandle, $offset);
			}
		elsif ($algorithm==2) # IndexedTable16
			{
			my $characterCode;
			for ($characterCode=$firstInputCharacterCodeInRange; $characterCode<=$lastInputCharacterCodeInRange; ++$characterCode)
				{
				if (!defined($characterCodes->{$characterCode}))
					{
					die("Error: There is no conversion defined for ".($outputIsUnicode? 'foreign': 'Unicode')." character code ".sprintf("0x%08x", $characterCode)."\n");
					}
				&write16($fileHandle, $characterCodes->{$characterCode});
				delete $characterCodes->{$characterCode};
				}
			}
		elsif ($algorithm==3) # KeyedTable1616
			{
			my $characterCode;
			my @table=();
			for ($characterCode=$firstInputCharacterCodeInRange; $characterCode<=$lastInputCharacterCodeInRange; ++$characterCode)
				{
				if (defined($characterCodes->{$characterCode}))
					{
					push(@table, [$characterCode, $characterCodes->{$characterCode}]);
					delete $characterCodes->{$characterCode};
					}
				}
			my $firstIteration=1;
			my $lastKey;
			&writePositiveIntegerCompacted30($fileHandle, scalar(@table));
			if ($table[0][0]!=$firstInputCharacterCodeInRange)
				{
				die("Error: no conversion is specified for the first ".($outputIsUnicode? 'foreign': 'Unicode')." character code in the KeyedTable1616 range ".sprintf("0x%08x to 0x%08x", $firstInputCharacterCodeInRange, $lastInputCharacterCodeInRange)."\n");
				}
			my $pair;
			foreach $pair (@table)
				{
				my $key=$pair->[0];
				if ($firstIteration)
					{
					$firstIteration=0;
					}
				else
					{
					if ($key<=$lastKey)
						{
						die("Error: internal error 14\n");
						}
					&writePositiveIntegerCompacted15($fileHandle, $key-$lastKey);
					}
				&write16($fileHandle, $pair->[1]);
				$lastKey=$key;
				}
			}
		elsif ($algorithm==4) # KeyedTable16OfIndexedTables16
			{
			die("Error: \"KeyedTable16OfIndexedTables16\" is only supported if generating source code\n");
			}
		else
			{
			die("Error: internal error 15\n");
			}
		}
	my @characterCodes=sort({$a<=>$b} keys(%$characterCodes));
	if (@characterCodes>0)
		{
		die('The following '.($outputIsUnicode? 'foreign': 'Unicode').'characters have no conversion algorithm specified: ['.join(', ', map({sprintf('0x%x', $_)} @characterCodes))."\]\n");
		}
	}

