// CDBSTORE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// CStoreableOverrideSettings class header

#ifndef __CDBSTORE_H__
#define __CDBSTORE_H__

#include <s32mem.h>
#include <cdbover.h>

class CStoreableOverrideSettings : public CCommDbOverrideSettings
	{
public:
	IMPORT_C static CStoreableOverrideSettings* NewL(TParamList aParamList, TCommDbDatabaseType aType);	// aType parameter will be removed in 7.0
	CStoreableOverrideSettings(TParamList aParamList);
	IMPORT_C ~CStoreableOverrideSettings();
	//
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C CBufFlat* StoreLC();
	IMPORT_C void RestoreL(HBufC8* aBuf);
	inline CBufStore* GetStore() const;
protected:
	virtual void ConstructL(TCommDbDatabaseType aType);
private:
	CBufStore* iStore;
	};

#include <cdbstore.inl>

#endif