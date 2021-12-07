/*
* ============================================================================
*  Name     : CAknExFormContainer
*  Part of  : AknExForm
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXFORMCONTAINER_H
#define AKNEXFORMCONTAINER_H

// INCLUDES
#include <coecntrl.h>

// FORWARD DECLARATIONS
class CAknExFormView;
class CEikLabel;

// CLASS DECLARATION

/**
* CAknExFormContainer container control class.
*/
class CAknExFormContainer : public CCoeControl
    {
    private: // Enumerations

        enum TAknExFormComponentControls
            {
            EAknExFormComponentLabel
            };

    public: // Constructors and destructor

        /**
        * Overload constructor.
        * @param aView Pointer to view class object.
        */
        CAknExFormContainer( CAknExFormView* aView );

        /**
        * EPOC constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL( const TRect& aRect );

        /**
        * Destructor.
        */
        virtual ~CAknExFormContainer();

    public: // New functions

        /**
        *
        * @param aResourceId
        */
        void SetTextToLabelL( TInt aResourceId );

        /**
        *
        * @param aResourceId
        */
        void DisplayFormL( TInt aResourceId );

    private: // New functions

        /**
        * Creates the label object.
        */
        void CreateLabelL();

    private: // From CCoeControl

        /**
        * From CCoeControl, OfferKeyEventL.
        * Handles the key events.
        * @return if key-event is consumed, EKeyWasConsumed. Else EKeyWasNotConsumed
        * @param aKeyEvent Key event
        * @param aType Type of key event (EEventKey, EEventKeyUp or EEventKeyDown)
        */
        TKeyResponse OfferKeyEventL(
            const TKeyEvent& aKeyEvent,
            TEventCode aType );

        /**
        * From CCoeControl, SizeChanged.
        *
        */
        void SizeChanged();

        /**
        * From CCoeControl, CountComponentControls.
        * Returns number of component.
        * @return Number of controls
        */
        TInt CountComponentControls() const;

        /**
        * From CCoeControl, ComponentControl.
        * Returns pointer to particular component.
        * @return Pointer to Control's component control, identified by index
        * @param aIndex Index of the control
        */
        CCoeControl* ComponentControl( TInt aIndex ) const;

        /**
        * From CCoeControl, Draw.
        *
        * @param aRect Region of the control to be (re)drawn.
        */
        void Draw( const TRect& aRect ) const;

    private: // Data

        CAknExFormView* iView;
        CEikLabel* iLabel;

    };

#endif
