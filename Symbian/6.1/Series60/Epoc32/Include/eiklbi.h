// EIKLBI.H

//

// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.

//



#if !defined(__EIKLBI_H__)

#define __EIKLBI_H__  



#include <e32base.h>

#include <gdi.h>



class CWindowGc;

class CListBoxData;

class TListItemProperties;

class TListFontBoundValues;



/**

 * The CListItemDrawer class is the base class for the list box item drawers which handle

 * drawing of the contents of list box items.

 */

class CListItemDrawer : public CBase

	{

public:

	IMPORT_C ~CListItemDrawer();

	IMPORT_C virtual void DrawItem(TInt aItemIndex, TPoint aItemRectPos, TBool aItemIsSelected, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aViewIsDimmed) const;

	IMPORT_C virtual void ClearRect(const TRect& aRect) const;

	IMPORT_C virtual TInt ItemWidthInPixels(TInt aItemIndex) const;

	IMPORT_C virtual TSize MinimumCellSize() const;

	IMPORT_C virtual void SetGc(CWindowGc* aGc);

	IMPORT_C CWindowGc* Gc() const;

	IMPORT_C virtual void SetMarkColumnWidth(TInt aWidthInPixels);

	IMPORT_C virtual void SetMarkGutter(TInt aGapInPixels);

	IMPORT_C TInt MarkColumn() const;

	IMPORT_C TInt MarkGutter() const;

	IMPORT_C void SetItemCellSize(const TSize& aSizeInPixels);

	IMPORT_C virtual void SetViewRect(const TRect& aRect);

	IMPORT_C void SetDrawMark(TBool aDrawMark);

	IMPORT_C virtual TRect MatcherCursorRect(const TDesC& aMatchableText, TInt aCharPos, TInt aItemCellYPos, TInt aCurrentItemIndex ) const;

	IMPORT_C virtual TInt MatcherCursorAscent( TInt aCurrentItemIndex ) const;

	IMPORT_C virtual void DrawItemMark(TBool aItemIsSelected, TBool aViewIsDimmed, const TPoint& aMarkPos) const;

	IMPORT_C void SetSymbolFont(const CFont* aFont);

	IMPORT_C void SetVerticalInterItemGap(TInt aGapInPixels);

	IMPORT_C void SetData(CListBoxData* aData);

	IMPORT_C CFont* Font(TInt aItemIndex) const;

	IMPORT_C virtual TListItemProperties Properties(TInt aItemIndex) const;


	IMPORT_C void DrawFrame(CWindowGc& aGc,const TRect& aRect,TInt aFlags) const;

public:

	enum TFlags

		{

		EDrawMarkSelection			= 0x0001,

		EPaintedSelection			= 0x0002,

		EDrawOnlyActiveSelection	= 0x0004,

		EDisableHighlight = 0x0008

		};

public:

    enum TListItemAttribute

        {

		ECurrent    = 0x0001,		// may be drawn with a frame

		EEmphasized = 0x0002,		// special highlight (not selected)

		ESelected   = 0x0004,		// usually different than emphasized
		

		// This last attribute is used to control that one can use only

		// valid attributes above. So do not use it at all.

		EMask		= 0x0007 // sum of all others attributes

        };

public:

	inline void SetTextColor(TRgb aColor);

	inline void SetBackColor(TRgb aColor);

	inline void SetHighlightedTextColor(TRgb aColor);

	inline void SetHighlightedBackColor(TRgb aColor);

	inline void SetDimmedTextColor(TRgb aColor);

	inline void SetDimmedBackColor(TRgb aColor);

	inline TRgb TextColor() const;

	inline TRgb BackColor() const;

	inline TRgb HighlightedTextColor() const;

	inline TRgb HighlightedBackColor() const;

	inline TRgb DimmedTextColor() const;

	inline TRgb DimmedBackColor() const;

	inline TInt Flags() const;

	IMPORT_C void SetFlags(TInt aFlags);

	IMPORT_C void ClearFlags(TInt aFlags);

protected:

	IMPORT_C CListItemDrawer();

    virtual void DrawActualItem(TInt aItemIndex, const TRect& aActualItemRect, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aViewIsDimmed, TBool aItemIsSelected) const = 0;

	IMPORT_C virtual void ResetGc() const;

	inline TRgb MarkColor() const;

	IMPORT_C TInt VerticalInterItemGap() const;

    IMPORT_C void SetupGc(TInt aItemIndex) const;

private:

	IMPORT_C virtual TAny* Reserved_1();

    inline TInt& VerticalInterItemGap();

    inline const CFont* SymbolFont() const;

    inline const CFont*& SymbolFont();

protected:

	TSize iItemCellSize;

	TInt iMarkGutter;

	TInt iMarkColumnWidth;

	TRect iViewRect;

	TBool iDrawMark;

	CWindowGc* iGc;

	TRgb iTextColor;

	TRgb iBackColor;

	TRgb iHighlightedTextColor;

	TRgb iHighlightedBackColor;

	TRgb iDimmedTextColor;

	TRgb iDimmedBackColor;

	TRgb iMarkColor;

    CListBoxData* iData;

private:

	const CFont* iSymbolFont;

	TInt iVerticalInterItemGap;

	TInt iSpare;

	TUint iFlags;

	};





class MTextListBoxModel;



/**

 * The CTextListItemDrawer class implements an item drawer which can handle text.

 */

class CTextListItemDrawer : public CListItemDrawer

	{

public:

	IMPORT_C CTextListItemDrawer();

	IMPORT_C ~CTextListItemDrawer();

	IMPORT_C CTextListItemDrawer(MTextListBoxModel* aTextListBoxModel, const CFont* aFont);

	IMPORT_C void ConstructL(const CFont* aFont);

	IMPORT_C virtual void DrawActualItem(TInt aItemIndex, const TRect& aActualItemRect, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aViewIsDimmed,TBool aItemIsSelected) const;

	IMPORT_C virtual TInt ItemWidthInPixels(TInt aItemIndex) const;

	IMPORT_C virtual TSize MinimumCellSize() const;

	IMPORT_C virtual void SetGc(CWindowGc* aGc);

	IMPORT_C void SetCellWidthInChars(TInt aNumOfCharsToDisplayInCell);

    IMPORT_C virtual TRect MatcherCursorRect(const TDesC& aMatchableText, TInt aCharPos, TInt aItemCellYPos, TInt aCurrentItemIndex ) const;

    IMPORT_C virtual TInt MatcherCursorAscent( TInt aCurrentItemIndex ) const;

	IMPORT_C void SetFont(const CFont* aFont);

	IMPORT_C void SetSearchStringL(const TDesC* aSearchString);

	IMPORT_C const CFont* Font(TInt aIndex) const;

 	// SAPLAF new methods.


	inline void SetItemMarkPosition(TInt aPos);

        inline TInt ItemMarkPosition() const;

 	inline void SetItemMarkReplacement(const TDesC &aReplacement);

 	inline TPtrC ItemMarkReplacement() const;

    inline void SetItemMarkReverse(TBool aReverse);
	inline TBool ItemMarkReverse() const;


protected:

    IMPORT_C virtual void DoDrawItemText(const TDesC& aDes, const TRect& aItemTextRect, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aItemIsSelected, TInt aItemIndex) const;

    IMPORT_C virtual void DrawItemText(TInt aItemIndex, const TRect& aItemTextRect, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aItemIsSelected) const;

	IMPORT_C virtual void ResetGc() const;

private:

	IMPORT_C virtual TAny* Reserved_1();

protected:

	MTextListBoxModel* iModel;

	const CFont* iFont;

private:

	TInt iNumOfCharsInCell;

	// AVKON LAF 

	TInt iItemMarkPos;

	TPtrC iItemMarkReplacement;

	TBool iItemMarkReverse;

	// AVKON LAF ENDS 

	};





/**

 * The TListItemProperties class packages together the color and style properties which

 * can be applied when drawing the contents of list box items.

 *

 * @since ER5U

 */

class TListItemProperties

    {

public:

	IMPORT_C TListItemProperties();

public:

    inline void SetBold(TBool aBold);

    inline TBool IsBold() const;

    inline void SetItalics(TBool aItalics);

    inline TBool IsItalics() const;

    inline void SetUnderlined(TBool aUnderlined);

    inline TBool IsUnderlined() const;

    inline void SetDimmed(TBool aDimmed);

    inline TBool IsDimmed() const;

    inline void SetColor(TRgb aColor);

    inline TRgb Color() const;

    inline void SetSeparatorAfter(TBool aSeparator);

    inline TBool IsSeparatorAfter() const;

    inline void SetHiddenSelection(TBool aHidden);

    inline TBool IsSelectionHidden() const;

private:

    TUint iFlags;

    TRgb iColor;

private:

    enum

        {

        ELbxItemBold		= 0x0001,

        ELbxItemItalics		= 0x0002,

        ELbxItemUnderlined	= 0x0004,

	ELbxItemDimmed		= 0x0008,

 	ELbxItemSeparatorAfter  = 0x0010,
	
	ELbxItemSelectionHidden = 0x0020
	
        };

    };



//

// Inlines

//



inline void CListItemDrawer::SetTextColor(TRgb aColor)

	{iTextColor=aColor;}

inline void CListItemDrawer::SetBackColor(TRgb aColor)

	{iBackColor=aColor;}

inline void CListItemDrawer::SetHighlightedTextColor(TRgb aColor)

	{iHighlightedTextColor=aColor;}

inline void CListItemDrawer::SetHighlightedBackColor(TRgb aColor)

	{iHighlightedBackColor=aColor;}

inline void CListItemDrawer::SetDimmedTextColor(TRgb aColor)

	{iDimmedTextColor=aColor;}

inline void CListItemDrawer::SetDimmedBackColor(TRgb aColor)

	{iDimmedBackColor=aColor;}

inline TRgb CListItemDrawer::TextColor() const

	{return iTextColor;}

inline TRgb CListItemDrawer::BackColor() const

	{return iBackColor;}

inline TRgb CListItemDrawer::HighlightedTextColor() const

	{return iHighlightedTextColor;}

inline TRgb CListItemDrawer::HighlightedBackColor() const

	{return iHighlightedBackColor;}

inline TRgb CListItemDrawer::DimmedTextColor() const

	{return iDimmedTextColor;}

inline TRgb CListItemDrawer::DimmedBackColor() const

	{return iDimmedBackColor;}

inline TRgb CListItemDrawer::MarkColor() const

	{return iMarkColor;}

inline TInt CListItemDrawer::Flags() const

	{return iFlags;}



inline TBool TListItemProperties::IsItalics() const

	{return iFlags&ELbxItemItalics;}

inline TBool TListItemProperties::IsBold() const

	{return iFlags&ELbxItemBold;}

inline TBool TListItemProperties::IsUnderlined() const

	{return iFlags&ELbxItemUnderlined;}

inline TBool TListItemProperties::IsDimmed() const

	{return iFlags&ELbxItemDimmed;}

inline TBool TListItemProperties::IsSeparatorAfter() const

 	{return iFlags&ELbxItemSeparatorAfter;}

inline TBool TListItemProperties::IsSelectionHidden() const

 	{return iFlags&ELbxItemSelectionHidden;}



inline void TListItemProperties::SetColor(TRgb aColor)

	{iColor=aColor;}

inline TRgb TListItemProperties::Color() const

    {return iColor;}

inline void TListItemProperties::SetBold(TBool aBold)

    {

    if (aBold) 

		iFlags|=ELbxItemBold;

	else

		iFlags&=(~ELbxItemBold);

    }

inline void TListItemProperties::SetItalics(TBool aItalics)

    {

    if (aItalics)

		iFlags|=ELbxItemItalics;

	else

		iFlags&=(~ELbxItemItalics);

    }

inline void TListItemProperties::SetUnderlined(TBool aUnderlined)

    {

	if (aUnderlined)

		iFlags|=ELbxItemUnderlined;

	else

		iFlags&=(~ELbxItemUnderlined);

    }

inline void TListItemProperties::SetDimmed(TBool aDimmed)

    {

    if (aDimmed)

		iFlags|=ELbxItemDimmed;

	else

		iFlags&=(~ELbxItemDimmed);

    }



inline void TListItemProperties::SetSeparatorAfter(TBool aSeparator)

    {

    if (aSeparator) 

		iFlags|=ELbxItemSeparatorAfter;

	else

		iFlags&=(~ELbxItemSeparatorAfter);

    }


inline void TListItemProperties::SetHiddenSelection(TBool aBlocked)

    {

    if (aBlocked) 

		iFlags|=ELbxItemSelectionHidden;

	else

		iFlags&=(~ELbxItemSelectionHidden);

    }




 

// AVKON LAF 

inline void CTextListItemDrawer::SetItemMarkPosition(TInt aPos) { iItemMarkPos = aPos; }

inline TInt CTextListItemDrawer::ItemMarkPosition() const { return iItemMarkPos; }

inline void CTextListItemDrawer::SetItemMarkReplacement(const TDesC & aReplacement) { iItemMarkReplacement.Set(aReplacement); }

inline TPtrC CTextListItemDrawer::ItemMarkReplacement() const { return iItemMarkReplacement; }

inline void CTextListItemDrawer::SetItemMarkReverse(TBool aReverse) { iItemMarkReverse = aReverse; }
inline TBool CTextListItemDrawer::ItemMarkReverse() const { return iItemMarkReverse; }

// END OF AVKON LAF 



#endif









