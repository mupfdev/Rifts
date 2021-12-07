// SHGAPI.H
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
// The spreadsheet engine API

#ifndef __SHGAPI_H__
#define __SHGAPI_H__

#include <e32std.h>
#include <e32base.h>
#include <s32std.h>
#include <bacell.h>

#include <shgerr.h>

const TUid KUidClipboardTypeSheet={0x1000011c};
const TUid KUidSheetEngineStream={0x1000011d};
const TUid KUidSheetEngineResourceSignature={0x1000011e};
const TUid KUidSheetEngineDll={0x10000122};

const TUint KShgBaseTimeHigh=13960314u;
const TUint KShgBaseTimeLow=2328109056u;

enum TShgLimits
	{
	ESheetNumRowBits=14,
	ESheetMaxRows=1<<ESheetNumRowBits,
	ESheetMaxColumns=256,
	ESheetMaxNoWorkSheets=64,
	ESheetMaxStringFileRead=8912, // MaxLength of string to be read from a file into a HBufC
	ESheetMaxCellTextLength=256,
	ESheetMaxFormulaRecursionDepth=8,
	ESheetMaxWorkSheetNameLength=31 // same as another well known spreadsheet app
	};

#if defined(_DEBUG)
typedef RRegion RRegionBuf10;
#else
typedef RRegionBuf<10> RRegionBuf10;
#endif

class NShgRangeAndCellUtils
	{
public:
	static TBool RangeArrayIsOk(const CArrayFix<TRangeRef>* aRangeArray);
	static TBool RangeIsOk(const TRangeRef& aRange);
	static TBool CellIsOk(const TCellRef& aCell);
	static void ConvertRangeArrayToRegionL(TRegion& aRegion,const CArrayFix<TRangeRef>* aRangeArray);
	};

class RReadStream;
class RWriteStream;

const TInt KShgRealFormatType=KDoNotUseTriads|KAllowThreeDigitExp;
const TInt KShgRealFormatTypeFixed=KRealFormatFixed|KDoNotUseTriads|KAllowThreeDigitExp;
const TInt KShgRealFormatTypeTriad=KRealFormatFixed|KAllowThreeDigitExp;
const TInt KShgRealFormatTypeExponent=KRealFormatExponent|KDoNotUseTriads|KAllowThreeDigitExp;
const TInt KShgRealFormatTypeGeneral=KRealFormatGeneral|KDoNotUseTriads|KAllowThreeDigitExp;

const TInt KShgRealFormatLength=64;

class TShgNumberFormat
	{
public:
	IMPORT_C TShgNumberFormat();
	IMPORT_C TShgNumberFormat(const TShgNumberFormat& aNumberFormat);
	IMPORT_C TBool operator==(const TShgNumberFormat& aNumberFormat) const;
	IMPORT_C void InternalizeL(RReadStream& aReadStream);
	IMPORT_C void ExternalizeL(RWriteStream& aWriteStream) const;
public:
	enum TFormat
		{
		EFirst,
		EGeneral=EFirst,
		EStartOfFormatsWithDecimalPlaces,
		EFixed=EStartOfFormatsWithDecimalPlaces,
		EScientific,
		ECurrency,
		EPercent,
		ETriad,
		EEndOfFormatsWithDecimalPlaces=ETriad,
		ETrueFalse,
		EText,
		EStartOfFormatsInferrableFromText,
		EDateDM=EStartOfFormatsInferrableFromText,
		EDateMD,
		EDateDdMmYy,
		EDateMmDdYy,
		EDateYyMmDd,
		EDateDMmm,
		EDateDMmmYy,
		EDateDdMmmYy,
		EDateMmm,
		EDateMmmmm,
		EDateMmmYy,
		EDateMmmmmYy,
		EDateMmmmmDYyyy,
		EDateDdMmYy12a,
		EDateDdMmYy24,
		EDateMmDdYy12a,
		EDateMmDdYy24,
		EDateYyMmDd12a,
		EDateYyMmDd24,
		ETime12a,
		ETime12sa,
		ETime24,
		ETime24s,
		ELast=ETime24s,

		EDefaultFormat=EGeneral
		};
	enum
		{
		EDefaultDecimalPlaces=2
		};
public:
	TFormat iFormat;
	TInt iDecimalPlaces;
	};

class CParaFormatLayer;
class CCharFormatLayer;
class CParaFormat;
class TParaFormatMask;
class TCharFormat;
class TCharFormatMask;

class CShgCellAdditionalData : public CBase
	{
public:
	IMPORT_C virtual ~CShgCellAdditionalData();
	IMPORT_C static CShgCellAdditionalData* NewEmptyL();
	IMPORT_C static CShgCellAdditionalData* NewDefaultL();
	IMPORT_C static CShgCellAdditionalData* NewDeepCopyL(const CShgCellAdditionalData* aCellData);
	static CShgCellAdditionalData* NewL(RReadStream& aStream);
public:
	static CShgCellAdditionalData* MergedShgCellAdditionalDataL(const CShgCellAdditionalData* aOldCellData,
																const CShgCellAdditionalData* aDefaultAdditionalData,
																const CShgCellAdditionalData* aChanges);
	void ExternalizeL(RWriteStream& aStream) const;
	static void RemoveUnnecessaryParagraphFormatting(CParaFormatLayer* aParaFormatLayer,TParaFormatMask& aParaMask,const CParaFormat* aParaFormat);
	static void RemoveUnnecessaryCharacterFormatting(CCharFormatLayer* aCharFormatLayer,TCharFormatMask& aCharMask,const TCharFormat& aCharFormat);
private:
	CShgCellAdditionalData();
	void ConstructL();
private:
	enum {EIsParaFormat=0x01,EIsCharFormat=0x02,EIsNumberFormat=0x04};
public:
	CParaFormatLayer* iParaFormatLayer;
	CCharFormatLayer* iCharFormatLayer;
	TShgNumberFormat* iNumberFormat;
	};

class MShgCallBackAPI
	{
public:
	virtual void GetCurrentCell(TInt& aWorkSheetNo,TCellRef& aCellRef) const = 0; //!!! only needed for CELLPOINTER function
	virtual void ReportCellChanged(TInt aWorkSheetNo,const TCellRef& aCellRef) = 0;
	virtual TBool NeedToReportCellChanged(TInt aWorkSheetNo,const TCellRef& aCellRef) const = 0;
	virtual void ReportRecalculationNeeded(TBool aNeeded) = 0;
	virtual void ReportRecalculationInProgress(TBool aInProgress) = 0;
	virtual void ReportCircularDependencyExists(TBool aExists) = 0;
	virtual void DisplayInfoMessage(const TDesC& aMessage) const = 0;
private:
	IMPORT_C virtual void MShgCallBackAPI_Reserved1();
	};

class NShgUtils
	{
public:
	IMPORT_C static void ColumnToText(TDes& aDes,TInt aCol);
	IMPORT_C static void CellRefToText(TDes& aDes,const TCellRef& aCell);
	IMPORT_C static void CellRefToTextAbsolute(TDes& aDes,const TCellRef& aCell);
	IMPORT_C static void ColumnRangeToText(TDes& aDes,TInt aStartCol,TInt aEndCol);
	IMPORT_C static void RowRangeToText(TDes& aDes,TInt aStartRow,TInt aEndRow);
	IMPORT_C static void RangeRefToText(TDes& aDes,const TRangeRef& aRange);
	IMPORT_C static void RangeRefToTextAbsolute(TDes& aDes,const TRangeRef& aRange);
	};

class CFormula;
class TShgCellRef;
class TShgRangeRef;
class TStreamId;
class CStreamStore;
class CShgWorkBook;
class CShgFormulaViewer;
class CShgFormulaSet;
class CSheetEngine;
class CShgNameSet;

class TShgCell
	{
public:
	enum TErrorType
		{
		ENoError,
		EErrNull,			// #NULL!	Null intersection of ranges
		EErrDivByZero,		// #DIV/0!	Formula has tried to divide by zero
		EErrValue,			// #VALUE!	An argument or operand is of the wrong type
		EErrRef,			// #REF!	A cell is refered to that is not valid
		EErrName,			// #NAME?	Unrecognised name is used
		EErrNum,			// #NUM!	Under/Overflow or eg: SQRT(-1)
		EErrNotAvailable	// #N/A		No data available, can be user generated
		};
	enum TType
		{
		EBlank,
		EInt,
		EBool,
		EError,
		EReal,
		EText
		};
public:
	IMPORT_C TShgCell();
	IMPORT_C TShgCell(const TCellRef& aCellRef);
	void SetCoord(const TCellRef& aCellRef);
	IMPORT_C TCellRef Coord() const;
	IMPORT_C TType Type() const;
	void SetBlank();
	IMPORT_C void SetInt(TInt32 aInt);
	IMPORT_C TInt32 Int() const;
	IMPORT_C void SetBool(TBool aBool);
	IMPORT_C TBool Bool() const;
	IMPORT_C void SetErrorType(TErrorType aErrorType);
	IMPORT_C TErrorType ErrorType() const;
	IMPORT_C void SetReal(const TReal64& aReal);
	IMPORT_C TReal64 Real() const;
	IMPORT_C void SetTextTakingOwnership(HBufC* aText);
	IMPORT_C const TDesC& Text() const;
	IMPORT_C void SetFormulaL(CShgFormulaSet* aFormulaSet,const TDesC8& aTokenFormula);
	IMPORT_C void SetFormulaTakingOwnershipL(CShgFormulaSet* aFormulaSet,TDesC8* aTokenFormula);
	IMPORT_C void CloseFormula(CShgFormulaSet* aFormulaSet);
	IMPORT_C const TDesC8* Formula() const; // returns as token formula
	TBool HasIdenticalValueTo(const TShgCell& aCell) const;
public:
	// for use by CShgCellArray
	inline TUint32 Key() const {return iTypeAndFlagsAndRowAndCol&EKeyBits;}
	static inline TUint32 Row(TUint32 aKey) {return aKey>>ERowShift;}
	static inline TUint32 CoordBitsOfKey() {return ERowBits|EColBits;}
	static inline TUint32 MaximumKey() {return ((ESheetMaxRows-1)<<ERowShift)|((ESheetMaxColumns-1)<<EColShift)|(EKeyBits&~(ERowBits|EColBits));}
public:
	// for use by CShgTable and TShgCellIter
	static inline TUint32 MinimumKeyFromCoord(const TCellRef& aCellRef);
	static inline TUint32 MinimumKeyFromCoord(TInt aRow,TInt aCol);
	static inline TUint32 MaximumKeyFromCoord(const TCellRef& aCellRef);
	static inline TUint32 MaximumKeyFromCoord(TInt aRow,TInt aCol);
	inline TCellRef ReturnCoord() const;
	inline TType ReturnType() const;
	inline TBool IsShadow() const;
	inline TBool IsShadowOf(const TShgCell& aRealCell) const;
	inline TBool IsTemporarilyReal() const;
	inline void MakeShadow();
	inline void MakeTemporarilyReal();
	inline void MakeProperlyReal();
private:
	void DoSetFormula(CShgFormulaSet* aFormulaSet,const CFormula* aTokenFormula);
private:
	enum
		{
		ETypeBits			=0xe0000000,
		ETypeShift			=29,
		EFlagsBits			=0x1c000000,
		EFlagsShift			=26,
		EKeyBits			=0x03ffffff,
		ERowBits			=0x03fffc00,
		ERowShift			=10,
		EColBits			=0x000003fc,
		EColShift			=2,
		EIsShadow			=0x00000002,
		EIsTemporarilyReal	=0x00000001
		};
	enum
		{
		EFlagUnprotected		=0x01<<EFlagsShift,
		// the following are only used in streams
		EFlagHasFormula			=0x02<<EFlagsShift,
		EFlagHasAdditionalData	=0x04<<EFlagsShift 
		};
	union UData
		{
		TInt32 iInt;
		TBool iBool;
		TErrorType iErrorType;
		TReal64 iReal;
		HBufC* iText;
		};
private:
	friend class TShgCellStoredForV1;
private:
	TUint32 iTypeAndFlagsAndRowAndCol;
	UData iData;
	const CFormula* iFormula;
	};

class CShgName : public CBase
	{
public:
	enum TType
		{
		EInt,
		EReal,
		EText,
		ECell,
		ERange,
		EFormula,
		EPermanentlyDeleted,
		EError
		};
public:
	virtual ~CShgName();
public:
	static CShgName* NewL(HBufC* aName,TInt32 aInt);
	static CShgName* NewL(HBufC* aName,TReal64 aReal);
	static CShgName* NewL(HBufC* aName,TShgCell::TErrorType aError);
	static CShgName* NewL(HBufC* aName,HBufC* aText);
	static CShgName* NewL(HBufC* aName,TInt aWorkSheetNo,const TCellRef& aCellRef);
	static CShgName* NewL(HBufC* aName,TInt aWorkSheetNo,const TRangeRef& aRangeRef);
	static CShgName* NewL(HBufC* aName,CShgFormulaSet* aFormulaSet,const TDesC8& aFormula);
	static CShgName* NewL(HBufC* aName,const CShgName* aNameToCopyDataFrom);
	static CShgName* NewL(CSheetEngine* aSheetEngine,RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C TPtrC Name() const;
	IMPORT_C void AsTextL(const CShgWorkBook* aWorkBook,TDes& aDes) const;
	IMPORT_C TType Type() const;
	IMPORT_C TInt32 Int() const;
	IMPORT_C TReal64 Real() const;
	IMPORT_C TShgCell::TErrorType Error() const;
	IMPORT_C const TDesC& Text() const;
	IMPORT_C void GetCell(TInt& aWorkSheetNo,TCellRef& aCellRef) const;
	IMPORT_C void GetRange(TInt& aWorkSheetNo,TRangeRef& aRangeRef) const;
	IMPORT_C const TDesC8* Formula() const;
	static TBool NameContainsIllegalCharacters(const TDesC& aName);
	static TBool NameIsAlreadyValidTokenL(const CSheetEngine* aSheetEngine,const TDesC& aName);
	void MakePermanentlyDeleted();
	void ChangeToError(TShgCell::TErrorType aError);
	void SetWorkSheetNoForCellOrRange(TInt aWorkSheetNo);
private:
	union UData
		{
		TInt32 iInt;
		TReal64 iReal;
		TShgCell::TErrorType iError;
		HBufC* iText;
		struct
			{
			TInt iWorkSheetNo;
			TUint8 iCellRef[sizeof(TCellRef)];
			} iCell;
		struct
			{
			TInt iWorkSheetNo;
			TUint8 iRangeRef[sizeof(TRangeRef)];
			} iRange;
		struct
			{
			CShgFormulaSet* iFormulaSet;
			const CFormula* iFormula;
			} iFormula;
		};
	class TCleanupStackableDataWrapper : public TCleanupItem
		{
	public:
		TCleanupStackableDataWrapper(TType aType,UData& aData);
	private:
		static void Cleanup(TAny* aPtr);
	private:
		TType iType;
		UData& iData;
		};
private:
	CShgName(HBufC* aName,TType aType,const UData& aData);
	void DeleteData();
	static void DeleteData(TType aType,UData& aData);
private:
	friend class TCleanupStackableDataWrapper;
private:
	HBufC* iName;
	TType iType;
	UData iData;
	};

typedef TBool (TShgCellRef::*TIsDimensionAbsoluteFunction)() const;

class CShgNameSet : public CBase
	{
public:
	virtual ~CShgNameSet();
	static CShgNameSet* NewL(CSheetEngine* aSheetEngine);
	IMPORT_C TStreamId StoreL(CStreamStore& aStore) const; // previously was exported for test code
	IMPORT_C void RestoreL(const CStreamStore& aStore,TStreamId aStreamId); // previously was exported for test code
	IMPORT_C TShgError AddNameL(const TDesC& aName,const TDesC& aData); // returns EShgNameAlreadyExists if found
	IMPORT_C TShgError ChangeNameL(const TDesC& aName,const TDesC& aData); // returns EShgNameDoesNotExist if not found
	IMPORT_C TShgError RenameNameL(const TDesC& aOldName,const TDesC& aNewName); // returns EShgNameDoesNotExist if aOldName is not found, or EShgNameAlreadyExists if aNewName is found
	IMPORT_C TShgError DeleteNameL(const TDesC& aName);
	IMPORT_C TInt32 FindNameId(const TDesC& aName,TBool aIncludePermanentlyDeletedNames=EFalse) const; // returns KErrNotFound if not found
	IMPORT_C const CShgName* FindName(TInt32 aNameId,TBool aIncludePermanentlyDeletedNames=EFalse) const; // returns NULL if not found
	IMPORT_C TInt Count(TBool aIncludePermanentlyDeletedNames=EFalse) const;
	IMPORT_C const CShgName* operator[](TInt aPhysicalIndex) const;
	TBool HasChanged() const;
	void MarkUnchanged();
	TBool NameHasJustBeenRenamed(TInt32 aNameId) const;
	void Reset();
	void Compress();
	void AdjustAllNamesForCellShiftL(TInt aShiftAmount,TIsDimensionAbsoluteFunction aIsDimensionParallelToShiftAbsolute,TInt TCellRef::* aDimensionParallelToShift,TInt TCellRef::* aDimensionOrthogonalToShift,const TRangeRef& aWholeRangeAffected,const TRangeRef& aRangeShifted,const TRangeRef& aRangeObliterated,TInt aWorkSheetNo);
	void PurgeUnreferencedPermanentlyDeletedNames();
	void WorkSheetIsBeingDeleted(TInt aWorkSheetNo);
public:
	void UndoOperation();
	void RollBackOperation();
	IMPORT_C void StartEditOperation(); // previously was exported for test code
	IMPORT_C void EditOperationComplete(); // previously was exported for test code
private:
	struct SName
		{
		enum
			{
			EFlagRenamed	=0x00000001, // this *must* be the least significant bit
			EFlagAdded		=0x00000002,
			EFlagDeleted	=0x00000004,
			EIdShift		=3
			};
		CShgName* iName;
		TUint32 iIdAndFlags;
		};
	struct SBufferItem
		{
		TPtrC iName;
		enum
			{
			ECell,
			ERange,
			EFormula,
			EError
			} iType;
		union
			{
			struct
				{
				TInt iWorkSheetNo;
				TUint8 iCellRef[sizeof(TCellRef)];
				} iCell;
			struct
				{
				TInt iWorkSheetNo;
				TUint8 iRangeRef[sizeof(TRangeRef)];
				} iRange;
			HBufC8* iFormula;
			TShgCell::TErrorType iError;
			} iData;
		TUint32 iIdOfNewName;
		};
	class CDeepDestructingNameBuffer : public CArrayFixFlat<SBufferItem>
		{
	public:
		CDeepDestructingNameBuffer(TInt aGranularity);
		virtual ~CDeepDestructingNameBuffer();
		};
	enum
		{
		EFlagExistsPermanentlyDeletedNames	=0x01,
		EFlagExistsOutstandingOperations	=0x02,
		EFlagIsInsideEditOperation			=0x04,
		EFlagHasChanged						=0x08
		};
private:
	friend class TShgNameIter;
private:
	CShgNameSet(CSheetEngine* aSheetEngine);
	void ConstructL();
	TShgError DoAddNameL(const TDesC& aName,const TDesC& aData);
	TShgError DoChangeNameL(const TDesC& aName,const TDesC& aData);
	TShgError DoRenameNameL(const TDesC& aOldName,const TDesC& aNewName);
	TShgError DoDeleteName(const TDesC& aName);
	TShgError DeleteName(const TDesC& aName,const SName** aDeletedName);
	TShgError CheckNameOnlyClashesWithPermanentlyDeletedNameAndIfSoDeleteLatter(const TDesC& aName,const SName** aPermanentlyDeletedName);
	void InsertNameL(CShgName* aName,const SName* aNameBeingReplaced,TUint32 aExtraFlagsToSet=0);
	void InsertNameL(CShgName* aName,TUint32 aIdOfNewName,TUint32 aExtraFlagsToSet=0);
	void ReverseAnyOutstandingOperations();
	void CleanupAnyOutstandingOperations();
	TInt PhysicalIndex(TInt aLogicalIndex,TInt& aLastPhysicalIndex,TInt& aLastLogicalIndex,TBool aIncludePermanentlyDeletedNames) const;
	TInt FindNamePhysicalIndex(TInt32 aNameId,TBool aIncludePermanentlyDeletedNames) const; // returns KErrNotFound if not found
	inline static TKeyArrayFix Key() {return TKeyArrayFix(_FOFF(SName,iIdAndFlags),ECmpTUint32);}
#if defined(_DEBUG)
	void CheckKeysAndIdsAreOk() const;
#endif
private:
	CSheetEngine* iSheetEngine;
	CArrayFix<SName>* iArray;
	TUint32 iFlags;
	};

class TShgNameIter
	{
public:
	IMPORT_C TShgNameIter(const CShgNameSet* aNameSet,TBool aIncludePermanentlyDeletedNames=EFalse);
	IMPORT_C void Reset();
	// the next two functions return TInts that are to be passed into CShgNameSet::operator[](TInt aPhysicalIndex)
	IMPORT_C TInt Current(); // returns a negative value when iteration has completed
	IMPORT_C TInt operator++(); // returns a negative value when iteration has completed
private:
	TInt PhysicalIndex(TInt aLogicalIndex);
private:
	const CShgNameSet* iNameSet;
	TInt iLastPhysicalIndex;
	TInt iLastLogicalIndex;
	TBool iIncludePermanentlyDeletedNames;
#if defined(_DEBUG)
	TInt iArrayCount;
#endif
	};

class TShgCellStoredForV1 : public TShgCell
	{
public:
	TShgCellStoredForV1();
	TShgCellStoredForV1(const TCellRef& aCellRef,CShgCellAdditionalData* aAdditionalData=NULL);
	TShgCellStoredForV1(const TShgCell& aCell,CShgCellAdditionalData* aAdditionalData=NULL);
	void CreateDeepCopyL(CShgFormulaSet* aFormulaSet,const TShgCellStoredForV1& aCell);
	void CreateDeepCopyWithoutAdditionalDataL(CShgFormulaSet* aFormulaSet,const TShgCellStoredForV1& aCell);
	void FreeResources(CShgFormulaSet* aFormulaSet);
	void ExternalizeWritingFormulaByDataL(RWriteStream& aStream) const;
	void ExternalizeWritingFormulaByIndexL(RWriteStream& aStream,const CShgFormulaSet* aFormulaSet) const;
	void InternalizeReadingFormulaByDataL(RReadStream& aStream,CShgFormulaSet* aFormulaSet);
	void InternalizeReadingFormulaByIndexL(RReadStream& aStream,CShgFormulaSet* aFormulaSet);
	TBool IsProtected() const;
	void MarkProtected(TBool aMark);
	void SetAdditionalData(CShgCellAdditionalData* aAdditionalData);
	CShgCellAdditionalData* AdditionalData() const;
#if defined(_DEBUG)
	TBool IsInDefaultState() const;
#endif
public:
	// for use by CShgTable and TShgCellIter
	static void SwapRealAndShadow(TShgCellStoredForV1& aRealCell,TShgCellStoredForV1& aShadowCell);
private:
	void DoExternalizeL(RWriteStream& aStream) const;
	void DoInternalizeL(RReadStream& aStream);
private:
	CShgCellAdditionalData* iAdditionalData;
	};

class CShgCellArray : public CBase
	{
public:
	virtual ~CShgCellArray();
	CShgCellArray();
	void Reset();
	void Compress();
	void InsertL(const TShgCellStoredForV1& aCell);
	void Delete(TUint32 aKey);
	void At(TUint32 aKey,TUint32 aKeyMask,TInt& aNumberOfContiguousCellsMatchingMask,TShgCellStoredForV1*& aCells);
#if defined(_DEBUG)
	TBool IsEmpty() const;
#endif
private:
	class HRow;
	typedef HRow* TLevelTwo;
	typedef TLevelTwo* TLevelOne;
#if (1) // so that use of TIter is enforced to be confined to within the DLL for V1; once TShgCellStoredForV1 has gone "public:" can be restored
private:
	friend class TShgCellIter;
	friend class CShgTable;
#else
public:
#endif
	class TIter
		{
	public:
		enum TDirection
			{
			EDirectionForwards,
			EDirectionBackwards
			};
	public:
		inline TIter(CShgCellArray* aCells) : iCell(NULL),iB1(aCells ? aCells->iLevelOne : NULL) {}
		inline void SetToNULL() {iCell=NULL;}
		TShgCellStoredForV1* SetTo(TUint32 aKey,TDirection aDirectionToSearchIfKeyNotFound);
		inline TShgCellStoredForV1* SetToFirst() {return SetTo(0,EDirectionForwards);}
		inline TShgCellStoredForV1* SetToLast() {return SetTo(TShgCell::MaximumKey(),EDirectionBackwards);}
		inline TShgCellStoredForV1* Current() const {return iCell;}
		TShgCellStoredForV1* operator++();
		TShgCellStoredForV1* operator--();
	private:
		TShgCellStoredForV1* SearchForwards(TLevelOne* aP1,TLevelTwo* aP2);
		TShgCellStoredForV1* SearchBackwards(TLevelOne* aP1,TLevelTwo* aP2);
		void Set(TLevelOne* aP1,TLevelTwo* aP2,HRow* aRow);
	private:
		TShgCellStoredForV1* iCell;
		TShgCellStoredForV1* iCellEnd;
		TShgCellStoredForV1* iCellBegin;
		TLevelTwo* iP2;
		TLevelOne* iP1;
		TLevelOne* const iB1;
		};
	friend class TIter;
private:
	enum
		{
		ELevelOneShift=(ESheetNumRowBits>>1)+0, // alter "0" to some other number to move the split
		ELevelTwoBits=(1<<ELevelOneShift)-1,
		ELevelOneSize=1<<(ESheetNumRowBits-ELevelOneShift),
		ELevelTwoSize=1<<ELevelOneShift
		};
	enum
		{
		EFlagMayNeedCompressing	=0x01
		};
private:
	TLevelOne iLevelOne[ELevelOneSize];
	TUint32 iFlags;
	};

class CShgTable;
class CShgWorkSheet;

class TShgCellIter
	{
public:
	enum TStartPoint
		{
		EStartPointFirst,
		EStartPointLast
		};
public:
	TShgCellIter(const CShgTable* aTable,const TRangeRef& aRange,TStartPoint aStartPoint=EStartPointFirst);
	IMPORT_C TShgCellIter(const CShgWorkSheet* aWorkSheet,const TRangeRef& aRange,TStartPoint aStartPoint=EStartPointFirst);
	IMPORT_C void SetToFirst();
	IMPORT_C void SetToLast();
	inline TShgCell* Current() {return iIter.Current();}
	IMPORT_C TShgCell* operator++();
	IMPORT_C TShgCell* operator--();
	TShgCellStoredForV1* CurrentAsShgCellStoredForV1();
	TShgCellStoredForV1* NextAsShgCellStoredForV1();
	TShgCellStoredForV1* PreviousAsShgCellStoredForV1();
private:
	void SetToStartPoint(TStartPoint aStartPoint);
	void StepForwardsOverInvalidCells();
	void StepBackwardsOverInvalidCells();
private:
	CShgCellArray::TIter iIter;
	TRangeRef iRange;
	TBool iIsInsideEditOperation;
	};

class MShgCellReader
	{
public:
	virtual TShgCell* MShgReadCell(const TCellRef& aCellRef) const = 0;
	};

class CShgOrderedArray;
class CShgTable;
class CStreamDictionary;
class CShgCellBuffer;
class CPlainText;
class CGridLay;
class MGridTable;
class CShgGridTable;

class CShgWorkSheet : public CBase, public MShgCellReader
	{
public:
	enum TSearchOrder
		{
		ESearchOrderByRow,
		ESearchOrderByColumn
		};
	enum TSearchDirection
		{
		ESearchDirectionForwards,
		ESearchDirectionBackwards
		};
	enum TSearchThroughWhat // should be OR-ed together by the caller and passed into aWhatToSearchThrough
		{
		ESearchThroughFormulae	=0x01,
		ESearchThroughValues	=0x02,
		ESearchThroughAll		=ESearchThroughFormulae|ESearchThroughValues
		};
	enum TShiftDirection
		{
		EShiftVertically,
		EShiftHorizontally
		};
	enum TShiftRule
		{
		EDeleteCellsInRangeObliterated,
		EDisallowCellsInRangeObliterated
		};
	enum TClearParameters // should be OR-ed together by the caller and passed into aWhatToClear
		{
		EClearContents			=0x01,
		EClearAdditionalData	=0x02,
		EClearAll				=EClearContents|EClearAdditionalData
		};
	enum TPasteWhat // should be OR-ed together by the caller and passed into aWhatToPaste
		{
		EPasteFormula			=0x01,
		EPasteValue				=0x02, // must be set if EPasteFormula bit is set
		EPasteAdditionalData	=0x04,
		EPasteAll				=EPasteFormula|EPasteValue|EPasteAdditionalData
		};
	enum TPasteAction
		{
		EPasteActionOverwrite,
		EPasteActionAdd,
		EPasteActionSubtract,
		EPasteActionMultiply,
		EPasteActionDivide
		};
	enum TSortOrientation
		{
		ESortOrientationTopToBottom,
		ESortOrientationLeftToRight
		};
	struct SSortKey
		{
		enum TDirection
			{
			EDirectionAscending,
			EDirectionDescending
			};
		TInt iCellRefDimensionPerpendicularToSort;
		TDirection iDirection;
		TBool iCaseSensitive;
		};
public:
	virtual ~CShgWorkSheet();
	static CShgWorkSheet* NewLC(CSheetEngine* aSheetEngine,TBool aIsInsideEditOperation);
	TStreamId StoreL(CStreamStore& aStore) const;
	void RestoreL(const CStreamStore& aStore,TStreamId aStreamId);
	TBool HasChanged() const;
	void MarkUnchanged();
	void Reset();
	void Compress();
public:
	IMPORT_C TShgError SortL(const TRangeRef& aRangeRef,const CArrayFix<SSortKey>* aArrayOfSortKeys,TSortOrientation aSortOrientation);
	IMPORT_C const TShgCell* SearchL(const TDesC& aTextToFind,const CArrayFix<TRangeRef>* aRangeArrayToSearchIn,const TCellRef& aStartCell,TBool aIncludeStartCell,TBool aSearchCyclically,TSearchOrder aSearchOrder,TSearchDirection aSearchDirection,TUint32 aWhatToSearchThrough,TBool aMatchCase,TBool aFindEntireCellOnly) const;
	IMPORT_C const TShgCell* SearchL(const TDesC& aTextToFind,const TRangeRef& aRangeToSearchIn,const TCellRef& aStartCell,TBool aIncludeStartCell,TBool aSearchCyclically,TSearchOrder aSearchOrder,TSearchDirection aSearchDirection,TUint32 aWhatToSearchThrough,TBool aMatchCase,TBool aFindEntireCellOnly) const;
	IMPORT_C TShgError ShiftCellsL(const TCellRef& aReferenceCell,TInt aShiftAmount,TInt aExtentOfBlockShifted,TShiftDirection aShiftDirection,TShiftRule aShiftRule);
	IMPORT_C TShgError ClearL(const TCellRef& aCell,TUint32 aWhatToClear=EClearAll);
	IMPORT_C TShgError ClearL(const CArrayFix<TRangeRef>* aRangeArray,TUint32 aWhatToClear=EClearAll);
	IMPORT_C TBool CellWasChangedByLastEditOperation(const TCellRef& aCellRef) const;
	IMPORT_C TShgError UpdateAdditionalDataL(const TCellRef& aCell,const CShgCellAdditionalData* aData);
	IMPORT_C TShgError UpdateAdditionalDataL(const CArrayFix<TRangeRef>* aRangeArray,const CShgCellAdditionalData* aData);

	IMPORT_C const CParaFormatLayer* EffectiveParaFormatRead(const TCellRef& aCell) const;
	IMPORT_C const CParaFormatLayer* EffectiveParaFormat(const TCellRef& aCell,const TShgCell* aShgCell) const;
	IMPORT_C const CCharFormatLayer* EffectiveCharFormatRead(const TCellRef& aCell) const;
	IMPORT_C const CCharFormatLayer* EffectiveCharFormat(const TCellRef& aCell,const TShgCell* aShgCell) const;
	IMPORT_C TShgNumberFormat EffectiveNumberFormatRead(const TCellRef& aCell) const;
	IMPORT_C TShgNumberFormat EffectiveNumberFormat(const TCellRef& aCell,const TShgCell* aShgCell) const;

	IMPORT_C TShgError ProtectL(const TCellRef& aCell,TBool aProtected);
	IMPORT_C TShgError ProtectL(const CArrayFix<TRangeRef>* aRangeArray,TBool aProtected);
	IMPORT_C TBool IsCellProtected(const TCellRef& aCell) const;
	IMPORT_C TBool IsAnyCellInRangeProtected(const TRangeRef& aRange) const;
	IMPORT_C void Lock(TBool aLocked);
	IMPORT_C TBool IsLocked() const;
	IMPORT_C void SetShowZeros(TBool aShowZeros);
	IMPORT_C TBool ShowZeros() const;

	IMPORT_C MGridTable* GridTable() const;
	IMPORT_C CSheetEngine* SheetEngine() const;
	IMPORT_C TShgCell* ReadShgCell(const TCellRef& aCellRef) const;
	IMPORT_C TPtrC ReadFormulaCellTextL(const TShgCell& aCell) const;
	IMPORT_C TShgError SetCellL(const TCellRef& aCellRef,const TDesC& aText);
	IMPORT_C TShgError AddCellInsideEditOperationL(const TShgCell& aCell);
	IMPORT_C TShgError DeleteCellInsideEditOperationL(const TCellRef& aCellRef);

	IMPORT_C void SetNameL(const TDesC& aName);
	void SetNameTakingOwnershipL(HBufC* aName);
	IMPORT_C const TPtrC Name() const;
	void SetWorkSheetNo(TInt aWorkSheetNo);
	IMPORT_C TInt WorkSheetNo() const;
	IMPORT_C TCellRef BottomRight() const;
	IMPORT_C CGridLay* GridLay() const;
	IMPORT_C const CShgCellAdditionalData* DefaultAdditionalData() const;

	IMPORT_C TShgError PasteL(TRangeRef& aBounds,const TRangeRef& aDestination,const CStreamStore& aStore,const CStreamDictionary& aDictionary,TBool aSkipBlanks=EFalse,TUint32 aWhatToPaste=EPasteAll,TPasteAction aPasteAction=EPasteActionOverwrite);
	TShgError PasteNativeDataL(TRangeRef& aBounds,const TRangeRef& aDestination,const CStreamStore& aStore,const CStreamDictionary& aDictionary,TBool aSkipBlanks,TUint32 aWhatToPaste,TPasteAction aPasteAction);
	TShgError PastePlainTextL(TRangeRef& aBounds,const TRangeRef& aDestination,const CStreamStore& aStore,const CStreamDictionary& aDictionary);
	IMPORT_C void CopyL(CStreamStore& aStore,CStreamDictionary& aDictionary,const TCellRef& aCell) const;
	IMPORT_C void CopyL(CStreamStore& aStore,CStreamDictionary& aDictionary,const CArrayFix<TRangeRef>* aRangeArray) const;
	void CopyNativeDataL(CStreamStore& aStore,CStreamDictionary& aDictionary,const TRegion& aRegion) const;
	void CopyPlainTextL(CStreamStore& aStore,CStreamDictionary& aDictionary,const TRegion& aRegion) const;
	TShgCellStoredForV1* ReadShgCellStoredForV1(const TCellRef& aCellRef) const;
	static TBool NameContainsSpaces(const TDesC& aName);
public:
// from MShgCellReader
	virtual TShgCell* MShgReadCell(const TCellRef& aCellRef) const;
private:
	enum TActionForPastePlainText
		{
		EActionCalculateSource,
		EActionPasteCells
		};
	struct SParametersOfActionForPastePlainText
		{
		TRangeRef iSource;
		struct
			{
			TInt iSourceNumRows;
			TInt iNumRowRepetitions;
			TInt iSourceNumCols;
			TInt iNumColRepetitions;
#if defined(_DEBUG)
			const TRangeRef* iBounds;
#endif
			} iPasteData;
		};
	class CSortItem;
	class CDeepDestructingArrayOfSortItems;
private:
	TShgError DoSortL(const TRangeRef& aRangeRef,const CArrayFix<SSortKey>* aArrayOfSortKeys,TSortOrientation aSortOrientation);
	CDeepDestructingArrayOfSortItems* NewPopulatedArrayOfSortItemsLC(const TRangeRef& aRangeRef,const CArrayFix<SSortKey>* aArrayOfSortKeys,TInt TCellRef::* aDimensionParallelToSort,TInt TCellRef::* aDimensionPerpendicularToSort) const;
	void HeapSort(CDeepDestructingArrayOfSortItems* aArrayOfSortItems);
	TShgError CompleteSortL(const TRangeRef& aRangeRef,CDeepDestructingArrayOfSortItems* aArrayOfSortItems,TInt TCellRef::* aDimensionParallelToSort,TInt TCellRef::* aDimensionPerpendicularToSort);
	const TShgCell* DoSearchL(const TDesC& aTextToFind,const TRegion& aRegionToSearchIn,const TCellRef& aStartCell,TBool aIncludeStartCell,TBool aSearchCyclically,TSearchOrder aSearchOrder,TSearchDirection aSearchDirection,TUint32 aWhatToSearchThrough,TBool aMatchCase,TBool aFindEntireCellOnly) const;
	const TShgCell* SearchByRowInRangeL(const TDesC& aTextToFind,const TRegion& aRegionToSearchIn,const TCellRef& aStartCell,TBool aIncludeStartCell,TBool aSearchCyclically,TSearchDirection aSearchDirection,TUint32 aWhatToSearchThrough,TBool aMatchCase,TBool aFindEntireCellOnly) const;
	TShgError DoShiftCellsL(const TCellRef& aReferenceCell,TInt aShiftAmount,TInt aExtentOfBlockShifted,TShiftDirection aShiftDirection,TShiftRule aShiftRule);
	TShgError DoUpdateAdditionalDataL(const TCellRef& aCell,const CShgCellAdditionalData* aData);
	TShgError DoUpdateAdditionalDataL(const CArrayFix<TRangeRef>* aRangeArray,const CShgCellAdditionalData* aData);
	TShgError DoSetCellL(const TCellRef& aCellRef,const TDesC& aText);
	TShgError DoPasteNativeDataL(TRangeRef& aBounds,const TRangeRef& aDestination,const CStreamStore& aStore,const CStreamDictionary& aDictionary,TBool aSkipBlanks,TUint32 aWhatToPaste,TPasteAction aPasteAction);
	void AdjustCellFormulaForImplicitWorksheetNosL(TShgCell& aCell);
	TShgError DoPasteActionForPasteNativeDataL(CShgFormulaSet* aFormulaSet,const TShgCellStoredForV1& aCell,const TCellRef& aCoord,TBool aSkipBlanks,TUint32 aWhatToPaste,TPasteAction aPasteAction);
	TShgError DoPastePlainTextL(TRangeRef& aBounds,const TRangeRef& aDestination,const CStreamStore& aStore,const CStreamDictionary& aDictionary);
	void DoActionForPastePlainTextL(TShgError& aShgError,const TRangeRef& aDestination,const CPlainText* aPlainText,TActionForPastePlainText aActionForPastePlainText,SParametersOfActionForPastePlainText& aParameters);
	static void GetBoundsInfoL(TShgError& aShgError,TInt& aSourceSize,TInt& aNumRepetitions,TRangeRef& aBounds,const TRangeRef& aSource,const TRangeRef& aDestination,TInt TCellRef::* aDimension);
	TShgError EvaluateAndAddCellL(TShgCellStoredForV1& aCell);
	TShgError DoClearL(const TCellRef& aCell,TUint32 aWhatToClear);
	TShgError DoClearL(const CArrayFix<TRangeRef>* aRangeArray,TUint32 aWhatToClear);
	TShgError DoProtectL(const TCellRef& aCell,TBool aProtected);
	TShgError DoProtectL(const CArrayFix<TRangeRef>* aRangeArray,TBool aProtected);
	const CParaFormatLayer* BaseParaFormat(const TCellRef& aCell) const;
	const CCharFormatLayer* BaseCharFormat(const TCellRef& aCell) const;
public:
	const TShgNumberFormat* BaseNumberFormat(const TCellRef& aCell) const;
public:
// Roll-back
	void UndoOperation();
	void StartEditOperation();
	void EditOperationComplete();
	void RollBackOperation();
private:
	TShgError ClearRegionL(const TRegion& aRegion,TUint32 aWhatToClear);
	TInt ApproximateNumCellsAddedByClearL(TRegion& aRegion,CShgOrderedArray* aRowOrColData,TInt TPoint::* aThinDimension,TInt aNumCellsInRowOrCol) const;
	TShgError ClearRowOrColL(CShgCellBuffer* aCellBuffer,TRegion& aRegion,CShgOrderedArray* aRowOrColData,TInt TPoint::* aThinDimension,TInt aNumCellsInRowOrCol,TUint32 aWhatToClear);
	void ClearCellL(CShgCellBuffer* aCellBuffer,const TCellRef& aCellRef,const TShgCellStoredForV1* aCell,TUint32 aWhatToClear);
	TShgError ProtectRegionL(const TRegion& aRegion,TBool aProtected);
	static TInt NumCells(const TRegion& aRegion);
	static void LeaveIfOperationIsTooBigL(const TRegion& aRegion);
	static void LeaveIfOperationIsTooBigL(TInt aNumCells);
	void CopyCellAsNativeDataL(RWriteStream& aStream,const TCellRef& aCell) const;
	void AdjustAllShiftingCellsForCellShiftL(CShgCellBuffer* aCellBuffer,TInt aShiftAmount,TIsDimensionAbsoluteFunction aIsDimensionParallelToShiftAbsolute,TInt TCellRef::* aDimensionParallelToShift,TInt TCellRef::* aDimensionOrthogonalToShift,const TRangeRef& aWholeRangeAffected,const TRangeRef& aRangeShifted,const TRangeRef& aRangeObliterated,TInt aWorkSheetNo);
	void ReverseAnyOutstandingOperations();
	void CleanupAnyOutstandingOperations();
	const CShgCellAdditionalData* DefaultAdditionalData(const TCellRef& aCellRef) const;
public:
	void AdjustCellForCellShiftIfNecessaryL(CShgCellBuffer* aCellBuffer,TInt aShiftAmount,TIsDimensionAbsoluteFunction aIsDimensionParallelToShiftAbsolute,TInt TCellRef::* aDimensionParallelToShift,TInt TCellRef::* aDimensionOrthogonalToShift,const TRangeRef& aWholeRangeAffected,const TRangeRef& aRangeShifted,const TRangeRef& aRangeObliterated,TInt aWorkSheetNo,const TShgCellStoredForV1& aCell,TBool aOwningCellIsInRangeShifted,HBufC8*& aBuffer);
	static void AdjustFormulaForCellShiftIfNecessary(TBool& aAdjustmentWasMade,const TDesC8& aOldFormula,TDes8& aNewFormula,TInt aShiftAmount,TIsDimensionAbsoluteFunction aIsDimensionParallelToShiftAbsolute,TInt TCellRef::* aDimensionParallelToShift,TInt TCellRef::* aDimensionOrthogonalToShift,const TRangeRef& aWholeRangeAffected,const TRangeRef& aRangeShifted,const TRangeRef& aRangeObliterated,TInt aWorkSheetNo,TBool aOwningCellIsInRangeShifted,const TCellRef& aCoordOfOwningCell);
	static void AdjustCellReferenceForCellShiftIfNecessary(TBool& aAdjustmentWasMade,TBool& aCellReferenceIsContainedByRangeObliterated,TShgCellRef& aShgCellRef,TInt aShiftAmount,TIsDimensionAbsoluteFunction aIsDimensionParallelToShiftAbsolute,TInt TCellRef::* aDimensionParallelToShift,const TRangeRef& aWholeRangeAffected,const TRangeRef& aRangeObliterated,TBool aOwningCellIsInRangeShifted,const TCellRef& aCoordOfOwningCell);
	static void AdjustRangeReferenceForCellShiftIfNecessary(TBool& aAdjustmentWasMade,TBool& aRangeReferenceIsContainedByRangeObliterated,TShgRangeRef& aShgRangeRef,TInt aShiftAmount,TIsDimensionAbsoluteFunction aIsDimensionParallelToShiftAbsolute,TInt TCellRef::* aDimensionParallelToShift,TInt TCellRef::* aDimensionOrthogonalToShift,const TRangeRef& aWholeRangeAffected,const TRangeRef& aRangeShifted,const TRangeRef& aRangeObliterated,TBool aOwningCellIsInRangeShifted,const TCellRef& aCoordOfOwningCell);
private:
	static void AdjustReferenceForCellShiftIfNecessary(TBool& aAdjustmentWasMade,TShgCellRef& aShgReference,TInt aShiftAmount,TIsDimensionAbsoluteFunction aIsDimensionParallelToShiftAbsolute,TInt TCellRef::* aDimensionParallelToShift,TBool aOwningCellIsInRangeShifted,TBool aReferenceIsWithinLimits);
	static TBool IsValidWorkSheetName(const TDesC& aName);
private:
	CShgWorkSheet(CSheetEngine* aSheetEngine);
	void ConstructL();
private:
	enum
		{
		EFlagIsInsideEditOperation				=0x01,
		EFlagExistsShadowDefaultAdditionalData	=0x02,
		EFlagHasChanged							=0x04,
		EFlagShowZeros							=0x08
		};
	friend class TTestSheet;
	friend class TShgCellIter;
	friend class CShgAdditionalDataIter;
private:
	CSheetEngine* const iSheetEngine;
	HBufC*			iName;
	CShgTable*		iTable;
	CShgOrderedArray* iRowData;
	CShgOrderedArray* iColData;
	CShgCellAdditionalData* iDefaultAdditionalData;
	CShgCellAdditionalData* iShadowDefaultAdditionalData;
	CGridLay*		iGridLay;
	CShgGridTable*	iGridTable;
	TUint32 iFlags;
	};

class CStreamStore;

class CShgWorkBook : public CBase
	{
public:
	enum TShgInvalidWorkSheetNameChars
		{
		// Not allowed anywhere in worksheet name
		EShgBadCharAsterisk = '*',
		EShgBadCharForwardSlash = '/',
		EShgBadCharBackSlash = '\\',
		EShgBadCharColon = ':',

		// Allowed providing not at start of name
		EShgBadCharOpenSquareBracket = '[',

		// Allowed providing not at start or end of name
		EShgBadCharWorkSheetNameDelimiter = '\''
		};
public:
	virtual ~CShgWorkBook();
	static CShgWorkBook* NewL(CSheetEngine* aEngine);
public:
	inline CSheetEngine* SheetEngine() const {return iSheetEngine;}
	TBool HasChanged() const;
	void MarkUnchanged();
	void Reset();
	void Compress();
	TBool IsLegalWorkSheetNo(TInt aWorkSheetNo) const;
	IMPORT_C TStreamId StoreL(CStreamStore& aStore) const; // previously was exported for test code
	TStreamId StoreWorkSheetNamesL(CStreamStore& aStore) const;
	IMPORT_C void RestoreL(const CStreamStore& aStore,TStreamId aId); // previously was exported for test code
	void RestoreWorkSheetNamesL(const CStreamStore& aStore,TStreamId aStreamId);
	IMPORT_C CShgWorkSheet* WorkSheet(const TDesC& aName) const;
	IMPORT_C CShgWorkSheet* WorkSheet(TInt aWorkSheetNo) const;
	IMPORT_C void SetCurrentWorkSheet(const TDesC& aName);
	IMPORT_C CShgWorkSheet* CurrentWorkSheet() const;
	IMPORT_C TShgError CreateWorkSheetL(const TDesC& aName); // also makes the new worksheet the current one
	IMPORT_C TShgError DeleteWorkSheetL(const TDesC& aName);
	IMPORT_C void ChangeNameL(const TDesC& aOldName,const TDesC& aNewName);
public:
	void UndoOperation();
	IMPORT_C void StartEditOperation(); // previously was exported for test code
	IMPORT_C void EditOperationComplete(); // previously was exported for test code
	void RollBackOperation();
public:
	void AdjustAllFormulaeForCellShiftExceptThoseOfShiftingCellsL(CShgCellBuffer* aCellBuffer,TInt aShiftAmount,TIsDimensionAbsoluteFunction aIsDimensionParallelToShiftAbsolute,TInt TCellRef::* aDimensionParallelToShift,TInt TCellRef::* aDimensionOrthogonalToShift,const TRangeRef& aWholeRangeAffected,const TRangeRef& aRangeShifted,const TRangeRef& aRangeObliterated,TInt aWorkSheetNo);
	IMPORT_C TInt Count() const; // previously was exported for test code
	IMPORT_C TInt WorkSheetNo(const TDesC& aName) const; // previously was exported for test code
	IMPORT_C TInt CurrentWorkSheetNo() const; // previously was exported for test code
private:
	static TBool ValidWorkSheetName(const TDesC& aWorkSheetName);
	TShgError DoCreateWorkSheetL(const TDesC& aName);
	TShgError DoDeleteWorkSheet(const TDesC& aName);
private:
	CShgWorkBook(CSheetEngine* aEngine);
	void ConstructL();
private:
	friend class TShgWorkSheetIter;
private:
	CArrayFix<CShgWorkSheet*>* iWorkSheetArray;
	CSheetEngine*	iSheetEngine;
	CShgWorkSheet*	iCurrentWorkSheet;
	TInt			iCurrentWorkSheetNo;
	};

class TShgWorkSheetIter
	{
public:
	IMPORT_C TShgWorkSheetIter(const CShgWorkBook* aWorkBook);
	IMPORT_C void Reset();
	IMPORT_C const CShgWorkSheet* Current(); // returns NULL when iteration has completed
	IMPORT_C const CShgWorkSheet* operator++(); // returns NULL when iteration has completed
private:
	const CArrayFix<CShgWorkSheet*>* iArray;
	TInt iPhysicalIndex;
	TBool iIsInsideEditOperation; // not currently used
#if defined(_DEBUG)
	TInt iArrayCount;
#endif
	};

class CShgProtectionIter : public CBase
	{
public:
	IMPORT_C static CShgProtectionIter* NewL(const CShgWorkSheet* aWorkSheet,TBool aProtectionSetting);
	IMPORT_C virtual ~CShgProtectionIter();
	IMPORT_C void Reset();
	IMPORT_C const TRangeRef* Current(); // returns NULL when iteration has completed
	IMPORT_C const TRangeRef* operator++(); // returns NULL when iteration has completed
private:
	CShgProtectionIter();
	void ConstructL(const CShgWorkSheet* aWorkSheet,TBool aProtectionSetting);
private:
	TRangeRef iReturnData;
	RRegion iRegion;
	TInt iRectIndex;
#if defined(_DEBUG)
	TInt iRegionCount;
#endif
	};

class CShgAdditionalDataIter : public CBase
	{
public:
	struct SAdditionalData
		{
		TRangeRef iRangeRef;
		const CShgCellAdditionalData* iAdditionalData;
		};
public:
	IMPORT_C static CShgAdditionalDataIter* NewL(const CShgWorkSheet* aWorkSheet);
	IMPORT_C virtual ~CShgAdditionalDataIter();
	IMPORT_C void Reset();
	IMPORT_C const SAdditionalData* CurrentL(); // returns NULL when iteration has completed
	IMPORT_C const SAdditionalData* NextL(); // returns NULL when iteration has completed
private:
	CShgAdditionalDataIter(const CShgWorkSheet* aWorkSheet);
	void SetRowOrCol(const CShgOrderedArray* aArray,TInt TCellRef::* aDimensionOfArray,TInt aRowOrCol);
private:
	enum TPhase
		{
		EPhaseSingleCellsWithAdditionalData,
		EPhaseRowData,
		EPhaseColData
		};
private:
	SAdditionalData iReturnData;
	const CShgWorkSheet* iWorkSheet;
	TPhase iPhase;
	TShgCellIter iIter;
	TInt iRowOrCol;
	RRegion iRegion;
	TInt iRectIndex;
#if defined(_DEBUG)
	TInt iRegionCount;
#endif
	};

class CShgRecalculator;

class CSheetEngine : public CBase
	{
public:
	enum {EForceText='\''};
public:
	IMPORT_C virtual ~CSheetEngine();
	IMPORT_C static CSheetEngine* NewL();
	IMPORT_C static CSheetEngine* NewLC();
	IMPORT_C static CSheetEngine* NewL(CShgCellAdditionalData* aAdditionalData);
	IMPORT_C static CSheetEngine* NewL(CShgCellAdditionalData* aAdditionalData,const TDesC& aResourceFileName);
	IMPORT_C static CSheetEngine* NewL(const TDesC& aResourceFileName);
	IMPORT_C static CSheetEngine* NewEmptyL(const CSheetEngine* aSheetEngine);
protected:
	IMPORT_C CSheetEngine();
	IMPORT_C void ConstructL();
	IMPORT_C void ConstructL(CShgCellAdditionalData* aAdditionalData);
	IMPORT_C void ConstructL(CShgCellAdditionalData* aAdditionalData,const TDesC& aResourceFileName);
	IMPORT_C void ConstructL(const TDesC& aResourceFileName);
	void ConstructEmptyL(const CSheetEngine* aSheetEngine);
public:
	IMPORT_C void SetCallBackAPI(MShgCallBackAPI* aCallBackAPI);
	IMPORT_C void Reset();
	IMPORT_C void LocaleHasChanged();
	IMPORT_C void Compress();
	IMPORT_C TBool HasChanged() const;
	IMPORT_C void MarkUnchanged(); // previously was exported for test code
	IMPORT_C TStreamId StoreL(CStreamStore& aStore) const;
	IMPORT_C void RestoreL(const CStreamStore& aStore,TStreamId aStreamId);
private:
	static void CleanupOperationReset(TAny* aPtr);
public:
	IMPORT_C TShgError CreateCellFromTextL(TShgCell& aCell,const TDesC& aText,const CShgWorkSheet* aWorkSheet);
	TShgError CreateCellStoredForV1FromTextL(TShgCellStoredForV1& aCell,const TDesC& aText,const CShgWorkSheet* aWorkSheet,TBool aTryParseAsDateOrTime=ETrue);
	IMPORT_C void ShgCellAsText(TDes& aDes,const TShgCell& aShgCell) const; // always uses TShgNumberFormat::EDefaultFormat
	IMPORT_C void ShgCellAsText(TDes& aDes,const TShgCell& aShgCell,TInt aWorkSheetNo) const; // uses aShgCell's number-format as found in aWorkSheetNo at coord aShgCell.Coord()
	IMPORT_C void SetRecalculationToBeDoneAutomatically(TBool aRecalculationToBeDoneAutomatically);
	IMPORT_C TBool RecalculationToBeDoneAutomatically() const;
	IMPORT_C void SetRecalculationToBeDoneInBackgroundL(TBool aRecalculationToBeDoneInBackground);
	IMPORT_C TBool RecalculationToBeDoneInBackground() const;
	IMPORT_C void RecalculateL();
	IMPORT_C TBool RecalculationNeeded() const;
	IMPORT_C TBool RecalculationInProgress() const;
	IMPORT_C TBool ExistsCircularDependency() const;
	IMPORT_C void GetAnyCircularDependency(TBool& aKnown,TInt& aWorkSheetNo,TCellRef& aCoord) const;
	IMPORT_C void DisableUndoAndRedo();
	IMPORT_C TBool IsUndoAvailable() const;
	IMPORT_C TBool IsRedoAvailable() const;
	CShgName* CreateNameL(const TDesC& aName,const TDesC& aData) const; // returns NULL if aData is bad
public:
	IMPORT_C CShgNameSet* NameSet() const;
	IMPORT_C void SetCurrentWorkSheet(const TDesC& aName);
	IMPORT_C CShgWorkSheet* CurrentWorkSheet() const;
	IMPORT_C CShgWorkBook* WorkBook() const;

	IMPORT_C TInt SyntaxErrorPos() const;
	TShgError CalculateDatabaseTableL(const TDesC& aRangeText,const TDesC& aCell1,const TDesC& aCell2);

	IMPORT_C CShgFormulaViewer* FormulaViewer() const;
	CShgFormulaSet* FormulaSet() const;

	IMPORT_C void SetTemplateAdditionalDataL(CShgCellAdditionalData* aData);
	IMPORT_C const CShgCellAdditionalData* TemplateAdditionalData() const;
public:
	CShgRecalculator* Recalculator() const;
	MShgCallBackAPI* CallBackAPI() const;
public:
	IMPORT_C void UndoOperationL();
	IMPORT_C void RedoOperationL();
	IMPORT_C void StartEditOperation();
	IMPORT_C TShgError EndEditOperationL(TShgError aShgError);
private:
	void EditOperationCompleteL();
	void RollBackOperation();
	TShgError TryParseAsDateOrTime(TShgCell& aCell,TShgNumberFormat& aNumberFormat,const TDesC& aText);
	void DoShgCellAsText(TDes& aDes,const TShgCell& aShgCell,const TShgNumberFormat& aNumberFormat) const;
public:
	class TCleanupStackableRollBack : public TCleanupItem
		{
	public:
		TCleanupStackableRollBack(CSheetEngine* aSheetEngine);
	private:
		static void Cleanup(TAny* aPtr);
		};
	enum
		{
		EUndoDataAvailable	=0x01,
		ERedoDataAvailable	=0x02
		};
	friend class TCleanupStackableRollBack;
private:
	MShgCallBackAPI* iCallBackAPI;
// following is stored to file
	CShgFormulaSet* iFormulaSet;
	CShgNameSet* iNameSet;
	CShgWorkBook* iWorkBook;
	CShgRecalculator* iRecalculator;
// end of what is stored
	CShgFormulaViewer* iFormulaViewer;
	CShgCellAdditionalData* iTemplateAdditionalData;
	TUint32 iFlags;
	TAny* iSpare; // for if we ship with a derivable CSheetEngine
	};
#endif
