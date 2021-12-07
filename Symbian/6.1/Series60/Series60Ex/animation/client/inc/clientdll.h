/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __RCLIENT_DLL_H__
#define __RCLIENT_DLL_H__


#if !defined __W32ADLL_H__
#include <w32adll.h>
#endif

/*! 
  @class RClientDll
  
  @discussion An instance of RClientDll is an Animation Client DLL, used to load 
              and destroy the Animation Server
  */
class RClientDll : public RAnimDll
    {
public:
/*!
  @function CAnimationAppUi
  
  @discussion Construct an Animation Client DLL object for use with the 
              aSession window server session 
  @param aSession the window server session to use
  */
    IMPORT_C RClientDll(RWsSession& aSession);
    };
 
#endif //__RCLIENT_DLL_H__