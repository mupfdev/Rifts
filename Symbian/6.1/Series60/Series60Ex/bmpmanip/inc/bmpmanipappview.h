/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __BMPMANIPAPPVIEW_H__
#define __BMPMANIPAPPVIEW_H__


#include <coecntrl.h>
#include <MdaImageConverter.h>


/*! 
  @class CBmpmanipAppView
  
  @discussion An instance of the Application View object for the Bmpmanip 
  example application
  */
class CBmpmanipAppView : public CCoeControl, public MMdaImageUtilObserver
    {
public:

	/** Valid angles to rotate image */
	enum TImageRotateAngle
		{
		E90Degrees,
		E180Degrees,
		E270Degrees
		};

public:

/*!
  @function NewL
   
  @discussion Create a CBmpmanipAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CBmpmanipAppView
  */
    static CBmpmanipAppView* NewL(const TRect& aRect);

/*!
  @function NewLC
   
  @discussion Create a CBmpmanipAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CBmpmanipAppView
  */
    static CBmpmanipAppView* NewLC(const TRect& aRect);


/*!
  @function ~CBmpmanipAppView
  
  @discussion Destroy the object and release all memory objects
  */
     ~CBmpmanipAppView();


public:  // from CCoeControl
/*!
  @function Draw
  
  @discussion Draw this CBmpmanipAppView to the screen
  @param aRect the rectangle of this view that needs updating  
  */
    void Draw(const TRect& aRect) const;
  

public:	 //from MMdaImageUtilObserver

/*!
  @function MiuoOpenComplete
  
  @discussion Called when the gif file has been opened
  @param aError an error code or KErrNone if process was successful
  */
	virtual void MiuoOpenComplete(TInt aError);

/*!
  @function MiuoConvertComplete
  
  @discussion Called when any conversion process performed on the bitmap is complete
  @param aError an error code or KErrNone if process was successful
  */
	virtual void MiuoConvertComplete(TInt aError);

/*!
  @function MiuoCreateComplete
  
  @discussion Called when the file in which the bitmap is to be saved has been created 
  @param aError an error code or KErrNone if process was successful
 */
	virtual void MiuoCreateComplete(TInt aError);


public:  //new functions

/*!
  @function RotateImageClockwiseL
  
  @discussion Rotate the bitmap clockwise
  @param aAngle an enum representing an angle to rotate
  */
	void RotateImageClockwiseL(TImageRotateAngle aAngle);

/*!
  @function SaveL
  
  @discussion Save the bitmap to a new file
  */
	void SaveL();

private:

/*!
  @function ConstructL
  
  @discussion  Perform the second phase construction of a CBmpmanipAppView object
  @param aRect the rectangle this view will be drawn to
  */
    void ConstructL(const TRect& aRect);

/*!
  @function CBmpmanipAppView
  
  @discussion Perform the first phase of two phase construction 
  */
    CBmpmanipAppView();

/*!
  @function ConvertingFromGifFinished
  
  @discussion  Called when the the file has been converted to a GIF
  @param aError an error code or KErrNone if process was successful  
*/
	void ConvertingFromGifFinished(TInt aError);
/*!
  @function SavingFinished
  
  @discussion  Called when the the file has been saved
  @param aError an error code or KErrNone if process was successful  
*/
	void SavingFinished(TInt aError);
/*!
  @function ScalingFinished
  
  @discussion  Called when scaling has completed
  @param aError an error code or KErrNone if process was successful  
*/
	void ScalingFinished(TInt aError);
/*!
  @function RotatingFinished
  
  @discussion  Called when rotating has completed
  @param aError an error code or KErrNone if process was successful  
*/
	void RotatingFinished(TInt aError);

private:
	/** Keeps track of which stage the open/conversion/creating process is at */
	enum TConvertState
		{
		EConvertStateNull,
		EConvertStateConvertingFromGif,
		EConvertStateScaling,
		EConvertStateRotating,
		EConvertStateSaving,
		EConvertStateReady
		} iConvertState;

private:

	/** Converts the gif file to a bitmap */
	CMdaImageFileToBitmapUtility*		iConverter;
	/** Scales the bitmap */
	CMdaBitmapScaler*					iScaler;
	/** Rotates the bitmap */
	CMdaBitmapRotator*					iRotator;
	/** Saves a bitmap file */
	CMdaImageBitmapToFileUtility*		iFileSaver;

	/** The bitmap being displayed */
	CFbsBitmap*							iBitmap;

	/** The format to be loaded (i.e. gif) */
	TMdaBmpClipFormat					iClipFormat;
	/** The codec used to perform the conversion */
	TMda24BppBmpCodec					iCodec;

    };


#endif // __BMPMANIPAPPVIEW_H__
