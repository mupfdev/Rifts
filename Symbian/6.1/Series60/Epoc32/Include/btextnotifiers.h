// BTExtNotifiers.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef BTEXTNOTIFIERS_H
#define BTEXTNOTIFIERS_H

#include <e32std.h>
#include <bttypes.h>
#include <btdevice.h>

const TUid KDeviceSelectionNotifierUid={0x100069D1};
const TUid KUidBTBasebandNotification={0x1000A5FB};
/**
Class to allow parameters to be sent to the device selection dialog via the RNotifier API.
**/
class TBTDeviceSelectionParams
	{
public:
	IMPORT_C TBTDeviceSelectionParams();
	IMPORT_C void SetUUID(const TUUID& aUUID);
	IMPORT_C void SetDeviceClass(TBTDeviceClass aClass);
	IMPORT_C const TUUID& UUID();
	IMPORT_C TBTDeviceClass DeviceClass();
	IMPORT_C TBool IsValidDeviceClass();
	IMPORT_C TBool IsValidUUID();
private:
	TBTDeviceClass iDeviceClass;
	TUUID iSdpUuid;
	TBool iValidDeviceClass;
	TBool iValidUuid;
	};

class TBTDeviceResponseParams
	{
public:
	IMPORT_C TBTDeviceResponseParams();
	IMPORT_C void SetDeviceAddress(const TBTDevAddr& aBDAddr);	///< Set the address of the device
	IMPORT_C void SetDeviceName(const TDesC& aName);	///< Set the name of the device
	IMPORT_C void SetDeviceClass(TBTDeviceClass aClass);
	IMPORT_C const TBTDevAddr& BDAddr() const;				///< Returns the address of the device
	IMPORT_C const TDesC& DeviceName() const;		///< Returns the name of the device
	IMPORT_C TBTDeviceClass DeviceClass();
	IMPORT_C TBool IsValidBDAddr() const;			///< Has the address of the device been set?
	IMPORT_C TBool IsValidDeviceName() const;		///< Has the name of the device been set?
	IMPORT_C TBool IsValidDeviceClass();
private:
	TBTDevAddr iBDAddr; 				///< The BT address of the remote device
	TBTDeviceName iDeviceName; 			///< The name given by the remote device
	TBTDeviceClass iDeviceClass;
	TBool iValidBDAddr;
	TBool iValidDeviceName;
	TBool iValidDeviceClass;
	};


/**
Class to allow passing of baseband connection event information to an extended
notifier.
**/
class TBTBasebandNotificationParams
	{
public:
	
	enum TBasebandEvent
		{
		EBasebandDisconnect,
		EBasebandConnectAttempt,
		EBasebandConnectAttemptFailure,
		EBasebandConnectAttemptSuccess
		};

	//	Construction
	IMPORT_C TBTBasebandNotificationParams();
	IMPORT_C TBTBasebandNotificationParams(TBasebandEvent aEvent, TInt aNumConnections);
	
	IMPORT_C TBasebandEvent BasebandEvent() const;
	IMPORT_C TInt CurrentConnections() const;
	
	IMPORT_C void SetBasebandEvent(TBasebandEvent aEvent);
	IMPORT_C void SetCurrentConnections(TInt aCurrentConnections);

private:
	TBasebandEvent  iBasebandEvent;
	TInt			iCurrentConnections;
	};

typedef TPckgBuf<TBTDeviceSelectionParams> TBTDeviceSelectionParamsPckg;
typedef TPckgBuf<TBTDeviceResponseParams> TBTDeviceResponseParamsPckg;
typedef TPckgBuf<TBTBasebandNotificationParams> TBTBasebandNotificationParamsPckg;

#endif