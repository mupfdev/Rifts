/*
* ============================================================================
*  Name     : CPbkContactItem from CPbkContactItem.h
*  Part of  : PbkEng.dll 
*
*  Description:
*     Phonebook Contact item class.
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

#ifndef __CPbkContactItem_H__
#define __CPbkContactItem_H__

//  INCLUDES
#include <e32base.h>        // CBase, CArrayFixFlat
#include "MPbkFieldData.h"  // MPbkFieldDataArray
#include "PbkFields.hrh"    // TPbkFieldId
#include "TPbkContactItemField.h"

// FORWARD DECLARATIONS
class CPbkFieldsInfo;
class CPbkFieldInfo;
class CContactItemField;
class CContactItem;
class MPbkContactNameFormat;


// CLASS DECLARATION

/**
 * Array of TPbkContactItemField instances.
 */
class CPbkFieldArray : public CArrayFixFlat<TPbkContactItemField>
    {
    public:
        enum
            {
            /// Default array reallocation granularity
            KDefaultGranularity = 8
            };

        /** 
         * Constructor.
         */
        inline CPbkFieldArray() 
            : CArrayFixFlat<TPbkContactItemField>(KDefaultGranularity)
            {
            }

        /**
         * Constructor.
         * @param aGranularity  reallocation granularity of this array.
         */
        inline CPbkFieldArray(TInt aGranurality) 
            : CArrayFixFlat<TPbkContactItemField>(aGranurality)
            {
            }
    };


/**
 * Phonebook Contact item class.
 * This class extends contact model class CContactItem capabilities to better 
 * suit Phonebook application's needs.
 */
class CPbkContactItem : 
        public CBase, public MPbkFieldDataArray
    {
    public:  // Constructor and destructor
        /**
         * Creates an instance of this class.
         *
         * @param aItem         Contact item this object wraps. This object 
         *                      takes ownership of aItem.
         * @param aFieldsInfo   collection of Phonebook field types.
         * @param aNameFormat   Contact name formatter.
         * @return  a new instance of this class.
         */
        IMPORT_C static CPbkContactItem* NewL(
                CContactItem* aItem, 
                const CPbkFieldsInfo& aFieldsInfo, 
                MPbkContactNameFormat& aNameFormat);

        /**
         * Like NewL, but leaves the created object on the cleanup stack.
         */
        IMPORT_C static CPbkContactItem* NewLC(
                CContactItem* aItem, 
                const CPbkFieldsInfo& aFieldsInfo,
                MPbkContactNameFormat& aNameFormat);

        /**
         * Destructor.
         */
        ~CPbkContactItem();

    public: // CContactItem functions
        /**
         * Returns this contact item's id.
         * @see CContactItem::Id()
         */
        IMPORT_C TContactItemId Id() const;
        
        /**
         * Returns type of this contact item.
         * @see CContactItem::Type()
         */
        IMPORT_C TUid Type() const;

        /**
         * Gets the groups this contact belongs to.
         * @return array of group ids. Caller owns the array.
         * @see CContactItem::GroupsJoinedLC()
         */
        IMPORT_C CContactIdArray* GroupsJoinedLC() const;

        /**
         * Converts this object to a CContactItem. Use only if this class's API
         * is not enough.
         */
        IMPORT_C CContactItem& ContactItem();

        /**
         * Converts this object to a const CContactItem. Use only if this 
         * class's API is not enough.
         */
        IMPORT_C const CContactItem& ContactItem() const;

    public:  // Field set operations
        /**
         * Returns the field set of this contact item.
         */
        IMPORT_C CPbkFieldArray& CardFields() const;

        /**
         * Creates a new field based on aFieldInfo and adds it to this contact.
         *
         * @param aFieldInfo    type of field to create.
         * @return the created field.
         */
      	IMPORT_C TPbkContactItemField& AddFieldL(CPbkFieldInfo& aFieldInfo);

        /**
         * Returns true if data of type aFieldInfo can be added to this 
         * contact.
         */
        IMPORT_C TBool CanAcceptDataOfType(CPbkFieldInfo& aFieldInfo) const;

        /**
         * Finds an unused or creates a new field based on aFieldInfo.
         *
         * @param aFieldInfo    type of field to search or create.
         * @return  pointer to the found or created field. NULL only if<br>
         *          field exists AND <br>
         *          field is nonempty AND <br>
         *          aFieldInfo.Multiplicity()==EPbkFieldMultiplicityOne.
         */
      	IMPORT_C TPbkContactItemField* AddOrReturnUnusedFieldL(CPbkFieldInfo& aFieldInfo);

        /**
         * Deletes field at aIndex.
         */
        IMPORT_C void RemoveField(TInt aIndex);

        /**
         * Updates this contacts field set to match field set of
         * the owned CContactItem. No need to call unless contact item's
         * field set has been manipulated directly.
         */
        IMPORT_C void UpdateFieldSetL(const CPbkFieldsInfo& aFieldsInfo);

    public:  // Field searching
        /**
         * Returns first field matching aFieldId.
         *
         * @param aFieldId  field id to search.
         * @return first field matching aFieldId, NULL if none found.
         */
        IMPORT_C TPbkContactItemField* FindField(TPbkFieldId aFieldId) const;

        /**
         * Returns first field matching aFieldId starting from aIndex.
         *
         * @param aFieldId  field id to search.
         * @param aIndex    input: field index where to start the search from,
         *                  output: index of the found field or -1 if not found.
         * @return field matching aFieldId, NULL if none found.
         */
        IMPORT_C TPbkContactItemField* FindField
            (TPbkFieldId aFieldId, TInt& aIndex) const;

        /**
         * Returns first field matching aFieldInfo.
         *
         * @return first field matching aFieldInfo, NULL if none found.
         */
        IMPORT_C TPbkContactItemField* FindField(const CPbkFieldInfo& aFieldInfo) const;

        /**
         * Returns first field matching aFieldInfo starting from aIndex.
         *
         * @param aIndex    input: field index where to start the search from,
         *                  output: index of the found field or -1 if not found.
         * @return field matching aFieldInfo, NULL if none found.
         */
        IMPORT_C TPbkContactItemField* FindField
            (const CPbkFieldInfo& aFieldInfo, TInt& aIndex) const;

        /**
         * Returns aField's index from this contact item.
         *
         * @param aField    field to search for. Field is matched with 
         *                  TPbkContactItemField::IsSame -function.
         * @return  index of aField in this contact item's field set, -1 if 
         *          not found.
         * @see TPbkContactItemField::IsSame
         */
        IMPORT_C TInt FindFieldIndex(const TPbkContactItemField& aField) const;

        /**
         * Returns aField's index from ContactItem()'s CardFields() or -1 if 
         * not found.
         */
        IMPORT_C TInt FindContactItemFieldIndex(const CContactItemField& aField) const;

        /**
         * Searches phone number fields of this contact for a match.
         * Uses PbkEngUtils::ContainSameDigits to perform the matching.
         *
         * @param aNumber   phone number to match to.
         * @param aNumberOfDigits   number of digits to compare from the end 
         *                          of the phone numbers. Full comparison
         *                          performed if 0.
         * @param aIndex    input: field index where to start the search from,
         *                  output: index of the found field or -1 if not found.
         * @return the matching field, NULL if not found.
         * @see PbkEngUtils::ContainSameDigits
         */
        IMPORT_C TPbkContactItemField* FindNextFieldWithPhoneNumber
            (const TDesC& aNumber,
            TInt aNumberOfDigits,
            TInt &aIndex) const;

        /**
         * Searches for a text in this contact's fields. Uses TDesC::FindF()
         * search the text from the fields.
         *
         * @param aIndex    input: field index from where to start the search,
         *                  output: index of the found field or -1 if not found.
         * @return the matching field, NULL if not found.
         * @see TDesC::FindF
         */
        IMPORT_C TPbkContactItemField* FindNextFieldWithText
            (const TDesC& aText,
            TInt& aIndex) const;

        /**
         * Returns field matching aField from this contact item's field set, NULL if
         * not found.
         *
         * @postcond !FindSameField(field) || FindSameField(field)->IsSame(field)
         */
        IMPORT_C TPbkContactItemField* FindSameField
            (const TPbkContactItemField& aField) const;

    public: // Contact presentation
        /**
         * Gets a title text for this contact or qtn_phob_unnamed.
         *
         * @return  a buffer containing the title or qtn_phob_unnamed if no
         *          title can be generated. Caller is responsible for deleting 
         *          the returned buffer.
         */
        IMPORT_C HBufC* GetContactTitleL() const;

        /**
         * Gets a title text for this contact.
         *
         * @return  a buffer containing the title text, NULL if title is empty.
         *          Caller is responsible for deleting the returned buffer.
         */
        IMPORT_C HBufC* GetContactTitleOrNullL() const;

        /**
         * Returns an Phonebook icon Id for a contact.
         *
         * @return icon index for this contact, EPbkNullIconId for no icon.
         */
        IMPORT_C TPbkIconId ContactIconIdL() const;

    public:  // Defaults
        /**
         * Returns the default phone number field of this contact.
         *
         * @return  default phone number field of this contact, 
         *          NULL if no default set.
         */
        IMPORT_C TPbkContactItemField* DefaultPhoneNumberField() const;

        /**
         * Sets this contact's default phone number field to aField.
         *
         * @param aField    field to set as default, if NULL phone number
         *                  default is removed. Guaranteed not to leave if
         *                  aField is NULL.
         * @exception KErrNotFound  if aField is not this contact's field.
         * @exception KErrNotSupported  if aField is not a phone number field.
         */
        IMPORT_C void SetDefaultPhoneNumberFieldL
            (TPbkContactItemField* aField);

        /**
         * Removes phone number default from this contact.
         *
         * @postcond DefaultPhoneNumberField()==NULL.
         */
        IMPORT_C void RemoveDefaultPhoneNumberField();

        /**
         * Returns the default SMS field of this contact.
         *
         * @return  default SMS field of this contact, 
         *          NULL if no default set.
         */
        IMPORT_C TPbkContactItemField* DefaultSmsField() const;

        /**
         * Sets this contact's default SMS field to aField.
         *
         * @param aField    field to set as default, if NULL SMS
         *                  default is removed. Guaranteed not to leave if
         *                  aField is NULL.
         * @exception KErrNotFound  if aField is not this contact's field.
         * @exception KErrNotSupported  if aField is not a phone number field.
         */
        IMPORT_C void SetDefaultSmsFieldL(TPbkContactItemField* aField);

        /**
         * Removes SMS field default from this contact.
         *
         * @postcond DefaultSmsField()==NULL.
         */
        IMPORT_C void RemoveDefaultSmsField();

        /**
         * Returns the default email field of this contact.
         *
         * @return  default email field of this contact, 
         *          NULL if no default set.
         */
        IMPORT_C TPbkContactItemField* DefaultEmailField() const;

        /**
         * Sets this contact's default email address field to aField.
         *
         * @param aField    field to set as default, if NULL email 
         *                  default is removed. Guaranteed not to leave if
         *                  aField is NULL.
         * @exception KErrNotFound  if aField is not this contact's field.
         * @exception KErrNotSupported  if aField is not an email field.
         */
        IMPORT_C void SetDefaultEmailFieldL(TPbkContactItemField* aField);

        /**
         * Removes email field default from this contact.
         *
         * @postcond DefaultEmailField()==NULL.
         */
        IMPORT_C void RemoveDefaultEmailField();

        /**
         * Returns the default Mms field of this contact.
         *
         * @return  default Mms field of this contact, 
         *          NULL if no default set.
         */
        IMPORT_C TPbkContactItemField* DefaultMmsField() const;

        /**
         * Sets this contact's default MMS address field to aField.
         *
         * @param aField    field to set as default, if NULL MMS 
         *                  default is removed. Guaranteed not to leave if
         *                  aField is NULL.
         * @exception KErrNotFound  if aField is not this contact's field.
         * @exception KErrNotSupported  if aField is not an email field.
         */
        IMPORT_C void SetDefaultMmsFieldL(TPbkContactItemField* aField);

        /**
         * Removes MMS field default from this contact.
         *
         * @postcond DefaultMmsField()==NULL.
         */
        IMPORT_C void RemoveDefaultMmsField();

    public:  // Voice tags
        /**
         * Returns the voice tag field of this contact.
         *
         * @return  voice tag field of this contact, 
         *          NULL if no voice tag set.
         */
        IMPORT_C TPbkContactItemField* VoiceTagField() const;

        /**
         * Sets this contact's voice tag field to aField.
         *
         * @param aField    field to set as default, if NULL voice tag mark
         *                  is removed. Guaranteed not to leave if
         *                  aField is NULL.
         * @exception KErrNotFound  if aField is not this contact's field.
         * @exception KErrNotSupported  if aField is not a phone number field.
         * @postcond (aField && VoiceTagField()->IsSame(*aField)) || (!aField && !VoiceTagField())
         */
        IMPORT_C void SetVoiceTagFieldL(TPbkContactItemField* aField);

        /**
         * Removes any voice tag mark from this contact.
         *
         * @postcond VoiceTagField()==NULL.
         */
        IMPORT_C void RemoveVoiceTagField();

    public:  // from MPbkFieldDataArray
        TInt PbkFieldCount() const;
        MPbkFieldData& PbkFieldAt(TInt aIndex);
        const MPbkFieldData& PbkFieldAt(TInt aIndex) const;

    public: // Phonebook internal functions, do not call
        /**
         * @internal
         * Prepares this contact for saving into the contact database.
         * @see PrepareAfterLoad
         */
        void PrepareForSaveL();

        /**
         * @internal
         * Prepares this contact after loading it from the contact database.
         * @see PrepareForSaveL
         */
        void PrepareAfterLoadL();
        
    private: // Implementation
        CPbkContactItem(MPbkContactNameFormat& aNameFormat);
        void ConstructL(CContactItem* aItem, const CPbkFieldsInfo& aFieldsInfo);
        void CreateFieldArrayL(CContactItem& aContactItem, const CPbkFieldsInfo& aFieldsInfo);
        TInt InsertionPos(const TPbkContactItemField& aField) const;
        __DECLARE_TEST;
        typedef CPbkContactItem SelfType;

    private:    // Data
        /// Own: Embedded contact item.
        CContactItem* iItem;
        /// Own: array of phonebook contact item fields
        CPbkFieldArray iFields;
        /// Ref: Contact name formatting API
        MPbkContactNameFormat& iNameFormat;

    private:  // Friend declarations
        friend IMPORT_C TBool operator==
            (const CPbkContactItem& aLeft, const CPbkContactItem& aRight);
    };


// FUNCTION DECLARATIONS

/**
 * Returns ETrue if aLeft and aRight contents are the same.
 */
IMPORT_C TBool operator==
    (const CPbkContactItem& aLeft, const CPbkContactItem& aRight);

/**
 * Returns ETrue if aLeft and aRight contents differ.
 */
inline TBool operator!=
    (const CPbkContactItem& aLeft, const CPbkContactItem& aRight)
    {
    return !(aLeft==aRight);
    }


#endif // __CPbkContactItem_H__
            
// End of File
