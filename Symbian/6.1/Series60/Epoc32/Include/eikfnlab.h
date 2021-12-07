// EIKFNLAB.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKFNLAB_H__)
#define __EIKFNLAB_H__

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

class CEikLabel;

class CEikFileNameLabel : public CEikBorderedControl
	{
public:
	IMPORT_C CEikFileNameLabel();
	IMPORT_C ~CEikFileNameLabel();
	IMPORT_C void ConstructL();
	IMPORT_C void UpdateL();
public:	// from CCoeControl 
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C void HandleResourceChange(TInt aType);			// not available before Release 005u
	IMPORT_C TSize MinimumSize();
protected: // from CCoeControl
	IMPORT_C void Draw(const TRect& aRect) const;
private: // from CCoeControl
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C void SizeChanged();
private:
	CEikLabel* iLabel;
	TInt iSpare;
	};



#endif
