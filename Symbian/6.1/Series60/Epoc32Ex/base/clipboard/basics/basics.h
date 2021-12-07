// Basics.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.



//	This header file contains the class definitions and local
//	
//	function prototypes used by the example
	
	
const TUid KExampleClipUid={2306};
 
class CClassA : public CBase
	{
public :
	CClassA();
	void ExternalizeL(RWriteStream& aStream) const;
	void InternalizeL(RReadStream& aStream);
public :
	TBuf<32> iBuffer;
	TInt     iXA;
	TUint    iYA;
	};

LOCAL_C void doCopyL();

LOCAL_C void doPasteL();

LOCAL_C void doShow(const TDesC& aHeading,const CClassA* anItem);

