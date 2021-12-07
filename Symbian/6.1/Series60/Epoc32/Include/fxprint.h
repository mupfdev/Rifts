// FXPRINT.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__FXPRINT_H__)
#define __FXPRINT_H__

#if !defined(__GDI_H__)
#include <gdi.h>
#endif

#if !defined(__FAXDEF_H__)
#include <faxdefn.h>
#endif


const TUid KFaxPrinterModelUid    = {0x10004350};
const TInt KFaxPrinterModelUidVal =  0x10004350;

const TUid KFaxPrintPdlUid    = {0x1000434F};
const TInt KFaxPrintPdlUidVal = 0x1000434F;

class CFaxPrinterDevice : public CPrinterDevice
	{
public:
	virtual void SetOutputFileNameL(const TDesC& aFileName)=0;
	virtual const TDesC& OutputFileName() const=0;
	virtual void SetResolutionL(TFaxResolution aResolution)=0;
	virtual TFaxResolution Resolution() const=0;
	virtual void SetMessagingInitiated(TBool aResolution)=0;
	virtual TBool MessagingInitiated() const=0;
	};

#endif

