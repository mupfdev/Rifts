// Mda\Server\AudioCodecs.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// *********** All classes Internal to Symbian *************//

#ifndef __MDA_SERVER_AUDIOCODECS_H__
#define __MDA_SERVER_AUDIOCODECS_H__

#include <Mda\Server\Base.h>
#include <Mda\Server\Environment.h>

// Base of Audio codecs

// Internal to Symbian
class TMdaAudioCodecBase
	{
public:
	inline TMdaAudioCodecBase();
	//
	virtual void Convert(TUint8* aSrc, TUint8* aDst, TInt aSamples)=0;
	};

// PCM Codecs
// Internal to Symbian

class TMdaAudioU8ToS16PcmCodec : public TMdaAudioCodecBase
	{ public: IMPORT_C virtual void Convert(TUint8* aSrc, TUint8* aDst, TInt aSamples); };
class TMdaAudioS8ToS16PcmCodec : public TMdaAudioCodecBase
	{ public: IMPORT_C virtual void Convert(TUint8* aSrc, TUint8* aDst, TInt aSamples); };
class TMdaAudioU16ToS16PcmCodec : public TMdaAudioCodecBase
	{ public: IMPORT_C virtual void Convert(TUint8* aSrc, TUint8* aDst, TInt aSamples); };
class TMdaAudioU16BEToS16PcmCodec : public TMdaAudioCodecBase
	{ public: IMPORT_C virtual void Convert(TUint8* aSrc, TUint8* aDst, TInt aSamples); };

class TMdaAudioS16ToU8PcmCodec : public TMdaAudioCodecBase
	{ public: IMPORT_C virtual void Convert(TUint8* aSrc, TUint8* aDst, TInt aSamples); };
class TMdaAudioS16ToS8PcmCodec : public TMdaAudioCodecBase
	{ public: IMPORT_C virtual void Convert(TUint8* aSrc, TUint8* aDst, TInt aSamples); };
class TMdaAudioS16ToU16PcmCodec : public TMdaAudioCodecBase
	{ public: IMPORT_C virtual void Convert(TUint8* aSrc, TUint8* aDst, TInt aSamples); };
class TMdaAudioS16ToU16BEPcmCodec : public TMdaAudioCodecBase
	{ public: IMPORT_C virtual void Convert(TUint8* aSrc, TUint8* aDst, TInt aSamples); };

class TMdaAudioS16ToS16PcmSwapEndianCodec : public TMdaAudioCodecBase
	{ public: IMPORT_C virtual void Convert(TUint8* aSrc, TUint8* aDst, TInt aSamples); };

// Base of codecs that could be optimised by a generated table

// Internal to Symbian
class TMdaTableAudioCodec : public TMdaAudioCodecBase
	{
public:
	inline TMdaTableAudioCodec();
	//
	inline TInt TableSize();
	inline void SetTable(TPtr8 aTable);
	//
	virtual void FillTable(TPtr8 aTable)=0;
	IMPORT_C virtual void Convert(TUint8* aSrc, TUint8* aDst, TInt aSamples);
protected:
	virtual void ConvertSlow(TUint8* aSrc, TUint8* aDst, TInt aSamples)=0;
	virtual void ConvertFast(TUint8* aSrc, TUint8* aDst, TInt aSamples)=0;
protected:
	TInt iTableSize;
	TUint8* iTablePtr;
	};

// ALAW codecs

const TInt KMdaAlawTo16PcmExpLutSize = 8;
// Internal to Symbian
class TMdaAlawTo16PcmCodec : public TMdaTableAudioCodec
	{
public:
	inline TMdaAlawTo16PcmCodec();
	IMPORT_C virtual void FillTable(TPtr8 aTable);
protected:
	IMPORT_C TInt AlawSampleToPcm(TUint8 aAlaw);
	IMPORT_C virtual void ConvertSlow(TUint8* aSrc, TUint8* aDst, TInt aSamples);
	IMPORT_C virtual void ConvertFast(TUint8* aSrc, TUint8* aDst, TInt aSamples);
private:
	const static TInt iExpLut[KMdaAlawTo16PcmExpLutSize];
	};

const TInt KMda16PcmToAlawExpLutSize = 128;
const TInt KMda16PcmToAlawClip = 31744;
// Internal to Symbian
class TMda16PcmToAlawCodec : public TMdaTableAudioCodec
	{
public:
	inline TMda16PcmToAlawCodec();
	IMPORT_C virtual void FillTable(TPtr8 aTable);
protected:
	IMPORT_C TUint8 PcmSampleToAlaw(TInt aPcm);
	IMPORT_C virtual void ConvertSlow(TUint8* aSrc, TUint8* aDst, TInt aSamples);
	IMPORT_C virtual void ConvertFast(TUint8* aSrc, TUint8* aDst, TInt aSamples);
private:
	const static TInt8 iExpLut[KMda16PcmToAlawExpLutSize];
	};

// MULAW Codecs

const TInt KMda16PcmToMulawExpLutSize = 256;
const TInt KMda16PcmToMulawClip = 32635;
const TInt KMda16PcmToMulawBias = 0x84;
// Internal to Symbian
class TMda16PcmToMulawCodec : public TMdaTableAudioCodec
	{
public:
	inline TMda16PcmToMulawCodec();
	IMPORT_C virtual void FillTable(TPtr8 aTable);
protected:
	IMPORT_C TUint8 PcmSampleToMulaw(TInt16 aPcm);
	IMPORT_C virtual void ConvertSlow(TUint8* aSrc, TUint8* aDst, TInt aSamples);
	IMPORT_C virtual void ConvertFast(TUint8* aSrc, TUint8* aDst, TInt aSamples);
private:
	const static TInt8 iExpLut[KMda16PcmToMulawExpLutSize];
	};

const TInt KMdaMulawTo16PcmExpLutSize = 8;
// Internal to Symbian
class TMdaMulawTo16PcmCodec : public TMdaTableAudioCodec
	{
public:
	inline TMdaMulawTo16PcmCodec();
	IMPORT_C virtual void FillTable(TPtr8 aTable);
protected:
	IMPORT_C TInt MulawSampleToPcm(TUint8 aMulaw);
	IMPORT_C virtual void ConvertSlow(TUint8* aSrc, TUint8* aDst, TInt aSamples);
	IMPORT_C virtual void ConvertFast(TUint8* aSrc, TUint8* aDst, TInt aSamples);
private:
	const static TInt iExpLut[KMdaMulawTo16PcmExpLutSize];
	};

// IMA ADPCM Codecs

// Internal to Symbian
class TMdaImaAdpcmCodecState
	{
public:
	inline TMdaImaAdpcmCodecState();
	inline TMdaImaAdpcmCodecState(TInt16 aPredicted, TUint8 aIndex);
public:
	TInt16 iPredicted; // Previous output value
	TUint8 iIndex; // Index into stepsize table
	};

// Internal to Symbian
class TMdaImaAdpcmBaseCodec : public TMdaAudioCodecBase
	{
public:
	inline TMdaImaAdpcmBaseCodec(const TInt aChannels);
	inline void SetState(const TMdaImaAdpcmCodecState& aState);
	inline void SetState(const TMdaImaAdpcmCodecState& aState,const TInt aChannel);
	inline const TMdaImaAdpcmCodecState& GetState();
	inline const TMdaImaAdpcmCodecState& GetState(const TInt aChannel);
	IMPORT_C void ResetBuffer();
	IMPORT_C TBool OutputStep();
protected:
	TMdaImaAdpcmCodecState iState[2];	//for mono & stereo
	static const TInt iIndexTable[16];
	static const TInt iStepSizeTable[89];
	TBool iBufferStep;
	TInt iBuffer;
	TInt iChannels;
	};

// Internal to Symbian
class TMdaImaAdpcmTo16PcmCodec : public TMdaImaAdpcmBaseCodec
	{
public:
	inline TMdaImaAdpcmTo16PcmCodec(const TInt aChannels);
	IMPORT_C virtual void Convert(TUint8* aSrc, TUint8* aDst, TInt aSamples);
	};

//class TMdaImaAdpcmTo16PcmStereoCodec : public TMdaImaAdpcmBaseCodec
//	{
//public:
//	IMPORT_C virtual void Convert(TUint8* aSrc, TUint8* aDst, TInt aSamples);
//	};

// Internal to Symbian
class TMda16PcmToImaAdpcmCodec : public TMdaImaAdpcmBaseCodec
	{
public:
	inline TMda16PcmToImaAdpcmCodec(const TInt aChannels);
	IMPORT_C virtual void Convert(TUint8* aSrc, TUint8* aDst, TInt aSamples);
	};

// Packaged codecs

// Internal to Symbian
class CMdaAudioCodec : public CMdaCodec
	{
public:
	IMPORT_C virtual void SetChannelsL(TInt aChannels);
protected:
	TMdaAudioCodecBase* iCodec;
	};

// Internal to Symbian
class CMda8To16AudioCodec : public CMdaAudioCodec
	{
public:
	IMPORT_C virtual void ProcessL(TMdaPtr8* aSrc, TMdaPtr8* aDst);
	};

// Internal to Symbian
class CMda16To8AudioCodec : public CMdaAudioCodec
	{
public:
	IMPORT_C virtual void ProcessL(TMdaPtr8* aSrc, TMdaPtr8* aDst);
	};

// Internal to Symbian
class CMda16To16AudioCodec : public CMdaAudioCodec
	{
public:
	IMPORT_C virtual void ProcessL(TMdaPtr8* aSrc, TMdaPtr8* aDst);
	};

// Concrete packaged codecs

// Internal to Symbian
class CMdaMulawTo16PcmCodec : public CMda8To16AudioCodec
	{ public: inline CMdaMulawTo16PcmCodec() { iCodec = &iMulawTo16Pcm; }
	 private: TMdaMulawTo16PcmCodec iMulawTo16Pcm;	};

// Internal to Symbian
class CMda16PcmToMulawCodec : public CMda16To8AudioCodec
	{ public: inline CMda16PcmToMulawCodec() { iCodec = &i16PcmToMulaw; }
	 private: TMda16PcmToMulawCodec i16PcmToMulaw;  };

// Internal to Symbian
class CMdaAlawTo16PcmCodec : public CMda8To16AudioCodec
	{ public: inline CMdaAlawTo16PcmCodec() { iCodec = &iAlawTo16Pcm; }
	 private: TMdaAlawTo16PcmCodec iAlawTo16Pcm;	};

// Internal to Symbian
class CMda16PcmToAlawCodec : public CMda16To8AudioCodec
	{ public: inline CMda16PcmToAlawCodec() { iCodec = &i16PcmToAlaw; }
	 private: TMda16PcmToAlawCodec i16PcmToAlaw;  };

// Internal to Symbian
class CMda16PcmTo16PcmSwapEndianCodec : public CMda16To16AudioCodec
	{ public: inline CMda16PcmTo16PcmSwapEndianCodec() { iCodec = &i16PcmTo16PcmSwap; }
	private: TMdaAudioS16ToS16PcmSwapEndianCodec i16PcmTo16PcmSwap;	};

// Internal to Symbian
class CMdaU8PcmTo16PcmCodec : public CMda8To16AudioCodec
	{ public: inline CMdaU8PcmTo16PcmCodec() { iCodec = &iU8To16; }
	private: TMdaAudioU8ToS16PcmCodec iU8To16; };

// Internal to Symbian
class CMda16PcmToU8PcmCodec : public CMda16To8AudioCodec
	{ public: inline CMda16PcmToU8PcmCodec() { iCodec = &i16ToU8; }
	private: TMdaAudioS16ToU8PcmCodec i16ToU8; };

// Internal to Symbian
class CMda8PcmTo16PcmCodec : public CMda8To16AudioCodec
	{ public: inline CMda8PcmTo16PcmCodec() { iCodec = &i8To16; }
	private: TMdaAudioS8ToS16PcmCodec i8To16; };

// Internal to Symbian
class CMda16PcmTo8PcmCodec : public CMda16To8AudioCodec
	{ public: inline CMda16PcmTo8PcmCodec() { iCodec = &i16To8; }
	private: TMdaAudioS16ToS8PcmCodec i16To8; };

// Internal to Symbian
class CMdaU16PcmTo16PcmCodec : public CMda16To16AudioCodec
	{ public: inline CMdaU16PcmTo16PcmCodec() { iCodec = &iU16To16; }
	private: TMdaAudioU16ToS16PcmCodec iU16To16; };

// Internal to Symbian
class CMda16PcmToU16PcmCodec : public CMda16To16AudioCodec
	{ public: inline CMda16PcmToU16PcmCodec() { iCodec = &i16ToU16; }
	private: TMdaAudioS16ToU16PcmCodec i16ToU16;
	};

// Internal to Symbian
class CMdaU16PcmTo16PcmSwapEndianCodec : public CMda16To16AudioCodec
	{ public: inline CMdaU16PcmTo16PcmSwapEndianCodec() { iCodec = &iU16BETo16; }
	private: TMdaAudioU16BEToS16PcmCodec iU16BETo16; };

// Internal to Symbian
class CMda16PcmToU16PcmSwapEndianCodec : public CMda16To16AudioCodec
	{ public: inline CMda16PcmToU16PcmSwapEndianCodec() { iCodec = &i16ToU16BE; }
	private: TMdaAudioS16ToU16BEPcmCodec i16ToU16BE;
	};

// Internal to Symbian
class CMda16PcmTo16PcmCodec : public CMdaAudioCodec
// Special case - optimsed
	{
public:
	IMPORT_C virtual void ProcessL(TMdaPtr8* aSrc, TMdaPtr8* aDst);
	};

// Inline functions

inline TMdaAudioCodecBase::TMdaAudioCodecBase()
	{}

inline TMdaTableAudioCodec::TMdaTableAudioCodec()
	: iTablePtr(0) {}
inline TInt TMdaTableAudioCodec::TableSize()
	{ return iTableSize; }
inline void TMdaTableAudioCodec::SetTable(TPtr8 aTable)
	{ ASSERT(aTable.Length()>iTableSize); iTablePtr = &aTable[0]; }


inline TMda16PcmToAlawCodec::TMda16PcmToAlawCodec()
	{ iTableSize = (2<<14); }
inline TMdaAlawTo16PcmCodec::TMdaAlawTo16PcmCodec()
	{ iTableSize = (2<<9); }
inline TMda16PcmToMulawCodec::TMda16PcmToMulawCodec()
	{ iTableSize = (2<<14); }
inline TMdaMulawTo16PcmCodec::TMdaMulawTo16PcmCodec()
	{ iTableSize = (2<<9); }

inline TMdaImaAdpcmBaseCodec::TMdaImaAdpcmBaseCodec(const TInt aChannels)
: iBufferStep(ETrue), iBuffer(0), iChannels(aChannels) {}
inline TMdaImaAdpcmCodecState::TMdaImaAdpcmCodecState()
	: iPredicted(0), iIndex(0) {}
inline TMdaImaAdpcmCodecState::TMdaImaAdpcmCodecState(TInt16 aPredicted, TUint8 aIndex)
	: iPredicted(aPredicted), iIndex(aIndex) {}
inline void TMdaImaAdpcmBaseCodec::SetState(const TMdaImaAdpcmCodecState& aState)
	{ iState[0] = aState; }
inline const TMdaImaAdpcmCodecState& TMdaImaAdpcmBaseCodec::GetState()
	{ return iState[0]; }
inline void TMdaImaAdpcmBaseCodec::SetState(const TMdaImaAdpcmCodecState& aState, const TInt aChannel)
	{ iState[aChannel] = aState; }
inline const TMdaImaAdpcmCodecState& TMdaImaAdpcmBaseCodec::GetState(const TInt aChannel)
	{ return iState[aChannel]; }
inline TMdaImaAdpcmTo16PcmCodec::TMdaImaAdpcmTo16PcmCodec(const TInt aChannels)
	:TMdaImaAdpcmBaseCodec(aChannels)
	{}
inline TMda16PcmToImaAdpcmCodec::TMda16PcmToImaAdpcmCodec(const TInt aChannels)
	:TMdaImaAdpcmBaseCodec(aChannels)
	{}

#endif
