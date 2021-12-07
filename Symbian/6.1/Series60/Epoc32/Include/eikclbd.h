// EIKCLBD.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
#if !defined(__EIKCLBD_H__)
#define __EIKCLBD_H__

#include <e32base.h>
#include <gdi.h>

#include <eiklbd.h>

class CWindowGc;
class CGulIcon;

/**
 * The CColumnListBoxData class handles the data required to draw a column list box.
 */
class CColumnListBoxData : public CListBoxData
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
		};
public:
	IMPORT_C static CColumnListBoxData* NewL();
	IMPORT_C ~CColumnListBoxData();
public:
	IMPORT_C TInt LastColumn() const;
	//
	IMPORT_C TInt ColumnWidthPixel(TInt aColumn) const;
	IMPORT_C void SetColumnWidthPixelL(TInt aColumn,TInt aWidth);
	//
	IMPORT_C TInt ColumnHorizontalGap(TInt aColumn) const;
	IMPORT_C void SetColumnHorizontalGapL(TInt aColumn,TInt aGap);
	//
	IMPORT_C TInt ColumnBaselinePos(TInt aColumn) const;
	IMPORT_C void SetColumnBaselinePosL(TInt aColumn,TInt aPos);
	//
	IMPORT_C TMargins ColumnMargins(TInt aColumn) const;
	IMPORT_C void SetColumnMarginsL(TInt aColumn,TMargins aMargins);
	//
	IMPORT_C const CFont* ColumnFont(TInt aColumn) const;
	IMPORT_C void SetColumnFontL(TInt aColumn,const CFont* aFont);
	//
	IMPORT_C CGraphicsContext::TTextAlign ColumnAlignment(TInt aColumn) const;
	IMPORT_C void SetColumnAlignmentL(TInt aColumn,CGraphicsContext::TTextAlign aAlign);
	//
	IMPORT_C CGraphicsContext::TPenStyle ColumnSeparatorStyle(TInt aColumn) const;
	IMPORT_C void SetColumnSeparatorStyleL(TInt aColumn, CGraphicsContext::TPenStyle aStyle);
	//
	IMPORT_C TBool ColumnIsOptional(TInt aColumn) const;
	IMPORT_C void SetOptionalColumnL(TInt aColumn,TBool aIsOptional);
	//
	IMPORT_C TBool ColumnIsGraphics(TInt aColumn) const;
	IMPORT_C void SetGraphicsColumnL(TInt aColumn,TBool aIsGraphics);
	//
	IMPORT_C CArrayPtr<CGulIcon>* IconArray() const;
	IMPORT_C void SetIconArray(CArrayPtr<CGulIcon>* aArray);
	//
	IMPORT_C TInt ColumnTextClipGap(TInt aSubCellIndex) const;
	IMPORT_C void SetColumnTextClipGapL(TInt aSubCellIndex, TInt aSize);
	//
	IMPORT_C CFont* Font(const TListItemProperties& aItemProperties, TInt aColumn) const;
	IMPORT_C TBool MakeColumnRect( TInt aColumn, TRect& aRect );
	IMPORT_C virtual void Draw(const TListItemProperties& aItemProperties, CWindowGc& aGc,const TDesC* aText,const TRect& aRect,TBool aHighlight,const TColors& aColors) const;
	
private:
    struct SColumn
        {
        TInt iColumn; // Must be first entry
        TInt iWidth;
		TMargins iMargins;
        TInt iVerticalCap;
        const CFont* iBaseFont;
        TInt iActualFontIndex;
        TBool iGraphics;
	TBool iOptional;
	TInt iBaseline;
        CGraphicsContext::TTextAlign iAlign;
	CGraphicsContext::TPenStyle iSeparator;
	TInt iTextClipGap;
	// the next are for storing x-coordinates of a column for the drawing algorithm.
	__MUTABLE TInt iX;
	__MUTABLE TInt iEndX;
        };
protected:
	IMPORT_C CColumnListBoxData();
	IMPORT_C void ConstructLD();
private:
	
	IMPORT_C TInt ColumnX(TInt aColumn) const;
	IMPORT_C void SetColumnXL(TInt aColumn,TInt aX) const; // note, const! (do not affect external state)
	//
	IMPORT_C TInt ColumnEndX(TInt aColumn) const;
	IMPORT_C void SetColumnEndXL(TInt aColumn,TInt aEndX) const; // note, Const!

	void AddColumnL(TInt aColumn);
	SColumn& At(TInt aArrayIndex);
	const SColumn& At(TInt aArrayIndex) const;
	TInt FindColumnIndex(TInt& aArrayIndex,TInt aColumn) const;
	void FindColumnIndexOrAddL(TInt& aArrayIndex,TInt aColumn);
	TInt AddActualFontL(const CFont* aBaseFont);
private:
	CArrayFix<SColumn>* iColumnArray;
	CArrayPtr<CGulIcon>* iIconArray;
	};

#endif
