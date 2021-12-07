/* Copyright (c) 2001, Nokia. All rights reserved */
#include <eiktbar.h>
#include <eikenv.h>
#include <w32adll.h>
#include <avkon.hrh>
#include "animation.pan"
#include "animationdocument.h"
#include "animationappui.h"
#include "animationappview.h"
#include "animation.hrh"
#include "clientdll.h"
#include "clientimagecommander.h"


// local constants

// the location of the animation server changes in the emulator and target builds
#if defined(__WINS__)
_LIT(KServerDllFilename, "Z:\\system\\apps\\animation\\ANIMATION_SERVER");
#else
_LIT(KServerDllFilename, "C:\\system\\apps\\animation\\ANIMATION_SERVER");
#endif




// UI constructor list, required to initialise R types
CAnimationAppUi::CAnimationAppUi(RWsSession& aSession)
    : CAknAppUi(),                                  // Base class constructor
      iClientDll(aSession),                        // Animation client dll
      iClientCommander(iClientDll)                    // Animation client object
    {
    }


void CAnimationAppUi::ConstructL()
    {
    // Perform the base class construction
    BaseConstructL();

    // Create an application view
    iAppView = CAnimationAppView::NewL(ClientRect());    

    // Allow the appview to receive keyboard input
    AddToStackL(iAppView);

    // Initialise the RClientDll class
    SetupClientDllL();

    // Initialise the RImageCommander class
    SetupImageCommanderL();    
    }

void CAnimationAppUi::SetupClientDllL()
    {
    // Create the server dll filename
    TFileName serverDllFilename(KServerDllFilename);

    // Load the animation server, if an error occurs then 
    // let higher level handle the problem
    User::LeaveIfError(iClientDll.Load(serverDllFilename));
    }

void CAnimationAppUi::SetupImageCommanderL()
    {
    // Tell client to construct a server side object
    TBuf8<1> params(TInt8(0));
    RWindowBase* windowBase = iAppView->DrawableWindow();
    iClientCommander.ImageConstruct(*windowBase, RImageCommander::KAnimationSquare, params);
    }


CAnimationAppUi::~CAnimationAppUi()
    {
    // remove the application view from the stack
    RemoveFromStack(iAppView);

    // Close the animation object
    iClientCommander.Close ();

    // Close the animation server
    iClientDll.Close();

    // Delete and NULL the application view
    delete iAppView;
    iAppView = NULL;
    }

void CAnimationAppUi::HandleCommandL(TInt aCommand)
    {
    switch(aCommand)
        {
    // Exit the application
	case EEikCmdExit:
    case EAknSoftkeyExit:
        Exit();
        break;

    // Ask the animation to do something, in this case, reset
    case EEikCmdReset:
        iClientCommander.ImageCommand(RImageCommander::KAnimationReset);
        break;

    default:
        User::Panic(KAnimation, EPanicAnimationUi);
        break;
        }
    }

