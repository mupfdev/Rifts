/*
* ============================================================================
*  Name     : CAknExEditorContainer1 from CCoeControl, MCoeControlObserver
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXEDITORCONTAINER1_H
#define AKNEXEDITORCONTAINER1_H

// INCLUDES
#include <aknview.h>
   
// FORWARD DECLARATIONS
class CEikLabel;
class CEikEdwin;
class CEikGlobalTextEditor;

// CLASS DECLARATION

/**
*  CAknExEditorContainer  container control class.
*  
*/
class CAknExEditorContainer1 : public CCoeControl, MCoeControlObserver
    {
    public: // Constructors and destructor
        /**
        * C++ default constructor.
        */
        CAknExEditorContainer1();

        /**
        * EPOC default constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL(const TRect& aRect);

        /**
        * Destructor.
        */
        virtual ~CAknExEditorContainer1();

    public: // New functions
        /**
        * Change focussed control using specified command.
        * @param aCommand Command to be used.
        */
        void FocusTo(TInt aCommand);

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

    private:
       /**
        * From MCoeControlObserver, Handles an event of type aEventType
        * @param aControl Pointer to component control
        * @param aEventType Event Code
        */
        void HandleControlEventL(CCoeControl* /*aControl*/,
                                    TCoeEvent /*aEventType*/);
        
    private: //data
        
        CEikLabel*              iLabel1;
        CEikLabel*              iLabel2;
        CEikEdwin*              iEdwin;
        CEikGlobalTextEditor*   iGTextEd;
    };

#endif // AKNEXEDITORCONTAINER1_H

// End of File
