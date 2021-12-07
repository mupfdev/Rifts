/*
* =============================================================================
*  Name     : CAknExListColumnContainer
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXLISTCOLUMNCONTAINER_H
#define AKNEXLISTCOLUMNCONTAINER_H

// INCLUDES
#include <eiklbo.h>
#include "AknExListBaseContainer.h"

// FORWARD DECLARATIONS
class CEikLabel;
class CEikColumnListBox;
class CAknSearchField;
class CAknExListColumnView;

// CLASS DECLARATION

/**
* CAknExListColumnContainer  container control class.
*/
class CAknExListColumnContainer :
    public CAknExListBaseContainer,
    public MEikListBoxObserver
    {
    private: // Enumerations

        enum TAknExListComponentControls
            {
            EAknExListDefaultComponent,
            EAknExListComponent1,
            EAknExListComponent2
            };

        enum TAknExListPriority
            {
            EKAknExListFirstPriority = 1,
            EKAknExListSecondPriority,
            EKAknExListThirdPriority
            };

        enum TAknExListIconIndex
            {
            EKAknExListFirstIconIndex = 1,
            EKAknExListSecondIconIndex,
            EKAknExListThirdIconIndex
            };

        enum TAknExListItemIndex
            {
            EKAknExListItemIndex0,
            EKAknExListItemIndex1
            };

    public: // Constructors and destructor

        /**
        * Copy constructor.
        * @param aView Pointer of CAknExListColumnView class.
        */
        CAknExListColumnContainer( CAknExListColumnView* aView );

        /**
        * EPOC constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL( const TRect& aRect );

        /**
        * Destructor.
        */
        virtual ~CAknExListColumnContainer();

    public: // New functions

        /**
        * Displays listbox or start screen.
        * @param aOutlineId The ID of outline to displayed next.
        */
        void DisplayListBoxL( const TInt aOutlineId );

        
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

    public: // From MEikListBoxObserver

        /**
        * Handles listbox event.
        * @param aListBox Pointer to ListBox object is not used.
        * @param aEventType Type of listbox event.
        */
        void HandleListBoxEventL(
            CEikListBox* aListBox,
            TListBoxEvent aEventType );

    private: // New functions
        /**
        * Creates and sets label control object.
        * @param aResourceId Resource ID of text.
        */
        void SetLabelL( const TInt aResourceId );

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

        /**
        * Confirms priority of additional icons.
        */
        void AdditionalIconPriorityL();

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

        CEikLabel* iLabel;
        CEikColumnListBox* iListBox;
        CAknExListColumnView* iView;
        CAknSearchField* iFindBox;
        TInt iOutlineId;

    };

#endif

// End of File
