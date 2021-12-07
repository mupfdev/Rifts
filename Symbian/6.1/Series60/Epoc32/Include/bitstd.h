// BITSTD.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __BITSTD_H__
#define __BITSTD_H__

#include <e32std.h>
#include <gdi.h>
#include <fbs.h>
#include <bitbase.h>

class CFbsBitGcFont : public CFbsFont
	{
public:
	IMPORT_C CFbsBitGcFont();
	IMPORT_C virtual ~CFbsBitGcFont();
	IMPORT_C CBitmapFont* Address() const;
	IMPORT_C TInt Duplicate(TInt aHandle);
	IMPORT_C void Reset();
	IMPORT_C void operator=(const CFbsBitGcFont& aFont);
protected:
	TBool iCopy;
	};

class CFbsBitGcBitmap : public CFbsBitmap
	{
public:
	IMPORT_C CBitwiseBitmap* Address() const;
	IMPORT_C void LockHeap() const;
	IMPORT_C void UnlockHeap() const;
	};

class TEllipse
	{
public:
	enum TEllipseStatus
		{
		EInitialised,
		EFirstSector,
		ESecondSector,
		EComplete,
		ELine
		};
public:
	IMPORT_C void Construct(const TRect& aRect);
	IMPORT_C TBool SingleStep(TPoint& aTopLeft,TPoint& aTopRight,TPoint& aBottomLeft,TPoint& aBottomRight);
	IMPORT_C TBool NextStep(TPoint& aTopLeft,TPoint& aTopRight,TPoint& aBottomLeft,TPoint& aBottomRight);
	IMPORT_C TPoint Intersection(const TRect& aRect,const TPoint& aPoint);
protected:
	IMPORT_C TBool Output(TPoint& aTopLeft,TPoint& aTopRight,TPoint& aBottomLeft,TPoint& aBottomRight);
protected:
	TEllipseStatus iStatus;
	TInt iA;
	TInt iB;
	TInt64 iASquared;
	TInt64 iBSquared;
	TInt64 iASquBSqu;
	TInt iX;
	TInt iY;
	TInt iXAdj;
	TInt iYAdj;
	TPoint iOffset;
	TInt64 iD1;
	TInt64 iD2;
	};

// Polygon stuff written by DPB September 1995

class CPolygonFiller : public CBase
	{
public:
	enum TUsage
		{
		EGetAllPixelRunsSequentially,
		EGetPixelRunsSequentiallyForSpecifiedScanLines
		};
public:
	IMPORT_C CPolygonFiller();
	IMPORT_C ~CPolygonFiller();
	IMPORT_C void Construct(const CArrayFix<TPoint>* aPointArray,CGraphicsContext::TFillRule aFillRule,TUsage aUsage=EGetAllPixelRunsSequentially); // N.B. this cannot fail
	IMPORT_C void Construct(const TPoint* aPointList,TInt aNumPoints, CGraphicsContext::TFillRule aFillRule, TUsage aUsage=EGetAllPixelRunsSequentially); // N.B. this cannot fail
	IMPORT_C void Reset();
	IMPORT_C void GetNextPixelRun(TBool& aExists, TInt& aScanLine, TInt& aStart, TInt& aEnd);
	IMPORT_C void GetNextPixelRunOnSpecifiedScanLine(TBool& aExists, TInt aScanLine, TInt& aStart, TInt& aEnd);
private: // data-types for the fast algorithm
	struct SFastEdge
		{
		TInt upperVertex;
		TInt lowerVertex;
		TInt firstVertex;
		};
	struct SFastScanLineIntersection;
	struct SFastActiveEdge
		{
		SFastEdge* edgePtr;
		TLinearDDA lineGenerator;
		SFastScanLineIntersection* scanLineIntersectionPtr;
		};
	struct SFastScanLineIntersection
		{
		TInt firstPixel;
		TInt lastPixel;
		SFastActiveEdge* activeEdgePtr;
		};
private: // data-types for the slow algorithm
	struct SSlowScanLineIntersection
		{
		TInt firstPixel;
		TInt lastPixel;
		TInt firstVertexOfEdge;
		};
private: // data-types for both algorithms
	struct SFastData
		{
		TPoint* vertexList;
		SFastEdge* edgeList;
		SFastActiveEdge* activeEdgeList;
		SFastScanLineIntersection* scanLineIntersectionList;
		TInt numActiveEdges;
		TInt numScanLineIntersections;
		TInt nextEdgeToActivate;
		};
	struct SSlowData
		{
		enum {EStoreSize=8};
		TLinearDDA lineGenerator;
		SSlowScanLineIntersection scanLineIntersectionList[EStoreSize];
		TInt numIntersectionsWithSameFirstPixelPreviouslyMet;
		TInt numIntersectionsWithSameFirstPixelMetThisTime;
		TInt numScanLineIntersections;
		TBool scanLineComplete;
		TInt firstPixelOfLastIntersectionInPrevBuffer;
		};
private:
	void Construct(CGraphicsContext::TFillRule aFillRule,TUsage aUsage);
	void FastHandleVertexIntersection(TInt& aCurrentActiveEdge, TBool aIsLowerVertex);
	void SetFastIntersection(SFastActiveEdge& aActiveEdge, SFastScanLineIntersection& aScanLineIntersection);
	void SlowHandleVertexIntersection(SSlowScanLineIntersection& aScanLineIntersection, TInt& aVertexStartingCurrentEdge,TBool aIsLowerVertex);
	void JumpToCurrentScanLine(TLinearDDA& aLineGenerator, const TPoint& aUpper, const TPoint& aLower,TPoint& aStartPos, TPoint& aEndPos) const;
	const TPoint& Point(TInt aIndex);
private:
	const CArrayFix<TPoint>* iPointArray; // not owned by the class
	const TPoint* iPointList; // not owned by the class
	CGraphicsContext::TFillRule iFillRule;
	TBool iUseFastAlgorithm;
	TInt iNumVertexes;
	TBool iToggler; // used by EAlternate fill-rule
	TInt iNestingLevel; // used by EWinding fill-rule
	TInt iScanLineIntersection;
	TInt iRightMostPixelOnScanLine;
	TInt iFirstVertex;
	TBool iPolygonIsAllHorizontal;
	TInt iFirstScanLine;
	TInt iLastScanLine;
	TInt iCurrentScanLine;
	SFastData iFastData;
	SSlowData iSlowData;
	};

class CFbsDevice;
class TOpenFontCharMetrics;
class CFbsBitGc : public CBitmapContext
	{
public:
	enum TGraphicsOrientation
		{
		EGraphicsOrientationNormal,
		EGraphicsOrientationRotated90,
		EGraphicsOrientationRotated180,
		EGraphicsOrientationRotated270
		};
public:
	IMPORT_C static CFbsBitGc* NewL();
	IMPORT_C virtual ~CFbsBitGc();
	IMPORT_C void Activate(CFbsDevice* aDevice);
	IMPORT_C void ActivateNoJustAutoUpdate(CFbsDevice* aDevice);
	IMPORT_C void BitBlt(const TPoint& aPoint,const CFbsBitGc& aGc);
	IMPORT_C void BitBlt(const TPoint& aPoint,const CFbsBitGc& aGc,const TRect& aSourceRect);
	IMPORT_C void BitBlt(const TPoint& aPoint,const CFbsBitmap* aBitmap);
	IMPORT_C void BitBlt(const TPoint& aPoint,const CFbsBitmap* aBitmap,const TRect& aSourceRect);
	IMPORT_C void BitBltMasked(const TPoint& aPoint,const CFbsBitmap* aBitmap,const TRect& aSourceRect,const CFbsBitmap* aMaskBitmap,TBool aInvertMask);
	IMPORT_C void CancelClipping();
	IMPORT_C void CancelClippingRect();
	IMPORT_C void CancelClippingRegion();
	IMPORT_C void Clear();
	IMPORT_C void Clear(const TRect& aRect);
	IMPORT_C void CopyRect(const TPoint& aOffset,const TRect& aRect);
	IMPORT_C void CopySettings(const CFbsBitGc& aGc);
	IMPORT_C CGraphicsDevice* Device() const;
	IMPORT_C void DiscardBrushPattern();
	IMPORT_C void DiscardFont();
	IMPORT_C void DrawArc(const TRect& aRect,const TPoint& aStart,const TPoint& aEnd);
	IMPORT_C void DrawPie(const TRect& aRect,const TPoint& aStart,const TPoint& aEnd);
	IMPORT_C void DrawBitmap(const TPoint& aTopLeft,const CFbsBitmap* aSource);
	IMPORT_C void DrawBitmap(const TRect& aDestRect,const CFbsBitmap* aSource);
	IMPORT_C void DrawBitmap(const TRect& aDestRect,const CFbsBitmap* aSource,const TRect& aSourceRect);
	IMPORT_C void DrawRoundRect(const TRect& aRect,const TSize& aEllipse);
	IMPORT_C void DrawPolyLine(const CArrayFix<TPoint>* aPointList);
	IMPORT_C void DrawPolyLineNoEndPoint(const CArrayFix<TPoint>* aPointList);
	IMPORT_C void DrawPolyLine(const TPoint* aPointList,TInt aNumPoints);
	IMPORT_C void DrawPolyLineNoEndPoint(const TPoint* aPointList,TInt aNumPoints);
	IMPORT_C TInt DrawPolygon(const CArrayFix<TPoint>* aPointList,CGraphicsContext::TFillRule aFillRule=CGraphicsContext::EAlternate);
	IMPORT_C TInt DrawPolygon(const TPoint* aPointList,TInt aNumPoints,CGraphicsContext::TFillRule aFillRule=CGraphicsContext::EAlternate);
	IMPORT_C void DrawEllipse(const TRect& aRect);
	IMPORT_C void DrawLine(const TPoint& aStart,const TPoint& aEnd);
	IMPORT_C void DrawLineTo(const TPoint& aPoint);
	IMPORT_C void DrawLineBy(const TPoint& aVector);
	IMPORT_C void DrawRect(const TRect& aRect);
	IMPORT_C void DrawText(const TDesC& aText);
	IMPORT_C void DrawText(const TDesC& aText,const TPoint& aPosition);
	IMPORT_C void DrawText(const TDesC& aText,const TRect& aBox);
	IMPORT_C void DrawText(const TDesC& aText,const TRect& aBox,TInt aBaselineOffset,TTextAlign aHrz=ELeft,TInt aMargin=0);
	IMPORT_C void DrawText(const TDesC& aText,const TRect& aBox,TInt aBaselineOffset,TInt aTextWidth,TTextAlign aHrz=ELeft,TInt aMargin=0);
	IMPORT_C void DrawTextVertical(const TDesC& aText,TBool aUp);
	IMPORT_C void DrawTextVertical(const TDesC& aText,const TPoint& aPosition,TBool aUp);
	IMPORT_C void DrawTextVertical(const TDesC& aText,const TRect& aBox,TBool aUp);
	IMPORT_C void DrawTextVertical(const TDesC& aText,const TRect& aBox,TInt aBaselineOffset,TBool aUp,TTextAlign aVert=ELeft,TInt aMargin=0);
	IMPORT_C void DrawTextVertical(const TDesC& aText,const TRect& aBox,TInt aBaselineOffset,TInt aTextWidth,TBool aUp,TTextAlign aVert=ELeft,TInt aMargin=0);
	IMPORT_C void MapColors(const TRect& aRect,const TRgb* aColors,TInt aNumPairs=2,TBool aMapForwards=ETrue);
	IMPORT_C void MoveTo(const TPoint& aPoint);
	IMPORT_C void MoveBy(const TPoint& aVector);
	IMPORT_C void OrientationsAvailable(TBool aOrientation[4]);
	IMPORT_C void Plot(const TPoint& aPoint);
	IMPORT_C void RectDrawnTo(TRect& aRect);
	IMPORT_C void Reset();
	IMPORT_C void Resized();
	IMPORT_C void SetBrushColor(const TRgb& aColor);
	IMPORT_C void SetBrushOrigin(const TPoint& aOrigin);
	IMPORT_C void SetBrushStyle(TBrushStyle aBrushStyle);
	IMPORT_C void SetClippingRegion(const TRegion* aRegion);
	IMPORT_C void SetClippingRect(const TRect& aRect);
	IMPORT_C void SetDitherOrigin(const TPoint& aPoint);
	IMPORT_C void SetDrawMode(TDrawMode);
	IMPORT_C void SetOrigin(const TPoint& aPoint=TPoint(0,0));
	IMPORT_C void SetPenColor(const TRgb& aColor);
	IMPORT_C void SetPenStyle(TPenStyle);
	IMPORT_C void SetPenSize(const TSize& aSize);
	IMPORT_C void SetCharJustification(TInt aExcessWidth,TInt aNumGaps);
	IMPORT_C void SetWordJustification(TInt aExcessWidth,TInt aNumChars);
	IMPORT_C void SetUnderlineStyle(TFontUnderline aUnderlineStyle);
	IMPORT_C void SetUserDisplayMode(TDisplayMode aDisplayMode);
	IMPORT_C void SetStrikethroughStyle(TFontStrikethrough aStrikethroughStyle);
	IMPORT_C void SetShadowMode(TBool aShadowMode = EFalse);
	inline void SetFadeMode(TBool aFadeMode = EFalse);			//Deprecated
	inline void SetFadingParameters(TUint8 aBlackMap = 0);		//Deprecated
	IMPORT_C void SetFaded(TBool aFaded);		//Virtual from CBitmapContext
	IMPORT_C void SetFadingParameters(TUint8 aBlackMap,TUint8 aWhiteMap);	//Virtual from CBitmapContext
	IMPORT_C TBool SetOrientation(TGraphicsOrientation aOrientation);
	IMPORT_C void ShadowArea(const TRegion* aRegion);
	IMPORT_C void FadeArea(const TRegion* aRegion);
	IMPORT_C void UpdateJustification(const TDesC& aText);
	IMPORT_C void UpdateJustificationVertical(const TDesC& aText,TBool aUp);
	IMPORT_C void UseBrushPattern(const CFbsBitmap* aBitmap);
	IMPORT_C TInt UseBrushPattern(TInt aFbsBitmapHandle);
	IMPORT_C void UseFont(const CFont* aFont);
	IMPORT_C TInt UseFont(TInt aFontHandle);
	IMPORT_C void UseFontNoDuplicate(const CFbsBitGcFont* aFont);
	IMPORT_C TBool IsBrushPatternUsed() const;
	IMPORT_C TBool IsFontUsed() const;
	inline static TInt16 Load16(const TUint8* aPtr) { return TInt16(aPtr[0]+(aPtr[1]<<8)); }
private:
	CFbsBitGc();
	void AddRect(const TRect& aRect);
	void AnalyseEllipse(const TRect& rc,TPoint& srad,TPoint& erad,TPoint& center,TInt& startq,TInt& endq,TBool* quads);
	void BitMultiply(TUint32* aBinaryDataPtr,TInt aBitLength,TInt aMultiplier);
	void CheckDevice() const;
	TBool CheckDevice(const TRect& aRect) const;
	TUint32* ClipBinaryArray(TUint32* aArray,TUint32* aArrayLimit,TInt aArrayWordWd,TInt& aDataWd,TInt& aDataHt,TPoint& aPos);
	void ClipFillLine(TPoint,TPoint);
	void CopyCharWord(TUint32* aBinaryDataPtr,const TUint8* aData,TInt aBitShift);
	void CopyCharLine(TUint32* aBinaryDataPtr,TInt aBufferWords,const TUint8* aData,TInt aBitShift,TInt aCharWidth);
	void DrawText(const TDesC& aText,const TPoint& aPosition,TTextAlign aAlignment,
				  CFont::TTextDirection aDirection,const TRect* aBox = NULL);
	void DoBitBlt(const TPoint& aDest,CFbsDevice* aDevice,const TRect& aSourceRect);
	void DoBitBlt(const TPoint& aDest,CBitwiseBitmap* aBitmap,TUint32* aBase,const TRect& aSourceRect);
	void DoBitBltMasked(const TPoint& aDest,CBitwiseBitmap* aSourceBitmap,TUint32* aSourceBase,const TRect& aSourceRect,CBitwiseBitmap* aMaskBitmap,TUint32* aMaskBase,TBool aInvertMask,const TPoint& aDitherOrigin,TInt aShadowMode);
	void DoBitBltMaskedFlicker(const TPoint& aDest,CBitwiseBitmap* aSourceBitmap,TUint32* aSourceBase,const TRect& aSourceRect,CBitwiseBitmap* aMaskBitmap,TUint32* aMaskBase,TBool aInvertMask,const TPoint& aDitherOrigin,TInt aShadowMode);
	void DoBitBltMaskedNonFlicker(const TPoint& aDest,CBitwiseBitmap* aSourceBitmap,TUint32* aSourceBase,const TRect& aSourceRect,CBitwiseBitmap* aMaskBitmap,TUint32* aMaskBase,TBool aInvertMask,const TPoint& aDitherOrigin,TInt aShadowMode);
	void DoBitBltMaskedNonFlickerSolid(const TPoint& aDest,CBitwiseBitmap* aSourceBitmap,TUint32* aSourceBase,const TRect& aSourceRect,CBitwiseBitmap* aMaskBitmap,TUint32* aMaskBase,TBool aInvertMask,const TPoint& aDitherOrigin,TInt aShadowMode);
	void DoBitBltMaskedNonFlickerPatterned(const TPoint& aDest,CBitwiseBitmap* aSourceBitmap,TUint32* aSourceBase,const TRect& aSourceRect,CBitwiseBitmap* aMaskBitmap,TUint32* aMaskBase,TBool aInvertMask,const TPoint& aDitherOrigin,TInt aShadowMode);
	void DoBitBltAlpha(const TPoint& aDest,CBitwiseBitmap* aSourceBitmap,TUint32* aSourceBase,const TRect& aSourceRect,CBitwiseBitmap* aMaskBitmap,TUint32* aMaskBase,const TPoint& aDitherOrigin,TInt aShadowMode);
	void DoCopyRect(const TPoint&,const TRect&);
	void DoDrawBitmap(const TRect&,CBitwiseBitmap*,TUint32* aBase,const TRect&,const TPoint& aDitherOrigin);
	void DoDrawLine(TPoint aStart,TPoint aEnd,TBool aDrawStartPoint);
	void DoDrawDottedWideLine(const TPoint& pt1,const TPoint& pt2,TBool drawstart,const TRect& screenrect);
	void DoDrawSolidWideLine(const TPoint& pt1,const TPoint& pt2,TBool drawstart,const TRect& screenrect);
	void DoDrawText(CFont::TPositionParam& aParam);
	void DoDrawCharacter(const TPoint& aTopLeft,const TSize& aDataSize,const TUint8* aData);
	void DoDrawTextEx(CFont::TPositionParam& aParam,const CBitmapFont* font);
	void DoDrawCharacterEx(const TPoint& aTopLeft,const TSize& aDataSize,const TUint8* aData,
		TBool aBold,TBool aItalic,TInt aSemiAscent);
	void DoDrawTextLarge(CFont::TPositionParam& aParam,const CBitmapFont* font);
	void DoDrawCharacterLarge(const TPoint& aTopLeft,const TSize& aDataSize,const TUint8* aData,
		TBool aBold,TBool aItalic,TInt aSemiAscent,TInt aWidthFactor,TInt aHeightFactor);
	void DoDrawCharacterExLarge(const TPoint& aTopLeft,const TSize& aDataSize,const TUint8* aData,
		TBool aBold,TBool aItalic,TInt aSemiAscent,TInt aWidthFactor,TInt aHeightFactor);
	void DoDrawCharacterMultiplied(const TPoint& aTopLeft,const TSize& aDataSize,const TUint8* aData,
		TBool aBold,TBool aItalic,TInt aSemiAscent,TInt aWidthMultiplier,TInt aHeightMultiplier);
	void DoDrawTextVertical(CFont::TPositionParam& aParam,const CBitmapFont* font,TBool aUp);
	void DoDrawCharacterVertical(const TPoint& aTopLeft,const TSize& aDataSize,const TUint8* aData,
		TBool aBold,TBool aItalic,TInt aSemiAscent,TInt aWidthFactor,TInt aHeightFactor,TBool aUp);
	void DoPlot(const TPoint& pt);
	void EllipseFill(const TRect& aRect);
	void EllipseOutline(const TRect& aRect);
	void EllipseOutlineWide(const TRect& aRect);
	void GetUnderlineMetrics(TInt& aTop,TInt& aBottom);
	void GetStrikethroughMetrics(TInt& aTop,TInt& aBottom);
	void OutputCharLine(TPoint aPrintPos,TUint32* aBuffer,TInt aDataLength,TInt aNum,TBool aBold,TInt aWidthFactor,TInt aHeightFactor);
	void OutputCharLineMultiplied(TPoint aPrintPos,TUint32* aBuffer,TInt aDataLength,TInt aNum,TBool aBold,TInt aWidthMultiplier,TInt aHeightMultiplier);
	void OutputCharLineVertical(TPoint aPrintPos,TUint32* aBuffer,TInt aDataLength,TInt aNum,TBool aBold,TInt aWidthFactor,TInt aHeightFactor,TBool aUp);
	void PenAllocate();
	void PenDrawClipped(TPoint aPoint);
	void PenDrawDeferred(TPoint aPoint,TInt* aArray,TInt aFirstElement);
	void PieArcOutline(const TRect& aRect,const TPoint& aStartRadius,const TPoint& aEndRadius,TBool aDoPie);
	void PieFill(const TRect& aRect,const TPoint& aStartRadius,const TPoint& aEndRadius);
	void PieShell(const TRect& ellrect,const TPoint& startradius,const TPoint& endradius,TBool quads[5],TInt startquad,TInt endquad);
	void PieTriangles(TBool aInside,const TPoint& aStart,const TPoint& aEnd);
	void PieSliver(const TRect& ellrect,const TPoint& startradius,const TPoint& endradius,TInt quad);
	void PolyFill(const CArrayFix<TPoint>* aPointList,TFillRule aFillRule);
	void PolyFillLarge(const CArrayFix<TPoint>* aPointList,TFillRule aFillRule);
	void PolyFill(const TPoint* aPointList,TInt aNumPoints,TFillRule aFillRule);
	void PolyFillLarge(const TPoint* aPointList,TInt aNumPoints,TFillRule aFillRule);
	void PolyOutline(const CArrayFix<TPoint>* aPointList);
	void PolyOutline(const TPoint* aPointList,TInt aNumPoints);
	void RectFill(const TRect& aRect);
	void RoundRectFill(const TRect& aRect,TSize aSize);
	void RoundRectOutline(const TRect& aRect,TSize aSize);
	void SetupDevice() const;
	void ShadowFadeArea(const TRegion* aRegion,TInt8 aShadowMode);
	TBool UserClipRect(TRect& aRect);
private:
	CFbsBitGcBitmap iBrushBitmap;
	TBool iBrushUsed;
	TRgb iBrushColor;
	TPoint iBrushOrigin;
	TBrushStyle iBrushStyle;
	TRect iClipRect;
	TRegionFix<1> iDefaultRegion;
	const TRegion* iDefaultRegionPtr;
	TRect iUserClipRect;
	CFbsDevice* iDevice;
	TPoint iDitherOrigin;
	TInt iDotLength;
	TInt iDotMask;
	TInt iDotParam;
	TInt iDotDirection;
	TDrawMode iDrawMode;
	TRect iDrawnTo;
	CFbsBitGcFont iFont;
	TInt iCharJustExcess;
	TInt iCharJustNum;
	TInt iWordJustExcess;
	TInt iWordJustNum;
	TPoint iLastPrintPosition;
	TPoint iLinePosition;
	TPoint iOrigin;
	TInt* iPenArray;
	TRgb iPenColor;
	TPenStyle iPenStyle;
	TSize iPenSize;
	TInt8 iShadowMode;
	TInt8 iAutoUpdateJustification;
	TInt8 iSpareByte1;
	TInt8 iSpareByte2;
	TFontStrikethrough iStrikethrough;
	TFontUnderline iUnderline;
	TDisplayMode iUserDisplayMode;
	};

inline void CFbsBitGc::SetFadeMode(TBool aFadeMode /*=EFalse*/)
	{SetFaded(aFadeMode);}
inline void CFbsBitGc::SetFadingParameters(TUint8 aBlackMap /*=0*/)
	{SetFadingParameters(aBlackMap,255);}		//255 is the value of white map when not fading

#endif

