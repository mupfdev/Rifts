/* Copyright (c) 2001 Nokia. All rights reserved */

EpocSwitch enables you to switch between different epoc build 
enviroments (e.g. Crystal <-> Pearl).

EpocSwitch sits in the system tray and allows you to select which version 
of epoc you want to use by right clicking the icon.  You cal also double 
click the icon or select a command prompt off the menu to give you a console 
with the new environment.

To install EpocSwitch do the following:

1. Copy EpocSwitch.exe and settings.ini files to a directory on you local machine.

2. Edit the settings.ini file and specify the placement of your epoc 
   installations.  The text between the square braces is used to identify
   the installation.
   
   EPOCROOT is the path to the epoc sdk installation.
   EPOCPATH is the path to the gcc executables and the epoc utilities.
   EPOCICON is an optional setting for overriding the EpocSwitch system tray icon
            when the associated installation is selected. This specifies the
            full path and filename of a 16x16 pixel icon file.
   PROJECTPATH is the directory into which the command window will be opened.
   

3. Open up your system enviroment settings (Control Panel -> System -> Environment) 
   and remove any epoc related search paths from you path.

4. Add the following to your path %EPOCPATH%; and accept your changes.

5. Run EpocSwitch.exe and a system tray icon should appear.  Add this to your 
   start menu for convenience.
