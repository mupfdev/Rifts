/*
* ============================================================================
*  Name     : CAknExSpanePopUpWindow from CCoeControl
*  Part of  : AknExSpane
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXSPANEPOPUPWINDOW_H
#define AKNEXSPANEPOPUPWINDOW_H

//  INCLUDES
#include <aknview.h>

// CLASS DECLARATION
/**
*  Popup window class
*/    
class CAknExSpanePopUpWindow : public CCoeControl
    { 
    public:  // Constructors and destructor
        /**
        * C++ default constructor.
        */
        CAknExSpanePopUpWindow();

        /**
        * EPOC default constructor.
        */
        void ConstructL(const TRect& aRect);

        /**
        * Destructor.
        */
        virtual ~CAknExSpanePopUpWindow();

    public: // Functions from base classes
        /**
        * From CCoeControl, SetColoe
        * @param aColor, aColor is the color set to.
        */
        void SetColor(TRgb aColor);

    private: // Functions from base classes

        /**
        * From CCoeControl,Draw.
        * @param Specified area for drawing
        */
        void Draw(const TRect& aRect) const;
       
    private:  // Data
        RWindowGroup iMyWindowGroup;
        TRgb iColor;
    };

#endif // AKNEXSPANEPOPUPWINDOW_H

// End of File
