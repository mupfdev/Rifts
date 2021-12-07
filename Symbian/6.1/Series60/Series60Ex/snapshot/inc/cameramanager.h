/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __CAMERAMANAGER_H__
#define __CAMERAMANAGER_H__

#include <e32base.h>
#include <CameraServ.h>

class MCameraObserver;


/*! 
  @class CCameraManager
  
  @discussion An instance of this manages the camera operations
  */
class CCameraManager : public CActive
	{
private:
    enum TCameraState
        {
        EUninitalised,      //  Uninitalised
        EStartingCamera,    //  Started turning the camera on
        EReady,             //  Idle
        ETakingPicture,     //  Busy taking a picture
        EError              //  Error has occured
        };

public:	//	New methods
/*!
  @function NewL
   
  @discussion Create a CCameraManager object
  @param aObserver the object to be notified when a picture is taken, or an error
  occurs
  @result a pointer to the created instance of CCameraManager
  */
	static CCameraManager* NewL(MCameraObserver& aObserver);
/*!
  @function NewLC
   
  @discussion Create a CCameraManager object
  @param aObserver the object to be notified when a picture is taken, or an error
  occurs
  @result a pointer to the created instance of CCameraManager
  */
	static CCameraManager* NewLC(MCameraObserver& aObserver);

/*!
  @function ~CCameraManager
  
  @discussion Destroy the object and release all memory objects
  */
	~CCameraManager();


/*!
  @function IsReady
  
  @discussion Check if the camera is ready to take a picture.
  @result ETrue if the camera is ready, otherwise EFalse
  */
    TBool IsReady();

/*!
  @function Snap
  
  @discussion Take a picture.
  @param aBitmap the bitmap to hold the picture
  */
    void Snap(CFbsBitmap& aBitmap);

protected:	//	New methods
/*!
  @function CCameraManager
  
  @discussion Perform the first phase of two phase construction
  @param aView the view that is to be updated
  */
	CCameraManager(MCameraObserver& aObserver);

protected:	// from CActive
/*!
  @function DoCancel
  
  @discussion Cancel the request
  */
	void DoCancel();

/*!
  @function RunL
  
  @discussion Mark the current operation as completed
  */
	void RunL();

private:	//	New methods
/*!
  @function ConstructL
  
  @discussion  Perform the second phase construction of a CCameraManager object
  */
	void ConstructL();


private:
	/*! @var iCameraServer the sever that controls the camera */
    RCameraServ   iCameraServer;

	/*! @var iObserver the object to notify after taking a picture */
    MCameraObserver& iObserver;

	/*! @var iCameraState current state of the camera */
    TCameraState iCameraState;
	};

#endif // __CAMERAMANAGER_H__

