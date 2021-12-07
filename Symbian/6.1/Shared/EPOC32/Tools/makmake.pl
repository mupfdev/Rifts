# MAKMAKE.PL
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
#


# all variables called *Path* are set up to end with a backslash
# all variables called *Path or *File are stored as absolute (file)paths within makmake
# all variables called UpPath* are stored as relative paths within makmake

my $PerlLibPath;

BEGIN {
# check user has a version of perl that will cope and use makmake as specified by the system path
	require 5.003_07;
	foreach (split ';', $ENV{Path}) {
		s-/-\\-go;	# for those working with UNIX shells
		s-^$-.-o;	# convert empty string to .
		s-^(.*[^\\])$-$1\\-o;   # ensure path ends with a backslash
		if (-e $_.'MAKMAKE.PL') {
			$PerlLibPath=uc $_;
			last;
		}
	}
}


use Getopt::Long;

use lib $PerlLibPath;
use E32env;
use E32Plat;
use Genutl;
use Modload;
use Pathutl;
use Trgtype;


# THE MAIN PROGRAM SECTION
##########################

{
	Load_SetModulePath($PerlLibPath);
	Plat_Init($PerlLibPath);
}

my %BldMacros;
my $MAKEFILE;
my $MMPFILE;
my %Options;
my %Plat;

{
	# process the command line
	unless (GetOptions(\%Options, 'd', 'mmp', 'plat=s', 'v')) {
		exit 1;
	}

	$Options{makemakefile}='1' unless ($Options{mmp} || $Options{plat});

	if ($Options{mmp} or $Options{plat}) {
		eval { &Load_ModuleL('MAKHELP'); };
		die $@ if $@;
	}

	if ($Options{mmp}) {
		&Help_Mmp;
		exit;
	}

	if ($Options{plat}) {
		eval { &Plat_GetL($Options{plat},\%Plat,\%BldMacros); };
		die $@ if $@;
		eval { &Load_ModuleL($Plat{MakeMod}); };
		die $@ if $@;
		&Help_Plat($Plat{Real},$Plat{CPU},\@{$Plat{MmpMacros}},\@{$Plat{Macros}});
		exit;
	}

#	show help & exit if necessary
	if (@ARGV!=2) {
		&Usage();
	}

	if ($Options{v}) {
		print "perl -S makmake.pl @ARGV\n";
		&Load_SetVerbose;
		&Path_SetVerbose;
		&Plat_SetVerbose;
	}

	# set up platform information
	my $Plat=uc pop @ARGV;
	eval { &Plat_GetL($Plat,\%Plat,\%BldMacros); };
	die $@ if $@;

	$MMPFILE=uc pop @ARGV;
	die "ERROR: Can't specify MMP file on a different drive\n" if $MMPFILE=~/^\w:\\/o;
	if ($MMPFILE!~/.MMP$/o) {
		$MMPFILE.='.MMP';
	}
	$MMPFILE=&Path_AbsToWork($MMPFILE);

	# MMP FILE PROCESSING - filter the mmp file content through the GCC preprecessor
	#-------------------------------------------------------------------------------
	eval { &Load_ModuleL('Mmp'); };
	die $@ if $@;
	if ($Options{v}) {
		&Mmp_SetVerbose;
	}
	eval { &Mmp_ProcessL($E32env::Data{EPOCPath}, $MMPFILE, \%Plat); };
	die $@ if $@;
}

my $ABI=&Mmp_ABI;
my @AifStruct=@{&Mmp_AifStruct};
my $AllowDllData=&Mmp_AllowDllData;
my $ASSPExports=&Mmp_ASSPExports;
my @ASSPLibList=&Mmp_ASSPLibList;
my @BitMapStruct=@{&Mmp_BitMapStruct};
my $CallDllEntryPoints=&Mmp_CallDllEntryPoints;
my @CompatibleABIs=&Mmp_CompatibleABIs;
my $DataLinkAddress=&Mmp_DataLinkAddress;
my @DebugLibList=@{&Mmp_DebugLibList};
my %Def=%{&Mmp_Def};
my %DocHash=%{&Mmp_DocHash};
my $ExportUnfrozen=&Mmp_ExportUnfrozen;
my $FirstLib=&Mmp_FirstLib;
my $FixedProcess=&Mmp_FixedProcess;
my %HeapSize=%{&Mmp_HeapSize};
my @LangList=&Mmp_LangList;
my @LibList=@{&Mmp_LibList};
my $LinkAs=&Mmp_LinkAs;
my %MmpFlag=%{&Mmp_MmpFlag};
my @PlatTxt2D=&Mmp_PlatTxt2D;
my $ProcessPriority=&Mmp_ProcessPriority;
my @RamTargets=&Mmp_RamTargets;
my %ResrcHash=%{&Mmp_ResrcHash};
my @RomTargets=&Mmp_RomTargets;
my %SrcHash=%{&Mmp_SrcHash};
my $StackSize=&Mmp_StackSize;
my @StatLibList=&Mmp_StatLibList;    
my @SysIncPaths=&Mmp_SysIncPaths;
my %SysResrcHash=%{&Mmp_SysResrcHash};
my $Trg=&Mmp_Trg;
my %TrgType=%{&Mmp_TrgType};
my @UidList=&Mmp_UidList;
my @UserIncPaths=&Mmp_UserIncPaths;
my $SrcDbg=&Mmp_SrcDbg;

{
#	finish defining any macros

	if ($Plat{CPU} eq 'MARM') {
#		apply the ABI source define - note that it is difficult to define a corresponding
#		.MMP define since we can't be sure what the ABI is until we've processed the .MMP file,
#		though we could apply it for generic MARM builds only
		push @{$Plat{Macros}}, "__MARM_${ABI}__";
	}

	if ($TrgType{Basic}=~/^(DLL|EXE)$/o) { # this macro may soon be removed
		push @{$Plat{Macros}},'__'.$TrgType{Basic}.'__';
	}

#	add the macros defined in the .mmp file
	push @{$Plat{Macros}}, &Mmp_Macros;
}

# set up a hash containing the start paths for various things
my %Path;
{

#	set up ASSP link path - this is the path where the target looks for ASSP-specific import libraries
	$Path{ASSPLink}="$E32env::Data{LinkPath}$Plat{ASSP}\\";

#	set up build path
	$Path{Bld}=join('', &Path_Chop($E32env::Data{BldPath}), &Path_Split('Path',$MMPFILE), &Path_Split('Base',$MMPFILE), "\\$Plat{Real}\\");

#	set up lib path - this is the path where the target puts it's import library
	$Path{Lib}="$E32env::Data{LinkPath}";
	unless ($ASSPExports) {
		$Path{Lib}.="$ABI\\";
	}
	else {
		$Path{Lib}.="$Plat{ASSP}\\";
	}

#	set up link path - this is the place where the target looks for ordinary libraries
	$Path{Link}="$E32env::Data{LinkPath}$ABI\\";

#	set up stat link path - this is where the target looks for static libraries
	$Path{StatLink}="$E32env::Data{LinkPath}";
	unless ($Plat{OS} eq 'WINS') {	# WINC and WINS versions of EEXE are different
		$Path{StatLink}.="$ABI\\"; # ARM static libraries are currently always ASSP-independent
	}
	else {
		$Path{StatLink}.="$Plat{ASSP}\\"; # WINC static libraries are currently always ASSP-specific
	}

#	set up release path
	unless ($TrgType{Basic} eq 'LIB') {
		$Path{Rel}="$E32env::Data{RelPath}$Plat{Real}\\";
	}
	else {
		$Path{Rel}=$Path{StatLink}; # static libraries can't #define the __SINGLE__ macro
	}
}

{
	# set up the makefile filepath - need to do this before loading the platform module
	# because UID source file will be added and set up in the makefile path under WINS
	if ($Options{d}) {
		$MAKEFILE=join ('', $Path{Bld}, &Path_Split('Base',$MMPFILE), $Plat{Ext});
	}
	else {
		$MAKEFILE=join "", &Path_WorkPath, &Path_Split('Base',$MMPFILE), $Plat{Ext};
	}
}

{

#	load the platform module
	eval { &Load_ModuleL($Plat{MakeMod}); };
	die $@ if $@;

	unless (defined &PMHelp_Mmp) {
#		check this function is defined - all modules must have it - if not perhaps the
#		platform module has not loaded is compiler module successfully via "use"
		die "ERROR: Module \"$Plat{MakeMod}\" not loaded successfully\n";
	}
}

{
	# allow the platform to bow out if it can't support some .MMP file specifications
	if (defined &PMCheckPlatformL) {
		eval { &PMCheckPlatformL(); };
		die $@ if $@;
	}
}

my @StdIncPaths=();

{
	# get the platform module to do it's mmpfile processing - WINS modules may set up an extra source file
	# for UIDs here depending upon the targettype
	&PMPlatProcessMmp(@PlatTxt2D) if defined &PMPlatProcessMmp;
}

{
	# if verbose mode set, output some info
	#--------------------------------------
	if ($Options{v}) {
		print  
			"Target: \"$Trg\"\n",
			"TargetType: \"$TrgType{Name}\"\n",
			"Libraries: \"@LibList\"\n",
			"Debug Libraries: \"@DebugLibList\"\n",
			"Static Libraries: \"@StatLibList\"\n",
			"Uids: \"@UidList\"\n",
			"BuildVariants: \"@{$Plat{Blds}}\"\n",
			"TargetMakeFile: \"$MAKEFILE\"\n",
			"UserIncludes: \"<Source Dir> @UserIncPaths\"\n",
			"SystemIncludes: \"@SysIncPaths\"\n",
			"Languages: \"@LangList\"\n"
		;
	}
}

my $CurAifRef;
my $CurBaseObj;
my $CurBld;
my $CurBitMapRef;
my @CurDepList;
my $CurDoc;
my $CurResrc;
my $CurSrc;
my $CurSrcPath;
my $ResrcIsSys;

{

	# LOOPING SECTION
	#----------------
# Load the output module
	eval { &Load_ModuleL('OUTPUT'); };
	die $@ if $@;

	&PMStartBldList if defined &PMStartBldList;
	my $LoopBld;
	foreach $LoopBld (@{$Plat{Blds}}) {
		$CurBld=$LoopBld;
		&PMBld if defined &PMBld;
	}
	undef $CurBld;
	undef $LoopBld;
	&PMEndBldList if defined &PMEndBldList;


	# Load the Dependency Generator
	eval { &Load_ModuleL('MAKDEPS'); };
	die $@ if $@;
	eval { &Deps_InitL($E32env::Data{EPOCIncPath},@StdIncPaths); };
	die $@ if $@;
	if ($Options{v}) {
		&Deps_SetVerbose;
	}
	if ($Plat{UsrHdrsOnly}) {
		&Deps_SetUserHdrsOnly;
	}
	&Deps_SetUserIncPaths(@UserIncPaths);
	&Deps_SetSysIncPaths(@SysIncPaths);
	&Deps_SetPlatMacros(@{$Plat{Macros}});


#	Start source list - bitmaps, system resources, resources, .AIF files, documents, sources.

	&PMStartSrcList if defined &PMStartSrcList;

#	start bitmaps

	if ($Options{v}) {
		print "Starting bitmaps\n";
	}
	my $LoopBitMapRef;
	foreach $LoopBitMapRef (@BitMapStruct) {
		$CurBitMapRef=$LoopBitMapRef;
		if ($Options{v}) {
			print "BitMap: \"$$CurBitMapRef{Trg}\"\n";
		}
		&PMStartBitMap if defined &PMStartBitMap;
		my $LoopBld;
		foreach $LoopBld (@{$Plat{Blds}}) {
			$CurBld=$LoopBld;
			&PMBitMapBld if defined &PMBitMapBld;
		}
		undef $CurBld;
		undef $LoopBld;
		&PMEndBitMap if defined &PMEndBitMap;
	}
	undef $CurBitMapRef;
	undef $LoopBitMapRef;

#	end bitmaps

#	start system resources

	if ($Options{v}) {
		print "Starting system resources\n";
	}
	$ResrcIsSys=1;
	my $LoopSrcPath;
	foreach $LoopSrcPath (sort keys %SysResrcHash) {
		$CurSrcPath=$LoopSrcPath;
		if ($Options{v}) {
			print "Sourcepath: \"$CurSrcPath\"\n";
		}
		my $LoopResrc;
		foreach $LoopResrc (@{$SysResrcHash{$CurSrcPath}}) {
			$CurResrc=$LoopResrc;
			if ($Options{v}) {
				print "SystemResource: \"$CurResrc\"\n";
			}
			&PMStartResrc if defined &PMStartResrc;
			if (defined &PMResrcDepend) {
				@CurDepList=();
				my %combinedDepList;
				my $lang;
				foreach $lang (@LangList) {
					my @depList;
					eval { @depList=&Deps_GenDependsL($CurSrcPath.$CurResrc, ("LANGUAGE_$lang")); };
					die $@ if $@;
					foreach (@depList) {
						if (!exists $combinedDepList{$_}) {
							$combinedDepList{$_} = 1;
							push @CurDepList, $_;
						}
					}
				}
				&PMResrcDepend if defined &PMResrcDepend;
				undef @CurDepList;
				undef %combinedDepList;
			}
			my $LoopBld;
			foreach $LoopBld (@{$Plat{Blds}}) {
				$CurBld=$LoopBld;
				&PMResrcBld if defined &PMResrcBld;
			}
			undef $CurBld;
			undef $LoopBld;
			&PMEndResrc if defined &PMEndResrc;
		}
		undef $CurResrc;
		undef $LoopResrc;
	}
	undef $CurSrcPath;
	undef $LoopSrcPath;
	undef $ResrcIsSys;

#	end system resources

#	start resources

	if ($Options{v}) {
		print "Starting resources\n";
	}
	foreach $LoopSrcPath (sort keys %ResrcHash) {
		$CurSrcPath=$LoopSrcPath;
		if ($Options{v}) {
			print "Sourcepath: \"$CurSrcPath\"\n";
		}
		my $LoopResrc;
		foreach $LoopResrc (sort @{$ResrcHash{$CurSrcPath}}) {
			$CurResrc=$LoopResrc;
			if ($Options{v}) {
				print "Resource: \"$CurResrc\"\n";
			}
			&PMStartResrc if defined &PMStartResrc;
			if (defined &PMResrcDepend) {
				@CurDepList=();
				my %combinedDepList;
				my $lang;
				foreach $lang (@LangList) {
					my @depList;
					eval { @depList=&Deps_GenDependsL($CurSrcPath.$CurResrc, ("LANGUAGE_$lang")); };
					die $@ if $@;
					foreach (@depList) {
						if (!exists $combinedDepList{$_}) {
							$combinedDepList{$_} = 1;
							push @CurDepList, $_;
						}
					}
				}
				&PMResrcDepend if defined &PMResrcDepend;
				undef @CurDepList;
				undef %combinedDepList;
			}
			my $LoopBld;
			foreach $LoopBld (@{$Plat{Blds}}) {
				$CurBld=$LoopBld;
				&PMResrcBld if defined &PMResrcBld;
			}
			undef $CurBld;
			undef $LoopBld;
			&PMEndResrc if defined &PMEndResrc;
		}
		undef $CurResrc;
		undef $LoopResrc;
	}
	undef $CurSrcPath;
	undef $LoopSrcPath;

#	end resources

#	start aifs

	if ($Options{v}) {
		print "Starting aifs\n";
	}

# Add tools-relative include path to sys includes, to allow for shared include\aiftool.rh
	use FindBin;
	$FindBin::Bin =~ /:(.*)\//;
	my $extraIncPath = $1;
	$extraIncPath =~ s/\//\\/g;
	my @SavedSysIncPaths = @SysIncPaths;
	push @SysIncPaths, "$extraIncPath\\INCLUDE";
	&Deps_SetSysIncPaths(@SysIncPaths);

	my $LoopAifRef;
	foreach $LoopAifRef (@AifStruct) {
		$CurAifRef=$LoopAifRef;
		if ($Options{v}) {
			print "Aif: \"$$CurAifRef{Trg}\"\n";
		}
		&PMStartAif if defined &PMStartAif;
		if (defined &PMAifDepend) {
			eval { @CurDepList=&Deps_GenDependsL("$$CurAifRef{Dir}$$CurAifRef{Resrc}"); };
			die $@ if $@;
			&PMAifDepend if defined &PMAifDepend;
			undef @CurDepList;
		}
		my $LoopBld;
		foreach $LoopBld (@{$Plat{Blds}}) {
			$CurBld=$LoopBld;
			&PMAifBld if defined &PMAifBld;
		}
		undef $CurBld;
		undef $LoopBld;
		&PMEndAif if defined &PMEndAif;
	}
	undef $CurAifRef;
	undef $LoopAifRef;

	@SysIncPaths = @SavedSysIncPaths;
	&Deps_SetSysIncPaths(@SysIncPaths);

#	end aifs

#	start sources

	if ($Options{v}) {
		print "Starting sources\n";
	}
	foreach $LoopSrcPath (sort keys %SrcHash) {
		$CurSrcPath=$LoopSrcPath;
		if ($Options{v}) {
			print "Sourcepath: \"$CurSrcPath\"\n";
		}
		my $LoopSrc;
		foreach $LoopSrc (sort @{$SrcHash{$CurSrcPath}}) {
			$CurSrc=$LoopSrc;
			if ($Options{v}) {
				print "Source: \"$CurSrc\"\n";
			}
			&PMStartSrc if defined &PMStartSrc;

#			strict depend alt 1 start - call different module function if strict depend flag specified
			if (((not $MmpFlag{StrictDepend}) || (not defined &PMSrcBldDepend)) && defined &PMSrcDepend) {
				eval { @CurDepList=&Deps_GenDependsL($CurSrcPath.$CurSrc); };
				die $@ if $@;
				&PMSrcDepend if defined &PMSrcDepend;
				undef @CurDepList;
			}
#			strict depend alt 1 end

			my $LoopBld;
			foreach $LoopBld (@{$Plat{Blds}}) {
				$CurBld=$LoopBld;
				&PMStartSrcBld if defined &PMStartSrcBld;

#				strict depend alt 2 start - call the module function that deals with dependencies generated for each build variant
				if ($MmpFlag{StrictDepend} && defined &PMSrcBldDepend) {
					eval { @CurDepList=Deps_GenDependsL($CurSrcPath.$CurSrc,@{$BldMacros{$CurBld}}); };
					die $@ if $@;
					&PMSrcBldDepend if defined &PMSrcBldDepend;
					undef @CurDepList;
				}
#				strict depend alt 2 end

				&PMEndSrcBld if defined &PMEndSrcBld;
			}
			undef $CurBld;
			undef $LoopBld;
			&PMEndSrc if defined &PMEndSrc;
		}
		undef $CurSrc;
		undef $LoopSrc;
	}
	undef $CurSrcPath;
	undef $LoopSrcPath;

#	end sources

#	start documents

	if ($Options{v}) {
		print "Starting documents\n";
	}
	foreach $LoopSrcPath (sort keys %DocHash) {
		$CurSrcPath=$LoopSrcPath;
		if ($Options{v}) {
			print "Sourcepath: \"$CurSrcPath\"\n";
		}
		my $LoopDoc;
		foreach $LoopDoc (sort @{$DocHash{$CurSrcPath}}) {
			$CurDoc=$LoopDoc;
			if ($Options{v}) {
				print "Document: \"$CurDoc\"\n";
			}
			&PMDoc if defined &PMDoc;
		}
		undef $CurDoc;
		undef $LoopDoc;
	}
	undef $CurSrcPath;
	undef $LoopSrcPath;

#	end documents

#	rombuild

	my %SpecialRomFileTypes=(
		KEXT=>'extension[MAGIC]',
		LDD=>'device[MAGIC]',
		PDD=>'device[MAGIC]',
		VAR=>'variant[MAGIC]'
	);
	unless ($Plat{Ext} eq '.DSP') { # hack to avoid rombuild target for VC6
		&Output("ROMFILE:\n");
	}
	unless ($Plat{OS} ne 'EPOC32' or $TrgType{Basic} eq 'LIB') {
		my $ref;
		foreach $ref (@RomTargets) {
			my $RomFileType='file';
			if ($$ref{FileType}) {	# handle EKERN.EXE and EFILE.EXE with new ROMFILETYPE keyword instead
				$RomFileType=$$ref{FileType}; # or just do this bit as a custom build makefile
			}
			elsif ($CallDllEntryPoints) {
				$RomFileType='dll';
			}
			elsif ($SpecialRomFileTypes{$TrgType{Name}}) {
				$RomFileType=$SpecialRomFileTypes{$TrgType{Name}};
			}
#			$RomFileType='primary[MAGIC]' if $Trg eq 'EKERN.EXE';
#			$RomFileType='secondary[MAGIC]' if $Trg eq 'EFILE.EXE';
			my $RomPath="System\\Libs\\";
			if ($$ref{Path}) {
				$RomPath=$$ref{Path};
			}
			elsif ($TrgType{Path}) {
				$RomPath=$TrgType{Path};
				$RomPath=~s-Z\\(.*)-$1-o;
			}
			elsif ($TrgType{Name} eq 'EXE') {
				$RomPath="Test\\";
			}
			my $RomFile=$LinkAs;
			if ($$ref{File}) {
				$RomFile=$$ref{File};
			}
			my $RomDecorations='';
			if ($DataLinkAddress) {
				$RomDecorations="reloc=$DataLinkAddress";
			}
			elsif ($FixedProcess) {
				$RomDecorations.='fixed';
			}
			my $IbyTextFrom="$RomFileType=$E32env::Data{RelPath}$Plat{Real}\\##BUILD##\\$Trg";
			my $IbyTextTo="$RomPath$RomFile";
			my $Spaces= 60>length($IbyTextFrom) ? 60-length($IbyTextFrom) : 1; 
#			&Output("\t\@echo \"", $IbyTextFrom, ' 'x$Spaces, "$IbyTextTo $RomDecorations\"\n");
			&Output("\t\@echo ", $IbyTextFrom, ' 'x$Spaces, "$IbyTextTo $RomDecorations\n");
		}
		foreach $ref (@RamTargets) {
			my $RomFileType='data';
			my $RomPath="Img\\";
			if ($$ref{Path}) {
				$RomPath=$$ref{Path};
			}
			my $RomFile=$Trg;
			if ($$ref{File}) {
				$RomFile=$$ref{File};
			}
			my $RomDecorations='attrib=r';
			my $IbyTextFrom="$RomFileType=$E32env::Data{RelPath}$Plat{Real}\\##BUILD##\\$Trg";
			my $IbyTextTo="$RomPath$RomFile";
			my $Spaces= 60>length($IbyTextFrom) ? 60-length($IbyTextFrom) : 1; 
#			&Output("\t\@echo \"", $IbyTextFrom, ' 'x$Spaces, "$IbyTextTo $RomDecorations\"\n");
			&Output("\t\@echo ", $IbyTextFrom, ' 'x$Spaces, "$IbyTextTo $RomDecorations\n");
		}
	}

#	end rombuild

	&PMEndSrcList if defined &PMEndSrcList;
}

{

	# open the makefile and write all the text it requires to it if makmake has so far been successful
	#-------------------------------------------------------------------------------------------------
	eval { &Path_MakePathL($MAKEFILE); };
	die $@ if $@;
	if ($Options{v}) {
		print "Creating: \"$MAKEFILE\"\n";
	}
	open MAKEFILE,">$MAKEFILE" or die "ERROR: Can't open or create file \"$MAKEFILE\"\n";
	print MAKEFILE &OutText or die "ERROR: Can't write output to file \"$MAKEFILE\"\n";
	close MAKEFILE or die "ERROR: Can't close file \"$MAKEFILE\"\n";
	if ($Options{v}) {
		print "Successful MakeFile Creation\n";
	}
}

	
################ END OF MAIN PROGRAM SECTION #################
#------------------------------------------------------------#
##############################################################





# SUBROUTINE SECTION
####################

sub FatalError (@) {

	print STDERR "MAKMAKE ERROR: @_\n";
	exit 1;
}

sub Usage () {

		eval { &Load_ModuleL('MAKHELP'); };
		die $@ if $@; 
		eval { &Help_Invocation; };
		die $@ if $@;
		exit;
}



sub CreateExtraFile ($$) { # takes abs path for source and text
# allows modules to create extrafiles
	my ($FILE,$Text)=@_;
	if ($Options{makemakefile}) {	# only create if making the makefile
		if ($Options{v}) {
			print "Creating \"$FILE\"\n";
		}
		eval { &Path_MakePathL($FILE); };
		die $@ if $@;
		open FILE, ">$FILE" or die "WARNING: Can't open or create \"$FILE\"\n";
		print  FILE $Text or die "WARNING: Can't write text to \"$FILE\"\n";
		close FILE or die "WARNING: Can't close \"$FILE\"\n";
	}
}

sub ABI () {
	$ABI;
}
sub AddSrc ($$) { # needs abs path for source
# allows modules to add a source file to the project and have it created if necessary
	my ($SRCFILE,$Text)=@_;
	my $SrcPath=&Path_Split('Path',$SRCFILE);
	if ((not -e $SRCFILE) || (-M $SRCFILE > -M $MMPFILE)) {
		# only create the file if it's older than the .MMP file
		CreateExtraFile($SRCFILE,$Text);
	}
	push @{$SrcHash{$SrcPath}}, &Path_Split('File',$SRCFILE);
}
sub AddPlatMacros (@) {
# allows modules to add extra macros to the platform macro list
	push @{$Plat{Macros}},@_;
}
sub AifRef () {
	$CurAifRef;
}
sub AifStructRef () {
	\@AifStruct;
}
sub AllowDllData () {
	$AllowDllData;
}
sub ASSPLibList () {
	@ASSPLibList;
}
sub ASSPLinkPath () {
#	this is the path where the target looks for ASSP-specific import libraries
	my $Path=$Path{ASSPLink};
	if ($CurBld) {
#regression hack
		if ($Plat{OS} eq 'EPOC32') {
			$Path.="UREL\\";
		}
		else {
			$Path.="UDEB\\";
		}
#regression hack end
	}
	$Path;
}
sub BaseMak () {
	&Path_Split('Base',$MAKEFILE);
}
sub BaseResrc () {
	&Path_Split('Base',$CurResrc);
}
sub BaseResrcList () {
	my @ResrcList=&ResrcList;
	my $Path;
	foreach $Path (@ResrcList) {
		$Path=&Path_Split('Base',$Path);
	}
	@ResrcList;
}
sub BaseSrc () {
	&Path_Split('Base',$CurSrc);
}
sub BaseSrcList () {
	my @SrcList=&SrcList;
	my $Path;
	foreach $Path (@SrcList) {
		$Path=&Path_Split('Base',$Path);
	}
	@SrcList;
}
sub BaseSysResrcList () {
	my @SysResrcList=&SysResrcList;
	my $Path;
	foreach $Path (@SysResrcList) {
		$Path=&Path_Split('Base',$Path);
	}
	@SysResrcList;
}
sub BaseTrg () {
	&Path_Split('Base',$Trg);
}
sub BitMapRef () {
	$CurBitMapRef;
}
sub BitMapStructRef () {
	\@BitMapStruct;
}
sub Bld () {
	$CurBld;
}
sub BldList () {
	@{$Plat{Blds}};
}
sub BldPath () {
	my $Path=$Path{"Bld"};
	if ($CurBld) {
		$Path.="$CurBld\\";
	}
	$Path;
}
sub CallDllEntryPoints () {
	$CallDllEntryPoints;
}
sub CompatibleABIs () {
	@CompatibleABIs;
}
sub DataLinkAddress () {
	$DataLinkAddress;
}
sub DataPath () {
	$E32env::Data{DataPath};
}
sub DebugLibList () {
	@DebugLibList;
}
sub DefFile () {
	"$Def{Path}$Def{Base}$Def{Ext}";
}
sub DepList () {
	sort @CurDepList;
}
sub Doc () {
	$CurDoc;
}
sub DocList () {
	if ($CurSrcPath) {
		return sort @{$DocHash{$CurSrcPath}};
	}
	my @DocList;
	my $Key;
	foreach $Key (keys %DocHash) {
		push @DocList,@{$DocHash{$Key}};
	}
	sort @DocList;
}
sub EPOCPath () {
	$E32env::Data{EPOCPath};
}
sub EPOCIncPath () {
	$E32env::Data{EPOCIncPath};
}
sub EPOCRelPath () {
	$E32env::Data{RelPath};
}
sub EPOCToolsPath () {
	$E32env::Data{EPOCToolsPath};
}
sub Exports () {
	@{$TrgType{Exports}{$Plat{"DefFile"}}};
}
sub ExportUnfrozen () {
	$ExportUnfrozen;
}
sub FirstLib () {
	$FirstLib;
}
sub FixedProcess () {
	$FixedProcess;
}
sub BasicTrgType () {
	$TrgType{Basic};
}
sub HeapSize () {
	%HeapSize;
}
sub LangList () {
	@LangList;
}
sub LibList () {
	@LibList;
}
sub LibPath () {
#	this is the path where the target puts it's import library
	my $Path=$Path{Lib};
	if ($CurBld) {
#regression hack
		if ($Plat{OS} eq 'EPOC32') {
			$Path.="UREL\\";
		}
		else {
			$Path.="UDEB\\";
		}
#regression hack end
	}
	$Path;
}
sub LinkAs () {
	$LinkAs;
}
sub LinkPath () {
#	this is the place where the target looks for CPU-specific libraries
	my $Path=$Path{Link};
	if ($CurBld) {
#regression hack
		if ($Plat{OS} eq 'EPOC32') {
			$Path.="UREL\\";
		}
		else {
			$Path.="UDEB\\";
		}
#regression hack end
	}
	$Path;
}
sub MacroList ($) {
	if ($_[0]) {
	return @{$BldMacros{$_[0]}};
	}
	return @{$Plat{Macros}} unless $CurBld;
	(@{$Plat{Macros}},@{$BldMacros{$CurBld}});
}
sub MakeFilePath () {
	&Path_Split('Path',$MAKEFILE);
}
sub MmpFile () {
	$MMPFILE;
}
sub PerlLibPath () {
	$PerlLibPath;
}
sub Plat () {
	$Plat{Real};
}
sub PlatABI () {
	$Plat{"ABI"};
}
sub PlatName () {
	$Plat{Name};
}
sub ProcessPriority () {
	$ProcessPriority;
}
sub RelPath () {
	my $Path=$Path{Rel};
	if ($CurBld) {
		$Path.="$CurBld\\";
	}
	$Path;
}
sub Resrc () {
	$CurResrc;
}
sub ResrcIsSys () {
	$ResrcIsSys;
}
sub ResrcList () {
	if ($CurSrcPath) {
		return @{$ResrcHash{$CurSrcPath}};
	}
	my @ResrcList;
	my $Key;
	foreach $Key (keys %ResrcHash) {
		push @ResrcList,@{$ResrcHash{$Key}};
	}
	sort @ResrcList;
}
sub	SetStdIncPaths (@) {
# allows module to set standard include paths
	@StdIncPaths=();
	my $Path;
	foreach $Path (@_) {
		$Path=uc $Path;
		$Path=~s-^(.*[^\\])$-$1\\-o;
		push @StdIncPaths, $Path;	# only place drive letters may appear, up to modules to handle
	}
}
sub Src () {
	$CurSrc;
}
sub SrcList () {
	if ($CurSrcPath) {
		return sort @{$SrcHash{$CurSrcPath}};
	}
	my @SrcList;
	my $Key;
	foreach $Key (keys %SrcHash) {
		push @SrcList,@{$SrcHash{$Key}};
	}
	sort @SrcList;
}
sub StackSize () {
	$StackSize;
}
sub StatLibList () {
	@StatLibList;
}
sub StatLinkPath () {
	my $Path=$Path{StatLink};
	if ($CurBld) {
		$Path.="$CurBld\\";
	}
	$Path;
}
sub SrcPath () {
	$CurSrcPath;
}
sub SysIncPaths () {
	@SysIncPaths;
}
sub SysResrcList () {
	if ($CurSrcPath) {
		return sort @{$SysResrcHash{$CurSrcPath}};
	}
	my @SysResrcList;
	my $Key;
	foreach $Key (keys %SysResrcHash) {
		push @SysResrcList,@{$SysResrcHash{$Key}};
	}
	sort @SysResrcList;
}
sub Trg () {
	$Trg;
}
sub TrgPath () {
	$TrgType{Path};
}
sub TrgType () {
	$TrgType{Name};
}
sub UidList () {
	@UidList;
}
sub UserIncPaths () {
	@UserIncPaths;
}
sub SrcDbg () {
	$SrcDbg;
}

