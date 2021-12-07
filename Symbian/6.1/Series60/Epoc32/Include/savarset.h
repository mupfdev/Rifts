// SAVARSET.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __SAVARSET_H__
#define __SAVARSET_H__

#include <e32base.h>
#include "saclient.h"

class RSAVarChangeNotify : public RSystemAgentBase
 	{
public:
	IMPORT_C RSAVarChangeNotify();    
	IMPORT_C void NotifySaVarChangeL(const TUid aVariable, const TInt aState);	
	IMPORT_C TInt ReleaseVariable(TUid aVariable);
	};

#endif