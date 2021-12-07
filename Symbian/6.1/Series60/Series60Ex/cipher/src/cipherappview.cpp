/* Copyright (c) 2002, Nokia. All rights reserved */
#include <eiklabel.h>
#include <aknlists.h>
#include "CipherAppView.h"
#include "Cipher.pan"

const TInt KMaxLineLength = 40;
const TInt KGranularityOfArray = 10;

// Standard construction sequence
CCipherAppView* CCipherAppView::NewL(const TRect& aRect)
    {
    CCipherAppView* self = CCipherAppView::NewLC(aRect);
    CleanupStack::Pop(self);
    return self;
    }

CCipherAppView* CCipherAppView::NewLC(const TRect& aRect)
    {
    CCipherAppView* self = new (ELeave) CCipherAppView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

void CCipherAppView::ConstructL(const TRect& aRect)
    {
    iOutputText = HBufC::NewL(KMaxLineLength);

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

CCipherAppView::CCipherAppView()
    {
    // Add any construction code that can not leave here
    }


CCipherAppView::~CCipherAppView()
    {
    //delete iMessageList;   //  Owned by iListBox->Model()

    delete iListBox;
    iListBox = NULL;

    delete iOutputText;
    iOutputText = NULL;
    }

TInt CCipherAppView::CountComponentControls() const
    {
    return 1; // Only have one Component
    }

CCoeControl* CCipherAppView::ComponentControl(TInt aIndex) const
    {
    __ASSERT_DEBUG(aIndex == 0, Panic(ECipherInvalidComponentIndex));
    return iListBox;
    }

TKeyResponse CCipherAppView::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    return iListBox->OfferKeyEventL(aKeyEvent, aType);
    }

void CCipherAppView::PrintLineL(const TDesC& aText)
    {
    iOutputText->Des().Append(_L("\t"));
    TInt spaceRemaining = KMaxLineLength - iOutputText->Des().Length();
    // if mlen is greater than the length of the string
    // then Left returns the whole of the descriptor.
    iOutputText->Des().Append(aText.Left(spaceRemaining));
    iMessageList->AppendL(*iOutputText);
    iListBox->HandleItemAdditionL();
    iOutputText->Des().Zero();
    }
