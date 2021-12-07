// APAMDR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __APAMDR_H__
#define __APAMDR_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__GDI_H__)
#include <gdi.h>
#endif
#if !defined(__APADBASE_H__)
#include <apadbase.h>
#endif

// classes defined:
class TApaModelDoorFactory;
class CApaModelDoor;
class CApaModelHeader;
class MApaModelHeaderFactory;
//
// classes referenced:
class RReadStream;
class RWriteStream;
class CStreamStore;
class CStreamDictionary;
class CEmbeddedStore;
class TApaAppIdentifier;
//


class TApaModelDoorFactory : public MPictureFactory
// Recognizes KUidPictureTypeDoor and creates CApaModelDoor pictures
	{
public:
	IMPORT_C TApaModelDoorFactory(const MApaModelHeaderFactory* aFactory);
	//
	// from MPictureFactory
	IMPORT_C void NewPictureL(TPictureHeader& aPictureHeader,const CStreamStore& aPictureStore)const; // used to create CApaDoor's during document restore only 
private:
	const MApaModelHeaderFactory* iHeaderFactory;
	};


class CApaModelDoor : public CApaDoorBase
// Provides the persistant representation of a CApaDoor while acting as a wrapper around an app's model
	{
public:
	IMPORT_C static CApaModelDoor* NewL(CApaModelHeader* aHeader);
	IMPORT_C static CApaModelDoor* NewLC(CApaModelHeader* aHeader);
	IMPORT_C static CApaModelDoor* NewL(const CStreamStore& aStore,TStreamId aHeadStreamId,const MApaModelHeaderFactory* aFactory);
	//
	inline CApaModelHeader* ModelHeader() { return iModelHeader; }
	inline void SetFormat(TFormat aFormat) { iFormat = aFormat; }
	//
	IMPORT_C TStreamId StoreL(CStreamStore& aStore) const;
	IMPORT_C void RestoreL(const CStreamStore& aStore,TStreamId aHeadStreamId,const MApaModelHeaderFactory* aFactory);
	//
	IMPORT_C ~CApaModelDoor();
	//
	// from CPicture
	IMPORT_C void DetachFromStoreL(TDetach /*aDegree*/=EDetachFull);
	IMPORT_C void ExternalizeL(RWriteStream& aStream)const;
	IMPORT_C void Draw(CGraphicsContext& aGc,const TPoint& aTopLeft,const TRect& aClipRect,MGraphicsDeviceMap* aMap)const; 
	IMPORT_C void GetOriginalSizeInTwips(TSize& aSize)const;
	IMPORT_C void SetScaleFactor(TInt aScaleFactorWidth,TInt aScaleFactorHeight); 
	IMPORT_C TInt ScaleFactorWidth()const; 
	IMPORT_C TInt ScaleFactorHeight()const;
	//
private:
	CApaModelDoor();
	CApaModelDoor(CApaModelHeader* aHeader);
	//
	static CStreamDictionary* ReadStreamDictionaryLC(const CStreamStore& aSourceStore,TStreamId aStreamId);
	static void CopyStoreL(const CEmbeddedStore& aSourceStore,RWriteStream& aTargetStream);
	void InternalizeModelL(const MApaModelHeaderFactory* aFactory);
	//
	// from CApaDoorBase
	TSize GlassDoorSize()const;
private:
	CApaModelHeader* iModelHeader;
	CEmbeddedStore* iStore;
	TSize iScaleFactor;
	CBufSeg* iStoreHost; // the host for the embedded store, if the door has been detached from its originating store
	};


class CApaModelHeader : public CBase
// Abstract wrapper for an applications model - used for file format conversion etc
	{
public:
	virtual void StoreL(CStreamStore& aStore,CStreamDictionary& aDict) const=0;
	virtual TApaAppIdentifier AppId()const=0;
	virtual void DetachFromStoreL(CPicture::TDetach aDegree)=0;
private:
	IMPORT_C virtual void Reserved_1();
	};


class MApaModelHeaderFactory
	{
public:
	virtual CApaModelHeader* NewHeaderL(const CStreamStore& aStore,const CStreamDictionary& aDict,const TApaAppIdentifier& aAppId)const=0;
	};


#endif