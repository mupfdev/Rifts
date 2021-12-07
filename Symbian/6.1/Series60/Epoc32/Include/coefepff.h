// COEFEPFF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COEFEPFF_H__)
#define __COEFEPFF_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

class CCoeFepParameters;
class CCoeFep;

IMPORT_C CCoeFep* NewFepL(CCoeEnv& aConeEnvironment, const TDesC& aFullFileNameOfDll, const CCoeFepParameters& aFepParameters);
IMPORT_C void SynchronouslyExecuteSettingsDialogL(CCoeEnv& aConeEnvironment, const TDesC& aFullFileNameOfDll);
IMPORT_C void Reserved_1();
IMPORT_C void Reserved_2();
IMPORT_C void Reserved_3();
IMPORT_C void Reserved_4();
IMPORT_C void Reserved_5();
IMPORT_C void Reserved_6();
IMPORT_C void Reserved_7();
IMPORT_C void Reserved_8();

#endif

