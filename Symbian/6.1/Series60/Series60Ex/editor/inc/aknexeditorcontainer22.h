/*
* ============================================================================
*  Name     : CAknExEditorContainer22 from CCoeControl, MCoeControlObserver
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXEDITORCONTAINER22_H
#define AKNEXEDITORCONTAINER22_H

// INCLUDES
#include <aknview.h>
   
// FORWARD DECLARATIONS
class CCoeControl;
class CEikLabel;
class CEikTimeEditor;
class CEikDateEditor;
class CEikTimeAndDateEditor;
class CEikDurationEditor;

// Constants
const TInt KBufLength = 64;

// CLASS DECLARATION

/**
*  CAknExEditorContainer  container control class.
*  
*/
class CAknExEditorContainer22 : public CCoeControl, MCoeControlObserver
    {
    public: // Constructors and destructor
        /**
        * C++ default constructor.
        */
        CAknExEditorContainer22();

        /**
        * EPOC default constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL(const TRect& aRect);

        /**
        * Destructor.
        */
        virtual ~CAknExEditorContainer22();

    public: // New functions
        /**
        * Change focussed control using specified command.
        * @param aCommand Command to be used.
        */
        void FocusTo(TInt aCommand);

        /**
        * Show form.
        */
        void ShowFormL();

        void PrepareForFocusLossL();

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

        void FocusChanged(TDrawNow aDrawNow);

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
        CEikLabel*              iLabel3;
        CEikLabel*              iLabel4;
        CEikTimeEditor*         iTimeEditor;
        CEikDateEditor*         iDateEditor;
        CEikTimeAndDateEditor*  iTimeAndDateEditor;
        CEikDurationEditor*     iDurationEditor;
        CCoeControl*            iFocusedControl;

    };

#endif // AKNEXEDITORCONTAINER22_H

// End of File
