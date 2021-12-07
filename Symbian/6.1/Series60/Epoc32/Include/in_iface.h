// IN_IFACE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__IN_IFACE_H__)
#define __IN_IFACE_H__

#if !defined(__IN_SOCK_H__)
#include <in_sock.h>
#endif

#if !defined(__NIFVAR_H__)
#include <nifvar.h>
#endif

// Feature Flags
const TUint KIfIsLoopback			= 0x00000001;	// Is a loopback interface
const TUint KIfIsPointToPoint		= 0x00000002;	// Is single point to point
const TUint KIfCanBroadcast			= 0x00000004;	// Supports broadcasting
const TUint KIfCanMulticast			= 0x00000008;	// Supports multicasting
const TUint KIfCanSetMTU			= 0x00000010;	// Can have its MTU	set
const TUint KIfHasHardwareAddr		= 0x00000020;	// Has a hardware address (ie needs ARP)
const TUint KIfCanSetHardwareAddr	= 0x00000040;	// Can have its hardware address changed
const TUint KIfIsDialup				= 0x00000080;	// Dialup interface

// Control options level received by network interfaces
const TUint KSOLInterface			= 0x203;

// Option names
const TUint KSoIfInfo				= 0x101;		// Get Interface Information
const TUint KSoIfHardwareAddr		= 0x102;		// Get Hardware Address
const TUint KSoIfConfig				= 0x103;		// Get Network parameters
const TUint KSoIfCompareAddr		= 0x104;		// Compare address with one passed in

const TUint KMaxInterfaceName=32;
typedef TBuf<KMaxInterfaceName> TInterfaceName;

// Information which allows IP to enter route table entries
class TInetIfConfig
	{
public:
	TInetAddr iAddress;
	TInetAddr iNetMask;
	TInetAddr iBrdAddr;
	TInetAddr iDefGate;
	TInetAddr iNameSer1;
	TInetAddr iNameSer2;
	};

// Socket option structure for KSoIfInfo
class TSoIfInfo
	{
public:
	TUint iFeatures;		// Feature flags
	TInt iMtu;				// Max frame size
	TInt iSpeedMetric;		// Indication of performance, approx to Kbps
	TInterfaceName iName;
	};

// Socket option structure for KSoIfHardwareAddr
class TSoIfHardwareAddr
	{
public:
	TSockAddr iHardwareAddr;
	};

class TSoIfConfigBase
	{
public:
	TUint iFamily;
	};

class TSoInetIfConfig : public TSoIfConfigBase
	{
public:
	TInetIfConfig iConfig;
	};

enum TIfProgressNotification
	{
	
	EIfProgressLinkUp=KMinInterfaceProgress,
	EIfProgressLinkDown,
	EIfProgressAuthenticationComplete
	};

const TInt KErrIfAuthenticationFailure = -3050;
const TInt KErrIfAuthNotSecure         = -3051;
const TInt KErrIfAccountDisabled       = -3052;
const TInt KErrIfRestrictedLogonHours  = -3053;
const TInt KErrIfPasswdExpired         = -3054;
const TInt KErrIfNoDialInPermission    = -3055;
const TInt KErrIfChangingPassword      = -3056;
const TInt KErrIfCallbackNotAcceptable = -3057;
const TInt KErrIfDNSNotFound		   = -3058;
const TInt KErrIfLRDBadLine			   = -3059;   

#endif // __IN_IFACE_H__
