// BTRegistry.h
//
// Copyright (c) 1999 - 2000 Symbian Ltd. All rights reserved.
//

#ifndef BTREGISTRY_H
#define BTREGISTRY_H
#include <BTDevice.h>
#include <Commdb.h>
#include <BTDefCommPort.h>



class CBTRegistryHelper;


const TInt KCommDBOpenTime = 2; //number of seconds before CommDB will be clodes down after use
/**
	CBTRegistry, This class owns the registry public API. 
	It's responsible for Adding/Deleting/Retrieving/Modifying 
	devices held in the registry. It also adds/retrieves TBTCommPortSettings
	used by the BTCOMM.CSY.
**/
class CBTRegistry : public CBase
{

public:
	IMPORT_C static CBTRegistry* NewLC();
	IMPORT_C static CBTRegistry* NewL();
	~CBTRegistry();

	IMPORT_C TInt Add(const CBTDevice& aDevice);

	IMPORT_C TInt Delete(const CBTDevice& aDevice);

	IMPORT_C TInt Retrieve(const CBTDevice& aDeviceToSearchFor, CBTDeviceArray& aDeviceList);

	IMPORT_C TInt Modify(const CBTDevice& aOldDevice, const CBTDevice& aNewDevice);

	IMPORT_C TInt SetDefaultCommPort(const TBTCommPortSettings& aService);

	IMPORT_C TInt GetDefaultCommPort(TUint32 aBtCommPort, TBTCommPortSettings& aService);

private:
	void ConstructL();
	CBTRegistry();
private:
	CBTRegistryHelper* iHelper;				///<does all the actual work 
	};





#endif