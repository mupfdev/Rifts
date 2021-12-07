// WNGMODEL.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

CRichText* CWordModel::Text()
	{return iText;}

CStyleList* CWordModel::StyleList()
	{return iStyleList;}

CPrintSetup* CWordModel::PrintSetup()
	{return iPrintSetup;}

CArrayFix<TInt>* CWordModel::PageTable()
	{return iPageTable;}

CStyleShortCutList* CWordModel::StyleShortCutList()
	{return iStyleShortCutList;}

TChar& CWordModel::NormalStyleShortCut()
	{return iNormalStyleShortCut;}