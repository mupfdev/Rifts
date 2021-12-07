// COEAUIB.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COEAUIB_H__)
#define __COEAUIB_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

class CCoeControl;
class TWsEvent;

/**
 * The CCoeAppUiBase class is the abstract base class for all application-wide user interface classes.
 */
class CCoeAppUiBase : public CBase
    {
public:

	/**
	 * Handles the window server event aEvent which ocurred in the control aDestination.
	 */
    virtual void HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination)=0;
	IMPORT_C virtual void PrepareToExit();
// reserved virtual function space
private:
	IMPORT_C virtual void Reserved_1();
	IMPORT_C virtual void Reserved_2();
    };

#endif
