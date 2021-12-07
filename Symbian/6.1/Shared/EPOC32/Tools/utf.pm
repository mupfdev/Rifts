# UTF.PM
#
# Copyright (c) 2000 Symbian Ltd.  All rights reserved.
#

use strict;
use integer;

package UTF;
require Exporter;
@UTF::ISA=qw(Exporter);
@UTF::EXPORT=qw(Utf8ToUnicode UnicodeToUtf8);

my $KErrorIllFormedInput=-1;

sub Utf8ToUnicode
	{
	my $Unicode = shift;  
	my $Utf8 = shift;
	my $UnicodeTemplate = shift;
	my $Utf8Index = 0;
	my $UnicodeIndex = 0;
	my $numOfBytes = length($Utf8);
	my @Utf8Unpacked = unpack "C*",$Utf8;
	my @UnicodeUnpacked = (); 

	for (;;)
		{
		if ($Utf8Index > $#Utf8Unpacked)
			{
			last;
			}

		my $currentUtf8Byte = $Utf8Unpacked[$Utf8Index];
		
		if (($currentUtf8Byte&0x80)==0x00)
			{
			$UnicodeUnpacked[$UnicodeIndex] = $currentUtf8Byte;
			}
		
		elsif (($currentUtf8Byte&0xe0)==0xc0)
			{
			my $currentUnicodeCharacter=(($currentUtf8Byte&0x1f)<<6);
			++$Utf8Index;
			$currentUtf8Byte=$Utf8Unpacked[$Utf8Index];
			if (($currentUtf8Byte&0xc0)!=0x80)
				{
				return $KErrorIllFormedInput;
				}
			$currentUnicodeCharacter|=($currentUtf8Byte&0x3f);
			$UnicodeUnpacked[$UnicodeIndex] = $currentUnicodeCharacter;
			}

		elsif (($currentUtf8Byte&0xf0)==0xe0)
			{
			my $currentUnicodeCharacter=(($currentUtf8Byte&0x0f)<<12);
			++$Utf8Index;
			$currentUtf8Byte=$Utf8Unpacked[$Utf8Index];
			if (($currentUtf8Byte&0xc0)!=0x80)
				{
				return $KErrorIllFormedInput;
				}
			$currentUnicodeCharacter|=(($currentUtf8Byte&0x3f)<<6);
			++$Utf8Index;
			$currentUtf8Byte=$Utf8Unpacked[$Utf8Index];
			if (($currentUtf8Byte&0xc0)!=0x80)
				{
				return $KErrorIllFormedInput;
				}
			$currentUnicodeCharacter|=($currentUtf8Byte&0x3f);
			$UnicodeUnpacked[$UnicodeIndex] = $currentUnicodeCharacter;
			}

		elsif (($currentUtf8Byte&0xf8)==0xf0)
			{                                         
			my $currentUnicodeCharacter=(($currentUtf8Byte&0x07)<<8);
			++$Utf8Index;
			$currentUtf8Byte=$Utf8Unpacked[$Utf8Index];
			if (($currentUtf8Byte&0xc0)!=0x80)
				{
				return $KErrorIllFormedInput;
				}
			$currentUnicodeCharacter|=(($currentUtf8Byte&0x3f)<<2);
			if ($currentUnicodeCharacter<0x0040)
				{
				return $KErrorIllFormedInput;
				}
			$currentUnicodeCharacter-=0x0040;
			if ($currentUnicodeCharacter>=0x0400)
				{
				return $KErrorIllFormedInput;
				}
			++$Utf8Index;
			$currentUtf8Byte=$Utf8Unpacked[$Utf8Index];
			if (($currentUtf8Byte&0xc0)!=0x80)
				{
				return $KErrorIllFormedInput;
				}
			$currentUnicodeCharacter|=(($currentUtf8Byte&0x30)>>4);
			$UnicodeUnpacked[$UnicodeIndex] = (0xd800|$currentUnicodeCharacter);
			$currentUnicodeCharacter=(($currentUtf8Byte&0x0f)<<6);
			++$Utf8Index;
			$currentUtf8Byte=$Utf8Unpacked[$Utf8Index];
			if (($currentUtf8Byte&0xc0)!=0x80)
				{
				return $KErrorIllFormedInput;
				}
			$currentUnicodeCharacter|=($currentUtf8Byte&0x3f);
			++$UnicodeIndex;
			$UnicodeUnpacked[$UnicodeIndex] = (0xdc00|$currentUnicodeCharacter);
			}
		else
			{
			return $KErrorIllFormedInput;
			}
		++$UnicodeIndex;
		++$Utf8Index;
		}
	$$Unicode = (); 
	$$Unicode = pack "$UnicodeTemplate*", @UnicodeUnpacked;
	return $UnicodeIndex;  
	}

sub UnicodeToUtf8
	{
	my $Utf8 = shift; 
	my $Unicode = shift;
	my $UnicodeTemplate = shift;
	my $Utf8Index = 0;
	my $UnicodeIndex = 0;
	my $numOfBytes = length($Unicode);
	my @UnicodeUnpacked = unpack "$UnicodeTemplate*", $Unicode;
	my @Utf8Unpacked = ();
	
	for (;;)
		{
		# exit the loop if no more in the UnicodeUnpacked
		if ($UnicodeIndex > $#UnicodeUnpacked)
			{
			last;
			}

		my $currentUnicodeCharacter=$UnicodeUnpacked[$UnicodeIndex];
		if (($currentUnicodeCharacter&0xff80)==0x0000)
			{	
			$Utf8Unpacked[$Utf8Index]= $currentUnicodeCharacter;
			}
		elsif (($currentUnicodeCharacter&0xf800)==0x0000)
			{

			$Utf8Unpacked[$Utf8Index]= (0xc0 | $currentUnicodeCharacter >> 6);
			++$Utf8Index;
			$Utf8Unpacked[$Utf8Index]= (0x80 | $currentUnicodeCharacter&0x3f);
			}
		elsif (($currentUnicodeCharacter&0xfc00)==0xd800)
			{
			$currentUnicodeCharacter+=0x0040;
			$Utf8Unpacked[$Utf8Index]= (0xf0|(($currentUnicodeCharacter>>8)&0x07));
			++$Utf8Index;
			$Utf8Unpacked[$Utf8Index]= (0x80|(($currentUnicodeCharacter>>2)&0x3f));
			my $currentUtf8Byte=(0x80|(($currentUnicodeCharacter&0x03)<<4));
			++$UnicodeIndex;
			$currentUnicodeCharacter=$UnicodeUnpacked[$UnicodeIndex];
			if (($currentUnicodeCharacter&0xfc00)!=0xdc00)
				{
				return $KErrorIllFormedInput;
				}
			$currentUtf8Byte|=(($currentUnicodeCharacter>>6)&0x0f);
			++$Utf8Index;
			$Utf8Unpacked[$Utf8Index]= $currentUtf8Byte;
			++$Utf8Index;
			$Utf8Unpacked[$Utf8Index]= (0x80| ($currentUnicodeCharacter&0x3f));
			}
		else
			{
			$Utf8Unpacked[$Utf8Index]= (0xe0|($currentUnicodeCharacter>>12));
			++$Utf8Index;
			$Utf8Unpacked[$Utf8Index]= (0x80|(($currentUnicodeCharacter>>6)&0x3f));
			++$Utf8Index;
			$Utf8Unpacked[$Utf8Index]= (0x80| ($currentUnicodeCharacter&0x3f));
			}
		++$Utf8Index;
		++$UnicodeIndex;
		}
	$$Utf8 = ();	
	$$Utf8 = pack "C*", @Utf8Unpacked;
	return $Utf8Index; 

	}
