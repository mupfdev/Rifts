/*
* ============================================================================
*  Name     : MMsgBioControl.h
*  Part of  : MsgEditorUtils
*
*  Description:
*     Interface for Bio controls.
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
*
* ============================================================================
*/

#ifndef MMSGBIOCONTROL_H
#define MMSGBIOCONTROL_H

//  INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <msgeditor.hrh>   // for enums

// CONSTANTS

/// Leave code which signals that the smart message data was invalid.
const TInt KErrMsgBioMessageNotValid = -90;


/**
 * Used by HandleBaseControlEventRequestL().
 */
enum TMsgBioControlEventRequest 
    {
    EMsgBioUpdateScrollBars
    };

    /**
     * These option menu flags are used with the function
     * MMsgBioControl::OptionMenuPermissionsL().
     */
    enum TMsgBioOptionMenu {
        EMsgBioReply        = 0x00000001,
        EMsgBioForward      = 0x00000002,
        EMsgBioCallBack     = 0x00000004,
        EMsgBioDelete       = 0x00000008,
        EMsgBioMessInfo     = 0x00000010,
        EMsgBioMove         = 0x00000020,
        EMsgBioCreateCC     = 0x00000040,
        EMsgBioFindItem     = 0x00000080,
        EMsgBioAddPinBoard  = 0x00000100,
        EMsgBioSend         = 0x00000200,
        EMsgBioAddRecipient = 0x00000400,
        EMsgBioSave         = 0x00000800,
        EMsgBioEditText     = 0x00001000,
        EMsgBioInsert       = 0x00002000,
        EMsgBioSendingOpt   = 0x00004000,
        EMsgBioHelp         = 0x00008000,
        EMsgBioExit         = 0x00010000,
        EMsgBioReserved1    = 0x00020000,
        EMsgBioReserved2    = 0x00040000,
        EMsgBioReserved3    = 0x00080000,
        EMsgBioReserved4    = 0x00100000,
        EMsgBioReserved5    = 0x00200000,
        EMsgBioReserved6    = 0x00400000,
        EMsgBioReserved7    = 0x00800000,
        EMsgBioReserved8    = 0x01000000
        };

    /// This flag is given as a construction parameter to the Bio Control.
    enum TMsgBioMode {
        EMsgBioEditorMode,
        EMsgBioViewerMode
        };

// MACROS
// DATA TYPES
// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS
class CEikMenuPane;

// CLASS DECLARATION

/**
 * Interface for handling of event request.
 */
class MMsgBioBodyControl
    {
    public:
        virtual TBool HandleBaseControlEventRequestL(        
            TMsgBioControlEventRequest aRequest,
            TInt aDelta = 0) = 0;
    };

/**
* The interface for Bio controls
*/
class MMsgBioControl
    {
    public:

        /**
         * Calculates and sets size for a Bio control according to aSize.
         * This function might become deprecated. The SetSizeL() function will
         * be the replacement.
         * The height of the Bio control may be less or more than requested by
         * aSize, but the width must be exactly the same. If width of the Bio
         * control is not the same as given by aSize, the width must be reset
         * back to requested one. The aSize is set to the new size.
         * @param aSize Size. See explanation.
         */
        virtual void SetAndGetSizeL(TSize& aSize) = 0;

        /**
         * This is called by the container to allow the Bio control to add
         * a menu item command. The command ID's should start from the value
         * returned by the MMsgBioControlObserver::FirstFreeCommand().
         * @param aMenuPane Reference to the applications menu which will be
         * modified.
         */
        virtual void SetMenuCommandSetL(CEikMenuPane& aMenuPane) = 0;

        /**
         * The command handler. The Bio Control should only handle its own
         * commands that it has set using the function SetMenuCommandSetL().
         * @param aCommand ID of command to be handled.
         * @return If the command is handled, it returns ETrue, and vice versa
         */
        virtual TBool HandleBioCommandL(TInt aCommand) = 0;

        /**
         * Returns a rectangle slice of the bio controls viewing area.
         * It is used by the CMsgEditorView class for scrolling the screen.
         * The position is given relative to the bio controls top left
         * corner.
         * @return TRect
         */
        virtual TRect CurrentLineRect() const = 0;

        /**
         * Used by the body container for managing focus and scrolling.
         * @param aDirection The direction to be checked.
         * @return ETrue if focus change is possible, and vice versa.
         */
        virtual TBool IsFocusChangePossible(
            TMsgFocusDirection aDirection) const = 0;

        /**
         * Returns the header text.
         * @return The header text.
         */
        virtual HBufC* HeaderTextL(void)  const = 0;

        /**
         * The application can get the option menu permissions using this
         * function.
         * @return The option menu permission flags. If the flag is off it
         * means that the option menu command is not recommended with this
         * Bio Control.
         */
        virtual TUint32 OptionMenuPermissionsL() const = 0;

        /**
         * Gives the height of the text in pixels.
         * It is used by the scrolling framework.
         * @return Height of the text in pixels.
         */
        virtual TInt VirtualHeight() = 0;

        /**
         * Gives the cursor position in pixels.
         * It is used by the scrolling framework.
         * @return Cursor position in pixels.
         */
        virtual TInt VirtualVisibleTop() = 0;

        /**
         * Tells whether the cursor is in the topmost or bottom position.
         * It is used by the scrolling framework.
         * @param aLocation Specifies either top or bottom.
         * @return ETrue if the cursor is in the part specified by aLocation.
         */
        virtual TBool IsCursorLocation(TMsgCursorLocation aLocation) const = 0;

    };

#endif // MMSGBIOCONTROL_H

// end of file
