/*
* ============================================================================
*  Name     : CAknCommonDialogsBase from CAknCommonDialogsBase.h
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

#ifndef __CAKNCOMMONDIALOGSBASE_H__
#define __CAKNCOMMONDIALOGSBASE_H__

// INCLUDES
#include <E32BASE.H>
#include <ConeResLoader.h>

// CONSTANTS

/**
* Enumerations for different dialogs. A dialog loads its default values
* (such as softkey texts and title) depending on its type.
*/
enum TCommonDialogType
	{
	ECFDDialogTypeNormal,
	ECFDDialogTypeSelect,
	ECFDDialogTypeSave,
	ECFDDialogTypeMove,
	ECFDDialogTypeBrowse,
	ECFDDialogTypeDefaultSetting
	};

/**
* Text that is shown when Common File Dialogs panics.
*/
_LIT( KCFDPanicText, "CommonDialogs" );

/**
* Enumerations for Common File Dialog panics.
*/
enum TCFDPanics
	{
	ECFDPanicInvalidFilterType						=  1,
	ECFDPanicInvalidFilterStyle						=  2,
	ECFDPanicInvalidAttributeFilterDataLength		=  3,
	ECFDPanicInvalidAttributeFilterDataCount		=  4,
	ECFDPanicInvalidFileNameFilterDataLength		=  5,
	ECFDPanicInvalidFileNameFilterDataCount			=  6,
	ECFDPanicNoLocationStructures					=  7,
	ECFDPanicRootPathNotDefined						=  8,
	ECFDPanicNoPathForFileNamePromptDialog			=  9,
	ECFDPanicOutOfBounds							= 10,
	ECFDPanicNullParameter							= 11,
	ECFDPanicNoResourceDefined						= 12,
	ECFDPanicTitleOrSoftkeyNotSet					= 13
	};

// FORWARD DECLARATIONS
class CCoeEnv;

//  CLASS DEFINITION
/**
* Base class for Common File Dialogs.
* Can't be created without derivation because of the protected constructor.
* Opens CFD's resource in BaseConstructL.
*/
class CAknCommonDialogsBase : public CBase
	{
	public:		// Enumerations
		/**
		* Sometimes it is necessary to know if dialog was exited by
		* left softkey or selection key. This enumeration works as TBool,
		* ERightSoftkey is not true and other return values are.
		* For example, memory selection dialog and file selection dialog
		* return values of this enumeration.
		*/
		enum TReturnKey
			{
			ERightSoftkey = EFalse,
			ELeftSoftkey,
			ESelectionKey
			};

	protected:	// Constructors and destructors
		CAknCommonDialogsBase();

		virtual ~CAknCommonDialogsBase();

		/**
		* Loads resource of Common File Dialogs on any language.
		*/
		void BaseConstructL();

	protected:	// Data
		/**
		* Pointer to control environment.
		* Pointer is cached because using of CCoeEnv::Static() is slow.
		*/
		CCoeEnv* iCoeEnv;

	private:	// Data
		/**
		* Loads resource file of Common File Dialogs on any language.
		*/
		RConeResourceLoader iResourceLoader;
	};

#endif // __CAKNCOMMONDIALOGSBASE_H__

// End of File