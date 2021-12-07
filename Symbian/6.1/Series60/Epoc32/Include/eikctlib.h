// EIKCTLIB.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKCTLIB_H__)
#define __EIKCTLIB_H__

#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__EIKLIBRY_H__)
#include <eiklibry.h>
#endif

#if !defined(__EIKBGFTY_H__)
#include <eikbgfty.h>
#endif

/**
 * The CEikCtlLibrary class proovides static functions called by CEikDllInitializer; setting EikCtl
 * library resources in Cone and giving access to its controls via ControlFactoryFuncArray() in EikonEnv
 *
 * @internal
 */
class CEikCtlLibrary : public CBase
	{
public:
	IMPORT_C static TFileName ResourceFile();
	IMPORT_C static TCreateByTypeFunction ControlFactory();
	IMPORT_C static void InitializeL();
	IMPORT_C static TCreateButtonGroupByTypeFunction ButtonGroupFactory();
public:
	static SEikControlInfo CreateByTypeL(TInt aControlId);
	static MEikButtonGroup* CreateButtonGroupByTypeL(TInt aButtonGroupType,EikButtonGroupFactory::TCreationData& aCreationData,TBool& aAddToButtonGroupStack);
private:
	CEikCtlLibrary();
	};

#endif