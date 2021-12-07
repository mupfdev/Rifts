// IMCVDATA.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//

// definitions of hard-coded data required by the RFC822 protocol

#if !defined ( __IMCVDATA_H__ )
#define __IMCVDATA_H__

#if !defined (__E32STD_H__)
#include <e32std.h>
#endif

// max SMTP line length is actually 1001 but this includes a CR
// so allow 1024 characters to be nice to the memory allocator.

const TInt KMaxIMailHeaderReadLineLength  = 1024;
const TInt KMaxIMailHeaderWriteLineLength  = 76;
const TInt KMaxIMailBodyLineLength = 79;

// From RFC 1521, (Boundaries) must be no longer than 70 characters.
// Including beginning and end "--" lets check for 74.
const TInt KMaxBoundaryTextLength = 74;


enum TMimeContentType {		EMimeUnknownContent=0, 
							EMimeText, 
							EMimeMessage, 
							EMimeMultipart, 
							EMimeImage, 
							EMimeApplication, 
							EMimeAudio, 
							EMimeVideo,
							EMimeTextDirectory };


#endif 
