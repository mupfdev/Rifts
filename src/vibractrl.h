/*
* ==============================================================================
*  Name        : VibraCtrl.h
*  Part of     : VibraControl
*  Interface   : VibraControl
*  Description : Vibra Control API
*  Version     :
*
*  Copyright (c) 2003 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/

#ifndef VIBRA_CTRL_H__
#define VIBRA_CTRL_H__

// INCLUDES
#include <e32base.h>
#include <e32std.h>

/**
 *  Interface that is used to control the device vibration feature.
 *  This class provides the ability to control the device vibration feature.
 *  Vibration might be used in a game to signal a collision or explosion or for
 *  giving tactile feedback to gaming events, such as a ball hitting 
 *  a wall (shaking).
 *
 *  @lib VibraCtrl.DLL
 *  @since 2.0
 */  
class CVibraControl : public CBase
    {  
    public:
        /**
        * Vibration setting in the user profile.
        */
        enum TVibraModeState 
            {
            EVibraModeON = 0,   // Vibration setting in the user profile is on.
            EVibraModeOFF,      // Vibration setting in the user profile is off.
            EVibraModeUnknown   // For debugging/development and signalling an error condition.
            };

        /**
        * Status of the vibrating setting request.
        */
        enum TVibraRequestStatus 
            {
            EVibraRequestOK = 0,      // Request is OK.
            EVibraRequestFail,        // Request has failed.
            EVibraRequestNotAllowed,  // Vibra is set off in the user profile
            EVibraRequestStopped,     // Vibra is stopped
            EVibraRequestUnableToStop,// Unable to stop vibra
            EVibraRequestUnknown      // For debugging/development and signalling an error condition.
            };

        /**
        * Internal panic codes.
        */
        enum TVibraCtrlPanic 
            {
            EPanicUnableToGetVibraSetting,
            EPanicVibraGeneral
            };

    public:
        /**
        * Destructor.
        */
        virtual ~CVibraControl();

        /**
        * Starts the device vibration feature with factory-defined intensity.
        * The method does not block, but returns immediately so that the 
        * vibration happens simultaneously as the game continues to run.
        * If StartVibra is called again before the first vibration completes
        * then the first vibration is interrupted and the second vibrations
        * starts immediately -- i.e. The periods of vibration are not cumulative.
        *
        * The vibration can be interrupted with the method StopVibra before
        * the specified interval has elasped.
        *
        * Vibra settings of the vibration feature in the user profile 
        * must be active. If no, vibration is not activated.
        *
        * Note: The device may have implementation defined or hardware imposed
        *       limits to the duration of the vibration feature. In such 
        *       circumstances any vibration will cut off at that limit even if
        *       the duration parameter is greater than the limit.
        *
        * @param aDuration Duration of the vibration measured in milliseconds. 
        *                  A value of 0 specifies that the vibration should
        *                  continue indefinitly and should be stopped with a 
        *                  call to StopVibra.
        * @exception KErrGeneral Unable to start vibra.
        *            KErrNotSupported Device doesn't support vibration feature.
        * @see MVibraControlObserver
        */
        virtual void StartVibraL(TUint16 aDuration) = 0;
		
        /**
        * Interrupts the device vibration that is started with the StartVibra
        * method immediately.
        *
        * @exception KErrNotSupported Device doesn't support vibration feature.
        * @see MVibraControlObserver
        */		
        virtual void StopVibraL(void) = 0; 
		
        /**
        * This method retrieves the current settings of the vibration feature
        * in the user profile. The developer can check the Vibra settings 
        * in the profile and if there is no Vibra active but it is needed by 
        * the game then the user can be informed, or asked if he wants to enable
        * the Vibra during the game.
        * @return TVibraModeState with the possible states EvibraModeON, 
        *                         EVibraModeOFF or, 
        *                         if an error occurs, EVibraModeUnknown
        */
        virtual TVibraModeState VibraSettings(void) const = 0;

        /**
        * Starts the device vibration feature. The method does not block, 
        * but returns immediately so that the vibration happens simultaneously
        * as the game continues to run. If StartVibra is called again before
        * the first vibration completes then the first vibration is interrupted
        * and the second vibrations starts immediately -- i.e. The periods of
        * vibration are not cumulative.
        *
        * The vibration can be interrupted with the method StopVibra before
        * the specified interval has elasped.
        *
        * Vibra settings of the vibration feature in the user profile 
        * must be active. If no, vibration is not activated.
        *
        * Note: The device may have implementation defined or hardware imposed
        *       limits to the duration of the vibration feature. In such 
        *       circumstances any vibration will cut off at that limit even if
        *       the duration parameter is greater than the limit.
        *
        *
        * @param aDuration Duration of the vibration measured in milliseconds. 
        *                  A value of 0 specifies that the vibration should
        *                  continue indefinitly and should be stopped with a 
        *                  call to StopVibra.
        * @param aIntensity Intensity of the vibra in decimal is -100 to 100,
        *                   which shows the percentage of the vibra motor full
        *                   rotation speed. When intensity is negative, 
        *                   the vibra motor rotates in the negative direction.
        *                   When intensity is positive, the vibra motor rotates
        *                   in the positive direction. Value 0 stops the vibra.
        * @exception KErrGeneral Unable to start vibra.
        *            KErrNotSupported Device doesn't support user-defined 
        *            intensity or vibration feature is not supported.
        *            KErrArgument One of the parameters is out of range.
        * @see MVibraControlObserver
        */
	    virtual void StartVibraL(TUint16 aDuration, TInt aIntensity) = 0;
	
    protected:
       /**
        * C++ default constructor.
        * @see VibraFactory
        */
        CVibraControl();
    };

/**
*  An interface the developer implements for handling notifies events. 
*
*  @lib VibraCtrl.DLL
*  @since 2.0
*/
class MVibraControlObserver
    {    
    public:
        /** 
        * Called when the vibration setting in the user profile is changed.
        * @param aStatus Indicates the new setting.
        */
        virtual void VibraModeStatus(CVibraControl::TVibraModeState aStatus) = 0;
        /** 
        * Called when the device vibration feature is requested.
        * @param aStatus Indicates vibra request status.
		*/
        virtual void VibraRequestStatus(CVibraControl::TVibraRequestStatus aStatus) = 0;
	};

/**
 *  Factory to create instance of the VibraControl.
 *
 *  @lib VibraCtrl.DLL
 *  @since 2.0
 */
class VibraFactory
    {
    public:
        /**
        * Create a CVibraControl object without notify handling.
        */
        IMPORT_C static CVibraControl* NewL(); 
		
        /** 
        * Create a CVibraControl Object using notify handling
        * The clients of this code will be notified about every change
        * of the vibration setting in the user profile via the 
        * MvibraControlObserver interface.
        *
        * @param aCallback A reference to a class implementing 
        *                  the MVibraControlObserver interface.		
        * @see MVibraControlObserver
        */
        IMPORT_C static CVibraControl* NewL(MVibraControlObserver* aCallback);

        /** 
        * Create a CVibraControl Object using notify handling
        * The clients of this code will be notified about every change
        * of the vibration setting in the user profile via the 
        * MvibraControlObserver interface. The object is left to cleanup stack.
        *
        * @param aCallback A reference to a class implementing 
        *                  the MVibraControlObserver interface.		
        * @see MVibraControlObserver
        */
        IMPORT_C static CVibraControl* NewLC(MVibraControlObserver* aCallback);

    private:
        /**
        * C++ default constructor.
        */
        VibraFactory();
    };

#endif // VIBRA_CTRL_H__
