// ReadData.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

//	This header file contains the class definitions for:
//	CResData
#include "CommonFile.hrh"

class CResData : public CBase
	{
public:
	~CResData();
	static	CResData* NewLC(TResourceReader& aReader);
	void	ShowData(const TInt aStructNum = 0);
private:
    void	ConstructL(TResourceReader& aReader);
private:
	TInt        	iWrd;		// STRUCT member type: WORD,
	TInt			iFlags;     // WORD
	TInt			iLng;		// LONG,
	TInt         	iByt;		// BYTE,
	TReal			iDbl;		// DOUBLE,
	TBufC<TEXTMAX>  iTxt;		// LTEXT (maximum length specified),
	HBufC*        	iLtxt;	  	// LTEXT
	};


				



