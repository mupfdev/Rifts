/*
* ============================================================================
*  Name     : AknView.h
*  Part of  : Avkon
*
*  Description:
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
// AknView.h
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#ifndef AKNVIEW_H
#define AKNVIEW_H

#include <coecntrl.h>
#include <eikmobs.h>
#include <coeaui.h>
#include <coeview.h>
#include <eikdef.h>
#include <coemop.h>

class CAknViewAppUi;
class CEikStatusPane;
class CEikButtonGroupContainer;
class CAknControlStack;

/**
 * Base class for a Series 60 application view.
 */
class CAknView : public CBase, public MCoeView, public MEikMenuObserver, public MObjectProvider
	{
public:
	IMPORT_C CAknView();
	IMPORT_C ~CAknView();
	IMPORT_C void BaseConstructL(TInt aResId=0);
	IMPORT_C void ConstructMenuAndCbaEarlyL();		// to be used by views which need to access the menu or cba before the view is activated for the first time

	// View activation.
	IMPORT_C void ActivateViewL(const TVwsViewId& aViewId);
	IMPORT_C void ActivateViewL(const TVwsViewId& aViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage);

	IMPORT_C virtual TUid Id() const =0;
	IMPORT_C virtual void HandleStatusPaneSizeChange();

	// From MCoeView.
	IMPORT_C TVwsViewId ViewId() const;

	// from MEikMenuObserver
	IMPORT_C virtual void ProcessCommandL(TInt aCommand);

	IMPORT_C virtual void HandleCommandL(TInt aCommand);
	IMPORT_C virtual CEikMenuBar* MenuBar() const;
	IMPORT_C TRect ClientRect() const;
	IMPORT_C void StopDisplayingMenuBar();
	IMPORT_C TBool IsForeground() const;

	// Avkon view architecture system. Internal use only.
	IMPORT_C virtual void AknViewActivatedL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage);
	void AknViewDeactivated();
	void ProcessForegroundEventL(TBool aForeground);

private: // formerly from MTopSetMember<CEikMenuBar>
	IMPORT_C virtual void Reserved_MtsmPosition();
	IMPORT_C virtual void Reserved_MtsmObject();

protected:
	IMPORT_C CAknViewAppUi* AppUi() const;
	IMPORT_C CEikStatusPane* StatusPane() const;
	IMPORT_C CEikButtonGroupContainer* Cba() const;

	IMPORT_C virtual void DoActivateL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage) = 0;
	IMPORT_C virtual void DoDeactivate() = 0;

protected: // From MCoeView.
	IMPORT_C void ViewActivatedL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage);
	IMPORT_C void ViewDeactivated();
	IMPORT_C TVwsViewIdAndMessage ViewScreenDeviceChangedL();

protected: // from MObjectProvider
	IMPORT_C TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
	IMPORT_C MObjectProvider* MopNext();

protected: // From MEikMenuObserver.
	IMPORT_C virtual void SetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis);

	// foreground event handler
	IMPORT_C virtual void HandleForegroundEventL(TBool aForeground);

private: // internal functions
	void ConstructMenuAndCbaL(TBool aVisible);
		
protected:
	// The follow objects are not owned by this class
	// iCoeEnv is protected in keeping with CCoeAppUi & CCoeControl
	CCoeEnv* iCoeEnv;

private:
	CAknViewAppUi* iAppUi;

	// SAknViewInfo is the C++ image of resource structure AVKON_VIEW
	struct SAknViewInfo
		{
	public:
		TInt iHotKeys;		// resource id
		TInt iMenu;			// resource id
		TInt iCba;			// resource id
		};

	// The following member data are owned by this class
	SAknViewInfo iViewInfo;
	CEikMenuBar* iMenu;
	CEikButtonGroupContainer* iCba;
	TBitFlags iFlags;
	TInt iSpare;
	};

#endif
