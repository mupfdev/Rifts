# PREPFILE.PM
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
#


# module for preprocessing makmake-style project files


package Prepfile;

require Exporter;
@ISA=qw(Exporter);

@EXPORT=qw(
	Prepfile_SetVerbose Prepfile_SetUpperCase Prepfile_ProcessL
);


use Checkgcc;
use Pathutl;

my %Mode=(
	Verbose=>0,
	UpperCase=>0
);

sub Prepfile_SetVerbose () {
	$Mode{Verbose}=1;
}

sub Prepfile_SetUpperCase () {
	$Mode{UpperCase}=1;
}

sub Prepfile_ProcessL ($$@) {
# use the C++ preprocessor to process a file.  The function fills the data structure specified
# by the first argument, an array reference, according to the contents of the second argument -
# a filehandle.  Any other arguments are assumed to be MACROS and are defined for preprocessing.

	my ($ArrayRef,$FILE,@Macros)=@_;
	die "\nERROR: Project File \"$FILE\" not found\n" unless -e $FILE;

	my @CppCall;
	push @CppCall, 'CPP.EXE -undef';

	my $Macro;
	# add CL macros to the CPP call for preprocessing of the file
	foreach $Macro (@Macros) {
		$Macro=uc $Macro;					 # add the underscores so we can tell what has been
		push @CppCall, "-D $Macro=___$Macro"; # expanded and remove the space CPP puts in most of the time
	}
	# all macros made upper case and suppress user-expansion of macros for nefarious purposes

	push @CppCall, join '',"\"",&Path_RltToWork($FILE),"\"";
	if ($Mode{'Verbose'}) {
		print "@CppCall\n";
	}
	my $CPPPIPE;
	open CPPPIPE,"@CppCall |" or die "ERROR: Can't invoke CPP.EXE\n";
	undef @CppCall;


	# read the processed output
	#--------------------------

	my $LineNum=0;
	my $FileName;
	while (<CPPPIPE>) {

		# skip blank lines
		if (/^\s*$/o) {
			$LineNum++;
			next;
		}

		my @Tmp=();

	    # Process the file information lines that cpp inserts.
		# (note that we don't currently do anything with the
		# number cpp sometimes puts out after the filename -
		# it's something to do with inclusion nesting levels)
		if (/^# (\d+) "(.*)"( \d+)?/o) {
			$LineNum = scalar $1;
			my $CurFile=$2;
			$CurFile=~s-\\\\-\\-go;
			$CurFile=&Path_MakeAbs($FILE, $CurFile);
			@Tmp=('#', $CurFile);
			push @{$ArrayRef}, [ @Tmp ];
			next;
		}

		# Process file data
		push @Tmp, $LineNum;
		# get rid of the space that cpp puts in most of the time after macro expansion (CPP help doesn't say exactly when!)
		# don't upper case everything until you've done this.
		foreach $Macro (@Macros) {
			s/___$Macro /$Macro/g;
		}
		while (/("([^"\t\n\r\f]+)"|([^ "\t\n\r\f]+))/go) {
			push @Tmp, $2 ? $2 : $3;
		}
		push @{$ArrayRef}, [ @Tmp ];
		$LineNum++;
	}		

	if ($Mode{UpperCase}) {
#		upper-case all the data
		my $Line;
		my $Item;
		foreach $Line (@{$ArrayRef}) {
			foreach $Item (@$Line) {
				$Item=uc $Item;
			}
		}
	}

	close CPPPIPE or die "ERROR: CPP.EXE Failure\n";
}

1;
