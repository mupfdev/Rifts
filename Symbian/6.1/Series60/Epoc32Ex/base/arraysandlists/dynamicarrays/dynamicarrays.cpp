// DynamicArrays.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// Examples to demonstrate arrays

#include "CommonFramework.h"
#include <e32math.h>

//
// Common literal text
//

_LIT(KMsgPressAnyKey," (press any key to continue)\n");
_LIT(KMsgInsert,"\n\n--->InsertL");
_LIT(KMsgDelete,"\n\n--->Delete");
_LIT(KMsgNewLine,"\n");

//
// Common format strings
//
_LIT(KCommonFormat2,"\nLength()=%d");
_LIT(KCommonFormat3,"\nCount()=%d");
_LIT(KCommonFormat4,"\n%S");
_LIT(KCommonFormat5,"Count()=%d");

//
// A T type class used in the example demonstrating the:
// CArrayFixFlat class
// 
class TElement
	{
public :
	TElement();
public :
	TBuf<4> iData;
	};

TElement::TElement()
	{
	_LIT(KTextBase,"BASE");
	iData = KTextBase;
	}
		 
//
// A CBase derived class used in the example demonstrating the CArrayPtrFlat
// array
//
class CElement : public CBase
	{
public :
	CElement();
	~CElement();
	void SetTextL(const TDesC& aText);
public :
	HBufC* iBuf;
	};

CElement::CElement()
	{
	}

CElement::~CElement()
	{
	delete iBuf;
	}

void CElement::SetTextL(const TDesC& aText)
	{
	if (!iBuf)
		{
		iBuf  = HBufC::NewL(aText.Length());
		*iBuf = aText;	
		return;
		}

	if (aText.Length() > iBuf->Length())
		{
		delete iBuf;
		iBuf  = HBufC::NewL(aText.Length());
		*iBuf = aText;
		}
	else
		{
		*iBuf = aText;
		if (aText.Length() < iBuf->Length())
			iBuf  = iBuf->ReAllocL(aText.Length()); // reclaim space
		}
	}


// Do the example
LOCAL_C void doExampleL()
    {				  
	TInt forix;
	TInt value;

	//************************************************************
	// Demonstrate a general fixed length array using
	// a flat buffer
	//************************************************************
				
	
	CArrayFixFlat<TElement>* fixflat;
	
				// Construct array of TElement objects where the iData
				// data member of each element contains "X0", "X1", etc
				// Uses the AppendL() function to add the members
				// and the [] operator to access elements.
    fixflat = new (ELeave) CArrayFixFlat<TElement>(3);	
	
	TElement theElement;

	_LIT(KFormat1,"X%u");
	for (value = 0; value < 3; value++) 
		{
		theElement.iData.Format(KFormat1,value);
		fixflat->AppendL(theElement);
		}

				// Show length of each element
	console->Printf(KCommonFormat2,fixflat->Length());

				// Show number of elements
	console->Printf(KCommonFormat3,fixflat->Count());

				// Show each element
	for (forix = 0; forix < fixflat->Count(); forix++)
		console->Printf(KCommonFormat4,&(*fixflat)[forix].iData);	
		
			//
	 		// InsertL  * * * * * * * * * 
			//
	console->Printf(KMsgInsert);
	console->Printf(KMsgPressAnyKey);
	console->Getch();
	
				// Insert elements
				// ... at the beginning,
	_LIT(KMsgBEG,"BEG");
	theElement.iData = KMsgBEG;
	fixflat->InsertL(0,theElement);
				
				// ... near the middle,
	_LIT(KMsgMID,"MID");
	theElement.iData = KMsgMID;
	fixflat->InsertL(2,theElement);

				// ... at the end.
				// This is the same as using the AppendL() function
	_LIT(KMsgEND,"END");
	theElement.iData = KMsgEND;
	fixflat->InsertL(fixflat->Count(),theElement);

				// Show number of elements
	console->Printf(KCommonFormat5,fixflat->Count());

				// Show each element
	for (forix = 0; forix < fixflat->Count(); forix++)
		console->Printf(KCommonFormat4,&(*fixflat)[forix].iData);	
		

			//
	 		// Delete  * * * * * * * * * 
			//
	console->Printf(KMsgDelete);
	console->Printf(KMsgPressAnyKey);
	console->Getch();
	
			// Delete the 2nd, 4th and 5th elements. Note:
			//
			//  1. We use position to identify the elements (i.e. offset)
			//  2. As elements are deleted, the position of other
			//     elements changes.
				
	fixflat->Delete(1);		// delete the 2nd
	fixflat->Delete(2,2);   // delete what are now the 3rd and 4th

	fixflat->Compress();    // compress the array

				// Show number of elements
	console->Printf(KCommonFormat5,fixflat->Count());

				// Show each element
	for (forix = 0; forix < fixflat->Count(); forix++)
		console->Printf(KCommonFormat4,&(*fixflat)[forix].iData);	

			//
	 		// Reset  * * * * * * * * * 
			//
	_LIT(KMsgReset,"\n\n--->Reset");
	console->Printf(KMsgReset);
	console->Printf(KMsgPressAnyKey);
	console->Getch();
		
				// reset the array (i.e. empty it)
	fixflat->Reset();

				// Show number of elements
	console->Printf(KCommonFormat5,fixflat->Count());

				// Show each element
	for (forix = 0; forix < fixflat->Count(); forix++)
		console->Printf(KCommonFormat4,&(*fixflat)[forix].iData);	
		
			//
	 		// ExpandL & ExtendL  * * * * * * * * * 
			//
	_LIT(KMsgExpandExtend,"\n\n--->ExpandL & ExtendL");
	console->Printf(KMsgExpandExtend);
	console->Printf(KMsgPressAnyKey);
	console->Getch();

				// re-build the array
	_LIT(KFormat6,"%u");
	for (value = 0; value < 3; value++) 
		{
		theElement.iData.Format(KFormat6,value);
		fixflat->AppendL(theElement);
		}
				// Expand by constructing a new element at position 1.
				// Extend the array.
				//
				// Note the use of the TElement default constructor
				// in both cases
	fixflat->ExpandL(1);
	fixflat->ExtendL();

				// Show number of elements
	console->Printf(KCommonFormat5,fixflat->Count());

				// Show each element
	for (forix = 0; forix < fixflat->Count(); forix++)
		console->Printf(KCommonFormat4,&(*fixflat)[forix].iData);	
		

			//
	 		// ResizeL * * * * * * * * * * * * 
			//
	_LIT(KMsgResize,"\n\n--->ResizeL");
	console->Printf(KMsgResize);
	console->Printf(KMsgPressAnyKey);
	console->Getch();

				// Resize the array so that it only contains
				// one element
	fixflat->ResizeL(1);
	
				// Resize so that it contains 3 elements.
				// The two new elements are bit-wise copies 
				// of a TElement object constructed using 
				// its default constructor.
	fixflat->ResizeL(3);

				// Resize so that it contains 5 elements. 
				// The two new elements are bit-wise copies of
				// the TElement object passed through 
				// the reference. 
	_LIT(KMsgXXX,"XXX");
	theElement.iData = KMsgXXX;
	fixflat->ResizeL(5,theElement);

				// Show number of elements
	console->Printf(KCommonFormat5,fixflat->Count());

				// Show each element
	for (forix = 0; forix < fixflat->Count(); forix++)
		console->Printf(KCommonFormat4,&(*fixflat)[forix].iData);
	
			//
	 		// SetReserveL * * * * * * * * * * * * 
			//
	_LIT(KMsgSetReserve,"\n\n--->SetReserveL");
	console->Printf(KMsgSetReserve);
	console->Printf(KMsgPressAnyKey);
	console->Getch();

				// Reserve sufficient space to append another
				// five elements.
				// This function may leave if there is 
				// insufficient memory.
				// NOTE: this does NOT increase the number of 
				//       elements in the array.
	fixflat->SetReserveL(5);
				
				// We can now append five elements and be sure that
				// no leave will occur.
	_LIT(KMsgDoubleAtoE,"AABBCCDDEE");
	TBufC<10> source(KMsgDoubleAtoE);
	for (forix = 0; forix < source.Length(); forix+=2)
		{
		theElement.iData = source.Mid(forix,2);
		fixflat->AppendL(theElement);	
		}
	
	
				// Show number of elements
	console->Printf(KCommonFormat5,fixflat->Count());

				// Show each element
	for (forix = 0; forix < fixflat->Count(); forix++)
		console->Printf(KCommonFormat4,&(*fixflat)[forix].iData);
	console->Printf(KMsgNewLine);
	
				// Delete the array
	delete fixflat;

	//************************************************************
	// Demonstrate an array of pointers to CBase
	// derived objects. Uses the specialised array CArrayPtrFlat
	//************************************************************
	_LIT(KMsgArrayOfPointers,"\nARRAYS OF POINTERS (to CBase derived objects)\n");
	console->Printf(KMsgArrayOfPointers);

	CArrayPtrFlat<CElement>* ptrflat;
	CElement*  ptr;

				// Construct an array of four CElement objects each 
				// containing the text "First" "second" etc
				// Uses the AppendL() function to add the members
				// and the [] operator to access elements.
    ptrflat = new (ELeave) CArrayPtrFlat<CElement>(16);	
	
	ptr = new (ELeave) CElement;
	_LIT(KMsgFirstElement,"First Element");
	ptr->SetTextL(KMsgFirstElement);
	ptrflat->AppendL(ptr);
	
	
	ptr = new (ELeave) CElement;
	_LIT(KMsgSecondElement,"Second Element");
	ptr->SetTextL(KMsgSecondElement);
	ptrflat->AppendL(ptr);

	
	ptr = new (ELeave) CElement;
	_LIT(KMsgThirdElement,"Third Element");
	ptr->SetTextL(KMsgThirdElement);
	ptrflat->AppendL(ptr);

	
				// Show length of each element
	console->Printf(KCommonFormat2,ptrflat->Length());

				// Show number of elements
	console->Printf(KCommonFormat3,ptrflat->Count());

				// Show each element
	for (forix = 0; forix < ptrflat->Count(); forix++)
		console->Printf(KCommonFormat4,((*ptrflat)[forix])->iBuf);	

			//
	 		// InsertL  * * * * * * * * * 
			//
	console->Printf(KMsgInsert);
	console->Printf(KMsgPressAnyKey);
	console->Getch();
	
				// Insert an element at the beginning 
				// of the array.
	
	ptr = new (ELeave) CElement;
	_LIT(KMsgInsertedBeg,"Inserted @ beginning Element");
	ptr->SetTextL(KMsgInsertedBeg);
	ptrflat->InsertL(0,ptr);

				// Show number of elements
	console->Printf(KCommonFormat5,ptrflat->Count());

				// Show each element
	for (forix = 0; forix < ptrflat->Count(); forix++)
		console->Printf(KCommonFormat4,((*ptrflat)[forix])->iBuf);	

			//
	 		// Delete  * * * * * * * * * 
			//
	console->Printf(KMsgDelete);
	console->Printf(KMsgPressAnyKey);
	console->Getch();

			// Delete the last two elements from the array BUT 
			// first we must get a reference to those elements
			// (pointers to CElement objects) otherwise 
			// the CElement objects are orphaned.
			//
			// Here, we destroy those CElement objects.
			//
			// There are two alternative ways of indexing into 
			// the array, using either At() or the [] operator

			// NOTE that the code below could be compressed to:
			//
			// delete (*ptrflat)[ptrflat->Count()-1];
			// delete (*ptrflat)[ptrflat->Count()-2];
			// ptrflat->Delete(ptrflat->Count()-2,2);
	TInt index;
	
	index = ptrflat->Count();

	ptr = (*ptrflat)[--index];
	ptrflat->Delete(index);
	delete ptr;

	ptr = ptrflat->At(--index);
	ptrflat->Delete(index);
	delete ptr;

				// Show number of elements
	console->Printf(KCommonFormat5,ptrflat->Count());

				// Show each element
	for (forix = 0; forix < ptrflat->Count(); forix++)
		console->Printf(KCommonFormat4,((*ptrflat)[forix])->iBuf);	

			//
	 		// At & the [] operator * * * * * * * * * * * * 
			//
	_LIT(KMsgAt,"\n\n--->At() and the operator []");
	console->Printf(KMsgAt);
	console->Printf(KMsgPressAnyKey);
	console->Getch();

				// Make a change to the object pointed to by the first element in the array
	_LIT(KMsgNewTextFirst,"New text for the first CElement");
	_LIT(KMsgNewTextSecond,"New text for the second CElement");
	(*ptrflat)[0]->SetTextL(KMsgNewTextFirst);
	ptrflat->At(1)->SetTextL(KMsgNewTextSecond);

				// Show number of elements
	console->Printf(KCommonFormat5,ptrflat->Count());

				// Show each element
	for (forix = 0; forix < ptrflat->Count(); forix++)
		console->Printf(KCommonFormat4,((*ptrflat)[forix])->iBuf);	

			//
	 		// ResetAndDestroy  * * * * * * * * * 
			//
	_LIT(KMsgResetDestroy,"\n\n--->ResetAndDestroy");
	console->Printf(KMsgResetDestroy);
	console->Printf(KMsgPressAnyKey);
	console->Getch();

				// destroy all of the CElement objects and reset the 
				// array.
	ptrflat->ResetAndDestroy();

				// Show number of elements
	console->Printf(KCommonFormat3,ptrflat->Count());

				// Show each element
	for (forix = 0; forix < ptrflat->Count(); forix++)
		console->Printf(KCommonFormat4,((*ptrflat)[forix])->iBuf);	
	
	console->Printf(KMsgNewLine);

				// Delete the array
	delete ptrflat;


}

 	



	
	
