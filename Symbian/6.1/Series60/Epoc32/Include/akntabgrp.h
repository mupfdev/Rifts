/*
* ============================================================================
*  Name     : akntabgrp.h
*  Part of  : AVKON
*
*  Description:
*     Implements tab control to the status pane's navigation pane.
*
*
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNTABGRP_H
#define AKNTABGRP_H

#include <coecntrl.h>
#include <coeccntx.h>
#include <coecobs.h>
#include "aknconsts.h"
#include "aknutils.h"

#include <avkon.mbg> 

//
// Forward declarations.
//
class CEikLabel;
class CEikImage;
class CAknTabGroup;


class CAknTab : public CCoeControl
	{

public:
	enum TAknTabDataType
		{
		EAknTabNone,
		EAknTabText,
		EAknTabIcon,
		EAknTabTextAndIcon
		};

public:
	~CAknTab();

	static CAknTab* NewL(const CCoeControl& aParent,TResourceReader& aReader);
	static CAknTab* NewLC(const CCoeControl& aParent,TResourceReader& aReader);
	static CAknTab* NewL(TInt aId,const CCoeControl& aParent,const TDesC& aTabText);
	static CAknTab* NewLC(TInt aId,const CCoeControl& aParent,const TDesC& aTabText);
	static CAknTab* NewL(TInt aId,const CCoeControl& aParent,const TDesC& aTabText,
							const CFbsBitmap* aTabBitmap,const CFbsBitmap* aMask = NULL);
	static CAknTab* NewLC(TInt aId,const CCoeControl& aParent,const TDesC& aTabText,
							const CFbsBitmap* aTabBitmap,const CFbsBitmap* aMask = NULL);
	static CAknTab* NewL(TInt aId,const CCoeControl& aParent,const CFbsBitmap* aTabBitmap,
															const CFbsBitmap* aMask = NULL);
	static CAknTab* NewLC(TInt aId,const CCoeControl& aParent,const CFbsBitmap* aTabBitmap,
															const CFbsBitmap* aMask = NULL);

    void ReplaceTextL(const TDesC& aTabText);

	void SetActive(TBool aActive,TDrawNow aDrawNow);
	TBool Active() const;
	TInt Id() const;
	enum TAknTabDataType TabType() const;

public: // from CCoeControl
	virtual TSize MinimumSize();
	virtual void SetDimmed(TBool aDimmed);
	virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;

protected: // from CCoeControl
	virtual void SizeChanged();
	virtual TInt CountComponentControls() const;
	virtual CCoeControl* ComponentControl(TInt aIndex) const;
	virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);

private:
    virtual void Draw(const TRect& aRect) const;

private:
	CAknTab(TInt aId);

	void ConstructFromResourceL(TResourceReader& aReader);
	void ConstructL(const TDesC& aTabText);
	void ConstructL(const CFbsBitmap* aTabBitmap,const CFbsBitmap* aMask = NULL);

private:
	CEikLabel* iLabel;
	TInt iId;
	TBool iActive;

    const CFbsBitmap* iBitmap;
    const CFbsBitmap* iBitmapMask;
    TAknLayoutRect iBitmapRect;

	const CFont* iTabTextFont;
    TInt iSpare_1; // Not in use
	};


/**
 * Tab group functionality for navigation pane.
 */
class CAknTabGroup : public CCoeControl, public MCoeControlObserver, public MCoeControlContext
	{
public:
    /**
    * Destructor.
    */
	IMPORT_C ~CAknTabGroup();

    /** 
    * Creates new tab group.
    *
    * @param aParent Parent control.
    */
	IMPORT_C static CAknTabGroup* NewL(const CCoeControl& aParent);

    /** 
    * Creates new tab group and pushes it to the clean up stack.
    *
    * @param aParent Parent control.
    */
    IMPORT_C static CAknTabGroup* NewLC(const CCoeControl& aParent);

public:
    /**
    * Add a tab to the tab group from resources.
    *
    * @param aReader resource reader.
    * @return Id of the added tab.
    */
	IMPORT_C TInt AddTabL(TResourceReader& aReader);
    
    /**
    * Add a tab to the tab group.
    *
    * @param aTabId id of the added tab.
    * @param aTabText text for the tab.
    */
	IMPORT_C void AddTabL(TInt aTabId, const TDesC& aText);
    
    /**
    * Add a tab to the tab group.
    *
    * @param aTabId id of the tab.
    * @param aTabText text for the tab.
    * @param aTabBitmap bitmap for the tab. Ownership of a bitmap is taken.
    * @param aMask bitmap's mask.
    */
	IMPORT_C void AddTabL(TInt aTabId, const TDesC& aText, const CFbsBitmap* aTabBitmap,
										const CFbsBitmap* aMask = NULL);

    /**
    * Add a tab to the tab group.
    *
    * @param aTabId id of the tab.
    * @param aTabBitmap bitmap for the tab. Ownership of a bitmap is taken.
    * @param aMask bitmap's mask.
    */
	IMPORT_C void AddTabL(TInt aTabId, const CFbsBitmap* aTabBitmap, 
										const CFbsBitmap* aMask = NULL);
    /**
    * Replaces a tab with a new one from resources. Tab with same id is replaced.
    *
    * @param aReader resource reader.
    */
	IMPORT_C void ReplaceTabL(TResourceReader& aReader);
    
    /**
    * Replaces a tab with a new one.
    *
    * @param aTabId id of the tab to be replaced.
    * @param aTabText text for the new tab.
    */
	IMPORT_C void ReplaceTabL(TInt aTabId, const TDesC& aText);
    
    /**
    * Replaces a tab with a new one.
    *
    * @param aTabId id of the tab to be replaced.
    * @param aTabText text for the new tab.
    * @param aTabBitmap bitmap for the tab. Ownership of a bitmap is taken.
    * @param aMask bitmap's mask.
    */
	IMPORT_C void ReplaceTabL(TInt aTabId, const TDesC& aText, const CFbsBitmap* aTabBitmap,
										const CFbsBitmap* aMask = NULL);

    /**
    * Replaces a tab with a new one.
    *
    * @param aTabId id of the tab to be replaced.
    * @param aTabBitmap bitmap for the tab. Ownership of a bitmap is taken.
    * @param aMask bitmap's mask.
    */
	IMPORT_C void ReplaceTabL(TInt aTabId, const CFbsBitmap* aTabBitmap, 
										const CFbsBitmap* aMask = NULL);
    
    /**
    * Replaces a tab text with a new one.
    *
    * @param aTabId Id of the tab of replaced tab text.
    * @param aTabText New tab text.
    */
    IMPORT_C void ReplaceTabTextL(TInt aTabId, const TDesC& aTabText);

    /**
    * Delete a tab.
    *
    * @param aTabId id of the tab to be deleted.
    */
	IMPORT_C void DeleteTabL(TInt aTabId);

    /**
    * Hightlight (activate) a tab.
    *
    * @param aTabId id of the tab to be set highlighted.
    */
	IMPORT_C void SetActiveTabById(TInt aTabId);
    
    /**
    * Hightlight (activate) a tab.
    *
    * @param aTabIndex index of the tab to be set highlighted.
    */
	IMPORT_C void SetActiveTabByIndex(TInt aTabIndex);
    
    /**
    * Returns the id of the currently active (=highlighted) tab.
    *
    * @return id of the highlighted tab.
    */
	IMPORT_C TInt ActiveTabId() const;
    
    /**
    * Returns the index of the currently active (=highlighted) tab.
    *
    * @return index of the highlighted tab.
    */
	IMPORT_C TInt ActiveTabIndex() const;
	
    /**
    * Set width of each tab. This width determines what tab layout is used.
    * To get specific tab layout, use following constants/enumerations:
    * (KTabWidthWithOneTab, KTabWidthWithTwoTabs, KTabWidthWithThreeTabs, 
    * KTabWidthWithFourTabs, KTabWidthWithTwoLongTabs, KTabWidthWithThreeLongTabs).
    *
    * @param aWidth width of each tab.
    */
	IMPORT_C void SetTabFixedWidthL(TInt aWidth);

	IMPORT_C void DimTab(TInt aTabId,TBool aDimmed);

	IMPORT_C virtual TBool IsTabDimmed(TInt aTabId) const;

    /**
    * Returns index of a tab.
    *
    * @param aTabId id of a tab.
    * @return index of the tab.
    */
	IMPORT_C virtual TInt TabIndexFromId(TInt aTabId) const;
    
    /**
    * Returns id of a tab.
    *
    * @param aTabIndex index of a tab.
    * @return id of the tab.
    */
	IMPORT_C virtual TInt TabIdFromIndex(TInt aTabIndex) const;
    
    /**
    * Number of tabs in the tab group.
    *
    * @return number of tabs in the tab group.
    */
	IMPORT_C virtual TInt TabCount() const;

public: // from CCoeControl

    /**
    * From CCoeControl. Return minimum size of the control.
    *
    * @return Minimum size of the control.
    */
    IMPORT_C virtual TSize MinimumSize();

    /**
    * From CCoeControl. Handles key events.
    * @param aKeyEvent The key event.
    * @param aType The type of the event.
    * @return Indicates whether or not the key event was used by this control.
    */
    IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

    /**
    * Gets the list of logical colors employed in the drawing of the control,
    * paired with an explanation of how they are used. Appends the list into aColorUseList.
    */
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;

public: // from MCoeControlObserver

    /**
    * From MCoeControlObserver.
    * @param aControl Control that caused the event.
    * @param aEventType Type of the event.
    */
    IMPORT_C virtual void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);

public:	// from MCoeControlContext

    /** 
    * From MCoeControlContext. Allows to modify graphics context before Draw.
    *
    * @param aGc Graphics context to be modified.
    */
    IMPORT_C virtual void PrepareContext(CWindowGc& aGc) const;

protected:	// from CCoeControl

    /**
    * From CCoeControl. Handle the size change events.
    */
	IMPORT_C virtual void SizeChanged();

    /**
    * From CCoeControl. Returns number of controls inside the context pane control.
    * @return Number of component controls.
    */
    IMPORT_C virtual TInt CountComponentControls() const;

    /**
    * From CCoeControl. Returns a control determined by control id.
    * @param anIndex Index of a control to be returned.
    * @return Pointer to control
    */
    IMPORT_C virtual CCoeControl* ComponentControl(TInt aIndex) const;

    /**
    * From CCoeControl. This is called when a focus is changed.
    */
    IMPORT_C virtual void FocusChanged(TDrawNow aDrawNow);

private:
	IMPORT_C CAknTabGroup();

private:
	IMPORT_C virtual void Draw(const TRect& aRect) const;

private:
	enum TDirection
		{
		ELeft,
		ERight
		};

private:
	void ConstructL();
	void CommonAddTabL(CAknTab* aTab);
	void CommonReplaceTabL(CAknTab* aTab);
	void HandleTabStateChangedL(CCoeControl* aControl);
	TInt Index(TInt aTabId) const;
	TBool CycleFocus(TDirection aDirection,TDrawNow aDrawNow);
	TInt LeftMostTabIndex() const;
	TInt RightMostTabIndex() const;
	void DrawLowerBorder(TDrawNow aDrawNow) const;
	void DoDrawLowerBorder() const;
    void ReportNavigationEvent();

	void LoadTabBitmapsL(TInt aNumberOfTabsShown, TBool aLongTabs);

private:
	CArrayPtr<CAknTab>* iTabArray;
	TInt iActiveTab;
	TRect iSpareRect;

	TInt iTabFixedWidth;
	TBool iLongTabs;
	TInt iNumberOfTabsShown;
	TInt iFirstShownTab;

	CFbsBitmap* iTabBitmaps[KTabNumberOfTabBitmaps];
	CFbsBitmap* iTabMaskBitmaps[KTabNumberOfTabBitmaps];

	TInt iBitmapNames[KTabNumberOfTabBitmaps];
	TInt iBitmapMaskNames[KTabNumberOfTabBitmaps];
    TInt iSpare_1; // Not in use
	};


#endif // AKNTABGRP_H
