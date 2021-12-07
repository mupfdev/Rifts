/*
* ============================================================================
*  Name     : CAknExSettingListContainer.h
*  Part of  : AknExSettingList
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXSETTINGLISTCONTAINER_H
#define AKNEXSETTINGLISTCONTAINER_H

// INCLUDES
#include <coecntrl.h>
#include <eiklbo.h>
#include <AknTextSettingPage.h>

// CONSTANTS
const TInt KAknExSettingListInitialMaxLength = 0;
// for text
const TInt KAknExSettingListTextBufLength = 256;

// FORWARD DECLARATIONS
class CEikLabel;
class CAknExSettingListView;

//class CDesCArrayFlat;
class CAknQueryValueTextArray;
class CAknQueryValueText;



// CLASS DECLARATION

/**
* CAknExSettingListContainer  container control class.
*/
class CAknExSettingListContainer : public CCoeControl
    {
    public: // Enumerations

        enum TAknExSettingListComponentControls
            {
            EAknExSettingListComponentLabel,
            };

    public: // Constructors and destructor

        /**
        * Copy constructor.
        * @param aView Pointer to View class object.
        */
        CAknExSettingListContainer( CAknExSettingListView* aView );

        /**
        * EPOC constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL( const TRect& aRect );

        /**
        * Destructor.
        */
        virtual ~CAknExSettingListContainer();

    public: // New functions

        /**
        * Sets ID of current outline.
        * @param aOutlineId ID of the outline to set.
        */
        void SetCurrentOutlineId( const TInt aOutlineId );

        /**
        * Displays label by ID of resource.
        * @param aResourceId ID of resource for text.
        */
        void DisplayLabelL( const TInt aResourceId );
        
    private: // From CCoeControl

        /**
        * From CCoeControl, OfferKeyEventL.
        * Handles the key events.
        * @return If key-event is consumed, EKeyWasConsumed.
        *  Else EKeyWasNotConsumed.
        * @param aKeyEvent Key event.
        * @param aType Type of key event(EEventKey, EEventKeyUp or
        *  EEventKeyDown).
        */
        TKeyResponse OfferKeyEventL(
            const TKeyEvent& aKeyEvent,
            TEventCode aType );

        /**
        * From CoeControl, SizeChanged.
        * Called by framework when the View size is changed.
        */
        void SizeChanged();

        /**
        * From CoeControl, CountComponentControls.
        * Returns number of component.
        * @return Number of controls.
        */
        TInt CountComponentControls() const;

        /**
        * From CCoeControl, ComponentControl.
        * Returns pointer to particular component.
        * @return Pointer to container's component control,
        *  identified by index.
        * @param aIndex Index of the control.
        */
        CCoeControl* ComponentControl( TInt aIndex ) const;

        /**
        * From CCoeControl, Draw.
        * Fills the window's rectangle.
        */
        void Draw( const TRect& aRect ) const;

    private: // Data

        CEikLabel* iLabel;
        CAknExSettingListView* iView;
        TInt iCurrentOutlineId;
        CDesCArrayFlat* iItems;
        CAknQueryValueTextArray* iTextArray;
        CAknQueryValueText* iQueryValueText;

    };

#endif

// End of File
