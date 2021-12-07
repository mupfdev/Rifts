// GRDPRINT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__GRDPRINT_H__)
#define __GRDPRINT_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__GRDSTD_H__)
#include <grdstd.h>
#endif


class CGridPrinter : public CBase, public MPageRegionPrinter
	{
public:
	IMPORT_C static CGridPrinter* NewL(CGridLay* aGridLay,CGridLabelImg* aPrintLabelImg,
		CGridCellImg* aPrintCellImg,TZoomFactor* aZoomFactor);
	IMPORT_C virtual ~CGridPrinter();
	inline void SetRealPrintingDeviceMap(const MGraphicsDeviceMap* aGraphicsDeviceMap);
	IMPORT_C void SetTopLeftMargin(const TPoint& aTlMarginInTwips);
	IMPORT_C void SetPageSizeInTwipsL(const TSize& aSizeInTwips);
	IMPORT_C void PaginateL();
	inline CGridLay& GridLay();
public:	// from MPageRegionPrinter
	IMPORT_C virtual void PrintBandL(CGraphicsDevice* aDevice,TInt aPageNo,const TBandAttributes& aBandInPixels);
private:
	CGridPrinter(CGridLabelImg* aPrintLabelImg,CGridCellImg* aPrintCellImg,TZoomFactor* aZoomFactor);
	void ConstructL(CGridLay* aGridLay);
	void SetGdMapAndPushLabelImgLC();
private:
	CGridLay* iGridLay;
	CGridImg* iGridImg;
	CGridLabelImg* iPrintLabelImg;
	CGridCellImg* iPrintCellImg;
	TZoomFactor* iZoomFactor;
	const MGraphicsDeviceMap* iGraphicsDeviceMap;
	TPoint iTlMarginInTwips;
	TRect iPrintablePage;
	TInt iScaleFactor;
	};

#include <grdprint.inl>
#endif


