// EIKBTPAN.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKBTPAN_H__)
#define __EIKBTPAN_H__

#if !defined(__EIKBTGRP_H__)
#include <eikbtgrp.h>
#endif

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

#if !defined(__COECOBS_H__)
#include <coecobs.h>
#endif

#if !defined(__EIKLBBUT_H__)
#include <eiklbbut.h>
#endif

#include <eikctgrp.h>

class MEikCommandObserver;

/**
 * @internal
 * Internal to Symbian
 */
class CEikButtonPanel : public CCoeControl, public MCoeControlObserver, public MEikButtonGroup
	{
public: // new functions
	IMPORT_C CEikButtonPanel();
	IMPORT_C ~CEikButtonPanel();
	IMPORT_C void ConstructL();
	IMPORT_C void AddButtonL(CEikLabeledButton* aButton,TInt aId);
	IMPORT_C void AddButtonL(CEikLabeledButton* aButton,TInt aId, TInt aRow);
	IMPORT_C void SetHorizontal();
	IMPORT_C TInt ButtonId(CCoeControl* aControl) const;
	IMPORT_C CEikCommandButtonBase* ButtonById(TInt aButtonId) const;
	IMPORT_C CEikLabeledButton* LabeledButtonById(TInt aButtonId) const;
	IMPORT_C void MakeButtonVisible(TInt aButtonId,TBool aVisible);
	IMPORT_C CEikCommandButtonBase* ButtonForKey(TInt aChar,TInt& aButtonId) const;
	IMPORT_C void ResetMinimumSize();
	IMPORT_C void SetMinButtonWidth(TInt aWidth);
	IMPORT_C void SetCommandObserver(MEikCommandObserver* aCommandObserver);
	void UpdateHotKeyL(TInt aCommandId,CEikLabeledButton::TFlags aFlags,TInt aKeyCode);
public:	// from CCoeControl
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C TSize MinimumSize();
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C void HandleResourceChange(TInt aType);			// not available before Release 005u
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
protected: // from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
public: // from MCoeControlObserver
	IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
private: // from MEikButtonGroup
	void SetCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);
	void SetCommandL(TInt aPosition,TInt aResourceId);
	void SetCommandSetL(TInt aResourceId);
	void AddCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);
	void AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask);
	void AddCommandToStackL(TInt aPosition,TInt aResourceId);
	void AddCommandSetToStackL(TInt aResourceId);
	void SetDefaultCommand(TInt aCommandId);
	TSize CalcMinimumSizeL(TInt aResourceId);
	void RemoveCommandFromStack(TInt aPosition,TInt aCommandId);
	TInt CommandPos(TInt aCommandId) const;
	void DimCommand(TInt aCommandId,TBool aDimmed);
	TBool IsCommandDimmed(TInt aCommandId) const;
	void MakeCommandVisible(TInt aCommandId,TBool aVisible);
	TBool IsCommandVisible(TInt aCommandId) const;
	CCoeControl* AsControl();
	const CCoeControl* AsControl() const;
	void SetBoundingRect(const TRect& aBoundingRect);
	void ReduceRect(TRect& aBoundingRect) const;
	CCoeControl* GroupControlById(TInt aCommandId) const;
	CEikCommandButton* GroupControlAsButton(TInt aCommandId) const;
	TInt CommandId(TInt aCommandPos) const;
	TInt ButtonCount() const;
	TUint ButtonGroupFlags() const;
private: // from CCoeControl
	IMPORT_C void ActivateL();
    IMPORT_C TInt CountComponentControls() const;
    IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
    IMPORT_C void SizeChanged();
	IMPORT_C void Reserved_2();
private: // new functions
	TInt RelativePosition(TInt aCommandPos, TInt& aGroupIndex) const;
	TBool ButtonsConsumedKeyL(TInt aCode);
	void AppendNewLineL();
	CEikLabeledButton* LabeledButtonByPosition(TInt aPosition, TInt& aGroupIndex) const;
	CEikLabeledButton* LabeledButtonByPosition(TInt aPosition) const;
	void AdjustMarginsToFit(TInt8& aLeftBorder, TInt8& aRightBorder, TInt& aGapBetweenButtons);
	void SetButtonWidths();
private:
	CArrayPtrFlat<CEikControlGroup>* iControlGroups;
	TSize iMinSize;
	TInt iButWidth;
	TInt iMinButWidth;
	TInt iCount; // for efficiency
	MEikCommandObserver* iCommandObserver;
	};

#endif
