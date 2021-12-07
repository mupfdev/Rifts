/*
* =============================================================================
*  Name     : CAknExQueryContainer
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <eikenv.h>
#include <eiklabel.h> // For label control
#include <eikclb.h>   // For listbox
#include <eiktxlbm.h> // For listbox model
#include <eikclbd.h>  // For listbox data
#include <aknlists.h> // For list pane
#include <aknpopup.h>
#include <aknpopupheadingpane.h>
#include <akniconarray.h>
#include <AknMessageQueryDialog.h> // for global message query
#include <aknglobalconfirmationquery.h> // for global message query
#include <StringLoader.h>
#include <avkon.hrh>
#include <avkon.rsg>
#include <AVKON.mbg>
#include <AKNEXQUERY.mbg>
#include <AknListQueryDialog.h>
#include <AknExQuery.rsg>
#include "AknExQuery.hrh"
#include "AknExQueryView.h"
#include "AknExQueryContainer.h"
#include "AknExQueryEditorListEventHandler.h"
#include "AknExQueryRollerListEventHandler.h"
#include "AknExQueryTextAndTextListEventHandler.h"
#include "AknExQueryTextAndTimeListEventHandler.h"
#include "AknExQueryTimeAndTimeListEventHandler.h"
#include "AknExQueryTextAndNumberListEventHandler.h"
#include "AknExQueryTextAndDurationListEventHandler.h"
#include "AknExQueryTimeAndDurationListEventHandler.h"
#include "AknExQueryKeyListEventHandler.h"
#include "AknExQueryIconListEventHandler.h"
//#include <aknexquery.mbg>
//#include <aknexquery.rsg>

// MACROS

// CONSTANTS
#define KAknExQueryGray TRgb(0xaaaaaa)

#define AKNEXQUERY_LABEL_ORIGIN TPoint( 0, 0 )
#define AKNEXQUERY_LABEL2_POSITION TPoint( 0, 20 )
#define AKNEXQUERY_POPUP_MENU_SIZE TSize( 80, 80 )

const TInt KAknExQueryCountComponentControls = 1;
const TInt KAknExQueryText2BufLength = 32;
const TInt KAknExQueryTextMaxLength = 256;
const TInt KAknExQueryTextLargeMessageLength = 1024; 
const TInt KAknExQueryCodeBufLength = 8;
const TInt KAknExQueryNameColumnIndex = 0;
const TInt KAknExQueryNameGapColumnIndex = 1;
const TInt KAknExQueryArrayFlatResourceId = 1;
const TInt KAknExQueryListBoxRectPointX = 30;
const TInt KAknExQueryListBoxRectPointY = 15;
const TInt KAknExQueryListBoxRectWidth = 120;
const TInt KAknExQueryListBoxRectHeight = 120;

_LIT(KAvkonMbmFilePath, "z:\\system\\data\\avkon.mbm");
_LIT(KAknExQueryMbmFilePath, "\\system\\apps\\aknexquery\\aknexquery.mbm");
_LIT(KAknExQueryDefaultDataText, "Hello");
_LIT(KAknExQueryDefaultPhoneNumber, "12345");
//#define KAknExQueryDefaultDataText     "Hello"
//#define KAknExQueryDefaultPhoneNumber  "12345"


// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExQueryContainer::CAknExQueryContainer( CAknExQueryView* aView )
// Overload constructor.
//-----------------------------------------------------------------------------
//
CAknExQueryContainer::CAknExQueryContainer( CAknExQueryView* aView )
:   iView( aView )
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::ConstructL(const TRect& aRect)
// EPOC two phased constructor
//-----------------------------------------------------------------------------
//
void CAknExQueryContainer::ConstructL( const TRect& aRect )
    {
    // Creates window.
    CreateWindowL();

    // Creates label object.
    if ( !iLabel )
        {
        iLabel = new( ELeave ) CEikLabel;
        iLabel->SetContainerWindowL( *this );
        iLabel->SetFont( LatinBold19() );

        SetTextToLabelL( R_AKNEXQUERY_TITLE_MESSAGE );
        }

    SetRect( aRect ); // Sets rectangle of frame.
    ActivateL(); // Activates the window. (Ready to draw)
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::~CAknExQueryContainer()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExQueryContainer::~CAknExQueryContainer()
    {
    delete iLabel;
    delete iLabelResultMessage;
    delete iListBox;
    delete iHandler;

    delete iGlobalListQuery;
    delete iGlobalListObserver;
    delete iGlobalMsgQuery;


    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::ShowConfirmationQueryL(const TInt aResourceId,
//                           const TInt aTextResourceId=0, TBool aToneFlag)
//                            
// Display of Confirmation Query.
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::ShowConfirmationQueryL(
                             const TInt aResourceId,
                             const TInt aTextResourceId, 
                             const TBool aPromptFlag,
                             const TBool aToneFlag, 
                             const TBool aHeaderTextAndImageFlag,
                             const CAknQueryDialog::TTone aTone
                             )
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );
    CAknQueryDialog* dlg;

    if (aHeaderTextAndImageFlag)
        {
        dlg = CAknQueryDialog::NewL( aTone );
        dlg->PrepareLC( aResourceId );
        TBuf<KAknExQueryTextBufLength> prompt;
        iCoeEnv->ReadResource(prompt,R_AKNEXQUERY_NUMQUERY_WITHHEAD_HEAD);
        dlg->QueryHeading()->SetTextL(prompt);          
        SetIconL(dlg, EMbmAknexqueryAnchor_id, EMbmAknexqueryAnchor_id_mask);
        dlg->RunLD();
        }
    else
        { 
        if ( !aTextResourceId )
            {
            dlg = CAknQueryDialog::NewL( aTone );
            }
        else
            {
            TBuf<KAknExQueryTextBufLength> prompt;
            iCoeEnv->ReadResource(prompt, aTextResourceId);

            if ( aPromptFlag )
                {
                dlg = CAknQueryDialog::NewL( aTone );
                CleanupStack::PushL(dlg);
                dlg->SetPromptL(prompt);
                CleanupStack::Pop();
                }
            else if ( aToneFlag )
                {
                dlg = new( ELeave ) CAknQueryDialog(prompt, aTone);
                }
            else
                {
                dlg = new( ELeave ) CAknQueryDialog(prompt);
                }
            }
        ShowResultMessageL( dlg->ExecuteLD( aResourceId ));    
        }
    iDisplayDialog = EFalse;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::ShowResultMessageL(TBool aResult)
// Display return value of dialog.
// ----------------------------------------------------------------------------
void CAknExQueryContainer::ShowResultMessageL(TBool aResult)
    {
    TInt res(R_AKNEXQUERY_NO_OR_CANCEL_MESSAGE);

    if ( aResult )
        {
        res = R_AKNEXQUERY_YES_OR_OK_MESSAGE;
        }

    TBuf<KAknExQueryTextBufLength> messageConfirmationQuery;
    iCoeEnv->ReadResource( messageConfirmationQuery, res);

    ShowMessageL( messageConfirmationQuery );
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::ShowDataQueryL
// Display of Data Query.
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::ShowDataQueryL(
    const TInt aQueryResourceId,
    const TInt aTextResourceId,
    const TInt aPromptResoureId,
    const TInt aMaxLength,
    const TBool aDisplayFlag)
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    TBuf<KAknExQueryTextBufLength> textData;
    if ( aTextResourceId )
        {
        iCoeEnv->ReadResource( textData, aTextResourceId );
        }

    CAknTextQueryDialog* dlg;
    if ( !aPromptResoureId )
        {
        dlg = new(ELeave)CAknTextQueryDialog(
            textData, CAknQueryDialog::ENoTone );
        }
    else
        {
        TBuf<KAknExQueryTextBufLength> prompt;
        iCoeEnv->ReadResource(prompt, aTextResourceId);
        dlg = CAknTextQueryDialog::NewL(
            textData, CAknQueryDialog::ENoTone );
        CleanupStack::PushL(dlg);
        dlg->SetPromptL(prompt);
        CleanupStack::Pop(); // dlg
        }

    if (aMaxLength)
        {
        dlg->SetMaxLength(aMaxLength);
        }

    TBool answer( dlg->ExecuteLD( aQueryResourceId ) );
    
    if ( aDisplayFlag && answer)
        {
        iLabelResultMessage->SetTextL( textData ); 
        }

    iDisplayDialog = EFalse;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::ShowTimeQueryL
// Display of Time Query.
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::ShowTimeQueryL(
                                 TInt aResourceQueryId, 
                                 TInt aResourceValueId, 
                                 TInt aResourcePromptId)
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    TBuf<KAknExQueryTextBufLength> textData;
   
    TTime value;
    iCoeEnv->ReadResource( textData, aResourceValueId); 
    value.Set( textData );

    CAknTimeQueryDialog* dlg;
    if ( !aResourcePromptId )
        {
        dlg = CAknTimeQueryDialog::NewL( value, CAknQueryDialog::ENoTone );
        }
    else
        {
        TBuf<KAknExQueryTextBufLength> prompt;
        iCoeEnv->ReadResource( prompt, aResourceValueId);
        dlg = CAknTimeQueryDialog::NewL( value, CAknQueryDialog::ENoTone );
        CleanupStack::PushL(dlg);
        dlg->SetPromptL(prompt);
        CleanupStack::Pop(); //dlg
        }

    dlg->ExecuteLD( aResourceQueryId );     

    iDisplayDialog = EFalse;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::ShowDurationLayoutL
// Display of Duration Query.
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::ShowDurationLayoutL()
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    TTimeIntervalSeconds duration;
    CAknDurationQueryDialog* dlg = CAknDurationQueryDialog::NewL(
        duration, CAknQueryDialog::ENoTone );
    dlg->ExecuteLD( R_AKNEXQUERY_DURATION_LAYOUT );

    iDisplayDialog = EFalse;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::ShowNumberLayoutL
// Display of Number Query.
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::ShowNumberLayoutL(
                           const TInt aResourceId, 
                           const TInt /* aTextResourceId */, 
                           const TInt aQueryValue, 
                           TInt aMinimumValue, 
                           TInt aMaximumValue)
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    TInt number(aQueryValue);

    CAknNumberQueryDialog* dlg;
    
      
    if (aMinimumValue || aMaximumValue)
        {
        dlg = new (ELeave) CAknNumberQueryDialog (number);
        dlg->PrepareLC( aResourceId );
        dlg->SetEmergencyCallSupport(EFalse);
        dlg->SetMinimumAndMaximum( aMinimumValue, aMaximumValue );
        dlg->RunLD();
        }
    else
        {
        dlg = CAknNumberQueryDialog::NewL( 
                    number, CAknQueryDialog::ENoTone);
        dlg->ExecuteLD( aResourceId ); 
        }

    iDisplayDialog = EFalse;
    }



// ----------------------------------------------------------------------------
// CAknExQueryContainer::ShowPopupSubMenuLayoutL( TBool aTitle )
// Display sub popmenu
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::ShowPopupSubMenuLayoutL( TBool aTitle )
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    CEikTextListBox* listPane = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( listPane );

    CAknPopupList* popupList = CAknPopupList::NewL(
       listPane,
       R_AVKON_SOFTKEYS_SELECT_CANCEL,
       AknPopupLayouts::EMenuWindow);

    CleanupStack::PushL( popupList );

    listPane->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    listPane->CreateScrollBarFrameL( ETrue );
    listPane->ScrollBarFrame()->SetScrollBarVisibilityL(
        CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );
    listPane->SetSize( AKNEXQUERY_POPUP_MENU_SIZE );

    if ( aTitle )
        {
        TBuf<KAknExQueryTextBufLength> titleData;
        iCoeEnv->ReadResource( titleData, R_AKNEXQUERY_SUB_POPUP_TITLE );
        popupList->SetTitleL( titleData );
        }
    
    CEikImage* image = new (ELeave) CEikImage();	
    CleanupStack::PushL(image);
    CFbsBitmap* bitmap = iEikonEnv->CreateBitmapL(
        KAknExQueryMbmFilePath, EMbmAknexqueryAnchor_id);
    CleanupStack::PushL(bitmap);
    CFbsBitmap* mask = iEikonEnv->CreateBitmapL(
        KAknExQueryMbmFilePath, EMbmAknexqueryAnchor_id_mask);
    CleanupStack::PushL(mask);
    image->SetBitmap(bitmap);
    image->SetMask(mask);
    popupList->Heading()->SetHeaderImageL(image);
    CleanupStack::Pop(2); // mask and bitmap
    CleanupStack::PopAndDestroy();  // image...mask and bitmap are also deleted
                                    // when image is deleted. 
    
    CDesCArray* array = NULL;
    array = iCoeEnv->ReadDesCArrayResourceL(R_AKNEXQUERY_SUB_POPUP_DATA);
    CleanupStack::PushL(array);

    CDesCArrayFlat* items =
        new( ELeave ) CDesCArrayFlat( KAknExQueryArrayFlatResourceId );
    CleanupStack::PushL( items );


    for ( TInt i(0) ; i < 5 ; i += 1)
        {
        items->AppendL( (*array)[i] );
        }

    CTextListBoxModel* model = listPane->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );
    CleanupStack::Pop(); // items - listbox model now owns this

    popupList->ExecuteLD();
    CleanupStack::PopAndDestroy(); // array
    CleanupStack::Pop(); // popupList
    CleanupStack::PopAndDestroy(); // listPane

    // delete array;
    iDisplayDialog = EFalse;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::ShowListQueryL( const TInt aResourceId )
// Display of List Query.
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::ShowListQueryL( const TInt aResourceId )
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE ); 
    CArrayFixFlat<TInt>* indexArray = NULL;
    CAknListQueryDialog* dlg;
    TInt index( 0 );

    if ( aResourceId == R_AKNEXQUERY_MULTI_SELECTION_LIST_QUERY)
        {
        
        indexArray = new(ELeave)CArrayFixFlat<TInt>(6);
        CleanupStack::PushL(indexArray);
        dlg = new (ELeave) CAknListQueryDialog(indexArray);
        
        }
    else
        {
        dlg = new( ELeave ) CAknListQueryDialog( &index );
        }

    TInt answer( dlg->ExecuteLD( aResourceId ) );

    TBuf<KAknExQueryTextBufLength> text;
    if ( aResourceId == R_AKNEXQUERY_LIST_QUERY )
        {
        if ( answer )
            {
            TBuf<KAknExQueryTextBufLength> baseText;
            iCoeEnv->ReadResource(baseText, R_AKNEXQUERY_ITEM_SELECTED);
            text.Format(baseText, index+1);
            ShowMessageL( text );
            }
        else
            {
            iCoeEnv->ReadResource(text, R_AKNEXQUERY_QUERYDISCARDED);
            ShowMessageL( text );
            }
        }

    if  (indexArray)
        {
        CleanupStack::PopAndDestroy();
        }
    iDisplayDialog = EFalse;
    }


// ----------------------------------------------------------------------------
// CAknExQueryContainer::PopoutListBoxL( TInt aCommand )
// Create handler.
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::PopoutListBoxL( TInt aCommand )
    {
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    if ( CreateListBoxL( aCommand ) )
        {
        iHandler->HandleListBoxEventL(
            iListBox, MEikListBoxObserver::EEventEnterKeyPressed );
        }
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::CreateListBoxL( TInt aCommand )
// Creates listbox object.
// ----------------------------------------------------------------------------
//
TBool CAknExQueryContainer::CreateListBoxL( TInt aCommand )
    {
    DeleteListBoxL();

    TInt resourceId;
    switch ( aCommand )
        {
        case EAknExQueryOutline7:
            iHandler = new( ELeave ) CAknExQueryEditorListEventHandler( this );
            resourceId = R_AKNEXQUERY_EDITOR_LIST_ITEM;
            break;
        case EAknExQueryOutline9:
            iHandler = new( ELeave ) CAknExQueryKeyListEventHandler( this );
            resourceId = R_AKNEXQUERY_KEY_LIST_ITEM;
            break;
        case EAknExQueryOutline32:
            iHandler = new( ELeave ) CAknExQueryIconListEventHandler( this );
            resourceId = R_AKNEXQUERY_ICON_LIST_ITEM;
            break;
        case EAknExQueryOutline34:
            iHandler = new( ELeave ) CAknExQueryRollerListEventHandler( this );
            resourceId = R_AKNEXQUERY_ROLLER_LIST_ITEM;
            break;
        case EAknExQueryOutline39:
            iHandler =
                new( ELeave ) CAknExQueryTextAndTextListEventHandler( this );
            resourceId = R_AKNEXQUERY_MULTILINE_TEXT_AND_TEXT_LIST_ITEM;
            break;
        case EAknExQueryOutline40:
            iHandler =
                new( ELeave ) CAknExQueryTextAndTimeListEventHandler( this );
            resourceId = R_AKNEXQUERY_MULTILINE_TEXT_AND_TIME_LIST_ITEM;
            break;
        case EAknExQueryOutline41:
            iHandler =
                new( ELeave ) CAknExQueryTimeAndTimeListEventHandler( this );
            resourceId = R_AKNEXQUERY_MULTILINE_TIME_AND_TIME_LIST_ITEM;
            break;
        case EAknExQueryOutline42:
            iHandler =
                new( ELeave ) CAknExQueryTextAndNumberListEventHandler( this );
            resourceId = R_AKNEXQUERY_MULTILINE_TEXT_AND_NUMBER_LIST_ITEM;
            break;
        case EAknExQueryOutline43:
            iHandler =
                new( ELeave ) CAknExQueryTextAndDurationListEventHandler(
                    this );
            resourceId = R_AKNEXQUERY_MULTILINE_TEXT_AND_DURATION_LIST_ITEM;
            break;
        case EAknExQueryOutline44:
            iHandler =
                new( ELeave ) CAknExQueryTimeAndDurationListEventHandler(
                    this );
            resourceId = R_AKNEXQUERY_MULTILINE_TIME_AND_DURATION_LIST_ITEM;
            break;
        case EAknExQueryOutline112:
            iHandler = new( ELeave ) CAknExQueryEditorListEventHandler( this );
            resourceId = R_AKNEXQUERY_EDITOR_LIST_ITEM;
            break;
        default:
            return( EFalse );
        }

    TInt flags( CEikListBox::EPopout | CEikListBox::ELeftDownInViewRect );
    iListBox = new( ELeave ) CEikColumnListBox;
    iListBox->ConstructL( this, flags );

    iListBox->SetListBoxObserver( iHandler );
    iListBox->SetBorder( TGulBorder::EShallowRaised );
    iListBox->CreateScrollBarFrameL( ETrue );
    iListBox->ScrollBarFrame()->SetScrollBarVisibilityL(
        CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );

    // Creates list items
    CDesCArray* textArray = iCoeEnv->ReadDesCArrayResourceL( resourceId );
    iListBox->Model()->SetItemTextArray( textArray );
    iListBox->Model()->SetOwnershipType( ELbmOwnsItemArray );

    // Sets pixel values of width.
    TRect rect(TPoint(KAknExQueryListBoxRectPointX, 
        KAknExQueryListBoxRectPointY),
        TSize(KAknExQueryListBoxRectWidth, 
        KAknExQueryListBoxRectHeight)  );

    CColumnListBoxData* columnData = iListBox->ItemDrawer()->ColumnData();
    columnData->SetColumnWidthPixelL( KAknExQueryNameColumnIndex,
                                      rect.Width() );
    columnData->SetColumnWidthPixelL( KAknExQueryNameGapColumnIndex,
                                      rect.Width() );

    // Gets current number of list box items.
    TInt numberOfItems( iListBox->Model()->NumberOfItems() );
    // Gets new height of list box.
    TInt height( iListBox->CalcHeightBasedOnNumOfItems( numberOfItems ) );
    // If new height is less than defined height of list box
    // sets new height to list box height.
    if ( height < rect.Height() )
        {
        rect.SetHeight( height );
        }
    
    iListBox->SetRect( rect ); // Sets rectangle of list box.
    ActivateL();
    
    return( ETrue );
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::DeleteListBoxL()
// Deletes listbox object.
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::DeleteListBoxL()
    {
    if ( iListBox )
        {
        delete iListBox;
        iListBox = NULL;
        }
    if ( iHandler )
        {
        delete iHandler;
        iHandler = NULL;
        }
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::CreateLabelL( TInt aResourceId )
// Creates label object.
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::CreateLabelL( TInt aResourceId )
    {
    if ( !iLabelResultMessage )
        {
        iLabelResultMessage = new( ELeave ) CEikLabel;
        iLabelResultMessage->SetContainerWindowL( *this );
        iLabelResultMessage->SetRect( Rect() );
        iLabelResultMessage->SetAlignment( EHCenterVTop );
        iLabelResultMessage->SetPosition( AKNEXQUERY_LABEL2_POSITION );
        iLabelResultMessage->SetFont( LatinBold19() );
        }

    TBuf<KAknExQueryTextBufLength> labelText;
    iCoeEnv->ReadResource( labelText, aResourceId );
    iLabelResultMessage->SetTextL( labelText );
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::DeleteLabelL()
// Deletes label object.
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::DeleteLabelL()
    {
    delete iLabelResultMessage;
    iLabelResultMessage = NULL;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::SetTextToLabelL( TInt aResourceId )
// Set Label text.
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::SetTextToLabelL( TInt aResourceId )
    {
    TBuf<KAknExQueryTextBufLength> messageString;
    iCoeEnv->ReadResource( messageString, aResourceId );
    iLabel->SetTextL( messageString );
    DrawNow();
    }


// ----------------------------------------------------------------------------
// CAknExQueryContainer::ShowMessageL(const TDesC& aMessage) 
// Show Message.
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::ShowMessageL(const TDesC& aMessage)
    {
    iLabelResultMessage->SetTextL( aMessage );
    DrawNow();
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::ShowMessageQueryL() 
// Show Message Query.
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::ShowMessageQueryL()
    {
    iDisplayDialog = ETrue;
    HBufC* message= HBufC::NewLC(10000); 
    //CleanupStack::PushL(message);
    
    TBuf<KAknExQueryTextBufLength> messageFormat;
    
    iCoeEnv->ReadResource(messageFormat,  R_AKNEXQUERY_MESSAGE_TEXT4);
    TBuf<KAknExQueryTextBufLength> messageString; 
    //"Very long text entry for message query %d. "
    messageString.Format(messageFormat, 1);
    message->Des().Format(messageString); 
    //"Now two empty lines:\n\n\n...and text continues\n"
    iCoeEnv->ReadResource(messageString, R_AKNEXQUERY_MESSAGE_TEXT5);
    message->Des().Append(messageString);
    //"Crap text many lines:\n"
    iCoeEnv->ReadResource(messageString, R_AKNEXQUERY_MESSAGE_TEXT6);
    message->Des().Append(messageString);

    //"Loop:\n"
    TBuf<KAknExQueryTextBufLength> messageString2; 
    iCoeEnv->ReadResource(messageString2, R_AKNEXQUERY_MESSAGE_TEXT7);

    for (TInt ii( 0 ); ii < 80; ii++)
        {
        message->Des().Append(messageString2);
        message->Des().AppendNum(ii);
        message->Des().Append(messageString);
        }
    //"\nTHE END!"
    iCoeEnv->ReadResource(messageString, R_AKNEXQUERY_MESSAGE_TEXT8);
    message->Des().Append(messageString);    

    //"Ari's header";
    TPtrC messagePtrC(message->Des());
    CAknMessageQueryDialog* dlg = CAknMessageQueryDialog::NewL(messagePtrC); 
    CleanupStack::PopAndDestroy(); // message
    dlg->PrepareLC(R_AVKON_MESSAGE_QUERY_DIALOG);
    
    HBufC* header = HBufC::NewLC(30); 
    iCoeEnv->ReadResource(messageString, R_AKNEXQUERY_HEADING_TEXT);
    header->Des().Append(messageString);
    TPtrC headerPtrC(header->Des());
    dlg->QueryHeading()->SetTextL(headerPtrC);
    CleanupStack::PopAndDestroy(); // header
    
    dlg->RunLD();

    iDisplayDialog = EFalse;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::ShowDataQueryWithHeadingLineL(const TInt aResouceId,
//                           const TInt aTextId=NULL)
// Show Query With Heading Text.
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::ShowQueryWithHeadingLineL(const TInt aResouceId,
                                      const TInt aTextId)
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    TBuf<KAknExQueryTextBufLength> longText;
	TBuf<KAknExQueryTextBufLength> prompt;
    iCoeEnv->ReadResource(prompt, aResouceId);
   //__UHEAP_MARK; 

    CAknTextQueryDialog* dlg = CAknTextQueryDialog::NewL(
        longText, CAknQueryDialog::ENoTone);
    CleanupStack::PushL(dlg);
    dlg->SetPromptL(prompt);
    CleanupStack::Pop(); //dlg
   
    if (aTextId)
        {
        TBuf<128> string;
        iCoeEnv->ReadResource(string, aTextId);
        dlg->QueryHeading()->SetTextL(string);
        dlg->SetPromptL(string);
        }

    dlg->ExecuteLD(R_AKNEXQUERY_DATA_QUERY_WITH_HEADING);
   
    //__UHEAP_MARKEND; 
    iDisplayDialog = EFalse;
    }


// ----------------------------------------------------------------------------
// CAknExQueryContainer::OfferKeyEventL( const TKeyEvent&, TEventCode )
// Handles the key events.
// ----------------------------------------------------------------------------
//
TKeyResponse CAknExQueryContainer::OfferKeyEventL(
    const TKeyEvent& aKeyEvent,
    TEventCode aType )
    {
    if ( aType != EEventKey )
        {
        return EKeyWasNotConsumed;
        }
    switch ( aKeyEvent.iCode )
        {
        case EKeySpace:
            if ( iDisplayDialog )
                {
                return EKeyWasNotConsumed;
                }
            iView->DisplayNextOutlineL();
            DrawNow();
            break;
        default:
            if ( !iDisplayDialog && iListBox )
                {
                return iListBox->OfferKeyEventL( aKeyEvent, aType );
                }
            else
                {
                return EKeyWasNotConsumed;
                }
        }
    return EKeyWasConsumed;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::SizeChanged()
// Called by framework when the view size is changed
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::SizeChanged()
    {
    if ( iLabel )
        {
        iLabel->SetExtent( AKNEXQUERY_LABEL_ORIGIN, Size() );
        iLabel->SetAlignment( EHCenterVCenter );
        }
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::CountComponentControls() const
//  Returns number of component.
// ----------------------------------------------------------------------------
//
TInt CAknExQueryContainer::CountComponentControls() const
    {
    TInt count( KAknExQueryCountComponentControls );
    if ( iLabelResultMessage )
        {
        count++;
        }
    if ( iListBox )
        {
        count++;
        }
    return count;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::ComponentControl(TInt aIndex) const
// Returns pointer to particular component.
// ----------------------------------------------------------------------------
//
CCoeControl* CAknExQueryContainer::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex )
        {
        case EAknExQueryComponentLabel:
            return iLabel;
        case EAknExQueryComponentLabel2:
            if ( iLabelResultMessage )
                {
                return iLabelResultMessage;
                }
            else
                {
                return iListBox;
                }
        case EAknExQueryComponentListBox:
            return iListBox;
        default:
            return NULL;
        }
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::Draw(const TRect& aRect) const
// 
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAknExQueryGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }


// ----------------------------------------------------------------------------
// CAknExQueryContainer::ShowMultiLineNumberAndNumberLayoutL
// Display of MultiLineNumber Query                                             
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::ShowMultiLineNumberAndNumberLayoutL()
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    TInt topData(0);
    TInt bottomData(0);

    CAknMultiLineDataQueryDialog* dlg =
        CAknMultiLineDataQueryDialog::NewL( topData, bottomData );

    dlg->ExecuteLD( R_AKNEXQUERY_MULTI_LINE_NUMBER_AND_NUMBER_LAYOUT);

    iDisplayDialog = EFalse;
    }


// ----------------------------------------------------------------------------
// CAknExQueryContainer::DoRunDlgL
// Call CAknQueryDialog::RunDlgLD.
// ----------------------------------------------------------------------------
void CAknExQueryContainer::DoRunDlgL(TInt aResouceId)
    {
    CAknQueryDialog* dlg = CAknQueryDialog::NewL(
        CAknQueryDialog::ENoTone);
    dlg->ExecuteLD(aResouceId);
    }


// ----------------------------------------------------------------------------
// CAknExQueryContainer::ShowMultiLineTextAndTextLayoutL
// Display of MultiLineText Query.
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::ShowMultiLineTextAndTextLayoutL(
    const TInt  aResouceId,
    const TInt  aTopResourceId,
    const TInt  aBottomResourceId,
    const TBool aSetPromptFlag,
    const TInt  aLengthOfFirstEditor,
    const TInt  aLengthOfSecondEditor)
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    TBuf<KAknExQueryTextBufLength> topData;
    TBuf<KAknExQueryTextBufLength> bottomData;

    if ( aResouceId == R_AKNEXQUERY_MULTI_LINE_DATA_AND_DATA_LAYOUT)
        {
        if ( aTopResourceId != KAknExQueryInitialId )
            {
            iCoeEnv->ReadResource( topData, aTopResourceId );
            }
        if ( aBottomResourceId != KAknExQueryInitialId )
            {
            iCoeEnv->ReadResource( bottomData, aBottomResourceId );
            }
        }

    CAknMultiLineDataQueryDialog* dlg = 
            CAknMultiLineDataQueryDialog::NewL( topData, bottomData );

    if (aSetPromptFlag)
        {
        dlg->SetPromptL(topData, bottomData );
        }

    if ( aLengthOfFirstEditor || aLengthOfSecondEditor)
        {
        dlg->PrepareLC(aResouceId);

        if (aLengthOfFirstEditor)
            {
            dlg->SetMaxLengthOfFirstEditor(aLengthOfFirstEditor);
            }
        if (aLengthOfSecondEditor)
            {
            dlg->SetMaxLengthOfSecondEditor(aLengthOfSecondEditor);
            }

        dlg->RunLD();
        }
    else
        {
        dlg->ExecuteLD( aResouceId );
        }

    iDisplayDialog = EFalse;
    }


// ----------------------------------------------------------------------------
// CAknExQueryContainer::ShowMultiLineTextAndNumberLayoutL
// Display of MultiLine Text with number Query
// ----------------------------------------------------------------------------    
void CAknExQueryContainer::ShowMultiLineTextAndNumberLayoutL(
    const TInt aResourceId)
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    TBuf<KAknExQueryTextBufLength> topData;
    TInt bottomData(0);

    CAknMultiLineDataQueryDialog* dlg =
        CAknMultiLineDataQueryDialog::NewL( topData, bottomData );

    dlg->ExecuteLD( aResourceId );

    iDisplayDialog = EFalse;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::ShowMultiLineTextAndLDurationLayoutL
// Display of MultiLine Text with Duration Query
// ----------------------------------------------------------------------------   
void CAknExQueryContainer::ShowMultiLineTextAndLDurationLayoutL(
    const TInt aResourceId)
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    TBuf<KAknExQueryTextBufLength> topData;
    TTimeIntervalSeconds bottomData( 0 );

    CAknMultiLineDataQueryDialog* dlg =
        CAknMultiLineDataQueryDialog::NewL( topData, bottomData );
    dlg->ExecuteLD( aResourceId );

    iDisplayDialog = EFalse;
    }


// ----------------------------------------------------------------------------
// CAknExQueryContainer::ShowMultiLineTimeAndDurationLayoutL
// Display of MultiLine Time with Duration Query
// ----------------------------------------------------------------------------
void CAknExQueryContainer::ShowMultiLineTimeAndDurationLayoutL(
     const TInt aResourceId, 
    const TInt aTopResourceId)
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    TBuf<KAknExQueryTextBufLength> topData;
    TTimeIntervalSeconds bottomData;
    TTime topTime;
    iCoeEnv->ReadResource( topData, aTopResourceId );
    topTime.Set( topData );

    CAknMultiLineDataQueryDialog* dlg =
        CAknMultiLineDataQueryDialog::NewL( topTime, bottomData );
    dlg->ExecuteLD( aResourceId );

    iDisplayDialog = EFalse;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::DoSetItemTextArrayL()
// Set item dynamically
// ----------------------------------------------------------------------------
void CAknExQueryContainer::DoSetItemTextArrayL()
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    CDesCArrayFlat* items =
        new( ELeave ) CDesCArrayFlat( KAknExQueryArrayFlatResourceId );
    CleanupStack::PushL( items );
    

    CDesCArray *array = NULL;
    array = iCoeEnv->ReadDesCArrayResourceL(R_AKNEXQUERY_SUB_POPUP_DATA);
    CleanupStack::PushL(array);

    for ( TInt i(0) ; i < 5 ; i += 1)
        {
        items->AppendL( (*array)[i] );
        }

    TInt index(0);
    CAknListQueryDialog* dlg = new(ELeave) CAknListQueryDialog(&index);
    dlg->PrepareLC(R_AKNEXQUERY_LIST_QUERY);
    dlg->SetItemTextArray(items);

    dlg->SetOwnershipType(ELbmDoesNotOwnItemArray);
    dlg->RunLD();
    CleanupStack::PopAndDestroy(); // items with array
    CleanupStack::PopAndDestroy(); // items with array
    iDisplayDialog = EFalse;
    }


// ----------------------------------------------------------------------------
// CAknExQueryContainer::ShowMultiLineTimeAndTimeLayoutL
// Display of MultiLine Time with Time Query
// ----------------------------------------------------------------------------
void CAknExQueryContainer::ShowMultiLineTimeAndTimeLayoutL(
        const TInt aResourceId,
        const TInt aTopResourceId,
        const TInt aBottomResourceId)
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    TBuf<KAknExQueryTextBufLength> topData;
    TBuf<KAknExQueryTextBufLength> bottomData;
    TTime topTime;
    TTime bottomTime;
    iCoeEnv->ReadResource( topData, aTopResourceId );
    topTime.Set( topData );
    iCoeEnv->ReadResource( bottomData, aBottomResourceId );
    bottomTime.Set( bottomData );

    CAknMultiLineDataQueryDialog* dlg =
        CAknMultiLineDataQueryDialog::NewL( topTime, bottomTime );
    dlg->ExecuteLD( aResourceId );

    iDisplayDialog = EFalse;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::ShowMultiLineTextAndTimeLayoutL
// Display of MultiLine Text with Time Query
// ----------------------------------------------------------------------------
void CAknExQueryContainer::ShowMultiLineTextAndTimeLayoutL(
    const TInt aResourceId,
    const TInt aBottomResourceId )
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    TBuf<KAknExQueryCodeBufLength> topData;
    TBuf<KAknExQueryTextBufLength> bottomData;
    TTime bottomDate;
    iCoeEnv->ReadResource( bottomData, aBottomResourceId );
    bottomDate.Set( bottomData );
          
 
    CAknMultiLineDataQueryDialog* dlg =
        CAknMultiLineDataQueryDialog::NewL( topData, bottomDate );
    dlg->ExecuteLD( aResourceId );

    iDisplayDialog = EFalse;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::ShowGlobalMessageQueryL(
//                const TTimerUpdateType& aUpdateType) 
// Show Global Message Query
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::ShowGlobalMessageQueryL(
                                           const TTimerUpdateType& aUpdateType)
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    if (!iGlobalMsgQuery)
        {
        iGlobalMsgQuery = CAknGlobalMsgQuery::NewL();
        }
    delete iGlobalListObserver;
    iGlobalListObserver = NULL;
    iGlobalListObserver = CAknExQueryGlobalListObserver::NewL( this );
    
    iGlobalListObserver->SetSelectItemFlag();
    iGlobalListObserver->Start();

    HBufC* messageText = HBufC::NewLC(KAknExQueryTextLargeMessageLength);

    // Read message from resouce
    for (TInt   i(R_AKNEXQUERY_MESSAGE_TEXT1);
                i <= R_AKNEXQUERY_MESSAGE_TEXT3 ; i += 1)
        {
        TBuf<KAknExQueryTextMaxLength> temp;
        iCoeEnv->ReadResource(temp, i);
        messageText->Des() += temp;
        }

    TBuf<KAknExQueryTextBufLength> headerText;
    iCoeEnv->ReadResource( headerText, R_AKNEXQUERY_HEADING_TEXT );


    
    iGlobalMsgQuery->ShowMsgQueryL( iGlobalListObserver->iStatus,
                                    *messageText,               
                                    R_AVKON_SOFTKEYS_ANSWER_EXIT,
                                    headerText, 
                                    KAvkonMbmFilePath,
                                    EMbmAvkonQgn_indi_checkbox_on,
                                    EMbmAvkonQgn_indi_checkbox_on_mask);

    CleanupStack::PopAndDestroy(); //messageText
    iGlobalListObserver->UnsetSelectItemFlag();
    StartTimerL(3000000, 50000000, aUpdateType);
    iDisplayDialog = EFalse;
    }


// ----------------------------------------------------------------------------
// CAknExQueryContainer::StartTimerL
//
// ----------------------------------------------------------------------------
void CAknExQueryContainer::StartTimerL(TInt aStart, TInt aInterval, 
                              const TTimerUpdateType& aUpdateType)
	{
    DeleteTimer();

    iTimer = CPeriodic::NewL(EPriorityLow);
	iTimerUpdateType = aUpdateType;
    
	iTimer->Start(aStart, aInterval, TCallBack(TimerCallbackL, this));
	}

// ----------------------------------------------------------------------------
// CAknExQueryContainer::TimerCallbackL
//
// ----------------------------------------------------------------------------
TInt CAknExQueryContainer::TimerCallbackL(TAny* aThis)
	{
    static_cast<CAknExQueryContainer*>(aThis)->ProcessTimerEventL();
	return 0;
	}

// ----------------------------------------------------------------------------
// CAknExQueryContainer::ProcessTimerEventL
//
// ----------------------------------------------------------------------------
void CAknExQueryContainer::ProcessTimerEventL()
    {
    if (iGlobalMsgQuery && iTimerUpdateType == EUpdateGlobalQuery )
		{
        iGlobalMsgQuery->UpdateMsgQuery(R_AVKON_SOFTKEYS_EXIT);
        iTimerUpdateType = ECancelGlobalQuery;
        }
    else if (iGlobalMsgQuery && iTimerUpdateType == ECancelGlobalQuery )
		{
        iTimerUpdateType = ENoUpdate;
		iGlobalMsgQuery->CancelMsgQuery();
        DeleteTimer();
        }
    else if (iGlobalListQuery && iTimerUpdateType == ECancelListQuery)
        {
    	iGlobalListQuery->CancelListQuery();
        DeleteTimer();
        }
    else if (iPopupList && iTimerUpdateType == ECancelPopupList)
        {
        iPopupList->CancelPopup();
        DeleteTimer();
        }
    else if (iGlobalListQuery && iTimerUpdateType == EUpdateGlobalListQueryUp)
		{
        iGlobalListQuery->MoveSelectionUp();
		iTimerUpdateType = EUpdateGlobalListQueryDown;
		DeleteTimer();
		}
    else if (iGlobalListQuery && iTimerUpdateType == EUpdateGlobalListQueryDown)
		{
        iGlobalListQuery->MoveSelectionDown();
		iTimerUpdateType = EUpdateGlobalListQuerySelect;
		DeleteTimer();
        }
	else if (iGlobalListQuery && iTimerUpdateType 
                        == EUpdateGlobalListQuerySelect)
		{
        iGlobalListQuery->SelectItem();
        iTimerUpdateType = ENoUpdate;
        DeleteTimer();
        }
    else if (iQueryDialog && iTimerUpdateType == ECancelQueryAnim)
        {
        CAknQueryControl* control = STATIC_CAST(CAknQueryControl*,
                                   iQueryDialog->ControlOrNull(EGeneralQuery));
        control->CancelAnimation();
        DeleteTimer();
        }
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::DoSetIconArrayL
// Set icon to array dynamically.
// ----------------------------------------------------------------------------
void CAknExQueryContainer::DoSetIconArrayL()
    {
    TInt index( 0 );
    CAknListQueryDialog* dialog = new( ELeave ) CAknListQueryDialog( &index );
    dialog->PrepareLC(R_AKNEXQUERY_MULTI_SELECTION_QUERY);

    CArrayPtr<CGulIcon>* icons = new (ELeave) CAknIconArray(10);
    CleanupStack::PushL(icons);


    icons->AppendL(iEikonEnv->CreateIconL(KAvkonMbmFilePath, 
        EMbmAvkonQgn_indi_marked_add, EMbmAvkonQgn_indi_marked_add_mask));
    icons->AppendL(iEikonEnv->CreateIconL(KAvkonMbmFilePath,
        EMbmAvkonQgn_prop_folder_medium,EMbmAvkonQgn_prop_folder_medium_mask));

    dialog->SetIconArrayL(icons);
    dialog->RunLD();
    CleanupStack::Pop(); //icons
    }

void CAknExQueryContainer::DeleteTimer()
    {
    delete iTimer;
    iTimer = NULL;
    }
// ----------------------------------------------------------------------------
// CAknExQueryContainer::SetIconL
// Set Icon dynamically
// ----------------------------------------------------------------------------
void CAknExQueryContainer::SetIconL(CAknQueryDialog* aDlg,
                                    TInt32 aBitmap, 
                                    TInt32 aMask)
    {
    CEikImage* image = new (ELeave) CEikImage();	
    CleanupStack::PushL(image);

    CFbsBitmap* bitmap = iEikonEnv->CreateBitmapL(
        KAknExQueryMbmFilePath, aBitmap);
    CleanupStack::PushL(bitmap);
    CFbsBitmap* mask = iEikonEnv->CreateBitmapL(
        KAknExQueryMbmFilePath, aMask);
    CleanupStack::PushL(mask);

    image->SetBitmap(bitmap);
    image->SetMask(mask);
    CleanupStack::Pop(2); //mask and bitmap
 
    aDlg->QueryHeading()->SetHeaderImageL(image);
    CleanupStack::PopAndDestroy(); //image 
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::ShowCodeQueryL(const TInt aLength)
// Display of Code Query.
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::ShowCodeQueryL(
     const TInt aLength, TDesC* aDefaultText)
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    TBuf<KAknExQueryCodeBufLength> textData;

    if (aDefaultText && aDefaultText->Length() <= KAknExQueryCodeBufLength)
        {
        textData = *aDefaultText;
        }

    CAknTextQueryDialog* dlg =
        new( ELeave ) CAknTextQueryDialog( textData,
                                           CAknQueryDialog::ENoTone );

	if (aLength)
		{
		dlg->PrepareLC(R_AKNEXQUERY_CODE_QUERY);
		dlg->SetMaxLength(aLength);
		dlg->RunLD();
		}
	else
		{
		dlg->ExecuteLD( R_AKNEXQUERY_CODE_QUERY );
		}
    iDisplayDialog = EFalse;
    }


// ----------------------------------------------------------------------------
// CAknExQueryContainer::DoCancelPopUp()
// Cancel Popup.
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::DoCancelPopUp()
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );
    CEikTextListBox* list = new(ELeave)CEikTextListBox;
    CleanupStack::PushL(list);
    iPopupList = CAknPopupList::NewL(list, R_AVKON_SOFTKEYS_OK_BACK, AknPopupLayouts::EMenuWindow);
    CleanupStack::PushL(iPopupList);	
    list->ConstructL(iPopupList,CEikListBox::ELeftDownInViewRect);
    list->CreateScrollBarFrameL(ETrue);
    list->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);

    TBuf<50> buf;
    CDesCArrayFlat* items = new(ELeave)CDesCArrayFlat(1);
    CleanupStack::PushL(items);
    iCoeEnv->ReadResource( buf, R_AKNEXQUERY_LIST_ITEM4); 
    items->AppendL(buf);
    iCoeEnv->ReadResource( buf, R_AKNEXQUERY_LIST_ITEM5); 
    items->AppendL(buf);
    iCoeEnv->ReadResource( buf, R_AKNEXQUERY_LIST_ITEM6); 
    items->AppendL(buf);

    CTextListBoxModel* model=list->Model();
    model->SetItemTextArray(items);
    model->SetOwnershipType(ELbmOwnsItemArray);


    iCoeEnv->ReadResource( buf, R_AKNEXQUERY_LIST_TITLE2); 
    iPopupList->SetTitleL(buf);

    StartTimerL(3000000, 10000000, ECancelPopupList);
    TInt answer(iPopupList->ExecuteLD());
    DeleteTimer();

    if (answer)
        {
        iCoeEnv->ReadResource( buf, R_AKNEXQUERY_MESSAGE_TEXT10); 
        TInt index = list->CurrentItemIndex();
        TBuf<50> text;
        text.Format(buf, index+1);
        User::InfoPrint(text);
        }
    else
        {
        iCoeEnv->ReadResource( buf, R_AKNEXQUERY_MESSAGE_TEXT11); 
        User::InfoPrint(buf);
        }

    CleanupStack::Pop(2);			//items (destroyed by listbox). popupList
    CleanupStack::PopAndDestroy();	// list
    
    iDisplayDialog = EFalse;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::ShowGlobalListQueryL(const TTimerUpdateType& aUpdateType)
// 
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::ShowGlobalListQueryL(const TTimerUpdateType& aUpdateType)
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    CDesCArray* textArray = iCoeEnv->ReadDesCArrayResourceL(
       R_AKNEXQUERY_SUB_POPUP_DATA); 

    CleanupStack::PushL(textArray);

    if (iGlobalListObserver)
        {
        iGlobalListObserver->Cancel();
        delete iGlobalListObserver;
        iGlobalListObserver = NULL;
        }
    iGlobalListObserver = CAknExQueryGlobalListObserver::NewL( this );
    iGlobalListObserver->UnsetSelectItemFlag(); 

    iGlobalListObserver->Start();

    if (iGlobalListQuery)
        {
        delete iGlobalListQuery;
        iGlobalListQuery = NULL;
        }
    iGlobalListQuery = CAknGlobalListQuery::NewL();

    iGlobalListObserver->SetSelectItemFlag();
    iGlobalListQuery->ShowListQueryL(
        textArray, 
        iGlobalListObserver->iStatus,
        0);

    if (aUpdateType != ENoTimer)
        {
        StartTimerL(5000000, 10000000, aUpdateType); 
        }

    CleanupStack::PopAndDestroy(); // textArray
    iDisplayDialog = EFalse;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::DataLayoutFromControlByLayoutOrNull()
// 
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::DataLayoutFromControlByLayoutOrNull() 
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    CAknQueryDialog* dlg = CAknQueryDialog::NewL( CAknQueryDialog::ENoTone );
    dlg->PrepareLC(R_AKNEXQUERY_DATA_QUERY);

    CAknQueryControl* control = 
        STATIC_CAST(CAknQueryControl*,dlg->ControlOrNull(EGeneralQuery));
    
    CEikEdwin* edwin = STATIC_CAST(CEikEdwin*, 
           control->ControlByLayoutOrNull( EDataLayout ));
    edwin->SetTextL(&KAknExQueryDefaultDataText);

    dlg->RunLD();
    iDisplayDialog = EFalse;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::StaticSizeDataLayoutFromControlByLayoutOrNull()
// 
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::StaticSizeDataLayoutFromControlByLayoutOrNull() 
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    TBuf<KAknExQueryTextBufLength> temp;
    CAknTextQueryDialog* dlg = new (ELeave) 
        CAknTextQueryDialog(temp, CAknQueryDialog::ENoTone);
    
    dlg->PrepareLC( R_AKNEXQUERY_DATA_QUERY_WITH_HEADING );

    CAknQueryControl* control = 
        STATIC_CAST(CAknQueryControl*,dlg->ControlOrNull(EGeneralQuery));

    CEikEdwin* edwin = STATIC_CAST(CEikEdwin*, 
           control->ControlByLayoutOrNull( EStaticSizeDataLayout ));
    edwin->SetTextL(&KAknExQueryDefaultDataText);

    dlg->RunLD();
    iDisplayDialog = EFalse;
    }


// ----------------------------------------------------------------------------
// CAknExQueryContainer::PhoneLayoutFromControlByLayoutOrNull()
// 
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::PhoneLayoutFromControlByLayoutOrNull() 
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    TBuf<KAknExQueryTextBufLength> temp;
    CAknTextQueryDialog* dlg = new (ELeave) 
        CAknTextQueryDialog(temp, CAknQueryDialog::ENoTone);
    
    dlg->PrepareLC( R_AKNEXQUERY_PHONENUMBER_QUERY );

    CAknQueryControl* control = 
        STATIC_CAST(CAknQueryControl*,dlg->ControlOrNull(EGeneralQuery));

    CEikEdwin* edwin = STATIC_CAST(CEikEdwin*, 
           control->ControlByLayoutOrNull( EStaticSizeDataLayout ));

    if (edwin)
        {
        edwin->SetTextL(&KAknExQueryDefaultPhoneNumber);
        }

    dlg->RunLD();
    iDisplayDialog = EFalse;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::CodeLayoutFromControlByLayoutOrNull()
// 
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::CodeLayoutFromControlByLayoutOrNull() 
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    TBuf<KAknExQueryTextBufLength> temp;
    CAknTextQueryDialog* dlg = new (ELeave) 
        CAknTextQueryDialog(temp, CAknQueryDialog::ENoTone);
    
    dlg->PrepareLC( R_AKNEXQUERY_CODE_QUERY );

    CAknQueryControl* control = 
        STATIC_CAST(CAknQueryControl*,dlg->ControlOrNull(EGeneralQuery));

    CEikSecretEditor* secretEd = STATIC_CAST(CEikSecretEditor*, 
           control->ControlByLayoutOrNull( ECodeLayout ));

    if (secretEd)
        {
        secretEd->SetText(*&KAknExQueryDefaultDataText);
        }

    dlg->RunLD();
    iDisplayDialog = EFalse;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::DateLayoutFromControlByLayoutOrNull()
// 
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::DateLayoutFromControlByLayoutOrNull() 
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    TBuf<KAknExQueryTextBufLength> temp;
    TTime initialValue;
    iCoeEnv->ReadResource( temp, R_AKNEXQUERY_DATE_INITIAL_VALUE); 
    initialValue.Set( temp );

    CAknTimeQueryDialog* dlg = CAknTimeQueryDialog::NewL( 
        initialValue, CAknQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_AKNEXQUERY_DATE_QUERY );

    CAknQueryControl* control = 
        STATIC_CAST(CAknQueryControl*,dlg->ControlOrNull(EGeneralQuery));

    CEikDateEditor* dateEdwin = STATIC_CAST(CEikDateEditor*, 
           control->ControlByLayoutOrNull( EDateLayout ));

    if (dateEdwin)
        {
        TTime setValue;
        iCoeEnv->ReadResource( temp, R_AKNEXQUERY_DATE_INITIAL_VALUE2); 
        setValue.Set( temp );
        dateEdwin->SetDate(setValue);
        }

    dlg->RunLD();
    iDisplayDialog = EFalse;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::TimeLayoutFromControlByLayoutOrNull()
// 
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::TimeLayoutFromControlByLayoutOrNull() 
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    TBuf<KAknExQueryTextBufLength> temp;
    TTime initialValue;
    iCoeEnv->ReadResource( temp, R_AKNEXQUERY_TIME_INITIAL_VALUE); 
    initialValue.Set( temp );

    CAknTimeQueryDialog* dlg = CAknTimeQueryDialog::NewL( 
        initialValue, CAknQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_AKNEXQUERY_TIME_QUERY );

    CAknQueryControl* control = 
        STATIC_CAST(CAknQueryControl*,dlg->ControlOrNull(EGeneralQuery));

    CEikTimeEditor* timeEdwin = STATIC_CAST(CEikTimeEditor*, 
           control->ControlByLayoutOrNull( ETimeLayout ));
   
    if ( timeEdwin)
        {
        TTime setValue;
        iCoeEnv->ReadResource( temp, R_AKNEXQUERY_TIME_INITIAL_VALUE2); 
        setValue.Set( temp );
        timeEdwin->SetTime(setValue);
        }

    dlg->RunLD();
    iDisplayDialog = EFalse;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::DurationLayoutFromControlByLayoutOrNull()
// 
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::DurationLayoutFromControlByLayoutOrNull() 
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    TTimeIntervalSeconds duration;

    CAknDurationQueryDialog* dlg =  
        CAknDurationQueryDialog::NewL( duration, CAknQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_AKNEXQUERY_DURATION_LAYOUT );

    CAknQueryControl* control = 
        STATIC_CAST(CAknQueryControl*,dlg->ControlOrNull(EGeneralQuery));

    CEikDurationEditor* durationEdwin = STATIC_CAST(CEikDurationEditor*, 
           control->ControlByLayoutOrNull( EDurationLayout ));
   
    if (durationEdwin)
        {
        TTimeIntervalSeconds setValue(3600);
        durationEdwin->SetDuration(setValue);
        }

    dlg->RunLD();

    iDisplayDialog = EFalse;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::NumberLayoutFromControlByLayoutOrNull()
// 
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::NumberLayoutFromControlByLayoutOrNull() 
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    TInt value(0);

    CAknNumberQueryDialog*  dlg = 
        CAknNumberQueryDialog::NewL( value, CAknQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_AKNEXQUERY_NUMBER_LAYOUT );

    CAknQueryControl* control = 
        STATIC_CAST(CAknQueryControl*,dlg->ControlOrNull(EGeneralQuery));

    CAknIntegerEdwin* numberEdwin = STATIC_CAST(CAknIntegerEdwin*, 
           control->ControlByLayoutOrNull( ENumberLayout ));
   
    if (numberEdwin)
        {
        numberEdwin->SetUnsetValue(0);
        }
    dlg->RunLD();

    iDisplayDialog = EFalse;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::PinLayoutFromControlByLayoutOrNull()
// 
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::PinLayoutFromControlByLayoutOrNull() 
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    TBuf<KAknExQueryTextBufLength> text;

    CAknTextQueryDialog*  dlg = new( ELeave ) 
        CAknTextQueryDialog( text, CAknQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_AKNEXQUERY_PIN_QUERY );

    //CAknQueryControl* control = 
    //   STATIC_CAST(CAknQueryControl*,dlg->ControlOrNull(EGeneralQuery));

    //CAknNumericSecretEditor* pinEdwin = STATIC_CAST(
    //    CAknNumericSecretEditor*, control->ControlByLayoutOrNull(EPinLayout));

    //if (pinEdwin)
    //    {
    //    pinEdwin->RevealSecretText(ETrue);
    //    }

    dlg->RunLD();

    iDisplayDialog = EFalse;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::DoRemoveEditorIndicator()
// 
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::DoRemoveEditorIndicator()
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    CAknTextQueryDialog* dlg = new( ELeave ) CAknTextQueryDialog( 
        iTextData, CAknQueryDialog::ENoTone );

    dlg->PrepareLC(R_AKNEXQUERY_DATA_QUERY_NO_WAIT);
    dlg->RemoveEditorIndicator();
    dlg->RunLD();

    iDisplayDialog = EFalse;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::SetImageL()
// 
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::SetImageL()
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    CAknQueryDialog* dlg = CAknQueryDialog::NewL(CAknQueryDialog::ENoTone);

    dlg->PrepareLC(R_AKNEXQUERY_CONFIRMATION_QUERY);
    CAknQueryControl* control = 
        STATIC_CAST(CAknQueryControl*,dlg->ControlOrNull(EGeneralQuery));
    control->SetImageL(KAknExQueryMbmFilePath, 
        EMbmAknexqueryIndicato, EMbmAknexqueryIndicatom);
    dlg->RunLD();

    iDisplayDialog = EFalse;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::SetAnimationL()
// 
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::SetAnimationL()
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    CAknQueryDialog* dlg = CAknQueryDialog::NewL(CAknQueryDialog::ENoTone);

    dlg->PrepareLC(R_AKNEXQUERY_CONFIRMATION_NO_ICON_QUERY);
    CAknQueryControl* control = 
        STATIC_CAST(CAknQueryControl*,dlg->ControlOrNull(EGeneralQuery));

    control->SetAnimationL(R_QGN_NOTE_OK_ANIM);
    dlg->RunLD();

    iDisplayDialog = EFalse;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::SetAndCancelAnimationL()
// 
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::SetAndCancelAnimationL()
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    iQueryDialog = CAknQueryDialog::NewL(CAknQueryDialog::ENoTone);

    iQueryDialog->PrepareLC(R_AKNEXQUERY_CONFIRMATION_NO_ICON_QUERY);
    CAknQueryControl* control = 
        STATIC_CAST(CAknQueryControl*, iQueryDialog->ControlOrNull(EGeneralQuery));

    control->SetAnimationL(R_QGN_NOTE_OK_ANIM);
    StartTimerL(1200000, 50000000, ECancelQueryAnim);
    iQueryDialog->RunLD(); // Wait until query is dismissed.
    DeleteTimer(); 
    iQueryDialog = NULL;    
    iDisplayDialog = EFalse;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::ChangeMaxHightL()
// 
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::ChangeMaxHightL()
    {
    iDisplayDialog = ETrue;
    SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    CEikTextListBox* list = new( ELeave ) CAknSinglePopupMenuStyleListBox;
    CleanupStack::PushL( list );

    CAknPopupList* popupList = CAknPopupList::NewL(
       list,
       R_AVKON_SOFTKEYS_SELECT_CANCEL,
       AknPopupLayouts::EMenuWindow);

    CleanupStack::PushL( popupList );
    
    popupList->SetMaximumHeight(2);

    list->ConstructL( popupList, CEikListBox::ELeftDownInViewRect );
    list->CreateScrollBarFrameL( ETrue );
    list->ScrollBarFrame()->SetScrollBarVisibilityL(
        CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto );

    CDesCArray* items = iCoeEnv->ReadDesCArrayResourceL(R_AKNEXQUERY_SUB_POPUP_DATA);

    CTextListBoxModel* model = list->Model();
    model->SetItemTextArray( items );
    model->SetOwnershipType( ELbmOwnsItemArray );

    popupList->ExecuteLD();
    CleanupStack::Pop(); // popupList
    CleanupStack::PopAndDestroy(); // list

    iDisplayDialog = EFalse;
    }

// ----------------------------------------------------------------------------
// CAknExQueryContainer::ShowDeleteConfirmationQueryL()
// 
// ----------------------------------------------------------------------------
//
void CAknExQueryContainer::ShowDeleteConfirmationQueryL()
	{
    iDisplayDialog = ETrue;
	SetTextToLabelL( R_AKNEXQUERY_OPERATE_MESSAGE );

    HBufC* prompt = StringLoader::LoadLC(
		R_AKNEXQUERY_COMMON_CONF_DELETE, _L("it"));

    CAknQueryDialog* dlg = CAknQueryDialog::NewL();

	dlg->SetPromptL(prompt->Des());
    dlg->ExecuteLD( R_AKNEXQUERY_CONFIRMATION_QUERY );
	
	CleanupStack::PopAndDestroy(); //prompt

    iDisplayDialog = EFalse;
	}	
// End of File
