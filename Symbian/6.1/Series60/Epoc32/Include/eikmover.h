// EIKMOVER.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKMOVER_H__)
#define __EIKMOVER_H__

#include <coecntrl.h>

//
// Forward declarations
//

class TResourceReader;

/**
 * The CEikMover class implements a draggable bar that can be used as
 * the title bar of a dialog window.
 */
class CEikMover : public CCoeControl
	{
public: // class specific
	IMPORT_C ~CEikMover();
	IMPORT_C CEikMover();
	IMPORT_C void SetText(HBufC* aText);
	IMPORT_C void SetTextL(const TDesC& aText);
	IMPORT_C void SetActive(TBool aActive);
	IMPORT_C TBool Active() const;
	IMPORT_C void SetFont(const CFont* aFont);
	IMPORT_C void SetTitleLeftMargin(TInt aLeftMargin);
public: // from CCoeControl
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C virtual TSize MinimumSize(); 
	IMPORT_C virtual void SetContainerWindowL(const CCoeControl& aContainer);
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
protected: //from CCoeControl
	IMPORT_C virtual void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C virtual void Draw(const TRect& aRect) const;
	IMPORT_C virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
private:
	IMPORT_C virtual void Reserved_2();
private:
	HBufC* iText;
	const CFont* iFont;
	TPoint iPointerDownPos;
	TInt iMoverFlags;
	TInt iTitleLeftMargin;
	CCoeControl* iParentControl;
	};

#endif
