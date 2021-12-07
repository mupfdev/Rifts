// SHGPANIC.H
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.

#if !defined(__SHGPANIC_H__)
#define __SHGPANIC_H__

#if !defined(__E32DEF_H__)
#include <e32def.h>
#endif

enum TShgPanic
	{
	EShgPanicBug=1,

	EShgPanicStackMemoryAllocation,
	EShgPanicStackBounds,
	EShgPanicStackPointerOutsideBounds,
	EShgPanicStackOverflow,
	EShgPanicStackUnderflow,
	EShgPanicStackMaxItemSizeIncorrect,
	EShgPanicBadStackValue,
	EShgPanicStackSafetyMarginTooSmall,

	EShgPanicFormulaNotFound,
	EShgPanicFormulaCellNotListMember,

	EShgPanicRowOutOfRange,
	EShgPanicColumnOutOfRange,
	EShgPanicInvalidCellCount,
	EShgPanicBadCellType,
	EShgPanicNotFormulaCell,

	EShgPanicUnknownFunction,
	EShgPanicUnknownOperator,
	EShgPanicUnknownToken,
	EShgPanicUnknownDelimiter,
	EShgPanicParametersNotConsumed,
	EShgPanicWrongBaseTime,

	EShgPanicBadArrayIndex,
	EShgPanicNameNotFound,
	EShgPanicNameAlreadyExists,

	EShgPanicOrderedArrayMemberNotFound,
	EShgPanicCellOutsideRange,
	EShgPanicNullCellPointer,

	EShgPanicDataFactoryNotSet,
	EShgPanicWorkBookNewFailed,
	EShgPanicWorkBookIdOutOfRange,
	EShgPanicWorkSheetNameNotFound,
	EShgPanicWorkSheetNameAlreadyUsed,
	EShgPanicWorkBookIllegalArrayPos,
	EShgPanicNoSuchWorkSheet,

	EShgPanicContainerInsertionOverIter,

	EShgPanicCellDataIncorrectSize,

	EShgPanicTemplateAdditionalDataIsNull,
	EShgPanicDefaultAdditionalDataIsNull,
	EShgPanicInvalidNumberFormat
	};

GLREF_C void Panic(TShgPanic);
#endif
