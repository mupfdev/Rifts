// MIUTATCH.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//

#if !defined (__MIUTATCH_H__)
#define __MIUTATCH_H__


#if !defined (__S32FILE_H__)
#include <s32file.h>
#endif

const TInt KDataLineBufferLength = 512;
_LIT(KImcvAttachFormatStr, "%S(%d)%S");

enum TImAttachmentFileState
	{ 
	EFileNotOpen, 
	EFileIsOpen, 
	EFileIsClosed,		
	EFileIsCorrupt,		// UU data being decoded is corrupt
	EFileIsIncomplete,	// file write failed
	EFileFailedToOpen	// can't open attach file
	};

class TImAttachmentFile		// utility class to handle file operations with Email attachments
    {
public:
    IMPORT_C TImAttachmentFile(RFs& aFileSession);  // constructor
    IMPORT_C ~TImAttachmentFile();  // destructor

    IMPORT_C TInt MakeDir (const TDesC& aDirPath);
    IMPORT_C TInt OpenFile (const TDesC& aDirPath ,const TDesC& aFileName );
    IMPORT_C TInt CreateFile (const TDesC& aDirPath ,const TDesC& aFileName );
    IMPORT_C TInt ReadFile (TDes8& rBuffer, TInt aNumBytes );
    IMPORT_C TInt WriteFile (const TDesC8& aBuffer);
    IMPORT_C TInt WriteFile (const TDesC16& aBuffer);
    IMPORT_C TInt CloseFile();
	IMPORT_C TInt DeleteAttachment(const TDesC& aDirPath,const TDesC& aFileName);
						
	void AppendValidFile(const TDesC& aDirPath, const TDesC& aFileName, TDes& rFullFilePath);
private:
	void Reset();
	TInt WriteFile ();
    TInt ReadFile ();
	TInt FlushFile();
	TPtrC8 SelectFileData(TInt& abufLen, TInt& aDataLen);

private:
    RFs&		    iFileSession;
	RFile			iFile;
	TFileText		iFileText;
	TFileName		iFullFilePath;
	TBuf8<KDataLineBufferLength>		iDataLine;
	TBool			iWritingToFile;
	TInt			iSpaceOnCache;
	TInt			iPositionInCache;
    };

#endif