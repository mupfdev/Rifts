/*
* ============================================================================
*  Name     : AknLayoutDef.h
*  Part of  : Avkon Layout
*
*  Description:
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNLAYOUTDEF_H
#define AKNLAYOUTDEF_H

class TAknWindowLineLayout
	{
public:
	IMPORT_C TAknWindowLineLayout(TInt aLineId);
	IMPORT_C TAknWindowLineLayout(TInt aLineId, const TRect& aRect);
	IMPORT_C TAknWindowLineLayout(TInt aLineId, TInt aCOffset, TInt alOffset, TInt atOffset, TInt arOffset, TInt abOffset, TInt aWOffset, TInt aHOffset);
	IMPORT_C TAknWindowLineLayout(TInt aLineId, const TRect& aRect, TInt aCOffset, TInt alOffset, TInt atOffset, TInt arOffset, TInt abOffset, TInt aWOffset, TInt aHOffset);
	IMPORT_C TAknWindowLineLayout(TInt aFirstLineIndex, TInt aLineIndex, TInt aLineSet);
	IMPORT_C TAknWindowLineLayout(TInt aFirstLineIndex, TInt aLineIndex, TInt aLineSet, const TRect& aRect);
	IMPORT_C TAknWindowLineLayout(TInt aFirstLineIndex, TInt aLineIndex, TInt aLineSet, TInt aCOffset, TInt alOffset, TInt atOffset, TInt arOffset, TInt abOffset, TInt aWOffset, TInt aHOffset);
	IMPORT_C TAknWindowLineLayout(TInt aFirstLineIndex, TInt aLineIndex, TInt aLineSet, const TRect& aRect, TInt aCOffset, TInt alOffset, TInt atOffset, TInt arOffset, TInt abOffset, TInt aWOffset, TInt aHOffset);

private:
	void DirectCopy(TInt aLineId);

	void SetlParentOffset(TInt16 aVal, const TRect& aRect);
	void SettParentOffset(TInt16 aVal, const TRect& aRect);
	void SetrParentOffset(TInt16 aVal, const TRect& aRect);
	void SetbParentOffset(TInt16 aVal, const TRect& aRect);
	void SetWParentOffset(TInt16 aVal, const TRect& aRect);
	void SetHParentOffset(TInt16 aVal, const TRect& aRect);
	void SetAllParentOffsets(const TRect& aRect);

protected:
	void CheckLayout();
public:
	TInt16 iC;
	TInt16 il;
	TInt16 it;
	TInt16 ir;
	TInt16 ib;
	TInt16 iW;
	TInt16 iH;
	};


class TAknTextLineLayout
	{
public:
	IMPORT_C TAknTextLineLayout(TInt aLineId);
	IMPORT_C TAknTextLineLayout(TInt aLineId, const TRect& aRect);
	IMPORT_C TAknTextLineLayout(TInt aLineId, TInt aCOffset, TInt alOffset, TInt arOffset, TInt aBOffset, TInt aWOffset, TInt aJOffset, TInt aFontOffset);
	IMPORT_C TAknTextLineLayout(TInt aLineId, const TRect& aRect, TInt aCOffset, TInt alOffset, TInt arOffset, TInt aBOffset, TInt aWOffset, TInt aJOffset, TInt aFontOffset);
	IMPORT_C TAknTextLineLayout(TInt aFirstLineIndex, TInt aLineIndex, TInt aLineSet);
	IMPORT_C TAknTextLineLayout(TInt aFirstLineIndex, TInt aLineIndex, TInt aLineSet, const TRect& aRect);
	IMPORT_C TAknTextLineLayout(TInt aFirstLineIndex, TInt aLineIndex, TInt aLineSet, TInt aCOffset, TInt alOffset, TInt arOffset, TInt aBOffset, TInt aWOffset, TInt aJOffset, TInt aFontOffset);
	IMPORT_C TAknTextLineLayout(TInt aFirstLineIndex, TInt aLineIndex, TInt aLineSet, const TRect& aRect, TInt aCOffset, TInt alOffset, TInt arOffset, TInt aBOffset, TInt aWOffset, TInt aJOffset, TInt aFontOffset);

	IMPORT_C TInt FontId() const;
	IMPORT_C TInt BaselineSkip() const;
	IMPORT_C TInt NumberOfLinesShown() const;

protected:
	void CheckLayout();

private:
	void DirectCopy(TInt aLineId);

	void SetlParentOffset(TInt16 aVal, const TRect& aRect);
	void SetrParentOffset(TInt16 aVal, const TRect& aRect);
	void SetBParentOffset(TInt16 aVal, const TRect& aRect);
	void SetWParentOffset(TInt16 aVal, const TRect& aRect);
	void SetAllParentOffsets(const TRect& aRect);

public:
	TInt16 iC;
	TInt16 il;
	TInt16 ir;
	TInt16 iB;
	TInt16 iW;
	TInt16 iJ;
	TInt16 iFont;

protected:
	TInt iBaselineSkip;
	TInt iNumberOfLinesShown;
	};



class TAknMultiLineTextLayout : public TAknTextLineLayout
	{
public:
	IMPORT_C TAknMultiLineTextLayout(TInt aLineId, TInt aCOffset, TInt alOffset, TInt arOffset, TInt aBOffset, TInt aWOffset, TInt aJOffset, TInt aFontOffset, TInt aNumberOfLinesShown);
	IMPORT_C TAknMultiLineTextLayout(TInt aLineId, const TRect& aRect, TInt aCOffset, TInt alOffset, TInt arOffset, TInt aBOffset, TInt aWOffset, TInt aJOffset, TInt aFontOffset, TInt aNumberOfLinesShown );
	IMPORT_C TAknMultiLineTextLayout(TInt aFirstLineIndex, TInt aLineIndex, TInt aLineSet, TInt aCOffset, TInt alOffset, TInt arOffset, TInt aBOffset, TInt aWOffset, TInt aJOffset, TInt aFontOffset, TInt aNumberOfLinesShown);
	IMPORT_C TAknMultiLineTextLayout(TInt aFirstLineIndex, TInt aLineIndex, TInt aLineSet, const TRect& aRect, TInt aCOffset, TInt alOffset, TInt arOffset, TInt aBOffset, TInt aWOffset, TInt aJOffset, TInt aFontOffset, TInt aNumberOfLinesShown );

protected:
	void CheckMultiLineInfo();

private:
	void CalculateBaselineSkip(TInt aLineId);
	};
#endif
// End of File
