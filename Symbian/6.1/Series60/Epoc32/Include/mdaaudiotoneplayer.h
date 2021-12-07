// MdaAudioTonePlayer.h 
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

//
// Notes:
//
// This file defines the API for generating various types of audio
// tones on an EPOC device.
//
// Tone types include:
//
// 1. Simple (sine) tone of specified frequency and duration
// 2. DTMF sequence consisting of characters 0-9 A-F * # , and white space
// 3. Fixed sequence from a list (including human readable names)
// 4. Sequence from file or descriptor (data format is platform specific)
//

#ifndef __MDAAUDIOTONEPLAYER_H__
#define __MDAAUDIOTONEPLAYER_H__

#include <Mda\Common\Audio.h>
#include <Mda\Client\Controller.h>

class CMdaServer; // Forward reference

enum TMdaTonePlayerPanic
	{
	EMdaTonePlayerPanicNotReady=0,
	EMdaTonePlayerPanicBusyPreparing=1,
	EMdaTonePlayerPanicBusyPlaying=2,
	EMdaTonePlayerPanicInvalidSequenceNumber=3,
	EMdaTonePlayerPanicVolumeOutOfRange=4,
	EMdaTonePlayerPanicInvalidDuration=5,
	EMdaTonePlayerPanicInvalidRepeatCount=6
	};

enum TMdaAudioToneUtilityState
	{
	EMdaAudioToneUtilityNotReady=0,
	EMdaAudioToneUtilityPrepared,
	EMdaAudioToneUtilityPlaying
	};


//
// Pass KInfiniteDurationDTMFToneOnLength as 
// aToneOnLength parameter to SetDTMFLengths()
// to play only the first DTMF tone of supplied 
// string until CancelPlay() is called
//
const TInt KMdaInfiniteDurationDTMFToneOnLength = -1; 
const TInt KMdaAudioToneRepeatForever = -2;

//
// Derive from MMdaAudioToneObserver
// to use the tone utility.
// Callbacks will be made on completion of
// asynchronous PrepareToPlayXxxx & Play function
// to indicate success or failure
//
class MMdaAudioToneObserver
	{
public:
	virtual void MatoPrepareComplete(TInt aError)=0;
	virtual void MatoPlayComplete(TInt aError)=0;
	};

//
// To use the tone utility:
// 1. Create an instance by calling NewL
// 2. Call the appropriate PrepareToPlay variant for the required tone type
//    and wait for the callback indicating success
// 3. Call Play and either wait for the callback to indicate completion, 
//    or call CancelPlay to end playback early
// 4. Delete the instance
//
class CMdaAudioToneUtility : public CBase
	{
public:
	IMPORT_C static CMdaAudioToneUtility* NewL(MMdaAudioToneObserver& aObserver, CMdaServer* aServer=NULL);
	//
	virtual TMdaAudioToneUtilityState State()=0;
	//
	virtual TInt MaxVolume()=0;
	virtual TInt Volume()=0;
	virtual void SetVolume(TInt aVolume)=0;
	virtual void SetPriority(TInt aPriority, TMdaPriorityPreference aPref)=0;
	virtual void SetDTMFLengths(TTimeIntervalMicroSeconds32 aToneOnLength,TTimeIntervalMicroSeconds32 aToneOffLength,TTimeIntervalMicroSeconds32 aPauseLength)=0;
	virtual void SetRepeats(TInt aRepeatNumberOfTimes, const TTimeIntervalMicroSeconds& aTrailingSilence)=0;
	virtual void SetVolumeRamp(const TTimeIntervalMicroSeconds& aRampDuration)=0;
	virtual TInt FixedSequenceCount()=0;
	virtual const TDesC& FixedSequenceName(TInt aSequenceNumber)=0;
	//
	virtual void PrepareToPlayTone(TInt aFrequency, const TTimeIntervalMicroSeconds& aDuration)=0;
	virtual void PrepareToPlayDTMFString(const TDesC& aDTMF)=0;
	virtual void PrepareToPlayDesSequence(const TDesC8& aSequence)=0;
	virtual void PrepareToPlayFileSequence(const TDesC& aFilename)=0;
	virtual void PrepareToPlayFixedSequence(TInt aSequenceNumber)=0;
	virtual void CancelPrepare()=0;
	//
	virtual void Play()=0;
	virtual void CancelPlay()=0;
	};

#endif
