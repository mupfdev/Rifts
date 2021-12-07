/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __ERRORUI_PAN__
#define __ERRORUI_PAN__

/** ErrorUi application panic codes */
enum TErrorUiPanics 
    {
    EErrorUiBasicUi = 1
    };

inline void Panic(TErrorUiPanics aReason)
    {
    _LIT(applicationName,"ErrorUi");
    User::Panic(applicationName, aReason);
    }

#endif // __ERRORUI_PAN__
