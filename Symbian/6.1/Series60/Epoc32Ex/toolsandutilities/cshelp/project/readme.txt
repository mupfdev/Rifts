Note:

Paths which are relative (i.e. do not start with either a slash or a drive letter) are used as 
paths relative to the directory containing the project file. 

For example, a graphics directory that is located in the same directory as the project file is specified as follows:
	
	<graphics></graphics>

Directories that are not located within the same directory as the project file use '..\'  to mean the parent directory, for example:
	<output>..\..\..\..\..\epoc32\wins\c\system\help\</output>
	
Directories always should end with a backslash.