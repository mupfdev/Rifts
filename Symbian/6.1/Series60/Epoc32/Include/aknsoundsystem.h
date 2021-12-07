/*
* ============================================================================
*  Name     : AknSoundSystem.h
*  Part of  : Avkon
*
*  Description:
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
// AKNSOUNDSYSTEM.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

// CAknKeySoundSystem - interface for controlling keysounds


#if !defined(__AKNSOUNDSYSTEM_H__)
#define __AKNSOUNDSYSTEM_H__

#include <e32base.h>
#include <w32std.h>

class CAknSoundPlayer;
class CAknKeySoundStack;

class CAknKeySoundSystem : public CBase
	{
public:
	IMPORT_C static CAknKeySoundSystem* NewL(TInt aUid);
	IMPORT_C ~CAknKeySoundSystem();
	IMPORT_C void PushContextL(TInt aResourceId);
	IMPORT_C void PopContext();
	IMPORT_C void PlaySound(const TKeyEvent& aKeyEvent);
	IMPORT_C void PlaySound(TInt aSid);
	IMPORT_C void AddAppSoundInfoListL(TInt aResourceId);
	IMPORT_C void BringToForeground();
    IMPORT_C void StopSound(TInt aSid);
    IMPORT_C void LockContext();
    IMPORT_C void ReleaseContext();

private:
	CAknKeySoundSystem();
	void ConstructL(TInt aUid);
private:
	CAknSoundPlayer* iSoundPlayer;
	TInt iSpare;
	};

#endif
