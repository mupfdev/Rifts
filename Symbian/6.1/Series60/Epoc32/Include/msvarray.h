// MSVARRAY.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__MSVARRAY_H__)
#define __MSVARRAY_H__

#if !defined(__MSVSTD_H__)
#include "msvstd.h"
#endif

//*************************
//  class TKeyArrayFixPtr
//*************************

class TKeyArrayFixPtr : public TKeyArrayFix
// 
// Generic Key class for sorting arrays of pointers in flat arrays. 
//
	{ 
public:
	inline TKeyArrayFixPtr(TInt anOffset,TKeyCmpText aType);
	inline TKeyArrayFixPtr(TInt anOffset,TKeyCmpText aType,TInt aLength);
	inline TKeyArrayFixPtr(TInt anOffset,TKeyCmpNumeric aType);
	// At returns dereferenced pointer to objects (but not index)
	IMPORT_C TAny* At(TInt anIndex) const;
	};


//**********************************
// CMsvEntryArray
//**********************************
//
// The array of TMsvEntry pointers
//

class CMsvEntryArray : public CArrayPtrFlat<const TMsvEntry>
	{ 
public: 
	IMPORT_C static CMsvEntryArray* NewL(const CArrayFix<TUid>& iMtmList); 
	IMPORT_C static CMsvEntryArray* NewLC(const CArrayFix<TUid>& iMtmList); 
	IMPORT_C void SortL(TMsvSelectionOrdering aOrdering);
	IMPORT_C ~CMsvEntryArray();
private:
	enum TGroupCriterion
		{
		EGroupByStandardFolders, 
		EGroupByType, 
		EGroupByPriority, 
		EGroupByMtm, 
		EStopGrouping
		};
private:
	TInt NumberOfArraysToSplitIntoL(TGroupCriterion aGroupCriterion);
	TBool OkToGroup(TGroupCriterion aGroupCriterion,TMsvSelectionOrdering aOrdering) const;
	TInt ArrayId(const TMsvEntry* aEntry,TGroupCriterion aGroupCriterion) const;
	void GroupL(TGroupCriterion aGroupCriterion,TMsvSelectionOrdering aOrdering,TBool aDoSort);
	void ReverseOrder(TMsvSorting aSortType);
	void ReverseOrder();
	CMsvEntryArray(const CArrayFix<TUid>& iMtmList);
	TKeyArrayFixPtr MessageSortKey(TMsvSorting aSortType) const;
private:
	const CArrayFix<TUid>& iOrigMtmList;
	CArrayFix<TUid>* iActualMtmList;
	};

// inline

inline TKeyArrayFixPtr::TKeyArrayFixPtr(TInt anOffset,TKeyCmpText aType)
	: TKeyArrayFix(anOffset,aType)
	{}

inline TKeyArrayFixPtr::TKeyArrayFixPtr(TInt anOffset,TKeyCmpText aType,TInt aLength)
	: TKeyArrayFix(anOffset,aType,aLength)
	{}

inline TKeyArrayFixPtr::TKeyArrayFixPtr(TInt anOffset,TKeyCmpNumeric aType)
	: TKeyArrayFix(anOffset,aType)
	{}



#endif