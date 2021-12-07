/*
* =============================================================================
*  Name     : CAknExQueryContainer
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXQUERYCONTAINER_H
#define AKNEXQUERYCONTAINER_H

// INCLUDES
#include <coecntrl.h>
#include <coecobs.h>
#include <AknGlobalListQuery.h>
#include <AknQueryDialog.h>
#include <aknglobalmsgquery.h>     // for global message query
#include <AknPopup.h>
#include "AknExQueryGlobalListObserver.h"


// FORWARD DECLARATIONS
class CEikLabel;
class CEikColumnListBox;
class CAknExQueryView;
class CAknExQueryBaseListEventHandler;


// CONSTANTS
const TInt KAknExQueryInitialId = 0;
const TInt KAknExQueryTextBufLength = 128;

// CLASS DECLARATION

/**
* CAknExQueryContainer  container control class.
*/
class CAknExQueryContainer : public CCoeControl
    {
    public:
        //Type of actions to be performed at timer expiry
        enum TTimerUpdateType {
	        ENoUpdate          = 0, //default
	        EUpdateGlobalQuery,
            ECancelGlobalQuery,
            ECancelListQuery,
            ECancelPopupList,
            EUpdateGlobalListQueryUp,
            EUpdateGlobalListQueryDown,
            EUpdateGlobalListQuerySelect,
            ECancelQueryAnim,
            ENoTimer
	        };

    private: // Enumerations

        enum TAknExQueryComponentControls
            {
            EAknExQueryComponentLabel, //0
            EAknExQueryComponentLabel2, //1 
            EAknExQueryComponentListBox //2
            };

    public: // Constructors and destructor

        /**
        * Constructor.
        * @param aView Pointer to View class object.
        */
        CAknExQueryContainer( CAknExQueryView* aView );

        /**
        * EPOC default constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL( const TRect& aRect );

        /**
        * Destructor.
        */
        virtual ~CAknExQueryContainer();

    public: // New functions

        /**
        * Shows confirmation query.
        * @param aResourceId for dialog.
        * @param aTextResourceId for prompt.
        * @param aToneFlaga is flag for adding tone to argument of constructor.
        * @param aPromptFlag is flag for displaying prompt dynamically.
        */
        void ShowConfirmationQueryL(
            const TInt aResourceId,
            const TInt aTextResourceId = 0,
            const TBool aPromptFlag = EFalse,
            const TBool aToneFlag = EFalse,
            const TBool aHeaderTextAndImageFlag = EFalse,
			const CAknQueryDialog::TTone aTone = CAknQueryDialog::ENoTone);
 

        /**
        * Shows data query.
        * @param aResourceId for dialog.
        * @param aTextResourceId for inial value.
        * @param aPromptResourceId for ptompt
        * @param aMaxLength sets up the length of the character.
        */
        void ShowDataQueryL(
            const TInt aQueryResourceId,
            const TInt aTextResourceId = 0,
            const TInt aPromptResoureId = 0,
            const TInt aMaxLength = 0,
            const TInt aDisplayFlag = ETrue);


        /**
        * Shows time query.
        * @param aResourceQueryId for dialog
        * @param aResourceValued for inial value
        * @param aResourcePromptId for prompt
        */
        void ShowTimeQueryL(
            TInt aResourceQueryId, 
            TInt aResourceValueId, 
            TInt aResourcePromptId = 0);

        /**
        * Shows duration layout.
        * 
        */
        void ShowDurationLayoutL();

        /**
        * Shows number layout.
        */
        void ShowNumberLayoutL(const TInt aResourceId, 
                               const TInt aPromptResouceId = 0,
                               const TInt aQueryValue = 0, 
                               TInt aMinimumValue = 0, 
                               TInt aMaximumValue = 0);

        /**
        * Show popup menu layout.
        * @param aTitle.
        */
        void ShowPopupSubMenuLayoutL( TBool aTitle );

        /**
        * Show list query.
        * @param aResourceId.
        */
        void ShowListQueryL( const TInt aResourceId );

 
        /**
        * Create handler.
        * @param aCommand.
        */
        void PopoutListBoxL( TInt aCommand );

        /**
        * Creates listbox object.
        * @param aCommand.
        */
        TBool CreateListBoxL( TInt aCommand );

        /**
        * Deletes listbox object.
        */
        void DeleteListBoxL();

        /**
        * Creates label object.
        * @param aResourceId.
        */
        void CreateLabelL( TInt aResourceId );

        /**
        * Deletes label object.
        */
        void DeleteLabelL();

        /**
        * Set Label text.
        * @param aResourceId.
        */
        void SetTextToLabelL( TInt aResourceId );


        /**
        * Show Message Text. 
        * @param aMessage
        */
        void ShowMessageL(const TDesC& aMessage);

        /*
        * Show Message Query
        */
        void ShowMessageQueryL();

        /*
        * Show Global Message Query
        */
        void ShowGlobalMessageQueryL( 
            const TTimerUpdateType& aUpdateType = ENoUpdate);

        /*
        * Show Query with Heading text
        * @param aResouceId
        */
        void ShowQueryWithHeadingLineL( TInt aResouceId, TInt aTextId = 0);

        /**
        * Show multi line text and text layout.
        * @param aResouceId
        * @param aTopResourceId
        * @param aBottomResourceId
        * @param aSetPromptaFlag
        * @param aLengthOfFirstEditor
        * @param aLengthOfSecondEditor
        */
        void ShowMultiLineTextAndTextLayoutL(
                const TInt aResouceId ,
                const TInt aTopResourceId = 0,
                const TInt aBottomResourceId = 0,
                const TBool aSetPromptFlag = EFalse,
                const TInt aLengthOfFirstEditor = 0,
                const TInt aLengthOfSecondEditor = 0);
     
        /*
        * Show multi line text and number layout.
        * @param aResourceId
        */
        void ShowMultiLineTextAndNumberLayoutL( const TInt aResourceId);

        /*
        * Show multi line text and duration layout.
        * @param aResourceId
        */
        void ShowMultiLineTextAndLDurationLayoutL(const TInt aResourceId);

        /*
        * Show multi line time and time layout.
        * @param aResourceId for dialog
        * @param aTopResourceId for top of multi line 
        * @param aBottomResourceId for bottom of multi line
        */
        void ShowMultiLineTimeAndTimeLayoutL(
            const TInt aResourceId,
            const TInt aTopResourceId,
            const TInt aBottomResourceId);

        /*
        * Show multi line number and number layout.
        */
        void ShowMultiLineNumberAndNumberLayoutL();

        /*
        * Show multi line text and time layout.
        * @param aResourceId for dialog
        * @param aBottomResourceId for bottom of multi line
        */
        void ShowMultiLineTextAndTimeLayoutL(
            const TInt aResourceId,
            const TInt aBottomResourceId = 0);

        /*
        * show multi line time and duration layout.
        * @param aResourceId for dialog
        * @param aTopResourceId for top of multi line.
        */
        void ShowMultiLineTimeAndDurationLayoutL(
            const TInt aResourceId, 
            const TInt aTopResourceId);

        /*
        * Call CAknQueryDialog::RunDlgLD and it tests.
        *  @param aResourceId for dialog
        */
        void DoRunDlgL(TInt aResourceId);


        /*
        * Call CAknListQueryDialog::SetItemTextArrayL and it tests.
        */
        void DoSetItemTextArrayL();


        /*
        * Call CAknListQueryDialog::SetIconArrayL and it tests.
        */
        void DoSetIconArrayL();


        /*
        * Dlete timer.
        */
        void DeleteTimer(); 


        /*
        * Show Code Query.
        */
        void ShowCodeQueryL(const TInt aLength = 0, TDesC* aDefaulText = NULL);

        /*
        * Cancel PopUp
        */
        void DoCancelPopUp();

        /*
		* The function for the test of the following three APIs.
        * MoveSelectionUp, MoveSelectionDown, SelectItem.
        */
        void ShowGlobalListQueryL(const TTimerUpdateType& aUpdateType);

        /*
        * Control can be acquired from 
		* ControlByLayoutOrNull about data layout, 
		* and  it tests.
        */
        void DataLayoutFromControlByLayoutOrNull();

        /*
        * Control can be acquired from 
		* ControlByLayoutOrNull about StaticSizeDat layout, 
		* and  it tests.
        */
        void StaticSizeDataLayoutFromControlByLayoutOrNull();

        /*
        * Control can be acquired from 
		* ControlByLayoutOrNull about Phone layout, 
		* and  it tests.
        */
        void PhoneLayoutFromControlByLayoutOrNull();

        /*
        * Control can be acquired from 
		* ControlByLayoutOrNull about Code layout, 
		* and  it tests.
        */
        void CodeLayoutFromControlByLayoutOrNull();

        /*
        * Control can be acquired from 
		* ControlByLayoutOrNull about Date layout, 
		* and  it tests.
        */
        void DateLayoutFromControlByLayoutOrNull();

        /*
        * Control can be acquired from 
		* ControlByLayoutOrNull about Time layout, 
		* and  it tests.
        */
        void TimeLayoutFromControlByLayoutOrNull();

        /*
        * Control can be acquired from 
		* ControlByLayoutOrNull about Duration layout, 
		* and  it tests.
        */
        void DurationLayoutFromControlByLayoutOrNull();

        /*
        * Control can be acquired from 
		* ControlByLayoutOrNull about Number layout, 
		* and  it tests.
        */
        void NumberLayoutFromControlByLayoutOrNull();

        /*
        * Control can be acquired from 
		* ControlByLayoutOrNull about Pin layout, 
		* and  it tests.
        */
        void PinLayoutFromControlByLayoutOrNull();

        /*
		* Call RemoveEditorIndicator and it tests.
        */
        void DoRemoveEditorIndicator();

        /**
        * set image of confirmation query
        */
        void SetImageL();

        /**
        * set animation of confirmation query
        */
        void SetAnimationL();

        /**
        * set and animation
        */
        void SetAndCancelAnimationL();

        /**
        * Change maximum height of pop-up list
        */
        void ChangeMaxHightL();

		/*
		* Show Delete Confirmation Query
		*/
		void ShowDeleteConfirmationQueryL();


    public: // From CCoeControl

        /**
        * From CCoeControl, OfferKeyEventL.
        * Handles the key events.
        * @return if key-event is consumed, EKeyWasConsumed.
        *   Else EKeyWasNotConsumed
        * @param aKeyEvent Key event
        * @param aType Type of key event (EEventKey, EEventKeyUp or
        *   EEventKeyDown)
        */
        TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,
                                    TEventCode aType );

    private: // From CCoeControl

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

    private: //New Function

        /*
        * Show Result Message.
        */
        void ShowResultMessageL( TBool aResult );

	    //Timer methods
	    static TInt TimerCallbackL( TAny* aThis );

        void ProcessTimerEventL();
        
        void StartTimerL(
            TInt aStart, 
            TInt aInterval, 
            const TTimerUpdateType& aUpdateType);

        void SetIconL(CAknQueryDialog* aDlg, 
            TInt32 aBitmap, TInt32 aMask);


    private: // Data
        CEikLabel*                          iLabel;
        CEikLabel*                          iLabelResultMessage;
        CAknExQueryView*                    iView;
        CEikColumnListBox*                  iListBox;
        CAknExQueryBaseListEventHandler*    iHandler;
        TBool                               iDisplayDialog;
        CAknGlobalListQuery*                iGlobalListQuery;
        CAknExQueryGlobalListObserver*      iGlobalListObserver;
        CAknGlobalMsgQuery*                 iGlobalMsgQuery;
        CAknQueryDialog*                    iQueryDialog;
        TTimerUpdateType                    iTimerUpdateType;
        CPeriodic*                          iTimer;
        CAknPopupList*                      iPopupList;
		TBuf<KAknExQueryTextBufLength>      iTextData;

    };

#endif

// End of File
