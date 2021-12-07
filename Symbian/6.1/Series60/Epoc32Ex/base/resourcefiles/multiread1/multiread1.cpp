// MultiRead1.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

/*
	This example, together with MultiRead2, shows how to use multiple
	resource files with cross-referenced resources.

    It introduces the class CMultipleResourceFileReader, capable of
	reading resources from multiple	resource files. However, only one
	resource file is used. The example MultipleReader2 uses more than one resource file
*/

#include "CommonToResourceFilesEx.h"

#include <MultiRead1.rsg> // resources
#include "MultiRead.h"

// Do the example
void doExampleL()
	{
	_LIT(KFormat,"%S\n");

	// allocate multi-reader
	CMultipleResourceFileReader* multiReader =
			CMultipleResourceFileReader::NewLC();

		// open a resource file
	#if defined(__WINS__)
			// add MultipleReader1 version 23
	_LIT(KZSystemDataBasigbRsc,"Z:\\system\\data\\MultiRead1.rsc");
	multiReader->AddResourceFileL(KZSystemDataBasigbRsc,23);
	#endif

	#if defined(__ARM__)
			// add MultipleReader1 version 23
	_LIT(KCSystemDataBasigbRsc,"C:\\system\\data\\MultiRead1.rsc");
	multiReader->AddResourceFileL(KCSystemDataBasigbRsc,23);
	#endif

	// read string resource from file into a descriptor
	HBufC8* dataBuffer=multiReader->AllocReadLC(R_BASE_HELLO);
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

