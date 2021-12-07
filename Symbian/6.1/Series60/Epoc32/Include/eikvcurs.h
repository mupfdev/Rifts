// eikvcurs.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

//
// class TEikVirtualCursor
//

#ifndef __EIKVCURS_H__
#define __EIKVCURS_H__

#include <e32std.h>


/**
 * The TEikVirtualCursor class provides support for
 * the states which a virtual cursor may be in within an application.
 * There is one instance of this object per CEikonEnv.
 *
 * @since Uikon1.2
 */
class TEikVirtualCursor
	{
public:
	enum TState
		{
		EOff=0,
		EOn,
		ESuspended
		};
public:
	TEikVirtualCursor();
private: //prevent passing by value
	inline TEikVirtualCursor(const TEikVirtualCursor&);
public:
	IMPORT_C void SetCursorStateL(TState aState, CCoeEnv& aEnv);
	IMPORT_C TState CursorState(CCoeEnv& aEnv);
public: // but not exported
	void HandleAppToForeground(CCoeEnv& aEnv);
private:
	void SwitchOffEmulationAndBitmap(CCoeEnv& aEnv);
	void SwitchOnEmulationAndBitmap(CCoeEnv& aEnv);
private:
	TState iState;
	TInt iSpare;
	};


// inlines

inline TEikVirtualCursor::TEikVirtualCursor(const TEikVirtualCursor&)
	{}

#endif
