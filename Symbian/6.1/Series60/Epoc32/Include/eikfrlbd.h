/*
* ============================================================================
*  Name     : Eikfrlbd.h
*  Part of  : Avkon
*
*  Description:
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
//
// EIKFRLBD.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
#if !defined(__EIKFRLBD_H__)
#define __EIKFRLBD_H__

#include <e32base.h>
#include <gdi.h>

#include <eiklbd.h>
#include <eikfrlb.h>

class CWindowGc;
class CGulIcon;

class CFormattedCellListBoxData : public CListBoxData
	{
public:
	class TColors
		{
	public:
		IMPORT_C TColors();
	public:
		TRgb iText;
		TRgb iBack;
		TRgb iHighlightedText;
		TRgb iHighlightedBack;
		TRgb iRightSeparatorColor;
		};
public:
	IMPORT_C static CFormattedCellListBoxData* NewL();
	IMPORT_C ~CFormattedCellListBoxData();
public:
	IMPORT_C const TColors& SubCellColors(TInt aSubCellIndex) const;
	IMPORT_C void SetSubCellColorsL(TInt aSubCellIndex, const TColors &aColors);
	//
	IMPORT_C TInt SubCellBaselinePos(TInt aSubCellIndex) const;
	IMPORT_C void SetSubCellBaselinePosL(TInt aSubCellIndex, TInt aSize);
	//
	IMPORT_C TSize SubCellSize(TInt aSubCellIndex) const;
	IMPORT_C void SetSubCellSizeL(TInt aSubCellIndex, TSize aSize);
	//
	IMPORT_C TPoint SubCellPosition(TInt aSubCellIndex) const;
	IMPORT_C void SetSubCellPositionL(TInt aSubCellIndex, TPoint aPosition);
	//
	IMPORT_C TBool SubCellIsTransparent(TInt aSubCellIndex) const;
	IMPORT_C void SetTransparentSubCellL(TInt aSubCellIndex, TBool aIsTransparent);
	//
	IMPORT_C TBool SubCellIsNotAlwaysDrawn(TInt aSubCellIndex) const;
	IMPORT_C void SetNotAlwaysDrawnSubCellL(TInt aSubCellIndex, TBool aIsNotAlwaysDrawn);
	//
	IMPORT_C TMargins SubCellMargins(TInt aSubCellIndex) const;
	IMPORT_C void SetSubCellMarginsL(TInt aSubCellIndex, TMargins aMargins);
	//
	IMPORT_C const CFont* SubCellFont(TInt aSubCellIndex) const;
	IMPORT_C void SetSubCellFontL(TInt aSubCellIndex, const CFont* aFont);
	//
	IMPORT_C CGraphicsContext::TTextAlign SubCellAlignment(TInt aSubCellIndex) const;
	IMPORT_C void SetSubCellAlignmentL(TInt aSubCellIndex, CGraphicsContext::TTextAlign aAlign);
	//
	IMPORT_C TBool SubCellIsGraphics(TInt aSubCellIndex) const;
	IMPORT_C void SetGraphicsSubCellL(TInt aSubCellIndex, TBool aIsGraphics);
	//
	IMPORT_C CGraphicsContext::TPenStyle SubCellRightSeparatorStyle(TInt aColumn) const;
	IMPORT_C void SetSubCellRightSeparatorStyleL(TInt aSubCell, CGraphicsContext::TPenStyle aStyle);
	//
	IMPORT_C TInt SubCellTextClipGap(TInt aSubCellIndex) const;
	IMPORT_C void SetSubCellTextClipGapL(TInt aSubCellIndex, TInt aSize);
	//
	IMPORT_C CArrayPtr<CGulIcon>* IconArray() const;
	IMPORT_C void SetIconArrayL(CArrayPtr<CGulIcon>* aArray);
	IMPORT_C void SetIconArray(CArrayPtr<CGulIcon>* aArray);
	//
	IMPORT_C CFont* Font(const TListItemProperties& aItemProperties,
			       TInt aSubCellIndex) const;
	
	IMPORT_C virtual void Draw(TListItemProperties aProperties, CWindowGc& aGc,const TDesC* aText,const TRect& aRect,TBool aHighlight, const TColors& aColors) const;

	IMPORT_C TBool UseSubCellColors(TInt aSubCell) const;

private:
	// next methods are only used inside the drawing algorithm.
	// The set methods are also const because they do not change observable behavior of the system.
	TSize SubCellRealSize(TInt aSubCellIndex) const;
	void SetSubCellRealSize(TInt aSubCellIndex, TSize aRealSize) const;
	//
	TSize SubCellRealTextSize(TInt aSubCellIndex) const;
	void SetSubCellRealTextSize(TInt aSubCellIndex, TSize aRealSize) const;
	

	struct SSubCell
		{
		SSubCell() { }
		TInt iSubCell; // Must be first entry
		
		TInt iWidth;
		TMargins iMargin;
		const CFont* iBaseFont;
		TInt iActualFontIndex;
		TBool iGraphics;
		TBool iTransparent;
		TBool iNotAlwaysDrawn;
		CGraphicsContext::TTextAlign iAlign;
		CGraphicsContext::TPenStyle iRightSeparatorStyle;
		
		TPoint iPosition;
		TInt iBaseline;
		TSize iSize;

		TBool iUseSubCellColors; // this is set if someone calls SetSubCellColorsL()
		TColors iColors;
		TInt iTextClipGap;
		// the next ones change during drawing algorithm
		__MUTABLE TSize iRealSize;
		__MUTABLE TSize iRealTextSize;
		};
protected:
	IMPORT_C CFormattedCellListBoxData();
	IMPORT_C void ConstructLD();

	// the next one is here to ease the implementation of settings listbox.
	// it implements the formatted drawing routine.
	IMPORT_C void DrawFormatted(TListItemProperties aProperties, CWindowGc& aGc,const TDesC* aText,const TRect& aRect,TBool aHighlight, const TColors& aColors) const;

private:
	const TColors &Colors(TInt aItemIndex, TInt aSubCell) const;
	TInt LastSubCell() const;
	void AddSubCellL(TInt aSubCell);
	SSubCell& At(TInt aArrayIndex);
	const SSubCell& At(TInt aArrayIndex) const;
	TInt FindSubCellIndex(TInt& aArrayIndex,TInt aSubCell) const;
	void FindSubCellIndexOrAddL(TInt& aArrayIndex,TInt aSubCell);
	TInt AddActualFontL(const CFont* aBaseFont);
private:
	CArrayFix<SSubCell>* iSubCellArray;
	CArrayPtr<CGulIcon>* iIconArray;
	friend class CFormattedCellListBoxItemDrawer; // this is for "lastsubcell" -access.
	TColors defaultcolors;
	TBool iSimpleDrawer;
	};

// Highlight style for setting item editing.
class CSettingItemEditingListBoxData : public CFormattedCellListBoxData
    {
public:
    IMPORT_C static CSettingItemEditingListBoxData* NewL();
    IMPORT_C virtual void Draw(TListItemProperties aProperties,
			       CWindowGc& aGc,
			       const TDesC* aText,
			       const TRect& aRect,
			       TBool aHighlight,
			       const TColors& aColors) const;
    };

// Highlight style for setting item editing.
class CFormGraphicListBoxData : public CFormattedCellListBoxData
    {
public:
    IMPORT_C static CFormGraphicListBoxData* NewL();
    IMPORT_C virtual void Draw(TListItemProperties aProperties,
			       CWindowGc& aGc,
			       const TDesC* aText,
			       const TRect& aRect,
			       TBool aHighlight,
			       const TColors& aColors) const;
    };


class CPopupFormattedListBoxData : public CFormattedCellListBoxData
    {
public:
    IMPORT_C static CPopupFormattedListBoxData* NewL();
    IMPORT_C virtual void Draw(TListItemProperties aProperties,
			       CWindowGc& aGc,
			       const TDesC* aText,
			       const TRect& aRect,
			       TBool aHighlight,
			       const TColors& aColors) const;
    };

class CFormattedCellGridData : public CFormattedCellListBoxData
    {
public:
    IMPORT_C static CFormattedCellGridData* NewL();

    IMPORT_C virtual void Draw(TListItemProperties aProperties,
			       CWindowGc& aGc,
			       const TDesC* aText,
			       const TRect& aRect,
			       TBool aHighlight,
			       const TColors& aColors) const;
    };

#endif



