/* Copyright (c) 2001, Nokia. All rights reserved */

#include "Sprite.h"


// Standard Epoc construction sequence
CSprite* CSprite::NewL(TInt aXVelocity,TInt aYVelocity, const TPoint& aInitialPosition)
	{
	CSprite* self = CSprite::NewLC(aXVelocity,aYVelocity,aInitialPosition);
	CleanupStack::Pop();
	return self;
	}

	
CSprite* CSprite::NewLC(TInt aXVelocity,TInt aYVelocity, const TPoint& aInitialPosition)
	{
	CSprite* self = new (ELeave) CSprite(aXVelocity,aYVelocity,aInitialPosition);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}


CSprite::CSprite(TInt aXVelocity,TInt aYVelocity, const TPoint& aInitialPosition)
:	iPosition(aInitialPosition),
	iXVelocity(aXVelocity),
	iYVelocity(aYVelocity)
	{
	}


CSprite::~CSprite()
	{
	}


void CSprite::ConstructL()
	{
	}


TPoint CSprite::Position() const
	{
	return iPosition;
	}


void CSprite::Move(const TSize& aSize, const TRect& aBounds)
	{
	TBool okToMove = ETrue;
	
	// Calculate the new sprite position
	TPoint newPostion = iPosition + TPoint(iXVelocity,iYVelocity);
	
	// Check that the new sprite X position is not out of bounds
	TInt width = aSize.iWidth;
	TInt leftX = newPostion.iX;
	TInt rightX = newPostion.iX + width;
	if ((rightX > aBounds.iBr.iX) || (leftX < aBounds.iTl.iX))
		{
		// If it is, "bounce" the sprite off the edge of the boundary
		iXVelocity = -iXVelocity;
		// and don't let it move this tick
		okToMove = EFalse;
		}

	// Check that the new sprite Y position is not out of bounds
	TInt height = aSize.iHeight;
	TInt topY = newPostion.iY;
	TInt bottomY = newPostion.iY + height;
	if ((bottomY > aBounds.iBr.iY) || (topY < aBounds.iTl.iY))
		{
		// If it is, "bounce" the sprite off the edge of the boundary
		iYVelocity = -iYVelocity;
		// and don't let it move this tick
		okToMove = EFalse;
		}

	// If the sprite can move this tick
	if (okToMove)
		{
		// Move it
		iPosition = newPostion;
		}
	}
