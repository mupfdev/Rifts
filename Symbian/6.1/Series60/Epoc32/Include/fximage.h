// FXIMAGE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


#ifndef __FXIMAGE_H__
#define __FXIMAGE_H__


#if !defined(__FAXSTORE_H__)
#include <faxstore.h>
#endif

#if !defined(__FAXTIFF_H__)
#include "faxtiff.h"
#endif

#if !defined (__MSVAPI_H__)
#include <msvapi.h>
#endif




// Here's the class definition for CMsvFaxStores

// The purpose of this class to encapsulate different ways of storing
// raw fax data

// This is for two reasons :

// 1.  It is possible that at some point it might be necessary
//     to change the format for fax storage - with a storage class and
//     a well defined interface this is not a problem.
// 2.  Having different fax storage implementations makes the task of
//     writing convertors much easier. All that is needed is to read
//     using one storage class and then write with another

// We have to assume that anything to do with storage might leave

// Begin with a constant :

// maximum size of a descriptor for reading and writing T4 scan lines

// the longest possible encoded scan line is alternating black and white dots
// that's 8 bits, as single white dot = 00111 single black dot = 010
// there's a maximum of 864 such pairs in a 1728 dot scan line
// let's be generous and allow for eols and padding - 896
// this is sufficient for faxes we generate ourselves

// On the other hand, a scan line can take up to 5 seconds to transmit
// At 14400 bps, it could contain 72000 bits = 9000 bytes
// There could be internal line padding (alternate run lengths of zero)
// So this bigger figure is needed for faxes which we receive via the line

// we also use this when sending phase C data to the modem


// we only support normal at the moment, though we know about fine
// we don't even know about superfine

// compression 

// we only support MH (Modified Huffman, T4-1D) at the moment
// we know about MR (Modified Read, T4-2D) but don't support it
// we don't know about UMR (Uncompressed Modified Read, T4-2D)
// we know about MMR (modified modified Read, T6) but don't support it

// beware the following magic modifier number used for compression -
// we add 'U' = 85 to compression value for uncompressed data
// Currently this *only* works with reading from PsiFaxStores (which
// will deliver uncompressed scanlines if compression >= 'U') and with
// writing to TIFF files (which will deliver uncompressed images if
// compression is >= 'U').

// This kludge was put in to the code to deliver a Q&D method of
// exporting fax data for viewing and testing out the T4 decoder -
// please note the Microsoft Word will happily import uncompressed
// TIFF images but doesn't accept TIFF class F.


class CMsvFaxStore : public CBase
   {

 public:

   // these are the fax parameter for each page

   TInt iByteCount;             // size of image in bytes
   TInt iLines;                 // length of image in lines
   TInt iResolu;            // resolution of image
   TInt iCompression;           // type of compression
   TInt iBitOrder;              // little or big endian ordering of bits in a byte
   TInt iPage;                  // page number of image in fax

   // functions for receiving

   virtual void OpenFaxInL (const TDesC &) = 0;       // takes a name
   virtual void PagePrepareL (void) = 0;
   virtual void WriteFaxDataL (TDesC8 &) = 0;   // takes a buffer to write
   virtual void WritePageParmsL (TFaxBufSenderId &) = 0;
   virtual void CloseFaxInStoreL (void) = 0;

   // functions for sending

   virtual TInt OpenFaxOutL (const TDesC &) = 0;      // takes a name
   virtual TInt NextPageFind (void) = 0;       // returns 0 if no more pages
   virtual void ReadPageParmsL (void) = 0;
   virtual void ReadFaxDataL (TDes8 &) = 0;     // fills the buffer with data
   virtual void PreviousPageFind (void) = 0;
   virtual void CloseFaxStore (void) = 0;
   };
/*******************************************************************
2. A version that handles TIFF class F fax images
   and can also be used to write uncompressed data
*******************************************************************/



class CMsvTiffStore : public CMsvFaxStore
   {

 private:
   RFs iFileSession;
   RFile iFile;

   TIfdPkg iOurIfdBuf;
   TIfdEntryPkg iOurIfdEntryBuf;
   TInt32Pkg iAnyDes32;
   TInt16Pkg iAnyDes16;

   TInt32 iNextIfd;
   TInt32 iLastIfd;

   TInt iSeekpos;
   TInt iPageStart;
   TInt iPageEnd;

   void ConstructL ();

   void InitIfd (TIfd & aIfd);

 public:
    ~CMsvTiffStore ();
   static CMsvTiffStore *NewL ();
   static CMsvTiffStore *NewLC ();

   void OpenFaxInL (const TDesC & aFileName);
   void PagePrepareL ();
   void WriteFaxDataL (TDesC8 & aBuffer);
   void WritePageParmsL (TFaxBufSenderId &);
   void CloseFaxInStoreL ();

   TInt OpenFaxOutL (const TDesC & aFileName);
   TInt NextPageFind ();
   void ReadPageParmsL ();
   void ReadFaxDataL (TDes8 & aBuffer);
   void PreviousPageFind ();
   void CloseFaxStore ();
   };

/*******************************************************************
3. A version that does Psion streams and stores -
   this can also be used to generate uncompressed data
*******************************************************************/

class CPsiFaxStore : public CMsvFaxStore
   {

 private:
   CWriteFaxFile *writefaxfile;
   CReadFaxFile *readfaxfile;

   void ConstructL ();

 public:
    ~CPsiFaxStore ();
   static CPsiFaxStore *NewL ();
   static CPsiFaxStore *NewLC ();

   void OpenFaxInL (const TDesC & aFileName);
   void PagePrepareL ();
   void WriteFaxDataL (TDesC8 & aBuffer);
   void WritePageParmsL (TFaxBufSenderId &);
   void CloseFaxInStoreL ();

   TInt OpenFaxOutL (const TDesC & aFileName);
   TInt NextPageFind ();
   void ReadPageParmsL ();
   void ReadFaxDataL (TDes8 & aBuffer);
   void PreviousPageFind ();
   void CloseFaxStore ();


   TInt NumPages();
   };


#endif




