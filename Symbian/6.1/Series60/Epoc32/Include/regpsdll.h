// regpsdll.h
//
// Copyright (c) 1999 Symbian Software plc.  All rights reserved.
//
// A revised version of the CRegisteredParserDll class.  This no longer uses a 
// reference to a CParserRegistrationData object.  Instead a UidType is passed in 
// the  constructor, or through a set method.  The class is used to find the file 
// which contains a parser, to load and maintain a reference count of the number of 
// objects using the dll, so that it can be unloaded when no longer required. 
// It will also unload the dll when a new parser is required.



#ifndef __REGPSDLL_H__
#define __REGPSDLL_H__

#include <e32base.h>

// forward declarations
class RWriteStream;
class RReadStream;
class RFs;

//
//  Real non-derivable class
//
class CRegisteredParserDll : public CTimer
	{
public:
    IMPORT_C static CRegisteredParserDll* NewL(TUidType& aParserUidType);
    IMPORT_C ~CRegisteredParserDll();

	inline TInt DllRefCount() const;
	inline TUidType UidType() const;
	inline void SetUidType(const TUidType& aUidType);

	IMPORT_C TInt GetLibrary(RFs& aFs,RLibrary& aParserDllLibrary);   // Increments reference count if successful or returns error 
	IMPORT_C void ReleaseLibrary();                                   // Decrements access count
	                                                                  // Should be called from destructor of any objects created from the library 
private:
	CRegisteredParserDll(TUidType& aParserUidType);
    void ConstructL();

	void LoadLibraryL(RFs& aFs);   
	TInt FindFullName(RFs& aFs,TDes& aFullName); 

private:
	TUidType iUidType;
	RLibrary iParserDllLibrary;
	TInt iDllRefCount;

    void RunL();
    enum { KReleaseLibraryTimeout = 30000000 };
	};

#include "regpsdll.inl"
#endif