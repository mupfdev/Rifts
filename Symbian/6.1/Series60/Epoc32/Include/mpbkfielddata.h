/*
* ============================================================================
*  Name     : MPbkFieldData.h
*  Part of  : PbkEng.dll
*
*  Description:
*       Interface classes for accessing Phonebook contact data.
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

#ifndef __MPbkFieldData_H__
#define __MPbkFieldData_H__

//  INCLUDES
#include <cntdef.h>         // TStorageType
#include "PbkFields.hrh"    // TPbkFieldId

// CLASS DECLARATION

/**
 * Phonebook field data abstract interface.
 */
class MPbkFieldData
    {
    public:  // Destructor
        /**
         * Destructor.
         */
        virtual ~MPbkFieldData() {}

    public:  // Interface
        /**
         * Returns the type of this field data.
         * @return KStrorageTypeText or KStoragetTypeDateTime.
         */
        virtual TStorageType PbkFieldType() const = 0;

        /**
         * Returns the field id of this field data.
         */
        virtual TPbkFieldId PbkFieldId() const = 0;

        /**
         * Returns the text value of this field data.
         * @precond PbkFieldType()==KStrorageTypeText.
         */
        virtual TPtrC PbkFieldText() const = 0;

        /**
         * Returns the Time value of this field data.
         * @precond PbkFieldType()==KStoragetTypeDateTime.
         */
        virtual TTime PbkFieldTime() const = 0;

    public:  // Operations
        /**
         * Makes a presentation text for this field.
         *
         * @param aText         descriptor where the text is formatted.
         * @param aTimeFormat   format string to pass to TTime::FormatL when 
         *                      formatting a date/time field.
         * @exception KErrOverflow if aText is to small for the formatted text.
         * @exception KErrNoMemory if out of memory.
         * @exception KErrGeneral if a formatting error occurs.
         */
        IMPORT_C void PbkFieldDisplayTextL(TDes& aText, const TDesC& aTimeFormat) const;
    };


/**
 * Array of MPbkFieldData objects.
 */
class MPbkFieldDataArray
    {
    public:  // Destructor
        virtual ~MPbkFieldDataArray() {}

    public:  // Abstract interface
        /**
         * Returns the number of field data objects in this array.
         */
        virtual TInt PbkFieldCount() const = 0;

        /**
         * Returns the field data object at aIndex.
         */
        virtual MPbkFieldData& PbkFieldAt(TInt aIndex) = 0;

        /**
         * Returns the const field data object at aIndex.
         */
        virtual const MPbkFieldData& PbkFieldAt(TInt aIndex) const = 0;
    };


#endif // __MPbkFieldData_H__

// End of File
