/*
* ============================================================================
*  Name     : CAknExMenuSubView from CAknView
*  Part of  : AknExMenu
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXMNEUSUBVIEW_H
#define AKNEXMNEUSUBVIEW_H

// INCLUDES
#include <aknview.h>


// CONSTANTS
// UID of view
const TUid KSubViewId = {2};
const TInt KLengthOfMsgStringInSubView = 64;
const TInt KMsgDisplayTimeInSubView = 1000000;

// FORWARD DECLARATIONS
class CAknExMenuSubContainer;

// CLASS DECLARATION

/**
*  CAknExMenuSubView view class.
* 
*/
class CAknExMenuSubView : public CAknView
    {
    public:
        enum TState
            {
            EAknExMenuStateMoreItems,
            EAknExMenuStateLessItems,
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
        virtual ~CAknExMenuSubView();

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
        * From AknView, deactivate an AknView.
        */
        void DoDeactivate();

    public:
        TBuf<KLengthOfMsgStringInSubView>            iUpperMsg;
        TBuf<KLengthOfMsgStringInSubView>            iLowerMsg;
        TBuf<KLengthOfMsgStringInSubView>            iTitleMsg;

    private: // Data
        CAknExMenuSubContainer*  iContainer;
        TState                   iState;
    };

#endif    // AKNEXMNEUSUBVIEW_H

// End of File
