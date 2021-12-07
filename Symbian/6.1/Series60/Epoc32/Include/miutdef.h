// MIUTDEF.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//

//
// This header file defines the bit flags that may be used to instruct
// the CImMessageOperation class how to construct a new Email message
//

#if !defined (__MIUTDEF_H__)
#define __MIUTDEF_H__

typedef TUint TMsvEmailTypeList;

const TMsvEmailTypeList KMsvEmailTypeListMHTMLMessage				= 0x00000001;	// if not set Email is a "normal" (i.e. non-MHTML) Email message
const TMsvEmailTypeList KMsvEmailTypeListInvisibleMessage			= 0x00000002;	// if set, message stays invisible on completion
const TMsvEmailTypeList KMsvEmailTypeListMessageInPreparation		= 0x00000004;	// if set, message stays marked "In preparation" on completion

#endif //MIUTDEF.H

