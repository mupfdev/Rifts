/*
 * NOKIA MOBILE PHONES
 * DIGITAL CONVERGENCE
 * LINDA SW
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *          AMR Codec Plug-In
 *          -----------------
 *
 *          SW Include Document - C++
 *
 *
 *
 *
 *
 *
 *
 *
 * Module name: AmrMda
 *
 * $Archive:$
 *
 * $Revision:$ 
 *
 *
 * Copyright (c) 2002. Nokia Mobile Phones
 *
 *
 * Change History:
 *
 * $History:$
 *
 *-----------------------------------------------------------------------------
 */


/*
-----------------------------------------------------------------------------

    DESCRIPTION

    Low level AMR decoder and encoder APIs

-----------------------------------------------------------------------------
*/
#ifndef __AMRCODEC_H__
#define __AMRCODEC_H__


// INCLUDES

#include <E32Base.h>


// FORWARD DECLARATIONS

class CAmrToPcmDecoderImpl;
class CPcmToAmrEncoderImpl;


// CLASS DEFINITIONS
/*
-----------------------------------------------------------------------------

    TAmrDecParams

    AMR decoding parameters.

-----------------------------------------------------------------------------
*/
class TAmrDecParams
    {
public:
    inline TAmrDecParams();
public:
    TInt iConcealment; // error concealment level (0 none, 1 default)
    };

TAmrDecParams::TAmrDecParams() :
iConcealment(1) {}


/*
-----------------------------------------------------------------------------

    TAmrEncParams

    AMR encoding parameters.

-----------------------------------------------------------------------------
*/
class TAmrEncParams
    {
public:
    inline TAmrEncParams();
public:
    TInt iMode;      // encoding mode 0-7 (0=MR475,1=MR515,...,7=MR122, default 7)
    TInt iDTX;       // DTX flag (TRUE or default FALSE)
    };

TAmrEncParams::TAmrEncParams() :
iMode(7), iDTX(0) {}


// CLASS DEFINITIONS
/*
-----------------------------------------------------------------------------

    TAmrFrameInfo

    AMR frame info struct.

-----------------------------------------------------------------------------
*/
class TAmrFrameInfo
    {
public:
    TAmrFrameInfo() {};
public:
    IMPORT_C static TInt MinFrameSize();
    IMPORT_C static TInt MaxFrameSize();
    IMPORT_C static TInt MaxFrameSamples();
    IMPORT_C static TInt MaxChannels();
    IMPORT_C static TInt FrameHeaderSize();
    IMPORT_C static TInt FrameSize(const TAmrFrameInfo& aInfo);
public:
    TInt iMode;            // encoding mode
    TInt iBitrate;         // bitrate (kbit/s)
	TInt iSamplingRate;    // sampling frequency (Hz)
	TInt iChannels;        // number of channels
    TInt iFrameSize;       // encoded size (bytes)
    TInt iFrameSamples;    // decoded size (samples per channel)
public:
    TInt iSamplingRateOut; // sampling frequency after conversion (Hz)
    TInt iChannelsOut;     // number of audio channels after conversion (1 or 2)
    TInt iFrameSamplesOut; // decoded size after conversion (samples per channel)
    };

/*
-----------------------------------------------------------------------------

    CAmrToPcmDecoder

    Low level AMR decoding API.

-----------------------------------------------------------------------------
*/
class CAmrToPcmDecoder : public CBase
    {
protected:
    IMPORT_C CAmrToPcmDecoder();
    IMPORT_C void ConstructL();
public:
    IMPORT_C static CAmrToPcmDecoder* NewL(const TAmrDecParams& aConf);
    IMPORT_C virtual ~CAmrToPcmDecoder();
    IMPORT_C void Reset();
    IMPORT_C void Reset(const TAmrDecParams& aConf);
    IMPORT_C static TInt FrameInfo(const TUint8* aBuf, TInt aBufLen, TAmrFrameInfo& aInfo);
    IMPORT_C static TInt FrameInfo(const TUint8* aBuf, TInt aBufLen, TAmrFrameInfo& aInfo, const TAmrDecParams& aConf);
    IMPORT_C static TInt SeekSync(const TUint8* aBuf, TInt aBufLen);
    IMPORT_C TInt Decode(TUint8* aSrc, TInt& aSrcUsed, TUint8* aDst, TInt& aDstLen, TBool aMuteFlag);
    IMPORT_C TInt Decode(TUint8* aSrc, TInt& aSrcUsed, TUint8* aDst1, TUint8* aDst2, TInt& aDstLen1, TInt& aDstLen2, TInt aMuteFlag);
private:
    CAmrToPcmDecoderImpl* iState;
    };

/*
-----------------------------------------------------------------------------

    CPcmToAmrEncoder

    Low level AMR encoding API.

-----------------------------------------------------------------------------
*/
class CPcmToAmrEncoder : public CBase
    {
protected:
    IMPORT_C CPcmToAmrEncoder();
    IMPORT_C void ConstructL();
public:
    IMPORT_C static CPcmToAmrEncoder* NewL(const TAmrEncParams& aConf);
    IMPORT_C virtual ~CPcmToAmrEncoder();
    IMPORT_C void Reset();
    IMPORT_C void Reset(const TAmrEncParams& aConf);
    IMPORT_C TInt Encode(TUint8* aSrc, TInt& aSrcUsed, TUint8* aDst, TInt& aDstLen);
private:
    CPcmToAmrEncoderImpl* iState;
    };

#endif //__AMRCODEC_H__
//-----------------------------------------------------------------------------
//  End of File
//-----------------------------------------------------------------------------
