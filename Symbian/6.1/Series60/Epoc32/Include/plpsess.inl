// PLPSESS.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

//////////////////////////////////////////////////////////////////////////////
//
// TRemoteLinkStatus
//
//////////////////////////////////////////////////////////////////////////////

inline TRemoteLinkStatus::TRemoteLinkStatus()
    { iStatus=EDisabled; iRemoteVersion=0; }

//////////////////////////////////////////////////////////////////////////////
//
// RRemoteLink Deprecated methods
//
//////////////////////////////////////////////////////////////////////////////

inline TInt RRemoteLink::Enable(TBps aBaud, const TDesC& aPort, const TDesC& aModule, TBool /*aLowPowerMode*/)
//
// Set up the RRemoteLink configuration parameters and initiate a connection
//
	{

	TPlpConfigPkgSerial pkg(aBaud,aPort,aModule);
	TInt ret = SetConfig(pkg);
	return ret;
	}

inline TInt RRemoteLink::Disable()
//
// Disable the remote link
//
	{

	TInt ret = Disconnect();
	return ret;
	}

inline TInt RRemoteLink::Config(TBps* aBaud /*=NULL*/, TDesC* aPort /*=NULL*/, TDesC* aModule /*=NULL*/, TBool* /*aLowPowerMode*/)
//
// Read the current RRemoteLink configuration
//
	{

	TPlpConfigPkgSerial pkg;
	TInt ret = Config(pkg);
	if (ret!=KErrNone)
		return ret;

	if (aBaud)
		*aBaud = pkg.Baud();
	if (aPort)
		*(TDes*)aPort = pkg.PortName();
	if (aModule)
		*(TDes*)aModule = pkg.ModuleName();
	return KErrNone;
	}

inline TInt RRemoteLink::LoadLocalServer(TPlpServiceName& aResult, const TDesC& aFileName, const TDesC& aArgs /*=TPtrC()*/, TInt aReserved /*=0*/)
//
// Load a local server
//
	{

	TRequestStatus status;
	LoadLocalServer(status,aResult,aFileName,aArgs,aReserved);
	User::WaitForRequest(status);
	return status.Int();
	}

inline TInt RRemoteLink::UnloadLocalServer(const TDesC& aFileName)
//
// Unload the local server
//
	{

	TRequestStatus status;
	UnloadLocalServer(status,aFileName);
	User::WaitForRequest(status);
	return status.Int();
	}

inline TInt RRemoteLink::EnableFileAccess(TBool /*aEnable=ETrue*/)
//
// Dummy implementation
//
	{

	return KErrNone;
	}

inline void RRemoteLink::WaitForConnect(TRequestStatus& aStatus, TRemoteLinkStatusBuf& aBuf)
//
// Wait for connection to complete
//
	{

	Connect(aStatus,aBuf);
	}
