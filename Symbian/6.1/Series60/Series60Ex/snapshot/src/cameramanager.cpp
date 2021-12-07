/* Copyright (c) 2001, Nokia. All rights reserved */

#include <CameraServ.h>
#include "CameraManager.h"
#include "CameraObserver.h"


CCameraManager* CCameraManager::NewL(MCameraObserver& aObserver)
	{
	CCameraManager* self = CCameraManager::NewLC(aObserver);
	CleanupStack::Pop();
	return self;
	}


CCameraManager* CCameraManager::NewLC(MCameraObserver& aObserver)
	{
	CCameraManager* self = new (ELeave) CCameraManager(aObserver);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}


CCameraManager::CCameraManager(MCameraObserver& aObserver)
:	CActive(CActive::EPriorityStandard),
    iObserver(aObserver),
    iCameraState(EUninitalised)
	{
	//	Implementation not required
	}


CCameraManager::~CCameraManager()
	{
	Cancel();

    if (iCameraState != EUninitalised)
        {
        //  Connected to the server so shut the camera down
        iCameraServer.TurnCameraOff();

        iCameraServer.Close();
        }

	}


void CCameraManager::ConstructL()
	{
    User::LeaveIfError(iCameraServer.Connect());

    iCameraState = EStartingCamera;
    iCameraServer.TurnCameraOn(iStatus);

	CActiveScheduler::Add(this);

	SetActive();
	}


TBool CCameraManager::IsReady()
    {
    if (iCameraState == EReady)
        {
        return  ETrue;
        }
    else
        {
        return  EFalse;
        }
    }

void CCameraManager::Snap(CFbsBitmap& aBitmap)
    {
    ASSERT(IsReady());

    iCameraState = ETakingPicture;
    iCameraServer.GetImage(iStatus, aBitmap);
    SetActive();
    }

void CCameraManager::DoCancel()
	{
    //  Not implementated
	}


void CCameraManager::RunL()
	{
    if (iStatus != KErrNone)
        {
            iObserver.Error(iStatus.Int());
            return;
        }

    switch (iCameraState)
        {
    case EStartingCamera:
        iCameraServer.SetLightingConditions(RCameraServ::ELightingNormal);
        iCameraServer.SetImageQuality(RCameraServ::EQualityHigh);
        iCameraState = EReady;
        break;

    case ETakingPicture:
        iObserver.PictureTaken();
        iCameraState = EReady;
        break;

    case EReady:
    case EError:
    default:
        iCameraState = EError;  //  For the invalid cases
        iObserver.Error(KErrGeneral);

        }
	}
    
