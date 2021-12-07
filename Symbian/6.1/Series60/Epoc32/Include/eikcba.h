// EIKCBA.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKCBA_H__)
#define __EIKCBA_H__

#if !defined(__EIKCTGRP_H__)
#include <eikctgrp.h>
#endif

#if !defined(__BADESCA_H__)
#include <badesca.h>
#endif

#if !defined(__EIKBRGRP_H__)
#include <eikbtgrp.h>
#endif

#if !defined(__EIKSBOBS_H__)
#include <eiksbobs.h>
#endif

#if !defined(__EIKSBFRM_H__)
#include <eiksbfrm.h>
#endif


class CEikLabel;
class CEikCbaButton;
class CCoeBrushAndPenContext;
class MEikCommandObserver;
class TCoeColorUse;

class CAknScrollBar;
class TEikScrollBarModel;


const TInt KMaxCbaLabelLength = 32;

/**
 * Defines a Control Button Array control, used in Avkon to define the softkeys in the
 * control pane.
 *
 */
class CEikCba : public CEikControlGroup, public MEikButtonGroup, public MEikScrollBarObserver
	{
public:
	DECLARE_TYPE_ID(0x101F4105);

	// Construction/Destruction
	static CEikCba* NewL(const CEikCba* aPrevious,MEikCommandObserver* aCommandObserver,RWindowGroup* aParentWg);
	static CEikCba* NewL(TInt aResourceId,const CEikCba* aPrevious,MEikCommandObserver* aCommandObserver,RWindowGroup* aParentWg);
	static CEikCba* NewLC(const CEikCba* aPrevious,MEikCommandObserver* aCommandObserver,RWindowGroup* aParentWg);
	static CEikCba* NewLC(TInt aResourceId,const CEikCba* aPrevious,MEikCommandObserver* aCommandObserver,RWindowGroup* aParentWg);
	~CEikCba();

public:		// new methods
	const TInt MaxCommands() const;
	void UpdateCbaLabels(TBool aScrollerOn);

	// Scrollbar handling methods
	void SetSBFrameObserver(MEikScrollBarObserver* aObserver);
	void SetScrollBarModelL(TEikScrollBarModel* aModel);
	const CEikCbaScrollBarFrame* ScrollBarFrame() const;
	CAknScrollBar* VScrollBarAsControl();

public:		// from CEikControlGroup
	void InsertControlL(TEikGroupControl& aGroupControl,TInt aIndex);	// Overridden to prevent setting container window

public:		// from MEikButtonGroup
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
	void AnimateCommand(TInt aCommandId);
	CCoeControl* AsControl();
	const CCoeControl* AsControl() const;
	void SetBoundingRect(const TRect& aBoundingRect);
	void ReduceRect(TRect& aBoundingRect) const;
	CCoeControl* GroupControlById(TInt aCommandId);
	CCoeControl* GroupControlById(TInt aCommandId) const;
	TInt CommandId(TInt aCommandPos) const;
	TInt ButtonCount() const;
	void RemovePreviousCommand(TInt aPosition);

	// Added during integration for Rel18 by Tim.
	CEikCommandButton* GroupControlAsButton(TInt aCommandId) const ;
	TUint ButtonGroupFlags() const ;
	IMPORT_C void SetButtonGroupFlags(TInt aFlags);

public:		// formerly from MTopSetMember<CEikCba>, now reserved
	virtual void Reserved_MtsmPosition();
	virtual void Reserved_MtsmObject();

public:		// from CCoeControl
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	TSize MinimumSize();
	void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	void HandleResourceChange(TInt aType);

protected:	// from MEikScrollBarObserver
	virtual void HandleScrollEventL(CEikScrollBar* aScrollBar,TEikScrollEvent aEventType);

private:	// new methods
	CEikCba(const CEikCba* aPrevious,MEikCommandObserver* aCommandObserver,RWindowGroup* aParentWg);
	void BaseConstructL();
	void ConstructL(TInt aResourceId);
	void ConstructFromResourceL(TResourceReader& aReader);
	CEikCbaButton* ButtonById(TInt aCommandId) const;
	void CreateScrollBarFrameL();
	void InsertScrollBarL();
	TEikGroupControl VScrollBarAsGroupControl();

private:	// from CCoeControl
	void SizeChanged();

private:
	TUint					iCbaFlags;
	const CEikCba*			iLink;	// used to maintain the original settings if a client needs to temporarily change its cba 
	CCoeBrushAndPenContext* iBrushAndPenContext;
	MEikCommandObserver*	iCommandObserver;
	CEikCbaScrollBarFrame*	iSBFrame;
	const CFont*			iLabelFont;
	RWindowGroup*			iParentWg;
	};


class CEikCbaButton : public CCoeControl
	{
public:
	struct SButtonOptions
		{
		TInt iCommandId;
		TBool iDimmed;
		};
public:
	~CEikCbaButton();
	void ConstructL(TGulAlignmentValue aAlignment);
public:
	void AddCommandL(const TDesC& aText);
	void PushCommandL(TInt aCommandId,const TDesC& aText);
	TInt PopCommand();
	void RemoveCommand(TInt aCommandId);
	void RemovePreviousCommand();
	// AKNLAF start
	void SwitchToShortTextL(TBool aShortText);
	void SetLabelFont(const CFont* aLabelFont);
	void TruncateLabelText();
	// AKNLAF end
public: // from CCoeControl
	void SetContainerWindowL(const CCoeControl& aContainer);
	void ConstructFromResourceL(TResourceReader& aReader, TGulAlignmentValue anAlignment);
	TSize MinimumSize();
	void SetDimmed(TBool aDimmed);
private:
//	void UpdateLabelReserveLengthL(const TDesC& aText);
	TInt IndexFromCommandId(TInt aCommandId);
	void UpdateLabelText(TPtrC aLabelText);
	TBool TruncateText(TDes& aText, TInt aMaximumSize, const CFont* aFont);
private: // from CCoeControl
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	void SizeChanged();
private:
	TBuf<KMaxCbaLabelLength> iFullLabelText;
	TPtrC iLongLabelText;
	TPtrC iShortLabelText;
	CEikLabel* iLabel;
	CDesCArray* iText;
	CArrayFix<SButtonOptions>* iButtonOptions;
	TInt iSpare;
	};


#endif
