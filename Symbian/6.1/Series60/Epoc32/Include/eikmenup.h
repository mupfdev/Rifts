// EIKMENUP.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKMENUP_H__)
#define __EIKMENUP_H__

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#if !defined(__EIKDEF_H__)
#include <eikdef.h>
#endif

#if !defined(__EIKSBOBS_H__)
#include <eiksbobs.h> // for TEikScrollEvent
#endif

class MEikMenuObserver;
class CEikHotKeyTable;
class CEikMenuPaneTitle;
class CEikButtonBase;
class CEikScrollBarFrame;
class CEikScrollBar;
class TEikScrollBarModel;
class CGulIcon;


/**
 * The CEikMenuPaneItem class encapsulates the data needed to define a menu pane item and
 * provides some of the functionality required to display the item.
 *
 * @since ER5U
 */
class CEikMenuPaneItem : public CBase
	{
public:
	struct SData
		{
		enum { ENominalTextLength=40 };
		TInt iCommandId;
		TInt iCascadeId;
		TInt iFlags;
		TBuf<ENominalTextLength> iText; // less than this actually stored
		TBuf<1> iExtraText;
		};
public:
	IMPORT_C CEikMenuPaneItem();
	IMPORT_C ~CEikMenuPaneItem();
	IMPORT_C void SetIcon(CGulIcon* aIcon);
	IMPORT_C void DrawItemIcon(CWindowGc& aGc, TRect aRect, TBool aDimmed, TInt aBitmapSpaceRequired) const;
	IMPORT_C void CreateIconL(CFbsBitmap* aBitmap, CFbsBitmap* aMask);
	IMPORT_C CFbsBitmap* IconBitmap() const;
	IMPORT_C CFbsBitmap* IconMask() const;
	IMPORT_C void SetBitmapsOwnedExternally(TBool aOwnedExternally);
	IMPORT_C void SetIconBitmapL(CFbsBitmap* aBitmap);
	IMPORT_C void SetIconMaskL(CFbsBitmap* aMask);
public:
	TInt iPos;
	TInt iHotKeyCode;
	SData iData;
private:
	CGulIcon* iIcon;
	};


class CEikMenuPane : public CEikBorderedControl
	{	
private:
	enum {ENothingSelected=-1};
	class CMenuScroller;
	friend class CMenuScroller;
public:
	typedef TBuf<20> THotKeyDisplayText;
public:
	class CItemArray:public CArrayPtrFlat<CEikMenuPaneItem>
		{
	public:
		IMPORT_C CItemArray();
		IMPORT_C ~CItemArray();
		IMPORT_C void AddItemL(CEikMenuPaneItem* aMenuItem);
		};

public:
	IMPORT_C ~CEikMenuPane();
	IMPORT_C CEikMenuPane(MEikMenuObserver* aMenuObserver);

	IMPORT_C void ConstructL(CEikMenuPane* aOwner, MEikMenuObserver* aEditMenuObserver = NULL);
	IMPORT_C void Reset();
public: // framework
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
public: // from MCoeInputObserver
	IMPORT_C TCoeInputCapabilities InputCapabilities() const;
protected: // framework
	IMPORT_C void Draw(const TRect& aRect) const;
	IMPORT_C void FocusChanged(TDrawNow aDrawNow);
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
public: // new functions
	IMPORT_C void AddMenuItemL(const CEikMenuPaneItem::SData& aMenuItem);
	IMPORT_C void AddMenuItemL(const CEikMenuPaneItem::SData& aMenuItem, TInt aPreviousId);
	IMPORT_C void AddMenuItemsL(TInt aResourceId, TInt aPreviousId=0,TBool aAddSeperator=EFalse);
	IMPORT_C void DeleteMenuItem(TInt aCommandId);
	IMPORT_C void DeleteBetweenMenuItems(TInt aStartIndex, TInt aEndIndex);
	IMPORT_C CEikMenuPaneItem::SData& ItemData(TInt aCommandId);
	IMPORT_C CEikMenuPaneItem* ItemAndPos(TInt aCommandId,TInt& aPos);
	IMPORT_C void StartDisplayingMenuPane(const CEikHotKeyTable* aHotKeyTable,const TPoint& aTargetPos, const CEikMenuPaneTitle* aMenuPaneTitle,TInt aMinWidth,  TPopupTargetPosType aTargetType = EPopupTargetTopLeft);
	IMPORT_C void SetItemTextL(TInt aCommandId,const TDesC& aDes);
	IMPORT_C void SetItemTextL(TInt aCommandId,TInt aRid);
	IMPORT_C void SetItemDimmed(TInt aCommandId,TBool aDimmed);
	IMPORT_C void SetItemButtonState(TInt aCommandId,TInt aButtonState);
	IMPORT_C void SetSelectedItem(TInt aSelectedItem);
	IMPORT_C TInt SelectedItem() const;
	IMPORT_C void CloseCascadeMenu();
	IMPORT_C void SetItemArray(CItemArray* aItemArray);
	IMPORT_C void SetItemArrayOwnedExternally(TBool aOwnedExternally);
	IMPORT_C void SetLaunchingButton(CEikButtonBase* aButton);
	IMPORT_C void MoveHighlightTo(TInt aNewSelectedItem);
	IMPORT_C TInt NumberOfItemsInPane() const;
	IMPORT_C void Close();
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType,TBool aConsumeAllKeys); // not available before Platform 004
	IMPORT_C void SetScrollBarOnLeft(TBool aOnLeft);
	IMPORT_C void SetArrowHeadScrollBar(TBool aArrowHead);
	// new for AVKON
	IMPORT_C void NavigateToNextItem();
	IMPORT_C void InsertMenuItemL(const CEikMenuPaneItem::SData& aMenuItem, TInt aPosition);
	void ActivateCurrentItemL();
	TBool CancelActiveMenuPane();
	void FilterDimmedItems();
	void ClipMenuItems(TInt aWidth);
	CEikMenuPane* CascadeMenuPane();
private:
	enum { EInvalidCurrentSize=0x01, EBackgroundFaded=0x02 };
private: // new functions
	TSize CalculateSize();
	enum THighlightType {ENoHighlight,EDrawHighlight,ERemoveHighlight};
	void DrawItem(CWindowGc& aGc,TInt aItem,THighlightType aHighlight) const;
	void DrawCascadeSymbol(CGraphicsContext& aGc,const TRect& aRect,TRgb aColor) const;
	void FindHotKeyDisplayText(TDes& aDes,const CEikMenuPaneItem& aItem) const;
	void ReportSelectionMadeL();
	void ReportCanceled();
	void GiveVisualFeedback();
	void LaunchCascadeMenuL(TInt aCascadeMenuId);
	void DoLaunchCascadeMenuL(TInt aCascadeMenuId);
	void TryLaunchCascadeMenuL(const CEikMenuPaneItem& aItem);
	void PrepareGcForDrawingItems(CGraphicsContext& aGc) const;
	TBool ItemArrayOwnedExternally();
	TBool IsHotKeyL(const TInt modifiers,const TInt aCode);
	TBool MoveToItemL(TInt aCode, TInt aModifiers);
	void HandleScrollEventL(CEikScrollBar* aScrollBar,TEikScrollEvent aEventType);
	void CreateScrollBarFrame();
	void UpdateScrollBar();
	void DoUpdateScrollBarL();
	void UpdateScrollBarThumbsL();
	static TInt UpdateScrollBarCallBackL(TAny* aObj);
	TRect ViewRect() const;
	TInt NumberOfItemsThatFitInView() const;
	TInt TotalItemHeight() const;
	void ScrollToMakeItemVisible(TInt aItemIndex);
	void Scroll(TInt aAmount);
	TBool CheckCreateScroller();
	void CheckCreateScrollerL();
	void ResetItemArray();
	void CreateItemArrayL();
	void SetVScrollBarFlag();
	TInt TopHighlightGap() const;
	TInt BottomHighlightGap() const;
	TInt EvaluateMaxIconWidth() const;
	void CreateIconFromResourceL(TResourceReader& aReader, CEikMenuPaneItem& aItem);
	// new for AVKON
	void AnimateMenuPane(TPoint aNewPos);

	// To make layout correct
	TRect ListMenuPane() const;
	TRect PopupMenuWindow() const;
	TRect PopupSubmenuWindow() const;
private: // from CCoeControl
	IMPORT_C void Reserved_1();
	IMPORT_C void Reserved_2();
private:
	friend class CEikMenuButton; // added by SimonC 7/7/97
	MEikMenuObserver* iMenuObserver;
	MEikMenuObserver* iEditMenuObserver;
	CEikMenuPane* iCascadeMenuPane;
	const CEikMenuPaneTitle* iMenuPaneTitle;
 	const CEikHotKeyTable* iHotKeyTable;
	CEikMenuPane* iOwner;
	CItemArray* iItemArray;
	TBool iArrayOwnedExternally;
	TBool iAllowPointerUpEvents;
	TInt iNumberOfDragEvents;
	TInt iSelectedItem;
	TInt iItemHeight;
	TInt iBaseLine;
	TInt iHotkeyColWidth;
	TInt iFlags;
	CEikScrollBarFrame* iSBFrame;
	CMenuScroller* iScroller;
	CEikButtonBase* iLaunchingButton; // for popouts only
	TInt iSubPopupWidth; // 0..2
	TBool iEnableAnimation;
	TInt iSpare;
	};



#endif

