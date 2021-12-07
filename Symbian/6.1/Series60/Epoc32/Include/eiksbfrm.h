// EIKSBFRM.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
	
#if !defined(__EIKSBFRM_H__)
#define __EIKSBFRM_H__

#include <lafpublc.h>
#if !defined(__AKNSCRLB_H__)
#include <aknscrlb.h>
#endif

class CEikCba;

// 
// TEikScrollBarFrameLayout
//

class TEikScrollBarFrameLayout
	{
public:
	// enums
	enum TTilingMode
		{
		EClientRectConstant,
		EInclusiveRectConstant
		};
public:
	// c'tor
	IMPORT_C TEikScrollBarFrameLayout();

	// set all margins to the same value
	IMPORT_C void SetInclusiveMargin(TInt aMargin);
	IMPORT_C void SetClientMargin(TInt aMargin);
public:
	TMargins iInclusiveMargin;
	TMargins iClientMargin;
	TSize iClientAreaGranularity;
	TTilingMode iTilingMode;
	};

// 
// CEikScrollBarFrame
//

class CEikCornerWindow;

class CEikScrollBarFrame : public CBase
	{
public:	// enums
	enum TScrollBarVisibility
		{
		EOff,
		EOn,
		EAuto
		};
	enum TScrollBarType
		{
		ENormalScrollBar	=0x0,
		EArrowHead			=0x200
		};
	enum TScrollBarSide
		{
		EBottomOrRight		=0x0,
		ETopOrLeft			=0x800
		};

	enum TScrollBarManagement 
		{
		EComponent					,//=SLafScrollBarFrame::EComponent,
		EFloating					,//=SLafScrollBarFrame::EFloating,
		EApplicationScrollBar		//=SLafScrollBarFrame::EApplicationScrollBar
		};

	enum TScrollBarFrameFlags
		{
		EHVisible			=0x01,
		EVVisible			=0x02,
		};
private:
	enum TMarginsAdjustmentMode
		{
		EGrow,
		EShrink
		};

public:	// specific
	CEikScrollBarFrame(){}
	IMPORT_C CEikScrollBarFrame(CCoeControl* aParentWindow, MEikScrollBarObserver* aObserver, TBool aPreAlloc=EFalse);
	IMPORT_C ~CEikScrollBarFrame();

	// drawing
	IMPORT_C void DrawScrollBarsNow() const;

	// scrollbar visibility functions
	IMPORT_C void SetScrollBarVisibilityL(TScrollBarVisibility aHVisibility, TScrollBarVisibility aVVisibility);
	inline TScrollBarVisibility HScrollBarVisibility() const;
	inline TScrollBarVisibility VScrollBarVisibility() const;

	// scrollbar dimming
	IMPORT_C void SetScrollBarsDimmed(TBool aHorizDimmed, TBool aVertDimmed) const;

	// Set scrollbar observers
	IMPORT_C void SetScrollBarFrameObserver(MEikScrollBarObserver* aObserver);

	// Model setting. Does not actually draw anything until the thumb or focus setting functions below are called.
	IMPORT_C TBool Tile(TEikScrollBarModel* aVModel);
	IMPORT_C TBool TileL(TEikScrollBarModel* aHModel, TEikScrollBarModel* aVModel,
			  TRect& aClientRect, TRect& aInclusiveRect, const TEikScrollBarFrameLayout& aLayout);
	
	// move scrollbar thumbs functions
	IMPORT_C void MoveThumbsBy(TInt aDeltaX, TInt aDeltaY);
	IMPORT_C void MoveHorizThumbTo(TInt aHorizThumbPos);
	IMPORT_C void MoveVertThumbTo(TInt aVertThumbPos);
	IMPORT_C void SetVFocusPosToThumbPos(TInt aFocusPosition);

 	IMPORT_C TInt ScrollBarBreadth(CEikScrollBar::TOrientation aOrientation) const;

	// scroll bar frame behavior functions
	IMPORT_C void SetAdjustsHorizontalModel(TBool aAdjusts); 
	IMPORT_C void SetAdjustsVerticalModel(TBool aAdjusts);
	IMPORT_C TBool AdjustsHorizontalModel() const;
	IMPORT_C TBool AdjustsVerticalModel() const;

	// scrollbar flags functions
	inline void SetScrollBarFrameFlags(TInt aMask);
	inline void SetFlagsForHScrollBar(TInt aMask);
	inline void SetFlagsForVScrollBar(TInt aMask);
	inline void ClearFlagsForHScrollBar(TInt aMask);
	inline void ClearFlagsForVScrollBar(TInt aMask);
	inline TInt FlagsForHScrollBar() const;
	inline TInt FlagsForVScrollBar() const;

	// does a scrollbar exist? function
	IMPORT_C TBool ScrollBarExists(CEikScrollBar::TOrientation aOrientation) const;

	// component control functions
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C CEikScrollBar* GetScrollBarHandle(CEikScrollBar::TOrientation aOrientation) const;
	IMPORT_C CEikScrollBar* VerticalScrollBar() const;
	IMPORT_C void SetTypeOfHScrollBar(TScrollBarType aType);
	IMPORT_C void SetTypeOfVScrollBar(TScrollBarType aType);
	IMPORT_C void SetSideOfHScrollBar(TScrollBarSide aSide);
	IMPORT_C void SetSideOfVScrollBar(TScrollBarSide aSide);
	IMPORT_C TScrollBarType TypeOfHScrollBar() const;
	IMPORT_C TScrollBarType TypeOfVScrollBar() const;
	IMPORT_C TBool RightSideForHScrollBar() const;
	IMPORT_C TBool RightSideForVScrollBar() const;
	IMPORT_C TBool IsArrowHeadScrollBar(TInt aFlag) const;

	// application scroll bar utilities
  	IMPORT_C static void SetApplicationScrollBarL(CEikScrollBar::TOrientation aOrientation, CEikScrollBar* aScrollBar);
	IMPORT_C static CEikScrollBar* ApplicationScrollBar(CEikScrollBar::TOrientation aOrientation);

	// scroll bar attributes functions
	IMPORT_C void SetScrollBarManagement(CEikScrollBar::TOrientation aOrientation, TScrollBarManagement aManagement);
	IMPORT_C TScrollBarManagement ScrollBarManagement(CEikScrollBar::TOrientation aOrientation) const;
	IMPORT_C void SetScrollBarControlType(CEikScrollBar::TOrientation aOrientation, TInt aControlType);
	IMPORT_C TInt ScrollBarControlType(CEikScrollBar::TOrientation aOrientation) const;
	IMPORT_C void SetScrollBarSide(CEikScrollBar::TOrientation aOrientation, TScrollBarSide aSide);
	IMPORT_C TScrollBarSide ScrollBarSide(CEikScrollBar::TOrientation aOrientation) const;
	IMPORT_C void SetScrollBarBreadth(CEikScrollBar::TOrientation aOrientation, TInt aBreadth);
	IMPORT_C TBool AdjustsModel(CEikScrollBar::TOrientation aOrientation) const;

	// for CEikScrollBars use
	void DisconnectExternalScrollBar(CEikScrollBar* aScrollBar);

protected:
	// Accessor methods
	void SetParentWindow(CCoeControl* aParentWindow);
	CCoeControl* ParentWindow() const;

protected:
	struct SBarData
		{
		CAknScrollBar* iBar;
		TEikScrollBarModel iModel;
		TScrollBarVisibility iVisibility;
		TBool iExternalScrollBarAttached;
		};

private:
	void CalcTheoreticalScrollBarVisibility(const TEikScrollBarModel* aVModel);
	void ApplyModel(SBarData& aSBar);
	void MakeSBarVisible(SBarData& aSBar, TBool aVisible);
	void GetScrollBars();
	CEikCba* GetCurrentCba();

protected:
	SBarData iV;

private:
	CCoeControl* iParentWindow;
	TInt iScrollBarFrameFlags;
	};

inline CEikScrollBarFrame::TScrollBarVisibility CEikScrollBarFrame::HScrollBarVisibility() const
	{ return EOff; }
inline CEikScrollBarFrame::TScrollBarVisibility CEikScrollBarFrame::VScrollBarVisibility() const
	{ return iV.iVisibility; }
inline void CEikScrollBarFrame::SetScrollBarFrameFlags(TInt aMask)
	{ iScrollBarFrameFlags|=aMask; }
inline void CEikScrollBarFrame::SetFlagsForHScrollBar(TInt /*aMask*/)
	{ }
inline void CEikScrollBarFrame::SetFlagsForVScrollBar(TInt /*aMask*/)
	{ }
inline void CEikScrollBarFrame::ClearFlagsForHScrollBar(TInt /*aMask*/)
	{ }
inline void CEikScrollBarFrame::ClearFlagsForVScrollBar(TInt /*aMask*/)
	{ }
inline TInt CEikScrollBarFrame::FlagsForHScrollBar() const
	{ return 0; }
inline TInt CEikScrollBarFrame::FlagsForVScrollBar() const
	{ return 0; }



// Cba scroll bar frame (with it's own scrollbar creation methods)
class CEikCbaScrollBarFrame : public CEikScrollBarFrame
	{
public:
	CEikCbaScrollBarFrame(CCoeControl* aParentWindow, MEikScrollBarObserver* aObserver, TBool aPreAlloc=EFalse);
	void ConstructL();
	};

#endif
