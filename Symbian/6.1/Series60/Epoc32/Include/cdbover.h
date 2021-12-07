// CDBOVER.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// CCommDbOverrideSettings class header

#ifndef __CDBOVER_H__
#define __CDBOVER_H__

#include <e32base.h>
#include <commdb.h>
#include <cdbpreftable.h>

class TCommDbIntOverride;
class TCommDbBoolOverride;
class TCommDbDes8Override;
class TCommDbDes16Override;
class CCommDbLongDesOverride;
class TCommDbIapConnectionPrefOverride;
class TCommDbIspConnectionPrefOverride;

// CCommDbOverrideSettings class
//
// Holds all information about CommDb overrides. Allows overrides to be set and checked

class CCommDbOverrideSettings : public CBase
	{
public:
	enum TParamList
		{
		EParamListPartial,
		EParamListFull
		};

	enum TValueType
		{
		EIntValue,
		EBoolValue,
		EDes8Value,
		EDes16Value,
		ELongDesValue
		};
public:
	IMPORT_C static CCommDbOverrideSettings* NewL(TParamList aParamList, TCommDbDatabaseType aType);	// aType parameter will be removed in 7.0
	CCommDbOverrideSettings(TParamList aParamList);
	IMPORT_C virtual ~CCommDbOverrideSettings();
//
	IMPORT_C TInt SetIntOverride(const TDesC& aTableName, const TDesC& aColumnName, TUint32 aValue);
	IMPORT_C TInt SetBoolOverride(const TDesC& aTableName, const TDesC& aColumnName, TBool aValue);
	IMPORT_C TInt SetDesOverride(const TDesC& aTableName, const TDesC& aColumnName, const TDesC8& aValue);
	IMPORT_C TInt SetDesOverride(const TDesC& aTableName, const TDesC& aColumnName, const TDesC16& aValue);
	IMPORT_C TInt SetLongDesOverride(const TDesC& aTableName, const TDesC& aColumnName, const TDesC& aValue);
//
	IMPORT_C TInt SetConnectionPreferenceOverride(const CCommsDbConnectionPrefTableView::TCommDbIapConnectionPref& aPref);
	IMPORT_C TInt SetConnectionPreferenceOverride(const CCommsDbConnectionPrefTableView::TCommDbIspConnectionPref& aPref);	// will be deprecated in 7.0
	IMPORT_C TInt GetConnectionPreferenceOverride(CCommsDbConnectionPrefTableView::TCommDbIapConnectionPref& aPref);
	IMPORT_C TInt GetConnectionPreferenceOverride(CCommsDbConnectionPrefTableView::TCommDbIspConnectionPref& aPref);		// will be deprecated in 7.0
//
	IMPORT_C TInt GetIntOverride(const TDesC& aTableName, const TDesC& aColumnName, TUint32& aValue);
	IMPORT_C TInt GetBoolOverride(const TDesC& aTableName, const TDesC& aColumnName, TBool& aValue);
	IMPORT_C TInt GetDesOverride(const TDesC& aTableName, const TDesC& aColumnName, TDes8& aValue);
	IMPORT_C TInt GetDesOverride(const TDesC& aTableName, const TDesC& aColumnName, TDes16& aValue);
	IMPORT_C TInt GetLongDesOverride(const TDesC& aTableName, const TDesC& aColumnName, TDes& aValue);
	IMPORT_C TInt GetLongDesOverrideLength(const TDesC& aTableName, const TDesC& aColumnName, TInt& aLength);
//
	IMPORT_C TBool Compare(CCommDbOverrideSettings* aOverrides) const;
	IMPORT_C TBool IsOverridden(const TDesC& aTableName, const TDesC& aColumnName, TValueType aType);
	inline TParamList PartialFull() const;
	inline TCommDbDatabaseType DatabaseType() const;	// will be deprecated in 7.0
protected:
	virtual void ConstructL(TCommDbDatabaseType aType);
	TInt FindOverride(const TDesC& aTableName, const TDesC& aColumnName, TValueType aType);
	TBool IllegalOverride(const TDesC& aTableName,  const TDesC& aColumnName);
	void CheckL(const TDesC& aTableName, const TDesC& aColumnName, TValueType aType);
protected:
	TParamList iPartialFull;
	CArrayFixFlat<TCommDbIntOverride>* iIntOverrides;
	CArrayFixFlat<TCommDbBoolOverride>* iBoolOverrides;
	CArrayFixFlat<TCommDbDes8Override>* iDes8Overrides;
	CArrayFixFlat<TCommDbDes16Override>* iDes16Overrides;
	CArrayFixFlat<CCommDbLongDesOverride*>* iLongDesOverrides;
	RArray<TCommDbIapConnectionPrefOverride> iIapOverrides;
	RArray<TCommDbIspConnectionPrefOverride> iIspOverrides;
	CCommsDatabase* iDb;
	};

#include <cdbover.inl>

#endif