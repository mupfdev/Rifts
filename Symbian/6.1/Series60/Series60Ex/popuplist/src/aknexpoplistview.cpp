/*
* ============================================================================
*  Name     : CAknExPopListView from CAknView
*  Part of  : AknExPopList
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include  <aknviewappui.h>
#include  <avkon.hrh>

#include <AknPopup.h>
#include <AknLists.h>
#include <AknNoteDialog.h>
#include <BarsRead.h>
#include <eikdef.h>

#include <GulIcon.h>
#include <EikClbd.h>

#include <AknIconArray.h>

#include  <AknExPopList.mbg>
#include  <AknExPopList.rsg>
#include  "AknExPopList.hrh"
#include  "AknExPopListView.h"
#include  "AknExPopListContainer.h" 

// CONSTANTS
const TInt KMaxIcons = 10;
const TInt KMaxTitleLength = 32;
const TInt KMessageLength = 64;

const   TInt KIndexArraySize = 5;
const   TInt KInitPos     = 0;
#define KInitPosString  _L("0")

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CAknExPopListView::ConstructL(const TRect& aRect)
// EPOC two-phased constructor
// ---------------------------------------------------------
void CAknExPopListView::ConstructL()
    {
    BaseConstructL(R_AKNEXPOPLIST_VIEW1);
    }

// ---------------------------------------------------------
// CAknExPopListView::~CAknExPopListView()
// Destructor
// ---------------------------------------------------------
CAknExPopListView::~CAknExPopListView()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    delete iContainer;
    }

// ---------------------------------------------------------
// TUid CAknExPopListView::Id()
// returns view id
// ---------------------------------------------------------
TUid CAknExPopListView::Id() const
    {
    return KViewId;
    }

// ---------------------------------------------------------
// CAknExPopListView::HandleCommandL(TInt aCommand)
// handles commands to be handled.
// ---------------------------------------------------------
void CAknExPopListView::HandleCommandL(TInt aCommand)
    {   
    switch (aCommand)
        {
        case EAknSoftkeyBack:
            AppUi()->HandleCommandL(EAknCmdExit);
            break;

        case EAknExPopListCmdAuto:
        case EAKnTaPopListSoftkeyNext:
            AutoTestL();
            break;

        case EAknExPopListCmdView1Menu1:
            ShowSingleItemPopupListL(EFalse);
            break;

        case EAknExPopListCmdView1Menu2:
            ShowSingleItemPopupListL(ETrue);
            break;

        case EAknExPopListCmdView1Menu3:
            ShowSingleItemPopupListWithGraphicsL(EFalse);
            break;

        case EAknExPopListCmdView1Menu4:
            ShowSingleItemPopupListWithGraphicsL(ETrue);
            break;

        case EAknExPopListCmdView1Menu5:
            ShowSingleItemPopupListWithHeadingAndGraphicsL(EFalse);
            break;

        case EAknExPopListCmdView1Menu6:
            ShowSingleItemPopupListWithHeadingAndGraphicsL(ETrue);
            break;

        case EAknExPopListCmdView1Menu7:
            ShowDoubleItemPopupListL(EFalse);
            break;

        case EAknExPopListCmdView1Menu8:
            ShowDoubleItemPopupListL(ETrue);
            break;

        case EAknExPopListCmdView1Menu9:
            ShowDoubleItemPopupListWithGraphicsL(EFalse);
            break;

        case EAknExPopListCmdView1Menu10:
            ShowDoubleItemPopupListWithGraphicsL(ETrue);
            break;

        default:
            AppUi()->HandleCommandL(aCommand);
            break;

        }
    }

// ---------------------------------------------------------
// CAknExPopListView::HandleClientRectChange()
// 
// ---------------------------------------------------------
void CAknExPopListView::HandleClientRectChange()
    {
    if (iContainer)
        {
        iContainer->SetRect(ClientRect());
        }
    }

// ---------------------------------------------------------
// CAknExPopListView::DoActivateL(...)
// 
// ---------------------------------------------------------
void CAknExPopListView::DoActivateL(
   const TVwsViewId& /*aPrevViewId*/,TUid /*aCustomMessageId*/,
   const TDesC8& /*aCustomMessage*/)
    {
    iContainer = new(ELeave) CAknExPopListContainer;
    iContainer->SetMopParent(this);
    iContainer->ConstructL(ClientRect());
    AppUi()->AddToStackL(*this, iContainer);
   }

// ---------------------------------------------------------
// CAknExPopListView::DoDeactivateL(TInt aCommand)
// 
// ---------------------------------------------------------
void CAknExPopListView::DoDeactivate()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    
    delete iContainer;
    iContainer = NULL;
    }


// -----------------------------------------------------------------
// CAknExPopListView::AutoTestL()
// shows all kind of popup-windows except list_single_number_pane,
// list_single_heading_pane, and list_single_number_heading_pane
// automatically.
// -----------------------------------------------------------------
void CAknExPopListView::AutoTestL()
    {
    ShowSingleItemPopupListL(EFalse);
    ShowSingleItemPopupListL(ETrue);
    ShowSingleItemPopupListWithGraphicsL(EFalse);
    ShowSingleItemPopupListWithGraphicsL(ETrue);
    ShowSingleItemPopupListWithHeadingAndGraphicsL(EFalse);
    ShowSingleItemPopupListWithHeadingAndGraphicsL(ETrue);
    ShowDoubleItemPopupListL(EFalse);
    ShowDoubleItemPopupListL(ETrue);
    ShowDoubleItemPopupListWithGraphicsL(EFalse);
    ShowDoubleItemPopupListWithGraphicsL(ETrue);
    }

//------------------------------------------------------------------
// CAknExPopListView::ShowSingleItemPopupList(TBool aShowTitle)
// shows "List pane for single item"
//------------------------------------------------------------------
void CAknExPopListView::ShowSingleItemPopupListL(TBool aShowTitle)
    {
    // Create listbox and PUSH it.
    CEikTextListBox* list = new(ELeave) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL(list);

    // Create popup list and PUSH it.
    CAknPopupList* popupList = CAknPopupList::NewL(
                                        list, R_AVKON_SOFTKEYS_OK_BACK,
                                        AknPopupLayouts::EMenuWindow);
    CleanupStack::PushL(popupList);

    // initialize listbox.
    list->ConstructL(popupList, CEikListBox::ELeftDownInViewRect);
    list->CreateScrollBarFrameL(ETrue);
    list->ScrollBarFrame()->SetScrollBarVisibilityL(
                                CEikScrollBarFrame::EOff,
                                CEikScrollBarFrame::EAuto);

    // Make listitems. and PUSH it
    CDesCArrayFlat* items = 
            iCoeEnv->ReadDesCArrayResourceL(R_AKNEXPOPLIST_MENU_ITEMS_TEST1);
    CleanupStack::PushL(items);

    // Set listitems.
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray(items);
    model->SetOwnershipType(ELbmOwnsItemArray);
    CleanupStack::Pop();

    // Set title if it is needed.
    if (aShowTitle)
        {
        TBuf<KMaxTitleLength> title;
        iCoeEnv->ReadResource(title, R_AKNEXPOPLIST_MENU_TITLE_TEST1);
        popupList->SetTitleL(title);
        }

    // Show popup list and then show return value.
    TInt popupOk = popupList->ExecuteLD();
    CleanupStack::Pop();            // popuplist
    if (popupOk)
        {
        TInt index = list->CurrentItemIndex();
        TBuf<KMessageLength> msg;
        TBuf<KMessageLength> format;
        iCoeEnv->ReadResource(format, R_AKNEXPOPLIST_SELECT_MESSAGE);
        msg.Format(format, index + 1);
        CAknNoteDialog* dlg = new( ELeave ) CAknNoteDialog( 
            CAknNoteDialog::ENoTone, CAknNoteDialog::ENoTimeout);
        dlg->PrepareLC( R_AKNEXPOPLIST_SELECT_MESSAGE_NOTE );
        dlg->SetTextPluralityL( EFalse );
        dlg->SetTextL( msg );
        dlg->RunLD();
        }

    CleanupStack::PopAndDestroy();  // list
    }


//------------------------------------------------------------------
// CAknExPopListView::ShowSingleItemPopupListWithGraphicsL(TBool aShowTitle)
// shows "List pane for single item with graphic"
//------------------------------------------------------------------
void CAknExPopListView::ShowSingleItemPopupListWithGraphicsL(TBool  aShowTitle)
    {
    CAknSingleGraphicPopupMenuStyleListBox* list = 
                     new(ELeave) CAknSingleGraphicPopupMenuStyleListBox;
    
    CleanupStack::PushL(list);
    CAknPopupList* popupList = CAknPopupList::NewL(
                                        list, R_AVKON_SOFTKEYS_OK_BACK,
                                        AknPopupLayouts::EMenuGraphicWindow);
    
    CleanupStack::PushL(popupList);

    list->ConstructL(popupList, CEikListBox::ELeftDownInViewRect);
    list->CreateScrollBarFrameL(ETrue);
    list->ScrollBarFrame()->SetScrollBarVisibilityL(
                                CEikScrollBarFrame::EOff,
                                CEikScrollBarFrame::EAuto);

    // Set Item text and PUSH it
    CDesCArrayFlat* items = 
            iCoeEnv->ReadDesCArrayResourceL(R_AKNEXPOPLIST_MENU_ITEMS_TEST2);
    CleanupStack::PushL(items);

    // Set listitems.
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray(items);
    model->SetOwnershipType(ELbmOwnsItemArray);
    CleanupStack::Pop();

    // Create Icon object
    CArrayPtr<CGulIcon>* icons = 
                            new(ELeave) CAknIconArray(KMaxIcons);
    CleanupStack::PushL(icons); // PUSH Icon

    // Load bitmap file name
    TBuf<KMaxFileName> iconFile;
    iCoeEnv->ReadResource(iconFile, R_AKNEXPOPLIST_ICONFILE);

    icons->AppendL(iEikonEnv->CreateIconL(
                iconFile, EMbmAknexpoplistCard, EMbmAknexpoplistCardm));
    icons->AppendL(iEikonEnv->CreateIconL(
                iconFile, EMbmAknexpoplistTel, EMbmAknexpoplistTelm));

    list->ItemDrawer()->FormattedCellData()->SetIconArrayL(icons);
    
    CleanupStack::Pop();    // POP Icon

    list->ClearSelection();

    CArrayFixFlat<TInt>* array1 = 
                            new(ELeave) CArrayFixFlat<TInt>(KIndexArraySize);

    CleanupStack::PushL(array1);
    array1->AppendL(1);
    array1->AppendL(2);
    
    list->SetSelectionIndexesL(array1);

    CleanupStack::PopAndDestroy(); //Array

    list->ItemDrawer()->SetItemMarkPosition(KInitPos);
    TPtrC blank(KInitPosString);
    list->ItemDrawer()->SetItemMarkReplacement(blank);

    // Set title if it is needed.
    if (aShowTitle)
        {
        TBuf<KMaxTitleLength> title;
        iCoeEnv->ReadResource(title, R_AKNEXPOPLIST_MENU_TITLE_TEST2);
        popupList->SetTitleL(title);
        }

    // Show popup list and then show return value.
    TInt popupOk = popupList->ExecuteLD();
    CleanupStack::Pop();            // popuplist
    if (popupOk)
        {
        TInt index = list->CurrentItemIndex();
        TBuf<KMessageLength> msg;
        TBuf<KMessageLength> format;
        iCoeEnv->ReadResource(format, R_AKNEXPOPLIST_SELECT_MESSAGE);
        msg.Format(format, index + 1);
        CAknNoteDialog* dlg = new( ELeave ) CAknNoteDialog( 
            CAknNoteDialog::ENoTone, CAknNoteDialog::ENoTimeout);
        dlg->PrepareLC( R_AKNEXPOPLIST_SELECT_MESSAGE_NOTE );
        dlg->SetTextPluralityL( EFalse );
        dlg->SetTextL( msg );
        dlg->RunLD();
        }


    CleanupStack::PopAndDestroy();  // list
    }

//------------------------------------------------------------------
// CAknExPopListView::ShowSingleItemPopupListWithHeadingAndGraphicsL(
//                                          TBool aShowTitle)
// shows "List pane for single item with heading and graphic"
//------------------------------------------------------------------
void CAknExPopListView::ShowSingleItemPopupListWithHeadingAndGraphicsL(
                                                            TBool aShowTitle)
    {
    CAknSingleGraphicHeadingPopupMenuStyleListBox* list = 
                     new(ELeave) CAknSingleGraphicHeadingPopupMenuStyleListBox;

    CleanupStack::PushL(list);
    CAknPopupList* popupList = CAknPopupList::NewL(
                                list, R_AVKON_SOFTKEYS_OK_BACK,
                                AknPopupLayouts::EMenuGraphicHeadingWindow);
  
    CleanupStack::PushL(popupList);
    list->ConstructL(popupList, CEikListBox::ELeftDownInViewRect);
    list->CreateScrollBarFrameL(ETrue);
    list->ScrollBarFrame()->SetScrollBarVisibilityL(
                                CEikScrollBarFrame::EOff,
                                CEikScrollBarFrame::EAuto);

    // Set Item text
    CDesCArrayFlat* items = 
            iCoeEnv->ReadDesCArrayResourceL(R_AKNEXPOPLIST_MENU_ITEMS_TEST3);

    CleanupStack::PushL(items);

    // Set listitems.
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray(items);
    model->SetOwnershipType(ELbmOwnsItemArray);
    CleanupStack::Pop();

   
    // Create Icon object
    CArrayPtr<CGulIcon>* icons = 
                            new(ELeave) CAknIconArray(KMaxIcons);
    CleanupStack::PushL(icons);

    // Load bitmap file name
    TBuf<KMaxFileName> iconFile;
    iCoeEnv->ReadResource(iconFile, R_AKNEXPOPLIST_ICONFILE);

    // Load bitmap and append them to "icons" array.
    icons->AppendL(iEikonEnv->CreateIconL(
                iconFile, EMbmAknexpoplistTel, EMbmAknexpoplistTelm));
    icons->AppendL(iEikonEnv->CreateIconL(
                iconFile, EMbmAknexpoplistMail, EMbmAknexpoplistMailm));

    list->ItemDrawer()->FormattedCellData()->SetIconArrayL(icons);

    CleanupStack::Pop();    // icon

    list->ClearSelection();

    CArrayFixFlat<TInt>* array1 = 
                            new(ELeave) CArrayFixFlat<TInt>(KIndexArraySize);

    CleanupStack::PushL(array1);
    array1->AppendL(1);
    array1->AppendL(2);
    
    list->SetSelectionIndexesL(array1);

    CleanupStack::PopAndDestroy(); //Array

    list->ItemDrawer()->SetItemMarkPosition(KInitPos);
    TPtrC blank(KInitPosString);
    list->ItemDrawer()->SetItemMarkReplacement(blank);

    // Set title if it is needed.
    if (aShowTitle)
        {
        TBuf<KMaxTitleLength> title;
        iCoeEnv->ReadResource(title, R_AKNEXPOPLIST_MENU_TITLE_TEST3);
        popupList->SetTitleL(title);
        }

    // Show popup list and then show return value.
    TInt popupOk = popupList->ExecuteLD();
    CleanupStack::Pop();            // popuplist
    if (popupOk)
        {
        TInt index = list->CurrentItemIndex();
        TBuf<KMessageLength> msg;
        TBuf<KMessageLength> format;
        iCoeEnv->ReadResource(format, R_AKNEXPOPLIST_SELECT_MESSAGE);
        msg.Format(format, index + 1);
        CAknNoteDialog* dlg = new( ELeave ) CAknNoteDialog( 
            CAknNoteDialog::ENoTone, CAknNoteDialog::ENoTimeout);
        dlg->PrepareLC( R_AKNEXPOPLIST_SELECT_MESSAGE_NOTE );
        dlg->SetTextPluralityL( EFalse );
        dlg->SetTextL( msg );
        dlg->RunLD();
        }
    
    CleanupStack::PopAndDestroy();  // list

    }


//------------------------------------------------------------------
// CAknExPopListView::ShowDoubleItemPopupListL(TBool aShowTitle)
// shows "List pane for double item"
//------------------------------------------------------------------
void CAknExPopListView::ShowDoubleItemPopupListL(TBool aShowTitle)
    {
    // Create listbox and PUSH it.
    CEikFormattedCellListBox* list =
                        new(ELeave) CAknDoublePopupMenuStyleListBox;
    CleanupStack::PushL(list);

    // Create popup list and PUSH it.
    CAknPopupList* popupList = CAknPopupList::NewL(
                                        list, R_AVKON_SOFTKEYS_OK_BACK,
                                        AknPopupLayouts::EMenuDoubleWindow);


    CleanupStack::PushL(popupList);

    // initialize listbox.
    TInt flags = 0; // Clear flag.
    list->ConstructL(popupList, flags);
    list->CreateScrollBarFrameL(ETrue);
    list->ScrollBarFrame()->SetScrollBarVisibilityL(
                                CEikScrollBarFrame::EOff,
                                CEikScrollBarFrame::EAuto);
//    list->SetSize(TSize(ClientRect().Size()));

    // Make listitems.
    CDesCArrayFlat* items =
            iCoeEnv->ReadDesCArrayResourceL(R_AKNEXPOPLIST_MENU_ITEMS_TEST4);
    CleanupStack::PushL(items);

    // Set listitems.
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray(items);
    model->SetOwnershipType(ELbmOwnsItemArray);
    CleanupStack::Pop();

    // Set title if it is needed.
    if (aShowTitle)
        {
        TBuf<KMaxTitleLength> title;
        iCoeEnv->ReadResource(title, R_AKNEXPOPLIST_MENU_TITLE_TEST4);
        popupList->SetTitleL(title);
        }

    // Show popup list and then show return value.
    TInt popupOk = popupList->ExecuteLD();
    CleanupStack::Pop();            // popuplist
    if (popupOk)
        {
        TInt index = list->CurrentItemIndex();
        TBuf<KMessageLength> msg;
        TBuf<KMessageLength> format;
        iCoeEnv->ReadResource(format, R_AKNEXPOPLIST_SELECT_MESSAGE);
        msg.Format(format, index + 1);
        CAknNoteDialog* dlg = new( ELeave ) CAknNoteDialog( 
            CAknNoteDialog::ENoTone, CAknNoteDialog::ENoTimeout);
        dlg->PrepareLC( R_AKNEXPOPLIST_SELECT_MESSAGE_NOTE );
        dlg->SetTextPluralityL( EFalse );
        dlg->SetTextL( msg );
        dlg->RunLD();
        }

    CleanupStack::PopAndDestroy();  // list
    }

//------------------------------------------------------------------
// CAknExPopListView::ShowDoubleItemPopupListWithGraphicsL(TBool aShowTitle)
// shows "List pane for double item"
//------------------------------------------------------------------
void CAknExPopListView::ShowDoubleItemPopupListWithGraphicsL(TBool aShowTitle)
    {
    CAknDoubleLargeGraphicPopupMenuStyleListBox* list = 
                     new(ELeave) CAknDoubleLargeGraphicPopupMenuStyleListBox;
    
    CleanupStack::PushL(list);
    CAknPopupList* popupList = CAknPopupList::NewL(
                                        list, R_AVKON_SOFTKEYS_OK_BACK,
                                        AknPopupLayouts::EMenuDoubleLargeGraphicWindow);
    
    CleanupStack::PushL(popupList);

    TInt flags = 0; // Initialize flag
    list->ConstructL(popupList, flags);
    list->CreateScrollBarFrameL(ETrue);
    list->ScrollBarFrame()->SetScrollBarVisibilityL(
                                CEikScrollBarFrame::EOff,
                                CEikScrollBarFrame::EAuto);
//    list->SetSize(TSize(ClientRect().Size()));

    // Set Item text
    CDesCArrayFlat* items = 
            iCoeEnv->ReadDesCArrayResourceL(R_AKNEXPOPLIST_MENU_ITEMS_TEST5);
    CleanupStack::PushL(items);

    // Set listitems.
    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray(items);
    model->SetOwnershipType(ELbmOwnsItemArray);
    CleanupStack::Pop();

    // Create Icon object
    CArrayPtr<CGulIcon>* icons = 
                            new(ELeave) CAknIconArray(KMaxIcons);
    CleanupStack::PushL(icons); // PUSH Icon

    // Load bitmap file name
    TBuf<KMaxFileName> iconFile;
    iCoeEnv->ReadResource(iconFile, R_AKNEXPOPLIST_ICONFILE);

    icons->AppendL(iEikonEnv->CreateIconL(
        iconFile, EMbmAknexpoplistFinflag, EMbmAknexpoplistFinflagm));
    icons->AppendL(iEikonEnv->CreateIconL(
        iconFile, EMbmAknexpoplistJpnflag, EMbmAknexpoplistJpnflagm));


    list->ItemDrawer()->FormattedCellData()->SetIconArrayL(icons);

    CleanupStack::Pop();    // POP Icon

    list->ClearSelection();

    CArrayFixFlat<TInt>* array1 =
                            new(ELeave) CArrayFixFlat<TInt>(KIndexArraySize);

    CleanupStack::PushL(array1);
    array1->AppendL(1);
    array1->AppendL(2);
    
    list->SetSelectionIndexesL(array1);

    CleanupStack::PopAndDestroy(); //Array

    list->ItemDrawer()->SetItemMarkPosition(KInitPos);
    TPtrC blank(KInitPosString);
    list->ItemDrawer()->SetItemMarkReplacement(blank);

    // Set title if it is needed.
    if (aShowTitle)
        {
        TBuf<KMaxTitleLength> title;
        iCoeEnv->ReadResource(title, R_AKNEXPOPLIST_MENU_TITLE_TEST5);
        popupList->SetTitleL(title);
        }

    // Show popup list and then show return value.
    TInt popupOk = popupList->ExecuteLD();
    CleanupStack::Pop();            // popuplist
    if (popupOk)
        {
        TInt index = list->CurrentItemIndex();
        TBuf<KMessageLength> msg;
        TBuf<KMessageLength> format;
        iCoeEnv->ReadResource(format, R_AKNEXPOPLIST_SELECT_MESSAGE);
        msg.Format(format, index + 1);
        CAknNoteDialog* dlg = new( ELeave ) CAknNoteDialog( 
            CAknNoteDialog::ENoTone, CAknNoteDialog::ENoTimeout);
        dlg->PrepareLC( R_AKNEXPOPLIST_SELECT_MESSAGE_NOTE );
        dlg->SetTextPluralityL( EFalse );
        dlg->SetTextL( msg );
        dlg->RunLD();
        }

    CleanupStack::PopAndDestroy();  // list

    }

// End of File