// TXTSTYLE.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

RParagraphStyleInfo::RParagraphStyleInfo()
	: iStyle(NULL),iStyleForNextPara(NULL)
	{}

RParagraphStyleInfo::RParagraphStyleInfo(CParagraphStyle* aStyle,CParagraphStyle* aStyleForNextPara)
	: iStyle(aStyle),iStyleForNextPara(aStyleForNextPara)
	{}

void RParagraphStyleInfo::Discard()
	{delete iStyle;}


CCharFormatLayer* CParagraphStyle::CharFormatLayer()const
	{return iCharFormatLayer;}

TInt CParagraphStyle::OutlineLevel()const
	{return iOutlineLevel;}


void CParagraphStyle::SetOutlineLevel(TInt aOutlineLevel)
	{iOutlineLevel=aOutlineLevel;}


void CParagraphStyle::SetType(TUid aType)
	{iType=aType;}


CParagraphStyle* CParagraphStyle::CloneL()const
	{return STATIC_CAST(CParagraphStyle*,DoCloneL());}


const RParagraphStyleInfo& CStyleList::operator[](TInt aIndex)const
	{return iList->At(aIndex);}


RParagraphStyleInfo& CStyleList::operator[](TInt aIndex)
	{return iList->At(aIndex);}

TInt CStyleList::Count()const
	{return (iList) ? iList->Count() : 0;}
