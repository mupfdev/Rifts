// Mda\Server\AudioDatatype.h
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

// *********** All classes Internal to Symbian *************//

#ifndef __MDA_SERVER_AUDIODATATYPE_H__
#define __MDA_SERVER_AUDIODATATYPE_H__

// Public Media Server includes
#include <Mda\Common\Audio.h>

#include <Mda\Server\Base.h>
#include <Mda\Server\Environment.h>
#include <Mda\Server\Buffer.h>
#include <Mda\Server\AudioRateConverter.h>

class CMdaAudioBuffer; // Forward references to escape circular dependency
class CMdaAudioSrcIO; 
class CMdaAudioDstIO; 

enum CMdaAudioDatatypePanic
	{
	EMdaAudioDatatypePanicBadState=0
	};

//
// Audio datatype class definition
//

// Internal to Symbian
class CMdaAudioDatatype : public CMdaDatatype
	{
protected:
	enum TDataState
		{
		EDataFinished=0,
		EDataReady=1
		};
protected:
	TMdaMachineState iState;
	TInt iDataState; // Negative = error
	};

//
// Audio src datatype class definitions
//

// Internal to Symbian
class MMdaAudioDatatypeSupplier
	{
public: // Interface for CMdaAudioSrcDatatype to call
	virtual void AdtsInitL()=0; // Fill settings values
	virtual void AdtsPrepareL()=0; // Allocate resources
	virtual void AdtsPrimeL()=0; // Allocate resources
	virtual void AdtsPlayL()=0; // Allocate resources
	virtual void AdtsBuffer(CMdaAudioBuffer* aBuffer)=0;
	virtual void AdtsPause()=0;
	virtual void AdtsStop()=0;
	virtual void AdtsUnprepare()=0;
protected:
	// For datatype to read only - must be set after Init
	TMdaAudioBufferSettings iAdtsBuffers;
	TTimeIntervalMicroSeconds iAdtsLatency;
	// For datatype to read and modify before prepare
	TMdaAudioDataSettings iAdtsAudioSettings;
	// For datatype to set - will be set before prepare
	TInt iAdtsPriority;
	TMdaPriorityPreference iAdtsPriorityPref;
	//
	friend class CMdaAudioSrcDatatype;
	};

// Internal to Symbian
class CMdaAudioSrcDatatype : public CMdaAudioDatatype
	{
public:
	IMPORT_C static CMdaAudioSrcDatatype* NewL(MMdaAudioDatatypeSupplier& aSupplier);
	// From CMdaDatatype
	IMPORT_C virtual CMdaIO& DoCreateIOL(CMdaPort& aPort);
	// New functions
	// Interface for AudioIO objects
	IMPORT_C void IOInitL(CMdaAudioSrcIO* aIO);
	IMPORT_C void IOPrepareL(CMdaAudioSrcIO* aIO);
	IMPORT_C void IOPrimeL(CMdaAudioSrcIO* aIO);
	IMPORT_C void IOPlayL(CMdaAudioSrcIO* aIO);
	IMPORT_C void IOBufferDelivered(CMdaAudioSrcIO* aIO);
	IMPORT_C void IOBufferReceived(CMdaAudioSrcIO* aIO);
	IMPORT_C void IOPause(CMdaAudioSrcIO* aIO);
	IMPORT_C void IOStop(CMdaAudioSrcIO* aIO);
	IMPORT_C void IOUnprepare(CMdaAudioSrcIO* aIO);

	// Interface for Supplier object
	IMPORT_C void SupplierNeedsBuffer();
	IMPORT_C void SupplierBuffer(CMdaAudioBuffer* aBuffer);
	IMPORT_C void SupplierFinished();
	IMPORT_C void SupplierError(TInt aError);
protected:
	inline CMdaAudioSrcDatatype(MMdaAudioDatatypeSupplier& aSupplier);
protected:
	MMdaAudioDatatypeSupplier& iSupplier;
	friend class CMdaAudioSrcIO;
	};

inline CMdaAudioSrcDatatype::CMdaAudioSrcDatatype(MMdaAudioDatatypeSupplier& aSupplier) :
iSupplier(aSupplier) {}


//
// Audio dst datatype class definitions
//

// Internal to Symbian
class MMdaAudioDatatypeConsumer
	{
public: // Interface for CMdaAudioDstDatatype to call
	virtual void AdtcInitL()=0; // Fill settings values
	virtual void AdtcPrepareL()=0; // Allocate resources
	virtual void AdtcPrimeL()=0; // Allocate resources
	virtual void AdtcPlayL()=0; // Allocate resources
	virtual void AdtcBuffer(CMdaAudioBuffer* aBuffer)=0;
	virtual void AdtcPause()=0;
	virtual void AdtcStop()=0;
	virtual void AdtcUnprepare()=0;
protected:
	// For datatype to read only - must be set after Init
	TMdaAudioBufferSettings iAdtcBuffers;
	TTimeIntervalMicroSeconds iAdtcLatency;
	// For datatype to read and modify before prepare
	TMdaAudioDataSettings iAdtcAudioSettings;
	// For datatype to set - will be set before prepare
	TInt iAdtcPriority;
	TMdaPriorityPreference iAdtcPriorityPref;
	//
	friend class CMdaAudioDstDatatype;
	};

// Internal to Symbian
class CMdaAudioDstDatatype : public CMdaAudioDatatype
	{
public:
	IMPORT_C static CMdaAudioDstDatatype* NewL(MMdaAudioDatatypeConsumer& aConsumer);
	// From CMdaDatatype
	IMPORT_C virtual CMdaIO& DoCreateIOL(CMdaPort& aPort);
	// New functions
	// Interface for AudioIO objects
	IMPORT_C void IOInitL(CMdaAudioDstIO* aIO);
	IMPORT_C void IOPrepareL(CMdaAudioDstIO* aIO);
	IMPORT_C void IOPrimeL(CMdaAudioDstIO* aIO);
	IMPORT_C void IOPlayL(CMdaAudioDstIO* aIO);
	IMPORT_C void IOBufferDelivered(CMdaAudioDstIO* aIO);
	IMPORT_C void IOBufferReceived(CMdaAudioDstIO* aIO);
	IMPORT_C void IOPause(CMdaAudioDstIO* aIO);
	IMPORT_C void IOStop(CMdaAudioDstIO* aIO);
	IMPORT_C void IOUnprepare(CMdaAudioDstIO* aIO);
	// Interface for Consumer object
	IMPORT_C void ConsumerNeedsBuffer();
	IMPORT_C void ConsumerBuffer(CMdaAudioBuffer* aBuffer);
	IMPORT_C void ConsumerFinished();
	IMPORT_C void ConsumerError(TInt aError);
protected:
	inline CMdaAudioDstDatatype(MMdaAudioDatatypeConsumer& aConsumer);
	//
	void DeliverBufferToConsumer();
	void CheckForEndAndDeliver();
	void CheckForHeldBufferEmpty(CMdaAudioDstIO* aIO);
protected:
	MMdaAudioDatatypeConsumer& iConsumer;
	TBool iNeedConversion;
	CMdaAudioBuffer* iTargetBuffer;
	CMdaAudioBuffer* iConsumerBuffer;
	TBool iDeliverBuffer;
	TBool iMarkConsumerBufferEnd;
	friend class CMdaAudioDstIO;


	};

inline CMdaAudioDstDatatype::CMdaAudioDstDatatype(MMdaAudioDatatypeConsumer& aConsumer) :
iConsumer(aConsumer) {}

const TInt KMdaAudioMixerOutputVolumeShift	= 10;
const TInt KMdaAudioMixerOutputVolume		= 1 << (KMdaAudioMixerOutputVolumeShift);
const TInt KMdaAudioMixerMaxChannelVolume	= KMdaAudioMixerOutputVolume * 2;

#endif
