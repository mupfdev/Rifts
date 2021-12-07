/* Copyright (c) 2001, Nokia. All rights reserved */

/*!
	@header circle
	
*/

#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include <e32std.h>
#include <w32std.h>

#include "shape.h"

namespace NShapes 
{

	/*!
		@class	TCircle

		@discussion	An instance of class TCircle is a circular shape.
		*/
	class TCircle : public TShape
		{
	public:
	/*!
	  @function	TCircle
	  @abstract	Creates an instance of TCircle at a specified position, and of a 
	  specified radius.
	  @param	aCenter where the center of the circle is located.
	  @param	aRadius The radius of the circle
	  */
	    IMPORT_C TCircle(const TPoint& aCenter, TInt aRadius);

	/*!
	  @function	TCircle
	  @abstract	Creates an instance of TCircle 
	  */
	    IMPORT_C TCircle();

	public:	//	From TShape
	/*!
	  @function	Draw
	  @abstract	Virtual method that draws the shape to the specified
	  graphics context.
	  @param	aActiveGraphicsContext the active context to draw the shape into.
	  */
		IMPORT_C void Draw(CWindowGc& aActiveGraphicsContext) const ;

	/*!
	  @function	GetRect
	  @abstract	Returns the smallest bounding rectangle that entirely contains the shape.
	  */
		IMPORT_C TRect GetRect() const;

	/*!
	  @function	ExternalizeL
	  @abstract	Virtual method that writes the shape to the specified
	  write stream.
	  @param	aStream the stream to write the shape to.
	  */
		IMPORT_C void ExternalizeL(RWriteStream& aStream) const;

	/*!
	  @function	InternalizeL
	  @abstract	Virtual method that reads the shape from the specified
	  read stream.
	  @param	aStream the stream to read the shape from.
	  */
		IMPORT_C void InternalizeL(RReadStream& aStream);

	private:
		/*! @var iRadius	The Radius of the circle	*/
		TInt iRadius;
		};

	}

#endif	//	__CIRCLE_H__
