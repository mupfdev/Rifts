/*
* =============================================================================
*  Name     : CAknExListFlagTestContainer
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXLISTFLAGTESTCONTAINER_H
#define AKNEXLISTFLAGTESTCONTAINER_H

// INCLUDES
#include <eiklbo.h>
#include "AknExListBaseContainer.h"

// FORWARD DECLARATIONS
class CEikListBox;
class CAknExListFlagTestView;

// CLASS DECLARATION

/**
* CAknExListFlagTestContainer  container control class.
*/
class CAknExListFlagTestContainer :
    public CAknExListBaseContainer,
    public MEikListBoxObserver
    {
    private: // Enumerations

        enum TAknExListComponentControls
            {
            EAknExListDefaultComponent
            };

    public: // Constructors and destructor

        /**
        * Copy constructor.
        * @param aView Pointer of CAknExListFlagTestView class.
        */
        CAknExListFlagTestContainer( CAknExListFlagTestView* aView );

        /**
        * EPOC constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL( const TRect& aRect );

        /**
        * Destructor.
        */
        virtual ~CAknExListFlagTestContainer();

    public: // New functions

        /**
        * Displays listbox or start screen.
        * @param aTabId The ID of tab.
        */
        void DisplayListBoxL( const TInt aTabId );

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
        * Returns resource ID for CAknSingleStyleListBox.
        * @return Resource ID for CAknSingleStyleListBox
        */
        TInt ResourceIdSingle();

        /**
        * Returns resource ID for CAknSingleNumberStyleListBox.
        * @return Resource ID for CAknSingleNumberStyleListBox.
        */
        TInt ResourceIdSingleNumber();

        /**
        * Returns resource ID for CAknSingleHeadingStyleListBox.
        * @return Resource ID for CAknSingleHeadingStyleListBox.
        */
        TInt ResourceIdSingleHeading();

        /**
        * Returns resource ID for CAknSingleGraphicStyleListBox.
        * @return Resource ID for CAknSingleGraphicStyleListBox.
        */
        TInt ResourceIdSingleGraphic();

        /**
        * Returns resource ID for CAknSingleGraphicHeadingStyleListBox.
        * @return Resource ID for CAknSingleGraphicHeadingStyleListBox.
        */
        TInt ResourceIdSingleGraphicHeading();

        /**
        * Returns resource ID for CAknSingleNumberHeadingStyleListBox.
        * @return Resource ID for CAknSingleNumberHeadingStyleListBox.
        */
        TInt ResourceIdSingleNumberHeading();

        /**
        * Returns resource ID for CAknSingleLargeStyleListBox.
        * @return Resource ID for CAknSingleLargeStyleListBox.
        */
        TInt ResourceIdSingleLargeGraphic();

        /**
        * Returns resource ID for CAknDoubleStyleListBox as single big pane.
        * @return Resource ID for CAknDoubleStyleListBox as single big pane.
        */
        TInt ResourceIdBigSingle();

        /**
        * Returns resource ID for CAknDoubleNumberStyleListBox as single big
        * number pane.
        * @return Resource ID for CAknDoubleNumberStyleListBox as single big
        * number pane.
        */
        TInt ResourceIdBigSingleNumber();

        /**
        * Returns resource ID for CAknDoubleLargeStyleListBox as single big
        * large graphic pane.
        * @return Resource ID for CAknDoubleLargeStyleListBox as single big
        * large graphic pane.
        */
        TInt ResourceIdBigSingleLargeGraphic();

        /**
        * Returns resource ID for CAknDoubleStyleListBox.
        * @return Resource ID for CAknDoubleStyleListBox.
        */
        TInt ResourceIdDouble();

        /**
        * Returns resource ID for CAknDoubleNumberStyleListBox.
        * @return Resource ID for CAknDoubleNumberStyleListBox.
        */
        TInt ResourceIdDoubleNumber();

        /**
        * Returns resource ID for CAknDoubleLargeStyleListBox.
        * @return Resource ID for CAknDoubleLargeStyleListBox.
        */
        TInt ResourceIdDoubleLargeGraphic();

        /**
        * Returns resource ID for CAknSettingStyleListBox.
        * @return Resource ID for CAknSettingStyleListBox.
        */
        TInt ResourceIdSetting();

        /**
        * Returns resource ID for CAknSettingNumberStyleListBox.
        * @return Resource ID for CAknSettingNumberStyleListBox.
        */
        TInt ResourceIdSettingNumber();

        /**
        * Returns resource ID for CAknDoubleGraphicStyleListBox.
        * @return Resource ID for CAknDoubleGraphicStyleListBox.
        */
        TInt ResourceIdDoubleGraphic();

        /**
        * Sets flag for creating graphic.
        * @param aFlagsOfGraphic Flag of graphic whether to need creating or
        * not.
        */
        void IsNeedGarphic( TBool& aFlagsOfGraphic );

        /**
        * Returns flags of listbox to use ConstructL() of listbox.
        * @return Flags of listbox.
        */
        TInt ListFlags();

        /**
        * Returns list items as CDesCArray.
        * @param ID of current tab.
        * @return Pointer of list items as CDesCArray.
        */
        CDesCArray* ListItemsL( TInt aTabId );

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

        CEikListBox* iListBox;
        CAknExListFlagTestView* iView;
        TInt iOutlineId;
        TBool iInternalFlag;
        TBool iKeyEvent;

    };

#endif

// End of File
