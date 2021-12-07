/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __ASYNCTIMEOBSERVER_H__
#define __ASYNCTIMEOBSERVER_H__

/*! 
  @class MAsyncTimeObserver
  
  @discussion Mixin class. Observer which handles updates from the server 
  example application
  */
class MAsyncTimeObserver
	{
public:
/*!
  @function HandleTimeUpdate
  
  @discussion handle updates from the server
  */
	virtual void HandleTimeUpdate() = 0;
	};

#endif