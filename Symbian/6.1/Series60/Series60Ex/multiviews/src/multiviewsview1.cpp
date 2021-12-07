/* Copyright (c) 2002, Nokia. All rights reserved */

#include <aknviewappui.h>
#include <aknconsts.h>
#include <MultiViews.rsg>

#include "MultiViewsView1.h"
#include "MultiViewsContainer1.h"
#include "MultiViews.hrh"

CMultiViewsView1* CMultiViewsView1::NewL()
    {
    CMultiViewsView1* self = CMultiViewsView1::NewLC();
    CleanupStack::Pop(self);
    return self;
    }

CMultiViewsView1* CMultiViewsView1::NewLC()
    {
    CMultiViewsView1* self = new (ELeave) CMultiViewsView1();
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

CMultiViewsView1::CMultiViewsView1()
    {
    // no implementation required
    }

CMultiViewsView1::~CMultiViewsView1()
    {
    //  DoDeactivate is called by the base class destructor
    }

void CMultiViewsView1::ConstructL()
    {
    BaseConstructL(R_MULTIVIEWS_VIEW1);
    }


TUid CMultiViewsView1::Id() const
    {
    return TUid::Uid(EMultiViewsView1Id);
    }

void CMultiViewsView1::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
                                    TUid /*aCustomMessageId*/,
                                    const TDesC8& /*aCustomMessage*/)
    {
    ASSERT(iContainer == NULL);
    iContainer = CMultiViewsContainer1::NewL(ClientRect());
    }

void CMultiViewsView1::DoDeactivate()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        delete iContainer;
        iContainer = NULL;
        }
    }

void CMultiViewsView1::HandleCommandL(TInt aCommand)
    {
    if (aCommand == EMultiViewsSwitchToView2)
        {
        AppUi()->ActivateLocalViewL(TUid::Uid(EMultiViewsView2Id));
        }
    else
        {
        AppUi()->HandleCommandL(aCommand);
        }
    }
