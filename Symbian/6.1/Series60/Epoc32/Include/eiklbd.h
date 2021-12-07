// EIKLBD.H
//
// Copyright (c) 1998-1999 Symbian Ltd.  All rights reserved.
//


#if !defined(__EIKLBD_H__)
#define __EIKLBD_H__

#include <e32base.h>
#include <gdi.h>
#include <w32std.h>
#include <eiklbx.h>

/**
 * The TListFontBoundValues class holds some global properties of the 
 * fonts used in list boxes.
 *
 * @since ER5U
 */
class TListFontBoundValues
    {
public:
    IMPORT_C TListFontBoundValues();
    TInt iMaxNormalCharWidthInPixels;
    TInt iHeightInPixels;
    };

class TListItemProperties;

/**
 * The CListBoxData class is the base class for list box data classes. It stores one
 * or more instances fonts in normal, bold and italic styles.
 *
 * @since ER5U
 */
class CListBoxData : public CBase
    {
friend class CListItemDrawer;
public:
    IMPORT_C CListBoxData();
    IMPORT_C ~CListBoxData();
    IMPORT_C void ConstructL(const CFont* aBaseFont);
    IMPORT_C virtual CFont* Font(const TListItemProperties& aItemProperties) const;
    IMPORT_C void SetupGc(const TListItemProperties& aItemProperties, CWindowGc& aGc) const;
    IMPORT_C const TListFontBoundValues& FontBoundValues() const;
    IMPORT_C TInt SetFontHeight(TInt aFontHeightInTwips);
	IMPORT_C void SetSearchStringL(const TDesC* aSearchString);
	IMPORT_C TBool IsSearchString() const;
	IMPORT_C void DrawItem(CWindowGc& aGc,const TRect& aItemTextRect,const TDesC& aItemText,const CFont& aItemFont,
						const TInt aBaseLineOffset,const CGraphicsContext::TTextAlign aAlign=CGraphicsContext::ELeft) const;
	inline void SetAlignmentL(CGraphicsContext::TTextAlign aAlign);
	inline CGraphicsContext::TTextAlign Alignment() const;
protected:
    class CFontsWithStyle : public CBase
        {
    public:
        CFontsWithStyle();
		~CFontsWithStyle();
	public:
		IMPORT_C void ReleaseFonts();
		IMPORT_C TFontStyle FontStyle();
		IMPORT_C void SetFontStyle(TFontStyle aFontStyle);
        // CArrayPtrFlat<CFont> is used instead of CFont*,
        // because in some subclasses this structure
        // can contain more than 1 font.
        CArrayPtrFlat<CFont>* iFonts;
	private:
		TFontStyle iFontStyle;
        };
    IMPORT_C void ConstructFontL(const CFont* aBaseFont, TFontStyle aFontStyle, CFontsWithStyle& aFonts);
    IMPORT_C void UpdateFontBoundValues(const CFont& aFont);
    IMPORT_C TInt RegenerateFonts(CFontsWithStyle& aFonts, TInt aFontHeightInTwips);
protected:
    CFontsWithStyle iNormalFont;
    CFontsWithStyle iBoldFont;
    CFontsWithStyle iItalicFont;
    CFontsWithStyle iBoldItalicFont;
	HBufC* iSearchString;
private:
    IMPORT_C virtual void Reserved_1();
	IMPORT_C virtual void Reserved_2();
private:
    TListFontBoundValues iFontBoundValues;
	CGraphicsContext::TTextAlign iAlign;
private:
	TAny* iSpare;
    };


inline void CListBoxData::SetAlignmentL(CGraphicsContext::TTextAlign aAlign)
	{iAlign=aAlign;}
inline CGraphicsContext::TTextAlign CListBoxData::Alignment() const
	{return iAlign;}

#endif
