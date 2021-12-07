// AKNWSEVENTOBSERVER.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// Support for events to be sent independent of the control stack to other consumers yet 
// internal to the application 
//
#if !defined(__AKNWSEVENTOBSERVER_H__)
#define __AKNWSEVENTOBSERVER_H__

// INCLUDES
#include <e32std.h>
//#include <w32std.h>
#include <coecntrl.h>

// CONSTANTS

enum TAknWsEventObserverPanic
	{
	EAknWsEventObserverFailedToAddObserver,
	EAknWsEventObserverUnknownObserverRemoved
	};

GLREF_C void Panic(TAknWsEventObserverPanic aPanic);


// CLASS DECLARATION

class MAknWsEventObserver
	{
public:
	virtual void HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination) = 0;
	};


// 
// This class distributes events to the Ws event observers; It is itself a Ws event observer
//

class CAknWsEventMonitor: public CBase, public MAknWsEventObserver
{
public:
	static CAknWsEventMonitor* NewL();
	virtual ~CAknWsEventMonitor();
	void ConstructL();
	IMPORT_C void AddObserverL(MAknWsEventObserver* aEventObserver);
	IMPORT_C void RemoveObserver(const MAknWsEventObserver* aEventObserver);
	IMPORT_C void HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination);
private:
	MAknWsEventObserver* iEventObserver;
	TInt iSpare;
private:
// reserved virtual function space
	IMPORT_C virtual void Reserved_1();

};


#endif  // __AKNWSEVENTOBSERVER_H__