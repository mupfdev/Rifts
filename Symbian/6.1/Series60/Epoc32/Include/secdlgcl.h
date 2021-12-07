// SECDLGCL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Security Dialog Server Client Header

#ifndef __SECDLGCL_H__
#define __SECDLGCL_H__

#include <e32std.h>

enum TSecurityAlertEnum { EGeneralAlert, EUnsupportedAlg, EUnsupportedVersion };

class CX509Certificate;
class RSecurityDialogServer : public RSessionBase
	{
public:
	IMPORT_C RSecurityDialogServer();
	IMPORT_C ~RSecurityDialogServer();
	IMPORT_C TVersion Version() const;
	IMPORT_C TInt Connect();
//pg 16/02/2000 Port to new certman api
	IMPORT_C void DisplayCertNotTrustedDlg(TBool& aBool,const CX509Certificate& aCert,TRequestStatus& aStatus);
//	IMPORT_C void DisplayCertNotTrustedDlg(TBool& aBool,TCertInfo& aCert,TRequestStatus& aStatus);
	IMPORT_C void DisplayAlertDialog(TSecurityAlertEnum aAlert,TRequestStatus& aStatus);
	IMPORT_C TInt Cancel();
private:
	RNotifier* iNotifier;
	TPtr8 iProceed;
	};

IMPORT_C TInt StartDialogThread();

#endif
