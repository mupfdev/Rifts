// APGDOOR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __APGDOOR_H__
#define __APGDOOR_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__S32STD_H__)
#include <s32std.h>
#endif
#if !defined(__GDI_H__)
#include <gdi.h>
#endif
#if !defined(__APPARC_H__)
#include <apparc.h>
#endif
#if !defined(__APADBASE_H__)
#include <apadbase.h>
#endif

#ifdef _UNICODE
#define KUidApaDoorDocStream KUidApaDoorDocStream16
#else
#define KUidApaDoorDocStream KUidApaDoorDocStream8
#endif
const TUid KUidApaDoorDocStream8={0x10000144};
const TUid KUidApaDoorDocStream16={0x10003A35};

// classes defined:
class CApaDoor;
class TApaPictureFactory;
//
// classes referenced:
class CEmbeddedStore;
//

class CApaDoor : public CApaDoorBase
// A wrapper for embedded CApaDocuments
// Can display either as an icon or as a glass picture
	{
public:
	IMPORT_C static CApaDoor* NewLC(RFs& aFs, CApaDocument& aDoc,const TSize& aDefaultIconSizeInTwips); // call to create a new door in iconic format - restoration is achieved with TApaPictureFactory
	IMPORT_C static CApaDoor* NewL(RFs& aFs, CApaDocument& aDoc,const TSize& aDefaultIconSizeInTwips); // call to create a new door in iconic format - restoration is achieved with TApaPictureFactory
	IMPORT_C static CApaDoor* NewL(RFs& aFs, const CStreamStore& aStore,TStreamId aStreamId,CApaProcess& aProcess); // restoring constructor called by TApaPictureFactory
	//
	IMPORT_C void SetFormatToIconL();
	IMPORT_C void SetFormatToGlassL();
	IMPORT_C void SetFormatToTemporaryIconL(TBool aEnabled=ETrue);
	//
	IMPORT_C CApaDocument* DocumentL(TBool aCheckPassword=EFalse); // returns a pointer to the doc, restoring it if necessary. Checks password if required.
	inline TDesC* Caption()const;
	IMPORT_C TUid AppUidL()const;
	//
	// persistence methods
	IMPORT_C void RestoreL(const CStreamStore& aStore,TStreamId aHeadStreamId);
	TStreamId StoreL(CStreamStore& aStore) const;
	//
	IMPORT_C ~CApaDoor();
	//
	// from CPicture
	void Draw(CGraphicsContext& aGc,const TPoint& aTopLeft,const TRect& aClipRect,
						MGraphicsDeviceMap* aMap)const; // draws according to current iPicFormat
	void DetachFromStoreL(TDetach aDegree=EDetachFull);
	void GetOriginalSizeInTwips(TSize& aSize)const;
	void SetScaleFactor(TInt aScaleFactorWidth,TInt aScaleFactorHeight);
	void SetCropInTwips(const TMargins& aMargins);
	TPictureCapability Capability() const;
	void GetCropInTwips(TMargins& aMargins) const;
	TInt ScaleFactorWidth() const;
	TInt ScaleFactorHeight() const;
private:
	CApaDoor(RFs& aFs, CApaProcess& aProcess);
	CApaDoor(RFs& aFs, CApaDocument& aDoc,const TSize& aDefaultIconSizeInTwips);
	void ConstructL();
	void GetCaptionFromFile(const TParse& aParser);
	//
	void SetIconSizeInTwips(TSize aSize); // for use of factory
	//
	void StoreDocL(CPersistentStore& aStore)const;
	void RestoreDocL(const CPersistentStore& aStore);
	CPicture* GetDefaultIconL(const TSize& aIconSizeInTwips);
	void RestoreDoorStateL(const CStreamStore& aStore,const CStreamDictionary& streamDic);
	static CStreamDictionary* ReadStreamDictionaryLC(const CStreamStore& aStore,TStreamId aStreamId);
	static void CopyStoreL(const CEmbeddedStore& aSourceStore,RWriteStream& aTargetStream);
	void ExternalizeStateStreamL(CStreamStore& aStore,CStreamDictionary& aStreamDict)const;
	void InternalizeStateStreamL(const CStreamStore& aStore,const CStreamDictionary& aStreamDict,TSize aDefaultIconSize);
	//
	// required so CPicture's can be swizzled
	void ExternalizeL(RWriteStream& aStream)const;
	// from CApaDoorBase
	virtual TSize GlassDoorSize()const;
	void GetAppUidAndFilenameFromDocL(TUid& aAppUid, TParse& aParser);
	TBool GetAppUidAndFilenameFromStreamL(TUid& aAppUid, TParse& aParser);
private:
	RFs& iFs;
	HBufC* iAppCaption; // name of the app used to create the embedded object
	CApaProcess* iApaProcess;
	CApaDocument* iApaDoc;
	CPicture* iPicture; // the current view of the door, either iconic or glass
	CEmbeddedStore* iStore; // store containing the doc
	CBufSeg* iStoreHost; // the host for the embedded store, if the door has been detached from its originating store
	__MUTABLE TSize iIconSizeInTwips;
	//
	friend class TApaPictureFactory;
	};


class TApaPictureFactory : public MPictureFactory
// Recognizes KUidPictureTypeDoor and creates CApaDoor pictures
	{
public:
	IMPORT_C TApaPictureFactory(CApaProcess* aAppProcess);
	inline void SetIconSize(TSize aIconSizeInTwips);
	//
	// from MPictureFactory
	IMPORT_C void NewPictureL(TPictureHeader& aPictureHeader,const CStreamStore& aPictureStore)const; // used to create CApaDoor's during document restore only 
private:
	CApaProcess* iApaProcess;
	TSize iIconSize;
	TInt iSpare;
	};


//
// inlines
//

inline TDesC* CApaDoor::Caption()const 
	{ return iAppCaption; }

inline void TApaPictureFactory::SetIconSize(TSize aIconSizeInTwips)
	{ iIconSize = aIconSizeInTwips; }

#endif
