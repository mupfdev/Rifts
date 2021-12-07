// FXCONVRT.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#ifndef __FXCONVRT_H__
#define __FXCONVRT_H__

#include "fximage.h"

class TConvertToImageProgress
	{
public:
	enum TConvertToImageProgressType { EConvertToImageProcessingPage, EConvertToImageFinished };
	//
	TConvertToImageProgressType iConvertToImageProgress;
	TInt iErrorCode;	
	TInt iCurrentPage;
	TInt iFirstPage;
	TInt iLastPage;
	TInt iNextPage;
	};
typedef TPckgBuf<TConvertToImageProgress> TConvertToImageProgressBuf;				

enum Tifftype { Classf=0, Uncompressed=85 };

class CConvertToImage  : public CMsvOperation
	{
public:	
	//
	IMPORT_C static CConvertToImage* CreateTIFFOperationL(CMsvSession& aMsvSession, const TDesC & aReadfile, const TDesC & aWritefile, Tifftype aCompression, TUid aMtm, TMsvId aService, TRequestStatus& aObserverRequestStatus);
	~CConvertToImage();
	//
	const TDesC8& ProgressL();
	//
private:
	void DoCancel();
	void RunL();
	void ProcessPageImageL();
	TInt RunError(TInt aError);
	void Complete(TInt aError);
	//
	void ResetProgress();
	void StoreProgress(TInt aError);
	CConvertToImage(CMsvSession& aMsvSession, TRequestStatus& aObserverRequestStatus);
	void ConstructL(const TDesC & aReadfile, const TDesC & aWritefile, Tifftype aCompression, TUid aMtm, TMsvId aService);
	//
private:
	enum TConvertToImageState { ENextPage, EFinished };
	//
	TInt iCompressionType;
	TInt iState;		
	CPsiFaxStore *iReadStore;
	CMsvTiffStore *iWriteStore;
	TBuf8 < 896+1 > iDataBuf;
	TBuf < 20 > iAnswerback;
	//
	TConvertToImageProgress iProgress;
	TPckgBuf<TConvertToImageProgress> iProgressBuf;
	};

#endif
