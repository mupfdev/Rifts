// APGAPLST.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__APGAPLST_H__)
#define __APGAPLST_H__

#if !defined(__APAID_H__)
#include <apaid.h>
#endif
#if !defined(__APMSTD_H__)
#include <apmstd.h>
#endif
#if !defined(__BADESCA_H__)
#include <badesca.h>
#endif

// classes defined:
class CApaAppData;
class CApaAppList;
class CApaAppViewData;
//
// classes referenced:
class CApaMaskedBitmap;
class CApaAppInfoFileReader;
class RFs;
//

const TInt KApaMaxAppIcons=3;
const TInt KApaIconIndexSmall=0;
const TInt KApaIconIndexMedium=1;
const TInt KApaIconIndexLarge=2;

const TInt KIgnoreScreenMode=-1;
/**
 * Utility class with smaller RAM footprint than TApaAppEntry
 *
 * @internal
 */
class CApaAppEntry : public CBase
	{
public:
	static CApaAppEntry* NewL(const TApaAppEntry& aAppEntry);
	~CApaAppEntry();
	void Get(TApaAppEntry& aAppEntry) const;
private:
	CApaAppEntry(const TUidType& aUidType);
	void ConstructL(const TDesC& aFileName);
public:
	TUidType iUidType;
	HBufC* iFullName;
	};

/**
 * The CApaAppData class represents the data associated with a CApaApplication, such as its 
 * caption, capabilities and icons. These should be accessed through the Apparc Server.
 *
 * @internal
 */
class CApaAppData : public CBase
	{
public:
	IMPORT_C TApaAppEntry AppEntry() const;
	inline TPtrC Caption() const;
	inline TPtrC ShortCaption() const;
	IMPORT_C CApaMaskedBitmap* Icon(TInt aIconIndex) const;
	IMPORT_C void Capability(TDes8& aCapabilityBuf)const;
	inline TBool IsPresent() const;
	// ER5
	IMPORT_C TDataTypePriority DataType(const TDataType& aDataType) const;
	// ER6
	IMPORT_C CApaMaskedBitmap* Icon(TSize aSize) const;
	IMPORT_C CArrayFixFlat<TSize>* IconSizesL() const;
	// ER6.1
	IMPORT_C CArrayPtrFlat<CApaAppViewData>* Views() const;
	IMPORT_C CDesCArray* OwnedFiles() const;
	IMPORT_C TBool CanUseScreenMode(TInt aScreenMode);
	//
	inline void Lock();
	inline void Unlock();
private:
	static CApaAppData* NewL(const TApaAppEntry& aAppEntry,const TDesC& aDefaultAppInfoFileName,RFs& aFs);
	CApaAppData();
	~CApaAppData();
	void ConstructL(const TApaAppEntry& aAppEntry,const TDesC& aDefaultAppInfoFileName,RFs& aFs);
	void GetCaptionsFromFile(RFs& aFs);
	void GetIconsL(CApaAppInfoFileReader& aAppInfoFile);
	TBool UpdateAifL(RFs& aFs,const TDesC& aDefaultAppInfoFileName);
	void GetAifDataL(RFs& aFs,const TDesC& aDefaultAppInfoFileName);
	TBool IsPending()const;
	void GetViewsL(CApaAppInfoFileReader& aAppInfoFile);
private:
	enum { ENotPresent, ENotPresentPendingUpdate, EPresentPendingUpdate, EIsPresent, ESuperseded };
private:
	CArrayPtrFlat<CApaMaskedBitmap>* iIcons;
	HBufC* iCaption;
	HBufC* iShortCaption;
	HBufC* iFullName;
	TInt iIsPresent; // uses enum
	TUidType iUidType;
	TInt iReferenceCount;
	CApaAppData* iNext;
	TApaAppCapabilityBuf iCapabilityBuf;
	CApaAppEntry* iSuccessor;
	TTime iAifTimeStamp;
	CArrayFixFlat<TDataTypeWithPriority> iDataTypeArray;
	CArrayPtrFlat<CApaAppViewData>* iViewDataArray;
	CDesCArray* iOwnedFileArray;
private:
	friend class CApaAppList;
	};


/**
 * The CApaAppViewData class represents the data associated with an application view.
 *
 * @internal
 * @since App-Framework_6.1
 */
class CApaAppViewData : public CBase
	{
public:
	IMPORT_C TUid Uid() const;
	inline TPtrC Caption() const;
	IMPORT_C CApaMaskedBitmap* Icon(const TSize& aSize) const;
	IMPORT_C CArrayFixFlat<TSize>* IconSizesL() const;
	IMPORT_C TInt ScreenMode() const;
public:
	~CApaAppViewData();
	static CApaAppViewData* NewLC();
	void SetUid(TUid aUid);
	void SetCaptionL(const TDesC& aCaption);
	void AddIconL(CApaMaskedBitmap* aIcon);
	void SetScreenMode(TInt aScreenMode);
private:
	CApaAppViewData();
	void ConstructL();
private:
	CArrayPtrFlat<CApaMaskedBitmap>* iIcons;
	HBufC* iCaption;
	TUid iUid;
	TInt iScreenMode;
	};


/**
 * The MApaAppListObserver interface allows a class to be informed when a CApaAppList is 
 * updated.
 *
 * @internal
 */
class MApaAppListObserver
	{
public:
	virtual void NotifyUpdate(TInt aReason)=0;
	};

/**
 * The CApaAppList class provides a list of all available applications present on a device.
 * Its functionality should be accessed through the Apparc Server.
 *
 * @internal
 */
class CApaAppList : public CBase
	{
public: // Internal to Symbian
	IMPORT_C static CApaAppList* NewL(RFs& aFs,CApaAppFinder* aAppFinder); // takes ownership of aAppFinder
public:
	IMPORT_C void UpdateL();
	IMPORT_C void Purge();
	IMPORT_C TInt Count() const;
	IMPORT_C CApaAppData* FirstApp() const;
	IMPORT_C CApaAppData* FirstApp(TInt aScreenMode) const;
	IMPORT_C CApaAppData* NextApp(const CApaAppData* aApp) const;
	IMPORT_C CApaAppData* NextApp(const CApaAppData* aApp, TInt aScreenMode) const;
	IMPORT_C CApaAppData* AppDataByUid(TUid aAppUid) const;
	IMPORT_C TInt UpdateCounter() const;
	// ER5
	IMPORT_C TUid PreferredDataHandlerL(const TDataType& aDataType) const;
	IMPORT_C void StartIdleUpdateL();
	IMPORT_C void StartIdleUpdateL(MApaAppListObserver* aObserver);
	IMPORT_C TBool IsIdleUpdateComplete() const;
	//
	IMPORT_C ~CApaAppList();
private:
	CApaAppList(RFs& aFs,CApaAppFinder* aAppFinder);
	void UpdateNextAppL(TApaAppEntry& aAppEntry,TBool& aHasChanged);
	void SetPending(CApaAppData* aAppData);
	void SetNotFound(CApaAppData* aAppData, TBool& aHasChanged);
	static TInt IdleUpdateCallback(TAny* aObject);
	TInt IdleUpdate();
	void StopIdler();
private:
	RFs& iFs;
	CApaAppData* iAppData; // linked list of apps
	CApaAppFinder* iAppFinder;
	TInt iUpdateCounter;
	CPeriodic* iIdler;
	TApaAppEntry iCurrentApp;
	TInt iOldUpdateCounter;
	MApaAppListObserver* iObserver;
	};


//
// inlines
//

inline TPtrC CApaAppViewData::Caption() const
	{ return *iCaption; }

inline TPtrC CApaAppData::Caption() const
	{ return *iCaption; }

inline TPtrC CApaAppData::ShortCaption() const
	{ return *iShortCaption; }

inline TBool CApaAppData::IsPresent() const
	{ return iIsPresent; }

inline void CApaAppData::Lock()
	{ ++iReferenceCount; }

inline void CApaAppData::Unlock()
	{ --iReferenceCount; }

#endif
