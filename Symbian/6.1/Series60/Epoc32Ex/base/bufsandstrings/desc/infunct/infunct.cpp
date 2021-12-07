// InFunct.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// Examples to demonstrate the use of descriptors in function interfaces.

#include "CommonFramework.h"

//
// Literal text
//

_LIT(KDataTPtrC,"A TPtrC descriptor");
_LIT(KDataTPtr,"A TPtr descriptor");
_LIT(KDataTBufC,"A TBufC descriptor");
_LIT(KDataTBuf,"A TBuf descriptor");
_LIT(KDataHBufC,"An HBufC descriptor");

//
// Common format strings
//

_LIT(KCommonFormat2,"0x%02x ");

// A set of functions called by the example code
LOCAL_C void StringRead(const TDesC& aString); 
LOCAL_C void StringWrite(TDes& aString);       
LOCAL_C void BufferRead(const TDesC8& aBuffer); 
LOCAL_C void BufferWrite(TDes8& aBuffer);       
		 
// Do the example
LOCAL_C void doExampleL()
    {				   
				// We create four functions:
				// StringRead()
				// StringWrite()
				// BufferRead()
				// BufferWrite() 
				// to illustrate the use of descriptors
				// in function interfaces	
	
    TText      area[48]; 
	TPtrC      ptrc;
    TPtr       ptr(&area[0],48);

    TBufC<48>  bufc;
	TBuf<48>   buf;
	HBufC*     hbufcptr;

	hbufcptr = HBufC::NewL(48);

				// Set up some data	for our
				// descriptors
	ptrc.Set(KDataTPtrC);    // "A TPtrC descriptor"        
	ptr       = KDataTPtr;   // "A TPtr descriptor"
	bufc      = KDataTBufC;  // "A TBufC descriptor"
	buf       = KDataTBuf;   // "A TBuf descriptor"
	*hbufcptr = KDataHBufC;  //	"An HBufC descriptor"

				// We can pass a reference to all
				// descriptor types to StringRead() but	the 
				// function cannot change the 
				// descriptor content 
	StringRead(ptrc);                    // <-- a TPtrC
	StringRead(ptr);					 //	<-- a TPtr
	StringRead(bufc);					 //	<-- a TBufC
	StringRead(buf);					 //	<-- a TBuf
	StringRead(*hbufcptr);				 //	<-- an HBufC
				 	
				// We can only pass a reference to those
				// descriptors which are derived 
				// from TDes, to StringWrite();
				// these are the modifiable
				// descriptors: TPtr and TBuf. 
				//
				// The compiler will not permit a reference
				// to any other descriptor type to 
				// be passed. 
  //StringWrite(ptrc);                   <-- Illegal
    StringWrite(ptr);					 //	<-- a TPtr
  //StringWrite(bufc);					 <-- Illegal
	StringWrite(buf);					 //	<-- a TBuf
  //StringWrite(*hbufcptr);				 <-- Illegal

	delete hbufcptr;
    
	_LIT(KTxtPressToContinue," (press any key to continue)\n");
	console->Printf(KTxtPressToContinue);
	console->Getch();
				
	TUint8      data1[3] = {0x00,0x01,0x02};
	TUint8      data2[3] = {0x03,0x04,0x05};
	TUint8      data3[3] = {0x06,0x07,0x08};
	TUint8      data4[3] = {0x09,0x0A,0x0B};
	TUint8      data5[3] = {0x0C,0x0D,0x0E};
	 					      
				// Use the 8 bit variants explicitly for
				// general binary data.

				// ptrc8's data area is data1[]
				// ptr8's data areais data2[]
	TPtrC8      ptrc8(&data1[0],3);
	TPtr8       ptr8(&data2[0],3,3);

				// bufc8 contains a copy of data3[] data
				// buf8 contains a copy of data4[] data
				// hbufcptr8 contains a copy of data5[] data
    TBufC8<3>  bufc8= TPtrC8(&data3[0],3);
	TBuf8<3>   buf8= TPtrC8(&data4[0],3);
	HBufC8*    hbufcptr8;

	hbufcptr8  = HBufC8::NewL(3);
	*hbufcptr8 = TPtrC8(&data5[0],3);

				// We can pass a reference to all
				// descriptor types to BufferRead()
				// but the function cannot change the 
				// descriptor content 
	BufferRead(ptrc8);                   // <-- a TPtrC
	BufferRead(ptr8);					 //	<-- a TPtr
	BufferRead(bufc8);					 //	<-- a TBufC
	BufferRead(buf8);					 //	<-- a TBuf
	BufferRead(*hbufcptr8);				 //	<-- an HBufC
	
				// We can only pass a reference to those
				// descriptors which are derived 
				// from TDes, to BufferWrite; these are 
				// the modifiable descriptors: TPtr and TBuf. 
				//
				// The compiler will not permit a reference
				// to any other descriptor type to 
				// be passed. 
  //BufferWrite(ptrc8);                  <-- Illegal
    BufferWrite(ptr8);					 //	<-- a TPtr
  //BufferWrite(bufc8);					 <-- Illegal
	BufferWrite(buf8);					 //	<-- a TBuf
  //BufferWrite(*hbufcptr8);	 		 <-- Illegal			 	

  	delete hbufcptr8;
	}



// ************************************************
// Functions used by doInterface()
// ************************************************
LOCAL_C void StringRead(const TDesC& aString)
	{
				// A function which handles the content
				// of ANY descriptor passed to it but CANNOT
				// change that descriptor.
				//
				// Function displays descriptor content,
				// length and size.
				//
				// All descriptors can be passed to this 
				// function	because all descriptors are 
				// ultimately derived from TDesC.
				//
				// Note, however, that all data members and
				// function members in the TDes abstract class
				// cannot be accessed (recall that TDes is 
				// derived from TDesC).
				// These include the data member containing 
				// the maximum length and all modifying 
				// member functions.
	
	_LIT(KFormat5,"\"%S\"; %d; %d\n");
	console->Printf(KFormat5,&aString,aString.Length(),aString.Size());
	}


LOCAL_C void StringWrite(TDes& aString)
	{
				// A function which handles the content
				// of a descriptor derived from TDes;
				// i.e. the modifiable descriptors TPtr and
				// TBuf. 
				//
				// Function changes the content of the
				// referenced descriptors and then displays
				// their content, length, size and maximum
				// length.
				//
				// Note that the references to TPtrC, TBufC
				// and HBufC cannot be passed.  
	_LIT(KTxtModStringWrite," modified by StringWrite");			
    aString.Append(KTxtModStringWrite);
	_LIT(KFormat3,"\"%S\"; %d; %d; %d\n");
	console->Printf(KFormat3,
                    &aString,
					aString.Length(),
					aString.Size(),
					aString.MaxLength()
				   );
	}


LOCAL_C void BufferRead(const TDesC8& aBuffer)
	{
				// A function which handles the content
				// of ANY descriptor passed to it but
				// CANNOT change that descriptor.
				//
				// Function displays descriptor content,
				// length and size.
				//
				// All descriptors can be passed to this 
				// function because all descriptors are 
				// ultimately derived from TDesC.
				//
				// Note, however, that all data members 
				// and function members in the TDes abstract
				// class cannot be accessed (recall that 
				// TDes is derived from TDesC).
				// These include the data member containing
				// the maximum length and all modifying
				// member functions.
	for (TInt ix = 0; ix < aBuffer.Length(); ix++)
		console->Printf(KCommonFormat2,aBuffer[ix]);
	
	_LIT(KFormat4,"; %d; %d\n");
	console->Printf(KFormat4,aBuffer.Length(),aBuffer.Size());	
	}


LOCAL_C void BufferWrite(TDes8& aBuffer)
	{
				// A function which handles the content
				// of a descriptor derived from TDes;
				// i.e. the modifiable descriptors TPtr
				// and TBuf
				//
				// Function changes the content of the 
				// referenced descriptors and then displays
				// their content, length, size and maximum
				// length.
				//
				// Note that the references to TPtrC, TBufC
				// and HBufC cannot be passed.

	_LIT(KTxtModBufferWrite,"Modified by BufferWrite ");			
	console->Printf(KTxtModBufferWrite);
				
	for (TInt ix = 0; ix < aBuffer.Length(); ix++)
		{
		aBuffer[ix] += 0xF0;
		console->Printf(KCommonFormat2,aBuffer[ix]);
		}

	_LIT(KFormat1,"; %d; %d; %d\n");
	console->Printf(KFormat1,
		            aBuffer.Length(),
					aBuffer.Size(),
					aBuffer.MaxLength()
				   );
	}

	
