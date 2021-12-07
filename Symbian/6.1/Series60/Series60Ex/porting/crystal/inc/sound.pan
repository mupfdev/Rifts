// Copyright c 2000, Nokia. All rights reserved.

#ifndef __SOUND_H__
#define __SOUND_H__

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
