// GULFONT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__GULFONT_H__)
#define __GULFONT_H__

#include <gdi.h>
#include <w32std.h>

class TResourceReader;

/**
 * The TLogicalFont class packages arrtibutes of a logical font.  iFontId may not be the same as the uid
 * used to create the font and should be used to access a known font directly by most ROM based apps.
 */
class TLogicalFont
	{
public:
	enum TFontCategory
		{
		EView,
		EButton,
		EAnnotation,
		ETitle
		};
	enum TFontStyle
		{
		ENormal,
		EBold,
		EItalic,
		EBoldItalic,
		ESuperscript,
		ESubscript,
		ELight,
		ECustom
		};
public:
	IMPORT_C TLogicalFont();
	IMPORT_C TLogicalFont(TUid aId);
	IMPORT_C TLogicalFont(TFontCategory aCategory,TFontStyle aStyle,const TZoomFactor& aZoomFactor);
	IMPORT_C TLogicalFont(TUid aId,TFontCategory aCategory,TFontStyle aStyle,const TZoomFactor& aZoomFactor);
public:
	TUid iFontId;
	TFontCategory iCategory;
	TFontStyle iStyle;
	TZoomFactor iZoomFactor;
	};

class CCleanupStackableFont : public CBase
	{
public:
	IMPORT_C static CCleanupStackableFont* NewL(TResourceReader& aReader,CWsScreenDevice& aScreenDevice);
	IMPORT_C static CCleanupStackableFont* NewLC(TResourceReader& aReader,CWsScreenDevice& aScreenDevice);
	IMPORT_C static CCleanupStackableFont* NewByNameL(TResourceReader& aReader,CWsScreenDevice& aScreenDevice);
	IMPORT_C static CCleanupStackableFont* NewByNameLC(TResourceReader& aReader,CWsScreenDevice& aScreenDevice);
	IMPORT_C virtual ~CCleanupStackableFont();
public:
	IMPORT_C CFbsFont& Font() const;
	IMPORT_C CFbsFont* TakeOwnershipOfFont();
private:
	CCleanupStackableFont(CWsScreenDevice& aScreenDevice);
	static CCleanupStackableFont* NewLC(TBool aByUid,TResourceReader& aReader, CWsScreenDevice& aScreenDevice);
private:
	CWsScreenDevice& iScreenDevice;
	CFbsFont* iFont;
	};

#endif
