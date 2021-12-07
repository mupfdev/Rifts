/*
* ============================================================================
*  Name     : CPbkFieldInfo.h
*  Part of  : PbkEng.dll
*
*  Description:
*     Phonebook constant field type information
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

#ifndef __CPbkFieldInfo_H__
#define __CPbkFieldInfo_H__

//  INCLUDES
#include    <e32std.h>
#include    <cntdef.h>
#include    "PbkFields.hrh"
#include    "PbkIconId.hrh"

// FORWARD DECLARATIONS
class CContentType;
class CContactItemField;
class CContactItemViewDef;
class CContactItemFieldDef;
class CPbkFieldsInfo;
class TResourceReader;
class CPbkFieldInfoGroup;
class CPbkFieldImportType;
class TPbkContactItemFieldType;
class TPbkVcardFieldType;
class CPbkUidMap;
class TPbkMatchPriorityLevel;


// CLASS DECLARATION

/**
 * Phonebook constant field type information. Loaded from resources into
 * CPbkFieldsInfo array. The corresponding resource structure is PHONEBOOK_FIELD
 * in PbkFieldInfo.rh.
 *
 * @see CPbkFieldsInfo
 * @see PHONEBOOK_FIELD
 * @see FIELD
 */
class CPbkFieldInfo : 
        public CBase
	{
    public: // Interface
        /**
         * Returns the unique Phonebook field id for this field type.
         */
        IMPORT_C TPbkFieldId FieldId() const;

        /**
         * Returns the storage type of this field type.
         */
        IMPORT_C TStorageType FieldStorageType() const;

        /**
         * Returns the content type of this field type.
         */
        IMPORT_C const CContentType& ContentType() const;

        /**
         * Returns the category of this field type.
         */
        IMPORT_C TInt Category() const;

        /**
         * Returns this field type's default label.
         */
        IMPORT_C const TDesC& FieldName() const;

        /**
         * Returns Contact Model field flags of this field type.
         */
        IMPORT_C TUint Flags() const;

        /**
         * Returns the multiplicity allowed for this field type.
         */
        IMPORT_C TPbkFieldMultiplicity Multiplicity() const;

        /**
         * Returns the maximum data length that Phonebook UI spec specifies 
         * for this field type.
         */
        IMPORT_C TInt MaxLength() const;

        /**
         * Returns the default editing mode for this field type.
         */
        IMPORT_C TPbkFieldEditMode EditMode() const;

        /**
         * Returns the default character case for this field type.
         */
        IMPORT_C TPbkFieldDefaultCase DefaultCase() const;

        /**
         * Returns the icon id for this field type.
         */
        IMPORT_C TPbkIconId IconId() const;

        /**
         * Returns the UI control type required to edit this field.
         */
        IMPORT_C TPbkFieldCtrlType CtrlType() const;

        /**
         * Returns additional flags of this field type.
         */
        IMPORT_C TUint AddFlags() const;

        /**
         * Returns the UI ordering group of this field type.
         */
        IMPORT_C TPbkOrderingGroup OrderingGroup() const;
        
        /**
         * Returns the UI ordering item of this field type.
         */
        IMPORT_C TPbkOrderingItem OrderingItem() const;

        /**
         * Returns the UI ordering for adding a field.
         */
        IMPORT_C TPbkAddItemOrdering AddItemOrdering() const;

        /**
         * Returns ETrue if this field is hidden.
         */ 
        IMPORT_C TBool IsHidden() const;

        /**
         * Returns ETrue if this field is read only.
         */ 
        IMPORT_C TBool IsReadOnly() const;

        /**
         * Returns ETrue if this field is synchornized.
         */ 
        IMPORT_C TBool DoSynchronize() const;

        /**
         * Returns ETrue if this field is disabled.
         */ 
        IMPORT_C TBool IsDisabled() const;

        /**
         * Returns true if this is a name field type.
         */
        IMPORT_C TBool NameField() const;

        /**
         * Returns true if this field is part of the default template.
         */
        IMPORT_C TBool TemplateField() const;

        /**
         * Returns true if this field can be added by the user.
         */
        IMPORT_C TBool UserCanAddField() const;

        /**
         * Returns true if the field can be edited in Phonebook's contact 
         * editor.
         */
        IMPORT_C TBool IsEditable() const;

        /**
         * Returns ETrue if this is a numeric field
         */
        IMPORT_C TBool NumericField() const;

        /**
         * Returns ETrue if this is a phone number field.
         */ 
        IMPORT_C TBool IsPhoneNumberField() const;

        /**
         * Returns ETrue if this is a MMS address field.
         */ 
        IMPORT_C TBool IsMmsField() const;

        /**
         * Returns ETrue if this is an image field.
         */
        IMPORT_C TBool IsImageField() const;

        /**
         * Returns ETrue if aFieldInfo is same as this.
         */
        IMPORT_C TBool IsSame(const CPbkFieldInfo& aFieldInfo) const;

        /**
         * Returns ETrue if this field info matches aFieldId.
         */
        IMPORT_C TBool Match(TPbkFieldId aFieldId) const;

        /**
         * Returns ETrue if this field info matches aFieldType at any import
         * type priority level.
         */
        TBool Match(const TPbkContactItemFieldType& aFieldType) const;

        /**
         * Returns ETrue if this field info matches aFieldType at import
         * type priority level defined by aMatchPriority.
         */
        TBool Match
            (const TPbkContactItemFieldType& aFieldType, 
            const TPbkMatchPriorityLevel& aMatchPriority) const;

        /**
         * Returns ETrue if this field info matches aVcardType at import
         * type priority level defined by aMatchPriority.
         */
        TBool Match
            (const TPbkVcardFieldType& aVcardType,
            const TPbkMatchPriorityLevel& aMatchPriority) const;

        /**
         * @deprecated  This function is no longer supported. If you want to 
         *              find the CPbkFieldInfo instance matching a 
         *              CContactItemField use 
         *              CPbkFieldsInfo::Match(const CContactItemField&) const.
         *              That function works correctly and uses <it>a lot</it>
         *              faster algorithm than this function.
         *
         * Returns ETrue if this field info matches aField.
         */
        IMPORT_C TBool Match(const CContactItemField& aField) const;

        /**
         * Creates a contact model field of this field type.
         */
        IMPORT_C CContactItemField* CreateFieldL() const;

        /**
         * Returns ETrue if aField's label is equal to this field info object.
         */
        TBool IsEqualLabel(const CContactItemField& aField) const;

        /**
         * Returns ETrue if aField's type is equal to this field info object.
         */
        TBool IsEqualType(const CContactItemField& aField) const;

        /**
         * Returns ETrue if aField's type and labels are equal to this field 
         * info object.
         */
        IMPORT_C TBool IsEqualTo(const CContactItemField& aField) const;

        /**
         * Compares the field ordering of this and aOther. 
         *
         * @param   aOther  the other object this is compared against.
         * @return  0, if this and aOther are equal in field ordering<br>
         *          negative, if this is less than aOther in field ordering<br>
         *          positive, if this is greater than aOther in field ordering.
         */
        IMPORT_C TInt CompareOrdering(const CPbkFieldInfo& aOther) const;

        /**
         * Returns the field info group this field info belongs to or NULL.
         */
        IMPORT_C const CPbkFieldInfoGroup* Group() const;

        /**
         * Returns the location information of the field.
         */
        IMPORT_C const TPbkFieldLocation Location() const;

        /**
         * Returns the versit storage type of the field.
         */
        IMPORT_C const TPbkVersitStorageType VersitStorageType() const;

        /**
         * Add this field's type information to a contact item view definition.
         *
         * @param aViewDef  view definition to add types to.
         */
        IMPORT_C void AddToViewDefL(CContactItemViewDef& aViewDef) const;

        /**
         * Add this field's type information to a contact item field definition.
         *
         * @param aFieldDef field definition to add types to.
         */
        IMPORT_C void AddToFieldDefL(CContactItemFieldDef& aFieldDef) const;

        /**
         * Returns the Add item labeltext of the field.
         */
        IMPORT_C const TDesC& AddItemText() const; 


    private: // Constructors and destructor
        CPbkFieldInfo();
        static CPbkFieldInfo* NewLC(TResourceReader& aReaderStd, TResourceReader& aReaderAdd);
        ~CPbkFieldInfo();
        void ReadCntModelFieldsL(TResourceReader& aReaderStd);
        void ReadAdditionalFieldsL(TResourceReader& aReaderAdd);
        void ReadImportPropertiesL(TResourceReader& aReaderAdd);
        void ConstructFromResourceL
            (TResourceReader& aReaderStd, TResourceReader& aReaderAdd);
        TInt ImportPropertyCount() const;
        void UpdateTypeUidMapL(CPbkUidMap& aTypeUidMap) const;
        void CalculateTypeSignatures(const CPbkUidMap& aTypeUidMap);
        TBool IsEqualFlags(const CContactItemField& aField) const;

    private:  // Data
        /// Own: The unique field type id 
        TPbkFieldId iFieldId;

        /**
		 *Contact Model attributes			Attribute in resource
		 *									struct FIELD
		 */
        /// Own: storage type (Text,Date,...)
        TStorageType iFieldStorageType;		// LONG fieldStorageType
		/// Own: content type
        CContentType* iContentType;			// LONG contactFieldType,
											// LONG vCardMapping,
											// STRUCT extraMapping[]
		/// Own: category (Home/Work)
        TInt iCategory;						// LONG category
		/// Own: field's default name and label
        HBufC* iFieldName;					// LTEXT fieldName
		/// Own: special flags
        TUint iFlags;						// LONG flags

		/**
         *Additional attributes				Attributes in resource
		 *									struct PHONEBOOK_FIELD
		 */
        /// Own: allowed multiplicity (one/many).
        TPbkFieldMultiplicity iMultiplicity;// BYTE Multiplicity
        /// Own: maximum length in characters
        TInt iMaxLength;					// WORD MaxLength
        /// Own: default editing mode
        TPbkFieldEditMode iEditMode;		// BYTE EditMode
        /// Own: default character case
        TPbkFieldDefaultCase iDefaultCase;  // BYTE DefaultCase
        /// Own: index of an icon
        TPbkIconId iIconId;					// WORD IconId
        /// Own: editor UI control type
        TPbkFieldCtrlType iCtrlType;        // BYTE CtrlType
        /// Own: assorted flags for the field type
        TUint iAddFlags;					// LONG Flags
        /// Own: entry item grouping
        TPbkOrderingGroup iOrderingGroup;	// BYTE OrderingGroup
        /// Own: entry item group item ordering
        TPbkOrderingItem iOrderingItem;		// BYTE OrderingItem
        /// Own: entry Add Item ordering
        TPbkAddItemOrdering iAddItemOrdering;// BYTE AddItemOrdering
        /// Own: entry Add item labeltext
        HBufC* iAddItemText;				// LTEXT AddItemText
        /// Own: entry item location (none/home/work)
        TPbkFieldLocation iLocation;		// BYTE Location
        // Own: data storage type in versit
        TPbkVersitStorageType iVersitStorageType;// BYTE VersitStorageType
        
		/// Own: field import type
        CPbkFieldImportType* iImportType;

        union 
            {
            /// Own: group id before groups are loaded
            TPbkFieldGroupId iGroupId;
            /// Ref: field info group this contact info belongs to
            const CPbkFieldInfoGroup* iGroup;
            } iGroupLink;

    private: // Friend declarations
        friend class CPbkFieldsInfo;
	};


#endif // __CPbkFieldInfo_H__
            
// End of File
