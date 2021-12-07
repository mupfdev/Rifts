// Mda\Client\Audio.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
#ifndef __MDA_CLIENT_AUDIO_H__
#define __MDA_CLIENT_AUDIO_H__

// Standard EPOC32 includes
#include <e32base.h>

// Public Media Server includes
#include <Mda\Common\Resource.h>
#include <Mda\Common\Audio.h>
#include <Mda\Client\Base.h>
#include <Mda\Client\Port.h>
#include <Mda\Client\Controller.h>

// Audio connection

class TMdaAudioConnection : public TMdaConnection
	{
public:
	inline TMdaAudioConnection(const RMdaSrcPort& aSrc, const RMdaDstPort& aDst):
		TMdaConnection(aSrc,aDst,KUidMdaMediaTypeAudio) {}
	};

#endif
