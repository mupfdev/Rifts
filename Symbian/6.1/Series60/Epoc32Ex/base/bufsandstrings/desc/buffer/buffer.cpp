// Buffer.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// Examples to demonstrate the basic ideas of
// buffer descriptors.

#include "CommonFramework.h"

//
// Common literal text
//
_LIT(KTxtHelloWorld,"Hello World!");
_LIT(KTxtRepText,"Replacement text");
_LIT(KTxtTBufC,"TBufC: ");
_LIT(KTxtTPtr,"TPtr:  ");

//
// Common Format strings
//
_LIT(KCommonFormat2,"\"%S\"; ");
_LIT(KCommonFormat3,"Descriptor at %x; Ptr()=%x; ");
_LIT(KCommonFormat6,"\"%S\"; Ptr()=%x; Length()=%d; Size()=%d\n");
_LIT(KCommonFormat7,"\"%S\"; Ptr()=%x; Length()=%d; Size()=%d; ");
_LIT(KCommonFormat8,"\nMaxLength()=%d\n");
_LIT(KCommonFormat9,"Length()=%d; Size()=%d;\n");
_LIT(KCommonFormat10,"MaxLength()=%d\n");


LOCAL_C void doExampleL()
    {				   
				// Set up an area and initialise to a 
				// C style string (including the NULL).
	TText cstr[13] =  {'H', 'e' ,'l' ,'l' ,'o', ' ',
				       'W', 'o','r', 'l', 'd', '!', '\0'};

				// Construct a TBufC using the NULL 
				// terminated string in cstr to initialise
				// it.
	TBufC<16> bufc1(&cstr[0]);

				// Look at the address of the C string
	_LIT(KFormat1,"C string at %x; \n");
	console->Printf(KFormat1,&cstr[0]);
					  								
				// Look at: 
				//   1. Descriptor content
				//   2. Address of descriptor
				//   3. Address of descriptor data area
				//   4. Length of descriptor
				//   5. Size of descriptor
				//         
				// Address of descriptor data area is 
				// different from the address of cstr but
				// is offset 4 from the start of the 
				// descriptor itself.
				//
				// Descriptor length is 12.
				//
				// The template parameter value defines 
				// the length of the descriptor data area 
				// and, therefore, governs its size 
				// (depending on the build variant).
				// Size of data is 12 in ASCII build but 24 in
				// UNICODE build.  
	console->Printf(KCommonFormat2,&bufc1);
	console->Printf(KCommonFormat3,&bufc1,bufc1.Ptr());
	_LIT(KFormat4,"Length()=%d; Size()=%d\n");
	console->Printf(KFormat4,bufc1.Length(),bufc1.Size());	
					  						
				// If the TBufC is to hold string data on
				// construction, use a _LIT macro.
	TBufC<16> bufc2(KTxtHelloWorld);

				// Cannot modify existing data but can replace
				// it entirely using assignment operator. 
				// The replacement text must not have a length 
				// greater than 16
	bufc2 = KTxtRepText;
	_LIT(KFormat5,"\"%S\"; Length()=%d; Size()=%d\n");
	console->Printf(KFormat5,&bufc2,bufc2.Length(),bufc2.Size());

				// Replacing text which has a length > 16
				// causes panic !!
				// 
				// Remove the "//" marks on the next two lines
				// to see this happen
	//_LIT(KTxtRepTextPanic,"Text replacement causes panic");
	//bufc2 = KTxtRepTextPanic;
    
	
				// The Des() function returns a TPtr to the
				// TBufC.
				// The TBufC data can be changed through 
				// the TPtr.
				// The maximum length of the TPtr is the 
				// value of the TBufC template parameter,
				// i.e. 16 

	bufc2 = KTxtHelloWorld;
	TPtr ptr = bufc2.Des();
	
	console->Printf(KTxtTBufC);
	console->Printf(KCommonFormat6,
					&bufc2,
					bufc2.Ptr(),
					bufc2.Length(),
					bufc2.Size()
				   );
	
	console->Printf(KTxtTPtr);
	console->Printf(KCommonFormat7,
					&ptr,
					ptr.Ptr(),
					ptr.Length(),
					ptr.Size()
				   );

	console->Printf(KCommonFormat8,ptr.MaxLength());

				// Now change the TBufC data through
				// the TPtr. This is OK provided the length
				// of the changed data does not exceed 16.
				//
				// The following change deletes the last 
				// character (the "!") and appends 
				// the characters " & Hi".
				//
				// Note that the length of both the TBufC 
				// and the TPtr reflect the changed data.
	_LIT(KTxtAndHi," & Hi");
	ptr.Delete((ptr.Length()-1),1);
	ptr.Append(KTxtAndHi);

	console->Printf(KTxtTBufC);
	console->Printf(KCommonFormat6,
					&bufc2,
					bufc2.Ptr(),
					bufc2.Length(),
					bufc2.Size()
				   );

	console->Printf(KTxtTPtr);
	console->Printf(KCommonFormat7,
					&ptr,
					ptr.Ptr(),
					ptr.Length(),
					ptr.Size()
				   );
	console->Printf(KCommonFormat8,ptr.MaxLength());

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	
	_LIT(KTxtBasicConcepts,"\n-->TBuf basic concepts");
	console->Printf(KTxtBasicConcepts);
	_LIT(KTxtPressToContinue," (press any key to continue)\n");
	console->Printf(KTxtPressToContinue);
	console->Getch();

				// Construct a TBuf using a Literal			   
	TBuf<16> buf(KTxtHelloWorld);
	
				// Look at: 
				//   1. Descriptor content
				//   2. Address of descriptor
				//   3. Address of descriptor data area
				//   4. Length of descriptor
				//   5. Size of descriptor
				//   6. Maximum length of descriptor      
				//
				// Like a TBufC, the address of the descriptor
				// data area is offset 4 from the start of the
				// descriptor itself.
				//
				// Descriptor length is 12.
				//
				// The template parameter value defines 
				// the maximum length of the descriptor. 
				// and, therefore, governs its size 
				// (depending on the build variant).
				// Size of data is 12 in ASCII build but 24 in
				// UNICODE build.
				
	console->Printf(KCommonFormat2,&buf);
	console->Printf(KCommonFormat3,&buf,buf.Ptr());
	console->Printf(KCommonFormat9,buf.Length(),buf.Size());	
	console->Printf(KCommonFormat10,buf.MaxLength());
					  	
				// The data can be modified
	buf.Append('@');
	console->Printf(KCommonFormat2,&buf);
	console->Printf(KCommonFormat9,buf.Length(),buf.Size());	
	console->Printf(KCommonFormat10,buf.MaxLength());

   			    // Length can be changed; data represented
   			    // by the descriptor is now "Hel"
	buf.SetLength(3);
	console->Printf(KCommonFormat2,&buf);
	console->Printf(KCommonFormat9,buf.Length(),buf.Size());	
	console->Printf(KCommonFormat10,buf.MaxLength());

				// Length can be zeroised; no data is now 
				// represented by the descriptor but 
				// the maximum length is still 16
	buf.Zero();
	console->Printf(KCommonFormat2,&buf);
	console->Printf(KCommonFormat9,buf.Length(),buf.Size());	
	console->Printf(KCommonFormat10,buf.MaxLength());
					  				  				  
				// The data can be replaced entirely 
				// using the assignment operator.
				// The replacement text must not have a
				// length greater than 16.
	buf = KTxtRepText;
	console->Printf(KCommonFormat2,&buf);
	console->Printf(KCommonFormat9,buf.Length(),buf.Size());	
	console->Printf(KCommonFormat10,buf.MaxLength());
	
				// Replacing text which has a length > 16
				// causes panic !!
				// 
				// Remove the "//" marks on the next two lines
				// to see this happen
	//_LIT(KTxtRepTextPanic,"Text replacement causes panic");
	//buf = _L("Text replacement causes panic!");
    }





	
	
