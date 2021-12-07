// MultiRead2.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

/*
	This example shows how to use multiple resource files with cross-referenced
	resources.  It depends on the resource file created for the MultiRead1 project.

	It introduces a second resource file, MultiRead2, which contains an LLINK
	to a resource defined in the MultiRead1 project. The important point to note is
	that the effect of introducing this second resource file is minimal: just
	another #include file; and the logic in doExampleL() would be identical whether
	the LLINK pointed to another resource in the same file or a different file.
*/

#include "CommonToResourceFilesEx.h"
#include <MultiRead2.rsg> // user resources
#include "MultiRead.h"    // definition of multi-resource-reader class

// Do the example
void doExampleL()
	{
	_LIT(KFormat,"%S\n");

	// allocate multi-reader
	CMultipleResourceFileReader* multiReader =
			CMultipleResourceFileReader::NewLC();

		// open a couple of resource files
	#if defined(__WINS__)
			// add MultiRead1 version 23
	_LIT(KZSystemDataBasigbRsc,"Z:\\system\\data\\MultiRead1.rsc");
	multiReader->AddResourceFileL(KZSystemDataBasigbRsc,23);
			// add MultiRead2 version 17
	_LIT(KZSystemDataBasiguRsc,"Z:\\system\\data\\MultiRead2.rsc");
	multiReader->AddResourceFileL(KZSystemDataBasiguRsc,17);
	#endif

	#if defined(__ARM__)
			// add MultiRead1 version 23
	_LIT(KCSystemDataBasigbRsc,"C:\\system\\data\\MultiRead1.rsc");
	multiReader->AddResourceFileL(KCSystemDataBasigbRsc,23);
			// add MultiRead2 version 17
	_LIT(KCSystemDataBasiguRsc,"C:\\system\\data\\MultiRead2.rsc");
	multiReader->AddResourceFileL(KCSystemDataBasiguRsc,17);
	#endif
	
	// read resource that returns a reference to another resource
	HBufC8* refBuffer=multiReader->AllocReadLC(R_USER_HELLOREF);
	TResourceReader theReader;
	theReader.SetBuffer(refBuffer);
	TInt referencedId=theReader.ReadInt32(); // treat resource as integer
	CleanupStack::PopAndDestroy(); // refBuffer
	// read the other resource
	HBufC8* dataBuffer=multiReader->AllocReadLC(referencedId);
	TResourceReader reader;
	reader.SetBuffer(dataBuffer);
	TPtrC textdata = reader.ReadTPtrC();

	// write string to test console
	console->Printf(KFormat, &textdata);
	// clean up data buffer
	CleanupStack::PopAndDestroy(); // finished with dataBuffer
	// cleanup multi-reader
	CleanupStack::PopAndDestroy(); // multi-reader
	}
