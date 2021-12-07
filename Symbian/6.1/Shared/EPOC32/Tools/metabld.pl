# METABLD.PL
#
# Copyright (c) 2000 Symbian Ltd.  All rights reserved.
#


# all variables called *Path* are set up to end with a backslash
# all variables called *Path or *File are stored as absolute (file)paths within makmake
# all variables called UpPath* are stored as relative paths within makmake

my $PerlLibPath;

BEGIN
	{
	# check user has a version of perl that will cope and use metabld as specified by the system path
	require 5.003_07;
	my $Script=$0;
  	$Script=~s-\/-\\-go;
	if ($Script=~/^(.*\\)/o)
		{
		$PerlLibPath=$1;
		}
	else
		{
		$PerlLibPath='.';
		}
	}

use File::Find;
use Cwd;

use lib $PerlLibPath;
use E32env;
use Prepfile;
use Pathutl;


my (@Commands, @BldInfDirs);
# should end in .mbc where .mbc means for "MetaBld Configuration file"
# must end in .mbc if passed on command-line
my $ConfigFile;

my $StartDir=&cwd();

	{
	# Process command-line
	
  	unless (@ARGV)
		{
		&Usage();
		}
	else
		{
		# check for a root from a config file in EPOCROOT dir as first argument
	  	if (-e "$ENV{EPOCROOT}$ARGV[0].mbc")
			{
		  	$ConfigFile="$ENV{EPOCROOT}$ARGV[0].mbc";
		  	shift @ARGV;
			}
		# check for a config file as the first argument
	  	elsif ($ARGV[0]=~/.mbc$/io)
			{
			$ConfigFile=shift @ARGV;
			if ($ConfigFile=~/^.:/o)
				{
				&Error("Config file can't be specified with a drive letter, as \"$ConfigFile\" is");
				}
			unless (-e $ConfigFile)
				{
				&Error("Can't find file $ConfigFile");
				}
			}
		if (@ARGV)
			{
			# pass any other arguments as commands
			@Commands=("@ARGV");
			}
		}
	}

	{
	# scan config file if necessary
	
	if ($ConfigFile)
		{
		# make config file path absolute
		$ConfigFile=&Path_AbsToWork($ConfigFile);
		
		my @Config2D;
		eval { &Prepfile_ProcessL(\@Config2D, $ConfigFile); };
		&Error($@) if $@;
		
		my %CheckDir;
		
		my @ConfigCommands;
		my $Section='';
		my @Death;
		my $Line;
		my $CurFile=$ConfigFile;
	  LINE: foreach $Line (@Config2D)
			{
			my $LineNum=shift @$Line;
			$_=shift @$Line;
			if ($LineNum eq '#')
				{
				$CurFile=$_;
				next;
				}
			if (/^SECTION_(\w*)$/io)
				{
				$Section=uc $1;
				if ($Section=~/^(COMMANDS|DIRS)$/o)
					{
					if (@$Line)
						{
						push @Death, "$CurFile($LineNum) : Can't specify anything on the same line as a section header\n";
						}
					next LINE;
					}
				push @Death, "$CurFile($LineNum) : Unknown section header - $_\n";
				$Section=0;
				next LINE;
				}
			unshift @$Line, $_;
			if ($Section eq 'COMMANDS')
				{
				if ($$Line[0]=~/^ONEOFF$/io)
					{
					# check syntax for oneoff commands
					unless (@$Line>=3)
						{
						push @Death, "$CurFile($LineNum) : Too few arguments for oneoff command\n";
						}
					# resolve oneoff dir relative to .mb file location
					$$Line[1]=~s-^.*[^\\]$-$&\\-o; # add trailing backslash if necessary
					$$Line[1]=&Path_MakeAbs($CurFile, $$Line[1]);
					unless (-d $$Line[1])
						{
						warn "$CurFile($LineNum) : Can't find dir $$Line[1]\n";
						}
					}
				push @ConfigCommands, "@$Line";
				next LINE;
				}
			if ($Section eq 'DIRS')
				{
				my $Dir;
				foreach $Dir (@$Line)
					{
					if ($Dir=~/^.:/o)
						{
						push @Death, "$CurFile($LineNum) : directory $Dir is specified with a drive letter\n";
						next;
						}
					$Dir=~s-^.*[^\\]$-$&\\-o;
					$Dir=&Path_MakeAbs($CurFile, $Dir); # dirs must be the same for check
					if ($CheckDir{uc $Dir})
						{
						# Silently ignore duplicate directories - #including of several .mbc files
						# will often cause directory duplication.
						# We can't do the same for duplicate commands because the order in which
						# the commands are executed might be significant.
						# push @Death, "$CurFile($LineNum) : Directory $Dir already specified\n";
						next;
						}
					print "$Dir\n";
					
					unless (-d $Dir)
						{
						push @Death, "$CurFile($LineNum) : Can't find directory $Dir\n";
						next;
						}
					push @BldInfDirs, $Dir;
					$CheckDir{uc $Dir}=$LineNum;
					}
				next LINE;
				}
			else
				{
				push @Death, "$CurFile($LineNum) : No section specified\n";
				}
			}
		
		if (@Death)
			{
			chomp $Death[$#Death];
			&Error(@Death);
			}
		
		# apply the commands unless already collected
		unless (@Commands)
			{
			&Error("$ConfigFile : No Commands specified") unless @ConfigCommands;
			@Commands=@ConfigCommands;
			}
		}
	
	# Should have commands now
	&Usage() unless @Commands;
	}

	{
	# Search for the BLD.INF files if necessary
	
	unless (@BldInfDirs)
		{
		# find the files in the source directories - skip the EPOCROOT directory
		
		my $EPOCROOTDir=$E32env::Data{EPOCPath};
		$EPOCROOTDir=~s/^\\([^\\]*).*$/$1/o;
		
		opendir DIR, "\\" or &Error("Can't open dir: $!");
		# remove ., .. and EPOCROOT dir
		my @SrcDirs=grep !/^(\.\.?|$EPOCROOTDir)$/i, readdir DIR; 
		foreach (@SrcDirs)
			{
			# prepend with a backslash
			$_="\\".$_;
			}
		@SrcDirs=grep -d, @SrcDirs;
		find(\&BldInfDirs, @SrcDirs);
		@BldInfDirs=sort @BldInfDirs;
		}
	}

	{
	# Execute the commands
	
	my $Time=localtime;
	print "=== metabld started $Time.\n";
	my $Command;
	foreach $Command (@Commands)
		{
		
		$Time=localtime;
		# Check if we should execute this command just the once
		if ($Command=~s/^\s*ONEOFF\s+(\S+)\s+(.*)$/$2/io)
			{
			my $OneOffDir=$1;
			# execute the command once rather than for each BLD.INF directory
			chdir $OneOffDir or &Error("Can't change dir to $OneOffDir: $!");
			print
			(
			 "===-------------------------------------------------\n",
			 "=== $Command\n",
			 "===-------------------------------------------------\n",
			 "=== $Command started $Time.\n",
			 "=== $Command == $OneOffDir\n"
			);
			open PIPE, "$Command |";
			while (<PIPE>)
				{
				print;
				}
			close PIPE or &Error("Can't close pipe $Command |: $!");
			}
		else
			{
			# execute the command for each BLD.INF directory
			print
			(
			 "===-------------------------------------------------\n",
			 "=== $Command\n",
			 "===-------------------------------------------------\n",
			 "=== $Command started $Time.\n",
			);
			my $Dir;
			foreach $Dir (@BldInfDirs)
				{
				chdir $Dir or &Error("Can't change dir to $Dir: $!");
				print "=== $Command == $Dir\n";
				open PIPE, "$Command |";
				while (<PIPE>)
					{
					print;
					}
				close PIPE or &Error("Can't close pipe $Command | : is command valid?");
				}
			}
		chdir $StartDir or &Error("Can't change dir to $StartDir: $!");
		$Time=localtime;
		print "=== $Command finished $Time.\n";
		}
	}


#################################################
#	SUBROUTINES
#################################################

sub Usage
	{
	print <<ENDHERESTRING;
usage: metabld [EPOCROOT .mbc file basename|.mbc config file] [command]
MetaBld is a tool for carrying out build commands across several components.
A .mbc config file contains directories and commands, eg:

SECTION_COMMANDS
bldmake bldfiles
abld target wins udeb
// "oneoff" means carry out command just once, not for each directory.
// First arg after "oneoff" must be a start dir, and can be "."
oneoff \\e32\\rombuild rom xxx
oneoff . \\e32test\\group\\abld test build wins urel
SECTION_DIRS
\\e32
\\f32\\group

It's possible to #include lists of dirs from other files if necessary,
and may be useful for carrying out different sets of commands on the same set
of directories via different .mbc files.
If a command is specified on the command-line, it will be executed instead
of any commands specified in a .mbc file.
If no directories are specified in a .mbc file, then all the directories
containing a bld.inf file on the current drive will be searched for instead.
ENDHERESTRING
exit 1;
}

sub Error (@)
	{
	
	die
	@_, "\n",
	"Error executing metabld.bat\n"
	;
	}

sub BldInfDirs
	{
	s-\/-\\-go;
	if (/^BLD.INF$/io)
		{
		$File::Find::dir=~s-\/-\\-go;
		push @BldInfDirs, $File::Find::dir;
		}
	}

