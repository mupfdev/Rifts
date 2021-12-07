/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __EIKONENVIRONMENT_H__
#define __EIKONENVIRONMENT_H__


#include <e32base.h>

class CEikAppUi;
class CEikonEnv;
class CEikDocument;
class CCoeControl;
class RFs;

/*! 
  @namespace NEikonEnvironment
  
  @discussion Useful functions based around the Eikon environment
  */
namespace NEikonEnvironment
	{

/*!
  @function EikAppUi
   
  @discussion the appui
  @result a reference to the CEikAppUi
  */
	CEikAppUi& EikAppUi();

/*!
  @function EikEnv
   
  @discussion the eikon environment
  @result a reference to the CEikonEnv
  */
	CEikonEnv& EikEnv();

/*!
  @function EikDocument
   
  @discussion the document
  @result a reference to CEikDocument
  */
	CEikDocument& EikDocument();

/*!
  @function AddToStackL
   
  @discussion add a control to the control stack
  @param aControl the control to add
  */
	void AddToStackL(CCoeControl& aControl);

/*!
  @function AddToStackL
   
  @discussion add a control to the control stack given a priority and flags
  @param aControl the control to add
  @param aPriority the priority
  @param aStackingFlags the flags
  */
	void AddToStackL(CCoeControl& aControl,TInt aPriority,TInt aStackingFlags);

/*!
  @function RemoveFromStack
   
  @discussion remove a control from the control stack
  @param aControl the control to remove
  */
	void RemoveFromStack(CCoeControl& aControl);

/*!
  @function AppFullName
   
  @discussion the full name of the application
  @result the name
  */
	TFileName AppFullName();

/*!
  @function ApplicationDriveAndPath
   
  @discussion the drive and path of the application
  @result the drive and path
  */
	TFileName ApplicationDriveAndPath();

/*!
  @function AddPath
   
  @discussion convert a filename to a filename with the drive and path of the application added
  @result the drive, path and filename
  @param aFileName the file name to convert
  */
	TFileName AddPath(const TDesC& aFileName);

/*!
  @function MessageBox
   
  @discussion Display a message box
  @param the message to display
  */
	void MessageBox(const TDesC&  aMessage);

/*!
  @function FlushWindowServer
   
  @discussion flush the windows server to ensure all changes to the display are reflected on the screen
  */
	void FlushWindowServer();

/*!
  @function TheRFs
   
  @discussion the eikon frameworks file server connection
  @result a reference to the RFs
  */
	RFs& TheRFs();

	}



#endif //__EIKONENVIRONMENT_H__
