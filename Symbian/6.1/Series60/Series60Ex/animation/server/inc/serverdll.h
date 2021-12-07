/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __CSERVERDLL_H__
#define __CSERVERDLL_H__

#if !defined __W32ADLL_H__
#include <w32adll.h>
#endif

/*! 
  @class CServerDll
  
  @discussion An instance of CServerDll is a 'factory' object which creates a new 
              instance of CAnim
  */
class CServerDll : public CAnimDll 
    {
public: // New methods
/*!
  @function CServerDll
  
  @discussion Construct an Animation Server dll
  */
    CServerDll ();

// Public destructor not created as this class does not own any data

public: // From CAnimDll
/*!
  @function CreateInstanceL
  
  @discussion Create an instance of the Animation Server image aType, 
  @param aType KAnimationSquare implies "construct a bouncing square" 
  */
    IMPORT_C CAnim* CreateInstanceL(TInt aType);

    };

#endif // __CSERVERDLL_H__

