// PolymorphicDLL2.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

#ifndef __PolymorphicDLL2_H
#define __PolymorphicDLL2_H

// get definition of base class
#include "UsingDLLS.h"

class CGermanMessenger : public CMessenger
  	{
public:
	// constructor support
	virtual void ConstructL(CConsoleBase* aConsole, const TDesC& aName);
	// destructor
	virtual ~CGermanMessenger();
	// useful functions
	virtual void ShowMessage();
	};

#endif
