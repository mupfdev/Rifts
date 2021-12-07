/* Copyright (c) 2002, Nokia. All rights reserved */

#include <aknviewappui.h>
#include <aknconsts.h>
#include <aknnotewrappers.h>
#include <MultiViews.rsg>

#include "MultiViewsView2.h"
#include "MultiViewsContainer2.h"
#include "MultiViews.hrh"

CMultiViewsView2* CMultiViewsView2::NewL()
    {
    CMultiViewsView2* self = CMultiViewsView2::NewLC();
    CleanupStack::Pop(self);
    return self;
    }

CMultiViewsView2* CMultiViewsView2::NewLC()
    {
    CMultiViewsView2* self = new (ELeave) CMultiViewsView2();
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

CMultiViewsView2::CMultiViewsView2()
    {
    // no implementation required
    }

CMultiViewsView2::~CMultiViewsView2()
    {
    //  DoDeactivate is called by the base class destructor
    }

void CMultiViewsView2::ConstructL()
    {
    BaseConstructL(R_MULTIVIEWS_VIEW2);
    }


TUid CMultiViewsView2::Id() const
    {
    return TUid::Uid(EMultiViewsView2Id);
    }

void CMultiViewsView2::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
                                    TUid /*aCustomMessageId*/,
                                    const TDesC8& /*aCustomMessage*/)
    {
    ASSERT(iContainer == NULL);
    iContainer = CMultiViewsContainer2::NewL(ClientRect());
    }

void CMultiViewsView2::DoDeactivate()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        delete iContainer;
        iContainer = NULL;
        }
    }

void CMultiViewsView2::HandleCommandL(TInt aCommand)
    {   
    if (aCommand == EMultiViewsCommand1)
        {
        _LIT(message,"Hello");
        CAknInformationNote* informationNote = new (ELeave) CAknInformationNote;
        informationNote->ExecuteLD(message);
        }
    else if (aCommand == EMultiViewsSwitchToView1)
        {
        AppUi()->ActivateLocalViewL(TUid::Uid(EMultiViewsView1Id));
        }
    else 
        {
        AppUi()->HandleCommandL(aCommand);
        }
    }
