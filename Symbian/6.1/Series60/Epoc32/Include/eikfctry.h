// EIKFCTRY.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKFCTRY_H__)
#define __EIKFCTRY_H__

#if !defined(__E32DEF_H__)
#include <e32def.h>
#endif

class CCoeControl;

enum
	{
	EEikControlHasEars=0x01,
	EEikControlIsNonFocusing=0x02,
	EEikControlHasExtraAscent=0x04
	};

struct SEikControlInfo
    {
    CCoeControl* iControl;
	TInt iTrailerTextId;
    TInt iFlags;
    };

class EikControlFactory
	{
public:
    IMPORT_C static SEikControlInfo CreateByTypeL(TInt aControlType);
	};

#endif
