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

    General AMR plug-in definitions.

-----------------------------------------------------------------------------
*/
#ifndef __AMRMDA_H__
#define __AMRMDA_H__

// INCLUDES

#include <Mda\Common\Audio.h>
#include <AmrCodec.h>
#include <AmrMda.hrh>


// CONSTANTS

// raw amr clip format uid
const TUint KUidMdaClipFormatRawAmrValue = KUidMdaClipFormatRawAmrDefine;
const TUid KUidMdaClipFormatRawAmr = {KUidMdaClipFormatRawAmrValue};

// raw amr audio codec uid
const TUint KUidMdaRawAmrCodecValue = KUidMdaRawAmrCodecDefine;
const TUid KUidMdaRawAmrCodec = {KUidMdaRawAmrCodecValue};


// CLASS DEFINITIONS

/*
-----------------------------------------------------------------------------

    TMdaRawAmrAudioCodec

    AMR clip format config package.

-----------------------------------------------------------------------------
*/
class TMdaRawAmrClipFormat : public TMdaClipFormat
    {
public:
    inline TMdaRawAmrClipFormat();
    };

/*
-----------------------------------------------------------------------------

    TMdaRawAmrAudioCodec

    Config package for raw AMR codec.

-----------------------------------------------------------------------------
*/
class TMdaRawAmrAudioCodec : public TMdaPackage
    {
public:
    enum TAmrMode
        {
        EMR475 = 0, // 4.75 kbit/s
        EMR515,     // 5.15 kbit/s       
        EMR59,      // etc.
        EMR67,      //
        EMR74,      //
        EMR795,     //
        EMR102,     //
        EMR122,     // 12.2 kbit/s (default)
        };
public:
    inline TMdaRawAmrAudioCodec(TAmrMode aMode=EMR515, TBool aDTX=ETrue);
    inline TMdaRawAmrAudioCodec(const TMdaRawAmrAudioCodec& aConf);
    inline TMdaRawAmrAudioCodec& operator=(const TMdaRawAmrAudioCodec& aConf);
public:
    TAmrDecParams iDecConf; // decoder configuration parameters
    TAmrEncParams iEncConf; // encoder configuration parameters
    };

inline TMdaRawAmrClipFormat::TMdaRawAmrClipFormat() :
TMdaClipFormat(KUidMdaClipFormatRawAmr, sizeof(TMdaRawAmrClipFormat)) {}

inline TMdaRawAmrAudioCodec::TMdaRawAmrAudioCodec(TAmrMode aMode, TBool aDTX) :
TMdaPackage(KUidMdaRawAmrCodec, KUidMdaRawAmrCodec, sizeof(TMdaRawAmrAudioCodec)),
iDecConf(), iEncConf() {iEncConf.iDTX=aDTX;iEncConf.iMode=aMode;}

inline TMdaRawAmrAudioCodec::TMdaRawAmrAudioCodec(const TMdaRawAmrAudioCodec& aConf) :
TMdaPackage(KUidMdaRawAmrCodec, KUidMdaRawAmrCodec, sizeof(TMdaRawAmrAudioCodec)),
iDecConf(aConf.iDecConf),iEncConf(aConf.iEncConf) {}

inline TMdaRawAmrAudioCodec& TMdaRawAmrAudioCodec::operator=(const TMdaRawAmrAudioCodec& aConf)
{iDecConf=aConf.iDecConf;iEncConf=aConf.iEncConf;return *this;}

#endif //__AMRMDA_H__
//-----------------------------------------------------------------------------
//  End of File
//-----------------------------------------------------------------------------
