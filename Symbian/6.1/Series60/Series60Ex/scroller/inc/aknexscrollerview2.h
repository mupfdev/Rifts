/*
* ============================================================================
*  Name     : CAknExScrollerView2 from CAknView
*  Part of  : AknExScroller
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXSCROLLERVIEW2_H
#define AKNEXSCROLLERVIEW2_H

// INCLUDES
#include <aknview.h>


// CONSTANTS
// UID of view
const TUid KView2Id = {2};

// FORWARD DECLARATIONS
class CAknExScrollerContainer2;

// CLASS DECLARATION

/**
*  CAknExScrollerView2 view class.
* 
*/
class CAknExScrollerView2 : public CAknView
    {
    public: // Constructors and destructor
        /**
        * C++ default constructor.
        */
        CAknExScrollerView2();

        /**
        * EPOC default constructor.
        */
        void ConstructL();

        /**
        * Destructor.
        */
        virtual ~CAknExScrollerView2();


    public: // From CAknView
        /**
        * From CAknView, Id.
        * Returns the ID of view.
        * @return The ID of view.
        */
        TUid Id() const;

        /**
        * From CAknView, HandleCommandL.
        * handles the commands.
        * @param aCommand Command to be handled.
        */
        void HandleCommandL( TInt aCommand );


    private:
        /**
        * From CAknView, DoActivateL.
        * Creates the Container class object.
        * @param aPrevViewId aPrevViewId is not used.
        * @param aCustomMessageId aCustomMessageId is not used.
        * @param aCustomMessage aCustomMessage is not used.
        */
        void DoActivateL( const TVwsViewId& aPrevViewId,
                          TUid aCustomMessageId,
                          const TDesC8& aCustomMessage );

        /**
        * From CAknView, DoDeactivate.
        * Deletes the Container class object.
        */
        void DoDeactivate();


    private: // Data
        CAknExScrollerContainer2* iContainer;
    };

#endif  // AKNEXSCROLLERVIEW2_H

// End of File
