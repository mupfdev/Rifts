// Mda\Client\Video.inl
//
// Copyright (c) 1998-1999 Symbian Ltd.  All rights reserved.
//

inline TMdaFbsBitmapDevice::TMdaFbsBitmapDevice():
	TMdaStreamDevice(KUidMdaFbsBitmapDevice,sizeof(TMdaFbsBitmapDevice))
	{}

inline TMdaFbsBitmapHandle::TMdaFbsBitmapHandle():
	TMdaPackage(KUidMdaFbsBitmapDevice,KUidMdaFbsBitmapHandle,sizeof(TMdaFbsBitmapHandle)),
	iBitmapHandle(0)
	{}

inline TMdaFbsBitmapMaskHandle::TMdaFbsBitmapMaskHandle():
	TMdaPackage(KUidMdaFbsBitmapDevice,KUidMdaFbsBitmapMaskHandle,sizeof(TMdaFbsBitmapMaskHandle)),
	iBitmapHandle(0)
	{}

