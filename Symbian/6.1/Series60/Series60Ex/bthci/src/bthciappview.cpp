/* Copyright (c) 2002, Nokia. All rights reserved */

#include <eiklabel.h>
#include <bt_sock.h>

#include "BTHCIAppView.h"
#include "BTHCI.pan"

const TInt KMaxLineLength = 40;
const TInt KGranularityOfArray = 10;

CBTHCIAppView* CBTHCIAppView::NewL(const TRect& aRect)
    {
    CBTHCIAppView* self = CBTHCIAppView::NewLC(aRect);
    CleanupStack::Pop(self);
    return self;
    }

CBTHCIAppView* CBTHCIAppView::NewLC(const TRect& aRect)
    {
    CBTHCIAppView* self = new (ELeave) CBTHCIAppView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

void CBTHCIAppView::ConstructL(const TRect& aRect)
    {
    iOutputText = HBufC::NewL(KMaxLineLength);

    CreateWindowL();
    SetRect(aRect);

    iMsgIndex = 0;
    
    // iListBox is used by the view for displaying multiple lines
    // of information to the user
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

void CBTHCIAppView::ClearL()
    {
    iMessageList->Reset();
    iListBox->HandleItemRemovalL();
    iListBox->Reset();
    iMsgIndex = 0;
    }

CBTHCIAppView::~CBTHCIAppView()
    {
    //delete iMessageList;   //  Owned by iListBox->Model()

    delete iListBox;
    iListBox = NULL;

    delete iOutputText;
    iOutputText = NULL;
    }

TInt CBTHCIAppView::CountComponentControls() const
    {
    return 1; // Only have one Component
    }

CCoeControl* CBTHCIAppView::ComponentControl(TInt aIndex) const
    {
    __ASSERT_DEBUG(aIndex == 0, Panic(EBTHCIInvalidComponentIndex));
    return iListBox;
    }

TKeyResponse CBTHCIAppView::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    return iListBox->OfferKeyEventL(aKeyEvent, aType);
    }

void CBTHCIAppView::Print(const TDesC& aText)
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

void CBTHCIAppView::PrintLine(const TDesC& aText)
    {
    Print(aText);
    PrintNewLine();
    iOutputText->Des().Zero();
    }

void CBTHCIAppView::PrintNewLine()
    {
    TRAPD(err, 
        {
        iMessageList->AppendL(*iOutputText);
        iListBox->HandleItemAdditionL();
        });

    if (err != KErrNone)
        {
        Panic(EBTHCIViewPrintNewLine);
        }
    }

