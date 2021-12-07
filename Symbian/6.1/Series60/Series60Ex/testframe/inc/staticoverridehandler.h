/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __STATICOVERRIDEHANDLER_H__
#define __STATICOVERRIDEHANDLER_H__

#include <e32base.h>

/*! 
  @class MStaticOverrideHandler
  
  @discussion an observer of static overrides
  */
class MStaticOverrideHandler
	{
public:

/*!
  @function OnPanicL
   
  @discussion called by the static overrides when a panic occurs
  @param aCategory panic category
  @param aReason reason number
  */
	virtual void OnPanicL(const TDesC& aCategory, TInt aReason) = 0;

/*!
  @function OnInvariantL
   
  @discussion called by the static overrides when an invariant is bad
  */
	virtual void OnInvariantL() = 0;

	};


#endif //__STATICOVERRIDEHANDLER_H__
