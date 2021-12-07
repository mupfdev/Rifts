/*
* ============================================================================
*  Name     : CAknExSliderContainer
*  Part of  : AknExSlider
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXSLIDERCONTAINER_H
#define AKNEXSLIDERCONTAINER_H

// INCLUDES
#include <coecntrl.h>

// CONSTANTS
const TInt KAknExSliderInitialValue = 0;
const TInt KAknExSliderMessageBufLength = 256;

// FORWARD DECLARATIONS
class CAknExSliderView;
class CAknSlider;
class CEikLabel;

// CLASS DECLARATION

/**
* CAknExSliderContainer container control class.
* @short This class controls displaying the user data or information.
* @author Kaoru Haga
* @version 1.00
*/
class CAknExSliderContainer : public CCoeControl, public MCoeControlObserver
    {
    private: // Enumerations

        enum TAknExSliderLabelState
            {
            EAknExSliderLabelTitle,
            EAknExSliderLabelInformation
            };

        enum TAknExSliderComponentControls
            {
            EAknExSliderComponentLabel,
            EAknExSliderComponentSlider
            };

        enum TAknExSliderChangeLabels
            {
            EAknExSliderChangeLabel1 = 1,
            EAknExSliderChangeLabel2,
            EAknExSliderChangeLabel3,
            EAknExSliderChangeLabel4
            };

        enum TAknExSliderChangeOfTextAppearanceScreen
            {
            EAknExSliderChangeText1 = 1,
            EAknExSliderChangeText2,
            EAknExSliderChangeText3,
            EAknExSliderChangeText4,
            EAknExSliderChangeText5
            };

    public: // Constructors and destructor

        /**
        * Default constructor.
        * @param aView 
        */
        CAknExSliderContainer(CAknExSliderView* aView);

        /**
        * EPOC constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL( const TRect& aRect );

        /**
        * Destructor.
        */
        virtual ~CAknExSliderContainer();

    public: // New functions

        /**
        * Handles the commands.
        * @param aCommand command to be handled
        */
        void HandleCommandL( TInt aCommand );

        /**
        * Sets ID of feature to displayed next.
        */
        void DisplayNextFeature();

    public: // From CCoeControl

        /**
        * From CoeControl,OfferKeyEventL.
        * Handles the key-events.
        * @return if key-event is consumed, EKeyWasConsumed. Else EKeyWasNotConsumed.
        * @param aKeyEvent Key event
        * @param aType Type of key event(EEventKey, EEventKeyUp or EEventKeyDown)
        */
        TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent,
            TEventCode aType );

    private: // New functions

        /**
        * If slider control displays slider object is deleted.
        */
        void StopDisplaySlider();

        /**
        * Sets font and alignment of label.
        * @param aLabel
        */
        void SetLabelState( TAknExSliderLabelState aLabel );

        /**
        * Displays the slider and label.
        */
        void DisplayFeatureL();

        /**
        * Creates slider object.
        * @param aResourceId The ID of resource (Slider structure)
        * @param aValue Inital current value of slider control
        */
        void DisplaySliderL(
            TInt aResourceId,
            TInt aValue = KAknExSliderInitialValue );

        /**
        * Creates and displays form object.
        * @param aResourceId The id of resource (Form struct)
        */
        void DisplayFormL( TInt aResourceId );

        /**
        * Displays the information.
        * @param aResourceId The id of resource (Text)
        */
        void DisplayInformationL( TInt aResourceId );

        /*
        * Displays the message.
        * @param aResourceId The id of resource (Text)
        *
        void DisplayMessage( TInt aResourceId );
        */

        /**
        * Sets string in the label.
        * @param aInformation Text which is displayed
        */
        void SetLabelL( TDesC& aInformation );

        /**
        * Makes the string which is displayed.
        * @return Text which is displayed
        * @param aTextBuf Reference to TDes class object.
        */
        TDesC* SetValueTextL( TDes& aTextBuf ) const;

        /**
        * Changes the display of the label.
        */
        void ChangeLabelL();

        /**
        * Changes the display of the value text in slider of each value type.
        */
        void ChangeScreenOfTextAppearance();

    private: // From CCoeControl

        /**
        * From CoeControl, CountComponentControls.
        * Returns number of components.
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
        * Clears the window's rectangle.
        * @param aRect Region of the control to be (re)drawn
        */
        void Draw( const TRect& aRect ) const;

    private: // From MCoeControlObserver
        /**
        * From MCoeControlObserver, HandleControlEventL.
        * Handles the event when state change.
        * @param aControl Pointer to control object
        * @param aEventType Event type
        */
        void HandleControlEventL(
            CCoeControl* aControl,
            TCoeEvent aEventType );

    private: //data

        CAknSlider* iSlider;
        CEikLabel* iLabel;
        TBuf<KAknExSliderMessageBufLength> iLabelFormat;
        TInt iCurrentFeature;
        TInt iCurrentLabel;
        TInt iCurrentStep;
        TInt iScreenStep;
        CAknExSliderView* iView;

    };

#endif

// End of File
