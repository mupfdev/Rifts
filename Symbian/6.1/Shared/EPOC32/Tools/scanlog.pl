# summarise an automated build log

my $line;
my $phase;
my $command;
my $starttime;
my $duration;
my $errorcount;
my $component;
my %errors;
my %missing;
my %not_built;
my $totalduration = 0;
my $totalerrors = 0;
my $warningcount;
my %warnings;
my $totalwarnings = 0;
my %waivers;


printf "%-39s\t%-8s\t%-7s\t%-8s\n", 'Command', 'Time', 'Errors', 'Warnings';
while ($line=<>)
	{
	if ($line =~ /^\s*waiver\s+(\w+)\s+(\d+)/)
		{
		$waivers{lc($1)} = $2;
		next;
		}

	# ===-------------------------------------------------
	# === baseline_bldfiles   
	# ===-------------------------------------------------
	# === bldfiles started Sat Jul 24 01:38:03 1999.

	if ($line =~ /^===------/)
		{
		$line = <>;
		$line =~ /=== (.*)$/;
		$command = $1;
		<>;
		$line = <>;
		$line =~ /^=== (\S+) started ... ... .. (..):(..):(..)/;
		$phase = $1;
		$starttime = ($2*60 + $3)*60 + $4;
		next;
		}

	# === bldfiles finished Sat Jul 24 01:38:56 1999.

	if ($line =~ /^=== $phase finished ... ... .. (..):(..):(..)/)
		{
		$duration = ($1*60 + $2)*60 + $3 - $starttime;
		if ($duration < 0)
			{
			$duration += 24*60*60;
			}
		my ($sec,$min,$hour) = gmtime($duration);

		printf "%-39s\t%02d:%02d:%02d\t%6d\t%6d\n", $command, $hour, $min, $sec, $errorcount, $warningcount;
		$totalduration += $duration;
		$totalerrors += $errorcount;
		$errorcount = 0;
		$totalwarnings += $warningcount;
		$warningcount = 0;
		next;
		}

	# === resource == gdtran 036

	if ($line =~ /=== $phase == (\S+)/)
		{
		$component = $1;
		next;
		}

	# BLDMAKE ERROR: Can't find "\INTERNET\GROUP\BLD.INF"

	if ($line =~ /BLDMAKE ERROR:/)
		{
		$errorcount += 1;
		$errors{$component} += 1;
		next;
		}

	# "\WAPENG\GROUP\BLD.INF" FATAL ERROR(S):

	if ($line =~ /FATAL ERROR\(S\):/)
		{
		$errorcount += 1;
		$errors{$component} += 1;
		next;
		}

	# NMAKE : fatal error U1073: don't know how to make '"\EPOC32\INCLUDE\COMMS.MBG"'

	if ($line =~ /fatal error U1073: .* make '(.*)'/)
		{
		$errorcount += 1;
		$errors{$component} += 1;
		$missing{$1} += 1;
		next;
		}

	# NMAKE : fatal error U1077: 'C:\apps\DevStudio\VC\BIN\NMAKE.EXE' : return code '0x2'

	if ($line =~ /fatal error U1077/)
		{
		$errorcount += 1;
		$errors{$component} += 1;
		next;
		}

	# NMAKE : warning U4010: 'FINALCOPYFXCM' : build failed; /K specified, continuing ...

	if ($line =~ /warning U4010/)
		{
		$errorcount += 1;
		$errors{$component} += 1;
		next;
		}

	# BLDMAKE WARNING: read-only ABLD.BAT will be overwritten

	if ($line =~ /^BLDMAKE WARNING:/)
		{
		$warningcount += 1;
		$warnings{$component} += 1;
		next;
		}

	# WARNING: Can't find following headers in User or System Include Paths

	if ($line =~ /^WARNING: Can't find/)
		{
		$warningcount += 1;
		$warnings{$component} += 1;
		next;
		}

	# WARNING(S)

	if ($line =~ /^WARNING\(S\)/)
		{
		$warningcount += 1;
		$warnings{$component} += 1;
		next;
		}

	# WARNING: Frozen .DEF file \CSTUBSHELL\BMARM\STUBRUNU.DEF not found - project not frozen

	if ($line =~ /^WARNING: Frozen/)
		{
		$warningcount += 1;
		$warnings{$component} += 1;
		next;
		}

	# WARNING: Not attempting to create any import libraries.


	if ($line =~ /^WARNING: Not .* import/)
		{
		$warningcount += 1;
		$warnings{$component} += 1;
		next;
		}

	# \BIOMSG\BITSINC\BioTestUtils.inl(4) : warning C4100: 'iOperation' : unreferenced formal parameter

	if ($line =~ /\(\d+\) : warning C/)
		{
		$warningcount += 1;
		$warnings{$component} += 1;
		next;
		}

	# LINK : warning LNK4005: no objects used from library \EPOC32\RELEASE\WINS\UDEB\ESTOR.LIB

	if ($line =~ /LINK : warning/)
		{
		$warningcount += 1;
		$warnings{$component} += 1;
		next;
		}

	# ..\\..\\BAFL\\SRC\\Bacline.cpp:68: warning: value computed is not used

	if ($line =~ /:\d+: warning:/)
		{
		$warningcount += 1;
		$warnings{$component} += 1;
		next;
		}

	# MAKEDEF WARNING: 1 export(s) not yet Frozen:

	if ($line =~ /^MAKEDEF WARNING:/)
		{
		$warningcount += 1;
		$warnings{$component} += 1;
		next;
		}

	# Comment from PETRAN which is actually a warning rather than an error
	# ERROR: bad relocation:  [00004f60] = 00000f68

	if ($line =~ /ERROR: bad relocation:/)
		{
		$warningcount += 1;
		$warnings{$component} += 1;
		next;
		}

	# 1 warning

	if ($line =~ /^(\d+) warning/)
		{
		$warningcount += $1;
		$warnings{$component} += $1;
		next;
		}

	# MISSING: \EPOC32\RELEASE\WINS\UDEB\OPLR.DLL

	if ($line =~ /^MISSING: (\S+)/)
		{
		$not_built{$1} = $component;
		next;
		}


	
	# BLD.INF WARNING(S) scanlog.pl should detect and report bld.inf warnings
	# \FORM\GROUP\BLD.INF(28) : Exported source file \form\group\tagma.rtf not found

	if ($line =~ /WARNING\(S\):/)
		{
		$warningcount += 1;
		$warnings{$component} += 1;
		next;
		}


	}

print "\n";
my ($sec,$min,$hour) = gmtime($totalduration);

printf "%-39s\t%02d:%02d:%02d\t%6d\t%6d\n\n", "Total", $hour, $min, $sec, $totalerrors, $totalwarnings;

if ($totalerrors > 0)
	{
	print "Fatal Errors by Component\n";
	$errorcount = 0;
	foreach $component (sort keys %errors)
		{
		printf "%-16s\t%6d\n", $component, $errors{$component};
		$errorcount += $errors{$component};
		}

	print "\nDon't know how to make...\n";
	foreach $file (sort keys %missing)
		{
		printf "%d\t%s\n", $missing{$file}, $file;
		}

	print "\nThings not built...\n";
	foreach $file (sort keys %not_built)
		{
		print "MISSING: $file ($not_built{$file})\n";
		}
	print "\n\n";
	}

if ($totalwarnings > 0)
	{
	my $adjusted;
	my $waiver;
	print "Warnings by Component\t  Total\tWaivers\t   Net\n";
	$warningcount = 0;
	foreach $component (sort keys %warnings)
		{
		$waiver=0;
		$adjusted = $warnings{$component};
		if (exists($waivers{$component}))
			{
			$waiver = $waivers{$component};
			$adjusted -= $waiver;
			}
		printf "%-16s\t%6d\t%6d\t%6d\n", $component, $warnings{$component},$waiver,$adjusted;
		$warningcount += $warnings{$component};
		}
	}
