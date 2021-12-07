/* Copyright (c) 2001, Nokia. All rights reserved */

#include <avkon.hrh>
#include <eikmenup.h>

#include "EikonEnvironment.h"
#include "Dialer.pan"
#include "DialerAppUi.h"
#include "DialerAppView.h"
#include "Dialer.hrh"


_LIT (KTsyName,"phonetsy.tsy");
_LIT (KPhoneNumber,"01");
_LIT (KEmulatorError, "Dialing is not currently supported by this emulator.");


// ConstructL is called by the application framework
void CDialerAppUi::ConstructL()
    {
    BaseConstructL();

    //  Create the application view
    iAppView = CDialerAppView::NewL(ClientRect());    

    AddToStackL(iAppView);

    }

CDialerAppUi::CDialerAppUi()
    {
    //  Implementation not required
    }

CDialerAppUi::~CDialerAppUi()
    {
    if (iAppView)
		{
		RemoveFromStack(iAppView);

		delete iAppView;
		iAppView = NULL;
		}
    }

// Handle any menu commands
void CDialerAppUi::HandleCommandL(TInt aCommand)
    {
    switch(aCommand)
        {
        case EAknSoftkeyExit:
            Exit();
            break;

        case EDialerDial:
            {
            TRAPD(err, DialNumberL(KPhoneNumber); );
            if (err)
                {
                User::InfoPrint(_L("Error dialing"));
                }
            }
            break;

        default:
            User::Panic (_L("Dialer"), EDialerBasicUi);
            break;
        }
    }


void CDialerAppUi::DialNumberL(const TDesC& aPhoneNumber)
	{
	// emulator does not support dialing
#if __WINS__
	NEikonEnvironment::MessageBox (KEmulatorError);
#else

	//Create a connection to the tel server
	RTelServer server;
	CleanupClosePushL(server);
	User::LeaveIfError(server.Connect());

	//Load in the phone device driver
	User::LeaveIfError(server.LoadPhoneModule(KTsyName));
	
	//Find the number of phones available from the tel server
	TInt numberPhones;
	User::LeaveIfError(server.EnumeratePhones(numberPhones));

	//Check there are available phones
	if (numberPhones < 1)
		{
		User::Leave(KErrNotFound);
		}

	//Get info about the first available phone
	RTelServer::TPhoneInfo info;
	User::LeaveIfError(server.GetPhoneInfo(0, info));

	//Use this info to open a connection to the phone, the phone is identified by its name
	RPhone phone;
	CleanupClosePushL(phone);
	User::LeaveIfError(phone.Open(server, info.iName));

	//Get info about the first line from the phone
	RPhone::TLineInfo lineInfo;
	User::LeaveIfError(phone.GetLineInfo(0, lineInfo));

	//Use this to open a line
	RLine line;
	CleanupClosePushL(line);
	User::LeaveIfError(line.Open(phone, lineInfo.iName));

	//Open a new call on this line
	TBuf <100> newCallName;
	RCall call;
	CleanupClosePushL(call);
	User::LeaveIfError(call.OpenNewCall(line, newCallName));

	//newCallName will now contain the name of the call
	User::LeaveIfError(call.Dial(aPhoneNumber));

	//Close the phone, line and call connections and remove them from the cleanup stack
	//NOTE: This does not hang up the call
	CleanupStack::PopAndDestroy(3);//phone, line, call

	//Unload the phone device driver
	User::LeaveIfError(server.UnloadPhoneModule(KTsyName));

	//Close the connection to the tel server and remove it from the cleanup stack
	CleanupStack::PopAndDestroy(&server);

#endif
	}



