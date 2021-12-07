/*
* =============================================================================
*  Name     : CAknExListMarkContainer
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXLISTMARKCONTAINER_H
#define AKNEXLISTMARKCONTAINER_H

// INCLUDES
#include "AknExListBaseContainer.h"

// FORWARD DECLARATIONS
class CEikColumnListBox;
class CAknExListMarkView;
class CAknSearchField;

// CLASS DECLARATION

/**
* CAknExListMarkContainer  container control class.
*/
class CAknExListMarkContainer : public CAknExListBaseContainer
    {
    private: // Enumerations

        enum TAknExListComponentControls
            {
            EAknExListDefaultComponent,
            EAknExListFindBox    
            };

    public: // Constructors and destructor

        /**
        * Copy constructor.
        * @param aView Pointer of CAknExListMarkView class.
        */
        CAknExListMarkContainer( CAknExListMarkView* aView );

        /**
        * EPOC constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL( const TRect& aRect );

        /**
        * Destructor.
        */
        virtual ~CAknExListMarkContainer();

    public: // New functions

        /**
        * Displays listbox or start screen.
        * @param aOutlineId The ID of outline to displayed next.
        */
        void DisplayListBoxL( const TInt aOutlineId );

        /**
        * Returns pointer to listbox object.
        * @return Pointer to listbox object.
        */
        CEikListBox* ListBox();

    public: // From CoeControl

        /**
        * From CoeControl, OfferKeyEventL.
        * Handles the key-events.
        * @return If key-event is consumed, EKeyWasConsumed. Else
        * EKeyWasNotConsumed.
        * @param aKeyEvent Key event.
        * @param aType Type of key event(EEventKey, EEventKeyUp or
        * EEventKeyDown).
        */
        TKeyResponse OfferKeyEventL(
            const TKeyEvent& aKeyEvent,
            TEventCode aType );

    private: // New functions
        /**
        * Called by framework when the view size is changed for creating
        * listbox with findbox.
        */
        void SizeChangedForFindBox();

    private: // From CAknExListBaseContainer

        /**
        * Appends graphics data.
        * @param Pointer of icon using graphics for listbox.
        */
        void GraphicIconL( CArrayPtr<CGulIcon>* aIcons );

    private: // From CoeControl

        /**
        * From CoeControl, SizeChanged.
        * Called by framework when the view size is changed.
        */
        void SizeChanged();

        /**
        * From CoeControl, CountComponentControls.
        * Returns number of components.
        * @return Number of controls
        */
        TInt CountComponentControls() const;

        /**
        * From CCoeControl, ComponentControl.
        * Returns pointer to particular component.
        * @return Pointer to Control's component control, identified by index.
        * @param aIndex Index of the control.
        */
        CCoeControl* ComponentControl( TInt aIndex ) const;

    private: // Data

        CEikColumnListBox* iListBox;
        CAknExListMarkView* iView;
        CAknSearchField* iFindBox;
        TInt iOutlineId;

    };

#endif

// End of File
