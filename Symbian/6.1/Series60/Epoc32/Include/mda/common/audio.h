// Mda\Common\Audio.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __MDA_COMMON_AUDIO_H__
#define __MDA_COMMON_AUDIO_H__

// Standard EPOC32 includes
#include <e32base.h>

// Public Media Server includes
#include <Mda\Common\Base.h>
#include <Mda\Common\Resource.h>
#include <Mda\Common\Controller.h>
#include <Mda\Common\Audio.hrh>
#include <Mda\Common\AudioStream.hrh>

MDA_UID(KUidMdaPrioritySettings)
MDA_UID(KUidMdaMediaTypeAudio) // Audio data type Uid
MDA_UID(KUidMdaLocalSoundDevice) // Local audio stream location
MDA_UID(KUidMdaTelephonySoundDevice) // Telephony audio stream location
MDA_UID(KUidMdaClientPCMSoundDevice) // Client PCM audio stream location
MDA_UID(KUidMdaToneGeneratorDevice) // Tone Generator Device
MDA_UID(KUidMdaClipFormatWav) // Wav Audio Clip Format Uid

MDA_UID(KUidMdaAudioOutputStreamDevice) // Output Stream Device

MDA_UID(KUidMdaWavCodec) // Wav Codec Type Uid
MDA_UID(KUidMdaWavPcmCodec) // Wav Codec Uids
MDA_UID(KUidMdaWavAlawCodec) 
MDA_UID(KUidMdaWavMulawCodec) 
MDA_UID(KUidMdaWavImaAdpcmCodec) 

MDA_UID(KUidMdaClipFormatEpocWve) // EPOC Wve Audio Clip format Uid
MDA_UID(KUidMdaEpocWveCodec) // EPOC Wve Codec Type Uid
MDA_UID(KUidMdaEpocWveAlawCodec) // EPOC Wve Codec Uids
MDA_UID(KUidMdaEpocWveAdpcmCodec) 

MDA_UID(KUidMdaClipFormatSiboWve) // SIBO Wve Audio Clip format Uid

MDA_UID(KUidMdaClipFormatAu) // Sun/Next "Au" Audio Clip format Uid
MDA_UID(KUidMdaAuCodec) // Sun/Next "Au" Audio Codec Type Uid
MDA_UID(KUidMdaAuMulawCodec) // Sun/Next "Au" Audio Codec Uids
MDA_UID(KUidMdaAu8PcmCodec)  
MDA_UID(KUidMdaAu16PcmCodec) 
MDA_UID(KUidMdaAuAlawCodec)

MDA_UID(KUidMdaClipFormatRawAudio) // Raw Audio Clip format Uid
MDA_UID(KUidMdaRawAudioCodec) // Raw Audio Codec Type Uid
MDA_UID(KUidMdaRawAudioMulawCodec)
MDA_UID(KUidMdaRawAudioAlawCodec) 
MDA_UID(KUidMdaRawAudioS8PcmCodec) // Signed 8bit
MDA_UID(KUidMdaRawAudioU8PcmCodec) // Unsigned 8bit
MDA_UID(KUidMdaRawAudioSL16PcmCodec) // Signed little-endian 16bit
MDA_UID(KUidMdaRawAudioSB16PcmCodec) // Signed big-endian 16bit
MDA_UID(KUidMdaRawAudioUL16PcmCodec) // Unsigned little-endian 16bit
MDA_UID(KUidMdaRawAudioUB16PcmCodec) // Unsigned big-endian 16bit

MDA_UID(KUidMdaTelephonyStateQuery) // Telephony state query 
MDA_UID(KUidMdaAudioStreamVolumeRamp) // Audio stream volume ramp 

enum TMdaAudioBufferSettings
	{
	// Combinations
	EMdaAudioBufferAtPlay =		0x0000000, // Can only handle buffers whilst playing
	EMdaAudioBufferAtPrime =	0x0000001, // Can handle buffers when primed
	EMdaAudioBufferDouble =		0x0000002, // Must have two buffers for uninterrupted play
	EMdaAudioBufferSupply =		0x0000004  // Will supply buffers for efficiency
	};

// Package classes

// Generic Audio Parameters
class TMdaPrioritySettings : public TMdaPackage
	{
public:
	inline TMdaPrioritySettings();
public:
	TInt iPriority;
	TMdaPriorityPreference iPref;
	};

class TMdaAudioDataSettings : public TMdaDatatypeSettings
	{
public:
	enum TAudioCaps
		{
		// Sampled audio capabilities
		ESampleRateFixed =		0x00000001,
		ESampleRateAnyInRange = 0x00000002,
		ESampleRate8000Hz =		0x00000010,
		ESampleRate11025Hz =	0x00000040,
		ESampleRate16000Hz =	0x00000100,
		ESampleRate22050Hz =	0x00000400,
		ESampleRate32000Hz =	0x00001000,
		ESampleRate44100Hz =	0x00004000,
		ESampleRate48000Hz =	0x00010000,
		// Channel related - applies to sampled
		EChannelsMono =			0x02000000,
		EChannelsStereo =		0x04000000,
		// Routing related
		ERoutingControl =		0x08000000,
		// True if data flow is synchronised with real time (e.g. stream)
		ERealTime =				0x10000000
		};
	enum TAudioFlags
		{
		ENoLocalRouting =		0x00000001,
		ENoNetworkRouting =		0x00000002
		};
public:
	inline TMdaAudioDataSettings();
	inline void Query(); // Call this when you just want to have caps and maxvolume filled
public:
	// Fixed values - must be queried
	TInt iCaps;
	TInt iMaxVolume; // One means fixed volume (zero not valid)
	// Variables
	TInt iSampleRate;
	TInt iChannels;
	TInt iVolume;
	TInt iFlags;
	};

// Wav Config Packages
class TMdaWavClipFormat : public TMdaClipFormat
	{
public:
	inline TMdaWavClipFormat();
	};

class TMdaWavCodec : public TMdaPackage
	{
public:
	inline TMdaWavCodec(); // Unknown type
protected:
	inline TMdaWavCodec(TUid aUid,TInt aDerivedSize);
	};

class TMdaCodecQuery : public TMdaPackage
	{
public:
	inline TMdaCodecQuery(TUid aType, TUid aUid,TInt aAdditionalSize);
	};

class TMdaPcmWavCodec : public TMdaWavCodec
	{
public:
	enum TBits
		{
		E8BitPcm=0,
		E16BitPcm=1
		};
public:
	inline TMdaPcmWavCodec(TBits aBits=E16BitPcm);
public:
	TBits iBits;
	};

class TMdaAlawWavCodec : public TMdaWavCodec
	{ 
public: 
	inline TMdaAlawWavCodec();
	};

class TMdaMulawWavCodec : public TMdaWavCodec
	{
public:
	inline TMdaMulawWavCodec();
	};

class TMdaImaAdpcmWavCodec : public TMdaWavCodec
	{
public:
	inline TMdaImaAdpcmWavCodec();
	};

// EPOC Wve Config Packages
class TMdaEpocWveClipFormat : public TMdaClipFormat
	{
public:
	inline TMdaEpocWveClipFormat();
public:
	TInt iTrailingSilence;
	TInt iRepeatCount;
	TInt iEpocVolume;
	};
 
class TMdaEpocWveCodec : public TMdaPackage
	{
public:
	inline TMdaEpocWveCodec(); // Unknown type
protected:
	inline TMdaEpocWveCodec(TUid aUid,TInt aDerivedSize);
	};

class TMdaAlawEpocWveCodec : public TMdaEpocWveCodec
	{ 
public: 
	inline TMdaAlawEpocWveCodec();
	};

class TMdaAdpcmEpocWveCodec : public TMdaEpocWveCodec
	{
public:
	inline TMdaAdpcmEpocWveCodec();
	};

// SIBO Wve Config Packages
class TMdaSiboWveClipFormat : public TMdaClipFormat
	{
public:
	inline TMdaSiboWveClipFormat();
public:
	TInt iTrailingSilence;
	TInt iRepeatCount;
	};

class TMdaSiboWveCodec : public TMdaPackage
	{
public:
	inline TMdaSiboWveCodec(); // Unknown type
protected:
	inline TMdaSiboWveCodec(TUid aUid,TInt aDerivedSize);
	};

class TMdaAlawSiboWveCodec : public TMdaSiboWveCodec
	{ 
public: 
	inline TMdaAlawSiboWveCodec();
	};

// Sun/NeXT "Au" Config Packages
class TMdaAuClipFormat : public TMdaClipFormat
	{
public:
	inline TMdaAuClipFormat();
	};

class TMdaAuCodec : public TMdaPackage
	{
public:
	inline TMdaAuCodec(); // Unknown type
protected:
	inline TMdaAuCodec(TUid aUid,TInt aDerivedSize);
	};

class TMdaPcm8BitAuCodec : public TMdaAuCodec
	{
public:
	inline TMdaPcm8BitAuCodec();
	};

class TMdaPcm16BitAuCodec : public TMdaAuCodec
	{
public:
	inline TMdaPcm16BitAuCodec();
	};

class TMdaAlawAuCodec : public TMdaAuCodec
	{ 
public: 
	inline TMdaAlawAuCodec();
	};

class TMdaMulawAuCodec : public TMdaAuCodec
	{
public:
	inline TMdaMulawAuCodec();
	};

// Raw Audio Config Packages
class TMdaRawAudioClipFormat : public TMdaClipFormat
	{
public:
	inline TMdaRawAudioClipFormat();
	};

class TMdaRawAudioCodec : public TMdaPackage
	{
public:
	inline TMdaRawAudioCodec(); // Unknown type
protected:
	inline TMdaRawAudioCodec(TUid aUid,TInt aDerivedSize);
	};

class TMdaMulawRawAudioCodec : public TMdaRawAudioCodec
	{
public:
	inline TMdaMulawRawAudioCodec();
	};

class TMdaAlawRawAudioCodec : public TMdaRawAudioCodec
	{
public:
	inline TMdaAlawRawAudioCodec();
	};

class TMdaS8PcmRawAudioCodec : public TMdaRawAudioCodec
	{
public:
	inline TMdaS8PcmRawAudioCodec();
	};

class TMdaU8PcmRawAudioCodec : public TMdaRawAudioCodec
	{
public:
	inline TMdaU8PcmRawAudioCodec();
	};

class TMdaSL16RawAudioCodec : public TMdaRawAudioCodec
	{
public:
	inline TMdaSL16RawAudioCodec();
	};

class TMdaSB16RawAudioCodec : public TMdaRawAudioCodec
	{
public:
	inline TMdaSB16RawAudioCodec();
	};

class TMdaUL16RawAudioCodec : public TMdaRawAudioCodec
	{
public:
	inline TMdaUL16RawAudioCodec();
	};

class TMdaUB16RawAudioCodec : public TMdaRawAudioCodec
	{
public:
	inline TMdaUB16RawAudioCodec();
	};

// Local Audio Stream Device
// Control local microphone/speaker audio stream
// May not function during telephone call

class TMdaLocalAudioDevice : public TMdaStreamDevice
	{
public:
	inline TMdaLocalAudioDevice();
	};

// Telephony Audio Stream Device
// Control telephony microphone+downlink/speaker+uplink audio stream
// Only functional during telephone call

class TMdaTelephonyAudioDevice : public TMdaStreamDevice
	{
public:
	inline TMdaTelephonyAudioDevice();
	};

class TMdaTelephonyStateQuery : public TMdaPackage
// This class is used in a ResourceConfig on a telephony port
// to determine the current state of telephony 
	{
public:
	inline TMdaTelephonyStateQuery();
public:
	TBool iIsTelephonyActive;
	};

// Client PCM Audio Stream Device
// Used to configure a 16bit PCM audio stream to/from client

class TMdaClientPCMAudioDevice : public TMdaStreamDevice
	{
public:
	inline TMdaClientPCMAudioDevice();
	};

// Volume ramping control on audio stream devices

class TMdaAudioStreamVolumeRamp : public TMdaPackage
	{
public:
	inline TMdaAudioStreamVolumeRamp();
public:
	TTimeIntervalMicroSeconds iDuration;
	};

// Tone Generator

enum TMdaToneGeneratorFunction
	{
	EMdaToneGeneratorConfig=0,
	EMdaToneGeneratorGetFixedNames=1,
	EMdaToneGeneratorPlay=2
	};

enum TMdaToneType // Play type prepared for
	{
	EMdaToneTypeSimple,
	EMdaToneTypeDTMF,
	EMdaToneTypeDesSeq,
	EMdaToneTypeFileSeq,
	EMdaToneTypeFixedSeq
	};

class TMdaToneGeneratorConfig : public TMdaReturnPackage
	{
public:
	inline TMdaToneGeneratorConfig();
	inline void SetReturnSize(TInt aReturnSize);
public:
	enum TMask
		{
		EPrepare		= 0x1,
		EVolumeChange	= 0x2,
		EPriorityChange = 0x4,
		EDTMFLengths    = 0x8,
		ESetRepeat		= 0x10,
		EVolumeRamp		= 0x20
		};
public:
	TUint32 iMask;
	TInt iVolume;
	TInt iMaxVolume;
	TInt iPriority;
	TMdaPriorityPreference iPref;
	TTimeIntervalMicroSeconds32 iDtmfToneOnLength;
	TTimeIntervalMicroSeconds32 iDtmfToneOffLength;
	TTimeIntervalMicroSeconds32 iDtmfPauseLength;
	TMdaToneType iType;
	TInt iFrequency;
	TTimeIntervalMicroSeconds iDuration;
	const TDesC8* iDes;
	TInt iDesLength;
	TInt iFixedSequenceNumber;
	TTimeIntervalMicroSeconds iRepeatTrailingSilence;
	TInt iRepeatCount;
	TTimeIntervalMicroSeconds iRampDuration;
	};

enum TMdaAudioOutputFunction
	{
	EMdaAudioOutputPrepare=0,
	EMdaAudioOutputConfig=1,
	EMdaAudioOutputWrite=2,
	EMdaAudioOutputStop=3,
	EMdaAudioOutputPlay=4
	};

class TMdaAudioOutputConfig : public TMdaReturnPackage
	{
public:
	inline TMdaAudioOutputConfig();
	inline void SetReturnSize(TInt aReturnSize);
public:
	enum TMask
		{
		ENull = 0x0,
		EQuery	= 0x1,
		EVolumeChange		= 0x2,
		EPriorityChange		= 0x4,
		EChannelsChange		= 0x8,
		ESampleRateChange	= 0x10
		};
public:
	TUint32 iMask;
	TInt						iPriority;
	TTimeIntervalMicroSeconds	iPosition;
	TInt						iMaxVolume;
	TInt						iVolume;
	TInt						iNumChannels;
	TInt						iSampleRate;
	TMdaPriorityPreference		iPref;
	};

class TMdaToneFixedSequenceNames : public TMdaRawPackage
	{
public:
	inline TMdaToneFixedSequenceNames();
public:
	TInt iCount;
	};

// Inlines 

inline TMdaAudioDataSettings::TMdaAudioDataSettings() :
TMdaDatatypeSettings(KUidMdaMediaTypeAudio,sizeof(TMdaAudioDataSettings)) 
	{
	Mem::FillZ(&iSampleRate,sizeof(TInt)*4);
	}

inline void TMdaAudioDataSettings::Query()
	{
	iChannels = KMdaUnknown;
	iSampleRate = KMdaUnknown;
	iVolume = KMdaUnknown;
	}// Call this when you just want to have caps and maxvolume filled

inline TMdaWavClipFormat::TMdaWavClipFormat() : 
TMdaClipFormat(KUidMdaClipFormatWav,sizeof(TMdaWavClipFormat)) {}

inline TMdaWavCodec::TMdaWavCodec() :
TMdaPackage(KUidMdaWavCodec,KNullUid,sizeof(TMdaWavCodec)) {}

inline TMdaCodecQuery::TMdaCodecQuery(TUid aType, TUid aUid,TInt aAdditionalSize) :
TMdaPackage(aType,aUid,sizeof(TMdaCodecQuery)+aAdditionalSize) {}

inline TMdaWavCodec::TMdaWavCodec(TUid aUid, TInt aDerivedSize) :
TMdaPackage(KUidMdaWavCodec,aUid,aDerivedSize) {}

inline TMdaPcmWavCodec::TMdaPcmWavCodec(TBits aBits) :
TMdaWavCodec(KUidMdaWavPcmCodec,sizeof(TMdaPcmWavCodec)), iBits(aBits) {}

inline TMdaAlawWavCodec::TMdaAlawWavCodec() :
TMdaWavCodec(KUidMdaWavAlawCodec,sizeof(TMdaAlawWavCodec)) {}

inline TMdaMulawWavCodec::TMdaMulawWavCodec() :
TMdaWavCodec(KUidMdaWavMulawCodec,sizeof(TMdaMulawWavCodec)) {}

inline TMdaImaAdpcmWavCodec::TMdaImaAdpcmWavCodec() :
TMdaWavCodec(KUidMdaWavImaAdpcmCodec,sizeof(TMdaImaAdpcmWavCodec)) {}

inline TMdaEpocWveClipFormat::TMdaEpocWveClipFormat() :
TMdaClipFormat(KUidMdaClipFormatEpocWve,sizeof(TMdaEpocWveClipFormat)) {}

inline TMdaEpocWveCodec::TMdaEpocWveCodec() :
TMdaPackage(KUidMdaEpocWveCodec,KNullUid,sizeof(TMdaEpocWveCodec)) {}

inline TMdaEpocWveCodec::TMdaEpocWveCodec(TUid aUid,TInt aDerivedSize) :
TMdaPackage(KUidMdaEpocWveCodec,aUid,aDerivedSize) {}

inline TMdaAlawEpocWveCodec::TMdaAlawEpocWveCodec() :
TMdaEpocWveCodec(KUidMdaEpocWveAlawCodec,sizeof(TMdaAlawEpocWveCodec)) {}

inline TMdaAdpcmEpocWveCodec::TMdaAdpcmEpocWveCodec() :
TMdaEpocWveCodec(KUidMdaEpocWveAdpcmCodec,sizeof(TMdaAdpcmEpocWveCodec)) {}

inline TMdaSiboWveClipFormat::TMdaSiboWveClipFormat() :
TMdaClipFormat(KUidMdaClipFormatSiboWve,sizeof(TMdaSiboWveClipFormat)) {}

inline TMdaSiboWveCodec::TMdaSiboWveCodec() :
TMdaPackage(KUidMdaEpocWveCodec,KNullUid,sizeof(TMdaSiboWveCodec)) {}

inline TMdaSiboWveCodec::TMdaSiboWveCodec(TUid aUid,TInt aDerivedSize) :
TMdaPackage(KUidMdaEpocWveCodec,aUid,aDerivedSize) {}

inline TMdaAlawSiboWveCodec::TMdaAlawSiboWveCodec() :
TMdaSiboWveCodec(KUidMdaEpocWveAlawCodec,sizeof(TMdaAlawSiboWveCodec)) {}

inline TMdaAuClipFormat::TMdaAuClipFormat() : 
TMdaClipFormat(KUidMdaClipFormatAu,sizeof(TMdaAuClipFormat)) {}

inline TMdaAuCodec::TMdaAuCodec() :
TMdaPackage(KUidMdaAuCodec,KNullUid,sizeof(TMdaAuCodec)) {}

inline TMdaAuCodec::TMdaAuCodec(TUid aUid,TInt aDerivedSize) :
TMdaPackage(KUidMdaAuCodec,aUid,aDerivedSize) {}

inline TMdaPcm16BitAuCodec::TMdaPcm16BitAuCodec() :
TMdaAuCodec(KUidMdaAu16PcmCodec,sizeof(TMdaPcm16BitAuCodec)) {}

inline TMdaPcm8BitAuCodec::TMdaPcm8BitAuCodec() :
TMdaAuCodec(KUidMdaAu8PcmCodec,sizeof(TMdaPcm8BitAuCodec)) {}

inline TMdaAlawAuCodec::TMdaAlawAuCodec() :
TMdaAuCodec(KUidMdaAuAlawCodec,sizeof(TMdaAlawAuCodec)) {}

inline TMdaMulawAuCodec::TMdaMulawAuCodec() :
TMdaAuCodec(KUidMdaAuMulawCodec,sizeof(TMdaMulawAuCodec)) {}

inline TMdaRawAudioClipFormat::TMdaRawAudioClipFormat() : 
TMdaClipFormat(KUidMdaClipFormatRawAudio,sizeof(TMdaRawAudioClipFormat)) {}

inline TMdaRawAudioCodec::TMdaRawAudioCodec() :
TMdaPackage(KUidMdaRawAudioCodec,KNullUid,sizeof(TMdaRawAudioCodec)) {}

inline TMdaRawAudioCodec::TMdaRawAudioCodec(TUid aUid,TInt aDerivedSize) :
TMdaPackage(KUidMdaRawAudioCodec,aUid,aDerivedSize) {}

inline TMdaMulawRawAudioCodec::TMdaMulawRawAudioCodec() :
TMdaRawAudioCodec(KUidMdaRawAudioMulawCodec,sizeof(TMdaMulawRawAudioCodec)) {}

inline TMdaAlawRawAudioCodec::TMdaAlawRawAudioCodec() :
TMdaRawAudioCodec(KUidMdaRawAudioAlawCodec,sizeof(TMdaAlawRawAudioCodec)) {}

inline TMdaS8PcmRawAudioCodec::TMdaS8PcmRawAudioCodec() :
TMdaRawAudioCodec(KUidMdaRawAudioS8PcmCodec,sizeof(TMdaS8PcmRawAudioCodec)) {}

inline TMdaU8PcmRawAudioCodec::TMdaU8PcmRawAudioCodec() :
TMdaRawAudioCodec(KUidMdaRawAudioU8PcmCodec,sizeof(TMdaU8PcmRawAudioCodec)) {}

inline TMdaSL16RawAudioCodec::TMdaSL16RawAudioCodec() :
TMdaRawAudioCodec(KUidMdaRawAudioSL16PcmCodec,sizeof(TMdaSL16RawAudioCodec)) {}

inline TMdaSB16RawAudioCodec::TMdaSB16RawAudioCodec() :
TMdaRawAudioCodec(KUidMdaRawAudioSB16PcmCodec,sizeof(TMdaSB16RawAudioCodec)) {}

inline TMdaUL16RawAudioCodec::TMdaUL16RawAudioCodec() :
TMdaRawAudioCodec(KUidMdaRawAudioUL16PcmCodec,sizeof(TMdaUL16RawAudioCodec)) {}

inline TMdaUB16RawAudioCodec::TMdaUB16RawAudioCodec() :
TMdaRawAudioCodec(KUidMdaRawAudioUB16PcmCodec,sizeof(TMdaUB16RawAudioCodec)) {}

inline TMdaLocalAudioDevice::TMdaLocalAudioDevice() : 
TMdaStreamDevice(KUidMdaLocalSoundDevice,sizeof(TMdaLocalAudioDevice)) {}

inline TMdaTelephonyAudioDevice::TMdaTelephonyAudioDevice() : 
TMdaStreamDevice(KUidMdaTelephonySoundDevice,sizeof(TMdaTelephonyAudioDevice)) {}

inline TMdaClientPCMAudioDevice::TMdaClientPCMAudioDevice() : 
TMdaStreamDevice(KUidMdaClientPCMSoundDevice,sizeof(TMdaClientPCMAudioDevice)) {}

inline TMdaAudioStreamVolumeRamp::TMdaAudioStreamVolumeRamp() :
TMdaPackage(KUidMdaAudioStreamVolumeRamp,KUidMdaAudioStreamVolumeRamp,sizeof(TMdaAudioStreamVolumeRamp)) {}

inline TMdaTelephonyStateQuery::TMdaTelephonyStateQuery() :
TMdaPackage(KUidMdaTelephonySoundDevice,KUidMdaTelephonyStateQuery,sizeof(TMdaTelephonyStateQuery)) {}
 
inline TMdaToneGeneratorConfig::TMdaToneGeneratorConfig() :
TMdaReturnPackage(KUidMdaToneGeneratorDevice,KUidMdaToneGeneratorDevice,sizeof(TMdaToneGeneratorConfig)) {}

inline void TMdaToneGeneratorConfig::SetReturnSize(TInt aReturnSize)
	{ TMdaReturnPackage::SetReturnSize(aReturnSize); }

inline TMdaAudioOutputConfig::TMdaAudioOutputConfig() : 
TMdaReturnPackage(KUidMdaAudioOutputStreamDevice,KUidMdaAudioOutputStreamDevice,sizeof(TMdaAudioOutputConfig)) {}

inline void TMdaAudioOutputConfig::SetReturnSize(TInt aReturnSize)
	{ TMdaReturnPackage::SetReturnSize(aReturnSize); }

inline TMdaToneFixedSequenceNames::TMdaToneFixedSequenceNames() :
TMdaRawPackage(sizeof(TMdaToneFixedSequenceNames)) {}


inline TMdaPrioritySettings::TMdaPrioritySettings() :
TMdaPackage(KUidMdaPrioritySettings,KUidMdaPrioritySettings,sizeof(TMdaPrioritySettings)) {}


#endif
