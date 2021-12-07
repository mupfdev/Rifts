#ifndef __ESTW32_H__
#define __ESTW32_H__

// ESTW32.H
//
// Copyright (c) 1999-1999 Symbian Ltd.  All rights reserved.
//

// EPOC Client interface for accessing Win32 stdin/stdout/stderr

#include <e32std.h>

const TInt Kstdin=0;
const TInt Kstdout=1;
const TInt Kstderr=2;

//
class RWin32Stream : public RSessionBase
	{
public:
	IMPORT_C static void StartServer();
	IMPORT_C TInt Open(TInt aStream);
	IMPORT_C void Read(TRequestStatus& aStatus, TDes8& aDes);
	IMPORT_C void Read(TRequestStatus& aStatus, TDes8& aDes, TInt aLength);
	IMPORT_C void Write(TRequestStatus& aStatus, const TDesC8& aDes);
	IMPORT_C void Write(TRequestStatus& aStatus, const TDesC8& aDes, TInt aLength);
	IMPORT_C void Flush(TRequestStatus& aStatus);
private:
	TInt CheckEOF(TRequestStatus& aStatus);
	};

//
#endif

