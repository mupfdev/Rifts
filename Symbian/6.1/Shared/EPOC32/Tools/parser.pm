# PARSER.PM
#
# Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
#

use strict;
use integer;

package PARSER;
require Exporter;
@PARSER::ISA=qw(Exporter);
@PARSER::EXPORT=qw(nextNonEmptyStrippedDownLine ungetNonEmptyStrippedDownLine);

# @PARSER::nextNonEmptyStrippedDownLine is a global variable in this package

sub strippedDownLine
	{
	my $strippedDownLine=shift;
	$strippedDownLine=~s/#.*$//;
	$strippedDownLine=~s/^\s+//;
	$strippedDownLine=~s/\s+$//;
	return $strippedDownLine;
	}

sub nextNonEmptyStrippedDownLine
	{
	my $fileHandle=shift;
	if (defined(@PARSER::nextNonEmptyStrippedDownLine) && (@PARSER::nextNonEmptyStrippedDownLine>0))
		{
		if (@{$PARSER::nextNonEmptyStrippedDownLine[0]}!=2)
			{
			close($fileHandle);
			die("Error: internal error in \"PARSER.PM\"\n");
			}
		return @{shift(@PARSER::nextNonEmptyStrippedDownLine)};
		}
	my $buffer='';
	my $line;
	while ($line=<$fileHandle>)
		{
		$buffer.=$line;
		my $strippedDownBuffer=&strippedDownLine($buffer);
		if ($strippedDownBuffer!~/\\$/)
			{
			$strippedDownBuffer=~s/\\\n/ /g;
			if ($strippedDownBuffer ne '')
				{
				return ($buffer, $strippedDownBuffer);
				}
			$buffer='';
			}
		}
	if ($buffer ne '')
		{
		close($fileHandle);
		die("Error: file ends with a \"\\\"\n");
		}
	return ('', '');
	}

sub ungetNonEmptyStrippedDownLine
	{
	my $arrayCopy;
	@$arrayCopy=@_;
	unshift(@PARSER::nextNonEmptyStrippedDownLine, $arrayCopy);
	}

