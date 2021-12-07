// INSTPREF.H
// Copyright (c) 1997-1999 Symbian Ltd. All rights reserved.
//
// Software installation preference settings reader/writer
//

#if !defined(__INSTPREF_H__)
#define __INSTPREF_H__

#include <e32base.h>

class RReadStream;
class RWriteStream;

const TUid KUidInstallPrefs={268436795};

// ===========================================================================

class TInstallPrefs
// preferences used by InstCtrl and InstApp
	{
public:
	enum TInstSortField
		{
		EInstSortByName,
		EInstSortByType,
		EInstSortBySize
		};	
public:
	IMPORT_C TInstallPrefs();
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
public:
	TLanguage iLanguage;
	TBool iAutoDelete;
	TInstSortField iSortField;
	};

#endif