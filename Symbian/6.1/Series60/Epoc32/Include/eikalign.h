// EIKALIGN.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKALIGN_H__)
#define __EIKALIGN_H__

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

#if !defined(__GULALIGN_H__)
#include <gulalign.h>
#endif

#if !defined(__GULUTIL_H__)
#include <gulutil.h>
#endif

class CEikAlignedControl : public CCoeControl
	{
public:
	IMPORT_C CEikAlignedControl();
	IMPORT_C ~CEikAlignedControl();
	IMPORT_C void SetAllMarginsTo(TInt aValue);
	IMPORT_C void SetAlignment(TGulAlignmentValue aAlign);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
public:
	TMargins8 iMargin;
	TGulAlignment iAlignment;
	};


#endif
