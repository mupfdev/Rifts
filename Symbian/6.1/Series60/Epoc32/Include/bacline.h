// BACLINE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __BACLINE_H
#define __BACLINE_H

#ifndef __E32BASE_H
#include <e32base.h>
#endif

// Not available until Platform 003

typedef TBuf<0x100> TBaCommand;

class CCommandLineArguments : public CBase
	{
public:
	// construct/destruct
	IMPORT_C static CCommandLineArguments* NewLC();
	IMPORT_C static CCommandLineArguments* NewL();
	IMPORT_C ~CCommandLineArguments();
	// extract
	IMPORT_C TPtrC Arg(TInt aArg) const;
	IMPORT_C TInt Count() const;
private:
	CCommandLineArguments();
	void ConstructL();
private:
	CArrayFixFlat<TPtrC>* iArgs;
	TBaCommand iCommandLine;
	TFileName iFileName;
	};

#endif
