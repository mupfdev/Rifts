// Copyright (c) 2001, Nokia. All rights reserved.

#include <eikmenup.h>

#include "sound.pan"
#include "sound.hrh"
#include "toneadapter.h"
#include "soundappui.h"

// Identifying string for this audio utility
_LIT(KAudioTone, "Tone");

// Frequency and duration of the tone to be played
static const TInt KSoundFrequency = 3000;
static const TInt KSoundDuration = 5000000;


CToneAdapter::CToneAdapter(CSoundAppUi& aAppUi) : 
    iAppUi(aAppUi) 
    {
    }

CToneAdapter* CToneAdapter::NewL(CSoundAppUi& aAppUi)
    {
    CToneAdapter* self = NewLC(aAppUi);
    CleanupStack::Pop(); // self
    return self;
    }

CToneAdapter* CToneAdapter::NewLC(CSoundAppUi& aAppUi)
    {
    CToneAdapter* self = new(ELeave)CToneAdapter(aAppUi);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CToneAdapter::ConstructL()
    {
    iMdaAudioToneUtility = CMdaAudioToneUtility::NewL(*this);

    // Configure the audio tone utility to play a single tone
    // causes MMdaAudioToneObserver::MatoPrepareComplete to be called
    iMdaAudioToneUtility->PrepareToPlayTone(KSoundFrequency, TTimeIntervalMicroSeconds(KSoundDuration));
    }

CToneAdapter::~CToneAdapter()
    {
    delete iMdaAudioToneUtility;    
    iMdaAudioToneUtility = NULL;
    }


// Note that this implementation of the virtual function does not leave.
void CToneAdapter::UpdateMenuL(CEikMenuPane* aMenuPane)
    {
    aMenuPane->SetItemDimmed(ESoundCmdPlay,   ETrue);
    aMenuPane->SetItemDimmed(ESoundCmdRecord, ETrue);
    aMenuPane->SetItemDimmed(ESoundCmdStop,   ETrue);
    aMenuPane->SetItemDimmed(ESoundCmdChange, ETrue);
    
    switch (iMdaAudioToneUtility->State())
        {
    case EMdaAudioToneUtilityNotReady:
        aMenuPane->SetItemDimmed(ESoundCmdChange, EFalse);
        break;
    case EMdaAudioToneUtilityPrepared:
        aMenuPane->SetItemDimmed(ESoundCmdPlay, EFalse);
        aMenuPane->SetItemDimmed(ESoundCmdChange, EFalse);
        break;
    case EMdaAudioToneUtilityPlaying:
        aMenuPane->SetItemDimmed(ESoundCmdStop, EFalse);
        break;
    default:
        __ASSERT_ALWAYS(EFalse, User::Panic(KToneAdapter, KSoundPanicInvalidMdaState));
        break;
        }
    }

// Note that this implementation of the virtual function does not leave.
void CToneAdapter::PlayL()
    {
    iMdaAudioToneUtility->Play();
    }

// CMdaAudioToneUtility is not able to record
void CToneAdapter::RecordL() 
    {
    }

// Note that this implementation of the virtual function does not leave.
void CToneAdapter::StopL()
    {
    iMdaAudioToneUtility->CancelPlay();
    }

const TDesC& CToneAdapter::Identify()
    {
    return KAudioTone;
    }


// from MMdaAudioToneObserver
void CToneAdapter::MatoPrepareComplete(TInt /*aError*/)
    {
    iMdaAudioToneUtility->SetVolume(iMdaAudioToneUtility->MaxVolume());
    }

// from MMdaAudioToneObserver
void CToneAdapter::MatoPlayComplete(TInt /*aError*/)
    {
    }
