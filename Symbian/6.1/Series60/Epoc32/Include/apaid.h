// APAID.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __APAID_H__
#define __APAID_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__APADEF_H__)
#include <apadef.h>
#endif

// classes defined:
class TApaAppIdentifier;
class TApaAppEntry;
class CApaAppFinder;
//
// classes referenced:
class RReadStream;
class RWriteStream;
class RFs;
//

class TApaAppIdentifier
	{
public:
	IMPORT_C TApaAppIdentifier();
	IMPORT_C TApaAppIdentifier(TUid aAppUidType,const TFileName& aDllName);
	IMPORT_C void ExternalizeL(RWriteStream& aStream)const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
public:
	TUid iAppUid;
	TFileName iFullName;
	};


class TApaAppEntry
	{
public:
	IMPORT_C TApaAppEntry();
	IMPORT_C TApaAppEntry(const TUidType& aAppUidType,const TFileName& aDllName);
	IMPORT_C void ExternalizeL(RWriteStream& aStream)const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
public:
	TUidType iUidType;
	TFileName iFullName;
	};


class TApaAppInfo
	{
public:
	IMPORT_C TApaAppInfo();
	IMPORT_C TApaAppInfo(TUid aAppUid,const TFileName& aDllName,const TApaAppCaption& aCaption);
	IMPORT_C TApaAppInfo(TUid aAppUid,const TFileName& aDllName,const TApaAppCaption& aCaption,const TApaAppCaption& aShortCaption);
	IMPORT_C void ExternalizeL(RWriteStream& aStream)const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
public:
	TUid iUid;
	TFileName iFullName;
	TApaAppCaption iCaption;
	TApaAppCaption iShortCaption;
	};


/**
 * The TApaAppViewInfo class encapsulates the basic information available on an application view.
 *
 * @since App-Framework_6.1
 */
class TApaAppViewInfo
	{
public:
	IMPORT_C TApaAppViewInfo();
	IMPORT_C TApaAppViewInfo(TUid aViewUid,const TApaAppCaption& aViewCaption,TInt aScreenMode);
	IMPORT_C void ExternalizeL(RWriteStream& aStream)const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
public:
	TUid iUid;
	TApaAppCaption iViewCaption;
	TInt iScreenMode;
	};
typedef CArrayFixFlat<TApaAppViewInfo> CApaAppViewArray;


class TApaAppCapability
// expandable class - add new members to the end, add them to the end of int/ext also, and increment the version no.
// default value for all data members must be 0
	{
public:
	IMPORT_C static void CopyCapability(TDes8& aDest,const TDesC8& aSource);
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	//
	enum TEmbeddability {
		ENotEmbeddable=0,
		EEmbeddable,
		EEmbeddableOnly };
public:
	TEmbeddability iEmbeddability;
	TBool iSupportsNewFile;
	TBool iAppIsHidden; // not shown in the Shell etc.
	TBool iLaunchInBackground;	// Series 60 extension to allow apps to be launched in the background	
	TApaAppGroupName iGroupName; // Series 60 extension to allow apps to be categorized according a logical group name, e.g. 'games'
private:
	enum { EVersion=3 };
	};
typedef TPckgBuf<TApaAppCapability> TApaAppCapabilityBuf;


class CApaAppFinder : public CBase
	{
public:
	virtual void FindAllAppsL()=0; // sets up a scan for all apps
	virtual TBool NextL(TApaAppEntry& aEntry)=0; // increments a scan for all apps
	virtual TFileName FindAppL(const TDesC& aFileName,TUid aFileUid)=0; // searches for a particular app - should support wildcards in aFileName
	//
	virtual TFileName TempPath()const=0; // should return the drive and path of the temp directory
	virtual TFileName DefaultAppInfoFileName()const=0; // should return the full name, path and drive of the default icon file
	};


#endif
