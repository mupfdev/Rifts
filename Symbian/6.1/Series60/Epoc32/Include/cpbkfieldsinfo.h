/*
* ============================================================================
*  Name     : CPbkFieldsInfo.h
*  Part of  : PbkEng.dll
*
*  Description:
*     Phonebook field types collection class
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


#ifndef __CPbkFieldsInfo_H__
#define __CPbkFieldsInfo_H__

//  INCLUDES
#include <e32base.h>
// This include is not absolutely needed,  but this class is very rarely used 
// without class CPbkFieldInfo.
#include "CPbkFieldInfo.h"

//  FORWARD DECLARATIONS
class CContactItem;
class CContactItemField;
class CContactItemViewDef;
class RResourceFile;
class CPbkUidMap;
class CPbkFieldInfo;
class CPbkFieldInfoGroup;
class MPbkVcardProperty;
class TPbkMatchPriorityLevel;


//  CLASS DECLARATION 

/**
 * Phonebook field types collection class.
 */
class CPbkFieldsInfo : 
        public CBase
	{
	public: // interface
        /**
         * Creates and returns an instance of this class intialised from 
         * resources.
         * 
         * @param aPbkResFile       Phonebook's resource file.
         * @param aCntModelResFile  Contact Model's resource file.
         */
        static CPbkFieldsInfo* NewL
            (RResourceFile& aPbkResFile, RResourceFile& aCntModelResFile);

        /**
         * Destructor.
         */
        ~CPbkFieldsInfo();

        /**
         * Search field info by Phonebook field id.
         *
         * @param aFieldId  Phonebook field id to search from the array
         * @return  the <it>first</it> (there may be several that match) field 
         *          info object in field UI presentation order matching 
         *          aFieldId. Returns NULL if no match found.
         */
        IMPORT_C CPbkFieldInfo* Find(TPbkFieldId aFieldId) const;

        /**
         * Search field info by Phonebook field id and location
         *
         * @param aFieldId   Phonebook field id to search from the array
         * @param aLocation  Field location (home/work/none) to search from the array
         * @return  the field info object (there should be only one) matching 
         *          aFieldId and aLocation. NULL if no match found.
         */
        IMPORT_C CPbkFieldInfo* Find
			(TPbkFieldId aFieldId, TPbkFieldLocation aLocation) const;

        /**
         * Search a field info matching contact model field.
         *
         * @param aContactItemField Contact item field whose match is searched
         *                          from all field info objects.
         * @return  the field info object matching aContactItemField. NULL if 
         *          no match is found.
         */
        IMPORT_C CPbkFieldInfo* Find
			(const CContactItemField& aContactItemField) const;

        /**
         * @internal Only Phonebook internal use is supported!
         * Creates and returns an initialized matching priority level object.
         */
        IMPORT_C TPbkMatchPriorityLevel CreateMatchPriority() const;

        /**
         * @internal Only Phonebook internal use is supported!
         * Searches a match for a contact model field.
         *
         * @param aContactItemField Contact item field whose match is searched
         *                          from all field info objects.
         * @param aMatchPriority    priority to match against. Only import
         *                          types of this priority are checked.
         * @return  a match information object.
         */
        CPbkFieldInfo* Match
            (const CContactItemField& aContactItemField,
            const TPbkMatchPriorityLevel& aMatchPriority) const;

        /**
         * @internal Only Phonebook internal use is supported!
         * Searches a match for a vCard property.
         *
         * @param aVcardProperty    vCard property to search for a match from 
         *                          all field info objects.
         * @param aMatchPriority    priority to match against. Only import
         *                          types of this priority are checked.
         * @return  a match information object.
         */
        IMPORT_C CPbkFieldInfo* Match
            (const MPbkVcardProperty& aVcardProperty,
            const TPbkMatchPriorityLevel& aMatchPriority) const;

        /**
         * @deprecated Rather use CPbkContactItem::FindField() -functions.
         *
         * Returns the first field from contact item matching a Phonebook 
         * field id.
         *
         * @param   aCi       the contact item where the field is searched.
         * @param   aFieldId  the searched field's id.
         * @return  the matching contact item field from aCi. NULL if not found.
         */
        IMPORT_C CContactItemField* FindField(const CContactItem& aCi,
			TPbkFieldId aFieldId) const;
        
        /**
         * Returns the count of field infos.
         */
        IMPORT_C TInt Count() const;

        /**
         * Returns the aIndex:th field info. Field info objects are sorted by
         * the field presentation ordering.
         */
        IMPORT_C CPbkFieldInfo* operator[](TInt aIndex) const;

        /**
         * Returns the count of field info groups.
         */
        IMPORT_C TInt GroupCount() const;

        /**
         * Returns the field info group at aIndex.
         */
        IMPORT_C const CPbkFieldInfoGroup& GroupAt(TInt aIndex) const;

        /**
         * Creates a contact item view definition from an array of Phonebook 
         * field ids.
         *
         * @param aFieldTypes   array of Phonebook field types.
         * @return a new contact item view definition.
         */
        IMPORT_C CContactItemViewDef* CreateContactItemViewDefLC
            (const CPbkFieldIdArray& aFieldTypes) const;

        /**
         * Creates contact item field definition from an array of Phonebook 
         * field ids.
         *
         * @param aFieldTypes   Phonebook field types to add into the returned
         *                      array. If NULL an array matching all fields is
         *                      returned.
         * @return  a field def array matching <it>at least fields</it> in 
         *          aFieldTypes. Please note that the returned field definition
         *          may also match other fields than those specified.
         */
        IMPORT_C CContactItemFieldDef* CreateContactItemFieldDefLC
            (const CPbkFieldIdArray* aFieldTypes) const;

    private:  // Implementation
        CPbkFieldsInfo();
        CPbkFieldInfoGroup* FindGroup(TPbkFieldGroupId aGroupId);
        void LinkGroupsL();
        void ReadGroupsInfoL(RResourceFile& aResFile);
        void ConstructFromResourceL
            (RResourceFile& aPbkResFile, RResourceFile& aCntModelResFile);

    private: // data
        /// Own: array of field infos
        RPointerArray<CPbkFieldInfo> iEntries;
        /// Own: field info groups
        RPointerArray<CPbkFieldInfoGroup> iGroups;
        /// Own: UID map for field content type matching
        CPbkUidMap* iTypeUidMap;
        /// Own: highest field matching priority level
        TInt iHighestMatchPriorityLevel;
    };

#endif // __CPbkFieldsInfo_H__

// End of File
