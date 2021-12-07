/*
* ============================================================================
*  Name     : TPbkContactItemField.h
*  Part of  : PbkEng.dll
*
*  Description:
*     This class extends contact model CContactItemField class capabilities
*	  to better suit Phonebook's needs.
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

#ifndef __TPbkContactItemField_H__
#define __TPbkContactItemField_H__

//  INCLUDES
#include    <e32std.h>
#include    "MPbkFieldData.h"
#include    <cntdef.h>  // TStorageType
#include    "PbkIconId.hrh"

// These two includes are not needed here anymore
// and might be removed in the future
#include    <cntitem.h> // CContactItem
#include    <cntfldst.h> // CContactItemField storage types


// FORWARD DECLARATIONS
class CPbkFieldInfo;
class CContactItemField;
class CContactTextField;
class CPbkContactItem;
class CContactDateField;


// CLASS DECLARATION

/**
 *  Phonebook Contact item Field class.
 *  This class extends contact model CContactItemField class capabilities
 *  to better suit Phonebook's needs.
 */
class TPbkContactItemField : public MPbkFieldData
    {
    public:  // Constructors and destructor
        /**
         * C++ default constructor.
         */
        IMPORT_C TPbkContactItemField();

        /**
         * C++ constructor.
         *
         * @param aField        Contact Model field this object is wrapping.
         * @param aFieldInfo    Phonebook field type of aField.
         */
        IMPORT_C TPbkContactItemField(CContactItemField* aField,
			CPbkFieldInfo* aFieldInfo);

        /**
         * Sets the contents of this object after construction.
         * @param aField        Contact Model field this object is wrapping
         * @param aFieldInfo    Phonebook field type of aField
         */
        IMPORT_C void Set(CContactItemField* aField,
			CPbkFieldInfo* aFieldInfo);

    public: // New functions
        /**
         * Returns an Phonebook icon id for this field.
         */
        IMPORT_C TPbkIconId IconId() const;

        /**
         * Returns the Phonebook field info object of this field.
         * @return  field info for this field, NULL if no field info could
         *          be matched with the field.
         */
        IMPORT_C CPbkFieldInfo& FieldInfo() const;

        /**
         * Returns this field's textual content.
         * @precond StorageType()==KStorageTypeText.
         */ 
        IMPORT_C TPtrC Text() const;

        /**
         * Returns this field's date/time content.
         * @precond StorageType()==KStorageTypeDateTime.
         */ 
        IMPORT_C TTime Time() const;

        /**
         * Fills aText with field's text content. If field is of date
		 * type formats the date as text.
         *
         * @exception KErrOverflow  if aText is not big enough for
		 * the text. aText contents will be clipped to aText.MaxLength().
         * @exception KErrNotSupported  if the field content cannot be
		 * represented as text.
         */
        IMPORT_C void GetTextL(TDes& aText) const;

        /**
         * Returns the storage type of this field.
         */
        IMPORT_C TStorageType StorageType() const;

        /**
         * Returns the embedded contact item field.
         */
        IMPORT_C CContactItemField& ItemField() const;

        /**
         * Returns the text storage object of this field.
         */
        IMPORT_C CContactTextField* TextStorage() const;

        /**
         * Returns the label text of this field
         */
        IMPORT_C TPtrC Label() const;

        /**
         * Sets the label text of this field to aLabel.
         */
        IMPORT_C void SetLabelL(const TDesC& aLabel);

        /**
         * Marks this field as hidden or unhidden.
         * @param aHidden   ETrue marks as hidden EFalse removes the mark.
         */
        IMPORT_C void SetHidden(TBool aHidden);

        /**
         * Check if field is marked hidden.
         */
        IMPORT_C TBool IsHidden() const;

        /**
         * Returns time storage of this field.
         */
        IMPORT_C CContactDateField* DateTimeStorage() const;

        /**
         * Returns ETrue if this is the same field as aField.
         */
        IMPORT_C TBool IsSame(const TPbkContactItemField& aField) const;

        /**
         * Converts this field to a CContactItemField.
         * @return the embedded CContactItemField object.
         */
        IMPORT_C CContactItemField& ContactItemField();

        /**
         * Converts this field to a const CContactItemField.
         * @return the embedded CContactItemField object.
         */
        IMPORT_C const CContactItemField& ContactItemField() const;

        /**
         * Compares two items against the group ordering.
         */
        IMPORT_C TInt Compare(const TPbkContactItemField& aRhs) const;

        /**
         * Returns an unique id for this field.
         * NOTE: Returned id is valid only as long as this object is in memory
         * in other words the id is not persistent!
         */
        IMPORT_C TInt UniqueFieldIdentity() const;

        /**
         * Returns ETrue if this field's contents is empty.
         */
        IMPORT_C TBool IsEmpty() const;
        
        /**
         * Returns ETrue if this field's contents is empty or all spaces.
         */
        IMPORT_C TBool IsEmptyOrAllSpaces() const;

        /**
         * Returns ETrue is this field is a default phone number field.
         * @see CPbkContactItem::DefaultPhoneNumberField
         * @see CPbkContactItem::SetDefaultPhoneNumberField
         */
        IMPORT_C TBool DefaultPhoneNumberField() const;

        /**
         * Returns ETrue is this field is a default SMS field.
         * @see CPbkContactItem::DefaultSmsField
         * @see CPbkContactItem::SetDefaultSmsField
         */
        IMPORT_C TBool DefaultSmsField() const;

        /**
         * Returns ETrue is this field is a default email field.
         * @see CPbkContactItem::DefaultEmailField
         * @see CPbkContactItem::SetDefaultEmailField
         */
        IMPORT_C TBool DefaultEmailField() const;

        /**
         * Returns ETrue is this field is a default MMS field.
         * @see CPbkContactItem::DefaultMmsField
         * @see CPbkContactItem::SetDefaultMmsField
         */
        IMPORT_C TBool DefaultMmsField() const;

        /**
         * Returns a array of speed dial indexes assigned to this field, 
         * NULL if none.
         */
        IMPORT_C CArrayFix<TInt>* SpeedDialIndexesL() const;

    public:  // from MPbkFieldData
        IMPORT_C TStorageType PbkFieldType() const;
        IMPORT_C TPbkFieldId PbkFieldId() const;
        IMPORT_C TPtrC PbkFieldText() const;
        IMPORT_C TTime PbkFieldTime() const;
        
    private: // CPbkContactItem support functions
        /// CPbkContactItem calls private functions of this class
        friend class CPbkContactItem;
        void PrepareForSaveL();
        void PrepareAfterLoadL();
        TBool HasInvalidDate();

    private:    // Data
        /// Ref: Contact item field to be expanded into greater heights
        CContactItemField* iField;
        /// Ref: field info object matching iField's type
        CPbkFieldInfo* iFieldInfo;

    private:  // Friend declarations
        friend IMPORT_C TBool operator==
            (const TPbkContactItemField& aLeft, 
            const TPbkContactItemField& aRight);
    };


// FUNCTION DECLARATIONS

/**
 * Returns ETrue if aLeft has same contents as aRight.
 * Doesn't compare everything (all field flags etc.) but all the attributes
 * that could affect how this field looks like in the Phonebook UI. This 
 * function can be used to determine wheter to update this field in the UI.
 */
IMPORT_C TBool operator==
    (const TPbkContactItemField& aLeft, 
    const TPbkContactItemField& aRight);

/**
 * Returns !(aLeft==aRight).
 */
inline TBool operator!=
    (const TPbkContactItemField& aLeft, 
    const TPbkContactItemField& aRight)
    {
    return !(aLeft==aRight);
    }


#endif // __TPbkContactItemField_H__
            
// End of File
