/* Copyright (c) 2001, Nokia. All rights reserved */

#include	"circle.h"

using namespace NShapes;


// TCircle

EXPORT_C TCircle::TCircle(const TPoint& aCenter, TInt aRadius)
:	TShape(KCircle, aCenter - TSize(aRadius, aRadius)), 
	iRadius(aRadius)
    {
	//	No implementation required
    }

EXPORT_C TCircle::TCircle()
: TShape(KCircle, TPoint(0,0)), iRadius(0)
    {
	//	No implementation required
    }

EXPORT_C void TCircle::Draw(CWindowGc& aActiveGraphicsContext) const
    {
    aActiveGraphicsContext.DrawEllipse(GetRect());
    }

EXPORT_C TRect TCircle::GetRect() const
    {
    return TRect(iOrigin, TSize(iRadius * 2, iRadius * 2));
    }

EXPORT_C void TCircle::ExternalizeL(RWriteStream& aStream) const
    {
    TShape::ExternalizeL(aStream);

    aStream.WriteInt32L(iRadius);
    }

EXPORT_C void TCircle::InternalizeL(RReadStream& aStream)
    {
    TShape::InternalizeL(aStream);

    iRadius = aStream.ReadInt32L();
    }

