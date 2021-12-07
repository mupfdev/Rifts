# Trgtype.pm
#
# Copyright (c) 2000 Symbian Ltd.  All rights reserved.
#


# this package controls target types known to the build system
#
# To add new types to the system, simply add an entry to the %Types data structure.
# Look at the existing types for an appropriate example
#

package Trgtype;

require Exporter;
@ISA=qw(Exporter);
@EXPORT=qw(
	Trg_GetL
	Trg_List
);

use Genutl;

my %Types=(
	ANI=>{
		'Exports'=>{
			MARM=>['CreateCAnimDllL__Fv'],
			WINS=>['?CreateCAnimDllL@@YAPAVCAnimDll@@XZ'],
		},
		UID2=>'0x10003b22',
	},
	APP=>{
		'Exports'=>{
			MARM=>['NewApplication__Fv'],
			WINS=>['?NewApplication@@YAPAVCApaApplication@@XZ'],
		},
		NeedUID3=>1,
		UID2=>'0x100039ce',
	},
	CTL=>{
		'Exports'=>{
			MARM=>['CreateControlL__FRC7TDesC16'],
			WINS=>['?CreateControlL@@YAXABVTDesC16@@@Z'],
		},
		UID2=>'0x10003a34',
	},
	CTPKG=>{
		'Exports'=>{
			MARM=>['NewComponentTestLC__FR11CDataLoggerR22MComponentTestObserver'],
			WINS=>['?NewComponentTestLC@@YAPAVCComponentTester@@AAVCDataLogger@@AAVMComponentTestObserver@@@Z'],
		},
		Path=>'system\Apps\testbed\tests',
		UID2=>'0x10009DF0',
	},
	DLL=>{
		NeedDeffile=>1,
	},	
	EPOCEXE=>{
		Basic=>'EXEDLL',
		'Exports'=>{
			WINS=>['?WinsMain@@YAHXZ'],
		},
	},
	EXE=>{
		Basic=>'EXE',
	},
	EXEDLL=>{
		Basic=>'EXEDLL',
		NeedDeffile=>1,
	},
#	FEP=>{
#		'Exports'=>{
#			MARM=>['NewFepL__FR7CCoeEnvRC7TDesC16RC17CCoeFepParameters','SynchronouslyExecuteSettingsDialogL__FR7CCoeEnvRC7TDesC16','Reserved_1__Fv','Reserved_2__Fv','Reserved_3__Fv','Reserved_4__Fv','Reserved_5__Fv','Reserved_6__Fv','Reserved_7__Fv','Reserved_8__Fv'],
#			WINS=>['?NewFepL@@YAPAVCCoeFep@@AAVCCoeEnv@@ABVTDesC16@@ABVCCoeFepParameters@@@Z','?SynchronouslyExecuteSettingsDialogL@@YAXAAVCCoeEnv@@ABVTDesC16@@@Z','?Reserved_1@@YAXXZ','?Reserved_2@@YAXXZ','?Reserved_3@@YAXXZ','?Reserved_4@@YAXXZ','?Reserved_5@@YAXXZ','?Reserved_6@@YAXXZ','?Reserved_7@@YAXXZ','?Reserved_8@@YAXXZ'],
#		},
#		UID2=>'0x10005e32',
#	},
	FSY=>{
		'Exports'=>{
			MARM=>['CreateFileSystem'],
			WINS=>['CreateFileSystem'],
		},
		UID2=>'0x100039df',
	},
	KDLL=>{
		FirstLib=>'EDEV.LIB',
		Kernel=>1,
	},
	KEXT=>{
		FirstLib=>'EEXT.LIB',
		Kernel=>1,
	},
	KLIB=>{
		Basic=>'LIB',
		Kernel=>1,
	},
	LDD=>{
		FirstLib=>'EDEV.LIB',
		Kernel=>1,
		'Exports'=>{
			MARM=>['CreateLogicalDevice__Fv'],
			WINS=>['?CreateLogicalDevice@@YAPAVDLogicalDevice@@XZ'],
		},
		UID2=>'0x100000af',
	},
	LIB=>{
		Basic=>'LIB',
	},
	ECOMIIC=>{
		'Exports'=>{
			MARM=>['ImplementationGroupProxy__FRi'],
			WINS=>['?ImplementationGroupProxy@@YAPBUTImplementationProxy@@AAH@Z'],
		},
		Path=>'System\Libs\Plugins',
		UID2=>'0x10009D8D',
	},
	MDA=>{
		'Exports'=>{
			MARM=>['NewMediaLibraryL__Fv'],
			WINS=>['?NewMediaLibraryL@@YAPAVCMdaLibrary@@XZ'],
		},
		UID2=>'0x1000393f',
	},
	MDL=>{
		'Exports'=>{
			MARM=>['CreateRecognizer__Fv'],
			WINS=>['?CreateRecognizer@@YAPAVCApaDataRecognizerType@@XZ'],
		},
		UID2=>'0x10003a19',
	},
	NOTIFIER=>{
		'Exports'=>{
			MARM=>['NotifierArray__Fv'],
			WINS=>['?NotifierArray@@YAPAV?$CArrayPtr@VMEikSrvNotifierBase@@@@XZ'],
		},
		Path=>'System\Notifiers',
		UID2=>'0x10005522',
	},
	OPX=>{
		'Exports'=>{
			MARM=>['NewOpxL__FR6OplAPI','Version__Fv'],
			WINS=>['?NewOpxL@@YAPAVCOpxBase@@AAVOplAPI@@@Z','?Version@@YAIXZ'],
		},
		UID2=>'0x10003a7b',
	},
	PDD=>{
		FirstLib=>'EDEV.LIB',
		Kernel=>1,
		'Exports'=>{
			MARM=>['CreatePhysicalDevice__Fv'],
			WINS=>['?CreatePhysicalDevice@@YAPAVDPhysicalDevice@@XZ'],
		},
		UID2=>'0x100039d0',
	},
	PDL=>{
		'Exports'=>{
			MARM=>['NewPrinterDeviceL__Fv'],
			WINS=>['?NewPrinterDeviceL@@YAPAVCPrinterDevice@@XZ'],
		},
		UID2=>'0x10003b1c',
	},
	RDL=>{
		'Exports'=>{
			MARM=>['CreateRecognizer__Fv'],
			WINS=>['?CreateRecognizer@@YAPAVCApaFileRecognizerType@@XZ'],
		},
		UID2=>'0x10003a37',
	},
	VAR=>{
		'Exports'=>{
			MARM=>['VariantInitialise__Fv'],
		},
		FirstLib=>'EVAR.LIB',
		Kernel=>1,
	},
	WLOG=>{
		'Exports'=>{
			MARM=>['CreateDebugLog__FiR7TDesC16'],
			WINS=>['?CreateDebugLog@@YAPAVCDebugLogBase@@HAAVTDesC16@@@Z'],
		},
		UID2=>'0x10003b23',
	},
);

sub Trg_GetL ($$$) {
#	takes target type, followed by a ref to a data structure
#	to fill with exports, second UID and default targetpath, etc.,
#
#	dies upon error

	my ($Candidate, $TrgHash_ref)=@_;
	$Candidate= uc $Candidate;

#	Is type in our list?
	unless (defined $Types{$Candidate}) {
		die "ERROR: Target type \"$Candidate\" not supported\n";
	}

#	Get the data
	my %TrgHash=%{$Types{$Candidate}};


#	Set the defaults
	$TrgHash{Name}=$Candidate;

	
	unless ($TrgHash{Basic}) {
		$TrgHash{Basic}='DLL';
	}

	unless ($TrgHash{FirstLib}) {
		$TrgHash{FirstLib}='';
	}

	unless ($TrgHash{Kernel}) {
		$TrgHash{Kernel}=0;
	}

	unless ($TrgHash{Exports}{MARM}) {
		$TrgHash{Exports}{MARM}=[];
	}
	else {
		unless (@{$TrgHash{Exports}{MARM}}<=2) {
			die "INTERNAL ERROR: Too many MARM exports defined for type \"$TrgHash{Name}\" in Trgtype.pm\n";
		}
	}

	unless ($TrgHash{Exports}{WINS}) {
		$TrgHash{Exports}{'WINS'}=[];
	}
	else {
		unless (@{$TrgHash{Exports}{WINS}}<=2) {
			die "INTERNAL ERROR: Too many WINS exports defined for type \"$TrgHash{Name}\" in Trgtype.pm\n";
		}
	}


	unless ($TrgHash{NeedDeffile}) {
		$TrgHash{NeedDeffile}=0;
	}

	unless ($TrgHash{NeedUID3}) {
		$TrgHash{NeedUID3}=0;
	}

	unless ($TrgHash{Path}) {
		$TrgHash{Path}='';
	}
	else {
		# apply terminating backslash
		$TrgHash{Path}=~s-^(.*[^\\])$-$1\\-o;
		# apply Z drive
		$TrgHash{Path}="Z\\$TrgHash{Path}";
	}

	unless ($TrgHash{UID2}) {
		$TrgHash{UID2}='';
	}
	else {
		$TrgHash{UID2}=&Genutl_AnyToHex($TrgHash{UID2});
		unless (defined $TrgHash{UID2}) {
			die "INTERNAL ERROR: UID2 badly defined for type \"$TrgHash{Name}\" in Trgtype.pm\n";
		}
	}

	
#	Pass the data
	%{$TrgHash_ref}=%TrgHash;
}

sub Trg_List () {
#	returns a list of known poly types

	sort keys %Types;
}


1;
