/* Copyright (c) 2001, Nokia. All rights reserved */
/*!
	@header GuiEngineAppView
	
*/

#ifndef __GUIENGINEAPPVIEW_H__
#define __GUIENGINEAPPVIEW_H__


#include <coecntrl.h>

#include "ShapeListManager.h"

class	CGuiEngineDocument;

/*!
  @class CGuiEngineAppView
  @discussion An instance of class CGuiEngineAppView is the Application View object for the
  GUI / Engine example
  */
class CGuiEngineAppView : public CCoeControl
    {
public:
    enum TBrushShapeType {ECircle = 0, ERectangle};

/*!
  @function NewL
  @abstract Creates a CGuiEngineAppView object, which will draw itself to aRect
  @param aRect A rectangle that defines the size and location of the displayable area
  for the view
  @param aDocument the document
  */
    static CGuiEngineAppView* NewL(const TRect& aRect, CGuiEngineDocument* aDocument);

/*!
  @function NewLC
  @abstract Creates a CGuiEngineAppView object, which will draw itself to aRect
  @param aRect A rectangle that defines the size and location of the displayable area
  for the view
  @param aDocument the document
  */
    static CGuiEngineAppView* NewLC(const TRect& aRect, CGuiEngineDocument* aDocument);

/*!
  @function	~CGuiEngineAppView
  @abstract Destroys the object
  */
    ~CGuiEngineAppView();

  
/*!
  @function Clear
  @abstract Clears the view / model
  */
	void Clear();

/*!
  @function SetBrushShapeType
  @abstract Set the type of shape that will be added to the list
  @param aBrushShapeType the shape type of the brush
  */
    void SetBrushShapeType(TBrushShapeType aBrushShapeType);

/*!
  @function BrushShapeType
  @abstract Gets the type of shape that will be added to the list
  @result Returns the type of shape that will be added.
  */
    TBrushShapeType BrushShapeType() const;

/*!
  @function ExternalizeL
  @abstract Saves the view settings to a stream
  @param aStream the stream to save the data to.
  */
    void ExternalizeL(RWriteStream& aStream) const;

/*!
  @function InternalizeL
  @abstract Reads the view settings from a stream
  @param aStream the stream to read the data from.
  */
    void InternalizeL(RReadStream& aStream);

public:	// from CCoeControl
/*!
  @function Draw
  @abstract Draws the view
  @param aRect the rectangle of this view that needs updating
  */
    void Draw(const TRect& aRect) const;

/*!
  @function OfferKeyEventL
  @abstract Handle the user pressing a key
  @param aKeyEvent Details of the event that has occured
  @param aType The type of event that has occured
  */
  TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);


private: 

/*!
  @function CGuiEngineAppView
  @abstract Performs the first stage construction
  @param aModel the model
  */
    CGuiEngineAppView(CGuiEngineDocument* aDocument);

/*!
  @function ConstructL  
  @abstract Performs the second phase construction, setting the bounding 
  rectangle to aRect
  @param aRect the display area for the view
  */
    void ConstructL(const TRect& aRect);

private:
	/*! @var iDocument The document	*/
	CGuiEngineDocument* iDocument;

    /*! @var iBrushShapeType The type of shape currently selected for adding */
    TBrushShapeType iBrushShapeType;

    /*! @var iPosition The current 'cursor' position */
	TPoint iPosition;
};


#endif // __GUIENGINEAPPVIEW_H__
