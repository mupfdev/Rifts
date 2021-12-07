// COEERROR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COEERROR_H__)
#define __COEERROR_H__

#define KUidConeDllValue8 0x1000004d
const TUid KUidConeDll8={KUidConeDllValue8};

#define KUidConeDllValue16 0x10003a41
const TUid KUidConeDll16={KUidConeDllValue16};

#if defined(_UNICODE)
#define KUidConeDllValue KUidConeDllValue16
const TUid KUidConeDll={KUidConeDllValue};
#else
#define KUidConeDllValue KUidConeDllValue8
const TUid KUidConeDll={KUidConeDllValue};
#endif

enum
	{
	KErrCoeResourceFileDuplicateOffset,
	KErrCoeFailedToReadFromProgDisk
	};

#endif

