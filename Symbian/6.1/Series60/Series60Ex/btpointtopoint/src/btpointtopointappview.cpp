/* Copyright (c) 2002, Nokia. All rights reserved */

#include "BTPointToPointAppView.h"
#include "BTPointToPoint.pan"

#include "MessageClient.h"
#include "MessageServer.h"

static const TInt KMaxTIntLen = 8;
static const TInt KMessageHeaderLen = 8;

// Standard Symbian construction sequence
CBTPointToPointAppView* CBTPointToPointAppView::NewL(const TRect& aRect)
    {
    CBTPointToPointAppView* self = CBTPointToPointAppView::NewLC(aRect);
    CleanupStack::Pop(self);
    return self;
    }

CBTPointToPointAppView* CBTPointToPointAppView::NewLC(const TRect& aRect)
    {
    CBTPointToPointAppView* self = new (ELeave) CBTPointToPointAppView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

void CBTPointToPointAppView::ConstructL(const TRect& aRect)
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

CBTPointToPointAppView::CBTPointToPointAppView()
    {
    // no implementation required
    }


CBTPointToPointAppView::~CBTPointToPointAppView()
    {
    // iMessageList not deleted as it is owned by iListBox->Model()

    delete iListBox;
    iListBox = NULL;

    }

void CBTPointToPointAppView::ClearMessageListL()
    {
    iMessageList->Reset();

    iListBox->HandleItemRemovalL();
    iListBox->Reset();

    iMsgIndex = 0;
    }

TInt CBTPointToPointAppView::CountComponentControls() const
    {
    return 1; // Only have one Component
    }

CCoeControl* CBTPointToPointAppView::ComponentControl(TInt aIndex) const
    {
    __ASSERT_DEBUG(aIndex == 0, Panic(EBTPointToPointInvalidControlIndex));
    return iListBox;    //  Return the component
    }

TKeyResponse CBTPointToPointAppView::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    return iListBox->OfferKeyEventL(aKeyEvent, aType);
    }

void CBTPointToPointAppView::LogL(const TDesC& aText)
    {
    LogL(aText, KNullDesC);
    }

void CBTPointToPointAppView::LogL(const TDesC& aText, TInt aNumber)
    {
    TBuf<KMaxTIntLen> numberString;

    numberString.Num(aNumber);

    LogL(aText, numberString);
    }

void CBTPointToPointAppView::LogL(const TDesC& aText, const TDesC& aExtraText)
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

TBool CBTPointToPointAppView::ContainsEntries()
    {
    return iListBox->Model()->NumberOfItems() != 0;
    }
