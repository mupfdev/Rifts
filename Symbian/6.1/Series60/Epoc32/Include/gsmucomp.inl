// GSMUCOMP.INL
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
// 



inline TGsmCompressionSettings::TGsmLanguage TGsmCompressionSettings::CurrentLanguageContext() const
	{
	return iCurrentLanguageContext;
	}

inline void TGsmCompressionSettings::SetCurrentLanguageContext(TGsmLanguage aLanguage)
	{
	iCurrentLanguageContext=aLanguage;
	}

