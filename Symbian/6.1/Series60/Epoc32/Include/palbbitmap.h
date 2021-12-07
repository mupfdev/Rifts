/*
 * ============================================================================
 *  Name     : PAlbBitmap.h
 *  Part of  : PhotoAlbum
*
 *  Description:
 * Class PAlbBitmap, encapsulates CFbsBitmap and IML loading
 *
*       This class is used to create Symbian OS CFbsBitmaps from gfx file types supported
 * by Media Server. Internally this class uses IML for loading and other
 * operations like zoom, rotate.
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

#ifndef __PalbBitmap_h
#define __PalbBitmap_h

// INCLUDE FILES
#include <bldvariant.hrh>
#include <MdaImageConverter.h>
#include <f32file.h>


class MPAlbFrameProcessor;
class MPAlbAnimLoaderObserver;

// CLASS DEFINITION
/**
 * Class PAlbBitmap, encapsulates CFbsBitmap and IML loading
 *
 * This class is used to create Symbian OS CFbsBitmaps from gfx file types supported
 * by Media Server. Internally this class uses IML for loading
 * format conversion and other operations like zoom, rotate.
 *
 * All scaling is now done using BITGDI for much faster operation.
 *
 * Supports animation.
 *
 */
class CPAlbBitmap : 
    public CBase, 
    public MMdaImageUtilObserver
    {
    private:
        /**
         * A CBase derived cleanupitem that is used to preserve the internal
         * state when a leavable operation is called.
         */
        class CPABCleanupItem : public CBase
            {
            public:
                /**
                 * Public constructor for the CleanupItem
                 *
                 * @param aObj The object to be cleaned up on destruction
                 * @param aState Internal state to set for aObj on destruction
                 */
                CPABCleanupItem( CPAlbBitmap* aObj, TInt aState = EPBAsIdle );

                /**
                 * Destructor
                 */
                virtual ~CPABCleanupItem();
            private: 
                /**
                 * Default constructor can not be used to instantiate this.
                 */
                CPABCleanupItem() { };
            private: // data
                /// Ref: object which state will be restored on destruction
                CPAlbBitmap* iObj;
                /// State to restore
                TInt iState;
            };

    public:
        friend CPABCleanupItem;
        /**
         * Internal states of the CPAlbBitmap class
         */
        enum TPABState
            {
            EPBAsIdle = 0,  // doing nothing
            EPBAsLoad,      // Loading/converting a bitmap from file
            EPBAsZoom,      // Doing a scale operation
            EPBAsRotate     // Rotating
            };

        /**
         * Used when the image is internally rotated. Describes the rotation
         * angle
         */
        enum TPABRotationAngle
            {
            EPBRot0 = 0,    // 0 degrees rotated
            EPBRot90,       // 90 degrees rotated
            EPBRot180,      // 180 degrees rotated
            EPBRot270       // 270 degrees rotated
            };

        /**
         * Internal panic codes
         */
        enum TPABPanicReason
            {
            EPanicNullPointer = 1,
            EPanicGeneral
            };

    public: // construction
        /**
         * Public NewL constructor (first phase).
         * @param aFileName descriptor containing full path to the image
         * @param aDepth (default EColor4K) color depth for target bmp
         *
         * Please note: The parameter aDepth defines the Maximum color depth
         * of the produced bitmap! If the loaded bitmap has less colors its
         * color depth will be used!
         */
        IMPORT_C static CPAlbBitmap* NewL(
            const TDesC& aFileName, 
            const TDisplayMode& aDepth = EColor16M);
        /**
         * Destructor
         */
        IMPORT_C virtual ~CPAlbBitmap();

    public:
        /**
         * Some operations like BitmapL, BitmapSizeL can cause a longer wait
         * using this method you can check if such operation is in place!
         * @return ETrue if the object is in use. 
         */
        IMPORT_C TBool IsBusy() const;

        /**
         * @return ETrue if the bitmap is an animation
         */
        IMPORT_C TBool IsAnimation();

        /**
         * Sets the rotation angle for the bitmap that is 
         * produced by the BitmapL methods.
         * @param aRotation angle for the produced bitmap.
         */
        IMPORT_C void SetRotationL( const TPABRotationAngle aRotation );

        /**
         * Sets the rotation angle for the bitmap that is 
         * produced by the BitmapL methods.
         * @param aRotation angle for the produced bitmap.
         * @deprecated 
         */
        IMPORT_C void SetRotation( const TPABRotationAngle aRotation );

        /**
         * @return the current rotation angle.
         */
        IMPORT_C TPABRotationAngle Rotation() const;

        /**
         * This will release the internal CFbsBitmap kept by this object
         * If not called by the user of this class a copy of the
         * loaded bitmap will be kept in the class (the original size
         * bitmap with rotation that was loaded from the filestore)
         * Call to save memory!
         * BitmapL will load the bitmap again when needed!
         */ 
        IMPORT_C void ReleaseBitmap();

        /**
         * This method will return the size of the bitmap currently
         * owned by the instance of this class. The size is returned
         * according to the rotation set with SetRotation() method.
         *
         * Note! Because the bitmap might have been loaded using
         * downscale. This method can return: 1:1 size, 1:2 size, 
         * 1:4 size or 1:8 size of the original image size.
         *
         * @return the TSize of the current bitmap 
         */
        IMPORT_C TSize BitmapSizeL();

        /**
         * @return the original size of the bitmap in the file.
         */
        IMPORT_C TSize BitmapOriginalSizeL();

        /**
         * Return the downscale ratio of the memory bitmap
         * Will return 0 if the bitmap is not valid!
         * @return the DownScale factor of the loaded bitmap
         */
        IMPORT_C TInt DownScaleRatio() const;

        /**
         * Reload a higher resolution version of the image if needed.
         * Reloads only if the aZoomRatio is higher than the downscale
         * ratio of the bitmap loaded previously with this method or with
         * BitmapL() method. If aZoomRatio is -1 and higher an 1:1 size
         * image will be loaded into memory. After 1:1 size image is already
         * loaded, nothing will happen when this method is called.
         *
         * Note, possible values are only: -8, -4, -2, -1.
         * If the parameter is smaller than -8, -8 will be used.
         * if the parameter is -1 or higher, 1 will be used.
         *
         * @param aZoomRatio Zooming ratio, negative causes downscale.
         */
        IMPORT_C void ReloadBitmapUsingDownscaleL( TInt aZoomRatio );

        /**
         * @return the filename that was set during construction
         */
        IMPORT_C const TDesC& FileName() const;

        /**
         * @return the displaymode that was set during construction !
         */
        IMPORT_C const TDisplayMode& DisplayMode() const;

        /**
         * Create a bitmap as large as aTgtBitmap. A source rectangle
         * aSourceRect is cut out from the original bitmap and it is scaled
         * up/down to the size of aTgtBitmap. 
         *
         * If aRetainAspect is ETrue, the method will retain the aspect
         * ratio of aSourceRect while scaling to the aTgtBitmap. This might
         * cause a change in the size of aTgtBitmap. 
         *
         * By using negative values in aZoomRatio you can cause the loading
         * operation to happen faster. he higher negative value (up to -8)
         * the faster loading operation. 
         * If the bitmap is large, and you require a small version of it
         * use the aZoomRatio parameter:
         *
         * -8 = 1:8 size image will be loaded in memory
         * -4 = 1:4 size image will be loaded in memory
         * -2 = 1:2 size image will be loaded in memory
         * Higher than -2 = original size image will be loaded
         *
         * Note. On first call, and when the aZoomRatio changes from lower
         * negative values (e.g. -8) to higher negative values (e.g. -2)
         * this method will LOAD the bitmap from the file specified in 
         * the constructor! The aZoomFactor will be used as a downscale
         * factor.
         * However, if the value changes from smaller negative value 
         * (e.g. -2) to higher (e.g. -8) it will NOT cause a reload because
         * the previously used highest resolution version of the image 
         * will be used as a source bitmap.
         *
         * @param aSourceRect rectangle defining the area to cut from the bitmap
         * @param aTgtBitmap target bitmap reference.
         * @param aZoomRatio required zoomratio. Read description!
         * @param aRetainAspect (default ETrue) retain aspect ration during scale
         */
        IMPORT_C void BitmapL(
            const TRect& aSourceRect, 
            CFbsBitmap& aTgtBitmap, 
            TInt aZoomRatio = 1,
            TBool aRetainAspect = ETrue );

        /**
         * This is similiar to the above BitmapL() method, except you can also
         * get the mask with this.
         *
         * @param aSourceRect rectangle defining the area to cut from the bitmap
         * @param aTgtBitmap target bitmap reference.
         * @param aTgtBitmapMask target bitmap reference.
         * @param aZoomRatio required zoomratio. Read description!
         * @param aRetainAspect (default ETrue) retain aspect ration during scale
         */
        IMPORT_C void BitmapL(
            const TRect& aSourceRect, 
            CFbsBitmap& aTgtBitmap,
            CFbsBitmap& aTgtBitmapMask,
            TInt aZoomRatio = 1,
            TBool aRetainAspect = ETrue );

        /**
         * Get a frame from the bitmap.
         *
         * Note! This method works only if you load the frames sequentially
         * starting from frame 0 (aFrameId). Load frames incrementing aFrameId
         * until the method returns EFalse.
         *
         * If you call BitmapL method before the whole animation is loaded
         * you will loose the state and must restart from frame 0!
         *
         * @param aSourceRect Rectangle defining the area to cut from source
         * @param aTgtBitmap Target bitmap initialized having the desired size.
         * @param aTgtMaskBitmap Target mask bitmap
         * @param aFrameInfo Will be replaced by the frameinfo from frame
         * @param aFrameId Which frame to load from the bitmap. 
         * @param aRetainAspect if ETrue scaling will retain aspect ratio
         * @return ETrue if there are more frames to load.
         */
        IMPORT_C TBool GetAnimFrameWithMaskL( const TRect& aSourceRect, 
            CFbsBitmap& aTgtBitmap,
            CFbsBitmap& aTgtMaskBitmap,
            TFrameInfo& aFrameInfo,
            TInt aFrameId = 0,
            TBool aRetainAspect = ETrue);

        /**
         * Bitmaps having smaller color depth will be loaded using the
         * depth set using this method.
         *
         * @param aDisplayMode mimimum colordepth to use for internal bitmaps
         */
        IMPORT_C void SetMinimumLoadingDepth(const TDisplayMode aDisplayMode);

        /**
         * Bitmaps having larger color depth will be loaded using the
         * depth set using this method.
         *
         * @param aDisplayMode maximum colordepth to use for internal bitmaps
         */
        IMPORT_C void SetMaximumLoadingDepth(const TDisplayMode aDisplayMode);

        /**
         * This method can be used to get a optimum loading size for the bitmap.
         * Media server has the ability to load bitmaps by directly downscaling
         * them while loading. Bitmaps can be loaded with 1, 2, 4 or 8 times
         * downscaling. Use this method to get the size that you need to pass
         * to media server depending on the image size you need.
         *
         * e.g. You have a bitmap that has a size of 640x480
         *      You need to produce a bitmap with size 44x48
         * calling this method returns the maximum downscaled size: 80, 60.
         * Using this size (80x60) you get the fastest loading speed and less
         * usage of memory when you load the bitmap in memory. 
         *
         * This method also handles the needed rounding if the original size 
         * can not be divided evenly!
         *
         * @param aOriginalSize the size of the unscaled bitmap
         * @param aNeededSize the needed size
         * @return a optimal loading size that can be given to media server IML
         */
        IMPORT_C static TSize OptimizedLoadSize(
            const TSize& aOriginalSize, 
            const TSize& aNeededSize );

        /**
         * Scale bitmap using linear scaling from BITGDI
         * @param aSource Defines source bitmap
         * @param aTarget Defines target bitmap, will be replaced
         * @param aSourceRect Defines source rectangle taken from aSource
         * @param aRetainAspect If ETrue, will retain the aspect ratio 
         */
        IMPORT_C static void ScaleBitmapL(
            const CFbsBitmap& aSource, 
            CFbsBitmap& aTarget,
            const TRect& aSourceRect,
            TBool aRetainAspect = ETrue);

        /**
         * This method will fit the size aSrc into second size aTgt
         * while retaining the aspect ratio of aSrc. The resulted
         * size might be smaller than aTgt but have the same aspect
         * ratio (aSrc.iWidth / aSrc.iHeight) as the aSrc.
         *
         * @param aSrc the size that will be fitted to aTgt
         * @param aTgt target size that will be used in comparison
         * @return new size
         */
        IMPORT_C static TSize Fit( const TSize& aSrc, const TSize& aTgt );

        /**
         * Set the image enhancement and dithering (IETD) on or off
         * @param aEnhance if ETrue will enhance the image using IETD
         */
        IMPORT_C void SetEnhancementAndDithering(TBool aEnhance);



    public: // public but not exported methods
        /**
        * Release bitmap loader
        */
        void ReleaseLoader();

        /**
         * Cancel the currently on going operation, if any.
         */
        void CancelOperation();

        /**
         *
         * @param aFrameInfo refernce to a frameinfo object
         * @return TDisplayMode depending on the frameinfo
         */
        static TDisplayMode SetCorrectDisplayMode(
            TFrameInfo& aFrame, 
            const TDisplayMode iMaxMode,
            const TDisplayMode iMinMode);

        /**
         * Divides integers aVal with aDiv and adds one to the result 
         * if the divide operation results quotient. 
         * @param aVal value to divide
         * @param aDiv aVal will be divided by this value.
         * @return aVal/aDiv or aVal/aDiv+1 if aVal%aDiv>0]
         */
        static TInt Ceil(const TInt aVal, const TInt aDiv);

        /**
         * Divides aSize dimensions by aDiv and rounds the result up
         * if necessary!
         * @return aSize dimensions divided by aDiv. 
         */
        static TSize SizeDividedByValueAndCeil(
            const TSize& aSize, 
            const TInt aDiv);


    private: // from MMdaImageUtilObserver, observer methods for mda
        void MiuoCreateComplete(TInt aError);
        void MiuoOpenComplete(TInt aError);
        void MiuoConvertComplete(TInt aError);

    private: // constructors
        /**
         * default constructor private.
         */
        CPAlbBitmap() {};

        /**
         * Symbian OS second phase constructor
         * @param aFileName descriptor containing full path to the image
         * @param aDepth (default EColor4K) color depth for target bmp
         */
        void ConstructL(const TDesC& aFileName, const TDisplayMode& aDepth);

        /**
         * no implementation
         */
        CPAlbBitmap(const CPAlbBitmap& aObj);

        /**
         * no implementation
         */
        const CPAlbBitmap& operator=(const CPAlbBitmap& aObj);

    private: // private methods
        /**
         * Panic helper method
         * @param aReason error code telling a panic reason
         */
        static void Panic(TInt aReason);

        /**
         * Return (and LOAD if necessary) the bitmap from file
         * calls LoadBitmapL(..).
         * @return CFbsBitmap pointer
         */
        CFbsBitmap* BitmapL(const TSize& aTgtBitmapSize);

        /**
         * Load a bitmap from the file that this object points to.
         * multiple frames can be loaded if the file is an animation
         * The loading must always start from frame 0 and the caller
         * can see from the return boolean if more frames exist after 
         * the current one. 
         *
         * @param aSizeOnly only get the size of the bitmap in the file
         * @param aGetMask if ETrue loads the mask also (to iBitmapMask)
         * @param aFrameId the frame number to load (if multiple frames)
         * @return ETrue if the file contains more frames after aFrameId
         */
        TBool LoadBitmapL( 
            TSize aTgtBitmapSize,
            const TBool aSizeOnly = EFalse, 
            const TBool aGetMask = EFalse, 
            const TInt aFrameId = 0 );

        /**
         * Rotates the bitmap given as a parameter
         * @param aRotation rotation angle (TPABRotationAngle)
         * @param aBitmap  bitmap to be rotated
         */
        void RotateBitmapL(TPABRotationAngle aRotation, 
            CFbsBitmap& aBitmap, CFbsBitmap* aMask);

        /**
         * Beings waiting an asynchronous request to complete. 
         * Calls CActiveScheduler::Start() unless it was started already by
         * this object.
         * NOTE! There must always be a EndActiveWait() at some point 
         * if BeginActiveWait() was called. 
         */
        void BeginActiveWait();

        /**
         * Ends waiting an asynchronous request to complete. 
         * Calls CActiveSceduler::Stop() if BeginActiveWait() was 
         * called previously. 
         */
        void EndActiveWait();




    public:
        /**
         * Loads all frames from image file (animated gif)
         */
        void LoadFramesL();

        /**
         * Sets frame processor for frame loading.
         * The prosessor is called after each frame is loaded
         */
        void SetLoaderProcessor( MPAlbFrameProcessor* aProcessor );

        /**
         * Sets observer for frame loading.
         * The prosessor is when frame loading is started, ended or canceled
         * Also called when each frame is loaded
         */
        void SetLoaderObserver( MPAlbAnimLoaderObserver* aObserver );

        /**
         * Cancels frame loading if in progress
         */
        void FrameLoaderCancel();

    private:
        /**
         * Initializes the frame loader
         */
        void InitFrameLoaderL();

        /**
         * Handles frame loader state changes
         */

        void DoFrameLoaderStateL();

        /**
         * Handles frame loader completion
         */
        void FrameLoaderComplete();

        /**
         * Loads the next frames
         */

        void LoadFrameL();

        /**
         * Processes loaded frame and calls MPAlbFrameProcessor if set
         */
        void ProcessFrameL();

    private: // data

        // Internal bitmap for frameloader
        CFbsBitmap*                 iFrameLoaderFrame;
        
        // Internal bitmap mask for frameloader
        CFbsBitmap*                 iFrameLoaderFrameMask;
        
        // Internal frameinfo for frameloader
        TFrameInfo                  iFrameLoaderFrameInfo;
        
        // Internal frame number counter for frameloader
        TInt                        iFrameLoaderFrameNumber;
        
        // observer pointer
        MPAlbAnimLoaderObserver*    iFrameLoaderObserver;

        // processor pointer
        MPAlbFrameProcessor*        iFrameLoaderProcessor;

        // state indicator for frameloader
        TInt iFrameLoaderState;

        // different internal states for frameloader
        enum TAnimationLoaderState
            {
            EFrameLoaderIdle,
            EFrameLoaderLoadFrame,
            EFrameLoaderProcessFrame,
            EFrameLoaderLoadCompleted
            }; 

        /// Own: file to bitmap loader
        CMdaImageFileToBitmapUtility* iLoader;

        /// Own: bitmap scaler
        CMdaBitmapRotator* iRotator;

        /// Own: bitmap object
        CFbsBitmap* iBitmap;

        /// Own: Bitmap mask
        CFbsBitmap* iBitmapMask;

        /// Own: file name to the bitmap
        HBufC* iFileName;

        /// Own: Flag determining if CActiveSceduler::Start() was called'
        TBool iSizeIsKnown;

        /// Own: Display Mode 
        TDisplayMode iDisplayMode;

        /// Own:
        TDisplayMode iMimimumDisplayMode;

        /// Own:
        TDisplayMode iMaximumDisplayMode;

        /// Own: Frame information
        TFrameInfo iFrameInfo;

        /// Own: Frame information
        TFrameInfo iNextFrameInfo;

        /// Own: Internal error code
        TInt iError;

        /// Own: internal state, see TPABState
        TInt iState;

        /// Own: FrameId, frame number we are loading
        TInt iFrameId;

        /// Own: rotation angle
        TPABRotationAngle iRotation;

        /// Own: Animation flag, ETrue if animation!
        TBool iAnimation;

        /// Own: the original 1:1 size of the bitmap
        TSize iOriginalBitmapSize;

        /// Own: If bitmap was loaded, this tells the used DSR
        TInt iDownscaleRatio;

        /// Own: If ETrue loaded image will be enhanced using IETD
        TBool iEnhanceMode;

        /// Own: this will be used to synchronize the operations
        CActiveSchedulerWait iWait;
    };

#endif // _PAlbBitmap_h

// End of File
