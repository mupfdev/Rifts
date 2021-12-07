// Copyright c 2000, Nokia. All rights reserved.

#include <eikmenup.h>

#include "sound.pan"
#include "sound.hrh"
#include "playeradapter.h"
#include "soundappui.h"

// Identifying string for this audio utility
_LIT(KAudioPlayer, "Player");


CPlayerAdapter::CPlayerAdapter(CSoundAppUi& aAppUi) : 
    iState(ENotReady), 
    iAppUi(aAppUi) 
    {
    //empty constructor body
    }

CPlayerAdapter* CPlayerAdapter::NewL(const TDesC& aFileName, CSoundAppUi& aAppUi)
    {
    CPlayerAdapter* self = NewLC(aFileName, aAppUi);
    CleanupStack::Pop();  // self
    return self;
    }

CPlayerAdapter* CPlayerAdapter::NewLC(const TDesC& aFileName, CSoundAppUi& aAppUi)
    {
    CPlayerAdapter* self = new(ELeave)CPlayerAdapter(aAppUi);
    CleanupStack::PushL(self);
    self->ConstructL(aFileName);
    return self;
    }


void CPlayerAdapter::ConstructL(const TDesC& aFileName)
    {
    // Create an audio player utility instance for playing sample data from a file
    // causes MMdaAudioPlayerCallback::MapcInitComplete to be called
    iMdaAudioPlayerUtility = CMdaAudioPlayerUtility::NewFilePlayerL(aFileName, *this);
    //

    __TEST_INVARIANT;
    }

CPlayerAdapter::~CPlayerAdapter()
    {
    delete iMdaAudioPlayerUtility;    
    iMdaAudioPlayerUtility = NULL;
    }

void CPlayerAdapter::UpdateCBA()
    {
    __TEST_INVARIANT;

    switch (iState)
        {
    case ENotReady:
        iAppUi.DisableCBACommand(ESoundCmdPlay);
        iAppUi.DisableCBACommand(ESoundCmdRecord);
        iAppUi.DisableCBACommand(ESoundCmdStop);
        iAppUi.EnableCBACommand(ESoundCmdChange);
        break;
    case EReadyToPlay:
        iAppUi.EnableCBACommand(ESoundCmdPlay);
        iAppUi.DisableCBACommand(ESoundCmdRecord);
        iAppUi.DisableCBACommand(ESoundCmdStop);
        iAppUi.EnableCBACommand(ESoundCmdChange);
        break;
    case EPlaying:
        iAppUi.DisableCBACommand(ESoundCmdPlay);
        iAppUi.DisableCBACommand(ESoundCmdRecord);
        iAppUi.EnableCBACommand(ESoundCmdStop);
        iAppUi.DisableCBACommand(ESoundCmdChange);
        break;
    default:
        __ASSERT_ALWAYS(EFalse, User::Panic(_L("CPlayerAdapter"), KSoundPanicInvalidMdaState));
        break;
        }

    iAppUi.DrawCBA();

    __TEST_INVARIANT;
    }

// Note that this implementation of the virtual function does not leave.
void CPlayerAdapter::UpdateMenuL(CEikMenuPane* aMenuPane)
    {
    __TEST_INVARIANT;

    aMenuPane->SetItemDimmed(ESoundCmdPlay,   ETrue);
    aMenuPane->SetItemDimmed(ESoundCmdRecord, ETrue);
    aMenuPane->SetItemDimmed(ESoundCmdStop,   ETrue);
    aMenuPane->SetItemDimmed(ESoundCmdChange, ETrue);

    switch (iState)
        {
    case ENotReady:
        aMenuPane->SetItemDimmed(ESoundCmdChange, EFalse);
        break;
    case EReadyToPlay:
        aMenuPane->SetItemDimmed(ESoundCmdPlay, EFalse);
        aMenuPane->SetItemDimmed(ESoundCmdChange, EFalse);
        break;
    case EPlaying:
        aMenuPane->SetItemDimmed(ESoundCmdStop, EFalse);
        break;
    default:
        __ASSERT_ALWAYS(EFalse, User::Panic(_L("CPlayerAdapter"), KSoundPanicInvalidMdaState));
        break;
        }

    __TEST_INVARIANT;
    }


// Note that this implementation of the virtual function does not leave.
void CPlayerAdapter::PlayL()
    {
    __TEST_INVARIANT;

    iMdaAudioPlayerUtility->Play();
    iState = EPlaying;

    __TEST_INVARIANT;
    }


// CMdaAudioPlayerUtility is not able to record
void CPlayerAdapter::RecordL() 
    {
    }


// Note that this implementation of the virtual function does not leave.
void CPlayerAdapter::StopL()
    {
    __TEST_INVARIANT;

    iMdaAudioPlayerUtility->Stop();
    iState = EReadyToPlay;

    __TEST_INVARIANT;
    }



const TDesC& CPlayerAdapter::Identify()
    {
    return KAudioPlayer;
    }


// from MMdaAudioPlayerCallback
void CPlayerAdapter::MapcInitComplete(TInt aError, const TTimeIntervalMicroSeconds& /*aDuration*/)
    {
    __TEST_INVARIANT;

    iState = aError? ENotReady : EReadyToPlay;
    
    __TEST_INVARIANT;
    }

void CPlayerAdapter::MapcPlayComplete(TInt aError)
    {
    __TEST_INVARIANT;

    iState = aError? ENotReady : EReadyToPlay;

    UpdateCBA();

    __TEST_INVARIANT;
    }


void CPlayerAdapter::__DbgTestInvariant() const
    {
    __ASSERT_DEBUG(iMdaAudioPlayerUtility != NULL, User::Panic(_L("CPlayerAdapter"), KSoundPanicInvariant));
    }

