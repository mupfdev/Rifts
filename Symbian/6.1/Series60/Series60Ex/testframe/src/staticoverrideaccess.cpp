/* Copyright (c) 2001, Nokia. All rights reserved */

#include "staticoverrideaccess.h"
#include "staticoverridehandler.h"

void NStaticOverrideAccess::SetHandler(MStaticOverrideHandler& aHandler)
	{
	Dll::SetTls(&aHandler);
	}


MStaticOverrideHandler* NStaticOverrideAccess::GetHandler()
	{
	return static_cast<MStaticOverrideHandler*>(Dll::Tls());
	}
