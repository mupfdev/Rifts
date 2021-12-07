/*
* ============================================================================
*  Name     : AknApp.h
*  Part of  : Avkon
*
*  Description:
*     ?description_line
*     ?description_line
*     ?description_line
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
#ifndef __AKNAPP_H__
#define __AKNAPP_H__

#include <eikapp.h>

class CAknApplication : public CEikApplication
	{
public:
	// from CApaApplication
	IMPORT_C void PreDocConstructL();
	IMPORT_C CDictionaryStore* OpenIniFileLC(RFs& aFs) const;
	};

#endif

