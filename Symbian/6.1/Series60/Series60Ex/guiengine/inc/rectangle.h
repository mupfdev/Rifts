/* Copyright (c) 2001, Nokia. All rights reserved */

/*!
	@header rectangle
	
*/

#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include <e32std.h>
#include <w32std.h>

#include "shape.h"


namespace NShapes 
{


	/*!
	  @class	TRectangle
	  @discussion	An instance of class TRectangle is a rectangular shape.
	  */
	class TRectangle : public TShape
		{
	public:
	/*!
	  @function	TRectangle
	  @abstract	Creates an instance of TRectangle at a specified position, and of a 
	  specified size.
	  @param	aOrigin where the origin of the shape is located.
	  @param	aWidth The width of the rectangle
	  @param	aHeight The height of the rectangle
	  */
		IMPORT_C TRectangle(const TPoint& aOrigin, TInt aWidth, TInt aHeight);

	/*!
	  @function	TRectangle
	  @abstract	Creates an instance of TRectangle.
	  */
		IMPORT_C TRectangle();

	public:	//	From TShape
	/*!
	  @function	Draw
	  @abstract	Virtual method that draws the shape to the specified
	  graphics context.
	  @param	aActiveGraphicsContext the active context to draw the shape into.
	  */
		IMPORT_C void Draw(CWindowGc& aActiveGraphicsContext) const;

	/*!
	  @function	GetRect
	  @abstract	Returns the smallest bounding
	  rectangle that entirely contains the shape.
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
		/*! @var iWidth	The width of the rectangle	*/
		TInt iWidth;
		/*! @var iHeight The height of the rectangle	*/
		TInt iHeight;
		};


	}

#endif	//	__RECTANGLE_H__
