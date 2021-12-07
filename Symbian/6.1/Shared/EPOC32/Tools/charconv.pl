# CHARCONV.PL
#
# Copyright (c) 2000 Symbian Ltd.  All rights reserved.
#

use strict;
use integer;

sub PerlScriptPath
	{
	my $perlScriptPath=$0;
	$perlScriptPath=~s/\//\\/g; # replace any forward-slashes with back-slashes
	$perlScriptPath=~s/(\\?)[^\\]+$/$1/; # get rid of this Perl-script's file-name
	return $perlScriptPath;
	}
BEGIN
	{
	unshift(@INC, &PerlScriptPath()); # can't do "use lib &PerlScriptPath()" here as "use lib" only seems to work with *hard-coded* directory names
	}
use PARSER;
use UTF;

# The following numbers are used for byte-orders:
#     0 means unspecified
#     1 means big-endian
#     2 means little-endian

FixParametersToWorkWithWindows98(\@ARGV);
my $versionNumber = 3;
my $outputByteOrderMark = 0;
my $unicodeByteOrder = 0;
my $inputEncoding = ""; 
my $outputEncoding = ""; 
my %foreignCharacters = (); # Hash with the foreign Character code as the value, unicode as key 
my %unicodeCharacters = (); # Hash with the Unicode Character code as the value, foreign as key 


my $inputFile=\*STDIN;
my $outputFile=\*STDOUT;
ReadParameters(\@ARGV,\$outputByteOrderMark,\$unicodeByteOrder,\$inputEncoding,\$outputEncoding,\$inputFile,\$outputFile);
HandleByteOrderMarks($outputByteOrderMark,\$unicodeByteOrder, \$inputEncoding,\$outputEncoding, $inputFile, $outputFile);
DoConversion(\$unicodeByteOrder, \$inputEncoding, \$outputEncoding, $inputFile, $outputFile, \%foreignCharacters, \%unicodeCharacters);
if ($inputFile!=\*STDIN)
	{
	close($inputFile) or die;
	}
if ($outputFile!=\*STDOUT)
	{
	close($outputFile) or die;
	}

sub FixParametersToWorkWithWindows98
	{
	my $parameters=shift;
	my $i;
	for ($i=@$parameters-2; $i>=0; --$i) # iterate backwards as some parameters may be deleted from @$parameters
		{
		if (($parameters->[$i]=~/^(-input)$/i) ||
			($parameters->[$i]=~/^(-output)$/i))
			{
			$parameters->[$i].='='.$parameters->[$i+1];
			splice(@$parameters, $i+1, 1);
			}
		}
	}

sub PrintUsage 
	{
	print "\nVersion $versionNumber\n\nCharacter set conversion tool\nCopyright (c) 1999 Symbian Ltd\n\n";
	print "Usage:\n\n\t charconv [<options>] <inputspec> <outputspec>\n\nwhere\n\n\t";
	print "options    :=  [-big|-little][-byteordermark]\n\t";
	print "inputspec  :=  -input=<format> [<input_file>]\n\t";
	print "outputspec :=  -output=<format> [<output_file>]\n\t";
	print "format     :=  unicode|utf8|big5|gb2312...\n\n";
	}

sub Assert
	{
	my $condition = shift;
	my $errorMessage = shift;
	if (!($condition)) # find out where this is used and work this out 
		{
		die("Error: $errorMessage");
		}
	}

sub PrintWarning 
	{
	my $warningMessage = shift;
	print STDERR "Warning: $warningMessage\n";
	}
	

sub TryFileParameter 
	{
	my $args = shift;
	my $argindex = shift;
	my $inputoroutput = shift;
	my $encoding = shift;
	my $filehandle = shift;
	my $prefix = "-$inputoroutput=";

	if ($args->[$$argindex] =~ /^$prefix(.*)/)
		{
		Assert($$encoding eq "", "\"$prefix...\" is specified more than once");
		$$encoding = $1;
		++$$argindex;
		if (($$argindex >= @$args) || ($args->[$$argindex] =~ /^-/))
			{
			--$$argindex;
			}
		else
			{
			if ($inputoroutput =~ /input/i)
				{
				open(INPUT_FILE,"<$args->[$$argindex]") or die "opening $inputoroutput-file failed $!";
				$$filehandle=\*INPUT_FILE;
				}
			else
				{
				open(OUTPUT_FILE,">$args->[$$argindex]") or die "opening $inputoroutput-file failed $!";
				$$filehandle=\*OUTPUT_FILE;
				}
			}
		binmode $$filehandle;
		return  1;
		}
	return 0; 
	}

sub ReadParameters 
	{
	my $args = shift; 
	my $outputbyteordermark = shift;
	my $unicodebyteorder = shift;
	my $inputencoding = shift;
	my $outputencoding = shift;
	my $inputhandle = shift;
	my $outputhandle = shift;
	my $i;
	my $range;
	if ((@$args <= 0) || ($args->[0] eq "?") || ($args->[0] eq "/?"))
		{
		PrintUsage();
		exit;
		}

	for ($i = 0; $i < @$args ; ++$i)
		{
		if ( $args->[$i]=~ /-byteordermark/i)
			{
			Assert(!$$outputbyteordermark, "\"-byteordermark\" is specified more than once");
			$$outputbyteordermark = 1; 
			}
		elsif ($args->[$i]=~ /-big/i)
			{
			Assert(($$unicodebyteorder==0),"the byte order of unicode text (i.e. \"-big\"/\"-little\") is specified more than once");
			$$unicodebyteorder = 1;
			}
		elsif ($args->[$i]=~ /-little/i)
			{
			Assert(($$unicodebyteorder==0),"the byte order of unicode text (i.e. \"-big\"/\"-little\") is specified more than once");
			$$unicodebyteorder = 2;
			}
		else
			{ 
			Assert(TryFileParameter($args, \$i, "input",$inputencoding,$inputhandle) ||
				   TryFileParameter($args, \$i, "output",$outputencoding, $outputhandle), "bad parameter \"$args->[$i]\"");
			}
		}
	Assert($$inputencoding ne "", "no input encoding is specified");
	Assert($$outputencoding ne "", "no output encoding is specified");
	}

sub ReadFromFile
	{  
	my $buffer = shift;
	my $numOfBytesToRead = shift;
	my $inputhandle = shift;
	my $numOfBytesRead = 0;									
	my $numOfBytesToReadThisTime = $numOfBytesToRead;		

	for(;;)
		{
		for(;;)
			{
			my $remainingNumOfBytesToRead = $numOfBytesToRead - $numOfBytesRead;  
			if ($numOfBytesToReadThisTime > $remainingNumOfBytesToRead)
				{
				$numOfBytesToReadThisTime = $remainingNumOfBytesToRead;
				}  		
			my $numOfBytesReadThisTime = read $inputhandle, $$buffer, $numOfBytesToReadThisTime;  
			if (defined $numOfBytesReadThisTime)
				{
				$numOfBytesRead += $numOfBytesReadThisTime;
				Assert($numOfBytesRead <= $numOfBytesReadThisTime, "internal error (read too many bytes)");
				if (($numOfBytesRead >= $numOfBytesReadThisTime) || $numOfBytesReadThisTime == 0)
					{
					return;
					}
				last;
				}
			$numOfBytesToReadThisTime /= 2;
			Assert($numOfBytesToReadThisTime >0, "reading from file failed");
			}
		}
	}

sub HandleByteOrderMarks 
	{
	my $outputbyteordermark = shift;
	my $unicodebyteorder = shift;
	my $inputencoding = shift;
	my $outputencoding = shift;
	my $inputhandle = shift;
	my $outputhandle = shift;

	if ($$inputencoding =~ /unicode/i) 
		{
		my $firstUnicodeCharacter = 0; 
		ReadFromFile(\$firstUnicodeCharacter, 2, $inputhandle);
		my $byteOrderSpecifiedByByteOrderMark = 0;
		if (length($firstUnicodeCharacter) == 2)
			{
			my @firstUnicodeCharacter = unpack "C*", $firstUnicodeCharacter;
			if (($firstUnicodeCharacter[0]==0xff) && ($firstUnicodeCharacter[1]==0xfe))
				{
				$byteOrderSpecifiedByByteOrderMark = 2; 
				}
			elsif (($firstUnicodeCharacter[0]==0xfe) && ($firstUnicodeCharacter[1]==0xff))
				{
				$byteOrderSpecifiedByByteOrderMark = 1; 
				}
			else
				{
				my $error = seek $inputhandle, 0, 0; # rewind to start of file
				Assert ($error == 1, "could not rewind to the start of input file");
				}
			}
		if ($byteOrderSpecifiedByByteOrderMark!=0)
			{
			if (($$unicodebyteorder!=0) && ($byteOrderSpecifiedByByteOrderMark!=$$unicodebyteorder))
				{
				PrintWarning ("the byte order specified by the byte-order mark in the unicode input is different from the byte order specified by the parameter - taking the byte-order specified by the byte-order mark in the unicode input");
				}
			$$unicodebyteorder = $byteOrderSpecifiedByByteOrderMark;
			}
		}
	if ($outputbyteordermark)
		{
		if ($$outputencoding ne "unicode") 
			{
			PrintWarning("\"-byteordermark\" is only relevant for unicode output");
			}
		else
			{
			Assert($$unicodebyteorder!=0, "the byte order must be specified if a byte-order mark is to be added to the unicode output");
			my $firstUnicodeCharacter=($$unicodebyteorder==1)? "\xfe\xff": "\xff\xfe";
			WriteToFile(\$firstUnicodeCharacter, $outputhandle);
			}
		}
	}

sub WriteToFile 
	{
	my $buffer = shift;
	my $outputhandle = shift;

	print $outputhandle $$buffer;
	}

sub DoConversion
	{
	my $unicodebyteorder = shift;
	my $inputencoding = shift;
	my $outputencoding = shift;
	my $inputhandle = shift;
	my $outputhandle = shift; 
	my $foreignCharacters = shift;
	my $unicodeCharacters = shift;
	
	my $currentBuffer = 0;
	my @arrayOfBuffers = ('', '', '');
	my $largeNumber=1000000;
	ReadFromFile(\($arrayOfBuffers[$currentBuffer]), $largeNumber, $inputhandle);
	ReverseByteOrderIfUnicodeAndBigEndian($unicodebyteorder, $inputencoding, \($arrayOfBuffers[$currentBuffer]));
	if ($$inputencoding ne $$outputencoding) 
		{
		if ($$inputencoding !~ /^unicode$/i)
			{
			my $nextBuffer = $currentBuffer + 1;
			OtherToUnicode ($inputencoding, \($arrayOfBuffers[$nextBuffer]), ($arrayOfBuffers[$currentBuffer]), $foreignCharacters, $unicodeCharacters, 'v');
			$currentBuffer = $nextBuffer;
			}
		if ($$outputencoding !~ /^unicode$/i)
			{
			my $nextBuffer = $currentBuffer + 1;
			UnicodeToOther($outputencoding, \($arrayOfBuffers[$nextBuffer]), ($arrayOfBuffers[$currentBuffer]), $foreignCharacters, $unicodeCharacters, 'v');
			$currentBuffer = $nextBuffer;
			}
		}
	ReverseByteOrderIfUnicodeAndBigEndian($unicodebyteorder, $outputencoding, \($arrayOfBuffers[$currentBuffer]));
	WriteToFile(\($arrayOfBuffers[$currentBuffer]), $outputhandle);
	}

sub ReverseByteOrderIfUnicodeAndBigEndian
	{
	my $unicodebyteorder = shift;
	my $encoding = shift;
	my $buffer = shift;
	my $i;

	if ($$encoding =~ /^unicode$/i)
		{
		Assert(length($$buffer)%2==0, "internal error (bad number of bytes in unicode buffer)");
		if ($$unicodebyteorder==0)
			{
			PrintWarning("the byte order of unicode text is unspecified - defaulting to little-endian");
			$$unicodebyteorder = 2;
			}
		if ($$unicodebyteorder==1)
			{
			$$buffer=pack('v*', unpack('n*', $$buffer));
			}
		}
	}

sub FillInHashes
	{
	my $foreignCharacters = shift;
	my $unicodeCharacters = shift;
	my $encoding = shift; 
	my $replacementCharacter = shift;
	my $ranges = shift;
	my $bigEndian = shift;

	my $endianness = 0;
	my $replacenum = 0;
	my $rangenum = 0;
	my $fileread = 0;
	my $largenumber = 1000000;

	my $dataFile=&PerlScriptPath()."charconv\\".$$encoding.'.dat';

	my $line;

	if (-e $dataFile)
		{
		open (HASH_INPUT, "< $dataFile") or die ("Could not open file for reading");
		
		binmode HASH_INPUT;
		# reading the endianness
		$fileread = read HASH_INPUT, $endianness, 1;
		$endianness = unpack "C",$endianness;
		if ($endianness == 0)
			{
			# set the template to a default-> n for the eman time
			$$bigEndian = 0;
			}
		elsif ($endianness == 1)
			{
			$$bigEndian = 0;
			}
		elsif ($endianness == 2)
			{
			$$bigEndian = 1;
			}
		else
			{
			print "Illegal Endianness specified in the control files";
			}
		#reading the replacement characters
		$fileread = read HASH_INPUT, $replacenum,1;
		$replacenum= unpack "C",$replacenum;
		$fileread = read HASH_INPUT, $$replacementCharacter,$replacenum;
		# reading the ranges
		$fileread = read HASH_INPUT, $rangenum, 1;
		$rangenum = unpack "C",$rangenum;
		my $i; # loop variable 
		for ($i=0; $i < $rangenum; ++$i)
			{
			my $lowerrange = 0;
			my $upperrange = 0;
			my $followchar = 0;

			$fileread = read HASH_INPUT,$lowerrange,1;
			$lowerrange = unpack "C",$lowerrange;
			$fileread = read HASH_INPUT,$upperrange,1;
			$upperrange = unpack "C",$upperrange;
			$fileread = read HASH_INPUT,$followchar,1;
			$followchar = unpack "C",$followchar;

			push @$ranges,[$lowerrange,$upperrange,$followchar];
			}
		my $data = 0;
		my @unpackeddata = 0;
		$fileread = read HASH_INPUT, $data, $largenumber;
		@unpackeddata = unpack "v*",$data;
		for($i = 0; $i <= $#unpackeddata; $i= $i+2)
			{
			$unicodeCharacters->{$unpackeddata[$i]}=$unpackeddata[$i+1];
			$foreignCharacters->{$unpackeddata[$i+1]}=$unpackeddata[$i];
			}
		}
	else
		{
		die ("Encoding Format \"$$encoding\" not recognised");
		}
	}

sub OtherToUnicode
	{
	my $inputencoding = shift;
	my $unicode = shift;  
	my $other = shift; 
	my $foreignCharacters = shift;
	my $unicodeCharacters = shift;
	my $unicodetemplate = shift;
	my $replacementCharacter = 0;
	my $unicodeReplacementCharacter = pack($unicodetemplate, 0xfffd);
	my @ranges=(); 
 
	my $otherIndex= 0;
	my $numOfBytes = length($other);
	my $key = 0;
	my $inRange = 0;
	my $followByte = -1;

	if ($$inputencoding=~/^utf8$/i)
		{
		return &Utf8ToUnicode($unicode, $other, $unicodetemplate);
		}
	my $bigEndian;
	FillInHashes($foreignCharacters,$unicodeCharacters, $inputencoding, \$replacementCharacter,\@ranges,\$bigEndian);
	for (;;)
		{
		if ($otherIndex > $numOfBytes -1) 
			{
			last;
			}
		my $frontByte = (unpack("x$otherIndex".'C', $other))[0];
		# @ranges is an array of references. Each reference is a reference to an array
		for ($key = 0; $key <= $#ranges; ++$key)
			{
			my $arrayref = $ranges[$key];
			if (($frontByte >= $arrayref->[0]) && ($frontByte <= $arrayref->[1]))
				{
				$followByte = $arrayref->[2];
				$inRange = 1;
				}
			}
		Assert ($inRange != 0, "cannot figure out the Byte size of the character");
		my $tempByte = 0;
		for ($key = 0; $key<= $followByte; ++$key)
			{
			if ($bigEndian)
				{
				$tempByte = ($tempByte << 8) | (unpack("x$otherIndex".'C', $other))[0];
				}
			else
				{
				$tempByte = $tempByte | ((unpack("x$otherIndex".'C', $other))[0] << (8*$key));
				}
			$otherIndex++;	
			}
		if (exists $unicodeCharacters->{$tempByte})
			{
			$$unicode .= pack $unicodetemplate , $unicodeCharacters->{$tempByte};
			}
		else
			{
			$$unicode .= $unicodeReplacementCharacter;
			}
		}
	}

sub UnicodeToOther
	{
	my $outputencoding = shift;
	my $other = shift;
	my $unicode = shift;
	my $foreignCharacters = shift;
	my $unicodeCharacters = shift;
	my $unicodetemplate = shift;
	my $replacementCharacter = 0;
	my @ranges=(); 

	my $unicodeIndex= 0;
	my $numOfBytes = length($unicode);
	my @UnicodeUnpacked = ();
	my $key = 0;

	if ($$outputencoding=~/^utf8$/i)
		{
		return &UnicodeToUtf8($other, $unicode, $unicodetemplate);
		}
	my $bigEndian;
	FillInHashes($foreignCharacters,$unicodeCharacters, $outputencoding, \$replacementCharacter,\@ranges,\$bigEndian);
	my $foreignTemplate=$bigEndian? 'n': 'v';
	@UnicodeUnpacked = unpack "$unicodetemplate*", $unicode;
	foreach $key (@UnicodeUnpacked)
		{
		if (!exists($foreignCharacters->{$key}))
			{
			$$other .= $replacementCharacter;
			}
		else
			{
			# This is the WRONG but it will work for the mean time
			# This will fail if the foreignCharacter has characters that are more than
			# two bytes long ..... But this should work for foreign characters of 1 or 2 Bytes

			my $foreignValue = $foreignCharacters->{$key};
			if ( $foreignValue <= 255)
				{
				$$other .= pack "C" , $foreignValue;
				}
			else
				{
				$$other .= pack $foreignTemplate, $foreignValue;
				}
			}
		}
	}

