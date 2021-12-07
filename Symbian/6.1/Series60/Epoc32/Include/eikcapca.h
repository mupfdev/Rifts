// EIKCAPCA.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKCAPCA_H__)
#define __EIKCAPCA_H__

#include <e32base.h>

class CEikCaptionedControl;
class CCoeControl;

class CEikCapCArray : public CArrayPtrFlat<CEikCaptionedControl>
	{
public:
	IMPORT_C CEikCapCArray(TInt aGranularity);
	IMPORT_C ~CEikCapCArray();
	IMPORT_C TSize MinimumSize();
	IMPORT_C void SetRect(const TRect& aRect);
	IMPORT_C void ResetMinimumSizes();
	IMPORT_C TInt LineIndexFromId(TInt aControlId) const;
	IMPORT_C TInt FindLineIndex(const CCoeControl* aControl) const;
	IMPORT_C void DeleteLine(TInt aIndex);
	IMPORT_C void AdjustAllIds(TInt aControlIdDelta);
	IMPORT_C void SetDensePacking(TBool aDensePacking);
private:
	TInt iCaptionWidth;
	TBool iDensePacking;
	};

#endif
