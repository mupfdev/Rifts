// BITDEV.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

TInt CFbsDevice::CreateContext(CGraphicsContext*& aGc)
	{return(CreateContext((CFbsBitGc*&)aGc));} // relies on CFbsDevice deriving _only_ from CBitmapDevice

TInt CFbsDevice::GetNearestFontInTwips(CFbsFont*& aFont,const TFontSpec& aFontSpec)
	{return(GetNearestFontInTwips((CFont*&)aFont,aFontSpec));} // relies on CFbsFont deriving _only_ from CFont

TInt CFbsDevice::GetNearestFontInPixels(CFbsFont*& aFont,const TFontSpec& aFontSpec)
	{return(GetNearestFontInPixels((CFont*&)aFont,aFontSpec));} // relies on CFbsFont deriving _only_ from CFont

TInt CFbsDevice::GetFontById(CFbsFont*& aFont,TUid aFileId,const TAlgStyle& aStyle)
	{return(GetFontById((CFont*&)aFont,aFileId,aStyle));} // relies on CFbsFont deriving _only_ from CFont

