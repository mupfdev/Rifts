// BITMAP.H
//
// Copyright (c) 1995-2001 Symbian Ltd. All rights reserved.
//

#if !defined(__BITMAP_H__)
#define __BITMAP_H__
#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif
#if !defined(__GDI_H__)
#include <gdi.h>
#endif

const TUid KCBitwiseBitmapUid={268435520};
const TUid KMultiBitmapFileImageUid={268435522};
const TInt KMaxLargeBitmapAlloc=0x1000;
const TInt KCompressionBookMarkThreshold=0x2000;

enum TBitmapfileCompression
	{
	ENoBitmapCompression = 0,
	EByteRLECompression = 1,
	ETwelveBitRLECompression = 2,
	ESixteenBitRLECompression = 3,
	ETwentyFourBitRLECompression = 4,
	EByteRLECompressionInMemory = 51,
	ETwelveBitRLECompressionInMemory = 52
	};

class TRgb24bit
	{
public:
	TUint8 iRed;
	TUint8 iGreen;
	TUint8 iBlue;
	};

class SEpocBitmapHeader
	{
public:
	TInt iBitmapSize;
	TInt iStructSize;
	TSize iSizeInPixels;
	TSize iSizeInTwips;
	TInt iBitsPerPixel;
	TBool iColor;
	TInt iPaletteEntries;
	TBitmapfileCompression iCompression;
	};

class TLineScanningPosition
	{
public:
	TLineScanningPosition(TUint8* aSrcDataPtr): iSrcDataPtr(aSrcDataPtr), iCursorPos(0), iScanLineBuffer(NULL) { };
	TUint8* iSrcDataPtr;
	TInt iCursorPos;
	HBufC8* iScanLineBuffer;
	};

// BitGdi bitmap class (pseudo-CXxx class)

class CChunkPile;
class CBitwiseBitmap
	{
	friend class CFbTop;
	friend class CFbClient;
	friend class CFbsBitmap;
	friend class CBitmapObject;
	friend class CFbsBitmapAsyncStreamer;
private:
	class TCompressionBookMark
		{
	public:
		TCompressionBookMark();
	public:
		inline void CalculateCheckSum();
		inline TBool IsCheckSumOk();
		TInt iSrcDataOffset;
		TInt iCursorPos;
		TUint32 iCheckSum;
		TInt iCheckSum2;
		};
public:
	IMPORT_C TUid Uid() const;
	IMPORT_C void ExternalizeL(RWriteStream& aStream,const CFbsBitmap& aHandleBitmap) const;
	IMPORT_C void ExternalizeRectangleL(RWriteStream& aStream,const TRect& aRect,const CFbsBitmap& aHandleBitmap) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C static void InternalizeHeaderL(RReadStream& aStream,SEpocBitmapHeader& aHeader);
	IMPORT_C TSize SizeInPixels() const;
	IMPORT_C TSize SizeInTwips() const;
	IMPORT_C TDisplayMode DisplayMode() const;
	IMPORT_C TInt HorizontalTwipsToPixels(TInt aTwips) const;
	IMPORT_C TInt VerticalTwipsToPixels(TInt aTwips) const;
	IMPORT_C TInt HorizontalPixelsToTwips(TInt aPixels) const;
	IMPORT_C TInt VerticalPixelsToTwips(TInt aPixels) const;
	IMPORT_C void GetPixel(TRgb& aColor,const TPoint& aPos,TUint32* aBase) const;
	IMPORT_C TInt GetScanLinePtr(TUint32*& aSlptr, TPoint& aPixel,TInt& aLength, TUint32* aBase, TLineScanningPosition& aLineScanningPosition) const;
	IMPORT_C void GetScanLine(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TBool aDither,const TPoint& aDitherOffset,TDisplayMode aDispMode,TUint32* aBase, TLineScanningPosition& aLineScanningPosition) const;
	IMPORT_C void GetScanLine(TUint32*& aSlptr, TDes8& aBuf,const TPoint& aPixel,TInt aLength,TBool aDither,const TPoint& aDitherOffset,TDisplayMode aDispMode) const;
	IMPORT_C void GetScanLine(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TBool aDither,const TPoint& aDitherOffset,TDisplayMode aDispMode,TUint32* aBase) const;
	IMPORT_C void GetVerticalScanLine(TDes8& aBuf,TInt aX,TBool aDither,const TPoint& aDitherOffset,TDisplayMode aDispMode,TUint32* aBase) const;
	IMPORT_C void StretchScanLine(TDes8& aBuf,const TPoint& aPixel,TInt aClipStrchX,TInt aClipStrchLen,TInt aStretchLength,TInt aOrgX,TInt aOrgLen,const TPoint& aDitherOffset,TDisplayMode aDispMode,TUint32* aBase) const;
	IMPORT_C void StretchScanLine(TDes8& aBuf,const TPoint& aPixel,TInt aClipStrchX,TInt aClipStrchLen,TInt aStretchLength,TInt aOrgX,TInt aOrgLen,const TPoint& aDitherOffset,TDisplayMode aDispMode,TUint32* aBase, TLineScanningPosition& aLineScanningPosition) const;
	IMPORT_C TUint32* ScanLineAddress(TUint32* aBase,TUint aY) const;
	IMPORT_C TBool IsMonochrome(TUint32* aBase) const;
	IMPORT_C void Compress(TUint8* aNewData,TUint8* aOldData);
	IMPORT_C TBool IsLargeBitmap() const;
	IMPORT_C TInt CompressData();
	IMPORT_C void SetCompressionBookmark(TLineScanningPosition& aLineScanningPosition, TUint32* aBase, const CFbsBitmap* aFbsBitmap);
	IMPORT_C TInt HardwareBitmapHandle() const;
	IMPORT_C TBool IsCompressedInRAM() const;
private:
	IMPORT_C void operator delete(TAny*);
	IMPORT_C CBitwiseBitmap(RHeap* aHeap,CChunkPile* aPile);
	IMPORT_C ~CBitwiseBitmap();
	IMPORT_C void Reset();
	IMPORT_C TInt Construct(const TSize& aSize,TDisplayMode aDispMode);
	IMPORT_C void ConstructL(RFs& aFs,const TDesC& aFilename,TInt32 aId);
	IMPORT_C TInt Resize(const TSize& aSize);
private:
	void GenerateLineFromCompressedTwelveBitData(TUint8* aDestBuffer, const TPoint& aPixel,TInt aLength,TUint32* aBase, TLineScanningPosition& aLineScanningPosition) const;
	void GenerateLineFromCompressedEightBitData(TUint8* aDestBuffer, const TPoint& aPixel,TInt aLength,TUint32* aBase, TLineScanningPosition& aLineScanningPosition) const;
	TUint8 GetGrayPixelEx(TInt aX,TUint32* aScanLineAddress) const;
	TRgb GetRgbPixelEx(TInt aX,TUint32* aScanLineAddress) const;
	void GetScanLineGray2(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TBool aDither,const TPoint& aDitherOffset,TUint32* aScanlinePtr) const;
	void GetScanLineGray4(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TBool aDither,const TPoint& aDitherOffset,TUint32* aScanlinePtr) const;
	void GetScanLineGray16(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TUint32* aScanlinePtr) const;
	void GetScanLineGray256(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TUint32* aScanlinePtr) const;
	void GetScanLineColor16(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TUint32* aScanlinePtr) const;
	void GetScanLineColor256(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TUint32* aScanlinePtr) const;
	void GetScanLineColor4K(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TUint32* aScanlinePtr) const;
	void GetScanLineColor64K(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TUint32* aScanlinePtr) const;
	void GetScanLineColor16M(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TUint32* aScanlinePtr) const;
	void GetScanLineColorRgb(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TUint32* aScanlinePtr) const;
	void GetScanLineExBits(TDes8& aBuf,TInt aX,TInt aLength,TUint32* aScanlinePtr) const;
	void GetScanLineExBytes(TDes8& aBuf,TInt aX,TInt aLength,TUint32* aScanlinePtr) const;
	void DoExternalizeDataCompressedL(RWriteStream& aStream,TUint8* aData,TInt aSizeInBytes) const;
	void DoExternalizeByteDataCompressedL(RWriteStream& aStream,TUint8* aData,TInt aSizeInBytes) const;
	void DoExternalizeTwelveBitDataCompressedL(RWriteStream& aStream,TUint8* aData,TInt aSizeInBytes) const;
	void DoExternalizeSixteenBitDataCompressedL(RWriteStream& aStream,TUint8* aData,TInt aSizeInBytes) const;
	void DoExternalizeTwentyFourBitDataCompressedL(RWriteStream& aStream,TUint8* aData,TInt aSizeInBytes) const;
	TInt SizeOfDataCompressed(TUint8* aData,TInt aSizeInBytes) const;
	TInt SizeOfByteDataCompressed(TUint8* aData,TInt aSizeInBytes) const;
	TInt SizeOfTwelveBitDataCompressed(TUint8* aData,TInt aSizeInBytes) const;
	TInt SizeOfSixteenBitDataCompressed(TUint8* aData,TInt aSizeInBytes) const;
	TInt SizeOfTwentyFourBitDataCompressed(TUint8* aData,TInt aSizeInBytes) const;
	TBool TrueColorPointerCompare(TUint8* aColorPointer,TUint8 aComponent1,TUint8 aComponent2,TUint8 aComponent3) const;
	void DoInternalizeL(RReadStream& aStream,TInt aSrceSize,TUint32* aBase);
	void DoInternalizeCompressedDataL(RReadStream& aStream,TInt aSrceSize,TUint32* aBase,TBitmapfileCompression aCompression);
	void DoDecompressByteData(TUint8* aDestBuffer,TInt aDestSize,TUint8* aSrceBuffer,TInt aSrceSize);
	void DoDecompressByteDataAlt(RReadStream& aStream,TInt aSrceSizeInBytes,TUint32* aBase);
	void DoDecompressTwelveBitData(TUint8* aDestBuffer,TInt aDestSize,TUint8* aSrceBuffer,TInt aSrceSize);
	void DoDecompressTwelveBitDataAlt(RReadStream& aStream,TInt aSrceSizeInBytes,TUint32* aBase);
	void DoDecompressSixteenBitData(TUint8* aDestBuffer,TInt aDestSize,TUint8* aSrceBuffer,TInt aSrceSize);
	void DoDecompressSixteenBitDataAlt(RReadStream& aStream,TInt aSrceSizeInBytes,TUint32* aBase);
	void DoDecompressTwentyFourBitData(TUint8* aDestBuffer,TInt aDestSize,TUint8* aSrceBuffer,TInt aSrceSize);
	void DoDecompressTwentyFourBitDataAlt(RReadStream& aStream,TInt aSrceSizeInBytes,TUint32* aBase);
	void DoStretchScanLine(TDes8& aBuf,TInt x,TInt y,TInt aClipStrchX,TInt aClipStrchLen,TInt aStretchLength,TInt aOrgX,TInt aOrgLen,const TPoint& aDitherOffset,TDisplayMode aDispMode,TUint32* aBase,TLineScanningPosition& aLineScanningPosition) const;
	void DoCompressScanLine(TDes8& aBuf,TInt x,TInt y,TInt aClipStrchX,TInt aClipStrchLen,TInt aStretchLength,TInt aOrgX,TInt aOrgLen,const TPoint& aDitherOffset,TDisplayMode aDispMode,TUint32* aBase,TLineScanningPosition& aLineScanningPosition) const;
	TUint32 HashTo1bpp(TUint32 aGray256,TBool aOddX,TBool aOddY) const;
	TUint32 HashTo2bpp(TUint32 aGray256,TInt aDitherIndex) const;
	TBool IsWordMonochrome(TUint32 aWord) const;
	TUint32* DataAddress() const;
	static void WhiteFill(TUint8* aData,TInt aDataSize,TDisplayMode aDispMode);
	static TInt ByteWidth(TInt aPixelWidth,TDisplayMode aDispMode);
	static TInt Bpp(TDisplayMode aDispMode);
	static TBool IsColor(TDisplayMode aDispMode);
	static TDisplayMode DisplayMode(TInt aBpp,TBool aColor);
	static TBitmapfileCompression CompressionType(TInt aBpp);
	TInt DoGetScanLinePtr(TUint32*& aSlptr, TPoint& aPixel,TInt aLength, TUint32* aBase, TLineScanningPosition& aLineScanningPosition) const;
private:
	const TUid iUid;
	TDisplayMode iDispMode;
	RHeap* iHeap;
	CChunkPile* iPile;
	TInt iByteWidth;
	SEpocBitmapHeader iHeader;
	RChunk iLargeChunk;
	TInt iDataOffset; // offset from "this" in bytes
	};

#endif
