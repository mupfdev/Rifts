/*
* ============================================================================
*  Name     : PAlbImageRecognizer.h
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

#ifndef __PALBIMAGERECOGNIZER_H
#define __PALBIMAGERECOGNIZER_H

// INCLUDE FILES
#include <bldvariant.hrh>
#include <mda\client\recognizer.h>
#include <MdaImageConverter.h>

/**
 * This class implements an image recognizer using IML CMdaRecognizer
 *
 * Basic usage:
 * CPAlbImageRecognizer *iRecog = CPAlbImageRecognizer::NewL();
 * if(KImageFormatJPEG == iRecog->TryRecognizeL(_L("test.jpg")) )
 *     {
 *     RDebug::Print(_L("Wow, this really is a JPEG picture"));
 *     }
 * delete iRecog;
 *
 * If the method TryRecognizeL() returns KImageFormatUnknown this doesn't mean
 * that the image format is unknown. IML might have a new plugin installed.
 * For this reason there is a way to get the MIME string originating from the
 * MediaServer.
 *
 * After calling TryRecognizeL() you can get the actual MIME string by using
 * the the method MimeString().
 *
 */

class CPAlbUtImageRecognizer;

class CPAlbImageRecognizer : public CBase 
    {
    public:

        /// Enumerations for image formats
        enum EImageFormatId
            {
            KImageFormatPNG=0,
            KImageFormatTIFF,
            KImageFormatGIF,
            KImageFormatMBM,
            KImageFormatBMP,
            KImageFormatJPEG,
            KImageFormatWBMP,
            KImageFormatOTA,
            KImageFormatWMF,
            KImageFormatUPF,
            KImageFormatUnknown,
            KImageFormatERROR,
            KImageFormatNotSupported
            };

    public: // Constructors

        /**
         * Public first phase constructor
         * @return a pointer to the new instance
         */
        IMPORT_C static CPAlbImageRecognizer* NewL();

        /**
         * destructor
         */
        IMPORT_C ~CPAlbImageRecognizer();

    public: // methods

        /**
         * Try to recognize an image file. On error it returns KImageFormatERROR
         * and if the image format can not be identified it returns KImageFormatUnknown
         *
         * @param aFileName Image file name
         * @return Value for image format (EImageFormatId)
         */
        IMPORT_C TInt TryRecognizeL( const TDesC& aFileName );

        /**
         * Get Mime string for image format (for example: "image/jpeg")
         *
         * @return a reference to the mimestring describing the image format
         */
        IMPORT_C const TDesC8& MimeString();

        /**
         * What kind of recognition was used to determine the image format
         * (filename, file header or none).
         *
         * @return CMdaRecognizer::TMatchMethod
         */
        IMPORT_C CMdaRecognizer::TMatchMethod MatchMethod() const;

        /**
         * Get file information of file, including size and modification time.
         *
         * @param aFilename filename to be examined
         * @param aTime reference to TTime object for storing the modification time
         * @param aSize reference to TInt for storing the file size
         * @return KErrNone if no error happened, otherwise the error code
         */
        IMPORT_C TInt FileInfoL( const TDesC& aFileName, 
                                 TTime& aTime, TInt& aSize );

        /**
         * Get the frame info (TFrameInfo) for the image stored in file.
         * @param aFilename filename to be examined
         * @param aFrameInfo reference to TFrameInfo object
         */
        IMPORT_C void FrameInfoL( const TDesC& aFileName, 
                                  TFrameInfo& aFrameInfo );
           /**
         * Check if the recognized file was a picture.
         * @param aFormat the format returned by TryRecognizeL(...)
         * @return ETrue if format is a picture.
         */
        IMPORT_C TBool IsPicture( TInt aFormat );

        /*
         * Check if the recognized file was a image.
         * @param aFormat the format returned by TryRecognizeL(...)
         * @return ETrue if format is an image.
         */
        IMPORT_C TBool IsImage( TInt aFormat );

    private: // private methods

        /**
         * Default constructor private
         */
        CPAlbImageRecognizer();

        /**
         * Second phase constructor - private
         */
        void ConstructL();
        
    private:

        // Real recognizer class
        CPAlbUtImageRecognizer* iReg;

    };

#endif // __PALBIMAGERECOGNIZER_H

// End of File
