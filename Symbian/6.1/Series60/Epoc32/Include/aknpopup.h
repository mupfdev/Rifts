/*
* ============================================================================
*  Name     : AknPopup.h
*  Part of  : Avkon
*
*  Description:
* Support for Avkon Popped-up lists
*
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#if !defined(__AKNPOPUP_H__)
#define __AKNPOPUP_H__

#include <coecntrl.h>
#include <eikcmobs.h>
#include <eiklbx.h>
#include <aknpopuplayout.h>
#include <aknintermediate.h>
#include <aknpopupfader.h>

class CAknPopupHeadingPane;
class CEikButtonGroupContainer;
class CEikListBox;

/** Used to popup a list or grid. Takes an existing listbox control and
 *  puts it into a popup frame together with an optional title.
 *
 * CAknPopupList is _not_ a dialog!
 *
 * There are two standard usages of CAknPopupList:
 * CAknPopupList *plist = CAknPopupList::NewL(...);
 * CleanupStack::PushL(plist);
 * ...
 * TInt popupOk = plist->ExecuteLD(...);
 * // No leaving functions allowed between executeLD and CleanupStack::Pop().
 * CleanupStack::Pop(); // plist
 * if (popupOk) { ... } else { ... }
 *
 * And then another way:
 * iPList = CAknPopupList::NewL(...);
 * ...
 * TInt popupOk = iPlist->ExecuteLD(...);
 * // No leaving functions allowed between ExecuteLD and iPlist=NULL;
 * iPlist = NULL;
 * if (popupOk) {... } else {... }
 * // note, destructor deletes the iPlist instance.
 * 
 * Both these work corretly and leave-safe way. Notice this usage is pretty
 * different of how dialogs work. With dialogs you _always_ want to do 
 * CleanupStack::Pop() before calling ExecuteLD().
 */
class CAknPopupList : public CEikBorderedControl, public MEikCommandObserver, public MEikListBoxObserver, public MCoeControlObserver, public MAknIntermediateState, public MAknFadedComponent
	{
public:
	IMPORT_C static CAknPopupList* NewL(CEikListBox* aListBox, TInt aCbaResource, AknPopupLayouts::TAknPopupLayouts aType =AknPopupLayouts::EMenuWindow);
	IMPORT_C TBool ExecuteLD();
	IMPORT_C void SetTitleL(const TDesC& aTitle);
	IMPORT_C void CancelPopup();
public: // Access methods
	IMPORT_C CEikButtonGroupContainer *ButtonGroupContainer();
	IMPORT_C CAknPopupHeadingPane *Heading();
	IMPORT_C CAknPopupHeadingPane *Heading() const;
	IMPORT_C CEikListBox *ListBox();
	
	IMPORT_C void SetMaximumHeight(TInt aItems);
protected:
	// From MEikCommandObserver
	IMPORT_C void ProcessCommandL(TInt aCommandId);
	// From MEikListBoxObserver
	IMPORT_C void HandleListBoxEventL(CEikListBox* aListBox, TListBoxEvent aEventType);
	// From MCoeControlObserver
	IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
protected:
	IMPORT_C CAknPopupList();
	IMPORT_C ~CAknPopupList();
	IMPORT_C void ConstructL(CEikListBox* aListBox, TInt aCbaResource, AknPopupLayouts::TAknPopupLayouts aType );
	IMPORT_C virtual void AttemptExitL(TBool aAccept);
	IMPORT_C virtual void SetupWindowLayout(AknPopupLayouts::TAknPopupLayouts aType);
	IMPORT_C CEikListBox* ListBox() const;
	IMPORT_C const TAknPopupWindowLayoutDef &Layout() const;
	IMPORT_C TAknPopupWindowLayoutDef &Layout();

protected: // from MObjectProvider
	IMPORT_C TTypeUid::Ptr MopSupplyObject(TTypeUid aId);

private:
	void FadeBehindPopup(TBool aFade);

private:
	// the following needs to be imported, because they need to be
	// used in virtual table of any derived class.
	IMPORT_C TSize MinimumSize();
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C void Draw(const TRect& aRect) const;
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C void FocusChanged(TDrawNow aDrawNow);

	IMPORT_C void CloseState();
	static TInt ClosePopup(TAny *aObj);
	// From MAknFadedComponent
	IMPORT_C virtual TInt CountFadedComponents();
	IMPORT_C virtual CCoeControl* FadedComponent(TInt aIndex);
protected: // these are protected to allow overriding virtual functions.
	CEikListBox*				iListBox;
	CEikButtonGroupContainer*	iPopoutCba;
	CAknPopupHeadingPane*		iTitle;
	TBool*						iReturn;	// iReturn is the address to hold the return value from the popup
	TBool						iMarkable;
	TInt						iCurrentResource;
	AknPopupLayouts::TAknPopupLayouts iWindowType;
	TAknPopupWindowLayoutDef iLayout;
    
    TBool iAppBroughtForwards;
	TAknPopupFader iPopupFader;
	CIdle *iIdle;

	CActiveSchedulerWait iWait;		// owned, safe to use as direct member data.
private:
	TInt iSpare;	
	};

#endif



