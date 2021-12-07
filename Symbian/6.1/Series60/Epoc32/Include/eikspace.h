// EIKSPACE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKSPACE_H__)
#define __EIKSPACE_H__

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

#if !defined(__GDI_H__)
#include <gdi.h>
#endif

class TResourceReader;

class CEikSpacer : public CCoeControl
    {
public:
    IMPORT_C CEikSpacer();
	IMPORT_C CEikSpacer(TInt aWidth,TInt aHeight,TRgb aColor);
    IMPORT_C ~CEikSpacer();
	IMPORT_C void SetWidth(TInt aWidth);
	IMPORT_C void SetHeight(TInt aHeight);
	IMPORT_C void SetColor(TRgb aColor);
	IMPORT_C void SetClear(TBool aClear);
private: // from CCoeControl
    void ConstructFromResourceL(TResourceReader& aReader);
	void Draw(const TRect& aRect) const;
private:
	TRgb iColor;
	TBool iClear;
    };



#endif
