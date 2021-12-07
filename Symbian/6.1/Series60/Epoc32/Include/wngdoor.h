// WNGDOOR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__WNGDOOR_H__)
#define __WNGDOOR_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__APAMDR_H__)
#include <apamdr.h>
#endif

//
// Classes defined
class CWordModelHeader;
class TWordModelHeaderFactory;
class CWordModelHeaderV2;
class TWordModelHeaderFactoryV2;
//
// Class referenced
class CWordModel;
class TWordModelStoreResolver;

const TUid KUidWordApp = {0x10003A64};

class CWordModelHeader : public CApaModelHeader
	{
public:
	IMPORT_C CWordModelHeader(CWordModel* aModel);
	IMPORT_C virtual ~CWordModelHeader();
	IMPORT_C virtual void StoreL(CStreamStore& aStore,CStreamDictionary& aDict)const;
	IMPORT_C void RestoreL(const CStreamStore& aStore,const CStreamDictionary& aDict);
	IMPORT_C virtual TApaAppIdentifier AppId()const;
	IMPORT_C void DetachFromStoreL(CPicture::TDetach aDegree);
	IMPORT_C CWordModel* Model();
protected:
	CWordModel*	iModel;
	};


//
//

class TWordModelHeaderFactory : public MApaModelHeaderFactory
	{
public:
	IMPORT_C TWordModelHeaderFactory(const TFileName& aPrintDriverPath);
	IMPORT_C CApaModelHeader* NewHeaderL(const CStreamStore& aStore,const CStreamDictionary& aDict,
										const TApaAppIdentifier& aAppId)const;
private:
	TFileName iPrintDriverPath;
	};

//
// Takes ownership of the referenced word model
//
class CWordModelHeaderV2 : public CApaModelHeader
	{
	friend class TWordModelHeaderFactoryV2;
public:
	IMPORT_C ~CWordModelHeaderV2();
public:	// from CApaModelHeader
	IMPORT_C void StoreL(CStreamStore& aStore,CStreamDictionary& aDict)const;
	IMPORT_C TApaAppIdentifier AppId()const;
	IMPORT_C void DetachFromStoreL(CPicture::TDetach aDegree);
public:
	IMPORT_C void RestoreL(const CStreamStore& aStore,const CStreamDictionary& aDict);
	IMPORT_C CWordModel* Model();
	void SetFactory(MApaModelHeaderFactory* aFactory); // takes ownership
private:
	CWordModelHeaderV2(CWordModel* aModel);
private:
	CWordModel*	iModel;
	TWordModelStoreResolver* iResolver; // created during restore
	MApaModelHeaderFactory* iHeaderFactory;
	};


//
//

class TWordModelHeaderFactoryV2 : public MApaModelHeaderFactory
	{
public:
	IMPORT_C TWordModelHeaderFactoryV2(const TFileName& aPrintDriverPath);
	IMPORT_C CApaModelHeader* NewHeaderL(const CStreamStore& aStore,const CStreamDictionary& aDict,
										const TApaAppIdentifier& aAppId)const;
private:
	TFileName iPrintDriverPath;
	};




/** Wrapper for application model */
class CWordModelHeaderV3 : public CApaModelHeader
	{
	friend class TWordModelHeaderFactoryV3;
public:
	IMPORT_C ~CWordModelHeaderV3();
public:	// from CApaModelHeader
	IMPORT_C void StoreL(CStreamStore& aStore,CStreamDictionary& aDict)const;
	IMPORT_C TApaAppIdentifier AppId()const;
	IMPORT_C void DetachFromStoreL(CPicture::TDetach aDegree);
public:
	IMPORT_C void RestoreL(const CStreamStore& aStore,const CStreamDictionary& aDict);
	IMPORT_C CWordModel* Model();
	void SetFactory(MApaModelHeaderFactory* aFactory); // takes ownership
private:
	CWordModelHeaderV3(CWordModel* aModel);
private:
	CWordModel*	iModel;
	TWordModelStoreResolver* iResolver; // created during restore
	MApaModelHeaderFactory* iHeaderFactory;
	};


/** Mimimal header factory for efficiency
 * Does not restore header or footer information from the document
 */
class TWordModelHeaderFactoryV3 : public MApaModelHeaderFactory
	{
public:
	IMPORT_C TWordModelHeaderFactoryV3();
	IMPORT_C CApaModelHeader* NewHeaderL(const CStreamStore& aStore,const CStreamDictionary& aDict,
										const TApaAppIdentifier& aAppId) const;
	};


#endif