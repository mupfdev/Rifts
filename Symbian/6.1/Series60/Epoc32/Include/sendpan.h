// SENDPAN.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__SENDPAN_H__)
#define __SENDPAN_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

enum TSendPanic
	{
	ESendAsInvalidMtmIndex=1,
	ESendDifferentMtmAndNameCount=2,
	ESendMtmOrNameExist=3,
	ESendAsMessageAlreadyCreated=4,
	ESendAsIncorrectStateWhenCreatingServiceArray=5,
	ESendAsIncorrectStateWhenCreatingMessage=6,
	ESendAsIncorrectStateWhenAbandoningMessage=7,
	ESendAsIncorrectStateWhenSavingMessage=8,
	ESendAsIncorrectStateForAttachments=9,
	ESendAsIncorrectStateForSubject=10,
	ESendAsIncorrectStateForBody=11,
	ESendActiveWithoutRendering1=12,
	ESendActiveWithoutRendering2=13
	};

GLREF_C void Panic(TSendPanic aPanic);

#endif
