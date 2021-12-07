// W32STD.H
//
// Copyright (c) 1994-2001 Symbian Ltd.  All rights reserved.
//

//
// Standard window server header file
//

#ifndef __W32STD_H__
#define __W32STD_H__

#ifndef __FNTSTORE_H__
#include <fntstore.h>
#endif
#ifndef __BITDEV_H__
#include <bitdev.h>
#endif
#ifndef __BITSTD_H__
#include <bitstd.h>
#endif

class RWindowBase;
class RWindow;
class RWsBuffer;


enum TScreenModeEnforcement
	{
	ESizeEnforcementNone,
	ESizeEnforcementPixelsAndRotation,
	ESizeEnforcementPixelsTwipsAndRotation,
		// Possibly more modes later?
	};

struct TPixelsAndRotation	// zzz Should be in GDI as well? Or maybe not.
	{
	TSize iPixelSize;
	CFbsBitGc::TGraphicsOrientation iRotation;
	};

struct TPixelsTwipsAndRotation	// zzz Should be in GDI as well? Or maybe not.
	{
	TSize iPixelSize;
	TSize iTwipsSize;
	CFbsBitGc::TGraphicsOrientation iRotation;
	};

enum {KLogMessageLength=0x80};
typedef TBuf<KLogMessageLength> TLogMessageText;

enum {KPasswordWindowGroupPriority=1000};
enum {KOrdinalPositionSwitchToOwningWindow=0x80000000};

enum TCornerType
//
// Bottom 16 bits available for corner type
//
	{
	EWindowCornerSquare,
	EWindowCorner1,
	EWindowCorner2,
	EWindowCorner3,
	EWindowCorner5,
	EWindowCornerRegion,		// Private
	ECornerTypeMask=0xFFFF
	};
enum TCornerFlags
//
// Top 16 bits available for corner flags
//
	{
	EWindowCornerNotTL=0x10000,
	EWindowCornerNotTR=0x20000,
	EWindowCornerNotBL=0x40000,
	EWindowCornerNotBR=0x80000,
	};

enum TWindowBackupType
	{
	EWindowBackupAreaBehind=0x0001,
	EWindowBackupFullScreen=0x0002,
	};

enum TEventCode
	{
	EEventNull,
	EEventKey,
	EEventKeyUp,
	EEventKeyDown,
	EEventModifiersChanged,
	EEventPointer,			//5
	EEventPointerEnter,
	EEventPointerExit,
	EEventPointerBufferReady,
	EEventDragDrop,
	EEventFocusLost,		//10
	EEventFocusGained,
	EEventSwitchOn,
	EEventPassword,
	EEventWindowGroupsChanged,
	EEventErrorMessage,		//15
	EEventMessageReady,
	EEventMarkInvalid,	// For internal use only
	EEventSwitchOff,
	EEventKeySwitchOff,
	EEventScreenDeviceChanged, //20
	EEventFocusGroupChanged,
	EEventCaseOpened,
	EEventCaseClosed,
	EEventWindowGroupListChanged,
	EEventUser=1000,	// Event codes from EEventUser upwards may be used for non-wserv events
						// No event codes below this should be defined except by the window server
	};

enum THotKey
	{
	EHotKeyEnableLogging,
	EHotKeyDisableLogging,
	EHotKeyStateDump,
	EHotKeyOfDeath,
	EHotKeyShutDown,
	EHotKeyHeapDump,
	EHotKeyIncContrast,
	EHotKeyDecContrast,
	EHotKeyOff,
	EHotKeyBacklightOn,
	EHotKeyBacklightOff,
	EHotKeyBacklightToggle,
	EHotKeyScreenDimension0,
	EHotKeyScreenDimension1,
	EHotKeyScreenDimension2,
	EHotKeyScreenDimension3,
	EHotKeyCycleDisplaySize,		//Used for debug purposes only
	EHotKeyCycleOrientation,
	EHotKeyIncBrightness,
	EHotKeyDecBrightness,
	EHotKeyFirstKeyType=EHotKeyEnableLogging,		//Must always be set to the first one
	EHotKeyLastKeyType=EHotKeyDecBrightness,		//Must always be set to the last one
	};

enum TPasswordMode
	{
	EPasswordCancel,	// Releases ownership of the password handling, allows another window to take over
	EPasswordNone,		// No password handling but another window can not take control of password handling
	EPasswordOnceADay,
	EPasswordAlways,
	EPasswordAlwaysTriggerNow,
	EPasswordOnceADayTriggerNow,
	};

struct TTextCursor
    {
	enum EType
		{
		ETypeNone,		// Do not use in app interface, private for window server use only
		ETypeRectangle,
		ETypeHollowRectangle,
		ETypeFirst=ETypeRectangle,			//Must be the first available cursor type
		ETypeLast=ETypeHollowRectangle,		//Must be the last available cursor type
		};
	enum EFlags
		{
		EFlagNoFlash=0x1,
//private flags
		EUserFlags=0x0000FFFF,
		EFlagClipped=0x10000,
		EPrivateFlags=0xFFFF0000,
		};
	EType iType;
    TInt iHeight;
    TInt iAscent;
    TInt iWidth;
    TUint iFlags;
	TRgb iColor;
    };

enum TSpriteFlags
	{
	ESpriteFlash=0x1,
	ESpriteNoChildClip=0x2,
	ESpriteNoShadows=0x4,
// Private flags, do not use
	ESpriteNonSystemFlags=0x0000FFFF,
	ESpriteSystemFlags=	  0xFFFF0000,
	ESpritePointer=0x10000,
	ESpriteOOM=0x20000,
	ESpriteDisabled=0x40000,
	ESpriteActive=0x80000,
	};
struct TSpriteMember
	{
	CFbsBitmap *iBitmap;		// If NULL, there is no sprite for the time specified
	CFbsBitmap *iMaskBitmap;
	TBool iInvertMask;
	CGraphicsContext::TDrawMode iDrawMode;	// Only applies if mask is NULL
	TPoint iOffset;				// Offset from sprites central position
	TTimeIntervalMicroSeconds32 iInterval;
	};

enum TEventControl {EEventControlAlways, EEventControlOnlyWithKeyboardFocus, EEventControlOnlyWhenVisible};

enum TPointerFilter
	{
	//Basic Types
	EPointerFilterEnterExit=0x1,
	EPointerFilterMove=0x2,
	EPointerFilterDrag=0x4,
	EPointerGenerateSimulatedMove=0x8,
	//Combinations of the above
	EPointerMoveEvents=EPointerFilterMove|EPointerGenerateSimulatedMove,
	};

struct TPointerEvent
	{
	enum TType
		{
		EButton1Down,
		EButton1Up,
		EButton2Down,
		EButton2Up,
		EButton3Down,
		EButton3Up,
		EDrag,
		EMove,
		EButtonRepeat,
		ESwitchOn,
		};
	TType iType;	// Type of pointer event
	TUint iModifiers;	// State of pointing device and associated buttons
	TPoint iPosition; 	// Window co-ordinates of mouse event
	TPoint iParentPosition; 	// position relative to parent window
	};

struct TKeyEvent
	{
	TUint iCode;
	TInt iScanCode;
	TUint iModifiers;	// State of modifier keys and pointing device
	TInt iRepeats;		// Count of auto repeats generated
	};

struct TModifiersChangedEvent
	{
	TUint iChangedModifiers;	// Bits set mean this modifier has changed
	TUint iModifiers;			// Current state of modifiers
	};

struct TWsErrorMessage
	{
	enum TErrorCategory
		{
		EDrawingRegion,
		EBackLight,		//For backlight and brightness
		ELogging,
		EContrast,
		};
	TErrorCategory iErrorCategory;
	TUint iError;
	};

class TWsRedrawEvent
	{
public:
	inline TUint Handle() const;
	inline TRect Rect() const;
protected:
	TUint iHandle;
	TRect iRect;			// Rectangle to redraw
	};

class TWsPriorityKeyEvent
	{
public:
	inline TKeyEvent *Key() const;
	inline TUint Handle() const;
	inline void SetHandle(TUint aHandle);
protected:
	TUint iHandle;
	TUint8 iEventData[sizeof(TKeyEvent)];
	};

class TWsEvent
	{
public:
	enum {EWsEventDataSize=sizeof(TPointerEvent)};
public:
	inline TPointerEvent *Pointer() const;
	inline TKeyEvent *Key() const;
	inline TModifiersChangedEvent *ModifiersChanged() const;
	inline TWsErrorMessage *ErrorMessage() const;
	inline TUint8 *EventData() const;
	inline TInt Type() const;
	inline TUint Handle() const;
	inline TTime Time() const;
	inline void SetType(TInt aType);
	inline void SetHandle(TUint aHandle);
	inline void SetTimeNow();
protected:
	TInt iType;
	TUint iHandle;
	TTime iTime;
	TUint8 iEventData[EWsEventDataSize];
	};

class RWsPointerCursor; // Forward ref
enum TPointerCursorMode
	{
	EPointerCursorNone,		//Don't have a pointer cursor
	EPointerCursorFixed,	//Only use the default system pointer cursor
	EPointerCursorNormal,	//Use the default system pointer cursor unless the window specifies one
	EPointerCursorWindow,	//Only have a pointer cursor when the window specifies one
	EPointerCursorFirstMode=EPointerCursorNone,
	EPointerCursorLastMode=EPointerCursorWindow,		//Must be the last valid mode
	};

class MWsClientClass
	{
	friend class CWindowGc;
public:
	MWsClientClass();
	MWsClientClass(RWsBuffer *aBuffer);
	inline TInt WsHandle() const;
protected:
	void Write(const TAny *aData, TInt aLength,const TAny *aData2, TInt aLength2,TUint aOpcode) const;
	void Write(const TAny *aBuf, TInt aBufLen,TUint aOpcode) const;
	void Write(TUint aOpcode) const;
	void WriteInt(TInt aInt, TUint aOpcode) const;
	void WriteRect(const TRect &aRect, TUint aOpcode) const;
	void WritePoint(const TPoint &aPoint, TUint aOpcode) const;
	void WriteSize(const TSize &aSize, TUint aOpcode) const;
	TInt WriteReply(TUint aOpcode) const;
	TInt WriteReplyInt(TInt aInt, TUint aOpcode) const;
	TInt WriteReply(const TAny *aBuf, TInt aBufLen,TUint aOpcode) const;
	TInt WriteReply(const TAny *aBuf, TInt aBufLen,const TAny *aBuf2, TInt aBuflen2,TUint aOpcode) const;
	TInt WriteReplyP(TAny *aPackage,TUint aOpcode) const;
	TInt WriteReplyIntP(TInt aInt, TAny *aPackage,TUint aOpcode) const;
	TInt WriteReplyP(const TAny *aBuf, TInt aBufLen,TAny *aPackage,TUint aOpcode) const;
	TInt WriteReplyP(const TAny *aBuf, TInt aBufLen,const TAny *aBuf2, TInt aBuflen2,TAny *aPackage,TUint aOpcode) const;
protected:
	TInt32 iWsHandle;
	RWsBuffer *iBuffer;
	};

class RWsSession : public MWsClientClass, public RSessionBase
	{
	friend class RWsBuffer;
	friend class RWindowTreeNode;
	friend class CWsScreenDevice;
	friend class CWsBitmap;
	friend class RAnimDll;
	friend class RWsSpriteBase;
	friend class RDirectScreenAccess;
public:
	enum TComputeMode
		{
		EPriorityControlDisabled,
		EPriorityControlComputeOn,
		EPriorityControlComputeOff
		};
	enum {ESystemInfoArraySize=16};
	struct SSystemInfo
		{
		TInt iInfo[ESystemInfoArraySize];
		};
//
public:
	IMPORT_C RWsSession();
	IMPORT_C TInt Connect();
	IMPORT_C void Close();
	IMPORT_C TVersion Version();

	IMPORT_C TInt SetHotKey(THotKey aType, TUint aKeyCode, TUint aModifierMask, TUint aModifier);
	IMPORT_C TInt ClearHotKeys(THotKey aType);
	IMPORT_C TInt RestoreDefaultHotKey(THotKey aType);
//
	IMPORT_C void EventReady(TRequestStatus *aStat);
	IMPORT_C void EventReadyCancel();
	IMPORT_C void GetEvent(TWsEvent &aEvent);
	IMPORT_C void PurgePointerEvents();
//
	IMPORT_C void RedrawReady(TRequestStatus *aStat);
	IMPORT_C void RedrawReadyCancel();
	IMPORT_C void GetRedraw(TWsRedrawEvent &aEvent);
//
	IMPORT_C void PriorityKeyReady(TRequestStatus *aStat);
	IMPORT_C void PriorityKeyReadyCancel();
	IMPORT_C void GetPriorityKey(TWsPriorityKeyEvent &aEvent);
//
	IMPORT_C void Flush();
	IMPORT_C TBool SetAutoFlush(TBool aState);
	IMPORT_C void SetKeyboardRepeatRate(const TTimeIntervalMicroSeconds32 &aInitialTime, const TTimeIntervalMicroSeconds32 &aTime);
	IMPORT_C void GetKeyboardRepeatRate(TTimeIntervalMicroSeconds32 &aInitialTime, TTimeIntervalMicroSeconds32 &aTime);
	IMPORT_C void GetDoubleClickSettings(TTimeIntervalMicroSeconds32 &aInterval, TInt &aDistance);
	IMPORT_C void SetDoubleClick(const TTimeIntervalMicroSeconds32 &aInterval, TInt aDistance);
//
	IMPORT_C TInt NumWindowGroups() const;
	IMPORT_C TInt WindowGroupList(CArrayFixFlat<TInt> *aWindowList);
	IMPORT_C TInt NumWindowGroups(TInt aPriority) const;
	IMPORT_C TInt WindowGroupList(TInt aPriority, CArrayFixFlat<TInt> *aWindowList);
	IMPORT_C TInt GetFocusWindowGroup();
	IMPORT_C TInt GetDefaultOwningWindow();
	IMPORT_C TInt SetWindowGroupOrdinalPosition(TInt aIdentifier, TInt aPosition);
	IMPORT_C TInt GetWindowGroupClientThreadId(TInt aIdentifier, TThreadId &aThreadId);
	IMPORT_C TInt GetWindowGroupHandle(TInt aIdentifier);
	IMPORT_C TInt GetWindowGroupOrdinalPriority(TInt aIdentifier);
	IMPORT_C TInt SendEventToWindowGroup(TInt aIdentifier, const TWsEvent &aEvent);
	IMPORT_C TInt SendEventToAllWindowGroups(const TWsEvent &aEvent);
	IMPORT_C TInt SendEventToAllWindowGroups(TInt aPriority, const TWsEvent &aEvent);
	IMPORT_C TInt GetWindowGroupNameFromIdentifier(TInt aIdentifier, TDes &aWindowName);
	IMPORT_C TInt FindWindowGroupIdentifier(TInt aPreviousIdentifier,const TDesC& aMatch,TInt aOffset=0);
	IMPORT_C TInt FindWindowGroupIdentifier(TInt aPreviousIdentifier,TThreadId aThreadId);
	IMPORT_C TInt SendMessageToWindowGroup(TInt aIdentifier, TUid aUid, const TDesC8 &aParams);
	IMPORT_C TInt SendMessageToAllWindowGroups(TUid aUid, const TDesC8& aParams);
	IMPORT_C TInt SendMessageToAllWindowGroups(TInt aPriority, TUid aUid, const TDesC8& aParams);
	IMPORT_C TInt FetchMessage(TUid &aUid, TPtr8 &aParams, const TWsEvent& aMessageEvent);
//
	IMPORT_C void SetShadowVector(const TPoint &aVector);
	IMPORT_C TPoint ShadowVector() const;
//
	IMPORT_C void SetBackgroundColor(TRgb aColor);
	IMPORT_C TRgb GetBackgroundColor() const;
//
	IMPORT_C TInt SetSystemPointerCursor(const RWsPointerCursor &aPointerCursor,TInt aCursorNumber);
	IMPORT_C void ClearSystemPointerCursor(TInt aCursorNumber);
	IMPORT_C TInt ClaimSystemPointerCursorList();
	IMPORT_C void FreeSystemPointerCursorList();
//
	IMPORT_C TInt ResourceCount();
	IMPORT_C void PasswordEntered();
	IMPORT_C void ComputeMode(TComputeMode aMode);
//
	IMPORT_C TInt HeapCount() const;
	IMPORT_C void MarkStart();
	IMPORT_C void CheckNum(TUint aCount);
	IMPORT_C void MarkEnd(TUint aCount);
	IMPORT_C void HeapSetFail(RHeap::TAllocFail aType,TInt aValue);
	IMPORT_C void SetModifierState(TEventModifier aModifier,TModifierState aState);
	IMPORT_C TInt GetModifierState() const;
//
	IMPORT_C TInt RequestOffEvents(TBool aOn,RWindowTreeNode *aWin=NULL);
	IMPORT_C TDisplayMode GetDefModeMaxNumColors(TInt& aColor,TInt& aGray) const;
	IMPORT_C TInt GetColorModeList(CArrayFixFlat<TInt> *aModeList) const;
//
	IMPORT_C void SetPointerCursorArea(const TRect& aArea);
	IMPORT_C void SetPointerCursorArea(TInt aScreenSizeMode,const TRect& aArea);
	IMPORT_C TRect PointerCursorArea() const;
	IMPORT_C TRect PointerCursorArea(TInt aScreenSizeMode) const;
	IMPORT_C void SetPointerCursorMode(TPointerCursorMode aMode);
	IMPORT_C TPointerCursorMode PointerCursorMode() const;
	IMPORT_C void SetDefaultSystemPointerCursor(TInt aCursorNumber);
	IMPORT_C void ClearDefaultSystemPointerCursor();
	IMPORT_C void SetPointerCursorPosition(const TPoint& aPosition);
	IMPORT_C TPoint PointerCursorPosition() const;

	IMPORT_C void SetDefaultFadingParameters(TUint8 aBlackMap,TUint8 aWhiteMap);
	IMPORT_C void PrepareForSwitchOff();		//For SYMBIAN use only!!

	// New for Series 60
	IMPORT_C void SetBufferSizeL(TInt aBufSize);
	IMPORT_C void SetSystemFaded(TBool aFaded);
	IMPORT_C void SetSystemFaded(TBool aFaded,TUint8 aBlackMap,TUint8 aWhiteMap);

#if defined(__WINS__)
// Function for WINS behaviour only
//
	IMPORT_C void SetRemoveKeyCode(TBool aRemove);
	IMPORT_C void SimulateXyInputType(TXYInputType aInputType);		//Only for testing WSERV
#endif
// Raw event simulation is designed purely for Wserv testing at the moment
// Althoug it is possible it may in future be used by applications
//
	IMPORT_C void SimulateRawEvent(TRawEvent aEvent);
	IMPORT_C void SimulateKeyEvent(TKeyEvent aEvent);
	IMPORT_C void LogMessage(const TLogMessageText &aMessage);
//
// Functions for test code use only
//
	IMPORT_C void SystemInfo(TInt &aSystemInfoNumber, SSystemInfo &aSystemInfo);
	IMPORT_C void TestWrite(TInt aHandle,TInt aOpcode,const TAny *aData, TInt aLength);
	IMPORT_C void TestWriteReply(TInt aHandle,TInt aOpcode,const TAny *aData, TInt aLength);
	IMPORT_C void TestWriteReplyP(TInt aHandle,TInt aOpcode,const TAny *aData,TInt aLength,TDes8 *aReplyPackage);
private:
	TInt doWindowGroupList(TInt aPriority, CArrayFixFlat<TInt> *aWindowList, TInt aNumOpcode, TInt aListOpcode);
	TInt doSetHotKey(TInt aOpcode, TInt aType, TUint aKeycode, TUint aModifierMask, TUint aModifiers);
	void doReadEvent(TRequestStatus *aStat, TInt aOpcode);
private:
	void connectL();
	TInt DoFlush(const TPtr8 *aBuf, TAny *aPackage);
	void DirectAcessActivation(TBool aIsNowActive);
	};

typedef TInt (*AnimCommand)(TPtr8 *aBufPtr,TAny *aPackage);

class RWindowTreeNode : public MWsClientClass
	{
	friend class RWindowGroup;
	friend class RWindowBase;
	friend class CWindowGc;
	friend class RAnimDll;
	friend class RWsSprite;
public:
	enum TFadeControl
		{
		EFadeIncludeChildren=ETrue,
		EFadeWindowOnly=EFalse,
		};
protected:
	RWindowTreeNode();
	RWindowTreeNode(RWsSession &aWs);
public:
	IMPORT_C void Close();
	IMPORT_C void Destroy();
	IMPORT_C TUint32 Parent() const;
	IMPORT_C TUint32 PrevSibling() const;
	IMPORT_C TUint32 NextSibling() const;
	IMPORT_C TUint32 Child() const;
	IMPORT_C TInt OrdinalPriority() const;
	IMPORT_C TInt OrdinalPosition() const;
	IMPORT_C TInt FullOrdinalPosition() const;
	IMPORT_C void SetOrdinalPosition(TInt aPos);
	IMPORT_C void SetOrdinalPosition(TInt aPos,TInt aOrdinalPriority);
	IMPORT_C TInt SetPointerCursor(TInt aCursorNumber);
	IMPORT_C void SetCustomPointerCursor(const RWsPointerCursor &aPointerCursor);
	IMPORT_C TInt EnableOnEvents(TEventControl aCircumstances=EEventControlOnlyWithKeyboardFocus);
	IMPORT_C void DisableOnEvents();
	IMPORT_C TInt EnableGroupChangeEvents();
	IMPORT_C void DisableGroupChangeEvents();
	IMPORT_C TInt EnableFocusChangeEvents();
	IMPORT_C void DisableFocusChangeEvents();
	IMPORT_C TInt EnableGroupListChangeEvents();
	IMPORT_C void DisableGroupListChangeEvents();
	IMPORT_C TInt EnableErrorMessages(TEventControl aCircumstances);
	IMPORT_C void DisableErrorMessages();
	IMPORT_C TInt EnableModifierChangedEvents(TUint aModifierMask, TEventControl aCircumstances);
	IMPORT_C void DisableModifierChangedEvents();
	IMPORT_C void SetNonFading(TBool aNonFading);
	IMPORT_C void SetFaded(TBool aFaded,TFadeControl aIncludeChildren);
	IMPORT_C void SetFaded(TBool aFaded,TFadeControl aIncludeChildren,TUint8 aBlackMap,TUint8 aWhiteMap);
	IMPORT_C void ClearPointerCursor();
protected:
	__DECLARE_TEST;
	};

class RWindowBase : public RWindowTreeNode
	{
public:
	enum TCaptureFlags
		{
// Flags, these can be combined to customise pointer capture
		TCaptureFlagEnabled=0x01,
		TCaptureFlagDragDrop=0x02,
		TCaptureFlagAllGroups=0x04,
// States, made up of a set of flags
		TCaptureDisabled=0,
		TCaptureEnabled=TCaptureFlagEnabled,
		TCaptureDragDrop=TCaptureFlagEnabled|TCaptureFlagDragDrop|TCaptureFlagAllGroups,
		};
protected:
	RWindowBase();
	RWindowBase(RWsSession &aWs);
public:
	IMPORT_C void Activate();
	IMPORT_C void SetPosition(const TPoint &point);
	IMPORT_C TInt SetSizeErr(const TSize &size);
	IMPORT_C TInt SetExtentErr(const TPoint &point,const TSize &size);
	IMPORT_C TSize Size() const;
	IMPORT_C TPoint InquireOffset(const RWindowTreeNode &aWindow) const;
	IMPORT_C void PointerFilter(TUint32 aFilterMask, TUint32 aFilter);
	IMPORT_C void SetPointerGrab(TBool aState);
	IMPORT_C void ClaimPointerGrab(TBool aSendUpEvent=ETrue);
	IMPORT_C void SetPointerCapture(TInt aFlags);
	IMPORT_C void SetVisible(TBool aState);
	IMPORT_C void SetShadowHeight(TInt aHeight);
	IMPORT_C void SetShadowDisabled(TBool aState);
	IMPORT_C TPoint Position() const;
	IMPORT_C TInt SetCornerType(TCornerType aCornerType, TInt aCornerFlags=0);
	IMPORT_C TInt SetShape(const TRegion &aRegion);
	IMPORT_C TInt SetRequiredDisplayMode(TDisplayMode aMode);
	IMPORT_C TDisplayMode DisplayMode();
	IMPORT_C void EnableBackup(TUint aBackupType=EWindowBackupAreaBehind);
	IMPORT_C void RequestPointerRepeatEvent(TTimeIntervalMicroSeconds32 aTime,const TRect &aRect);
	IMPORT_C void CancelPointerRepeatEventRequest();
	IMPORT_C TInt AllocPointerMoveBuffer(TInt aMaxPoints, TUint aFlags);
	IMPORT_C void FreePointerMoveBuffer();
	IMPORT_C void EnablePointerMoveBuffer();
	IMPORT_C void DisablePointerMoveBuffer();
	IMPORT_C TInt RetrievePointerMoveBuffer(TDes8 &aBuf);
	IMPORT_C void DiscardPointerMoveBuffer();
	IMPORT_C TInt AddKeyRect(const TRect &aRect, TInt aScanCode, TBool aActivatedByPointerSwitchOn);
	IMPORT_C void RemoveAllKeyRects();
	IMPORT_C TInt PasswordWindow(TPasswordMode aPasswordMode);
	IMPORT_C void FadeBehind(TBool aFade);
	IMPORT_C TBool IsFaded();
	IMPORT_C TBool IsNonFading();
	IMPORT_C TInt MoveToGroup(TInt aIdentifier);
protected:
	TInt construct(const RWindowTreeNode &parent,TUint32 aHandle, TInt aType, TDisplayMode aDisplayMode);
	};

class RBlankWindow : public RWindowBase
	{
public:
	IMPORT_C RBlankWindow();
	IMPORT_C RBlankWindow(RWsSession &aWs);
	IMPORT_C TInt Construct(const RWindowTreeNode &parent, TUint32 aHandle);
	IMPORT_C void SetColor(TRgb aColor);
	IMPORT_C void SetSize(const TSize &size);
	IMPORT_C void SetExtent(const TPoint &point,const TSize &size);
	};

class RDrawableWindow : public RWindowBase
	{
protected:
	RDrawableWindow();
	RDrawableWindow(RWsSession &aWs);
public:
	IMPORT_C void Scroll(const TPoint &aOffset);
	IMPORT_C void Scroll(const TRect &aClipRect, const TPoint &aOffset);
	IMPORT_C void Scroll(const TPoint &aOffset, const TRect &aRect);
	IMPORT_C void Scroll(const TRect &aClipRect, const TPoint &aOffset, const TRect &aRect);
private:
	void doScroll(const TRect &aClipRect, const TPoint &aOffset, const TRect &aRect, TInt aOpcode);
	};

class RWindow : public RDrawableWindow
	{
public:
	IMPORT_C RWindow();
	IMPORT_C RWindow(RWsSession &aWs);
	IMPORT_C TInt Construct(const RWindowTreeNode &parent,TUint32 aHandle);
	IMPORT_C void BeginRedraw();
	IMPORT_C void BeginRedraw(const TRect &aRect);
	IMPORT_C void EndRedraw();
	IMPORT_C void Invalidate();
	IMPORT_C void Invalidate(const TRect &aRect);
	IMPORT_C void GetInvalidRegion(RRegion &aRegion);
	IMPORT_C void SetBackgroundColor(TRgb aColor);
	IMPORT_C void SetBackgroundColor();
	IMPORT_C void SetSize(const TSize &size);
	IMPORT_C void SetExtent(const TPoint &point,const TSize &size);
	};

class RBackedUpWindow : public RDrawableWindow
	{
public:
	IMPORT_C RBackedUpWindow();
	IMPORT_C RBackedUpWindow(RWsSession &aWs);
	IMPORT_C TInt Construct(const RWindowTreeNode &parent,TDisplayMode aDisplayMode, TUint32 aHandle);
	IMPORT_C TInt BitmapHandle();
	IMPORT_C void UpdateScreen();
	IMPORT_C void UpdateScreen(const TRegion &aRegion);
	IMPORT_C void UpdateBackupBitmap();
	IMPORT_C void MaintainBackup();
	};

class RWindowGroup : public RWindowTreeNode
	{
public:
	IMPORT_C RWindowGroup();
	IMPORT_C RWindowGroup(RWsSession &aWs);
	IMPORT_C TInt Construct(TUint32 aClientHandle);
	IMPORT_C TInt Construct(TUint32 aClientHandle, TBool aInitialFocusState);
	IMPORT_C void EnableReceiptOfFocus(TBool aState);
	IMPORT_C void AutoForeground(TBool aState);
	IMPORT_C void SetOrdinalPriorityAdjust(TInt aAdjust);
	IMPORT_C TInt32 CaptureKey(TUint aKeycode, TUint aModifierMask, TUint aModifier);
	IMPORT_C void CancelCaptureKey(TInt32 aCaptureKey);
	IMPORT_C TInt32 CaptureKeyUpAndDowns(TUint aScanCode, TUint aModifierMask, TUint aModifier);
	IMPORT_C void CancelCaptureKeyUpAndDowns(TInt32 aCaptureKey);
	IMPORT_C TInt AddPriorityKey(TUint aKeycode, TUint aModifierMask, TUint aModifier);
	IMPORT_C void RemovePriorityKey(TUint aKeycode, TUint aModifierMask, TUint aModifier);
	IMPORT_C void SetTextCursor(RWindowBase &aWin, const TPoint &aPos, const TTextCursor &aCursor);
	IMPORT_C void SetTextCursor(RWindowBase &aWin, const TPoint &aPos, const TTextCursor &aCursor, const TRect &aClipRect);
	IMPORT_C void CancelTextCursor();
	IMPORT_C void SetOwningWindowGroup(TInt aIdentifier);
	IMPORT_C void DefaultOwningWindow();
	IMPORT_C TInt SetName(const TDesC &aName);
	IMPORT_C TInt Name(TDes &aWindowName) const;
	IMPORT_C TInt Identifier() const;
	IMPORT_C void DisableKeyClick(TBool aState);		//Deptecated, does not currently do anything
	IMPORT_C TInt EnableScreenChangeEvents();
	IMPORT_C void DisableScreenChangeEvents();
	IMPORT_C void SimulatePointerEvent(TRawEvent aEvent);
private:
	TInt32 doCaptureKey(TUint aKey, TUint aModifierMask, TUint aModifiers, TInt aOpcode);
	void doCancelCaptureKey(TInt32 aCaptureKeyHandle, TInt aOpcode);
	};

class CWsBitmap : public CFbsBitmap, public MWsClientClass
	{
public:
	IMPORT_C CWsBitmap();
	IMPORT_C CWsBitmap(RWsSession &aWs);
	IMPORT_C ~CWsBitmap();
	IMPORT_C TInt Create(const TSize& aSizeInPixels,TDisplayMode aDispMode);
	IMPORT_C TInt Duplicate(TInt aHandle);
	IMPORT_C TInt Load(const TDesC& aFileName,TInt32 aId,TBool aShareIfLoaded=ETrue);
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void Reset();
private:
	TInt createWsBitmap(TInt aErr);
	};

class CWindowGc : public CBitmapContext, public MWsClientClass
	{
	friend class CWsScreenDevice;
public:
	IMPORT_C CWindowGc(CWsScreenDevice *aDevice);
	IMPORT_C virtual ~CWindowGc();
	IMPORT_C virtual TInt Construct();
	IMPORT_C virtual void Activate(RDrawableWindow &aWindow);
	IMPORT_C virtual void Deactivate();
//====================FROM CGraphicsContext.H===============================
	IMPORT_C virtual CGraphicsDevice* Device() const;
	IMPORT_C virtual void SetOrigin(const TPoint &aPos=TPoint(0,0));
	IMPORT_C virtual void SetDrawMode(TDrawMode aDrawingMode);
	IMPORT_C virtual void SetClippingRect(const TRect& aRect);
	IMPORT_C virtual void CancelClippingRect();
	IMPORT_C virtual void Reset();

	IMPORT_C virtual void UseFont(const CFont *aFont);
	IMPORT_C virtual void DiscardFont();
	IMPORT_C virtual void SetUnderlineStyle(TFontUnderline aUnderlineStyle);
	IMPORT_C virtual void SetStrikethroughStyle(TFontStrikethrough aStrikethroughStyle);
// Used to do justified text properly
	IMPORT_C virtual void SetWordJustification(TInt aExcessWidth,TInt aNumGaps);
// Used primarily to get accurate WYSIWYG
	IMPORT_C virtual void SetCharJustification(TInt aExcessWidth,TInt aNumChars);

	IMPORT_C virtual void SetPenColor(const TRgb &aColor);
	IMPORT_C virtual void SetPenStyle(TPenStyle aPenStyle);
	IMPORT_C virtual void SetPenSize(const TSize& aSize);

	IMPORT_C virtual void SetBrushColor(const TRgb &aColor);
	IMPORT_C virtual void SetBrushStyle(TBrushStyle aBrushStyle);
	IMPORT_C virtual void SetBrushOrigin(const TPoint &aOrigin);
	IMPORT_C virtual void UseBrushPattern(const CFbsBitmap *aBitmap);
	IMPORT_C virtual void DiscardBrushPattern();
//
// Move the internal position, as used by DrawLineTo & DrawLineBy, and set by MoveTo,
// MoveBy, DrawLine, DrawLineTo, DrawLineBy and DrawPolyline
	IMPORT_C virtual void MoveTo(const TPoint &aPoint);
	IMPORT_C virtual void MoveBy(const TPoint &aVector);
	IMPORT_C virtual void Plot(const TPoint &aPoint);
//
//  Line drawing subject to pen color, width and style and draw mode
	IMPORT_C virtual void DrawArc(const TRect &aRect,const TPoint &aStart,const TPoint &aEnd);
	IMPORT_C virtual void DrawLine(const TPoint &aPoint1,const TPoint &aPoint2);
	IMPORT_C virtual void DrawLineTo(const TPoint &aPoint);
	IMPORT_C virtual void DrawLineBy(const TPoint &aVector);
	IMPORT_C virtual void DrawPolyLine(const CArrayFix<TPoint> *aPointList);
	IMPORT_C virtual void DrawPolyLine(const TPoint* aPointList,TInt aNumPoints);
//
// Filled outlines
// Outlines subject to pen color, width and style and draw mode
// (set pen to ENullPen for no outline)
// Fill subject to brush style (color, hash or pattern) and origin and
// drawing mode (set brush to ENullBrush for no fill)
	IMPORT_C virtual void DrawPie(const TRect &aRect,const TPoint &aStart,const TPoint &aEnd);
	IMPORT_C virtual void DrawEllipse(const TRect &aRect);
	IMPORT_C virtual void DrawRect(const TRect &aRect);
	IMPORT_C virtual void DrawRoundRect(const TRect &aRect,const TSize &aEllipse);
	IMPORT_C virtual TInt DrawPolygon(const CArrayFix<TPoint> *aPointList,TFillRule aFillRule=EAlternate);
	IMPORT_C virtual TInt DrawPolygon(const TPoint* aPointList,TInt aNumPoints,TFillRule aFillRule=EAlternate);
//
// Uses the bitmap's Twips size and does a "stretch" blit in general
	IMPORT_C virtual void DrawBitmap(const TPoint &aTopLeft, const CFbsBitmap *aSource);
	IMPORT_C virtual void DrawBitmap(const TRect &aDestRect, const CFbsBitmap *aSource);
	IMPORT_C virtual void DrawBitmap(const TRect &aDestRect, const CFbsBitmap *aSource, const TRect &aSourceRect);
//
// Text drawing subject to drawing mode
// Subject to used font, pen color, drawing mode, 
// word and char justification
	IMPORT_C virtual void DrawText(const TDesC &aString,const TPoint &aPosition);
//
// Subject to same as above plus brush for background
// (set brush to ENullBrush for no effect on background)
	IMPORT_C virtual void DrawText(const TDesC &aString,const TRect &aBox,TInt aBaselineOffset,TTextAlign aHoriz=ELeft,TInt aLeftMrg=0);
//================Extra functions from CBitmapContext==============
	IMPORT_C virtual void Clear();
	IMPORT_C virtual void Clear(const TRect &aRect);
	IMPORT_C virtual void CopyRect(const TPoint &aOffset,const TRect &aRect);
	IMPORT_C virtual void BitBlt(const TPoint &aPos, const CFbsBitmap *aDevice);
	IMPORT_C virtual void BitBlt(const TPoint &aPos, const CFbsBitmap *aDevice, const TRect &aRect);
	IMPORT_C virtual void BitBltMasked(const TPoint& aPoint,const CFbsBitmap* aBitmap,const TRect& aSourceRect,const CFbsBitmap* aMaskBitmap,TBool aInvertMask);
	IMPORT_C virtual void BitBlt(const TPoint &aPos, const CWsBitmap *aDevice);
	IMPORT_C virtual void BitBlt(const TPoint &aPos, const CWsBitmap *aDevice, const TRect &aRect);
	IMPORT_C virtual void BitBltMasked(const TPoint& aPoint,const CWsBitmap *aBitmap,const TRect& aSourceRect,const CWsBitmap *aMaskBitmap,TBool aInvertMask);
	IMPORT_C virtual void MapColors(const TRect& aRect,const TRgb* aColors,TInt aNumPairs=2,TBool aMapForwards=ETrue);

	IMPORT_C virtual void DrawTextVertical(const TDesC& aText,const TPoint& aPosition,TBool aUp);
	IMPORT_C virtual void DrawTextVertical(const TDesC& aText,const TRect& aBox,TInt aBaselineOffset,TBool aUp,TTextAlign aVert=ELeft,TInt aMargin=0);
//=================Extra functions specific to wserv GDI==============
	IMPORT_C virtual void SetDitherOrigin(const TPoint& aPoint);
	IMPORT_C virtual TInt SetClippingRegion(const TRegion &aClippingRegion);
	IMPORT_C virtual void CancelClippingRegion();
//=================Functions also supplied by CFbsBitGc==============
	IMPORT_C void SetFaded(TBool aFaded);
	IMPORT_C void SetFadingParameters(TUint8 aBlackMap,TUint8 aWhiteMap);
////=============================================================
private: // Private code
	TRgb Color(TInt aOpcode)const;
	void SetJustification(TInt aExcessWidth,TInt aNumGaps, TInt aOpcode);
	void DrawArcOrPie(const TRect &aRect,const TPoint &aStart,const TPoint &aEnd, TInt aOpcode);
	void doDrawPolyLine(const CArrayFix<TPoint> *aPointArray, const TPoint* aPointList,TInt aNumPoints);
	TInt doDrawPolygon(const CArrayFix<TPoint> *aPointArray,const TPoint* aPointList,TInt aNumPoints,TFillRule aFillRule);
	void WriteTextPos(TInt aOpcode,TInt aOpcodePtr,const TPoint &aPos,const TDesC &aBuf) const;
	void WriteTextCommand(TAny *aCmd, TInt aLen,const TDesC &aBuf,TInt aOpcode,TInt aOpcodePtr) const;
private: // Private data
	CFbsFont *iFont;
	CWsScreenDevice *iDevice;
	};

class CWsScreenDevice : public CBitmapDevice, public MWsClientClass
	{
public:
	IMPORT_C CWsScreenDevice();
	IMPORT_C CWsScreenDevice(RWsSession &aWs);
	IMPORT_C ~CWsScreenDevice();
	IMPORT_C TInt Construct();
//==== From CGraphicsDevice ====//
	IMPORT_C TDisplayMode DisplayMode() const;
	IMPORT_C TSize SizeInPixels() const;
	IMPORT_C TSize SizeInTwips() const;
	IMPORT_C TInt HorizontalTwipsToPixels(TInt aTwips) const;
	IMPORT_C TInt VerticalTwipsToPixels(TInt aTwips) const;
	IMPORT_C TInt HorizontalPixelsToTwips(TInt aPixels) const;
	IMPORT_C TInt VerticalPixelsToTwips(TInt aPixels) const;
	IMPORT_C TRect PointerRect() const;
	IMPORT_C TInt CreateContext(CGraphicsContext *&aGc);
    inline TInt CreateContext(CWindowGc *&aGc);
	IMPORT_C TInt GetNearestFontInTwips(CFont*& aFont,const TFontSpec& aFontSpec);
	IMPORT_C TInt NumTypefaces() const;
	IMPORT_C void TypefaceSupport(TTypefaceSupport& aTypefaceSupport,TInt aTypefaceIndex) const;
	IMPORT_C TInt FontHeightInTwips(TInt aTypefaceIndex,TInt aHeightIndex) const;
// ==== From CBitmapDevice ====//
    IMPORT_C void GetPixel(TRgb &aColor,const TPoint &aPixel) const;
    IMPORT_C void GetScanLine(TDes8 &aBuf,const TPoint &aPixel,TInt aLength, TDisplayMode aDispMode) const;
	IMPORT_C TInt AddFile(const TDesC& aName,TInt& aId);
	IMPORT_C void RemoveFile(TInt aId=0);
	IMPORT_C TInt GetNearestFontInPixels(CFont*& aFont,const TFontSpec& aFontSpec);
	IMPORT_C TInt FontHeightInPixels(TInt aTypefaceIndex,TInt aHeightIndex) const;
	IMPORT_C void ReleaseFont(CFont* aFont);
//===== From CFbsScreenDevice ====//
	IMPORT_C void PaletteAttributes(TBool& aModifiable,TInt& aNumEntries) const;
	IMPORT_C void SetPalette(CPalette* aPalette);
	IMPORT_C TInt GetPalette(CPalette*& aPalette) const;
//===== Extra functions ====//
	IMPORT_C TInt SetCustomPalette(const CPalette* aPalette);
 	IMPORT_C TInt GetFontById(CFont *&aFont,TUid aUid,const TAlgStyle& aAlgStyle);
	IMPORT_C TBool RectCompare(const TRect &aRect1,const TRect &aRect2);
	IMPORT_C TInt CopyScreenToBitmap(const CFbsBitmap *aBitmap) const;
	IMPORT_C TInt CopyScreenToBitmap(const CFbsBitmap *aBitmap, const TRect &aRect) const;
//===== Screen Rotation functions ====//
	IMPORT_C void SetScreenSizeAndRotation(const TPixelsTwipsAndRotation &aSizeAndRotation);
	IMPORT_C void GetDefaultScreenSizeAndRotation(TPixelsTwipsAndRotation &aSizeAndRotation) const;
	IMPORT_C void SetScreenSizeAndRotation(const TPixelsAndRotation &aSizeAndRotation);
	IMPORT_C void GetDefaultScreenSizeAndRotation(TPixelsAndRotation &aSizeAndRotation) const;
	IMPORT_C TScreenModeEnforcement ScreenModeEnforcement() const;
	IMPORT_C void SetScreenModeEnforcement(TScreenModeEnforcement aMode) const;
	IMPORT_C void GetScreenModeSizeAndRotation(TInt aMode, TPixelsTwipsAndRotation &aSizeAndRotation) const;
	IMPORT_C void GetScreenModeSizeAndRotation(TInt aMode, TPixelsAndRotation &aSizeAndRotation) const;
	IMPORT_C void SetCurrentRotations(TInt aMode, CFbsBitGc::TGraphicsOrientation aRotation) const;
	IMPORT_C TInt GetRotationsList(TInt aMode, CArrayFixFlat<TInt> *aRotationList) const;
	IMPORT_C TInt NumScreenModes() const;
	IMPORT_C void SetScreenMode(TInt aMode);		//This function does not have much use outside of testing purposes	
private: // Private data
	CFbsTypefaceStore* iTypefaceStore;
	TSize iPhysicalScreenSizeInTwips;
	TSize iDisplaySizeInPixels;
	friend class CWindowGc;
	};

class RWsSpriteBase : public MWsClientClass
//
// Client side class base class for sprites and pointer cursors
//
	{
protected:
	IMPORT_C RWsSpriteBase();
	IMPORT_C RWsSpriteBase(RWsSession &aWs);
public:
	IMPORT_C TInt Activate();
	IMPORT_C TInt AppendMember(const TSpriteMember &aSpriteList);
	IMPORT_C void UpdateMember(TInt aIndex);
	IMPORT_C TInt UpdateMember(TInt aIndex, const TSpriteMember &aMemberData);
	IMPORT_C void Close();
	};

class RWsSprite : public RWsSpriteBase
//
// Client side class for sprites
//
	{
public:
	IMPORT_C RWsSprite();
	IMPORT_C RWsSprite(RWsSession &aWs);
	IMPORT_C TInt Construct(RWindowTreeNode &aWindow, const TPoint &aPos, TInt aFlags);
	IMPORT_C void SetPosition(const TPoint &aPos);
	};

class RWsPointerCursor : public RWsSpriteBase
//
// Client side class for pointer cursor
//
	{
	friend class RWindowTreeNode;
	friend class RWsSession;
public:
	IMPORT_C RWsPointerCursor();
	IMPORT_C RWsPointerCursor(RWsSession &aWs);
	IMPORT_C TInt Construct(TInt aFlags);
	};

class RAnim;
class RAnimDll : public MWsClientClass
//
// Client side class for DLL Animators
//
	{
public:
	IMPORT_C RAnimDll();
	IMPORT_C virtual ~RAnimDll();
	IMPORT_C RAnimDll(RWsSession &aWs);
	IMPORT_C TInt Load(const TDesC &aFileName);
	IMPORT_C void Destroy();
	IMPORT_C virtual void Close();
private:
	TInt CommandReply(TInt aHandle, TInt aOpcode, const TPtrC8 &aArgs);
	TInt CommandReply(TInt aHandle, TInt aOpcode);
	void Command(TInt aHandle, TInt aOpcode, const TPtrC8 &aArgs);
	void Command(TInt aHandle, TInt aOpcode);
	TInt CreateInstance(const MWsClientClass &aDevice, TInt aType, const TPtrC8 &aArgs, TBool aIsWindow);
	void DestroyInstance(TInt aHandle);
private:
	friend class RAnim;
	};

class RAnim
//
// Client side class for each instance of an animated object
//
	{
public:
	IMPORT_C virtual ~RAnim();
	IMPORT_C virtual void Close();
	IMPORT_C void Destroy();
protected:
	IMPORT_C RAnim();
	IMPORT_C RAnim(RAnimDll &aAnimDll);
	IMPORT_C TInt Construct(const RWindowBase &aDevice, TInt aType, const TDesC8 &aParams);
	IMPORT_C TInt Construct(const RWsSprite &aDevice, TInt aType, const TDesC8 &aParams);
	IMPORT_C TInt CommandReply(TInt aOpcode, const TPtrC8 &aArgs);
	IMPORT_C TInt CommandReply(TInt aOpcode);
	IMPORT_C void Command(TInt aOpcode, const TPtrC8 &aArgs);
	IMPORT_C void Command(TInt aOpcode);
private:
	TInt32 iHandle;
	RAnimDll *iAnimDll;
	};

class RDirectScreenAccess : public MWsClientClass
	{
public:
	enum TTerminationReasons
		{
		ETerminateCancel,
		ETerminateRegion,
		ETerminateScreenMode,
		ETerminateRotation,
		};
	enum TPriority
		{
		EPriorityVeryHigh=100,
		};
public:
	IMPORT_C RDirectScreenAccess();
	IMPORT_C RDirectScreenAccess(RWsSession &aWs);
	IMPORT_C TInt Construct();
	IMPORT_C TInt Request(RRegion*& aRegion,TRequestStatus& aStatus,RWindowBase& aWindow); 
	IMPORT_C void Completed();
	IMPORT_C void Cancel();
	IMPORT_C void Close();
private:
	RWsSession* iWs;
	RThread iWsThread;
	TRequestStatus* iAborted;
	TRequestStatus* iAbortedBackup;
	};

class MAbortDirectScreenAccess
	{
public:
	virtual void AbortNow(RDirectScreenAccess::TTerminationReasons aReason)=0;
	};

class MDirectScreenAccess : public MAbortDirectScreenAccess
	{
public:
	virtual void Restart(RDirectScreenAccess::TTerminationReasons aReason)=0;
	};

class CDirectScreenAccess : public CActive
	{
public:
	IMPORT_C static CDirectScreenAccess* NewL(RWsSession& aWs,CWsScreenDevice& aScreenDevice,RWindowBase& aWindow,MDirectScreenAccess& aAbort);
	~CDirectScreenAccess();
	IMPORT_C void StartL();
	inline CFbsBitGc* Gc();
	inline CFbsScreenDevice*& ScreenDevice();
	inline RRegion* DrawingRegion();
private:
	enum TFlags
		{
		EDirectCheckModeChange=0x1,
		EDirectCheckSizeModeChange=0x2,
		};
private:
	inline CDirectScreenAccess(RWsSession& aWs,CWsScreenDevice* aScreenDevice,RWindowBase& aWindow,MDirectScreenAccess& aAbort);
	void ConstructL(RWsSession& aWs);
	void CreateScreenObjectsL(TDisplayMode aCurrentMode);
	void UpdateSizeAndRotation(CFbsBitGc* aGc);
	static TInt Restart(TAny* aDirect);
	void Restart();
	//Pure virtual functions from CActive
	void DoCancel();
	void RunL();
private:
	CFbsBitGc* iGc;
	CFbsScreenDevice* iScreenDevice;
	RRegion* iDrawingRegion;
	RWindowBase& iWindow;
	CWsScreenDevice* iWsScreenDevice;
	MDirectScreenAccess& iAbort;
	RDirectScreenAccess iDirectAccess;
	RDirectScreenAccess::TTerminationReasons iReason;
	CIdle* iRestart;
	TSize iScreenSize;
	TBool iAborting;
	TUint iFlags;
	};

inline TInt MWsClientClass::WsHandle() const
	{return(iWsHandle);}

inline TInt CWsScreenDevice::CreateContext(CWindowGc *&aGc)
	{return(CreateContext((CGraphicsContext *&)aGc));}
//
inline TUint TWsRedrawEvent::Handle() const
	{return(iHandle);}
inline TRect TWsRedrawEvent::Rect() const
	{return(iRect);}
//
inline TPointerEvent *TWsEvent::Pointer() const
	{return((TPointerEvent *)&iEventData);}
inline TKeyEvent *TWsEvent::Key() const
	{return((TKeyEvent *)&iEventData);}
inline TModifiersChangedEvent *TWsEvent::ModifiersChanged() const
	{return((TModifiersChangedEvent *)&iEventData);}
inline TWsErrorMessage *TWsEvent::ErrorMessage() const
	{return((TWsErrorMessage *)&iEventData);}
inline TUint8 *TWsEvent::EventData() const
	{return((TUint8 *)&iEventData);}
inline TInt TWsEvent::Type() const
	{return(iType);}
inline TUint TWsEvent::Handle() const
	{return(iHandle);}
inline TTime TWsEvent::Time() const
	{return(iTime);}
inline void TWsEvent::SetType(TInt aType)
	{iType=aType;}
inline void TWsEvent::SetHandle(TUint aHandle)
	{iHandle=aHandle;}
inline void TWsEvent::SetTimeNow()
	{iTime.HomeTime();}

inline TUint TWsPriorityKeyEvent::Handle() const
	{return(iHandle);}
inline TKeyEvent *TWsPriorityKeyEvent::Key() const
	{return((TKeyEvent *)&iEventData);}
inline void TWsPriorityKeyEvent::SetHandle(TUint aHandle)
	{iHandle=aHandle;}
inline CDirectScreenAccess::CDirectScreenAccess(RWsSession& aWs,CWsScreenDevice* aScreenDevice,RWindowBase& aWindow
																											,MDirectScreenAccess& aAbort)
		:CActive(RDirectScreenAccess::EPriorityVeryHigh), iWindow(aWindow), iAbort(aAbort), iDirectAccess(aWs)
		{iWsScreenDevice=aScreenDevice;}
inline CFbsBitGc* CDirectScreenAccess::Gc()
	{return iGc;}
inline CFbsScreenDevice*& CDirectScreenAccess::ScreenDevice()
	{return iScreenDevice;}
inline RRegion* CDirectScreenAccess::DrawingRegion()
	{return iDrawingRegion;}


#endif
