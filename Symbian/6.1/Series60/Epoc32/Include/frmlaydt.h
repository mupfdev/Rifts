// FRMLAYDT.H
//
// Copyright (c) 1997-1999 Symbian Ltd. All rights reserved.
//

#ifndef __FRMLAYDT_H__
#define __FRMLAYDT_H__

#include <e32std.h>
#include <e32base.h>
#include <gdi.h>
#include <txtlaydc.h>
#include "frmvis.h"

class TLineSegment;
class TTextBox;
class TParaBorder;
class CFormLine;
class CLineLayout;

#if defined(TIMING_CODE)
class CWindowGc;
class RWsSession;
#endif

//
// This class is internal but needs to be visible because public
// enums defined here are part of the interface
//

/**
 *
 * Layout data.
 *
 * Most of this class is internal to EPOC, but it defines two
 * enumerations which are part of the Text Views API.
 *
 * @since 5.0
 * @lib ""
 */

class CLayoutData : public CBase
	{
public:
	enum
		{
		EFLargeNumber = KMaxTInt / 3,	// must be less than KMaxTInt/2 to avoid overflow problems
		EFMaximumTBoxLength = 256,
		EFFontHeightIncreaseFactor = 7,	// by default, increase the font height by this percentage
		EFMinimumLineDescent = 3,		// by default, this is the minimum line descent
		EFBaseLinePosition = 82			// position down ViewRect for BaseLine
		};
	enum
		{
		EFHeightForFormattingAllText=EFLargeNumber,
		EFBodyWidthForNoWrapping=EFLargeNumber
		};
	
	/**
	 *
	 * Flags used when converting between layout coordinates and document
	 * position (see <code>CTextLayout::XyPosToDocPosL()</code> and
	 * <code>DocPosToXyPosL()</code>).
	 * @since 
	 */
	enum		
		{
		/**
		 * Count individual characters and don't treat the end of the line specially.
		 * @deprecated 6.2
		 */
		EFIndividualChars = 0,
		/**
		 * Only consider the beginnings and ends of whole lines. Only useful in
		 * XyToDocPos functions.
		 */
		EFWholeLinesOnly = 1,
		/**
		 * Only consider the beginnings and ends of whole TBoxs so as not to
		 * access the document. Only useful in XyToDocPos functions.
		 */
		EFWholeTBoxesOnly=EFWholeLinesOnly,
		/**
		 * Disambiguate the end position of a line from the start position of
		 * the next line. If both positions are the same, a position at the end
		 * of the line will be invalid, and the position before will be
		 * returned instead.
		 */
		EFDisambiguateEndOfLine = 2,
		};	
	
	/**
	 *
	 * Format modes.
	 * @since 
	 */

	enum TFormatMode
		{
		/** Dimensions stored in pixels with no mapping between format and image device. */
		EFScreenMode, 
		/** Dimensions stored in twips with no mapping. */
		EFPrintMode,
		/** Dimensions stored in twips with partial mapping. */
		EFPrintPreviewMode, 
		/** Dimensions stored in twips with full mapping. */
		EFWysiwygMode
		};
public:
	CLayoutData();
 	void ConstructL(MLayDoc *aDoc,TInt aWrapWidth);
	~CLayoutData();
	void SetImageDeviceMap(MGraphicsDeviceMap* aGd);
	inline void SetLabelsGDMap(MGraphicsDeviceMap* aDeviceMap);
	inline void SetFormatDeviceMap(MGraphicsDeviceMap* aGd);
	void SetBandHeight(TInt aHeight);
	TInt BandHeightInPixels() const;
	TInt BodyWidthInPixels() const;
	TInt VisibleHeightInPixels() const;
	void SetFormatAllText(TBool aAll);
	TBool IsFormattingAllText() const;
	inline void SetWrapWidth(TInt aWidth);
	void SetFormatMode(CLayoutData::TFormatMode aMode,TInt aWrapWidth
																,MGraphicsDeviceMap* aFormatDevice);
	inline void SetToWrapping(TBool aIsWrapping);
	void SetLayDoc(MLayDoc *aDoc);
	inline TInt DocumentLength() const;
	TInt EffectiveBodyWidth(const CParaFormat* aParaFormat=NULL) const;
	TBool IsParaWrapping(const CParaFormat* aParaFormat) const;
	TBool GetParaFormatL(TInt aDocPos,CParaFormat*& aParaFormat);
	TBool UpdateStoredParaFormatL(TInt aDocPos);
	void DestroyStoredParaFormat();
	void UpdateLabelsParaFormatL();
	void DestroyLabelsParaFormat();
	inline TBool IsBackgroundFormatting();
	TInt SpaceBeforeInPixels(const CParaFormat *aParaFormat);
	TInt SpaceAfterInPixels(const CParaFormat *aParaFormat);
	void GetNearestFontInTwipsL(CFont *&aFont,const TFontSpec &aFontSpec);
	void ReleaseLastFont();
	TInt VertFormatToImagePixels(TInt aInt) const;
	TInt HorzFormatToImagePixels(TInt aInt) const;
	TInt HorzTwips2Pixels(TInt aTwips) const;
	TInt VertTwips2Pixels(TInt aTwips) const;
	void UseImageDevice(TBool aImage=ETrue);
	inline void UseLabelDevice(TBool aLabel=ETrue);
	MGraphicsDeviceMap* CurrentImageDevice() const;
	MGraphicsDeviceMap* GetCurrentDevice() const;
	TText MapSpecialCharacter(TText aChar) const;
	static TInt SingleBorderWidthInTwips(const TParaBorder& aBorder);
	static TInt TotalBorderWidthInTwips(const TParaBorder& aBorder);
	static TInt SingleBorderWidthInPixels(const MGraphicsDeviceMap* aGd,const TParaBorder& aBorder,TBool aHoriz);
	TInt TotalBorderWidthInPixels(const TParaBorder& aBorder,TBool aHoriz);
	/** @deprecated 7.0 */
	inline void SetExcludePartialLines(TBool);
	/** @deprecated 7.0 */
	inline TBool ExcludingPartialLines();
	TBool CanMapSpecialCharacters() const;
	TBool EnquirePageBreakVisible(TInt aPos,TInt aLength) const;
	TInt AscentInPixels(const CFont* aFont) const;
	TInt DescentInPixels(const CFont* aFont) const;
	inline TInt IncreaseFontHeight(TInt aHeight) {return (iFontHeightIncreaseFactor*aHeight)/100;}
	inline void SetFontHeightIncreaseFactor(TInt aPercentage);
	inline TInt FontHeightIncreaseFactor() const;
	inline void SetMinimumLineDescent(TInt aPixels);
	inline TInt MinimumLineDescent() const;

public:
	MLayDoc *iDoc;
	CFormLine *iFormLine;
	CFont *iLastCreatedFont;
	CParaFormat *iParaFormat;
	CParaFormat *iLabelsParaFormat;
	CLineLayout *iReadLine;
	TLineSegment* iReadLineSegment;
	TTextBox *iReadTBox;
	TBool iIsWrapping;
	TBool iIsBackgroundFormatting;
	TInt iLabelsWidth;
	TInt iFontHeightIncreaseFactor; // increase the font height by (100/<n>)%
	TInt iMinimumLineDescent;
	TNonPrintingCharVisibility iShowFormatChars;
	TFormatMode iFormatMode;
	TTextBox* iFirstNonUnderlineBox;
private:
	MGraphicsDeviceMap* iImageDevice; // Always used for viewing text.
	MGraphicsDeviceMap* iLabelsDevice; // On the image device only
	MGraphicsDeviceMap* iFormatDevice; // Allways used for initial formatting of text.
	TBool iUseImageDevice;	 // Switch between the two devices.
	TBool iUseLabelsDevice;
	TInt iVisibleHeight; // In pixels for screen mode and Wysiwyg mode (printing - twips)
	TInt iBandHeight;
	TInt iWrapWidth;	 // In pixels for screen mode only, otherwise twips.
	TInt iReserved1;
#if defined(TIMING_CODE)
public:
	IMPORT_C void SetTimingFlags(TUint aFlags);
	IMPORT_C void SetHandle(CWindowGc *aGc,RWsSession *aWs);
	inline void SetCallBack(TCallBack aCallBack) {iCallBack=aCallBack;}
	class TTestTimingCode* iTestTimingCode;
	TUint iTimingFlags;
	CWindowGc *iGc;
	RWsSession *iWs;
	TCallBack iCallBack;
#endif
	};

// inline functions

inline void CLayoutData::SetLabelsGDMap(MGraphicsDeviceMap* aDeviceMap)
	{
	iLabelsDevice = aDeviceMap;
	}

inline void CLayoutData::SetFormatDeviceMap(MGraphicsDeviceMap* aGd)
	{
	iFormatDevice = aGd;
	}

inline void CLayoutData::SetWrapWidth(TInt aWrapWidth)
	{
	iWrapWidth = aWrapWidth;
	}

inline void CLayoutData::SetToWrapping(TBool aIsWrapping)
	{
	iIsWrapping = aIsWrapping;
	}

inline TInt CLayoutData::DocumentLength() const
	{
	return iDoc->LdDocumentLength();
	}

inline TBool CLayoutData::IsBackgroundFormatting()
	{
	return iIsBackgroundFormatting;
	}

inline void CLayoutData::UseLabelDevice(TBool aLabel)
	{
	iUseLabelsDevice = aLabel;
	}

// deprecated functionality
inline void CLayoutData::SetExcludePartialLines(TBool){}

inline TBool CLayoutData::ExcludingPartialLines()
	{
	// deprecated functionality: we will never be excluding partial lines
	return EFalse;
	}

inline void CLayoutData::SetFontHeightIncreaseFactor(TInt aPercentage)
	{
	iFontHeightIncreaseFactor = aPercentage;
	}

inline TInt CLayoutData::FontHeightIncreaseFactor() const
	{
	return iFontHeightIncreaseFactor;
	}

inline void CLayoutData::SetMinimumLineDescent(TInt aPixels)
	{
	iMinimumLineDescent = aPixels;
	}

inline TInt CLayoutData::MinimumLineDescent() const
	{
	return iMinimumLineDescent;
	}

#endif
