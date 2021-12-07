// BAMDESCA.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Started by DavidW, March 1996
// Mixin descriptor array
//

#if !defined(__BAMDESCA_H__)
#define __BAMDESCA_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif


class MDesC8Array
    {
public:
    virtual ~MDesC8Array() {}
    virtual TInt MdcaCount() const =0;
    virtual TPtrC8 MdcaPoint(TInt aIndex) const =0;
    };

class MDesC16Array
    {
public:
    virtual ~MDesC16Array() {}
    virtual TInt MdcaCount() const =0;
    virtual TPtrC16 MdcaPoint(TInt aIndex) const =0;
    };


// The definitions below are macros rather than typedefs to avoid generating
// warning C4097 every time the generic mixin class is used in a class
// definition.

#if defined(_UNICODE)
#define MDesCArray MDesC16Array
//typedef MDesC16Array MDesCArray;
#else
#define MDesCArray MDesC8Array
//typedef MDesC8Array  MDesCArray;
#endif


#endif // __BAMDESCA_H__

