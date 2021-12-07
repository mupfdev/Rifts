/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <e32base.h>

class CFbsBitmap;

/*! 
  @class CSprite
  
  @discussion An instance of class CSprite represents an object being displayed on the screen
  */
class CSprite : public CBase
{
public:

/*!
  @function NewL
  
  @discussion Construct a CSprite using two phase construction, and return a pointer to the created object
  @param aXVelocity The velocity of the sprite on the x axis
  @param aYVelocity The velocity of the sprite on the y axis
  @param aInitialPosition The starting position of the sprite on the screen
  @result a pointer to the created instance of CSprite
  */
	static CSprite* NewL(TInt aXVelocity, TInt aYVelocity, const TPoint& aInitialPosition);

/*!
  @function NewLC
  
  @discussion Construct a CSprite using two phase construction, and return a pointer to the created object
  @param aXVelocity The velocity of the sprite on the x axis
  @param aYVelocity The velocity of the sprite on the y axis
  @param aInitialPosition The starting position of the sprite on the screen
  @result a pointer to the created instance of CSprite
  */
	static CSprite* NewLC(TInt aXVelocity, TInt aYVelocity, const TPoint& aInitialPosition);

/*!
  @function Position
  
  @discussion Return the position of the sprite on the screen
  @result The position
  */
	TPoint Position() const;

/*!
  @function Move
  
  @discussion Move the sprite
  @param aSize The size of the sprite
  @param aBounds The rectangle the sprite is allowed to move in
  */
	void Move(const TSize& aSize, const TRect& aBounds);

/*!
  @function ~CSprite
  
  @discussion Destroy the object and release all memory objects
  */
	~CSprite();

private:

/*!
  @function CSprite
  
  @discussion Perform the first phase of two phase construction 
  @param aXVelocity The velocity of the sprite on the x axis
  @param aYVelocity The velocity of the sprite on the y axis
  @param aInitialPosition The starting position of the sprite on the screen
  */
	CSprite(TInt aXVelocity,TInt aYVelocity, const TPoint& aInitialPosition);

/*!
  @function ConstructL
  
  @discussion  Perform the second phase construction of a CSprite object
  */
	void ConstructL();

private:

	/** position of sprite */
	TPoint iPosition;

	/** x axis velocity */
	TInt iXVelocity;

	/** y axis velocity */
	TInt iYVelocity;
};

#endif // __SPRITE_H__

