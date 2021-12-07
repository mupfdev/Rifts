//	DialogProvider.h
//
//	Copyright (c) 2000 Symbian Ltd.  All rights reserved. 
//

#ifndef __DIALOGPROVIDER_H__
#define __DIALOGPROVIDER_H__

// System includes
//
#include <e32std.h>
#include <wapcli.h> // for Certificate Information structure

/**
	@public
	@class MDialogProvider
	Dependencies : none
	Comments : This class provides an API to be called by low level components,
	like data collectors, and implemented by the UI.

	It is mainly used for dialog creation and information passing.
	@lib	euser.lib
	@since	6.0
	@todo	Should this be renamed?
 */
class MDialogProvider
	{
public:

/**
	@fn				PromptL( const TDesC& aMessage, const TDesC& aDefaultInput) =0
	Intended Usage	:	This creates an input dialog for the user to enter a text 
	string into a single text field.
	@warning		This function must be a blocking function.
	@since			6.0
	@param			aMessage		A descriptor with the label/title of the text field.
	@param			aDefaultInput	A descriptor with (if any) default input text.
	@return			A pointer to a buffer with the input text. 
	@todo			Is warning correct?
 */
	virtual HBufC* PromptL( const TDesC& aMessage, const TDesC& aDefaultInput) =0;

/**
	@fn				PasswordL(TPassword& aPasswd) =0
	Intended Usage	:	Creates a password dialog for user to enter some hidden text.
	@warning		This function must be a blocking function.
	@since			6.0
	@param			aPasswd	An output argument which is set the entered password.
	@return			void.
	@todo			Is warning correct?
 */
	virtual void PasswordL(TPassword& aPasswd) =0;

/**
	@fn				ConfirmationL(const TDesC& aMessage, const TDesC& aOkButtonLabel, const TDesC& aCancelButtonLabel ) =0
	Intended Usage	:	Creates a simple confirmation dialog with Ok and Cancel (or 
	similar) buttons. Allows the user to confirm an action or message. Some text 
	is displayed indicating the nature of the action.
	@warning		This function must be a blocking function.
	@since			6.0
	@param			aMessage			A descriptor with a display message. 
	@param			aOkButtonLabel		A descriptor with the label for the Ok button.
	@param			aCancelButtonLabel	A descriptor with the label for the Cancel button.
	@return			A boolean value of ETrue if the Ok button was pressed, or a value 
	of EFalse if the cancel button was pressed.
	@todo			Is warning correct?
 */
	virtual TBool ConfirmationL(const TDesC& aMessage, const TDesC& aOkButtonLabel, const TDesC& aCancelButtonLabel ) =0;

/**
	@fn				CertificateConfirmationL(const RCertificate::TInfo& aCertificateInfo) =0
	Intended Usage	:	Created a certificate confirmation dialog. Requests that the
	user accept or reject the displayed certificate.
	@warning		This function must be a blocking function.
	@since			6.0
	@param			aCertificateInfo	The certificate details.
	@return			A boolean value of ETrue if the certifiacte was accepted, or a 
	value of EFalse if it was not.
	@todo			Is warning correct?
 */
	virtual TBool CertificateConfirmationL(const RCertificate::TInfo& aCertificateInfo) =0;

/**
	@fn				AlertL(const TDesC& aMessage) =0
	Intended Usage	:	Creates an alert dialog to inform the user. A message is
	displayed and there is an Ok (or similar) button to close the dialog.
	@warning		This function must be a blocking function.
	@since			6.0
	@param			aMessage	A descriptor with the alert message.
	@return			void.
	@todo			Is warning correct?
 */
	virtual void  AlertL(const TDesC& aMessage) =0;

/**
	@fn				DisplayConnectingDialogL() =0
	Intended Usage	:	This creates a dialog which indicates that a connection
	is being done.
	@warning		This function must be a non blocking function.
	@since			6.0
	@return			virtual void 
	@todo			Is warning ok? Also, need to change this to take a message.
	@pre 			A connecting dialog is not already been created.
	@post			Unspecified
 */
	virtual void DisplayConnectingDialogL() =0;

/**
	@fn				CancelConnectingDialog() =0
	Intended Usage	:	Cancels the current connecting dialog.
	@since			6.0
	@return			void.
 */
	virtual void CancelConnectingDialog() =0;

/**
	@fn				MDialogProvider_Reserved1() = 0
	Intended Usage	:	Function placeholder for BC proofing.
	@since			6.0
	@return			void.
 */
	virtual void MDialogProvider_Reserved1() = 0;
	};

#endif // __DIALOG_PROVIDER_H__
