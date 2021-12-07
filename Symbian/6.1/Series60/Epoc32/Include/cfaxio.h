// CFAXIO.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//



#if defined(__VC32__) && _MSC_VER==1100
// Disable MSVC++ 5.0 aggressive warnings about non-expansion of inline functions. 
#pragma warning(disable : 4710)	// function '...' not expanded
#endif

#if !defined(__CFAXIO_H__)
#define __CFAXIO_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif

#if !defined(__FAXDEFN_H__)
#include <faxdefn.h>
#endif

typedef TUint32 TCodeDef;

const TInt KFaxFileStoreUidVal(268435712);

class CFileWriteStream;
class CFileReadStream;


class CFaxT4 : public CBase // // replaces FaxT4 class used up to faxstore 013
	{
public:
	IMPORT_C static CFaxT4 * NewL ();
	IMPORT_C static CFaxT4 * NewLC ();
	IMPORT_C void EncodeScanLine(const TDesC8& aScanLine,TDes8& anEncodedScanLine);
	IMPORT_C TInt DecodeScanLine(TDes8& aScanLine,const TDesC8& anEncodedScanLine);
	IMPORT_C void EncodeScanLine1D(const TDesC8& aScanLine,TDes8& anEncodedScanLine);
	IMPORT_C TInt DecodeScanLine1D(TDes8& aScanLine,const TDesC8& anEncodedScanLine);
	IMPORT_C void EncodeScanLine2D(const TDesC8& aScanLine,TDes8& anEncodedScanLine);
	IMPORT_C TInt DecodeScanLine2D(TDes8& aScanLine,const TDesC8& anEncodedScanLine);
	IMPORT_C void PageInitialize (TFaxResolution aResolution, TFaxCompression aCompression, TInt aFlag2 = 0);
private:
	inline CFaxT4();
	//
	void DoEncodeScanLine2D (const TDesC8 & aScanLine, TDes8 & anEncodedScanLine);
	void DecodeHuffman(const TDesC8 & aEncodedScanLine);
private:
	TFaxResolution iResolution;
	TFaxCompression iCompression;
	TInt iLineCount;
	TInt iK;
	TInt iReservedFlag2;
	const TUint8* iEndRef;
	TUint8 iRef[KFaxPixelsPerScanLine+4];
	};

class TFaxHeaderInfo
   {
 public:
   TInt iHeaderFontWidthInBytes;	// width of font in bytes
   TInt iHeaderFontHeightInLines;// height of font in lines
   TInt iOffsetToDay;            // offset to two digit day of month
   TInt iOffsetToMonth;          // offset to two digits month of year
   TInt iOffsetToYear;           // offset to four digits year
   TInt iOffsetToHour;           // offset to two digits hour (24 hour clock) 
   TInt iOffsetToMinute;         // offset to two digits minute
   TInt iOffsetToTotalPages;     // offset to two digits for total pages
   TInt iOffsetToCurrentPage;    // offset to two digits for current page
   };

typedef TPckgBuf < TFaxHeaderInfo > TFaxHeaderInfoPckg;


class CFaxHeaderLines : public CBase
   {
 public:
   IMPORT_C static CFaxHeaderLines * NewL ();
   IMPORT_C static CFaxHeaderLines * NewLC ();
   ~CFaxHeaderLines ();

   IMPORT_C void WriteRawFontLineL (const TInt alineNumber,TRawScanLine & aUncompressedDataLine);
   IMPORT_C void WriteRawHeaderLineL (const TInt alineNumber,TRawScanLine & aUncompressedDataLine);
   IMPORT_C void WriteFaxHeaderInfoL (TFaxHeaderInfo & aFaxHeaderInfo);
   IMPORT_C void ReadRawFontLineL (const TInt alineNumber,TRawScanLine & aUncompressedDataLine);
   IMPORT_C void ReadRawHeaderLineL (const TInt alineNumber,TRawScanLine & aUncompressedDataLine);
   IMPORT_C void ReadFaxHeaderInfoL (TFaxHeaderInfo & aFaxHeaderInfo);

 protected:
   void ConstructL ();

 private:
   RFs iFileSession;
   RFile iFile;
   TInt iSeekpos;
   TInt iLineNumber;
	
   public:
   TFaxHeaderInfoPckg iOurFaxHeaderInfoPckg;
	};
#endif

