/*
* ============================================================================
*  Name     : AknPanic.h
*  Part of  : Avkon
*
*  Description:
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
// EIKPANIC.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNPANIC_H__)
#define __AKNPANIC_H__

#include <e32def.h>

enum TAknPanic
	{
	EAknPanicFormattedCellListInvalidBitmapIndex,
	EAknPanicNoSuchControlInStack,
	EAknPanicListboxUndefined,
	EAknPanicListboxSizeIsNotAccordingToLAFSpec,
	EAknPanicListboxShortcutValueNotHandled,
	EAknPanicListboxShortcutInvalidValue,
	EAknPanicOutOfRange,
	EAknPanicListboxLayoutProblem,
	EAknPanicLAF,
	EAknPanicLayoutResourceProblem,
	EAknPopupCorrupt, // Added for Release 16
    EAknPanicNullPointer,
	EAknPanicLayoutMismatchBetweenMarginsAndParentRect,
	EAknPanicLayoutTextResourceProblem,
	EAknPanicLayoutRectResourceProblem,
	EAknPanicLayoutEdwinResourceProblem,
	EAknPanicLayoutMfneResourceProblem,
	EAknPanicLayoutControlResourceProblem,
	EAknPanicLayoutIncorrectEdwinSize,
	EAknPanicLayoutControlSetRectChangedControlSize,
	EAknPanicNoAnimationData,
	EAknPanicUnknownAnimationType,
	EAknPanicNoUserAnimation,
	EAknPanicAnimationCorrupt,
	EAknPanicDCADecoratorIndexOutOfRange,
	EAknPanicPopupFieldListInvalidDecorator,
	EAknPanicPopupFieldInvalidValue,
	EAknPanicPopupFieldUninitialisedMember,
	EAknPanicPopupFieldEditComboInsufficientSize,
	EAknPanicQueryTimeArrayTimeFormatLeave,
	EAknPanicLayoutTextNotCalled,
	EAknPanicLayoutRectNotCalled,
	EAknStatusPaneUidIndic,
	EAknPanicLayoutDoesNotExists,
	EAknPanicListBoxLayoutDecoratorMemoryAllocation,
	EAknPanicPopupFieldUndefinedMode,
	EAknPanicPopupFieldWrongMode,
	EAknPanicPopupFieldSelectionListDoesntExist,
	EAknPanicPopupFieldSelectionListAlreadyExists,
	EAknPanicPopupFieldListNotImplemented,
	EAknPanicPopupFieldArrayIsEmpty,
	EAknPanicLayoutPopupFieldResourceProblem,
	EAknPanicInvalidResourceData,
	EAknPanicListBoxNotSupportedByListQuery,
	EAknPanicQueryDateArrayTimeFormatLeave,
	EAknPanicPopupFieldCBADoesntExist,
	EAknPanicPopupSettingListMenuListDoesntExist,
	EAknPanicPopupSettingListMenuListAlreadyExists,
	EAknPanicPopupSettingListListNotImplemented,
	EAknPanicLayoutPopupSettingListResourceProblem,
	EAknPanicPopupSettingListInvalidValue,
	EAknPanicPopupSettingListUninitialisedMember,
	EAknPanicOverflow,
	EAknPanicKeyLockObserverAlreadyExists,
	EAknPanicKeyLockObserverNotFound,
	EAknPanicQueryValueInvalidMode,
    EAknPanicNotSupported,
	EAknPanicWrongListBoxTypeUsedInPopupWindow,
	EAknPanicInvalidValue,
	EAknPanicObjectNotFullyConstructed,
	EAknPanicSelfCheckFailure
	};

GLREF_C void Panic(TAknPanic aPanic);

#endif
