// tranp.h
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

//  
// IrTranp API 
//
#ifndef _TRANP_H_
#define _TRANP_H_

const TInt KErrIrtranpPeerDoesNotHaveIrtranp = -5530;

_LIT8(KDefaultPMID, "\x08\x00\x74\x00\x00\x00\x00\x01"); //Casio's number
_LIT8(KNullPMID, "\x00\x00\x00\x00\x00\x00\x00\x00");

enum TLatticeSize { EQVGA, EVGA, ESVGA, EXGA, ESXGA, EFREE };

class TTranpConfig
	{
public:
	IMPORT_C TTranpConfig();
	IMPORT_C ~TTranpConfig();

	IMPORT_C void SetPrimaryMachine(const TDesC8& aPMID);
	IMPORT_C void SetSecondaryMachine(const TDesC8& aSMID);

	IMPORT_C const TDesC8& PrimaryMachine();
	IMPORT_C const TDesC8& SecondaryMachine();

private:
	TBufC8<8> iPMID;
	TBufC8<8> iSMID;
	};

//
// Encapsulation the UPF file format.
//
class TTranpPicture
	{
friend class CTranpProtocol;
public:
	IMPORT_C void SetFilename(const TDesC8& aName);
	IMPORT_C void SetLongFilename(const TDesC8& aName);    
	IMPORT_C void SetTime(const TDesC8& aTime);

	IMPORT_C const TDesC8& Filename();
	IMPORT_C const TDesC8& LongFilename();
	IMPORT_C const TDesC8& Time();
	IMPORT_C const TDesC8* Picture();
	
	IMPORT_C void SetDesiredLatticeSize(TLatticeSize aSize, TInt iWidth = 0, TInt iHeight = 0); // Default is EVGA
	IMPORT_C void GetLatticeSize(TLatticeSize aSize, TInt iWidth, TInt iHeight);
	
	IMPORT_C void SetDesiredAspectRatio(TInt aX, TInt aY); // Default is 1:1
	IMPORT_C void GetAspectRatio(TInt aX, TInt aY);

	IMPORT_C const TDesC8* GetThumbNail();

	IMPORT_C TInt SaveAsJpeg(const TFileName& aFileName);
	IMPORT_C TInt LoadFromJpeg(const TFileName& aFileName);

	IMPORT_C TInt SaveAsUPF(const TFileName& aFileName);
	IMPORT_C TInt LoadFromUPF(const TFileName& aFileName);

public:
	IMPORT_C TTranpPicture();
	IMPORT_C ~TTranpPicture();

private:
	TBuf8<31> iFilename;		// fomatted in DOS 8.3 format
	TBuf8<256> iLongFilename;	// in SJIS or ISO8859-1 [Latin-1]
	TBuf8<14> iTime;			// Time string in format YYYYMMDDHHMMSS
	TPtrC8 iPicture;			// Pointer to a buffer conatining the image data [JPEG format]
	TDesC8* iUPFPicture;		// Pointer to a buffer conatining the image data [UPF format]
	TPtrC8 iThumbNail;			// Pointer to a buffer conatining the thumbnail image data [JPEG format] Not implemented.
	TLatticeSize iLatticeSize;	// Size of picture 
	TInt iWidth;	// QVGA:=320x240, VGA:=640x480, SVGA:=800x600, XGA:=1024x768, SXGA:=1280x960, FREE:=m x n
	TInt iHeight;
	TInt iX;		// Aspect Ratio iX:iY
	TInt iY;
	HBufC8* iHeapData;
	};

// 
// Callback interface for Asynchrnous requests
//
class MTranpNotification
	{
public:
	virtual void Connected() = 0;
	virtual void Disconnected() =0;
	virtual void GetComplete() = 0;
	virtual void ProgressIndication(TInt aPercent) = 0;
	virtual void PutComplete() = 0;
	virtual void QueryComplete(/*return result from query [what]*/)= 0;
	virtual void Error(TInt aError) =0;
	};

class CTranpProtocol;

class CTranpSession : public CBase
	{
public: 
	enum TTranP { EReqImageInfo = 0, EReqStatus, EReqCommands};

public:
	// Constructs a TranP Session
	IMPORT_C static CTranpSession* NewL(MTranpNotification& aNotifier);

private:
	IMPORT_C void ConstructL(MTranpNotification& aNotifier);

public:
	// Methods for establishing a connection
	IMPORT_C void Connect();
	IMPORT_C void Disconnect();
	IMPORT_C void Abort();

	// Query capabilities of peer
	IMPORT_C void Query(TTranP aWhat);

	// Receive picture from peer
	IMPORT_C void Get(TTranpPicture& aPicture);

	// Send picture to peer
	IMPORT_C void Put(const TTranpPicture& aPicture);

	// Change configuration parameters
	IMPORT_C void Config(const TTranpConfig& aConfig);
	IMPORT_C TTranpConfig Config() const;

	IMPORT_C ~CTranpSession();

private:
	IMPORT_C CTranpSession();	

private:
	CTranpProtocol* iTranpProtocol;
	TTranpConfig iConfig;
	};

#endif //_TRANP_H_