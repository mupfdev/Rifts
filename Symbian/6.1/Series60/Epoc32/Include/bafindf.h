// BAFINDF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__BAFINDF_H__)
#define __BAFINDF_H__

#include <e32base.h>
#include <f32file.h>

class CFindFileByType : public CBase
	{
public:
	IMPORT_C CFindFileByType(RFs& aFs);
	IMPORT_C ~CFindFileByType();
	IMPORT_C TInt FindFirst(const TDesC& aName,const TDesC& aDir,const TUidType& aType);
	IMPORT_C TInt FindNext();
	IMPORT_C const TEntry& Entry() const;
	inline const TParse& File() const;
private:
	void CloseDir();
private:
	TUidType iType;
	CDir* iDir;
	TInt iCurrentFile;
	TParse iFile;
	TFindFile iFind;
	};

inline const TParse& CFindFileByType::File() const
	{return iFile;}

#endif
