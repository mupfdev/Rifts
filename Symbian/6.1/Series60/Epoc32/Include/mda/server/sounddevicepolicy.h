// Mda\Server\SoundDevicePolicy.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// *********** All classes Internal to Symbian *************//

#ifndef __MDA_SERVER_SOUNDDEVICEPOLICY_H__
#define __MDA_SERVER_SOUNDDEVICEPOLICY_H__

// Public Media Server includes
#include <Mda\Common\Audio.h>

#include <Mda\Server\Base.h>
#include <Mda\Server\Environment.h>
#include <Mda\Server\Buffer.h>
#include <Mda\Server\AudioIo.h>
#include <Mda\Server\AudioCodecs.h>

// Recorder code

class CMdaSoundRecorderPolicy; // Forward reference

// Internal to Symbian
class MMdaSoundRecorderClient
	{
public:
	virtual void SreclDataFilled(CMdaAudioBuffer* aBuffer)=0; // Called when buffer used up
	virtual void SreclFatalRecordError(TInt aError)=0; // Called when stopped due to error
	};

// Internal to Symbian
class TMdaSoundRecorderClient
// T class used as interface between client and policy object
	{
public:
	TMdaSoundRecorderClient(CMdaSoundRecorderPolicy* aPolicy, MMdaSoundRecorderClient& aClient);
	inline MMdaSoundRecorderClient& Client();
	inline const TMdaAudioDataSettings& GetCaps();
	inline const TTimeIntervalMicroSeconds& MaxLatency();
	inline const TTimeIntervalMicroSeconds& MinLatency();
	inline TInt SampleRate();
	inline TInt Channels();
	inline TInt Gain();
	inline TInt Flags();
	inline const TTimeIntervalMicroSeconds& Latency();
	inline void SetAudio(TInt aSampleRate, TInt aChannels, TTimeIntervalMicroSeconds aLatency);
	inline void SetGain(TInt aVolume);
	inline void SetFlags(TInt aFlags);
	inline void AddL();
	inline void Remove();
	inline void RecordL();
	inline void Stop();
	inline void SetCurrentBuffer(CMdaAudioBuffer* aBuffer);
	inline CMdaAudioBuffer*& Buffer();
	inline TInt SamplesRecorded();
	inline void SetPriority(TInt aPriority, TMdaPriorityPreference aPriorityPref);
	inline TMdaPriorityPreference PriorityPref();
	inline void SetRecording(TBool aIsRecording);
	inline TBool IsRecording();
public:
	TPriQueLink iLink;
private:
	CMdaSoundRecorderPolicy* iPolicy;
	MMdaSoundRecorderClient& iClient;
	CMdaAudioBuffer* iCurrentBuffer;
	TBool iIsRecording;
	TInt iSampleRate;
	TInt iChannels;
	TInt iGain;
	TInt iFlags;
	TTimeIntervalMicroSeconds iLatency;
	TMdaPriorityPreference iPriorityPref;
	friend class CMdaSoundRecorderPolicy;
	};

// Internal to Symbian
class CMdaSoundRecorderPolicy : public CMdaObject
// Abstract sound recorder policy class
	{
protected:
	inline CMdaSoundRecorderPolicy();
	// Must be implemented by derived class implementing policy
	virtual const TMdaAudioDataSettings& GetCaps()=0;
	virtual const TTimeIntervalMicroSeconds& MaxLatency()=0;
	virtual const TTimeIntervalMicroSeconds& MinLatency()=0;
	virtual void AddClientL(TMdaSoundRecorderClient& aClient)=0;
	virtual void RemoveClient(TMdaSoundRecorderClient& aClient)=0;
	virtual void ClientRecordL(TMdaSoundRecorderClient& aClient)=0;
	virtual void ClientStop(TMdaSoundRecorderClient& aClient)=0;
	virtual void ClientGainChanged(TMdaSoundRecorderClient& aClient)=0;
	virtual void ClientBufferChanged(TMdaSoundRecorderClient& aClient)=0;
	virtual void SetNextDataBlock()=0;
	virtual void HandleRecordError(TInt aReason)=0;
	virtual TInt SamplesRecorded()=0;
protected:
	TPriQue<TMdaSoundRecorderClient> iClients;
	friend class TMdaSoundRecorderClient;
	};

// Player code

class CMdaSoundPlayerPolicy; // Forward reference

// Internal to Symbian
class MMdaSoundPlayerClient
	{
public:
	virtual void SpcDataUsed(CMdaAudioBuffer* aBuffer)=0; // Called when buffer used up
	virtual void SpcFatalPlayError(TInt aError)=0; // Called when stopped due to error
	};

// Internal to Symbian
class TMdaSoundPlayerClient
// T class used as interface between client and policy object
	{
public:
	TMdaSoundPlayerClient(CMdaSoundPlayerPolicy* aPolicy, MMdaSoundPlayerClient& aClient);
	inline MMdaSoundPlayerClient& Client();
	inline const TMdaAudioDataSettings& GetCaps();
	inline const TTimeIntervalMicroSeconds& MaxLatency();
	inline const TTimeIntervalMicroSeconds& MinLatency();
	inline TInt SampleRate();
	inline TInt Channels();
	inline TInt Volume();
	inline TInt Flags();
	inline const TTimeIntervalMicroSeconds& Latency();
	inline void SetAudio(TInt aSampleRate, TInt aChannels, TTimeIntervalMicroSeconds aLatency);
	inline void SetVolume(TInt aVolume);
	inline void SetFlags(TInt aFlags);
	inline void AddL();
	inline void Remove();
	inline void PlayL();
	inline void Stop();
	inline void SetCurrentBuffer(CMdaAudioBuffer* aBuffer);
	inline CMdaAudioBuffer*& Buffer();
	inline TInt SamplesPlayed();
	inline void SetPriority(TInt aPriority, TMdaPriorityPreference aPriorityPref);
	inline TMdaPriorityPreference PriorityPref();
	inline void SetPlaying(TBool aIsPlaying);
	inline TBool IsPlaying();
public:
	TPriQueLink iLink;
private:
	CMdaSoundPlayerPolicy* iPolicy;
	MMdaSoundPlayerClient& iClient;
	CMdaAudioBuffer* iCurrentBuffer;
	TBool iIsPlaying;
	TInt iSampleRate;
	TInt iChannels;
	TInt iVolume;
	TInt iFlags;
	TTimeIntervalMicroSeconds iLatency;
	TMdaPriorityPreference iPriorityPref;
	friend class CMdaSoundPlayerPolicy;
	};

// Internal to Symbian
class CMdaSoundPlayerPolicy : public CMdaObject
// Abstract sound player policy class
	{
protected:
	inline CMdaSoundPlayerPolicy();
	// Must be implemented by derived class implementing policy
	virtual const TMdaAudioDataSettings& GetCaps()=0;
	virtual const TTimeIntervalMicroSeconds& MaxLatency()=0;
	virtual const TTimeIntervalMicroSeconds& MinLatency()=0;
	virtual void AddClientL(TMdaSoundPlayerClient& aClient)=0;
	virtual void RemoveClient(TMdaSoundPlayerClient& aClient)=0;
	virtual void ClientPlayL(TMdaSoundPlayerClient& aClient)=0;
	virtual void ClientStop(TMdaSoundPlayerClient& aClient)=0;
	virtual void ClientVolumeChanged(TMdaSoundPlayerClient& aClient)=0;
	virtual void ClientBufferChanged(TMdaSoundPlayerClient& aClient)=0;
	virtual void SetNextDataBlock()=0;
	virtual void HandlePlayError(TInt aReason)=0;
	virtual TInt SamplesPlayed()=0;
protected:
	TPriQue<TMdaSoundPlayerClient> iClients;
	friend class TMdaSoundPlayerClient;
	};

//
// Interface to policy objects on a sound device
// These can used to gain direct access to the policy objects of a device
// in order to be a direct client obeying the same policy
//

IMPORT_C CMdaSoundRecorderPolicy* GetDeviceRecorderPolicy(CMdaObject* aDevice);
IMPORT_C CMdaSoundPlayerPolicy* GetDevicePlayerPolicy(CMdaObject* aDevice);

// Recorder inlines

inline TMdaSoundRecorderClient::TMdaSoundRecorderClient(CMdaSoundRecorderPolicy* aPolicy, MMdaSoundRecorderClient& aClient) :
iPolicy(aPolicy), iClient(aClient)
	{
	}

inline void TMdaSoundRecorderClient::SetAudio(TInt aSampleRate, TInt aChannels, TTimeIntervalMicroSeconds aLatency)
	{
	ASSERT(!IsRecording());
	iSampleRate = aSampleRate;
	ASSERT(aChannels>0);
	ASSERT(aChannels<3);
	iChannels = aChannels;
	ASSERT(aLatency >= iPolicy->MinLatency());
	ASSERT(aLatency <= iPolicy->MaxLatency());
	iLatency = aLatency;
	}

inline void TMdaSoundRecorderClient::SetGain(TInt aGain)
	{
	ASSERT(aGain >= 0);
	ASSERT(aGain <= iPolicy->GetCaps().iMaxVolume);
	iGain = aGain;
	if (IsRecording())
		iPolicy->ClientGainChanged(*this);
	}

inline void TMdaSoundRecorderClient::SetFlags(TInt aFlags)
	{
	iFlags = aFlags;
	}

inline void TMdaSoundRecorderClient::AddL()
	{
	iPolicy->AddClientL(*this);
	}

inline void TMdaSoundRecorderClient::Remove()
	{
	iPolicy->RemoveClient(*this);
	}

inline void TMdaSoundRecorderClient::RecordL()
	{
	iPolicy->ClientRecordL(*this);
	}

inline void TMdaSoundRecorderClient::Stop()
	{
	iPolicy->ClientStop(*this);
	iCurrentBuffer = NULL;
	}

inline void TMdaSoundRecorderClient::SetCurrentBuffer(CMdaAudioBuffer* aBuffer)
	{
	ASSERT(aBuffer?(!iCurrentBuffer):ETrue);
	iCurrentBuffer = aBuffer;
	if (IsRecording())
		iPolicy->ClientBufferChanged(*this);
	}

inline MMdaSoundRecorderClient& TMdaSoundRecorderClient::Client()
	{
	return iClient;
	}

inline const TMdaAudioDataSettings& TMdaSoundRecorderClient::GetCaps()
	{
	return iPolicy->GetCaps();
	}

inline const TTimeIntervalMicroSeconds& TMdaSoundRecorderClient::MaxLatency()
	{
	return iPolicy->MaxLatency();
	}

inline const TTimeIntervalMicroSeconds& TMdaSoundRecorderClient::MinLatency()
	{
	return iPolicy->MinLatency();
	}

inline CMdaAudioBuffer*& TMdaSoundRecorderClient::Buffer()
	{
	return iCurrentBuffer;
	}

inline TInt TMdaSoundRecorderClient::SamplesRecorded()
	{
	return iPolicy->SamplesRecorded();
	}

inline void TMdaSoundRecorderClient::SetPriority(TInt aPriority, TMdaPriorityPreference aPriorityPref)
	{
	iLink.iPriority = aPriority;
	iPriorityPref = aPriorityPref;
	}

inline TBool TMdaSoundRecorderClient::IsRecording()
	{
	return iIsRecording;
	}

inline TInt TMdaSoundRecorderClient::SampleRate()
	{
	return iSampleRate;
	}

inline TInt TMdaSoundRecorderClient::Channels()
	{
	return iChannels;
	}

inline TInt TMdaSoundRecorderClient::Gain()
	{
	return iGain;
	}

inline TInt TMdaSoundRecorderClient::Flags()
	{
	return iFlags;
	}

inline const TTimeIntervalMicroSeconds& TMdaSoundRecorderClient::Latency()
	{
	return iLatency;
	}

inline TMdaPriorityPreference TMdaSoundRecorderClient::PriorityPref()
	{
	return iPriorityPref;
	}

inline void TMdaSoundRecorderClient::SetRecording(TBool aIsRecording)
	{
	iIsRecording = aIsRecording;
	}

inline CMdaSoundRecorderPolicy::CMdaSoundRecorderPolicy()
: iClients(_FOFF(TMdaSoundRecorderClient,iLink))
	{
	}

// Player inlines

inline TMdaSoundPlayerClient::TMdaSoundPlayerClient(CMdaSoundPlayerPolicy* aPolicy, MMdaSoundPlayerClient& aClient) :
iPolicy(aPolicy), iClient(aClient)
	{
	}

inline void TMdaSoundPlayerClient::SetAudio(TInt aSampleRate, TInt aChannels, TTimeIntervalMicroSeconds aLatency)
	{
	ASSERT(!IsPlaying());
	iSampleRate = aSampleRate;
	ASSERT(aChannels>0);
	ASSERT(aChannels<3);
	iChannels = aChannels;
	ASSERT(aLatency >= iPolicy->MinLatency());
	ASSERT(aLatency <= iPolicy->MaxLatency());
	iLatency = aLatency;
	}

inline void TMdaSoundPlayerClient::SetVolume(TInt aVolume)
	{
	ASSERT(aVolume >= 0);
	ASSERT(aVolume <= iPolicy->GetCaps().iMaxVolume);
	iVolume = aVolume;
	if (IsPlaying())
		iPolicy->ClientVolumeChanged(*this);
	}

inline void TMdaSoundPlayerClient::SetFlags(TInt aFlags)
	{
	iFlags = aFlags;
	}

inline void TMdaSoundPlayerClient::AddL()
	{
	iPolicy->AddClientL(*this);
	}

inline void TMdaSoundPlayerClient::Remove()
	{
	iPolicy->RemoveClient(*this);
	}

inline void TMdaSoundPlayerClient::PlayL()
	{
	iPolicy->ClientPlayL(*this);
	}

inline void TMdaSoundPlayerClient::Stop()
	{
	iPolicy->ClientStop(*this);
	iCurrentBuffer = NULL;
	}

inline void TMdaSoundPlayerClient::SetCurrentBuffer(CMdaAudioBuffer* aBuffer)
	{
	ASSERT(aBuffer?(!iCurrentBuffer):ETrue);
	iCurrentBuffer = aBuffer;
	if (IsPlaying())
		iPolicy->ClientBufferChanged(*this);
	}

inline MMdaSoundPlayerClient& TMdaSoundPlayerClient::Client()
	{
	return iClient;
	}

inline const TMdaAudioDataSettings& TMdaSoundPlayerClient::GetCaps()
	{
	return iPolicy->GetCaps();
	}

inline const TTimeIntervalMicroSeconds& TMdaSoundPlayerClient::MaxLatency()
	{
	return iPolicy->MaxLatency();
	}

inline const TTimeIntervalMicroSeconds& TMdaSoundPlayerClient::MinLatency()
	{
	return iPolicy->MinLatency();
	}

inline CMdaAudioBuffer*& TMdaSoundPlayerClient::Buffer()
	{
	return iCurrentBuffer;
	}

inline TInt TMdaSoundPlayerClient::SamplesPlayed()
	{
	return iPolicy->SamplesPlayed();
	}

inline void TMdaSoundPlayerClient::SetPriority(TInt aPriority, TMdaPriorityPreference aPriorityPref)
	{
	iLink.iPriority = aPriority;
	iPriorityPref = aPriorityPref;
	}

inline void TMdaSoundPlayerClient::SetPlaying(TBool aIsPlaying)
	{
	iIsPlaying = aIsPlaying;
	}

inline TBool TMdaSoundPlayerClient::IsPlaying()
	{
	return iIsPlaying;
	}

inline TInt TMdaSoundPlayerClient::SampleRate()
	{
	return iSampleRate;
	}

inline TInt TMdaSoundPlayerClient::Channels()
	{
	return iChannels;
	}

inline TInt TMdaSoundPlayerClient::Volume()
	{
	return iVolume;
	}

inline TInt TMdaSoundPlayerClient::Flags()
	{
	return iFlags;
	}

inline const TTimeIntervalMicroSeconds& TMdaSoundPlayerClient::Latency()
	{
	return iLatency;
	}

inline TMdaPriorityPreference TMdaSoundPlayerClient::PriorityPref()
	{
	return iPriorityPref;
	}

inline CMdaSoundPlayerPolicy::CMdaSoundPlayerPolicy()
: iClients(_FOFF(TMdaSoundPlayerClient,iLink))
	{
	}


#endif
