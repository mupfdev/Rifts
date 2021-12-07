/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __CIPHER_PAN__
#define __CIPHER_PAN__

/** Cipher application panic codes */
enum TCipherPanics 
    {
    ECipherBasicUi = 1,
	ECipherInvalidComponentIndex
    // add further panics here
    };

inline void Panic(TCipherPanics aReason)
    {
    _LIT(applicationName,"Cipher");
    User::Panic(applicationName, aReason);
    }

#endif // __CIPHER_PAN__
