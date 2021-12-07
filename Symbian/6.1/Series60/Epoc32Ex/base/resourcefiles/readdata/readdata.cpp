// ReadData.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

/*
	This example shows how to load data from resource files
	into a class.
	
	It loads the resource identified as resource FIRST from the resource
	file. This is a simple resource of type DATA.
		
	The example constructs a CResData object to hold the 
	individual items corresponding to the items in a 
	DATA struct.

	The CResData object can also display the individual
	items at the test console. All WORD, BYTE and LONG
	are interpreted as signed values
*/
	
#include "CommonToResourceFilesEx.h"

#include "ReadData.h"
#include <ReadData.rsg>

				// Construct a new CResData object and place 
				// on the cleanup stack
CResData* CResData::NewLC(TResourceReader& aReader)
	{
	CResData* self=new (ELeave) CResData;
	CleanupStack::PushL(self);
	self->ConstructL(aReader);
	return self;
	}


				// Complete the construction of the 
				// CResData object using the supplied
				// reource reader representing the resource data.
				// The structure of the data is assumed to be
				// defined by the resource struct DATA in "ReadData.rh"
void CResData::ConstructL(TResourceReader& aReader)
	{
				// Interpret next bytes as a TInt16
	iWrd   = aReader.ReadInt16();
			
				// Interpret next bytes as a TInt16
	iFlags = aReader.ReadInt16();
					
				// Interpret next bytes as a TInt32
	iLng   = aReader.ReadInt32();

	iTxt	= aReader.ReadTPtrC();
				// Interpret the next byte as the length
				// of text. The text itself follows
				// this byte.
	iLtxt  = aReader.ReadHBufC16L(); 
				// Interpret the next byte as a TInt8
	iByt   = aReader.ReadInt8();
	
 				// Interpret next bytes as a TReal
	iDbl   = aReader.ReadReal64();
			
	}


				// Destructor needs to ensure that 
				// the HBufC descriptor iLtxt is destroyed.
CResData::~CResData()
	{
	if (iLtxt)
		delete iLtxt;
	}


				// Show the individual resource itens
				// at the test console.
void CResData::ShowData(const TInt aStructNum)
	{
	_LIT(KResourceItems,"Resource items (struct #%d):\n");
	_LIT(KResourceItems2,"Resource items:\n");
	_LIT(KWrdFormat,"wrd   = %d\n");
	_LIT(KFlags,"flags = ");
	_LIT(KEFlagItem,"EFlagItem");
	_LIT(KNewline,"\n");
	_LIT(KLngFormat,"lng   = %d\n");
	_LIT(KBytFormat,"byt   = %d\n");
	_LIT(KDblFormat,"dbl   = %S\n");
	_LIT(KTxtFormat,"txt   = %S\n");
	_LIT(KLtxtFormat,"ltxt  = %S\n");

	TBuf<16>	temp;
	TRealFormat	format(16,2);

	if (aStructNum)
		console->Printf(KResourceItems,
						   aStructNum
						  );
	else 
		console->Printf(KResourceItems2);

				//  * * * * * * * * *
	console->Printf(KWrdFormat,iWrd);

				//  * * * * * * * * *
		_LIT(KLtxt,"ltxt  = \n");
	console->Printf(KFlags);
	TUint		mask = 1;
	TBuf<256>	temp2;
	for (TInt ii = 0 ; ii < 16; ii++)
		{
		if (iFlags & mask)
			{
			temp2.Append(KEFlagItem);
			temp2.AppendNum(ii+1);
			temp2.Append('+');    
			}
		mask <<= 1;
		}
	if (temp2.Length())
		temp2.SetLength(temp2.Length()-1);
	console->Printf(temp2);
	console->Printf(KNewline);
		
				//  * * * * * * * * *
	console->Printf(KLngFormat,iLng);
				//  * * * * * * * * *
	console->Printf(KTxtFormat,&iTxt);

				//  * * * * * * * * *	
	if (iLtxt)
		console->Printf(KLtxtFormat,iLtxt);
	else
	    console->Printf(KLtxt);
				//  * * * * * * * * *
	console->Printf(KBytFormat,iByt);

				//  * * * * * * * * *
	temp.Num(iDbl,format);
	console->Printf(KDblFormat,&temp);
				
	}
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Do the example(s)

LOCAL_C void doExampleL()
    {
		// Declare a resource file
	RResourceFile resourceFile;
	
		// Open the resource file
	#if defined(__WINS__)
	_LIT(KZSystemDataRsc,"Z:\\system\\data\\ReadData.rsc");
	resourceFile.OpenL(fsSession, KZSystemDataRsc);
	#endif

	#if defined(__ARM__)
	_LIT(KCSystemDataRsc,"C:\\system\\data\\ReadData.rsc");
	resourceFile.OpenL(fsSession, KCSystemDataRsc);
	#endif
	
		// Read the first resource & construct a resource reader
	HBufC8* res = resourceFile.AllocReadLC(FIRST);

	TResourceReader theReader;
	theReader.SetBuffer(res);

		// construct a CResData object to contain
		// the simple resource of type DATA.
	CResData* resData = CResData::NewLC(theReader);

		// Can now remove resData from the cleanup stack
	CleanupStack::Pop();

		// finished with res
	CleanupStack::PopAndDestroy(); 

		// display data
	resData->ShowData();

		// destroy the CResData 
	delete resData;

		// finished with resource file, so close it.
	resourceFile.Close();
	}
	 

