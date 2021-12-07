// COESNDPY.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COESNDPY_H__)
#define __COESNDPY_H__

#include <e32std.h>

class TBaSystemSoundType;
class CCoeSoundPlayerManager;

/**
 * Utility class for simple sound playing.
 * Must be used in the same thread as an active cone environment (CCoeEnv).
 */
class CoeSoundPlayer
	{
public:
	enum { ENoRepeat=1, ERepeatForever=KMaxTInt};
public:
	inline static void PlaySound(const TBaSystemSoundType& aType);
	inline static void PlaySound(const TBaSystemSoundType& aType,TInt aPlayCount,TTimeIntervalMicroSeconds32 aGap);
	inline static void PlaySoundNow(const TBaSystemSoundType& aType);
	inline static void PlaySoundNow(const TBaSystemSoundType& aType,TInt aPlayCount,TTimeIntervalMicroSeconds32 aGap);
	IMPORT_C static void CancelSound(const TBaSystemSoundType& aType);
private:
	IMPORT_C static void PlaySound(const TBaSystemSoundType& aType,TInt aPlayCount,
											TTimeIntervalMicroSeconds32 aGap,TBool aInterrupt);
	static CCoeSoundPlayerManager* ManagerL();
	};

inline void CoeSoundPlayer::PlaySound(const TBaSystemSoundType& aType)
	{CoeSoundPlayer::PlaySound(aType,ENoRepeat,TTimeIntervalMicroSeconds32(),EFalse);}
inline void CoeSoundPlayer::PlaySound(const TBaSystemSoundType& aType,TInt aPlayCount,TTimeIntervalMicroSeconds32 aGap)
	{CoeSoundPlayer::PlaySound(aType,aPlayCount,aGap,EFalse);}
inline void CoeSoundPlayer::PlaySoundNow(const TBaSystemSoundType& aType)
	{CoeSoundPlayer::PlaySound(aType,ENoRepeat,TTimeIntervalMicroSeconds32(),ETrue);}
inline void CoeSoundPlayer::PlaySoundNow(const TBaSystemSoundType& aType,TInt aPlayCount,TTimeIntervalMicroSeconds32 aGap)
	{CoeSoundPlayer::PlaySound(aType,aPlayCount,aGap,ETrue);}

#endif
