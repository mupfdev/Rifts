// GlassTerm.CPP
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

// Purpose: Glass Term : read/Write from keyboard/serial port : example code for SDK

// This uses the first serial port on the system, and offers a choice between different
// handshaking modes.  All control characters apart from carriage returns and line feeds are
// displayed on the screen with ^ carets in from of the the ASCII equivalent (so tab = ^I)

// The ESC key is used to end the program

// Note :

// In order for this program to do anything, the serial port should be connected to something.
// A modem is of course quite suitable.  In the absence of a modem, a loopback plug with the
// receive and transmit lines connected will echo all serial port output to the screen.  In
// the absence of a loopback plug, a bent paper clip or somethings similar connecting pins 2 and 3
// on any 25 or 9 way serial connector will do exactly the same thing.  This last suggestion
// is something that is carried out entirely at your own risk, and you should be very careful
// neither to connect any other pins by mistake nor to push the paper clip in too far !

// If using the bent paper clip, you'll find that in order for the hardware handshaking option
// to work, a second bent paper clip connecting pins 4 and 5 on a 25-way connector or pin 7 and 8
// on a 9-way connector will also be needed - this second paper clip is needed to connect RTS to CTS

// Note: this sample program now shows how to support infra-red as well
// as RS232 and also systems with multiple serial ports and multiple
// possible CSYs.

#include <e32base.h>
#include <e32test.h>
#include <e32svr.h>
#include <c32comm.h>
#include <f32file.h>

#include "CommonFiles.h"

// first define our device driver names

_LIT(LDD_NAME,"ECOMM");

#if defined (__WINS__)
_LIT(PDD_NAME,"ECDRV");
#else
_LIT(PDD_NAME,"EUART1");
#endif

// next define an arbitrary buffer size and tenth of a second in microseconds

const TInt KBufSize (512);
const TInt KTenthSecond (100000);

// short literals for use in doExampleL() declared at file scope
_LIT(KMessage2,"%c\n");
_LIT(KMessage14,"^%c");
_LIT(KMessage15,"%c");
_LIT(KColons,"::");

// utility function to print received text
void printReceivedText(TDes8& localInputBuffer,TInt numberRead);

LOCAL_C void doExampleL ()
	{
	_LIT(KMessage0,"Select S for RS232 Serial or R for InfraRed port : ");
	_LIT(KMessage1,"Select 0 for no handshaking, 1 for CTS/RTS and 2 for XON/XOFF :");
	_LIT(KMessage4,"Loading device drivers\n");
	_LIT(KMessage5,"Starting comms server\n");
	_LIT(KMessage6,"Connecting to comms server\n");
	_LIT(KMessage7,"Loading %S.CSY module\n");
	_LIT(KMessage8,"%S has %S available as %S::%u to %S::%u\n");
	_LIT(KMessage9,"Opened %S\n");
	_LIT(KMessage10,"Configuring Serial port for 19200 bps 8 bits no parity 1 stop\n");
	_LIT(KMessage11,"Powering up port\n");
	_LIT(KMessage12,"\nDisconnecting\n");
	_LIT(KMessage13,"\nWrite Failed %d\n");
	_LIT(KMessage16,"\nRead failed %d\n");
	_LIT(KMessage17,"Closed %S\n");
	_LIT(KMessage18,"Closing server connection\n");
	_LIT(KMessage19,"Comms server reports we have %u comms modules loaded\n");
	_LIT(KMessage20,"Using the lowest %S out of %S::%u to %S::%u\n");
	
	_LIT(KPanic,"StraySignal");
	_LIT(RS232,"ECUART");
	_LIT(IRCOMM,"IRCOMM");

	TBuf16 < 6 > csyName;

	TUint8 csyMode;
	const TUint8 mask=0xdf; // this mask 0xdf turns lower to upper case

	console->Printf (KMessage0);
	do
		csyMode = STATIC_CAST(TUint8,console->Getch () & mask); 
	while ((csyMode < 'R') || (csyMode > 'S'));
	console->Printf (KMessage2, csyMode);

	if (csyMode=='S')
		csyName.Copy(RS232);
	else
		csyName.Copy(IRCOMM);



	TKeyCode handshakingMode;
	console->Printf (KMessage1);
	do
		handshakingMode = console->Getch ();
	while ((handshakingMode < '0') || (handshakingMode > '2'));
	console->Printf (KMessage2, handshakingMode);


	// Under WINS we must force a link to the file server
	// so that we're sure we'll be able to load the device drivers.
	// On a MARM implementation, this code would not
	// be required because higher level components (EIKON)
	// will automatically have started the services.

#if defined (__WINS__)
	_LIT(KMessage3,"Connect to file server\n");
	console->Printf (KMessage3);
	RFs fileServer;
	User::LeaveIfError (fileServer.Connect ());
	fileServer.Close ();
#endif


	// Load the physical and logical device drivers
	// EPOC32 will automatically append .PDD and .LDD and
	// search /System/Libs on all drives starting from C:
	// If EIKON has done this, they'll already exist -
	// no harm will have been done

	console->Printf (KMessage4);
	TInt r = User::LoadPhysicalDevice (PDD_NAME);
	if (r != KErrNone && r != KErrAlreadyExists)
		User::Leave (r);
	r = User::LoadLogicalDevice (LDD_NAME);
	if (r != KErrNone && r != KErrAlreadyExists)
		User::Leave (r);

	// Both WINS and EIKON will have started the comms server process.
	// (this is only really needed for ARM hardware development racks)

#if !defined (__WINS__)
	console->Printf (KMessage5);
	r = StartC32 ();
	if (r != KErrNone && r != KErrAlreadyExists)
		User::Leave (r);
#endif

	// Now (at last) we can actually connect to the comm server

	console->Printf (KMessage6);
	RCommServ server;
	User::LeaveIfError (server.Connect ());

	// Load the CSY module
	// EPOC/32 will automatically search \System\Libs
	// on all drives starting from C:

	console->Printf (KMessage7,&csyName);
	r = server.LoadCommModule (csyName);
	User::LeaveIfError (r);

	// if we know our machine architecture we can just go ahead and open (say) COMM::0
	// however, for machine independence we are better off looking up that information

	// the oddly-named NumPorts function actually tells us how many CSYs are loaded
	// this isn't 0 since we've just loaded one ...

	TInt numPorts;
	r = server.NumPorts (numPorts);
	User::LeaveIfError (r);
	console->Printf (KMessage19,numPorts);

	// we can get port information for each loaded CSY in turn (note we
	// index them from 0) - we can find out the number of ports supported
	// together with their names, and their description. The information is
	// returned in a TSerialInfo structure together with the name of the
	// CSY that we've indexed

	TSerialInfo portInfo;
	TBuf16 < 12 > moduleName;

	for (TInt index=0 ; index < numPorts ; index++)
		{
		r = server.GetPortInfo (index, moduleName, portInfo);
		User::LeaveIfError (r);
		console->Printf (KMessage8,
							  &moduleName,
							  &portInfo.iDescription,
							  &portInfo.iName,
							  portInfo.iLowUnit,
							  &portInfo.iName,
							  portInfo.iHighUnit);
		}

	// However, we are really only interested in using the CSY that we've
	// just loaded up ourselves.  We could find out its portInfo by
	// comparing the moduleName returned by the version of GetPortInfo we
	// just used to the name of the CSY we loaded, but there's a better
	// version of GetPortInfo we can use, which just takes the name of a CSY
	// as a parameter. We'd expect to find this informtion is an exact 
	// duplicate of the indexed portInfo for the last loaded CSY
	// Our example code will use the lowest possible port (why not?)

	r = server.GetPortInfo (csyName, portInfo);
	console->Printf (KMessage20,
						  &portInfo.iDescription,
						  &portInfo.iName,
						  portInfo.iLowUnit,
						  &portInfo.iName,
						  portInfo.iHighUnit);

	// Now let's use a few EPOC32 functions to construct a descriptor for the
	// name of the lowest port our CSY supports -
	// The name can can be as long as a TSerialInfo.iName plus a
	// couple of colons and digits

	TBuf16 < KMaxPortName + 4 > portName; // declare an empty descriptor buffer
	portName.Num (portInfo.iLowUnit);	 // put in the port number in ASCII
	portName.Insert (0, KColons);	  // stick in a couple of colons
	portName.Insert (0, portInfo.iName); // and lead off with the iName

	// and at last we can open the first serial port,which we do here in exclusive mode

	RComm commPort;
	console->Printf (KMessage9, &portName);
	r = commPort.Open (server, portName, ECommExclusive);
	User::LeaveIfError (r);

	// Now we can configure our serial port
	// we want to run it at 19200 bps 8 bits no parity (why not?)
	// so maybe we ought to get of its capabilities and check it can
	// do what we want before going ahead

	TCommCaps ourCapabilities;
	commPort.Caps (ourCapabilities);

	if (((ourCapabilities ().iRate & KCapsBps19200) == 0) ||
		 ((ourCapabilities ().iDataBits & KCapsData8) == 0) ||
		 ((ourCapabilities ().iStopBits & KCapsStop1) == 0) ||
		 ((ourCapabilities ().iParity & KCapsParityNone) == 0))
		User::Leave (KErrNotSupported);

	console->Printf (KMessage10);

	TCommConfig portSettings;
	commPort.Config (portSettings);
	portSettings ().iRate = EBps19200;
	portSettings ().iParity = EParityNone;
	portSettings ().iDataBits = EData8;
	portSettings ().iStopBits = EStop1;

	// as well as the physical characteristics, we need to set various logical ones
	// to do with handshaking, behaviour of reads and writes and so so

	portSettings ().iFifo = EFifoEnable;
	if (handshakingMode == '2')
		portSettings ().iHandshake = (KConfigObeyXoff | KConfigSendXoff); // for xon/xoff
	else if (handshakingMode == '1')
		portSettings ().iHandshake = (KConfigObeyCTS | KConfigFreeRTS);	// for cts/rts
	else
		portSettings ().iHandshake = KConfigFailDSR;	// for no handshaking

	portSettings ().iTerminator[0] = 10;
	portSettings ().iTerminatorCount = 1;		  // so that we terminate a read on each line feed arrives

	r = commPort.SetConfig (portSettings);
	User::LeaveIfError (r);

	// now turn on DTR and RTS, and set our buffer size

	commPort.SetSignals (KSignalDTR, 0);
	commPort.SetSignals (KSignalRTS, 0);
	TInt curlenth = commPort.ReceiveBufferLength ();
	commPort.SetReceiveBufferLength (4096);
	curlenth = commPort.ReceiveBufferLength ();

	// now we can start using the port

	TKeyCode key;
	TPtrC8 outputByte ((TUint8 *) & key, 1);
	TBuf8 < KBufSize > localInputBuffer;
	TRequestStatus readStat, keyStat;

	// a null read or write powers up the port

	console->Printf (KMessage11);
	commPort.Read (readStat, localInputBuffer, 0);
	User::WaitForRequest(readStat);
	r = readStat.Int ();
	User::LeaveIfError (r);

	// now the main glass terminal
	// this could be either an active object
	// or, as in this case, an asynchronous loop

	// note that we use Read() with a timeout - we have configured the port so that
	// line feeds trigger early completion of reads, which optimizes text based reception.

	// if we'd used the request commPort.ReadOneOrMore (readStat, localInputBuffer) we
	// could well have ended up calling the server once per character (up to 2000 times
	// per second!) so a regular re-issuing of the read request 10 times per second is no
	// big deal (to retain echoing of keyboard characters)


	console->Read (keyStat);
	commPort.Read (readStat, KTenthSecond, localInputBuffer);
	for (;;)
		{
		User::WaitForRequest (readStat, keyStat);

		// From keyboard

		if (keyStat != KRequestPending)
			{
			key = console->KeyCode ();

			if (key == 0x1b)		 // ESCAPE - Disconnect
				{
				console->Printf (KMessage12);
				commPort.ReadCancel ();	  // Cancel Read
				User::WaitForRequest (readStat);
				break;
				}

			if (key < 256)			// ASCII - Write to serial port
				{
				TRequestStatus stat;
				commPort.Write (stat, outputByte);
				User::WaitForRequest (stat);
				r = stat.Int ();
				if (r != KErrNone)  // Write has failed for some reason
					console->Printf (KMessage13, r);
				}

			console->Read (keyStat);		 // When complete, read again
			}

		// From serial port - we display printable characters, line feeds and carriage returns
		// but control characters are displayed as a caret ^ followed by the printable equivalent

		// timeout errors are OK here, but we do need to check that there really is data in the
		// buffer before printing it to the screen as we might have timed out with no data

		else if (readStat != KRequestPending)
			{
			if (readStat == KErrNone || readStat == KErrTimedOut)
				{
				// check descriptor and print any characters
				TInt numberRead = localInputBuffer.Length ();
				if (numberRead != 0) 
					printReceivedText(localInputBuffer,numberRead);
				else
				// else check the input buffer and print any characters
					{
					numberRead = commPort.QueryReceiveBuffer();
					if (numberRead != 0)
						{
						commPort.ReadOneOrMore(readStat, localInputBuffer);
						User::WaitForRequest (readStat);
						if (readStat == KErrNone) printReceivedText(localInputBuffer,numberRead);
						}
					}
				}
			else	 // An error occured on reading
				console->Printf (KMessage16, readStat.Int ());
			commPort.Read (readStat, KTenthSecond, localInputBuffer);
			}

		// help !! a request we can't cater for

		else
			{
			User::Panic (KPanic, 0);
			}

		}

	// Close port

	commPort.Close ();
	console->Printf (KMessage17, &portName);
	console->Printf (KMessage18);
	server.Close ();
	}

void printReceivedText(TDes8& localInputBuffer,TInt numberRead)
	{
	TUint8 *nextByte = &localInputBuffer[0];
	for (int i = 0; i < numberRead; i++, nextByte++)
		{
		if ((*nextByte < 32) && (*nextByte != 10) && (*nextByte != 13))
			console->Printf (KMessage14, (*nextByte) + 64);
		else
			console->Printf (KMessage15, *nextByte);
		}
	}
