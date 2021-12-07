/* Copyright (c) 2002, Nokia. All rights reserved */

#include <eiklabel.h>
#include <bt_sock.h>

#include "BTDiscoveryAppView.h"
#include "BTAttributeValueLister.h"
#include "BTDiscovery.pan"

const TInt KMaxLineLength = 40;
const TInt KGranularityOfArray = 10;

CBTDiscoveryAppView* CBTDiscoveryAppView::NewL(const TRect& aRect)
    {
    CBTDiscoveryAppView* self = CBTDiscoveryAppView::NewLC(aRect);
    CleanupStack::Pop(self);
    return self;
    }

CBTDiscoveryAppView* CBTDiscoveryAppView::NewLC(const TRect& aRect)
    {
    CBTDiscoveryAppView* self = new (ELeave) CBTDiscoveryAppView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

void CBTDiscoveryAppView::ConstructL(const TRect& aRect)
    {
    iOutputText = HBufC::NewL(KMaxLineLength);

    iDiscoverer = CBTDiscoverer::NewL(*this);

    CreateWindowL();
    SetRect(aRect);

    iMsgIndex = 0;
    
    iListBox = new (ELeave) CAknSingleStyleListBox;
    iListBox->SetContainerWindowL(*this);
    iListBox->ConstructL(this, 0);
    
    iListBox->SetRect(aRect.Size());

    iListBox->ActivateL();
    iListBox->CreateScrollBarFrameL(ETrue);
    iListBox->ScrollBarFrame()
            ->SetScrollBarVisibilityL(CEikScrollBarFrame::EOn, CEikScrollBarFrame::EAuto);
    iListBox->SetDimmed(ETrue);

    iMessageList = new (ELeave) CDesCArrayFlat(KGranularityOfArray);

    CTextListBoxModel* model = iListBox->Model();
    model->SetItemTextArray(iMessageList);
    model->SetOwnershipType(ELbmOwnsItemArray); // transfer ownership of iMessageList

    ActivateL();
    MakeVisible(ETrue);
    }

void CBTDiscoveryAppView::ClearL()
    {
    iMessageList->Reset();
    iListBox->HandleItemRemovalL();
    iListBox->Reset();

    iMsgIndex = 0;
    }

CBTDiscoveryAppView::~CBTDiscoveryAppView()
    {
    //delete iMessageList;   //  Owned by iListBox->Model()

    delete iListBox;
    iListBox = NULL;

    delete iOutputText;
    iOutputText = NULL;

    delete iDiscoverer;
    iDiscoverer = NULL;
    }

TInt CBTDiscoveryAppView::CountComponentControls() const
    {
    return 1; // Only have one Component
    }

CCoeControl* CBTDiscoveryAppView::ComponentControl(TInt aIndex) const
    {
    __ASSERT_DEBUG(aIndex == 0, Panic(EBTDiscoveryInvalidComponentIndex));
    return iListBox;
    }

TKeyResponse CBTDiscoveryAppView::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    return iListBox->OfferKeyEventL(aKeyEvent, aType);
    }

void CBTDiscoveryAppView::Error(const TDesC& aText)
    {
    PrintLine(aText);
    }

void CBTDiscoveryAppView::Print(const TDesC& aText)
    {
    if (!iOutputText->Des().Length())
        {
        iOutputText->Des().Append(_L("\t"));
        }

    TInt spaceRemaining = KMaxLineLength - iOutputText->Des().Length();
    // if mlen is greater than the length of the string
    // then Left returns the whole of the descriptor.
    iOutputText->Des().Append(aText.Left(spaceRemaining));
    }

void CBTDiscoveryAppView::PrintLine(const TDesC& aText)
    {
    Print(aText);
    PrintNewLine();
    iOutputText->Des().Zero();
    }

void CBTDiscoveryAppView::PrintNewLine()
    {
    TRAPD(err, iMessageList->AppendL(*iOutputText));
    if (err != KErrNone)
        {
        Panic(EBTDiscoveryViewPrintNewLine);
        }
    iListBox->HandleItemAdditionL();
    }

void CBTDiscoveryAppView::SelectDeviceAndListServicesL()
    {
    TBTDeviceResponseParamsPckg response;

    if (iDiscoverer->SelectDeviceL(response))
        {
        PrintLine(_L("Device Selected: "));
        PrintLine(response().DeviceName());
        PrintLine(_L("Retrieving services..."));
        iDiscoverer->ListServicesL(response().BDAddr());
        }
    }
