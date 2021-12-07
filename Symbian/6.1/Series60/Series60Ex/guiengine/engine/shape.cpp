/* Copyright (c) 2001, Nokia. All rights reserved */

#include	"shape.h"

using namespace NShapes;

EXPORT_C TShape::TShape(TShapeType aShapeType, const TPoint& aOrigin)
:	iShapeType(aShapeType),
    iOrigin(aOrigin)
    {
	//	No implementation required
    }

EXPORT_C TShapeType TShape::ReadShapeTypeL(RReadStream& aStream)
    {
    return static_cast<TShapeType>(aStream.ReadInt32L());
    }

EXPORT_C void TShape::ExternalizeL(RWriteStream& aStream) const
    {
    aStream.WriteInt32L(iShapeType);

    aStream.WriteInt32L(iOrigin.iX);
    aStream.WriteInt32L(iOrigin.iY);
    }

EXPORT_C void TShape::InternalizeL(RReadStream& aStream)
    {
    //  iShapeType has already been read
    iOrigin.iX = aStream.ReadInt32L();
    iOrigin.iY = aStream.ReadInt32L();
    }


