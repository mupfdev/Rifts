/* Copyright (c) 2001, Nokia. All rights reserved */

#include <eikgted.h>
#include "SocketsEngine.h"
#include "TimeOutTimer.h"
#include "SocketsReader.h"
#include "SocketsWriter.h"
#include "Sockets.pan"
#include "UINotifier.h"

const TInt CSocketsEngine::KTimeOut = 30000000; // 30 seconds time-out

_LIT(KDefaultServerName, "127.0.0.1");
const TInt CSocketsEngine::KDefaultPortNumber = 7;

CSocketsEngine* CSocketsEngine::NewL(MUINotifier& aConsole)
    {
	CSocketsEngine* self = CSocketsEngine::NewLC(aConsole);
	CleanupStack::Pop(self);
	return self;
    }

	
CSocketsEngine* CSocketsEngine::NewLC(MUINotifier& aConsole)
    {
	CSocketsEngine* self = new (ELeave) CSocketsEngine(aConsole);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
    }


CSocketsEngine::CSocketsEngine(MUINotifier& aConsole)
: CActive(EPriorityStandard),
  iConsole(aConsole),
  iPort(KDefaultPortNumber),
  iServerName(KDefaultServerName)
    {
    }


CSocketsEngine::~CSocketsEngine()
    {
    Cancel();

    delete iSocketsReader;
    iSocketsReader = NULL;

    delete iSocketsWriter;
    iSocketsWriter = NULL;

    delete iTimer;
    iTimer = NULL;

    iSocketServ.Close();
    }


void CSocketsEngine::ConstructL()
    {
	ChangeStatus(ENotConnected);

    // Start a timer
	iTimer = CTimeOutTimer::NewL(EPriorityHigh, *this);
	CActiveScheduler::Add(this); 

	// Open channel to Socket Server
	User::LeaveIfError(iSocketServ.Connect());

    // Create socket read and write active objects
	iSocketsReader = CSocketsReader::NewL(*this, iSocket);
	iSocketsWriter = CSocketsWriter::NewL(*this, iSocket);
    }

void CSocketsEngine::ConnectL()
    {
    // Initiate connection process
    if (iEngineStatus == ENotConnected)
        {
        TInetAddr addr;
        if (addr.Input(iServerName) == KErrNone)
            {
            // server name is already a valid ip address
            ConnectL(addr.Address());
            }
        else // need to look up name using dns
            {
	        // Initiate DNS
	        User::LeaveIfError(iResolver.Open(iSocketServ, KAfInet, KProtocolInetUdp));
	        // DNS request for name resolution
	        iResolver.GetByName(iServerName, iNameEntry, iStatus);
	        
	        ChangeStatus(ELookingUp);
	        // Request time out
	        iTimer->After(KTimeOut);
	        SetActive();
            }
        }
    }

void CSocketsEngine::ConnectL(TUint32 aAddr) // <a name="ConnectL32">
    {
    // Initiate attempt to connect to a socket by IP address	
    if (iEngineStatus == ENotConnected)
        {
        // Open a TCP socket
        User::LeaveIfError(iSocket.Open(iSocketServ, KAfInet, KSockStream, KProtocolInetTcp));

        // Set up address information
	    iAddress.SetPort(iPort);
	    iAddress.SetAddress(aAddr);

        // Initiate socket connection
	    iSocket.Connect(iAddress, iStatus);
	    ChangeStatus(EConnecting);
        
        // Start a timeout
	    iTimer->After(KTimeOut);

	    SetActive();
        }
    }

void CSocketsEngine::Disconnect()
    {
    __ASSERT_ALWAYS(iEngineStatus == EConnected, User::Panic(KPanicSocketsEngine, ESocketsBadState));

	// cancel all outstanding operations
    // since we are connected, the only possibilities are read and write
    iSocketsReader->Cancel();
    iSocketsWriter->Cancel();

	iSocket.Close();
	ChangeStatus(ENotConnected);
    }

// from CActive
void CSocketsEngine::DoCancel()
    {
    iTimer->Cancel();

    // Cancel appropriate request to socket
    switch (iEngineStatus)
        {
        case EConnecting:
            iSocket.CancelConnect();
            iSocket.Close();
            break;
        case ELookingUp:
            // Cancel look up attempt
            iResolver.Cancel();
            iResolver.Close();
            break;
	    default:
            User::Panic(KPanicSocketsEngine, ESocketsBadStatus);
            break;
	    }

    ChangeStatus(ENotConnected);
    }

void CSocketsEngine::WriteL(const TDesC8& aData)
    {
    // Write data to socket
	if (iEngineStatus == EConnected)
        {
        iSocketsWriter->IssueWriteL(aData);
        }
    }
	
void CSocketsEngine::Read()
    {
    // Initiate read of data from socket
	if ((iEngineStatus == EConnected) && (!iSocketsReader->IsActive())) 
        {
        iSocketsReader->Start();
        }
    }

// from CActive
void CSocketsEngine::RunL()
    {
    // Active object request complete handler.
    // iEngineStatus flags what request was made, so its
    // completion can be handled appropriately
	iTimer->Cancel(); // Cancel TimeOut timer before completion

	switch(iEngineStatus)
	    {
	    case EConnecting:
		    // IP connection request
		    if (iStatus == KErrNone)
		        // Connection completed successfully
		        {
			    ChangeStatus(EConnected);
			    Read(); //Start CSocketsReader Active object
		        }
		    else
		        {
			    iSocket.Close();
			    iConsole.ErrorNotify(_L("CSocketsEngine\nConn. failed"), iStatus.Int());
                ChangeStatus(ENotConnected);
                }
		    break;
	    case ELookingUp:
		    iResolver.Close();
		    if (iStatus == KErrNone)
		        {
    		    // DNS look up successful
			    iNameRecord = iNameEntry();
			    // Extract domain name and IP address from name record
			    Print(_L("Domain name = "));
			    Print(iNameRecord.iName);
                TBuf<15> ipAddr;
			    TInetAddr::Cast(iNameRecord.iAddr).Output(ipAddr);
			    Print(_L("\r\nIP address = "));
			    Print(ipAddr);
                Print(_L("\r\n"));
			    // And connect to the IP address
                ChangeStatus(ENotConnected);
			    ConnectL(TInetAddr::Cast(iNameRecord.iAddr).Address());
		        }
		    else
		        {	
                // DNS lookup failed
			    iConsole.ErrorNotify(_L("CSocketsEngine\nDNS lookup failed"), iStatus.Int());
                ChangeStatus(ENotConnected);
		        }
		    break;
	    default:
            User::Panic(KPanicSocketsEngine, ESocketsBadStatus);
            break;

	    };
    }

void CSocketsEngine::TimerExpired()
    {
	Cancel();
	iConsole.ErrorNotify(_L("CSocketsEngine\nTimed out"), KErrTimedOut);
    }

void CSocketsEngine::ReportError(MEngineNotifier::TErrorType aErrorType, TInt aErrorCode)
    {
    // No recovery or retries are attempted in this example so we just
    // disconnect and inform the user
    Disconnect();

    switch (aErrorType)
        {
        case MEngineNotifier::EDisconnected:
	        iConsole.ErrorNotify(_L("CSocketsEngine\nDisconnected"), aErrorCode);
            break;
        case MEngineNotifier::EGeneralReadError:
	        iConsole.ErrorNotify(_L("CSocketsEngine\nRead Error"), aErrorCode);
            break;
        case MEngineNotifier::ETimeOutOnWrite:
	        iConsole.ErrorNotify(_L("CSocketsEngine\nTime Out on write"), aErrorCode);
            break;
        case MEngineNotifier::EGeneralWriteError:
	        iConsole.ErrorNotify(_L("CSocketsEngine\nWrite Error"), aErrorCode);
            break;
        default:
            User::Panic(KPanicSocketsEngine, ESocketsBadStatus);
            break;
        }
    }

void CSocketsEngine::ResponseReceived(const TDesC8& aBuffer)
    {
    iConsole.PrintNotify(aBuffer);
    }

void CSocketsEngine::ChangeStatus(TSocketsEngineState aNewStatus)
    {
    // Update the status (and the status display)
    switch (aNewStatus)
        {
        case ENotConnected:
            iConsole.SetStatus(_L("Not connected"));
            break;
        case EConnecting:
            iConsole.SetStatus(_L("Connecting"));
            break;
        case EConnected:
            iConsole.SetStatus(_L("Connected"));
            break;
        case ELookingUp:
            iConsole.SetStatus(_L("Looking up"));
            break;
        default:
            User::Panic(KPanicSocketsEngine, ESocketsBadStatus);
            break;
        }

    iEngineStatus = aNewStatus;
    }

void CSocketsEngine::Print(const TDesC& aDes)
    {
    // Print some text on the console
    iConsole.PrintNotify(aDes, CEikGlobalTextEditor::EItalic);
    }

void CSocketsEngine::SetServerName(const TDesC& aName)
    {
    iServerName.Copy(aName);
    }

const TDesC& CSocketsEngine::ServerName() const
    {
    return iServerName;
    }

void CSocketsEngine::SetPort(TInt aPort)
    {
    iPort = aPort;
    }

TInt CSocketsEngine::Port() const
    {
    return iPort;
    }

TBool CSocketsEngine::Connected() const
    {
    return (iEngineStatus == EConnected);
    }
