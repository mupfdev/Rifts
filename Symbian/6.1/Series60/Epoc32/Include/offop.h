// OFFOP.H
// 
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//

#if !defined(__OFFOP_H__)
#define __OFFOP_H__

#if !defined (__MSVIDS_H__)
#include <MSVIDS.H>
#endif

#if !defined (__MSVUIDS_H__)
#include <MSVUIDS.H>
#endif

#if !defined(__MSVSTORE_H__)
#include <MSVSTORE.H>
#endif

#include "miut_err.h"

const TInt KCurrentOfflineOperationArrayVersion = 2;
_LIT(KImcmPanic, "IMCM");

///////////////////////////////////////////////////////////////////////////////
// CImOffLineOperation container for cached off line operation, to be performed
// on next connection to remote server.
class CImOffLineOperation : public CBase
	{
    public: 
        enum TOffLineOpType
        {
            EOffLineOpNone               = 0x0000,
//
            EOffLineOpCopyToLocal        = 0x0001,
            EOffLineOpCopyFromLocal,
            EOffLineOpCopyWithinService,
//
            EOffLineOpMoveToLocal        = 0x0010,
            EOffLineOpMoveFromLocal,
            EOffLineOpMoveWithinService,
//
            EOffLineOpDelete             = 0x0020,
//
            EOffLineOpChange             = 0x0030,
            EOffLineOpCreate,
//
            EOffLineOpMtmSpecific        = 0x0100, 
        };
    
    public: // Constructor of a null operation
        IMPORT_C CImOffLineOperation(); 
        IMPORT_C ~CImOffLineOperation(); 
    public: // Set this operation to a specific type.
        inline   void SetCopyToLocal(TMsvId aMessageId, TMsvId aTargetFolderId);
        inline   void SetCopyFromLocal(TMsvId aMessageId, TMsvId aTargetFolderId);
        inline   void SetCopyWithinService(TMsvId aMessageId, TMsvId aTargetFolderId);
//
        inline   void SetMoveToLocal(TMsvId aMessageId, TMsvId aTargetFolderId);
        inline   void SetMoveFromLocal(TMsvId aMessageId, TMsvId aTargetFolderId);
        inline   void SetMoveWithinService(TMsvId aMessageId, TMsvId aTargetFolderId);
        
        inline   void SetDelete(TMsvId aMessageId);
        inline   void SetChange(TMsvId aMessageId);
        inline   void SetCreate(TMsvId aMessageId);
        IMPORT_C void SetMtmSpecificCommandL(TMsvId aMessageId, TMsvId aTargetFolderId, TInt aMtmFunctionId, const TDesC8& aParameters);
    public: // Access to parameters of operation
        inline TOffLineOpType OpType()const ;
        inline TMsvId  MessageId()const ;
        inline TMsvId  TargetMessageId()const ;
        inline TInt    MtmFunctionId() const ;
        inline TPtrC8  MtmParameters() const ;

    public: 
        IMPORT_C void    DetachMtmParameters() ;
          // Need this detach because the copy constructor will not be called when appending this class to an array!
        IMPORT_C void DeleteBuffer();
          // Need this because destructor will not be called when item is removed from an array
    public: 
        IMPORT_C TBool Equals(const CImOffLineOperation& aOperation) const;
        IMPORT_C void CopyL(const CImOffLineOperation& aOperation);
          // Copy-constructor that can leave
    public: 
        IMPORT_C void ExternalizeL( RMsvWriteStream& aWriteStream ) const;
        IMPORT_C void InternalizeL( RMsvReadStream& aReadStream );
	public:
		IMPORT_C int operator ==(const CImOffLineOperation& otherOperation) const;
    private:
        IMPORT_C void SetOperation(TOffLineOpType aOpType, TMsvId aMessageId, TMsvId aTargetFolderId, TInt aMtmFunctionId, HBufC8* aParameters);
        IMPORT_C void SetOperation(TOffLineOpType aOpType, TMsvId aMessageId, TMsvId aTargetFolderId);
    private:
        TOffLineOpType iOpType;
        TMsvId  iMessageId;
        TMsvId  iTargetMessageId;
        TInt    iMtmFunctionId;
        HBufC8*  iMtmParameters; // Mtm-specifics
	};

///////////////////////////////////////////////////////////////////////////////
// MOffLineOperationArray : generic mixin for accessing arrays of Off line operations. 
class MImOffLineOperationArray
    {
    public:
        virtual TInt CountOperations() const = 0;
        virtual const CImOffLineOperation& Operation(TInt aIndex) const = 0;
        virtual void AppendOperationL(const CImOffLineOperation& aOperation) = 0;
        virtual void Delete(TInt aIndex) = 0;
    };

///////////////////////////////////////////////////////////////////////////////
// CImOffLineArrayStore : storing and restoring MImOffLineOperationArray
// derived classes
class CImOffLineArrayStore : public CBase
    {
    public:
        inline CImOffLineArrayStore(MImOffLineOperationArray& aArray);
        inline void SetVersion(TUint16 aVersion);
        inline TUint16 Version();
        IMPORT_C void StoreL(CMsvStore& aMsvStore) const;
        IMPORT_C void RestoreL(const CMsvStore& aMessageStore );
        IMPORT_C void ExternalizeL(RMsvWriteStream& aWriteStream) const;
        IMPORT_C void InternalizeL(RMsvReadStream& aReadStream);
    private:
        TUint16 iVersion;
        MImOffLineOperationArray* iArray;
    };

///////////////////////////////////////////////////////////////////////////////
// CImOffLineOperationArray : implementation of MImOffLineOperationArray
class CImOffLineOperationArray : public  CBase, public MImOffLineOperationArray
    {
    public:
        IMPORT_C static CImOffLineOperationArray* NewL();
        IMPORT_C virtual ~CImOffLineOperationArray();
    public: // derived from MImOffLineOperationArray
        TInt CountOperations() const;
        const CImOffLineOperation& Operation(TInt aIndex) const;
        void AppendOperationL(const CImOffLineOperation& aOperation);
        void Delete(TInt aIndex);
    public: // Not derived from MImOffLineOperationArray
        IMPORT_C void InsertOperationL(CImOffLineOperation& aOperation, TInt aPosition);
    protected:
        CImOffLineOperationArray();
        IMPORT_C void ConstructL();
    protected:
        CArrayFixFlat<CImOffLineOperation> *iArray;
    };


class TQueuedOperation 
	{
	public:
        IMPORT_C static TQueuedOperation* NewL(TMsvId aFolderId,TInt aOperationIndex, const CImOffLineOperation& aStoredOperation);
        IMPORT_C TQueuedOperation();
	    IMPORT_C TBool operator!=(const TQueuedOperation& aOp);
		inline TMsvId FolderId() const;
		inline TInt OperationIndex() const;
		inline CImOffLineOperation& Operation() ;
        IMPORT_C void CopyL(const TQueuedOperation& aOperation);
	private:
        TQueuedOperation(TMsvId aFolderId,TInt aOperationIndex);
	private:
		TMsvId iFolderId;
		TInt   iOperationIndex;
		CImOffLineOperation iStoredOperation;
	};

class CImQueuedList : public  CBase, public MImOffLineOperationArray
    {
    public:
        IMPORT_C static CImQueuedList* NewL();
        IMPORT_C virtual ~CImQueuedList() ;
        IMPORT_C void SetFolder(TMsvId  aFolderId);
        IMPORT_C void ResetLineCounter();
		IMPORT_C TQueuedOperation& operator[](TInt anIndex);
        IMPORT_C void Delete(TInt aIndex);
        IMPORT_C void Reset();
        IMPORT_C void AppendL(TQueuedOperation& aOperation);
    public: // From MOffLineOperationArrayStore
        IMPORT_C virtual TInt CountOperations() const;
        IMPORT_C virtual const CImOffLineOperation& Operation(TInt aIndex) const;
        IMPORT_C virtual void AppendOperationL(const CImOffLineOperation& aOperation);
    private:
        CImQueuedList() ;
    private:
        TMsvId  iFolderId;
        TInt    iLine;
        CArrayFixFlat<TQueuedOperation> *iArray;
    };

class MImUndoOffLineOperation
    {
    public:
        virtual void UndoOffLineChangesL(const CImOffLineOperation& aDeleted, TMsvId aFolderId) = 0; 
    };

class CImOperationQueueList : public CBase
	{
	public:
		IMPORT_C static CImOperationQueueList* NewL(CMsvEntry& aServiceEntry, MImUndoOffLineOperation *aImUndoOffLineOperation);
		    // Create new list of queued operations for service entry aServiceEntry is set to.
		IMPORT_C ~CImOperationQueueList();
		inline const TInt Count() const;
			// Current number of queued operations in list
		inline TQueuedOperation& operator[](TInt anIndex);
			// Access to array of queued operations.
		IMPORT_C void DeleteL(TInt aLine);
			// Remove operation from list of queued operations locally.
		IMPORT_C void ExpungeDeletedOperationsL();
			// Enforce removal of queued operations from the stores of the folders.
	protected:
		void ConstructL();
		CImOperationQueueList(CMsvEntry& aServiceEntry,MImUndoOffLineOperation *aImUndoOffLineOperation);
		void RestoreQueuedListL(CImQueuedList &/*aList*/);
		void StoreQueuedListL(CImQueuedList &/*aList*/);
		void ProcessFoldersL();
	private:
		CImQueuedList *iQueuedList;
		CImQueuedList *iDeletedList;
		CMsvEntry*  iServiceEntry;
		TMsvId	    iServiceId;
        MImUndoOffLineOperation *iUndoOffline;
    };

#include "offop.inl"

#endif
