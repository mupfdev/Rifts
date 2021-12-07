// EIKBTGPC.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKBTGPC_H__)
#define __EIKBTGPC_H__

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

#if !defined(__EIKBTGRP_H__)
#include <eikbtgrp.h>
#endif

#if !defined(__EIKCMOBS_H__)
#include <eikcmobs.h>
#endif

#if !defined(__LAFCCTEN_H__)
#include <lafpublc.h>
#endif

#if !defined(__UIKON_HRH__)
#include <uikon.hrh>
#endif

class MEikCommandObserver;
class CEikButtonGroupStack;
class CEikCommandButton;

/**
 * The CEikButtonGroupContainer class provides a wrapper around the different button arrays
 * used in pen and no-pen devices.  Requesting aUse as either EView or EDialog will create
 * the default button set for the host device; the other options are included primarily 
 * for testing.
 *
 * @since ER5U 
 */
class CEikButtonGroupContainer : public CCoeControl, public MEikCommandObserver
	{
public:
	DECLARE_TYPE_ID(0x101F4107);

	enum TUse
		{
		EView			=SLafButtonGroupContainer::EView,
		EDialog			=SLafButtonGroupContainer::EDialog,
		EToolbar		=SLafButtonGroupContainer::EToolbar,		// deprecated (App-framework_6.1)
		ECba			=SLafButtonGroupContainer::ECba,			// deprecated (App-framework_6.1)
		EDialogButtons	=SLafButtonGroupContainer::EDialogButtons	// deprecated (App-framework_6.1)
		};
	enum TOrientation
		{
		EVertical	=SLafButtonGroupContainer::EVertical,
		EHorizontal =SLafButtonGroupContainer::EHorizontal
		};
	enum TLocation
		{
		EInternal	=SLafButtonGroupContainer::EInternal,	// E.g. dialog buttons.
		EExternal	=SLafButtonGroupContainer::EExternal// E.g. toolbar or cba.
		};
	enum THotKeyFlags
		{
		EShowHotKey			=0x01,
		EPlainHotKey		=0x02
		};
	enum TFlags
		{
		EAddToStack			=0x01,
		EDelayActivation	=0x02,
		EUseMaxSize			=0x04,
		};
public:
	IMPORT_C static CEikButtonGroupContainer* NewL(TUse aUse,TOrientation aOrientation,
													MEikCommandObserver* aCommandObserver,TInt aResourceId,
													TUint aFlags=EAddToStack);
	IMPORT_C static CEikButtonGroupContainer* NewL(TUse aUse,TOrientation aOrientation,
													MEikCommandObserver* aCommandObserver,TInt aResourceId,
													const CCoeControl& aParent,TUint aFlags=EAddToStack);
	IMPORT_C static CEikButtonGroupContainer* NewL(TUse aUse,TOrientation aOrientation,
													MEikCommandObserver* aCommandObserver,TInt aResourceId,
													RWindowGroup& aParentWg,TUint aFlags=EAddToStack);
	IMPORT_C ~CEikButtonGroupContainer();
	IMPORT_C static CEikButtonGroupContainer* Current();
public:
	inline void SetCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText);
	inline void SetCommandL(TInt aPosition,TInt aCommandId,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask);
	inline void SetCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask);
	inline void SetCommandL(TInt aPosition,TInt aCommandId,const TDesC& aFile,TInt aBitmapId,TInt aMaskId);
	inline void SetCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId);
	inline void SetCommandL(TInt aPosition,TInt aResourceId);
	inline void SetCommandL(TInt aCommandId,const TDesC& aText);
	inline void SetCommandL(TInt aCommandId,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask);
	inline void SetCommandL(TInt aCommandId,const TDesC& aText,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask);
	inline void SetCommandL(TInt aCommandId,const TDesC& aFile,TInt aBitmapId,TInt aMaskId);
	inline void SetCommandL(TInt aCommandId,const TDesC& aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId);
	IMPORT_C void SetCommandSetL(TInt aResourceId);
	inline void AddCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText);
	inline void AddCommandL(TInt aPosition,TInt aCommandId,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask);
	inline void AddCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask);
	inline void AddCommandL(TInt aPosition,TInt aCommandId,const TDesC& aFile,TInt aBitmapId,TInt aMaskId);
	inline void AddCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId);
	inline void AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC& aText);
	inline void AddCommandToStackL(TInt aPosition,TInt aCommandId,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask);
	inline void AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC& aText,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask);
	inline void AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC& aFile,TInt aBitmapId,TInt aMaskId);
	inline void AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC& aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId);
	inline void AddCommandToStackL(TInt aPosition,TInt aResourceId);
	IMPORT_C void AddCommandSetToStackL(TInt aResourceId);
	IMPORT_C void RemoveCommandFromStack(TInt aPosition,TInt aCommandId);
	IMPORT_C void SetDefaultCommand(TInt aCommandId); 
	IMPORT_C TSize CalcMinimumSizeL(TInt aResourceId) const;
	IMPORT_C void CleanupCommandPushL(TInt aPosition);
	inline void CleanupCommandPop();
	IMPORT_C void CleanupCommandPop(TInt aCount);
	inline void CleanupCommandPopAndDestroy();
	inline void CleanupCommandPopAndDestroy(TInt aCount);
	IMPORT_C TInt MaxCommands() const;
	IMPORT_C TInt ButtonCount() const;
	IMPORT_C void DimCommand(TInt aCommandId,TBool aDimmed);
	IMPORT_C TBool IsCommandDimmed(TInt aCommandId) const;
	IMPORT_C void MakeCommandVisible(TInt aCommandId,TBool aVisible);
	IMPORT_C TBool IsCommandVisible(TInt aCommandId) const;
	IMPORT_C void AnimateCommand(TInt aCommandId);
	IMPORT_C TLocation Location() const;
	IMPORT_C CEikCommandButton* CommandButtonOrNull(TInt aCommandId) const;
	// For use by EExternal button groups only.
	IMPORT_C void SetBoundingRect(const TRect& aRect);
	IMPORT_C void ReduceRect(TRect& aBoundingRect) const;
	//
	IMPORT_C CCoeControl* ControlOrNull(TInt aCommandId) const;
	IMPORT_C CEikCommandButton* ButtonById(TInt aCommandId) const;
	IMPORT_C TInt PositionById(TInt aCommandId) const;
	IMPORT_C void UpdateHotKey(TInt aCommandId,THotKeyFlags aFlags,TInt aKeyId);
	IMPORT_C void UpdateCommandObserverL(TInt aPos,MEikCommandObserver& aCommandObserver);
	IMPORT_C void RemoveCommandObserver(TInt aPos);
	IMPORT_C TBool DelayActivation() const;
	//
	inline MEikButtonGroup* ButtonGroup();
	inline TUse ButtonGroupType();
public: // from CCoeControl
	IMPORT_C TSize MinimumSize();
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	void MakeVisible(TBool aVisible);
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
public: // formerly from MTopSetMember<CEikButtonGroupContainer>, now reserved
	IMPORT_C virtual void Reserved_MtsmPosition();
	IMPORT_C virtual void Reserved_MtsmObject();
private:
	enum TCommandOp {ESet, EAdd, EPush};
private:
	class TCmdPos
		{
	public:
		inline TCmdPos();
		inline TCmdPos(TInt aPos,TInt aCmd);
	public:
		TInt iPos;
		TInt iCmd;
		};
	class TCmdObserver
		{
	public:
		inline TCmdObserver(TInt aPos,MEikCommandObserver& aObserver);
	public:
		TInt iPos;
		MEikCommandObserver& iObserver;
		};
	class CCmdObserverArray : public CArrayFixFlat<TCmdObserver>
		{
	public:
		inline CCmdObserverArray();
		TInt FindIndex(TInt aPos);
		};
private:
	CEikButtonGroupContainer(TUse aUse);
	void ConstructL(TOrientation aOrientation,MEikCommandObserver* aCommandObserver,TInt aResourceId,RWindowGroup* aParentWg,TUint aFlags);
	IMPORT_C void DoSetCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask,TCommandOp aOp);
	IMPORT_C void DoSetCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId,TCommandOp aOp);
	IMPORT_C void DoSetCommandL(TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask,TCommandOp aOp);
	IMPORT_C void DoSetCommandL(TInt aCommandId,const TDesC* aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId,TCommandOp aOp);
	IMPORT_C void DoSetCommandL(TInt aPosition,TInt aResourceId,TCommandOp aOp);
	inline CCoeControl* ButtonGroupAsControl() const;
	void UpdateRect();
	static void CleanupCommandDestroy(TAny* aPtr);
	TCmdPos DoCleanupCommandPop();
	void DoCleanupCommandPopAndDestroy();
private: // from CCoeControl
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	void SizeChanged();
private: // from MEikCommandObserver
	void ProcessCommandL(TInt aCommandId);
	CCoeControl* CreateCustomCommandControlL(TInt aControlType);
private:
	MEikButtonGroup* iButtonGroup;
	TUse iUse;
	CArrayFix<TCmdPos>* iCommandsCleanup;
	MEikCommandObserver* iCommandObserver;
	CCmdObserverArray* iObserverArray;
	TDblQueLink iBtLink;
private:
	friend class CCmdObserverArray;
	friend class CEikButtonGroupStack;
	};


/**
 * Sets aText and aCommandId (but no bitmaps) into the button at aPosition, 
 * overwriting any previous contents.  Panics if aPosition is out of range.
 *
 * @since ER5U 
 */
inline void CEikButtonGroupContainer::SetCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText)
	{DoSetCommandL(aPosition,aCommandId,&aText,NULL,NULL,ESet);}
/**
 * Sets aBitmap, aMask and aCommandId (but no text) into the button at aPosition, 
 * overwriting any previous contents.  Ownership of the bitmaps is transferred at
 * the end of the function.  aMask must be specified to guarantee compliance with
 * different colour schemes.  Panics if aPosition is out of range.
 *
 * @since ER5U 
 */
inline void CEikButtonGroupContainer::SetCommandL(TInt aPosition,TInt aCommandId,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask)
	{DoSetCommandL(aPosition,aCommandId,NULL,&aBitmap,&aMask,ESet);}
/**
 * Sets aText, aBitmap, aMask and aCommandId into the button at aPosition, overwriting any
 * previous contents.  Ownership of the bitmaps is transferred at the end of the function.
 * aMask must be specified to guarantee compliance with different colour schemes.  Panics
 * if aPosition is out of range.
 *
 * @since ER5U 
 */
inline void CEikButtonGroupContainer::SetCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask)
	{DoSetCommandL(aPosition,aCommandId,&aText,&aBitmap,&aMask,ESet);}
/**
 * Sets the bitmaps from the file specified and aCommandId into the button at aPosition, 
 * overwriting any previous contents.  aMask must be specified to guarantee compliance
 * with different colour schemes.  Panics if aPosition is out of range.
 *
 * @since ER5U 
 */
inline void CEikButtonGroupContainer::SetCommandL(TInt aPosition,TInt aCommandId,const TDesC& aFile,TInt aBitmapId,TInt aMaskId)
	{DoSetCommandL(aPosition,aCommandId,NULL,aFile,aBitmapId,aMaskId,ESet);}
/**
 * Sets aText, the bitmaps from the file specified and aCommandId into the button at 
 * aPosition, overwriting any previous contents.  aMask must be specified to guarantee
 * compliance with different colour schemes.  Panics if aPosition is out of range.
 *
 * @since ER5U 
 */
inline void CEikButtonGroupContainer::SetCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId)
	{DoSetCommandL(aPosition,aCommandId,&aText,aFile,aBitmapId,aMaskId,ESet);}
/**
 * Sets the text, bitmaps and command id defined by aResourceId into the button at 
 * aPosition, overwriting any previous contents.  Panics if aPosition is out of range.
 *
 * @since ER5U 
 */
inline void CEikButtonGroupContainer::SetCommandL(TInt aPosition,TInt aResourceId)
	{DoSetCommandL(aPosition,aResourceId,ESet);}
/**
 * Sets aText (but no bitmaps) into the button with id aCommandId, overwriting any 
 * previous contents.  If two buttons have the same id, it is undefined which one 
 * will be altered.  The behaviour is also undefined if aCommandId can't be matched 
 * to any button.
 *
 * @since ER5U 
 */
inline void CEikButtonGroupContainer::SetCommandL(TInt aCommandId,const TDesC& aText)
	{DoSetCommandL(aCommandId,&aText,NULL,NULL,ESet);}
/**
 * Sets aBitmap and aMask (but no text) into the button with id aCommandId,
 * overwriting any previous contents.  Ownership of the bitmaps is transferred at
 * the end of the function.  aMask must be specified to guarantee compliance with
 * different colour schemes.  If two buttons have the same id, it is undefined
 * which one will be altered.  The behaviour is also undefined if aCommandId can't 
 * be matched to any button.
 *
 * @since ER5U 
 */
inline void CEikButtonGroupContainer::SetCommandL(TInt aCommandId,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask)
	{DoSetCommandL(aCommandId,NULL,&aBitmap,&aMask,ESet);}
/**
 * Sets aText, aBitmap, aMask into the button with id aCommandId, overwriting any 
 * previous contents.  Ownership of the bitmaps is transferred at the end of the 
 * function.  aMask must be specified to guarantee compliance with different colour 
 * schemes.  If two buttons have the same id, it is undefined which one will be altered.
 * The behaviour is also undefined if aCommandId can't be matched to any button
 *
 * @since ER5U 
 */
inline void CEikButtonGroupContainer::SetCommandL(TInt aCommandId,const TDesC& aText,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask)
	{DoSetCommandL(aCommandId,&aText,&aBitmap,&aMask,ESet);}
/**
 * Sets the bitmaps from the file specified into the button with id aCommandId,
 * overwriting any previous contents.  Ownership of the bitmaps is transferred at
 * the end of the function.  aMaskId must be specified to guarantee compliance with
 * different colour schemes.  If two buttons have the same id, it is undefined
 * which one will be altered.  The behaviour is also undefined if aCommandId can't 
 * be matched to any button.
 *
 * @since ER5U 
 */
inline void CEikButtonGroupContainer::SetCommandL(TInt aCommandId,const TDesC& aFile,TInt aBitmapId,TInt aMaskId)
	{DoSetCommandL(aCommandId,NULL,aFile,aBitmapId,aMaskId,ESet);}
/**
 * Sets aText and the bitmaps from the file specified into the button with id aCommandId,
 * overwriting any previous contents.  Ownership of the bitmaps is transferred at
 * the end of the function.  aMaskId must be specified to guarantee compliance with
 * different colour schemes.  If two buttons have the same id, it is undefined
 * which one will be altered.  The behaviour is also undefined if aCommandId can't 
 * be matched to any button.
 *
 * @since ER5U 
 */
inline void CEikButtonGroupContainer::SetCommandL(TInt aCommandId,const TDesC& aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId)
	{DoSetCommandL(aCommandId,&aText,aFile,aBitmapId,aMaskId,ESet);}
/**
 * Adds a button containing aText and aCommandId at aPosition.
 * Panics if aPosition is out of range.
 *
 * @since ER5U 
 */
inline void CEikButtonGroupContainer::AddCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText)
	{DoSetCommandL(aPosition,aCommandId,&aText,NULL,NULL,EAdd);}
/**
 * Adds a button containing aBitmap, aMask and aCommandId at aPosition, transferring 
 * ownership of the bitmaps at the end.  Panics if aPosition is out of range.
 *
 * @since ER5U 
 */
inline void CEikButtonGroupContainer::AddCommandL(TInt aPosition,TInt aCommandId,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask)
	{DoSetCommandL(aPosition,aCommandId,NULL,&aBitmap,&aMask,EAdd);}
/**
 * Adds a button containing aText, aBitmap, aMask and aCommandId at aPosition, transferring 
 * ownership of the bitmaps at the end.  Panics if aPosition is out of range.
 *
 * @since ER5U 
 */
inline void CEikButtonGroupContainer::AddCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask)
	{DoSetCommandL(aPosition,aCommandId,&aText,&aBitmap,&aMask,EAdd);}
/**
 * Adds a button containing the bitmaps specified at aPosition.
 * Panics if aPosition is out of range.
 *
 * @since ER5U 
 */
inline void CEikButtonGroupContainer::AddCommandL(TInt aPosition,TInt aCommandId,const TDesC& aFile,TInt aBitmapId,TInt aMaskId)
	{DoSetCommandL(aPosition,aCommandId,NULL,aFile,aBitmapId,aMaskId,EAdd);}
/**
 * Adds a button containing aText and the bitmaps specified at aPosition.
 * Panics if aPosition is out of range.
 *
 * @since ER5U 
 */
inline void CEikButtonGroupContainer::AddCommandL(TInt aPosition,TInt aCommandId,const TDesC& aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId)
	{DoSetCommandL(aPosition,aCommandId,&aText,aFile,aBitmapId,aMaskId,EAdd);}
/**
 * As with SetCommandL but allows the previous command to be retrieved at 
 * any time by calling RemoveCommand.  Panics if aPosition is out of range.
 *
 * @since ER5U 
 */
inline void CEikButtonGroupContainer::AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC& aText)
	{DoSetCommandL(aPosition,aCommandId,&aText,NULL,NULL,EPush);}
/**
 * As with SetCommandL but allows the previous command to be retrieved at 
 * any time by calling RemoveCommand.  Panics if aPosition is out of range.
 *
 * @since ER5U 
 */
inline void CEikButtonGroupContainer::AddCommandToStackL(TInt aPosition,TInt aCommandId,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask)
	{DoSetCommandL(aPosition,aCommandId,NULL,&aBitmap,&aMask,EPush);}
/**
 * As with SetCommandL but allows the previous command to be retrieved at 
 * any time by calling RemoveCommand.  Panics if aPosition is out of range.
 *
 * @since ER5U 
 */
inline void CEikButtonGroupContainer::AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC& aText,const CFbsBitmap& aBitmap,const CFbsBitmap& aMask)
	{DoSetCommandL(aPosition,aCommandId,&aText,&aBitmap,&aMask,EPush);}
/**
 * As with SetCommandL but allows the previous command to be retrieved at 
 * any time by calling RemoveCommand.  Panics if aPosition is out of range.
 *
 * @since ER5U 
 */
inline void CEikButtonGroupContainer::AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC& aFile,TInt aBitmapId,TInt aMaskId)
	{DoSetCommandL(aPosition,aCommandId,NULL,aFile,aBitmapId,aMaskId,EPush);}
/**
 * As with SetCommandL but allows the previous command to be retrieved at 
 * any time by calling RemoveCommand.  Panics if aPosition is out of range.
 *
 * @since ER5U 
 */
inline void CEikButtonGroupContainer::AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC& aText,const TDesC& aFile,TInt aBitmapId,TInt aMaskId)
	{DoSetCommandL(aPosition,aCommandId,&aText,aFile,aBitmapId,aMaskId,EPush);}
/**
 * As with SetCommandL but allows the previous command to be retrieved at 
 * any time by calling RemoveCommand.  Panics if aPosition is out of range.
 *
 * @since ER5U 
 */
inline void CEikButtonGroupContainer::AddCommandToStackL(TInt aPosition,TInt aResourceId)
	{DoSetCommandL(aPosition,aResourceId,EPush);}
/**
 * Remove a command from the cleanup stack.
 *
 * @since ER5U 
 */
inline void CEikButtonGroupContainer::CleanupCommandPop()
	{CleanupCommandPop(1);}
/**
 * Remove a command placed on the cleanup stack by calling CleanupCommandPushL, 
 * rolling back to the previous details.
 *
 * @since ER5U 
 */
inline void CEikButtonGroupContainer::CleanupCommandPopAndDestroy()
	{CleanupStack::PopAndDestroy();}
/**
 * Remove aCount commands placed on the cleanup stack by calling CleanupCommandPushL, 
 * rolling back to the previous details.
 *
 * @since ER5U 
 */
inline void CEikButtonGroupContainer::CleanupCommandPopAndDestroy(TInt aCount)
	{CleanupStack::PopAndDestroy(aCount);}

inline MEikButtonGroup* CEikButtonGroupContainer::ButtonGroup()
	{return iButtonGroup;}

inline CEikButtonGroupContainer::TUse CEikButtonGroupContainer::ButtonGroupType()
	{return iUse;}

#endif
