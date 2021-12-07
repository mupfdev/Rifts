/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __BITMAPMETHODS__
#define __BITMAPMETHODS__

#define KColourDepth EColor4K

//Ensure these libraries are linked against:
//LIBRARY           bitgdi.lib


#include <e32base.h>
#include <gdi.h>

class CFbsBitGc;
class CFbsBitmapDevice;
class CWsBitmap;
class CFbsBitmap;


/*! 
  @namespace NBitmapMethods
  
  @discussion A set of functions to make bitmap manipulation easier
  */
namespace NBitmapMethods
{
/*!
  @function CreateGraphicsContextLC
  
  @discussion Create a graphics context and leave it on the cleanup stack
  @param aBitmapDevice a reference to a bitmap device
  */
	CFbsBitGc* CreateGraphicsContextLC(CFbsBitmapDevice& aBitmapDevice);

/*!
  @function CreateGraphicsContextL
  
  @discussion Create a graphics context
  @param aBitmapDevice a reference to a bitmap device
  */
	CFbsBitGc* CreateGraphicsContextL(CFbsBitmapDevice& aBitmapDevice);

/*!
  @function CreateBitmapDeviceLC
  
  @discussion Create a bitmap device and leave it on the cleanup stack
  @param aBitmap a reference to a bitmap
  */
	CFbsBitmapDevice* CreateBitmapDeviceLC(CFbsBitmap& aBitmap);

/*!
  @function CreateBitmapDeviceL
  
  @discussion Create a bitmap device
  @param aBitmap a reference to a bitmap
  */
	CFbsBitmapDevice* CreateBitmapDeviceL(CFbsBitmap& aBitmap);

/*!
  @function CreateBitmapLC
  
  @discussion Create a bitmap and leave it on the cleanup stack
  @param aSizeInPixels the size of the bitmap to be created
  @param aDispMode the display mode of the bitmap
  */
	CFbsBitmap* CreateBitmapLC(TSize aSizeInPixels,TDisplayMode aDispMode);

/*!
  @function CreateBitmapL
  
  @discussion Create a bitmap
  @param aSizeInPixels the size of the bitmap to be created
  @param aDispMode the display mode of the bitmap
  */
	CFbsBitmap* CreateBitmapL(TSize aSizeInPixels,TDisplayMode aDispMode);

/*!
  @function CreateBitmapLC
  
  @discussion Create a bitmap from an mbm file bitmap and leave it on the cleanup stack
  @param aFileName the name of an mbm file
  @param aId the position of the bitmap in the mbm file
  */
	CFbsBitmap* CreateBitmapLC(const TDesC& aFileName,TInt aId);

/*!
  @function CreateBitmapLC
  
  @discussion Create a bitmap from an mbm file bitmap
  @param aFileName the name of an mbm file
  @param aId the position of the bitmap in the mbm file
  */
	CFbsBitmap* CreateBitmapL(const TDesC& aFileName,TInt aId);

/*!
  @function BitBltMaskedEntireBitmap
  
  @discussion Blit the entire of a bitmap with a mask onto a gc
  @param aTargetGc gc to blit onto
  @param aTopLeft the position at which the top left of the bitmap will be placed on the gc
  @param aBitmap the bitmap to blit
  @param aBitMask the mask
  */
	void BitBltMaskedEntireBitmap(CFbsBitGc& aTargetGc,TPoint aTopLeft,const CFbsBitmap& aBitmap,
								const CFbsBitmap& aBitMask);
/*!
  @function PartialReset
  
  @discussion Reset a gc so that it is in a sensible state.
  Not all settings are reset, just some of the more useful ones
  @param aGc the gc to reset
  */
	void PartialReset(CFbsBitGc& aGc);
}

#endif //__BITMAPMETHODS__
