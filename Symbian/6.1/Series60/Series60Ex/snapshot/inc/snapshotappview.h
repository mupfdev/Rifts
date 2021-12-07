/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __SNAPSHOTAPPVIEW_H__
#define __SNAPSHOTAPPVIEW_H__


#include <coecntrl.h>
#include <CameraServ.h>

#include "CameraManager.h"
#include "CameraObserver.h"

/*! 
  @class CSnapShotAppView
  
  @discussion An instance of class CSnapShotAppView is the Application View object 
  for the SnapShot example application
  */
class CSnapShotAppView : public CCoeControl, public MCameraObserver
    {
public:

/*!
  @function NewL
   
  @discussion Create a CSnapShotAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CSnapShotAppView
  */
    static CSnapShotAppView* NewL(const TRect& aRect);

/*!
  @function NewLC
   
  @discussion Create a CSnapShotAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CSnapShotAppView
  */
    static CSnapShotAppView* NewLC(const TRect& aRect);


/*!
  @function ~CSnapShotAppView
  
  @discussion Destroy the object and release all memory objects
  */
     ~CSnapShotAppView();

/*!
  @function IsCameraReady

  @discussion Check if the camera is ready to take a picture
  @result ETrue if the camera is ready, EFalse otherwise
  */
     TBool IsCameraReady();

/*!
  @function Snap

  @discussion Take a picture
  */
     void Snap();

public:  // from CCoeControl
/*!
  @function Draw
  
  @discussion Draw this CSnapShotAppView to the screen
  @param aRect the rectangle of this view that needs updating
  */
    void Draw(const TRect& aRect) const;
  
public:	//	from MCameraObserver

/*!
  @function PictureTaken
   
  @discussion Called when the camera has finished taking a picture
  */
	void	PictureTaken();

/*!
  @function Error
   
  @discussion Called when an error occurs
  @param aError the error code for the error
  */
	void	Error(TInt aError);

private:

/*!
  @function ConstructL
  
  @discussion  Perform the second phase construction of a CSnapShotAppView object
  @param aRect the rectangle this view will be drawn to
  */
    void ConstructL(const TRect& aRect);

/*!
  @function CSnapShotAppView
  
  @discussion Perform the first phase of two phase construction 
  */
    CSnapShotAppView();


    /*! @var iCameraManager the manager for the camera */
    CCameraManager* iCameraManager;

    /*! @var iBitmap where to put the picture */
    CFbsBitmap* iBitmap;
    };

#endif // __SNAPSHOTAPPVIEW_H__
