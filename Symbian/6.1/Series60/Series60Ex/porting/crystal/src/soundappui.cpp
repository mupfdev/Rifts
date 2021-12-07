// Copyright c 2000, Nokia. All rights reserved.

#include <eikenv.h>
#include <eikon.hrh>
#include <eikbtgpc.h>

#include <Sound.rsg>

#include "sound.pan"
#include "Sound.hrh"
#include "SoundAppUi.h"
#include "SoundView.h"

#include "toneadapter.h"
#include "playeradapter.h"
#include "recorderadapter.h"

_LIT(KSoundSampleFile, "C:\\documents\\play.wav");

CSoundAppUi::CSoundAppUi() 
    {
    //empty constructor body
    }

void CSoundAppUi::ConstructL()
    {
    BaseConstructL();

    iToneAdapter     = CToneAdapter::NewL(*this);

    iPlayerAdapter   = CPlayerAdapter::NewL(KSoundSampleFile, *this);

    iRecorderAdapter = CRecorderAdapter::NewL(*this);

    iAudioAdapter = iToneAdapter;

    iAppView = new (ELeave) CSoundView;
    iAppView->ConstructL();
    iAppView->NotifyStatusL(iAudioAdapter->Identify());
    iAppView->SetRect(ClientRect());

    AddToStackL(iAppView);
    
    __TEST_INVARIANT;
    }


CSoundAppUi::~CSoundAppUi()
    {
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
    __TEST_INVARIANT;

    // Handle non CBA commands
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
    case EEikCmdExit:
        Exit();
        break;
        //
    default:
        // Handle CBA commands which are state dependent
        if (IsCommandEnabled(aCommand))
            {
            switch (aCommand)
                {
            case ESoundCmdChange:
                ChangeAdapterL();
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
                __ASSERT_ALWAYS(EFalse, User::Panic(_L("CSoundAppUi"), KSoundPanicUnexpectedCommand));
                break;
                }
            }
        }

    iAudioAdapter->UpdateCBA();

    __TEST_INVARIANT;
    }


void CSoundAppUi::ChangeAdapterL()
    {
    __TEST_INVARIANT;

    if (iAudioAdapter == iToneAdapter)
        {
        iAudioAdapter = iPlayerAdapter;
        }
    else if (iAudioAdapter == iPlayerAdapter)
        {
        iAudioAdapter = iRecorderAdapter;
        }
    else if (iAudioAdapter == iRecorderAdapter)
        {        
        iAudioAdapter = iToneAdapter;
        }

    UpdateViewL();

    __TEST_INVARIANT;
    }

void CSoundAppUi::SetAdapterL(MAudioAdapter* aAudioAdapter)
    {
    __TEST_INVARIANT;

    iAudioAdapter = aAudioAdapter;

    UpdateViewL();

    __TEST_INVARIANT;
    }

void CSoundAppUi::UpdateViewL()
    {
    __TEST_INVARIANT;

    iAppView->NotifyStatusL(iAudioAdapter->Identify());
    
    iAppView->DrawNow();

    __TEST_INVARIANT;
    }


TBool CSoundAppUi::IsCommandEnabled(TInt aCommandId) const
    {
    __TEST_INVARIANT;

    return (iEikonEnv->AppUiFactory()->ToolBar()->IsCommandVisible(aCommandId));
    }


void CSoundAppUi::DisableCBACommand(TInt aCommandId)
    {
    __TEST_INVARIANT;

    iEikonEnv->AppUiFactory()->ToolBar()->MakeCommandVisible(aCommandId, EFalse);

    __TEST_INVARIANT;
    }

void CSoundAppUi::EnableCBACommand(TInt aCommandId)
    {
    __TEST_INVARIANT;

    iEikonEnv->AppUiFactory()->ToolBar()->MakeCommandVisible(aCommandId, ETrue);

    __TEST_INVARIANT;
    }

void CSoundAppUi::DrawCBA()
    {
    __TEST_INVARIANT;

    iEikonEnv->AppUiFactory()->ToolBar()->DrawNow();

    __TEST_INVARIANT;
    }

void CSoundAppUi::DynInitMenuPaneL(TInt aMenuId, CEikMenuPane* aMenuPane)
    {
    __TEST_INVARIANT;

    if (aMenuId == R_SOUND_SOUND_MENU)
        {
        iAudioAdapter->UpdateMenuL(aMenuPane);
        }

    __TEST_INVARIANT;
    }

void CSoundAppUi::__DbgTestInvariant() const
    {
    __ASSERT_DEBUG(iAppView != NULL, User::Panic(_L("CSoundAppUi"), KSoundPanicInvariant));

    __ASSERT_DEBUG(iToneAdapter != NULL, User::Panic(_L("CSoundAppUi"), KSoundPanicInvariant));

    __ASSERT_DEBUG(iPlayerAdapter != NULL, User::Panic(_L("CSoundAppUi"), KSoundPanicInvariant));

    __ASSERT_DEBUG(iRecorderAdapter != NULL, User::Panic(_L("CSoundAppUi"), KSoundPanicInvariant));

    __ASSERT_DEBUG((iAudioAdapter == iToneAdapter) || (iAudioAdapter == iPlayerAdapter) || (iAudioAdapter == iRecorderAdapter), 
                   User::Panic(_L("CSoundAppUi"), KSoundPanicInvariant));
    }









