// TXTFMLYR.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


inline CParaFormatLayer* CParaFormatLayer::CloneL()const
	{return STATIC_CAST(CParaFormatLayer*,DoCloneL());}


inline CCharFormatLayer* CCharFormatLayer::CloneL()const
	{return STATIC_CAST(CCharFormatLayer*,DoCloneL());}
