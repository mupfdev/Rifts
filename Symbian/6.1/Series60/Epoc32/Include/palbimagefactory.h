/*
 * ============================================================================
 *  Name     : PAlbImageFactory.h
 *  Part of  : PhotoAlbum
 *
*  Description:
 *    Implementation of ImageFactory class. The class provides operations
 *    to get thumbnails and bitmaps from the Photo Album folders.
 *    Thumbnails are created on demand when GetThumbnailAsync() is called.
 *    LoadThumbnail provides a way to get previously generated thumbnail images
 *    without generation. 
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

#ifndef __PALBIMAGEFACTORY_H
#define __PALBIMAGEFACTORY_H

// INCLUDE FILES
#include <bldvariant.hrh>
#include <e32base.h>
#include <MdaImageConverter.h>
#include <PAlbImageData.h>

// CONSTANTS
// Default attribs for thumbnail
const TInt KThumbMinimum = 30;
const TInt KThumbWidth = 44;
const TInt KThumbHeight = 48;
const TReal KThumbMinRatio = TReal( KThumbMinimum ) / TReal( KThumbHeight );
const TReal KThumbMaxRatio = TReal( KThumbWidth ) / TReal( KThumbMinimum );

// following sizes for special cases
const TInt KWidth_VGA = 640;
const TInt KHeight_VGA = 480;
const TReal KWidthPerHeight_VGA = TReal( KWidth_VGA ) / TReal( KHeight_VGA );
const TReal KHeightPerWidth_VGA = TReal( KHeight_VGA ) / TReal( KWidth_VGA );
const TInt KThumbWidth_VGA = 40;
const TInt KThumbHeight_VGA = 30;

const TInt KWidth_CIF = 352;
const TInt KHeight_CIF = 288;
const TReal KWidthPerHeight_CIF = TReal( KWidth_CIF ) / TReal( KHeight_CIF );
const TReal KHeightPerWidth_CIF = TReal( KHeight_CIF ) / TReal( KWidth_CIF );
const TInt KThumbWidth_CIF = 44;
const TInt KThumbHeight_CIF = 36;

const TInt KWidth_COMM = 80;
const TInt KHeight_COMM = 96;
const TReal KHeightPerWidth_COMM = TReal( KHeight_COMM ) / TReal( KWidth_COMM);
const TInt KThumbWidth_COMM = 40;
const TInt KThumbHeight_COMM = 48;


// FORWARD DECLARATIONS
class CPAlbImageFactory;

// CLASS DECLARATION

/** MPAlbThumbnailFactoryObserver
 * Observer interface for the image factory CPAlbImageFactory class.
 * Classes using the factory must derive themselves from this observer
 * interface to get notification on the completion of the asynchronous
 * methods.
 */

class MPAlbImageFactoryObserver
    {
    public:

    /**
     * An observer method for asynchronous operations in 
     * CPAlbImageFactory. 
     *
     * Note! If the parameter aBitmap is not NULL the bitmap must eventually
     * be deleted by the class derived from this observer interface! 
     *
     * @param aObj which instance of CPAlbImageFactory called this
     * @param aError An error code if something went wrong otherwise KErrNone
     * @param aBitmap Pointer to the resulted bitmap or NULL.
     */
    virtual void MPTfoCreateComplete( CPAlbImageFactory* aObj, 
                                      TInt aError, 
                                      CFbsBitmap* aBitmap ) = 0;
    };

/** CPAlbImageFactory
 *
 * PhotoAlbum Image Factory class
 *
 * General description
 * -------------------
 * This class implements the image factory class for Photo Album. The image
 * factory can be used to retrieve bitmaps from the Photo Album folders. 
 * An original sized bitmap as well as a thumbnail representation 
 * of the original image can be retrieved.
 *
 * A thumbnail can be fetched using the method: @see CPAlbImageFactory#GetThumbnailAsync
 * 
 * As parameters you must give: 
 * (CPAlbImageData& aImagedata) describes image name and source photoalbum
 *      folder. Images can only be retrieved from photoalbum folders.
 * (CFbsBitmap& aThumbBitmap) reference to previously instantiated target 
 *      bitmap. This bitmap will be replaced to contain the thumbnail.
 *
 * Similar method is available for retrieving the original sized bitmap.
 * @see CPAlbImageFactory#GetImageAsync
 *
 * Success/failure conditions will be reported via the observer interface
 * MPAlbThumbnailFactoryObserver::MPTfoCreateComplete(...)
 * 
 * Thumbnail generation algorithm
 * ------------------------------
 * The algorithm will first check the size of the original bitmap.
 * There are 5 special cases:
 *
 * 
 * Original size    Thumb size  Image type
 * 640 x 480        40 x 30     VGA
 * 480 x 640        30 x 40     VGA turned
 * 352 x 288        44 x 36     CIF
 * 288 x 352        36 x 44     CIF turned
 * 80 x 96          40 x 48     ? comm. ?
 * 
 *
 * If the image size falls any of the above categories then the thumbnail
 * size will be as stated in the table above.
 *
 * If the image size is something else then the following rules are
 * applied.
 *
 * Very wide images with aspect ratio higher than 1.467 (= 44/30) will
 * be cropped horitzontally maintaining the aspect ratio of 1.467. 
 * In this case the thumbnail size will be [44 x 30]
 *
 * Very tall images with aspect ratio smaller than 0.625 (= 30/48) will be cropped
 * vertically maintaining the aspect ratio of 0.625.
 * In this case the thumbnail size will be [30 x 48]
 * 
 * The final rule is that if the original imate aspect ratio falls
 * in between the 0.625 and 1.467. (30/48 < ratio < 44/30)
 * 
 *   -> in this case the thumbnail size will be:
 *      [30...44]< x 48 for portrait images
 *      44 x [30...48] for landscape images
 */

class CPAlbImageFactory : public CBase, public MMdaImageUtilObserver
    {
    public:  // Constructors and destructor

        /**
         * Two-phased constructor.
         * @param aObserver (required) pointer to the observer object! 
         *
         * NOTE! The observer is REQUIRED! Otherwise you won't get notification
         * of the completion of the asynchronous operations. 
         */
        IMPORT_C static CPAlbImageFactory* NewL( MPAlbImageFactoryObserver* aObserver );

        /**
         * Destructor.
         */
        IMPORT_C virtual ~CPAlbImageFactory();

    public:
        /**
         *
         * Cancels all operations inside the factory.
         * NOTE! It is not necessary to call this method before
         * calling GetXXXAsync(..). This will be called automatically
         * if there is an operation underway.
         */
        IMPORT_C void CancelAsyncGet();

        /**
         * Retrieves original image. Success/failure conditions will be
         * signaled by the observer method. The created CFbsBitmap object will
         * be returned with the observer call:
         *      MPAlbImageFactoryObserver::MPTfoCreateComplete(...)
         *
         * @param aImageData information about source bitmap (from photoalbum folders)
         * @param aThumbBitmap target bitmap for the thumbnail, will be replaced
         * @param aDisplayMode allows setting the desired color depth for the image, 
         *                     default is 4K colors (4096).
         *                     if the thumbnail already exists it will be retrieved using the
         *                     colordepth it was previously created.
         */
        IMPORT_C void GetImageAsync( CPAlbImageData& aImageData, 
                                     TDisplayMode aDisplayMode = EColor4K );
        /**
         * Retrieves image with direct file name. Success/failure conditions will be
         * signaled by the observer method. The created CFbsBitmap object will
         * be returned with the observer call:
         *      MPAlbImageFactoryObserver::MPTfoCreateComplete(...)
         *
         * @param aFileName Full path filename of the image to load.
         * @param aThumbBitmap target bitmap for the thumbnail, will be replaced
         * @param aDisplayMode allows setting the desired color depth for the image, 
         *                     default is 4K colors (4096).
         */
        IMPORT_C void GetImageAsync( const TDesC& aFileName, 
                                     TDisplayMode aDisplayMode = EColor4K );

        /**
         * Retrieves image thumbnail. If the thumbnail does not exist it will be created
         * and stored. Success/failure conditions will be signaled by the
         * observer method MPAlbThumbnailFactoryObserver::MPTfoCreateComplete(...)
         * as well as the created CFbsBitmap object.
         *
         * @param aImageData information about source bitmap (from photoalbum folders)
         */
        IMPORT_C TBool GetThumbnailAsync( CPAlbImageData& aImageData );

        /**
         * Deletes a thumbnail (if exists). You can call this even the thumbnail does not exist.
         *
         * @param aImageData CPAlbImageData describing the photoalbum image file (folder/file)
         * @return KErrNone if no error, otherwise an error code.
         */
        IMPORT_C TInt DeleteThumbnail( CPAlbImageData& aImageData );

        /**
         * Checks if a thumbnail exists for the image.
         *
         * @param aImageData CPAlbImageData describing the photoalbum image file (folder/file)
         * @return ETrue if thumbnail exists, EFalse otherwise.
         */
        IMPORT_C TBool HasThumbnailL( CPAlbImageData& aImageData );

        /** 
         * Will try to load (internalize) a previously thumbnail bitmap from
         * the hard disk.
         * This method will leave on serious errors like the OOM situation or
         * if a connection with the file server cannot be established.
         *
         *
         * @param aImageData information about the image file, image file 
         *        name and folder.
         * @param aBitmap Target EPOC CFbsBitmap which will be replaced 
         *        by the bitmap..
         * @return (TInt) KErrNone if no error happened or an error conditon.
         *
         */
        IMPORT_C TInt LoadThumbnailL( CPAlbImageData& aImageData, 
                                      CFbsBitmap& aBitmap );

        /**
         * Crops the given bitmap according to the given rectangle.
         * After cropping the size of the image will be the size of
         * the given Rectangle and it will contain the bitmap information
         * which resided inside the given rectangle
         *
         * Before:                      After:
         * +-<aSource>-------------+
         * |.......................|
         * |.....+<aRect>----+.....|    +<aSource>--+
         * |.....|CCCCCCCCCCC|.....| -> |CCCCCCCCCCC|
         * |.....|CCCCCCCCCCC|.....|    |CCCCCCCCCCC|
         * |.....+-----------+.....|    +-----------+
         * |.......................|
         * |.......................|
         * +-----------------------+
         *
         * If the source bitmap is smaller than the crop rectangle a panic
         * will occur (EPanicCropPreCond_Boundaries). Also if the source
         * bitmap size is (0,0)
         * 
         * @aSource source bitmap to be cropped
         * @aRect rectangle to crop. Must be inside boundaries of aSource
         * 
         */
        IMPORT_C void DoCropBitmapL( CFbsBitmap& aSource, TRect& aRect );

        /**
         * Synchronous call to create a thumbnail from a bitmap that
         * is passed as a parameter. This is much faster than 
         * GetThumbnailAsync() because no sourceformat->EPOCformat
         * bitmap conversions need to be done. 
         * NOTE! The bitmap will be modified so if you need to retain
         * it, take a copy. 
         *
         * @param aImageData Which photoalbum image gets the thumbnail
         * @param aBitmap the source bitmap to be scaled down
         * @exception PANICs if source bmp dimensions are 0.
         * @exception Can leave on common errors like OOM 
         */
        IMPORT_C void CreateThumbFromBitmapL( CPAlbImageData& aImageData, 
                                              CFbsBitmap& aBitmap );

        /**
         * Creates a thumbnail from a given bitmap. Note that the bitmap
         * given as a parameter will be modified. The resulted thumbnail
         * will replace the original bitmap.
         *
         * @param aBitmap the bitmap that will be processed. 
         * @param aBitmap the result will also be returned here!
         */
        IMPORT_C void CreateThumbnailFromBitmapL( CFbsBitmap& aBitmap );

    private:

        CFbsBitmap* CreateThumbFromBitmapWithNoSaveLC( CFbsBitmap& aBitmap );

    protected:  // Functions from MMdaImageUtilObserver

        /**
         * Observer method for the Media Server operations.
         * Not called by anything in this class.
         *
         * @param aError error number, e.g. KErrNone if an error occured
         * @see MMdaImageUtilObserver.
         */
        void MiuoCreateComplete( TInt aError );

        /**
         * Observer method for the Media Server operations.
         * Gets called when the CMdaImageFileToBitmapUtility has opened
         * an image file.
         *
         * @param aError error number, e.g. KErrNone if an error occured
         * @see MMdaImageUtilObserver.
         */
        void MiuoOpenComplete( TInt aError );

        /**
         * Observer method for the Media Server operations.
         * Gets called when the CMdaImageFileToBitmapUtility or 
         * CMdaScaler has finished an operation.
         *
         * @param aError error number, e.g. KErrNone if an error occured
         * @see MMdaImageUtilObserver.
         */
        void MiuoConvertComplete( TInt aError );
        
    private:
        /**
         * Wraps leavable functions in one method so TRAPing is reduced
         * Called by MiuoOpenComplete() only.
         */
        void DoHandleOpenCompleteL();

        /**
         * Wraps leavable functions in one method so TRAPing is reduced
         * Called by MiuoConvertComplete() only.
         */
        void DoHandleConvertCompleteL();

        /**
         * Load/convert and process a bitmap contained in a bitmap
         * file. 
         *
         * @param aImageData Image file to process, name/folder
         * @see CPAlbImageData
         */
        TBool GetAsyncL( CPAlbImageData& aImageData );

        /**
         * C++ default constructor.
         */
        CPAlbImageFactory();

        /**
         * By default Symbian OS constructor is private.
         */
        void ConstructL( MPAlbImageFactoryObserver* aObserver );

        /**
         * Panic helper
         */
        void Panic(TInt aReason);

        /**
         * All exits through the factory will happen through this method. It
         * Calls the observer method from (MPAlbImageFactoryObserver)
         *   MPTfoCreateComplete
         *       ( CPAlbImageFactory* aObj, TInt aError, CFbsBitmap* aBitmap )
         *
         * In case of an error (aError != KErrNone) it will return NULL
         * as aBitmap. Otherwise a newly created CFbsBitmap is returned
         * to the observer which MUST BE TAKEN CARE OF! 
         *
         * @param aError error number or KErrNone for no error.
         */
        void NotifyObserver( TInt aError );

        /**
         * Will save (externalize) the thumbnail bitmap to the correct folder.
         * Each thumbnail image is a separate file and the directory structure
         * is kept similar to the source image folders.
         * NOTE! This method will leave on any error condition!
         *
         * @param aImageData information about the image file, image file 
         *        name and folder.
         * @param aBitmap Source Symbian OS CFbsBitmap to externalize.
         * @return (TInt) KErrNone if no error happened
         */
        TInt SaveThumbnailL( CPAlbImageData& aImageData, CFbsBitmap& aBitmap );

        /**
         * Set thumbnail attributes. Size and Colordepth
         * NOTE! If thumbnail has already been created then its attributes will
         * be used. These settings affect only when the thumbnail is being
         * created!
         *
         * @param aSize Size of the generated thumbnail
         * @param aMode color depth of the generated thumbnail, default EColor4K.
         */
        void SetThumbnailAttributes( TSize aSize, TDisplayMode aMode = EColor4K );

        /**
         * Set the size of the thumbnail (iThumbnail) according to the original
         * image. The rules are described in the description of this class.
         * 
         * @param aBitmap bitmap whose size is examined.
         * @return ETrue if the thumbnail size was modified
         */
        TBool SetThumbnailSizeFromSourceBitmap( CFbsBitmap& aBitmap, 
                                                CFbsBitmap& aThumbnail );

        /**
         * Processes the given bitmap. This is used to crop very
         * tall and very wide images. 
         * Image is very tall when aspect ratio < 0.625.
         * Image is very wide when aspect ratio > 1.467
         * These ratios come from the mimimun sizes of the thumbnail
         * 44/30 = 1.467
         * 30/48 = 0.625
         *
         * @param aBitmap a bitmap which is processed and cropped
         */
        void CropAndProcessBitmapL( CFbsBitmap& aBitmap, 
                                    CFbsBitmap& aThumbnail );

        // By default, prohibit copy constructor, no implementation
        CPAlbImageFactory( const CPAlbImageFactory& );

        // Prohibit assigment operator, no implementation
        CPAlbImageFactory& operator= ( const CPAlbImageFactory& );

    private:    // Data

        enum TThumbnailPanics
            {
            EPanicNone = 0,
            EPanicPreCond_GetAsyncL,
            EPanicPreCond_NoObserver,
            EPanicCropPreCond_Boundaries,
            EPanicCropPreCond_BitmapSize,
            EPanicCropPostCond_BitmapSize,
            EPanicPostCond_PointerNotNULL,
            EPanicNullPointer,
            EPanicGeneral
            };

        // Internal states of the factory
        enum TThumbfactOperations 
            {
            EPTfNoOperation = 0,
            EPTfLoading,
            EPTfConverting,
            EPTfScaling,
            EPTfDirectBitmapProcess
            };

        // Fileserver object
        RFs iFs;
        // Owns: MDA image file loader utility
        CMdaImageFileToBitmapUtility* iLoader;

        // Owns: CPalbImageData, folder/imagefile
        CPAlbImageData* iImageData;
        
        // Owns: CFBsBitmap for conversion
        CFbsBitmap* iBitmap;
        
        // Owns: buffer for image name
        HBufC* iNameBuffer;
        
        // References: CFBsBitmap for thumbnail
        CFbsBitmap* iThumbnail;
        
        // References: Observer pointer
        MPAlbImageFactoryObserver* iObserver;
        
        // Frame information for the loaded image file
        TFrameInfo iFrameInfo;
        
        // Displaymode indicator
        TDisplayMode iDisplayMode;
        
        // size of the generated thumbnail
        TSize iThumbSize;
        
        // Internal error indicator
        TInt iError;
        
        // Internal state indicator (TThumbfactOperations)
        TInt iState;
        
        // internal operation flag, ETrue if fetching thumbnail in proggress
        TBool iFetchThumbnail;
  
    };

#endif // __PALBIMAGEFACTORY_H

// End of File
