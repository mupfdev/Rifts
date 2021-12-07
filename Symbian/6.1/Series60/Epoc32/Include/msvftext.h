// MSVFTEXT.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

#ifndef __MSVFTEXT_H__
#define __MSVFTEXT_H__

#include <e32base.h>

#include "mentact.h"
#include "mtclbase.h"
#include "mtmdef.h"

class CRichText;

class CMsvFindText : public CMsgActive
	{
public:
	IMPORT_C static CMsvFindText* NewLC(TInt aPriority = EPriorityStandard);
	IMPORT_C static CMsvFindText* NewL(TInt aPriority = EPriorityStandard);
	IMPORT_C ~CMsvFindText();
	//
	IMPORT_C void FindTextL(const TDesC& aFind, const TDesC& aSource, TMsvPartList aFlags, TRequestStatus& aStatus);
	IMPORT_C void FindRichTextL(const TDesC& aFind, const CRichText& aSource, TMsvPartList aFlags, TRequestStatus& aStatus);
	//
	IMPORT_C TBool FindTextL(const TDesC& aFind, const TDesC& aSource, TMsvPartList aFlags);
	IMPORT_C TBool FindRichTextL(const TDesC& aFind, const CRichText& aSource, TMsvPartList aFlags);
	//
	inline TBool FoundText() const;
	//
private:
	CMsvFindText(TInt aPriority);
	//
	void InitialiseL(const TDesC& aFind, const TDesC* aPlainSource, const CRichText* aRichSource, TMsvPartList aFlags);
	void DoFindAsyncL(TRequestStatus& aStatus);
	void DoComplete(TInt&);
	TBool DoFindSyncL();
	TBool DoFindStepL();
	TBool DoFindTextL();
	void DoRunL();
	void Check();
	//
private:
	HBufC* iBuf;
	HBufC* iFind;
	TInt iSourcePos;
	TInt iMaxRead;
	TInt iSourceLen;
	const CRichText* iRichText;
	const TDesC* iPlainText;
	TMsvPartList iFlags;
	TChar iPreChar;
	TChar iPostChar;
	TBool iFoundText;
	};

#include "msvftext.inl"

#endif
