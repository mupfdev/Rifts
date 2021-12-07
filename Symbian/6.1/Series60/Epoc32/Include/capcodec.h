#ifndef __CAPCODEC_H__
#define __CAPCODEC_H__


#ifndef CAP_Codec_h
struct CapabilitySet;
#endif

// File   : CapCodec.h
// Author : Bob Cripps for Symbian Ltd Copyright (C) 1999 
// WAP client application capabilities interface class

class TAliasAddress;


class CCapCodec : public CBase
{
public:

	typedef enum
		{
		EAckHeaders =                  0x10,
		ESessionResume =               0x20,
		EPush =                        0x40,
		EConfPush =                    0x80,
		EAll =                         0xF0
		}EProtOptions;

	
	// WAP client application class needs access to private member 
	friend class RWSPCOConn;

	IMPORT_C ~CCapCodec();
	// Clear class members to defaults and release memory
	IMPORT_C void Reset();
    
	// Client application calls to construct a new capabilities class
	IMPORT_C static  CCapCodec* NewL();
    // Overloaded to take an encoded capabilities buffer retrieved from the client API
    // using a RWSPCOConn::GetSessionData() call
	IMPORT_C static  CCapCodec* NewL(const TDesC8& aEncodeBuf);
    
    // Set and Get for protocol options
    // Mask of TODO
	IMPORT_C void SetProtocolOptions(const  TUint32 aProtOptions);
	IMPORT_C void GetProtocolOptions(TUint32& aProtOptions);
    
    // Set and Get for the Server and Client SDU size
	IMPORT_C void SetClientSDUSize(const TUint32 aSize);
	IMPORT_C void ClientSDUSize(TUint32& aSize) const;
	IMPORT_C void SetServerSDUSize(const TUint32 aSize);
	IMPORT_C void GetServerSDUSize(TUint32& aSize) const;

	// Set and Get for Maximum Outstanding Requests
	IMPORT_C void SetMethodMOR(const TUint8 aVal);
	IMPORT_C void MethodMOR(TUint8& aVal) const;
	IMPORT_C void SetPushMOR(const TUint8 aVal);
	IMPORT_C void GetPushMOR(TUint8& aVal) const;

	// Set and Get for class extended methods
	// returns Nokia defined code , 0 = No Error
	IMPORT_C TInt AddExtendedMethod(TDes8& aMethod,const TUint8 aVal);
	// Call NumExtendedMethods() first
	// aIndex is between (0 to (aNumExtendedMethods - 1)
	// Return KErrNone or KErrTooBig if aIndex is out of range or
	// the descriptor is too small.
	IMPORT_C TInt GetExtendedMethod(const TInt aIndex,TDes8& aMethod,TUint8& aVal) const;
	IMPORT_C void NumExtendedMethods(TInt& aNumExtendedMethods) const;

	// Set and Get for class code pages
	// returns Nokia defined code , 0 = No Error
	IMPORT_C TInt AddCodePage(TDes8& aCodePage,const TUint8 aVal);
	// Call NumCodePages() first
	// aIndex is between (0 to (aNumCodePages - 1)
	// Return KErrNone or KErrTooBig if aIndex is out of range or
	// the descriptor is too small.
	IMPORT_C TInt GetCodePage(const TInt aIndex,TDes8& aCodePage,TUint8& aVal) const;
	IMPORT_C void NumCodePages(TInt& aNumCodePages) const;

	// Set and Get for Unknown/Other capabilities
	// returns Nokia defined code , 0 = No Error
	IMPORT_C TInt AddUnknownCap(TDes8& aName,const TDesC8& aValue);
	// Call NumUnknownCap first
	// aIndex is between (0 to (aNumUnknown - 1)
	// Return KErrNone or KErrTooBig if aIndex is out of range or one or more
	// of the descriptors is too small.
	IMPORT_C TInt GetUnknownCap(const TInt aIndex,TDes8& aName,TDes8& aValue) const;
	IMPORT_C void NumUnkownCap(TInt& aNumUnknown) const;

	// Set and Get for class aliases
	// Requires the use of an Alias class 
	// Returns Nokia defined code, 0 = no error
	IMPORT_C TInt AddAliasAddress(const TAliasAddress& aAddress);
	// Call NumAliasAddress() first
	// aIndex is between (0 to (aNumAddresses - 1)
	// Return KErrNone or KErrTooBig if aIndex is out of range 
	IMPORT_C TInt GetAliasAddress(const TInt aIndex, TAliasAddress& aAddress) const;
	IMPORT_C void NumAliasAddress(TInt& aNumAddresses) const;

protected:
private:
	IMPORT_C TInt CapEncodeSize(void) const;
	IMPORT_C TInt Encode(TDes8& aDestCapSet) const;
	IMPORT_C TInt Decode(const TDesC8& aSrcCapSet);
	IMPORT_C void ConstructL();
	IMPORT_C void ConstructL(const TDesC8& aDecodeBuf);

	CapabilitySet* iCapSet;
};

// For Get and Set of Alias Addresses information
class TAliasAddress
{
public:
	IMPORT_C ~TAliasAddress();
	IMPORT_C TAliasAddress();
    
    // Set the port value
	IMPORT_C void SetPort(const TUint16 aPort);
	// Set the bearer value
	IMPORT_C void SetBearer(const TUint8 aBearer);
	// Set the address array
	IMPORT_C TInt SetAddress(const TDesC8& aAddress);
	// Bool's, use uchar to avoid conflict with Nokia BOOL (uchar) and Epoc TBool (Uint32) 
	IMPORT_C TUint8 HasBearer(void) const;
	IMPORT_C TUint8 HasPort(void) const;
	// Get Bearer value
	IMPORT_C TUint8 Bearer(void) const;
	// Get Port value
	IMPORT_C TUint16 Port(void) const;
	// Get the stored address
	IMPORT_C const TDesC8& Address() const;
	// Restore to constructed state
	IMPORT_C void Reset(void);

protected:
private:

	TBuf8<64> iAddress;
	TUint8 iBearer;
	TUint16 iPort;
	TUint8 iHasPort;
	TUint8 iHasBearer;
};
#endif