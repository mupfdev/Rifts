// Mda\Server\AudioIo.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// *********** All classes Internal to Symbian *************//

#ifndef __MDA_SERVER_AUDIOIO_H__
#define __MDA_SERVER_AUDIOIO_H__

// Public Media Server includes
#include <Mda\Server\Environment.h>
#include <Mda\Common\Audio.h>
#include <Mda\Server\Io.h>
#include <Mda\Server\Buffer.h>
#include <Mda\Server\AudioDatatype.h>
#include <Mda\Server\AudioRateConverter.h>

const TInt KBufferLatency(125000);
const TInt KBufferLatencyDivide(8);

// Internal to Symbian
class CMdaAudioMaths : public CBase
//make a C class in case future methods allocate internal tables etc
	{
public:
	enum TRound {EDontRound, ERoundDown, ERoundUp};
public:
	static IMPORT_C TInt BytesOfAudio(TTimeIntervalMicroSeconds aDuration, TInt aChannels, TInt aRate,TInt aBytesPerSample=2,CMdaAudioMaths::TRound aRound=CMdaAudioMaths::EDontRound);
	};

//
// Audio settings class definition
// Takes a settings package and performs useful operations on it

// Internal to Symbian
class TMdaAudioDataSettingsQuery
	{
public:
	inline TMdaAudioDataSettingsQuery(const TMdaAudioDataSettings& aAudio) : iAudio(aAudio) {}
	//
	IMPORT_C TInt MinSupportedRate() const;
	IMPORT_C TInt MaxSupportedRate() const;
	IMPORT_C TBool IsRateSupported(TInt aRate) const;

	IMPORT_C TInt MinSupportedChannels() const;
	IMPORT_C TInt MaxSupportedChannels() const;
	IMPORT_C TBool IsNumberChannelsSupported(TInt aChannels) const;
public:
	const TMdaAudioDataSettings& iAudio;
	};

//
// Audio buffer class definition
//

enum TMdaAudioBufferPanic
	{
	EInvalidDuration=0,
	EChannelsZeroOrNegative=1,
	EInvalidRate=2
	};

// Internal to Symbian
class CMdaAudioBuffer : public CMdaTimedBuffer
	{
public:
	IMPORT_C static CMdaAudioBuffer* NewL(TTimeIntervalMicroSeconds aMaxDuration, 
		TInt aChannels, TInt aRate, CMdaAudioMaths::TRound aRound=CMdaAudioMaths::EDontRound);
	IMPORT_C virtual TUid MediaType() const; // Must supply
	//
	inline TInt Channels();
	inline TInt Rate();
	inline TMdaPtr8& Audio();
	inline TInt Samples();
	//	
	IMPORT_C void UpdateTimeInfo(TTimeIntervalMicroSeconds aPosition);
protected:
	CMdaAudioBuffer(TInt aBytes,TInt aChannels, TInt aRate);
private:
	TInt iChannels;
	TInt iRate;
	TMdaPtr8 iAudio; // Data allocated straight after in same alloc cell
public:
	TSglQueLink iQueueLink;
	};

//
// Audio IO class definitions
//

enum TMdaAudioIOPanic
	{
	EMdaAudioIOPanicBadState=0,
	EMdaAudioIOPanicAlreadyHasEmptyBuffer=1,
	EMdaAudioIOPanicDoesNotHaveFullBuffer=2
	};

// Internal to Symbian
enum TMdaAudioIOState
	{
	EMdaAudioIONotReady=		0x00000000,
	EMdaAudioIOReady=			0x00000001,
	EMdaAudioIONegotiating=		0x00000002,
	EMdaAudioIOWaitingToSupply=	0x00000004,
	EMdaAudioIOWaitingToAccept=	0x00000008,
	EMdaAudioIOWaiting=			EMdaAudioIOWaitingToSupply|EMdaAudioIOWaitingToAccept,
/*	EMdaAudioIOBusySupplying=	0x00000010,
	EMdaAudioIOBusyAccepting=	0x00000020,
	EMdaAudioIOBusy=			EMdaAudioIOBusySupplying|EMdaAudioIOBusyAccepting,*/
	};

// Internal to Symbian
class CMdaAudioIO : public CMdaIO
	{
public:
protected:
	inline CMdaAudioIO(CMdaPort& aPort,CMdaAudioDatatype& aDatatype):
		CMdaIO(aPort,aDatatype) {}
	// Interface for datatype
protected:
	TInt iState;
	TMdaAudioDataSettings iAudioSettings;
	TMdaAudioBufferSettings iSrcSupplyBuffer;
	TMdaAudioBufferSettings iDstSupplyBuffer;
	CMdaAudioBuffer* iEmptyBuffer;
	CMdaAudioBuffer* iFullBuffer;
	CMdaAudioBuffer* iHeldBuffer;
	};

class CMdaAudioSrcDatatype; // Forward reference
// Internal to Symbian
class CMdaAudioSrcIO : public CMdaAudioIO
	{
public:
	IMPORT_C static CMdaAudioSrcIO* NewL(CMdaPort& aPort,CMdaAudioSrcDatatype& aData);
	// Message passing
	virtual void OperationL(CMdaMessage* aMessage);
	// Interface for connection
	virtual CMdaBuffer* SupplyBuffer();
	virtual void AcceptBuffer(CMdaBuffer* aBuffer);
	// Interface for datatype
	void FullBuffer(CMdaAudioBuffer* aBuffer);
	CMdaAudioBuffer* EmptyBuffer();
protected:
	CMdaAudioSrcIO(CMdaPort& aPort,CMdaAudioSrcDatatype& aData);
	// Machine state change
	virtual void MachinePrepareL();
	virtual void MachineCancelPrepare();
	virtual void MachinePrimeL();
	virtual void MachineCancelPrime();
	virtual void MachinePlayL();
	virtual void MachineCancelPlay();
	virtual void MachinePause();
	virtual void MachineStop();
	virtual void MachineUnprepare();
	// Utility
	inline CMdaAudioSrcDatatype& Datatype();
	TInt ProcessNegotiation(CMdaMessage* aMessage);
protected:
	TInt iNegErr;
	friend class CMdaAudioSrcDatatype;
	};


class CMdaAudioDstDatatype; // Forward reference
// Internal to Symbian
class CMdaAudioDstIO : public CMdaAudioIO
	{
public:
	IMPORT_C static CMdaAudioDstIO* NewL(CMdaPort& aPort,CMdaAudioDstDatatype& aData);
	// Message passing
	IMPORT_C virtual CMdaBuffer* SupplyBuffer();
	IMPORT_C virtual void AcceptBuffer(CMdaBuffer* aBuffer);
	// Interface for datatype
	void EmptyBuffer(CMdaAudioBuffer* aBuffer);
	CMdaAudioBuffer* FullBuffer();
	// from MMdaMessage
	virtual void MessageDoComplete(TInt aVal);
protected:
	CMdaAudioDstIO(CMdaPort& aPort,CMdaAudioDstDatatype& aData);
	virtual void MachinePrepareL();
	virtual void MachineCancelPrepare();
	virtual void MachinePrimeL();
	virtual void MachineCancelPrime();
	virtual void MachinePlayL();
	virtual void MachineCancelPlay();
	virtual void MachinePause();
	virtual void MachineStop();
	virtual void MachineUnprepare();
	// Utility
	inline CMdaAudioDstDatatype& Datatype();
	inline CMdaAudioChannelRateConverterFactory& ConverterFactory(); 
protected:
	TInt iNegErr;
	TBool		iMute;
	TInt		iVolume;
	TBool		iFinished;
	friend class CMdaAudioDstDatatype;
private:
	CMdaAudioChannelRateConverterFactory iConverterFactory;
	};

// Inlines 
inline CMdaAudioChannelRateConverterFactory& CMdaAudioDstIO::ConverterFactory()
	{return iConverterFactory;}
inline TInt CMdaAudioBuffer::Channels()
	{ return iChannels; }
inline TInt CMdaAudioBuffer::Rate()
	{ return iRate; }
inline TMdaPtr8& CMdaAudioBuffer::Audio()
	{ return iAudio; }
inline TInt CMdaAudioBuffer::Samples()
	{ return (iAudio.Length())/(iChannels<<1); }

inline CMdaAudioSrcDatatype& CMdaAudioSrcIO::Datatype()
	{ return *STATIC_CAST(CMdaAudioSrcDatatype*,&iDatatype); }

inline CMdaAudioDstDatatype& CMdaAudioDstIO::Datatype()
	{ return *STATIC_CAST(CMdaAudioDstDatatype*,&iDatatype); }

#endif
