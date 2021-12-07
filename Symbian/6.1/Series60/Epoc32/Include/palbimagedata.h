/*
 * ============================================================================
*  Name     : PAlbImageData.h
 *  Part of  : PhotoAlbum
*
 *  Description:
 *      Acts as a wrapper between the filesystem and the photo album folder
 *      structure. Has features for operating on single images (Delete, rename etc.)
 *  Version  :
*
*  Copyright © 2002 Nokia Corporation.
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

#ifndef __PALBIMAGEDATA_H
#define __PALBIMAGEDATA_H

// INCLUDES
#include <bldvariant.hrh>
#include <e32std.h>
#include <e32base.h>
#include <f32file.h>


// CLASS DECLARATION


/**
 *  class stores data about the image to pass back from the fetching
 *  service to the calling class.
 *  @see CPAlbImageFetchPopupList
 */
class CPAlbImageData : public CBase
    {
public:  // Constructors and destructor
    /**
     *  destructor
     */
    IMPORT_C virtual ~CPAlbImageData();

    public:
    /**
     * creates and return instance of this class.
     * Name and subfolder is assigned t KNullDesC()
     * @return instance of this class
     */
    IMPORT_C static CPAlbImageData* NewL();

    /**
     * Copy constructor
     * @return a copy of aSrc.
     */
    IMPORT_C static CPAlbImageData* NewL( const CPAlbImageData& aSrc );

    /**
     * Returns subfolder of the image
     * @return subfolder name of the image stored in the object
     */
    IMPORT_C const TDesC& SubFolder() const;

    /**
     * Return the name of the image stored in the object.
     * @return the name of the image
     */
    IMPORT_C const TDesC& ImageName() const;

    /**
     * Set the image name for this CPAlbImageData
     * If the name is longer than KPAlbMaxFileLength it cause a leave
     * (KErrArgument). The length is defined in PAlbConstants.h.
     * @param aImageName name of the image without path!
     * @exception Leave if parameter is incorrect or OOM
     */
    IMPORT_C void SetImageNameL( const TDesC& aImageName );

    /**
     * Set the subfolder for this object. KNullDesC() means MainFolder.
     * NOTE! Use only the folder name eg. "Folder", less than KPAlbMaxFolderLength
     * chars
     * @param aFolder the subfolder name, or KNullDesC() for main folder
     * @exception will leave if parameter is incorrect, too long or OOM
     */
    IMPORT_C void SetSubFolderL( const TDesC& aFolder );

    /**
     * Set the folder and image name using a descriptor containing
     * a file path. Tries to find a filename and subfolder.
     * Examples:
     * aPath="\folder\name.jpg", subfolder = "folder", imagename = "name.jpg"
     * aPath="\name.jpg", subfolder = "", imagename = "name.jpg"
     * aPath="c:\test\folder\name.jpg, subfolder = "folder", imagename = "name.jpg"
     * @param aPath full absolute file path to fotoalbum folders
     * @exception will leave on incorrect parameters and OOM
     */
    IMPORT_C void SetNameAndSubFolderL( const TDesC& aPath );

    /**
     * resolve a full path using the set imagename and subfolder
     * If subfolder = "folder" and imagename = "name.jpg" this produces
     * "C:\nokia\images\folder\name.jpg".
     * @return the full path to the image
     *
     * The caller is responsible of deleting the resulted object!
     */
    IMPORT_C HBufC* ResolveImagePathL();

    /**
     * resolve a full path using the set imagename and subfolder
     * If subfolder = "folder" and imagename = "name.jpg" this produces
         * without MMC support: "C:\nokia\images_tn\folder\name.jpg".
         * with MMC support: "C:\nokia\images\folder\_PAlbTN\name.jpg".
       * @return the full path to the image
     *
     * Attention! Notice CleanupStack usage!
     * The caller is responsible of deleting the resulted object!
     */
    IMPORT_C HBufC* ResolveImagePathLC();

    /**
     * resolve a full path using the set imagename and subfolder
     * If subfolder = "folder" and imagename = "name.jpg" this produces
     * "C:\nokia\images\folder\name.jpg".
     * @return the full path to the image thumbnail!
     *
     * The caller is responsible of deleting the resulted object!
     */
    IMPORT_C HBufC* ResolveThumbnailPathL();

    /**
     * resolve a full path using the set imagename and subfolder
     * If subfolder = "folder" and imagename = "name.jpg" this produces
         * without MMC support: "C:\nokia\images_tn\folder\name.jpg".
         * with MMC support: "C:\nokia\images\folder\_PAlbTN\name.jpg".
     * @return the full path to the image thumbnail!
     *
     * Attention! Notice CleanupStack usage!
     * The caller is responsible of deleting the resulted object!
     */
    IMPORT_C HBufC* ResolveThumbnailPathLC();

    /**
     * Resolve the picture path from name. Folder is static
     * and defaults to C:\Nokia\Images\Pictures\ so this method
     * will not care about the set subfolder!
     * @return the path to the GMS picture!
     *
     * The caller is responsible of deleting the resulted object!
     */
    IMPORT_C HBufC* ResolvePicturePathL();

    /**
     * Resolve the picture path from name. Folder is static
     * and defaults to C:\Nokia\Images\Pictures\ so this method
     * will not care about the set subfolder!
     * @return the path to the GMS picture!
     *
     * Attention! Notice CleanupStack usage!
     * The caller is responsible of deleting the resulted object!
     */
    IMPORT_C HBufC* ResolvePicturePathLC();

    /**
     * Delete the image and the thumbnail pointed by this ImageData.
     */
    IMPORT_C void DeleteL();

    /**
     * Rename the image (and the thumbnail) pointed by this object
     * @param aDest CPAlbImageData containing new name
     */
    IMPORT_C void RenameL( CPAlbImageData& aDest );

    /**
     * @return ETrue if thumbnail file exists for the imagedata (this)
     */
    IMPORT_C TBool ThumbnailExistsL();

    /**
     * @return ETrue if image file exists for the imagedata (this)
     */
    IMPORT_C TBool ImageExistsL();

    /**
     * @return ETrue if picture file exists for the imagedata (this)
     */
    IMPORT_C TBool PictureExistsL();

    /**
     * Retuns ETrue if this object and aObj are equal.
     * @param aObj the imagedata object to be compared against
     */
    IMPORT_C TInt operator==( const CPAlbImageData& aObj ) const;

    /**
     * @return ETrue if the current image data is modifiable
     */
    IMPORT_C TBool IsModifiableL();

    /**
     * @return ETrue if image is newer than it's thumbnail or the
     * thumbnail does not exist
     */
    IMPORT_C TBool ImageIsNewerL();

public: // public but not exported
    /**
     * Check if given file is in use by another program
     * @param aFileName full path to file
     * @return ETrue if file is in use. EFalse if not
     */
     TBool IsFileInUse( const TDesC& aFileName );

    /**
     * Clears ReadOnly flag on given file
     * @param aFilePath full path to file
     * @return KErrNone if succesful. Other system wide code if error occurs.
     */
    TInt ClearReadOnlyFlagL( const TDesC& aFilePath );

    /**
     * Returns the size of given file
     * @param aFileName full path to file
     * @return file size in bytes
     */
    TInt FileSizeL( const TDesC& aFileName );
    
    /**
     * Verifies that the given filename is valid
     * @param aName filename to check
     * @return KErrNone if name is valid, KErrBadName if name is invalid
     */
    TInt IsValidFileName( const TDesC& aName );

protected: // Constructors and destructor

    /**
     *   default constructor
     */
    CPAlbImageData();

    /**
     *   2nd phase constrctions
     */
    void ConstructL();

protected:  // New functions

    /**
     *   panic helper
     */
    void Panic( TInt aReason );

private:    // Data

    // Owns: the dynamic buffer for image name
    HBufC* iImage;
    
    // Owns: the dynamic buffer for image path
    HBufC* iFolder;
    
    // Owns: The root folder of photoalbum images
    HBufC* iRootFolder;
    
    // Owns: pictures folder name
    HBufC* iPicFolder;
    
    // Owns: The root folder of photoalbum thumbnails
    HBufC* iRootTnFolder;
    
    // Owns: The state of this instance.
    TBool   iIsRelative;

    RFs     iFs;
    };

#endif // __PALBIMAGEDATA_H

// End of File
