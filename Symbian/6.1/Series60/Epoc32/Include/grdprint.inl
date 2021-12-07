// GRDPRINT.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

inline void CGridPrinter::SetRealPrintingDeviceMap(const MGraphicsDeviceMap* aGraphicsDeviceMap)
	{
	iGraphicsDeviceMap=aGraphicsDeviceMap;
	}

inline CGridLay& CGridPrinter::GridLay()
	{
	return *iGridLay;
	}
