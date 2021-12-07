// BITBASE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __BITBASE_H__
#define __BITBASE_H__

#ifndef __GDI_H__
#include <gdi.h>
#endif

class TSpriteBase
	{
public:
	virtual void Hide(const TRect& aRect,const TRegion* aRegion)=0;
	virtual void Reveal(const TRect& aRect,const TRegion* aRegion)=0;
	};

#endif
