// FBS.H
//
// Copyright (C) 1995-2000 Symbian Ltd. All rights reserved.
//

#ifndef __FBS_H__
#define __FBS_H__

#include <e32std.h>
#include <gdi.h>
#include <fntstore.h>
#include <bitmap.h>

const TUid KCFbsFontUid = { 268435518 };
const TUid KMultiBitmapRomImageUid = { 268435521 };
const TUint32 KFontBitmapServerUidValue = 0x10003a16;
const TUid KFontBitmapServerUid = { KFontBitmapServerUidValue };

IMPORT_C TInt FbsStartup();

class SCharWidth
	{
public:
	TInt iLeftAdjust;
	TInt iRightAdjust;
	TInt iMove;
	TInt iWidth;
	};

class RFbsSession : protected RSessionBase
	{
	friend class CFbsBitmap;
	friend class CFbsBitmapAsyncStreamer;
public:
	IMPORT_C RFbsSession();
	IMPORT_C static TInt Connect();
	IMPORT_C static void Disconnect();
	IMPORT_C static RFbsSession* GetSession();
	IMPORT_C void CallBack();
	IMPORT_C void SetCallBack(TCallBack aCallBack);
	IMPORT_C void ResetCallBack();
	IMPORT_C TInt ResourceCount();
	IMPORT_C TInt SendCommand(TInt aMessage,TInt aInt0=0,TInt aInt1=0,TInt aInt2=0,TInt aInt3=0) const;
	IMPORT_C TVersion Version();
	IMPORT_C TUint8* HeapBase() const;
	TInt SessionHandle() const { return Handle(); }
	TInt ScanLineBuffer(HBufC8*& aBuffer,TInt aSize);
private:
	TUint32* RomAddressIfCached(const TDesC& aFilename) const;
	void AddToCache(const TDesC& aFilename,TUint32* aFileAddress);
private:
	class TRomFileAddress
		{
	public:
		HBufC* iFilename;
		TUint32* iAddress;
		};
private:
	TInt iConnections;
	TCallBack iCallBack;
	RChunk iSharedChunk;
	RMutex iAddressMutex;
	RChunk iLargeBitmapChunk;
	RFs iFileServer;
	TRomFileAddress* iFileAddress1;
	TRomFileAddress* iFileAddress2;
	HBufC8* iScanLineBuffer;
	TUint32* iSpare;
	};

class CFbsFont: public CFont
	{
	friend class CFbsTypefaceStore;

	public:

	// instantiations of CFont virtual functions
	TUid TypeUid() const { return KCFbsFontUid; }
	IMPORT_C TInt HeightInPixels() const;
	IMPORT_C TInt AscentInPixels() const;
	IMPORT_C TInt CharWidthInPixels(TChar aChar) const;
	IMPORT_C TInt TextWidthInPixels(const TDesC& aText) const;
	IMPORT_C TInt BaselineOffsetInPixels() const;
	IMPORT_C TInt TextCount(const TDesC& aText,TInt aWidthInPixels) const;
	IMPORT_C TInt TextCount(const TDesC& aText,TInt aWidthInPixels,TInt& aExcessWidthInPixels) const;
	IMPORT_C TInt MaxCharWidthInPixels() const;
	IMPORT_C TInt MaxNormalCharWidthInPixels() const;
	IMPORT_C TFontSpec FontSpecInTwips() const;
	IMPORT_C CFont::TCharacterDataAvailability GetCharacterData(TUint aCode,TOpenFontCharMetrics& aMetrics,
			const TUint8*& aBitmap,TSize& aBitmapSize) const;

	IMPORT_C TBool GetFontMetrics(TOpenFontMetrics& aMetrics) const;
	IMPORT_C void TextWidthInPixels(const TDesC& aText,SCharWidth& aCharWidth) const;
	IMPORT_C TInt Handle() const;
	IMPORT_C TCharacterMetrics CharacterMetrics(TInt aCode,const TUint8*& aBytes) const;
	IMPORT_C TInt RawTextWidthInPixels(const TDesC& aText) const;
	IMPORT_C TBool GetFaceAttrib(TOpenFontFaceAttrib& aAttrib) const;
	IMPORT_C TBool IsOpenFont() const;
	IMPORT_C TBool HasCharacter(TInt aCode) const;

	protected:
	IMPORT_C CFbsFont();
	IMPORT_C ~CFbsFont();
	IMPORT_C CFbsFont(const CFbsFont& aFont);
	IMPORT_C CBitmapFont* Address() const;
	IMPORT_C TInt Duplicate(TInt aHandle);
	IMPORT_C void Reset();

	RFbsSession* iFbs;
	CBitmapFont* iAddressPointer;
	TInt iHandle;
	TInt iServerHandle;
	};

class CFbsBitmap : public CBase
	{
	friend class TBitmapUtil;
	friend class CBitwiseBitmap;
	friend class CFbsBitmapAsyncStreamer;
public:
	IMPORT_C CFbsBitmap();
	IMPORT_C ~CFbsBitmap();
	IMPORT_C void Reset();
	IMPORT_C static TInt ScanLineLength(TInt aLength,TDisplayMode aDispMode);
	IMPORT_C TDisplayMode DisplayMode() const;
	IMPORT_C TInt Create(const TSize& aSizeInPixels,TDisplayMode aDispMode);
	IMPORT_C TInt Duplicate(TInt aHandle);
	IMPORT_C TBool IsRomBitmap() const;
	IMPORT_C void SetRomBitmapL(CBitwiseBitmap* aRomBitmapPointer,TInt& aBitmapSizeInBytes);
	IMPORT_C TInt Load(const TDesC& aFileName,TInt32 aId=0,TBool aShareIfLoaded=ETrue);
	IMPORT_C TInt LoadAndCompress(const TDesC& aFileName,TInt32 aId=0,TBool aShareIfLoaded=ETrue);
	IMPORT_C TInt Save(const TDesC& aFilename);
	IMPORT_C static void StoreL(const TDesC& aFilename,TInt aNumSources,const TDesC* aSources[],TInt32 aSourceIds[]);
    IMPORT_C void GetScanLine(TDes8& aBuf,const TPoint& aPixel,TInt aLength,TDisplayMode aDispMode) const;
    IMPORT_C void SetScanLine(TDes8& aBuf,TInt aY) const;
	IMPORT_C void GetVerticalScanLine(TDes8& aBuf,TInt aX,TDisplayMode aDispMode) const;
	IMPORT_C void GetVerticalScanLine(TDes8& aBuf,TInt aX,const TPoint& aDitherOffset,TDisplayMode aDispMode) const;
	IMPORT_C TInt Handle() const;
	IMPORT_C SEpocBitmapHeader Header() const;
	IMPORT_C TInt HorizontalPixelsToTwips(TInt aPixels) const;
	IMPORT_C TInt HorizontalTwipsToPixels(TInt aTwips) const;
    IMPORT_C void GetPixel(TRgb& aColor,const TPoint& aPixel) const;
	IMPORT_C TInt Resize(const TSize& aSizeInPixels);
	IMPORT_C TSize SizeInPixels() const;
	IMPORT_C TSize SizeInTwips() const;
	IMPORT_C void SetSizeInTwips(const MGraphicsDeviceMap* aMap);
	IMPORT_C void SetSizeInTwips(const TSize& aSizeInTwips);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void ExternalizeRectangleL(RWriteStream& aStream,const TRect& aRect) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C TInt Compress();
	IMPORT_C TInt VerticalPixelsToTwips(TInt aPixels) const;
	IMPORT_C TInt VerticalTwipsToPixels(TInt aTwips) const;
	IMPORT_C static TBool IsFileInRom(const TDesC& aFilename,TUint32*& aWord);
	IMPORT_C TBool IsMonochrome() const;
	IMPORT_C TBool IsLargeBitmap() const;
	IMPORT_C void PaletteAttributes(TBool& aModifiable,TInt& aNumEntries) const;
	IMPORT_C void SetPalette(CPalette* aPalette);
	IMPORT_C TInt GetPalette(CPalette*& aPalette) const;
	IMPORT_C TUint32* DataAddress() const;
	IMPORT_C TBool IsCompressedInRAM() const;
protected:
	IMPORT_C void LockHeap(TBool aAlways=EFalse) const;
	IMPORT_C void UnlockHeap(TBool aAlways=EFalse) const;
	IMPORT_C void LockHeapLC(TBool aAlways=EFalse) const;
	IMPORT_C static void UnlockHeap(TAny* aFbsBitmap);
protected:
    IMPORT_C void GetScanLine(TDes8& aBuf,const TPoint& aPixel,TInt aLength,const TPoint& aDitherOffset,TDisplayMode aDispMode) const;
	CBitwiseBitmap* Address() const;
	void DoSaveL(RFile& aFile);
	TInt DoCreate(const TSize& aSizeInPixels,TDisplayMode aDispMode,TUid aCreatorUid);
	TUint32* GetDataAddress() const;
protected:
	RFbsSession* iFbs;
	CBitwiseBitmap* iAddressPointer;
	CBitwiseBitmap* iRomPointer;
	TInt iHandle;
	TInt iServerHandle;
	};

class CDirectFileStore;
class CFbsBitmapAsyncStreamer : public CBase
	{
public:
	enum TMode {ELoad, ESave};
public:
	IMPORT_C ~CFbsBitmapAsyncStreamer();
	IMPORT_C static CFbsBitmapAsyncStreamer* NewL(TMode aMode);
	IMPORT_C TInt Load(const TDesC& aFilename,TInt32 aId,TInt& aScanLines);
	IMPORT_C TBool LoadScanLinesL(TInt aNumberOfScanLines,CFbsBitmap*& aBitmap);
	IMPORT_C TInt Save(const TDesC& aFilename,CFbsBitmap* aBitmap,TInt32& aId,TInt& aScanLines);
	IMPORT_C TBool SaveScanLinesL(TInt aNumberOfScanLines);
private:
	CFbsBitmapAsyncStreamer(TMode aMode);
	void ConstructL();
	void DoLoadL(const TDesC& aFilename,TInt32 aId);
	void DoSaveL(RFile& aFile);
private:
	RFbsSession* iFbs;
	RStoreReadStream iReadStream;
	RStoreWriteStream iWriteStream;
	TStreamId iId;
	CDirectFileStore* iStore;
	TInt iCurrentScanLine;
	TUint32* iScanLineBase;
	CFbsBitmap* iBitmap;
	SEpocBitmapHeader iHeader;
	TDisplayMode iDispMode;
	TMode iMode;
	};

class TBitmapUtil
	{
public:
	IMPORT_C void Begin(const TPoint& aPosition);
	IMPORT_C void Begin(const TPoint& aPosition,const TBitmapUtil& aUtil);
	IMPORT_C void End();
	IMPORT_C TBitmapUtil(CFbsBitmap* aBitmap);
	IMPORT_C TUint32 GetPixel() const;
	IMPORT_C void SetPixel(TUint32 aValue);
	IMPORT_C void SetPixel(const TBitmapUtil& aSource);
	IMPORT_C void SetPos(const TPoint& aPosition);
	IMPORT_C void DecXPos();
	IMPORT_C void DecYPos();
	IMPORT_C void IncXPos();
	IMPORT_C void IncYPos();
private:
	CFbsBitmap* iFbsBitmap;
	TUint32* iWordPos;
	TUint32* iMinWordPos;
	TUint32* iMaxWordPos;
	TInt iBpp;
	TInt iPixelShift;
	TInt iBitShift;
	TUint32 iMask;
	TInt iScanlineWordLength;
	TBool iHeapLocked;
	};

class TFontInfo;
class CFbsTypefaceStore : public CTypefaceStore
	{
public:
	IMPORT_C static CFbsTypefaceStore* NewL(CGraphicsDevice* aDevice);
	IMPORT_C ~CFbsTypefaceStore();
	IMPORT_C TInt AddFile(const TDesC& aName,TInt& aId);
	IMPORT_C TInt InstallFile(const TDesC& aName,TInt& aId);
	IMPORT_C void RemoveFile(TInt aId=0);
	IMPORT_C virtual TInt GetNearestFontInTwips(CFont*& aFont,const TFontSpec& aFontSpec);
	IMPORT_C TInt GetNearestFontInPixels(CFont*& aFont,const TFontSpec& aFontSpec);
 	IMPORT_C TInt GetFontById(CFont *&aFont,TUid aUid,const TAlgStyle& aAlgStyle);
	IMPORT_C virtual TInt NumTypefaces() const;
	IMPORT_C virtual void TypefaceSupport(TTypefaceSupport& aTypefaceSupport,TInt aTypefaceIndex) const;
	IMPORT_C virtual TInt FontHeightInTwips(TInt aTypefaceIndex,TInt aHeightIndex) const;
	IMPORT_C TInt FontHeightInPixels(TInt aTypefaceIndex,TInt aHeightIndex) const;
	IMPORT_C static void RemoveFontFileLocksL(); // Unload all fonts loaded from RAM or removable media
private:
	CFbsTypefaceStore(CGraphicsDevice* aDevice);
	TInt CreateFont(CFont*& aFont,const TFontInfo& aFontInfo);
	TInt FontHeight(TInt aTypefaceIndex,TInt aHeightIndex,TInt aMessage) const;
	void SetSize() const;
private:
	RFbsSession* iFbs;
	CGraphicsDevice* iDevice;
	CFontCache* iTwipsCache;
	};

class CDitherColor256;
class CFbsColor256BitmapUtil : public CBase
	{
public:
	enum TDither {ENoDither, EFloydSteinberg};
public:
	IMPORT_C static CFbsColor256BitmapUtil* NewL(const CPalette* aPalette);
	IMPORT_C TInt CopyBitmap(CFbsBitmap* aColor256Destination,CFbsBitmap* aSource,TDither aDither=ENoDither);
	~CFbsColor256BitmapUtil();
private:
	CFbsColor256BitmapUtil();
private:
	TColor256Util* iColor256Util;
	CDitherColor256* iDither;
	};

#endif
