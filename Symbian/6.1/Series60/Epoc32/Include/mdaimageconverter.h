// MdaImageConverter.h
//
// Copyright (c) 1998-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __MDAIMAGECONVERTER_H__
#define __MDAIMAGECONVERTER_H__

#ifndef __FBS_H__
#include <fbs.h>
#endif
#ifndef __BITDEV_H__
#include <bitdev.h>
#endif
#ifndef __MDA_CLIENT_UTILITY_H__
#include <Mda\Client\Utility.h>
#endif
#ifndef __MDA_CLIENT_RESOURCE_H__
#include <Mda\Client\Resource.h>
#endif
#ifndef __MDA_CLIENT_VIDEO_H__
#include <Mda\Client\Video.h>
#endif
#ifndef __MDA_COMMON_VIDEO_H__
#include <Mda\Common\Video.h>
#endif

class MMdaImageUtilObserver
	{
public:
	virtual void MiuoCreateComplete(TInt aError) = 0;
	virtual void MiuoOpenComplete(TInt aError) = 0;
	virtual void MiuoConvertComplete(TInt aError) = 0;
	};

class TFrameInfo
	{
public:
	enum TFrameInfoFlags
		{
		EColor					= 0x00000001, // Grayscale if not set
		ETransparencyPossible	= 0x00000002, // Fully opaque if not set
		EFullyScaleable			= 0x00000004, // Will only scale to 1/2,1/4 & 1/8th if not set
		EConstantAspectRatio	= 0x00000008, // Scaling need not maintain aspect ratio if not set
		ECanDither				= 0x00000010, // Will not use error diffusion if not set
		EAlphaChannel			= 0x00000020, // Set if the image contains alpha-blending information
		ELeaveInPlace			= 0x00000040, // }
		ERestoreToBackground	= 0x00000080, // } Mutually exclusive image disposal methods
		ERestoreToPrevious		= 0x00000100  // }
		};
public:
	TRect iFrameCoordsInPixels;
	TSize iFrameSizeInTwips;
	TInt iBitsPerPixel;
	TTimeIntervalMicroSeconds iDelay;
	TUint32 iFlags;
	TSize iOverallSizeInPixels;
	};

class CMdaImageUtility : public CMdaResource, public MMdaObjectStateChangeObserver
	{
public:
	virtual ~CMdaImageUtility();
	IMPORT_C virtual void Close();
	// Image conversion
	virtual void ConvertL(CFbsBitmap& aBitmap,TInt aFrameNumber = 0) = 0;
	virtual void ConvertL(CFbsBitmap& aBitmap,CFbsBitmap& aMaskBitmap,TInt aFrameNumber = 0) = 0;
	virtual void CancelConvertL() = 0;
	// Image information
	IMPORT_C virtual void FrameInfo(TInt aFrame,TFrameInfo& aInfo) const;
	IMPORT_C virtual TInt FrameCount() const;
public:
	// Reserved functions - do not call
	virtual void ImageUtil_Reserved1();
	virtual void ImageUtil_Reserved2();
	virtual void ImageUtil_Reserved3();
	virtual void ImageUtil_Reserved4();
protected:
	CMdaImageUtility(MMdaImageUtilObserver& aObserver);
	void SetServerL(CMdaServer* aServer);
	void CancelControllerOperation();
	virtual void DoClose();
	// From MMdaObjectStateChangeObserver
	virtual void MoscoStateChangeEvent(CBase* aObject,TInt aPreviousState,TInt aCurrentState,TInt aErrorCode);
protected:
	MMdaImageUtilObserver& iObserver;
	CMdaServer* iServer;
	TBool iOwnsServer;
	CMdaController* iController;
	TInt iMoscoState;
	TMdaFbsBitmapDevice iBitmapDevice;
	TMdaFbsBitmapHandle iBitmapHandle;
	TMdaFbsBitmapMaskHandle iMaskBitmapHandle;
	RArray<TMdaVideoFrameSettings> iFrameSettings;
	TMdaVideoFrameSettings iCurrentFrameSettings;
	TMdaVideoDataSettings iOverallSettings;
	};

class CMdaImageDataReadUtility : public CMdaImageUtility
	{
public:
	virtual ~CMdaImageDataReadUtility();
	// From CMdaImageUtility
	IMPORT_C virtual void ConvertL(CFbsBitmap& aBitmap,TInt aFrameNumber = 0);
	IMPORT_C virtual void ConvertL(CFbsBitmap& aBitmap,CFbsBitmap& aMaskBitmap,TInt aFrameNumber = 0);
	IMPORT_C virtual void CancelConvertL();
	// From CMdaResource
	virtual void RunL();
	virtual void DoCancel();
	virtual const RMdaSrcPort& MspSrcPort();
	virtual const RMdaDstPort& MdpDstPort();
public:
	// Reserved functions - do not call
	virtual void ImageReadUtil_Reserved1();
	virtual void ImageReadUtil_Reserved2();
	virtual void ImageReadUtil_Reserved3();
	virtual void ImageReadUtil_Reserved4();
protected:
	enum TUtilState
		{
		EClosed,
		EOpenSrcOpen,
		EOpenSrcConfig,
		EOpenSrcConfigFormat,
		EOpenSrcConfigCodec,
		EOpenSrcConfigExtra,
		EOpenDstOpen,
		EOpenDstConfig,
		EOpenControllerCreate,
		EOpenControllerPrepare,
		EOpenSrcPortConfigOverall,
		EOpenSrcPortConfigFrame,
		EOpen,
		EConvertSrcPortConfig,
		EConvertSrcPortConfigMask,
		EConvertDstConfig,
		EConvertControllerPrime,
		EConvertSrcPortConfigFrame,
		EConvertControllerPrepare,
		EConvertNextFrameInfo
		};
protected:
	CMdaImageDataReadUtility(MMdaImageUtilObserver& aObserver);
	void DoOpenL(TMdaClipFormat* aFormat,TMdaPackage* aCodec,TMdaPackage* aExtra);
	// From CMdaImageUtility
	virtual void DoClose();
protected:
	RMdaSourceClipPort iSrcPort;
	RMdaDestinationStreamPort iDstPort;
	TMdaClipLocation* iLocation;
	TMdaFileClipLocation iFile;
	TMdaDesClipLocation iDesc;
	TUtilState iState;
	TMdaClipFormat* iFormat;
	TMdaPackage* iCodec;
	TMdaPackage* iExtra;
	TMdaVideoCurrentFrame iFrame;
	};

class CMdaImageDataWriteUtility : public CMdaImageUtility
	{
public:
	virtual ~CMdaImageDataWriteUtility();
	// From CMdaImageUtility
	IMPORT_C virtual void ConvertL(CFbsBitmap& aBitmap,TInt aFrameNumber = 0);
	IMPORT_C virtual void ConvertL(CFbsBitmap& aBitmap,const TRect& aSourceRect,TInt aFrameNumber = 0);
	IMPORT_C virtual void ConvertL(CFbsBitmap& aBitmap,CFbsBitmap& aMaskBitmap,TInt aFrameNumber = 0);
	IMPORT_C virtual void CancelConvertL();
	// From CMdaResource
	virtual void RunL();
	virtual void DoCancel();
	virtual const RMdaSrcPort& MspSrcPort();
	virtual const RMdaDstPort& MdpDstPort();
public:
	// Reserved functions - do not call
	virtual void ImageWriteUtil_Reserved1();
	virtual void ImageWriteUtil_Reserved2();
	virtual void ImageWriteUtil_Reserved3();
	virtual void ImageWriteUtil_Reserved4();
protected:
	enum TUtilState
		{
		EClosed,
		ECreateSrcOpen,
		ECreateSrcConfig,
		ECreateDstOpen,
		ECreateDstConfig,
		ECreateDstConfigFormat,
		ECreateDstConfigCodec,
		ECreateDstConfigExtra,
		ECreateControllerCreate,
		ECreated,
		EConvertSrcPortConfig,
		EConvertSrcPortConfigMask,
		EConvertDstPortConfigSourceRect,
		EConvertDstConfigCrop,
		EConvertControllerPrime
		};
protected:
	CMdaImageDataWriteUtility(MMdaImageUtilObserver& aObserver);
	void DoCreateL(TMdaClipFormat* aFormat,TMdaPackage* aCodec,TMdaPackage* aExtra);
	// From CMdaImageUtility
	virtual void DoClose();
protected:
	RMdaSourceStreamPort iSrcPort;
	RMdaDestinationClipPort iDstPort;
	TMdaClipLocation* iLocation;
	TMdaFileClipLocation iFile;
	TMdaDesClipLocation iDesc;

	TMdaClipFormat* iFormat;
	TMdaPackage* iCodec;
	TMdaPackage* iExtra;
	TMdaDstPortSourceRect iSourceRectPackage;
	TMdaClipCrop iCrop;

	TUtilState iState;
	};

class CMdaImageFileToBitmapUtility : public CMdaImageDataReadUtility
	{
public:
	IMPORT_C static CMdaImageFileToBitmapUtility* NewL(MMdaImageUtilObserver& aObserver,CMdaServer* aServer = NULL);
	IMPORT_C void OpenL(const TDesC& aFileName,TMdaClipFormat* aFormat = NULL,TMdaPackage* aCodec = NULL,TMdaPackage* aExtra = NULL);
protected:
	CMdaImageFileToBitmapUtility(MMdaImageUtilObserver& aObserver);
	};

class CMdaImageDescToBitmapUtility : public CMdaImageDataReadUtility
	{
public:
	IMPORT_C static CMdaImageDescToBitmapUtility* NewL(MMdaImageUtilObserver& aObserver,CMdaServer* aServer = NULL);
	IMPORT_C void OpenL(const TDesC8& aDescriptor,TMdaClipFormat* aFormat = NULL,TMdaPackage* aCodec = NULL,TMdaPackage* aExtra = NULL);
protected:
	CMdaImageDescToBitmapUtility(MMdaImageUtilObserver& aObserver);
	};

class CMdaImageBitmapToFileUtility : public CMdaImageDataWriteUtility
	{
public:
	IMPORT_C static CMdaImageBitmapToFileUtility* NewL(MMdaImageUtilObserver& aObserver,CMdaServer* aServer = NULL);
	IMPORT_C void CreateL(const TDesC& aFileName,TMdaClipFormat* aFormat,TMdaPackage* aCodec,TMdaPackage* aExtra);
protected:
	CMdaImageBitmapToFileUtility(MMdaImageUtilObserver& aObserver);
	};

class CMdaImageBitmapToDescUtility : public CMdaImageDataWriteUtility
	{
public:
	IMPORT_C static CMdaImageBitmapToDescUtility* NewL(MMdaImageUtilObserver& aObserver,CMdaServer* aServer = NULL);
	IMPORT_C void CreateL(TDes8& aDescriptor,TMdaClipFormat* aFormat,TMdaPackage* aCodec,TMdaPackage* aExtra);
protected:
	CMdaImageBitmapToDescUtility(MMdaImageUtilObserver& aObserver);
	};

class CMdaImageBitmapToBitmapUtility : public CMdaImageUtility
	{
public:
	IMPORT_C static CMdaImageBitmapToBitmapUtility* NewL(MMdaImageUtilObserver& aObserver,CMdaServer* aServer = NULL);
	IMPORT_C ~CMdaImageBitmapToBitmapUtility();
	IMPORT_C void OpenL(CFbsBitmap& aBitmap);
	// From CMdaImageUtility
	IMPORT_C virtual void ConvertL(CFbsBitmap& aBitmap,TInt aFrameNumber = 0);
	IMPORT_C virtual void ConvertL(CFbsBitmap& aBitmap,CFbsBitmap& aMaskBitmap,TInt aFrameNumber = 0);
	IMPORT_C virtual void CancelConvertL();
	// From CMdaResource
	virtual void RunL();
	virtual void DoCancel();
	virtual const RMdaSrcPort& MspSrcPort();
	virtual const RMdaDstPort& MdpDstPort();
protected:
	enum TUtilState
		{
		EClosed,
		EReady,
		ESrcOpen,
		ESrcConfig,
		ESrcPortConfig,
		EDstOpen,
		EDstConfig,
		EDstPortConfig,
		EControllerCreate,
		EControllerPrime
		};
protected:
	CMdaImageBitmapToBitmapUtility(MMdaImageUtilObserver& aObserver);
	// From CMdaImageUtility
	virtual void DoClose();
protected:
	RMdaSourceStreamPort iSrcPort;
	RMdaDestinationStreamPort iDstPort;
	TMdaFbsBitmapHandle iDstBitmapHandle;
	TUtilState iState;
	};

class CMdaBitmapRotator : public CBase
	{
public:
	enum TRotationAngle
		{
		ERotation90DegreesClockwise,
		ERotation180DegreesClockwise,
		ERotation270DegreesClockwise
		};
public:
	IMPORT_C static CMdaBitmapRotator* NewL();
	IMPORT_C virtual ~CMdaBitmapRotator();
	IMPORT_C void RotateL(MMdaImageUtilObserver& aObserver,CFbsBitmap& aSrcBitmap,CFbsBitmap& aTgtBitmap,TRotationAngle aAngle);
	IMPORT_C void RotateL(MMdaImageUtilObserver& aObserver,CFbsBitmap& aBitmap,TRotationAngle aAngle);
	IMPORT_C void CancelRotation();
protected:	
	static TInt Rotate(TAny* aParam);
	TBool DoRotate();
	void FlipScanLine(TDes8& aDes, TInt aWidth);
	CMdaBitmapRotator();
	void ConstructL();
protected:
	MMdaImageUtilObserver* iObserver;
	TInt iCurOffset;
	TInt iRows;
	CIdle* iRotator;
	TRotationAngle iAngle;
	TSize iBitmapSize;
	TDisplayMode iDisplayMode;
	CFbsBitmap* iTempBitmap;		// For the Rotate() with only one bitmap supplied
	CFbsBitmap* iSrcBitmap;
	CFbsBitmap* iTgtBitmap;
	HBufC8* iScanlineBuffer;
	TPtr8 iScanlineDes;
	TInt iLinesPerCall;				// Number of lines being rotated at once
  	CFbsBitmapDevice* iDevice;
	CFbsBitGc* iGc;	
	CFbsBitmap* iScanlineBitmap;	// Intermediate scanline bitmap
	};

class CMdaBitmapScaler : public CBase
	{
public:
	IMPORT_C static CMdaBitmapScaler* NewL();
	IMPORT_C virtual ~CMdaBitmapScaler();
	IMPORT_C void ScaleL(MMdaImageUtilObserver& aObserver,CFbsBitmap& aSrcBitmap,CFbsBitmap& aTgtBitmap,TBool aMaintainAspectRatio = ETrue);
	IMPORT_C void ScaleL(MMdaImageUtilObserver& aObserver,CFbsBitmap& aBitmap,TSize aDestSize,TBool aMaintainAspectRatio = ETrue);
	IMPORT_C void CancelScaling();
protected:
	void CalcFilterTables(TInt aOrigWidth,TInt aDestWidth, TInt*& aFilterIndexTablePtr,
						  TInt*& aFilterCoeffsTablePtr );
	void ScaleLine(TDes8& aInDes,TDes8& aOutDes,TInt aStartIndex,TInt aInputWidth,
				   TInt aOutputWidth,TInt* aTableIndexPtr,TInt* aTableCoeffsPtr);
	static TInt Scale(TAny* aParam);
	TBool DoScale();
	CMdaBitmapScaler();
	void ConstructL();
protected:
	CFbsBitmap* iSrcBitmap;
	CFbsBitmap* iTgtBitmap;
	CFbsBitmap* iScaleBitmap;
	CFbsBitmap* iScanlineBitmap;
	CFbsBitmapDevice* iDevice;
	CFbsBitGc* iGc;
	TInt* iFilterIndexTable;
	TInt* iFilterIndexTablePtr;
	TInt iFilterIndexNum;
	TInt* iFilterCoeffsTable;
	TInt* iFilterCoeffsTablePtr;
	TInt iFilterCoeffsNum;
	TSize iOrigSize;
	TSize iDestSize;
	CFbsBitmap* iTempBitmap;
	HBufC8* iRBuffer;
	HBufC8* iBBuffer;
	HBufC8* iGBuffer;
	TPtr8 iRDes;
	TPtr8 iGDes;
	TPtr8 iBDes;
	HBufC8* iOrigBuffer;
	HBufC8* iDestBuffer;
	TPtr8 iOrigDes;
	TPtr8 iDestDes;
	CIdle* iScaler;
	MMdaImageUtilObserver* iObserver;
	TInt iLinesPerCall;
	TBool iVerticalScan;
	TInt iCurOffset;
	TInt iFinalOffset;
	TInt iCurLineSize;
	};

#endif

