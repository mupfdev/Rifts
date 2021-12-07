// GDI.INL
//
// Copyright (c) 1998-1999 Symbian Ltd.  All rights reserved.
//

// TRgb

inline TRgb::TRgb():
	iValue(0x00ffffff)
	{}

inline TRgb::TRgb(TUint32 aValue):
	iValue(aValue)
	{}

inline TRgb::TRgb(TInt aRed,TInt aGreen,TInt aBlue):
	iValue(aRed|aGreen<<8|aBlue<<16)
	{}

inline TInt TRgb::Red() const
	{return(iValue&0xff);}

inline TInt TRgb::Green() const
	{return((iValue&0xff00)>>8);}

inline TInt TRgb::Blue() const
	{return((iValue&0xff0000)>>16);}

inline TBool TRgb::operator==(const TRgb& aColor) const
	{return(iValue==aColor.iValue);}

inline TBool TRgb::operator!=(const TRgb& aColor) const
	{return(!(*this==aColor));}

inline TRgb& TRgb::operator&=(const TRgb& aColor)
	{iValue&=aColor.iValue;return(*this);}

inline TRgb& TRgb::operator|=(const TRgb& aColor)
	{iValue|=aColor.iValue;return(*this);}

inline TRgb& TRgb::operator^=(const TRgb& aColor)
	{iValue^=aColor.iValue;return(*this);}

inline TUint32 TRgb::Value() const
	{return(iValue);}

inline TRgb TRgb::operator~() const
	{return(TRgb(iValue^0x00ffffff));}

inline TRgb TRgb::operator&(const TRgb& aColor)
	{return(TRgb(iValue&aColor.iValue));}

inline TRgb TRgb::operator|(const TRgb& aColor)
	{return(TRgb(iValue|aColor.iValue));}

inline TRgb TRgb::operator^(const TRgb& aColor)
	{return(TRgb(iValue^aColor.iValue));}

// CPalette

inline TInt CPalette::Entries() const
	{return(iNumEntries);}

// TColor256Utils
inline TRgb TColor256Util::Color256(TInt aColor256) const
	{ return TRgb(iColorTable[aColor256]); }

// TFontStyle

inline TBool TFontStyle::operator==(const TFontStyle& aFontStyle) const
	{return(iFlags==aFontStyle.iFlags);}

// CBitmapDevice

inline TInt CBitmapDevice::CreateBitmapContext(CBitmapContext*& aGC)
	{return(CreateContext((CGraphicsContext*&)aGC));} // relies on CBitmapContext deriving _only_ from CGraphicsContext

// TPictureCapability

inline TPictureCapability::TPictureCapability(TScalingType aScalingType,TBool aCroppable):
	iScalingType(aScalingType),iIsCroppable(aCroppable)
	{}

// TZoomFactor

inline TZoomFactor::TZoomFactor(const MGraphicsDeviceMap* aDevice):
	iZoomFactor(TZoomFactor::EZoomOneToOne),
	iDevice(aDevice)
	{}

inline void TZoomFactor::SetGraphicsDeviceMap(const MGraphicsDeviceMap* aDevice)
	{iDevice=aDevice;}

inline const MGraphicsDeviceMap* TZoomFactor::GraphicsDeviceMap() const
	{return(iDevice);}
