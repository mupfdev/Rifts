/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __STATICOVERRIDEACCESS_H__
#define __STATICOVERRIDEACCESS_H__

class MStaticOverrideHandler;

/*! 
  @namespace NStaticOverrideAccess
  
  @discussion A set of functions allowing us to store the address of an instance of
  a MStaticOverrideHandler in thread local storage
  */
namespace NStaticOverrideAccess
	{
/*!
  @function SetHandler
   
  @discussion Store the address of the MStaticOverrideHandler
  @param aHandler A reference to the MStaticOverrideHandler
  */
	void SetHandler(MStaticOverrideHandler& aHandler);

/*!
  @function GetHandler
   
  @discussion Retrieve the address of the MStaticOverrideHandler
  @result A pointer to the MStaticOverrideHandler NOTE:could return NULL if a call to SetHandler
  has not already been made
  */
	MStaticOverrideHandler* GetHandler();
	}


#endif //__STATICOVERRIDEACCESS_H__