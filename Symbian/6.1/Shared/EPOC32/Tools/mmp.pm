# MMP.PM
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
#


# Processes an mmp file and sets up subroutines to return the data

package Mmp;

require Exporter;
@ISA=qw(Exporter);

@EXPORT=qw(
	Mmp_SetVerbose
	Mmp_ProcessL

	Mmp_ABI
	Mmp_AifStruct
	Mmp_AllowDllData
	Mmp_ASSPExports
	Mmp_ASSPLibList
	Mmp_BitMapStruct 
	Mmp_CallDllEntryPoints
	Mmp_CompatibleABIs
	Mmp_DataLinkAddress
	Mmp_DebugLibList 
	Mmp_Def
	Mmp_DocHash
	Mmp_ExportUnfrozen
	Mmp_FirstLib
	Mmp_FixedProcess
	Mmp_HeapSize
	Mmp_LangList
	Mmp_LibList 
	Mmp_LinkAs
	Mmp_Macros
	Mmp_MmpFlag
	Mmp_PlatTxt2D
	Mmp_ProcessPriority
	Mmp_ResrcHash
	Mmp_RamTargets
	Mmp_RomTargets
	Mmp_SrcHash
	Mmp_StackSize
	Mmp_StatLibList 
	Mmp_SysIncPaths
	Mmp_SysResrcHash
	Mmp_Trg
	Mmp_TrgType
	Mmp_UidList
	Mmp_UserIncPaths
	Mmp_SrcDbg
);


use Genutl;
use Prepfile;
use Pathutl;
use Trgtype;

my %Mode;

my $ABI;
my @AifStruct;
my $AllowDllData=0;
my $ASSPABISwitch=0;
my $ASSPExports=0;
my @ASSPLibList;
my @BitMapStruct;
my $CallDllEntryPoints=0;
my @CompatibleABIs;
my $DataLinkAddress='';
my @DebugLibList;
my %Def;
$Def{Path}='';
$Def{Base}='';
$Def{Ext}='';
my %DocHash;
my $ExportUnfrozen=0;
my $FirstLib;
my $FixedProcess=0;
my %HeapSize;
my @LangList;
my @LibList;
my $LinkAs;
my @Macros;
my %MmpFlag;
my @PlatTxt2D;
my $ProcessPriority='';
my %ResrcHash;
my @RamTargets;
my @RomTargets=({}); # include default
my %SrcHash;    
my $StackSize='';
my @StatLibList;
my @SysIncPaths;
my %SysResrcHash;
my $Trg;
my %TrgType;
my @UidList;
my @UserIncPaths;
my $SrcDbg=0;


BEGIN {
	$Mode{'Verbose'}=0;
}

sub Mmp_SetVerbose () {
	$Mode{'Verbose'}=1;
}

sub Mmp_ProcessL ($$) {
	my ($EPOCPath, $MMPFILE, $Plat_ref)=@_;


	if ($Mode{Verbose}) {
		&Prepfile_SetVerbose;
	}

#	set the file-processor to upper-case all the data
	&Prepfile_SetUpperCase;

#	preprocess the project description file
	my @Mmp2D;
	eval { &Prepfile_ProcessL(\@Mmp2D, $MMPFILE, @{$$Plat_ref{MmpMacros}}); };
	die $@ if $@;

	my $NoStrictDef=0;
	my $TrgPath='';
	my $TrgType;

	my $MmpPath=&Path_Split('Path', $MMPFILE);

	my @MmpDie=();
	my @MmpWarn=();

	my (%CheckAif, %CheckASSPLib, %CheckDoc, %CheckLang, %CheckLib, %CheckMacro, %CheckResrc, %CheckSrc, %CheckStatLib, %CheckSysInc, %CheckSysResrc, %CheckUserInc);

	my ($CheckDef);

	my ($CheckRamTargets, $CheckRomTargets);

	my ($OtherPlatSwitch, $PlatTxtSwitch);

	my (%CurBitMap, $CurBitMapSrcPath);
	$CurBitMapSrcPath=$MmpPath;

	my ($CurSrcPath, $MmpMacro, $Line);
	$CurSrcPath=$MmpPath;

#	include the .MMP file as a document
	@{$DocHash{$MmpPath}}=(&Path_Split('File', $MMPFILE));
	$CheckDoc{$MMPFILE}='zero - specified by default';

# process the data structure
	my $CurFile=$MMPFILE;
	LINE: foreach $Line (@Mmp2D) {
		my $LineNum=shift @$Line;
		$_=shift @$Line;
		if ($LineNum eq '#') {
			$CurFile=$_;
			next LINE;
		}

		if ($PlatTxtSwitch) {
			if (/^END$/o) {
				$PlatTxtSwitch=0;
				next LINE;
			}
			push @PlatTxt2D, [ "$CurFile($LineNum)", $_, @$Line ];
			next LINE;
		}
		if ($OtherPlatSwitch) {
			if (/^END$/o) {
				$OtherPlatSwitch=0;
				next LINE;
			}
			next LINE;
		}
		if (%CurBitMap) {
			if (/^SOURCE$/o) {
				unless (@$Line>1) {
					push @MmpDie, "$CurFile($LineNum) : Not enough arguments for Bitmap keyword SOURCE\n";
				}
				my $ClDepth=shift @$Line;
				unless ($ClDepth=~/^C?\d\d?$/o) {
					push @MmpDie, "$CurFile($LineNum) : BITMAP color depth \"$ClDepth\" - unexpected format\n";
				}
				$ClDepth=lc $ClDepth; # bmconv can't handle upper-case 'C's
				foreach (@$Line) {
					$_=lc $_;	# bmconv generates a header with case-sensitive enums
					push @{$CurBitMap{Source}}, { # sources must be kept in order
						Src=>"$CurBitMapSrcPath$_",
						ClDepth=>$ClDepth
					};
					unless (-e "$CurBitMapSrcPath$_") {
						push @MmpWarn, "$CurFile($LineNum) : BITMAP source \"$CurBitMapSrcPath$_\" not found\n";
					}
				}
				next LINE;
			}
			if (/^END$/o) {
				$CurBitMapSrcPath=$MmpPath;
				my %BitMap=%CurBitMap;
				undef %CurBitMap;
				push @BitMapStruct, \%BitMap;
				next LINE;
			}
			if (/^SOURCEPATH$/o) {
				unless ($CurBitMapSrcPath=shift @$Line) {
					push @MmpDie, "$CurFile($LineNum) : No path specified with Bitmap keyword SOURCEPATH\n";
					next LINE;
				}
				$CurBitMapSrcPath=~s-^(.*[^\\])$-$1\\-o;   # ensure path ends with a backslash
				$CurBitMapSrcPath=&Path_MakeAbs($MMPFILE,$CurBitMapSrcPath);
				if (@$Line) {
					push @MmpWarn, "$CurFile($LineNum) : Too many arguments for Bitmap keyword SOURCEPATH\n";
				}
				next LINE;
			}
			if (/^HEADER$/o) {
				if ($CurBitMap{Hdr}) {
					push @MmpWarn, "$CurFile($LineNum) : Bitmap HEADER already specified at line $CurBitMap{Hdr}\n";
					next LINE;
				}
				$CurBitMap{Hdr}="$CurFile($LineNum)";
				if (@$Line) {
					push @MmpWarn, "$CurFile($LineNum) : Bitmap keyword HEADER takes no arguments\n";
				}
				next LINE;
			}
			if (/^TARGETPATH$/o) {
				if ($CurBitMap{TrgPath}) {
					push @MmpWarn, "$CurFile($LineNum) : Bitmap TARGETPATH already specified\n";
					next LINE;
				}
				unless ($CurBitMap{TrgPath}=shift @$Line) {
					push @MmpDie, "$CurFile($LineNum) : No path specified with Bitmap keyword TARGETPATH\n";
					next LINE;
				}
				$CurBitMap{TrgPath}=~s-^\\(.*)$-$1-o;
				$CurBitMap{TrgPath}=~s-^(.*[^\\])$-$1\\-o;   # ensure path ends with a backslash
				$CurBitMap{TrgPath}="Z\\$CurBitMap{TrgPath}";
				if (@$Line) {
					push @MmpWarn, "$CurFile($LineNum) : Too many arguments for Bitmap keyword TARGETPATH\n";
				}
				next LINE;
			}
			push @MmpWarn, "$CurFile($LineNum) : Unrecognised Bitmap Keyword \"$_\"\n";
		}
		if (/^START$/) {
			unless ($_=shift @$Line) {
				push @MmpWarn, "$CurFile($LineNum) : No Argument specified for START block\n";
				next LINE;
			}
			foreach $MmpMacro (@{$$Plat_ref{MmpMacros}}) {
				if ($_ eq $MmpMacro) {
					$PlatTxtSwitch="$CurFile($LineNum)";
					next LINE;
				}
			}
			if ($_ eq 'BITMAP') {
				unless ($CurBitMap{Trg}=shift @$Line) {
					push @MmpWarn, "$CurFile($LineNum) : No Bitmap Target specified\n";
					$CurBitMap{Trg}='NoTargetSpecified';
				}
				if (@$Line) {
					push @MmpWarn, "$CurFile($LineNum) : Too many arguments for START BITMAP clause\n";
				}
				next LINE;
			}
			$OtherPlatSwitch="$CurFile($LineNum)";
			next LINE;
		}

		if (/^AIF$/o) {
			my %Data;
			($Data{Trg}, $Data{Dir}, $Data{Resrc}, $Data{ClDepth}, @{$Data{BitMaps}})=@$Line;
			unless ($Data{Resrc}) { # bitmaps aren't essential
				push @MmpDie, "$CurFile($LineNum) : Not enough arguments for keyword AIF\n";
				next LINE;
			}
			$Data{Dir}=~s-^(.*[^\\])$-$1\\-o;   # ensure path ends with a backslash
			$Data{Dir}=&Path_MakeAbs($MMPFILE, $Data{Dir});
			my $File;
			foreach $File ($Data{Resrc}, @{$Data{BitMaps}}) {
				unless (-e "$Data{Dir}$File") {
					push @MmpWarn, "$CurFile($LineNum) : AIF source \"$Data{Dir}$File\" not found\n";
				}
			}
			if ($Data{ClDepth}) {
				unless ($Data{ClDepth}=~/^C?\d\d?$/o) {
					push @MmpDie, "$CurFile($LineNum) : AIF color depth \"$Data{ClDepth}\" - unexpected format\n";
				}
				$Data{ClDepth}=lc $Data{ClDepth}; # bmconv can't handle upper-case 'C's
			}
			if ($CheckAif{$Data{Trg}}) {
				push @MmpDie, "$CurFile($LineNum) : Duplicate Aif \"$Data{Trg}\" at line $CheckAif{$Data{Trg}}\n";
				next LINE;
			}
			$CheckAif{$Data{Trg}}="$CurFile($LineNum)";
			push @AifStruct, \%Data;
			next LINE;
		}
		if (/^ASSPABI$/o) {
			if (@$Line) {
				push @MmpWarn, "$CurFile($LineNum) : Keyword $_ takes no arguments\n";
			}
			$ASSPABISwitch=1;
			next LINE;
		}
		if (/^ASSPEXPORTS$/o) {
			if (@$Line) {
				push @MmpWarn, "$CurFile($LineNum) : Keyword $_ takes no arguments\n";
			}
			$ASSPExports=1;
			next LINE;
		}
		if (/^ASSPLIBRARY$/o) {
			if (@$Line) {
				my $Candidate;
				foreach $Candidate (@$Line) {
					if ($CheckASSPLib{$Candidate}) {
						push @MmpWarn, "$CurFile($LineNum) : Duplicate Library \"$Candidate\" at line $CheckASSPLib{$Candidate}\n";
						next; 
					}
					push @ASSPLibList, $Candidate;
					$CheckASSPLib{$Candidate}="$CurFile($LineNum)";
				}
				next LINE;
			}
			push @MmpWarn, "$CurFile($LineNum) : No Libraries specified for keyword ASSPLIBRARY\n";
			next LINE;
		}
		if (/^DEBUGLIBRARY$/o) {
			if (@$Line) {
				my $Candidate;
				foreach $Candidate (@$Line) {
					if ($CheckLib{$Candidate}) {
						push @MmpWarn, "$CurFile($LineNum) : Duplicate Library \"$Candidate\" at line $CheckLib{$Candidate}\n";
						next; 
					}
					push @DebugLibList, $Candidate;
					$CheckLib{$Candidate}="$CurFile($LineNum)";
				}
				next LINE;
			}
			push @MmpWarn, "$CurFile($LineNum) : No Libraries specified for keyword DEBUGLIBRARY\n";
			next LINE;
		}
		if (/^DEFFILE$/o)  {
			if ($CheckDef) {
				push @MmpWarn, "$CurFile($LineNum) : Attempt to redefine DEFFILE\n";
				next LINE;
			}
			$CheckDef=1;
			unless ($_=shift @$Line) {
				push @MmpWarn, "$CurFile($LineNum) : No file specified for keyword DEFFILE\n";
				next LINE;
			}
			$Def{Base}=&Path_Split('Base',$_);
			$Def{Ext}=&Path_Split('Ext',$_);
			$Def{Path}=&Path_Split('Path',$_);
			if ($Def{Path}) {
				$Def{Path}=&Path_MakeEAbs($EPOCPath,$MMPFILE,$Def{Path});
			}
			next LINE;
		}
		if (/^DOCUMENT$/o) {
			if (@$Line) {
				my $Candidate;
				foreach $Candidate (@$Line) {
					if ($CheckDoc{"$CurSrcPath$Candidate"}) {
						push @MmpWarn, "$CurFile($LineNum) : Duplicate Document \"$CurSrcPath$Candidate\" at line ", $CheckDoc{"$CurSrcPath$Candidate"}, "\n";
						next; 
					}
					unless (-e "$CurSrcPath$Candidate") {
						push @MmpWarn, "$CurFile($LineNum) : DOCUMENT \"$CurSrcPath$Candidate\" not found\n";
					}
					push @{$DocHash{$CurSrcPath}}, $Candidate;
					$CheckDoc{"$CurSrcPath$Candidate"}="$CurFile($LineNum)";
				}
				next LINE;
			}
			push @MmpWarn, "$CurFile($LineNum) : No Files specified for keyword DOCUMENT\n";
			next LINE;
		}
		if (/^EPOCALLOWDLLDATA$/o) {
			if (@$Line) {
				push @MmpWarn, "$CurFile($LineNum) : Keyword $_ takes no arguments\n";
			}
			$AllowDllData=1;
			next LINE;
		}
		if (/^EPOCCALLDLLENTRYPOINTS$/o) {
			if (@$Line) {
				push @MmpWarn, "$CurFile($LineNum) : Keyword $_ takes no arguments\n";
			}
			$CallDllEntryPoints=1;
			next LINE;
		}
		if (/^EPOCDATALINKADDRESS$/o) {
			if (@$Line) { 
				my $temp=&main::Genutl_AnyToHex(shift @$Line);
				if (defined $temp) {
					$DataLinkAddress=$temp;
					next LINE;
				}
				push @MmpDie, "$CurFile($LineNum) : Data link address doesn't fit expected number format\n";
			}
			push @MmpWarn, "$CurFile($LineNum) : No data link address specified for keyword $_\n";
			next LINE;
		}
		if (/^EPOCFIXEDPROCESS$/o) {
			if (@$Line) {
				push @MmpWarn, "$CurFile($LineNum) : Keyword $_ takes no arguments\n";
			}
			$FixedProcess=1;
			next LINE;
		}
		if (/^EPOCHEAPSIZE$/o) {
			if (@$Line) {
				my $tempMin=&main::Genutl_AnyToHex(shift @$Line);
				if (defined $tempMin) {
					if (@$Line) {
						my $tempMax=&main::Genutl_AnyToHex(shift @$Line);
						if (defined $tempMax) {
							$HeapSize{Min}=$tempMin;
							$HeapSize{Max}=$tempMax;
							next LINE;
						}
						push @MmpDie, "$CurFile($LineNum) : maximum heap size doesn't fit expected number format\n";
						next LINE;
					}
					push @MmpDie, "$CurFile($LineNum) : No maximum heap size specified for keyword $_\n";
					next LINE;
				}
				push @MmpDie, "$CurFile($LineNum) : minimum heap size doesn't fit expected number format\n";
				next LINE;
			}
			push @MmpWarn, "$CurFile($LineNum) : No minimum heap size specified for keyword $_\n";
			next LINE;
		}
		if (/^EPOCPROCESSPRIORITY$/o) {
			if ($ProcessPriority) {
				push @MmpWarn, "$CurFile($LineNum) : Attempt to redefine EPOCPROCESSPRIORITY\n";
				next LINE;
			}
			if ($ProcessPriority=shift @$Line) {
				if ($ProcessPriority=~/^(LOW|BACKGROUND|FOREGROUND|HIGH|WINDOWSERVER|FILESERVER|REALTIMESERVER|SUPERVISOR)$/o) {
					next LINE;
				}
				push @MmpDie, "$CurFile($LineNum) : ProcessPriority \"$ProcessPriority\" not supported\n";
				next LINE;
			}
			push @MmpWarn, "$CurFile($LineNum) : No Priority specified for keyword EPOCPROCESSPRIORITY\n";
			next LINE;
		}
		if (/^EPOCSTACKSIZE$/o) {
			if (@$Line) {
				my $temp=&main::Genutl_AnyToHex(shift @$Line);
				if (defined $temp) {
					$StackSize=$temp;
					next LINE;
				}
				push @MmpDie, "$CurFile($LineNum) : Stack size doesn't fit expected number format\n";
				next LINE;
			}
			push @MmpWarn, "$CurFile($LineNum) : No stack size specified for keyword STACKSIZE\n";
			next LINE;
		}
		if (/^EXPORTUNFROZEN$/o) {
			if (@$Line) {
				push @MmpWarn, "$CurFile($LineNum) : Keyword $_ takes no arguments\n";
			}
			$ExportUnfrozen=1;
			next LINE;
		}
		if (/^FIRSTLIB$/o) {
			if ($FirstLib) {
				push @MmpWarn, "$CurFile($LineNum) : Attempt to redefine FIRSTLIB\n";
				next LINE;
			}
			if ($FirstLib=shift @$Line) {
				next LINE;
			}
			push @MmpWarn, "$CurFile($LineNum) : Nothing specified for keyword FIRSTLIB\n";
			next LINE;
		}
		if (/^LANG$/o) {
			if (@$Line) {
				my $Candidate;
				foreach $Candidate (@$Line) {
					if ($CheckLang{$Candidate}) {
						push @MmpWarn, "$CurFile($LineNum) : Duplicate Language \"$Candidate\" at line $CheckLang{$Candidate}\n";
						next; 
					}
					push @LangList, $Candidate;
					$CheckLang{$Candidate}="$CurFile($LineNum)";
				}
				next LINE;
			}
			push @MmpWarn, "$CurFile($LineNum) : No Languages specified for keyword LANG\n";
			next LINE;
		}
		if (/^LIBRARY$/o) {
			if (@$Line) {
				my $Candidate;
				foreach $Candidate (@$Line) {
					if ($CheckLib{$Candidate}) {
						push @MmpWarn, "$CurFile($LineNum) : Duplicate Library \"$Candidate\" at line $CheckLib{$Candidate}\n";
						next; 
					}
					push @LibList, $Candidate;
					push @DebugLibList, $Candidate;	    # appears in both
					$CheckLib{$Candidate}="$CurFile($LineNum)";
				}
				next LINE;
			}
			push @MmpWarn, "$CurFile($LineNum) : No Libraries specified for keyword LIBRARY\n";
			next LINE;
		}
		if (/^LINKAS$/o) {
			if ($LinkAs) {
				push @MmpWarn, "$CurFile($LineNum) : Attempt to redefine LINKAS\n";
				next LINE;
			}
			if ($LinkAs=shift @$Line) {
				next LINE;
			}
			push @MmpWarn, "$CurFile($LineNum) : No name specified for keyword LINKAS\n";
			next LINE;
		}
		if (/^MACRO$/o) {
			if (@$Line) {
				my $Candidate;
				foreach $Candidate (@$Line) {
					if ($CheckMacro{$Candidate}) {
						push @MmpWarn, "$CurFile($LineNum) : Duplicate Macro \"$Candidate\" at line $CheckMacro{$Candidate}\n";
						next; 
					}
					push @Macros, $Candidate;
					$CheckMacro{$Candidate}="$CurFile($LineNum)";
				}
				next LINE;
			}
			push @MmpWarn, "$CurFile($LineNum) : No Macros specified for keyword MACRO\n";
			next LINE; 
		}
		if (/^NOSTRICTDEF$/o) {
			if ($NoStrictDef) {
				push @MmpWarn, "$CurFile($LineNum) : NOSTRICTDEF already set\n";
				next LINE;
			}
			if (@$Line) {
				push @MmpWarn, "$CurFile($LineNum) : Keyword NOSTRICTDEF takes no arguments\n";
			}
			$NoStrictDef=1;
			next LINE;
		}
		if (/^RAMTARGET$/o) {
			if ($CheckRamTargets) {
				push @MmpWarn, "$CurFile($LineNum) : RAM targets already specified at line $CheckRamTargets\n";
				next LINE;
			}
			$CheckRamTargets="$CurFile($LineNum)";
			unless (@$Line) {
				push @MmpWarn, "$CurFile($LineNum) : No targets specified for keyword RAMTARGET\n";
				next LINE;
			}
			if ($$Line[0] eq '+') {
				my %Data=();
				push @RamTargets, \%Data;	# include default
				shift @$Line;
			}
			my $Elem;
			foreach $Elem (@$Line) {
				my %Data=();
				$Data{File}=&Path_Split('File',$Elem);
				$Data{Path}=&Path_Split('Path',$Elem);
				push @RamTargets, \%Data;
			}
			next LINE;
		}
		if (/^RESOURCE$/o) {
			if (@$Line) {
				my $Candidate;
				foreach $Candidate (@$Line) {
					if ($CheckResrc{$Candidate}) {
						push @MmpDie, "$CurFile($LineNum) : Duplicate Resource $Candidate at line $CheckResrc{$Candidate}\n";
						next;
					}
					push @{$ResrcHash{$CurSrcPath}}, $Candidate;
					$CheckResrc{$Candidate}="$CurFile($LineNum)";
				}
				next LINE;
			}
			push @MmpWarn, "$CurFile($LineNum) : No Resources specified for keyword RESOURCE\n";
			next LINE; 
		}
		if (/^ROMTARGET$/o) {
			if ($CheckRomTargets) {
				push @MmpWarn, "$CurFile($LineNum) : ROM targets already specified at line $CheckRomTargets\n";
				next LINE;
			}
			$CheckRomTargets="$CurFile($LineNum)";
			unless (@$Line) {
				@RomTargets=();
				next LINE;
			}
			if ($$Line[0] eq '+') {
				shift @$Line;
			}
			else {
				@RomTargets=(); # remove default
			}
			my $Elem;
			foreach $Elem (@$Line) {
				my %Data=();
				$Data{File}=&Path_Split('File',$Elem);
				$Data{Path}=&Path_Split('Path',$Elem);
				push @RomTargets, \%Data;
			}
			next LINE;
		}
		if (/^SOURCE$/o) {
			if (@$Line) {
				my $Candidate;
				foreach $Candidate (@$Line) {
					if ($CheckSrc{$Candidate}) {
						push @MmpDie, "$CurFile($LineNum) : Duplicate Source \"$Candidate\" at line $CheckSrc{$Candidate}\n";
						next;
					}
					push @{$SrcHash{$CurSrcPath}}, $Candidate;
					$CheckSrc{$Candidate}="$CurFile($LineNum)";
				}
				next LINE;
			}
			push @MmpWarn, "$CurFile($LineNum) : No Sources specified for keyword SOURCE\n";
			next LINE; 
		}
		if (/^SOURCEPATH$/o) {
			if ($CurSrcPath=shift @$Line) {
				$CurSrcPath=~s-^(.*[^\\])$-$1\\-o;	# in case no terminating backslash
				$CurSrcPath=&Path_MakeAbs($MMPFILE,$CurSrcPath);
				if (-d &Path_Chop($CurSrcPath)) {
					next LINE;
				}
				push @MmpWarn, "$CurFile($LineNum) : SOURCEPATH \"$CurSrcPath\" not found\n";
				next LINE;
			}
			push @MmpDie, "$CurFile($LineNum) : No Source Path specified for keyword SOURCEPATH\n";
			next LINE;
		}
		if (/^STATICLIBRARY$/o) {
			if (@$Line) {
				my $Candidate;
				foreach $Candidate (@$Line) {
					if ($CheckStatLib{$Candidate}) {
						push @MmpWarn, "$CurFile($LineNum) : Duplicate Library \"$Candidate\" at line $CheckStatLib{$Candidate}\n";
						next;
					}
					push @StatLibList, $Candidate;
					$CheckStatLib{$Candidate}="$CurFile($LineNum)";
				}
				next LINE;
			}
			push @MmpWarn, "$CurFile($LineNum) : No Libraries specified for keyword STATICLIBRARY\n";
			next LINE;
		}
		if (/^STRICTDEPEND$/o) {
			if ($MmpFlag{StrictDepend}) {
				push @MmpWarn, "$CurFile($LineNum) : STRICTDEPEND already set\n";
				next LINE;
			}
			if (@$Line) {
				push @MmpWarn, "$CurFile($LineNum) : Keyword STRICTDEPEND takes no arguments\n";
			}
			$MmpFlag{StrictDepend}=1;
			next LINE;
		}
		if (/^SYSTEMINCLUDE$/o){
			if (@$Line) {
				my $Candidate;
				foreach $Candidate (@$Line) {
					$Candidate=~s-^(.*[^\\])$-$1\\-o;   # ensure path ends with a backslash
					$Candidate=&Path_MakeEAbs($EPOCPath,$MMPFILE,$Candidate);
					if ($CheckSysInc{$Candidate}) {
						push @MmpWarn, "$CurFile($LineNum) : Duplicate SYSTEMINCLUDE path $Candidate at line $CheckSysInc{$Candidate}\n";
						next; 
					}
					push @SysIncPaths,$Candidate;
					$CheckSysInc{$Candidate}="$CurFile($LineNum)";
					if (-d &Path_Chop($Candidate)) {
						next;
					}
					push @MmpWarn, "$CurFile($LineNum) : SYSTEMINCLUDE path \"$Candidate\" not found\n";
				}
				next LINE;
			}
			push @MmpWarn, "$CurFile($LineNum) : No Paths specified for keyword SYSTEMINCLUDE\n";
			next LINE;
		}
		if (/^SYSTEMRESOURCE$/o) {
			if (@$Line) {
				my $Candidate;
				foreach $Candidate (@$Line) {
					if ($CheckSysResrc{$Candidate}) {
						push @MmpDie, "$CurFile($LineNum) : Duplicate Resource \"$Candidate\" at line $CheckSysResrc{$Candidate}\n";
						next; 
					}
					push @{$SysResrcHash{$CurSrcPath}}, $Candidate;
					$CheckSysResrc{$Candidate}="$CurFile($LineNum)";
				}
				next LINE;
			}
			push @MmpWarn, "$CurFile($LineNum) : No Resources specified for keyword SYSTEMRESOURCE\n";
			next LINE; 
		}
		if (/^TARGET$/o) {
			if ($Trg) {
				push @MmpWarn, "$CurFile($LineNum) : Attempt to redefine TARGET\n";
				next LINE;
			}
			if ($Trg=shift @$Line) {
				next LINE;
			}
			push @MmpWarn, "$CurFile($LineNum) : No Target specified for keyword TARGET\n";
			next LINE;
		}
		if (/^TARGETPATH$/o) {
			if ($TrgPath) {
				push @MmpWarn, "$CurFile($LineNum) : Attempt to redefine TARGETPATH\n";
				next LINE;
			}
			unless ($TrgPath=shift @$Line) {
				push @MmpWarn, "$CurFile($LineNum) : No Path specified for keyword TARGETPATH\n";
				next LINE;
			}
			$TrgPath=~s-^\\(.*)$-$1-o;
			$TrgPath=~s-^(.*[^\\])$-$1\\-o;
			$TrgPath="Z\\$TrgPath";
			if (@$Line) {
				push @MmpWarn, "$CurFile($LineNum) : Too many arguments for keyword TARGETPATH\n";
			}
			next LINE;
		}
		if (/^TARGETTYPE$/o) {
			if ($TrgType) {
				push @MmpWarn, "$CurFile($LineNum) : Attempt to redefine TARGETTYPE\n";
				next LINE;
			}
			unless ($TrgType=shift @$Line) {
				push @MmpWarn, "$CurFile($LineNum) : No Type specified for keyword TARGETTYPE\n";
				next LINE;
			}
			eval { &Trg_GetL($TrgType, \%TrgType); };
			if ($@) {
				push @MmpDie, "$CurFile($LineNum) : $@";
			}
			next LINE;
		}
		if (/^UID$/o) {
			if (@$Line) {
				foreach (@$Line) {
					if ($#UidList>=1) {
						push @MmpWarn, "$CurFile($LineNum) : Can't specify more than 2 Uids\n";
						next LINE;
					}
					$_=&Genutl_AnyToHex($_);
					if (defined $_) {
						push @UidList, $_;
						next;
					}
					push @MmpDie, "$CurFile($LineNum) : Uid doesn't fit expected number format\n";
					next LINE;
				}
				next LINE;
			}
			push @MmpWarn, "$CurFile($LineNum) : No Uids specified for keyword UID\n";
			next LINE;
		}
		if (/^USERINCLUDE$/o) {
			if (@$Line) {
				my $Candidate;
				foreach $Candidate (@$Line) {
					$Candidate=~s-^(.*[^\\])$-$1\\-o;   # ensure path ends with a backslash
					$Candidate=&Path_MakeEAbs($EPOCPath,$MMPFILE,$Candidate);
					if ($CheckUserInc{$Candidate}) {
						push @MmpWarn, "$CurFile($LineNum) : Duplicate USERINCLUDE path \"$Candidate\" at line $CheckUserInc{$Candidate}\n";
						next; 
					}
					push @UserIncPaths,$Candidate;
					$CheckUserInc{$Candidate}="$CurFile($LineNum)";
					if (-d &Path_Chop($Candidate)) {
						next;
					}
					push @MmpWarn, "$CurFile($LineNum) : USERINCLUDE path \"$Candidate\" not found\n";
				}
				next LINE;
			}
			push @MmpWarn, "$CurFile($LineNum) : No Paths specified for keyword USERINCLUDE\n";
			next LINE;
		}
		if (/^SRCDBG$/o) {
			if (@$Line) {
				push @MmpWarn, "$CurFile($LineNum) : Keyword $_ takes no arguments\n";
			}
			$SrcDbg=1;
			next LINE;
		}
		push @MmpWarn, "$CurFile($LineNum) : Unrecognised Keyword \"$_\"\n";
	}

	undef $Line;
	undef $MmpMacro;


	# test the mmp contents
	#----------------------
	if ($PlatTxtSwitch || $OtherPlatSwitch)	{
		push @MmpDie, $PlatTxtSwitch ? $PlatTxtSwitch : $OtherPlatSwitch, ": Unterminated START ... END block\n";
	}
	undef $PlatTxtSwitch;
	undef $OtherPlatSwitch;

	# Check the consistency of the mmp file contents
	unless ($Trg) {
		push @MmpDie, "ERROR: No Target specified\n";
	}
	unless ($TrgType) {
		push @MmpDie, "ERROR: No TargetType specified\n";
	}
	unless (%SrcHash) {
		push @MmpDie, "ERROR: No Sources specified\n";
	}
	if ($TrgType{NeedUID3} && $#UidList<1) {
		push @MmpWarn, "WARNING: No Uid3 specified in \"$MMPFILE\" for TargetType \"$TrgType\"\n";
	}

#	ensure all bitmaps have targetpaths and check for duplicate bitmaps
	my %BitMapCheck;
	my $BitMapRef;
	foreach $BitMapRef (@BitMapStruct) {
		unless ($$BitMapRef{TrgPath}) {
			$$BitMapRef{TrgPath}=$TrgPath;
		}
		if ($BitMapCheck{"$$BitMapRef{TrgPath}$$BitMapRef{Trg}"}) {
			push @MmpDie, "ERROR: Duplicate bitmap target \"$$BitMapRef{TrgPath}$$BitMapRef{Trg}\"\n";
			next;
		}
		$BitMapCheck{"$$BitMapRef{TrgPath}$$BitMapRef{Trg}"}=1;
	}

	if (@MmpDie || @MmpWarn) {
		warn "\nMMPFILE \"$MMPFILE\"\n";
		if (@MmpWarn) {
			warn
				"WARNING(S)\n",
				@MmpWarn,
				"\n"
			;
		}
		if (@MmpDie) {
			die
				"FATAL ERROR(S)\n",
				@MmpDie
			;
		}
	}


#	PUT IN SOME DEFAULTS

	# check for languages
	@LangList=('SC') unless @LangList;

#	COMPLETE THE UID LIST

	while ($#UidList<1) {
		push @UidList, '0x00000000';
	}

	# check the second UID, or set it
	if ($TrgType{UID2}) {
		if ($UidList[0]=~/^0x00000000$/o) {
			# put in second uid for known targetypes without them
			$UidList[0]=$TrgType{UID2};
		}
		elsif ($UidList[0] ne $TrgType{UID2}) {
			# text comparison is OK here because UIDs have both been through AnyToHex function
			warn(
				"WARNING: Second Uid is $UidList[0], but\n",
				" expected value for Target Type $TrgType is $TrgType{UID2}\n"
			);
		}
	}

#	Put in the first UID in the list
	if ($TrgType{Basic}=~/^DLL$/o) {
		unshift @UidList, '0x10000079';
	}
	elsif ($TrgType{Basic}=~/^(EXE|EXEDLL)$/o) {
		unshift @UidList, '0x1000007a';
	}
	else {
		unshift @UidList, '0x00000000';
	}

#	SORT OUT TARGET TYPE DATA STRUCTURE

	# set the target path
	if ($TrgPath) {
		$TrgType{Path}=$TrgPath;
	}

#	put in the $Linkas default
	$LinkAs=$Trg unless $LinkAs;

#	Reconcile any EXEDLL targettypes - must be done after first UIDs put in the list
#	and after the $LinkAs keyword has been defined/defaulted
	if ($TrgType{Basic} eq 'EXEDLL') {
		if ($$Plat_ref{OS} eq 'EPOC32') {
			$TrgType{Basic}='EXE';
			$Trg=&Path_Split('Base',$Trg).'.EXE';
			$LinkAs=&Path_Split('Base',$LinkAs).'.EXE';
		}
		else {
			$TrgType{Basic}='DLL';
			if (&Path_Split('Ext',$Trg)=~/^(.EXE|)$/o) {
				$Trg=&Path_Split('Base',$Trg).'.DLL';
			}
			if (&Path_Split('Ext',$LinkAs)=~/^(.EXE|)$/o) {
				$LinkAs=&Path_Split('Base',$LinkAs).'.DLL';
			}
		}
	}
#	Get the EPOC entrypoint static library - must be done after EXEDLL basic types reconciled
	unless ($FirstLib) {
		unless ($TrgType{FirstLib}) {
			$FirstLib="E$TrgType{Basic}.LIB";
		}
		else {
			$FirstLib=$TrgType{FirstLib};
		}
	}


#	 WORK OUT THE ASSP IMPLICATIONS

#	Nullify ASSP-specific API things for WINS/WINC since the API should always be
#	the same for WINC as for WINS,
	unless ($$Plat_ref{OS} eq 'EPOC32') {
		$ASSPABISwitch=0;
		$ASSPExports=0;
		unshift @LibList, @ASSPLibList;
		unshift @DebugLibList, @ASSPLibList;	# keep DebugLibList in sync with LibList
		@ASSPLibList=();
	}
	else {
#		Force ASSPABISwitch for known kernel components or if ASSPEXPORTS or ASSPLIBRARY specified in .MMP file
		if ($TrgType{Kernel} or $ASSPExports or @ASSPLibList) {
			$ASSPABISwitch=1;
		}
	}

#	Switch the ABI if necessary
	unless ($ASSPABISwitch) {
#		apply the standard ABI
		$ABI=$$Plat_ref{ABI};
		@CompatibleABIs=@{$$Plat_ref{CompatibleABIs}};
	}
	else {
#		kernel-specific stuff
#		check that the platform is not generic
		if ($$Plat_ref{Generic}) {
			die "ERROR: Can't apply ASSPABI, ASSPEXPORTS or ASSPLIBRARY for generic platform \"$$Plat_ref{Name}\n";
		}

#		apply the ASSP-specific ABI
		$ABI=$$Plat_ref{ASSPABI};
#		nullify compatible ABIs - any kernel-specific stuff will always be built and link in the same ABI
		@CompatibleABIs=();
	}


#	COMPLETE THE .DEF FILE STRUCTURE

#	warn about .def files specified for targettypes with exports already defined
	if ($CheckDef) {
		if (@{$TrgType{Exports}{$$Plat_ref{DefFile}}}) {
			warn "WARNING: Specifying DEFFILE will override default exports for targettype $TrgType\n";
		}
	}

	# apply the default .DEF filename, and
	# check as far as possible that the project is frozen
	if ($TrgType{NeedDeffile} or $CheckDef) {
		unless ($Def{Base}) {
			$Def{Base}=&Path_Split('Base',$LinkAs);
		}
		unless ($Def{Ext}) {
			$Def{Ext}='.DEF';
		}
		unless ($Def{Path}) {
			unless ($ASSPExports) {
				$Def{Path}=&Path_Strip(&Path_Split('Path',$MMPFILE)."..\\B$$Plat_ref{DefFile}\\");
			}
			else {
				$Def{Path}=&Path_Strip(&Path_Split('Path',$MMPFILE)."..\\B$$Plat_ref{ASSP}\\");
			}
		}
#		now that we've dumped narrow, treat the 'U' basename suffix as part of the frozen
#		.DEF file basename.  Once we've dumped the suffix we won't have to store the extension
#		separately either
		unless ($NoStrictDef) {
			$Def{Base}.='U';
		}

#		check deffile exists
		unless (-e "$Def{Path}$Def{Base}$Def{Ext}") {
			warn "WARNING: Frozen .DEF file $Def{Path}$Def{Base}$Def{Ext} not found - project not frozen\n";
		}
	}
}

sub Mmp_ABI () {
	$ABI;
}
sub Mmp_AifStruct () {
	\@AifStruct;
}
sub Mmp_AllowDllData () {
	$AllowDllData;
}
sub Mmp_ASSPExports () {
	$ASSPExports;
}
sub Mmp_ASSPLibList () {
	@ASSPLibList;
}
sub Mmp_BitMapStruct () {
	\@BitMapStruct;
}
sub Mmp_CallDllEntryPoints () {
	$CallDllEntryPoints;
}
sub Mmp_CompatibleABIs () {
	@CompatibleABIs;
}
sub Mmp_DataLinkAddress () {
	$DataLinkAddress;
}
sub Mmp_DebugLibList () {
	\@DebugLibList;
}
sub Mmp_Def () {
	\%Def;
}
sub Mmp_DocHash () {
	\%DocHash;
}
sub Mmp_ExportUnfrozen () {
	$ExportUnfrozen;
}
sub Mmp_FirstLib () {
	$FirstLib;
}
sub Mmp_FixedProcess () {
	$FixedProcess;
}
sub Mmp_HeapSize () {
	\%HeapSize;
}
sub Mmp_LangList () {
	@LangList;
}
sub Mmp_LibList () {
	\@LibList;
}
sub Mmp_LinkAs () {
	$LinkAs;
}
sub Mmp_Macros () {
	@Macros;
}
sub Mmp_MmpFlag () {
	\%MmpFlag;
}
sub	Mmp_PlatTxt2D () {
	@PlatTxt2D;
}
sub Mmp_ProcessPriority () {
	$ProcessPriority;
}
sub Mmp_RamTargets () {
	@RamTargets;
}
sub Mmp_ResrcHash () {
	\%ResrcHash;
}
sub Mmp_RomTargets () {
	@RomTargets;
}
sub Mmp_SrcHash () {
	\%SrcHash;
}
sub Mmp_StackSize () {
	$StackSize;
}
sub Mmp_StatLibList () {
	@StatLibList;
}
sub Mmp_SysIncPaths () {
	@SysIncPaths;
}
sub Mmp_SysResrcHash () {
	\%SysResrcHash;
}
sub Mmp_Trg () {
	$Trg;
}
sub Mmp_TrgType () {
	\%TrgType;
}
sub Mmp_UidList () {
	@UidList;
}
sub	Mmp_UserIncPaths () {
	@UserIncPaths;
}
sub Mmp_SrcDbg () {
	$SrcDbg;
}

1;
