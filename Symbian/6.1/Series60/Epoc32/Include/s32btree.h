// S32BTREE.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//
#if !defined(__S32BTREE_H__)
#define __S32BTREE_H__
#if !defined(__S32PAGE_H__)
#include <s32page.h>
#endif

const TInt KMaxBtreeHeight=16;
const TInt KMaxBtreeKeyLength=255;
//
typedef TInt TBtreeHeight;
typedef TBuf8<KMaxBtreeKeyLength> TBtreePivot;
//
enum TBtreeMode {EBtreeSecure,EBtreeFast};
//
class TBtreeToken
	{
public:
	enum TEmpty {EEmpty};
public:
	TBtreeToken() {}
	inline TBtreeToken(TEmpty);
	inline void Touch();
//
	inline TBool IsBroken() const;
	inline TBool IsIntact() const;
	inline TBool IsEmpty() const;
//
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
protected:
	IMPORT_C void Clear();
private:
	inline TBtreeToken(TPageRef aFirst,TPageRef aRoot,TBtreeHeight aHeight);
private:
	TPageRef iFirst;
	TPageRef iRoot;
	TBtreeHeight iHeight;
private:
	friend class TBtree;
	};
#define KEmptyBtreeToken TBtreeToken(TBtreeToken::EEmpty)
//
class TBtreePath
	{
public:
	inline TBtreePath();
	inline TPageRef Node() const;
	inline TInt Entry() const;
	inline TBool IsLeaf() const;
	inline TBtreeHeight End() const;
	inline void SetEntry(TInt aEntry);
	void GotoRoot(TBtreeHeight aHeight,TPageRef aRoot);
	void Push(TPageRef aRef,TInt aEntry=0);
	inline void Pop();
private:
	TBtreeHeight iEnd;
	TPageRef iNodes[KMaxBtreeHeight];
	TUint8 iEntries[KMaxBtreeHeight];
	TUint8 iLasts[KMaxBtreeHeight];
	};
//
class TBtreePos
	{
private:
	TBtreePath iPath;
private:
	friend class TBtree;
	};
class TBtreeMark
	{
private:
	TPageRef iLeaf;
	TPageRef iLink;
	TUint8 iEntry;
	TUint8 iLast;
private:
	friend class TBtree;
	};
//
class MBtreeKey
	{
public:
	virtual IMPORT_C const TAny* Key(const TAny* anEntry) const;
	virtual TInt Compare(const TAny* aLeft,const TAny* aRight) const=0;
	virtual void Between(const TAny* aLeft,const TAny* aRight,TBtreePivot& aPivot) const=0;
	};
class MBtreeNodeOrg;
class MBtreeLeafOrg;
class MBtreeIndexOrg;
class TBtree
	{
public:
	enum TFind {EGreaterEqual,EEqualTo,ELessThan,EGreaterThan,ELessEqual};
public:
	IMPORT_C TBtree(TBtreeMode aMode);
	IMPORT_C TBtree(const TBtreeToken& aToken,TBtreeMode aMode);
	IMPORT_C void Connect(MPagePool* aPool,const MBtreeKey* aKey,const MBtreeLeafOrg* aLeafOrg,const MBtreeIndexOrg* anIndexOrg);
	IMPORT_C void Set(const TBtreeToken& aToken,TBtreeMode aMode);
	IMPORT_C TBtreeToken Token() const;
//
	inline TBool IsDirty() const;
	inline void MarkCurrent();
	inline void MarkDirty();
//
	inline TBool IsBroken() const;
	inline TBool IsIntact() const;
	inline void MarkBroken();
	IMPORT_C TInt RepairL();
//
	inline TBool IsEmpty() const;
	IMPORT_C void ClearL();
//
	IMPORT_C TBool FirstL(TBtreePos& aPos) const;
	IMPORT_C TBool LastL(TBtreePos& aPos) const;
	IMPORT_C TBool NextL(TBtreePos& aPos) const;
	IMPORT_C TBool PreviousL(TBtreePos& aPos) const;
//
	IMPORT_C TBool FindL(TBtreePos& aPos,const TAny* aKey,TFind aMode=EEqualTo) const;
	IMPORT_C TBool InsertL(TBtreePos& aPos,const TAny* anEntry,TInt aLength,TAllowDuplicates aDup=ENoDuplicates);
	IMPORT_C TBool DeleteL(const TAny* aKey);
	IMPORT_C void DeleteAtL(TBtreePos& aPos);
	IMPORT_C void ExtractAtL(const TBtreePos& aPos,TAny* anEntry,TInt aMaxLength) const;
//
	IMPORT_C TBool ResetL(TBtreeMark& aMark) const;
	IMPORT_C TBool NextL(TBtreeMark& aMark) const;
	IMPORT_C void ExtractAtL(const TBtreeMark& aMark,TAny* anEntry,TInt aMaxLength) const;
private:
	TBool AscendAtLastL(TBtreePath& aPath) const;
	TBool AscendAtFirstL(TBtreePath& aPath) const;
	void DescendFirstL(TBtreePath& aPath) const;
	void DescendLastL(TBtreePath& aPath) const;
//
	TBool SearchL(TBtreePath& aPath,const TAny* aKey,TBool aAfter=EFalse) const;
	void NewPivot(const TAny* aLeftNode,const TAny* aRightNode,TBtreePivot& aPivot) const;
	void ReplacePivotL(TBtreePath& aPath,TAny* aNode,TBtreePivot& aPivot);
	void InsertAtL(TBtreePath& aPath,const TDesC8& anEntry);
	void InsertAtL(TBtreePath& aPath,TBtreePivot& aPivot,TPageRef aChild);
	TBool InsertAtL(TBtreePath& aPath,const TDesC8& anEntry,TPageRef aChild,TBtreePivot& aPivot,TPageRef& aPromote);
	void DeleteAtL(TBtreePath& aPath);
	void DeleteIndexSetL();
	void DeleteIndexNodesL(TBtreePath& aPath,TBool aLeadingEdge);
//
	void NewTreeL();
	void NewRootL();
//
	void BeginUpdateL();
	void EndUpdate();
	inline void MarkIntact();
	void CheckIntactL() const;
//
	inline TBool IsRoot(const TBtreePath& aPath) const;
	inline const MBtreeNodeOrg* NodeOrg(TBool aLeaf) const;
	void GotoRoot(TBtreePath& aPath) const;
//
	TAny* GetNodeL(const TBtreePath& aPath) const;
	void PutNode(TAny* aNode,TBool aLeaf) const;
//
	TInt LastEntryL(const TBtreePath& aPath) const;
	TPageRef ChildNodeL(const TBtreePath& aPath) const;
	TPageRef LastChildNodeL(TBtreePath& aPath) const;
	TPageRef ChildNodeL(TBtreePath& aPath,TInt aChild) const;
private:
	enum {ESecure=EBtreeSecure,EFast=EBtreeFast,EBroken=0x40000000,EDirty=0x80000000};
private:
	MPagePool* iPages;
	const MBtreeKey* iKey;
	const MBtreeLeafOrg* iLeafOrg;
	const MBtreeIndexOrg* iIndexOrg;
	TPageRef iFirst;
	TPageRef iRoot;
	TBtreeHeight iHeight;
	TInt iStatus;
	};
//
class MBtreeNodeOrg
	{
public:
	virtual IMPORT_C void Init(TAny* aNode) const;
	virtual TInt LastEntry(const TAny* aNode) const=0;
	virtual TPtrC8 Entry(const TAny* aNode,TInt aPos) const=0;
	virtual const TAny* EntryPtr(const TAny* aNode,TInt aPos) const=0;
	virtual TBool Search(const TAny* aNode,const TAny* aKey,const MBtreeKey& aComp,TBool aLast,TInt& aPos) const=0;
	virtual TBool Delete(TAny* aNode,TInt aPos) const=0;
	};
class MBtreeLeafOrg : public MBtreeNodeOrg
	{
public:
	IMPORT_C TBool Search(const TAny* aNode,const TAny* aKey,const MBtreeKey& aComp,TBool aLast,TInt& aPos) const;
	virtual TBool Insert(TAny* aNode,TInt aPos,const TDesC8& anEntry) const=0;
	virtual IMPORT_C TBool InsertOverflow(TAny* aLeftNode,TAny* aRightNode,TInt aPos,TBool aInsertOnLeft,const TDesC8& anEntry) const;
	virtual void InsertSplit(TAny* aLeftNode,TAny* aRightNode,TInt aPos,const TDesC8& anEntry) const=0;
	virtual TBool Redistribute(TAny* aLeftNode,TAny* aRightNode) const=0;
	virtual void Concatenate(TAny* aLeftNode,const TAny* aRightNode) const=0;
	virtual TPageRef LinkNode(const TAny* aNode) const=0;
	virtual void SetLinkNode(TAny* aNode,TPageRef aNextNode) const=0;
	};
class MBtreeIndexOrg : public MBtreeNodeOrg
	{
public:
	IMPORT_C TBool Search(const TAny* aNode,const TAny* aKey,const MBtreeKey& aComp,TBool aLast,TInt& aPos) const;
	virtual TBool Insert(TAny* aNode,TInt aPos,const TDesC8& anEntry,TPageRef aChild) const=0;
	virtual IMPORT_C TBool InsertOverflow(TAny* aLeftNode,TAny* aRightNode,TInt aPos,TBool aInsertOnLeft,const TDesC8& anEntry,TPageRef aChild,const TDesC8& aPivot,TBtreePivot& aNewPivot) const;
	virtual void InsertSplit(TAny* aLeftNode,TAny* aRightNode,TInt aPos,const TDesC8& anEntry,TPageRef aChild,TBtreePivot& aPromote) const=0;
	virtual IMPORT_C TBool Update(TAny* aNode,TInt aPos,const TDesC8& anEntry) const;
	virtual TBool Redistribute(TAny* aLeftNode,TAny* aRightNode,const TDesC8& aPivot,TBtreePivot& aNewPivot) const=0;
	virtual void Concatenate(TAny* aLeftNode,const TAny* aRightNode,const TDesC8& aPivot) const=0;
	virtual void MakeRoot(TAny* aNode,TPageRef aChild) const=0;
	virtual TPageRef ChildNode(const TAny* aNode,TInt aPos) const=0;
	};
//
class TBtreeInlineLeafOrg : public MBtreeLeafOrg
	{
public:
	IMPORT_C TBtreeInlineLeafOrg();
	IMPORT_C void SetEntrySize(TInt aSize);
//
	IMPORT_C TInt LastEntry(const TAny* aNode) const;
	IMPORT_C TPtrC8 Entry(const TAny* aNode,TInt aPos) const;
	IMPORT_C const TAny* EntryPtr(const TAny* aNode,TInt aPos) const;
	IMPORT_C TBool Insert(TAny* aNode,TInt aPos,const TDesC8& anEntry) const;
	IMPORT_C TBool InsertOverflow(TAny* aLeftNode,TAny* aRightNode,TInt aPos,TBool aInsertOnLeft,const TDesC8& anEntry) const;
	IMPORT_C void InsertSplit(TAny* aLeftNode,TAny* aRightNode,TInt aPos,const TDesC8& anEntry) const;
	IMPORT_C TBool Delete(TAny* aNode,TInt aPos) const;
	IMPORT_C TBool Redistribute(TAny* aLeftNode,TAny* aRightNode) const;
	IMPORT_C void Concatenate(TAny* aLeftNode,const TAny* aRightNode) const;
	IMPORT_C TPageRef LinkNode(const TAny* aNode) const;
	IMPORT_C void SetLinkNode(TAny* aNode,TPageRef aNextNode) const;
private:
	TAny* DoRedistribute(TAny* aLeftNode,TAny* aRightNode,TInt aInsertPos=-1) const;
	struct SHeader
		{
		TInt32 iCount;
		TPageRef iLink;
		};
	struct SNode
		{
		SHeader iHead;
		TUint8 iEntries[KPoolPageSize-sizeof(SHeader)];
		};
private:
	inline static const SNode* Node(const TAny* aNode);
	inline static SNode* Node(TAny* aNode);
	inline const TUint8* Entry(const SNode* aNode,TInt anEntry) const;
	inline TUint8* Entry(SNode* aNode,TInt anEntry) const;
private:
	TInt iEntrySize;
	TInt iMaxEntries;
	};
class TBtreeInlineIndexOrg : public MBtreeIndexOrg
	{
public:
	IMPORT_C TBtreeInlineIndexOrg();
	IMPORT_C void SetEntrySize(TInt aSize);
//
	IMPORT_C TBool Insert(TAny* aNode,TInt aPos,const TDesC8& anEntry,TPageRef aChild) const;
	IMPORT_C TBool InsertOverflow(TAny* aLeftNode,TAny* aRightNode,TInt aPos,TBool aInsertOnLeft,const TDesC8& anEntry,TPageRef aChild,const TDesC8& aPivot,TBtreePivot& aNewPivot) const;
	IMPORT_C void InsertSplit(TAny* aLeftNode,TAny* aRightNode,TInt aPos,const TDesC8& anEntry,TPageRef aChild,TBtreePivot& aPromote) const;
	IMPORT_C TBool Update(TAny* aNode,TInt aPos,const TDesC8& anEntry) const;
	IMPORT_C TBool Delete(TAny* aNode,TInt aPos) const;
	IMPORT_C TBool Redistribute(TAny* aLeftNode,TAny* aRightNode,const TDesC8& aPivot,TBtreePivot& aNewPivot) const;
	IMPORT_C void Concatenate(TAny* aLeftNode,const TAny* aRightNode,const TDesC8& aPivot) const;

	IMPORT_C void MakeRoot(TAny* aNode,TPageRef aChild) const;
	IMPORT_C TInt LastEntry(const TAny* aNode) const;
	IMPORT_C TPtrC8 Entry(const TAny* aNode,TInt aPos) const;
	IMPORT_C const TAny* EntryPtr(const TAny* aNode,TInt aPos) const;
	IMPORT_C TPageRef ChildNode(const TAny* aNode,TInt aPos) const;
private:
	struct SEntry
		{
		TPageRef iChild;
		TUint8 iKey[4]; // at least four bytes of key
		};
	struct SHeader
		{
		TInt32 iCount;
		};
	struct SNode
		{
		SHeader iHead;
		TUint8 iEntries[KPoolPageSize-sizeof(SHeader)];
		};
	SNode* DoRedistribute(TAny* aLeftNode,TAny* aRightNode,const TDesC8& aPivot,TBtreePivot& aNewPivot,TInt aInsertPos=-1) const;
private:
	inline static const SNode* Node(const TAny* aNode);
	inline static SNode* Node(TAny* aNode);
	inline const SEntry* Entry(const SNode* aNode,TInt anEntry) const;
	inline SEntry* Entry(SNode* aNode,TInt anEntry) const;
	inline TInt KeySize() const;
private:
	TInt iEntrySize;
	TInt iMaxEntries;
	};
//
class TBtreeKey : public MBtreeKey
	{
public:
	IMPORT_C TBtreeKey();
	IMPORT_C TBtreeKey(TInt aLength);
	IMPORT_C TBtreeKey(TInt anOffset,TKeyCmpText aType);
	IMPORT_C TBtreeKey(TInt anOffset,TKeyCmpText aType,TInt aLength);
	IMPORT_C TBtreeKey(TInt anOffset,TKeyCmpNumeric aType);
//
	IMPORT_C const TAny* Key(const TAny* anEntry) const;
	IMPORT_C TInt Compare(const TAny* aLeft,const TAny* aRight) const;
	IMPORT_C void Between(const TAny* aLeft,const TAny* aRight,TBtreePivot& aPivot) const;
protected:
	TInt iKeyOffset;
	TInt iCmpType;
	TInt iKeyLength;
	};
//
class TBtreeFixBase : public TBtree
	{
public:
	IMPORT_C void Connect(MPagePool* aPool,const MBtreeKey* aKey);
	IMPORT_C TBool InsertL(TBtreePos& aPos,const TAny* anEntry,TAllowDuplicates aDup=ENoDuplicates);
	IMPORT_C void ExtractAtL(const TBtreePos& aPos,TAny* anEntry) const;
	IMPORT_C void ExtractAtL(const TBtreeMark& aMark,TAny* anEntry) const;
protected:
	IMPORT_C TBtreeFixBase(TBtreeMode aMode,TInt anEntrySize,TInt aKeySize);
	IMPORT_C TBtreeFixBase(const TBtreeToken& aToken,TBtreeMode aMode,TInt anEntrySize,TInt aKeySize);
private:
	TInt iEntrySize;
	TBtreeInlineLeafOrg iLeafOrgFix;
	TBtreeInlineIndexOrg iIndexOrgFix;
	};
template <class Entry,class Key>
class TBtreeFix : public TBtreeFixBase
	{
public:
	inline TBtreeFix(TBtreeMode aMode);
	inline TBtreeFix(const TBtreeToken& aToken,TBtreeMode aMode);
//
	inline TBool FindL(TBtreePos& aPos,const Key& aKey,TFind aMode=EEqualTo) const;
	inline TBool InsertL(TBtreePos& aPos,const Entry& anEntry,TAllowDuplicates aDup=ENoDuplicates);
	inline TBool DeleteL(const Key& aKey);
//
	inline Entry AtL(const TBtreePos& aPos) const;
	inline Entry AtL(const TBtreeMark& aMark) const;
	inline void ExtractAtL(const TBtreePos& aPos,Entry& anEntry) const;
	inline void ExtractAtL(const TBtreeMark& aMark,Entry& anEntry) const;
	};
TEMPLATE_SPECIALIZATION class TBtreeFix<TAny,TAny> : public TBtreeFixBase
	{
public:
	inline TBtreeFix(TBtreeMode aMode,TInt anEntrySize,TInt aKeySize);
	inline TBtreeFix(const TBtreeToken& aToken,TBtreeMode aMode,TInt anEntrySize,TInt aKeySize);
	};

#include <s32btree.inl>
#endif
