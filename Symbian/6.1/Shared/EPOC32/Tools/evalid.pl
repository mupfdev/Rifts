# EVALID.PL
#
# Copyright (c) 1999-2000 Symbian Ltd.  All rights reserved.
#

# Validate releasables
#
# See below for usage
# 

use Getopt::Long;
use Cwd;

GetOptions("c", "v", "l=s");

if (@ARGV==3)
	{
	shift;	# throw away the type
	}

if (@ARGV!=2)
	{
#........1.........2.........3.........4.........5.........6.........7.....
	print <<USAGE_EOF;

Usage:
  evalid [opts] [-v] [type] file1 file2     -- compare two files
  evalid [opts] [-v] [type] dir1  dir2      -- recursively compare two trees

The recursive form will take each file in the tree rooted at dir1, 
determine its type, and using the appropriate comparison attempt to
compare it with the corresponding file in the tree rooted at dir2.

  evalid file1 dir2   =>  evalid file1      dir2\\file1
  evalid dir1  file2  =>  evalid dir1\\file1 file2

The opts parameter controls where the output goes:

	-v              -- verbose information about failed comparisons
	-c              -- print results to standard output
	-l <logfile>    -- append results to <logfile>

The default is equivalent to "-l evalid.lis"

The type parameter is ignored but included for backwards compatibility - 
this version of evalid will determine the file types automatically.

USAGE_EOF
	exit 1;
	}

# Redirect output

if ($opt_c)
	{
	$log = \*STDOUT;
	}
else
	{
	if (!$opt_l)
		{
		$opt_l = "evalid.lis";
		}
	open LOG, ">>$opt_l" or die "Cannot open logfile $opt_l\n";
	$log = \*LOG;
	}

# Make the comparison(s)

compare(@ARGV[0], @ARGV[1]);

# Summarise the results

$total=$passed+$failed;

if ($total > 1)
	{
	print $log "\nResults of evalid  @ARGV[0]  @ARGV[1]\n";
	}

if (@missing)
	{
	if ($total>1)
		{
		printf $log "\n%d missing files\n\n", scalar @missing;
		}
	map {
		print $log "MISSING: $_\n";
		} @missing;
	}

if (@failures)
	{
	if ($total>1)
		{
		printf $log "\n%d failed comparisons\n\n", scalar @failures;
		}
	map {
		my ($left, $right, $type) = @{$_};
		print $log "FAILED: $left\tand $right  ($type)\n";
		} @failures;
	}

if ($total>1)
	{
	my ($sec, $min, $hour, $mday, $mon, $year) = localtime(time);
	printf $log "\n----------------\n%02d:%02d %02d/%02d/%04d\n", $hour, $min, $mday, $mon+1, $year+1900;
	print $log "evalid  @ARGV[0]  @ARGV[1]\n";
	if ($failed==0)
		{
		print $log "Passed all $total comparisons\n";
		}
	else
		{
		print $log "Failed $failed of $total comparisons\n";
		}
	
	print $log "----------------\n\n";
	}

exit($failed==0);

#---------------------------------
sub identical
	{
	my ($left, $right, $type)=@_;
	print $log "OK: $left\tand $right  ($type)\n";
	$passed+=1;
	}

sub different
	{
	my ($left, $right, $type)=@_;
	push @failures, [$left, $right, $type];
	$failed+=1;
	}

sub warning
	{
	my ($message)=@_;
	print $log "WARNING: $message\n";
	if (!$opt_c)
		{
		print "WARNING: $message\n";
		}
	# not a test failure as such
	}

sub problem
	{
	my ($message)=@_;
	print $log "PROBLEM: $message\n";
	$failed+=1;
	}

sub missing
	{
	my ($left) = @_;
	push @missing, $left;
	$failed+=1;
	}

sub compare
	{
	my ($left, $right, $recursing) = @_;
	if (-d $left && -d $right)
		{
		# Read all of the directory entries except . and ..
		# in to a local list.
		opendir LEFTDIR, $left or print "Cannot read directory $left\n" and return;
		my @list = grep !/^\.\.?$/, readdir LEFTDIR;
		closedir LEFTDIR;
		# recurse
		map { 
			compare($left."\\".$_, $right."\\".$_, 1);
			} @list;
		return;
		}
	if (-d $left)
		{
		if ($recursing)
			{
			if (-e $right)
				{
				problem("File $right should be a directory");
				}
			else
				{
				problem("Directory $right does not exist");
				}
			return;
			}
		compare($left."\\".$right,$right);
		return;
		}
	if (-d $right)
		{
		if ($recursing)
			{
			problem("Directory $right should be a file");
			return;
			}
		compare($left,$right."\\".$left);
		return;
		}
	# comparing files
	if (-e $left && !-e $right)
		{
		missing($right);
		return;
		}
	if (!-e $left && -e $right)
		{
		problem("File $left does not exist");
		return;
		}

	open LEFT, $left or problem("Cannot open $left") and return;
	open RIGHT, $right or problem("Cannot open $right") and return;

	binmode LEFT;
	binmode RIGHT;

	# Try a straight binary comparison anyway

	if ((-s $left == -s $right) && compare_streams(LEFT, RIGHT))
		{
		close LEFT;
		close RIGHT;
		identical($left, $right, "binary");
		return;
		}
	close RIGHT;

	# Hmm, not identical then... Find the type of file1

	seek LEFT, 0, 0;
	read LEFT, $leftbuf, 512;
	close LEFT;

	my $type = "unknown format";
	my $same = 0;

	my ($uid1, $uid2, $uid3, $checksum) = unpack "V4", $leftbuf;

	# NB. Need to use the s modifier so that '.' will match \x0A

	IDENTIFY_FORMAT: 
		{
		if ($leftbuf =~ /^.\x00\x00\x10.{12}EPOC.{24}(.)\x00\x00\x00/s)
			{
			# E32 Image file with a 0x100000?? UID1
			# $1 is the flag field indicating an EXE or a DLL
			# See e32tools\inc\e32image.h
			#
			if ((ord $1) & 0x1)
				{
				$type = "E32 DLL";
				}
			else
				{
				$type = "E32 EXE";
				}
			$same=compare_e32image($left,$right);
			last;
			}

		if ($leftbuf =~ /^\x4D\x5A.{38}\x00{20}(....)/s)
			{
			# A standard 64-byte MS-DOS header with e_magic == IMAGE_DOS_SIGNATURE
			# $1 is e_lfanew, which we expect to point to a COFF header

			my $offset = unpack "V",$1;
			if ($offset + 24 <= length $leftbuf)
				{
				$leftbuf = substr $leftbuf, $offset;
				}
			else
				{
				open LEFT, $left or problem("Cannot open $left") and return;
				binmode LEFT;
				seek LEFT, $offset, 0;
				read LEFT, $leftbuf, 512;
				close LEFT;
				}

			if ($leftbuf =~ /^PE\0\0\x4c\x01.{16}(..)/s)
				{
				# A PE signature "PE\0\0" followed by a COFF header with 
				# machine type IMAGE_FILE_MACHINE_I386
				# $1 is the characteristics field
				#
				if ((unpack "v",$1) & 0x2000)
					{
					$type = "Intel DLL";
					}
				else
					{
					$type = "Intel EXE";
					}
				$same = compare_intelpe($left,$right);
				}
			else
				{
				$type = "MSDOS executable";
				$same = compare_dumpbin($left,$right);
				}
			last;
			}

		if ($leftbuf =~ /^(\x4c\x01|\x00\x0A).(\x00|\x01).{4}...\x00/s)
			{
			# COFF header with less than 512 sections and a symbol table 
			# at an offset no greater than 0x00ffffff
			
			if ($1 eq "\x4c\x01")
				{
				$type = "Intel object";
				$same = compare_dumpbin($left, $right);
				}
			elsif ($1 eq "\x00\x0A")
				{
				$type = "ARM object";
				$same = compare_nm($left, $right);
				}
			else
				{
				$type = "Unknown COFF object";
				}
			last;
			}

		if ($leftbuf =~ /^!<arch>\x0A(.{48}([0-9 ]{10})\x60\x0A(..))/s)
			{
			# library - could be MARM or WINS

			$type = "unknown library";
			$leftbuf = $1;
			my $member_start = 8;

			open LEFT, $left or problem("Cannot open $left") and return;
			binmode LEFT;

			while ($leftbuf =~ /^.{48}([0-9 ]{10})\x60\x0A(..)/s) 
				{
				# $1 is the size of the archive member, $2 is first 2 bytes of the file
				# There may be several different sorts of file in the archive, and we
				# need to scan through until we find a type we recognize:
				# $2 == 0x0A00 would be ARM COFF, 0x014C would be Intel COFF
				if ($2 =~ /\x00\x0A/)
					{
					close LEFT;
					$type = "ARM library";
					$same = compare_nm($left,$right);
					last;
					}
				if ($2 =~ /\x4C\x01/)
					{
					close LEFT;
					$type = "Intel library";
					$same = compare_dumpbin($left,$right);
					last;
					}

				$member_start += 60 + $1;
				if ($member_start & 0x1)
					{
					$member_start += 1;		# align to multiple of 2 bytes
					}
				seek LEFT, $member_start, 0;
				read LEFT, $leftbuf, 512;
				}
			close LEFT;
			last;
			}

		if ($leftbuf =~ /^\xCA\xFE\xBA\xBE/)
			{
			# Java class file - should have matched as a straight binary comparison
			$type = "Java class";
			$same = 0;
			last;
			}

		if ($leftbuf =~ /^PK\x03\x04/)
			{
			# ZIP file
			$type = "ZIP file";
			$same = compare_zip($left,$right);
			last;
			}

		if ($uid1==0x10000050)
			{
			# Permanent File Store
			$type = "EPOC Permanent File Store";
			$same = compare_pfstore($left,$right);
			last;
			}

		if ($uid2==0x1000006d && $uid3==0x10000419)
			{
			if (    ($uid1==0x100002c3 && $checksum==0x128ca96f)	# narrow
				 || ($uid1==0x10003b0b && $checksum==0x75e21a1d))	# unicode
				{
				# SIS file
				$type = "SIS file";
				last;
				}
			}

		if ($leftbuf =~ /^Microsoft [^\x0A]+ [Dd]atabase/s)
			{
			$type = "MSVC database";
			$same = 1;	# don't know how to compare these
			last;
			}

		if ($leftbuf =~ /^\S.+ needed due to / || $leftbuf =~ /^Archive member included.*because of file/)
			{
			# MAP file - may need to ignore ds999.o before they match properly
			$type = "MAP file";
			$same = compare_mapfile($left,$right);
			last;
			}
		}

	if ($same)
		{
		identical($left, $right, $type);
		}
	else
		{
		different($left, $right, $type);
		}
}

sub compare_streams
	{
	local (*LEFT, *RIGHT) = @_;
	my $same = 1;
	my $offset = -4096;
	
	BINARY_COMPARISON: while ($same)
		{
		$leftlen = read LEFT,  $leftbuf,  4096;
		$rightlen= read RIGHT, $rightbuf, 4096;
		if ($rightlen == 0 && $leftlen == 0)
			{
			return 1;
			}
		$same= $leftbuf eq $rightbuf;
		$offset += 4096;
		}
	if ($opt_v)
		{
		my @leftbytes = unpack "C*", $leftbuf;
		my @rightbytes = unpack "C*", $rightbuf;
		foreach $_ (@leftbytes)
			{
			if ($_ != @rightbytes[0])
				{
				printf $log "Binary comparison failed at byte %d: %02x != %02x\n", $offset, $_, @rightbytes[0];
				last;
				}
			shift @rightbytes;
			$offset+=1;
			}
		}
	return 0;
	}

sub compare_texts
	{
	local (*LEFT, *RIGHT, $cleaner) = @_;
	my $same = 1;
	my $line = 0;

	TEXT_COMPARISON: while ($same)
		{
		$leftline = <LEFT>;
		$rightline= <RIGHT>;
		if ((!$leftline)&& (!$rightline))
			{
			return 1;
			}
		$leftline = &$cleaner($leftline);
		$rightline = &$cleaner($rightline);
		$same= $leftline eq $rightline;
		$line += 1;
		}
	if ($opt_v)
		{
		printf $log "Text comparison failed at line %d\n< %s\n> %s\n", $line, $leftline, $rightline;
		}
	return 0;
	}

sub drain
	{
	local (*LEFT, *RIGHT, $cleaner) = @_;
	while (<LEFT>)
		{
		next;
		}
	while (<RIGHT>)
		{
		next;
		}
	}

#
# pediff returns 0 if identical and 2 if different
#
sub compare_intelpe
	{
	local ($left, $right) = @_;
	$ret =  system "pediff $left $right >nul";
	my $same = ($ret & 0xffff) == 0;
	if (!$same && $opt_v)
		{
		system "pediff $left $right";
		}
	return $same;
	}

sub compare_e32image
	{
	local ($left, $right) = @_;
	$ret =  system "pediff -e32 $left $right >nul";
	my $same = ($ret & 0xffff) == 0;
	if (!$same && $opt_v)
		{
		system "pediff -e32 $left $right";
		}
	return $same;
	}

sub compare_dumpbin
	{
	local ($left, $right) = @_;
	
	open DUMPLEFT,  "dumpbin /symbols $left |";
	open DUMPRIGHT, "dumpbin /symbols $right |";

	my $same = compare_texts(DUMPLEFT, DUMPRIGHT, \&dumpbin_clean);

	drain(DUMPLEFT, DUMPRIGHT);
	close DUMPLEFT;
	close DUMPRIGHT;

	return $same;
	}

sub dumpbin_clean
	{
	my ($line) = @_;
	$line =~ s/^Dump of file.*$/Dump of file/;		# ignore the file names
	$line =~ s/line# [0-9A-Fa-f]{4}/line# ..../g;	# ignore source line numbers
	return $line;
	}

# Compare zip files by listing the contents and comparing
# the file names and sizes
#
sub compare_zip
	{
	local ($left, $right) = @_;
	
	open ZIPLEFT,  "unzip -l $left |";
	open ZIPRIGHT, "unzip -l $right |";
	
	my $same = compare_texts(ZIPLEFT, ZIPRIGHT, \&zipclean);
	
	drain(ZIPLEFT, ZIPRIGHT);
	close ZIPLEFT;
	close ZIPRIGHT;

	return $same;
	}

sub zipclean
	{
	my ($line) = @_;
	$line =~ s/^Archive:.*$/Archive/;					# ignore the archive names
	$line =~ s/ ..-..-..  ..:.. /  99-99-99  99:99 /;	# ignore datestamps on contained files
	return $line;
	}

# Compare ARM object & lib files by using nm to display the contents
# The nm command can mysteriously fail, hence the stuff about retrying...
#
sub compare_nm
	{
	local ($left, $right) = map { dir_fixup($_) } @_;
	
	open NMLEFT,  "nm --no-sort $left |";
	open NMRIGHT, "nm --no-sort $right |";

	my $same = compare_texts(NMLEFT, NMRIGHT, \&nmclean);

	drain(ZIPLEFT, ZIPRIGHT);
	close NMLEFT;
	my $leftstatus = $?;
	close NMRIGHT;
	my $rightstatus = $?;

	if ($leftstatus != 0 || $rightstatus != 0)
		{
		warning("nm failed ($leftstatus, $rightstatus) - retrying");

		# Don't recurse, just in case it's a systematic failure...

		open NMLEFT,  "nm --no-sort $left |";
		open NMRIGHT, "nm --no-sort $right |";

		$same = compare_texts(NMLEFT, NMRIGHT, \&nmclean);

		drain(ZIPLEFT, ZIPRIGHT);
		close NMLEFT;
		$leftstatus = $?;
		close NMRIGHT;
		$rightstatus = $?;

		if ($leftstatus != 0 || $rightstatus != 0)
			{
			warning("nm failed again ($leftstatus, $rightstatus) - reporting failure");
			return 0;
			}
		}
	return $same;
	}

sub nmclean
	{
	my ($line) = @_;
	$line =~ s/([d-z])s[0-9]+\.o/\1s999.o/;			# ignore the names of intermediate files in .LIB
	return $line;
	}

# Compare MAP files
#
sub compare_mapfile
	{
	local ($left, $right) = @_;
	
	open MAPLEFT, $left;
	open MAPRIGHT, $right;

	my $same = compare_texts(MAPLEFT, MAPRIGHT, \&map_clean);

	close MAPLEFT;
	close MAPRIGHT;

	return $same;
	}

sub map_clean
	{
	my ($line) = @_;
	$line =~ s/([d-z])s[0-9]+\.o/\1s999.o/;	   # ignore the names of intermediate files in .LIB
	$line =~ s/\s*\.stab.*//;                  # ignore lines with .stab at the start - these contain degbug info
	$line =~ s/.*\(size before relaxing\).*//; # dodgy ignore lines in between .stab lines - is there a better way of doing this?
	$line =~ s/\s+//g;                         # remove whitespace.
	return $line;
	}

# Compare EPOC Permanent File Stores
#
sub compare_pfstore
	{
	local ($left, $right) = @_;
	
	open PFSLEFT,  "pfsdump -c -v $left |";
	open PFSRIGHT, "pfsdump -c -v $right |";
	
	my $same = compare_streams(PFSLEFT, PFSRIGHT);
	
	drain(PFSLEFT, PFSRIGHT);
	close PFSLEFT;
	close PFSRIGHT;

	return $same;
	}


sub dir_fixup
	{
	my ($name) = @_;

	if ($name =~ /^\\/)
		{
		if (!$toroot)
			{
			$toroot = getcwd();
			$toroot =~ s/^[a-zA-Z]:\\(.*)$/\1/;
			$toroot =~ s/[^\\]+/../g;
			if ($toroot =~ /^$/)
				{
				$toroot=".";	# because we are starting in the root
				}
			}
		return $toroot.$name;
		}
	return $name;
	}
