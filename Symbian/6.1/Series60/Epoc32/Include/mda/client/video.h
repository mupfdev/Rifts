// Mda\Client\Video.h
//
// Copyright (c) 1998-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __MDA_CLIENT_VIDEO_H__
#define __MDA_CLIENT_VIDEO_H__

#ifndef __MDA_COMMON_RESOURCE_H__
#include <Mda\Common\Resource.h>
#endif
#ifndef __MDA_COMMON_VIDEO_H__
#include <Mda\Common\Video.h>
#endif

// Media Server Bitmap Device

class TMdaFbsBitmapDevice : public TMdaStreamDevice
	{
public:
	inline TMdaFbsBitmapDevice();
	};

class TMdaFbsBitmapHandle : public TMdaPackage
	{
public:
	inline TMdaFbsBitmapHandle();
public:
	TInt iBitmapHandle;
	};

class TMdaFbsBitmapMaskHandle : public TMdaPackage
	{
public:
	inline TMdaFbsBitmapMaskHandle();
public:
	TInt iBitmapHandle;
	};

#include <Mda\Client\Video.inl>

#endif

