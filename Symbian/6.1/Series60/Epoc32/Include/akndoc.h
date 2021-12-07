/*
* ============================================================================
*  Name     : AknDoc.h
*  Part of  : Avkon
*
*  Description:
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
#ifndef __AKNDOC_H__
#define __AKNDOC_H__

#include <eikdoc.h>

class CAknDocument : public CEikDocument
	{
public:	// from CEikDocument
	IMPORT_C CFileStore* OpenFileL(TBool aDoOpen,const TDesC& aFilename,RFs& aFs);
protected:
	IMPORT_C CAknDocument(CEikApplication& aApp);
	};

#endif

