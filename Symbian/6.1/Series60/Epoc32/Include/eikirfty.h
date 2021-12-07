// EIKIRFTY.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
// Defines mix-in interace to break dependencey of Eikon Application UI 
// on EikIr library

#if !defined(__EIKIRFTY_H__)
#define __EIKIRFTY_H__

#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__EIKDEF_H__)
#include <eikdef.h>
#endif

class CEikEdwin;

/**
 * @internal
 */
class MEikIrFactory
	{
public:
	virtual void SendDataOverIrL(CEikEdwin* aEditor) = 0;
	virtual void ReceiveDataOverIrL(CEikEdwin* aEditor) = 0;
	};



#endif
