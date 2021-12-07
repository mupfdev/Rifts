// Copyright (c) 2001, Nokia. All rights reserved.

#include <eikmenup.h>

#include "sound.pan"
#include "sound.hrh"
#include "recorderadapter.h"
#include "soundappui.h"

// Identifying string for this audio utility
_LIT(KAudioRecorder, "Recorder");

// An existing sound sample file 
_LIT(KRecorderFile, "C:\\System\\Apps\\Sound\\record.wav");


CRecorderAdapter::CRecorderAdapter(CSoundAppUi& aAppUi) : 
    iAppUi(aAppUi) 
    {
    }

CRecorderAdapter* CRecorderAdapter::NewL(CSoundAppUi& aAppUi)
    {
    CRecorderAdapter* self = NewLC(aAppUi);
    CleanupStack::Pop(); // self
    return self;
    }

CRecorderAdapter* CRecorderAdapter::NewLC(CSoundAppUi& aAppUi)
    {
    CRecorderAdapter* self = new (ELeave) CRecorderAdapter(aAppUi);
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
    }

CRecorderAdapter::~CRecorderAdapter()
    {
    delete iMdaAudioRecorderUtility;    
    iMdaAudioRecorderUtility = NULL;
    }

void CRecorderAdapter::UpdateMenuL(CEikMenuPane* aMenuPane)
    {
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
        __ASSERT_ALWAYS(EFalse, User::Panic(KRecorderAdapter, KSoundPanicInvalidMdaState));
        break;
        }
    }

void CRecorderAdapter::PlayL()
    {
    // Play through the device speaker
    iMdaAudioRecorderUtility->SetAudioDeviceMode(CMdaAudioRecorderUtility::ELocal);

    // Set maximum volume for playback
    iMdaAudioRecorderUtility->SetVolume(iMdaAudioRecorderUtility->MaxVolume());

    // Set the playback position to the start of the file
    iMdaAudioRecorderUtility->SetPosition(TTimeIntervalMicroSeconds(0));
    //

    iMdaAudioRecorderUtility->PlayL();
    }

void CRecorderAdapter::StopL()
    {
    iMdaAudioRecorderUtility->Stop();
    }

void CRecorderAdapter::RecordL()
    {
    // Record from the device microphone
    iMdaAudioRecorderUtility->SetAudioDeviceMode(CMdaAudioRecorderUtility::ELocal);

    // Set maximum gain for recording
    iMdaAudioRecorderUtility->SetGain(iMdaAudioRecorderUtility->MaxGain());
    
    // Delete current audio sample from beginning of file
    iMdaAudioRecorderUtility->SetPosition(TTimeIntervalMicroSeconds(0));
    iMdaAudioRecorderUtility->CropL();
    //

    iMdaAudioRecorderUtility->RecordL();
    }


const TDesC& CRecorderAdapter::Identify()
    {
    return KAudioRecorder;
    }


// from MMdaObjectStateChangeObserver
void CRecorderAdapter::MoscoStateChangeEvent(CBase* /*aObject*/, TInt /*aPreviousState*/, TInt /*aCurrentState*/, TInt /*aErrorCode*/)
    {
    }
