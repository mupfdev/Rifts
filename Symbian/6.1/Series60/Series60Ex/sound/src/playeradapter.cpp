// Copyright (c) 2001, Nokia. All rights reserved.

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
    }

CPlayerAdapter* CPlayerAdapter::NewL(const TDesC& aFileName, CSoundAppUi& aAppUi)
    {
    CPlayerAdapter* self = NewLC(aFileName, aAppUi);
    CleanupStack::Pop();  // self
    return self;
    }

CPlayerAdapter* CPlayerAdapter::NewLC(const TDesC& aFileName, CSoundAppUi& aAppUi)
    {
    CPlayerAdapter* self = new (ELeave) CPlayerAdapter(aAppUi);
    CleanupStack::PushL(self);
    self->ConstructL(aFileName);
    return self;
    }


void CPlayerAdapter::ConstructL(const TDesC& aFileName)
    {
    // Create an audio player utility instance for playing sample data from a file
    // causes MMdaAudioPlayerCallback::MapcInitComplete to be called
    iMdaAudioPlayerUtility = CMdaAudioPlayerUtility::NewFilePlayerL(aFileName, *this);
    }

CPlayerAdapter::~CPlayerAdapter()
    {
    delete iMdaAudioPlayerUtility;    
    iMdaAudioPlayerUtility = NULL;
    }


// Note that this implementation of the virtual function does not leave.
void CPlayerAdapter::UpdateMenuL(CEikMenuPane* aMenuPane)
    {
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
        __ASSERT_ALWAYS(EFalse, User::Panic(KPlayerAdapter, KSoundPanicInvalidMdaState));
        break;
        }
    }


// Note that this implementation of the virtual function does not leave.
void CPlayerAdapter::PlayL()
    {
    iMdaAudioPlayerUtility->Play();
    iState = EPlaying;
    }


// CMdaAudioPlayerUtility is not able to record
void CPlayerAdapter::RecordL() 
    {
    }


// Note that this implementation of the virtual function does not leave.
void CPlayerAdapter::StopL()
    {
    iMdaAudioPlayerUtility->Stop();
    iState = EReadyToPlay;
    }



const TDesC& CPlayerAdapter::Identify()
    {
    return KAudioPlayer;
    }


// from MMdaAudioPlayerCallback
void CPlayerAdapter::MapcInitComplete(TInt aError, const TTimeIntervalMicroSeconds& /*aDuration*/)
    {
    iState = aError ? ENotReady : EReadyToPlay;
    }


void CPlayerAdapter::MapcPlayComplete(TInt aError)
    {
    iState = aError ? ENotReady : EReadyToPlay;
    }
