// PPPCFG.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
#if !defined(__PPPCONFIG_H__)
#define __PPPCONFIG_H__

#include <e32base.h>

_LIT(PPP_COMPRESSORS, "Compressors");

//
// Compressor Configuration
//
class CPppCompConfig : public CBase
	{
public:
friend class CPppCcp;
	CPppCompConfig();
	~CPppCompConfig();
	static CPppCompConfig* NewL();
	void	AddNameL(TPtrC aName);
	void	AddOptionsL(TPtrC aOptions);
	void	AddID(TUint8 aID);
	TPtrC8	Options();
	TInt	OptionsLength();
	TPtrC	Name();
	TUint8	ID();
private:
	TSglQueLink link;
	HBufC*	iName;
	TUint8	iID;
	HBufC8*	iOptions;
	};

#endif // __PPPCONFIG_H__
