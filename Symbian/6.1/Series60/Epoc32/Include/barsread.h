// BARSREAD.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __BARSREAD_H__
#define __BARSREAD_H__

#include <e32std.h>
#include <badesca.h>


class TResourceReader
    {
public:
    IMPORT_C void SetBuffer(const TDesC8* aBuffer);
    IMPORT_C const TAny* Ptr();

    // Read counted strings into allocated buffer
    inline HBufC*   ReadHBufCL();
    IMPORT_C HBufC8*  ReadHBufC8L();
    IMPORT_C HBufC16* ReadHBufC16L();

    // Build pointer from a counted string
    inline TPtrC   ReadTPtrC();
    IMPORT_C TPtrC8  ReadTPtrC8();
    IMPORT_C TPtrC16 ReadTPtrC16();

    // Build pointer from a counted string in an array of counted strings,
    // also setting the buffer to be used.
    inline TPtrC   ReadTPtrC  (TInt aIndex,const TDesC8* aBuffer);
    IMPORT_C TPtrC8  ReadTPtrC8 (TInt aIndex,const TDesC8* aBuffer);
    IMPORT_C TPtrC16 ReadTPtrC16(TInt aIndex,const TDesC8* aBuffer);

    // Build an array of strings from a resource array
    inline CDesCArrayFlat*   ReadDesCArrayL();
    IMPORT_C CDesC8ArrayFlat*  ReadDesC8ArrayL();
    IMPORT_C CDesC16ArrayFlat* ReadDesC16ArrayL();

    IMPORT_C TInt ReadInt8();
    IMPORT_C TUint ReadUint8();
    IMPORT_C TInt ReadInt16();
    IMPORT_C TUint ReadUint16();
    IMPORT_C TInt ReadInt32();
    IMPORT_C TUint ReadUint32();
    IMPORT_C TReal64 ReadReal64();

    IMPORT_C void Read(TAny* aPtr,TInt aLength);
    IMPORT_C void Rewind(TInt aLength);
    IMPORT_C void Advance(TInt aLength);
private:
    void MovePtr(const TUint8* aPtr);
private:
    const TDesC8* iBuffer;
    const TUint8* iCurrentPtr;
    const TUint8* iEndPtr;
    };

#if defined(_UNICODE)
inline HBufC* TResourceReader::ReadHBufCL()
    {return ReadHBufC16L();}
inline TPtrC TResourceReader::ReadTPtrC()
    {return ReadTPtrC16();}
inline TPtrC TResourceReader::ReadTPtrC(TInt aIndex,const TDesC8* aBuffer)
    {return ReadTPtrC16(aIndex, aBuffer);}
inline CDesCArrayFlat* TResourceReader::ReadDesCArrayL()
    {return ReadDesC16ArrayL();}
#else
inline HBufC* TResourceReader::ReadHBufCL()
    {return ReadHBufC8L();}
inline TPtrC TResourceReader::ReadTPtrC()
    {return ReadTPtrC8();}
inline TPtrC TResourceReader::ReadTPtrC(TInt aIndex,const TDesC8* aBuffer)
    {return ReadTPtrC8(aIndex, aBuffer);}
inline CDesCArrayFlat* TResourceReader::ReadDesCArrayL()
    {return ReadDesC8ArrayL();}
#endif



#endif
