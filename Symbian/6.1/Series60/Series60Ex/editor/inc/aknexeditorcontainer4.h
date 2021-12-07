/*
* ============================================================================
*  Name     : CAknExEditorContainer4 from CCoeControl, MCoeControlObserver
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXEDITORCONTAINER4_H
#define AKNEXEDITORCONTAINER4_H

// INCLUDES
#include <aknview.h>
   
// FORWARD DECLARATIONS
class CEikLabel;        // for example labels
class CEikEdwin;
class CEikGlobalTextEditor;

// CLASS DECLARATION

/**
*  CAknExEditorContainer  container control class.
*  
*/
class CAknExEditorContainer4 : public CCoeControl, MCoeControlObserver
    {
    public: // Constructors and destructor
        /**
        * C++ default constructor.
        */
        CAknExEditorContainer4();

        /**
        * EPOC default constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL(const TRect& aRect);

        /**
        * Destructor.
        */
        virtual ~CAknExEditorContainer4();

    public: // New functions

        /**
        * Change font style using system font
        * @param aFontEnum Enumeration for system font in avkon.hrh
        */
        void SetSystemFontL(TInt aFontEnum);

        /**
        * Change font style.
        * @param aResourceID The ID of font resource to be set.
        */
        void SetFontL(TInt aResourceID);

    private:  // New Functions
        /**
        * Create FontSpec object from resource file.
        * @param aResourceID The ID of font resource.
        * @return Returns font pointer to TFontSpec object.
        */
        TFontSpec* CreateFontSpecFromResourceL(TInt aResourceID);

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
        CEikLabel*                  iLabel;
        CEikGlobalTextEditor*       iGTextEd;
    };

#endif // AKNEXEDITORCONTAINER4_H

// End of File
