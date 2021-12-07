/*
* ============================================================================
*  Name     : AknCommonDialogs from AknCommonDialogs.h
*  Part of  : Common File Dialogs
*
*  Description:
*
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

#ifndef __AKNCOMMONDIALOGS_H__
#define __AKNCOMMONDIALOGS_H__

#include <CAknCommonDialogsBase.h>

// FORWARD DECLARATIONS
class MAknMemorySelectionObserver;
class MAknFileSelectionObserver;

// CLASS DEFINITION
/**
 * A class that consists of static functions that launch UI components in a
 * sequence. First, memory selection component is launched and then
 * file/directory selection component. In save and move dialogs directory
 * selection may not be shown if there are no subdirectories to choose from.
 * In save dialog, finally filename prompt component is launched.
 *
 * All methods have an obligatory resource ID parameter for memory selection
 * because it contains the paths for both memories (Phone&MMC) (LOCATION structs).
 * If set, an observer is queried just before exiting the dialog.
 * At this point the application can either reject or accept user's selection.
 * Every dialog returns a boolean value which tells if user has selected something
 * or not.
 */
class AknCommonDialogs
	{
	public:
		/**
		 * A static method that launches file selection dialog.
		 * @param aFileName Full path and filename of the file that user
		 *        selects is stored to this descriptor.
		 * @param aMemorySelectionResourceId A resource id for memory selection dialog.
		 * @param aObserver An observer which is asked, if set, to verify user's selection.
		 * @return Returns ETrue if user selects a file, otherwise EFalse.
		 */
		IMPORT_C static TBool RunSelectDlgLD(
			TDes& aFileName,
			TInt aMemorySelectionResourceId,
			MAknFileSelectionObserver* aObserver = NULL );

		/**
		 * A static method that launches file selection dialog.
		 * @param aFileName Full path and filename of the file that user
		 *        selects is stored to this descriptor.
		 * @param aMemorySelectionResourceId A resource id for memory selection dialog.
		 * @param aFileSelectionTitle A custom title for file selection dialog.
		 * @param aObserver An observer which is asked, if set, to verify user's selection.
		 * @return Returns ETrue if user selects a file, otherwise EFalse.
		 */
		IMPORT_C static TBool RunSelectDlgLD(
			TDes& aFileName,
			TInt aMemorySelectionResourceId,
			const TDesC& aFileSelectionTitle,
			MAknFileSelectionObserver* aObserver = NULL );

		/**
		 * A static method that launches file selection dialog.
		 * @param aFileName Full path and filename of the file that user
		 *        selects is stored to this descriptor.
		 * @param aMemorySelectionResourceId A resource id for memory selection dialog.
		 * @param aFileSelectionResourceId A resource id for file selection dialog.
		 * @param aObserver An observer which is asked, if set, to verify user's selection.
		 * @return Returns ETrue if user selects a file, otherwise EFalse.
		 */
		IMPORT_C static TBool RunSelectDlgLD(
			TDes& aFileName,
			TInt aMemorySelectionResourceId,
			TInt aFileSelectionResourceId,
			MAknFileSelectionObserver* aObserver = NULL );

		/**
		 * A static method that launches move dialog.
		 * @param aDirectory Full path of the folder that user
		 *        selects is stored to this descriptor.
		 * @param aMemorySelectionResourceId A resource id for memory selection dialog.
		 * @param aObserver An observer which is asked, if set, to verify user's selection.
		 * @return Returns ETrue if user selects a folder, otherwise EFalse.
		 */
		IMPORT_C static TBool RunMoveDlgLD(
			TDes& aDirectory,
			TInt aMemorySelectionResourceId,
			MAknFileSelectionObserver* aObserver = NULL );

		/**
		 * A static method that launches move dialog.
		 * @param aDirectory Full path of the folder that user
		 *        selects is stored to this descriptor.
		 * @param aMemorySelectionResourceId A resource id for memory selection dialog.
		 * @param aFileSelectionTitle A custom title for directory selection dialog.
		 * @param aObserver An observer which is asked, if set, to verify user's selection.
		 * @return Returns ETrue if user selects a folder, otherwise EFalse
		 */
		IMPORT_C static TBool RunMoveDlgLD(
			TDes& aDirectory,
			TInt aMemorySelectionResourceId,
			const TDesC& aFileSelectionTitle,
			MAknFileSelectionObserver* aObserver = NULL );

		/**
		 * A static method that launches move dialog.
		 * @param aDirectory Full path of the folder that user
		 *        selects is stored to this descriptor.
		 * @param aMemorySelectionResourceId A resource id for memory selection dialog
		 * @param aFileSelectionResourceId A resource id for file selection dialog
		 * @param aObserver An observer which is asked, if set, to verify user's selection.
		 * @return Returns ETrue if user selects a folder, otherwise EFalse
		 */
		IMPORT_C static TBool RunMoveDlgLD(
			TDes& aDirectory,
			TInt aMemorySelectionResourceId,
			TInt aFileSelectionResourceId,
			MAknFileSelectionObserver* aObserver = NULL );

		/**
		 * A static method that launches save dialog.
		 * @param aDefaultFileName Full path + the filename that user enters
		 *        is stored to this descriptor. The descriptor may contain text that is
		 *        used as default filename, for example "Attachment".
		 * @param aMemorySelectionResourceId A resource id for memory selection dialog.
		 * @param aObserver An observer which is asked, if set, to verify the filename that user types.
		 * @return Returns ETrue if user accepts or enters a filename, otherwise EFalse.
		 */
		 IMPORT_C static TBool RunSaveDlgLD(
			TDes& aDefaultFileName,
			TInt aMemorySelectionResourceId,
			MAknFileSelectionObserver* aObserver = NULL );

		/**
		 * A static method that launches save dialog.
		 * @param aDefaultFileName Full path + the filename that user enters
		 *        is stored to this descriptor. The descriptor may contain text that is
		 *        used as default filename, for example "Attachment".
		 * @param aMemorySelectionResourceId A resource id for memory selection dialog.
		 * @param aFileSelectionTitle Custom title for file selection dialog.
		 * @param aFileNamePromptTitle Custom title for filename prompt dialog.
		 * @param aObserver An observer which is asked, if set, to verify the filename that user types.
		 * @return Returns ETrue if user accepts or enters a filename, otherwise EFalse.
		 */
		IMPORT_C static TBool RunSaveDlgLD(
			TDes& aDefaultFileName,
			TInt aMemorySelectionResourceId,
			const TDesC& aFileSelectionTitle,
			const TDesC& aFileNamePromptTitle,
			MAknFileSelectionObserver* aObserver = NULL );

		/**
		 * A static method that launches save dialog.
		 * @param aDefaultFileName Full path + the filename that user enters
		 *        is stored to this descriptor. The descriptor may contain text that is
		 *        used as default filename, for example "Attachment".
		 * @param aMemorySelectionResourceId A resource id for memory selection dialog.
		 * @param aFileSelectionResourceId A resource id for file selection dialog.
		 * @param aObserver An observer which is asked, if set, to verify the filename that user types.
		 * @return Returns ETrue if user accepts or enters a filename, otherwise EFalse.
		 */
		 IMPORT_C static TBool RunSaveDlgLD(
			TDes& aDefaultFileName,
			TInt aMemorySelectionResourceId,
			TInt aFileSelectionResourceId,
			MAknFileSelectionObserver* aObserver = NULL );

		/**
		 * A static method that launches save dialog.
		 * @param aDefaultFileName Full path + the filename that user enters
		 *        is stored to this descriptor. The descriptor may contain text that is
		 *        used as default filename, for example "Attachment".
		 * @param aMemorySelectionResourceId A resource id for memory selection dialog.
		 * @param aFileSelectionResourceId A resource id for file selection dialog.
		 * @param aFileNamePromptTitle Custom title for filename prompt dialog.
		 * @param aObserver An observer which is asked, if set, to verify the filename that user types.
		 * @return Returns ETrue if user accepts or enters a filename, otherwise EFalse.
		 */
		 IMPORT_C static TBool RunSaveDlgLD(
			TDes& aDefaultFileName,
			TInt aMemorySelectionResourceId,
			TInt aFileSelectionResourceId,
			const TDesC& aFileNamePromptTitle,
			MAknFileSelectionObserver* aObserver = NULL );

	private:
		/**
		 * A static method that launches UI components in a sequence.
		 * @param aType Defines what type of dialog is shown.
		 * @param aFileName A reference to a descriptor. Usage depends on the dialog type.
		 * @param aMemorySelectionResourceId A resource id for memory selection dialog.
		 * @param aFileSelectionResourceId A resource id for file selection dialog.
		 * @param aFileNamePromptResourceId A resource id for filename prompt dialog.
		 * @param aFileSelectionTitle Custom title for file selection.
		 * @param aFileNamePromptTitle Custom title for filename prompt dialog.
		 * @param aMemorySelectionObserver An observer for memory selection dialog.
		 * @param aFileSelectionObserver An observer for file selection dialog.
		 * @param aFileNamePromptObserver An observer for filename prompt dialog.
		 * @return Returns a boolean value that depends on the case.
		 */
		static TBool RunL(
			TCommonDialogType aType,
			TDes& aFileName,
			TInt aMemorySelectionResourceId,
			TInt aFileSelectionResourceId,
			TInt aFileNamePromptResourceId,
			const TDesC& aFileSelectionTitle,
			const TDesC& aFileNamePromptTitle,
			MAknMemorySelectionObserver* aMemorySelectionObserver,
			MAknFileSelectionObserver* aFileSelectionObserver,
			MAknFileSelectionObserver* aFileNamePromptObserver );

	};

#endif // __AKNCOMMONDIALOGS_H__

// End of File