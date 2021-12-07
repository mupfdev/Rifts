#!perl
####################################################################################
#
# Library: devtools.pm
#
# Library Contains functions used by devtools perl scripts
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved
#
# Version 1.0
#
# Date 12-1-1999
#
####################################################################################
#
# Modification history
#
####################################################################################
package devtools;
use Carp;
use strict;
use Cwd;
BEGIN
	{
	use Exporter   ();
	use vars       qw($VERSION @ISA @EXPORT @EXPORT_OK %EXPORT_TAGS);
	
	## set the version for version checking; uncomment to use
	$VERSION     = 1.00;

	@ISA         = qw(Exporter);
	@EXPORT      = qw(&DebugHash
			  &DebugArray
			  &InList
			  &AscTime		    
			  &ExtractFileNameNoExt
			  &ExtractFileName
			  &ExtractPathNoDrive
			  &ExtractPath
			  &ExtractPathNoExt
			  &ExtractDrive
			  &UpDir
			  &MakePathFromArray
			  &RelateFiles
			  &IsFileUptoDate
			  &TempFilename);
							
	#%EXPORT_TAGS = ( );  	# eg: TAG => [ qw!name1 name2! ],
	#@EXPORT_OK   = qw($maxErrors);
}

   use vars      @EXPORT_OK;
   # non-exported package globals go here
   #use vars      qw($_currentErrors);

   # initialize package globals
   $symbianl::maxErrors   = 0;
   
   # then the others (which are still accessible as $Some::Module::stuff)
   #$_currentErrors  = 0;

   # all file-scoped lexicals must be created before
   # the functions below that use them.
   # file-private lexicals go here
   #my $priv_var    = '';
   #my %secret_hash = ();
   
####################################################################################
#
# Function DebugArray
#
# Function prints out the content of an array
#
# Function takes: a reference to the array to print
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#
####################################################################################
#
# Modification history
#
####################################################################################

sub DebugArray($)
	{
	my($array) = @_;
	my($item);
	print "\nDebugArray\n";

	#loop through all the items in the array
	foreach $item (@$array)
		{
		print "$item\n";
		}
	}

####################################################################################
#
# Function DebugHash
#
# Function prints out the content of a hash
#
# Function takes: a reference to the hash to print
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#
####################################################################################
#
# Modification history
#
####################################################################################

sub DebugHash($)
	{
	my($array) = @_;
	my($item);
	print "\nDebugHash\n";

	#loop through all the items in the array
	foreach $item (keys(%$array))
		{
		print "$item => $array->{$item}\n";
		}
	}

################################################################################
#
# Function InList
#
# Function determines whether an item is in a list
#
# Function takes: The item to find, and a list to find it in
#
# Function Returns: 1 if it is found, 0 if not
#
# Notes:
#################################################################################

sub InList($@)
    {
    my ($item, @list) = @_;

    foreach my $entry (@list)
	{
	if ($entry eq $item)
	    { return 1; }
	}
    return 0;
    }

####################################################################################
#
# Date Time functions
#
####################################################################################
####################################################################################
#
# Function AscTime
#
# Function converts a given time into a date an time string
#
# Function takes: a time
#
# Function Returns: a formated date and time string
#
# Function Uses:
#
# Notes: This function is patterned after the c asctime function
#
####################################################################################
#
# Modification history
#
####################################################################################
sub AscTime($)
	{
	my($aTime)=@_;
	my($sec,$min,$hour,$mday,$mon,$year)=localtime($aTime);
	
	#$mon(th) indexed from 0
	$mon++;

	#$year offset from 1900
	$year=$year+1900;
	
	return "$hour:$min:$sec $mday/$mon/$year";
	}

####################################################################################
#
# Directory, path and file manipulations
#
####################################################################################
####################################################################################
#
# Function ExtractFileNameNoExt
#
# Function extracts the filename from a string and removes the extension
#
# Function takes: a string to extract the file name from
#
# Function Returns: the extracted string
#
# Function Uses:
#
# Notes:
#
####################################################################################
#
# Modification history
#
####################################################################################
sub ExtractFileNameNoExt($)
	{
	my($fileName)=ExtractFileName(@_);

	#remove the extension from the file name
	$fileName =~  s/(.*)\.[^\.]*$/$1/;

	return $fileName;
	}

####################################################################################
#
# Function ExtractFileName
#
# Function extracts the filename from a string
#
# Function takes: a string to extract the file name from
#
# Function Returns: the extracted string
#
# Function Uses:
#
# Notes:
#
####################################################################################
#
# Modification history
#
####################################################################################
sub ExtractFileName($)
	{
	my($fileName)=@_;

	$fileName =~ s/.*[\\:]([^\\:]*$)/$1/;

	return $fileName;
	}

####################################################################################
#
# Function ExtractPathNoDrive
#
# Function extracts the path from a string and removes the drive if any
#
# Function takes: a string to extract the path from
#
# Function Returns: the extracted string
#
# Function Uses:
#
# Notes: If the path has a trailing \ character this is returned as part of the path
# so that c:\ meaning root and c: meaning the current directory can be distinguished 
#
####################################################################################
#
# Modification history
#
####################################################################################
sub ExtractPathNoDrive($)
	{
	my($path)=ExtractPath(@_);

	$path =~ s/[a-zA-Z]:([^:]*$)/$1/;

	return $path;
	}

####################################################################################
#
# Function ExtractPath
#
# Function extracts the path from a string
#
# Function takes: a string to extract the path from
#
# Function Returns: the extracted string
#
# Function Uses:
#
# Notes: If the path has a trailing \ character this is returned as part of the path
# so that c:\ meaning root and c: meaning the current directory can be distinguished 
#
####################################################################################
#
# Modification history
#
####################################################################################
sub ExtractPath($)
	{
	my($path)=@_;

	$path =~ /(.*[\\:])[^\\:]*$/;
	$path=$1;

	return $path;
	}	

####################################################################################
#
# Function ExtractPathNoExt
#
# Function extracts the path and filename from a string removing any file extension
#
# Function takes: a string to extract the path from
#
# Function Returns: the extracted string
#
# Function Uses:
#
# Notes:
#
####################################################################################
#
# Modification history
#
####################################################################################
sub ExtractPathNoExt($)
	{
	my($path)=@_;

	$path =~ s/(.*)\.[^\.]*$/$1/;

	return $path;
	}	

####################################################################################
#
# Function ExtractDrive
#
# Function extracts the drive from a string
#
# Function takes: a string to extract the drive from
#
# Function Returns: the extracted string
#
# Function Uses:
#
# Notes:
#
####################################################################################
#
# Modification history
#
####################################################################################
sub ExtractDrive($)
	{
	my($drive)=@_;

	$drive =~ s/(.):[^:]*$/$1/;

	return $drive;
	}

##############################################################################
#
# Function UpDir
#
# Function takes a path (with or without a trailing '/') and returns the
# parent path (including the trailing '/'). Simulates doing a 'cd ..' on
# a Unix-like or DOS-like system.
#
# Function takes: The path as a string
#
# Function Returns: The parent path
#
# Function Uses:
#
# Notes: The backslash, \, also works as the directory seperator
#        Will return the empty string if a drive root was given, or anything
#        not containing a directory seperator (e.g. '..', '.', or 'X:' etc.)
#
##############################################################################

sub UpDir($)
	{
	my ($aPath) = @_;

	my $lastChar = substr($aPath,-1);
	my $end = length($aPath)-1;

	if ( ($lastChar eq '\\') || ($lastChar eq '/') )
		{
		$end -= 1;
		}

	my $last = rindex($aPath,'\\',$end);
	if ( (rindex($aPath,'/',$end)>$last) | ($last == -1) )
		{ $last = rindex($aPath,'/',$end); }

	if ($last == -1)
		{ return ""; }
	else
		{ return substr($aPath,0,$last).'/'; }
	}

####################################################################################
#
# Function MakePathFromArray
#
# Function creates a path from the entries in an array
#
# Function takes: an array to create the path from
#
# Function Returns: the created path
#
# Function Uses:
#
# Notes: the created path is terminated with a \ so an empty array generates a path
# to the root
#
####################################################################################
#
# Modification history
#
####################################################################################
sub MakePathFromArray(@)
	{
	my(@path)=@_;
	my($filePath)="\\";

	#create the path
	$filePath=$filePath.join("\\",@path);

	#check if the path is the root or needs terminating
	if(!($filePath=~/\\$/))
		{
		#terminate the end of the path
		$filePath=$filePath."\\";
		}

	return $filePath;
	}	

################################################################################
#
# Function RelateFiles
#
# Function takes two filenames, and calculates the relative path from one to the
#          other
#
# Function takes: The current filename, and the filename you wish to refer to
#                 from here
#
# Function Returns: The relative filename
#
# Function Uses:
#
# Notes: This is useful for HTML and other markup languages influenced by HTML
#################################################################################
sub RelateFiles($$)
    {
    my ($aCurrent, $aFile) = @_;

    # Special case, for simplicity (and speed)
    if ($aCurrent eq $aFile)
	{ return ""; }

    # First, knock off common path
    my $different = 0;
    
    do
	{
	# Split $aCurrent
	my $sep = index($aCurrent,"\\");
	my $someCurrent;
	my $someFile;

	if ($sep != -1)
	    {	
	    $someCurrent = substr($aCurrent,0,$sep);
	    $aCurrent = substr($aCurrent,$sep+1);
	    }
	else
	    {
	    $someCurrent = undef;
	    }

	# Split $aFile
	my $sep = index($aFile,"\\");
	if ($sep != -1)
	    {
	    $someFile = substr($aFile,0,$sep);
	    $aFile = substr($aFile,$sep+1);
	    }
	else
	    {
	    $someFile = undef;
	    }

	# If the split bits are the same...
	if ($someCurrent eq $someFile)
	    {
	    $different = 0;

	    if ($someFile eq undef)
		{
                # If we've hit the end on both filenames, pretend we've found
		# a difference, so we'll finish
		$different = 1;
		}
	    }
	else
	    {
	    $different = 1;
	    # Undo that last step
	    if ($someCurrent)
		{ $aCurrent = $someCurrent."\\".$aCurrent; }
	    if ($someFile)
		{ $aFile = $someFile."\\".$aFile; }
	    }
	} until ($different);
    
    # Now we have to step up the tree as necessary
    
    my $sep;
    
    do
	{
	$sep = index($aCurrent,"\\");
	if ($sep != -1)
	    {
	    $aCurrent = substr($aCurrent,$sep+1);
	    $aFile = "..\\".$aFile;
	    }
	} until ($sep == -1);
    
    return $aFile;
    }

####################################################################################
#
# Function IsFileUptoDate
#
# Function takes two filenames source and destination and checks that the
# destination exists and has a file date and time greater or equal to that of the
# source file. This function is useful in make like operations
#
# Function takes: two file names
#
# Function Returns: returns true if the destination file is more recient than the
# source file. False if not. If either of the files do not exist the function returns
# false.
#
# Function Uses:
#
# Notes:
#
####################################################################################
#
# Modification history
#
####################################################################################
sub IsFileUptoDate
	{
	my($source,$dest)=@_;
	my($sourceTime)=0;
	my($destTime)=0;

	my($success)=0;

	#check both files exist
	if(-e $source && -e $dest)
		{
		$sourceTime=FileaTime($source);
		$destTime=FileaTime($dest);

		if($destTime >= $sourceTime)
			{
			$success=1;
			}
		}
		
	return $success;
	}

####################################################################################
#
# Function FileaTime
#
# Function gets the aTime for a given file
#
# Function takes: the filename to read the aTime from
#
# Function Returns: returns the aTime of the file.
# source file
#
# Function Uses:
#
# Notes:
#
####################################################################################
#
# Modification history
#
####################################################################################
sub FileaTime($)
	{
	my($fileName)=@_;

	my($dev,$ino,$mode,$nlink,$uid,$gid,$rdev,$size,$atime,$mtime,$ctime) = stat($fileName);

	return $atime;
	}

###################################################################################
#
# Function TempFilename
#
# Function takes a directory path and then returns the path with an appended
# temporary filename of the format <temp.number>
#
# Function Takes   : The path to a directory where a temporary file is required
#
# Function Returns : The full path and filename for a new temporary file
#
# Function Uses    :
#
# Notes: chdir is used here to temporally move to the given directory to run the
# globbing function. This is due to the fact that globing for directories containing
# spaces does not work.
#
####################################################################################
sub TempFilename($)
	{
	my ($aPath) = @_;
	my $workingDir = getcwd();


	# Create a list of all <temp.*> files in the passed directory
	chdir $aPath;
	my @tempFilenames = glob("temp.*");
	chdir $workingDir;

	my $maxExtNum = 0;
	my $tempFile;

	# loop through all the temp files in the directory
	foreach $tempFile (@tempFilenames)
		{
		# Extract the file extension
		$tempFile =~ s/(.*)\.//;
		my $extension=$tempFile;

		# Ignore extensions that do not solely contain numbers
		# i.e. these must be some other files of the format <temp.*>
		if ($extension =~ /\D/)
			{
			next;
			}

		# Ascertain maximum <temp.*> filename extension number	
		if ($extension > $maxExtNum)
			{
			# make the extension one bigger
			$maxExtNum = $extension+1;
			}
		}

	# Return passed path string with appended temporary filename
	return $aPath."temp.".$maxExtNum;
	}

END { }       # module clean-up code here (global destructor)
1;



