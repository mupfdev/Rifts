// FAXSTORE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__FAXSTORE_H__)
#define __FAXSTORE_H__

#include <faxdefn.h>
#include <cfaxio.h>

class TFaxBandHeader
	{
public:
	IMPORT_C TFaxBandHeader();
	IMPORT_C TFaxBandHeader(TStreamId aStreamId);
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
public:
	TInt iNumScanLines;
	TInt iNumBytes;
	TStreamId iStreamId;
	};

class CFaxPageInfo : public CBase
	{
protected:
	CFaxPageInfo();
public:
	IMPORT_C static CFaxPageInfo* NewL();
	IMPORT_C ~CFaxPageInfo();
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
public:
	TFaxResolution iResolution;
	TFaxCompression iCompression; // was TInt iReservedFlag1 up to faxstore 013
	TInt iReservedFlag2;
	TFaxBufSenderId iSenderId;
	CArrayFixFlat<TFaxBandHeader>* iBandHeaderList;
	};

class CFaxPages	: public CBase
	{
protected:
	CFaxPages();
public:
	IMPORT_C static CFaxPages* NewL();
	IMPORT_C ~CFaxPages();
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
public:
	CArrayFixFlat<TStreamId>* iPageStreamIdList;
	};

class CWriteFaxPages : public CBase
	{
protected:
	CWriteFaxPages(CStreamStore& aStore,TInt aMaxScanLinesInBand);
	void ConstructL();
	TBool BandCompleted();
public:
	IMPORT_C static CWriteFaxPages* NewL(CStreamStore& aStore,TInt aMaxScanLinesInBand=0);
	IMPORT_C ~CWriteFaxPages();
	IMPORT_C void StartPage(TFaxResolution aResolution, TFaxCompression aCompression, TInt aFlag2 = 0);
	IMPORT_C void EndPageL(TFaxResolution aResolution, TFaxBufSenderId& aSenderId, TFaxCompression aCompression = EModifiedHuffman, TInt aFlag2 = 0);
	IMPORT_C void AddScanLineL(const TDesC8& aScanline);
	IMPORT_C void AddEncodedScanLineL(const TDesC8& anEncodedScanLine);
	IMPORT_C TStreamId CommitPageL();
private:
	TInt iMaxScanLinesInBand;
	CFaxPages* iFaxPages;
	CFaxPageInfo* iCurrentPage;
	CStreamStore* iStore;
	CFaxT4* iFaxT4;
	RStoreWriteStream iWriteStream;
	TBuf8<KFaxT4MaxDesLength> iEncodedScanLine;
	};

class CWriteFaxFile : public CBase
	{
protected:
	CWriteFaxFile();
	void ConstructL();
	void DoOpenL(TInt aMaxScanLinesInBand);
public:
	IMPORT_C static CWriteFaxFile* NewL();  
	IMPORT_C ~CWriteFaxFile();
	IMPORT_C void OpenL(const TDesC& aFileName,TInt aMaxScanLinesInBand);
	IMPORT_C void CommitL();	
	IMPORT_C void Close();	
	IMPORT_C void AbortWrite();	 // deletes file, called by OpenL() and CloseL() if they leave
private:
	TFileName iFileName;
	RFs iFs;
	CDirectFileStore* iFileStore;
public:
	CWriteFaxPages* iWriteFaxPages;
	};

class TFaxPageInfo
	{
public:
	TInt iNumScanLines;
	TFaxResolution iResolution;
	TFaxBufSenderId iSenderId;
    TFaxCompression iCompression; // was TInt iReservedFlag1 up to faxstore 013
	TInt iReservedFlag2;
	};

class CReadFaxPages : public CBase
	{
protected:
	CReadFaxPages(CStreamStore& aStore);
	void ConstructL(TStreamId aStreamId);
public:
	IMPORT_C static CReadFaxPages* NewL(CStreamStore& aStore,TStreamId aStreamId);
	IMPORT_C ~CReadFaxPages();
	IMPORT_C TInt NumPages() const;
	IMPORT_C void SetPageL(TInt aNum);
	IMPORT_C TInt NumScanLinesPerPage() const;
	IMPORT_C TFaxPageInfo CurrentPageInfo() const;
	IMPORT_C void SeekScanLineL(TInt anIndex);
	IMPORT_C TInt GetScanLineL(TDes8& aScanLine);
	IMPORT_C void GetEncodedScanLineL(TDes8& anEncodedScanLine);
protected:
	void SetBandL(TInt anIndex);
private:
	TInt iBandIndex;
	TInt iScanLineOffset;
	CFaxPages* iFaxPages;
	CFaxPageInfo* iCurrentPage;
	CStreamStore* iStore;
	CFaxT4* iFaxT4;
	RStoreReadStream iReadStream;
	TBuf8<KFaxT4MaxDesLength> iEncodedScanLine;
	};

class CReadFaxFile : public CBase
	{
protected:
	CReadFaxFile();
	void ConstructL();
	void DoOpenL(const TDesC& aFileName);
public:
	IMPORT_C static CReadFaxFile* NewL();
	IMPORT_C ~CReadFaxFile();
	IMPORT_C void OpenL(const TDesC& aFileName);
	IMPORT_C void Close();
private:
	RFs iFs;
	CDirectFileStore* iFileStore;
public:
	CReadFaxPages* iReadFaxPages;
	};

// now the TFaxHeaderInfo and CFaxHeaderLines classes
// for saving/restoring fax headers
// used by fax client and fax server

/*
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
   };*/
#endif