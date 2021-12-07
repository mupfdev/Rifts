// Mda\Server\AudioRateConverter.h
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

// *********** All classes Internal to Symbian *************//

#ifndef __MDA_SERVER_AUDIORATECONVERTER_H__
#define __MDA_SERVER_AUDIORATECONVERTER_H__

#include <Mda\Server\AudioFilter.h>

// Internal to Symbian
class CMdaAudioChannelRateConverter : public CBase
	{
public:
	virtual TInt Convert(TInt16* aSrc, TInt16* aDst, TInt aSamples)=0;
	virtual void Reset() {};
	void SetRates(TInt aSrcRate,TInt aSrcChannels,TInt aDstRate,TInt aDstChannels);
public:
	TInt iFromRate;
	TInt iToRate;
	TInt iFromChannels;
	TInt iToChannels;
protected:
	TReal iRatio;
	TInt iFraction;
	TInt iIndex;
	};

// Internal to Symbian
class CMdaStereoToMonoRateConverter : public CMdaAudioChannelRateConverter
	{
	public:
		virtual TInt Convert(TInt16* aSrc, TInt16* aDst, TInt aSamples);
	};

// Internal to Symbian
class CMdaStereoToMonoConverter : public CMdaAudioChannelRateConverter
	{
	public:
		virtual TInt Convert(TInt16* aSrc, TInt16* aDst, TInt aSamples);
	};

// Internal to Symbian
class CMdaStereoToStereoRateConverter : public CMdaAudioChannelRateConverter
	{
	public:
		virtual TInt Convert(TInt16* aSrc, TInt16* aDst, TInt aSamples);
	};
// Internal to Symbian
class CMdaMonoToMonoRateConverter : public CMdaAudioChannelRateConverter
	{
	public:
		virtual TInt Convert(TInt16* aSrc, TInt16* aDst, TInt aSamples);
	};
// Internal to Symbian
class CMdaMonoToStereoConverter : public CMdaAudioChannelRateConverter
	{
	public:
		virtual TInt Convert(TInt16* aSrc, TInt16* aDst, TInt aSamples);
	};
// Internal to Symbian
class CMdaMonoToStereoRateConverter : public CMdaAudioChannelRateConverter
	{
	public:
		virtual TInt Convert(TInt16* aSrc, TInt16* aDst, TInt aSamples);
	};

// Internal to Symbian
class CMdaAudioChannelRateConverterFactory : public CBase
	{
public:
	CMdaAudioChannelRateConverter* CreateCodecL(TInt aFromRate,TInt aFromChannels,
												 TInt aToRate,TInt aToChannels);
	CMdaAudioChannelRateConverter* CreateCodecL();
	CMdaAudioChannelRateConverter* Codec() {return iCodec;}
	~CMdaAudioChannelRateConverterFactory();
	TBool Match(TMdaAudioDataSettings& aSrcSettings, TMdaAudioDataSettings& aDstSettings);
	TInt Rate() {return iToRate;}
	TInt Channels() {return iToChannels;}
public:
	TInt iFromRate;
	TInt iToRate;
	TInt iFromChannels;
	TInt iToChannels;
private:
	CMdaAudioChannelRateConverter* iCodec;
	};
#endif
