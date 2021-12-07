/*
* ============================================================================
*  Name     : CAknExMenuView from CAknView
*  Part of  : AknExMenu
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXMNEUVIEW_H
#define AKNEXMNEUVIEW_H

// INCLUDES
#include <aknview.h>


// CONSTANTS
// UID of view
const TUid KViewId = {1};
const TInt KLengthOfMsgStringInView = 64;
const TInt KMsgDisplayTimeInView = 1000000;

// FORWARD DECLARATIONS
class CAknExMenuContainer;

// CLASS DECLARATION

/**
*  CAknExMenuView view class.
* 
*/
class CAknExMenuView : public CAknView
    {
    public:
        enum TState
            {
            EAknExMenuStateNo,
            EAknExMenuStateDim1,
            EAknExMenuStateDim2,
            EAknExMenuStateLast
            };

    public: // Constructors and destructor

        /**
        * EPOC default constructor.
        * @param aResId Resource ID used to create the view
        */
        void ConstructL(TInt aResId);

        /**
        * Destructor.
        */
        virtual ~CAknExMenuView();

    public: // Functions from base classes
        
        /**
        * From CAknView, return Uid.
        * @return Uid Uid value
        */
        TUid Id() const;

        /**
        * From CAknView, takes care of command handling.
        * @param aCommand Command
        */
        void HandleCommandL(TInt aCommand);

    private:
        /** 
        * From MEikMenuObserver
        * @param aResourceId Menu pane resource ID
        * @param aMenuPane Menu pane pointer
        */
        void DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane);

    private:

        /**
        * From CAknExView, activate an AknView.
        * @param aPrevViewId Specified TVwsViewId
        * @param aCustomMessageId Specified TUid
        * @param aCustomMessage Specified TDesC8
        */
        void DoActivateL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,
            const TDesC8& aCustomMessage);

        /**
        * From AknView, deactivate an AknView
        */
        void DoDeactivate();

    public:
        TBuf<KLengthOfMsgStringInView>            iUpperMsg;
        TBuf<KLengthOfMsgStringInView>            iLowerMsg;
        TBuf<KLengthOfMsgStringInView>            iTitleMsg;
    private: // Data
        CAknExMenuContainer* iContainer;
        TState               iState;
    };

#endif    // AKNEXMNEUVIEW_H

// End of File
