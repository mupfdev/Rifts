// EIKBTGRP.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKBTGRP_H__)
#define __EIKBTGRP_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

class CCoeControl;
class CEikCommandButton;
class CFbsBitmap;

/**
 * @internal
 */
class MEikButtonGroup
	{
public:
	void Release();
	virtual void SetCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask)=0;
	virtual void SetCommandL(TInt aPosition,TInt aResourceId)=0;
	virtual void SetCommandSetL(TInt aResourceId)=0;
	virtual void AddCommandL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask)=0;
	virtual void AddCommandToStackL(TInt aPosition,TInt aCommandId,const TDesC* aText,const CFbsBitmap* aBitmap,const CFbsBitmap* aMask)=0;
	virtual void AddCommandToStackL(TInt aPosition,TInt aResourceId)=0;
	virtual void AddCommandSetToStackL(TInt aResourceId)=0;
	virtual void SetDefaultCommand(TInt aCommandId)=0;
	virtual TSize CalcMinimumSizeL(TInt aResourceId)=0;
	virtual void RemoveCommandFromStack(TInt aPosition,TInt aCommandId)=0;
	virtual TInt CommandPos(TInt aCommandId) const=0;
	virtual void DimCommand(TInt aCommandId,TBool aDimmed)=0;
	virtual TBool IsCommandDimmed(TInt aCommandId) const=0;
	virtual void MakeCommandVisible(TInt aCommandId,TBool aVisible)=0;
	virtual TBool IsCommandVisible(TInt aCommandId) const=0;
	IMPORT_C virtual void AnimateCommand(TInt aCommandId);
	virtual CCoeControl* AsControl()=0;
	virtual const CCoeControl* AsControl() const=0;
	// The following methods are only needed for external button groups.
	virtual void SetBoundingRect(const TRect& aBoundingRect)=0;
	virtual void ReduceRect(TRect& aBoundingRect) const=0;
	//
	virtual CCoeControl* GroupControlById(TInt aCommandId) const=0;
	virtual CEikCommandButton* GroupControlAsButton(TInt aCommandId) const=0;
	virtual TInt CommandId(TInt aCommandPos) const=0;
	virtual TInt ButtonCount() const=0;
	virtual TUint ButtonGroupFlags() const=0;
private:
	IMPORT_C void Reserved_1();
	};

#endif
