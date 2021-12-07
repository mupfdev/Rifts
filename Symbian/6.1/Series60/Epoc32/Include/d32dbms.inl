// D32DBMS.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

// Class TDbCol
inline TDbCol::TDbCol(const TDesC &aName)
	: iName(aName)
	{}
inline TBool TDbCol::IsLong(TDbColType aType)
	{return aType>=EDbColLongText8;}

// Class CDbColSet
inline TInt CDbColSet::Count() const
	{return iColumns.Count();}
inline void CDbColSet::Clear()
	{iColumns.Reset();}
inline const TDbCol& CDbColSet::operator[](TDbColNo aCol) const
	{return iColumns[aCol-1];}		// 1-based column ids 
// Class TDbColSetIter
inline TDbColSetIter::operator TAny* () const
	{return CONST_CAST(TDbCol*,iColumn);}
inline const TDbCol& TDbColSetIter::operator*() const
	{__ASSERT_DEBUG(iIndex<iArray->Count(),User::Invariant());return *iColumn;}
inline const TDbCol* TDbColSetIter::operator->() const
	{__ASSERT_DEBUG(iIndex<iArray->Count(),User::Invariant());return iColumn;}
inline TDbColNo TDbColSetIter::Col() const
	{__ASSERT_DEBUG(iIndex<iArray->Count(),User::Invariant());return iIndex+1;}
inline TDbColSetIter TDbColSetIter::operator++(TInt)
	{TDbColSetIter tmp(*this);++(*this);return tmp;}

// Class CDbKey
inline TInt CDbKey::Count() const
	{return iKeys.Count();}
inline const TDbKeyCol& CDbKey::operator[](TInt aCol) const
	{return iKeys[aCol];}
inline void CDbKey::MakeUnique()
	{iAttributes|=EUnique;}
inline TBool CDbKey::IsUnique() const
	{return iAttributes&EUnique;}
inline TBool CDbKey::IsPrimary() const
	{return iAttributes&EPrimary;}
inline void CDbKey::SetComparison(TDbTextComparison aComparison)
	{iComparison=aComparison;}
inline TDbTextComparison CDbKey::Comparison() const
	{return iComparison;}
inline void CDbKey::MakePrimary()
	{iAttributes|=EPrimary;}

// Class TDbQuery
inline TDbQuery::TDbQuery(const TDesC& aQuery,TDbTextComparison aComparison)
	: iQuery(aQuery), iComparison(aComparison)
	{}
inline const TDesC& TDbQuery::Query() const
	{return iQuery;}
inline TDbTextComparison TDbQuery::Comparison() const
	{return iComparison;}

// Class RDbHandleBase
inline RDbHandleBase::RDbHandleBase()
	:iObject(0)
	{}

// Class RDbRowSet
inline void RDbRowSet::BeginningL()
	{GotoL(EBeginning);}
inline void RDbRowSet::EndL()
	{GotoL(EEnd);}
inline TBool RDbRowSet::FirstL()
	{return GotoL(EFirst);}
inline TBool RDbRowSet::LastL()
	{return GotoL(ELast);}
inline TBool RDbRowSet::NextL()
	{return GotoL(ENext);}
inline TBool RDbRowSet::PreviousL()
	{return GotoL(EPrevious);}
inline TBool RDbRowSet::IsColNull(TDbColNo aCol) const
	{return ColSize(aCol)==0;}
inline TInt RDbRowSet::ColInt(TDbColNo aCol) const
	{return ColInt32(aCol);}
inline TUint RDbRowSet::ColUint(TDbColNo aCol) const
	{return ColUint32(aCol);}
inline TReal RDbRowSet::ColReal(TDbColNo aCol) const
	{return ColReal64(aCol);}
inline void RDbRowSet::SetColL(TDbColNo aCol,TInt aValue)
	{SetColL(aCol,TInt32(aValue));}
inline void RDbRowSet::SetColL(TDbColNo aCol,TUint aValue)
	{SetColL(aCol,TUint32(aValue));}

// Class TDbWindow
inline TDbWindow::TDbWindow()
	: iSize(ENone)
	{}
inline TDbWindow::TDbWindow(TUnlimited)
	: iSize(EUnlimited)
	{}
inline TInt TDbWindow::Size() const
	{return iSize;}
inline TInt TDbWindow::PreferredPos() const
	{return iPreferredPos;}

// Class TUnion
template <class T>
inline TUnion<T>::operator const T&() const
	{return *(const T*)&iRep[0];}
template <class T>
inline const T& TUnion<T>::operator()() const
	{return *(const T*)&iRep[0];}
template <class T>
inline T& TUnion<T>::operator()()
	{return *(T*)&iRep[0];}
template <class T>
inline void TUnion<T>::Set(const T& aT)
	{new(&iRep[0]) T(aT);}

// Class TDbLookupKey
inline TDbLookupKey::TDbLookupKey()
	: iCount(0)
	{}
inline TInt TDbLookupKey::Count() const
	{return iCount;}
inline const TDbLookupKey::SColumn* TDbLookupKey::First() const
	{return &iKey[0];}
// Class TDbSeekKey
inline TDbSeekKey::TDbSeekKey()
	: iMaxKeys(1)
	{}
inline TDbSeekKey::TDbSeekKey(TInt aKey)
	: iMaxKeys(1)
	{Add(aKey);}
inline TDbSeekKey::TDbSeekKey(TUint aKey)
	: iMaxKeys(1)
	{Add(aKey);}
inline TDbSeekKey::TDbSeekKey(TInt64 aKey)
	: iMaxKeys(1)
	{Add(aKey);}
inline TDbSeekKey::TDbSeekKey(TReal32 aKey)
	: iMaxKeys(1)
	{Add(aKey);}
inline TDbSeekKey::TDbSeekKey(TReal64 aKey)
	: iMaxKeys(1)
	{Add(aKey);}
inline TDbSeekKey::TDbSeekKey(TTime aKey)
	: iMaxKeys(1)
	{Add(aKey);}
inline TDbSeekKey::TDbSeekKey(const TDesC8& aKey)
	: iMaxKeys(1)
	{Add(aKey);}
inline TDbSeekKey::TDbSeekKey(const TDesC16& aKey)
	: iMaxKeys(1)
	{Add(aKey);}
inline TDbSeekKey::TDbSeekKey(TInt aKeys,TInt)
	: iMaxKeys(aKeys)
	{}
// Class TDbSeekMultiKey
template <TInt S>
inline TDbSeekMultiKey<S>::TDbSeekMultiKey()
	: TDbSeekKey(S,0)
	{}

// Class RDbTable
inline TInt RDbTable::SetIndex(const TDesC& anIndex)
	{return SetIndex(&anIndex);}
inline TInt RDbTable::SetNoIndex()
	{return SetIndex(0);}

inline RDbColWriteStream::RDbColWriteStream(const MExternalizer<TStreamRef> &anExternalizer)
	: RWriteStream(anExternalizer)
	{}

// Class CDbNames
inline TInt CDbNames::Count() const
	{return iList.Count();}
inline const TDesC& CDbNames::operator[](TInt anIndex) const
	{return iList[anIndex];}

// Class RDbDatabase
inline TInt RDbDatabase::CreateTable(const TDesC& aName,const CDbColSet& aColSet)
	{return CreateTable(aName,aColSet,NULL);}
inline TInt RDbDatabase::CreateTable(const TDesC& aName,const CDbColSet& aColSet,const CDbKey& aPrimaryKey)
	{return CreateTable(aName,aColSet,&aPrimaryKey);}

// Class RDbIncremental
inline TInt RDbIncremental::Execute(RDbDatabase& aDatabase,const TDesC& aSql,TInt& aStep)
	{return Execute(aDatabase,aSql,EDbCompareNormal,aStep);}
