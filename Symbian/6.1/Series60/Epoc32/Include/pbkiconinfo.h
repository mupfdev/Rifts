/*
* ============================================================================
*  Name     : TPbkIconInfo from PbkIconInfo.h
*  Part of  : PbkView.dll
*
*  Description:
*           Phonebook icon info class definition.
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

#ifndef __PbkIconInfo_H__
#define __PbkIconInfo_H__

//  INCLUDES
#include <e32base.h>        // CBase
#include <PbkIconId.hrh>    // TPbkIconId

// FORWARD DECLARATIONS
class TResourceReader;
class CCoeEnv;
class CGulIcon;
class CPbkIconInfoContainer;

// CLASS DECLARATION

/**
 * Phonebook Icon info class.
 * @see CPbkIconInfoContainer
 */
class TPbkIconInfo
    {
    public: // interface
        /**
         * Returns the unique Phonebook icon id of this icon.
         */
        IMPORT_C TPbkIconId PbkIconInfoId() const;

        /**
         * Returns the bitmap file name of this icon.
         */
        IMPORT_C const TDesC& MbmFileName() const;

        /**
         * Returns this icon's id in the bitmap file.
         */
        IMPORT_C TInt IconId() const;

        /**
         * Returns this icon's mask id in the bitmap file.
         */
        IMPORT_C TInt MaskId() const;

    private:  // Interface for CPbkIconInfoContainer
        friend class CPbkIconInfoContainer;
        TPbkIconInfo();
        ~TPbkIconInfo();
        void ReadFromResourceLC(TResourceReader& aReader);
        void Destroy();

    private:  // Unimplemented functions
        /// Private, unimplemented copy constructor
        TPbkIconInfo(const TPbkIconInfo&);
        /// Private, unimplemented assignment operator
        TPbkIconInfo& operator=(const TPbkIconInfo&);

    private: // data members
        // Own: unique phonebook icon id
        TPbkIconId iPbkIconInfoId;
        // Own: Icon bitmap
        TInt iIconId;
        // Own: mask bitmap
        TInt iMaskId;
        // Ref: Mbm file name
        HBufC* iMbmFileName;
    };


/**
 * Collection of Phonebook icon info objects.
 * @see TPbkIconInfo
 */
class CPbkIconInfoContainer : public CBase
    {
    public: // Constructors and destructor
        /**
         * Creates a new instance of this class intialised with Phonebook 
         * default icon info from PbkView.rsc. Note that PbkView.rsc has to
         * be loaded, see RPbkViewResourceFile.
         *
         * @param aCoeEnv   optional CCoeEnv instance. This function performs
         *                  faster if this parameter is provided.
         * @return a new instance of this class.
         */
        IMPORT_C static CPbkIconInfoContainer* NewL(CCoeEnv* aCoeEnv=NULL);
        
        /**
         * Creates a new instance of this class.
         *
         * @param aReader   resource reader initialised to point to an array
         *                  of PBK_ICON_INFO resources.
         * @return a new instance of this class.
         */
        IMPORT_C static CPbkIconInfoContainer* NewL(TResourceReader& aReader);

        /**
         * Creates a new instance of this class.
         *
         * @param aResourceId aResourceId resource id of an array of 
         *                  PBK_ICON_INFO resources. Phonebook default icon
         *                  info array's resource id is R_PBK_ICON_INFO_ARRAY
         *                  in PbkView.rsc.
         * @param aCoeEnv   optional CCoeEnv instance. This function performs
         *                  faster if this parameter is provided.
         * @return a new instance of this class.
         */
        IMPORT_C static CPbkIconInfoContainer* NewL
            (TInt aResourceId, CCoeEnv* aCoeEnv=NULL);
        
        /**
         * Destructor.
         */
        ~CPbkIconInfoContainer();

    public:  // Interface
        /**
         * Finds a particular TPbkIconInfo in the container.
         *
         * @param aIconId   id of the icon info to search.
         * @return matching icon info or NULL if not found.
         */
        IMPORT_C const TPbkIconInfo* Find(TPbkIconId aIconId) const;

        /**
         * Creates and returns a CGulIcon that corresponds to the aIconId.
         */
        IMPORT_C CGulIcon* LoadBitmapL(TPbkIconId aIconId) const;

    private: // Implementation
        CPbkIconInfoContainer();
        void ConstructL(TResourceReader& aReader);

    private: // data members
        /// Own: array of icon infos
        RArray<TPbkIconInfo> iIconArray;
    };

#endif // __PbkIconInfo_H__

// End of File
