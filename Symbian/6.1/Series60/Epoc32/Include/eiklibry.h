// EIKLIBRY.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKLIBRY_H__)
#define __EIKLIBRY_H__

#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__EIKFCTRY_H__)
#include <eikfctry.h>
#endif

typedef SEikControlInfo (*TCreateByTypeFunction)(TInt);

// Abstract base class specifying the interface for a dynamically-loaded DLL
// which goes on to configure other Uikon statically-loaded DLLs.
class CEikLibrary : public CBase
	{
public:
	// When EikEnv dynamically loads a DLL, it calls its InitializeL function
	// which will set up any variables which EikEnv requires. 
	virtual void InitializeL() = 0;
	// These functions give the EikEnv access to the libraries
	// resources and Control Factories. 
	virtual CArrayFix<TFileName>*				ResourceFileArrayL() const = 0;
	virtual CArrayFix<TCreateByTypeFunction>*	ControlFactoryArrayL() const = 0;
	IMPORT_C virtual void PostAppUiInitializeL();
	};

#endif
