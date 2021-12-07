// Copyright c 2000, Nokia. All rights reserved.

#include <eikmenup.h>

#include "sound.pan"
#include "sound.hrh"
#include "recorderadapter.h"
#include "soundappui.h"

// Identifying string for this audio utility
_LIT(KAudioRecorder, "Recorder");

// An existing sound sample file 
_LIT(KRecorderFile, "C:\\documents\\record.wav");


CRecorderAdapter::CRecorderAdapter(CSoundAppUi& aAppUi) : 
    iAppUi(aAppUi) 
    {
    //empty constructor body
    }

CRecorderAdapter* CRecorderAdapter::NewL(CSoundAppUi& aAppUi)
    {
    CRecorderAdapter* self = NewLC(aAppUi);
    CleanupStack::Pop(); // self
    return self;
    }

CRecorderAdapter* CRecorderAdapter::NewLC(CSoundAppUi& aAppUi)
    {
    CRecorderAdapter* self = new(ELeave)CRecorderAdapter(aAppUi);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }


void CRecorderAdapter::ConstructL()
    {
    iMdaAudioRecorderUtility = CMdaAudioRecorderUtility::NewL(*this);

    // Open an existing sample file for playback or recording
    // causes MMdaObjectStateChangeObserver::MoscoStateChangeEvent to be called
    iMdaAudioRecorderUtility->OpenFileL(KRecorderFile);
    //

    __TEST_INVARIANT;
    }

CRecorderAdapter::~CRecorderAdapter()
    {
    delete iMdaAudioRecorderUtility;    
    iMdaAudioRecorderUtility = NULL;
    }

void CRecorderAdapter::UpdateCBA()
    {
    __TEST_INVARIANT;

    switch (iMdaAudioRecorderUtility->State())
        {
    case CMdaAudioRecorderUtility::ENotReady:
        iAppUi.DisableCBACommand(ESoundCmdPlay);
        iAppUi.DisableCBACommand(ESoundCmdRecord);
        iAppUi.DisableCBACommand(ESoundCmdStop);
        iAppUi.EnableCBACommand(ESoundCmdChange);
        break;
    case CMdaAudioRecorderUtility::EOpen:
        iAppUi.EnableCBACommand(ESoundCmdPlay);
        iAppUi.EnableCBACommand(ESoundCmdRecord);
        iAppUi.DisableCBACommand(ESoundCmdStop);
        iAppUi.EnableCBACommand(ESoundCmdChange);
        break;
    case CMdaAudioRecorderUtility::EPlaying:
        iAppUi.DisableCBACommand(ESoundCmdPlay);
        iAppUi.DisableCBACommand(ESoundCmdRecord);
        iAppUi.EnableCBACommand(ESoundCmdStop);
        iAppUi.DisableCBACommand(ESoundCmdChange);
        break;
    case CMdaAudioRecorderUtility::ERecording:
        iAppUi.DisableCBACommand(ESoundCmdPlay);
        iAppUi.DisableCBACommand(ESoundCmdRecord);
        iAppUi.EnableCBACommand(ESoundCmdStop);
        iAppUi.DisableCBACommand(ESoundCmdChange);
        break;
    default:
        __ASSERT_ALWAYS(EFalse, User::Panic(_L("CRecorderAdapter"), KSoundPanicInvalidMdaState));
        break;
        }

    iAppUi.DrawCBA();

    __TEST_INVARIANT;
    }

void CRecorderAdapter::UpdateMenuL(CEikMenuPane* aMenuPane)
    {
    __TEST_INVARIANT;

    aMenuPane->SetItemDimmed(ESoundCmdPlay,   ETrue);
    aMenuPane->SetItemDimmed(ESoundCmdRecord, ETrue);
    aMenuPane->SetItemDimmed(ESoundCmdStop,   ETrue);
    aMenuPane->SetItemDimmed(ESoundCmdChange, ETrue);

    switch (iMdaAudioRecorderUtility->State())
        {
    case CMdaAudioRecorderUtility::ENotReady:
        aMenuPane->SetItemDimmed(ESoundCmdChange, EFalse);
        break;
    case CMdaAudioRecorderUtility::EOpen:
        aMenuPane->SetItemDimmed(ESoundCmdPlay, EFalse);
        aMenuPane->SetItemDimmed(ESoundCmdRecord, EFalse);
        aMenuPane->SetItemDimmed(ESoundCmdChange, EFalse);
        break;
    case CMdaAudioRecorderUtility::EPlaying:
        aMenuPane->SetItemDimmed(ESoundCmdStop, EFalse);
        break;
    case CMdaAudioRecorderUtility::ERecording:
        aMenuPane->SetItemDimmed(ESoundCmdStop, EFalse);
        break;
    default:
        __ASSERT_ALWAYS(EFalse, User::Panic(_L("CRecorderAdapter"), KSoundPanicInvalidMdaState));
        break;
        }

    __TEST_INVARIANT;
    }

void CRecorderAdapter::PlayL()
    {
    __TEST_INVARIANT;

    // Play through the device speaker
    iMdaAudioRecorderUtility->SetAudioDeviceMode(CMdaAudioRecorderUtility::ELocal);

    // Set maximum volume for playback
    iMdaAudioRecorderUtility->SetVolume(iMdaAudioRecorderUtility->MaxVolume());

    // Set the playback position to the start of the file
    iMdaAudioRecorderUtility->SetPosition(TTimeIntervalMicroSeconds(0));
    //

    iMdaAudioRecorderUtility->PlayL();

    __TEST_INVARIANT;
    }

void CRecorderAdapter::StopL()
    {
    __TEST_INVARIANT;

    iMdaAudioRecorderUtility->Stop();

    __TEST_INVARIANT;
    }

void CRecorderAdapter::RecordL()
    {
    __TEST_INVARIANT;

    // Record from the device microphone
    iMdaAudioRecorderUtility->SetAudioDeviceMode(CMdaAudioRecorderUtility::ELocal);

    // Set maximum gain for recording
    iMdaAudioRecorderUtility->SetGain(iMdaAudioRecorderUtility->MaxGain());
    
    // Delete current audio sample from beginning of file
    iMdaAudioRecorderUtility->SetPosition(TTimeIntervalMicroSeconds(0));
    iMdaAudioRecorderUtility->CropL();
    //

    iMdaAudioRecorderUtility->RecordL();

    __TEST_INVARIANT;
    }


const TDesC& CRecorderAdapter::Identify()
    {
    return KAudioRecorder;
    }


// from MMdaObjectStateChangeObserver
void CRecorderAdapter::MoscoStateChangeEvent(CBase* /*aObject*/, TInt aPreviousState, TInt aCurrentState, TInt /*aErrorCode*/)
    {
    __TEST_INVARIANT;
    
    // Do nothing on the initialisation complete transition
    // Update the UI on all other transitions
    if (aPreviousState != CMdaAudioRecorderUtility::ENotReady ||
        aCurrentState  != CMdaAudioRecorderUtility::EOpen)
        {
        UpdateCBA();
        }

    __TEST_INVARIANT;
    }

void CRecorderAdapter::__DbgTestInvariant() const
    {
    __ASSERT_DEBUG(iMdaAudioRecorderUtility != NULL, User::Panic(_L("CRecorderAdapter"), KSoundPanicInvariant));
    }




