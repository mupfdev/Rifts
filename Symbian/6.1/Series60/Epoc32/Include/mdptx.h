// 
// mdptx.h
// Copyright (C) 1997-1998 Symbian Ltd. All rights reserved.
// 

//
// Data generator for data transmission, used by URL Handler when transmitting data
//

#if !defined(__MDPTX_H__)
#define __MDPTX_H__

#include <e32base.h>

class MDataProviderTransmissionData
	{
public:
	// This should return the data that the url handler should transmit.
	// This call will be repeated until datasize amounts of data has been
	// transmitted
	virtual const TDesC8& DataL()=0;

	// Returns the size of the amount of data that needs to be transmitted.
	virtual TInt DataSize()=0;

	// This returns the name of the data, this will depend on the type of
	// data transmission,
	virtual const TDesC& DataNameL()=0;

	// This should return the refering url or NULL;
	virtual const TDesC& RefererUrlL()=0;
	
	// This returns the accepted charset.
	virtual const TDesC& AcceptedCharsetL()=0;

	// This returns the accepted mimetype
	virtual const TDesC& AcceptedMimetypes()=0;

private:
	//	Reserved for future expansion
	IMPORT_C virtual void MDataProviderTransmissionData_Reserved1()=0;
	};

#endif    // __MDPTX_H__
