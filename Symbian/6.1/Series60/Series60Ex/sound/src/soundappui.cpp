// Copyright (c) 2001, Nokia. All rights reserved.
#include <eikenv.h>
#include <avkon.hrh>
#include <eikbtgpc.h>
#include <Sound.rsg>

#include "sound.pan"
#include "Sound.hrh"
#include "SoundAppUi.h"
#include "SoundView.h"
#include "toneadapter.h"
#include "playeradapter.h"
#include "recorderadapter.h"

_LIT(KSoundSampleFile, "C:\\System\\Apps\\Sound\\play.wav");

CSoundAppUi::CSoundAppUi() 
    {
    }

void CSoundAppUi::ConstructL()
    {
    BaseConstructL();

    iToneAdapter     = CToneAdapter::NewL(*this);

    iPlayerAdapter   = CPlayerAdapter::NewL(KSoundSampleFile, *this);

    iRecorderAdapter = CRecorderAdapter::NewL(*this);

    iAudioAdapter = iToneAdapter;

    iAppView = CSoundView::NewL(ClientRect(), iAudioAdapter->Identify());

    AddToStackL(iAppView);
    }


CSoundAppUi::~CSoundAppUi()
    {
    RemoveFromStack(iAppView);
    delete iAppView;
    iAppView = NULL;

    delete iToneAdapter;
    iToneAdapter =  NULL;
     
    delete iPlayerAdapter;    
    iPlayerAdapter =  NULL;

    delete iRecorderAdapter;    
    iRecorderAdapter = NULL;

    iAudioAdapter = NULL;
    }


void CSoundAppUi::HandleCommandL(TInt aCommand)
    {
    // Handle menu commands
    switch (aCommand)
        {
    case ESoundCmdTone:
        SetAdapterL(iToneAdapter);
        break;
    case ESoundCmdPlayer:
        SetAdapterL(iPlayerAdapter);
        break;
    case EESoundCmdRecorder:
        SetAdapterL(iRecorderAdapter);
        break;
    case EAknSoftkeyExit:
        Exit();
        break;
    case ESoundCmdPlay:
        iAudioAdapter->PlayL();
        break;
    case ESoundCmdStop:
        iAudioAdapter->StopL();
        break;
    case ESoundCmdRecord:
        iAudioAdapter->RecordL();
        break;
    default:
        __ASSERT_ALWAYS(EFalse, User::Panic(KSound, KSoundPanicUnexpectedCommand));
        break;
        }
    }


void CSoundAppUi::SetAdapterL(MAudioAdapter* aAudioAdapter)
    {
    iAudioAdapter = aAudioAdapter;

    UpdateViewL();
    }

void CSoundAppUi::UpdateViewL()
    {
    iAppView->NotifyStatusL(iAudioAdapter->Identify());
    
    iAppView->DrawNow();
    }


void CSoundAppUi::DynInitMenuPaneL(TInt aMenuId, CEikMenuPane* aMenuPane)
    {
    if (aMenuId == R_SOUND_MENU)
        {
        iAudioAdapter->UpdateMenuL(aMenuPane);
        }
    }
