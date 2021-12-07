// Mda\Server\Io.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// *********** All classes Internal to Symbian *************//

#ifndef __MDA_SERVER_IO_H__
#define __MDA_SERVER_IO_H__

#ifndef __MDA_SERVER_BASE_H__
#include <Mda\Server\Base.h>
#endif

#ifndef __MDA_SERVER_MACHINE_H__
#include <Mda\Server\Machine.h>
#endif

class CMdaPort;				// Forward declarations
class CMdaDatatype;
class CMdaConnection;	
class CMdaBuffer;			
class CMdaDispatchMessage;	

// Internal to Symbian
class CMdaIO : public CMdaObject, public MMdaMessage, public MMdaMachineSlave
	{
public:
	IMPORT_C virtual void ConnectL(CMdaConnection* aConnection);
	// From MMdaMessage
	IMPORT_C virtual void MessageDoComplete(TInt aVal);
	// Must be supplied by derived classes
	virtual CMdaBuffer* SupplyBuffer()=0;
	virtual void AcceptBuffer(CMdaBuffer* aBuffer)=0;
	// Utility
	inline CMdaPort& Port() const;
	inline CMdaDatatype& Datatype() const;
	inline CMdaConnection* Connection() const;
protected:
	inline CMdaIO(CMdaPort& aPort,CMdaDatatype& aDatatype);
	IMPORT_C ~CMdaIO();
public:
	TSglQueLink iPortLink;
	TDblQueLink iDatatypeLink;
protected:
	CMdaPort& iPort;
	CMdaDatatype& iDatatype;
	CMdaConnection* iConnection;
	CMdaDispatchMessage* iMessage;
	};

// Inlines

inline CMdaPort& CMdaIO::Port() const
	{ return iPort; }
inline CMdaDatatype& CMdaIO::Datatype() const
	{ return iDatatype; }
inline CMdaConnection* CMdaIO::Connection() const
	{ return iConnection; }

inline CMdaIO::CMdaIO(CMdaPort& aPort, CMdaDatatype& aDatatype) : 
iPort(aPort), iDatatype(aDatatype) {}

#endif
