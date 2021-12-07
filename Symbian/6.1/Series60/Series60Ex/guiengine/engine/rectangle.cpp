/* Copyright (c) 2001, Nokia. All rights reserved */

#include	"rectangle.h"

using namespace NShapes;


EXPORT_C TRectangle::TRectangle(const TPoint& aOrigin, TInt aWidth, TInt aHeight)
:	TShape(KRectangle, aOrigin), 
	iWidth(aWidth), 
	iHeight(aHeight)
    {
	//	No implementation required
    }

EXPORT_C TRectangle::TRectangle()
:	TShape(KRectangle, TPoint(0,0)), 
	iWidth(0), 
	iHeight(0)
    {
	//	No implementation required
    }

EXPORT_C void TRectangle::Draw(CWindowGc& aActiveGraphicsContext) const
    {
    aActiveGraphicsContext.DrawRect(GetRect());
    }

EXPORT_C TRect TRectangle::GetRect() const
    {
    return TRect(iOrigin, TSize(iWidth, iHeight));
    }

EXPORT_C void TRectangle::ExternalizeL(RWriteStream& aStream) const
    {
    TShape::ExternalizeL(aStream);

    aStream.WriteInt32L(iWidth);
    aStream.WriteInt32L(iHeight);
    }

EXPORT_C void TRectangle::InternalizeL(RReadStream& aStream)
    {
    TShape::InternalizeL(aStream);

    iWidth = aStream.ReadInt32L();
    iHeight = aStream.ReadInt32L();
    }


