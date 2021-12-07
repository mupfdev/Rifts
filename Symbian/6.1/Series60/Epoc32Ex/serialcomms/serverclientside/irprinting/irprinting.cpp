// IRPrinting.CPP
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


#include <e32base.h>
#include <e32test.h>
#include <e32svr.h>
#include <c32comm.h>
#include "f32file.h"

#include "CommonFiles.h"

// Device driver names
#if defined (__WINS__)
_LIT(PDD_NAME,"ECDRV");
_LIT(LDD_NAME,"ECOMM");
#else
_LIT(PDD_NAME,"EUART1");
_LIT(LDD_NAME,"ECOMM");
#endif

_LIT8(DATA_STRING,"Symbian EPOC infra red printing\n\r");

LOCAL_C void Init();

// Do the example 
LOCAL_C void doExampleL()
    {
	_LIT(KStatus0,"Connect to file server\n");
	_LIT(KStatus1,"Connect to comm server\n");
	_LIT(KStatus2,"Load IrCOMM.CSY\n");
	_LIT(KStatus3,"Open IrCOMM::0\n");
	_LIT(KStatus4,"Write to IrCOMM::0\n");
	_LIT(KStatus5,"Close IrCOMM::0\n");
	_LIT(KStatus6,"Close server connection\n");
	_LIT(KIrCOMM,"IrCOMM");
	_LIT(KIrCOMM0,"IrCOMM::0");

	const TTimeIntervalMicroSeconds32 KTimeOut(4000000);
	//time-out value

	console->Printf(KStatus0);
				// force a link to the file server
				// so that we're sure the loader 
				// will be present

	RFs f;
	User::LeaveIfError(f.Connect());
	f.Close();
				// Initialisation

	Init();
				
	RCommServ server;

				// Connect to the comm server
	console->Printf(KStatus1);
	server.Connect();

				// Load the IrCOMM comm module
				// C32 will automatically search \System\Libs
				// on all drives for IrCOMM.CSY
	console->Printf(KStatus2);
	TInt ret=server.LoadCommModule(KIrCOMM);
	
	//test(ret==KErrNone);
	User::LeaveIfError(ret);
		
	RComm commPort;
				// Open the IrCOMM port unit 0 (the only one supported)
				// Open port in exclusive mode because we don't 
				// have any access control code.
	console->Printf(KStatus3);
	ret=commPort.Open(server,KIrCOMM0,ECommExclusive);
	//test(ret==KErrNone);
	User::LeaveIfError(ret);

	TRequestStatus status;
				// Write to the IrCOMM port - the first write 
				// takes a long time as the IrDA connection is 
				// set up in response to this request. Subsequent 
				// writes to IrCOMM are very fast.
	console->Printf(KStatus4);
	commPort.Write(status,KTimeOut,DATA_STRING);
	User::WaitForRequest(status);

	//test(status.Int()==KErrNone);
	User::LeaveIfError(status.Int());
				// Close port
	console->Printf(KStatus5);
	commPort.Close();

	console->Printf(KStatus6);
	server.Close();
	}


LOCAL_C void Init()
//
// Initialisation code - loads the serial LDD and PDD
// starts the comm subsystem (for EPOC32 builds)
// On a full EPOC implementation, this code would not
// be required because higher level components (EIKON) 
// automatically start the services.
//
	{
	// Load the physical device driver
	// The OS will automatically append .PDD and 
	// search /System/Libs on all drives.

	TInt r=User::LoadPhysicalDevice(PDD_NAME);
	if (r != KErrNone && r!= KErrAlreadyExists)
		User::Leave(r);
	//test(r==KErrNone || r==KErrAlreadyExists);
	// Similarly for the Logical device driver
	r=User::LoadLogicalDevice(LDD_NAME);
	if (r != KErrNone && r != KErrAlreadyExists)
		User::Leave(r);
	//test(r==KErrNone|| r==KErrAlreadyExists);

#if defined (__EPOC32__)
	// For EPOC builds we need to start the comms subsystem
	// This call actually starts the comms server process
	r=StartC32();
	if (r != KErrAlreadyExists)
		User::LeaveIfError(r);
#endif
	}


