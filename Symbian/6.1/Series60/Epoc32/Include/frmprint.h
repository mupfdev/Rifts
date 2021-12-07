// FRMPRINT.H
//
// Copyright (c) 1997-1999 Symbian Ltd. All rights reserved.
//

#ifndef __FRMPRINT_H__
#define __FRMPRINT_H__

#include <e32std.h>
#include <frmtlay.h>

class CTextPageRegionPrinter : public CBase	, public MPageRegionPrinter 
	{
public:
	IMPORT_C static CTextPageRegionPrinter* NewL(MLayDoc* aLayDoc,CPrinterDevice* aPrinterDevice);
	IMPORT_C ~CTextPageRegionPrinter();
	IMPORT_C void SetPageList(const CArrayFix<TInt>* aPageList);
	IMPORT_C void SetPrinterDevice(CPrinterDevice* aPrinterDevice);
	IMPORT_C void SetDocument(MLayDoc *aDoc); // Used for replacing document
	IMPORT_C void SetPrintPreview(TBool aPrintPreview);
	IMPORT_C void SetPageSpecInTwips(const TPageSpec& aPageSpec);  // Physical size of page.
	IMPORT_C void SetPageMarginsInTwips(const TMargins& aPageMargins); // Default are all zero.
	IMPORT_C void SetTextMarginWidthsInTwips(TInt aLabelMarginWidth,TInt aGutterMarginWidth); // label margin &c (if any)
	IMPORT_C void SetFirstPageOfDoc(TInt aFirstPage);	// possible offset depending on document - Default is 1
	IMPORT_C void PrintBandL(CGraphicsDevice* aLayoutDevice,TInt aPageNo
															,const TBandAttributes& aBandInPixels);
	IMPORT_C void SetParagraphFillTextOnly(TBool aFillTextOnly);
private:
	CTextPageRegionPrinter();
	void ConstructL(MLayDoc* aLayDoc,CPrinterDevice* aPrinterDevice);
	void PrintBand2L(CGraphicsDevice* aLayoutDevice,TInt aPageNo,const TBandAttributes& aBandInPixels);
	void SetFormatAndImageDevicesL();
	void SetPageL(TInt aNextPage);
	TRect ViewRectInTwips() const;
	TInt LayoutWidthInTwips() const;
	TInt LabelMarginWidthInPixels() const;
	TInt TextStartXInPixels() const;
	void SetPageTextHeight();
	void LeaveL(TInt aErr);
private:
	CTextLayout* iLayout; // 'HAS' relationship
	CPrinterDevice* iPrinterDevice;
	CGraphicsDevice* iImageDevice;
	CGraphicsContext* iGc;
	CGraphicsContext* iPictureGc;
	TDrawTextLayoutContext iDrawTextLayoutContext;
	const CArrayFix<TInt>* iPageList;	// 'USES' relationship. Destroyed by application
	TSize iPageSizeInTwips; // In Twips
	TMargins iPageMarginsInTwips;	// In twips
	TInt iGutterMarginWidthInTwips;   // Gap between labels and text proper - in twips
	TInt iLabelMarginWidthInTwips;	   // In twips
	TInt iCurrentPage;
	TInt iFirstPage;
	TInt iTopPageDocPos;
	TInt iPageTextHeightInPixels; 
	TBool iPrintPreview;
	};

#endif
