// ShgFmEvl.h
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.

#if !defined(__SHGFMEVL_H__)
#define __SHGFMEVL_H__

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
#if !defined(__SHGAPI_H__)
#include <shgapi.h>
#endif
#if !defined(__SHGTOKEN_H__)
#include "shgtoken.h"
#endif

class CShgEvaluatorStack;
class TShgCellRef;
class TShgRangeRef;
class CShgWorkBook;

class MShgCellReader;
class CShgNameSet;
class CShgFormula;
class CShgFormulaViewer;
class CSheetEngine;

class CShgFormulaEvaluator;
typedef void (*TStatFunction)(CShgFormulaEvaluator* aFormulaEvaluator,CShgEvaluatorStack* aStack);

class CShgFormulaEvaluator : public CBase
	{
public:
	enum TCellInfoType
		{
		ECellInfoTypeNotSet=-1,ECellInfoTypeFirst,ECellInfoTypeAddress=ECellInfoTypeFirst,
		ECellInfoTypeRow,ECellInfoTypeCol,
		ECellInfoTypeContents,
		//ECellInfoTypeProtected,ECellInfoTypeWidth,ECellInfoTypeFormat,ECellInfoTypeType,
		ECellInfoTypeLast=ECellInfoTypeContents
		};
	enum {EMaxStringLength=255};
friend class ShgFormula;
public:
	virtual ~CShgFormulaEvaluator();
public:
	static CShgFormulaEvaluator* NewL(const CShgNameSet* aNameSet,const CShgWorkBook* aWorkBook,CSheetEngine* aSheetEngine,CShgFormulaViewer* aFormulaViewer);
	CShgFormulaEvaluator(const CShgNameSet* aNameSet,const CShgWorkBook* aWorkBook,CSheetEngine* aSheetEngine,CShgFormulaViewer* aFormulaViewer);
	void EvaluateFormulaL(TShgCell& aCell,const TUint8* aFormula,const MShgCellReader* aCellReader);
	TShgError CalculateDatabaseTableL(const TDesC& aRangeText,const TDesC& aCell1,const TDesC& aCell2);
protected:
	enum TOperandType {EBlank=TShgCell::EBlank,EInt=TShgCell::EInt,EBool=TShgCell::EBool,EError=TShgCell::EError,EReal=TShgCell::EReal,EText=TShgCell::EText,ERange};
private:
	void DoEvaluateFormulaL();

	void ConvertedSingleCellRangeToValueL();
	void TryConvertSingleCellRangeToValueL();
	void TryConvertRangeToValueL();
public:
	void LexRange(TInt& aWorkSheetNo,TRangeRef& aRangeRef);
	const MShgCellReader* CellReader();

	TBool IsNextArgumentL(TOperandType aType);

	void PushShgCellRefValueL(const TShgCellRef& aShgCellRef);
	void PushShgCellRefValueL(TInt aWorkSheetNo,const TCellRef& aCellRef);
	void PushCellL(const TShgCell* aCell);

	TInt LoadIntL(TInt& aInt);
	TInt LoadIntL(TInt& aInt,TInt aArgsLeft);
	TInt LoadRealL(TReal& aReal);
	TInt LoadRealL(TReal& aReal,TInt aArgsLeft);
	TInt LoadHBufL(HBufC*& aHBuf);
	TInt LoadHBufL(HBufC*& aHBuf,TInt aArgsLeft);
	TInt LoadHBufLC(HBufC*& aHBuf);
	TInt LoadHBufOrRealL(HBufC*& aHBuf,TReal& aReal);
	TInt LoadShgRangeRefL(TShgRangeRef& aRangeRef);
	TInt LoadShgRangeRefL(TShgRangeRef& aRangeRef,TInt aArgsLeft);

	TInt LoadArgumentsL(TInt& aInt1,TInt& aInt2);
	TInt LoadArgumentsL(TInt& aInt1,TInt& aInt2,TInt& aInt3);
	TInt LoadArgumentsL(TReal& aReal1,TReal& aReal2);
	TInt LoadArgumentsL(TReal& aReal1,TReal& aReal2,TReal& aReal3);
	TInt LoadArgumentsL(TReal& aReal1,TReal& aReal2,TReal& aReal3,TReal& aReal4);

	const CShgWorkSheet* WorkSheet(TInt aWorkSheetNo) const;
public:
	typedef void (*FShgFunction)(CShgFormulaEvaluator*,CShgEvaluatorStack*);
	class TFunction
		{
	public:
		FShgFunction iFunction;
		TUint8 iType;
		TUint8 iNoArguments;
		TUint8 iArgTypes;
		TUint8 iCheckArguments;
		};
private:
	static FShgFunction FunctionForToken(TFormulaToken aToken);
	TBool GetValL(TReal& aCellContents,const TShgCell* aCell);
public:
	const CShgWorkBook*	iWorkBook;
protected:
	const MShgCellReader* iCellReader;
	const CShgNameSet* const iNameSet;
	CSheetEngine*		iSheetEngine;
	CShgFormulaViewer*	iFormulaViewer;
	CShgEvaluatorStack*	iStack;
	RThread				iFpeExceptionThread;
protected:
	struct SStatTotal
		{
		enum TType {EBool,EReal,EText};
		TType iType;
		union {TReal64 iReal;HBufC* iText;};
		};
	SStatTotal		iStatTotal;
	TReal			iStatProduct;
	TReal			iStatSquares;
	TInt			iStatCount;
	TStatFunction	iStatLitFunction;
	TStatFunction	iStatRangeFunction;
	TStatFunction	iStatEndFunction;
	TInt64			iRandSeed;
protected:
	const TUint8* iTokenPtr;
	TFormulaToken iCurrentToken;
	TCellRef iRelativeCell;
//public:
	const TPtrC CellInfoType(TCellInfoType aCellInfoType) const;
	TShgError DoTable1L(const TShgRangeRef* aRangeRef,const TCellRef& aCoord1);
	TShgError DoTable2L(const TShgRangeRef* aRangeRef,const TCellRef& aCoord1,const TCellRef& aCoord2);
	void BeginStatFunctionL();
	TBool EndStatFunctionL();
	TBool EndStatFunctionL(TReal aResult,TInt aCount);
	TBool EndStatFunctionL(HBufC* aResult);
	TBool EndStatFunctionL(TBool aResult);
	};

inline const MShgCellReader* CShgFormulaEvaluator::CellReader()
	{return iCellReader;}
#endif

