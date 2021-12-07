/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __BTHCI_PAN__
#define __BTHCI_PAN__

/** BTHCI application panic codes */
enum TBTHCIPanics
    {
    EBTHCIUnrecognisedCommand = 1,
    EBTHCIInvalidComponentIndex,
    EBTHCIInvalidState,
    EBTHCIAlreadyActive,
    EBTHCIViewPrintNewLine
    };

inline void Panic(TBTHCIPanics aReason)
    {
    User::Panic(_L("BTHCI"), aReason);
    }

#endif // __BTHCI_PAN__
