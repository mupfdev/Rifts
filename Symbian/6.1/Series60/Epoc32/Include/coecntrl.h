// COECNTRL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COECNTRL_H__)
#define __COECNTRL_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__W32STD_H__)
#include <w32std.h>
#endif

#if !defined(__GULALIGN_H__)
#include <gulalign.h>
#endif

#if !defined(__COEDEF_H__)
#include <coedef.h>
#endif

#if !defined(__COECOBS_H__)
#include <coecobs.h>
#endif

#if !defined(__COEHELP_H__)
#include <coehelp.h>
#endif

#if !defined(__COEINPUT_H__)
#include <coeinput.h>
#endif

#include <coemop.h>

class TResourceReader;
class CCoeEnv;
class MCoeControlContext;
class CCoeControlExtension;

/**
 * The TCoeColorUse class is a packager which pairs a logical colour value with an explanation
 * of how it is used when drawing a control. The explanation is in terms of categories of use
 * e.g.in the 'ground' category, the colour can used for either the foreground
 * or background.
 *
 * @since ER5U
 */
class TCoeColorUse
    {
public:
	enum TGround { EFore=0x01, EBack=0x02 };
	enum TAreas { EContents=0x10, EHighlights=0x20, ESurrounds=0x40, EBorders=0x80 };
	enum TFocus { EActive=0x100, EDimmed=0x200, EShadowed=0x400, EPressed=0x800 };
	enum TState { ENormal=0x1000, ESet=0x2000, EChecked=0x4000 };
	enum TTones { ENeutral=0x10000, ELight=0x20000, EMidLight=0x40000, EMid=0x80000, EDark=0x100000 };
public:
	IMPORT_C TCoeColorUse();
	//
	IMPORT_C void SetUse(TInt aUse);
	IMPORT_C void SetLogicalColor(TInt aLogicalColor);
	IMPORT_C TInt LogicalColor() const;
	IMPORT_C TInt Use() const;
	//
	IMPORT_C TBool IsForeground() const;
	IMPORT_C TBool IsBackground() const;
	//
	IMPORT_C TBool IsContents() const;
	IMPORT_C TBool IsHighlights() const;
	IMPORT_C TBool IsSurrounds() const;
	IMPORT_C TBool IsBorders() const;
	IMPORT_C TBool IsActive() const;
	IMPORT_C TBool IsDimmed() const;
	IMPORT_C TBool IsPressed() const;
	IMPORT_C TBool IsNormal() const;
	IMPORT_C TBool IsSet() const;
private:
    TInt iLogicalColor;
	TInt iUse;
    };

/**
 * @internal
 */
class RCoeExtensionStorage
	{
public:
	RCoeExtensionStorage();
	void Close();
	TInt& Flags();
	TInt Flags() const;
	void SetExtension(CCoeControlExtension* aExtension);
	CCoeControlExtension* Extension() const;
private:
	inline TBool IsFlags() const;
private:
	union
		{
		TInt iFlags;
		CCoeControlExtension* iExtension;
		};
	};

/**
 * The CCoeControl class is the base class for all controls.
 */
class CCoeControl : public CBase, public MObjectProvider
	{
public:
	IMPORT_C CCoeControl();
	IMPORT_C ~CCoeControl();
	// client interface
	IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C virtual void MakeVisible(TBool aVisible);
	IMPORT_C virtual void SetDimmed(TBool aDimmed);
	IMPORT_C virtual void SetContainerWindowL(const CCoeControl& aContainer);
	IMPORT_C void SetContainerWindowL(RWindow& aWindow); 
	IMPORT_C void SetContainerWindowL(RBackedUpWindow& aWindow);
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C virtual void ActivateL();
	IMPORT_C virtual void PrepareForFocusLossL();
	IMPORT_C virtual void PrepareForFocusGainL();
	IMPORT_C virtual void SetAdjacent(TInt aAdjacent);
	IMPORT_C virtual void SetNeighbor(CCoeControl* aNeighbor);
	IMPORT_C virtual TBool HasBorder() const;
	IMPORT_C virtual TSize MinimumSize();
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void GetHelpContext(TCoeHelpContext& aContext) const;
	IMPORT_C virtual TCoeInputCapabilities InputCapabilities() const;
	IMPORT_C TCoeInputCapabilities RecursivelyMergedInputCapabilities() const; // not available before Release 006
	IMPORT_C void DrawNow() const;
	IMPORT_C void DrawDeferred() const;
	IMPORT_C void SetFocus(TBool aFocus,TDrawNow aDrawNow=ENoDrawNow);
	IMPORT_C void SetExtent(const TPoint& aPosition,const TSize& aSize);
	IMPORT_C void SetSize(const TSize& aSize);
	IMPORT_C void SetPosition(const TPoint& aPosition);
	IMPORT_C void SetRect(const TRect& aRect);
	IMPORT_C void SetExtentToWholeScreen();
	IMPORT_C TBool IsFocused() const;
	IMPORT_C TBool IsVisible() const;
	IMPORT_C TBool IsDimmed() const;
	IMPORT_C RDrawableWindow* DrawableWindow() const;
	IMPORT_C TSize Size() const;
	IMPORT_C TPoint Position() const;
	IMPORT_C TRect Rect() const;
	IMPORT_C TPoint PositionRelativeToScreen() const;
	IMPORT_C void SetObserver(MCoeControlObserver* aObserver);
	IMPORT_C MCoeControlObserver* Observer() const;

	/**
	 * Returns a pointer to the control environment. Does not imply transfer of ownership. 
	 */
	inline CCoeEnv* ControlEnv() const;
	
	IMPORT_C TInt Index(const CCoeControl* aControl) const;
	IMPORT_C void SetNonFocusing();
	IMPORT_C void SetFocusing(TBool aFocusing); // not available before Release 005
	IMPORT_C TBool IsNonFocusing() const;
	IMPORT_C void SetControlContext(MCoeControlContext* aContext);
	IMPORT_C void CopyControlContextFrom(const CCoeControl* aControl);
	IMPORT_C MCoeControlContext* ControlContext() const;
	IMPORT_C TBool OwnsWindow() const;
	IMPORT_C TBool IsBackedUp() const;
	IMPORT_C void SetPointerCapture(TBool aCapture=ETrue);
	IMPORT_C void ClaimPointerGrab(TBool aSendUpEvent=ETrue);
	IMPORT_C void IgnoreEventsUntilNextPointerUp();
	IMPORT_C void SetComponentsToInheritVisibility(TBool aInherit=ETrue);
	IMPORT_C void SetGloballyCapturing(TBool aGlobal);
	IMPORT_C void OverrideColorL(TInt aLogicalColor,TRgb aColor); // not available before Release 005
	IMPORT_C TBool GetColor(TInt aLogicalColor,TRgb& aColor) const; // not available before Release 005

	// Context access mechanism - new in Series 60
	IMPORT_C void SetMopParent(MObjectProvider* aParent);

public: // but not exported
	void ProcessPointerEventL(const TPointerEvent& aPointerEvent);
	void ProcessPointerBufferReadyL();
	void RecursivelyMergeInputCapabilities(TCoeInputCapabilities& aInputCapabilities) const;
	void WriteInternalStateNowL(RWriteStream& aWriteStream) const;
protected:
	IMPORT_C virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C virtual void HandlePointerBufferReadyL();
	IMPORT_C virtual void FocusChanged(TDrawNow aDrawNow);
	IMPORT_C virtual void SizeChanged();
	IMPORT_C virtual void PositionChanged();
public:
	IMPORT_C virtual TInt CountComponentControls() const;
	IMPORT_C virtual CCoeControl* ComponentControl(TInt aIndex) const;
protected:
	IMPORT_C void EnableDragEvents();
	IMPORT_C void HandleRedrawEvent(const TRect& aRect) const;
	IMPORT_C RWindow& Window() const;
	IMPORT_C RBackedUpWindow& BackedUpWindow() const;
	IMPORT_C void CloseWindow();
	IMPORT_C void CreateWindowL();
	IMPORT_C void CreateWindowL(const CCoeControl* aParent);
	IMPORT_C void CreateWindowL(RWindowTreeNode& aParent);
	IMPORT_C void CreateWindowL(RWindowGroup* aParent);
	IMPORT_C void CreateBackedUpWindowL(RWindowTreeNode& aParent); // not available before Release 005
	IMPORT_C void CreateBackedUpWindowL(RWindowTreeNode& aParent,TDisplayMode aDisplayMode);
	IMPORT_C void SetAllowStrayPointers();
	IMPORT_C void SetCanDrawOutsideRect();
	IMPORT_C void SetBlank();
	IMPORT_C void ReportEventL(MCoeControlObserver::TCoeEvent aEvent);
	IMPORT_C void SetCornerAndSize(TGulAlignment aCorner,const TSize& aSize);
	IMPORT_C void SetSizeWithoutNotification(const TSize& aSize);
	IMPORT_C CWindowGc& SystemGc() const;
	IMPORT_C void ActivateGc() const;
	IMPORT_C void ResetGc() const;
	IMPORT_C void DeactivateGc() const;
	IMPORT_C TBool IsReadyToDraw() const;
	IMPORT_C TBool IsActivated() const;
	IMPORT_C TBool IsBlank() const;
	IMPORT_C TBool IsBeingDestroyed() const;
	IMPORT_C CCoeControl* GrabbingComponent() const;
	IMPORT_C TBool CapturesPointer() const;
	IMPORT_C void HandleComponentControlsResourceChange(TInt aType); // not available before Release 005u

protected: // from MObjectProvider - new for Series 60
	IMPORT_C virtual TTypeUid::Ptr MopSupplyObject(TTypeUid aId);

private: // from MObjectProvider - new for Series 60
	IMPORT_C virtual MObjectProvider* MopNext();

private:
	friend class CCoeRedrawer;
	IMPORT_C virtual void Draw(const TRect& aRect) const;
	void DrawComponents(const TRect& aRect) const;
	void DrawWindowOwningComponentsNow() const;
	void SetGrabbed(TBool aGrabbed);
	TBool IsGrabbed() const;
	void DoMakeVisible(TBool aVisible);
	void CheckPointerEventPurge() const;
	inline TInt Flags() const;
	inline TInt& Flags();
protected: // was Reserved_1(). Must be left here to maintain BC
	IMPORT_C virtual void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
// reserved virtual function space
	IMPORT_C virtual void Reserved_2();
protected:
	CCoeEnv* iCoeEnv;
	MCoeControlContext* iContext;
	TPoint iPosition;
	TSize iSize;
private:
	RDrawableWindow* iWin;
	MCoeControlObserver* iObserver;
	RCoeExtensionStorage iExt;
	MObjectProvider* iMopParent;
	};

inline CCoeEnv* CCoeControl::ControlEnv() const
	{return(iCoeEnv);}

#endif
