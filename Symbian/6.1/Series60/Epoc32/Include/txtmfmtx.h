// TXTMFMTX.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __TXTMFMTX_H__
#define __TXTMFMTX_H__

#include <e32std.h>
#include <txtfrmat.h>

// Defines interface for getting/setting formatting attributes.

class MFormatText
	{
public:
	//
	// Paragraph format attributes
	virtual void GetParaFormatL(CParaFormat* aFormat,TParaFormatMask& aVaries,TInt aPos,TInt aLength,
								CParaFormat::TParaFormatGetMode aMode=CParaFormat::EAllAttributes)const=0;
	virtual void ApplyParaFormatL(const CParaFormat* aFormat,const TParaFormatMask& aMask,TInt aPos,TInt aLength)=0;
	//
	// Character format attributes
	virtual void GetCharFormat(TCharFormat& aFormat,TCharFormatMask& aVaries,TInt aPos,TInt aLength)const=0;
	virtual void ApplyCharFormatL(const TCharFormat& aFormat,const TCharFormatMask& aMask,TInt aPos,TInt aLength)=0;
	};

#endif

