// Mda\Common\Resource.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __MDA_COMMON_RESOURCE_H__
#define __MDA_COMMON_RESOURCE_H__

// Standard EPOC32 includes
#include <e32base.h>

// Public Media Server includes
#include <Mda\Common\Base.h>
#include <Mda\Common\Port.h>
#include <Mda\Common\Controller.h>
#include <Mda\Common\Resource.hrh>

// Uids
MDA_UID(KUidMdaResourceManager) // Resoruce Manager Uid
MDA_UID(KUidMdaSourceClip) // Resource Clip Handle Uids
MDA_UID(KUidMdaDestinationClip) 
MDA_UID(KUidMdaClipLocation) // Resource Clip Location/Format type Uids
MDA_UID(KUidMdaClipFormat) 
MDA_UID(KUidMdaSourceStream) // Resource Stream Handle Uids
MDA_UID(KUidMdaDestinationStream) 
MDA_UID(KUidMdaStreamDevice) // Resource Stream Device Uid
MDA_UID(KUidMdaFileResLoc) // Clip Location Uids
MDA_UID(KUidMdaDesResLoc) 
MDA_UID(KUidMdaClipDuration) // Time related Uids
MDA_UID(KUidMdaClipPrimeWindow) 
MDA_UID(KUidMdaClipCrop) 

// Unknown size

const TInt KMdaResourceSizeUnknown = KMdaUnknown;
const TInt KMdaRepeatForever = -2;

// Function numbers

enum // Resource Port Handle
	{
	EMLbResourceHandleConfig=EMLbPortNegotiate+1
	};

enum // Resource object functions
	{
	EMLbResourceObjectConfig=0,
	EMLbResourceObjectCreatePort=1
	};

enum // Clip Location
	{
	EMLbClipFunctionBase=EMLbResourceObjectCreatePort,
	EMLbClipLocRead,
	EMLbClipLocWrite
	};

enum // Resource event IDs
	{
	EMdaResourceEventIdConfigComplete,
	EMdaResourceEventIdConfigFailed,
	EMdaResourceEventIdSizeChanged,
	EMdaResourceEventIdDataChanged
	};

// Resource package classes

class TMdaResourceQuery : public TMdaPackage
	{
public:
	TMdaResourceQuery(TUid aType);
	};

class TMdaClipLocation : public TMdaPackage
	{
protected:
	inline TMdaClipLocation(TUid aUid, TInt aDerivedSize);
public:
	TInt iSize; // In bytes
	TInt iVisible; // In bytes
	};

class TMdaClipFormat : public TMdaPackage
	{
public:
	inline TMdaClipFormat();
protected:
	inline TMdaClipFormat(TUid aUid, TInt aDerivedSize);
	};

class TMdaClipFormatQuery : public TMdaClipFormat
	{
public:
	inline TMdaClipFormatQuery(TUid aUid, TInt aAdditionalSize);
	};

class TMdaStreamDevice : public TMdaPackage
	{
protected:
	inline TMdaStreamDevice(TUid aUid, TInt aDerivedSize);
	};

// Clip Locations

class TMdaFileClipLocation : public TMdaClipLocation
	{
public:
	inline TMdaFileClipLocation();
	inline TMdaFileClipLocation(const TDesC& aName);
public:
	TBuf<256> iName;
	};

class TMdaDesClipLocation : public TMdaClipLocation
	{
public:
	inline TMdaDesClipLocation();
	inline TMdaDesClipLocation(TDes8& aWriteableDes);
	inline TMdaDesClipLocation(const TDesC8& aReadOnlyDes);
public:
	TThreadId iThreadId;
	TDesC8* iDes;
	};

// Time related clip packages

class TMdaClipDuration : public TMdaDatatypeSettings
	{ // Used to query the duration of a clip
public:
	inline TMdaClipDuration();
public:
	TTimeIntervalMicroSeconds iDuration;
	TInt iBytesPerSecond;
	TInt64 iBytesFree;
	};

class TMdaClipPrimeWindow : public TMdaDatatypeSettings
	{ // Used to set/get a time window on a clip
public:
	inline TMdaClipPrimeWindow();
public:
	TTimeIntervalMicroSeconds iStart;
	TTimeIntervalMicroSeconds iEnd;
	TTimeIntervalMicroSeconds iTrailingSilence;
	TInt iRepeats;
	};

class TMdaClipCrop : public TMdaDatatypeSettings
	{ // Used to crop a clip
public:
	inline TMdaClipCrop();
public:
	TTimeIntervalMicroSeconds iCropFrom;
	TBool iRoundTimeUp;
	TBool iQueryOnly;
	};

// Inline functions

inline TMdaResourceQuery::TMdaResourceQuery(TUid aType) :
TMdaPackage(aType,KNullUid,sizeof(TMdaResourceQuery)) {}
	
inline TMdaClipLocation::TMdaClipLocation(TUid aUid, TInt aDerivedSize) :
TMdaPackage(KUidMdaClipLocation,aUid,aDerivedSize) {}

inline TMdaClipFormat::TMdaClipFormat(TUid aUid, TInt aDerivedSize) :
TMdaPackage(KUidMdaClipFormat,aUid,aDerivedSize) {}

inline TMdaClipFormatQuery::TMdaClipFormatQuery(TUid aUid, TInt aAdditionalSize) :
TMdaClipFormat(aUid,sizeof(TMdaClipFormat)+aAdditionalSize) {}
	
inline TMdaClipFormat::TMdaClipFormat() : 
TMdaPackage(KUidMdaClipFormat,KNullUid,sizeof(TMdaClipFormat)) {}

inline TMdaStreamDevice::TMdaStreamDevice(TUid aUid, TInt aDerivedSize) :
TMdaPackage(KUidMdaStreamDevice,aUid,aDerivedSize) {}

inline TMdaFileClipLocation::TMdaFileClipLocation() : 
TMdaClipLocation(KUidMdaFileResLoc,sizeof(TMdaFileClipLocation)) {}

inline TMdaFileClipLocation::TMdaFileClipLocation(const TDesC& aName) :
TMdaClipLocation(KUidMdaFileResLoc,sizeof(TMdaFileClipLocation)), 
iName(aName) {}

inline TMdaDesClipLocation::TMdaDesClipLocation() :
TMdaClipLocation(KUidMdaDesResLoc,sizeof(TMdaDesClipLocation)),
iThreadId(RThread().Id()) {}

inline TMdaDesClipLocation::TMdaDesClipLocation(const TDesC8& aReadOnlyDes) :
TMdaClipLocation(KUidMdaDesResLoc,sizeof(TMdaDesClipLocation)),
iThreadId(RThread().Id()),
iDes(&(TDesC8&)aReadOnlyDes) {}

inline TMdaDesClipLocation::TMdaDesClipLocation(TDes8& aWriteableDes) :
TMdaClipLocation(KUidMdaDesResLoc,sizeof(TMdaDesClipLocation)),
iThreadId(RThread().Id()),
iDes(&aWriteableDes) {}

inline TMdaClipDuration::TMdaClipDuration() :
TMdaDatatypeSettings(KUidMdaClipDuration,sizeof(TMdaClipDuration)),
iDuration(KMdaUnknown),
iBytesPerSecond(KMdaUnknown)	{}

inline TMdaClipPrimeWindow::TMdaClipPrimeWindow() :
TMdaDatatypeSettings(KUidMdaClipPrimeWindow,sizeof(TMdaClipPrimeWindow)),
iStart(KMdaUnknown),
iEnd(KMdaUnknown),
iTrailingSilence(KMdaUnknown),
iRepeats(KMdaUnknown) {}

inline TMdaClipCrop::TMdaClipCrop() :
TMdaDatatypeSettings(KUidMdaClipCrop,sizeof(TMdaClipCrop)),
iCropFrom(KMdaUnknown),
iRoundTimeUp(EFalse),
iQueryOnly(EFalse) {}

#endif
