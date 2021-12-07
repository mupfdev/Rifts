// CDBTEMP.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Comms Database Template Record View header

#ifndef __CDBTEMP_H__
#define __CDBTEMP_H__

#include <d32dbms.h>

class CCommsDatabaseBase;
class CCommsDbTableView;

class CCommsDbTemplateRecord : public CBase
	{
public:
	IMPORT_C static CCommsDbTemplateRecord* NewL(CCommsDatabaseBase* aDb,const TDesC& aTableName);
	CCommsDbTemplateRecord();
	IMPORT_C ~CCommsDbTemplateRecord();
//
// Record operations
//
	IMPORT_C TInt Modify();
	IMPORT_C TInt Delete();
	IMPORT_C TInt StoreModifications();
	IMPORT_C void CancelModifications();
//
// Reads
//
	IMPORT_C void ReadTextL(const TDesC& aColumn, TDes8& aValue);
	IMPORT_C void ReadTextL(const TDesC& aColumn, TDes16& aValue);
	IMPORT_C HBufC* ReadLongTextLC(const TDesC& aColumn);
	IMPORT_C void ReadUintL(const TDesC& aColumn, TUint32& aValue);
	IMPORT_C void ReadBoolL(const TDesC& aColumn, TBool& aValue);
	IMPORT_C void ReadTypeAttribL(const TDesC& aColumn, TDbColType& aColType, TUint32& aAttrib);
	IMPORT_C void ReadColumnLengthL(const TDesC& aColumn, TInt& aLength);
//
// Writes
//
	IMPORT_C void WriteTextL(const TDesC& aColumn, const TDesC8& aValue);
	IMPORT_C void WriteTextL(const TDesC& aColumn, const TDesC16& aValue);
	IMPORT_C void WriteLongTextL(const TDesC& aColumn, const TDesC& aValue);
	IMPORT_C void WriteUintL(const TDesC& aColumn, const TUint32& aValue);
	IMPORT_C void WriteBoolL(const TDesC& aColumn, const TBool& aValue);
//
// Get table name
//
	IMPORT_C void GetTableName(TDes& aTableName) const;
//
// See whether there is a record
//
	IMPORT_C TBool TemplateRecordExists();
//
private:
	void ConstructL(CCommsDatabaseBase* aDb, const TDesC& aTableName);
	void Reposition();
private:
	CCommsDbTableView* iView;
	TBool iRecordExists;
	};

#endif