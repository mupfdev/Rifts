// EIKLBM.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


#if !defined(__EIKLBM_H__)
#define __EIKLBM_H__  


#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__BAMDESCA_H__)
#include <bamdesca.h>
#endif


enum TListBoxModelItemArrayOwnership
	{
	ELbmOwnsItemArray,
	ELbmDoesNotOwnItemArray
	};


class MListBoxModel 
	{
public:
	IMPORT_C virtual ~MListBoxModel();
	virtual TInt NumberOfItems() const = 0;
	virtual const MDesCArray* MatchableTextArray() const = 0;
private:
	IMPORT_C virtual TAny* MListBoxModel_Reserved();
	};

class MTextListBoxModel : public MListBoxModel
	{
public:
	IMPORT_C ~MTextListBoxModel();
	virtual TPtrC ItemText(TInt aItemIndex) const = 0;
private: // from MListBoxModel
	IMPORT_C virtual TAny* MListBoxModel_Reserved();
	};

#endif
