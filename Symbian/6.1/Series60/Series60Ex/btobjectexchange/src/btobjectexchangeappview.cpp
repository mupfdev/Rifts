/* Copyright (c) 2002, Nokia. All rights reserved */

#include "BTObjectExchangeAppView.h"
#include "BTObjectExchange.pan"

static const TInt KMaxTIntLen = 8;
static const TInt KMessageHeaderLen = 8;

// Standard construction sequence
CBTObjectExchangeAppView* CBTObjectExchangeAppView::NewL(const TRect& aRect)
    {
    CBTObjectExchangeAppView* self = CBTObjectExchangeAppView::NewLC(aRect);
    CleanupStack::Pop(self);
    return self;
    }

CBTObjectExchangeAppView* CBTObjectExchangeAppView::NewLC(const TRect& aRect)
    {
    CBTObjectExchangeAppView* self = new (ELeave) CBTObjectExchangeAppView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

void CBTObjectExchangeAppView::ConstructL(const TRect& aRect)
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect(aRect);

    // Create a control to display a list of messages
    iListBox = new (ELeave) CAknSingleNumberStyleListBox;
    iListBox->SetContainerWindowL(*this);
    iListBox->ConstructL(this, 0);
    
    iListBox->SetRect(aRect.Size());

    iListBox->ActivateL();
    iListBox->CreateScrollBarFrameL(ETrue);
    iListBox->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOn, CEikScrollBarFrame::EAuto);

    // Create an array to hold the messages
    iMessageList = new (ELeave) CDesCArrayFlat(10);

    // Give it to the control
    CTextListBoxModel* model = iListBox->Model();
    model->SetItemTextArray(iMessageList);
    model->SetOwnershipType(ELbmOwnsItemArray); // transfer ownership of iMessageList

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

CBTObjectExchangeAppView::CBTObjectExchangeAppView()
: iMsgIndex(0)
    {
    // No implementation required.
    }


CBTObjectExchangeAppView::~CBTObjectExchangeAppView()
    {
    // iMessageList is not deleted as it is owned by iListBox->Model()
    delete iListBox;
    iListBox = NULL;
    }

TInt CBTObjectExchangeAppView::CountComponentControls() const
    {
    return 1; // Only have one Component
    }

CCoeControl* CBTObjectExchangeAppView::ComponentControl(TInt aIndex) const
    {
    __ASSERT_DEBUG(aIndex == 0, Panic(EBTObjectExchangeInvalidControlIndex));
    return iListBox;
    }

TKeyResponse CBTObjectExchangeAppView::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    return iListBox->OfferKeyEventL(aKeyEvent, aType);
    }

void CBTObjectExchangeAppView::LogL(const TDesC& aText)
    {
    LogL(aText, KNullDesC);
    }

void CBTObjectExchangeAppView::LogL(const TDesC& aText, TInt aNumber)
    {
    TBuf<KMaxTIntLen> numberString;

    numberString.Num(aNumber);

    LogL(aText, numberString);
    }

void CBTObjectExchangeAppView::LogL(const TDesC& aText, const TDesC& aExtraText)
    {
    HBufC* buffer = HBufC::NewLC(KMessageHeaderLen + aText.Length() + aExtraText.Length());

    buffer->Des().Num(++iMsgIndex);
    buffer->Des().Append('\t');
    buffer->Des().Append(aText);
    buffer->Des().Append(aExtraText);

    // add the message to the list
    iMessageList->AppendL(*buffer);
    CleanupStack::PopAndDestroy(buffer);

    // tell the control about the change
    iListBox->HandleItemAdditionL();
    }

void CBTObjectExchangeAppView::ClearMessageListL()
    {
    iMessageList->Reset();

    iListBox->HandleItemRemovalL();
    iListBox->Reset();

    iMsgIndex = 0;
    }

TBool CBTObjectExchangeAppView::ContainsEntries()
    {
    return iListBox->Model()->NumberOfItems() != 0;
    }
