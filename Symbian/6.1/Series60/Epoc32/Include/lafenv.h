// LAFENV.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __LAFENV_H__
#define __LAFENV_H__

#include <e32std.h>
#include <e32base.h>
#include <gulbordr.h>
#include <gulalign.h>
#include <lafmain.h>
#include <apgcli.h>
#include <fontids.hrh>
#include <gulfont.h>

#include <BldVariant.hrh>

class MParser;
class CCoeEnv;
class CFont;
class TLogicalFont;


//Avkon specific class that enables matching of font by Uid
class TAknSystemFont
{
public:
	IMPORT_C TAknSystemFont(TUid aUid, CFont* aFont);
	IMPORT_C CFont* Font() const;
	IMPORT_C TUid Uid() const;
private:
	TUid iUid;
	CFont* iFont;
};



/**
 * @internal
 * Do not use
 */
class LafEnv
	{
public:
	IMPORT_C static MParser* CreateTextParserL(TInt aIndex);
	IMPORT_C static void DrawLogicalBorder(const TGulBorder& aBorder,CGraphicsContext& aGc,const TRect& aRect,const TGulBorder::TColors& aBorderColors);
	IMPORT_C static TMargins LogicalBorderMargins(const TGulBorder& aBorder);
	IMPORT_C static void CreateSystemBitmapsL(CCoeEnv& aEnv, CArrayPtrFlat<CFbsBitmap>& aBitmaps);
	IMPORT_C static void CreateSystemFontsL(CCoeEnv& aEnv,CArrayFixFlat<TAknSystemFont>& aFonts);
	IMPORT_C static const CFont* MatchFont(const CArrayFixFlat<TAknSystemFont>& aFonts,const TLogicalFont& aLogicalFont);
	IMPORT_C static CFbsBitmap* MatchBitmap(const CArrayPtrFlat<CFbsBitmap>& aSystemBmps, TUid aBmpUid);
	IMPORT_C static TGulAlignment DefaultBusyMsgCorner();
	IMPORT_C static TBool IsDefaultKey(TUint aCharCode);
	IMPORT_C static TInt DefaultLineSpacingInTwips();
	IMPORT_C static TInt EditableControlStandardHeight(const MLafEnv& aLafEnv);
	IMPORT_C static void PrepareCharFormatAndMask(TCharFormat& aCharFormat,TCharFormatMask& aCharFormatMask);
	IMPORT_C static void GetDefaultPath(TDes& aFilePath,TUid aAppUid,RApaLsSession& aLs,CCoeEnv& aEnv);
public:
	inline static TInt ShadowHeight();
private:
	enum TConstantType
		{
		EShadowHeight
		};
private:
	IMPORT_C static TInt Constant(TConstantType aConstant);

	//this function should only ever be called from within MatchFont. Don' use it elsewhere
	//as a means of getting Fonts.
	static const CFont* GetRightFontFromCategory(const TLogicalFont::TFontCategory aCategory);
	
	static CFont* GetFontFromSystemArray(const CArrayFixFlat<TAknSystemFont>& aSystemFonts, TInt aIdToBeMatched);
	
	};

#define KLafUidNormalFontVal		0x10005F02
#define KLafUidTitleFontVal			0x10005F03
#define KLafUidAnnotationFontVal	0x10005F04
#define KLafUidLegendFontVal		0x10005F05
#define KLafUidSymbolFontVal		0x10005F06
#define KLafUidDenseFontVal			0x10005F07

// identifiers for legacy system bitmaps
#define KLafUidEikonTexturedVal		0x100048F4
#define KLafUidEikonGrayVal			0x100048F5
#define KLafUidEikonOptiVal			0x100048F6
#define KLafUidEikonOptihVal		0x100048F7
#define KLafUidEikonOptimVal		0x100048F8

// Inlines

inline TInt LafEnv::ShadowHeight()
	{//static
	return Constant(EShadowHeight);
	}

#endif
