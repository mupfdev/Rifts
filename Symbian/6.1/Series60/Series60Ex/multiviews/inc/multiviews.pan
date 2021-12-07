/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __MULTIVIEWS_PAN__
#define __MULTIVIEWS_PAN__

/** MultiViews application panic codes */
enum TMultiViewsPanics 
    {
    EMultiViewsBasicUi = 1
    // add further panics here
    };

inline void Panic(TMultiViewsPanics aReason)
    {
	_LIT(applicationName,"MultiViews");
    User::Panic(applicationName, aReason);
    }

#endif // __MULTIVIEWS_PAN__
