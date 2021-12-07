// Mda\Common\Video.h
//
// Copyright (c) 1998-2001 Symbian Ltd.  All rights reserved.
//

#ifndef __MDA_COMMON_VIDEO_H__
#define __MDA_COMMON_VIDEO_H__

#include <gdi.h>
#include <Mda\Common\Controller.h>
#include <Mda\Common\Resource.h>
#include <Mda\Common\Video.hrh>

// Video data type Uid

MDA_UID(KUidMdaMediaTypeVideo)
MDA_UID(KUidMdaVideoFrameSettings);
MDA_UID(KUidMdaVideoCurrentFrame);
MDA_UID(KUidMdaDstPortSourceRect);
MDA_UID(KUidMdaMbmClipFormat);
MDA_UID(KUidMdaMbmCodec);
MDA_UID(KUidMdaBmpClipFormat);
MDA_UID(KUidMdaBmpCodec);
MDA_UID(KUidMda1BppBmpCodec);
MDA_UID(KUidMda4BppBmpCodec);
MDA_UID(KUidMda8BppBmpCodec);
MDA_UID(KUidMda24BppBmpCodec);
MDA_UID(KUidMdaFbsBitmapDevice);
MDA_UID(KUidMdaFbsBitmapHandle);
MDA_UID(KUidMdaFbsBitmapMaskHandle);
MDA_UID(KUidMdaJfifClipFormat);
MDA_UID(KUidMdaJpgCodec);
MDA_UID(KUidMdaJpgQTable);
MDA_UID(KUidMdaJpgComment);
MDA_UID(KUidMdaWbmpClipFormat);
MDA_UID(KUidMdaWbmpCodec);
MDA_UID(KUidMdaOtaClipFormat);
MDA_UID(KUidMdaOtaCodec);
MDA_UID(KUidMdaPngClipFormat);
MDA_UID(KUidMdaPngCodec);
MDA_UID(KUidMdaWmfClipFormat);
MDA_UID(KUidMdaWmfApmClipFormat);
MDA_UID(KUidMdaWmfClpClipFormat);
MDA_UID(KUidMdaWmfCodec);
MDA_UID(KUidMdaTiffLittleEndianClipFormat);
MDA_UID(KUidMdaTiffBigEndianClipFormat);
MDA_UID(KUidMdaTiffCodec);

// Video buffer settings

enum TMdaVideoBufferSettings
	{
	// May be combined
	EMdaVideoBufferAtPlay =		0x0000000, // Can only handle buffers whilst playing
	EMdaVideoBufferAtPrime =	0x0000001, // Can handle buffers when primed
	EMdaVideoBufferDouble =		0x0000002, // Must have two buffers for uninterrupted play
	EMdaVideoBufferSupply =		0x0000004  // Will supply buffers for efficiency
	};

// Generic Video Parameters

class TMdaVideoDataSettings : public TMdaDatatypeSettings
	{
public:
	inline TMdaVideoDataSettings();
public:
	TSize iFrameSizeInPixels;
	TSize iFrameSizeInTwips;
	TDisplayMode iFrameDisplayMode;
	TTimeIntervalMicroSeconds iFrameDelay;
	TInt iNumberOfFrames;
	TBool iVariableSize;
	TBool iVariableDisplayMode;
	TBool iVariableDelay;
	};

// Specific frame Parameters

class TMdaVideoFrameSettings : public TMdaDatatypeSettings
	{
public:
	inline TMdaVideoFrameSettings();
public:
	enum TMdaVideoFrameSettingsFlags
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
	TRect iCoords;
	TSize iSizeInTwips;
	TInt iBitsPerPixel;
	TTimeIntervalMicroSeconds iDelay;
	TUint32 iFlags;
	};

// Current frame number

class TMdaVideoCurrentFrame : public TMdaDatatypeSettings
	{
public:
	inline TMdaVideoCurrentFrame();
public:
	TInt iFrameNumber;
	};

// Source rect for destination ports

class TMdaDstPortSourceRect : public TMdaDatatypeSettings
	{
public:
	inline TMdaDstPortSourceRect();
public:
	TRect iSourceRect;
	};

// Bmp Clip Format

class TMdaBmpClipFormat : public TMdaClipFormat
	{
public:
	inline TMdaBmpClipFormat();
	};

// 1 Bpp Bmp Codec

class TMda1BppBmpCodec : public TMdaPackage
	{
public:
	inline TMda1BppBmpCodec();
	};

// 4 Bpp Bmp Codec

class TMda4BppBmpCodec : public TMdaPackage
	{
public:
	inline TMda4BppBmpCodec();
	};

// 8 Bpp Bmp Codec

class TMda8BppBmpCodec : public TMdaPackage
	{
public:
	inline TMda8BppBmpCodec();
	};

// 24 Bpp Bmp Codec

class TMda24BppBmpCodec : public TMdaPackage
	{
public:
	inline TMda24BppBmpCodec();
	};

// Jpeg settings

class TMdaJpgSettings
	{
public:
	inline TMdaJpgSettings(); // Defaults to EColor420 and 50
public:
	enum TColorSampling
		{
		EMonochrome,
		EColor420,
		EColor422,
		EColor444
		};
public:
	TColorSampling iSampleScheme;
	TInt iQualityFactor; // 0 to 100 inclusive
	};

// Jfif Clip Format

class TMdaJfifClipFormat : public TMdaClipFormat
	{
public:
	inline TMdaJfifClipFormat();
public:
	TMdaJpgSettings iSettings;
	};

// Jpeg Quantization table - in direct format

const TInt KJpgQTableEntries = 64;
class TMdaJpgQTable : public TMdaPackage
	{
public:
	inline TMdaJpgQTable();
public:
	enum TQTableIndex { ELumaTable = 0, EChromaTable = 1 };
public:
	TInt iTableIndex;
	TBuf8<KJpgQTableEntries> iEntries;
	};

// Jpeg comment

const TInt KJpgCommentBufferSize = 256;
class TMdaJpgComment : public TMdaPackage
	{
public:
	inline TMdaJpgComment();
public:
	TInt iCommentIndex; // Comment block to set/query
	TInt iCommentBufferIndex; // Index of KJpgCommentBufferSize block within comment to set/query
	TInt iTotalCommentLength; // Total size of comment being queried
	TBuf8<KJpgCommentBufferSize> iComment; // Comment to set/query
	};

// Mbm Clip Format

class TMdaMbmClipFormat : public TMdaClipFormat
	{
public:
	inline TMdaMbmClipFormat();
public:
	TDisplayMode iDisplayMode;
	};

// Wbmp Clip Format

class TMdaWbmpClipFormat : public TMdaClipFormat
	{
public:
	inline TMdaWbmpClipFormat();
	};

// Wbmp Codec

class TMdaWbmpCodec : public TMdaPackage
	{
public:
	inline TMdaWbmpCodec();
	};

// Ota Clip Format

class TMdaOtaClipFormat : public TMdaClipFormat
	{
public:
	inline TMdaOtaClipFormat();
	};

// Ota Codec

class TMdaOtaCodec : public TMdaPackage
	{
public:
	inline TMdaOtaCodec();
	};

// Png Clip Format

class TMdaPngClipFormat : public TMdaClipFormat
	{
public:
	inline TMdaPngClipFormat();
	};

// Png Codec

class TMdaPngCodec : public TMdaPackage
	{
public:
	inline TMdaPngCodec();
	};

// Wmf Clip Format

class TMdaWmfClipFormat : public TMdaClipFormat
	{
public:
	inline TMdaWmfClipFormat();
	};

// Wmf Apm Clip Format

class TMdaWmfApmClipFormat : public TMdaClipFormat
	{
public:
	inline TMdaWmfApmClipFormat();
	};

// Wmf Clp Clip Format

class TMdaWmfClpClipFormat : public TMdaClipFormat
	{
public:
	inline TMdaWmfClpClipFormat();
	};

// Wmf Codec

class TMdaWmfCodec : public TMdaPackage
	{
public:
	inline TMdaWmfCodec();
	};

#include <Mda\Common\Video.inl>

#endif

