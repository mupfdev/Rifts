// EIKLAY.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#include <frmtlay.h>

class TAvkonEditorCustomWrap : public MFormCustomWrap
	{
public:
	enum
		{
		EAvkSpaceLineBreakClass=MTmCustom::ELineBreakClasses, // 29
		EAvkLineBreakClasses
		};

public:
	// overrides of line break functions from MFormCustomWrap
	TUint LineBreakClass(TUint aCode,TUint& aRangeStart,TUint& aRangeEnd) const;
	TBool LineBreakPossible(TUint aPrevClass,TUint aNextClass,TBool aHaveSpaces) const;
	};

