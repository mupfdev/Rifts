// BinaryData.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// Examples to demonstrate how descriptors can handle 
// general binary data.

#include "CommonFramework.h"

//
// Common literal text
//
_LIT(KTxtNewLine,"\n");

//
// Common format strings
//
_LIT(KCommonFormat2,"Size()=%d; MaxLength()=%d\n");
_LIT(KCommonFormat3,"0x%02x ");
_LIT(KCommonFormat4,"; Length()=%d;\n");

// do the example
LOCAL_C void doExampleL()
    {
    TInt counter;
	TInt index;
    
				// For general binary data, construct an 8 bit
				// variant descriptor. Binary data is always
				// treated as 8 bit data regardless of the 
				// build.
				//
				// This example constructs a TBuf8 using the 
				// default constructor.  				   

	TBuf8<32> buffer;

				// Look at:
				//   1. Descriptor content
				//   2. Length of descriptor
				//   3. Size of descriptor
				//   4. Maximum length of descriptor
				//  
				// Length is zero. Maximum length is 32.
				// Size is zero.  
	_LIT(KFormat1,"\"%S\"; Length()=%d; ");
	console->Printf(KFormat1,&buffer,buffer.Length());
	console->Printf(KCommonFormat2,buffer.Size(),buffer.MaxLength());
				
				// Set up an area in memory initialised
				// with binary data.
	TUint8 data[6] = {0x00,0x01,0x02,0xAD,0xAE,0xAF};
				
				// Put data into descriptor
	buffer.Append(&data[0],sizeof(data));

				// Append the following byte values
	buffer.Append(0xFD);
	buffer.Append(0xFE);
	buffer.Append(0xFF);

				// Length is now 9; maxlength is still 32;
				// Size is always 9 regardless of build.
	counter = buffer.Length();
	console->Printf(KTxtNewLine);
	for (index = 0; index < counter; index++)
		console->Printf(KCommonFormat3,buffer[index]);

	console->Printf(KCommonFormat4,buffer.Length()
					  );
	console->Printf(KCommonFormat2,buffer.Size(),buffer.MaxLength());				  			
				// We can also mix text characters and
				// general binary data.
	buffer.Append('A');
	buffer.Append('B');
	buffer.Append(0x11);					  	
	
				// Show it
	counter = buffer.Length();
	console->Printf(KTxtNewLine);
	for (index = 0; index < counter; index++)
		console->Printf(KCommonFormat3,buffer[index]);
	
	console->Printf(KCommonFormat4,buffer.Length());
	console->Printf(KCommonFormat2,buffer.Size(),buffer.MaxLength());				  			
	}
