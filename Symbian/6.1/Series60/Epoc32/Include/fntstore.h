// FNTSTORE.H
//
// Copyright (c) 1995-1999 Symbian Ltd. All rights reserved.
//

#ifndef __FNTSTORE_H__
#define __FNTSTORE_H__

#include <e32std.h>
#include <f32file.h>
#include <gdi.h>
#include <openfont.h>

class CFontStoreFile;
class CFontBitmap;
class RReadStream;
class TTypefaceFontBitmap;

class TCharacterMetrics
	{
	public:
	IMPORT_C TCharacterMetrics();

	TInt16 iAscentInPixels;
	TInt16 iHeightInPixels;
	TInt16 iLeftAdjustInPixels;
	TInt16 iMoveInPixels;
	TInt16 iRightAdjustInPixels;
	};

class TAlgStyle
	{
public:
	IMPORT_C TAlgStyle();
	IMPORT_C void SetIsBold(TBool aIsBold);
	IMPORT_C void SetIsItalic(TBool aIsItalic);
	IMPORT_C void SetIsMono(TBool aIsMono);
	IMPORT_C void SetWidthFactor(TInt aWidthFactor);
	IMPORT_C void SetHeightFactor(TInt aHeightFactor);
	IMPORT_C TBool IsBold() const;
	IMPORT_C TBool IsItalic() const;
	IMPORT_C TBool IsMono() const;
	IMPORT_C TInt WidthFactor() const;
	IMPORT_C TInt HeightFactor() const;
	IMPORT_C TBool operator==(const TAlgStyle& aAlgStyle) const;

public:
	TInt iBaselineOffsetInPixels;
private:
	enum
		{
		EBold=1,
		EItalic=2,
		EMono=4,
		};
    TInt8 iFlags;
	TInt8 iWidthFactor;
	TInt8 iHeightFactor;
	};

class CBitmapFont : public CFont
	{
	friend class CFontStore;
private:
	CBitmapFont(RHeap* aHeap,const TFontSpec& aFontSpecInTwips,const TAlgStyle& aAlgStyle,CFontBitmap* aFontBitmap);
	CBitmapFont(RHeap* aHeap,const TFontSpec& aFontSpecInTwips,const TAlgStyle& aAlgStyle,COpenFont* aOpenFont);
	void ConstructL();
	~CBitmapFont();
	IMPORT_C static CBitmapFont* NewL(RHeap* aHeap,const TFontSpec& aFontSpecInTwips,const TAlgStyle& aAlgStyle,CFontBitmap* aFontBitmap);
	static CBitmapFont* NewL(RHeap* aHeap,const TFontSpec& aFontSpecInTwips,const TAlgStyle& aAlgStyle,COpenFont* aOpenFont);
public:
	IMPORT_C TUid TypeUid() const;
	TUid Uid() const;
	IMPORT_C TInt HeightInPixels() const;
	IMPORT_C TInt AscentInPixels() const;
	IMPORT_C TInt CharWidthInPixels(TChar aChar) const;
	IMPORT_C TInt TextWidthInPixels(const TDesC &aText) const;
	IMPORT_C TInt BaselineOffsetInPixels() const;
	IMPORT_C TInt TextCount(const TDesC &aText,TInt aWidthInPixels) const;
	IMPORT_C TInt TextCount(const TDesC &aText,TInt aWidthInPixels,TInt &aExcessWidthInPixels) const;
	IMPORT_C TInt MaxCharWidthInPixels() const;
	IMPORT_C TInt MaxNormalCharWidthInPixels() const;
	IMPORT_C TFontSpec FontSpecInTwips() const;
	IMPORT_C TCharacterMetrics CharacterMetrics(TInt aCode,const TUint8*& aBytes) const;
	IMPORT_C TBool GetCharacterData(TInt aSessionHandle,TInt aCode,TOpenFontCharMetrics& aMetrics,
									const TUint8*& aBitmap) const;
	IMPORT_C TBool Rasterize(TInt aSessionHandle,TInt aCode,TOpenFontGlyphData* aGlyphData) const;
	IMPORT_C void GetFontMetrics(TOpenFontMetrics& aMetrics) const;
	IMPORT_C TBool GetFaceAttrib(TOpenFontFaceAttrib& aAttrib) const;
	IMPORT_C TInt BitmapEncoding() const;
	IMPORT_C TBool HasCharacterL(TInt aCode) const;
	IMPORT_C TBool CharacterNeedsToBeRasterized(TInt aSessionHandle,TInt aCode) const;
	IMPORT_C void operator delete(TAny*);
	inline TBool IsOpenFont() const;
	inline COpenFont* OpenFont() const;
private:
	TInt Width(TInt aNum) const;
	TInt Height(TInt aNum) const;
	CFontBitmap* FontBitmap() const;
private:
	TFontSpec iFontSpecInTwips;
public:
	TAlgStyle iAlgStyle;	// must not move this member
private:
	RHeap* iHeap;
	TInt iFontBitmapOffset;
	COpenFont* iOpenFont;	// if iOpenFont is non-null this is an open font and many functions are forwarded to it
	};

class CFontStore : public CTypefaceStore
    {
private:
	CFontStore();
	void ConstructL();
public:
	IMPORT_C static CFontStore* NewL(RHeap* aHeap);
	IMPORT_C ~CFontStore();
	IMPORT_C TUid AddFileL(const TDesC& aName);
	IMPORT_C void RemoveFile(TUid aFileUid);
	IMPORT_C TInt GetNearestFontInTwips(CFont *&aFont,const TFontSpec& aFontSpec);
	IMPORT_C TInt GetNearestFontInPixels(CFont *&aFont,const TFontSpec &aFontSpec);
	IMPORT_C TInt GetNearestFontInTwips(CFont *&aFont,const TOpenFontSpec& aFontSpec);
	IMPORT_C TInt GetNearestFontInPixels(CFont *&aFont,const TOpenFontSpec &aFontSpec);
 	IMPORT_C TInt GetFontById(CFont *&aFont,TUid aUid,const TAlgStyle& aAlgStyle);
	IMPORT_C TInt NumTypefaces() const;
	IMPORT_C void TypefaceSupport(TTypefaceSupport &aTypefaceSupport,TInt aTypefaceIndex) const;
	IMPORT_C TInt FontHeightInTwips(TInt aTypefaceIndex,TInt aHeightIndex) const;
	IMPORT_C TInt FontHeightInPixels(TInt aTypefaceIndex,TInt aHeightIndex) const;
	IMPORT_C void InstallRasterizerL(COpenFontRasterizer* aRasterizer);
	IMPORT_C void DeleteSessionCache(TInt aSessionHandle);
private:
	void InternalizeFontStoreFileL(CFontStoreFile* aFontStoreFile);
	TTypeface* GetNearestTypeface(const TTypeface& aTypeface) const;
	TTypefaceFontBitmap GetNearestTypefaceFontBitmap(const TFontSpec& aFontSpecInPixels);
	CFontBitmap* GetFontBitmapById(TUid aUid);
	CBitmapFont* FindFont(const TFontSpec& aFontSpecInPixels,const TAlgStyle& aAlgStyle,TUid aUid) const;
	CBitmapFont* FindFont(const TOpenFontSpec& aFontSpecInPixels,const TAlgStyle& aAlgStyle) const;
	CBitmapFont* NewFontL(const TFontSpec& aFontSpecInTwips,const TAlgStyle& aAlgStyle,CFontBitmap* aFontBitmap);
	CBitmapFont* NewFontL(const TOpenFontSpec& aFontSpecInTwips,const TAlgStyle& aAlgStyle,COpenFont* aOpenFont);
	TInt VerticalPixelsToTwips(TInt aPixelHeight) const;
	TInt VerticalTwipsToPixels(TInt aTwipsHeight) const;
	TInt GetNearestBitmapFontInPixels(CBitmapFont *&aFont,TFontSpec &aFontSpec);
	TInt GetNearestOpenFontInPixels(CBitmapFont *&aFont,TOpenFontSpec &aFontSpec,
									const TOpenFontSpec& aIdealFontSpecInPixels);
	void UpdateTypefaceSupportListL();

public:
	TInt iKPixelWidthInTwips;
	TInt iKPixelHeightInTwips;
private:
	RFs iFs;
	RHeap* iHeap;
	CArrayPtrFlat<CFontStoreFile> iFontStoreFileList;
	CArrayPtrFlat<TTypeface> iTypefaceList;
	CArrayPtrFlat<CFontBitmap> iFontBitmapList;
	CArrayFixFlat<TTypefaceFontBitmap> iTypefaceFontBitmapList;
	CArrayPtrFlat<COpenFontFile> iOpenFontFileList;
	CArrayFixFlat<TTypefaceSupport> iOpenFontTypefaceSupportList;
	CArrayPtrFlat<COpenFontRasterizer> iOpenFontRasterizerList;
	COpenFontSessionCacheList* iOpenFontSessionCacheList;
	TInt iOpenFontUid;
	};

// inline functions start here
inline TBool CBitmapFont::IsOpenFont() const
	{
	return iOpenFont != NULL;
	}

inline COpenFont* CBitmapFont::OpenFont() const
	{
	return iOpenFont;
	}

#endif
