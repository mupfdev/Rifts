// Modifier.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// Examples to demonstrate some of the modifying member
// functions of descriptors.

#include "CommonFramework.h"

//
// Common literal text 
//
_LIT(KPressAnyKeyToContinue," (press any key to continue)\n");
_LIT(KTextHelloWorld,"Hello World!");
_LIT(KTextHello,"Hello");
_LIT(KTextXYZ,"XYZ");
_LIT(KTextDinner,"D\214ner \205 la Fran\207ais");

//
// Common format strings
//

_LIT(KFormatfourex,"%4x");
_LIT(KFormatBufLenSizeMax,"\"%S\"; %d; %d; %d\n");
_LIT(KFormatLenSizeMax,"; %d; %d; %d\n");
_LIT(KFormatBufLen,"\"%S\"; Length()=%d; ");
_LIT(KFormatSizeMax,"Size()=%d; MaxLength()=%d\n");
_LIT(KFormatCommon,"0x%02x ");

			// Define and implement the 8 bit or 16 bit
			// flavours of the overflow handler used
			// by the AppendFormat() example.

//#if defined(_UNICODE)
class TestOverflow : public TDes16Overflow
	{
	void Overflow(TDes16& aDes);
	};
//#else
//class TestOverflow : public TDes8Overflow
//	{
//	void Overflow(TDes8& aDes);
//	};
//#endif

void TestOverflow::Overflow(TDes& aDes)
	{
	_LIT(KTextDescOverflow,"Descriptor overflow - maxlength %d\n");
	console->Printf(KTextDescOverflow,aDes.MaxLength());
	}


// Do the example
LOCAL_C void doExampleL()
    {				   

	TInt index;
	TInt counter;

				// Use a TBuf to demonstrate some of these
	TBuf<32> buf(KTextHelloWorld);
		
			//				
			// Copy(),CopyF(), CopyUC() & CopyCP()  * * * 

	_LIT(KTitleCopy,"\n--->Copy(),CopyF(),CopyUC() & CopyCP()\n");
	console->Printf(KTitleCopy);
						
				// Show buf's content,length,size and
				// maximum size.
	console->Printf(KFormatBufLen,&buf,buf.Length());
	console->Printf(KFormatSizeMax,buf.Size(),buf.MaxLength());

			 	// Copy normal
	buf.Copy(KTextDinner);

				// Show buf's content,length,size and 
				// maximum size.
	console->Printf(KFormatBufLen,&buf,buf.Length());
	console->Printf(KFormatSizeMax,buf.Size(),buf.MaxLength());
	

				// Copy folded - accents are not preserved
				//
				// (NB the display may use a different code
				// page to that used by the base, in which 
				// case the accents will seem to be preserved)
	buf.CopyF(KTextDinner);
				
				// Show buf's new content,length,size
				// and max size
	console->Printf(KFormatBufLen,&buf,buf.Length());
	console->Printf(KFormatSizeMax,buf.Size(),buf.MaxLength());
				// Copy uppercase
				// Note that accents are preserved.
	buf.CopyUC(KTextDinner);
				
				// Show buf's new content,length,size
				// and maximum size
	console->Printf(KFormatBufLen,&buf,buf.Length());
	console->Printf(KFormatSizeMax,buf.Size(),buf.MaxLength());

				// Copy capitalised
				// Note that accents are preserved.
	_LIT(KTextCatOnMat,"tHe CaT sAt On ThE mAt - voil\205");
	buf.CopyCP(KTextCatOnMat);
				
				// Show buf's new content,length,size
				// and max size
	console->Printf(KFormatBufLen,&buf,buf.Length());
	console->Printf(KFormatSizeMax,buf.Size(),buf.MaxLength());
					  	
				// Length of copied text > 32 causes panic !!
				// 
				// Remove the "//" marks on the next two lines
				// to see this happen
	//_LIT(KTxtCausePanic1,"Panic caused by an attempt to replace text.");
	//buf.Copy(KTxtCausePanic1);
    
			//
	 		// Append() & operator+=  * * * * * * * * * 
			//
	_LIT(KTitleAppend,"\n--->Append & Operator+=");
	console->Printf(KTitleAppend);
	console->Printf(KPressAnyKeyToContinue);
	console->Getch();

				// Show buf's content,length,size and
				// maximum size.
	buf = KTextHelloWorld;
	console->Printf(KFormatBufLen,&buf,buf.Length());
	console->Printf(KFormatSizeMax,buf.Size(),buf.MaxLength());

				// Append:
				//     1. a single character
				//     2. a descriptor
				//     3. another descrptor using operator +=
				//
				// Generates the string
				// "Hello World!@XYZ##" in buf
	buf.Append('@');
	buf.Append(KTextXYZ);
	_LIT(KTextHashHash,"##");
	buf += KTextHashHash;
	console->Printf(KFormatBufLen,&buf,buf.Length());
	console->Printf(KFormatSizeMax,buf.Size(),buf.MaxLength());

			//				
			// Swap()  * * * * * * * * * * * * * * * 
			//
	_LIT(KTitleSwap,"\n--->Swap()");
	console->Printf(KTitleSwap);
	console->Printf(KPressAnyKeyToContinue);
	console->Getch();
	
	_LIT(KWhatANiceDay,"What a nice day");
	TBuf<16> altbuf1(KWhatANiceDay);
	buf = KTextHelloWorld;

				// Show buf and altbuf BEFORE swap
	_LIT(KTextBefore,"          BEFORE...\n");
	console->Printf(KTextBefore);
	console->Printf(KFormatBufLen,&buf,buf.Length());
	console->Printf(KFormatSizeMax,buf.Size(),buf.MaxLength());
	
	console->Printf(KFormatBufLen,&altbuf1,altbuf1.Length());
	console->Printf(KFormatSizeMax,altbuf1.Size(),altbuf1.MaxLength());
	
				// now swap the descriptors and look at
				// buf and altbuf again;
				// The content, length and size of the 
				// descriptors have swapped; their maximum 
				// lengths have NOT changed.
	buf.Swap(altbuf1);

	_LIT(KTextAfter,"          AFTER...\n");
	console->Printf(KTextAfter);
	console->Printf(KFormatBufLen,&buf,buf.Length());
	console->Printf(KFormatSizeMax,buf.Size(),buf.MaxLength());
	
	console->Printf(KFormatBufLen,&altbuf1,altbuf1.Length());
	console->Printf(KFormatSizeMax,altbuf1.Size(),altbuf1.MaxLength()
					  );

				// Swap is ok provided the maximum length
				// of each descriptor is big enough to 
				// hold the other's data.
	
				// altbuf2 is too small to accommodate 
				// buf's data !!
				// 
				// Remove the "//" marks on the next three lines
				// to see this panic
	//_LIT(KTxtxxx,"xxx");
	//TBuf<8>  altbuf2(KTxtxxx);
	//buf = KTextHelloWorld;
	//buf.Swap(altbuf2);
    
	
			//				
			// Repeat()  * * * * * * * * * * * * * * * 
			//
	_LIT(KTitleRepeat,"\n--->Repeat()");
	console->Printf(KTitleRepeat);
	console->Printf(KPressAnyKeyToContinue);
	console->Getch();

				// Set current length of buf to 16 and
				// copy repeat the characters "Hello".
				// The descriptor is filled up to 
				// its CURRENT LENGTH.
				// Result is the 16 charcters
				// "HelloHelloHelloH"
				//
				// Note the truncation. 
	buf.SetLength(16);
	buf.Repeat(KTextHello);

				// Look at it.
	console->Printf(KFormatBufLen,&buf,buf.Length());
	console->Printf(KFormatSizeMax,buf.Size(),buf.MaxLength());

				// Now set the length to 8 characters
				// and do Repeat again.
				// Result is the 8 characters
				// "HelloHel"

	buf.SetLength(8);
	buf.Repeat(KTextHello);

				// Look at it
	console->Printf(KFormatBufLen,&buf,buf.Length());
	console->Printf(KFormatSizeMax,buf.Size(),buf.MaxLength());
	
	 		//				
			// Insert() & Delete()  * * * * * * * * *
			//
	_LIT(KTitleInsert,"\n--->Insert() & Delete()");
	console->Printf(KTitleInsert);
	console->Printf(KPressAnyKeyToContinue);
	console->Getch();

				// set buf to contain the text "abc" and 
				// look at it
	_LIT(KTextAbc,"abc");
	buf = KTextAbc;
	console->Printf(KFormatBufLenSizeMax,
					&buf,
					buf.Length(),
					buf.Size(),
					buf.MaxLength()
				   );

				// Insert the descriptor at the beginning
				// of buf to give "XYZabc"
				//
	
	buf.Insert(0,KTextXYZ);

				// Look at it
	console->Printf(KFormatBufLenSizeMax,
					&buf,
					buf.Length(),
					buf.Size(),
					buf.MaxLength()
				   );
	
				// Now insert another descriptor at pos 2
				// to give "XijklmnYZabc"
				//
	_LIT(KTextijklmn,"ijklmn");
	buf.Insert(1,KTextijklmn);

				// Show result
	console->Printf(KFormatBufLenSizeMax,
					&buf,
					buf.Length(),
					buf.Size(),
					buf.MaxLength()
				   );
					  				
	
				// Insertion point out of range
				// (> current length of descriptor)
				// 
				// Remove the "//" marks on the next line
				// to see this panic
	//_LIT(KTxtqwerty,"qwerty");
	//buf.Insert(buf.Length()+1,KTxtqwerty);
	
	
				// Resulting length of data
				// is > maximum length.
				// 
				// Remove the "//" marks on the next line
				// to see this panic
	//_LIT(KTxtatoz,"abcdefghijklmnopqrstuvwxyz");
	//buf.Insert(12,KTxtatoz);
	
	
				// Now delete the 3 data 
				// items (characters) at the start
				// of buf to give "klmnYZabc"
	buf.Delete(0,3);

				// Show result
	console->Printf(KFormatBufLenSizeMax,
					&buf,
					buf.Length(),
					buf.Size(),
					buf.MaxLength()
				   );
	
				// Now delete the 4 data items (characters) at
				// position 4 to give "klmnc"
				//
	buf.Delete(4,4);
	
				// Show result
	console->Printf(KFormatBufLenSizeMax,
					&buf,
					buf.Length(),
					buf.Size(),
					buf.MaxLength()
				   );
	
	 			// An excessive length for deletion is 
	 			// truncated to a sensible value. Deletes 
	 			// all the data starting at pos 1 to 
	 			// give "k"
	 			// (Note that the length actually
				//  deleted is 4 NOT 25000).
							
	buf.Delete(1,25000);
	
				// Show result
	console->Printf(KFormatBufLenSizeMax,
				    &buf,
				    buf.Length(),
				    buf.Size(),
				    buf.MaxLength()
				   );
		 
			//				
			// TrimLeft() & TrimRight()  * * * * * * * * *
			//
	_LIT(KTitleTrimLeft,"\n--->TrimLeft() & TrimRight()");
	console->Printf(KTitleTrimLeft);
	console->Printf(KPressAnyKeyToContinue);
	console->Getch();

				// set buf up and show the detail
	buf.Fill(' ',18);
	buf.Replace(3,(&KTextHelloWorld)->Length(),KTextHelloWorld);
	console->Printf(KFormatBufLenSizeMax,  
	                &buf,
					buf.Length(),
					buf.Size(),
					buf.MaxLength()
				   );

				// Remove left hand spaces 	
	buf.TrimLeft();	
	console->Printf(KFormatBufLenSizeMax,  
	                &buf,
					buf.Length(),
					buf.Size(),
					buf.MaxLength()
				   );

				// Remove right hand spaces 	
	buf.TrimRight();	
	console->Printf(KFormatBufLenSizeMax,  
	                &buf,
					buf.Length(),
					buf.Size(),
					buf.MaxLength()
				   );

				// Trim() removes both left and right
				// hand spaces 

		 
 			//				
			// FillZ() & Fill()  * * * * * * * * * *  
			//
	_LIT(KTitleFill,"\n--->FillZ() & Fill()");
	console->Printf(KTitleFill);
	console->Printf(KPressAnyKeyToContinue);
	console->Getch();
			    
				// Set current length of buf
				// Fillz() fills buf up to its current length
				// with 0x00.
	buf.SetLength(8);
	buf.FillZ();

				// Show it
	counter = buf.Length();
	for (index = 0; index < counter; index++)
		console->Printf(KFormatCommon,buf[index]);
		
	console->Printf(KFormatLenSizeMax,
		            buf.Length(),
					buf.Size(),
					buf.MaxLength()
				   );

				// Fills buf up to its current length 
				// with 'A'
	buf.Fill('A');
	
				// show it
	console->Printf(KFormatBufLenSizeMax,  
	                &buf,
					buf.Length(),
					buf.Size(),
					buf.MaxLength()
				   );
	
			//				
			// Num(), NumUC(), AppendNum() & AppendNumUC()
			//
	_LIT(KTitleNum,"\n--->Num(), NumUC(), AppendNum()");
	console->Printf(KTitleNum);
	console->Printf(KPressAnyKeyToContinue);
	console->Getch();

				// convert a signed integer to 
				// decimal characters
	buf.Num(-176);

				// show it
	console->Printf(KFormatBufLenSizeMax,  
	                &buf,
					buf.Length(),
					buf.Size(),
					buf.MaxLength()
				   );

				// convert another signed integer
	buf.Num(12345);

				// show it
	console->Printf(KFormatBufLenSizeMax,  
	                &buf,
				    buf.Length(),
					buf.Size(),
					buf.MaxLength()
				   );

				// convert an unsigned integer
	TUint nosign = 176;
	
				// ... into decimal characters (the default,
				// if not explicitly specified)
	buf.Num(nosign);
	console->Printf(KFormatBufLenSizeMax,  
	                &buf,
				    buf.Length(),
					buf.Size(),
					buf.MaxLength()
				   );
				 	
				// ... into binary characters
	buf.Num(nosign,EBinary);
	console->Printf(KFormatBufLenSizeMax,  
	                &buf,
					buf.Length(),
					buf.Size(),
					buf.MaxLength()
				   );
	
				// ... into octal characters
	buf.Num(nosign,EOctal);
	console->Printf(KFormatBufLenSizeMax,  
	                &buf,
					buf.Length(),
					buf.Size(),
					buf.MaxLength()
				   );
	
				// ... into lower case hex characters
	buf.Num(nosign,EHex);
	console->Printf(KFormatBufLenSizeMax,  
	                &buf,
					buf.Length(),
					buf.Size(),
					buf.MaxLength()
				   );				  
	
				// ... into upper case hex characters
	buf.NumUC(nosign,EHex);
	console->Printf(KFormatBufLenSizeMax,  
	                &buf,
				    buf.Length(),
				    buf.Size(),
				    buf.MaxLength()
				   );
			
				// Append functions the same, except 
				// they append the converted data.
				// Put "xyz" into the descriptor, convert
				// and concatenate the variations.

	_LIT(KTextxyz,"xyz");				
	buf = KTextxyz;

	buf.AppendNum(nosign);
	buf.AppendNum(nosign,EBinary);
	buf.AppendNum(nosign,EOctal);
	buf.AppendNum(nosign,EHex);
	buf.AppendNumUC(nosign,EHex);
	console->Printf(KFormatBufLenSizeMax,  
	                &buf,
					buf.Length(),
					buf.Size(),
					buf.MaxLength()
				   );
					  	
			//				
			// Justify() & AppendJustify()* * * 
			//
	_LIT(KTitleJustify,"\n--->Justify() & AppendJustify()");
	console->Printf(KTitleJustify);
	console->Printf(KPressAnyKeyToContinue);
	
	console->Getch();

				// source descriptor for this example has
				// length 12. 
	TBufC<40> src(KTextHelloWorld);
				
				// target field in buf has width 16 (NB this
				// is greater than the length of the descriptor 
				// src).
				// src is copied into target field, aligned left 
				// and padded with '@' characters.
				//
				// length of buf becomes the same as the 
				// specified width, i.e 16 
	buf.Justify(src,16,ELeft,'@');
	console->Printf(KFormatBufLenSizeMax,  
	                &buf,
					buf.Length(),
					buf.Size(),
					buf.MaxLength()
				   );
	
				// target field in buf has width 16 (NB this
				// is greater than the length of the descriptor
				// src).
				// src is copied into target field, aligned centre 
				// and padded with '@' characters
				//
				// length of buf becomes the same as the
				// specified width, i.e 16 
	buf.Justify(src,16,ECenter,'@');
	console->Printf(KFormatBufLenSizeMax,  
	                &buf,
					buf.Length(),
					buf.Size(),
					buf.MaxLength()
				   );
	
				// target field in buf has width 10 (NB this
				// is smaller than the length of the descriptor
				// src).
				// src is copied into target field but truncated
				// to 10 characters and, therefore, alignment and 
				// padding information not used.
				//
				// length of buf becomes the same as the 
				// width, i.e 10 
	buf.Justify(src,10,ECenter,'@');
	console->Printf(KFormatBufLenSizeMax,  
	                &buf,
					buf.Length(),
					buf.Size(),
					buf.MaxLength()
				   );
		
				// target field in buf is set to the length of
				// the descriptor src (whatever it currently is)
				//
				// src copied into target field. No padding and
				// no truncatiuon needed and so the
				// alignment and padding information is not used.
				//
				// length of buf becomes the same as the length
				// of src i.e 12 
	buf.Justify(src,KDefaultJustifyWidth,ECenter,'@');
	console->Printf(KFormatBufLenSizeMax,  
	                &buf,
					buf.Length(),
					buf.Size(),
					buf.MaxLength()
				   );
	
	
	
				// implied width > maximum length of buf.
				// 
				// Remove the "//" marks on the next two lines
				// to see this panic
	//_LIT(KTxtPanicCausingText,"Panic causing text because length > 32");
	//src = KTxtPanicCausingText;
	//buf.Justify(src,KDefaultJustifyWidth,ECenter,'@' );
	

	 
				// explicit width > maximum length of buf
				// 
				// Remove the "//" marks on the next line
				// to see this panic
	//buf.Justify(src,33,ECenter,'@');
	

				// AppendJustify() is  similar but target 
				// field appended to descriptor.
				//
				// Target field in buf has width 16 
				// (NB greater than length of descriptor 
				// src) and is appended	to existing content
				// of buf.
				// src copied into target field, 
				// aligned left and padded with '@' 
				// characters
				//
				// Resulting length of buf is the length
				// of "ABCD" plus the width of the target
				// field (16) giving a value of 20.
	_LIT(KTextABCD,"ABCD");
	buf = KTextABCD;
	buf.AppendJustify(src,16,ELeft,'@');
	console->Printf(KFormatBufLenSizeMax,  
	                &buf,
					buf.Length(),
					buf.Size(),
					buf.MaxLength()
				   );

	 		//				
			// Format() & AppendFormat() * * * 
			//
	_LIT(KTitleFormatAndAppendFormat,"\n--->Format() & AppendFormat()");
	console->Printf(KTitleFormatAndAppendFormat);
	console->Printf(KPressAnyKeyToContinue);
	console->Getch();

				// use tgt as a target descriptor to show 
				// the results of format()
	TBuf<128> tgt;
	
				// The basic %<type> format.
				// Interprets the arguments as signed/unsigned
				// integers and generates the appropriate
				// character representations. The characters only
				// occupy the space needed to represent them.
				//
				// Generates:"1000001 A 65 101 65 41"
				//
				// format string is:
				// "%b %c %d %o %u %x"

	_LIT(KFormat1,"%b %c %d %o %u %x");
	tgt.Format(KFormat1,65,65,65,65,65,65);
    console->Printf(KFormatBufLenSizeMax,  
	                &tgt,
					tgt.Length(),
					tgt.Size(),
					tgt.MaxLength()
				   );			

				// Interprets the argument as an unsigned
				// integer; the generated (hex) characters are
				// right aligned and padded to the left
				// with '0' to make a total of 4 characters.
				//
    			// Generates:"0041"
				//
				// format string is:
				// "%04x"
	_LIT(KFormat2,"%04x");
	tgt.Format(KFormat2,65);
    console->Printf(KFormatBufLenSizeMax,  
	                &tgt,
					tgt.Length(),
					tgt.Size(),
					tgt.MaxLength()
				   );
							  			
				// Interprets the argument as an unsigned
				// integer;the generated (hex) characters are
				// right aligned and padded to the left with 
				// blanks to make a total of 4 characters.
				//
    			// Generates:"  41"
				//
				// format string is:
				// "%4x"
	tgt.Format(KFormatfourex,65);
    console->Printf(KFormatBufLenSizeMax,  
	                &tgt,
					tgt.Length(),
					tgt.Size(),
					tgt.MaxLength()
				   );			
							  			
				// Interprets the argument as an unsigned
				// integer; the generated (hex) characters are
				// right aligned and padded to the left with 
				// blanks to make a total of 4 characters.
				//
    			// Generates:"1fff" 
				//
				// NB the correct hex value is "1ffff"
				// but width specified as 4 resulting 
				// in TRUNCATION.
				// 
				//
				// format string is:
				// "%4x"
	tgt.Format(KFormatfourex,131071);
    console->Printf(KFormatBufLenSizeMax,  
	                &tgt,
					tgt.Length(),
					tgt.Size(),
					tgt.MaxLength()
				   );								  			
	
				// The '*' means that the width of the output
				// is taken from the 1st argument in the list; 
				// Interprets the 2nd argument as an unsigned
				// integer.
				// The generated (hex) characters are right 
				// aligned and padded to the left with blanks
				// to make a total of 4 characters.
				//
    			// Generates:"  41"
				//
				// format string is:
				// "%*x"
	_LIT(KFormat4,"%*x");
	tgt.Format(KFormat4,4,65);
    console->Printf(KFormatBufLenSizeMax,  
	                &tgt,
				    tgt.Length(),
				    tgt.Size(),
				    tgt.MaxLength()
				   );			
		
				// Interprets the 1st argument as a signed
				// integer. 
				//
				// The generated (decimal) characters are 
				// right aligned and padded to the left 
				// with '$' to make a total of 4 characters.
				//
				// These are then followed by the
				// 4 characters ".00 "
				//											   
				// Interprets the 2nd argument as a descriptor.
				// The characters within the descriptor are
				// appended to those already generated.
				//
    			// Generates:"$$65.00 over"
				//
				// Format string is:
				// "%+$4d.00 %S"
				//
    
	_LIT(KTextover,"over");
	_LIT(KFormat5,"%+$4d.00 %S");
	tgt.Format(KFormat5,65,&KTextover);
    console->Printf(KFormatBufLenSizeMax,  
	                &tgt,
					tgt.Length(),
					tgt.Size(),
					tgt.MaxLength()
				   );
	
	
				// The * means that the width of the 
				// output is taken from the 1st argument 
				// in the list.
				//
				// Interprets the 2nd argument as a descriptor.
				// The characters copied from it are right 
				// aligned and padded on the left with
				// '0' characters
				//
    			// Generates:"000000fred"
				//
				// Format string is:
				// "%+0*S"
				//
	
	_LIT(KTextfred,"fred");
	_LIT(KFormat6,"%+0*S");
	tgt.Format(KFormat6,10,&KTextfred);
    console->Printf(KFormatBufLenSizeMax,  
	                &tgt,
					tgt.Length(),
					tgt.Size(),
					tgt.MaxLength()
				   );                          
    

				// The * means that the fill character is 
				// taken from the 1st argument in the list.
				//
				// Interprets the 2nd argument as an unsigned
				// integer.
				// The generated characters are centrally 
				// aligned and padded on the left and right
				// with '*' to make 6 characters.
				//
    			// Generates:"**41**"
				//
				// Format string is:
				// "%=*6x"
				//
	
	_LIT(KFormat7,"%=*6x");
	tgt.Format(KFormat7,'*',65);
    console->Printf(KFormatBufLenSizeMax,  
	                &tgt,
					tgt.Length(),
					tgt.Size(),
					tgt.MaxLength()
				   );
					                            
				// The 1st '*' means that the fill character 
				// is taken from the 1st argument in the list.
				//
				// The 2nd '*' means that the width is taken
				// from the 2nd argument in the list
				//
				// Interprets the 3rd argument as a signed
				// integer.
				// The generated characters are right aligned
				// and padded on the left with '.' to make
				// 10 characters.
				//
    			// Generates:".......-65"
				//
				// Format string is:
				// "%+**d"
				//
		
	_LIT(KFormat8,"%+**d");
	tgt.Format(KFormat8,'.',10,(-65));
    console->Printf(KFormatBufLenSizeMax,  
	                &tgt,
				    tgt.Length(),
					tgt.Size(),
					tgt.MaxLength()
				   );
					                           
                // Same as the previous example but the 
                // characters are left aligned and padded to
                // the right with '.' characters.
				//
    			// Generates:"-65......."              
				//
				// Format string is:
				// "%-**d"
				//
	
	_LIT(KFormat9,"%-**d");	    
	tgt.Format(KFormat9,'.',10,(-65));
    console->Printf(KFormatBufLenSizeMax,  
	                &tgt,
					tgt.Length(),
					tgt.Size(),
					tgt.MaxLength()
				   );                                                  
                              
                // Generates 6 fill characters 'A'.
                // Makes no use of the argument list.
                //
                // Generates: "AAAAAA"                
				//
				// Format string is:
				// "%-A6p"
				//
	
	_LIT(KFormat10,"%-A6p");	    
	tgt.Format(KFormat10,65);
	console->Printf(KFormatBufLenSizeMax,  
	                &tgt,
					tgt.Length(),
					tgt.Size(),
					tgt.MaxLength()
				   );

				// Interpret the argument as an unsigned integer
				// and convert to a two byte numeric 
				// representation (most significant byte first)
				//
				// So 4660 = 0x1234 => 1st byte contains 0x12
				//                     2nd byte contains 0x34 
				//
				// NB This is same for both ASCII & UNICODE build
				//
				// Format string is:
				// "%m"
				//
	    
	_LIT(KFormat11,"%m");
	tgt.Format(KFormat11,4660);
	
	counter = tgt.Length();
	for (index = 0; index < counter; index++)
		console->Printf(KFormatCommon,tgt[index]);
		
	console->Printf(KFormatLenSizeMax,
					tgt.Length(),
					tgt.Size(),
					tgt.MaxLength()
				   );

				// Interpret the argument as an unsigned integer
				// and convert to a four byte numeric 
				// representation (most significant byte first)
				//
				// So 4660 = 0x1234 => 1st byte contains 0x00
				//                     2nd byte contains 0x00 
				//					   3rd byte contains 0x12
				//                     4th byte contains 0x34
				// NB This is same for both ASCII & UNICODE build	  
				//
				// Format string is:
				// "%M"
				//
	
	_LIT(KFormat12,"%M");
	tgt.Format(KFormat12,4660);				                   
	
	counter = tgt.Length();	
    for (index = 0; index < counter; index++)
		console->Printf(KFormatCommon,tgt[index]);
		
	console->Printf(KFormatLenSizeMax,
					tgt.Length(),
					tgt.Size(),
					tgt.MaxLength()
				   );

				// Interpret the argument as an unsigned integer
				// and convert to a two byte numeric 
				// representation (least significant byte first)
				//
				// So 4660 = 0x1234 => 1st byte contains 0x34
				//                     2nd byte contains 0x12 
				//
				// NB This is same for both ASCII & UNICODE build
				//
				// Format string is:
				// "%w"
				//
      
	_LIT(KFormat13,"%w");
	tgt.Format(KFormat13,4660);
	
	counter = tgt.Length();
    for (index = 0; index < counter; index++)
		console->Printf(KFormatCommon,tgt[index]);
		
	console->Printf(KFormatLenSizeMax,
					tgt.Length(),
					tgt.Size(),
					tgt.MaxLength()
				   );

				// Interpret the argument as an unsigned integer
				// and convert to a four byte numeric 
				// representation (least significant byte first)
				//
				// So 4660 = 0x1234 => 1st byte contains 0x34
				//                     2nd byte contains 0x12 
				//					   3rd byte contains 0x00
				//                     4th byte contains 0x00
				// NB This is same for both ASCII & UNICODE build	  
				//
				// Format string is:
				// "%W"
				//

	_LIT(KFormat14,"%W");
	tgt.Format(KFormat14,4660);				                   
	
	counter = tgt.Length();	
    for (index = 0; index < counter; index++)
		console->Printf(KFormatCommon,tgt[index]);
		
	console->Printf(KFormatLenSizeMax,
					tgt.Length(),
					tgt.Size(),
					tgt.MaxLength()
				   );
	
	console->Printf(KPressAnyKeyToContinue);
	console->Getch();

		 	//				
			// AppendFormat() illustrating use of the
			// overflow handler 
			//
	_LIT(KTitleOverflowHandler,"\n--->AppendFormat() & the overflow handler");
	console->Printf(KTitleOverflowHandler);
	console->Printf(KPressAnyKeyToContinue);
	console->Getch();

				// use the TestOverflow class as the overflow 
				// handler
	TBuf<16>     overtgt;
	TestOverflow theoverflow;
	
				// prime "overtgt" with data (of length 14)
	_LIT(KTextabcdefghijklmn,"abcdefghijklmn");
	overtgt = KTextabcdefghijklmn;

				// Format string contains just literal
				// text and no embedded commands.
				// Length of literal text is 3
				// 14+3 > max length of "overtgt" and 
				// so theoverflow.Overflow() will be invoked
	
	_LIT(KTextopq,"opq");
	overtgt.AppendFormat(KTextopq,&theoverflow);

				// NB omitting the 2nd parameter, giving:
				// overtgt.AppendFormat(KTextopq);
				// results in a panic.
    }
	






	
	
