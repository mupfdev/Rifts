// ES_INI.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__ES_INI_H__)
#define __ES_INI_H__

#include <e32base.h>

#define ESOCK_INI_DATA _L("esock.ini")

class CESockIniData : public CBase 
	{
public:
	IMPORT_C static CESockIniData* NewL(const TDesC& aName=ESOCK_INI_DATA);
	IMPORT_C virtual ~CESockIniData();
	IMPORT_C TBool FindVar(const TDesC &aVarName, TPtrC &aResult);
	IMPORT_C TBool FindVar(const TDesC &aVarName, TInt &aResult);
	IMPORT_C TBool FindVar(const TDesC &aSection,const TDesC &aVarName,TPtrC &aResult);
	IMPORT_C TBool FindVar(const TDesC &aSection,const TDesC &aVarName,TInt &aResult);
	IMPORT_C TInt WriteVar(const TDesC& aSection,const TDesC& aVarName,TInt aValue);
	IMPORT_C TInt WriteVar(const TDesC& aSection,const TDesC& aVarName,const TDesC& aValue);
	IMPORT_C void CommitL();
protected:
	IMPORT_C CESockIniData();
	IMPORT_C void ConstructL(const TDesC& aName);
protected:
	HBufC* iName;
	HBufC* iToken;
	TPtr iPtr;
	};

#endif
