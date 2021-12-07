#!perl
################################################################################
#
# module: projfile.pm
#
# module implements the project file object
#
# Copyright (c) 1997-1999 Symbian Ltd.	All rights reserved
#
# Date Wed Jun 23 11:46:21 1999
#
################################################################################
package CProjFile;

use Carp;
use strict;
use Cwd;
use File::Path;

use devtools;
use log;

################################################################################
#
# Function New
#
# Function creates a new projfile object
#
# Function takes: none
#
# Function Returns: the created object
#
# Function Uses:
#
# Notes: All directory fields are set to the current working directory
# all file fields are set to undef
#################################################################################
sub New
	{
	my $proto = shift;
	my $class = ref($proto) || $proto;

	#get the current working directory
	my $cwd = cwd();
	
	my $self  = {};

	bless($self, $class);

	$self->_iLog(New CLog());

	$self->_iHelpFileUID(undef);
	$self->_iInputDir($cwd);
	$self->_iOutputDir($cwd);
	$self->_iGraphicDir($cwd);
	$self->_iWorkingDir($cwd);
	$self->_iHeadersDir(undef);
	
	$self->_iSourceFiles([]);
	$self->_iXmlFiles([]);
	$self->_iGraphicFiles([]);
	$self->_iDestFile(undef);
	$self->_iCustomizationFile(undef);

	return $self;
	}

################################################################################
#
# Function _iHelpFileUID _iInputDir _iOutputDir _iGraphicDir _iWorkingDir
# _iSourceFiles _iDestFile _iCustomizationFile 
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

sub _iHelpFileUID
	{
	my $self = shift;
	if (@_) { $self->{HELPFILEUID} = shift }
	return $self->{HELPFILEUID};
	}

sub _iInputDir
	{
	my $self = shift;
	if (@_) { $self->{INPUTDIR} = shift }
	return $self->{INPUTDIR};
	}

sub _iOutputDir
	{
	my $self = shift;
	if (@_) { $self->{OUTPUTDIR} = shift }
	return $self->{OUTPUTDIR};
	}

sub _iHeadersDir
	{
	my $self = shift;
	if (@_) { $self->{HEADERSDIR} = shift }
	return $self->{HEADERSDIR};
	}

sub _iGraphicDir
	{
	my $self = shift;
	if (@_) { $self->{GRAPHICDIR} = shift }
	return $self->{GRAPHICDIR};
	}

sub _iWorkingDir
	{
	my $self = shift;
	if (@_) { $self->{WORKINGDIR} = shift }
	return $self->{WORKINGDIR};
	}
	
sub _iSourceFiles
	{
	my $self = shift;
	if (@_) { $self->{SOURCEFILES} = shift }
	return $self->{SOURCEFILES};
	}

sub _iXmlFiles
	{
	my $self = shift;
	if (@_) { $self->{XMLFILES} = shift }
	return $self->{XMLFILES};
	}

sub _iGraphicFiles
	{
	my $self = shift;
	if (@_) { $self->{GRAPHICFILES} = shift }
	return $self->{GRAPHICFILES};
	}

sub _iDestFile
	{
	my $self = shift;
	if (@_) { $self->{DEST} = shift }
	return $self->{DEST};
	}

sub _iCustomizationFile 
	{
	my $self = shift;
	if (@_) { $self->{CUST} = shift }
	return $self->{CUST};
	}

sub _iProjectFile 
	{
	my $self = shift;
	if (@_) { $self->{PROJ} = shift }
	return $self->{PROJ};
	}

################################################################################
#
# Function _AddSourceFile 
#
# Function _AddSourceFile
#
# Function takes: the source filename
#
# Function Returns: non
#
# Function Uses:
#
# Notes:
################################################################################
sub _AddSourceFile
	{
	my $self = shift;

	my($aFileName) = @_;
	push(@{$self->_iSourceFiles},$aFileName);
	}

################################################################################
#
# Function _AddXmlFile 
#
# Function _AddXmlFile
#
# Function takes: the source filename
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
##########################################################################
sub _AddXmlFile
	{
	my $self = shift;

	my($aFileName) = @_;
	push(@{$self->_iXmlFiles},$aFileName);
	}

###############################################################################
#
# Function _AddGraphicFile 
#
# Function _AddGraphicFile
#
# Function takes: the graphic filename
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
###############################################################################
sub _AddGraphicFile
	{
	my $self = shift;

	my($aFileName) = @_;
	push(@{$self->_iGraphicFiles},$aFileName);
	}

################################################################################
#
# Function Public getter functions
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
################################################################################
sub HelpFileUID
	{
	my $self = shift;
	return $self->_iHelpFileUID;
	}

sub InputDir
	{
	my $self = shift;
	return $self->_iInputDir;
	}

sub OutputDir
	{
	my $self = shift;
	return $self->_iOutputDir;
	}

sub HeadersDir
	{
	my $self = shift;
	return $self->_iHeadersDir;
	}

sub GraphicDir
	{
	my $self = shift;
	return $self->_iGraphicDir;
	}

sub WorkingDir
	{
	my $self = shift;
	return $self->_iWorkingDir;
	}

sub SourceFiles
	{
	my $self = shift;
	return $self->_iSourceFiles;
	}

sub XmlFiles
	{
	my $self = shift;
	return $self->_iXmlFiles;
	}

sub GraphicFiles
	{
	my $self = shift;
	return $self->_iGraphicFiles;
	}

sub DestFile
	{
	my $self = shift;
	return $self->_iDestFile;
	}
sub CustomizationFile
	{
	my $self = shift;
	return $self->_iCustomizationFile;
	}

################################################################################
#
# Function Parse
#
# Function parses the project file, the extracted infromation in placed in to the
# member data
#
# Function takes: the project file to parse
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub Parse($)
	{
	my $self = shift;
	my($aProjectFile)=@_;

	#get a new xml parsing object
	my $parser = new XML::DOM::Parser;
	my $doc = $parser->parsefile($aProjectFile);

	$self->_iProjectFile($aProjectFile);

	$self->_ParseDoc($doc);

	# dispose the project file dom so that it can be garbage collected
	$doc->dispose();

	$self->_ValidateFiles();
	}

################################################################################
#
# Function _ParseDoc
#
# Function parses the doc 
#
# Function takes: a reference to the doc to parse
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _ParseDoc($)
	{
	my $self = shift;
	my($aDoc)=@_;

	#validate the doctype
	$self->_ValidateDocType($aDoc->getDoctype);

	#get the nodes in the project file
	my $nodes=$aDoc->getElementsByTagName("cshproj");
	
	if(!$nodes)
		{
		$self->_iLog->LogDie("Project file must contain a cshproj tag");
		}
	$self->_ProcCSHprojNodes($nodes->item(0));
	}
################################################################################
#
# Function _ValidateDocType
#
# Function validates the doc type 
#
# Function takes: the doctype node
#
# Function Returns: none
#
# Function Uses: none
#
# Notes: 
################################################################################
sub _ValidateDocType
	{
	my $self = shift;
	my($aNode) = @_;

	#check that the doctype is correct
	if ($aNode)
		{
		if($aNode->getName ne "cshproj")
			{
			$self->_iLog->LogDie("project file is of the wrong type");
			}
		}
	}

################################################################################
#
# Function _ProcCSHprojNodes
#
# Function processes all the nodes in the project file
#
# Function takes: a reference to the cshproj node
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _ProcCSHprojNodes($)
	{
	my $self=shift;
	my($aNode)=@_;

	#loop though all the children
	for my $kid ($aNode->getChildNodes)
	{
	#check if this is an element node
	if($kid->getNodeType == XML::DOM::ELEMENT_NODE)
			{
		  SWITCH:
			{
			my($tagName)=$kid->getTagName;

			if($tagName eq "helpfileUID")
					{
					#get the help file uid
					$self->_iHelpFileUID( $self->_RemoveRets($kid->getFirstChild->getData));
					last SWITCH;
					}
			
			if($tagName eq "directories")
					{
					#process the directories
					$self->_ProcDirectoriesNodes($kid);
					last SWITCH;
					}
			if($tagName eq "files")
					{
					#process the files
					$self->_ProcFilesNodes($kid);
					last SWITCH;
					}
			
			#otherwise
			$self->_iLog->LogDie($kid->getTagName." is not a recognised project file element");
			}
			}
	}
	}

###############################################################################
#
# Function _ProcDirectoriesNodes
#
# Function processes all the nodes in the directories element
#
# Function takes: a reference to the directory node
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
###############################################################################
sub _ProcDirectoriesNodes($)
	{
	my $self=shift;
	my($aNode)=@_;

	my $projectDir = $self->_iProjectFile();
	$projectDir =~ s/[\\\/][^\\\/]+$/\\/; # remove filename from end
	if ($projectDir !~ /[\\\/]/)
		{
		# Or, if it's just the filename
		$projectDir = "";
		}

	#loop though all the children
	for my $kid ($aNode->getChildNodes)
		{
		#check if this is an element node
		if($kid->getNodeType == XML::DOM::ELEMENT_NODE)
			{
			SWITCH:
				{
				my($tagName)=$kid->getTagName;
				my $text = $kid->getFirstChild;
				if ($text)
					{
					$text = $self->_RemoveRets($text->getData);
					}
				else
					{
					$text = "";
					}
				my $path = $self->_RelateToDir($projectDir, $text);

				if($tagName eq "input")
					{
					#get the input directory
					$self->_iInputDir( $path );
					last SWITCH;
					}
				if($tagName eq "output")
					{
					#get the output directory
					$self->_iOutputDir( $path );
					#check if the output directory exists
					if(!-d $self->_iOutputDir)
						{
						# create the output directory
						my $nullFile="";
						if ( (index($self->_iOutputDir(),':') != -1 ) )
							{
							$nullFile =
							  substr($self->_iOutputDir(), 0, index($self->_iOutputDir(),':')+1);
							}
						$nullFile = $nullFile."\\nul";
						open(NULL,">>$nullFile") or $self->_iLog->LogDie("The output directory '".$self->_iOutputDir."' is on a drive that doesn't exist, so cannot be created.");

						mkpath($self->_iOutputDir);
						}
					last SWITCH;
					}
				
				if($tagName eq "headers")
					{
					#get the headers directory
					$self->_iHeadersDir( $path );
					last SWITCH;
					}

				if($tagName eq "graphics")
					{
					#get the input directory
					$self->_iGraphicDir( $path );
					last SWITCH;
					}
				if($tagName eq "working")
					{
					#get the working directory
					$self->_iWorkingDir( $path );
					#check if the working directory exists
					if(!-d $self->_iWorkingDir)
						{
						# create the working directory
						my $nullFile="";
						if ( (index($self->_iWorkingDir(),':') != -1 ) )
							{
							$nullFile = substr($self->_iWorkingDir(),0,index($self->_iWorkingDir(),':')+1);
							}
						$nullFile = $nullFile."\\nul";
						open(NULL,">>$nullFile") or $self->_iLog->LogDie("The working directory '".$self->_iWorkingDir."' is on a drive that doesn't exist, so cannot be created.");

						mkpath($self->_iWorkingDir);
						}
					last SWITCH;
					}
				#otherwise
				$self->_iLog->LogDie($kid->getTagName." is not a recognised directory element");
				}
			}
		}

	#check if the headers directory was specified
	if ($self->_iHeadersDir() eq undef)
		{
		$self->_iHeadersDir($self->_iOutputDir());
		}

	#check if the headers directory exists
	if(!-d $self->_iHeadersDir)
		{
		# create the headers directory
		mkpath($self->_iHeadersDir);
		}
	}

################################################################################
#
# Function _RelateToDir
#
# Function as _RelateTo, but ensures backslash on the end
#
# Function takes: the fake cwd (can be relative to the real one),
#                 the path relative to that cwd
#
# Function Returns: the absolute path
#
# Function Uses:
#
# Notes:
################################################################################
sub _RelateToDir($$)
	{
	my $self = shift;
	my ($aCwd, $aPath) = @_;

	my $path=$self->_RelateTo($aCwd, $aPath);

	if ($path =~ /[^\\\/]$/)
		{
		$path = $path."\\";
		}
	
	return $path;
	}

################################################################################
#
# Function _RelateTo
#
# Function returns a path to another path as if the cwd was set as selected
#
# Function takes: the fake cwd (can be relative to the real one),
#                 the path relative to that cwd
#
# Function Returns: the absolute path
#
# Function Uses:
#
# Notes:
################################################################################
sub _RelateTo($$)
	{
	my $self = shift;
	my ($aCwd, $aPath) = @_;

	my $path;
	if (($aPath =~ /^[\\\/]/) || ($aPath =~ /:[\\\/]/))
		{
		$path = $aPath; # Path is absolute
		}
	else
		{
		# Path is relative to aCwd
		if (($aCwd =~ /^[\\\/]/) || ($aCwd =~ /:[\\\/]/))
			{
			$path = $aCwd; # aCwd is absolute
			}
		else	
			{
			# aCwd is relative to the real cwd
			$path = cwd();
		
			if ($path =~ /[^\\\/]$/)
				{
				# It doesn't end with a slash, yet also isn't empty
				$path = $path."\\";
				}
		
			$path = $path.$aCwd; # Go to the supplied cwd
			}

		if ($path =~ /[^\\\/]$/)
			{
			$path = $path."\\";
			}
		
		$path = $path.$aPath; # Move to the new path
		}

	# Convert unix slashes to DOS ones
	$path =~ s/\//\\/g;

	# Remove /dir/.. which cancel out
	while ($path =~ /\\[^\.\\]+\\\.\./)
		{
		$path =~ s/\\[^\.\\]+\\\.\.//;
		}
	
	return $path;
	}

################################################################################
#
# Function _ProcFilesNodes
#
# Function processes all the nodes in the files element
#
# Function takes: a reference to the files node
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _ProcFilesNodes($)
	{
	my $self=shift;
	my($aNode)=@_;

	my $projectDir = $self->_iProjectFile();
	$projectDir =~ s/[\\\/][^\\\/]+$/\\/; # remove filename from end
	if ($projectDir !~ /[\\\/]/)
		{
		# Or, if it's just the filename
		$projectDir = "";
		}
	
	#loop though all the children
	for my $kid ($aNode->getChildNodes)
		{
		#check if this is an element node
		if($kid->getNodeType == XML::DOM::ELEMENT_NODE)
			{
			SWITCH:
				{
				my($tagName)=$kid->getTagName;
				
				if($tagName eq "source")
					{
					#process the source files
					$self->_ProcSourceNodes($kid);
					last SWITCH;
					}
				if($tagName eq "destination")
					{
					#get the destination file
					$self->_iDestFile($self->_RemoveRets($kid->getFirstChild->getData));
					last SWITCH;
					}
				if($tagName eq "customization")
					{
					#get the customisation file
					$self->_iCustomizationFile($self->_RelateTo($projectDir, $self->_RemoveRets($kid->getFirstChild->getData)));
					last SWITCH;
					}
				if($tagName eq "graphicssource")
					{
					#get the graphics files
					$self->_ProcGraphicsSourceNodes($kid);
					last SWITCH;
					}
				if ($tagName eq "graphics")
					{
					#get the old-name graphics files
					$self->_ProcGraphicsSourceNodes($kid); # FIXME? Should we omit checking for these as an incentive?
					$self->_iLog->Log("Warning: <graphics> tag in <files> element should be renamed <graphicssource>\n");
					last SWITCH;
					}
				#otherwise
				$self->_iLog->LogDie($kid->getTagName." is not a recognised files element");
				}
			}
		}
	}

################################################################################
#
# Function _ProcSourceNodes
#
# Function processes all the nodes in the source element
#
# Function takes: a reference to the source node
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _ProcSourceNodes($)
	{
	my $self=shift;
	my($aNode)=@_;

	#loop though all the children
	for my $kid ($aNode->getChildNodes)
		{
		#check if this is an element node
		if($kid->getNodeType == XML::DOM::ELEMENT_NODE)
			{
			  SWITCH:
				{
				my($tagName)=$kid->getTagName;

				if($tagName eq "file")
					{
					#get the source file
					$self->_AddSourceFile($self->_RemoveRets($kid->getFirstChild->getData));
					last SWITCH;
					}
				elsif($tagName eq "xmlfile")
					{
					#get the xml source file
					$self->_AddXmlFile($self->_RemoveRets($kid->getFirstChild->getData));
					last SWITCH;
					}
				#otherwise
				$self->_iLog->LogDie($kid->getTagName." is not a recognised source element");
				}
			}
		}
	}

################################################################################
#
# Function _ProcGraphicsSourceNodes
#
# Function processes all the nodes in the graphics element
#
# Function takes: a reference to the source node
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub _ProcGraphicsSourceNodes($)
	{
	my $self=shift;
	my($aNode)=@_;
	
	#loop though all the children
	for my $kid ($aNode->getChildNodes)
		{
		#check if this is an element node
		if($kid->getNodeType == XML::DOM::ELEMENT_NODE)
			{
			SWITCH:
				{
				my($tagName)=$kid->getTagName;
			
				if($tagName eq "file")
					{
					#get the source file
					$self->_AddGraphicFile($self->_RemoveRets($kid->getFirstChild->getData));
					last SWITCH;
					}
				#otherwise
				$self->_iLog->LogDie($kid->getTagName." is not a recognised graphics element");
				}
			}
		}
	}

################################################################################
#
# Function _RemoveRets
#
# Function removes head and tail extra returns on a test element
#
# Function takes: the string to process
#
# Function Returns: the string without the extra returns
#
# Function Uses:
#
# Notes:
################################################################################
sub _RemoveRets($)
	{
	my $self = shift;

	my($aString)=@_;

	#remove any number of leading rets
	$aString =~ s/^(\n)+//g;
	#remove any number of trailing rets
	$aString =~ s/(\n)+$//g;
	
	return $aString;
	}

##############################################################################
#
# Function _ValidateFiles
#
# Function checks that all files which are stated in the project file are
#		   present
#
# Function takes: No arguments
#
# Function Returns: None
#
# Function Uses: _ValidateFileList
#
# Notes: Dies with an appropriate error if a file is missing
#
##############################################################################

sub _ValidateFiles()
	{
	my $self = shift;

	# Ensure RTF source files are present
	$self->_ValidateFileList($self->SourceFiles(),$self->InputDir());

	# Ensure graphic files are present
	$self->_ValidateFileList($self->GraphicFiles(),$self->GraphicDir());

	# Ensure XML source files are present
	$self->_ValidateFileList($self->XmlFiles(),$self->InputDir());

	# Delete the graphic files list - we are done with them now
	$self->_iGraphicFiles(undef);
	}

##############################################################################
#
# Function _ValidateFileList
#
# Function checks for the existence of a list of files in a given path
#
# Function takes: The list (reference) of files, and a string for the path
#
# Function Returns: None
#
# Function Uses:
#
# Notes: Dies with an appropriate error if a file is missing
#
##############################################################################

sub _ValidateFileList($$)
	{
	my $self = shift;
	my ($aFiles, $aPath) = @_;

	foreach my $file (@$aFiles)
		{
		if (!(-e $aPath.$file))
			{
			$self->_iLog->LogDie("Sorry, the file \"$aPath$file\" is listed in the project file, yet is not present. Either ensure there is a file there, or correct the project file.");
			}
		}
	}

################################################################################
#
# Function TEST
#
# Function the test code for the proj file object
#
# Function takes: none
#
# Function Returns: none
#
# Function Uses:
#
# Notes:
################################################################################
sub TEST
	{
	my $self = shift;

	print "#######################\n";
	print "Test1 store object data\n";
	
	print "filling up the data\n";
	$self->_iHelpFileUID("the help file UID");
	$self->_iInputDir("the input directory");
	$self->_iOutputDir("the output directory");
	$self->_iGraphicDir("the graphic directory");
	$self->_iWorkingDir("the working directory");
	
	$self->_AddSourceFile("source file 1");
	$self->_AddSourceFile("source file 2");
	$self->_AddSourceFile("source file 3");

	$self->_iDestFile("the output file");
	$self->_iCustomizationFile("the customization file");
	
	print "Recovering data\n";
	
	$self->PRINT;

	print "###################################\n";
	print "Test 2 testing pesky return removal\n";
	my($line)="this is a line with no returns";
	print $line. " | " . $self->_RemoveRets($line);
	$line="\nthis is a line with start and end returns\n";
	print $line. " | " . $self->_RemoveRets($line);
	$line="\n\n\n\nthis is a line with several returns\n\n\n\n";
	print $line. " | " . $self->_RemoveRets($line);
	$line="\n\n\n\nthis is a line with \n\n\nreturns at the start \n\n\nand in the middle\n\n\n";
	print $line. " | " . $self->_RemoveRets($line);
	
	print "\n############################################\n";
	print "Test 3 Testing parsing of a project file dom\n";

	my($text);
	my($file);

	print "constructing DOM object";
	my($doc)= new XML::DOM::Document;

	$doc->setXMLDecl($doc->createXMLDecl("1.0"));
	$doc->setDocType($doc->createDocumentType("cshproj","file:///h:/cshlpcmp/dtd/CSHproj.dtd"));
	$doc->setXMLStylesheet($doc->createXMLStylesheet("file:///h:/cshlpcmp/xsl/cshproj.xsl","cshproj","text/xsl"));
	
	my($cshProj)=$doc->createElement("cshproj");

	#create the help file uid
	my($helpfileUID) = $doc->createElement("helpfileUID");

	$text= $doc->createTextNode("0x123456789");
	$helpfileUID->appendChild($text);

	#create the dir
	my($dir) = $doc->createElement("directories");

	$cshProj->appendChild($dir);


	my($input) = $doc->createElement("input");
	$text = $doc->createTextNode("the input dir");
	$input->appendChild($text);

	my($output) = $doc->createElement("output");
	$text = $doc->createTextNode("the output dir");
	$output->appendChild($text);

	my($graphic) = $doc->createElement("graphics");
	$text = $doc->createTextNode("the graphic dir");
	$graphic->appendChild($text);

	my($working) = $doc->createElement("working");
	$text = $doc->createTextNode("the working dir");
	$working->appendChild($text);

	#add these directories to the directory element
	$dir->appendChild($input);
	$dir->appendChild($output);
	$dir->appendChild($graphic);
	$dir->appendChild($working);


	#create the files
	my($files) = $doc->createElement("files");

	#create the source element
	my($source)= $doc->createElement("source");

	#add ten files
	for my $count (1..10)
		{

		#create a file element
		$file= $doc->createElement("file");

		#create a text element
		$text=$doc->createTextNode("file$count");

		$file->appendChild($text);

		#add the file node to the source node
		$source->appendChild($file);
		}

	my($destination) = $doc->createElement("destination");
	$text = $doc->createTextNode("the destination file");
	$destination->appendChild($text);

	my($customization) = $doc->createElement("customization");
	$text = $doc->createTextNode("the customization file");
	$customization->appendChild($text);

	#add the file nodes to the files node
	$files->appendChild($source);
	$files->appendChild($destination);
	$files->appendChild($customization);

	#add the directory and the files to the cshproj
	$cshProj->appendChild($helpfileUID);
	$cshProj->appendChild($dir);
	$cshProj->appendChild($files);

	#add the cshproj element to the document
	$doc->appendChild($cshProj);

	print $doc->toString;

	$self->_ParseDoc($doc);

	$self->PRINT;
	}

################################################################################
#
# Function PRINT
#
# Function prints out the current contents of the projfile object
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
	print "the help file UID | ". $self->HelpFileUID ."\n";
	print "the input directory | ". $self->InputDir ."\n";
	print "the output directory | ". $self->OutputDir ."\n";
	print "the graphic directory | ". $self->GraphicDir ."\n";
	print "the working directory | ". $self->WorkingDir ."\n";

	#print the source files
	for my $sourceFile(@{$self->SourceFiles})
		{
		print "source file | ". $sourceFile ."\n";
		}

	print "the output file | ". $self->DestFile ."\n";
	print "the customization file | ". $self->CustomizationFile ."\n";
	}


1;

















