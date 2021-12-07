/*
* ============================================================================
*  Name     : AknViewAppUi.h
*  Part of  : Avkon
*
*  Description:
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
#ifndef __AKNVIEWAPPUI_H__
#define __AKNVIEWAPPUI_H__

#include "aknappui.h"

class CAknView;
class CAknViewShutter;
class CAknLocalScreenClearer;

#define iAvkonViewAppUi ((CAknViewAppUi*)CEikonEnv::Static()->EikAppUi())

class CAknViewAppUi : public CAknAppUi
    {
public:
	class CViewActivationItem : public CBase
		{
	public:
		static CViewActivationItem* NewLC(CAknView* aNewView, TUid aCustomMessageId, const TDesC8& aCustomMessage, const TVwsViewId& aPrevViewId);
		~CViewActivationItem();
	private:
		CViewActivationItem(CAknView* aNewView, TUid aCustomMessageId, const TVwsViewId& aPrevViewId);
		void ConstructL(const TDesC8& aCustomMessage);
	public:
		CAknView* iNewView;
		TUid iCustomMessageId;
		HBufC8* iCustomMessage;
		TVwsViewId iPrevViewId;
		};

	typedef CArrayPtrFlat<CViewActivationItem> CAknViewActivationQueue;
	typedef CArrayPtrFlat<CAknView> CAknViews;

public:
	IMPORT_C void BaseConstructL(TInt aAppUiFlags=0);
	IMPORT_C ~CAknViewAppUi();

	IMPORT_C void ActivateLocalViewL(TUid aViewId);
	IMPORT_C void ActivateLocalViewL(TUid aViewId, TUid aCustomMessageId, const TDesC8& aCustomMessage);
	IMPORT_C CAknView* View(TUid aView) const;
	IMPORT_C void AddViewL(CAknView* aView);		// takes ownership of aView
	IMPORT_C void RemoveView(TUid aViewId);

	IMPORT_C void ProcessCommandL(TInt aCommand);
	IMPORT_C void StopDisplayingMenuBar();

	// Avkon view architecture system. Internal use only.
	void ViewActivatedL(CAknView* aView, const TVwsViewId& aPrevViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage);
	void ViewDeactivated(CAknView* aView);

protected:
	// from MEikStatusPaneObserver
	IMPORT_C void HandleStatusPaneSizeChange();

	// from CCoeAppUi
	IMPORT_C void HandleForegroundEventL(TBool aForeground);

private:
	static TInt ActivationCallBack(TAny* aThis);
	void ActivationTick();
	void QueueActivationTick();

protected:
	CAknView* iView;
	CAknViews* iViews;

private:
	CAknViewShutter* iShutter;
	CAknLocalScreenClearer* iClearer;
	CAknViewActivationQueue* iActivationQueue;
	CIdle* iActivationTick;
	TInt iSpare;
    };


#endif
