// FLDSET.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __FLDSET_H__
#define __FLDSET_H__

#include <e32std.h>
#include <e32base.h>
#include <fldinfo.h>
#include <fldbase.h>
#include <fldbltin.h>

//
// Classes declared in this file
class CTextFieldSet;
//
// Classes referenced
class RReadStream;
class RWriteStream;
class MFieldFactory;
class CTextFieldHeader;
class TTextFieldEntry;
class CStreamStore;
class CStoreMap;
class TRollbackInfo;

const TInt KFieldArrayGranularity=1;


class CTextFieldSet : public CBase
// The engine that keeps the field table up to date
	{
public:
	enum {ENoPasteLimit=-1};
public:
	IMPORT_C static CTextFieldSet* NewL(TInt aDocumentLength=0);
	IMPORT_C static CTextFieldSet* NewL(const MTextFieldFactory* aFactory,const CStreamStore& aStore,TStreamId aStreamId);
	IMPORT_C ~CTextFieldSet();
	//
	// Factory functions
	IMPORT_C void SetFieldFactory(MTextFieldFactory* aFactory);
	IMPORT_C MTextFieldFactory* FieldFactory()const;
	//
	IMPORT_C void Reset(); // removes all fields from the array and reinitialises field array
	//
	// Persistence
	IMPORT_C TStreamId StoreL(CStreamStore& aStore)const;
	IMPORT_C void RestoreL(const CStreamStore& aFieldStore,TStreamId aStreamId);
	//
	// Component persistence
	IMPORT_C void StoreFieldsL(CStreamStore& aStore,CStoreMap& aMap)const;
	IMPORT_C void RestoreFieldsL(const CStreamStore& aFieldStore);
	//
	// Headstream persistence
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream)const;
	//	Cut/Paste
	IMPORT_C TStreamId CopyToStoreL(CStreamStore& aStore,TInt aPos,TInt aLength)const;
	IMPORT_C void CopyComponentsL(CStreamStore& aStore,CStoreMap& aMap,TInt aPos,TInt aLength)const;
	IMPORT_C void CopyToStreamL(RWriteStream& aStream,TInt aPos,TInt aLength)const;
	IMPORT_C void PasteFromStoreL(const CStreamStore& aFieldStore,TStreamId aStreamId,TInt aPos,TInt aMaxLen=ENoPasteLimit);
	IMPORT_C void PasteComponentsL(const CStreamStore& aFieldStore,TInt aPos);
	IMPORT_C void PasteFromStreamL(RReadStream& aStream,TInt aPos,TInt aMaxLen=ENoPasteLimit);
	// Insert/Remove field
	IMPORT_C CTextField* NewFieldL(TUid aFieldType);
	IMPORT_C TInt InsertFieldL(TInt aPos,CTextField* aField,TUid aFieldType); // inserts a field (including text) into doc (returns error num if it fails)
	IMPORT_C TInt RemoveField(TInt aPos); // remove the field aPos is in
	IMPORT_C TInt NewFieldValueL(HBufC*& aBuf, TInt aPos); // returns new value of the field in aBuf (or returns false if aPos not in field)
	// Update field set
	IMPORT_C void NotifyInsertion(TInt aPos, TInt aNumberAdded);
	IMPORT_C void NotifyDeletion(TInt aPos, TInt aNumberRemoved);
	IMPORT_C void NotifyFieldUpdate(TInt aPos, TInt aNewFieldValueLength);
	// Utilities
	IMPORT_C TInt FieldCount() const; // returns total number of fields in document
	IMPORT_C TInt CharCount() const; // returns num characters in the document (according to fields)
	IMPORT_C TBool FindFields(TInt aPos) const; // Returns ETrue if aPos is in a field
	IMPORT_C TBool FindFields(TFindFieldInfo& aInfo,TInt aPos,TInt aRange=0) const; // finds num fields at least partly in range. Returns true if aPos is in field, and returns info on the first field in aRange
	IMPORT_C const CTextField* TextField(TInt aPos)const;
	// Rollback
	IMPORT_C void RollbackPaste(); // call to carry out rollback if a paste goes wrong
protected:
	CTextFieldSet();
	void ConstructL(TInt aDocumentLength);
	void ConstructL(const CStreamStore& aFieldStore,TStreamId aStreamId);
private:
	// persistence
	void StoreFieldsL(CStreamStore& aStore,CStoreMap& aMap,CArrayFixSeg<TTextFieldEntry>* aArray)const;
	void DoRestoreL(const CStreamStore& aFieldStore,TStreamId aStreamId);
	void DoRestoreFieldsL(CArrayFixSeg<TTextFieldEntry>* aArray,const CStreamStore& aFieldStore,TInt aStartIndex=0);
	void InternalizeL(CArrayFixSeg<TTextFieldEntry>* aArray,RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream,CArrayFixSeg<TTextFieldEntry>* aArray)const;
	void DoPasteL(CArrayFixSeg<TTextFieldEntry>* aSourceArray,TInt aPos);
	// utility functions
	void AddInitialFieldEntryL(CArrayFixSeg<TTextFieldEntry>* aArray,TInt aDocumentLength); // used to initialise the array
	void InsertEntryL(TInt aIndex,TTextFieldEntry& aEntry); // inserts into iFieldArray
	void InsertEntryL(TInt aIndex,TTextFieldEntry& aEntry,CArrayFixSeg<TTextFieldEntry>* aArray);
	void AppendEntryL(TTextFieldEntry& aEntry); // appends into iFieldArray
	void AppendEntryL(TTextFieldEntry& aEntry,CArrayFixSeg<TTextFieldEntry>* aArray);
	void CopyToArrayL(CArrayFixSeg<TTextFieldEntry>* aArray,TInt aPos,TInt aLength)const;
	TBool InField(const TInt aPos, TInt& anIndex, TInt& anOffset) const; // anOffset set to distance into field or gap
	void DeleteFieldEntry(TInt anIndex);
	void DeleteFieldEntry(CArrayFixSeg<TTextFieldEntry>* aArray,TInt anIndex);
	TTextFieldEntry SplitEntry(TInt aIndex,TInt aOffset,TInt aRange)const;
	TInt EntryLen(const TTextFieldEntry& aEntry)const;
	TInt EntryLen(TInt aIndex)const;
	// rollback
	void RecordRollbackInfoL(TInt aPastePos);
private:
	MTextFieldFactory* iFieldFactory;
	CArrayFixSeg<TTextFieldEntry>* iFieldArray; // Array of fields in the document
	TRollbackInfo* iRollbackInfo;
	__DECLARE_TEST;
	};

//
// Allows NULL streams id's to be written out
// when no reference is found in a store map.

class TFieldMapExternalizer : public MExternalizer<TStreamRef>
	{
private:
	friend class CPlainText;
	friend class CTextFieldSet;
private:
	IMPORT_C TFieldMapExternalizer(const CStoreMap& aMap);
	IMPORT_C void ExternalizeL(const TStreamRef& anObject,RWriteStream& aStream) const;
private:
	const CStoreMap* iMap;
	};

#endif
