/*
BIDI.H

Copyright (C) 2000 Symbian Ltd. All rights reserved.
*/

/*
Definitions for bidirectional text reordering.
*/

#ifndef BIDI_H_
#define BIDI_H_ 1

#include <e32std.h>
#include <s32strm.h>

/*
The bidirectional state class. An object of this type carries the embedding level and stack
from one line to the next.
*/
class TBidirectionalState
	{
	public:
	/*
	Objects giving information about a run of characters with the same bidirectional category.
	An array of these representing a line is passed into and reordered by ReorderLine.
	*/
	class TRunInfo
		{
		public:
		TUint iCategory;		// category of a run of text: passed to ReorderLine; these are passed
								// in as TChar::TBdCategory values but are modified for internal use
		TUint8 iEmbeddingLevel;	// embedding level of this run: used internally by ReorderLine
		TUint8 iDirection;		// resolved direction of this run; 0 for left to right, 1 for right to left
		TInt iIndex;			// index of this run after reordering
		TInt iStart;			// start of text; returned by ReorderText
		TInt iLength;			// length of text; returned by ReorderText
		};

	IMPORT_C TBidirectionalState();
	IMPORT_C void ReorderLine(TRunInfo* aRunInfo,TInt aRuns,TBool aParStart,TBool aParEnd,TBool aParRightToLeft,
					 TChar::TBdCategory aNextCategory,TChar::TBdCategory aNextStrongCategory);
	IMPORT_C static TInt ReorderText(const TText* aText,TInt aLength,TBool aParRightToLeft,TText*& aNewText);
	IMPORT_C static void ReverseGroups(TText* aStart,TInt aLength);
	IMPORT_C void Reset();
	IMPORT_C TBool IsDefault() const;
	IMPORT_C TBool operator==(const TBidirectionalState& aState) const;
	IMPORT_C void ExternalizeL(RWriteStream& aDest);
	IMPORT_C void InternalizeL(RReadStream& aSource);

	private:

	// Bidirectional categories coded as bit flags
	enum TCategory
		{
		ELeftToRight = 1 << TChar::ELeftToRight, 
		ELeftToRightEmbedding = 1 << TChar::ELeftToRightEmbedding,
		ELeftToRightOverride = 1 << TChar::ELeftToRightOverride,
		ERightToLeft = 1 << TChar::ERightToLeft,
		ERightToLeftArabic = 1 << TChar::ERightToLeftArabic,
		ERightToLeftEmbedding = 1 << TChar::ERightToLeftEmbedding, 
		ERightToLeftOverride = 1 << TChar::ERightToLeftOverride,
		EPopDirectionalFormat = 1 << TChar::EPopDirectionalFormat, 
		EEuropeanNumber = 1 << TChar::EEuropeanNumber, 
		EEuropeanNumberSeparator = 1 << TChar::EEuropeanNumberSeparator, 
		EEuropeanNumberTerminator = 1 << TChar::EEuropeanNumberTerminator, 
		EArabicNumber = 1 << TChar::EArabicNumber,
		ECommonNumberSeparator = 1 << TChar::ECommonNumberSeparator, 
		ENonSpacingMark = 1 << TChar::ENonSpacingMark, 
		EBoundaryNeutral = 1 << TChar::EBoundaryNeutral, 
		EParagraphSeparator = 1 << TChar::EParagraphSeparator, 
		ESegmentSeparator = 1 << TChar::ESegmentSeparator, 
		EWhitespace = 1 << TChar::EWhitespace, 
		EOtherNeutral = 1 << TChar::EOtherNeutral,

		// categories used internally by the bidirectional algorithm
		EStartOfParagraph = 1 << (TChar::EOtherNeutral + 1),
		EEndOfParagraph = 1 << (TChar::EOtherNeutral + 2),

		// useful groups
		EBdControlsGroup = ELeftToRightEmbedding | ERightToLeftEmbedding |
						   ELeftToRightOverride | ERightToLeftOverride | EPopDirectionalFormat,
		ELeftToRightGroup = ELeftToRight | EEuropeanNumber | ELeftToRightOverride | ELeftToRightEmbedding,
		ERightToLeftGroup = ERightToLeft | EArabicNumber | ERightToLeftArabic | ERightToLeftOverride |
							ERightToLeftEmbedding,
		};

	enum
		{
		EMaxExplicitLevel = 61,
		EMaxLevel = 63,
		EMaxStackLevels = 62
		};

	enum TOverrideState
		{
		ENoOverrideState,
		ELeftToRightOverrideState,
		ERightToLeftOverrideState
		};

	class TStackItem
		{
		public:
		TUint8 iEmbeddingLevel;			// embedding level
		TOverrideState iOverrideState;	// directional override state
		TCategory iStartCategory;		// category that started this level; EOtherNeutral if none
		};

	// The information needed during line reordering.
	class TReorderContext
		{
		public:
		TCategory iNextCategory;			// category at start of next line, or EEndOfParagraph if at start of par
		TCategory iNextStrongCategory;		// L or R; derived from embedding level if at end of par
		TRunInfo* iRunInfo;					// the runs currently being processed
		TInt iRuns;							// the number of runs
		TUint32 iCategories;				// bitmap of the categories present in the data
		};

	const TStackItem& State() const { return iStack[iStackLevel]; }
	void Push(TInt aLevel,TOverrideState aOverrideState,TCategory aStartCategory);
	void HandleBdControls(TReorderContext& aContext); 
	void ResolveWeakTypes(TReorderContext& aContext); 
	void ResolveNeutralTypes(TReorderContext& aContext); 
	void ResolveImplicitLevels(TReorderContext& aContext); 
	void ReorderRuns(TReorderContext& aContext);
	static TInt CatToNumber(TBidirectionalState::TCategory aCat);
	static TInt ReorderText(const TText* aText,TInt aLength,TBool aParRightToLeft,TRunInfo* aRun,TInt aMaxRuns);

	TCategory iPreviousCategory;			// category at end of last line, or EStartOfParagraph if at start of par
	TCategory iPreviousStrongCategory;		// L or R; derived from embedding level if at start of par
	TInt iStackLevel;						// current stack level
	TStackItem iStack[EMaxStackLevels];		// the stack of embedding levels
	};

#endif // BIDI_H_
