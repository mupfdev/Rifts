/*
 * ============================================================================
*  Name     : PAlbImageViewerBasic.h
 *  Part of  : PhotoAlbum
*
 *  Description:
 *   ImageViewer component. Uses IML to manipulate (load, convert, rotate and
 *   scale) images.
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

#ifndef __PALBIMAGEVIEWERBASIC_H
#define __PALBIMAGEVIEWERBASIC_H

// INCLUDES
#include <bldvariant.hrh>
#include <coecntrl.h>
#include <MdaImageConverter.h>
#include <MPAlbAnimLoadObserver.h>

// FORWARD DECLARATIONS
class CPAlbBitmap;

// CLASS DECLARATION
class MPAlbAnimationObserver
    {
    public:
    // Notify events
    enum TAnimationEvent
        {
        EAnimationStarted = 1,
        EAnimationPlayed,    // event when one loop of animation is played
        EAnimationCancelled
        };

    virtual void Notify( TAnimationEvent aEvent ) = 0;
    };

/**
 * CPAlbImageViewerBasic class
 *
 * Definition of the common imageviewer component for image and GIF-animation
 * viewing.
 *
 * The class uses optimized loading of the bitmap! It uses the feature of Media
 * Server that is able to downscale the image in DCT-domain (for JPEG images,
 * but works for other formats too in API level). Media Server is able
 * to downscale images while loading using 1:2, 1:4 or 1:8 scaling.
 * For the viewing operation of images this means that the component will load
 * as much downscaled version of the bitmap as possible and needed. If
 * the initial view (Optimum View) is 1:8 then this optimized loading operation
 * will be able to do the initial view scaling automatically and no further
 * scaling is needed.
 *
 * The component keeps the biggest loaded bitmap in memory but never in larger
 * form than the original bitmap.
 *
 * When the user zooms in from the initial view a new bigger version of the bitmap
 * is loaded if needed. After 1:1 version of the bitmap is loaded all future
 * operations will be based on this memory bitmap -> No delay in operations.
 *
 * When the user zooms out the operation is always based on the biggest version
 * of the bitmap that is loaded so far. So there is no delay in the operation.
 *
 * CPAlbBitmap class is used for all operations that require bitmap manipulation:
 * Scale, Rotate, Convert etc.
 * @see CPAlbBitmap
 *
 *  Examples:
 * 1) Instantiation
 *    CPAlbImageViewerBasic* iViewer = CPAlbImageViewerBasic::NewL(this, Rect());
 *
 * 2) Loading a new image into the control
 *    iViewer->SetImageNameAndDisplaymodeL(_L("C:\\Images\\mini.jpg"), EColor4K);
 *    iViewer->LoadImageL();
 *
 *   or
 *
 * 2) iViewer->LoadImageL(_L("C:\\Images\\mini.jpg"), EColor4K);
 *    iViewer->ScaleOptimumL();
 *
 * 3) Rotation, around the center point of the visible window.
 *    RotateLeftL() and RotateRightL()
 *
 * 4) Panning, will move the center point of the window by half of the screen
 *    dimensions.
 *    PanLeft();
 *    PanRight();
 *    PanUp();
 *    PanDown();
 *
 */

class CPAlbImageViewerBasic : public CCoeControl,
                              public MPAlbAnimLoaderObserver,
                              public MPAlbFrameProcessor
    {
    public:
    /**
     * Rotation directions
     */
    enum TRotationDirection
        {
        EDirLeft = 1,
        EDirRight
        };

    /**
     * The internal states of the image viewer
     */
    enum TViewerOperation
        {
        EIvOperationNone = 0,
        EIvOperationScale,
        EIvOperationRotate,
        EIvOperationLoad,
        EIvOperationConvert,
        EIvOperationLoadAnimation,
        EIvOperationPlayAnimation
        };

    /**
     * Panic reasons
     */
    enum TViewerPanicReason
        {
        EIvPanicNone = 0,
        EIvPanicNullPointer,
        EIvPanicIllegalRectWidth,
        EIvPanicIllegalRectHeight
        };

    public: // Constructors and destructor

       /**
        * Public instantiator for this class.
        *
        * @param aParent    Parent control
        * @param aRect      Controls area
        * @return Pointer to the new control or NULL if control could not be instantiated
        */
        IMPORT_C static CPAlbImageViewerBasic* NewL( const CCoeControl* aParent,
                                                     const TRect& aRect );

       /**
        * Destructor.
        */
        IMPORT_C virtual ~CPAlbImageViewerBasic();

    public:

        /**
         * This method sets the filename and display mode in the control
         * Call it before issuing LoadImageL overload which does not take
         * parameters.
         *
         * @param aFileName file name of the image file to load
         * @param aDisplayMode the color depth (ie. EColor4K)
         */
        IMPORT_C void SetImageNameAndDisplaymodeL( const TDesC& aFileName,
                                                   const TDisplayMode& aDisplayMode );

        /**
         * Load and display the image file set with the method
         * SetImageNameAndDisplayModeL(...).
         *
         */
        IMPORT_C void LoadImageL();

        /**
         * Loads the image file specified in the aFileName.
         * This method returns only when the image is loaded or an error
         * happened.
         *
         * @param aFileName  Full path name for the bitmap file.
         * @param aDisplayMode the color depth of the image after
         *        load/conversion. For example, EColor4K
         * @return KErrNone if operation was succesfull
         */
        IMPORT_C TInt LoadImageL( const TDesC& aFileName,
                                  TDisplayMode aDisplayMode );

        /**
         * This method will return a pointer to the bitmap
         * contained in the control. Do not store this pointer because
         * it will get invalidated after every operation (zoom, pan, rotate etc.)
         *
         * Note! This operation will not return anything bigger than the size
         * of the control! So if you require the UNSCALED and original bitmap
         * you will need to use other means to get it. What this method returns
         * is the part of the image that is visible in the control!
         * @see FreeScaleLC
         *
         * @return Pointer to the visible part of the bitmap.
         */
        IMPORT_C CFbsBitmap* Bitmap() const;

        /**
         * @return ETrue if one displayed pixel represents one image pixel
         */
        IMPORT_C TBool ActualPixelsShown() const;

        /**
         * Returns the zoom ratio of the visible image.
         *  -x = reduced size (1:X)
         *   1 = actual pixels (1:1)
         *  +x = increased size (X:1)
         *
         * @return An integer (TInt) representing the zoom ratio of the visible image
         */
        IMPORT_C TInt ZoomRatio() const;

        /**
         * @return ETrue if image is scaled optimally (fit view, OptimumView)
         */
        IMPORT_C TBool OptimumScale() const;

        /**
         * @return ETrue if the control is doing an IML function (Loading etc).
         */
        IMPORT_C TBool IsBusy() const;

        /**
         * Scroll the viewing window
         * @param aStep size indicating the desired scroll amount (x and y)
         */
        IMPORT_C void Scroll( const TSize aStep );

        /**
         * Set the panning position (center of the visible window)
         * @param aPos center position of the window
         */
        IMPORT_C void SetPanningCenter( const TPoint aPos );

        /**
         * Pan the picture to left (move viewport to the left -> picture
         * moves right) Image is panned by half of the screen width (right
         * edge moves to the center of the window)
         */
        IMPORT_C void PanLeft();

        /**
         * Pan the picture to right
         * Image is panned by half of the screen width (left edge moves to
         * the center of the window)
         */
        IMPORT_C void PanRight();

        /**
         * Pan the picture to up
         * Image is panned by half of the screen height
         * (top edge moves to the center of the window)
         */
        IMPORT_C void PanUp();

       /**
        * Pan the picture to down
        * Image is panned by half of the screen height
        * (bottom edge moves to the center of the window)
        */
        IMPORT_C void PanDown();

        /**
         * Scales the image for optimum display so that the whole image is
         * displayed on the control. Allows 10% overshoot on borders.
         *
         * This method returns only when the image is loaded or an error
         * happened.
         */
        IMPORT_C void ScaleOptimumL();

        /**
         * Scale the image to any given size.
         *
         * This method returns only when the operation is complete or an
         * error happened.
         *
         * @param aNewSize size of the scaled image
         * @param aRetainAspectRatio if ETrue will retain the aspect ratio
         * @return Error code or KErrNone
         */
        IMPORT_C TInt FreeScaleL( TSize aNewSize, TBool aRetainAspectRatio );

        /**
         * Rotates the picture counter clockwise.
         *
         * This method returns only when the operation is complete or an
         * error happened.
         *
         */
        IMPORT_C void RotateLeftL();

        /**
         * Rotates the picture clockwise.
         *
         * This method returns only when the operation is complete or an
         * error happened.
         *
         */
        IMPORT_C void RotateRightL();

        /**
         * Increase the size of the image (Zoom In). If the zooming ratio was
         * 1:4, after this call it will be 1:2. Maximum zooming ratio is
         * 8:1
         *
         * This method returns only when the operation is complete or an
         * error happened.
         *
         */
        IMPORT_C void ZoomInL();

        /**
         * Decrease the size of the image (Zoom Out). If the zooming ratio
         * was 1:4 after this operation it will be 1:8.
         *
         * This method returns only when the operation is complete or an
         * error happened.
         *
         */
        IMPORT_C void ZoomOutL();

        /**
         * @return the size of the bitmap in the file. Original dimensions
         */
        IMPORT_C TSize UnscaledSizeL();

        /**
         * @return the size of the visible bitmap!
         */
        IMPORT_C TSize VisibleSize();

        /**
         * If this returns 1 the image is kept in memory as original size
         * -2 = 1:2
         * -4 = 1:4
         * -8 = 1:8
         * @return the downscale ratio of the bitmap in memory.
         */
        IMPORT_C TInt DownscaleRatioInMemory() const;

        /**
         * This method scales the loaded bitmap to a free size given as
         * a parameter for the call.
         * You can specify a source rectangle from the bitmap to be scaled
         * into the new size aNewSize.
         * @see UnscaledSizeL()
         *
         * Note! If the DownScaleRatio is -2 -4 or -8 this operation MIGHT
         * require loading/converting a bigger version of the bitmap!
         * @see DownscaleRatioInMemory()
         *
         * @param aSourceRect the source rectangle area to be scaled
         * @param aNewSize the target size
         * @param aRetainAspectRatio if ETrue bitmap will retain aspectraito
         */
        IMPORT_C CFbsBitmap* FreeScaleLC( const TRect& aSourceRect,
                                          const TSize& aNewSize,
                                          TBool aRetainAspectRatio=ETrue );

        /**
         * Release memory, calling this will release the internal bitmaps
         * and also the bitmap that is visible in the control!
         * Animation will be stopped and all the loaded frames will
         * be also released.
         *
         * Note, after this all operations that are done for the bitmap
         * will take longer on the first time because the internal bitmaps
         * will be reloaded!
         */
        IMPORT_C void ReleaseMemoryAndVisibleBitmap();


        /**
         * Release memory, calling this will release the internal bitmaps
         * but not the bitmap that is visible in the control!
         * Animation will be stopped and all the loaded frames will
         * be also released.
         *
         * Note, after this all operations that are done for the bitmap
         * will take longer on the first time because the internal bitmaps
         * will be reloaded!
         */
        IMPORT_C void ReleaseMemory();

        /**
         * Lock (open) the used image file to prevent modification (delete,
         * rename etc.) while the image is being viewed.
         */
        IMPORT_C void LockImageFileL();

        /**
         * Release a previously locked (opened) image file and allow
         * modification.
         * Note! Destructor will call this too.
         */
        IMPORT_C void ReleaseImageFileLock();

        /**
         * If this is called, the set observer will get notifications
         * of the animation states.
         *
         * This method also sets if the animation loops (after last frame
         * the animation restarts from the beginning). In this case
         * the animation frames will not be destroyed after the last frame
         * was displayed for the first time.
         *
         * @param aObserver the observer that will get events
         * @param aLooping looping animation is wanted!
         * @see MPAlbAnimationObserver
         */
        IMPORT_C void SetAnimationObserver( MPAlbAnimationObserver* aObserver,
                                            TBool aLooping = EFalse );

        /**
         * @return ETrue if the current image is an animation!
         */
        IMPORT_C TBool IsAnimation() const;

        /**
         * Play animation. Valid after LoadImageL(...);
         * Also check if the loaded file was actually an animation using
         * IsAnimation() method.
         *
         * If the last loaded file was not a GIF animation then this method
         * will call ScaleOptimumL() and return.
         *
         * This method can be also called after StopAnimation() to continue
         * the animation playback.
         */
        IMPORT_C void PlayAnimationL();

        /**
         * Cancel animation play if previously started. This does nothing
         * if the animation was not started and playing. Animation can not
         * be stopped while the frames are loading!
         */
        IMPORT_C void CancelAnimation();

        /**
         * Stop the animation play back. The difference to CancelAnimation
         * method is that this will not release the loaded frames. If the caller
         * wants to restart the animation it will happen faster because the
         * frames are already in the memory.
         */
        IMPORT_C void StopAnimation();


        /**
         * Set the image enhancement and dithering (IETD) on or off
         * @param aEnhance if ETrue will enhance the image using IETD
         */
        IMPORT_C void SetEnhancementAndDithering( TBool aEnhance );

        /**
         * Clear the image loader and release file lock
         */
        IMPORT_C void ReleaseImageLoader();

    private: // Private construction

       /**
        * default constructor is private, construct using NewL.
        */
        CPAlbImageViewerBasic() {};

       /**
        * Symbian OS second phase constructor.
        *
        * @param aParent    Parent control
        * @param aRect      Controls area
        */
        void ConstructL( const CCoeControl* aParent, const TRect& aRect );


    private: // from MPAlbFrameProcessor
        void ProcessFrameL( const CFbsBitmap& aBitmap,
                            const CFbsBitmap& aMask,
                            const TFrameInfo& aFrameInfo );

    private: // from MPAlbAnimLoadObserver
        void LoadCancelled();
        void LoadCompleted();
        void LoadFailed( TInt aError );

    protected: // From CoeControl

       /**
        * Notifies that the controls size has been changed.
        */
        IMPORT_C void SizeChanged();

       /**
        * Draw Control
        */
        IMPORT_C void Draw(const TRect& aRect) const;

    private: // Private image methods

        void DrawNextFrameL();

        static TInt TimerCallback( TAny* aObj );

        void DrawAnimFrameL( TInt aFrameNum );

        void Panic( TInt aReason ) const;

        void DoZoomL( TInt aZoomFactor, TPoint& aCenterPoint );

        void DoZoomInnerL( TInt aZoomFactor, TPoint& aCenterPoint );

        void CalculateZoomRect( TInt aFactor, TRect& aRectToSet,
                                const TSize& aBmpSize );

        TInt OptimumRectangle( const TSize& aBmpSize, TRect& aRectToSet );

        void ScrollL( const TSize& aStep );

        void SetPanningCenterL( const TPoint& aPos );

        void NotifyObserver( MPAlbAnimationObserver::TAnimationEvent aEvent );

        void ReleaseAnimation();

        void StartAnimationReplayL();

        /**
         * no implementation, copy constructor
         */
        CPAlbImageViewerBasic( const CPAlbImageViewerBasic& aObj );
        /**
         * no implementation, assignment operator
         */
        const CPAlbImageViewerBasic& operator=( const CPAlbImageViewerBasic& aObj );

    private:

        // File that is kept open when the image is being viewed
        RFile iFile;

        // Ref: Animation observer
        MPAlbAnimationObserver* iObserver;


        // array of bitmaps for animation
        CArrayPtrFlat<CFbsBitmap>* iAnimArray;

        // array of bitmaps for animation masks
        CArrayPtrFlat<CFbsBitmap>* iAnimMaskArray;

        // array of frameinfos for anim
        CArrayFixFlat<TFrameInfo>* iAnimFrameArray;

        // PhotoAlbum bitmap loader/processor
        CPAlbBitmap* iAlbumBitmap;

        // the visible image
        CFbsBitmap* iViewBitmap;

        // the visible image
        CFbsBitmap* iViewBitmapMask;

        CFbsBitmap* iRestoreToPreviousBitmap;

        // Timer for animation
        CPeriodic* iTimer;

        // Zooming factor, values [-8, .., 8]
        TInt iZoomFactor;

        // Zooming factor which causes the optimum view
        TInt iOptFactor;

        // Own: when animation is playing, current anim frame
        TInt iFrameNumber;

        // Own: The location from the source bitmap that is centered on view
        TPoint iPanPoint;

        // Own: Area that is visible in the view (cut from the big image)
        TRect iZoomRect;

        // Own: The frame number of last "Do Not Dispose" frame in anim
        TInt iLastLeaveInPlaceFrame;

        // Own: ETrue if image is viewed in Optimum View (fits to view)
        TBool iOptimumView;

        // Own: Indicates if the the caller wants a looping anim
        TBool iLoopingAnimation;

        // Own:
        TDisplayMode iDisplayMode;

        // Own:
        TBool iEnhanceMode;

    };

#endif // __PALBIMAGEVIEWERBASIC_H

// End of File
