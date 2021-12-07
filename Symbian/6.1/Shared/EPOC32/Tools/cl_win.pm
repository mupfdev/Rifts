# CL_WIN.PM
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
#


package Cl_win;

# declare variables global for module
my @Win32LibList=();
my $BaseAddressFlag;
my $Win32Resrc;

require Exporter;
@ISA=qw(Exporter);
@EXPORT=qw(
	PMHelp_Mmp

	PMCheckPlatformL

	PMPlatProcessMmp
	
	PMStartBldList
		PMBld
	PMStartSrcList
		PMStartBitMap
			PMBitMapBld
		PMEndBitMap
		PMStartResrc
		PMResrcDepend
			PMResrcBld
		PMEndResrc
		PMStartAif
		PMAifDepend
			PMAifBld
		PMEndAif
		PMStartSrc
		PMSrcDepend
			PMSrcBldDepend
			PMEndSrcBld
		PMEndSrc
	PMEndSrcList
);

use Winutl;

sub PMHelp_Mmp {
	&Winutl_Help_Mmp;
}

sub PMCheckPlatformL {
	if ((&main::Plat eq 'TOOLS') and (&main::BasicTrgType ne 'EXE')) {
		die "Can't specify anything but EXE targettypes for this platform\n";
	}
}

sub PMPlatProcessMmp (@) {

	&Winutl_DoMmp(@_);
	$BaseAddressFlag=&Winutl_BaseAddress;
	$BaseAddressFlag=~s/^(.+$)$/ \/base:\"$1\"/o;
	@Win32LibList=&Winutl_Win32LibList;
	$Win32Resrc=&Winutl_Win32Resrc;
}

sub PMStartBldList {
	my $AifStructRef=&main::AifStructRef;
	my @BaseResrcList=&main::BaseResrcList;
	my @BaseSysResrcList=&main::BaseSysResrcList;
	my $BaseTrg=&main::BaseTrg;
	my $BitMapStructRef=&main::BitMapStructRef;
	my @BldList=&main::BldList;
	my $BldPath=&main::BldPath;
	my $ChopDataPath=&main::Path_Chop(&main::DataPath);
	my @ChopSysIncPaths=&main::Path_Chop(&main::SysIncPaths);
	my $ChopTrgPath=&main::Path_Chop(&main::TrgPath);
	my @ChopUserIncPaths=&main::Path_Chop(&main::UserIncPaths);
	my $DefFile=&main::DefFile;
	my $BasicTrgType=&main::BasicTrgType;
	my @LangList=&main::LangList;
	my $LibPath=&main::LibPath;
	my $LinkPath=&main::LinkPath;
	my @MacroList=&main::MacroList;
	my $Plat=&main::Plat;
	my $RelPath=&main::RelPath;
	my $StatLinkPath=&main::StatLinkPath;
	my $Trg=&main::Trg;
	my $TrgType=&main::TrgType;


	&main::Output(
		"\n",
		'# CWD ', &main::Path_WorkPath, "\n",
		'# MMPFile ', &main::MmpFile, "\n",
		"# Target $Trg\n",
		"# TargetType $TrgType\n",
		"# BasicTargetType $BasicTrgType\n",
		"\n",
		"\n",
		"!if \"\$(OS)\" == \"Windows_NT\"\n",
		"ERASE = \@erase 2>>nul\n",
		"!else\n",
		"ERASE = \@erase\n",
		"!endif\n",
		"\n",
		"\n",
		"# EPOC DEFINITIONS\n",
		"\n"
	);

	&main::Output(
		"INCDIR  ="
	);
	foreach (@ChopUserIncPaths,@ChopSysIncPaths) {
		&main::Output(
			" /I \"$_\""
		);
	}
	&main::Output(
		"\n",
		"\n"
	);

	&main::Output(
		"CLFLAGS = /nologo /Zp4 /W4"
	);
# tools hack in line below
	unless (@Win32LibList or &main::Plat eq 'TOOLS') {
		&main::Output(
			" /X"
		);
	}
	&main::Output(
		"\n",
		"\n"
	);

	&main::Output(
		"CLDEFS  ="
	);
	foreach(@MacroList) {
		&main::Output(
			" /D \"$_\""
		);
	}
	&main::Output(
		" \$(USERDEFS)\n",
		"\n"
	);

	&main::Output(
		"EPOCBLD = $BldPath #\n",
		"EPOCTRG = $RelPath #\n",
		"EPOCLIB = $LibPath #\n",
		"EPOCLINK = $LinkPath #\n",
		"EPOCSTATLINK = $StatLinkPath #\n",
		"\n"
	);
	foreach (@BldList) {
		&main::Output(
			"EPOCBLD$_ = \$(EPOCBLD)$_\n",
			"EPOCTRG$_ = \$(EPOCTRG)$_\n",
			"EPOCLIB$_ = \$(EPOCLIB)UDEB\n",
			"EPOCLINK$_ = \$(EPOCLINK)UDEB\n",
			"EPOCSTATLINK$_ = \$(EPOCSTATLINK)$_\n",
			"\n"
		);
	}
	&main::Output(
		"\n"
	);

	&main::Output(
		"TRGDIR = "
	);
	if ($Plat!~/^WINC$/o && $ChopTrgPath) {	# target path not allowed under WINC
		&main::Output(
			$ChopTrgPath
		);
	}
	else {
		&main::Output(
			".\\"
		);
	}
	&main::Output(
		"\n",
		"\n"
	);

	&main::Output(
		"DATADIR = $ChopDataPath\n",
		"\n"
	);
	foreach (@BldList) {
		&main::Output(
			"CL$_ = cl.exe"
		);
		if ($BasicTrgType=~/^EXE$/o) {
			&main::Output(
				' /ML'
			);
		}
		elsif ($BasicTrgType=~/^(DLL|LIB)$/o) {
			&main::Output(
				' /MD'
			);
		}
		if (/DEB$/o) {
			&main::Output(
				'd'
			);
		}
		if (/DEB$/o) {
			&main::Output(
				' /Zi /Od'
			);
#			euser hack to apply inlining on the _NAKED functions
			if ($BaseTrg=~/^EUSER$/o) {
				&main::Output(
					' /Ob1'
				);
			}
		}
		elsif (/REL$/o) {
#			euser hack to prevent minimum size optimisation from disrupting the maths functions
			unless ($BaseTrg=~/^EUSER$/o) {
				&main::Output(
					' /O1 /Op'
				);
			}
			else {
				&main::Output(
					' /Od /Ob1'
				);
			}
		}
		&main::Output(
			' $(CLFLAGS)'
		);
		if (/DEB$/o) {
			&main::Output(
				" /FR\"\$(EPOCBLD$_)/\" /Fd\"\$(EPOCTRG$_)\\\$(TRGDIR)\\$BaseTrg.pdb\""
			);
		}
		foreach (&main::MacroList($_)) {
			&main::Output(
				" /D $_"
			);
		}
		&main::Output(
			" \$(CLDEFS) \$(INCDIR)\n"
		);
	}
	&main::Output(
		"\n",
		"\n"
	);
	

	&main::Output(
		"# EPOC PSEUDOTARGETS\n",
		"\n"
	);
	foreach (@BldList) {
		&main::Output(
			"$_ :"
		);

		&main::Output(
			" \\\n",
			"\tRESOURCE$_"
		);

		&main::Output (
			" \\\n",
			"\t\"\$(EPOCTRG$_)\\\$(TRGDIR)\\$Trg\""
		);
		unless (/REL$/o) {
			&main::Output(
				" \\\n",
				"\t\"\$(EPOCTRG$_)\\$BaseTrg.bsc\""
			);
		}

#		lib has to come after the main target so that a .DEF file will be generated if the project is not frozen
		if ($DefFile and not &main::ExportUnfrozen) {
			&main::Output(
				" \\\n",
				"\tLIBRARY\n"
			);
		}
		&main::Output(
			"\n",
			"\n"
		);
	}


	&main::Output(	# ALL comes after DEB: because first target in makefile is the default
		"ALL :"
	);
	foreach (@BldList) {
		&main::Output(
			" $_"
		);
	}
	&main::Output(
		"\n",
		"\n",
		"WHAT WHATALL :"
	);
	foreach (@BldList) {
		&main::Output(
			" WHAT$_"
		);
	}
	&main::Output(
		"\n",
		"\n",
		"RESOURCE RESOURCEALL :"
	);
	foreach (@BldList) {
		&main::Output(
			" RESOURCE$_"
		);
	}
	&main::Output(
		"\n",
		"\n",
		"CLEAN CLEANALL : CLEANBUILD CLEANRELEASE CLEANLIBRARY",
		"\n",
		"\n",
		"CLEANBUILD CLEANBUILDALL :"
	);
	foreach (@BldList) {
		&main::Output(
			" CLEANBUILD$_"
		);
	}
	&main::Output(
		"\n",
		"\n",
		"CLEANRELEASE :"
	);
	foreach (@BldList) {
		&main::Output(
			" CLEANRELEASE$_"
		);
	}
	&main::Output(
		"\n",
		"\n",
		"MAKEWORK : MAKEWORKBUILD MAKEWORKRELEASE MAKEWORKLIBRARY\n",
		"\n",
		"MAKEWORKBUILD :"
	);
	foreach (@BldList) {
		&main::Output(
			" MAKEWORKBUILD$_"
		);
	}
	&main::Output(
		"\n",
		"\n",
		"MAKEWORKRELEASE :"
	);
	foreach (@BldList) {
		&main::Output(
			" MAKEWORKRELEASE$_"
		);
	}
	&main::Output(
		"\n",
		"\n",
		"LISTING :"
	);
	foreach (@BldList) {
		&main::Output(
			" LISTING$_"
		);
	}
	&main::Output(
		"\n",
		"\n"
	);


	foreach (@BldList) {
		&main::Output(
			"\n",
			"RESOURCE$_ : MAKEWORK$_"
		);

		my $BitMapRef;
		foreach $BitMapRef (@$BitMapStructRef) {
			&main::Output(
				" \\\n",
				"\t\"\$(EPOCTRG$_)\\"
			);
			if ($$BitMapRef{TrgPath}) {
				&main::Output(
					$$BitMapRef{TrgPath}
				);
			}
			&main::Output(
				"$$BitMapRef{Trg}\""
			);
		}
		undef $BitMapRef;

		my $BaseResrc;
		foreach $BaseResrc (@BaseSysResrcList) { # system resources first
			my $Lang;
			foreach $Lang (@LangList) {
				&main::Output(	# must come before main target because source for target will depend on the
				" \\\n",						# *.rsg file in $EPOCIncPath
				"\t\"\$(EPOCTRG$_)\\\$(DATADIR)\\$BaseResrc.R$Lang\""
				);
			}
		}
		foreach $BaseResrc (@BaseResrcList) { # system resources first
			my $Lang;
			foreach $Lang (@LangList) {
				&main::Output(	# must come before main target because source for target will depend on the
				" \\\n",						# *.rsg file in $EPOCIncPath
				"\t\"\$(EPOCTRG$_)\\\$(TRGDIR)\\$BaseResrc.R$Lang\""
				);
			}
		}
		undef $BaseResrc;

		my $AifRef;
		foreach $AifRef (@$AifStructRef) {
			&main::Output(
				" \\\n",
				"\t\"\$(EPOCTRG$_)\\\$(TRGDIR)\\$$AifRef{Trg}\""
			);
		}
		undef $AifRef;

		&main::Output(
			"\n"
		);
	}
	&main::Output(
		"\n",
		"\n",
	);

	&main::Output(
		"LIBRARY :"
	);
	if ($BasicTrgType=~/^LIB$/o) {
#		code to ensure that the static libraries for all builds are built at the library stage
		foreach (@BldList) {
			&main::Output(
				" $_"
			);
		}
	}
	elsif ($DefFile) {
		unless (&main::ExportUnfrozen) {
			if (-e $DefFile) { # effectively "if project frozen ..."
				&main::Output(
					" \"\$(EPOCLIB)UDEB\\$BaseTrg.LIB\"\n"
				);
			}
			else {
				&main::Output(
					"\n",
					"\t\@echo WARNING: Not attempting to create \"\$(EPOCLIB)UDEB\\$BaseTrg.LIB\".\n",
					"\t\@echo When exports are frozen in \"$DefFile\", regenerate Makefile.\n"
				);
			}
		}
		else {
			&main::Output(
				"\n",
				"\t\@echo Not attempting to create \"\$(EPOCLIB)UDEB\\$BaseTrg.LIB\"\n",
				"\t\@echo from frozen .DEF file, since EXPORTUNFROZEN specified.\n"
			);
		}
		&main::Output(
			"\n",
			"\n",
			"# REAL TARGET - LIBRARY\n",
			"\n",
			"\"\$(EPOCLIB)UDEB\\$BaseTrg.LIB\" : \"$DefFile\" MAKEWORKLIBRARY\n",
			"\tlib.exe /nologo /machine:i386 /nodefaultlib /name:\"$Trg\" /def:\"$DefFile\" /out:\"\$(EPOCLIB)UDEB\\$BaseTrg.LIB\"\n",
			"\tdel \"\$(EPOCLIB)UDEB\\$BaseTrg.exp\"\n"
		);
	}
	&main::Output(
		"\n",
		"\n",
		"FREEZE :\n"
	);
	if ($DefFile) {
		&main::Output(
#			call perl on the script here so nmake will die if there are errors - this doesn't happen if calling perl in a batch file
			"\tperl -S efreeze.pl \"$DefFile\" \"\$(EPOCBLD)$BaseTrg.def\" \n"
		);
	}
	&main::Output(
		"\n",
		"CLEANLIBRARY :\n"
	);
	if ($DefFile) {
		&main::Output(
			"\t-\$(ERASE) \"\$(EPOCLIB)UDEB\\$BaseTrg.*\"\n"
		);
	}
	&main::Output(
		"\n",
		"MAKEWORKLIBRARY : \"${LibPath}UDEB\"\n",
		"\n",
		"\"${LibPath}UDEB\" :\n",
		"\t\@perl -S emkdir.pl \"${LibPath}UDEB\"\n",
		"\n",
		"\n"
	);
}

sub PMBld {

	my $AifStructRef=&main::AifStructRef;
	my @BaseResrcList=&main::BaseResrcList;
	my @BaseSrcList=&main::BaseSrcList;
	my @BaseSysResrcList=&main::BaseSysResrcList;
	my $BaseTrg=&main::BaseTrg;
	my $BitMapStructRef=&main::BitMapStructRef;
	my $Bld=&main::Bld;
	my $ChopBldPath=&main::Path_Chop(&main::BldPath);
	my $ChopDataPath=&main::Path_Chop(&main::DataPath);
	my $DefFile=&main::DefFile;
	my $EPOCIncPath=&main::EPOCIncPath;
	my $EPOCLocPath=&main::EPOCPath."Localisation\\";
	my $FirstLib=&main::FirstLib;
	my $BasicTrgType=&main::BasicTrgType;
	my @LangList=&main::LangList;
	my @LibList;
	my $RelPath=&main::RelPath;
	my @StatLibList=&main::StatLibList;
	my $Trg=&main::Trg;
	my $TrgPath=&main::TrgPath;
	my $TrgType=&main::TrgType;

	my $ChopTrgPath=&main::Path_Chop($TrgPath);
	unless ($ChopTrgPath) {
		$ChopTrgPath='.';
	}

	my $WarningLevel='/WARN:3';
	if (&main::Plat() eq 'TOOLS') {
		$WarningLevel='/WARN:1';    # avoid LNK4005 warnings about unused libraries
	}

	if ($Bld =~ /DEB/) {
		@LibList=&main::DebugLibList;
	} else {
		@LibList=&main::LibList;
	}

	my $BLDTRGPATH = "\$(EPOCTRG$Bld)\\";
	if ($TrgPath) {
		$BLDTRGPATH .= "\$(TRGDIR)\\";	    # handles TARGETPATH
	}

	# REAL TARGETS
	#-------------
	&main::Output(
		"# REAL TARGET - BUILD VARIANT $Bld\n",
		"\n"
	);

#	releasables
	&main::Output(
		"RELEASEABLES=",
	);
#tools hack
	unless (&main::Plat() eq 'TOOLS') {
		&main::Output(
			" \\\n\t\"$BLDTRGPATH$Trg\""
		);
		my $BitMapRef;
		foreach $BitMapRef (@$BitMapStructRef) {
			&main::Output(
				" \\\n\t\"\$(EPOCTRG$Bld)\\"
			);
			if ($$BitMapRef{TrgPath}) {
				&main::Output(
					$$BitMapRef{TrgPath}
				);
			}
			&main::Output(
				"$$BitMapRef{Trg}\""
			);
			if ($$BitMapRef{Hdr}) {
				&main::Output(
					" \\\n\t\"$EPOCIncPath", &main::Path_Split('Base', $$BitMapRef{Trg}), ".MBG\""
				);
			}
		}
		my $BaseResrc;
		foreach $BaseResrc (@BaseSysResrcList) {
			my $Lang;
			foreach $Lang (@LangList) {
				&main::Output(
					" \\\n\t\"\$(EPOCTRG$Bld)\\\$(DATADIR)\\$BaseResrc.R$Lang\""
				);
			}
			&main::Output(
				" \\\n\t\"$EPOCLocPath$BaseResrc.rpp\"",
				" \\\n\t\"$EPOCIncPath$BaseResrc.RSG\""
			);
		}
		foreach $BaseResrc (@BaseResrcList) {
			my $Lang;
			foreach $Lang (@LangList) {
				&main::Output(
					" \\\n\t\"$BLDTRGPATH$BaseResrc.R$Lang\""
				);
			}
			&main::Output(
				" \\\n\t\"$EPOCLocPath$BaseResrc.rpp\"",
				" \\\n\t\"$EPOCIncPath$BaseResrc.RSG\""
			);
		}
		my $AifRef;
		foreach $AifRef (@$AifStructRef) {
			&main::Output(
				" \\\n\t\"$BLDTRGPATH$$AifRef{Trg}\""
			);
		}
		if (-e $DefFile) { # effectively "if project frozen ..."
			&main::Output(
				" \\\n\t\"\$(EPOCLIB$Bld)\\$BaseTrg.LIB\""
			);
		}
		if ($Bld=~/DEB$/o) {
			&main::Output(
				" \\\n\t\"$BLDTRGPATH$BaseTrg.PDB\""
			);
		}
	}
	else {
		&main::Output(
			" \\\n\t\"", &main::EPOCToolsPath(), "$Trg\""
		);
	}
#tools hack end
	&main::Output(
		"\n",
		"\n"
	);

	&main::Output(
		"WHAT$Bld :\n",
		"\t\@echo \$(RELEASEABLES)\n",
		"\n",
		"CLEAN$Bld : CLEANBUILD$Bld CLEANRELEASE$Bld\n",
		"\n",
		"CLEANBUILD$Bld : \n",
		"\t\@perl -S ermdir.pl \"\$(EPOCBLD$Bld)\"\n",
		"\t-\$(ERASE) \"$BLDTRGPATH$BaseTrg.ILK\"\n",
		"\n",
		"CLEANRELEASE$Bld : \n",
		"\t-\$(ERASE) \$(RELEASEABLES)\n",
		"\t-\$(ERASE) \"$BLDTRGPATH$BaseTrg.ILK\"\n",
		"\n"
	);

	&main::Output(
		"MAKEWORK$Bld : MAKEWORKBUILD$Bld MAKEWORKRELEASE$Bld\n",
		"\n",
		"MAKEWORKBUILD$Bld : \"$ChopBldPath\"\n",
		"\n",
		"MAKEWORKRELEASE$Bld : \"$RelPath$ChopTrgPath\""
	);
	if (@BaseSysResrcList) {
		&main::Output(
			" \"$RelPath$ChopDataPath\""
		);
	}
	&main::Output(
		"\n",
		"\n"
	);
	foreach ($ChopBldPath, "$RelPath$ChopTrgPath", "$RelPath$ChopDataPath") {
		&main::Output(
			"\"$_\" : \n",
			"\t\@perl -S emkdir.pl \"$_\"\n",
			"\n"
		);
	}
	&main::Output(
		"\n"
	);

	&main::Output(
		"LISTING$Bld :"
	);
	foreach (@BaseSrcList) {
		&main::Output(
			" \\\n\tLISTING$Bld$_"
		);
	}
	&main::Output(
		"\n",
		"\n"
	);

	if ($Bld=~/DEB$/o) {
		&main::Output(
			"BSC32_SBRS="
		);
		foreach (@BaseSrcList) {
			&main::Output(
				" \\\n",
				"\t\"\$(EPOCBLD$Bld)\\$_.sbr\""
			);
		}
		&main::Output(
			"\n",
			"\n",
		"\"\$(EPOCTRG$Bld)\\$BaseTrg.bsc\" : \$(BSC32_SBRS)\n",
		"\tbscmake.exe \@<<\n",
		"\t/nologo /o\$\@ \$(BSC32_SBRS)\n",
		"<<\n",
		"\n",
		"\n"
		);
	}

	&main::Output(
		"LIBS="
	);
	foreach (@StatLibList) {
		&main::Output(
			" \\\n\t\"\$(EPOCSTATLINK$Bld)\\$_\""
		);
	}
	foreach (@LibList) {
		&main::Output(
			" \\\n\t\"\$(EPOCLINK$Bld)\\$_\""
		);
	}
	&main::Output(
		"\n",
		"\n"
	);

	&main::Output(
		"LINK_OBJS="
	);
	foreach (@BaseSrcList) {
		&main::Output(
			" \\\n",
			"\t\"\$(EPOCBLD$Bld)\\$_.obj\""
		);
	}
	if ($Win32Resrc) {
		&main::Output(
			" \\\n",
			"\t\"\$(EPOCBLD$Bld)\\",&main::Path_Split('Base',$Win32Resrc),".res\""
		);
	}
	&main::Output(
		"\n",
		"\n"
	);

	if ($BasicTrgType=~/^DLL$/o) {
		&main::OutFormat(
			"STAGE1_LINK_FLAGS="
		);
		&main::OutFormat(
			"\"\$(EPOCSTATLINK$Bld)\\$FirstLib\""
		);
		foreach (@Win32LibList) {
			&main::OutFormat(
				' ',lc $_
			);
		}
		&main::OutFormat(
			" \$(LIBS) /nologo$BaseAddressFlag /entry:\"_E32Dll\" /subsystem:windows /dll"
		);
		if ($Bld=~/DEB$/o) {
			&main::OutFormat(
				' /debug'
			);
		}
		&main::OutFormat(
			" /incremental:no /PDBTYPE:SEPT /machine:IX86 /nodefaultlib /include:\"",'?_E32Dll@@YGHPAXI0@Z',"\" /out:\"\$(EPOCBLD$Bld)\\$Trg\" $WarningLevel"
		);
		&main::Output(
			"\n",
			"\n"
		);
	}

	&main::OutFormat(
		'LINK_FLAGS='
	);
	if ($BasicTrgType=~/^(EXE|DLL)$/o) {
# tools hack
		unless (&main::Plat eq 'TOOLS') {
			&main::OutFormat(
				" \"\$(EPOCSTATLINK$Bld)\\$FirstLib\""
			);
		}
# tools hack end
	}
	foreach (@Win32LibList) {
		&main::OutFormat(
			' ',lc $_
		);
	}
	&main::OutFormat(
		' $(LIBS) /nologo'
	);
	if ($BasicTrgType=~/^DLL$/o) {
		&main::OutFormat(
			"$BaseAddressFlag /entry:\"_E32Dll\""
		);
	}
	elsif ($BasicTrgType=~/^EXE$/o) {
# tools hack
		unless (&main::Plat eq 'TOOLS') {
			&main::OutFormat(
				" /entry:\"_E32Startup\""
			);
		}
# tools hack end
	}
	if (&main::Plat=~/^(WINC|TOOLS)$/o && $BasicTrgType=~/^EXE$/o) {
		&main::OutFormat(
			' /subsystem:console'
		);
	}
	else {
		&main::OutFormat(
			' /subsystem:windows'
		);
	}
	if ($BasicTrgType=~/^DLL$/o) {
		&main::OutFormat(
			" /dll \"\$(EPOCBLD$Bld)\\$BaseTrg.exp\""
		);
	}
	if ($BasicTrgType=~/^(DLL|EXE)$/o) {
		if ($Bld=~/DEB$/o) {
			&main::OutFormat(
				' /debug'
			);
		}
		elsif ($Bld=~/REL$/o) {
			&main::OutFormat(
				' /incremental:no'
			);
		}
	}
	&main::OutFormat(
		' /PDBTYPE:SEPT /machine:IX86'
	);
# tools hack
	unless (&main::Plat eq 'TOOLS') {
		&main::OutFormat(
			' /nodefaultlib'
		);
		if ($BasicTrgType=~/^DLL$/o) {	# force link to edll.lib
			&main::OutFormat(
				" /include:\"",'?_E32Dll@@YGHPAXI0@Z',"\""
			);
		}
		elsif ($BasicTrgType=~/^EXE$/o) {	# force link to eexe.lib
			&main::OutFormat(
				" /include:\"",'?_E32Startup@@YGXXZ',"\""
			);
		}
	}
# tools hack end
	&main::OutFormat(
		" /out:\"\$(EPOCTRG$Bld)\\\$(TRGDIR)\\$Trg\""
	);
	if ($BasicTrgType=~/^(DLL|EXE)$/o) {
		&main::OutFormat(
			" $WarningLevel"
		);
	}
	&main::Output(
		"\n",
		"\n"
	);

	&main::Output(
		"\"\$(EPOCTRG$Bld)\\\$(TRGDIR)\\$Trg\" : \$(LINK_OBJS)"
	);
	if (-e $DefFile) { # effectively "if project frozen ..."
		&main::Output(
			" \"$DefFile\""
		);
	}
	if ($BasicTrgType=~/^(DLL|EXE)$/o) {
# tools hack
		unless (&main::Plat eq 'TOOLS') {
			&main::Output(
				" \"\$(EPOCSTATLINK$Bld)\\$FirstLib\""
			);
		}
	}
# tools hack end
	&main::Output(
		" \$(LIBS)\n"
	);


#	Link by name first time round for dlls
	if ($BasicTrgType=~/^DLL$/o) {
		&main::Output(
			"\tlink.exe \@<<\n",
			"\t\t\$(STAGE1_LINK_FLAGS) \$(LINK_OBJS)\n",
			"<<\n",
			"\tdel \"\$(EPOCBLD$Bld)\\$Trg\"\n",
			"\tdel \"\$(EPOCBLD$Bld)\\$BaseTrg.exp\"\n"
		);

#		Generate an export info file
		&main::Output(
			"\tdumpbin /exports /out:\"\$(EPOCBLD$Bld)\\$BaseTrg.inf\" \"\$(EPOCBLD$Bld)\\$BaseTrg.lib\"\n",
			"\tdel \"\$(EPOCBLD$Bld)\\$BaseTrg.lib\"\n"
		);

#		call makedef to reorder the export information
		&main::Output(
#			call perl on the script here so nmake will die if there are errors - this doesn't happen if calling perl in a batch file
			"\tperl -S makedef.pl -Inffile \"\$(EPOCBLD$Bld)\\$BaseTrg.inf\""
		);
		if (-e $DefFile) { # effectively "if project frozen ..."
			&main::Output(
				" -Frzfile \"$DefFile\""
			);
		}
		else { # freeze ordinals, a maximum of 2, for polymorphic dlls
			my $Ordinal;
			my $Num=1;
			foreach $Ordinal (&main::Exports) {
#				replace "$" with "$$" so that NMAKE doesn't think there's a macro in the function name
				$Ordinal=~s-\$-\$\$-go;
				&main::Output(
					" -$Num $Ordinal"
				);
				$Num++;
			}
		}
		&main::Output(
			" \"\$(EPOCBLD)$BaseTrg.def\" \n",
			"\tdel \"\$(EPOCBLD$Bld)\\$BaseTrg.inf\"\n"
		);

		# create the export object from the .DEF file
		&main::Output(
			"\tlib.exe  /nologo /machine:i386 /nodefaultlib /name:\"$Trg\" /def:\"\$(EPOCBLD)$BaseTrg.def\" /out:\"\$(EPOCBLD$Bld)\\$BaseTrg.lib\"\n"
		);
		if (&main::ExportUnfrozen) {
			&main::Output(
			"\tcopy \"\$(EPOCBLD$Bld)\\$BaseTrg.lib\" \"\$(EPOCLIB)UDEB\\$BaseTrg.LIB\"\n"
			);
		}
		&main::Output(
			"\tdel \"\$(EPOCBLD$Bld)\\$BaseTrg.lib\"\n"
		);
	}

	if ($BasicTrgType=~/^(DLL|EXE)$/o) {
		&main::Output(
			"\tlink.exe \@<<\n"
		);
	}
	elsif ($BasicTrgType=~/^LIB$/o) {
		&main::Output(
			"\tlib.exe \@<<\n"
		);
	}
	&main::Output(
		"\t\t\$(LINK_FLAGS) \$(LINK_OBJS)\n",
		"<<\n"
	);

	if ($BasicTrgType=~/^DLL$/o) {
		&main::Output(
			"\tdel \"\$(EPOCBLD$Bld)\\$BaseTrg.exp\"\n"
		);
	}

# tools hack
	if (&main::Plat eq 'TOOLS') {
		&main::Output(
			"\tcopy \"\$(EPOCTRG$Bld)\\\$(TRGDIR)\\$Trg\" \"",&main::EPOCToolsPath,"$Trg\"\n"
		);
	}
# tools hack end

	&main::Output(
		"\n",
		"\n"
	);
}

sub PMStartSrcList {

	&main::Output(
		"# SOURCES\n",
		"\n"
	);
}

sub PMStartBitMap {
	my $BitMapRef=&main::BitMapRef;


	&main::Output(
		"# BitMap $$BitMapRef{Trg}\n",
		"\n"
	);
}

sub PMBitMapBld {
	my $BitMapRef=&main::BitMapRef;
	my $Bld=&main::Bld;

#	must lower-case header here since bmconv generates a header with case-sensitive enums accordingly
	my $BitMapHdr=join('', &main::EPOCIncPath, &main::Path_Split('Base', $$BitMapRef{Trg}), '.mbg');
	my $RTWBitMapHdr=&main::Path_RltToWork($BitMapHdr);
	my $TmpBitMapHdr=join('', &main::BldPath, &main::Path_Split('Base', $$BitMapRef{Trg}), '.mbg');
	my $RTWTmpBitMapHdr=&main::Path_RltToWork($TmpBitMapHdr);

	my $ChopBitMapTrgFullPath="\$(EPOCTRG$Bld)";
	if ($$BitMapRef{TrgPath}) {
		$ChopBitMapTrgFullPath.="\\$$BitMapRef{TrgPath}";
		chop $ChopBitMapTrgFullPath;
	}

	&main::Output(
		"\"$ChopBitMapTrgFullPath\\$$BitMapRef{Trg}\" :"
	);
	my $SrcRef;
	foreach $SrcRef (@{$$BitMapRef{Source}}) {
		&main::Output(
			" \"$$SrcRef{Src}\""
		);
	}
	&main::Output(
		"\n",
		"\t\@if not exist \"$ChopBitMapTrgFullPath\" perl -S emkdir.pl \"$ChopBitMapTrgFullPath\"\n",
		"\tbmconv <<\n",
		" /q"
	);
	if ($$BitMapRef{Hdr}) {
		&main::Output(
			" /h$TmpBitMapHdr"
		);
	}
	&main::Output(
		" $ChopBitMapTrgFullPath\\$$BitMapRef{Trg}\n"
	);
	foreach $SrcRef (@{$$BitMapRef{Source}}) {
		&main::Output(
			" /$$SrcRef{ClDepth}$$SrcRef{Src}\n"
		);
	}
	&main::Output(
		"<<\n"
	);
	if ($$BitMapRef{Hdr}) {
		&main::Output(
			"\tcall <<\"MayRewriteHdr.bat\"\n",
			"\t\@echo off\n",
			"\tdiff \"$RTWTmpBitMapHdr\" \"$RTWBitMapHdr\" >NUL\n",
			"\tif errorlevel==1 copy \"$TmpBitMapHdr\" \"$BitMapHdr\"\n",
			"<<\n",
			"\tdel \"$TmpBitMapHdr\"\n",
		);
	}
	&main::Output(
		"\n"
	);
}

sub PMEndBitMap {

	&main::Output(
		"\n",
		"\n"
	);
}

sub PMStartResrc {
	my $Resrc=&main::Resrc;

	&main::Output(
		"# Resource ",$Resrc,"\n",
		"\n"
	);
}

sub PMResrcDepend {
	my @BldList=&main::BldList;	
	my @DepList=&main::DepList;

	&main::Output(
		"DEPEND="
	);
	foreach (@DepList) {
		&main::Output(
			" \\\n",
			"\t\"$_\""
		);
	}
	&main::Output(
		"\n",
		"\n"
	);
}

sub PMResrcBld {
	my $BaseResrc=&main::BaseResrc;
	my $Bld=&main::Bld;
	my @ChopRTWSysIncPaths=&main::Path_Chop(&main::Path_RltToWork(&main::SysIncPaths));
	my @ChopRTWUserIncPaths=&main::Path_Chop(&main::Path_RltToWork(&main::UserIncPaths));
	my @LangList=&main::LangList;
	my $Resrc=&main::Resrc;
	my $ResrcIsSys=&main::ResrcIsSys;
	my $RTWSrcPath=&main::Path_RltToWork(&main::SrcPath);
	my $ChopRTWSrcPath=&main::Path_Chop($RTWSrcPath);

	my $ResrcHdr=join '', &main::EPOCIncPath(), $BaseResrc, '.RSG';
	my $RTWResrcHdr=&main::Path_RltToWork($ResrcHdr);
	
	my $Lang;
	foreach $Lang (@LangList) {
		&main::Output(
			"\"\$(EPOCTRG$Bld)\\"
		);
		if ($ResrcIsSys) {
			&main::Output(
				"\$(DATADIR)\\"
			);
		}
		else {
			&main::Output(
				"\$(TRGDIR)\\"
			);
		}
		&main::Output(
			"$BaseResrc.r$Lang\" : \"$RTWSrcPath$Resrc\" \$(DEPEND)\n",
			"\tperl -S epocrc.pl -I \"$ChopRTWSrcPath\""
		);
		foreach (@ChopRTWUserIncPaths) {
			&main::Output(
				" -I \"$_\""
			);
		}
		&main::Output(
			" -I-"
		);
		foreach (@ChopRTWSysIncPaths) {
			&main::Output(
				" -I \"$_\""
			);
		}
		&main::Output(
			" -DLANGUAGE_$Lang -u \"$RTWSrcPath$Resrc\" ",
			"-o\$\@ -h\"$RTWSrcPath$BaseResrc.rs~\" -t\"\$(EPOCBLD$Bld)\"\n",
			"\tcall <<\"MayRewriteHdr.bat\"\n",
			"\t\@echo off\n",
			"\tdiff \"$RTWSrcPath$BaseResrc.rs~\" \"$RTWResrcHdr\" >NUL\n",
			"\tif errorlevel==1 copy \"$RTWSrcPath$BaseResrc.rs~\" \"$ResrcHdr\"\n",
			"<<\n",
			"\tdel \"$RTWSrcPath$BaseResrc.rs~\"\n",
			"\n"
		);
	}
}

sub PMEndResrc {

	&main::Output(
		"\n",
		"\n"
	);
}

sub PMStartAif {
	my $AifRef=&main::AifRef;

	&main::Output(
		"# Aif $$AifRef{Trg}\n",
		"\n"
	);
}

sub PMAifDepend {
	my @BldList=&main::BldList;	
	my @DepList=&main::DepList;

	&main::Output(
		"DEPEND="
	);
	foreach (@DepList) {
		&main::Output(
			" \\\n",
			"\t\"$_\""
		);
	}
	&main::Output(
		"\n",
		"\n"
	);
}

sub PMAifBld {
	my $AifRef=&main::AifRef;
	my $Bld=&main::Bld;
	my @ChopRTWSysIncPaths=&main::Path_Chop(&main::Path_RltToWork(&main::SysIncPaths));
	my @ChopRTWUserIncPaths=&main::Path_Chop(&main::Path_RltToWork(&main::UserIncPaths));

	my $BaseResrc=&main::Path_Split('Base',$$AifRef{Resrc});
	my $ChopRTWAifDir=&main::Path_Chop(&main::Path_RltToWork($$AifRef{Dir}));
	my $ChopBldPath=&main::Path_Chop(&main::BldPath);

	&main::Output(
		"\"\$(EPOCTRG$Bld)\\\$(TRGDIR)\\$$AifRef{Trg}\" : \"$$AifRef{Dir}$$AifRef{Resrc}\" \$(DEPEND)"
	);
	if (@{$$AifRef{BitMaps}}) { # bitmaps aren't essential
		my $BitMap;
		foreach $BitMap (@{$$AifRef{BitMaps}}) {
			&main::Output(
				" \"$$AifRef{Dir}$BitMap\""
			);
		}
	}
	&main::Output(
		"\n",
		"\tperl -S epocaif.pl -o\$@ ",
		"\"$ChopRTWAifDir\\$$AifRef{Resrc}\" ",
		"\\\n\t\t",
		"-t\"$ChopBldPath\" ",
		"\\\n\t\t"
	);
	if (@{$$AifRef{BitMaps}}) { 
		&main::Output(
			"-b\""
		);
		my $BitMap;
		foreach $BitMap (@{$$AifRef{BitMaps}}) {
			&main::Output(
				"\\\n\t\t/$$AifRef{ClDepth}$$AifRef{Dir}$BitMap"
			);
		}
		&main::Output(
			"\" \\\n\t\t"
		);
	}
	foreach (@ChopRTWUserIncPaths) {
		&main::Output(
			" -I \"$_\""
		);
	}
	&main::Output(
		" -I-"
	);
	foreach (@ChopRTWSysIncPaths) {
		&main::Output(
			" -I \"$_\""
		);
	}
	&main::Output(
		"\n",
		"\n"
	);
}

sub PMEndAif {

	&main::Output(
		"\n",
		"\n"
	);
}

sub PMStartSrc {
	my $Src=&main::Src;

	&main::Output(
		"# Source $Src\n",
		"\n"
	);
}

sub PMSrcDepend {
	my @BldList=&main::BldList;	
	my @DepList=&main::DepList;

	&main::Output(
		"DEPEND="
	);
	foreach (@DepList) {
		&main::Output(
		" \\\n\t\"$_\""
		);
	}
	&main::Output(
		"\n",
		"\n"
	);
	foreach (@BldList) {
		&main::Output(
			"DEPEND$_=\$(DEPEND)\n",
			"\n"
		);
	}
	&main::Output(
		"\n"
	);
}

sub PMSrcBldDepend {
	my $Bld=&main::Bld;
	my @DepList=&main::DepList;

	&main::Output(
		"DEPEND$Bld="
	);
	foreach (@DepList) {
		&main::Output(
			" \\\n\t\"$_\""
		);
	}
	&main::Output(
		"\n",
		"\n"
	);
}

sub PMEndSrcBld {
	my $BaseSrc=&main::BaseSrc;
	my $Bld=&main::Bld;
	my $Src=ucfirst lc &main::Src;
	my $SrcPath=&main::SrcPath;

	&main::Output(
		"\"\$(EPOCBLD$Bld)\\$BaseSrc.obj\" \"\$(EPOCBLD$Bld)\\$BaseSrc.sbr\" : \"$SrcPath$Src\" \$(DEPEND$Bld)\n",
		"\t\$(CL$Bld) /Fo\"\$(EPOCBLD$Bld)/\" /GF /c \"$SrcPath$Src\"\n",
		"\n",
#		assembler listing target - currently does nothing
		"LISTING$Bld$BaseSrc :\n",
		"\n",
		"\n"
	);
}

sub PMEndSrc {

	&main::Output(
		"\n",
		"\n"
	);
}

sub PMEndSrcList {
	if ($Win32Resrc) {
		my @BldList=&main::BldList;
		my @DepList=&main::Deps_GenDependsL($Win32Resrc);

		&main::Output(
			"# Win32 Resource $Win32Resrc\n",
			"\n",
			"DEPEND="
		);
		foreach (@DepList) {
			&main::Output(
				" \\\n\t\"$_\""
			);
		}
		&main::Output(
			"\n",
			"\n"
		);
	
		my $Bld;
		foreach $Bld (@BldList) {
			&main::Output(
				"\"\$(EPOCBLD$Bld)\\",&main::Path_Split('Base',$Win32Resrc),".res\" : \"$Win32Resrc\" \$(DEPEND)\n",
				"\trc /l 0x809 /fo\$\@ /i \"",&main::Path_Chop(&main::Path_Split('Path',$Win32Resrc)),"\" \"$Win32Resrc\"\n",
				"\n"
			);
		}
		&main::Output(
			"\n",
			"\n"
		);
	}
}

1;
