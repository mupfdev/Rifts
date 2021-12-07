// Mda\Common\Video.inl
// Copyright (c) 1998 Symbian Ltd
//

inline TMdaVideoDataSettings::TMdaVideoDataSettings():
	TMdaDatatypeSettings(KUidMdaMediaTypeVideo,sizeof(TMdaVideoDataSettings)),
	iFrameSizeInPixels(0,0),
	iFrameSizeInTwips(0,0),
	iFrameDisplayMode(ENone),
	iFrameDelay(0),
	iNumberOfFrames(0),
	iVariableSize(EFalse),
	iVariableDisplayMode(EFalse),
	iVariableDelay(EFalse)
	{}

inline TMdaVideoFrameSettings::TMdaVideoFrameSettings():
	TMdaDatatypeSettings(KUidMdaVideoFrameSettings,sizeof(TMdaVideoFrameSettings)),
	iCoords(0,0,0,0),
	iSizeInTwips(0,0),
	iBitsPerPixel(0),
	iDelay(0),
	iFlags(0)
 	{}

inline TMdaVideoCurrentFrame::TMdaVideoCurrentFrame():
	TMdaDatatypeSettings(KUidMdaVideoCurrentFrame,sizeof(TMdaVideoCurrentFrame)),
	iFrameNumber(-1)
	{}

inline TMdaDstPortSourceRect::TMdaDstPortSourceRect():
	TMdaDatatypeSettings(KUidMdaDstPortSourceRect,sizeof(TMdaDstPortSourceRect))
	{}

inline TMdaBmpClipFormat::TMdaBmpClipFormat():
	TMdaClipFormat(KUidMdaBmpClipFormat,sizeof(TMdaBmpClipFormat))
	{}

inline TMda1BppBmpCodec::TMda1BppBmpCodec():
	TMdaPackage(KUidMdaBmpCodec,KUidMda1BppBmpCodec,sizeof(TMda1BppBmpCodec))
	{}

inline TMda4BppBmpCodec::TMda4BppBmpCodec():
	TMdaPackage(KUidMdaBmpCodec,KUidMda4BppBmpCodec,sizeof(TMda4BppBmpCodec))
	{}

inline TMda8BppBmpCodec::TMda8BppBmpCodec():
	TMdaPackage(KUidMdaBmpCodec,KUidMda8BppBmpCodec,sizeof(TMda8BppBmpCodec))
	{}

inline TMda24BppBmpCodec::TMda24BppBmpCodec():
	TMdaPackage(KUidMdaBmpCodec,KUidMda24BppBmpCodec,sizeof(TMda24BppBmpCodec))
	{}

inline TMdaJpgSettings::TMdaJpgSettings():
	iSampleScheme(EColor420),
	iQualityFactor(50)
	{}

inline TMdaJfifClipFormat::TMdaJfifClipFormat():
	TMdaClipFormat(KUidMdaJfifClipFormat,sizeof(TMdaJfifClipFormat)),
	iSettings()
	{}

inline TMdaJpgQTable::TMdaJpgQTable():
	TMdaPackage(KUidMdaJpgQTable,KUidMdaJpgQTable,sizeof(TMdaJpgQTable)),
	iTableIndex(ELumaTable),
	iEntries(KJpgQTableEntries)
	{}

inline TMdaJpgComment::TMdaJpgComment():
	TMdaPackage(KUidMdaJpgComment,KUidMdaJpgComment,sizeof(TMdaJpgComment)),
	iCommentIndex(0),
	iCommentBufferIndex(0)
	{}

inline TMdaMbmClipFormat::TMdaMbmClipFormat():
	TMdaClipFormat(KUidMdaMbmClipFormat,sizeof(TMdaMbmClipFormat))
	{}

inline TMdaWbmpClipFormat::TMdaWbmpClipFormat():
	TMdaClipFormat(KUidMdaWbmpClipFormat,sizeof(TMdaWbmpClipFormat))
	{}

inline TMdaWbmpCodec::TMdaWbmpCodec():
	TMdaPackage(KUidMdaWbmpCodec,KUidMdaWbmpCodec,sizeof(TMdaWbmpCodec))
	{}

inline TMdaOtaClipFormat::TMdaOtaClipFormat():
	TMdaClipFormat(KUidMdaOtaClipFormat,sizeof(TMdaOtaClipFormat))
	{}

inline TMdaOtaCodec::TMdaOtaCodec():
	TMdaPackage(KUidMdaOtaCodec,KUidMdaOtaCodec,sizeof(TMdaOtaCodec))
	{}

inline TMdaPngClipFormat::TMdaPngClipFormat():
	TMdaClipFormat(KUidMdaPngClipFormat,sizeof(TMdaPngClipFormat))
	{}

inline TMdaPngCodec::TMdaPngCodec():
	TMdaPackage(KUidMdaPngCodec,KUidMdaPngCodec,sizeof(TMdaPngCodec))
	{}

inline TMdaWmfClipFormat::TMdaWmfClipFormat():
	TMdaClipFormat(KUidMdaWmfClipFormat,sizeof(TMdaWmfClipFormat))
	{}

inline TMdaWmfApmClipFormat::TMdaWmfApmClipFormat():
	TMdaClipFormat(KUidMdaWmfApmClipFormat,sizeof(TMdaWmfApmClipFormat))
	{}

inline TMdaWmfClpClipFormat::TMdaWmfClpClipFormat():
	TMdaClipFormat(KUidMdaWmfClpClipFormat,sizeof(TMdaWmfClpClipFormat))
	{}

inline TMdaWmfCodec::TMdaWmfCodec():
	TMdaPackage(KUidMdaWmfCodec,KUidMdaWmfCodec,sizeof(TMdaWmfCodec))
	{}

