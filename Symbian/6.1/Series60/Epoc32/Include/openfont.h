// OPENFONT.H
//
// Copyright (c) 1998-1999 Symbian Ltd. All rights reserved.
//

/*
A header for the open font system, which allows
EPOC32 to use fonts of arbitrary types, including TrueType
and other outline font formats.
*/

#ifndef __OPENFONT_H__
#define __OPENFONT_H__ 1

#include <e32base.h>
#include <gdi.h>

class CFont;
class COpenFontFile;
class COpenFontGlyph;
class COpenFontGlyphCache;
class COpenFontGlyphTreeEntry;
class COpenFontPositioner;
class COpenFontSessionCache;
class COpenFontSessionCacheList;
class RFs;
class TCharacterMetrics;
class TFontSpec;
class TOpenFontFaceAttrib;

/*
The 2nd UID (the interface type) of DLLs implementing the OpenFont interface,
which is a single exported function at ordinal 1 that creates a
COpenFontRasterizer object.
*/
const TInt KUidOpenFontRasterizerValue = 0x10003B1F;

// One of these should be used as the 3rd UID of DLLs implementing the OpenFont interface.
const TInt KUidTrueTypeRasterizerValue = 0x100012A7;
const TInt KUidBitstreamTrueDocRasterizerValue = 0x100012A8;
const TInt KUidAdobeType1RasterizerValue = 0x100012A9;
const TInt KUidAgfaMicroTypeRasterizerValue = 0x10001827;

/*
KReplacementCharacter is a Private Use Area codepoint for a character to be displayed in place of
a character that is not present in a font. If KReplacementCharacter exists in a font, it will be used,
otherwise whatever the rasterizer does by default will be used. For example, TrueType fonts return
glyph index 0 for nonexistent characters, and that is usually, but not always, mapped to an
empty rectangle.
*/
const TUint KReplacementCharacter = 0xF6DB;

/**
 * KFillCharacterOffset is a significant offset that is set when a character within a code section is 
 * not in the font. This means that for these fill characters nothing is stored within the binary
 * data part of the code section.
 */
const TInt KFillCharacterOffset = 0x7FFF;

// Font metrics
class TOpenFontMetrics
	{
	public:
	inline TOpenFontMetrics();
	IMPORT_C TOpenFontMetrics(const CFont* aFont);
	inline TInt Size() const;
	inline TInt Ascent() const;
	inline TInt Descent() const;
	inline TInt MaxHeight() const;
	inline TInt MaxDepth() const;
	inline TInt MaxWidth() const;
	inline void SetSize(TInt aSize);
	inline void SetAscent(TInt aAscent);
	inline void SetDescent(TInt aDescent);
	inline void SetMaxHeight(TInt aMaxHeight);
	inline void SetMaxDepth(TInt aMaxDepth);
	inline void SetMaxWidth(TInt aMaxWidth);

	private:
	TInt16 iSize;			// size of the font ('pointsize' or 'design height' in pixels)
	TInt16 iAscent;			// typographic ascent
	TInt16 iDescent;		// typographic descent
	TInt16 iMaxHeight;		// maximum height of a character; may be greater than iAscent
	TInt16 iMaxDepth;		// maximum depth of a character; may be greater than iDescent
	TInt16 iMaxWidth;		// maximum width of a character
	TInt32 iReserved;
	};

// Character metrics allowing characters to be placed horizontally or vertically.
class TOpenFontCharMetrics
	{
	public:
	inline TOpenFontCharMetrics();
	IMPORT_C TOpenFontCharMetrics(const TCharacterMetrics& aMetrics);
	IMPORT_C TBool GetTCharacterMetrics(TCharacterMetrics& aMetrics) const;
	inline TInt Width() const;
	inline TInt Height() const;
	inline TInt HorizBearingX() const;
	inline TInt HorizBearingY() const;
	inline TInt HorizAdvance() const;
	inline TInt VertBearingX() const;
	inline TInt VertBearingY() const;
	inline TInt VertAdvance() const;
	inline void GetHorizBounds(TRect& aBounds) const;
	inline void GetVertBounds(TRect& aBounds) const;
	inline void SetWidth(TInt aWidth);
	inline void SetHeight(TInt aHeight);
	inline void SetHorizBearingX(TInt aHorizBearingX);
	inline void SetHorizBearingY(TInt aHorizBearingY);
	inline void SetHorizAdvance(TInt aHorizAdvance);
	inline void SetVertBearingX(TInt aVertBearingX);
	inline void SetVertBearingY(TInt aVertBearingY);
	inline void SetVertAdvance(TInt aVertAdvance);

	private:
	TInt16 iWidth;			// width of the glyph
	TInt16 iHeight;			// height of the glyph
	TInt16 iHorizBearingX;	// x component of horizontal bearing
	TInt16 iHorizBearingY;	// y component of horizontal bearing
	TInt16 iHorizAdvance;	// horizontal advance
	TInt16 iVertBearingX;	// x component of vertical bearing
	TInt16 iVertBearingY;	// y component of vertical bearing
	TInt16 iVertAdvance;	// vertical advance
	TInt32 iReserved;
	};

// An object used by rasterizers to supply glyph data to FBSERV clients.
class TOpenFontGlyphData
	{
	public:
	IMPORT_C static TOpenFontGlyphData* New(RHeap* aHeap,TInt aBufferSize);
	inline TBool Overflow() const;
	inline TInt BytesNeeded() const;
	inline TPtrC8 Bitmap() const;
	inline const TUint8* BitmapPointer() const;
	inline const TOpenFontCharMetrics* Metrics() const;
	inline TInt GlyphIndex() const;
	inline TUint8* BufferStart();
	inline TUint8* BufferEnd();
	inline void SetBytesNeeded(TInt aBytes);
	inline void SetBitmapPointer(const TUint8* aBitmap);
	inline void SetMetricsPointer(const TOpenFontCharMetrics* aMetrics);
	inline void SetPointersToInternalBuffers();
	inline void SetMetrics(TOpenFontCharMetrics& aMetrics);
	inline void SetGlyphIndex(TInt aGlyphIndex);

	private:
	/*
	Prevent construction and destruction by normal means; the object resides on a specified heap.
	and is created by New and deleted by RHeap::Free.
	*/
	TOpenFontGlyphData();
	~TOpenFontGlyphData();

	TInt iBitmapBufferSize;					// size of the buffer in bytes
	TInt iBytesNeeded;						// bytes needed for the bitmap
	TOpenFontCharMetrics iMetricsBuffer;	// the metrics
	const TUint8* iBitmap;					// pointer to the bitmap; points either to iBitmapBuffer or to
											// the cache if the character was already rasterized
	const TOpenFontCharMetrics* iMetrics;	// pointer to the metrics; points either to iMetricsBuffer or to
											// the cache if the character was already rasterized
	TInt iGlyphIndex;						// the glyph index
	TAny* iReserved;						// unused; for future expansion
	TUint8 iBitmapBuffer[1];				// buffer used to write the bitmap when it is first rasterized; this
											// is actually of size iBitmapBufferSize.
	};

// A base class for new-style fonts.
class COpenFont: public CBase
	{
	public:

	// virtual functions
	virtual void RasterizeL(TInt aCode,TOpenFontGlyphData* aGlyphData) = 0;
	IMPORT_C virtual void Reserved(); // unused; for future expansion

	// exported functions
	IMPORT_C COpenFont(RHeap* aHeap,COpenFontSessionCacheList* aSessionCacheList,COpenFontFile* aFile);
	IMPORT_C COpenFont(RHeap* aHeap,COpenFontSessionCacheList* aSessionCacheList,COpenFontFile* aFile,TInt aFaceIndex);
	IMPORT_C ~COpenFont();
	IMPORT_C void operator delete(TAny*);

	// inline functions
	inline const TOpenFontMetrics& Metrics() const;
	inline const TOpenFontFaceAttrib* FaceAttrib() const;
	inline COpenFontFile* File() const;
	inline TInt FaceIndex() const;
	inline TBool CharacterNeedsToBeRasterized(TInt aSessionHandle,TInt aCode) const;

	// other public functions
	TBool Rasterize(TInt aSessionHandle,TInt aCode,TOpenFontGlyphData* aGlyphData);
	TBool HasCharacterL(TInt aCode) const;
	TBool GetCharacterData(TInt aSessionHandle,TInt aCode,const TOpenFontCharMetrics*& aMetrics,
						   const TUint8*& aBitmap) const;
	void OnFileDeleted();

	protected:
	RHeap* iHeap;
	TOpenFontMetrics iMetrics;
	const COpenFontPositioner* iPositioner;					// the character positioning information; owned by the
															// file, but placed in shared memory and accessed
															// from the client side, so cannot be accessed via iFile

	private:
	const COpenFontGlyph* Glyph(TInt aSessionHandle,TInt aCode) const;
	const COpenFontGlyph* FontCacheGlyph(TInt aCode,COpenFontGlyphTreeEntry**& aNode);
	const COpenFontGlyph* SessionCacheGlyph(RHeap* aHeap,TInt aSessionHandle,TInt aCode,
											COpenFontSessionCache*& aCache,TInt& aIndex,TBool aCreate) const;
	void RasterizeHelperL(TInt aCode,TOpenFontGlyphData* aGlyphData,TOpenFontGlyphData*& aTempGlyphData);

	COpenFontFile* iFile;									// the file used by this font; null if it has been deleted
															// or cannot be used
	TInt iFaceIndex;										// index of the face in the font file
	COpenFontGlyphCache* iGlyphCache;						// the per-font glyph cache; owned by the font
	COpenFontSessionCacheList* iSessionCacheList;			// the list of per-session glyph caches; owned by CFontStore
	TAny* iReserved; // unused; for future expansion
	};

// A base class used for TOpenFontFaceAttrib and TOpenFontSpec
class TOpenFontFaceAttribBase
	{
	public:
	inline TOpenFontFaceAttribBase();
	inline TBool HasLatin() const;
	inline TBool HasGreek() const;
	inline TBool HasCyrillic() const;
	inline TBool HasKana() const;
	inline TBool HasHangul() const;
	inline TBool HasCJK() const;
	inline TBool IsSymbol() const;
	inline TBool IsBold() const;
	inline TBool IsItalic() const;
	inline TBool IsSerif() const;
	inline TBool IsMonoWidth() const;
	inline TPtrC Name() const;
	inline const TUint* Coverage() const;
	inline void SetName(const TDesC& aName);
	inline void SetCoverage(TUint aCoverage0,TUint aCoverage1 = 0,TUint aCoverage2 = 0,TUint aCoverage3 = 0);
	inline void SetBold(TBool aBold);
	inline void SetItalic(TBool aItalic);
	inline void SetSerif(TBool aSerif);
	inline void SetMonoWidth(TBool aMonoWidth);
	inline TBool operator==(const TOpenFontFaceAttribBase& aAttrib) const;

	// Unicode ranges for iCoverage[0] (incomplete; see the TrueType documentation for other values)
	enum
		{
		ELatinSet = 0x1,			// 0000-007F
		EGreekSet = 0x80,			// 0370-03FF
		ECyrillicSet = 0x200,		// 0400-04FF
		EArmenianSet = 0x400,		// 0530-058F
		EHebrewSet = 0x800,			// 0590-05FF
		EArabicSet = 0x2000,		// 0600-06FF
		EDevanagariSet = 0x8000,	// 0900-097F
		EBengaliSet = 0x10000,		// 0980-09FF
		EGurmukhiSet = 0x20000,		// 0A00-0A7F
		EGujuratiSet = 0x40000,		// 0A80-0AFF
		EOriyaSet = 0x80000,		// 0B00-0B7F
		ETamilSet = 0x100000,		// 0B80-0BFF
		ETeluguSet = 0x200000,		// 0C00-0C7F
		EKannadaSet = 0x400000,		// 0C80-0CFF
		EMalayalamSet = 0x800000,	// 0D00-0D7F
		EThaiSet = 0x1000000,		// 0E00-0E7F
		ELaoSet = 0x2000000,		// 0E80-0EFF
		EGeorgianSet = 0x8000000,	// 10A0-10FF
		EHangulJamoSet = 0x10000000,// 1100-11FF
		};

	// Unicode ranges for iCoverage[1]
	enum
		{
		ESymbolSets = 0xFFFE,
		EKanaSets = 0x60000,
		EHangulSet = 0x100000,
		ECJKSet = 0x8000000
		};

	// Attribute flags
	enum
		{
		EBold = 0x1,			// weight > 500 in Windows terms
		EItalic = 0x2,			// italic or oblique - any forward slant counts
		ESerif = 0x4,			// characters have serifs
		EMonoWidth = 0x8		// all characters are the same width
		};

	// Other constants
	enum
		{
		ENameLength = 32		// we allow 32 but names that are compatible with old-style fonts are limited to 24
		};

	protected:
	TBufC<ENameLength> iName;				// the name of the typeface; whether this is the full name or family name
											// or is in English or another language depends on the context
	TUint iCoverage[4];						// bitmap of the character sets supported by the typeface;
											// these are the same as the fields ulUnicodeRange1 .. ulUnicodeRange4
											// in the OS/2 table in TrueType fonts
	TInt iStyle;							// bold, italic serif, and mono-width
	TInt32 iReserved;
	};

// Typeface attributes.
class TOpenFontFaceAttrib: public TOpenFontFaceAttribBase
	{
	public:
	inline TOpenFontFaceAttrib();
	inline TBool operator==(const TOpenFontFaceAttrib& aAttrib) const;
	inline TPtrC FullName() const;
	inline TPtrC FamilyName() const;
	inline TPtrC LocalFullName() const;
	inline TPtrC LocalFamilyName() const;
	inline TPtrC ShortFullName() const;
	inline TPtrC ShortFamilyName() const;
	inline TPtrC ShortLocalFullName() const;
	inline TPtrC ShortLocalFamilyName() const;
	inline void SetFullName(const TDesC& aName);
	inline void SetFamilyName(const TDesC& aName);
	inline void SetLocalFullName(const TDesC& aName);
	inline void SetLocalFamilyName(const TDesC& aName);
	inline TInt MinSizeInPixels() const;
	inline void SetMinSizeInPixels(TInt aSize);

	private:
	TBufC<ENameLength> iFamilyName;			// the name without any style suffixes; usually a truncation of iFullName
	TBufC<ENameLength> iLocalFullName;		// the full name in the language of the current locale
	TBufC<ENameLength> iLocalFamilyName;	// the family name in the language of the current locale
	TInt iMinSizeInPixels;					// minimum supported size, (or readable size if scalable) in pixels
	TInt32 iReserved2;
	};

/*
A font specification that allows stretching and slanting in the x dimension, and other algorithmic effects.
This is used to correct for non-square pixels, and to allow algorithmic slanting and bold.
The width factor and slant factor transform any point (x,y) to (x * iWidthFactor + y * iSlantFactor,y).
*/
class TOpenFontSpec: public TOpenFontFaceAttribBase
	{
	public:
	IMPORT_C TOpenFontSpec();
	IMPORT_C TOpenFontSpec(const TFontSpec& aFontSpec);
	IMPORT_C void operator=(const TFontSpec& aFontSpec);
	inline TBool operator==(const TOpenFontSpec& aFontSpec) const;
	IMPORT_C void SetAttrib(const TOpenFontFaceAttribBase& aAttrib);
	IMPORT_C void GetTFontSpec(TFontSpec& aFontSpec) const;
	IMPORT_C void CompensateForAspectRatio(TInt aKPixelWidth,TInt aKPixelHeight);
	IMPORT_C void CompensateForAspectRatio(const MGraphicsDeviceMap& aMap);

	inline TInt Height() const;
	inline TInt32 WidthFactor() const;
	inline TInt32 SlantFactor() const;
	inline TUint32 Effects() const;

	inline TFontPrintPosition PrintPosition() const;
	inline void SetHeight(TInt aHeight);
	inline void SetWidthFactor(TInt32 aWidthFactor);
	inline void SetSlantFactor(TInt32 aSlantFactor);
	inline void SetEffects(TUint32 aEffects);

	// Bit assignments for effects flags
	enum
		{
		EAlgorithmicBold = 1,
		EDropShadow = 2,
		EOutline = 4
		};

	private:
	TInt iHeight;						// em height
	TInt32 iWidthFactor;				// algorithmic width factor as a 16.16 fixed-point number
	TInt32 iSlantFactor;				// algorithmic slant factor as a 16.16 fixed-point number
	TInt iBitmapType;					// for anti-aliasing; to be decided whether this means bits per pixel,
										// levels, or something else; zero always means 'default' or 'don't care'
	TUint32 iEffects;					// bit flags for other effects like algorithmic bold and drop-shadow

	// The following data members exist only to allow round-trip conversion between TFontSpec and TOpenFontSpec
	TBool iSymbol;						// specifies a symbol font as understood by TFontSpec
	TFontPrintPosition iPrintPosition;	// normal, superscript or subscript
	TInt iReserved2;
	};

// Constants for attachment points for diacritics.
enum TOpenFontAttachment
	{
	EBaselineLeft,
	EBaselineRight,
	ETopLeft,
	ETopCenter,
	ETopRight,
	EBottomLeft,
	EBottomCenter,
	EBottomRight
	};

// A base class for classes that manage new-style font files.
class COpenFontFile: public CBase
	{
	public:

	// virtual functions
	virtual void GetNearestFontInPixelsL(RHeap* aHeap,COpenFontSessionCacheList* aSessionCacheList,
										 const TOpenFontSpec& aDesiredFontSpec,TInt aPixelWidth,TInt aPixelHeight,
										 COpenFont*& aFont,TOpenFontSpec& aActualFontSpec) = 0;
	virtual TBool HasUnicodeCharacterL(TInt aFaceIndex,TInt aCode) const = 0; 
	IMPORT_C virtual void Reserved(); // unused; for future expansion

	// exported functions
	IMPORT_C COpenFontFile(TInt aUid,const TDesC& aFileName);
	IMPORT_C ~COpenFontFile();
	IMPORT_C TBool GetNearestFontHelper(const TOpenFontSpec& aDesiredFontSpec,TInt aPixelWidth,TInt aPixelHeight,
										TInt& aFaceIndex,TOpenFontSpec& aActualFontSpec) const;
	IMPORT_C void AddFaceL(const TOpenFontFaceAttrib& aAttrib);

	// inline functions
	inline TUid Uid() const;
	inline const TDesC& FileName() const;
	inline const TOpenFontFaceAttrib& FaceAttrib(TInt aFaceIndex) const;
	inline TInt FaceCount() const;
	inline void IncRefCount();
	inline TBool DecRefCount();

	// other public functions
	TInt GetNearestFontInPixels(RHeap* aHeap,COpenFontSessionCacheList* aSessionCacheList,
								const TOpenFontSpec& aDesiredFontSpec,TInt aPixelWidth,TInt aPixelHeight,
								COpenFont*& aFont,TOpenFontSpec& aActualFontSpec);
	void RemoveFontFromList(const COpenFont* aFont);

	private:
	// A class to contain the public font attributes and private positioning information (for kerning, ligatures, etc.)
	class TAttrib: public TOpenFontFaceAttrib
		{
		public:
		COpenFontPositioner* iPositioner;	// if non-null, positioning information for the typeface
		};

	CArrayFixFlat<TAttrib> iFaceAttrib;
	TUid iUid;
	TBuf<KMaxFileName> iFileName;
	TInt iRefCount;
	CArrayPtrFlat<COpenFont> iFontList;
	TAny* iReserved; // unused; for future expansion
	};

// A base class for font rasterizers. For example, our wrapper for the FreeType rasterizer is derived from this class.
class COpenFontRasterizer: public CBase
	{
	public:
	virtual COpenFontFile* NewFontFileL(TInt aUid,const TDesC& aFileName,RFs& aFileSession) = 0;
	IMPORT_C virtual void Reserved(); // unused; for future expansion

	private:
	TAny* iReserved; // unused; for future expansion
	};

/*
A base class for rasterizer contexts. This has functions to write the glyph bitmap to a buffer.
It is a C rather than a T class because it is a base for C classes, and it derives from CBase
to avoid surprises during construction (i.e., memory is zeroed).
*/
class COpenFontRasterizerContext: public CBase
	{
	public:
	inline COpenFontRasterizerContext();
	inline void StartGlyph(TOpenFontGlyphData* aGlyphData);
	inline void WriteGlyphBit(TInt aBit);
	inline void EndGlyph();

	private:
	TOpenFontGlyphData* iGlyphData;
	TUint8* iGlyphDataStart;
	TUint8* iGlyphDataPtr;
	TUint8* iGlyphDataEnd;
	TInt iGlyphBit;
	TInt iBytesNeeded;
	TBool iOverflow;
	TAny* iReserved; // unused; for future expansion
	};


// Inline functions start here.

inline TOpenFontMetrics::TOpenFontMetrics()
	{
	Mem::FillZ(this,sizeof(*this));
	}

inline TInt TOpenFontMetrics::Size() const
	{
	return iSize;
	}

inline TInt TOpenFontMetrics::Ascent() const
	{
	return iAscent;
	}

inline TInt TOpenFontMetrics::Descent() const
	{
	return iDescent;
	}

inline TInt TOpenFontMetrics::MaxHeight() const
	{
	return iMaxHeight;
	}

inline TInt TOpenFontMetrics::MaxDepth() const
	{
	return iMaxDepth;
	}

inline TInt TOpenFontMetrics::MaxWidth() const
	{
	return iMaxWidth;
	}

inline void TOpenFontMetrics::SetSize(TInt aSize)
	{
	iSize = (TInt16)aSize;
	}

inline void TOpenFontMetrics::SetAscent(TInt aAscent)
	{
	iAscent = (TInt16)aAscent;
	}

inline void TOpenFontMetrics::SetDescent(TInt aDescent)
	{
	iDescent = (TInt16)aDescent;
	}

inline void TOpenFontMetrics::SetMaxHeight(TInt aMaxHeight)
	{
	iMaxHeight = (TInt16)aMaxHeight;
	}

inline void TOpenFontMetrics::SetMaxDepth(TInt aMaxDepth)
	{
	iMaxDepth = (TInt16)aMaxDepth;
	}

inline void TOpenFontMetrics::SetMaxWidth(TInt aMaxWidth)
	{
	iMaxWidth = (TInt16)aMaxWidth;
	}

inline TOpenFontCharMetrics::TOpenFontCharMetrics()
	{
	Mem::FillZ(this,sizeof(*this));
	}

inline TInt TOpenFontCharMetrics::Width() const
	{
	return iWidth;
	}

inline TInt TOpenFontCharMetrics::Height() const
	{
	return iHeight;
	}

inline TInt TOpenFontCharMetrics::HorizBearingX() const
	{
	return iHorizBearingX;
	}

inline TInt TOpenFontCharMetrics::HorizBearingY() const
	{
	return iHorizBearingY;
	}

inline TInt TOpenFontCharMetrics::HorizAdvance() const
	{
	return iHorizAdvance;
	}

inline TInt TOpenFontCharMetrics::VertBearingX() const
	{
	return iVertBearingX;
	}

inline TInt TOpenFontCharMetrics::VertBearingY() const
	{
	return iVertBearingY;
	}

inline TInt TOpenFontCharMetrics::VertAdvance() const
	{
	return iVertAdvance;
	}

// Get the bounds of the character relative to its origin when setting text horizontally.
inline void TOpenFontCharMetrics::GetHorizBounds(TRect& aBounds) const
	{
	aBounds.iTl.iX = iHorizBearingX;
	aBounds.iTl.iY = -iHorizBearingY;
	aBounds.iBr.iX = aBounds.iTl.iX + iWidth;
	aBounds.iBr.iY = aBounds.iTl.iY + iHeight;
	}

// Get the bounds of the character relative to its origin when setting text vertically.
inline void TOpenFontCharMetrics::GetVertBounds(TRect& aBounds) const
	{
	aBounds.iTl.iX = -iVertBearingX;
	aBounds.iTl.iY = iVertBearingY;
	aBounds.iBr.iX = aBounds.iTl.iX + iWidth;
	aBounds.iBr.iY = aBounds.iTl.iY + iHeight;
	}

inline void TOpenFontCharMetrics::SetWidth(TInt aWidth)
	{
	iWidth = (TInt16)aWidth;
	}

inline void TOpenFontCharMetrics::SetHeight(TInt aHeight)
	{
	iHeight = (TInt16)aHeight;
	}

inline void TOpenFontCharMetrics::SetHorizBearingX(TInt aHorizBearingX)
	{
	iHorizBearingX = (TInt16)aHorizBearingX;
	}

inline void TOpenFontCharMetrics::SetHorizBearingY(TInt aHorizBearingY)
	{
	iHorizBearingY = (TInt16)aHorizBearingY;
	}

inline void TOpenFontCharMetrics::SetHorizAdvance(TInt aHorizAdvance)
	{
	iHorizAdvance = (TInt16)aHorizAdvance;
	}

inline void TOpenFontCharMetrics::SetVertBearingX(TInt aVertBearingX)
	{
	iVertBearingX = (TInt16)aVertBearingX;
	}

inline void TOpenFontCharMetrics::SetVertBearingY(TInt aVertBearingY)
	{
	iVertBearingY = (TInt16)aVertBearingY;
	}

inline void TOpenFontCharMetrics::SetVertAdvance(TInt aVertAdvance)
	{
	iVertAdvance = (TInt16)aVertAdvance;
	}

inline const TOpenFontMetrics& COpenFont::Metrics() const
	{
	return iMetrics;
	}

inline TInt TOpenFontGlyphData::GlyphIndex() const
	{
	return iGlyphIndex;
	}

inline const TOpenFontFaceAttrib* COpenFont::FaceAttrib() const
	{
	return iFile ? &iFile->FaceAttrib(iFaceIndex) : NULL;
	}

inline COpenFontFile* COpenFont::File() const
	{
	return iFile;
	}

inline TInt COpenFont::FaceIndex() const
	{
	return iFaceIndex;
	}

inline TBool COpenFont::CharacterNeedsToBeRasterized(TInt aSessionHandle,TInt aCode) const
	{
	return Glyph(aSessionHandle,aCode) == NULL;
	}

inline TOpenFontFaceAttribBase::TOpenFontFaceAttribBase()
	{
	Mem::FillZ(this,sizeof(*this));
	}

inline TOpenFontFaceAttrib::TOpenFontFaceAttrib():
	iMinSizeInPixels(0),
	iReserved2(0)
	{
	}

inline TBool TOpenFontFaceAttribBase::HasLatin() const
	{
	return iCoverage[0] & ELatinSet;
	}

inline TBool TOpenFontFaceAttribBase::HasGreek() const
	{
	return iCoverage[0] & EGreekSet;
	}

inline TBool TOpenFontFaceAttribBase::HasCyrillic() const
	{
	return iCoverage[0] & ECyrillicSet;
	}

inline TBool TOpenFontFaceAttribBase::HasKana() const
	{
	return iCoverage[1] & EKanaSets;
	}

inline TBool TOpenFontFaceAttribBase::HasHangul() const
	{
	return iCoverage[1] & EHangulSet;
	}

inline TBool TOpenFontFaceAttribBase::HasCJK() const
	{
	return iCoverage[1] & ECJKSet;
	}

inline TBool TOpenFontFaceAttribBase::IsSymbol() const
	{
	return iCoverage[0] == 0 && iCoverage[2] == 0 && iCoverage[3] == 0 &&
		   iCoverage[1] & ESymbolSets && !(iCoverage[1] & ~ESymbolSets);
	}

inline TBool TOpenFontFaceAttribBase::IsBold() const
	{
	return iStyle & EBold;
	}

inline TBool TOpenFontFaceAttribBase::IsItalic() const
	{
	return iStyle & EItalic;
	}

inline TBool TOpenFontFaceAttribBase::IsSerif() const
	{
	return iStyle & ESerif;
	}

inline TBool TOpenFontFaceAttribBase::IsMonoWidth() const
	{
	return iStyle & EMonoWidth;
	}

inline TPtrC TOpenFontFaceAttribBase::Name() const
	{
	return iName;
	}

inline TPtrC TOpenFontFaceAttrib::FullName() const
	{
	return Name();
	}

inline TPtrC TOpenFontFaceAttrib::FamilyName() const
	{
	return iFamilyName;
	}

inline TPtrC TOpenFontFaceAttrib::LocalFullName() const
	{
	return iLocalFullName;
	}

inline TPtrC TOpenFontFaceAttrib::LocalFamilyName() const
	{
	return iLocalFamilyName;
	}

inline TPtrC TOpenFontFaceAttrib::ShortFullName() const
	{
	// I can't use TDesC::Left for this because it panics if the desired length is > the existing length!
	return TPtrC(iName.Ptr(),Min(iName.Length(),KMaxTypefaceNameLength));
	}

inline TPtrC TOpenFontFaceAttrib::ShortFamilyName() const
	{
	return TPtrC(iFamilyName.Ptr(),Min(iFamilyName.Length(),KMaxTypefaceNameLength));
	}

inline TPtrC TOpenFontFaceAttrib::ShortLocalFullName() const
	{
	return TPtrC(iLocalFullName.Ptr(),Min(iLocalFullName.Length(),KMaxTypefaceNameLength));
	}

inline TPtrC TOpenFontFaceAttrib::ShortLocalFamilyName() const
	{
	return TPtrC(iLocalFamilyName.Ptr(),Min(iLocalFamilyName.Length(),KMaxTypefaceNameLength));
	}

inline const TUint* TOpenFontFaceAttribBase::Coverage() const
	{
	return iCoverage;
	}

inline TInt TOpenFontFaceAttrib::MinSizeInPixels() const
	{
	return iMinSizeInPixels;
	}

inline void TOpenFontFaceAttribBase::SetName(const TDesC& aName)
	{
	iName = TPtrC(aName.Ptr(),Min(aName.Length(),(TInt)ENameLength));
	}

inline void TOpenFontFaceAttrib::SetFullName(const TDesC& aName)
	{
	SetName(aName);
	}

inline void TOpenFontFaceAttrib::SetFamilyName(const TDesC& aName)
	{
	iFamilyName = TPtrC(aName.Ptr(),Min(aName.Length(),(TInt)ENameLength));
	}

inline void TOpenFontFaceAttrib::SetLocalFullName(const TDesC& aName)
	{
	iLocalFullName = TPtrC(aName.Ptr(),Min(aName.Length(),(TInt)ENameLength));
	}

inline void TOpenFontFaceAttrib::SetLocalFamilyName(const TDesC& aName)
	{
	iLocalFamilyName = TPtrC(aName.Ptr(),Min(aName.Length(),(TInt)ENameLength));
	}

inline void TOpenFontFaceAttribBase::SetCoverage(TUint aCoverage0,TUint aCoverage1,TUint aCoverage2,TUint aCoverage3)
	{
	iCoverage[0] = aCoverage0;
	iCoverage[1] = aCoverage1;
	iCoverage[2] = aCoverage2;
	iCoverage[3] = aCoverage3;
	}

inline void TOpenFontFaceAttrib::SetMinSizeInPixels(TInt aSize)
	{
	iMinSizeInPixels = aSize;
	}

inline TBool TOpenFontFaceAttrib::operator==(const TOpenFontFaceAttrib& aAttrib) const
	{
	return TOpenFontFaceAttribBase::operator==(aAttrib) &&
		   iFamilyName == aAttrib.iFamilyName &&
		   iLocalFullName == aAttrib.iLocalFullName &&
		   iLocalFamilyName == aAttrib.iLocalFamilyName &&
		   iMinSizeInPixels == aAttrib.iMinSizeInPixels;
	}

inline void TOpenFontFaceAttribBase::SetBold(TBool aBold)
	{
	if (aBold)
		iStyle |= EBold;
	else
		iStyle &= ~EBold;
	}

inline void TOpenFontFaceAttribBase::SetItalic(TBool aItalic)
	{
	if (aItalic)
		iStyle |= EItalic;
	else
		iStyle &= ~EItalic;
	}

inline void TOpenFontFaceAttribBase::SetSerif(TBool aSerif)
	{
	if (aSerif)
		iStyle |= ESerif;
	else
		iStyle &= ~ESerif;
	}

inline void TOpenFontFaceAttribBase::SetMonoWidth(TBool aMonoWidth)
	{
	if (aMonoWidth)
		iStyle |= EMonoWidth;
	else
		iStyle &= ~EMonoWidth;
	}

inline TBool TOpenFontFaceAttribBase::operator==(const TOpenFontFaceAttribBase& aAttrib) const
	{
	return iStyle == aAttrib.iStyle &&
		   iCoverage[0] == aAttrib.iCoverage[0] &&
		   iCoverage[1] == aAttrib.iCoverage[1] &&
		   iCoverage[2] == aAttrib.iCoverage[2] &&
		   iCoverage[3] == aAttrib.iCoverage[3] &&
		   iName.CompareF(aAttrib.iName) == 0;
	}

inline TBool TOpenFontSpec::operator==(const TOpenFontSpec& aFontSpec) const
	{
	return TOpenFontFaceAttribBase::operator==(aFontSpec) &&
		   iHeight == aFontSpec.iHeight &&
		   iWidthFactor == aFontSpec.iWidthFactor &&
		   iSlantFactor == aFontSpec.iSlantFactor &&
		   iBitmapType == aFontSpec.iBitmapType &&
		   iEffects == aFontSpec.iEffects &&
		   iSymbol == aFontSpec.iSymbol &&
		   iPrintPosition == aFontSpec.iPrintPosition;
	}

inline TInt TOpenFontSpec::Height() const
	{
	return iHeight;
	}

inline TInt32 TOpenFontSpec::WidthFactor() const
	{
	return iWidthFactor;
	}

inline TInt32 TOpenFontSpec::SlantFactor() const
	{
	return iSlantFactor;
	}

inline TUint32 TOpenFontSpec::Effects() const
	{
	return iEffects;
	}

inline TFontPrintPosition TOpenFontSpec::PrintPosition() const
	{
	return iPrintPosition;
	}

inline void TOpenFontSpec::SetHeight(TInt aHeight)
	{
	iHeight = aHeight;
	}

inline void TOpenFontSpec::SetWidthFactor(TInt32 aWidthFactor)
	{
	iWidthFactor = aWidthFactor;
	}

inline void TOpenFontSpec::SetSlantFactor(TInt32 aSlantFactor)
	{
	iSlantFactor = aSlantFactor;
	}

inline void TOpenFontSpec::SetEffects(TUint32 aEffects)
	{
	iEffects = aEffects;
	}

inline TUid COpenFontFile::Uid() const
	{
	return iUid;
	}

inline const TDesC& COpenFontFile::FileName() const
	{
	return iFileName;
	}

inline const TOpenFontFaceAttrib& COpenFontFile::FaceAttrib(TInt aFaceIndex) const
	{
	return iFaceAttrib[aFaceIndex];
	}

inline TInt COpenFontFile::FaceCount() const
	{
	return iFaceAttrib.Count();
	}

inline void COpenFontFile::IncRefCount()
	{
	iRefCount++;
	}

inline TBool COpenFontFile::DecRefCount()
	{
	iRefCount--;
	return iRefCount <= 0;
	}

inline COpenFontRasterizerContext::COpenFontRasterizerContext():
	iGlyphData(NULL)
	{
	}

inline void COpenFontRasterizerContext::StartGlyph(TOpenFontGlyphData* aGlyphData)
	{
	aGlyphData->SetPointersToInternalBuffers();
	iGlyphData = aGlyphData;
	iGlyphDataStart = iGlyphDataPtr = aGlyphData->BufferStart();
	// Allow 4 extra bytes; BITGDI requires this.
	iGlyphDataEnd = aGlyphData->BufferEnd() - 4;
	iGlyphBit = 1;
	*iGlyphDataPtr = 0;
	iBytesNeeded = 1;
	iOverflow = FALSE;
	}

inline void COpenFontRasterizerContext::WriteGlyphBit(TInt aBit)
	{
	if (aBit && !iOverflow)
		*iGlyphDataPtr |= iGlyphBit;
	iGlyphBit <<= 1;
	if (iGlyphBit == 256)
		{
		iGlyphBit = 1;
		iBytesNeeded++;
		if (++iGlyphDataPtr < iGlyphDataEnd)
			*iGlyphDataPtr = 0;
		else
			iOverflow = TRUE;
		}
	}

inline void COpenFontRasterizerContext::EndGlyph()
	{
	// Add 4 bytes to the data size; some BITGDI functions require this.
	iGlyphData->SetBytesNeeded(iBytesNeeded + 4);
	iGlyphData = NULL;
	}

inline TBool TOpenFontGlyphData::Overflow() const
	{
	return iBytesNeeded > iBitmapBufferSize;
	}

inline TInt TOpenFontGlyphData::BytesNeeded() const
	{
	return iBytesNeeded;
	}

inline TPtrC8 TOpenFontGlyphData::Bitmap() const
	{
	return TPtrC8(iBitmap,iBytesNeeded);
	}

inline const TUint8* TOpenFontGlyphData::BitmapPointer() const
	{
	return iBitmap;
	}

inline const TOpenFontCharMetrics* TOpenFontGlyphData::Metrics() const
	{
	return iMetrics;
	}

inline TUint8* TOpenFontGlyphData::BufferStart()
	{
	return iBitmapBuffer;
	}

inline TUint8* TOpenFontGlyphData::BufferEnd()
	{
	return iBitmapBuffer + iBitmapBufferSize;
	}

inline void TOpenFontGlyphData::SetBytesNeeded(TInt aBytes)
	{
	iBytesNeeded = aBytes;
	}

inline void TOpenFontGlyphData::SetBitmapPointer(const TUint8* aBitmap)
	{
	iBitmap = aBitmap;
	}

inline void TOpenFontGlyphData::SetMetricsPointer(const TOpenFontCharMetrics* aMetrics)
	{
	iMetrics = aMetrics;
	}

inline void TOpenFontGlyphData::SetPointersToInternalBuffers()
	{
	iBitmap = iBitmapBuffer;
	iMetrics = &iMetricsBuffer;
	}

inline void TOpenFontGlyphData::SetMetrics(TOpenFontCharMetrics& aMetrics)
	{
	iMetricsBuffer = aMetrics;
	iMetrics = &iMetricsBuffer;
	}

inline void TOpenFontGlyphData::SetGlyphIndex(TInt aGlyphIndex)
	{
	iGlyphIndex = aGlyphIndex;
	}

#endif // __OPENFONT_H__
