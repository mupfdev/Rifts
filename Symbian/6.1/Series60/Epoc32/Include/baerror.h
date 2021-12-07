// BAERROR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Started by DWW, March 1997
// Error numbers
//

#if !defined(__BAERROR_H__)
#define __BAERROR_H__


#ifdef _UNICODE
#define KUidBaflDll KUidBaflDll16
#else
#define KUidBaflDll KUidBaflDll8
#endif

#define KUidBaflDllValue8 0x1000004e
const TUid KUidBaflDll8={KUidBaflDllValue8};
const TUid KUidBaflDll16={0x10003A0F};

#endif
