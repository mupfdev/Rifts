// RangeChecking.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//
//
// Code to demonstrate the range checking wrapper class
// for C++ arrays; i.e. the TFixedArray<class T,TInt S>.

#include "CommonFramework.h"

//
// Definition of the TTest class
//
class TTest
	{	
public:
	TTest();
	TTest(TInt aValue);
	void SetValue(TInt aValue);
	TInt GetValue() const;
private :
	TInt     iX;
	TBuf<8>  iPadding; // never used in this example
	};

TTest::TTest()
	: iX(1)
	{}

TTest::TTest(TInt aValue)
	: iX(aValue)
	{}

TInt TTest::GetValue() const
	{
	return iX;
	}

void TTest::SetValue(TInt aValue)
	{
	iX = aValue;
	}

//
// Definition of the CTest class
//
class CTest : public CBase 
	{	
public:
	static CTest* NewL(const TDesC& aText);
	~CTest();
	void ConstructL(const TDesC& aText);
private :
	HBufC*   iSomeText;
	};	

CTest* CTest::NewL(const TDesC& aText)
	{
	CTest* self=new (ELeave) CTest;
	CleanupStack::PushL(self);
	self->ConstructL(aText);
	CleanupStack::Pop();
	return self;
	}

void CTest::ConstructL(const TDesC& aText)
	{
	iSomeText = aText.AllocL();
	}

CTest::~CTest()
	{
	delete iSomeText;
	}



// Some source data
const TTest data[] = {TTest(1),TTest(2),TTest(3),TTest(4)};

//
// main body of the example
//
LOCAL_C void doExampleL()
    {

	// A C++ array of 4 elements of type class TTest.
	//
	// Effectively the same as if we had explicitly
	// declared: TTest array[4];
	//
	TFixedArray<TTest,4> array;
	
			
	//
	// Copy 4 elements into the array.
	//
	// We could have constructed the array by:
	// TFixedArray<TTest,4> array(&data[0],4);
	array.Copy(&data[0],4);

	//
	// Trying to execute the following call would result
	// in a USER 133 panic in a debug build. The range checking
	// stops us from trying to write to a 5th element which 
	// does not (legitimately) exist.
	//
	//array.Copy(&array[0],5);

	//
	// Count() should return the number of array elements, i.e. 4
	//
	_LIT(KTxtFormat1,"Array size is %d\n");
	console->Printf(KTxtFormat1,array.Count());
	
	//
	// Length() should return the size of an array element; here
	// that should be the size of a TTest object.
	//
	_LIT(KTxtFormat2,"Length of an array element is %d\n\n");
	console->Printf(KTxtFormat2,array.Length());
	
	//
	// Pointers to the beginning and end of the array
	//
	_LIT(KTxtFormat3,"Array ends   at ---> 0x%x\n      starts at ---> 0x%x\n");
	_LIT(KTxtFormat4,"Difference is decimal %d bytes (hopefully 4 times the size of TTest)\n\n");
	console->Printf(KTxtFormat3,array.End(),array.Begin());
	console->Printf(KTxtFormat4,((TUint8*)array.End() - (TUint8*)array.Begin()));
	
	//
	// Access the second element of the array and change it
	// using At().
	//
	array.At(1).SetValue(100);

	//
	// Access the second element of the array and change it
	// using the [] operator.
	//
	array[1].SetValue(99);
	
	// The following call using At() will panic in both a
	// release and a debug build.
	//array.At(4).SetValue(100);

	// The following call using the [] operator will only panic
	// in a debug build. In a release build, this  code
	// will go undetected and cause damage.
	//array[4].SetValue(99);
	
	// In this example we can also replace an entire element;
	// here we replace the third element.
	// In more complex cases, the TTest class could have 
	// a suitable operator= defined 
	_LIT(KTxtFormat5,"The new 3rd element has value %d\n\n");
	TTest x(256);
	array.At(2) = x; 
	console->Printf(KTxtFormat5,array.At(2).GetValue());

	//
	// Construct a generic array.
	//
	// Once done, we can use the standard TArray functions
	// Count() and operator[]
	// Remember that a TArray cannot be used to change data in the
	// original array.
	//
	TArray<TTest> generic = array.Array();

	_LIT(KTxtFormat6,"Array size as reported by TArray's Count() is %d\n\n");
	console->Printf(KTxtFormat6,generic.Count());

	// The value contained in the 2nd TTest element of the array
	// using the generic array's operator[]
	_LIT(KTxtFormat7,"Value contained in the 2nd TTest element of\nthe array using TArray's operator[] is %d\n\n");
	console->Printf(KTxtFormat7,generic[1].GetValue());

	// the following line will NOT compile
	//generic[1].SetValue(101);

	
	// This is A C++ array of 4 elements to contain
	// pointers to CTest type objects.
	// This is equivalent to
	// the naked declaration:
	// CTest* ptrarray[4];
	// 
	//
	TFixedArray<CTest*,4> ptrarray;

	
	// Allocate 4 CTest objects and put their pointers
	// into the array.
	//
	// We ignore cleanup issues arising from possible
	// failure of 'new'; this would need to be
	// considered in a real application.

	_LIT(KTxtDefault,"Default text");
	_LIT(KTxtState1,"The 4 elements are:     ");
	_LIT(KTxtState2,"After Reset() they are: ");
	_LIT(KTxtNewLine,"\n");
	_LIT(KTxtFormat8,"0x%08x ");
			
	CTest* ptr;
	TInt   ix;
	for (ix = 0; ix<4; ix++)
		{
		ptr = CTest::NewL(KTxtDefault);
		ptrarray.At(ix) = ptr;
		}

	console->Printf(KTxtState1);
	for (ix = 0; ix<4; ix++)
		{
		console->Printf(KTxtFormat8,ptrarray[ix]);
		}
	console->Printf(KTxtNewLine);

	// Now delete all the CTest objects
	ptrarray.DeleteAll();

	// Set the array's data members to NULL 
	ptrarray.Reset();

	console->Printf(KTxtState2);
	for (ix = 0; ix<4; ix++)
		{
		console->Printf(KTxtFormat8,ptrarray[ix]);
		}
	console->Printf(KTxtNewLine);

	}
