// TXTRICH.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


const TUint32 KStyleListExternallyOwned=0x01;
const TUint32 KParaTypeIsSingle=0x02;

TBool CRichText::StyleListPresent()const
	{return iStyleList.IsPtr() && iStyleList.AsPtr();}


CStyleList* CRichText::StyleList()const
	{return (StyleListPresent()) ? iStyleList.AsPtr() : NULL;}


TInt CRichText::StyleCount()const
	{return (StyleListPresent()) ? iStyleList->Count():0;}


void CRichText::SetStyleListExternallyOwned(TBool aBool)
	{
	if (aBool) iFlags|=KStyleListExternallyOwned;
	else iFlags&=~KStyleListExternallyOwned;
	}


TBool CRichText::StyleListExternallyOwned()const
	{return iFlags&KStyleListExternallyOwned;}


void CRichText::NotifyStyleDeletedL(const CParagraphStyle* aStyle)
	{NotifyStyleChangedL(NULL,aStyle);}


MRichTextStoreResolver* CRichText::StoreResolver()const
	{return iStoreResolver;}


MPictureFactory* CRichText::PictureFactory()const
	{return iPictureFactory;}


