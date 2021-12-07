/*
* ============================================================================
*  Name     : CAknIconArray.h
*  Part of  : Avkon
*
*  Description:
*     Icon array helper class
*
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef     __AKNICONARRAY_H__
#define     __AKNICONARRAY_H__


//  INCLUDES
#include <e32base.h>


//  FORWARD DECLARATIONS
class CGulIcon;
class TResourceReader;


// CLASS DECLARATION

/**
 * Icon array helper class. Extends CArrayPtrFlat<CGulIcon> to make it easier
 * to load icons for a listbox. This class IS-A CArrayPtrFlat<CGulIcon>, but 
 * owns the CGulIcons it contains for leave-safety.
 */
class CAknIconArray : public CArrayPtrFlat<CGulIcon>
    {
    public:  // Constructors and destructor
        /**
         * C++ Constructor.
         */
        IMPORT_C CAknIconArray(TInt aGranurality);

        /**
         * Second phase constructor: loads contents of array from resources.
         *
         * @param aResId    id of a AKN_ICON_ARRAY resource.
         */
        IMPORT_C void ConstructFromResourceL(TInt aResId);

        /**
         * Second phase constructor: loads contents of array from resources.
         *
         * @param aReader   resource reader pointed to a 
         *                  AKN_ICON_ARRAY resource.
         */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

        /**
         * Destructor. Destroys all icons in the array.
         */
        IMPORT_C ~CAknIconArray();

    public:  // interface
        /**
         * Append icons from a resource to this array.
         *
         * @param aResId    id of a AKN_ICON_ARRAY resource.
         */
        IMPORT_C void AppendFromResourceL(TInt aResId);

        /**
         * Append icons from a resource to this array.
         *
         * @param aReader   resource reader pointed to a 
         *                  AKN_ICON_ARRAY resource
         */
        IMPORT_C void AppendFromResourceL(TResourceReader& aReader);
	
	private: // implementation 
		/**
		 * Search for bitmap file on all connected drives
		 *
		 * Read bitmap file name from resource. This may or may
		 * not have a drive specified. If the drive has been specified,
		 * TFindFile::FindByDir searches for this file on that drive.
		 * If no drive has been specified, drives are searched from y:
		 * to a: and then z: as the last drive. Therefore, ROM apps should
		 * hard code the Z: drive in order to improve performance. 
		 *
		 * Security warning: third parties can replace the bitmap files
		 * by adding another file, with the same name and path, on a 
		 * drive which has a letter higher than the drive the existing
		 * file is installed on (e.g. file on MMC drive overrides file
		 * on C: drive). This can be prevented by hard-coding the drive
		 * letter. 
		 *
		 * Leave with KErrNotFound if the file specified is not found on
		 * any connected drive
		 *
		 * @param aReader   resource reader pointed to a 
         *                  AKN_ICON_ARRAY resource
		 *
		 * @return			The bitmap file name
		 */
		 HBufC* GetBmpNameLC(TResourceReader& aReader);

    };


#endif  // __AKNICONARRAY_H__
            

// End of File

