/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __HELLOWORLD_PAN__
#define __HELLOWORLD_PAN__

/** HelloWorld application panic codes */
enum THelloWorldPanics 
    {
    EHelloWorldBasicUi = 1
    // add further panics here
    };

inline void Panic(THelloWorldPanics aReason)
    {
	_LIT(applicationName,"HelloWorld");
    User::Panic(applicationName, aReason);
    }

#endif // __HELLOWORLD_PAN__
