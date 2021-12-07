// PDRSTORE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef PDRSTORE_H
#define PDRSTORE_H

#include <s32mem.h>
#include <gdi.h>
#include <fbs.h>

class CStreamStore;

class CFontInfo;
class TPdrResource;
class CPdrTranslates;
class CTypefaceFonts;
class CBandedDevice;
class CFbsBitGc;
class CFbsFont;

enum TFbsEncoding
	{
	EFbsNone = 0,
	EFbsRunLength = 1,
	EFbsTIFF = 2,
	EFbsDeltaRow = 3,
	EFbsReserved = 4,
	EFbsAdaptive = 5
	};

enum TFbsRasterGraphicsMode
	{
	EFbsLogicalPageOrientation = 0,
	EFbsPhysicalPageOrientation = 3
	};

enum TPdrResourceId  // Corresponds to IdentResource in PDRREADR.H
	{
	EPdrReset,
	EPdrSetPageSize,
	EPdrPreAmble,
	EPdrPostAmble,
	EPdrSetTextColor,
	EPdrBoldOn,
	EPdrBoldOff,
	EPdrItalicOn,
	EPdrItalicOff,
	EPdrUnderlineOn,
	EPdrUnderlineOff,
	EPdrStrikethroughOn,
	EPdrStrikethroughOff,
	EPdrNewPage,
	EPdrPortrait,
	EPdrLandscape,
	EPdrSetXPos,
	EPdrSetYPos,
	EPdrIncrementXPos,
	EPdrIncrementYPos,
	EPdrCarriageReturn,
	EPdrSetGraphicsColor,
	EPdrBitmapStart,
	EPdrBitmapEnd,
	EPdrScanLine,
	EPdrEndScanLine, 
	EPdrResource1,
	EPdrResource2,
	EPdrResource3,
	EPdrResource4,
	EPdrResource5,
	EPdrResource6,
	EPdrResource7,
	EPdrResource8
	};

const TInt KMaxCommandStringLength = 0x40;
typedef TBuf8<KMaxCommandStringLength> TCommandString;

/**
 * @internal
 * Internal to Symbian
 */
class CPdrResources : public CBase
	{
public:
	IMPORT_C CPdrResources();
	IMPORT_C void RestoreL(CStreamStore& aStore, TStreamId aStreamId);
	IMPORT_C ~CPdrResources();
	IMPORT_C TPtrC8 ResourceString(TInt anId) const;
private:
	TInt iNumResources;
	TPdrResource* iResourceList;
	};

/**
 * @internal
 * Internal to Symbian
 */
class CPdrDevice;
class CInfoFont : public CFont
	{
	friend class CPdrTypefaceStore;
private:
	CInfoFont(TInt aBaselineOffsetInPixels, const TFontSpec& aFontSpecInTwips, TInt aFontInfoHeightInTwips, TInt aHeightInPixels, CPdrTranslates* aTranslates, const TDesC8& aCommandString, CPdrDevice* aPdrDevice);
	~CInfoFont();
public:
	IMPORT_C TUid TypeUid() const;
	IMPORT_C TInt HeightInPixels() const;
	IMPORT_C TInt AscentInPixels() const;
	IMPORT_C TInt CharWidthInPixels(TChar aChar) const;
	IMPORT_C TInt TextWidthInPixels(const TDesC &aText) const;
	IMPORT_C TInt BaselineOffsetInPixels() const;
	IMPORT_C TInt TextCount(const TDesC &aText, TInt aWidthInPixels) const;
	IMPORT_C TInt TextCount(const TDesC &aText, TInt aWidthInPixels, TInt &aExcessWidthInPixels) const;
	IMPORT_C TInt MaxCharWidthInPixels() const;
	IMPORT_C TInt MaxNormalCharWidthInPixels() const;
	IMPORT_C TFontSpec FontSpecInTwips() const;
	IMPORT_C HBufC8* TranslateStringL(const TDesC& aString) const;
	IMPORT_C TPtrC8 CommandString() const;
	IMPORT_C TBool RepertoireContains(TChar aChar) const;
	IMPORT_C TBool AllCharsInFontRepertoire(const TDesC& aString, TInt& aFirstCharNotInRepertoire, TInt& aLength) const;
	inline CFontInfo* FontInfo() const {return iFontInfo;}
	CFont* RealFont() const;

private:
	TInt Width(TInt aNum) const;
	TInt Height(TInt aNum) const;
	void CreateBandedFontIfRequired();
private:
	TCommandString iCommandString;
	TInt iBaselineOffsetInPixels;
	TFontSpec iFontSpecInTwips;
	TInt iFontInfoHeightInTwips;
	TInt iHeightInPixels;
	CFontInfo* iFontInfo;
	CPdrTranslates* iTranslates;
	CPdrDevice* iPdrDevice;
	CFont* iRealFont;
	};

/**
 * @internal
 * Internal to Symbian
 */
class TTypefaceFontsEntry
	{
public:
	IMPORT_C void InternalizeL(RReadStream& aStream);
public:
	TStreamId iStreamId;
	TBool iNotInPortrait;
	TBool iNotInLandscape;
	};

/**
 * @internal
 * Internal to Symbian
 */
class CPdrModelInfo : public CBase
	{
public:
	IMPORT_C CPdrModelInfo();
	IMPORT_C ~CPdrModelInfo();
	IMPORT_C void InternalizeL(RReadStream& aStream);
public:
	TInt iFlags;
	TInt iKPixelWidthInTwips;
	TInt iKPixelHeightInTwips;
	TPoint iPortraitOffsetInPixels;
	TPoint iLandscapeOffsetInPixels;
	TMargins iMinMarginsInPixels;
	TDisplayMode iDisplayMode;
	TInt iNumTypefaceFonts;
	TTypefaceFontsEntry* iTypefaceFontsEntryList;
	TStreamId iResourcesStreamId;
	TStreamId iSpareStreamId; 
	};

/**
 * @internal
 * Internal to Symbian
 */
class CPdrTypefaceStore : public CTypefaceStore
	{
private:
	CPdrTypefaceStore(CStreamStore& aStore, TInt aKPixelHeightInTwips, CPdrDevice* aPdrDevice);
	void ConstructL(TInt aNumTypefacesFonts, TTypefaceFontsEntry* aTypefaceFontsEntryList, TPageSpec::TPageOrientation aPageOrientation);
public:
	IMPORT_C static CPdrTypefaceStore* NewL(CStreamStore& aStore, TInt aNumTypefacesFonts, TTypefaceFontsEntry* aTypefaceFontsEntryList, TPageSpec::TPageOrientation aPageOrientation, TInt aKPixelHeightInTwips, CPdrDevice* aPdrDevice);
	IMPORT_C ~CPdrTypefaceStore();
	IMPORT_C TInt GetNearestFontInTwips(CFont *&aFont, const TFontSpec &aFontSpec);
	IMPORT_C TInt NumTypefaces() const;
	IMPORT_C TInt FontHeightInTwips(TInt aTypefaceIndex, TInt aHeightIndex) const;
	IMPORT_C void TypefaceSupport(TTypefaceSupport &aTypefaceSupport, TInt aTypefaceIndex) const;
	IMPORT_C void SetPageOrientation(TPageSpec::TPageOrientation aPageOrientation);
private:
	CFontInfo* FontInfoL(TStreamId aStreamId) const;
	CPdrTranslates* TranslatesL(TStreamId aStreamId) const;
	TInt GetNearestFontHeightIndex(TInt aTypefaceIndex, TInt aHeightInTwips) const;
	TFontStyle GetNearestFontStyle(TInt aTypefaceIndex, TInt aHeightIndex, const TFontStyle& aFontStyle) const;
	CInfoFont* FindFont(const TFontSpec& aFontSpecInTwips, TInt aHeightInPixels) const;
	CInfoFont* NewFontL(TInt aBaselineOffsetInPixels, const TFontSpec& aFontSpecInTwips, TInt aFontInfoHeightInTwips, TInt aHeightInPixels, CPdrTranslates* aTranslates, const TDesC8& aCommandString, TStreamId aFontInfoStreamId);
	TInt VerticalTwipsToPixels(TInt aTwipsHeight) const;
private:
	CStreamStore* iStore;
	TInt iKPixelHeightInTwips;
	CArrayPtr<CTypefaceFonts>* iTypefaceFontsList;
	CArrayPtr<CTypefaceFonts>* iPortraitTypefaceFontsList;
	CArrayPtr<CTypefaceFonts>* iLandscapeTypefaceFontsList;
	CArrayPtr<CTypefaceFonts>* iCurrentTypefaceFontsList;
	CArrayPtr<CPdrTranslates>* iTranslatesList;
	CArrayPtr<CFontInfo>* iFontInfoList;
public:
	CPdrDevice* iPdrDevice;
	};

/**
 * @internal
 * Internal to Symbian
 */
class CPageBuffer : public CActive
	{
public:
	IMPORT_C static CPageBuffer* NewL(CPrinterPort* aPrinterPort);
	IMPORT_C static CPageBuffer* NewL(CPrinterPort* aPrinterPort, TInt aGranularity);
	IMPORT_C void StartFlush(TRequestStatus& aRequestStatus);
	IMPORT_C void AddBytesL(const TDesC8& aDes);
	IMPORT_C RWriteStream& CreateWriteStreamL();
	IMPORT_C void CloseWriteStream();
	IMPORT_C ~CPageBuffer();
	void DoCancel();
	void RunL();
private:
	void ConstructL();
	CPageBuffer(CPrinterPort* aPrinterPort, TInt aGranularity);
	void Queue();
private:
	TRequestStatus* iRequestStatus;
	TInt iWritePos;
	TInt iGranularity;
	CBufSeg* iBuffer;
	TPtr8 iPtr;
	CPrinterPort* iPrinterPort;
	RBufWriteStream iWriteStream;
	CBufSeg* iWriteStreamBuffer;
	};

/**
 * @internal
 * Internal to Symbian
 */
class TTextFormat
	{
public:
	IMPORT_C TTextFormat();
	IMPORT_C TTextFormat(const TFontUnderline anUnderlineStyle, const TFontStrikethrough aStrikethroughStyle, const TRgb& aColor, const TDesC8& aFontString, const TFontStyle& aFontStyle);
	IMPORT_C TBool operator == (const TTextFormat& aFormat) const;
public:
	TFontUnderline iUnderlineStyle;
	TFontStrikethrough iStrikethroughStyle;
	TRgb iColor;
	TCommandString iFontString;
	TFontStyle iFontStyle;
	};

/**
 * @internal
 * Internal to Symbian
 */
class CPageTextEntry : public CBase
	{
public:
	IMPORT_C CPageTextEntry(const TPoint& aDrawPos, TInt aHeightInPixels, TInt aTextWidthInPixels, HBufC8* aText, TTextFormat* aTextFormat);
	IMPORT_C ~CPageTextEntry();
	IMPORT_C TPoint TopTextPos();
public:
	TPoint iDrawPos;
	TInt iHeightInPixels;
	TInt iTextWidthInPixels;
	HBufC8* iText;
	TTextFormat* iTextFormat;
	};

/**
 * @internal
 * Internal to Symbian
 */
class CPageText : public CBase
	{
private:
	CPageText();
	void ConstructL();
public:
	IMPORT_C static CPageText* NewL();
	IMPORT_C ~CPageText();
	IMPORT_C void Reset();
	IMPORT_C void AddEntryL(const TPoint& aPoint, const TFontUnderline aUnderlineStyle, const TFontStrikethrough aStrikethroughStyle, const TRgb& aColor, const CInfoFont* aFont, const TDesC& aString);
	IMPORT_C TInt NumEntries();
	IMPORT_C CPageTextEntry* operator [] (TInt anIndex);
	inline TInt MaxFontHeightInPixels() const {return iMaxFontHeightInPixels;}
private:
	TInt iMaxFontHeightInPixels;
	CArrayPtr<TTextFormat>* iTextFormatList;
	CArrayPtr<CPageTextEntry>* iPageTextEntryList;
	};

class CPdrControl;

/**
 * @internal
 * Internal to Symbian
 */
class CPdrDevice : public CPrinterDevice
	{
protected:
	IMPORT_C CPdrDevice();
public:
	IMPORT_C virtual ~CPdrDevice();
	IMPORT_C void SelectPageSpecInTwips(const TPageSpec& aPageSpec);
	IMPORT_C TDisplayMode DisplayMode() const;
	IMPORT_C TSize SizeInPixels() const;
	IMPORT_C TSize SizeInTwips() const;
	IMPORT_C TRect PrintablePageInPixels() const;
	IMPORT_C TInt HorizontalTwipsToPixels(TInt aTwips) const;
	IMPORT_C TInt VerticalTwipsToPixels(TInt aTwips) const;
	IMPORT_C TInt HorizontalPixelsToTwips(TInt aPixels) const;
	IMPORT_C TInt VerticalPixelsToTwips(TInt aPixels) const;
	IMPORT_C TInt GetNearestFontInTwips(CFont*& aFont, const TFontSpec& aFontSpec);
	IMPORT_C TInt NumTypefaces() const;
	IMPORT_C void TypefaceSupport(TTypefaceSupport& aTypefaceSupport, TInt aTypefaceIndex) const;
	IMPORT_C TInt FontHeightInTwips(TInt aTypefaceIndex, TInt aHeightIndex) const;
	IMPORT_C void PaletteAttributes(TBool& aModifiable, TInt& aNumEntries) const;
	IMPORT_C void SetPalette(CPalette* aPalette);
	IMPORT_C TInt GetPalette(CPalette*& aPalette) const;
	IMPORT_C TPrinterModelEntry Model() const;
	IMPORT_C TInt Flags() const;
	IMPORT_C TInt SetModel(const TPrinterModelHeader& aModel, CStreamStore& aStore);
	IMPORT_C void ReleaseFont(CFont* aFont);
	IMPORT_C TPoint OffsetInPixels();

protected:
	IMPORT_C virtual TSize KPixelSizeInTwips() const;
private:
	void DoSetModelL();
protected:
	CStreamStore* iStore;
	TPrinterModelHeader iModel;
	CPdrModelInfo* iModelInfo;
	CPdrTypefaceStore* iTypefaceStore;
	}; 

/**
 * @internal
 * Internal to Symbian
 */
class CPdrControl : public CPrinterControl
	{
public:
	IMPORT_C ~CPdrControl();
	IMPORT_C TInt CreateContext(CGraphicsContext*& aGC);
	IMPORT_C TInt BandsPerPage();
	IMPORT_C TMoreOnPage QueueGetBand(TRequestStatus& aStatus, TBandAttributes& aBand); // returns affirmative if more to print on current page
	IMPORT_C void QueueEndPrint(TRequestStatus& aStatus); // Called at finish to flush buffer, tidy up printer etc.
	IMPORT_C void AbortPrint(); // tidy up synchronously in a short time
	IMPORT_C virtual void DrawTextL(const TPoint& aPoint, const TFontUnderline aUnderlineStyle, const TFontStrikethrough aStrikethroughStyle, const TRgb& aColor, const CInfoFont* aFont, const TDesC& aString); 
	IMPORT_C TBool IsGraphicsBand() const;
	inline CBandedDevice* BandedDevice() const {return iBandedDevice;}
protected:
	IMPORT_C CPdrControl(CPdrDevice* aPdrDevice, CPrinterPort* aPrinterPort);
	IMPORT_C virtual void DoQueueGetBandL();
	IMPORT_C virtual void DoQueueEndPrintL();
	IMPORT_C void ConstructL(CStreamStore& aStore, TStreamId aStreamId);

	virtual void OutputBandL() = 0;

	IMPORT_C virtual void MoveToL(const TPoint& aPoint); 
	IMPORT_C virtual void MoveByL(const TPoint& aVector); 
	IMPORT_C virtual void OutputTextL(const TPoint& aPoint, TInt aWidthInPixels, const TTextFormat& aTextFormat, const TDesC8& aString); 

	IMPORT_C virtual void SetPageSizeL(); 
	IMPORT_C virtual void SetPageOrientationL();
	IMPORT_C virtual void SetFontPostureL(const TFontPosture aPosture);
	IMPORT_C virtual void SetFontStrokeWeightL(const TFontStrokeWeight aStrokeWeight);
	IMPORT_C virtual void SetTextColorL(const TRgb& aColor);
	IMPORT_C virtual void CommandL(const TInt anId);

	IMPORT_C TBool TransformBuffer(); // These two functions are not implemented anywhere
	IMPORT_C TBool CompressBuffer();  // for this class. Nor do I believe they are defined
									  // for a reason. But since they are part of the 
									  // existing interface of a DLL in a ROM I need to
									  // patch. They get to stay there for the moment. CJC

protected:
	CPdrDevice* iPdrDevice;
	CPageBuffer* iPageBuffer;
	CPdrResources* iResources;
	CBandedDevice* iBandedDevice;
	CPageText* iPageText;
	TInt iBandIndex;
	TInt iEntryIndex;
	TPoint iPosition;
	TTextFormat iTextFormat;
	};

/**
 * @internal
 * Internal to Symbian
 */
class CPdrGc : public CGraphicsContext
	{
private:
	CPdrGc(CPdrDevice* aDevice);
	void ConstructL();
public:
	static CPdrGc* NewL(CPdrDevice* aDevice);
	IMPORT_C ~CPdrGc();

	IMPORT_C CGraphicsDevice* Device() const;
	IMPORT_C void SetOrigin(const TPoint& aPos = TPoint(0, 0));
	IMPORT_C void SetDrawMode(TDrawMode aDrawingMode);
	IMPORT_C void SetClippingRect(const TRect& aRect);
	IMPORT_C void CancelClippingRect();
	IMPORT_C void Reset();

	IMPORT_C void UseFont(const CFont* aFont);
	IMPORT_C void DiscardFont();

	IMPORT_C void SetUnderlineStyle(TFontUnderline aUnderlineStyle);
	IMPORT_C void SetStrikethroughStyle(TFontStrikethrough aStrikethroughStyle);
	IMPORT_C void SetWordJustification(TInt aExcessWidth, TInt aNumGaps);
	IMPORT_C void SetCharJustification(TInt aExcessWidth, TInt aNumChars);

	IMPORT_C void SetPenColor(const TRgb& aColor);
	IMPORT_C void SetPenStyle(TPenStyle aPenStyle);
	IMPORT_C void SetPenSize(const TSize& aSize = TSize(1, 1));

	IMPORT_C void SetBrushColor(const TRgb& aColor);
	IMPORT_C void SetBrushStyle(TBrushStyle aBrushStyle);
	IMPORT_C void SetBrushOrigin(const TPoint& aOrigin);
	IMPORT_C void UseBrushPattern(const CFbsBitmap* aBitmap);
	IMPORT_C void DiscardBrushPattern();

	IMPORT_C void MoveTo(const TPoint& aPoint);
	IMPORT_C void MoveBy(const TPoint& aVector);
	IMPORT_C void Plot(const TPoint& aPoint);

	IMPORT_C void DrawArc(const TRect& aRect, const TPoint& aStart, const TPoint& aEnd);
	IMPORT_C void DrawLine(const TPoint& aPoint1, const TPoint& aPoint2);
	IMPORT_C void DrawLineTo(const TPoint& aPoint);
	IMPORT_C void DrawLineBy(const TPoint& aVector);
	IMPORT_C void DrawPolyLine(const CArrayFix<TPoint>* aPointList);
	IMPORT_C void DrawPolyLine(const TPoint* aPointList, TInt aNumPoints);

	IMPORT_C void DrawPie(const TRect& aRect, const TPoint& aStart, const TPoint& aEnd);
	IMPORT_C void DrawEllipse(const TRect& aRect);
	IMPORT_C void DrawRect(const TRect& aRect);
	IMPORT_C void DrawRoundRect(const TRect& aRect, const TSize& aCornerSize);
	IMPORT_C TInt DrawPolygon(const CArrayFix<TPoint>* aPointList, TFillRule aFillRule = EAlternate);
	IMPORT_C TInt DrawPolygon(const TPoint* aPointList, TInt aNumPoints, TFillRule aFillRule = EAlternate);

	IMPORT_C void DrawBitmap(const TPoint& aTopLeft, const CFbsBitmap* aSource);
	IMPORT_C void DrawBitmap(const TRect& aDestRect, const CFbsBitmap* aSource);
	IMPORT_C void DrawBitmap(const TRect& aDestRect, const CFbsBitmap* aSource, const TRect& aSourceRect);

	IMPORT_C void DrawText(const TDesC& aString, const TPoint& aPosition);

	IMPORT_C void DrawText(const TDesC& aString, const TRect& aBox, TInt aBaselineOffset, TTextAlign aHoriz = ELeft, TInt aLeftMrg = 0);

private:
	inline CPdrControl* PdrControl() const {return ((CPdrControl*) iPdrDevice->iControl);}

private:
	CPdrDevice* iPdrDevice;
	CFbsBitGc* iBandedGc;
	CFbsFont* iFbsFont;
	CFont* iBandedFont;
	CInfoFont* iFont;
	TPoint iOrigin;
	TPoint iPosition;
	TFontUnderline iUnderlineStyle;
	TFontStrikethrough iStrikethroughStyle;
	TRect iClippingRect;  // Relative to absolute origin
	TInt iWordExcessWidthInPixels;
	TInt iNumGaps;
	TInt iCharExcessWidthInPixels;
	TInt iNumChars;
	TRgb iPenColor;
	TBool iPrintTextUsingBitmaps;
	};

/**
 * @internal
 * Internal to Symbian
 */
class CFbsDrvDevice : public CPdrDevice
	{
public:
	IMPORT_C CFbsDrvDevice();
	IMPORT_C ~CFbsDrvDevice();

	IMPORT_C TInt GetNearestFontInTwips(CFont*& aFont, const TFontSpec& aFontSpec);
	IMPORT_C void ReleaseFont(CFont* aFont);
	IMPORT_C TInt NumTypefaces() const;
	IMPORT_C void TypefaceSupport(TTypefaceSupport& aTypefaceSupport, TInt aTypefaceIndex) const;
	IMPORT_C TInt FontHeightInTwips(TInt aTypefaceIndex, TInt aHeightIndex) const;

	IMPORT_C TInt CreateContext(CGraphicsContext*& aGc);
	IMPORT_C void CreateControlL(CPrinterPort* aPrinterPort);
	IMPORT_C TInt SetModel(const TPrinterModelHeader& aModel, CStreamStore& aStore);
	IMPORT_C void LoadTypeFaceList();
	IMPORT_C TSize KPixelSizeInTwips() const;

private:
// reserved virtual function space
	IMPORT_C virtual void Reserved_1();

protected:
	CFbsTypefaceStore* iFbsTypefaceStore;
	CArrayFixFlat<TInt>* iGenTypefaceFontsList;
	CArrayFixFlat<TInt>* iGenTypefaceFontsType;
	TInt iFbsTypefaceCount;
	TInt iPdrTypefaceCount;

private:
	TAny* iReserved;
	};

/**
 * @internal
 * Internal to Symbian
 */
class CFbsDrvControl : public CPdrControl
	{
public:
	IMPORT_C static CFbsDrvControl* NewL(CPdrDevice* aPdrDevice, CPrinterPort* aPrinterPort, CStreamStore& aStore, TStreamId aResourcesStreamId);
	IMPORT_C ~CFbsDrvControl();

protected:
	IMPORT_C virtual void OutputBandL();

	IMPORT_C CFbsDrvControl(CPdrDevice* aPdrDevice, CPrinterPort* aPrinterPort);
	IMPORT_C void ConstructL(CStreamStore& aStore, TStreamId aResourcesStreamId);
	IMPORT_C void SetPageSizeL();

	IMPORT_C TBool TransformBuffer();
	IMPORT_C TBool CompressBuffer();

private:
// reserved virtual function space
	IMPORT_C virtual void Reserved_1();

protected:
	HBufC8* iScanLine;
	HBufC8* iCompressedScanLine;

private:
	TAny* iReserved;
	};

#endif
