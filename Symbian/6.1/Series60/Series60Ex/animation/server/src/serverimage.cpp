/* Copyright (c) 2001, Nokia. All rights reserved */
#include <e32std.h>
#include <e32base.h>
#include <txtfrmat.h>

#include "servertimeouttimer.h"
#include "serverimage.h"
#include "animation.pan"

// local constants
static const TInt KStepSize = 1;           // Pixels the animation moves each timer event 
static const TInt KAnimationReset  = 1;    // Request a reset of the bouncing square 


// The timer timeout resolution is different in the WINS and MARM platforms 
// under wins it is 1/10s, under marm it is 1/64s, also both platforms have
// a different time taken to draw the object
#ifdef __WINS__
static const TInt KTimerPeriod = 10000;
#else
static const TInt KTimerPeriod = 150000;
#endif


// Animation server object class functions
// these functions are called by the windows server from requests made by the 
// client animation dll

// Non trival construction
// does not (currently) make use of the optional parameters aArgs or if the
// object has focus
void CImage::ConstructL(TAny* /* aArgs */, TBool /* aHasFocus */)
    {
    // Initialise starting points to the top left hand corner
    iLastPoint.SetXY(0, 0);
    iNewPoint.SetXY(1, 1);

    // Set up how far the shape moves each timer event
    iDeltaX = KStepSize;
    iDeltaY = KStepSize;

    // Animation reset not requested by user
    iAnimationReset = EFalse;

    // initiates an initial position update
    iDrawn = ETrue;

    // Set the rectangles size
    iSize.SetSize(20,20);

    // Store the screen size
    iScreenSize = iWindowFunctions->WindowSize();

    // Set the screen visible
    iWindowFunctions->SetVisible(ETrue);

    // We are using a timer, not the built in synchronising, so turn it off
    iFunctions->SetSync(MAnimGeneralFunctions::ESyncNone);

    // Create the timeout timer
    iServerTimer = CTimeOutTimer::NewL(EPriorityHigh, *this);

    // Set the timeout period
    iServerTimer->After(KTimerPeriod);
    }


// Redraw the animation server object, includes rubbing out the old object
void CImage::Redraw()
    {
    // get the background colour
    TLogicalRgb backgroundColour(TLogicalRgb::ESystemBackgroundColor);

    // Clear the old image.
    iGc->SetPenSize(TSize(3,3));
    iGc->SetPenColor(backgroundColour);
    iGc->DrawRect(TRect(iLastPoint, iSize));

    // Draw a shape at the new position
    iGc->SetPenSize(TSize(1,1));
    iGc->SetPenColor(KRgbBlack);
    iGc->DrawRect(TRect(iNewPoint, iSize));

    // signal that the current position has been drawn
    iDrawn = ETrue;
    }

// Not bothered if the focus has changed
void CImage::FocusChanged(TBool /* aState */)
    {
    }


// Animate the animation server object, in this case move the square around the screen
// includes bouncing the square off the edges of the screen, and checking to see if
// a user reset has been requested
void CImage::Animate(TDateTime* /* aDateTime */)
    {
    
    // if the last position has been drawn, update the position
    if (iDrawn)
        {
        // this position has not been drawn, so clear the flag
        iDrawn = EFalse;


        // Save the current position, so we can rub it out later
        iLastPoint = iNewPoint;

        // Check current position, reverse the direction if either limit is reached
        if ((iNewPoint.iX == iScreenSize.iTl.iX) ||  
           ((iNewPoint.iX + iSize.iWidth) == iScreenSize.iBr.iX))
            {
            iDeltaX = -iDeltaX;
            }

        // Setup the next X coordinate
        iNewPoint.iX += iDeltaX;

        // Repeat for y coordinate
        if ((iNewPoint.iY == iScreenSize.iTl.iY) ||  
           ((iNewPoint.iY + iSize.iHeight) == iScreenSize.iBr.iY))
            {
            iDeltaY = -iDeltaY;
            }
        iNewPoint.iY += iDeltaY;

        // Check for user requested animation
        if (iAnimationReset)
            {
            iNewPoint.iX = 1;
            iNewPoint.iY = 1;
            iDeltaX = KStepSize;
            iDeltaY = KStepSize;
            iAnimationReset = EFalse;        
            }


        // Alternative method, works well on the MARM target, jumps on the
        // windows emulator, simply uncomment and recompile
        //iFunctions->ActivateGc();
        //Redraw();

        // Force a draw to be performed by declaring the screen invalid
        iWindowFunctions->Invalidate(iScreenSize);
        }
    }

// This function should be used for nonbuffered commands,
// and/or actions that can fail or leave
// in this example it is not used
TInt CImage::CommandReplyL(TInt aOpcode, TAny* /* aArgs */)
    {
    return aOpcode;
    }

// This function should be used for buffered commands
// and commands that cannot fail/leave
// the optional parameters aArgs is not used in this example
void CImage::Command(TInt aOpcode, TAny* /* aArgs */)
    {
    switch (aOpcode)
        {
    case KAnimationReset:
        // Set a flag to reset the animation back to the top left
        iAnimationReset = ETrue;
        break;

    default:
        User::Panic(KAnimation, EPanicAnimationServer);
        break;
        }
    }

// Timer control, called everytime the time times out
void CImage::TimedOut()
    {
    // Reset the timer timeout period
    iServerTimer->After(KTimerPeriod);

    // Call the animation function for this image
    iFunctions->Animate(0);
    }

CImage::CImage() 
    {
    }

// Destructor
CImage::~CImage() 
    {
    // If the CTimer derived object exists and has an outstanding request, cancel it.
    if (iServerTimer)
        {
        iServerTimer->Cancel();
        }

    // Then delete the timer object
    delete iServerTimer;
    iServerTimer = NULL;
    }

TBool CImage::OfferRawEvent(const TRawEvent &/*aRawEvent*/)
    {
    return ETrue;
    }
