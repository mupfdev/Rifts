/*
* ============================================================================
*  Name     : CPbkMemoryEntryAddItemDlg from CPbkMemoryEntryAddItemDlg.h
*  Part of  : PbkView.dll
*
*  Description:
*       Field type selection dialog for Phonebook's Create New / Edit Memory entry
*       functions.
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

#ifndef __CPbkMemoryEntryAddItemDlg_H__
#define __CPbkMemoryEntryAddItemDlg_H__

//  INCLUDES
#include <e32base.h>

// FORWARD DECLARATIONS
class CPbkFieldInfo;
class CEikFormattedCellListBox;
class CAknPopupList;

// CLASS DECLARATION

/**
 * Field type selection dialog for Phonebook's Create New / Edit Memory entry
 * functions.
 * Also used externally for Create New Entry and Add to Existing Entry 
 * services.
 */
class CPbkMemoryEntryAddItemDlg : public CBase
    {
    public:  // Interface
        /**
         * Constructor.
         */
        IMPORT_C CPbkMemoryEntryAddItemDlg();

        /**
         * Sets *aSelfPtr to NULL when this dialog is destroyed.
         * @precond !aSelfPtr || *aSelfPtr==this
         */
        IMPORT_C void ResetWhenDestroyed(CPbkMemoryEntryAddItemDlg** aSelfPtr);

        /**
         * Run the dialog and return selected field info.
         *
         * @param aFieldInfos   array of field infos to select from.
         * @param aCbaResource  cba buttons to use with the dialog.
         * @return pointer to a field info in aFieldInfos or NULL if canceled.
         */
        IMPORT_C CPbkFieldInfo* ExecuteLD
            (CArrayPtrFlat<CPbkFieldInfo>& aFieldInfos, TInt aCbaResource);

        /**
         * Run the dialog and return selected field info.
         *
         * @param aFieldInfos   array of field infos to select from.
         * @param aCbaResource  cba buttons to use with the dialog.
         * @param aTitleText    text to put into popup list's title. No title
         *                      pane if aTitleText is empty.
         * @return pointer to a field info in aFieldInfos or NULL if canceled.
         */
        IMPORT_C CPbkFieldInfo* ExecuteLD
            (CArrayPtr<CPbkFieldInfo>& aFieldInfos, 
            TInt aCbaResource,
            const TDesC& aTitleText);

        /**
         * Basic ExecuteLD for derived classes to override.
		 * @param aFieldInfos array of field infos to selecto from
         */
        IMPORT_C virtual CPbkFieldInfo* ExecuteLD
			(CArrayPtr<CPbkFieldInfo>& aFieldInfos);

        /**
         * Destructor.
         * Also cancels and dismisses this popup list, in other words makes
         * ExecuteLD return just like cancel was pressed.
         */
        IMPORT_C ~CPbkMemoryEntryAddItemDlg();

    public: // internal implementation
        /**
         * @internal
         * Sorts the field infos according to Phonebook specific rules.
         */
        void SortFieldInfoArray();

    protected:  // Interface for derived classes
        /**
         * Creates list items, sets Cba and title.
         * Executed pre RunLD.
         * First part of ExecuteLD.
		 * @param aFieldInfos array of field infos to selecto from
		 * @param aCbaResource  cba buttons to use with the dialog
		 * @param aTitle text to put into popup list's title
         */
        void PrepareLC(CArrayPtr<CPbkFieldInfo>& aFieldInfos, 
            TInt aCbaResource, const TDesC& aTitle);

        /**
         * Execute the initialized dialog.
         * Second part of ExecuteLD.
		 * @return pointer to a field info
         */
        CPbkFieldInfo* RunLD();

    private:  // Spare virtual functions
        IMPORT_C virtual void Reserved_1();
        IMPORT_C virtual void Reserved_2();

    private: // Data types
        class CListBoxModel;

    private: // Data members
        /// Own: list box.
        CEikFormattedCellListBox* iListBox;
        /// Own: popup listbox.
        CAknPopupList* iPopupList;
        /// Ref: Referred boolean is set to ETrue when this object is destroyed.
        TBool* iDestroyedPtr;
        /// Ref: set to NULL from destructor
        CPbkMemoryEntryAddItemDlg** iSelfPtr;
        // Own: Sort Field Infos 
        TBool iSortFieldInfos;
    };


/**
 * Field type selection dialog for Phonebook's Create New service.
 */
class CPbkItemTypeSelectCreateNew : public CPbkMemoryEntryAddItemDlg
    {
    public:  // Interface
        /**
         * Constructor.
         */
        IMPORT_C CPbkItemTypeSelectCreateNew();

        /**
         * Destructor.
         * Also cancels and dismisses this popup list, in other words makes
         * ExecuteLD return just like cancel was pressed.
         */
        IMPORT_C ~CPbkItemTypeSelectCreateNew();

    public:  // from CPbkMemoryEntryAddItemDlg
        /**
         * Run this dialog and return selected field info.
         *
         * @param aFieldInfos   array of field infos to select from.
         * @return pointer to a field info in aFieldInfos or NULL if canceled.
         */
        IMPORT_C CPbkFieldInfo* ExecuteLD(CArrayPtr<CPbkFieldInfo>& aFieldInfos);

    private:  // Data
        /// Own: popup list title text
        HBufC* iTitleBuf;
        // Spare data
        TInt32 iSpare1;
    };


/**
 * Field type selection dialog for Phonebook's Add to Existing service.
 */
class CPbkItemTypeSelectAddToExisting : public CPbkMemoryEntryAddItemDlg
    {
    public:  // Interface
        /**
         * Constructor.
         */
        IMPORT_C CPbkItemTypeSelectAddToExisting();

        /**
         * Destructor.
         * Also cancels and dismisses this popup list, in other words makes
         * ExecuteLD return just like cancel was pressed.
         */
        IMPORT_C ~CPbkItemTypeSelectAddToExisting();

    public:  // from CPbkMemoryEntryAddItemDlg
        /**
         * Run this dialog and return selected field info.
         *
         * @param aFieldInfos   array of field infos to select from.
         * @return pointer to a field info in aFieldInfos or NULL if canceled.
         */
        IMPORT_C CPbkFieldInfo* ExecuteLD(CArrayPtr<CPbkFieldInfo>& aFieldInfos);

    private:  // Data
        /// Own: popup list title text
        HBufC* iTitleBuf;
        // Spare data
        TInt32 iSpare1;
    };

#endif  // __CPbkMemoryEntryAddItemDlg_H__
            
// End of File
