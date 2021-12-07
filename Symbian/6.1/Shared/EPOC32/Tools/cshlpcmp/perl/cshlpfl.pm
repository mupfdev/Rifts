#!perl
################################################################################
#
# module: cshlpfl.pm
#
# module implements the cshlp file object
#
# Copyright (c) 1997-1999 Symbian Ltd.	All rights reserved
#
# Date Wed Jun 28 11:46:21 1999
#
################################################################################
package CCsHlpFile;

use Carp;
use strict;
use FileHandle;
use FindBin;

use devtools;
 
################################################################################
#
# Function New
#
# Function creates a new CSHlpFile object
#
# Function takes: the path / file name of the source file and the path and file
# name of the destination file and the filename for header files (without an
# extension)
#
# Function Returns: the created object
#
# Function Uses:
#
# Notes:
#################################################################################
sub New ($$$)
	{
	my $proto = shift;
	my($aCsHlpFile,$aEPOCHelpFile,$aHeaderFiles) = @_;

	my $class = ref($proto) || $proto;
	my $self  = {};
	bless($self, $class);

	$self->_iLog(New CLog());
	$self->_iCsHlpFile($aCsHlpFile);
	$self->_iEPOCHelpFile($aEPOCHelpFile);
	$self->_iHeaderFiles($aHeaderFiles);

	# Locate the winc components used
	my $root = $FindBin::Bin;
	$root =~ s/\w+[\/\\]\w+$//; # cd ../..
	if ($root !~ /[\/\\]$/)
		{ $root=$root."\/"; }
	$root =~ s/\//\\/g; # Change all / to \

	$self->_iOPLTranExe($root."epoc32\\release\\winc\\urel\\OplTran.exe");
	$self->_iCSHlpWtrExe($root."epoc32\\release\\winc\\urel\\cshlpwtr");

	return $self;
	}

################################################################################
#
# Function _iLog _iCsHlpFile _iEPOCHelpFile
#
# Function access the data of the given object
#
# Function takes:
#
# Function Returns: the value of the data
#
# Function Uses:
#
# Notes:
#################################################################################
sub _iLog
	{
	my $self = shift;
	if (@_) { $self->{LOG} = shift }
	return $self->{LOG};
	}

sub _iCsHlpFile
	{
	my $self = shift;
	if (@_) { $self->{CSHLPFILE} = shift }
	return $self->{CSHLPFILE};
	}

sub _iEPOCHelpFile
	{
	my $self = shift;
	if (@_) { $self->{EPOCHELPFILE} = shift }
	return $self->{EPOCHELPFILE};
	}

sub _iHeaderFiles
	{
	my $self = shift;
	if (@_) { $self->{HEADERFILE} = shift }
	return $self->{HEADERFILE};
	}

sub _iOPLTranExe
	{
	my $self = shift;
	if (@_) { $self->{OPLTRANEXE} = shift }
	return $self->{OPLTRANEXE};
	}

sub _iCSHlpWtrExe
	{
	my $self = shift;
	if (@_) { $self->{CSHLPWTREXE} = shift }
	return $self->{CSHLPWTREXE};
	}

################################################################################
#
# Function ToEPOCHelp
#
# Function converts the CsHlp file to EPOCHelp
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub ToEPOCHelp
	{
	my $self = shift;

	# call the cshlpwtr application to convert the CsHlp file to an EPOCHelp file
	my $command= $self->_iCSHlpWtrExe." \"-if".$self->_iCsHlpFile."\" \"-of".$self->_iEPOCHelpFile."\"";

	$self->_iLog->Log($command."\n");

	my $return=system($command);

	#check if cshlpwtr managed to run
	if($return != 0)
		{
		#some other error reported by cshlpwtr
		$self->_iLog->LogDie("cshlpwtr Fatal Error");
		}

	# put the contexts into a cpp header file
	$self->_MakeHeaderFiles();
	}

################################################################################
#
# Function _MakeHeaderFiles
#
# Function makes the opl and cpp header files
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _MakeHeaderFiles
	{
	my $self = shift;

	my $parser = new XML::DOM::Parser();

	# load the cshlpfile into the dom object
	my $dom = $parser->parsefile($self->_iCsHlpFile);

	# get all the context nodes in the CsHlp document
	my $contexts = $dom->getElementsByTagName ("context");

	# write the required header file
	$self->_WriteCppHeader($contexts);

	# write the required opl file
	# after finding if OPLtran is installed on this SDK
	if (-e $self->_iOPLTranExe())
		{
		$self->_WriteOPLHeader($contexts);
		}
	}

################################################################################
#
# Function _WriteCppHeader
#
# Function writes out the cpp header file
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _WriteCppHeader($)
	{
	my $self = shift;

	my($aContexts)=@_;

	# get the filename
	my $headerFileName = $self->_iHeaderFiles.".hrh";

	# writing the cpp header files
	$self->_iLog->Log("Extracting contexts into a cpp header file ".$headerFileName);
	#open the header file
	my $headerFile = new FileHandle;
	if(!$headerFile->open($headerFileName,"w"))
		{
		$self->_iLog->LogDie("Sorry could not open $headerFileName for output");
		}
	
	# write out the cpp header
	$self->_WriteCppPrologue($headerFile, ExtractFileName($headerFileName));

	# write out the cpp lines
	$self->_WriteCppLines($headerFile, $aContexts);

	# write out the cpp epilogue
	$self->_WriteCppEpilogue($headerFile);

	# close the header file
	$headerFile->close();
	}

################################################################################
#
# Function _WriteCppProlgue
#
# Function writes out a cpp header file prologue to the given header file
#
# Function takes: the file handle of the file to write to and the name of the 
# header file being written
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _WriteCppPrologue($$)
	{
	my $self = shift;

	my($aHeaderFile, $aHeaderFileName)=@_;

	# write out the header file
	print $aHeaderFile "//\n";
	print $aHeaderFile "// $aHeaderFileName\n";
	print $aHeaderFile "//\n";
	print $aHeaderFile "\n";
	print $aHeaderFile "//\n";
	print $aHeaderFile "// File generated on ".AscTime(time())."\n";
	print $aHeaderFile "// by cshlpcmp ".$main::params->ParamItem("Version")->Value()."\n";
	print $aHeaderFile "//\n";
	print $aHeaderFile "\n";

	# generate the header guard token
	my $headerGuard = $aHeaderFileName;
	# substitute all the . with _
	$headerGuard =~ s/\./_/g;
	$headerGuard = "__".uc($headerGuard)."__";

	print $aHeaderFile "#ifndef ".$headerGuard."\n";
	print $aHeaderFile "#define ".$headerGuard."\n";
	print $aHeaderFile "\n";
	print $aHeaderFile "\n";
	}

################################################################################
#
# Function _WriteCppLines
#
# Function writes out the lines into the cpp header file
#
# Function takes: the file handle of the file to write to and the array of 
# context nodes to write 
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _WriteCppLines($$)
	{
	my $self = shift;

	my($aHeaderFile, $aContexts)=@_;

	# write all the contexts
	my $numNodes = $aContexts->getLength();

	# loop through all the context nodes
	for (my $i = 0; $i < $numNodes; $i++)
		{
		my $context = $aContexts->item ($i);
		# write out the context
		print $aHeaderFile "_LIT(K".$context->getAttribute("contextUID").",\"".$context->getAttribute("contextUID")."\");";
		
		# write out any comment if it exists
		my $comment = $context->getAttribute("comment");
		if($comment)
				{
				$comment =~ s/&quot;/\"/g;
				print $aHeaderFile " //".$comment;
				}
		print $aHeaderFile "\n";
		}
	}

################################################################################
#
# Function _WriteCppEpilogue
#
# Function writes out the epilogue into the cpp header file
#
# Function takes: the file handle of the file to write to and the array of 
# context nodes to write 
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _WriteCppEpilogue($)
	{
	my $self = shift;

	my($aHeaderFile)=@_;

	print $aHeaderFile "\n";
	print $aHeaderFile "#endif\n";
	}

################################################################################
#
# Function _WriteOPLHeader
#
# Function writes out the opl header file
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _WriteOPLHeader($)
	{
	my $self = shift;

	my($aContexts)=@_;

	# get the filename
	my $headerFileName = $self->_iHeaderFiles.".oph.txt";

	# writing the opl header files
	$self->_iLog->Log("Extracting contexts into a opl header file ".$headerFileName);
	#open the header file
	my $headerFile = new FileHandle;
	if(!$headerFile->open($headerFileName,"w"))
		{
		$self->_iLog->LogDie("Sorry could not open $headerFileName for output");
		}
	
	# write out the opl header
	$self->_WriteOplPrologue($headerFile, ExtractFileNameNoExt($headerFileName));

	# write out the opl lines
	$self->_WriteOplLines($headerFile, $aContexts);

	# write out the opl epilogue
	$self->_WriteOplEpilogue($headerFile);

	# close the header file
	$headerFile->close();

	# convert the oph.txt file to an opl file
	$self->_ConvTextToOpl($headerFileName);
	}

################################################################################
#
# Function _WriteOplProlgue
#
# Function writes out a Opl header file prologue to the given header file
#
# Function takes: the file handle of the file to write to and the name of the 
# header file being written
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _WriteOplPrologue($$)
	{
	my $self = shift;

	my($aHeaderFile, $aHeaderFileName)=@_;

	# write out the header file
	print $aHeaderFile "rem\n";
	print $aHeaderFile "rem $aHeaderFileName\n";
	print $aHeaderFile "rem\n";
	print $aHeaderFile "\n";
	print $aHeaderFile "rem\n";
	print $aHeaderFile "rem File generated on ".AscTime(time())."\n";
	print $aHeaderFile "rem by cshlpcmp ".$main::params->ParamItem("Version")->Value()."\n";
	print $aHeaderFile "rem\n";
	print $aHeaderFile "\n";
	print $aHeaderFile "\n";
	}

################################################################################
#
# Function _WriteOplLines
#
# Function writes out the lines into the opl header file
#
# Function takes: the file handle of the file to write to and the array of 
# context nodes to write 
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _WriteOplLines($$)
	{
	my $self = shift;

	my($aHeaderFile, $aContexts)=@_;

	# write all the contexts
	my $numNodes = $aContexts->getLength();

	# loop through all the context nodes
	for (my $i = 0; $i < $numNodes; $i++)
		{
		my $context = $aContexts->item ($i);
		# write out the context
		print $aHeaderFile "const K".$context->getAttribute("contextUID")."\$ = \"".$context->getAttribute("contextUID")."\"";
		
		# write out any comment if it exists
		my $comment = $context->getAttribute("comment");
		if($comment)
			{
			$comment =~ s/&quot;/\"/g;
			print $aHeaderFile " rem ".$comment;
			}
		print $aHeaderFile "\n";
		}
	}

################################################################################
#
# Function _WriteOplEpilogue
#
# Function writes out the epilogue into the header file
#
# Function takes: the file handle of the file to write to and the array of 
# context nodes to write 
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _WriteOplEpilogue($)
	{
	my $self = shift;

	my($aHeaderFile)=@_;

	print $aHeaderFile "\n";
	print $aHeaderFile "rem end of header";
	}

################################################################################
#
# Function _ConvTextToOpl
#
# Function converts the .txt file to a oph file
#
# Function takes: the file name of the file to convert
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub _ConvTextToOpl($)
	{
	my $self = shift;

	my($aHeaderFileName)=@_;

	# call the opltran application to convert the text file to an opl file
	my $command= $self->_iOPLTranExe()." -e -v $aHeaderFileName -conv";

	$self->_iLog->Log($command."\n");

	my $return=system($command);

	#check if opltran managed to run
	if($return != 0)
		{
		#some other error reported by opltran
		$self->_iLog->LogDie("opltran Fatal Error");
		}
	}

################################################################################
#
# Function TEST
#
# Function the test code for the cshlp file object
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub TEST
	{
	my $self = shift;

	$self->_iLog->Log("#######################");
	$self->_iLog->Log("Test1 store object data");
	
	$self->_iLog->Log("filling up the data");
	$self->_iCsHlpFile("the input rtf file");
	$self->_iEPOCHelpFile("the output ptml file");

	$self->_iLog->Log("Recovering data");
	
	$self->PRINT;
	}

################################################################################
#
# Function PRINT
#
# Function prints out the current contents of the CsHlpfile object
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
#################################################################################
sub PRINT
	{
	my $self = shift;
	$self->_iLog->Log("the input CsHlp file | ". $self->_iRtfFile);
	$self->_iLog->Log("the output EPOCHelp file | ". $self->_iPtmlFile);
	}

1;

















