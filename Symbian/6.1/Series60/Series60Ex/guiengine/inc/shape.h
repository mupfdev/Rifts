/* Copyright (c) 2001, Nokia. All rights reserved */

/*!
	@header shape
	
*/

#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <e32std.h>
#include <w32std.h>


namespace NShapes 
    {

	enum TShapeType
        {
        KRectangle = 1,
	    KCircle
        };

	/*!
	  @class	TShape
	  @discussion	An abstract class.
	  */
	class TShape 
		{
	public:
	/*!
	  @function	TShape
	  @abstract	Constructor that creates the shape at a specific point.
      @param    aShapeType the type of the actual shape.
	  @param	aOrigin where the origin of the shape is located.
	  */
		IMPORT_C TShape (TShapeType aShapeType, const TPoint& aOrigin);

	/*!
	  @function	Draw
	  @abstract	Pure virtual method that draws the shape to the specified
	  graphics context.
	  @param	aActiveGraphicsContext the active context to draw the shape into.
	  */
		virtual void Draw(CWindowGc& aActiveGraphicsContext) const = 0;

	/*!
	  @function	GetRect
	  @abstract	Pure virtual method that returns the smallest bounding
	  rectangle that entirely contains the shape.
	  */
		virtual TRect GetRect() const = 0;

	/*!
	  @function	ReadShapeTypeL
	  @abstract	Static method that reads the type of the next shape from 
	  a stream.
	  @param	aStream The stream to read from
	  @result	Returns the type of the next shape
	  */
		IMPORT_C static TShapeType ReadShapeTypeL(RReadStream& aStream);
    
	/*!
	  @function	ExternalizeL
	  @abstract	Virtual method that writes the shape to the specified
	  write stream.
	  @param	aStream the stream to write the shape to.
	  */
		IMPORT_C virtual void ExternalizeL(RWriteStream& aStream) const;
    
	/*!
	  @function	InternalizeL
	  @abstract	Virtual method that reads the shape from the specified
	  read stream.
	  @param	aStream the stream to read the shape from.
	  */
		IMPORT_C virtual void InternalizeL(RReadStream& aStream);

	protected:
        /*! @var iShapeType The type of the actual shape */
        const TShapeType iShapeType;

		/*! @var iOrigin	The origin of the shape	*/
		TPoint iOrigin;
		};

	}

#endif	//	__SHAPE_H__
