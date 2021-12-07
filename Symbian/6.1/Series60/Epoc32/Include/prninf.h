// PRNINF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __PRNINF_H__
#define __PRNINF_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__GDI_H__)
#include <gdi.h>
#endif
#if !defined(__FLDBASE_H__)
#include <fldbase.h>
#endif

// Classes defined
//class TPageNumbers;
class CHeaderFooter;
class TPrintParameters;		
class TPageMargins;
class MPrintProcessObserver;	

// classes referenced
class RReadStream;
class RWriteStream;
class CRichText;
class CParaFormatLayer;
class CCharFormatLayer;
class MFieldFileNameInfo;
class MFieldPageNumInfo;
class MFieldNumPagesInfo;
//////////////////


class TPrintParameters
	{
public:
	IMPORT_C TPrintParameters(); // sets to 1,0,0
public:
	TInt iNumCopies;									
	TInt iFirstPage;	// First page to print			
	TInt iLastPage;		// ... and last page to print
	};


class TPageMargins
	{
public:
	IMPORT_C void InternalizeL(RReadStream& aStream); 	
	IMPORT_C void ExternalizeL(RWriteStream& aStream)const;
public:
	TInt iHeaderOffset; // from top of page
	TInt iFooterOffset; // from bottom margin
	TMargins iMargins;
	};


class CHeaderFooter : public CBase, private MTextFieldFactory
	{
public:
	IMPORT_C static CHeaderFooter* NewL();
	IMPORT_C virtual ~CHeaderFooter();
	//
	IMPORT_C void CreateTextL();
	IMPORT_C void SetFirstPageToPrintTo(TInt aPageNum); // allows the first few pages of a doc not to have a header on them
	inline TInt FirstPageToPrintTo()const; // relative to the first page being numbered 0
	//
	// persistence
	IMPORT_C TStreamId StoreL(CStreamStore& aStore)const;
	IMPORT_C void RestoreL(const CStreamStore& aStore,TStreamId aStreamId,MPictureFactory* aFactory);
	IMPORT_C void StoreComponentsL(CStreamStore& aStore,CStoreMap& aMap)const;
	IMPORT_C void RestoreComponentsL(const CStreamStore& aStore,MPictureFactory* aFactory);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	//
	// text bits
	IMPORT_C CRichText* Text()const;
	IMPORT_C CParaFormatLayer* ParaFormat()const;
	IMPORT_C CCharFormatLayer* CharFormat()const;
	IMPORT_C void SetText(CRichText* aText); // takes ownership
	IMPORT_C void SetParaFormat(CParaFormatLayer* aParaFormat); // takes ownership
	IMPORT_C void SetCharFormat(CCharFormatLayer* aCharFormat); // takes ownership
	//
	// field bits
	IMPORT_C void SetFileNameInfo(const MFieldFileNameInfo& aFileNameInfo); // call if you want headers/footers to support filename fields
	IMPORT_C void SetNumPagesInfo(const MFieldNumPagesInfo& aNumPagesInfo); // call if you want headers/footers to support "total number of pages" fields
	inline MFieldFileNameInfo* FileNameFieldInfo()const;
	inline MFieldNumPagesInfo* NumPagesFieldInfo()const;
	//
	void SetPageNumInfo(const MFieldPageNumInfo& aPageNumInfo); // called by CPrintSetup
private:
	CHeaderFooter();
	void CreateFormatLayersL();
	// from MTextFieldFactory
	CTextField* NewFieldL(TUid aFieldType);
private:
	TInt iFirstPageToPrintTo; // relative to the first page being numbered 0
	MFieldFileNameInfo* iFileNameInfo;
	MFieldPageNumInfo* iPageNumInfo;
	MFieldNumPagesInfo* iNumPagesInfo;
	CRichText* iText; // RichText Doc Handle
	CParaFormatLayer* iParaLayer;
	CCharFormatLayer* iCharLayer;
private:
	enum { ETextExists = 0x0001 };
	};


class MPrintProcessObserver
	{
public:
	// PrintProcess calls this once (before printing) to inform observer about the document to be printed.
	// When subclassing add variables to store initialization info. as required
	virtual void NotifyPrintStarted(TPrintParameters aPrintParams)=0;
	//
	// Called by PrintProcess just before each band of a page is printed
	virtual void NotifyBandPrinted(TInt aPercentageOfPagePrinted, TInt aCurrentPageNum, TInt aCurrentCopyNum)=0;
	//
	// Called by PrintProcess on completion of print job
	virtual void NotifyPrintEnded(TInt anErrorCode)=0;
	//
	};


//
// inlines
//
 
inline TInt CHeaderFooter::FirstPageToPrintTo()const
	{ return iFirstPageToPrintTo; }

inline MFieldFileNameInfo* CHeaderFooter::FileNameFieldInfo()const
	{ return iFileNameInfo; }

inline MFieldNumPagesInfo* CHeaderFooter::NumPagesFieldInfo()const
	{ return iNumPagesInfo; }

#endif
