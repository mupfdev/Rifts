/*
* ============================================================================
*  Name     : MPbkFetchCallback from MPbkFetchCallbacks.h
*  Part of  : PbkView.dll
*
*  Description:
*     Fetch dialog MPbkFetchKeyCallback for Phonebook.
*  Version:
*
*  Copyright (C) 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

#ifndef __MPbkFetchCallbacks_H__
#define __MPbkFetchCallbacks_H__

//  INCLUDES
#include <e32def.h>
#include <cntdef.h> // TContactItemId
#include <w32std.h> // TKeyEvent, TEventCode

//  FORWARD DECLARATIONS
class CContactIdArray;

// CLASS DECLARATION

/**
 * Phonebook fetch dialog key event callback. 
 */
class MPbkFetchKeyCallback
    {
    public:
        /// Callback result code
        enum TResult
            {
            /// Ignores the key event and lets the fetch dialog process it
            EKeyWasNotConsumed,
            /// Hides the key event from the fetch dialog
            EKeyWasConsumed,
            /// Close the fetch dialog like it was accepted
            EAccept,
            /// Close the fetch dialog like it was canceled
            ECancel
            };

        /**
         * Callback function for key presses in fetch.
         * @param   @see CCoeControl::OfferKeyEventL
         * @return  Callback result.
         */
        virtual TResult PbkFetchKeyCallbackL
            (const TKeyEvent& aKeyEvent, TEventCode aType)=0;

    protected:
        /**
         * Protected destructor. Derived class instances are not
         * destroyed through this interface.
         */
        virtual ~MPbkFetchKeyCallback() { }
    };


/**
 * Accept callback interface for fetch dialogs.
 */
class MPbkFetchDlgAccept
    {
    public:
        /**
         * Result code whether fetch should be accepted, rejected or canceled.
         */
        enum TPbkFetchAccepted
            {
            /// Fetch result is accepted and the fetch dialog is closed
            KFetchYes = 0,
            /// Fetch result is rejected and the fetch dialog remains open
            KFetchNo,
            /// Fetch result is rejected and the fetch dialog is canceled
            KFetchCanceled
            };

        /**
         * Called by a fetch dialog when user makes a selection.
         *
         * @param aId  Focused contact item
         * @param aMarkedEntries  Selected contact items array
         * @return @see TPbkFetchAccepted
         * @see TPbkFetchAccepted
         */
        virtual TPbkFetchAccepted PbkFetchAcceptedL
            (TContactItemId aId, CContactIdArray* aMarkedEntries) = 0;

    protected:
        /**
         * Protected destructor. Derived class instances are not destroyed 
         * through this interface.
         */
        virtual ~MPbkFetchDlgAccept() { }
    };

#endif // __MPbkFetchCallbacks_H__

// End of File
