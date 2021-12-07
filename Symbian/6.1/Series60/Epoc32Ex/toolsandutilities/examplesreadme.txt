This file gives a brief overview of how to create and install installation files.

The following example package files are provided:
 
- HelloWorld.pkg — Demonstrates the most basic Installation File Generator functionality. 
- HelloWorldText.pkg — Demonstrates how a text file is viewed on the PC, and a file is automatically run on the target platform, during installation. 
- HelloWorldLangs.pkg — Demonstrates how to install applications supporting more than one language. 
- HelloWorldSis.pkg — Demonstrates how an installation file bundles other sis files. The embedded .sis file is Shapes.sis provided with this example.
- HelloWorldOptions.pkg — Demonstrates how to use an options line and condition block in an installation. 
- HelloWorldSecure.pkg — Demonstrates the use of a package signature for secure installation. A key and certificate must be generated before creation of the .sis file using the Certification Generator.

To create an installation (.sis) file invoke the Installation File Generator (Makesis) on the required .pkg file. 

Use the emulator's install/remove program to install the sis file.


  
