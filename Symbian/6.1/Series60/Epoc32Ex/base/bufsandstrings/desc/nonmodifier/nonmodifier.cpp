// NonModifier.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// Examples to demonstrate some of the non-modifying member
// functions of descriptors.

#include "CommonFramework.h"

//
// Common literal text
//
_LIT(KTxtPressToContinue," (press any key to continue)\n");
_LIT(KTxtnotfound,"NOT FOUND");
_LIT(KTxtfound,"found");
_LIT(KTxtlessthan,"  is less than     ");
_LIT(KTxtgreaterthan,"  is greater than  ");
_LIT(KTxtequalto,"  is equal to      ");

//
// Common Format strings
//
_LIT(KCommonFormat2,"Length()=%d; Size()=%d\n");
_LIT(KCommonFormat8,"\"%S\"  Char %c is at pos %d (%S)\n");
_LIT(KCommonFormat9,"%- 8S   pos %2d  (%S)\n");
//
// Compare strings
//
_LIT(KTxtCompstr1,"Hello World!@@");
_LIT(KTxtCompstr2,"Hello");
_LIT(KTxtCompstr3,"Hello Worl");
_LIT(KTxtCompstr4,"Hello World!");
_LIT(KTxtCompstr5,"hello world!");
_LIT(KTxtCompstr6,"Hello World ");
_LIT(KTxtCompstr7,"Hello World@");

//
// Match strings
//
_LIT(KTxtMatchstr1,"*World*");
_LIT(KTxtMatchstr2,"*W?rld*");
_LIT(KTxtMatchstr3,"Wor*");
_LIT(KTxtMatchstr4,"Hello");
_LIT(KTxtMatchstr5,"*W*");
_LIT(KTxtMatchstr6,"hello*");
_LIT(KTxtMatchstr7,"*");


// Do the example
LOCAL_C void doExampleL()
    {
    TInt            index;
	TInt            pos;
	TPtrC           genptr;
														  	
				// Use a TBufC to demonstrate some of these
				// and use the standard "Hello World!" text
	_LIT(KTxtHelloWorld,"Hello World!");
	const TBufC<16> bufc(KTxtHelloWorld);
	
			//				
			// Right() & Mid()  * * * * * * * * * * * *  
	        //	
	_LIT(KTxtRightMid,"\n--->Right() & Mid()\n");
	console->Printf(KTxtRightMid);

				// Look at the content of bufc
	_LIT(KFormat1,"      TBufC: \"%S\"; Ptr()=%x; ");
	console->Printf(KFormat1,&bufc,bufc.Ptr());

	console->Printf(KCommonFormat2,bufc.Length(),bufc.Size());

				// Construct a TPtrC to represent the right
				// hand 5 data items. The function Left()
				// is similar.
	TPtrC ptrc1 = bufc.Right(5);

				// ptrc's data is "orld!"
				// Length of ptrc is 5
				// ptrc's data area address = bufc's data area
				// address + 7
	_LIT(KFormat3,"Right TPtrC: \"%S\"; Ptr()=%x; ");
	console->Printf(KFormat3,&ptrc1,ptrc1.Ptr());
	console->Printf(KCommonFormat2,ptrc1.Length(),ptrc1.Size());

				// Construct a TPtrC to represent the 6 data
				// items offset 3 from the start of bufc's
				// data area.	
	TPtrC ptrc2 = bufc.Mid(3,6);	 
	
				// ptrc's data is "lo Wor"
				// Length of ptrc is 6
				// ptrc's data area address = buf's data area
				// address + 3
	_LIT(KFormat4,"  Mid TPtrC: \"%S\"; Ptr()=%x; ");
	console->Printf(KFormat4,&ptrc2,ptrc2.Ptr());
	console->Printf(KCommonFormat2,ptrc2.Length(),ptrc2.Size());
				// In practice, there is often no need to 
				// assign the returned TPtrC to another TPtrC.
				// For example, the following code puts a 
				// value of 3 in pos; this is the offset
				// of char 'W' within the chars "lo Wor"  
				// (see later for more detail on Locate())
				
	pos = (bufc.Mid(3,6)).Locate('W');
	_LIT(KFormat5,"(bufc.Mid(3,6)).Locate('W') returns %d\n");
	console->Printf(KFormat5,pos);

				// Want the 13 right hand data items.
				// This is > current length of bufc
				// causing panic !!
				// 
				// Remove the "//" marks on the next line
				// to see this happen
	//TPtrC ptrc3 = bufc.Right(13);
    
			//				
			// Compare() & CompareF()   * * * * * * * * *
			//
	_LIT(KTxtCompare,"\n--->Compare() & CompareF()");
	console->Printf(KTxtCompare);
	console->Printf(KTxtPressToContinue);  //" (press any key to continue)\n"
	console->Getch();

				// Can compare any kind of data.
				// For binary data just use Compare().
				// For text use Compare(), CompareF() or 
				// CompareC(). Using the Compare() function,
				// case is important so that, below, the 4th 
				// comparison is equal but the 5th is unequal.
    
	const TBufC<16> compstr[7] =  {*&KTxtCompstr1, // "Hello World!@@"
								   *&KTxtCompstr2, // "Hello"
			    				   *&KTxtCompstr3, // "Hello Worl"
								   *&KTxtCompstr4, // "Hello World!"
								   *&KTxtCompstr5, // "hello world!"
								   *&KTxtCompstr6, // "Hello World "
								   *&KTxtCompstr7  // "Hello World@"
								  };

	for (index = 0; index < 7; index++)
		{
		
		if ( (bufc.Compare(compstr[index])) < 0 )
			genptr.Set(KTxtlessthan);
		else if ( (bufc.Compare(compstr[index])) > 0)
				genptr.Set(KTxtgreaterthan);
			 else genptr.Set(KTxtequalto);
	    _LIT(KFormat6,"\"%S\"%S\"%S\"\n");		
		console->Printf(KFormat6,&bufc,&genptr,&compstr[index]);
		}

				// CompareF() ignores case so that now,
				// both the 4th and the 5th comparsions
				// are equal.
	for (index = 3; index < 5; index++)
		{
		if ( (bufc.CompareF(compstr[index])) < 0 )
			genptr.Set(KTxtlessthan);
		else if ( (bufc.CompareF(compstr[index])) > 0)
				genptr.Set(KTxtgreaterthan);
			 else genptr.Set(KTxtequalto);
		_LIT(KTxtusingCF," (using CompareF())");
		_LIT(KFormat7,"\"%S\"%S\"%S\"%S\n");
		console->Printf(KFormat7,&bufc,&genptr,&compstr[index],&KTxtusingCF);
		}

	        //				
			// Locate(), LocateF(), LocateReverse()     * * *
			//
	_LIT(KTxtLocate,"\n--->Locate(), LocateF() & LocateReverse()");
	console->Printf(KTxtLocate);
	console->Printf(KTxtPressToContinue);  //" (press any key to continue)\n"
	console->Getch();
				
				// Locate the positions (i.e. the offsets) of
				// these characters in "Hello World!"			  
	TChar ch[4] = {'H', '!', 'o', 'w'};
							
				// using Locate().
				// Note that 'w' is not found because the
				// function is case sensitive
	_LIT(KTxtUsingLocate,"using Locate() \n");
	console->Printf(KTxtUsingLocate);
	for (index = 0  ; index < 4; index++)
		{
		pos = bufc.Locate(ch[index]);

		if (pos < 0)
			genptr.Set(KTxtnotfound);
		else 
			genptr.Set(KTxtfound);

		console->Printf(KCommonFormat8,&bufc,TUint(ch[index]),pos,&genptr);
		}

				// using LocateF()
				// Note that 'w' is found because the
				// function is NOT case sensitive.
	_LIT(KTxtUsingLocateF,"using LocateF() \n");
	console->Printf(KTxtUsingLocateF);
	for (index = 0  ; index < 4; index++)
		{
		pos = bufc.LocateF(ch[index]);

		if (pos < 0)
			genptr.Set(KTxtnotfound);
		else 
			genptr.Set(KTxtfound);

		console->Printf(KCommonFormat8,&bufc,TUint(ch[index]),pos,&genptr); 
		}
	
			// using LocateReverse()
			// Note that the 2nd char 'o' is found this time
	_LIT(KTxtUsingLocateReverse,"using LocateReverse() \n");
	console->Printf(KTxtUsingLocateReverse);
	for (index = 0  ; index < 4; index++)
		{
		pos = bufc.LocateReverse(ch[index]);

		if (pos < 0)
			genptr.Set(KTxtnotfound);
		else 
			genptr.Set(KTxtfound);

		console->Printf(KCommonFormat8,&bufc,TUint(ch[index]),pos,&genptr);
		}
		
			//				
			// Match() & MatchF()   * * * * * * *
			//
	_LIT(KTxtMatch,"\n--->Match()");
	console->Printf(KTxtMatch);
	console->Printf(KTxtPressToContinue);  //" (press any key to continue)\n"
	console->Getch();

	
    TBufC<8> matchstr[7] =  {*&KTxtMatchstr1, // "*World*"
							 *&KTxtMatchstr2, // "*W?rld*"
							 *&KTxtMatchstr3, // "Wor*"
							 *&KTxtMatchstr4, // "Hello"
							 *&KTxtMatchstr5, // "*W*"
							 *&KTxtMatchstr6, // "hello*"
							 *&KTxtMatchstr7  // "*" 
							};


	_LIT(KFormat10,"\"%S\"\n");
	console->Printf(KFormat10,&bufc);
			 
	 			// using Match()
	for (index = 0  ; index < 7; index++)
		{
		pos = bufc.Match(matchstr[index]);

		if (pos < 0)
			genptr.Set(KTxtnotfound);
		else 
			genptr.Set(KTxtfound);
		
		console->Printf(KCommonFormat9,&matchstr[index],pos,&genptr); 
		}

				// using MatchF()
				//   
				// Note the different result when matching 
				// the 6th string, where case is ignored.
	_LIT(KTxtMatchF,"\n--->MatchF()");
	console->Printf(KTxtMatchF);
	console->Printf(KTxtPressToContinue);  //" (press any key to continue)\n"
	console->Getch();
	
	for (index = 0  ; index < 7; index++)
		{
		pos = bufc.MatchF(matchstr[index]);

		if (pos < 0)
			genptr.Set(KTxtnotfound);
		else 
			genptr.Set(KTxtfound);

		console->Printf(KCommonFormat9,&matchstr[index],pos,&genptr); 
		}
	}





	
	
