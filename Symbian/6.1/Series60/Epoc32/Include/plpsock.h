// PLPSOCK.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__PLPSOCK_H__)
#define __PLPSOCK_H__

#if !defined(__ES_SOCK_H__)
#include <es_sock.h>
#endif

#if !defined(__PLPLINK_H__)
#include <plplink.h>
#endif

#if !defined(__PLPSESS_H__)
#include <plpsess.h>
#endif

const TUint KFamilyPlp               = 273;
const TUint KProtocolPlpTransport    = 4;
const TUint KProtocolPlpLink         = 11;
const TUint KProtocolPlpLoopback     = 12;

const TUint KPlpInfoIoctl                = 30;
const TUint KPlpSerialConfig             = 31;
const TUint KPlpSerialSetConfig          = 32;
const TUint KPlpLinkReset                = 33;
const TUint KPlpLinkStop                 = 34;
const TUint KPlpLinkStart                = 35;
const TUint KPlpLinkInfo                 = 36;
const TUint KPlpProvdSetMtuSize          = 37;
const TUint KPlpProvdMtuSize             = 38;
const TUint KPlpBinderNumber             = 39;
const TUint KPlpBinderSetLocalVersion    = 40;
const TUint KPlpBinderConfig             = 41;
const TUint KPlpBinderList               = 42;
const TUint KPlpBinderSetActivityMinTime = 43;
const TUint KPlpProvdLogonLink           = 44;
const TUint KPlpProvdLogoffLink          = 45;
const TUint KPlpProvdIsLoggingLink       = 46;
const TUint KPlpLinkIsStarted            = 47;
const TUint KPlpLinkTryConnect           = 48;

const TUint KPlpPortAny           = 0;

// Defined in PLPSESS.H
// const TUint KPlpInterfaceAny      = 0;
// const TUint KPlpInterfaceDevice0  = 1;
// const TUint KPlpInterfaceDevice1  = 2;
// const TUint KPlpInterfaceLoopback = 3;

//////////////////////////////////////////////////////////////////////////////
//
// TPLPAddr - PLP socket address structure
//
//////////////////////////////////////////////////////////////////////////////

class TPlpAddr : public TSockAddr
    {
public:
    inline TPlpAddr(TUint aInterface, const TDesC8 &aDes=TPtrC8(), TUint aPort=KPlpPortAny);
    inline TPlpAddr();
    inline TUint Interface() const;
    inline void SetInterface(TUint aInterface);
    inline void SetServiceName(const TDesC8 &aDes);
    inline TPtrC8 ServiceName() const;
    };

//////////////////////////////////////////////////////////////////////////////
//
// Data structures for socket options
//
//////////////////////////////////////////////////////////////////////////////

enum TPlpEvent
    {
    EPlpInitialized, EPlpError, EPlpVerOk, 
    EPlpVerInvalid, EPlpSignalHigh, EPlpActivity
    };
    
class TPlpBinderInfo
    {

public:
    TUint iNum;
    TInt iLastNetError;
    TPlpEvent iEvent;
    TUint8 iRemoteVersionNumber;
    TUint8 iLocalVersion;
    TUint iLocalStartDate;
    TUint iRemoteStartDate;
    TUint iActivityMinTime;
    };

class TPlpSerialConfig
    {
public:
    TPlpLinkConfig iLinkConfig;
    TCommAccess iAccess;			// Access type.
    TBufC<KMaxPortName> iPort;		// Port name.
    TBufC<KMaxFileName> iModule;	// UART module name.
    };

typedef TPckgBuf<TPlpSerialConfig> TPlpSerialConfigBuf;
typedef TPckgBuf<TPlpBinderInfo> TPlpBinderInfoBuf;
typedef TPckgBuf<TPlpLinkInfo> TPlpLinkInfoBuf;

#include "plpsock.inl"

#endif __PLPSOCK_H__
