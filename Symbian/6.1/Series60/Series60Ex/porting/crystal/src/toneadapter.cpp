// Copyright c 2000, Nokia. All rights reserved.

// CToneAdapter

#include <eikmenup.h>

#include "sound.pan"
#include "sound.hrh"

#include "toneadapter.h"

#include "soundappui.h"

// Identifying string for this audio utility
_LIT(KAudioTone, "Tone");

// Frequency and duration of the tone to be played
const TInt KSoundFrequency = 3000;
const TInt KSoundDuration = 5000000;


CToneAdapter::CToneAdapter(CSoundAppUi& aAppUi) : 
    iAppUi(aAppUi) 
    {
    //empty constructor body
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
    //

    __TEST_INVARIANT;
    }

CToneAdapter::~CToneAdapter()
    {
    delete iMdaAudioToneUtility;    
    iMdaAudioToneUtility = NULL;
    }

void CToneAdapter::UpdateCBA()
    {
    __TEST_INVARIANT;

    switch (iMdaAudioToneUtility->State())
        {
    case EMdaAudioToneUtilityNotReady:
        iAppUi.DisableCBACommand(ESoundCmdPlay);
        iAppUi.DisableCBACommand(ESoundCmdRecord);
        iAppUi.DisableCBACommand(ESoundCmdStop);
        iAppUi.EnableCBACommand(ESoundCmdChange);
        break;
    case EMdaAudioToneUtilityPrepared:
        iAppUi.EnableCBACommand(ESoundCmdPlay);
        iAppUi.DisableCBACommand(ESoundCmdRecord);
        iAppUi.DisableCBACommand(ESoundCmdStop);
        iAppUi.EnableCBACommand(ESoundCmdChange);
        break;
    case EMdaAudioToneUtilityPlaying:
        iAppUi.DisableCBACommand(ESoundCmdPlay);
        iAppUi.DisableCBACommand(ESoundCmdRecord);
        iAppUi.EnableCBACommand(ESoundCmdStop);
        iAppUi.DisableCBACommand(ESoundCmdChange);
        break;
    default:
        __ASSERT_ALWAYS(EFalse, User::Panic(_L("CToneAdapter"), KSoundPanicInvalidMdaState));
        break;
        }

    iAppUi.DrawCBA();
    
    __TEST_INVARIANT;
    }

// Note that this implementation of the virtual function does not leave.
void CToneAdapter::UpdateMenuL(CEikMenuPane* aMenuPane)
    {
    __TEST_INVARIANT;

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
        __ASSERT_ALWAYS(EFalse, User::Panic(_L("CToneAdapter"), KSoundPanicInvalidMdaState));
        break;
        }

    __TEST_INVARIANT;
    }

// Note that this implementation of the virtual function does not leave.
void CToneAdapter::PlayL()
    {

    __TEST_INVARIANT;

    iMdaAudioToneUtility->Play();

    __TEST_INVARIANT;
    }

// CMdaAudioToneUtility is not able to record
void CToneAdapter::RecordL() 
    {
    }

// Note that this implementation of the virtual function does not leave.
void CToneAdapter::StopL()
    {

    __TEST_INVARIANT;

    iMdaAudioToneUtility->CancelPlay();

    __TEST_INVARIANT;
    }

const TDesC& CToneAdapter::Identify()
    {
    return KAudioTone;
    }


// from MMdaAudioToneObserver
void CToneAdapter::MatoPrepareComplete(TInt /*aError*/)
    {
    __TEST_INVARIANT;

    iMdaAudioToneUtility->SetVolume(iMdaAudioToneUtility->MaxVolume());

    // Assumes CToneAdapter is the default start class
    UpdateCBA();

    __TEST_INVARIANT;
    }

// from MMdaAudioToneObserver
void CToneAdapter::MatoPlayComplete(TInt /*aError*/)
    {
    __TEST_INVARIANT;

    UpdateCBA();

    __TEST_INVARIANT;
    }

void CToneAdapter::__DbgTestInvariant() const
    {
    __ASSERT_DEBUG(iMdaAudioToneUtility != NULL, User::Panic(_L("CToneAdapter"), KSoundPanicInvariant));
    }
