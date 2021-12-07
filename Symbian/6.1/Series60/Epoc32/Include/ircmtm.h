// IrCMTM.CPP
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#if !defined (__IRCMTM_H__)
#define __IRCMTM_H__

#include <obexClientMtm.h>
#include <obexMtmUtil.h>
	

const TInt32 KUidMsgTypeIr = 0x100053A4;


class CIrClientMtm : public CObexClientMtm
	{
public:
	IMPORT_C static CIrClientMtm* NewL(CRegisteredMtmDll& aRegisteredMtmDll, CMsvSession& aMsvSession);

	enum TAsyncCmds
		{
		EIrcCmdSend
		};

	// --- RTTI functions ---
	CMsvOperation* InvokeAsyncFunctionL(TInt aFunctionId,const CMsvEntrySelection& aSelection, TDes8& aParameter, TRequestStatus& aCompletionStatus);

private:
	CIrClientMtm(CRegisteredMtmDll& aRegisteredMtmDll, CMsvSession& aMsvSession);
	};



#endif // __IRCMTM_H__
