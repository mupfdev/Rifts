// IMUTDLL.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//

#if !defined (__IMUTDLL_H__)
#define __IMUTDLL_H__

#if !defined (__E32STD_H__)
#include <e32std.h>
#endif

#if !defined (__BARSC_H__)
#include <barsc.h>		// RResourceFile
#endif

_LIT(KImutDllName,"IMUT");

enum TImutErrorReason {	KPanicNoRfc822Header = 1,
						KPanicNoRichText,
						EPanicNullTokenizer,
						KPanicBoundaryTooLong,
						KPanicUnknownSendingMethod,
						KPanicInvalidSMTPLine,
						KPanicAttachmentPathNotSet,
						KPanicNoMimeClassAvailable,
						KPanicUnknownAlgorithm,
						KPanicSetAlgorithmLNotCalled,
						KPanicNoResourceFile,
						KPanicDescriptorToSmall,
						KPanicReadLengthTooLarge,
						KPanicFileNotFlushed,
						KPanicEntryIsNotMessage,
						KPanicMessageEntryNotCalled,
						KPanicMessageEntryIdHasChanged,
						KPanicServiceIdNotValid,
						KPanicIncorrectResetState,
						KPanicNoMimeHeader,
						KPanicInvalidDefaultCharacterSet,
						KPanicUnknownFolderType,
						KPanicInvalidEncodingType,
						EPanicInvalidHeaderState,
						EImskSocketNotConnected,
						EImskSocketStillActive,
						EImskSocketOpen,
						EImskUnknownState,
						EImskInvalidPortNumber,
						EImskInvalidSocketEncryptionMethod,
						EImskSecurityFailed,
						EImskDatabaseTypeUnspecified,
						EImskNotSupported,
	 					EImskUnknownBearer
						};

// and some error codes
const TInt KErrCorruptHeader = 1;

GLDEF_C void gPanic( TImutErrorReason aReason );

GLREF_C void OpenResourceFileL(RResourceFile& aFile, RFs& anFs);

GLDEF_C void CloseResourceFile( TAny* aResourceFile );


#endif