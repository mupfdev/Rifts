// EIKMENUB.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKMENUB_H__)
#define __EIKMENUB_H__

#if !defined(__EIKDEF_H__)
#include <eikdef.h>
#endif

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#if !defined(__EIKMENUP_H__)
#include <eikmenup.h>
#endif

#include <eikbtgpc.h>
#include <eikcmobs.h>
#include <aknintermediate.h>

class CEikHotKeyTable;
class CEikMenuBarExtension;


/**
 * The CEikMenuBarTitle class encapsulates the data needed to define a menu bar title and
 * provides some of the functionality required to display the title.
 *
 * @since ER5U
 */
class CEikMenuBarTitle : public CBase
	{
public:
	struct SData
		{
		enum { ENominalTextLength=40 };
		TInt iMenuPaneResourceId;
		TBuf<ENominalTextLength> iText; // less than this actually stored
		};
public:
	IMPORT_C CEikMenuBarTitle();
	IMPORT_C ~CEikMenuBarTitle();
	IMPORT_C void SetIcon(CGulIcon* aIcon);
	IMPORT_C void SetBitmapsOwnedExternally(TBool aOwnedExternally);
	IMPORT_C void DrawIcon(CWindowGc& aGc, TRect aRect, TInt aLeftMargin) const;
	IMPORT_C void CreateIconL(CFbsBitmap* aBitmap, CFbsBitmap* aMask);
	IMPORT_C void SetIconBitmapL(CFbsBitmap* aBitmap);
	IMPORT_C void SetIconMaskL(CFbsBitmap* aMask);
	IMPORT_C CFbsBitmap* IconBitmap() const;
	IMPORT_C CFbsBitmap* IconMask() const;
public: // other functions
	TInt ExtraLeftMargin() const;
	void CalculateBaseLine(TInt& aBaseLine, TInt& aTitleHeight);
public:
	TInt iPos;
	TInt iWidth;
	SData iData;
	TInt iTitleFlags;
private:
	CGulIcon* iIcon;
	};

//
// CEikMenuBar
//

class CEikMenuBar : public CEikBorderedControl, public MEikCommandObserver, public MAknIntermediateState
	{
public:
	DECLARE_TYPE_ID(0x101F4106);

	struct SCursor
		{
		TInt iMenuPaneIndex;
		TInt iMenuItemIndex;
		};

	struct SPosition
		{
		TInt iMenuId;
		SCursor iMenuCursorPos;
		};

	friend class CEikMenuPaneTitle;
private:
	enum {ENothingSelected=-1};
public:
	IMPORT_C ~CEikMenuBar();
	IMPORT_C CEikMenuBar();
public: // framework
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C void Draw(const TRect& aRect) const;
private: // from MCoeInputObserver
	IMPORT_C TCoeInputCapabilities InputCapabilities() const;
public:
	class CTitleArray : public CArrayPtrFlat<CEikMenuBarTitle>
		{
	public:
		IMPORT_C ~CTitleArray();
		IMPORT_C CTitleArray();
		IMPORT_C void AddTitleL(CEikMenuBarTitle* aMenuTitle);
		void DeleteResource(TInt aResource);
		};

public: // new functions
	IMPORT_C void ConstructL(MEikMenuObserver* aMenuObserver,TInt aHotKeyResourceId=0,TInt aMenuTitleResourceId=0);
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void ChangeMenuBarL(TInt aHotKeyResourceId=0,TInt aMenuTitleResourceId=0,TInt aDisplayNow=ETrue);
	IMPORT_C CEikHotKeyTable* SetHotKeyTable(CEikHotKeyTable* aHotKeyTable);
	IMPORT_C void SetMenuTitleResourceId(TInt aMenuTitleResourceId);
	IMPORT_C void SetMenuTitleArray(CTitleArray* aTitleArray);
	IMPORT_C void SetTitleArrayOwnedExternally(TBool aOwnedExternally);
	IMPORT_C SCursor SetMenuCursor(const SCursor& aCursor);
	IMPORT_C void StopDisplayingMenuBar();
	IMPORT_C void TryDisplayMenuBarL();
	IMPORT_C void TryDisplayMenuBarWithoutFepMenusL();
	IMPORT_C void MoveHighlightToL(TInt aNewSelectedTitle,TInt aNewSelectedItem=0);
	IMPORT_C void DrawItem(TInt aItem) const;
	CEikHotKeyTable* HotKeyTable() const { return(iHotKeyTable); }
	IMPORT_C TInt SelectedTitle();
	IMPORT_C TInt SelectedItem();
	IMPORT_C virtual void FindCommandIdInResourceL(TInt aCommandId,TInt& aPaneindex,TInt& aItemindex);
	IMPORT_C CEikMenuPane* MenuPane();
	IMPORT_C void ReduceRect(TRect& aRect) const;
	IMPORT_C CTitleArray* TitleArray();
	IMPORT_C void SetEditMenuObserver(MEikMenuObserver* aEditMenuObserver);
	IMPORT_C void RemoveEditMenuObserver(MEikMenuObserver* aEditMenuObserver);
	// Added by RSD for Avkon
	IMPORT_C TBool IsDisplayed();
private: // from MAknIntermediateState
	void CloseState();
public:	// from CCoeControl
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
private: // from CCoeControl
	IMPORT_C void Reserved_1();
	IMPORT_C void Reserved_2();
	// from MEikCommandObserver
	void ProcessCommandL(TInt aCommandId);
private: // from MObjectProvider
	TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
private:
	void StartDisplayingMenuBarL();
	void HideMenuPane();
	void SaveCurrentMenuPositionL();
	void SetCursorPositionFromArray();
	TBool MenuHasItems();
	void SetMenuHasItems();
	TBool MenuHasPane();
	void SetMenuHasPane();
	TBool TitleArrayOwnedExternally();
	void ResetTitleArray();
	void CreateTitleArrayL();
	void SetMenuPaneFlag(TInt aFlag);
	void AddFEPMenuL();
	void AddMenuIfNotPresentL(TInt aResourceId);
	void UpdateTitleTextBaseline();
private:
	enum TEikMenuFlags {ETitleArrayOwnedExternally=0x01,EMenuHasItems=0x02,EMenuHasPane=0x04,EBackgroundFaded=0x08, ESoundsInstalled=0x10};
	CEikButtonGroupContainer* iMenuCba;
	MEikMenuObserver* iMenuObserver;
	MEikMenuObserver* iEditMenuObserver;
	MEikMenuObserver* iActiveEditMenuObserver;
	CEikMenuPane* iMenuPane;
 	CEikHotKeyTable* iHotKeyTable;
	SCursor iCursor;
	TInt iMenuTitleResourceId;
	TInt iMenuPaneResourceId;
	TInt iMenuHotKeyResourceId;
	TInt iSelectedTitle;
	TInt iBaseLine;
	TInt iMenuTitleLeftSpace;
	TInt iMenuFlags;
	CTitleArray* iTitleArray;
	CArrayFixFlat<SPosition>* iPastMenuPosArray;
	TBool iPreventFepMenu;
	friend class CEikMenuBarExtension;
	CEikMenuBarExtension* iExt;
	};


class CEikMenuPaneTitle : public CEikBorderedControl
	{
public:
	IMPORT_C CEikMenuPaneTitle(CEikMenuBar* aMenuBar);
	IMPORT_C void ConstructL();
	IMPORT_C void SetSelectedTitle(TInt aSelectedTitle);
	IMPORT_C void Draw(const TRect& aRect) const;
    IMPORT_C TMargins Margins() const;
	IMPORT_C void Close();
public:// framework
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
private:
	CEikMenuBar* const iMenuBar;
	TInt iSelectedTitle;
	};

#endif
