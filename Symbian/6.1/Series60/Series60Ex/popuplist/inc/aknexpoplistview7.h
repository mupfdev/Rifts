/*
* ============================================================================
*  Name     : CAknExPopListView7 from CAknView
*  Part of  : AknExPopList
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXPOPLISTVIEW7_H
#define AKNEXPOPLISTVIEW7_H

// INCLUDES
#include <aknview.h>


// CONSTANTS
// UID of view
const TUid KView7Id = {7};

// FORWARD DECLARATIONS
class CAknExPopListContainer;
class CAknPopupList;

// CLASS DECLARATION

/**
*  CAknExPopListView7 view class.
* 
*/
class CAknExPopListView7 : public CAknView
    {
    public: // Constructors and destructor

        /**
        * EPOC default constructor.
        */
        void ConstructL();

        /**
        * Destructor.
        */
        virtual ~CAknExPopListView7();

    public: // Functions from base classes
        
        /**
        * From CAknView, returns View Id.
        * @return view Id.
        */
        TUid Id() const;

        /**
        * From CAknView, handles commands.
        * @param aCommand Command to be handled.
        */
        void HandleCommandL(TInt aCommand);

        /**
        * From CAknView, handles client rectangle is changed.
        */
        void HandleClientRectChange();

    private:

        /**
        * From AknView, Creates the container class object.
        * @param aPrevViewId Previeous view id.
        * @param aCustomMessageId messge id.
        * @param aCustomMessage message.
        */
        void DoActivateL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,
            const TDesC8& aCustomMessage);

        /**
        * From AknView, Deletes the container class object.
        */
        void DoDeactivate();

    private: // New funcitons

    private: // Data
        CAknExPopListContainer* iContainer;
    };

#endif  // AKNEXPOPLISTVIEW7_H

// End of File
