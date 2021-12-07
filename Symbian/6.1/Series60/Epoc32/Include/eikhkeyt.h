// EIKHKEYT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKHKEYT_H__)
#define __EIKHKEYT_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__E32KEYS_H__)
#include <e32keys.h>
#endif

struct SEikHotKey
	{
	TInt iCommandId;
	TInt iKeycode;
	};

class CEikHotKeyTable : public CArrayFixFlat<SEikHotKey>
	{
public:
	IMPORT_C CEikHotKeyTable();
	IMPORT_C ~CEikHotKeyTable();
	IMPORT_C TBool HotKeyFromCommandId(TInt aCommandId,TInt& aKeycode,TInt& aModifiers) const;
	IMPORT_C TInt CommandIdFromHotKey(TInt aKeycode,TInt aModifiers) const;
	IMPORT_C void AddItemL(TInt aCommandId,TInt aKeycode,TInt aModifiers);
	IMPORT_C void RemoveItem(TInt aCommandId);
	IMPORT_C void ConstructFromResourceL(TInt aResourceId);
	IMPORT_C void Reset();
private:
	TInt iNumberPlain;
	TInt iNumberCtrl;
	TInt iNumberShiftCtrl;
	TInt iSpare;
	};

#endif
