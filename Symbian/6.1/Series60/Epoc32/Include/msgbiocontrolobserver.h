/*
* ============================================================================
*  Name     : MsgBioControlObserver.h
*  Part of  : MsgEditorUtils
*
*  Description:
*     Bio control observer.
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

#ifndef __MSGBIOCONTROLOBSERVER_H_
#define __MSGBIOCONTROLOBSERVER_H_

// INCLUDES 
// CONSTANTS
// MACROS
// DATA TYPES
// FUNCTION PROTOTYPES
// FORWARD DECLARATIONS
// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
 * Interface for Bio Control Observer. The MMsgBioControlObserver is used
 * for observing the Bio Control from the editor application.
 */
class MMsgBioControlObserver
    {
    public:

        /**
         * The command types. For use in conjunction with the
         * functions of this class.
         */
        enum TMsgCommands
            {
            EMsgNone = 0,
            EMsgSave,
            EMsgReply,
            EMsgForwad,
            EMsgSend,
            EMsgAddressBook,          
            EMsgClose
            };
	
    public:

        /**
         * Returns the first free command id that a BIO control can use for
         * its own purposes. All the commands having ids of more or equal to
         * an id returned by this function are passed to the BIO control.
         * @return First free command.
         */
        virtual TInt FirstFreeCommand() const = 0;

        /**
         * Requests the BIO message editor/viewer to handle a command.
         * Typically the BIO message editor/viewer does not handle a requested
         * command immediately but after the BIO control has returned from the
         * HandleCommandL function.
         * @param aCommand The command that can be handled.
         * @return KerrNone or KerrNotSupported
         */
        virtual TInt RequestHandleCommandL(TMsgCommands aCommand) = 0;

        /**
         * Returns ETrue or EFalse whether a requested aCommand is supported
         * by the BIO message editor or not. This command should be used
         * before requesting command handling by RequestHandleCommand().
         * @param aCommand The command
         * @return ETrue if command is support and EFalse if not.
         */
        virtual TBool IsCommandSupported(TMsgCommands aCommand) const = 0;
    };


#endif // __MSGBIOCONTROLOBSERVER_H_

//end of file
