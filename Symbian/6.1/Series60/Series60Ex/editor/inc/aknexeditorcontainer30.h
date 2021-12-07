/*
* ============================================================================
*  Name     : CAknExEditorContainer30from CCoeControl, MCoeControlObserver
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXEDITORCONTAINER30_H
#define AKNEXEDITORCONTAINER30_H

// INCLUDES
#include <aknview.h>


// CONSTANTS

// FORWARD DECLARATIONS
class CEikLabel;        // for example labels
class CEikEdwin; 

// CLASS DECLARATION

/**
*  CAknExEditorContainer  container control class.
*  
*/
class CAknExEditorContainer30 : public CCoeControl, MCoeControlObserver
    {
    public: // Constructors and destructor
        /**
        * C++ default constructor.
        */
        CAknExEditorContainer30();

        /**
        * EPOC default constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL(const TRect& aRect);

        /**
        * Destructor.
        */
        virtual ~CAknExEditorContainer30();

    public: // New functions

        void TestSelectedCase(TInt aCommand); 


    private: // Functions from base classes

       /**
        * From CoeControl,SizeChanged.
        */
        void SizeChanged();

       /**
        * From CoeControl,CountComponentControls.
        */
        TInt CountComponentControls() const;

       /**
        * From CCoeControl,ComponentControl.
        * @param aIndex of control
        */
        CCoeControl* ComponentControl(TInt aIndex) const;

       /**
        * From CCoeControl, Draw client rect.
        * @param aRect Frame rectangle for container.
        */
        void Draw(const TRect& aRect) const;

       /**
        * From CCoeControl, Handles key event.
        * @param aKeyEvent The key event.
        * @param aType The type of the event.
        * @return Indicates whether or not the key event was
        *           used by this control.
        */
        TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,
                                    TEventCode aType);

        // private functions for API testing




    private:
       /**
        * From MCoeControlObserver, Handles an event of type aEventType
        * @param aControl Pointer to component control
        * @param aEventType Event Code
        */
        void HandleControlEventL(CCoeControl* /*aControl*/,
                                    TCoeEvent /*aEventType*/);


    private: //data
        
        CEikEdwin*    iEdwin1;
        CEikEdwin*    iEdwin2;
        CEikEdwin*    iEdwin3;

    };

#endif // AKNEXEDITORCONTAINER30_H

// End of File
