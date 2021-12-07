// TXTFRMAT.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


TBool TTabStop::operator!=(const TTabStop& aTabStop)const
	{return !(*this==aTabStop);}

TBool TParaBorder::operator!=(const TParaBorder& aParaBorder)const
	{return !(*this==aParaBorder);}

TBool TBullet::operator!=(const TBullet& aBullet)const
	{return !(*this==aBullet);}

void CParaFormat::RemoveAllTabs()
	{
	if (iTabList)
		{
		delete iTabList;
		iTabList = NULL;
		}
	}

TInt CParaFormat::TabCount()const
	{return (iTabList)?iTabList->Count():0;}

TParaFormatMask::TParaFormatMask()
// Constructor.  Clears all guard bits.
//
	:iGuard(0)
	{}

void TParaFormatMask::SetAttrib(TTextFormatAttribute aAttribute)
	{iGuard|=(1<<aAttribute);}

void TParaFormatMask::ClearAttrib(TTextFormatAttribute aAttribute)
	{iGuard&=~(1<<aAttribute);}

TBool TParaFormatMask::AttribIsSet(TTextFormatAttribute aAttribute)const
	{return (iGuard&(1<<aAttribute));}

TBool TParaFormatMask::IsNull()const
// Returns ETrue if the mask has not been set.
//
	{return !iGuard;}

TBool TParaFormatMask::operator!=(const TParaFormatMask& aMask)const
	{return !(*this==aMask);}

TCharFormatMask::TCharFormatMask()
// Constructor.  Clears all guard bits.
//
	:iGuard(0)
	{}

void TCharFormatMask::SetAttrib(TTextFormatAttribute aAttribute)
	{iGuard|=(1<<((aAttribute-KMaxParaAttributes)-1));}

void TCharFormatMask::ClearAttrib(TTextFormatAttribute aAttribute)
	{iGuard&=~(1<<((aAttribute-KMaxParaAttributes)-1));}

TBool TCharFormatMask::AttribIsSet(TTextFormatAttribute aAttribute)const
	{return iGuard&(1<<((aAttribute-KMaxParaAttributes)-1));}

TBool TCharFormatMask::IsNull()const
	{return !iGuard;}

TBool TCharFormatMask::operator!=(const TCharFormatMask& aMask)const
	{return !(*this==aMask);}


