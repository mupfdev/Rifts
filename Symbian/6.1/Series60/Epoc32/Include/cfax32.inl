// CFAX32.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

/********************************************************************/

#ifndef __cfax32_INL
#define __cfax32_INL

/********************************************************************/

inline void CFaxTransfer::SetMode (TFaxMode aMode)
   {
   iMode = aMode ;
   }

inline void CFaxTransfer::SetPhoneNumber (TDesC8 & aNumber)
   {
   iPhoneNumber.Copy (aNumber);
   }

inline void CFaxTransfer::SetReceiveFileName (const TFileName & aName)
   {
   iReceiveFileName.Copy (aName);
   }

/********************************************************************/

#endif

