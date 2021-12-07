/*
* ============================================================================
*  Name     : CPbkContactIter.h
*  Part of  : PbkEng.dll
*
*  Description: 
*    Phonebook contact iterator
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

#ifndef __CPbkContactIter_H__
#define __CPbkContactIter_H__

//  INCLUDES
#include    <e32base.h>     // CBase
#include    <cntdb.h>       // TContactIter

// FORWARD DECLARATIONS
class CPbkContactEngine;
class CPbkContactItem;
class CContactItem;

// CLASS DECLARATION

/**
 * Phonebook contact iterator. Only iterates through recognised Phonebook
 * contact cards. NextL jumps over any other contacts.
 */
class CPbkContactIter : public CBase
	{
    public:  // Constructors and destructor
        /**
         * Creates a new instace of this class.
         *
         * @param aEngine   Phonebook engine whose contacts to iterate.
         * @param aUseMinimalRead   Use ReadMinimalContactL instead of 
         *                          ReadContactL to read the contacts.
         */
        IMPORT_C static CPbkContactIter* NewL
            (CPbkContactEngine& aEngine, TBool aUseMinimalRead=EFalse);

        /**
         * Same as NewL but leaves the created object on the cleanup stack.
         */
        IMPORT_C static CPbkContactIter* NewLC
            (CPbkContactEngine& aEngine, TBool aUseMinimalRead=EFalse);

	    /**
         * Destructor.
         */
        ~CPbkContactIter();

    public:  // interface
        /**
         * Intializes the iterator to the first Phonebook contact.
         * @return id of the first Phonebook contact, KNullContactId if none found.
         */
	    IMPORT_C TContactItemId FirstL();

        /**
         * Advances the iterator to the next Phonebook contact.
         * @return id of the next Phonebook contact, KNullContactId if none found.
         */
	    IMPORT_C TContactItemId NextL();

        /**
         * Resets the iterator to null state.
         */
	    IMPORT_C void Reset();

        /**
         * Returns the current Phonebook contact, NULL if none.
         */
        IMPORT_C CPbkContactItem* CurrentL() const;

        /**
         * Returns the current Phonebook contact, NULL if none.
         * Caller is responsible for deleting the contact.
         */
        IMPORT_C CPbkContactItem* GetCurrentL() const;

        __DECLARE_TEST;

    private:  // Implementation
	    CPbkContactIter(CPbkContactEngine& aEngine, TBool aUseMinimalRead);
        CContactItem* ReadPhonebookContactL(TContactItemId aId);

    private:  // Data
		/// Ref: phonebook engine
        CPbkContactEngine& iEngine;
		/// Own: contact iterator
        TContactIter iCmIter;
		/// Own: current item
        mutable CContactItem* iCurrentItem;
		/// Own: current pbk-item
        mutable CPbkContactItem* iCurrentPbkItem;
		/// Own: minimal read flag
        const TBool iUseMinimalRead;
	};


#endif // __CPbkContactIter_H__

// End of File
