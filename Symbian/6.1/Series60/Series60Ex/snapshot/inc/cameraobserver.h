/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __CAMERAOBSERVER_H__
#define __CAMERAOBSERVER_H__


/*! 
  @class MCameraObserver
  
  @discussion An instance of this observes the camera operations.
  This is an abstract base class so must be derrived from to be
  used.
  */
class MCameraObserver
	{
public:	//	New methods

/*!
  @function PictureTaken
   
  @discussion Called when the camera has finished taking a picture
  */
	virtual void	PictureTaken() = 0;

/*!
  @function Error
   
  @discussion Called when an error occurs
  @param aError the error code for the error
  */
	virtual void	Error(TInt aError) = 0;
	};

#endif // __CAMERAOBSERVER_H__