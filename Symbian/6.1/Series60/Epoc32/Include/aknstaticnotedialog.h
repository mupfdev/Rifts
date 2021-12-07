/*
* ============================================================================
*  Name     : AknStaticNoteDialog.h
*  Part of  : Avkon
*
*  Description:
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef __AKNSTATICNOTEDIALOG__
#define __AKNSTATICNOTEDIALOG__

#include <aknnotedialog.h>

class CEikImage;


class CAknStaticNoteStackIndicator : public CCoeControl
	{
public:
	void ConstructL(CCoeControl* aParentNote, TInt aStackDepth);
	void UpdateDepth(TInt aDepth);
private:
	void Draw(const TRect& aRect) const;
	void DoSetExtent();
private:
	TInt iStackDepth;
	CCoeControl* iParentNote;
	};


/**
 * Static note dialog
 */
class CAknStaticNoteDialog : public CAknNoteDialog
	{
public:
	IMPORT_C CAknStaticNoteDialog();
	IMPORT_C CAknStaticNoteDialog(CEikDialog** aSelfPtr);
	IMPORT_C virtual ~CAknStaticNoteDialog();

    IMPORT_C void SetNumberOfBorders(TInt aNumber);

protected:
	IMPORT_C void PostLayoutDynInitL();
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

protected:
	CAknStaticNoteStackIndicator* iStackIndicator;
	TInt iStackDepth;
	TInt iSpare;
	
public:
	/**
	 * @deprecated - use version without aControlId parameter
	 */
	IMPORT_C void SetNumberOfBorders(TInt aControlId,TInt aNumber);

	/**
	 * @deprecated - do not call or it will panic
	 */
	IMPORT_C void SetImageNoteThumbnailSize(TInt aControlId);
private: 
	IMPORT_C virtual void CEikDialog_Reserved_1();
	IMPORT_C virtual void CEikDialog_Reserved_2();	
private: 
	IMPORT_C virtual void CAknNoteDialog_Reserved();
private: // new virtual function.
	IMPORT_C virtual void CAknStaticNoteDialog_Reserved();
	};

#endif
