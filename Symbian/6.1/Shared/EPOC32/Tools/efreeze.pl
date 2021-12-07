# EFREEZE.PL
#
# Copyright (c) 1998-1999 Symbian Ltd.  All rights reserved.
#


# all variables called *Path* are set up to end with a backslash
# all variables called *Path or *File are stored as absolute (file)paths
# all variables called UpPath* are stored as relative paths

my $PerlLibPath;

BEGIN {
# check user has a version of perl that will cope and use DEFMAKE as specified by the system path
	require 5.003_07;
	foreach (split ';', $ENV{Path}) {
		s-/-\\-go;	# for those working with UNIX shells
		s-^$-.-o;	# convert empty string to .
		s-^(.*[^\\])$-$1\\-o;   # ensure path ends with a backslash
		if (-e $_.'EFREEZE.PL') {
			$PerlLibPath=uc $_;
			last;
		}
	}
}


use Getopt::Long;

use lib $PerlLibPath;
use Defutl;
use E32tpver;
use Pathutl;


# THE MAIN PROGRAM SECTION
##########################

{
	my %Options;

	# process the command-line
	unless (GetOptions(\%Options, 'compare')) {
		exit 1;
	}
	unless (@ARGV==2) {
		&Usage;
	}

	my ($FRZFILE,$GENFILE)=&Path_AbsToWork(@ARGV);

#	check the file exists
	unless (-e $FRZFILE) {
		warn "WARNING: $FRZFILE: File not found - OK if freezing for first time\n";
	}
	unless (-e $GENFILE) {
		die "EFREEZE ERROR: $GENFILE: File not found\n";
	}

#	Read the Frozen .DEF file if it exists
	my @FrzDataStruct;
	my $FrzExportsOn=0;
	if (-e $FRZFILE) {
		eval { &Def_ReadFileL(\@FrzDataStruct, $FRZFILE, $FrzExportsOn); };
		die $@ if $@;
	}

#	Read the New .DEF file
	my @GenDataStruct;
	my $Dummy;
	if ($GENFILE) {
		eval { &Def_ReadFileL(\@GenDataStruct, $GENFILE, $Dummy, $Options{compare}); };
	}
	die $@ if $@;

#	Compare the frozen .DEF data with the new .DEF file
	my (@NewDataStruct, @MissingDataStruct, @BadDataStruct);
	eval { &CompareFrzGenL (\@NewDataStruct, \@MissingDataStruct, \@BadDataStruct, \@FrzDataStruct, \@GenDataStruct); };
	die $@ if $@;

#	check for errors
	my $Ref;
	my @Errors;
	my $Title='EFREEZE ERROR:';
	if ($Options{compare}) {
		$Title='EFREEZE:';
	}
	if (@MissingDataStruct) {
		my $Num=@MissingDataStruct;
		push @Errors, "$Title $FRZFILE: $Num Frozen Export(s) missing from $GENFILE:\n";
		foreach $Ref (@MissingDataStruct) {
			my $r3unused = $$Ref{R3Unused} ? " R3UNUSED" : "";
			push @Errors, "  $$Ref{LineNum}: $$Ref{Name} \@ $$Ref{Ordinal} NONAME$r3unused\n";
		}
		push @Errors, "\n";
	}
	if (@BadDataStruct) {
		my $Num=@BadDataStruct;
		push @Errors, "$Title $GENFILE: $Num function(s) exported at wrong ordinal:\n";
		foreach $Ref (@BadDataStruct) {
			my $r3unused = $$Ref{R3Unused} ? " R3UNUSED" : "";
			push @Errors, "  $$Ref{LineNum}: $$Ref{Name} \@ $$Ref{Ordinal} NONAME$r3unused\n";
		}
	}
	if (@Errors) {
		unless ($Options{compare}) {
			die @Errors;
		}
		else {
			print @Errors;
		}
	}

#	Update the frozen .DEF file
	eval { &UpdateFrzFileL(\@NewDataStruct, \@FrzDataStruct, $FRZFILE, $FrzExportsOn, $Options{compare}); };
	die $@ if $@;
	

	exit;
}

#######################################################################
# SUBROUTINES
#######################################################################

sub Usage () {

	print(
		"\n",
		"EFREEZE - .DEF file maintenance utility (Build ",&E32tpver,")\n",
		"\n",
		"EFREEZE {options} [frozen .DEF file] [new .DEF file]\n",
		"\n",
		"options:   (case-insensitive)\n",
		"  -Compare\n",
		"\n"
	);
	exit 1;
}

sub CompareFrzGenL ($$$$$$) {
	my ($NewStructRef, $MissingStructRef, $BadStructRef, $FrzStructRef, $GenStructRef)=@_;

#	compare the input export data with the frozen data

#	take a copy of the frozen .DEF file structure that we can trash
	my @TmpStruct=@$FrzStructRef;

#	remove any entries not containing export data and get the highest ordinal value used
	my $LastOrdinal=0;
	foreach (@TmpStruct) {
		if ($$_{Name}) {
			if ($LastOrdinal<$$_{Ordinal}) {
				$LastOrdinal=$$_{Ordinal};
			}
			next;
		}
		undef $_;
	}

	my $GenRef;
	my $TmpRef;
	GENLOOP: foreach $GenRef (@$GenStructRef) {
		next unless $$GenRef{Name};		# ignore lines in the .DEF file not containing an export
		foreach $TmpRef (@TmpStruct) {
			next unless defined $TmpRef; # ignore nullified entries in the temporary array
#			does the function name match?
			if ($$GenRef{Name} eq $$TmpRef{Name}) {
#				check the names have the same ordinals
				if ($$GenRef{Ordinal}==$$TmpRef{Ordinal}) {
					undef $TmpRef;
					next GENLOOP;
				}
#				store exports with the wrong ordinals
				push @$BadStructRef, $GenRef;
				undef $TmpRef;
				next GENLOOP;
			}
		}
#		store new exports not found in the frozen .DEF file with the right ordinal value
		$LastOrdinal++;
		$$GenRef{Ordinal}=$LastOrdinal;
		push @$NewStructRef, $GenRef;
	}

#	all the exports left in the frozen .DEF file weren't found
	foreach $TmpRef (@TmpStruct) {
		next unless defined $TmpRef; # ignore nullified entries in the temporary array
		push @$MissingStructRef, $TmpRef;
	}
}

sub UpdateFrzFileL ($$$$$) {
	my ($NewStructRef, $FrzStructRef, $FILE, $ExportsOn, $Compare)=@_;

#	add the exports to the frozen .DEF file text
	unless (@$NewStructRef) {
		print "EFREEZE: No New Exports\n";
		return;
	}

	my $NumNewExports=@$NewStructRef;
	unless ($Compare) {
# 		abort the operation unless the frozen .DEF file is writeable
		if (-e $FILE and not -w $FILE) {
			die
				"EFREEZE ERROR: Can't append $NumNewExports New Export(s) to $FILE\n",
				"  as file is not writeable.  Check source code control system.\n"
			;
		}
		print "EFREEZE: Appending $NumNewExports New Export(s) to $FILE:\n";
	}
	else {
		print "EFREEZE: $NumNewExports New Export(s):\n";
	}

	my @Text;

#	Process the frozen .DEF file
	if (@$FrzStructRef) { # there is already a frozen .DEF file
		my $FrzRef;

#		get the lines of text from the frozen .DEF file
		foreach $FrzRef (@$FrzStructRef) {
			push @Text, "$$FrzRef{Line}";
		}

#		strip any blank lines at the end of the frozen .DEF file text
		foreach (reverse @Text) {
			if (/^\s*$/o) {
				$_='';
				next;
			}
			last;
		}

	}

#	Add an EXPORTS section header if there aren't already exports
	unless ($ExportsOn) {
		push @Text, "EXPORTS\n";
	}

	my $NewRef;
	foreach $NewRef (@$NewStructRef) {
		my $Comment='';
		if ($$NewRef{Comment}) {
			$Comment=" ; $$NewRef{Comment}";
		}
		my $r3unused = $$NewRef{R3Unused} ? " R3UNUSED" : "";
		print "  $$NewRef{Name} \@ $$NewRef{Ordinal} NONAME$r3unused$Comment\n";
		push @Text, "\t$$NewRef{Name} \@ $$NewRef{Ordinal} NONAME$r3unused$Comment\n";
	}

#	add a terminating newline
	push @Text, "\n";

	unless ($Compare) {
#		write the new frozen .DEF file
		eval { &Def_WriteFileL(\@Text, $FILE); };
		die $@ if $@;
	}
}

