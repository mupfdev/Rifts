/* Copyright (c) 2001, Nokia. All rights reserved */
#include "clientimagecommander.h"


// Create a new animation object 
EXPORT_C RImageCommander::RImageCommander(RAnimDll &aAnimDll) 
    : RAnim(aAnimDll)
    { 
    }


// Construct a new animation object
EXPORT_C void RImageCommander::ImageConstruct(const RWindowBase& aDevice, TInt aType, const TDesC8& aParams)
    {
    // Send the parameters to the animation server object construction 
    RAnim::Construct(aDevice, aType, aParams);
    }


// Send a command (aCommand) to the animation server object.
// Because there is no way to return an error from the server side using this
// method, it is important that any server side code for these commands should
// not be able to fail or leave.  If the operation can fail, then the method
// TInt CommandReply(TInt aOpcode) should be used instead
EXPORT_C void RImageCommander::ImageCommand(TInt aCommand)
    {
    // Could optionally decode the commands here
    RAnim::Command(aCommand);
    }

