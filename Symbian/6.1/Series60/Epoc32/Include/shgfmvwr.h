// SHGFMVWR.H
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved. 

#if !defined(__SHGFMVWR_H__)
#define __SHGFMVWR_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__BACELL_H__)
#include <bacell.h>
#endif

#if !defined(__SHGERR_H__)
#include <shgerr.h>
#endif

#if !defined(__SHGTOKEN_H__)
#include "shgtoken.h"
#endif
#if !defined(__SHGFMEVL_H__)
#include "shgfmevl.h"
#endif

class MShgCellReader;
class CShgNameSet;
class CShgFormulaTranslator;
class CShgFormulaCracker;
class CShgFormulaEvaluator;
class CShgWorkBook;
class CSheetEngine;

class CShgFormulaViewer : public CBase
// Formulae are manipulated via CShgFormulaViewer
	{
public:
	enum {EFormulaEqualsSign='='};
	enum TFunctionType
		{EFnError,EFnFinancial,EFnDateAndTime,EFnMathematical,EFnStatistical,EFnLookUp,EFnText,EFnLogical,EFnInformation,EFnDatabase};
public:
	virtual ~CShgFormulaViewer();
	IMPORT_C static CShgFormulaViewer* NewL(const CShgNameSet* aNameSet,const CShgWorkBook* aWorkBook,CSheetEngine* aEngine,const TDesC& aResourceFile); // previously was exported for test code
	static CShgFormulaViewer* NewEmptyL(const CShgNameSet* aNameSet,const CShgWorkBook* aWorkBook,CSheetEngine* aEngine,const CShgFormulaViewer* aShgFormulaViewer);
private:
	CShgFormulaViewer();
	void ConstructL(const CShgNameSet* aNameSet,const CShgWorkBook* aWorkBook,CSheetEngine* aEngine,const TDesC& aResourceFile);
	void ConstructEmptyL(const CShgNameSet* aNameSet,const CShgWorkBook* aWorkBook,CSheetEngine* aEngine,const CShgFormulaViewer* aShgFormulaViewer);
public:
	void LocaleHasChanged();
	IMPORT_C void InitWithTokenFormula(const TCellRef& aCell,const TDesC8* aFormula); // previously was exported for test code
	IMPORT_C void InitWithTextFormula(const TCellRef& aCell,const TDesC& aText); // previously was exported for test code
	IMPORT_C const TPtrC GetTextFormulaL(); // previously was exported for test code
	IMPORT_C const TPtrC8 GetTokenFormulaL(TShgError& aError); // previously was exported for test code
	TShgError EvaluateL(TShgCell& aCell,const MShgCellReader* aCellReader);
	inline CShgFormulaEvaluator* FormulaEvaluator() const;
	TInt SyntaxErrorPos() const;
	TShgError CalculateDatabaseTableL(const TDesC& aRangeText,const TDesC& aCell1,const TDesC& aCell2);
	const TPtrC CellInfoType(CShgFormulaEvaluator::TCellInfoType aCellInfoType) const;
	const TPtrC ErrorType(TShgCell::TErrorType aErrorType) const;
	const TPtrC BoolType(TBool aBool) const;
	const TPtrC DefaultWorkSheetName() const;
// SpreadSheet Token Info
	static TBool IsRange(TFormulaToken aToken);
	static TBool IsBeginStatFunction(TFormulaToken aToken);
	static TBool IsDatabaseFunction(TFormulaToken aToken);
	static TBool FunctionForcesRecalculation(TFormulaToken aToken);
	static TBool IsOperand(TFormulaToken aToken);
	static TBool IsOperandOrZeroArgumentFunction(TFormulaToken aToken);
	static TBool IsDelimiter(TFormulaToken aToken);
	const TPtrC DelimiterText(TFormulaToken aOperator) const;
	static const TUint8* SkipToken(const TUint8 *pToken);
// SpreadSheet Operators
	static TBool IsOperator(TFormulaToken aToken);
	static TBool IsLogicalOperator(TFormulaToken aToken);
	static TBool IsUnaryOperator(TFormulaToken aToken);
	TBool GetOperatorToken(TFormulaToken& aToken,const TDesC& aText) const;
	TBool GetLogicalOperatorToken(TFormulaToken& aToken,const TDesC& aText) const;
	const TPtrC OperatorText(TFormulaToken aOperator) const;
// SpreadSheet Functions
	IMPORT_C TInt FirstFunctionNo() const;
	IMPORT_C TInt LastFunctionNo() const;
	IMPORT_C const TPtrC FunctionName(TFormulaToken aToken) const;
	IMPORT_C TFunctionType FunctionType(TFormulaToken aToken) const;
	IMPORT_C TInt NoArguments(TFormulaToken aFunction) const;
	static TInt StaticNoArguments(TFormulaToken aFunction);
	TBool GetFunctionToken(TFormulaToken& aToken,const TDesC& aText) const;
	static TBool IsFunction(TFormulaToken aToken);
	static TBool IsMultiArgumentFunction(TFormulaToken aToken);
	static TInt ArgumentType(TFormulaToken aFunction,TInt aParameter);
	static TInt NoOperands(TFormulaToken aToken);
private:
	enum TState {ETPtrNotSet,ETPtrIsText,ETPtrIsToken};
	enum {EFunctionArraySize=ETokLastArrayFn-ETokFirstFn+1};
	enum {EResourceSignature=0};
private:
	TCellRef	iRelativeCell;
	TState		iTPtrState;
	TPtrC		iInitialValAsText; // renamed (from "iInitialVal") by DPB on 25/2/98
	TPtrC8		iInitialValAsToken; // added by DPB on 25/2/98
	CBufFlat*	iTranslatedVal;
	CShgFormulaCracker*		iFormulaCracker;
	CShgFormulaTranslator*	iFormulaTranslator;
	CShgFormulaEvaluator*	iFormulaEvaluator;
	TBuf<4>		iArgumentSeparator;
	HBufC8*		iFunctionNameData;
	TPtrC		iFunctionNameArray[EFunctionArraySize];
	const HBufC* iLogicalOperatorNameArray[3];
	const HBufC* iCellInfoTypeArray[CShgFormulaEvaluator::ECellInfoTypeLast-CShgFormulaEvaluator::ECellInfoTypeFirst+1];
	const HBufC* iErrorTypeArray[(TShgCell::EErrNotAvailable-TShgCell::ENoError+1)];
	const HBufC* iBoolTypeArray[2];
	const HBufC* iDefaultWorkSheetName;
public:
	static const TUint8 sSkipToken[256];
	static const CShgFormulaEvaluator::TFunction sFunction[ETokLastArrayFn+1];
	};

inline CShgFormulaEvaluator* CShgFormulaViewer::FormulaEvaluator() const
	{return iFormulaEvaluator;}

#endif
