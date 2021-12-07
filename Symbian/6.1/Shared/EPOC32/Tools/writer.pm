# WRITER.PM
#
# Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
#

use strict;
use integer;

package WRITER;
require Exporter;
@WRITER::ISA=qw(Exporter);
@WRITER::EXPORT=qw(write8 write16 write32 writePositiveIntegerCompacted15 writePositiveIntegerCompacted30 writeSignedIntegerCompacted29 writeString writeUids);

sub write8
	{
	my $fileHandle=shift;
	my $integer=shift;
	if ($integer&0xffffff00)
		{
		die("Error: the integer ".sprintf("0x%08x", $integer)." is too large to write into 8 bits\n");
		}
	printf $fileHandle "%c", $integer;
	}

sub write16 # little-endian
	{
	my $fileHandle=shift;
	my $integer=shift;
	if ($integer&0xffff0000)
		{
		die("Error: the integer ".sprintf("0x%08x", $integer)." is too large to write into 8 bits\n");
		}
	&write8($fileHandle, $integer&0x000000ff);
	&write8($fileHandle, ($integer>>8)&0x000000ff);
	}

sub write32 # little-endian
	{
	my $fileHandle=shift;
	my $integer=shift;
	&write8($fileHandle, $integer&0x000000ff);
	&write8($fileHandle, ($integer>>8)&0x000000ff);
	&write8($fileHandle, ($integer>>16)&0x000000ff);
	&write8($fileHandle, ($integer>>24)&0x000000ff);
	}

sub writePositiveIntegerCompacted15 # big-endian
	{
	my $fileHandle=shift;
	my $integer=shift;
	if ($integer<0)
		{
		die("Error: the integer ".sprintf("0x%08x", $integer)." is negative\n");
		}
	if ($integer<0x00000080)
		{
		&write8($fileHandle, $integer);
		}
	elsif ($integer<0x00008000)
		{
		&write8($fileHandle, 0x00000080|(($integer>>8)&0x0000007f));
		&write8($fileHandle, $integer&0x000000ff);
		}
	else
		{
		die("Error: the integer ".sprintf("0x%08x", $integer)." is too large to write into 15 bits\n");
		}
	}

sub writePositiveIntegerCompacted30 # big-endian
	{
	my $fileHandle=shift;
	my $integer=shift;
	if ($integer<0)
		{
		die("Error: the integer ".sprintf("0x%08x", $integer)." is negative\n");
		}
	if ($integer<0x00000080)
		{
		&write8($fileHandle, $integer);
		}
	elsif ($integer<0x00004000)
		{
		&write8($fileHandle, 0x00000080|(($integer>>8)&0x0000003f));
		&write8($fileHandle, $integer&0x000000ff);
		}
	elsif ($integer<0x40000000)
		{
		&write8($fileHandle, 0x000000c0|(($integer>>24)&0x0000003f));
		&write8($fileHandle, ($integer>>16)&0x000000ff);
		&write8($fileHandle, ($integer>>8)&0x000000ff);
		&write8($fileHandle, $integer&0x000000ff);
		}
	else
		{
		die("Error: the integer ".sprintf("0x%08x", $integer)." is too large to write into 30 bits\n");
		}
	}

sub writeSignedIntegerCompacted29 # big-endian
	{
	my $fileHandle=shift;
	my $integer=shift;
	my $negativeFlag=0x00000000;
	if ($integer<0)
		{
		$negativeFlag=0x00000080;
		if (($integer^-$integer)==0)
			{
			die("Error: the integer ".sprintf("0x%08x", $integer)." is too large to write into 29 bits\n");
			}
		$integer=-$integer;
		}
	if ($integer<0x00000040)
		{
		&write8($fileHandle, $negativeFlag|$integer);
		}
	elsif ($integer<0x00002000)
		{
		&write8($fileHandle, $negativeFlag|0x00000040|(($integer>>8)&0x0000001f));
		&write8($fileHandle, $integer&0x000000ff);
		}
	elsif ($integer<0x20000000)
		{
		&write8($fileHandle, $negativeFlag|0x00000060|(($integer>>24)&0x0000001f));
		&write8($fileHandle, ($integer>>16)&0x000000ff);
		&write8($fileHandle, ($integer>>8)&0x000000ff);
		&write8($fileHandle, $integer&0x000000ff);
		}
	else
		{
		die("Error: the integer ".sprintf("0x%08x", $integer)." is too large to write into 30 bits\n");
		}
	}

sub writeString
	{
	my $fileHandle=shift;
	my $string=shift;
	my $lengthOfString=length($string);
	my $i;
	for ($i=0; $i<$lengthOfString; ++$i)
		{
		my $byteAsNumber;
		($byteAsNumber)=unpack("C", substr($string, $i, 1));
		&write8($fileHandle, $byteAsNumber);
		}
	}

sub writeUids
	{
	my $fileHandle=shift;
	my $uid1=shift;
	my $uid2=shift;
	my $uid3=shift;
	use Cwd;
	system("UIDCRC.EXE ".sprintf("0x%08x 0x%08x 0x%08x ", $uid1, $uid2, $uid3).cwd()."\\UIDCRC.DAT");
	open(UIDCRC_DATA_FILE, "< ".cwd()."\\UIDCRC.DAT") or die("Error: could not open \"".cwd()."\\UIDCRC.DAT\" for reading\n");
	binmode UIDCRC_DATA_FILE;
	my $uidCrcBinaryBuffer="";
	my $numberOfBytesActuallyRead=read(UIDCRC_DATA_FILE, $uidCrcBinaryBuffer, 17);
	close(UIDCRC_DATA_FILE);
	unlink "UIDCRC.DAT"; # "unlink" deletes the specified file
	if (($numberOfBytesActuallyRead!=16) || (length($uidCrcBinaryBuffer)!=16))
		{
		die("Error: UIDCRC.DAT is not the expected length\n");
		}
	&writeString($fileHandle, $uidCrcBinaryBuffer);
	}

