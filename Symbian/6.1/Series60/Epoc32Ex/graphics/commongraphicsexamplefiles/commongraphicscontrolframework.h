// CommonGraphicsControlFramework.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.


#ifndef __CommonGraphicsControlFramework_H
#define __CommonGraphicsControlFramework_H

#include <coecntrl.h>
#include <s32file.h>

//
// class MGraphicsExampleObserver
//

class MGraphicsExampleObserver
	{
public:
	virtual void NotifyGraphicExampleFinished()=0;
	virtual void NotifyStatus(const TDesC& aMessage)=0;
	};

//
// class CGraphicExampleControl
//

/*
	Usage

		Use this class as a base class for examples for the
		graphics layer.  It uses CONE's facilities to provide
		an initailized graphics environment.

		It creates a 600x200 window in which you can do your
		drawing.

		it supports multiple phases, so you can do different drawings
		from one phase to another.  Tap the spacebar or click the
		mouse (anywhere) to advance a phase.

		Quit the program with CTRL-Q, or by advancing beyond the last
		phase.

	Writing derived classes

		A minimal derived class should have a Draw() function
		which puts a drawing onto the screen.

		If you are using multiplephases, code a constructor which
		calls SetMaxPhases() specifying the number of phases.  Have
		Draw() honour the phase number, available using Phase().
*/

#pragma warning(disable : 4100)
		// disable "parameter not used" warning on HandleKey()

class CGraphicExampleControl : public CCoeControl
	{
public:
	// construct/destruct
	void ConstructL(const TRect& aRect, MGraphicsExampleObserver* aGraphObserver, const CCoeControl& aParent);
		// second-phase construction
		// when all initialized, calls GraphicTestEnvironmentComplete()
	~CGraphicExampleControl();
	// allow access by container
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
		// intercepts ctrl-Q and space; offers other keys to derived classes
protected:
	// derived classes must provide these
	virtual void UpdateModelL() =0; // empty update model function
	virtual void Draw(const TRect& /* aRect */) const {}; // empty draw function
	// use Phase() in Draw() to tell what phase we're in
	TInt Phase() const { return iPhase; }; // get phase number
	void SetMaxPhases(TInt aMaxPhases) { iMaxPhases=aMaxPhases; };
			// use this from derived-class constructor to set number of phases
	CFont* iMessageFont; // font for messages
private:
	// functions provided for CCoeControl protocol
	void HandlePointerEventL(const TPointerEvent& aPointerEvent);
		// advances phase on pointer-down
	void Quit(); // does termination
	void NextPhaseL(); // advances phase: quits if all  phases done
	// phase control for graphics examples
	TInt iPhase; // phase number
	TInt iMaxPhases; // maximum phases
protected:
	MGraphicsExampleObserver* iGraphObserver;
	};

#endif