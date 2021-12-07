// TXTEXAMP.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#ifndef __TXTEXAMP_H
#define __TXTEXAMP_H

#include <coemain.h>
#include <coecntrl.h>
#include <s32file.h>
#include <txtglobl.h>
#include <frmtview.h>
#include <txtfmlyr.h>

//
// class MGraphicsExampleObserver
//

class MGraphicsExampleObserver
	// Defines an interface that controls can call to inform the shell 
	// that they have finished, or that the status message display needs 
	// updating. It is implemented by CExampleShellContainer	
	{
public:
	// Notify user that example has finished
	virtual void NotifyGraphicExampleFinished()=0;
	// Notify user of the current status of the example
	virtual void NotifyStatus(const TDesC& aMessage)=0;
	};

//
// class CGraphicExampleControl
//

/*
	Usage

		This class is used as a base class for graphics and text 
		examples. It uses CONE's facilities to provide an initialized 
		graphics environment.

		It creates a 600x200 window in which drawing can be done.

		It supports multiple phases, so different drawings can be 
		done from one phase to another.  Tap the spacebar or click the
		mouse (anywhere) to advance a phase.

		Quit the program by pressing the exit button.

	Writing derived classes

		A minimal derived class should have a Draw() function
		which puts a drawing onto the screen.

		If you are using multiple phases, code a constructor which
		calls SetMaxPhases() specifying the number of phases.  Have
		Draw() honour the phase number, available using Phase().
*/

#pragma warning(disable : 4100)
		// disable "parameter not used" warning on HandleKey()

class CGraphicExampleControl : public CCoeControl
	{
public:
	// construct/destruct
	void ConstructL(const TRect& aRect, MGraphicsExampleObserver* aObserver, const CCoeControl& aParent);
		// second-phase construction
	~CGraphicExampleControl();
	// public so container can offer keys
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
		// intercepts space; offers other keys to derived classes
protected:
	// derived classes must provide the next 2 functions
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
	void NextPhaseL(); // advances phase: quits if all phases done
	// phase control for graphics examples
	TInt iPhase; // phase number
	TInt iMaxPhases; // maximum phases
protected:
	MGraphicsExampleObserver* iFormObserver;
	TBool iUpdateModelDoesRedraw; // whether UpdateModelL() does a redraw for us
	};

// sundry derived classes

class CGlobalText;
class CRichText;
class CParaFormatLayer;
class CCharFormatLayer;
class CTextLayout;
class CTextView;
class CStyleList;
class CParagraphStyle;


class CGlobalControl : public CGraphicExampleControl
	{
	// Demonstrates the use of global text
public:
	CGlobalControl() { SetMaxPhases(16); };
	void UpdateModelL();
	void Draw(const TRect& aRect) const;
	~CGlobalControl();
private:
	CGlobalText* iGlobalText; // global text object
	CParaFormatLayer* iParaFormatLayer;
	CCharFormatLayer* iCharFormatLayer;
	TStreamId iStreamId; // required when storing and restoring global text
	// text layout and view stuff
	CTextLayout* iLayout; // text layout
	CTextView* iTextView; // text view
	TRect iViewRect; // rectangle through which to view text
	};

class CRichControl : public CGraphicExampleControl
	{
	// Demonstrates the use of rich text
public:
	CRichControl() { SetMaxPhases(14);}; 
	~CRichControl(); // destructor
	void UpdateModelL();
	void Draw(const TRect& aRect) const;
private:
	CRichText* iRichText; // global text object
	CParaFormatLayer* iParaFormatLayer;
	CCharFormatLayer* iCharFormatLayer;
	TStreamId iStreamId; // required when storing and restoring global text
	// text layout and view stuff
	CTextLayout* iLayout; // text layout
	CTextView* iTextView; // text view
	TRect iViewRect; // rectangle through which to view text
	};

class CStyleControl : public CGraphicExampleControl
	{
	// Demonstrates the use of styles in rich text
public:
	CStyleControl() { SetMaxPhases(9);}; 
	~CStyleControl(); // destructor
	void UpdateModelL();
	void Draw(const TRect& aRect) const;
private:
	void CreateNormal(); // Create Normal style (the global layers) 
	void CreateStyles(); // Create some paragraph styles
private:
	CRichText* iRichText; // rich text object
	CParaFormatLayer* iNormalParaFormatLayer;
	CCharFormatLayer* iNormalCharFormatLayer;
	TStreamId iStreamId; // required when storing and restoring global text
	// text layout and view stuff
	CTextLayout* iLayout; // text layout
	CTextView* iTextView; // text view
	TRect iViewRect; // rectangle through which to view text
	CStyleList* iStyleList; // Style list holds the two styles
	CParagraphStyle* iStyleOne;
	CParagraphStyle* iStyleTwo;
	};

class CViewControl : public CGraphicExampleControl
	{
	// Demonstrates the use of the text view and text layout classes
public:
	CViewControl() { SetMaxPhases(14);}; 
	~CViewControl(); 
	void UpdateModelL();
	void Draw(const TRect& aRect) const;
private:
	CRichText* iRichText; // rich text object
	CParaFormatLayer* iParaFormatLayer;
	CCharFormatLayer* iCharFormatLayer;
	// text layout and view stuff
	CTextLayout* iLayout; // text layout
	CTextView* iTextView; // text view
	TRect iViewRect; // rectangle through which to view text
	CFbsBitmap* iBitmap; // line cursor bitmap
	};

#endif
