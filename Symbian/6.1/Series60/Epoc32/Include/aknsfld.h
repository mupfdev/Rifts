/*
* ============================================================================
*  Name     : AknSfld.h
*  Part of  : Avkon
*
*  Description:
*  Search Field support. 
*
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef __AKNSFLD_H__
#define __AKNSFLD_H__

#include <coecntrl.h>
#include <gulicon.h>
#include <eikgted.h>

class CEikEdwin;
class CGlobalText;
class CAknInputFrame;
class CAknSearchFieldIndicator;

/**
 * The CAknSearchField class implements a
 *
 * Search field control. There are four different styles for the search field
 * defined by a TSearchFieldStyle.
 *
 */
class CAknSearchField : public CCoeControl,
                        public MCoeControlObserver
{
public:
	enum TSearchFieldStyle 
		{
		ESearch, // Use only ESearch in Series 60
		EInput,		
		EUrl,			
		EPhone,
		EPlain,
		EPopup, // Use as popup search field
		EPinb,   // Use as pinb search field
		EClockApp, // for Clock application/list_single_heading_pane
		EFixed,    // same as ESearch, but using CreateWindowL().
		ESearchWithoutLine // odd layout where no line is used
		};
public:
	IMPORT_C ~CAknSearchField();
	IMPORT_C static CAknSearchField* NewL(const CCoeControl& aParent, TSearchFieldStyle aFieldStyle, CGulIcon* aIcon, TInt aTextLimit);
public:					// for search string manipulation
	IMPORT_C TInt TextLength() const;
	IMPORT_C void GetSearchText(TDes& aSearchTxt) const;
	IMPORT_C void SetSearchTextL(const TDesC& aSearchTxt);
	IMPORT_C void SelectSearchTextL();
	IMPORT_C void ResetL();
	IMPORT_C void SetInfoTextL(const TDesC& aText);
	IMPORT_C void ClipboardL(CEikEdwin::TClipboardFunc aClipboardFunc);
public:	// from MCoeControlObserver
	void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
public: // From CCoeControl
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C TSize MinimumSize();
private: // from MObjectProvider
	TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
private:
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	void SizeChanged();
	void FocusChanged(TDrawNow aDrawNow);
private:
	void ConstructL(const CCoeControl& aParent, TSearchFieldStyle aFieldStyle, CGulIcon* aIcon, TInt aTextLimit);
	CAknSearchField(); 
private:
	void ZoomEditorL();
private:
	CEikEdwin* iEditor;
	CGlobalText* iGlobalText;
	CAknInputFrame* iInputFrame;
    CAknSearchFieldIndicator* iIndicator; 
	};

#endif


