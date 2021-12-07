/*
* ============================================================================
*  Name     : CAknExMenuOkView from CAknView
*  Part of  : AknExMenu
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXMNEUOKVIEW_H
#define AKNEXMNEUOKVIEW_H

// INCLUDES
#include <aknview.h>


// CONSTANTS
// UID of view
const TUid KOkViewId = {3};
const TInt KLengthOfMsgStringInOkView = 64;

// FORWARD DECLARATIONS
class CAknExMenuOkContainer;

// CLASS DECLARATION

/**
*  CAknExMenuOkView view class.
* 
*/
class CAknExMenuOkView : public CAknView
    {
    public: // Constructors and destructor

        /**
        * EPOC default constructor.
        * @param aResId Resource ID used to create the view
        */
        void ConstructL(TInt aResId);

        /**
        * Destructor.
        */
        virtual ~CAknExMenuOkView();

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
        TBuf<KLengthOfMsgStringInOkView>            iUpperMsg;
        TBuf<KLengthOfMsgStringInOkView>            iLowerMsg;
        TBuf<KLengthOfMsgStringInOkView>            iTitleMsg;

    private: // Data
        CAknExMenuOkContainer*  iContainer;
    };

#endif    // AKNEXMNEUOKVIEW_H

// End of File
