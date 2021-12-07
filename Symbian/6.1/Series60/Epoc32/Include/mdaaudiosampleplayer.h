// MdaAudioSamplePlayer.h 
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

#ifndef __MDAAUDIOSAMPLEPLAYER_H_
#define __MDAAUDIOSAMPLEPLAYER_H_

/*
Notes:
 This file defines a simple sound data playing utility API.
  
Classes:
CMdaAudioPlayerUtility
 The interface to a simple sound data (file or descriptor) playing utility. 
 It is capable of playing sounds in any format recognised by the Media Server.

MMdaAudioPlayerCallback
 Mixin class that defines callback interface used for asynchronous 
 notification.

Usage:
 "NewFilePlayerL" is used to create an instance of a file player.
 "NewDesPlayerL" is used to create a descriptor player. If a descriptor is 
 used as the data source, it must remain valid until the player object has 
 been destroyed. In either case, the data must be a recognised file format
 such as a WAV, AU, or WVE with a supported encoding scheme.
 
 The player object will call "MMdaAudioPlayerCallback::MapcInitComplete" when 
 it has been initialised and is ready to play the sound.

 "Play" will begin playback.

 "Stop" can be used to end playback.

 If the end of the sound data is reached, playback will terminate 
 automatically and "MMdaAudioPlayerCallback::MapcPlayComplete" will be called 
 with aErr==KErrNone.

 If playback terminates for any other reason (such as interruption by a higher
 priority sound playing event) "MMdaAudioPlayerCallback::MapcPlayComplete" 
 will be called with the appropriate error value.

 "SetVolume" can be used to change the volume both before or during playback.
 The parameter should be between 0 and the result returned by calling 
 "MaxVolume"

*/

#include <e32base.h>
#include <Mda\Common\Controller.h>

class CMdaServer;

const TInt KMdaAudioPlayerUnknownDuration = -1;
const TInt KMdaAudioPlayerRepeatForever = -2;

enum TAudioPlayerUtilityPanics
	{
	EMdaAudioPlayerAPIFileAlreadyPlaying = 0,
	EMdaAudioPlayerAPINotReady = 1,
	EMdaAudioPlayerAPIVolumeOutofRange = 2
	};

class MMdaAudioPlayerCallback
	{
public: 
	virtual void MapcInitComplete(TInt aError, const TTimeIntervalMicroSeconds& aDuration)=0;
	virtual void MapcPlayComplete(TInt aError)=0;
	};

class CMdaAudioPlayerUtility : public CBase
	{
public:
	IMPORT_C static CMdaAudioPlayerUtility* NewFilePlayerL(const TDesC& aFileName, MMdaAudioPlayerCallback& aCallback, TInt aPriority=EMdaPriorityNormal, TMdaPriorityPreference aPref=EMdaPriorityPreferenceTimeAndQuality, CMdaServer* aServer=NULL);
	IMPORT_C static CMdaAudioPlayerUtility* NewDesPlayerL(TDes8& aData, MMdaAudioPlayerCallback& aCallback, TInt aPriority=EMdaPriorityNormal, TMdaPriorityPreference aPref=EMdaPriorityPreferenceTimeAndQuality, CMdaServer* aServer=NULL);	
	IMPORT_C static CMdaAudioPlayerUtility* NewDesPlayerReadOnlyL(const TDesC8& aData, MMdaAudioPlayerCallback& aCallback, TInt aPriority=EMdaPriorityNormal, TMdaPriorityPreference aPref=EMdaPriorityPreferenceTimeAndQuality, CMdaServer* aServer=NULL);	

	// Control functions
	virtual void Play()=0;
	virtual void Stop()=0;
	virtual void SetVolume(TInt aVolume)=0;
	virtual void SetRepeats(TInt aRepeatNumberOfTimes, const TTimeIntervalMicroSeconds& aTrailingSilence)=0;
	virtual void SetVolumeRamp(const TTimeIntervalMicroSeconds& aRampDuration)=0;

	// Query functions
	virtual const TTimeIntervalMicroSeconds& Duration()=0;
	virtual TInt MaxVolume()=0;
	};

#endif
