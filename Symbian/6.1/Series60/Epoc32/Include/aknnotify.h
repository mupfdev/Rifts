/*
* ============================================================================
*  Name     : AknNotify.h
*  Part of  : Avkon
*
*  Description:
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
#ifndef __AKNNOTIFY_H__
#define __AKNNOTIFY_H__

#include <e32base.h>


class CAknNotifyBase : public CBase
    {
public:
	IMPORT_C ~CAknNotifyBase();

protected:
	CAknNotifyBase(TUid aUid);
	void ConstructL();
	void StartOrUpdateL(const TDesC8& aBuffer,TDes8& aResponse);
	void StartOrUpdateAndGetResponseL(TRequestStatus& aStatus,const TDesC8& aBuffer,TDes8& aResponse);
private:
	IMPORT_C void CAknNotifyBase_Reserved();

private:
	TUid iUid;
	TBool iStarted;
	RNotifier iNotify;
	TInt iSpare;
    };


#endif
