// EIKFORM.PAN
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKFORM_PAN__)
#define __EIKFORM_PAN__

enum TEikFormPanic
	{
	EEikFormPanicUnknownControlType,
	EEikFormPanicNoSuchControl,
	EEikFormPanicUnknownGetAutoType,
	EEikFormPanicFocusableLineWithIdZero,
	EEikFormPanicSettingDoublePageFormLayoutOnNonForm,
	EEikFormPanicLayoutErrorUnknownControlType
	};

GLREF_C void Panic(TEikFormPanic aPanic);

#endif

