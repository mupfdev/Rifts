// MdaAudioOutputStream.h 
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __MDAAUDIOOUTPUTSTREAM_H__
#define __MDAAUDIOOUTPUTSTREAM_H__

/*
Notes:
This file defines a simple audio streaming API
  
Classes:
CMdaAudioOutputStream
The interface to a simple audio output stream player.
 
MMdaAudioOutputStreamCallback
Mixin class that defines callback interface used for asynchronous 
notification.

Usage:
"NewL" is used to create an instance of a stream
 
"WriteL" is called to write data to the stream.  The playback will start when 
either all of the first bufer has been copied to the player plugin, or the
player plugin's own buffer is full.  "MMdaAudioOutputStreamCallback::MaoscBufferCopied"
will be called with the address of the buffer and an error value when the plugin
has finished with the buffer.  Usually this will be when the buffer has been copied
to the server, but could indicate an error has happened or that the client has stopped
the stream playing before this buffer has been copied.

"Stop" can be used to end playback.

If the end of the sound data is reached, playback will terminate 
automatically and "MMdaAudioOutputStreamCallback::MaoscPlayComplete" will be called 
with aErr==KErrUnderFlow.

If playback terminates for any other reason "MMdaAudioOutputStreamCallback::MaoscPlayComplete" 
will be called with the appropriate error value.

"MaxVolume" can be used to get the maximum value for the volume.

"Volume" can be used to get the current value for the volume.

"SetVolume" can be used to change the volume both before or during playback.
The parameter should be between 0 and the result returned by calling MaxVolume

"Open" the object must be opened before use

"Position" can be used to get the amount of data played as time.

"SetPriority" can be called to set the priority

"SetAudioPropertiesL" can be called to set the sample rate and number of channels
if the stream is stopped.
*/

#include <e32base.h>
#include <Mda\Client\Utility.h>
#include <Mda\common\controller.h>
#include <Mda\common\Base.h>

enum TMdaStreamPlayerPanic
	{
	EMdaStreamPlayerPanicBusyPlaying=0,
	EMdaStreamPlayerPanicNotPlaying=2,
	EMdaStreamPlayerPanicVolumeOutOfRange=4,
	EMdaStreamPlayerPanicNotOpen=6,
	EMdaStreamPlayerPanicAlreadyOpen=8,
	EMdaStreamPlayerPanicPriorityOutOfRange=10,
	EMdaStreamPlayerPanicIncorrectAudioPackage=12
	};

class MMdaAudioOutputStreamCallback 
	{
public:
	virtual void MaoscOpenComplete(TInt aError) = 0;
	virtual void MaoscBufferCopied(TInt aError, const TDesC8& aBuffer) = 0;
	virtual void MaoscPlayComplete(TInt aError) = 0;
	};

class CMdaAudioOutputStream : public CBase
	{
public:
	IMPORT_C static CMdaAudioOutputStream* NewL(MMdaAudioOutputStreamCallback& aCallBack,CMdaServer* aServer = NULL);
	//
	virtual void SetAudioPropertiesL(TInt aSampleRate, TInt aChannels) = 0;
	virtual void Open(TMdaPackage* aSettings) = 0;
	virtual TInt MaxVolume() = 0;
	virtual TInt Volume() = 0;
	virtual void SetVolume(const TInt aNewVolume) = 0;
	virtual void SetPriority(TInt aPriority, TMdaPriorityPreference aPref) = 0;
	virtual void WriteL(const TDesC8& aData) = 0;
	virtual void Stop() = 0;
	virtual const TTimeIntervalMicroSeconds& Position() = 0;
protected:
	CMdaAudioOutputStream();
	};

#endif

