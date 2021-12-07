/*
* ============================================================================
*  Name     : AknPopupFader.h
*  Part of  : Avkon
*
*  Description:
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
// AknPopupFader.h
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNPOPUPFADER_H__)
#define __AKNPOPUPFADER_H__

#include <e32base.h>

class CCoeControl;


class MAknFadedComponent
	{
public:
	IMPORT_C virtual TInt CountFadedComponents();
	IMPORT_C virtual CCoeControl* FadedComponent(TInt aIndex);
	};

class TAknPopupFader
	{
public:
	IMPORT_C void FadeBehindPopup(MAknFadedComponent* aComponent, CCoeControl* aParent, TBool aFade);

public:	// internal
	static void CreateStaticL();

private:
	void FadeBehindPopupL(MAknFadedComponent* aComponent, CCoeControl* aParent, TBool aFade);

private:
	TBool iBackgroundFaded; // unused
	};


#endif
