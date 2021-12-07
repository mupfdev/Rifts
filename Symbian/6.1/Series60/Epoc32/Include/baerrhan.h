// BAERRHAN.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Started by DWW, May 1997
// Error handler
//

#if !defined(__BAERRHAN_H__)
#define __BAERRHAN_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#ifdef _UNICODE
#define KUidBaflErrorHandlerValue KUidBaflErrorHandlerValue16
#define KUidBaflErrorHandler KUidBaflErrorHandler16
#else
#define KUidBaflErrorHandlerValue KUidBaflErrorHandlerValue8
#define KUidBaflErrorHandler KUidBaflErrorHandler8
#endif

const TInt KUidBaflErrorHandlerValue8=0x10000257;
const TUid KUidBaflErrorHandler8={KUidBaflErrorHandlerValue8};
const TInt KUidBaflErrorHandlerValue16=0x10003A13;
const TUid KUidBaflErrorHandler16={KUidBaflErrorHandlerValue16};


enum TErrorHandlerResponse
	{
	EErrorNotHandled,
	ENoDisplay,
	EAlertDisplay,
	EInfoDisplay
	};

class CBaErrorHandler : public CBase
	{ // deliberately *not* mixable - else couldn't be freely cast
public:
	virtual TErrorHandlerResponse HandleError(TDes& aErrorText,TDes& aContextText)=0;
	inline static TErrorHandlerResponse CallBack(TInt aErrorNumber,TDes& aErrorText,TDes& aContextText);
	};

inline TErrorHandlerResponse CBaErrorHandler::CallBack(TInt aErrorNumber,TDes& aErrorText,TDes& aContextText)
	{
	return((CBaErrorHandler*)(aErrorNumber))->HandleError(aErrorText,aContextText);
	}

#endif
