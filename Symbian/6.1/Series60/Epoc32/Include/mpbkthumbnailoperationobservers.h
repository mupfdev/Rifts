/*
* ============================================================================
*  Name     : MPbkThumbnailOperationObservers.h
*  Part of  : PbkView.dll
*
*  Description:
*      Phonebook asyncronous thumbnail operation observer interfaces.
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

#ifndef __MPbkThumbnailOperationObservers_H__
#define __MPbkThumbnailOperationObservers_H__

//  INCLUDES
#include <e32def.h>

//  FORWARD DECLARATIONS
class MPbkThumbnailOperation;
class CFbsBitmap;
class CPbkImageDataWithInfo;

// CLASS DECLARATION

/**
 * Observer interface for CPbkThumbnailManager get operation.
 * Only one of the event callbacks is called once by the operation.
 *
 * @see CPbkThumbnailManager::GetThumbnailAsyncL
 */
class MPbkThumbnailGetObserver
    {
    public:
        /**
         * Called when thumbnail loading is completed.
         *
         * @param aOperation    the completed operation.
         * @param aBitmap       The loaded bitmap. Callee is responsible of 
         *                      the bitmap.
         */
        virtual void PbkThumbnailGetComplete
            (MPbkThumbnailOperation& aOperation, CFbsBitmap* aBitmap) =0;

        /**
         * Called if the thumbnail loading fails.
         *
         * @param aOperation    the failed operation.
         * @param aError        error code of the failure.
         */
        virtual void PbkThumbnailGetFailed
            (MPbkThumbnailOperation& aOperation, TInt aError) =0;
    };


/**
 * Observer interface for CPbkThumbnailManager get image operation.
 * Only one of the event callbacks is called once by the operation.
 *
 * @see CPbkThumbnailManager::GetThumbnailImageAsyncL
 */
class MPbkThumbnailGetImageObserver
    {
    public:
        /**
         * Called when thumbnail loading is completed.
         *
         * @param aOperation    the completed operation.
         * @param aImageData    The thumbnail image. Caller is responsible
         *                      of the object.
         */
        virtual void PbkThumbnailGetImageComplete
            (MPbkThumbnailOperation& aOperation, CPbkImageDataWithInfo* aImageData) =0;

        /**
         * Called if the thumbnail loading fails.
         *
         * @param aOperation    the failed operation.
         * @param aError        error code of the failure.
         */
        virtual void PbkThumbnailGetImageFailed
            (MPbkThumbnailOperation& aOperation, TInt aError) =0;
    };


/**
 * Observer interface for CPbkThumbnailManager set operations.
 * Only one of the event callbacks is called once by the operation.
 *
 * @see CPbkThumbnailManager::SetThumbnailAsyncL
 */
class MPbkThumbnailSetObserver
    {
    public:
        /**
         * Called when thumbnail setting is completed.
         *
         * @param aOperation    the completed operation.
         */
        virtual void PbkThumbnailSetComplete
            (MPbkThumbnailOperation& aOperation) =0;

        /**
         * Called if the thumbnail setting fails.
         *
         * @param aOperation    the failed operation.
         * @param aError        error code of the failure.
         */
        virtual void PbkThumbnailSetFailed
            (MPbkThumbnailOperation& aOperation, TInt aError) =0;
    };

#endif // __MPbkThumbnailOperationObservers_H__

// End of File
