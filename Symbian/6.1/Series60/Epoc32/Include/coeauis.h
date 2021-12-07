// COEAUIS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COEAUIS_H__)
#define __COEAUIS_H__

#if !defined(__COEAUIB_H__)
#include <coeauib.h>
#endif

#if !defined(__W32STD_H__)
#include <w32std.h>
#endif

/**
 * The CCoeAppUiSimple class implements a simple app UI. Applications which use
 * it designate a root control which receives all key events for the application.
 * The root control must handle key events itself or channel them to other controls.
 *
 * @deprecated Deprecated in App-Framework_6.1
 */
class CCoeAppUiSimple : public CCoeAppUiBase
	{
public:
	IMPORT_C CCoeAppUiSimple();
	IMPORT_C ~CCoeAppUiSimple();
public: // new functions
	IMPORT_C void SetRootControl(CCoeControl* aControl);
protected: // from CCoeAppUiBase
	IMPORT_C void HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination);
private: // new functions
	IMPORT_C virtual void HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C virtual void HandleForegroundEventL(TBool aForeground);
private:
	CCoeControl* iRootControl;
	};

#endif
