# WINUTL.PM
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
#


# this package does various ancillary things for windows modules

package Winutl;

my $BaseAddress='';
my @Win32LibList=();
my $Win32Resrc='';

require Exporter;
@ISA=qw(Exporter);
@EXPORT=qw(
	Winutl_Help_Mmp

	Winutl_DoMmp

	Winutl_BaseAddress
	Winutl_Win32LibList
	Winutl_Win32Resrc

);


sub Winutl_Help_Mmp {
# provide the help text for START <windows platforms> END blocks

	print
		"BASEADDRESS    [base address for dll loading]\n",
		"WIN32_LIBRARY  [win32 libraries]\n",
		"WIN32_RESOURCE  [win32 resource]\n"
	;
}

sub Winutl_DoMmp (@) { # takes platform text
	my @PlatTxt=@_;


#	check that we're using VC5 SP3
	open PIPE, "LINK.EXE |" or die "ERROR: Can't invoke LINK.EXE\n";
	my $DoneCheck=0;
	while (<PIPE>) {
		unless ($DoneCheck) {
			if (/^.+\s+Version\s+(\d)\.(\d{2})\.(\d{4})\s*$/o) {
				if (($1<6) or ($1==6 and $2<0) or ($1==6 and $2==0 and $3<8447)) {
					warn "WARNING: Should install MSVC6 Service Pack 3\n";
				}
				$DoneCheck=1;
			}
		}
	}
	close PIPE;
	if (!$DoneCheck) {
		# Couldn't find version information? Might not have link.exe at all
		die "ERROR: failed to find version information for LINK.EXE\n";
	}


# process the START <windows platforms> END blocks

	my $BaseTrg=&main::BaseTrg;
	my $BasicTrgType=&main::BasicTrgType;
	my $MakeFilePath=&main::MakeFilePath;
	my $MMPFILE=&main::MmpFile;
	my @UidList=&main::UidList;

	# set up START WINS ... END block module variables
	my @MmpWarn=();
	my $Line;
	LINE: foreach $Line (@PlatTxt) {
		my $LineInfo=shift @$Line;
		$_=shift @$Line;
		if (/^BASEADDRESS$/o) {
			if (@$Line) {
				$BaseAddress=shift @$Line;
				$BaseAddress=~s/X/x/o;
				next LINE;
			}
			push @MmpWarn, "$LineInfo : No base address specified for keyword BASEADDRESS\n";
			next LINE;
		}
		if (/^WIN32_LIBRARY$/o) {
			if (push @Win32LibList, @$Line) {
				next LINE;
			}
			push @MmpWarn, "$LineInfo : No libraries specified for keyword WIN32_LIBRARY\n";
			next LINE;
		}
		if (/^WIN32_RESOURCE$/o) {
			if (@$Line) {
				$Win32Resrc=shift @$Line;
				$Win32Resrc=&main::Path_MakeAbs($MMPFILE, $Win32Resrc);
				next LINE;
			}
			push @MmpWarn, "$LineInfo : No resource specified for keyword WIN32RESOURCE\n";
			next LINE;
		}
		push @MmpWarn, "$LineInfo : Unrecognised Keyword \"$_\"\n";
	}

	undef $Line;
	if (@MmpWarn) {
		warn
			"\nMMPFILE \"",$MMPFILE,"\"\n",
			"START .. END BLOCK WARNINGS(S)\n",
			@MmpWarn,
			"\n"
		;
	}
	undef @MmpWarn;

	if ($BasicTrgType=~/^(EXE|DLL)$/o) {
		# create the UID source file
		my $UidText=join(
			"\n",
			'// Makmake-generated uid source file',
			'#include <E32STD.H>',
			'#pragma data_seg(".E32_UID")',
			'__WINS_UID('
		);
		foreach (@UidList) {
			$UidText.="$_,";
		}
		chop $UidText;
		$UidText.=")\n";
		$UidText.="#pragma data_seg()\n";
# tools hack
		unless (&main::Plat eq 'TOOLS') {
			&main::AddSrc("$MakeFilePath$BaseTrg.UID.CPP", $UidText);
		};
# tools hack end
	}


	# if Win32 Libraries required - set the Windows standard include paths
# tools hack in line below
	if (@Win32LibList  || $Win32Resrc || &main::Plat eq 'TOOLS') {	# show where to find win32 libraries
		# include env variable takes everything between ';', including spaces and '"', as part of path
		my @StdIncPaths=split ';', uc $ENV{INCLUDE};
		foreach (@StdIncPaths) {
			s-/-\\-go;	# for those working with UNIX shells
		}
		&main::SetStdIncPaths(@StdIncPaths);
		&main::AddPlatMacros('WIN32','_WINDOWS');
	}
}

sub Winutl_BaseAddress () {
	$BaseAddress;
}

sub Winutl_Win32LibList () {
	@Win32LibList;
}

sub Winutl_Win32Resrc () {
	$Win32Resrc;
}

1;

