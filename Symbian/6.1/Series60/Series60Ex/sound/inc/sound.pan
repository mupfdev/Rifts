// Copyright (c) 2001, Nokia. All rights reserved.

#ifndef __SOUND_H__
#define __SOUND_H__

/** Panic Category */
_LIT(KSound, "Sound");
_LIT(KPlayerAdapter, "CPlayerAdapter");
_LIT(KRecorderAdapter, "CRecorderAdapter");
_LIT(KToneAdapter, "CToneAdapter");

/** Sound application panic codes */
enum SoundPanics
	{
    /** Use 200 as the base for panics so that they are well above all Epoc panic codes.*/
    KSoundPanicInvalidState = 200, 
    KSoundPanicBadParameter, 
    KSoundPanicInvariant,
    KSoundPanicInvalidMdaState,
    KSoundPanicUnexpectedCommand
	};

#endif    // __SOUND_H__
