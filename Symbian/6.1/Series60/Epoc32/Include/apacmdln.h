// APACMDLN.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__APACMDLN_H__)
#define __APACMDLN_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__APADEF_H__)
#include <apadef.h>
#endif

class CApaCommandLine : public CBase
	{
public:
	// construction/destruction
	IMPORT_C static CApaCommandLine* New(HBufC* aCmdLine);
	IMPORT_C static CApaCommandLine* NewL();
	IMPORT_C static CApaCommandLine* NewL(const TDesC& aCmdLine);
	IMPORT_C static CApaCommandLine* NewLC();
	IMPORT_C static CApaCommandLine* NewLC(const TDesC& aCmdLine);
	IMPORT_C ~CApaCommandLine();
	IMPORT_C void SetReserveLengthL(TInt aMaxLength);

	// operations on the full command line
	IMPORT_C void SetFullCommandLine(HBufC* aCmdLine);
	IMPORT_C void SetFullCommandLineL(const TDesC& aCmdLine);
	IMPORT_C TPtrC FullCommandLine() const;

	// operations on the library name
	IMPORT_C void SetLibraryNameL(const TDesC& aLibName);
	IMPORT_C TPtrC LibraryName() const;

	// operations on the document name
	IMPORT_C void SetDocumentNameL(const TDesC& aDocName);
	IMPORT_C TPtrC DocumentName() const;

	// operations on the tail end
	IMPORT_C void SetTailEndL(const TDesC8& aTailEnd);
	IMPORT_C TPtrC8 TailEnd() const;

	// operations on the command byte
	IMPORT_C void SetCommandL(TApaCommand aCommand);
	IMPORT_C TApaCommand Command() const;
private:
	CApaCommandLine();
	void Parse();
	TPtrC StripQuotes(const TDesC& aDes) const;
	void AddQuotes(TDes& aDes) const;
	TBool FileNameNeedsQuotes(const TDesC& aFileName) const;
	TInt DifferenceIncludingQuotes(TDes& aNewDes, const TDesC& aOldDes) const;
	TBool ReAllocIfNecessaryL(TInt aExtraLengthReqd);
private:
	enum TStateFlags { ELibNamePresent=0x01, ECommandPresent=0x02, EDocNamePresent=0x04,
		               ETailEndPresent=0x08 };
	TInt iStateFlags;
	HBufC* iCmdLine;
	TInt iEndLibNameOffset;
	TInt iEndDocNameOffset;
	TInt iNumQuotes;
	TInt iTailEndLength;
	};

#endif
