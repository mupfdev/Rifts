// Mda\Server\AudioFilter.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// *********** All classes Internal to Symbian *************//

#ifndef __MDA_SERVER_AUDIOFILTER_H__
#define __MDA_SERVER_AUDIOFILTER_H__

#ifndef __E32BASE_H__
#include <e32base.h>
#endif

const TInt KMdaAudioFIRFilterDefaultVolume	= 1024;
const TInt KMdaAudioFIRFilterMaxRawFilter	= 128;
const TInt KMdaAudioFIRFilterDefaultRate	= 8000;
const TInt KMdaAudioFIRFilterMaxCoef		= 15;	// needs to be odd

// Internal to Symbian
class CMdaAudioFIRFilter : public CBase
	{
public:
	CMdaAudioFIRFilter();
	virtual ~CMdaAudioFIRFilter();
	//
	TInt Filter(TInt aValue);
	void Reset();
	void SetVolume(TInt aVol);
	void SetRates(TInt aHighRate, TInt aLowRate);
protected:
	void CalcRawCoef();
	void CalcVolCoef();
public:
	TInt iCoefCount;
	TInt iVolume;
	TInt iHighRate;
	TInt iLowRate;
protected:
	TInt iRawCoef[KMdaAudioFIRFilterMaxCoef];	// fractional coef
	TInt iVolCoef[KMdaAudioFIRFilterMaxCoef];	// volume multiplied coefs
	TInt iData[KMdaAudioFIRFilterMaxCoef];
	TInt iDataPos;
	};

#endif
