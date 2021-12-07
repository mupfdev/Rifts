// EIKTBAR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKTBAR_H__)
#define __EIKTBAR_H__

#if !defined(__EIKCTGRP_H__)
#include <eikctgrp.h>
#endif

#if !defined(__COECOBS_H__)
#include <coecobs.h>
#endif

#if !defined(__EIKBTGRP_H__)
#include <eikbtgrp.h>
#endif

#if !defined(__EIKBTGPC_H__)
#include <eikbtgpc.h>
#endif

class MEikCommandObserver;
class TEikButtonCoordinator;
class CEikCommandButton;
class CCoeBrushAndPenContext;

class CEikToolBar : public CEikControlGroup, public MCoeControlObserver, public MEikButtonGroup
	{
public:
	IMPORT_C ~CEikToolBar();
	IMPORT_C CEikToolBar();
	IMPORT_C void ConstructL(MEikCommandObserver* aCommandObserver,TInt aResourceId,const TRect& aBoundingRect);
	IMPORT_C void StaticConstructL(MEikCommandObserver* aCommandObserver,TInt aResourceId);
	IMPORT_C void SetCommandObserver(MEikCommandObserver* aCommandObserver);
	IMPORT_C void CoordinateButtons(TInt aId,TInt aCount,TEikButtonCoordinator* aCoordinator);
	IMPORT_C void SetButtonStateOn(TInt aId,TBool aState);
	IMPORT_C TBool DelayActivation() const;
public: // from CCoeControl
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void SetDimmed(TBool aDimmed);
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C void HandleResourceChange(TInt aType);			// not available before Release 005u
public: // from CEikControlGroup
	IMPORT_C void AddControlL(CCoeControl* aControl,TInt aId);
	IMPORT_C void AddControlL(TEikGroupControl& aGroupControl);
public: // but not exported
	void AddControlTypeL(TInt aType);
	void RemoveControlType(TInt aIndex);
	TBool ControlIsButton(TInt aIndex) const;
public: // from MEikButtonGroup
	IMPORT_C void SetBoundingRect(const TRect& aBoundingRect);
	IMPORT_C void ReduceRect(TRect& aBoundingRect) const;
protected: //fom CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	CEikCommandButton* ButtonByIndex(TInt aIndex) const;
	void SetCurrentId(TInt aPosition,TInt aId);
	TInt CurrentId(TInt aPosition) const;
	TEikGroupControl& GroupControlByIndex(TInt aIndex) const;
	TInt IndexFromPosition(TInt aPos) const;
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
	CCoeControl* GroupControlById(TInt aCommandId) const;
	CEikCommandButton* GroupControlAsButton(TInt aCommandId) const;
	TInt CommandId(TInt aCommandPos) const;
	TInt ButtonCount() const;
	TUint ButtonGroupFlags() const;
private: // from MCoeControlObserver
	IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEvent);
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
	void BaseConstructL();
	TInt ControlCount() const;
private:
	TInt iToolBarFlags;
	MEikCommandObserver* iCommandObserver;
	CCoeBrushAndPenContext* iBrushAndPenContext;
	CArrayFix<TInt>* iControlTypes; 
	};

#endif
