// MdaAudioSampleEditor.h 
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

#ifndef __MDAAUDIOSAMPLEEDITOR_H_
#define __MDAAUDIOSAMPLEEDITOR_H_

/*
Notes:
 This file defines an audio editing utility API. 

Classes:
 CMdaAudioClipUtility
 Abstract utility base class providing play, record, crop, and positioning functions

 CMdaAudioRecorderUtility
 Concrete class for playing and recording to audio data using an audio device

 CMdaAudioConvertUtility
 Concrete class for converting audio data between different formats

*/

#include <e32base.h>

#include <Mda\Client\Resource.h>
#include <Mda\Client\Utility.h>
#include <Mda\Common\Audio.h>

const TInt KMdaAudioClipUtilityRepeatForever = -1;

class CMdaAudioType : public CBase
	{
public:	
	IMPORT_C virtual ~CMdaAudioType();
public:
	TMdaClipFormat* iFormat;
	TMdaPackage* iCodec;
	TMdaAudioDataSettings* iSettings;
	// Registry entries
	TMdaRegistryEntryData* iFormatInfo;
	TMdaRegistryEntryData* iCodecInfo;
	TBool iIsPlayOnly;
	};

enum TMdaAudioClipUtilityPanic
	{ // Panic category will be reported as "MdaAudioSampleEditor"
	EMdaAudioClipUtilityPanicNotReady = 1,
	EMdaAudioClipUtilityPanicPlayCalledWhileStillRecording = 2,
	EMdaAudioClipUtilityPanicRecordCalledWhileStillPlaying = 3,
	EMdaAudioClipUtilityPanicAlreadyPlaying = 4,
	EMdaAudioClipUtilityPanicAlreadyRecording= 5,
	EMdaAudioClipUtilityPanicAlreadyOpen = 6
	};

class CMdaClipUtilityImplData;

//
// CMdaAudioClipUtility
//
// Defines common clip utility functions 
//

class CMdaAudioClipUtility : public CBase
	{
public:
	enum TState
		{
		ENotReady = 0,
		EOpen,
		EPlaying,
		ERecording
		};
public:
	// Functionality common to all clip utilities
	virtual TState State();

	// State related
	virtual void Close();
	virtual void PlayL();
	virtual void RecordL();
	virtual void Stop();

	// Common editing/control related
	virtual void CropL();
	virtual void SetPosition(const TTimeIntervalMicroSeconds& aPosition);
	virtual const TTimeIntervalMicroSeconds& Position();
	virtual const TTimeIntervalMicroSeconds& RecordTimeAvailable();
	virtual const TTimeIntervalMicroSeconds& Duration();
	virtual void SetPlayWindow(const TTimeIntervalMicroSeconds& aStart, const TTimeIntervalMicroSeconds& aEnd);
	virtual void ClearPlayWindow();
	virtual void SetRepeats(TInt aRepeatNumberOfTimes, const TTimeIntervalMicroSeconds& aTrailingSilence);
	virtual CMdaAudioType* TypeL();

public:
	// Reserved functions - do not call
	virtual void ClipUtil_Reserved1();
	virtual void ClipUtil_Reserved2();
	virtual void ClipUtil_Reserved3();
	virtual void ClipUtil_Reserved4();

protected:
	CMdaClipUtilityImplData* iData;
	};

//
// CMdaAudioRecorderUtility
//
// Used to playback and record audio 
// Inherits Play, Record, Stop, etc. from CMdaAudioClipUtility
//
class CMdaAudioRecorderUtility : public CMdaAudioClipUtility
	{
public:
	enum TDeviceMode
		{
		EDefault=0,
		ETelephonyOrLocal=EDefault,
		ETelephonyMixed=1,
		ETelephonyNonMixed=2,
		ELocal=3
		};
public:

	// Static constructor
	IMPORT_C static CMdaAudioRecorderUtility* NewL(
						MMdaObjectStateChangeObserver& aObserver, 
						CMdaServer* aServer=NULL, 
						TInt aPriority=EMdaPriorityNormal, 
						TMdaPriorityPreference aPref=EMdaPriorityPreferenceTimeAndQuality);

	// Open existing file to playback from / record to
	virtual void OpenFileL(const TDesC& aFilename)=0;

	// Open existing audio data in memory to playback from / record to
	virtual void OpenDesL(const TDesC8& aData)=0;

	// Open generic audio object 
	virtual void OpenL(TMdaClipLocation* aLocation,	// Normally file or descriptor
						TMdaClipFormat* aFormat,		// Data format
						TMdaPackage* aArg1 = NULL,		// Normally codec to use
						TMdaPackage* aArg2 = NULL)=0;		// Normally audio settings

	// Set the audio device to use
	virtual void SetAudioDeviceMode(TDeviceMode aMode)=0;
	
	// Control the volume/gain on the audio device
	virtual TInt MaxVolume()=0;
	virtual TInt MaxGain()=0;
	virtual void SetVolume(TInt aVolume)=0;
	virtual void SetGain(TInt aGain)=0;
	virtual void SetVolumeRamp(const TTimeIntervalMicroSeconds& aRampDuration)=0;
	};

//
// CMdaAudioConvertUtility
//
// Used to convert audio between two different data formats
// Inherits Play, Record, Stop, etc. from CMdaAudioClipUtility
//

class CMdaAudioConvertUtility : public CMdaAudioClipUtility
	{
public:
	// Static constructor
	IMPORT_C static CMdaAudioConvertUtility* NewL(
						MMdaObjectStateChangeObserver& aObserver, 
						CMdaServer* aServer=NULL, 
						TInt aPriority = EMdaPriorityNormal, 
						TMdaPriorityPreference aPref = EMdaPriorityPreferenceTimeAndQuality);

	// Open two existing file to append from primary to secondary 
	virtual void OpenL(const TDesC& aPrimaryFile, const TDesC& aSecondaryFile)=0;

	// Open existing file and new/existing secondary
	virtual void OpenL(const TDesC& aPrimaryFile,
						TMdaClipLocation* aLocation,	// Normally file or descriptor
						TMdaClipFormat* aFormat,		// Data format
						TMdaPackage* aArg1 = NULL,		// Normally codec to use
						TMdaPackage* aArg2 = NULL)=0;	// Normally audio settings

	// Completely generic open for arbitrary primary and secondary
	virtual void OpenL(TMdaClipLocation* aPriLocation, 
						TMdaClipLocation* aSecLocation, 
						TMdaClipFormat* aPriFormat, 
						TMdaClipFormat* aSecFormat, 
						TMdaPackage* aPriArg1 = NULL, 
						TMdaPackage* aPriArg2 = NULL, 
						TMdaPackage* aSecArg1 = NULL, 
						TMdaPackage* aSecArg2 = NULL)=0;
	};

#endif

