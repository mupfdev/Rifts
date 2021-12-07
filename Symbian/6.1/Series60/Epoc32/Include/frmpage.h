// FRMPAGE.H
//
// Copyright (c) 1997-1999 Symbian Ltd. All rights reserved.
//

#ifndef __FRMPAGE_H__
#define __FRMPAGE_H__

#include <e32std.h>
#include <e32base.h>
#include <gdi.h>

class MLayDoc;
class CTextLayout;
class CParaFormat;

//
// The following two classes are for internal use only
//

struct TPageLine
	{
	TInt iDocPos;
	TInt iLineHeight;
	TBool iKeepWithNext;
	TBool iStartNewPage;
	};

class TLinePaginator
	{
public:
	TLinePaginator();
	TBool AppendLineL(TPageLine aLine);
 	void FlushL(TInt aEndDocPos);
	void SetPageHeight(TInt aPageHeight);
	void SetArray(CArrayFix<TInt>* aCharsPerPage);
	void Reset();
private:
	void ResetArray();
 	void InsertPageBreakL();
	void SetPotentialBreakPoint(TInt aDocPos);
	void CheckTallLine(TPageLine& aLine);
private:
	CArrayFix<TInt>* iPageList;	 // This is created and destroyed by the application running the paginator.
	TInt iDocPos;
	TBool iKeepWithPrev;
	TInt iPageHeight;
	TInt iHeightRem;
	TBool iBreakOnPage;
	TInt iPrevPageBreak;
	TInt iHeightLines;
	TBool iFirstLine;  // Used to prevent page break being inserted at top of document.
	};


/**
 *
 * An abstract class which specifies the protocol for a pagination
 * observer.
 *
 * A pagination observer may be used when paginating a document in the
 * background (using
 * <code>CTextPaginator::PaginateCompleteDocumentL()</code>). It notifies
 * the client on page completion, document completion, and on errors.The
 * observer is set up using the function
 * <code>CTextPaginator::SetObserver()</code>.
 *
 * @since 5.0
 * @lib ""
 */

class MPaginateObserver
// Abstract	class which must be mixed with application calling the active object.
	{
public:
	
	/**
	 *
	 * Notifies the client on completion of document pagination.
	 *
	 */

	virtual void NotifyCompletion()=0;
	
	/**
	 *
	 * Notifies the client when a leave is trapped or when the pagination is
	 * cancelled.
	 *
	 * Implements error handling.
	 *
	 * @param     "TInt anErrorCode"
	 *            Error code indicates the type of error.
	 */

	virtual void NotifyError(TInt anErrorCode)=0;
	
	/**
	 *
	 * Called by the paginator when each page has been completed.
	 *
	 * @param     "TInt aCurrentPageNum"
	 *            The number of the page.
	 */

	virtual void NotifyPageCompletion(TInt aCurrentPageNum)=0;
	};


/**
 *
 * Paginates a document.
 *
 * Sets the page dimensions, the printer device and the source document
 * to paginate. Uses a page list, which is an array of
 * characters-per-page values.There are two ways of paginating a
 * document; either in the background using an active object or by
 * incrementally adding text to the document and repeatedly notifying the
 * <code>CTextPaginator</code> object to paginate the added text. If an
 * active object is used, the client may be notified on completion of
 * pages, on trapped leaves and on completion of the pagination by an
 * optional pagination observer.
 *
 * @since 5.0
 * @lib "form.lib"
 */

class CTextPaginator : public CActive
	{
public:
// 2 phase ctor: automatically adds self to active scheduler 
	IMPORT_C static CTextPaginator* NewL(CPrinterDevice* aPrinterDevice,CArrayFix<TInt>* aCharsPerPage,TInt aPriority);	
	IMPORT_C ~CTextPaginator();
	IMPORT_C void SetDocumentL(MLayDoc* aLayDoc); // Must call before anything else
	IMPORT_C void SetPrinterDevice(CPrinterDevice* aPrinterDevice);
	IMPORT_C void SetPageSpecInTwips(const TPageSpec& aPageSpec);  // Physical size of page.
	IMPORT_C void SetPageMarginsInTwips(const TMargins& aPageMargins); // Default are all zero.
	IMPORT_C void SetTextMarginWidthsInTwips(TInt aLabelMarginWidth,TInt aGutterMarginWidth); // label margins (if any)
// Called to initiate paginating a document using active object
	IMPORT_C void SetObserver(MPaginateObserver* aObserver);
	IMPORT_C void PaginateCompleteDocumentL();
// Called to paginate incrementally, without active object
	IMPORT_C TInt AppendTextL(TInt& aCumulativeDocPos);	// returns number of page breaks so far
	IMPORT_C TInt PaginationCompletedL();	// called at end of incremental pagination	- returns total number of page breaks
private:
	enum TPaginateMode
		{
		EFPaginateCompleteDocument,
		EFPaginateIncrementally
		};
	enum 
		{
		EPageLineArrayGranularity=10,
		EPageListArrayGranularity=5
		};
	enum
		{
		EFMaximumNumberLinesInBlock=20
		};
private:
	CTextPaginator(TInt aPriority);
	void RunL(); // Active scheduler is friend - can access 
	void DoCancel();  // Called by CActive::Cancel()
	void ConstructL(CPrinterDevice* aPrinterDevice,CArrayFix<TInt>* aCharsPerPage);
	void SetLayoutDimensions();
	void SetOrReplaceDocumentL(MLayDoc* aLayDoc);
	TRect TextRectInTwips() const;
	TSize TextSizeInPixels() const;
	TBool TrapPaginateParagraphL();
	TBool PaginateParagraphL();
	void PageCompleted();
	void Reque();
	void ResetPaginator();
	void CopyTempPageListL();  // Copies temporary page list to real one.
	void LeaveL(TInt aErr);
private:
	MLayDoc* iLayDoc;
	MPaginateObserver* iObserver;
	CPrinterDevice* iPrinterDevice;
	TLinePaginator iPaginator;
	CTextLayout* iLayout;
	CArrayFix<TInt>* iPageList;
	CArrayFixFlat<TInt>* iTempPageList;
	CArrayFixFlat<TPageLine>* iPageLineArray;
	TSize iPageSizeInTwips;
	TMargins iPageMarginsInTwips;
	TInt iGutterMarginWidthInTwips;   // Gap between labels and text proper - in twips
	TInt iLabelMarginWidthInTwips;
	TInt iDocPos;				// Within the laydoc
	TBool iPageBreakChar;
	TPaginateMode iMode;
	};

#endif
