# CL_GCC.PM
#
# Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
#


package Cl_gcc;

my $GccPrefix='';
my $ToolPrefix='';
my $HelperLib='';
my %PlatOpt=(
	'Dlltool'=>'',
	'Entry'=>'-e',
	'Gcc'=>'',
	'Ld'=>'',
	'Petran'=>'',
	'Optimize'=>'-O'
);
my $Dlltool;
my $Archive;
my $Link;
my $Objcopy;

require Exporter;
@ISA=qw(Exporter);
@EXPORT=qw(
	PMHelp_Mmp

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
);


sub PMHelp_Mmp {
	print "// No additional keywords for this platform\n";
}

sub PMPlatProcessMmp (@) {
	my $MMPFILE=&main::MmpFile;

	# set up START MARM ... END block module variables
	my @MmpWarn=();
	my $Line;
	LINE: foreach $Line (@_) {
		my $LineInfo=shift @$Line;
		$_=shift @$Line;
		push @MmpWarn, "$LineInfo : Unrecognised Keyword \"$_\"\n";
	}

	undef $Line;
	if (@MmpWarn) {
		warn
			"\nMMPFILE \"$MMPFILE\"\n",
			"START .. END BLOCK WARNINGS(S)\n",
			@MmpWarn,
			"\n"
		;
	}
	undef @MmpWarn;
}

sub PMStartBldList {
	my $ABI=&main::ABI;
	my $AifStructRef=&main::AifStructRef;
	my @BaseResrcList=&main::BaseResrcList;
	my @BaseSysResrcList=&main::BaseSysResrcList;
	my $BaseTrg=&main::BaseTrg;
	my $BasicTrgType=&main::BasicTrgType;
	my $BitMapStructRef=&main::BitMapStructRef;
	my @BldList=&main::BldList;
	my @ChopRTWSysIncPaths=&main::Path_Chop(&main::Path_RltToWork(&main::SysIncPaths));
	my @ChopRTWUserIncPaths=&main::Path_Chop(&main::Path_RltToWork(&main::UserIncPaths));
	my @CompatibleABIs=&main::CompatibleABIs;
	my $DefFile=&main::DefFile;
	my $EPOCPath=&main::EPOCPath;
	my @LangList=&main::LangList;
	my $LinkAs=&main::LinkAs;
	my $LibPath=&main::LibPath;
	my @MacroList=&main::MacroList;
	my $Plat=&main::Plat;
	my $RTWASSPLinkPath=&main::Path_RltToWork(&main::ASSPLinkPath);
	my $RTWBldPath=&main::Path_RltToWork(&main::BldPath);
	my $RTWLibPath=&main::Path_RltToWork(&main::LibPath);
	my $RTWLinkPath=&main::Path_RltToWork(&main::LinkPath);
	my $RTWRelPath=&main::Path_RltToWork(&main::RelPath);
	my $RTWStatLinkPath=&main::Path_RltToWork(&main::StatLinkPath);
	my $Trg=&main::Trg;
	my $TrgType=&main::TrgType;
	my @UidList=&main::UidList;	


#	set up LinkAs
	$UidList[2]=~/^0x(.*)$/o;
	if ($1 ne '00000000') { # have to make sure than series of noughts in brackets doesn't appear in name for null uids
		$LinkAs=join '', &main::Path_Split('Base',$LinkAs),"[$1]",&main::Path_Split('Ext',$LinkAs);
	}

#	set up CompatibleABI lib path hash
	my %ABILibPath=();
	foreach (@CompatibleABIs) {
		$ABILibPath{$_}=&main::Path_Strip("$LibPath..\\$_\\");
	}
	my %ABIRTWLibPath=();
	foreach (@CompatibleABIs) {
		$ABIRTWLibPath{$_}=&main::Path_RltToWork($ABILibPath{$_});
	}

#	set up dlltool flag hash
	my %ABIDlltool=(
		ARMI=>'-m arm_interwork',
		ARM4=>'-m arm',
		THUMB=>'-m thumb'
	);

#	work out the flags for various platforms
	if ($ABI eq 'ARMI') {
		$PlatOpt{Gcc}='-march=armv4t -mthumb-interwork';
		$PlatOpt{Dlltool}=$ABIDlltool{ARMI};
	}
	elsif ($ABI eq 'ARM4') {
		$PlatOpt{Gcc}='-march=armv4';
#		allow thumb for ARM4 ABI where necessary
		unless (&main::PlatABI eq 'ARM4') {
			$PlatOpt{Gcc}.='t';
		}
		$PlatOpt{Dlltool}=$ABIDlltool{ARM4};
	}
	elsif ($ABI eq 'THUMB') {
		$GccPrefix='thumb-epoc-pe-';
		$PlatOpt{Entry}='--thumb-entry';
		$PlatOpt{Gcc}='-mthumb-interwork';
		$PlatOpt{Dlltool}=$ABIDlltool{THUMB};
#		$HelperLib='up_thumb.lib';
	}
	else {
		&main::FatalError("Platform module - ABI \"$ABI\" unrecognised");
	}
	$Dlltool=$ToolPrefix.'dlltool';
	$Archive=$ToolPrefix.'ar';
	$Link=$ToolPrefix.'ld';
	$Objcopy=$ToolPrefix.'objcopy';
		 
#	GCC needs a fully-qualified path
	&main::Output(
		"\n",
		'PATH=',&main::Path_Drive,$EPOCPath,"gcc\\bin;\$(PATH)\n",
	);

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
	foreach (@ChopRTWUserIncPaths) {
		&main::Output(
			" -I \"$_\""
		);
	}
	foreach (@ChopRTWSysIncPaths) {
		&main::Output(
			" -I \"$_\""
		);
	}
	&main::Output(
		"\n",
		"\n"
	);

	&main::Output(
		"GCCFLAGS=$PlatOpt{Gcc} \\\n",
		"\t\t      -c -nostdinc -Wall -Wno-ctor-dtor-privacy -Wno-unknown-pragmas\n",
		"\n"
	);

	&main::Output(
		"GCCDEFS ="
	);
	foreach(@MacroList) {
		&main::Output(
			" -D$_"
		);
	}
	&main::Output(
		" \$(USERDEFS)\n",
		"\n"
	);

	&main::Output(
		"EPOCBLD = $RTWBldPath #\n",
		"EPOCTRG = $RTWRelPath #\n",
		"EPOCLIB = $RTWLibPath #\n",
		"EPOCLINK = $RTWLinkPath #\n",
		"EPOCSTATLINK = $RTWStatLinkPath #\n",
		"EPOCASSPLINK = $RTWASSPLinkPath #\n",
		"\n"
	);
	foreach (@BldList) {
		&main::Output(
			"EPOCBLD$_ = \$(EPOCBLD)$_\n",
			"EPOCTRG$_ = \$(EPOCTRG)$_\n",
			"EPOCLIB$_ = \$(EPOCLIB)UREL\n",
			"EPOCLINK$_ = \$(EPOCLINK)UREL\n",
			"EPOCSTATLINK$_ = \$(EPOCSTATLINK)$_\n",
			"EPOCASSPLINK$_ = \$(EPOCASSPLINK)UREL\n",
			"\n"
		);
	}
	&main::Output(
		"\n"
	);

	foreach (@BldList) {
		&main::Output(
			"GCC$_ = ${GccPrefix}gcc"
		);
		if (/REL$/o) {
			&main::Output(
				      ' -s -fomit-frame-pointer ',
				      $PlatOpt{Optimize}
			);
		}
		elsif (/DEB$/o) {
			&main::Output(
				' -g'
			);
			unless (&main::SrcDbg) {
			    &main::Output(
			    	' ', $PlatOpt{Optimize}
			    );
			}
		}
		&main::Output(
			' $(GCCFLAGS)'
		);
		foreach (&main::MacroList($_)) {
			&main::Output(
				" -D$_"
			);
		}
		&main::Output(
			" \$(GCCDEFS)\n"
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
			"\t\"\$(EPOCTRG$_)\\$Trg\""
		);

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


	&main::Output(	# ALL comes after REL: because first target in makefile is the default
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
				"\t\"\$(EPOCTRG$_)\\$$BitMapRef{Trg}\""
			);
		}
		undef $BitMapRef;

		my $BaseResrc;
		foreach $BaseResrc (@BaseSysResrcList,@BaseResrcList) { # do sys resrcs first always
			my $Lang;
			foreach $Lang (@LangList) {
				&main::Output(	# must come before main target because source for target will depend on the
					" \\\n",						# *.rsg file in $EPOCIncPath
					"\t\"\$(EPOCTRG$_)\\$BaseResrc.R$Lang\""
				);
			}
		}
		undef $BaseResrc;

		my $AifRef;
		foreach $AifRef (@$AifStructRef) {
			&main::Output(
				" \\\n",
				"\t\"\$(EPOCTRG$_)\\$$AifRef{Trg}\""
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
					" \"\$(EPOCLIB)UREL\\$BaseTrg.LIB\""
				);
				foreach (@CompatibleABIs) {
					&main::Output(
						" \"$ABILibPath{$_}UREL\\$BaseTrg.LIB\""
					);
				}
				&main::Output(
					"\n"
				);
			}
			else {
				&main::Output(
					"\n",
					"\t\@echo WARNING: Not attempting to create any import libraries.\n",
					"\t\@echo When exports are frozen in \"$DefFile\", regenerate Makefile.\n"
				);
			}
		}
		else {
			&main::Output(
				"\n",
				"\t\@echo Not attempting to create \"\$(EPOCLIB)UREL\\$BaseTrg.LIB\"\n",
				"\t\@echo from frozen .DEF file, since EXPORTUNFROZEN specified.\n"
			);
		}
		&main::Output(
			"\n",
			"\n",
			"# REAL TARGET - LIBRARY\n",
			"\n",
			"\"\$(EPOCLIB)UREL\\$BaseTrg.LIB\" : \"$DefFile\" MAKEWORKLIBRARY\n",
			"\t$Dlltool $PlatOpt{Dlltool} --output-lib \"\$(EPOCLIB)UREL\\$BaseTrg.LIB\" \\\n",
			"\t\t--def \"",&main::Path_RltToWork($DefFile),"\" \\\n",
			"\t\t--dllname \"$LinkAs\" \n"
		);
		foreach (@CompatibleABIs) {
			&main::Output(
				"\n",
				"\"$ABILibPath{$_}UREL\\$BaseTrg.LIB\" : \"$DefFile\" MAKEWORKLIBRARY\n",
				"\t$Dlltool $ABIDlltool{$_} --output-lib \"$ABIRTWLibPath{$_}UREL\\$BaseTrg.LIB\" \\\n",
				"\t\t--def \"",&main::Path_RltToWork($DefFile),"\" \\\n",
				"\t\t--dllname \"$LinkAs\" \n"
			);
		}
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
			"\t-\$(ERASE) \"\$(EPOCLIB)UREL\\$BaseTrg.*\"\n"
		);
		foreach (@CompatibleABIs) {
			&main::Output(
				"\t-\$(ERASE) \"$ABILibPath{$_}UREL\\$BaseTrg.*\"\n"
			);
		}
	}
#regression hack since link path is currently the same as release path in some cases
#so don't put out the targets for making the path here if they're the same
	&main::Output(
		"\n",
		"MAKEWORKLIBRARY :"
	);
	if ($DefFile) {
		&main::Output(
			" \"${LibPath}UREL\""
		);
		foreach (@CompatibleABIs) {
			&main::Output(
				" \"$ABILibPath{$_}UREL\""
			);
		}
	}
	&main::Output(
		"\n",
		"\n"
	);
	if ($DefFile) {
		unless ($LibPath eq &main::RelPath) {
			&main::Output(
				"\"${LibPath}UREL\" :\n",
				"\t\@perl -S emkdir.pl \"${LibPath}UREL\"\n",
				"\n"
			);
		}
		foreach (@CompatibleABIs) {
			&main::Output(
				"\"$ABILibPath{$_}UREL\" :\n",
				"\t\@perl -S emkdir.pl \"$ABILibPath{$_}UREL\"\n",
				"\n"
			);
		}
		&main::Output(
			"\n"
		);
	}

	&main::Output(
		"\n"
	);
}


sub PMBld {

	my $AifStructRef=&main::AifStructRef;
	my @ASSPLibList=&main::ASSPLibList;
	my @BaseResrcList=&main::BaseResrcList;
	my @BaseSrcList=&main::BaseSrcList;
	my @BaseSysResrcList=&main::BaseSysResrcList;
	my $BaseTrg=&main::BaseTrg;
	my $BitMapStructRef=&main::BitMapStructRef;
	my $Bld=&main::Bld;
	my $ChopBldPath=&main::Path_Chop(&main::BldPath);
	my @CompatibleABIs=&main::CompatibleABIs;
	my $DefFile=&main::DefFile;
	my $EPOCIncPath=&main::EPOCIncPath;
	my $EPOCLocPath=&main::EPOCPath."Localisation\\";
	my $FirstLib=&main::FirstLib;
	my $BasicTrgType=&main::BasicTrgType;
	my @LangList=&main::LangList;
	my @LibList;
	my $LibPath=&main::LibPath;
	my $LinkAs=&main::LinkAs;
	my $ChopRelPath=&main::Path_Chop(&main::RelPath);
	my $RelPath=&main::RelPath;
	my @StatLibList=&main::StatLibList;
	my $StatLinkPath=&main::StatLinkPath;
	my $Trg=&main::Trg;
	my $TrgType=&main::TrgType;
	my @UidList=&main::UidList;

	if ($Bld =~ /DEB/) {
		@LibList = &main::DebugLibList;
	} else {
		@LibList = &main::LibList;
	}

#	set up $LinkAs
	$UidList[2]=~/^0x(.*)$/o;
	if ($1 ne '00000000') {	# have to make sure than series of noughts in brackets doesn't appear in name for null uids
		$LinkAs=join '', &main::Path_Split('Base',$LinkAs),"[$1]",&main::Path_Split('Ext',$LinkAs);
	}


	# REAL TARGETS
	#-------------
	&main::Output(
		"# REAL TARGET - BUILD VARIANT $Bld\n",
		"\n"
	);

#	releasables
	&main::Output(
		"RELEASEABLES= \\\n",
		"\t\"$RelPath$Trg\""
	);
	if ($BasicTrgType=~/^(DLL|EXE)$/o) {
		&main::Output(
			" \\\n\t\"$RelPath$Trg.MAP\""
		);
	}
	my $BitMapRef;
	foreach $BitMapRef (@$BitMapStructRef) {
		&main::Output(
			" \\\n\t\"$RelPath$$BitMapRef{Trg}\""
		);
		if ($$BitMapRef{Hdr}) {
			&main::Output(
				" \\\n\t\"$EPOCIncPath", &main::Path_Split('Base', $$BitMapRef{Trg}), ".MBG\""
			);
		}
	}
	my $BaseResrc;
	foreach $BaseResrc (@BaseSysResrcList, @BaseResrcList) {
		my $Lang;
		foreach $Lang (@LangList) {
			&main::Output(
				" \\\n\t\"$RelPath$BaseResrc.R$Lang\""
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
			" \\\n\t\"$RelPath$$AifRef{Trg}\""
		);
	}
	if (-e $DefFile) { # effectively "if project frozen ..."
		&main::Output(
			" \\\n\t\"$LibPath$BaseTrg.LIB\""
		);
		my $ABI;
		foreach $ABI (@CompatibleABIs) {
			&main::Output(
				" \\\n\t\"", &main::Path_Strip("$LibPath..\\..\\$ABI\\UREL\\"), "$BaseTrg.LIB\""
			);
		}
	}
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
		"\n",
		"CLEANRELEASE$Bld : \n",
		"\t-\$(ERASE) \$(RELEASEABLES)\n",
		"\n"
	);


	&main::Output(
		"MAKEWORK$Bld : MAKEWORKBUILD$Bld MAKEWORKRELEASE$Bld\n",
		"\n",
		"MAKEWORKBUILD$Bld : \"$ChopBldPath\"\n",
		"\n",
		"MAKEWORKRELEASE$Bld : \"$ChopRelPath\"\n",
		"\n"
	);
	foreach ($ChopBldPath, $ChopRelPath) {
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

	&main::Output(
		"LIBS="
	);
	if ($HelperLib) {
		&main::Output(
			" \\\n",
			"\t\"\$(EPOCSTATLINK$Bld)\\$HelperLib\""
		);
	}
	foreach (@StatLibList) {
		&main::Output(
			" \\\n",
			"\t\"\$(EPOCSTATLINK$Bld)\\$_\""
		);
	}
	foreach (@ASSPLibList) {
		&main::Output(
			" \\\n",
			"\t\"\$(EPOCASSPLINK$Bld)\\$_\""
		);
	}
	foreach (@LibList) {
		&main::Output(
			" \\\n",
			"\t\"\$(EPOCLINK$Bld)\\$_\""
		);
	}
	&main::Output(
		"\n",
		"\n"
	);

	&main::Output(
		"\"\$(EPOCTRG$Bld)\\$Trg\" : \"\$(EPOCBLD$Bld)\\$BaseTrg.in\""
	);
	if (-e $DefFile) { # effectively "if project frozen ..."
		&main::Output(
			" \"$DefFile\""
		);
	}
	if ($BasicTrgType=~/^(EXE|DLL)$/o) {
		&main::Output(
			" \"\$(EPOCSTATLINK$Bld)\\$FirstLib\" \"\$(EPOCSTATLINK$Bld)\\EGCC.LIB\""
		);
	}
	if ($BasicTrgType=~/^(DLL)$/o) {	# Add the DLL stub
		&main::Output(
			" \"\$(EPOCSTATLINK$Bld)\\EDLLSTUB.LIB\""
		);
	}
	&main::Output(
		" \$(LIBS)\n"
	);

	if ($BasicTrgType=~/^DLL$/o || $TrgType=~/^EXEDLL$/o) {

#		generate a .DEF file from the objects and static libraries
		&main::Output(
			"\t$Dlltool $PlatOpt{Dlltool} --output-def \"\$(EPOCBLD$Bld)\\$BaseTrg.inf\" \"\$(EPOCBLD$Bld)\\$BaseTrg.in\""
		);
		foreach (@StatLibList) {
			&main::Output(
				" \"\$(EPOCSTATLINK$Bld)\\$_\""
			);
		}
		&main::Output(
			"\n"
		);

#		reorder the .DEF file taking frozen exports into account if there are any
		&main::Output(
#			call perl on the script here so nmake will die if there are errors - this doesn't happen if calling perl in a batch file
			"\tperl -S makedef.pl -Deffile \"\$(EPOCBLD$Bld)\\$BaseTrg.inf\""
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
				&main::Output(
					" -$Num $Ordinal"
				);
				$Num++;
			}
		}
		&main::Output(
			" \"\$(EPOCBLD)$BaseTrg.def\"\n"
		);

#		delete the unordered definition file
		&main::Output(
			"\tdel \"\$(EPOCBLD$Bld)\\$BaseTrg.inf\"\n"
		);

#		generate an export object from the ordered .DEF file
		&main::Output(
			"\t$Dlltool $PlatOpt{Dlltool} --def \"\$(EPOCBLD)$BaseTrg.def\" \\\n",
			"\t\t--output-exp \"\$(EPOCBLD$Bld)\\$BaseTrg.exp\" \\\n",
			"\t\t--dllname \"$LinkAs\""
		);
		if (&main::ExportUnfrozen) {
			&main::Output(
				"\\\n",
				"\t\t--output-lib \"\$(EPOCLIB)UREL\\$BaseTrg.LIB\""
			);
		}
		&main::Output(
			"\n"
		);
	}

#	call ld to do base relocations (and dll exports)
	if ($BasicTrgType=~/^(DLL|EXE)/o) {
		&main::Output(
			"\t$Link $PlatOpt{Ld} -s"
			);	
		if ($BasicTrgType=~/^DLL$/o) {
			&main::Output(
				" $PlatOpt{Entry} _E32Dll -u _E32Dll \"\$(EPOCBLD$Bld)\\$BaseTrg.exp\" --dll \\\n"
			);
		}
		elsif ($BasicTrgType=~/^EXE$/o) {
			&main::Output(
				" $PlatOpt{Entry} _E32Startup -u _E32Startup \\\n"
			);
		}
		&main::Output(
			"\t\t--base-file \"\$(EPOCBLD$Bld)\\$BaseTrg.bas\" -o \"\$(EPOCBLD$Bld)\\$Trg\" \\\n",
			"\t\t\"\$(EPOCSTATLINK$Bld)\\$FirstLib\" --whole-archive \"\$(EPOCBLD$Bld)\\$BaseTrg.in\" \\\n",
			"\t\t--no-whole-archive"
		);
		if ($BasicTrgType=~/^DLL$/o) { # Add the DLL stub
			&main::Output(
				" \$(EPOCSTATLINK$Bld)\\EDLLSTUB.LIB"
			);
		}
		if ($BasicTrgType=~/^(DLL|EXE)/o) { # Add the GCC helper fns
			&main::Output(
				 " \$(EPOCSTATLINK$Bld)\\EGCC.LIB"
			);
		}
		&main::Output(
			" \$(LIBS) \$(USERLDFLAGS)\n"
		);
#		--whole-archive is required here apparently because of a bug in the gcc toolchain
#		the flag can probably be removed with a later version of gcc

#		delete temporary files
		if ($BasicTrgType=~/^DLL$/o || $TrgType=~/^EXEDLL$/o) {
			&main::Output(
				"\tdel \"\$(EPOCBLD$Bld)\\$BaseTrg.exp\"\n"
			);
		}
		&main::Output(
			"\tdel \"\$(EPOCBLD$Bld)\\$Trg\"\n"
		);

#		call dlltool to do base relocations (and dll exports)
		&main::Output(
			"\t$Dlltool $PlatOpt{Dlltool} \\\n"
		);
		if ($BasicTrgType=~/^DLL$/o || $TrgType=~/^EXEDLL$/o) {
			&main::Output(
				"\t\t--def \"\$(EPOCBLD)$BaseTrg.def\" \\\n",
				"\t\t--dllname \"$LinkAs\" \\\n"
			);
		}
		&main::Output(
			"\t\t--base-file \"\$(EPOCBLD$Bld)\\$BaseTrg.bas\" \\\n",
			"\t\t--output-exp \"\$(EPOCBLD$Bld)\\$BaseTrg.exp\" \n"
		);

#		delete temporary files
		&main::Output(
			"\tdel \"\$(EPOCBLD$Bld)\\$BaseTrg.bas\"\n"
		);

#		call ld to link the target
		&main::Output(
			"\t$Link $PlatOpt{Ld}"
		);
		if ($Bld=~/^U?REL$/o) {
			&main::Output(
				" -s"
			);
		}
		if ($BasicTrgType=~/^DLL$/o) {
			&main::Output(
				" $PlatOpt{Entry} _E32Dll -u _E32Dll --dll \\\n"
			);
		}
		elsif ($BasicTrgType=~/^EXE$/o) {
			&main::Output(
				" $PlatOpt{Entry} _E32Startup -u _E32Startup \\\n"
			);
		}
		&main::Output(
			"\t\t\"\$(EPOCBLD$Bld)\\$BaseTrg.exp\" \\\n",
			"\t\t-Map \"\$(EPOCTRG$Bld)\\$Trg.map\" -o \"\$(EPOCBLD$Bld)\\$Trg\" \\\n",
			"\t\t\"\$(EPOCSTATLINK$Bld)\\$FirstLib\" --whole-archive \"\$(EPOCBLD$Bld)\\$BaseTrg.in\" \\\n",
			"\t\t--no-whole-archive"
		);
		if ($BasicTrgType=~/^DLL$/o) { # Add the DLL stub
			&main::Output(
				" \$(EPOCSTATLINK$Bld)\\EDLLSTUB.LIB"
			);
		}
		if ($BasicTrgType=~/^(DLL|EXE)/o) { # Add the GCC helper fns
			&main::Output(
				 " \$(EPOCSTATLINK$Bld)\\EGCC.LIB"
			);
		}
		&main::Output(
			" \$(LIBS) \$(USERLDFLAGS)\n"
		);
#		--whole-archive is required here apparently because of a bug in the gcc toolchain
#		the flag can probably be removed with a later version of gcc

#		delete temporary files
		&main::Output(
			"\tdel \"\$(EPOCBLD$Bld)\\$BaseTrg.exp\"\n"
		);

		if ($Bld=~/^U?DEB$/o) {
			&main::Output(
				"\t$Objcopy -X \"\$(EPOCBLD$Bld)\\$Trg\" \"\$(EPOCTRG$Bld)\\$BaseTrg.sym\"\n"
			);
		}

		&main::Output(
			"\tpetran $PlatOpt{Petran} \"\$(EPOCBLD$Bld)\\$Trg\" \$\@ \\\n",
			"\t\t"
		);
		if (&main::AllowDllData) {
			&main::Output(
				' -allow'
			);
		}
		if (not &main::CallDllEntryPoints) {
			&main::Output(
				' -nocall'
			);
		}
		if (&main::DataLinkAddress) {
			&main::Output(
				' -datalinkaddress ',&main::DataLinkAddress
			);
		}
		if (&main::FixedProcess) {
			&main::Output(
				' -fixed'
			);
		}
		if (&main::HeapSize) {
			my %HeapSize=&main::HeapSize;
			&main::Output(
				' -heap ',$HeapSize{Min},' ',$HeapSize{Max}
			);
		}
		if (&main::ProcessPriority) {
			&main::Output(
				' -priority ',&main::ProcessPriority
			);
		}
		if (&main::StackSize) {
			&main::Output(
				' -stack ',&main::StackSize
			);
		}
		my $i=1;
		foreach (@UidList) {
			&main::Output(
				" -uid$i $_"
			);
			$i++;
		}
		&main::Output(
			"\n"
		);
		&main::Output(
			"\tdel \"\$(EPOCBLD$Bld)\\$Trg\"\n"
		);
	}
	elsif ($BasicTrgType=~/^LIB$/o) {
		&main::Output(
			"\tcopy \"\$(EPOCBLD$Bld)\\$BaseTrg.in\" \"\$(EPOCSTATLINK$Bld)\\$Trg\"\n"
		);
	}

	&main::Output(
		"\n"
	);


	# TARGET *.IN
	#------------
	&main::Output(
		"OBJECTS="
	);
	foreach (@BaseSrcList) {
		&main::Output(
			" \\\n\t\$(EPOCBLD$Bld)\\$_.o"
		);	# would have quotes round these for longfilenames if ar didn't complain.  OK because not referred to as having quotes
	}
	&main::Output(
		"\n",
		"\n"
	);
	&main::Output(
		"\"\$(EPOCBLD$Bld)\\$BaseTrg.in\" : \$(OBJECTS)\n",	# MUST have quotes round .in file else file not thought of as a depend
		"\tif exist \$\@ del \$\@\n",
		"\tcd \"\$(EPOCBLD$Bld)\"\n",
		"\t$Archive -M < <<\n",
		"CREATE \$(\@F)\n",
		"ADDMOD \$(**F)\n",
		"SAVE\n",
		"END\n",
		"<<\n",
		"\tcd \"\$(MAKEDIR)\"\n",	# cd back to the directory where NMAKE was invoked
		"\n\n"
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

	my $BitMapHdr=join('', &main::EPOCIncPath, &main::Path_Split('Base', $$BitMapRef{Trg}), '.mbg');
	my $RTWBitMapHdr=&main::Path_RltToWork($BitMapHdr);
	my $TmpBitMapHdr=join('', &main::BldPath, &main::Path_Split('Base', $$BitMapRef{Trg}), '.mbg');
	my $RTWTmpBitMapHdr=&main::Path_RltToWork($TmpBitMapHdr);

	&main::Output(
		"\"\$(EPOCTRG$Bld)\\$$BitMapRef{Trg}\" :"
	);
	my $SrcRef;
	foreach $SrcRef (@{$$BitMapRef{Source}}) {
		&main::Output(
			" \"$$SrcRef{Src}\""
		);
	}
	&main::Output(
		"\n",
		"\tbmconv <<\n",
		" /q"
	);
	if ($$BitMapRef{Hdr}) {
		&main::Output(
			" /h$TmpBitMapHdr"
		);
	}
	&main::Output(
		" \$(EPOCTRG$Bld)\\$$BitMapRef{Trg}\n"
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
	my @LangList=&main::LangList;
	my $Resrc=&main::Resrc;
	my $SrcPath=&main::SrcPath;
	my $RTWSrcPath=&main::Path_RltToWork($SrcPath);
	my $ChopRTWSrcPath=&main::Path_Chop($RTWSrcPath);

	my $ResrcHdr=join '', &main::EPOCIncPath(), $BaseResrc, '.RSG';
	my $RTWResrcHdr=&main::Path_RltToWork($ResrcHdr);

	my $Lang;
	foreach $Lang (@LangList) {
		&main::Output(
			"\"\$(EPOCTRG$Bld)\\$BaseResrc.R$Lang\": \"$SrcPath$Resrc\" \$(DEPEND)\n",
			"\tperl -S epocrc.pl -I \"$ChopRTWSrcPath\" \$(INCDIR) -DLANGUAGE_$Lang -u \"$RTWSrcPath$Resrc\" ",
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
		"\"\$(EPOCTRG$Bld)\\$$AifRef{Trg}\" : \"$$AifRef{Dir}$$AifRef{Resrc}\" \$(DEPEND)"
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

	my $RTWSrcPath=&main::Path_RltToWork($SrcPath);

	# Use GCC trick to get assembler source files preprocessed with CPP
	$Src =~ s/\.s$/.S/i;

	&main::Output(
		"\"\$(EPOCBLD$Bld)\\$BaseSrc.o\": \"$SrcPath$Src\" \$(DEPEND$Bld)\n",
		"\t\$(GCC$Bld) -I \"$RTWSrcPath\" \$(INCDIR) -o \$\@ \"$RTWSrcPath$Src\"\n",
		"\n",
#		generate an assembly listing target too
		"LISTING$Bld$BaseSrc : MAKEWORKBUILD$Bld \"\$(EPOCBLD$Bld)\\$BaseSrc.lis\"\n",
		"\n",
		"\"\$(EPOCBLD$Bld)\\$BaseSrc.lis\": \"$SrcPath$Src\" \$(DEPEND$Bld)\n",
		"\t\$(GCC$Bld) -Wa,-adln -I \"$RTWSrcPath\" \$(INCDIR) -o nul: \"$RTWSrcPath$Src\" > \$\@\n",
		"\tcopy \$\@ \"$SrcPath$BaseSrc.lis\"\n",
		"\n"
	);
}

sub PMEndSrc {

	&main::Output(
		"\n",
		"\n"
	);
}

1;
