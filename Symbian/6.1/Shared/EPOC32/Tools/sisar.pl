#
# Copyright (c) 2001 Symbian Ltd.  All rights reserved.
#
# This script is only meant to be used to launch Sisar
# from the console. Use splash.exe directly in file
# associations and the Start menu, otherwise you'll
# get a nasty console window popping up.
#

use FindBin;
use Cwd;
use Win32API::Registry qw( :ALL );

$wd = cwd;
$curDrive = getDrive($wd);
$curPath = getPath($wd);
$curDrive =~ s/\\/\//g;
$curPath =~ s/\\/\//g;

my $toolDir = $FindBin::Bin;
# We are assuming no slashes in the end.
while($toolDir =~ /^(.*)\/$/)
{
    $toolDir = $1;
}

$console = 0;
$files = 0;
$illegal = 0;

for $a (@ARGV)
{
    if($a !~ /^-/)
    {
	$files++;
    }
    elsif(($a =~ /^-verbose$/))
    {}
    elsif(($a =~ /^-help$/) ||
	  ($a =~ /^-build$/))
    {
	$console = 1;
    }
    else
    {
	# Illegal switch, we will want to display some complaint.
	$illegal = 1;
	$console = 1;
    }
}

if($console)
{
    my $appDir = $toolDir . "/" . "Sisar";
    my $libDir = $toolDir . "/" . "javalib";
    my $classPath = $appDir . "/" . "sisar.jar";
    # $classPath .= ";" . 
    #	$appDir . "/" . "JavaCUP.jar" . ";" . 
    #	$libDir . "/" . "assertion.jar" . ";" . 
    #	$libDir . "/" . "langconfig.jar" . ";" . 
    #	$libDir . "/" . "shellexec.jar" . ";" . 
    #	$libDir . "/" . "mnemonicfix.jar" . ";" . 
    #	$libDir . "/" . "toolbarpanel.jar" . ";" . 
    #	$libDir . "/" . "jaxp.jar" . ";" . 
    #	$libDir . "/" . "parser.jar" . ";" . 
    #	$libDir . "/" . "jh.jar" . ";" . 
    #	$libDir . "/" . "javahelp.jar" . ";" . 
    #	$libDir . "/" . "testcaserunner.jar";

    #system("notepad.exe \"file.txt\""); # This works.
    #system("\"notepad.exe\" file.txt"); # This works.
    #system("\"notepad.exe\" \"file.txt\""); # This does not.
    # So we want to keep java.exe free of surrounding quotes.
    # To do this, we must try to make sure that java.exe is
    # on the PATH.
    $ENV{PATH} = &getJavaBin . ";" . $ENV{PATH}; 

    #my $command = esc(&getJava);
    my $command = "java";
    $command .= " -classpath \"" . $classPath . "\"";
    $command .= " com.symbian.sdk.sisar.CSisar";
    for $a (@ARGV)
    {
	$command .= " " . esc($a);
    }
    #print $command . "\n";
    #system("echo " . $command);
    # The return value is not very useful.
    # We get 0 even if the command is not found.
    system($command);

    # Another way to use system(). Doesn't work, though.
    #my @command = ();
    ##push @command, "echo";
    #push @command, esc(&getJava);
    #push @command, "-classpath";
    #push @command, "\"" . $classPath . "\"";
    #push @command, "com.symbian.sdk.sisar.CSisar";
    #push @commanh, @ARGV;
    ##print @command;
    #system(@command);

    exit(0);
}
else
{
    my $td = $toolDir;
    $td =~ s/\//\\/g;
    my $command = $td . "\\" . "splash " . "Sisar" . "\\" . "sisar.jar";
    if($files)
    {
	for $a (@ARGV)
	{
	    if($a !~ /^-/)
	    {
		$command .= " " . esc(toFull($a));
		last;
	    }
	}
    }
    #open(LOG,">c:\\temp\\sisar-log.txt");
    #print LOG $command . "\n";
    #close(LOG);
    exec($command) ||
	die("Failed to execute \"splash\" in order to start Sisar: $!");
}

# Escapes strings that contain any spaces.
sub esc
{
    my $s = shift;
    return "\"" . $s . "\"" if $s =~ / /;
    return $s;
}

sub toFull
{
    my $f = shift;
    my $drive;
    my $path;
    $f =~ s/\\/\//g;
    if(hasDrive($f)) {
	$drive = getDrive($f);
    } else {
	$drive = $curDrive;
    }
    if(isAbsolute($f)) {
	$path = getPath($f);
    } else {
	$path = $curPath . "/" . getPath($f);
    }
    return $drive . $path;
}

sub isAbsolute
{
    my $f = shift;
    my $p = getPath($f);
    return 1 if $p =~ /^\//;
    return 0;
}

sub hasDrive
{
    my $f = shift;
    my $r = getDrive($f);
    return !($r eq "");
}

sub getDrive
{
    my $f = shift;
    if($f =~ /^([a-zA-Z]):/) {
	return $1 . ":";
    }
    if($f =~ /^\/\/([a-zA-Z])/) {
	return $1 . ":";
    }
    return ""; # no drive
}

sub getPath
{
    my $f = shift;
    if($f =~ /^[a-zA-Z]:(.*)$/) {
	return $1;
    }
    if($f =~ /^\/\/[a-zA-Z](.*)$/) {
	return $1;
    }
    return $f;
}

# Gets a the location (directory) of the JRE executables.
# Returns 0 if not found.
sub getJavaBin
{
    my $topKey = HKEY_LOCAL_MACHINE;
    my $keyName = "SOFTWARE\\JavaSoft\\Java Runtime Environment\\1.3.1";
    my $valueName = "JavaHome";

    my $java = 0;

    if(RegOpenKeyEx($topKey,$keyName,0,KEY_READ,$regKey))
    {
	if(RegQueryValueEx($regKey,$valueName,[],$regType,$regData,[]))
	{
	    if($regType == REG_SZ)
	    {
		# Value data has expected type.
		$java = $regData . "\\bin";
	    }
	}
	RegCloseKey($regKey) ||
	    print STDERR "WARNING: Could not close registry key.";
    }

    $java || die
	"ERROR: Could not find Java 1.3 Runtime Environment. " .
	    "Please ensure that JRE 1.3 has been installed.\n";

    return $java;
}

# Returns the command to use to run the Java runtime.
sub getJava
{
    my $topKey = HKEY_LOCAL_MACHINE;
    my $keyName = "SOFTWARE\\JavaSoft\\Java Runtime Environment\\1.3.1";
    my $valueName = "JavaHome";

    my $java = 0;

    if(RegOpenKeyEx($topKey,$keyName,0,KEY_READ,$regKey))
    {
	if(RegQueryValueEx($regKey,$valueName,[],$regType,$regData,[]))
	{
	    if($regType == REG_SZ)
	    {
		# Value data has expected type.
		$java = $regData . "\\bin\\java.exe";
	    }
	}
	RegCloseKey($regKey) ||
	    print STDERR "WARNING: Could not close registry key.";
    }

    $java || die
	"ERROR: Could not find Java 1.3 Runtime Environment. " .
	    "Please ensure that JRE 1.3 has been installed.\n";

    return $java;
}
