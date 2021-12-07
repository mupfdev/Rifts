/*
* ============================================================================
*  Name     : CAknExEditorScenarioManager
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/


// INCLUDE FILES
#include <E32Std.h>
#include <eikapp.h>
#include "AknExEditorScenarioManager.h"
#include <eikenv.h>
#include <aknexeditor.rsg>

// count of scenario.
//const TInt  KMaxCount   = 14;

#define KMaxTitleLength      32
// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExEditorScenarioManager::CAknExEditorScenarioManager()
    {
    // Initialize scenario.
    // this is TEST code. this should be changed.
    TInt scenario[] = {1,4,5,6,7,9,21,22,23,25,30,33};
    iScenarioCount = sizeof(scenario) / sizeof scenario[0];

    for (TInt i = 0; i < iScenarioCount; i++)
        {
        iScenario[i]  = scenario[i];
        }
    }

// EPOC default constructor can leave.
void CAknExEditorScenarioManager::ConstructL()
    {
    }

// Two-phased constructor.
CAknExEditorScenarioManager* CAknExEditorScenarioManager::NewL()
    {
    CAknExEditorScenarioManager* self =
                         new (ELeave) CAknExEditorScenarioManager;
    
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

    
// Destructor
CAknExEditorScenarioManager::~CAknExEditorScenarioManager()
    {
    }


// ---------------------------------------------------------
// CAknExEditorScenarioManager::FirstViewId()
// returns Uid of the view in first scenario.
// (other items were commented in a header).
// ---------------------------------------------------------
//
TUid CAknExEditorScenarioManager::FirstViewId()
    {
    return TUid::Uid(iScenario[0]);
    }

// ---------------------------------------------------------
// CAknExEditorScenarioManager::LastViewId()
// returns Uid of the view in last scenario.
// (other items were commented in a header).
// ---------------------------------------------------------
//
TUid CAknExEditorScenarioManager::LastViewId()
    {
    return TUid::Uid(iScenario[iScenarioCount - 1]);
    }

// ---------------------------------------------------------
// CAknExEditorScenarioManager::NextViewTo(TUid aUid)
// returns Uid of next view to specified view.
// (other items were commented in a header).
// ---------------------------------------------------------
//
TUid CAknExEditorScenarioManager::NextViewTo(TUid aUid)
    {
    for (TInt i = 0; i < iScenarioCount - 1; i++)
        {
        if (aUid == TUid::Uid(iScenario[i]) )
            {
            return TUid::Uid(iScenario[i + 1]);
            }
        }
        return TUid::Uid(KScenarioNotFound);
    }

// ---------------------------------------------------------
// CAknExEditorScenarioManager::PrevViewTo(TUid aUid)
// returns Uid of previous view to specified view.
// (other items were commented in a header).
// ---------------------------------------------------------
//
TUid CAknExEditorScenarioManager::PrevViewTo(TUid aUid)
    {
    for (TInt i = 1; i < iScenarioCount; i++)
        {
        if (aUid == TUid::Uid(iScenario[i]) )
            {
            return TUid::Uid(iScenario[i - 1]);
            }
        }
        return TUid::Uid(KScenarioNotFound);

    }

// ---------------------------------------------------------
// CAknExEditorScenarioManager::GetTitle(TUid aUid, Tbuf<>* aTitle)
// returns title string of the view.
// (other items were commented in a header).
// ---------------------------------------------------------
//
void CAknExEditorScenarioManager::GetTitle(
                        TUid aUid, TBuf<KTitleBufLength>* aTitle)
    {

    TInt i;
    TBuf<KMaxTitleLength> normalTitle;
    TBuf<KMaxTitleLength> abnormalTitle;
    CEikonEnv::Static()->ReadResource(normalTitle, R_AKNEXEDITOR_EDITOR_NORMAL_TITLE);
    CEikonEnv::Static()->ReadResource(abnormalTitle, R_AKNEXEDITOR_EDITOR_ABNORMAL_TITLE);
    for (i = 0; i < iScenarioCount; i++)
        {
        if (aUid == TUid::Uid(iScenario[i]))
            {
            aTitle->Format(normalTitle, iScenario[i]);
            return;
            }
        }
        aTitle->Format(abnormalTitle, iScenario[i]);
    }

//  End of File  
