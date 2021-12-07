// SHGERR.H
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.


#if !defined(__SHGERR_H__)
#define __SHGERR_H__

#define SHG_ERROR_RESOURCE(x) (R_SHG_ERROR_ARGUMENT_TYPE_MISMATCH-1-x)

enum TShgError
	{
	EShgNoError=0,
	EShgArgumentTypeMismatch=-1,
	EShgCellProtected=-2,
	EShgFormulaTooComplex=-3,
	EShgIllegalCharacter=-4,
	EShgInvalidRange=-5,
	EShgInvalidName=-6,
	EShgMismatchedLeftBracket=-7,
	EShgMismatchedRightBracket=-8,
	EShgSyntaxError=-9,
	EShgShiftingCellsGoesOffWorkSheet=-10,
	EShgShiftingCellsLosesCellData=-11,
	EShgNonadjacentSelections=-12,
	EShgIncompatibleCopyAndPasteAreas=-13,
	EShgPasteOffWorksheet=-14,
	EShgPasteNotAvailable=-15,
	EShgPasteAreaIsWrongShape=-16,
	EShgIllegalWorkSheetName=-17,
	EShgWorkSheetNameAlreadyUsed=-18,
	EShgCannotDeleteCurrentWorkSheet=-19,
	EShgInvalidCell=-20,
	EShgNameAlreadyExists=-21,
	EShgNameDoesNotExist=-22,
	EShgBadNameData=-23,
	EShgNameContainsIllegalCharacters=-24,
	EShgNamedFormulaNotSupported=-25,
	EShgClearError=-26,
	EShgInvalidWorkSheetNameLength=-27
	};
#endif

