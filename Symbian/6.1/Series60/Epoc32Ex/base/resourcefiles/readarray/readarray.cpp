// ReadArray.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

/*
	This example shows how to load data from resource files
	into a class.
	
    It loads the resource identified as SECOND from the resource file
	This is an array of DATA structs. 

    (The resource FIRST is not used in this example)
		
	The example constructs a CResDataArray object to contain  
	an array of CResData objects, one for each DATA struct 
	in the array.
	
	The CResDataArray object can also display the individual 
	items of each DATA struct at the test console. All WORD, BYTE
	and LONG are interpreted as signed values.

    The example follows on from the ReadData example
*/
	
#include "CommonToResourceFilesEx.h"
#include "ReadArray.h"
#include <ReadArray.rsg>

				// Construct a new CResDataArray object and
				// place on the cleanup stack
CResDataArray* CResDataArray::NewLC(TResourceReader& aReader)
	{
	CResDataArray* self=new (ELeave) CResDataArray;
	CleanupStack::PushL(self);
	self->ConstructL(aReader);
	return self;
	}


				// Complete the construction of the 
				// CResDataArray object by constructing an array 
				// of (pointers to) CResData objects.
				//
				// Granularity of iDataArray is 3 because we know
				// that only 3 elements are to be added in
				// this example.
void CResDataArray::ConstructL(TResourceReader& aReader)
	{
	iDataArray = new (ELeave) CArrayPtrFlat<CResData> (3); 
	TRAPD(error,AddDataL(aReader));
	if (error)
		{
		iDataArray->ResetAndDestroy();
		delete iDataArray;
		User::Leave(error);
		}
	}


				// Destructor needs to ensure that 
				// the array of (pointers to) CResData
				// objects is destroyed.
CResDataArray::~CResDataArray()
	{
	if (iDataArray)
		{
		iDataArray->ResetAndDestroy();
		delete iDataArray;
		}
	}


				// For each DATA element within the resource,
				// construct a CResData object and add its
				// pointer into the array.
void CResDataArray::AddDataL(TResourceReader& aReader)
	{
	TInt	index;
	TInt	number;
	
				// The first WORD contains the number 
				// of DATA structs within the resource
	number = aReader.ReadInt16();
	
				// Add all newly created CResData objects 
				// to the cleanup stack before adding 
				// to the array
	for (index = 0; index < number ; index++)
		{
		CResData* resData = CResData::NewLC(aReader);
		iDataArray->AppendL(resData);
		CleanupStack::Pop(); // now resData safely in array
		}
	}

				// Show the individual resource items for 
				// each DATA struct in the resource at the 
				// test console.
void CResDataArray::ShowAllData()
	{
	_LIT(KPressAnyKeyToContinue," -->press any key to continue\n\n");
	TInt count;

	count = (iDataArray? iDataArray->Count() : 0);
	
	for (TInt index = 0; index < count; index++)
		{
		(*iDataArray)[index]->ShowData(index+1);
		console->Printf(KPressAnyKeyToContinue);
		console->Getch();
		}
	}


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
				// defined by the resource struct DATA in "baarray.rh"
void CResData::ConstructL(TResourceReader& aReader)
	{
				// Interpret next bytes as a TInt16
	iWrd   = aReader.ReadInt16();
			
				// Interpret next bytes as a TInt16
	iFlags = aReader.ReadInt16();
					
				// Interpret next bytes as a TInt32
	iLng   = aReader.ReadInt32();

	TPtrC8 temp((TText8*)aReader.Ptr());

	(iTxt.Des()).Copy(temp);   
	aReader.Advance(temp.Size()+2);
					 				
				// Interpret the next byte as the length
				// of text. The text itself follows
				// this byte.
	iLtxt  = aReader.ReadHBufCL(); 
					
				// Interpret the next byte as a TInt8
	iByt   = aReader.ReadInt8();
	
 				// Interpret next bytes as a TReal
	iDbl   = aReader.ReadReal64();
			
				// Interpret the next bytes as a zero
				// terminated string. The string will have 
				// a maximum length defined by the
				// symbol TEXTMAX 
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
	_LIT(KLtxt,"ltxt  = \n");

	TBuf<16>	temp;
	TRealFormat	format(16,2);

	if (aStructNum)
		console->Printf(KResourceItems,aStructNum);
	else 
		console->Printf(KResourceItems2);

				//  * * * * * * * * *
	console->Printf(KWrdFormat,iWrd);

				//  * * * * * * * * *
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
	console->Printf(KBytFormat,iByt);

				//  * * * * * * * * *
	temp.Num(iDbl,format);
	console->Printf(KDblFormat,&temp);

				//  * * * * * * * * *
	console->Printf(KTxtFormat,&iTxt);

				//  * * * * * * * * *	
	if (iLtxt)
		console->Printf(KLtxtFormat,iLtxt);
	else
	    console->Printf(KLtxt);
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
	_LIT(KZSystemDataArrayRsc,"Z:\\system\\data\\ReadArray.rsc");
	resourceFile.OpenL(fsSession, KZSystemDataArrayRsc);
	#endif

	#if defined(__ARM__)
	_LIT(KCSystemDataArrayRsc,"C:\\system\\data\\ReadArray.rsc");
	resourceFile.OpenL(fsSession, KCSystemDataArrayRsc);
	#endif

		// Read the second resource & construct a resource reader
	HBufC8* res = resourceFile.AllocReadLC(SECOND);
	
	TResourceReader theReader;
	theReader.SetBuffer(res);

		// Construct a CResDataArray object to contain
		// the array of CResData objects, and add the elements to it
	CResDataArray* resDataArray = CResDataArray::NewLC(theReader);

		// Can now remove resDataArray from cleanup stack
	CleanupStack::Pop();
	
		// finished with res
	CleanupStack::PopAndDestroy();

		// display all data
	resDataArray->ShowAllData();

		// finished with CResDataArray 
	delete resDataArray;
	
		// finished with resource file, so close it 
	resourceFile.Close();
	} 

