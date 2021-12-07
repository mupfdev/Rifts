/*
 * ============================================================================
 *  Name     : MPAlbAnimLoaderObserver.h
 *  Part of  : PhotoAlbum
*
 *  Description:
 *   
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

#ifndef __PALBANIMATIONLOADOBSERVER_H
#define __PALBANIMATIONLOADOBSERVER_H


// INCLUDE FILES 
#include <bldvariant.hrh>
#include <MdaImageConverter.h>

// CLASS DECLARATION
class MPAlbFrameProcessor
    {
    public:
        /**
         * This method is called for each loaded animation frame to allow
         * user modification of the frame (e.g. scaling while loading the
         * animation).
         *
         * @param aBitmap reference to the frame bitmap
         * @param aMask reference to the frame bitmap mask
         * @param aFrameInfo reference to the frameinfo of the anim frame
         */
        virtual void ProcessFrameL(
            const CFbsBitmap& aBitmap,
            const CFbsBitmap& aMask,
            const TFrameInfo& aFrameInfo) = 0;
    };

/**
 * Observer interface for the animation loading states
 * Called by CPAlbAnimationLoader when loading has been cancelled
 * or when the whole animation was succesfully loaded.
 */
class MPAlbAnimLoaderObserver
    {
    public:
        /**
         * Called when animation loading is cancelled
         */
        virtual void LoadCancelled() = 0;

        /**
         * Called when animation loading is completed
         */
        virtual void LoadCompleted() = 0;

        /**
         * Called when animation loading failes
         * @param aError why the loading failed
         */
        virtual void LoadFailed( TInt aError ) = 0;
    };

#endif // __PALBANIMATIONLOADOBSERVER_H

// End of file
