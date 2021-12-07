// PRNSETUP.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __PRNSETUP_H__
#define __PRNSETUP_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__FLDBLTIN_H__)
#include <fldbltin.h>
#endif
#if !defined(__PRNINF_H__)
#include <prninf.h>
#endif


// Classes defined //
class CPrintSetup;
//

// Forward Reference
class CPreviewProcess;
class CPrintProcess;
class CPdrModelList;
class CPdrDevice;
class CHeaderFooter;
class TPageSpec;
class RReadStream;
class RWriteStream;
class MPageRegionPrinter;
class RFs;
class CPrinterDriver;
class CPrinterDriverUI;
//


class CPrintSetup : public CBase, private MFieldPageNumInfo
	{
public:
	IMPORT_C static CPrintSetup* NewL();
	IMPORT_C virtual ~CPrintSetup();
	//
	// printer model selection/control functions
	IMPORT_C void AddPrinterDriverDirL(const TDesC& aDriverDir);
	IMPORT_C CPrinterModelList* ModelNameListL(RFs& aFs);
	IMPORT_C void FreeModelList();
	IMPORT_C void CreatePrinterDeviceL(TInt aModelIndex); // requires ModelList to exist
	IMPORT_C void CreatePrinterDeviceL(TUid aModelUid,RFs& aFs);
	IMPORT_C CPrinterDevice* PrinterDevice()const;
	IMPORT_C CPrinterDriverUI* CreatePrinterDriverUIL(); // ownership is transfered to the caller
	//
	// print functions
	IMPORT_C void EndPrint();
	IMPORT_C TInt StartPrintL(const TPrintParameters& aPrintParams,MPageRegionPrinter& aBodyPrinter,
				CPrinterPort* aPort,MPrintProcessObserver* anObserver);
	IMPORT_C TInt StartPreviewPrintL(const TPrintParameters& aPrintParams,MPageRegionPrinter& aBodyPrinter,
				MPrintProcessObserver* anObserver,CGraphicsDevice& aPreviewDev,const TRect& aHeaderRectInPixels,
				const TRect& aFooterRectInPixels,TInt aNumBands);
	//
	// accessors
	inline CHeaderFooter* Header()const;
	inline CHeaderFooter* Footer()const;
	//
	// persistence
	IMPORT_C TStreamId StoreL(CStreamStore& aStore)const;
	IMPORT_C void RestoreL(const CStreamStore& aStore,TStreamId aStreamId,const MFieldFileNameInfo* aFileNameInfo=NULL,const MFieldNumPagesInfo* aNumPagesInfo=NULL,MPictureFactory* aFactory=NULL);
	IMPORT_C void StoreComponentsL(CStreamStore& aStore,CStoreMap& aMap)const;
	IMPORT_C void RestoreComponentsL(const CStreamStore& aStore,const MFieldFileNameInfo* aFileNameInfo=NULL,const MFieldNumPagesInfo* aNumPagesInfo=NULL,MPictureFactory* aFactory=NULL);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	//
private:
	CPrintSetup();
	void ConstructL();
	void DoStartPrintL(const TPrintParameters& aPrintParams,MPageRegionPrinter& aBodyPrinter,MPrintProcessObserver* aObserver,CPrinterPort* aPort);
	void InitializePrintingL(CGraphicsDevice* aPrinterDev,const TPrintParameters& aPrintParams,MPrintProcessObserver* aObserver);
	void InitializePrintingL(const TPrintParameters& aPrintParams,MPrintProcessObserver* aObserver,
									 const TRect& aHeaderRectInPixels,const TRect& aFooterRectInPixels);
	// from MFieldPageNumInfo
	TInt UpdateFieldPageNum()const;
public:
	// Info regarding print setup etc.
	TPageMargins iPageMarginsInTwips;
	TInt iNumOfFirstPage; // value to start page numbering at
private:
	enum {
		ENumberFirstPage = 0x0001,
		};
private:
	CHeaderFooter* iHeader;
	CHeaderFooter* iFooter;
	CPrinterDriver* iPrinterDriver; // the target printer driver
	CPreviewProcess* iPrintProcess;
	CPdrModelList* iModelList;
	MPrintProcessObserver* iPrintObserver;
	TPrintParameters iPrintParams; // not persisted
	CArrayFixSeg<TFileName>* iDriverDirList;
	};


//
// inlines
//

inline CHeaderFooter* CPrintSetup::Header()const
	{ return iHeader; }

inline CHeaderFooter* CPrintSetup::Footer()const
	{ return iFooter; }




#endif
