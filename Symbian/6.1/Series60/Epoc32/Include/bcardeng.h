/*
* ============================================================================
*  Name     : BCardEng.h
*  Part of  : BCardEng.dll
*
*  Description:
*      A class to convert Phonebook items to vCard stream and vice versa
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

#ifndef __BCardEng_H__
#define __BCardEng_H__


// INCLUDES
#include <e32base.h>        // CBase
#include <badesca.h>        // CDesCArrayFlat
#include "PbkFields.hrh"    // TPbkFieldId


// CONSTANTS
_LIT(KPbkvCardFileExtension, ".vcf");

// FORWARD DECLARATIONS
class CPbkContactEngine;
class CPbkContactItem;
class RWriteStream;
class RReadStream;
class CBCardFieldUidMapping;
class CBCardExportProperty;
class CParserVCard;

// CLASS DECLARATION

/**
 * A class to import and export vCard and Compact Business Cards to and from
 * a Phonebook Contact.
 */
class CBCardEngine : public CBase
	{
    public: // Constructors and destructor
        /**
         * Creates a new instance of this class.
		 * @param aEngine An open Phonebook Engine object which CBCardEngine
		 *        uses to import and export vCard data.
         */
		IMPORT_C static CBCardEngine* NewL(CPbkContactEngine* aEngine);

        /**
         * Destructor
         */
		IMPORT_C ~CBCardEngine();

	public: // The main public interface
        /**
         * Reads a vCard record from a stream into a Phonebook Contact
		 * Item object.
		 * @param aDestItem Phonebook ContactItem where the information
		 *        should be written to. The item should be writable. The
		 *        caller should commit the changes.
		 * @param aSourceStream A stream where the vCard data is read from
         */
		IMPORT_C void ImportBusinessCardL(CPbkContactItem& aDestItem,
			RReadStream &aSourceStream);

        /**
         * Writes a vCard record with information from a Phonebook Contact
		 * Item object
		 * @param aDestStream A stream where the vCard data is written to.
		 *        The data written to the stream is not Commited by this method.
		 * @param aSourceItem Phonebook ContactItem where the information
		 *        should be read from
         */
        IMPORT_C void ExportBusinessCardL(RWriteStream& aDestStream,
			CPbkContactItem& aSourceItem);

        /**
         * Reads a Compact Business Card record from a stream into a Phonebook
		 * Contact Item object.
		 * @param aDestItem Phonebook ContactItem where the information
		 *        should be written to. The item should be writable.
		 *        The caller should commit the changes.
		 * @param aSourceStream A stream where the Compact Business Card
		 *        is read from
		 * @return ETrue on success
         */
        IMPORT_C TBool ImportCompactBusinessCardL(CPbkContactItem& aDestItem,
			RReadStream &aSourceStream);

        /** 
         * Checks if given field is supported by the vCard format
         * @param aFieldId field id type
         * @return ETrue if given field is supported, EFalse otherwise
         */
        IMPORT_C TBool SupportsFieldType(TPbkFieldId aFieldId);

    private:  // Constructors
		CBCardEngine();
		void ConstructL(CPbkContactEngine* aEngine);

    private:    // Private utility methods
        void ProcessExportPropertyL(
            CParserVCard& aParser, 
            CPbkContactItem& aSourceItem, 
            const CBCardExportProperty& aExportProperty);
        TInt GetLineFromStreamL(TDes& aBuf, RReadStream& aSourceStream);
        TInt GetByteFromStream(TInt8& aByte, RReadStream& aSourceStream);
		class CBCardFieldAction;
	
    private:
        /// Own: Filename for picture
        HBufC* iPictureFileName;
		/// Own: Filename for thumbnail
		HBufC* iThumbnailFileName;
        /// Own: Instance for property name-Uid mapping
        CBCardFieldUidMapping* iNameUidMap;
        /// Own: Instance for contact field handling
        CBCardFieldAction* iFieldAction;
        /// Ref: Phonebook engine
        CPbkContactEngine* iEngine;
        /// Own: Array of CBCardExportProperty instances for exporting contact
        RPointerArray<CBCardExportProperty> iExportProperties;
	};

#endif // __BCardEng_H__

// End of File
