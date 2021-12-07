/*
* ============================================================================
*  Name     : RCameraServ 
*  Part of  : CameraServ
*
*  Description:
*      Implements the Camera server session resource class on the client side
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef __CAMERA_SERV__
#define __CAMERA_SERV__

//  INCLUDES
#include <e32base.h>

// FORWARD DECLARATIONS
class CFbsBitmap; 

// CLASS DEFINITIONS

/**
 * RCameraServ
 *
 * Client side session class for connecting to the Camera Server.
 * RCameraServ provides the methods for connecting to the server, turning the power
 * of the camera HW on/off, setting the lighting conditions and image quality and
 * finally getting an image from the server. Methods taking a TRequestStatus object
 * as a parameter are asynchronous, so that application can stay responsive while
 * the server is processing the request. 
 */

class RCameraServ : public RSessionBase  
    {
    public:
        /**
        * Legal values for lighting setting. 
        * (ELightingNormal = normal lighting conditions
        *  ELightingNight = dark lighting conditions).
        */
        enum TLighting
            {
            ELightingNormal,
            ELightingNight
            };

        /**
        * Legal values for image quality setting.
        * (EQualityHigh = VGA,24bit 
        *  EQualityLow = QQVGA,12bit).
        */
        enum TImageQuality
            {
            EQualityHigh, 
            EQualityLow 
            };

        /**
        * C++ default constructor.
        */
        IMPORT_C RCameraServ();

        /**
        * C++ default destructor.
        */
        IMPORT_C virtual ~RCameraServ();


        /**
        * Sets the lighting conditions (normal/night).
        * @param aLightCondition The lighting condition to use for taking images.
        * @return TInt One of Symbian OS standard error codes.  
        */
        IMPORT_C TInt SetLightingConditions( const TLighting aLightCondition );


        /**
        * Sets the image quality (high = VGA,24bit / low = QQVGA,12bit).
        * @param aQuality The quality to use.
        * @return TInt One of Symbian OS standard error codes.
        */
        IMPORT_C TInt SetImageQuality( const TImageQuality aQuality );


        /**
        * Creates a connection to the Camera Server.
        * @return TInt One of Symbian OS standard error codes.
        */
        IMPORT_C TInt Connect();

        /**
        * Turns the camera HW's power on. Note that this takes at most a few seconds
        * because the camera settings are initialized after it is turned on.
        * The camera is also automatically turned off after a few minutes if
        * it is not used. 
        * @param aStatus Request status that contains one of Symbian OS 
        * standard error codes after the request is completed.
        * @return void
        */
        IMPORT_C void TurnCameraOn( TRequestStatus& aStatus );

        /**
        * Turns the camera HW's power off.
        * @return TInt One of Symbian OS standard error codes.
        */
        IMPORT_C TInt TurnCameraOff();

        /**
        * Gets an image from the camera. The image is taken with parameters
        * set by SetImageQuality() and SetLightingConditions(). The default
        * settings are EQualityHigh and ELightingNormal respectively. Camera
        * Server will call Create() for the bitmap with correct image width,
        * height and bit depth so user only needs to instantiate a new bitmap 
        * and pass a reference to it as a parameter.
        * @param aStatus Request status that contains one of Symbian OS 
        * standard error codes after the request is handled.
        * @param aBitmap A reference to a bitmap that contains the image after the
        * request is completed.
        * @return void
        */
        IMPORT_C void GetImage( TRequestStatus& aStatus, CFbsBitmap& aBitmap );
        
        /**
        * Returns the version of the Camera Server against which the client was
        * linked.
        * @return TVersion Version that the client was linked against.
        */
        IMPORT_C TVersion Version() const;


        // Unused, reserved for future expandability
        IMPORT_C void ReservedFunction1();
        IMPORT_C void ReservedFunction2();
        IMPORT_C void ReservedFunction3();
        IMPORT_C void ReservedFunction4();
        
    private:
        TImageQuality iImageQuality;
    };

#endif //__CAMERA_SERV__

// End of File
