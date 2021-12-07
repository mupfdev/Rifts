/*
* =============================================================================
*  Name     : CAknExListFormContainer
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXLISTFORMCONTAINER_H
#define AKNEXLISTFORMCONTAINER_H

// INCLUDES
#include "AknExListBaseContainer.h"

// FORWARD DECLARATIONS
class CEikFormattedCellListBox;
class CAknSearchField;
class CAknExListFormView;

// CLASS DECLARATION

/**
* CAknExListFormContainer  container control class.
*/
class CAknExListFormContainer : public CAknExListBaseContainer
    {

    private: // Enumerations

        enum TAknExListComponentControls
            {
            EAknExListComponentListBox,
            EAknExListComponentFindBox
            };

    public: // Constructors and destructor

        /**
        * Copy constructor.
        * @param aView Pointer of CAknExListFormView class.
        */
        CAknExListFormContainer( CAknExListFormView* aView );

        /**
        * EPOC constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL( const TRect& aRect );

        /**
        * Destructor.
        */
        virtual ~CAknExListFormContainer();

    public: // New functions

        /**
        * Displays the listbox by outline ID.
        * @param aOutlineId The ID of outline to displayed next.
        */
        void DisplayListBoxL( const TInt aOutlineId );

    public: // Functions from base classes

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
        * Sets count of added list items and calls AddItemL().
        * @param aKeyEvent Key event.
        */
        void SetCountAndAddItemL( const TKeyEvent& aKeyEvent );

        /**
        * Sets count of removed list items and calls RemoveItemL().
        * @param aKeyEvent Key event.
        */
        void SetCountAndRemoveItemL( const TKeyEvent& aKeyEvent );

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
        * @return Number of controls.
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

        CEikFormattedCellListBox* iListBox;
        CAknExListFormView* iView;
        CAknSearchField* iFindBox;
        TInt iOutlineId;

    };

#endif

// End of File
