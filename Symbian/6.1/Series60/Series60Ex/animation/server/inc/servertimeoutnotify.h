/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __SERVERTIMEOUTNOTIFY_H__
#define __SERVERTIMEOUTNOTIFY_H__


/*! 
  @class MTimeoutNotify
  
  @discussion An instance of a class derived from MTimeoutNotify is an object which can be 
              informed when a timeout completes
  */
class MTimeoutNotify 
    {
public:
/*!
  @function TimedOut
  
  @discussion Handle the event when a time out occurs
  */
    virtual void TimedOut() = 0;
    };

#endif //__SERVERTIMEOUTNOTIFY_H__

