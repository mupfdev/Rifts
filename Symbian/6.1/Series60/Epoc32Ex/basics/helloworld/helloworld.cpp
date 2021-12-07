// HelloWorld.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

#include "CommonFramework.h"

// do the example
LOCAL_C void doExampleL()
    {
	_LIT(KHelloWorldText,"Hello world!\n");
	console->Printf(KHelloWorldText);
	}
