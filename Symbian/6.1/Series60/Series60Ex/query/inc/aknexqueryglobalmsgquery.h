/*
* =============================================================================
*  Name     : CAknExQueryGlobalMsgQuery
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXQUERYGLOBALMSGQUERY_H
#define AKNEXQUERYGLOBALMSGQUERY_H

// INCLUDES
#include <AknGlobalMsgQuery.h>

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
*  CAknExQueryNumberSetMinAndMax class.
*/
class CAknExQueryGlobalMsgQuery : public CAknGlobalMsgQuery
    {
    public: // Constructors and destructor

        /**
        * Constructor.
        * @param .
        */
        CAknExQueryGlobalMsgQuery(/*TInt& aNumber ,
                                const TInt aMinimumValue = NULL, 
                                const TInt aMaximumValue = NULL,
                                const TTone aTone = ENoTone*/);

        /**
        * Destructor.
        */
        virtual ~CAknExQueryGlobalMsgQuery();

   // protected:
     //    void PreLayoutDynInitL();

    private: 
        CAknGlobalMsgQuery* iGlobalMsgQuery;
        /**
        * From AknQueryDialog, OfferKeyEventL.
        * Handles the key-events.
        * @return If key-event is consumed, EKeyWasConsumed. Else
        * EKeyWasNotConsumed.
        * @param aKeyEvent Key event.
        * @param aType Type of key event(EEventKey, EEventKeyUp or
        * EEventKeyDown).
        */
    /*    TKeyResponse OfferKeyEventL(
            const TKeyEvent& aKeyEvent,
            TEventCode aType );
    */};


#endif

// End of File