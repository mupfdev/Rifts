/*
* ============================================================================
*  Name     : PAlbImageUtil.h
*  Part of  : PhotoAlbum
*
*  Description:
*
*  Version  :
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

#ifndef _PALBIMAGEUTIL_H
#define _PALBIMAGEUTIL_H

//  INCLUDES
#include <bldvariant.hrh>
#include <e32base.h>
#include <PAlbImageFactory.h>

// FORWARD DECLARATIONS
class CResourceLoader;

// CLASS DECLARATION
/**
 * Class CPAlbImageUtil
 *
 * This class implements the Image Saving API for Photo Album.
 * GMS Pictures and Image files can be stored inside the Photo Album
 * application folders using this class and the API it provides.
 *
 * General behaviour of the saving API
 *
 * There are four methods for moving files into the Photo Album.
 * 
 * MoveImageL(...)
 * CopyImageL(...)
 * MovePictureL(...)
 * CopyPictureL(...)
 * 
 * The Move and Copy versions differ only how the source file is handled
 * Move-version will rename the source file to the target Photo Album directory.
 * Copy-versions will create a copy of the source file to the Photo Album
 *
 * All of the four saving/moving methods take two parameters:
 * aSourceFile   descriptor containing full path name to the source file
 * aReplace      boolean, replace files in Photo Album or not.
 *
 * if aReplace is ETrue, the methods will replace files existing in the
 * Photo Album image or picture folder.
 *
 * if aReplace is EFalse, the API will generate a *new* filename for the
 * target file in case a file named similarly to the source file exists
 * in the Photo Album folder. The name generated by the API can be retrieved
 * after calling the Copy/Move methods. To do this use the ImageData()-method
 * which will return a pointer to the internal CPAlbImageData-object. This
 * object has methods for retrieving the image file name, folder name and
 * for resolving a full absolute filesystem path to the target image.
 *
 * The name generation works like this:
 *
 *  If the given filename is:
 *      "picture.jpg"
 *  then the resulted filename is either
 *      "picture.jpg" or "picture(XX).jpg" if "picture.jpg" already exists
 *  XXX is a running number from 01 to 99 (the next free index).
 *
 *  if the given filename is:
 *      "picture"
 *  then the resulted filename is either
 *      "picture" or "picture(XX)" where
 *  XX is a running number from 01 to 99 (the next free index).
 *
 * For example:
 *  You try to copy a file named "c:\temp\image.jpg" with replacing mode
 *  set to EFalse (obj here is an instance of the CPAlbImageUtil class):
 *
 *      obj->CopyImageL(_L("c:\temp\image.jpg"), EFalse)
 *
 *  Again if the Photo Album main folder already contains files named:
 * 
 * "image.jpg"
 * "image(02).jpg"
 * "image(03).jpg"
 *  Then the target file name would get a name "image(004).jpg".
 *
 *  You could get this filename by calling:<br>
 *
 *        obj->ImageData()->ImageName();
 *  Which will result a const TDesC& object having the name "test(004).jpg".
 *
 * Note! The filename part must never be longer than 40 characters! Longer names
 * will be CLIPPED to 40 characters! The filename is cut between the extension and
 * the filename part.
 * E.g. "123456789012345678901234567890123456.JPG" is the longest filename,
 * if new name was generated by the SavingAPI then it will be in the form of:
 * "1234567890123456789012345678901(XXX).JPG" where XXX is the running number
 *
 */
class CPAlbImageUtil : public CBase, public MPAlbImageFactoryObserver // Image factory observer
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        IMPORT_C static CPAlbImageUtil* NewL();

        /**
        * Destructor.
        */
        IMPORT_C ~CPAlbImageUtil();

    public:

        /**
         * Store image or picture into the PhotoAlbum. This method tries
         * to recognize the image format before copying it to the photoalbum.
         * If the image format is WBMP or OTA it is copied to the pictures
         * folder.
         * If the image format is any other it is copied to the PhotoAlbum
         * main images folder (Root level).
         *
         * The source file is COPIED only if the image format is recognizable.
         *
         * If thumbnail creation is set to off, using SetCreateThumbnails(..),
         * this method will not create thumbnails! Use CreateThumbnailL(..)
         * later.
         * NOTE! Thumbnail creation requires that the Media Server is running!
         *
         * After the call you can use ImageData() method to get the
         * info on saved picture.
         *
         * @param aSourceFile Pathname for source file
         * @param aReplace shall it replace existing files (ETrue will replace)
         * @exception Unrecognized image formats or error will cause Leave
         */
        IMPORT_C void CopyAndRecognizeL( const TDesC& aSourceFile,
                                         TBool aReplace );

        /**
         * Store image or picture into the PhotoAlbum. This method tries
         * to recognize the image format before moving it to the photoalbum.
         * If the image format is WBMP or OTA it is moved to the pictures
         * folder.
         * If the image format is any other it is moved to the PhotoAlbum
         * main images folder (Root level).
         *
         * The source file is MOVED only if the image format is recognizable.
         *
         * If thumbnail creation is set to off, using SetCreateThumbnails(..),
         * this method will not create thumbnails! Use CreateThumbnailL(..)
         * later.
         * NOTE! Thumbnail creation requires that the Media Server is running!
         *
         * After the call you can use ImageData() method to get the
         * info on saved picture.
         *
         * @param aSourceFile Pathname for source file
         * @param aReplace shall it replace existing files (ETrue will replace)
         * @exception Unrecognized image formats or error will cause Leave
         */
        IMPORT_C void MoveAndRecognizeL( const TDesC& aSourceFile,
                                         TBool aReplace );

        /**
         * Store image into the PhotoAlbum main image folder.
         * The original image is *MOVED* from the source path
         * to PhotoAlbum.
         *
         *
         * If thumbnail creation is set to off, using SetCreateThumbnails(..),
         * this method will not create thumbnails! Use CreateThumbnailL(..)
         * later.
         * NOTE! Thumbnail creation requires that the Media Server is running!
         *
         * After the call you can use ImageData() method to get the
         * info on saved picture.
         *
         * @param aSourceFile Pathname for source image file
         * @param aReplace shall it replace existing files
         */
        IMPORT_C void MoveImageL( const TDesC& aSourceFile,
                                  TBool aReplace );

        /**
         * Store image into the PhotoAlbum main image folder.
         * The original image is *MOVED* from the source path
         * to PhotoAlbum.
         *
         * This version takes an Symbian OS CFbsBitmap as one parameter. This bitmap
         * will be used as a source for the thumbnail creation. The bitmap
         * will be scaled down to the thumbnail size. This saves a lot of time
         * ecause the SavingAPI does not need to do bitmap conversions (ie.
         * jpg->EPOC) before initiating the scale.
         *
         * NOTE! The bitmap will be modified! So take a copy if you need it
         * afterwards.
         * NOTE! Thumbnail creation requires that the Media Server is running!
         *
         * @param aSourceFile Pathname for source image file
         * @param aReplace shall it replace existing files
         * @param aThumbBitmap Symbian OS bitmap that will be used as a thumbnail source
         */
        IMPORT_C void MoveImageL( const TDesC& aSourceFile,
                                  TBool aReplace,
                                  CFbsBitmap& aThumbBitmap );

        /**
         * Store image into the PhotoAlbum. If aSubFolder is KNullDesC()
         * then the image will be placed inside the main folder.
         * otherwise the image will be placed in the subfolder defined
         * by the parameter. If the subfolder does not exist it will be
         * created.
         *
         * The original image is *MOVED* from the source path
         * to PhotoAlbum.
         *
         * If thumbnail creation is set to off, using SetCreateThumbnails(..),
         * this method will not create thumbnails! Use CreateThumbnailL(..)
         * later.
         * NOTE! Thumbnail creation requires that the Media Server is running!
         *
         * After the call you can use ImageData() method to get the
         * info on saved picture.
         *
         * @param aSourceFile Pathname for source image file
         * @param aSubFolder subfolder name (e.g. "Folder1").
         * @param aReplace shall it replace existing files
         */
        IMPORT_C void MoveImageL( const TDesC& aSourceFile,
                                  const TDesC& aSubFolder, TBool aReplace );

        /**
         * Store image into the PhotoAlbum. If aSubFolder is KNullDesC()
         * then the image will be placed inside the main folder.
         * otherwise the image will be placed in the subfolder defined
         * by the parameter. If the subfolder does not exist it will be
         * created.
         *
         * The original image is *MOVED* from the source path
         * to PhotoAlbum.
         *
         * This version takes an Symbian OS CFbsBitmap as one parameter. This bitmap
         * will be used as a source for the thumbnail creation. The bitmap
         * will be scaled down to the thumbnail size. This saves a lot of time
         * ecause the SavingAPI does not need to do bitmap conversions (ie.
         * jpg->EPOC) before initiating the scale.
         * NOTE! Thumbnail creation requires that the Media Server is running!
         *
         * NOTE! The bitmap will be modified! So take a copy if you need it
         * afterwards.
         *
         * @param aSourceFile Pathname for source image file
         * @param aSubFolder subfolder name (e.g. "Folder1").
         * @param aReplace shall it replace existing files
         * @param aThumbBitmap Symbian OS bitmap that will be used as a thumbnail source
         */
        IMPORT_C void MoveImageL( const TDesC& aSourceFile,
                                  const TDesC& aSubFolder,
                                  TBool aReplace,
                                  CFbsBitmap& aThumbBitmap  );

        /**
         * Store image into the PhotoAlbum main image folder.
         * The original image is *COPIED* from the source path
         * to PhotoAlbum. (original file is retained)
         *
         * If thumbnail creation is set to off, using SetCreateThumbnails(..),
         * this method will not create thumbnails! Use CreateThumbnailL(..)
         * later.
         * NOTE! Thumbnail creation requires that the Media Server is running!
         *
         * After the call you can use ImageData() method to get the
         * info on saved picture.
         *
         * @param aSourceFile Pathname for source image file
         * @param aReplace shall it replace existing files
         */
        IMPORT_C void CopyImageL( const TDesC& aSourceFile, TBool aReplace );

        /**
         * Store image into the PhotoAlbum main image folder.
         * The original image is *COPIED* from the source path
         * to PhotoAlbum. (original file is retained)
         *
         * This version takes an Symbian OS CFbsBitmap as one parameter. This bitmap
         * will be used as a source for the thumbnail creation. The bitmap
         * will be scaled down to the thumbnail size. This saves a lot of time
         * ecause the SavingAPI does not need to do bitmap conversions (ie.
         * jpg->EPOC) before initiating the scale.
         * NOTE! Thumbnail creation requires that the Media Server is running!
         *
         * NOTE! The bitmap will be modified! So take a copy if you need it
         * afterwards.
         *
         * @param aSourceFile Pathname for source image file
         * @param aReplace shall it replace existing files
         * @param aThumbBitmap Symbian OS bmp that will be used as a thumbnail src
         */
        IMPORT_C void CopyImageL( const TDesC& aSourceFile, TBool aReplace,
                                  CFbsBitmap& aThumbBitmap  );


        /**
         * Store image into the PhotoAlbum. If aSubFolder is KNullDesC()
         * then the image will be placed inside the main folder.
         * otherwise the image will be placed in the subfolder defined
         * by the parameter. If the subfolder does not exist it will be
         * created.
         *
         * The original image is *COPIED* from the source path
         * to PhotoAlbum.
         *
         * If thumbnail creation is set to off, using SetCreateThumbnails(..),
         * this method will not create thumbnails! Use CreateThumbnailL(..)
         * later.
         * NOTE! Thumbnail creation requires that the Media Server is running!
         *
         * After the call you can use ImageData() method to get the
         * info on saved picture.
         *
         * @param aSourceFile Pathname for source image file
         * @param aSubFolder subfolder name (e.g. "Folder1").
         * @param aReplace shall it replace existing files
         */
        IMPORT_C void CopyImageL( const TDesC& aSourceFile,
                                  const TDesC& aSubFolder, TBool aReplace );

        /**
         * Store image into the PhotoAlbum. If aSubFolder is KNullDesC()
         * then the image will be placed inside the main folder.
         * otherwise the image will be placed in the subfolder defined
         * by the parameter. If the subfolder does not exist it will be
         * created.
         *
         * The original image is *COPIED* from the source path
         * to PhotoAlbum.
         *
         * This version takes an Symbian OS CFbsBitmap as one parameter. This bitmap
         * will be used as a source for the thumbnail creation. The bitmap
         * will be scaled down to the thumbnail size. This saves a lot of time
         * ecause the SavingAPI does not need to do bitmap conversions (ie.
         * jpg->EPOC) before initiating the scale.
         * NOTE! Thumbnail creation requires that the Media Server is running!
         *
         * NOTE! The bitmap will be modified! So take a copy if you need it
         * afterwards.
         *
         * @param aSourceFile Pathname for source image file
         * @param aSubFolder subfolder name (e.g. "Folder1").
         * @param aReplace shall it replace existing files
         * @param aThumbBitmap Symbian OS bitmap that will be used as a thumbnail source
         */
        IMPORT_C void CopyImageL( const TDesC& aSourceFile,
                                  const TDesC& aSubFolder,
                                  TBool aReplace, CFbsBitmap& aThumbBitmap );

        /**
        * Similar to CopyImageL but target folder is always "Pictures"
        * folder inside PhotoAlbum. It does not do file type recognition
        * so only use this method for OTA bitmaps!!!
        * The filename must have extension ".ota", otherwise photoalbum
        * will not recognize them.
        *
        * @param aSourceFile Pathname for source image file (*.ota)
        * @param aReplace shall it replace existing files
        */
        IMPORT_C void MovePictureL( const TDesC& aSourceFile, TBool aReplace );

        /**
        * Similar to CopyImageL but target folder is always "Pictures"
        * folder inside PhotoAlbum. It does not do file type recognition
        * so only use this method for OTA bitmaps!!!
        * The filename must have extension ".ota", otherwise photoalbum
        * will not recognize them.
        *
        * @param aSourceFile Pathname for source image file (*.ota)
        * @param aReplace shall it replace existing files
        */
        IMPORT_C void CopyPictureL( const TDesC& aSourceFile, TBool aReplace );

        /**
        * After using Copy/Move methods this will contain information about
        * actual name used for storing the image.
        *
        * @return a pointer to the CPAlbImageData object owned by this class
        */
        IMPORT_C CPAlbImageData* ImageData() const;

        /**
        * Try to resolve an available name for a file. The PhotoAlbum main
        * folder is scanned for the files matching the aFileName.
        *
        * After calling this method, the image file name
        * can be retrieved using the CPAlbImageData object
        * pointer returned by the ImageData() method.
        *
        * @param aFileName a file pathname ie. "file.jpg"
        * @exception OOM will cause leave
        */
        IMPORT_C void FetchFreeImageNameL( const TDesC& aFileName );

        /**
        * Try to resolve an available name for a file. The PhotoAlbum
        * pictures folder is scanned for the files matching the aFileName.
        *
        * This method works similardly as the FetchFreeImageNameL(...).
        * Only the scanned target folder is different.
        *
        * @param aFileName a file pathname ie. "file"
        * @exception OOM will cause leave
        */
        IMPORT_C void FetchFreePictureNameL( const TDesC& aFileName );

        /**
        * Deletes image from Photo Album.
        * Also thumbnail and comment for the image will be deleted
        *
        * @param aImageData defines the image to be deleted.
        * @exeption Leaves on fatal errors.
        */
        IMPORT_C void DeleteImageL( CPAlbImageData& aImageData );

        /**
        * Renames one image defined by aSource to have a new folder/name
        * defined by aDest.
        * @param aSource source image (folder/image)
        * @param aDest destination image (folder/image)
        */
        IMPORT_C void RenameImageL( CPAlbImageData& aSource,
                                    CPAlbImageData& aDest );

        /**
        * Deletes all image files from the given folder.
        * If folder is empty after deleting the image files, the
        * folder itself will be removed.
        *
        * @param aSubFolder name of the subfolder to be deleted
        * @exeption Leaves on fatal errors.
        */
        IMPORT_C void DeleteFolderL( const TDesC& aSubFolder );

        /**
        * This will rename a folder inside Photo Album
        * All relating folders in the filesystem will be renamed
        * (thumbnail, image)
        * Do not use absolute path, only the folder name!
        * You can't rename the pictures folder! ("Pictures")-> KErrArgument
        * Destination name can not be the localized name of the
        * pictures folder (eng: "Messaging Pictures") -> KErrAlreadyExists!
        *
        * @param aSource folder name to be renamed (ie. "images")
        * @param aDest new name for the folder (ie. "myimages");
        * @exeption Leaves on errors.
        */
        IMPORT_C void RenameFolderL( const TDesC& aSource,
                                     const TDesC& aDest );

        /**
        * Syncronizes all files for one image.
        * if image does not exists but a comment or thumbnail file exists
        *     -> Delete them
        * if image exists but no thumbnail
        *     -> Create a thumbnail for the image
        * @param aImageData defines the image file to be synchronized
        * @exeption Leaves on fatal errors.
        */
        IMPORT_C void SynchronizeL( CPAlbImageData& aData );

        /**
         * Remove all images and thumbnails from photoalbum
         */
        IMPORT_C void RemoveAllL();

        /**
        * Synchronous wrapper for the CPAlbImageFactory::GetThumbnailAsync(.)
        * will load and create thumbnail image for the images...
        * The caller is responsible of deleting the returned bitmap object
        * NOTE! Requires that the Media Server is running!
        *
        * @param aImageData CPAlbImageData object containing file/folder info
        * @return pointer to the thumbnail bitmap or NULL if error
        * @exeption Leaves on fatal errors.
        */
        IMPORT_C CFbsBitmap* GetThumbnailL( CPAlbImageData& aImageData );

        /**
        * Create a thumbnail for the image after copying
        * NOTE! Thumbnail creation requires that the Media Server is running!
        *
        * @param aImageData image (folder/imagename) which will get thumbnail
        */
        IMPORT_C void CreateThumbnailL( CPAlbImageData& aImageData );

        /**
        * Not supported anymore!
        */
        IMPORT_C void ConvertFormatL( const TDesC& aSrcFileName,
                                      const TDesC& aDestFileName,
                                      TInt aFormat );

        /**
        * This will set the SavingAPI thumbnail creation to on/off.
        * If the creation is set to off you can create a thumbnail by hand
        * using ::CreateThumbnailL(...) call.
        *
        * @param ETrue = Thumbnails will be created, EFAlse = will not create
        */
        IMPORT_C void SetCreateThumbnails( TBool aCreateThumbnails );

       /**
        * Try to resolve an available name for a file. The given
        * subfolder is scanned for the files matching the aFileName.
        *
        * After calling this method, the image file name
        * can be retrieved using the CPAlbImageData object
        * pointer returned by the ImageData() method.
        *
        * @param aFileName a file pathname ie. "file.jpg"
        * @param aSubFolder a subfolder to scan for the file
        * @exception OOM will cause leave
        */
        IMPORT_C void FetchFreeImageNameL( const TDesC& aFileName,
                                           const TDesC& aSubFolder );

    protected:  // Functions from base classes

        /**
        * From MPAlbImageFactoryObserver, observer for CPAlbImageFactory
        * @param aObj pointer to the calling CPalbImageFactory object
        * @param aError KErrNone if no error, otherwise an errorcode
        * @param aBitmap Pointer to a new CFbsBitmap object
        */
        void MPTfoCreateComplete( CPAlbImageFactory* aObj, TInt aError,
                                  CFbsBitmap* aBitmap );

    private:

        /**
         * C++ default constructor.
         */
        CPAlbImageUtil();

        /**
         * By default Symbian OS constructor is private.
         */
        void ConstructL();

        /**
         * This will return a pointer to CPAlbImageFactory object and it will
         * create the object if it is not already created!
         * @return a pointer to CPAlbImageFactory object held by this class
         */
        CPAlbImageFactory* ImageFactoryL();

        void CreateThumbnailFromBitmapL( CFbsBitmap& aBitmap );

        /**
         * Clears all flags recursively from all files in given folder
         * @param aPathName path
         * @return KErrNone if succesful
         **/
        TInt ClearFlagsRecursiveL( const TDesC& aPathName );
        /**
         * return ETrue if source file aSrc is on the same drive as aDest
         */
        TBool IsSameDrive( const TDesC& aSrc, const TDesC& aDest );

        void MoveImageInternalL( const TDesC& aSourceFile,
                                 const TDesC& aSubFolder,
                                 TBool aReplace );

        void CopyImageInternalL( const TDesC& aSourceFile,
                                 const TDesC& aSubFolder,
                                 TBool aReplace );

        /**
         * Fetch free filename from directory aPath
         * @param aPath full path to file
         */
        void DoFetchFreeFileNameL( const TDesC& aPath );

        /**
         * Move file, source file will be deleted!
         * @param aSourceFile full file path for the source file
         * @param aTargetPath target filepath
         * @param aReplace if ETrue will replace files. If EFalse will leave if
         *                 filename already exists in aTargetPath.
         */
        void DoFileMoveL( const TDesC& aSourceFile,
                          const TDesC& aTargetPath,
                          TBool aReplace );

        /**
         * Copy file
         * @param aSourceFile full file path for the source file
         * @param aTargetPath target filepath
         * @param aReplace if ETrue will replace files. If EFalse will leave if
         *                 filename already exists in aTargetPath.
         */
        void DoFileCopyL( const TDesC& aSourceFile,
                          const TDesC& aTargetPath,
                          TBool aReplace );

        /**
         * Delete all images and empty subfolders from given folder
         * (for recursive use)
         * @param aTargetPath target filepath
         */
        void DoRecursiveDeleteFolderL( const TDesC& aTargetPath );

        /**
         * Check if aPath (the drive) has enough free space for aFile
         * @param aFile     Full path to file 
         * @param aPath     Target filepath to check for free space
         * @return TBool    ETrue if aPath has enough space for aFile
         */
        TBool CheckForFreeSpaceL( const TDesC& aFile, const TDesC& aPath );

    private:    // Data

        // Own: Image factory object, for thumbnail generation
        CPAlbImageFactory* iFactory;

        // Own: Image data object
        CPAlbImageData* iImageData;

        // Own: File manipulation CFileMan
        CFileMan* iFileMan;

        // Own: Pointer to retrieved thumbnail bitmap
        CFbsBitmap* iThumbnail;

        // Own: File server session
        RFs iFs;

        // Own: Flag defining whether async operation is running or not
        TBool iAsyncOper;

        // Own: Internal flag
        TBool iRetrieveThumbnail;

        // Own: Flag to indicate whether saving API creates thumbnails or not
        TBool iCreateThumbnails;

        // Own: Internal error code
        TInt iError;
    };

#endif // _PALBIMAGEUTIL_H

// End of File
