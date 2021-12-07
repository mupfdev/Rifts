/*
* =============================================================================
*  Name     : CAknExNoteContainer
*  Part of  : AknExNote
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <eikenv.h>
#include <eiklabel.h>
#include <e32math.h>
#include <eikclb.h>
#include <eiktxlbm.h>
#include <eikclbd.h>
#include <avkon.hrh>
#include <aknprogressdialog.h>
#include <aknstaticnotedialog.h>
#include <aknglobalnote.h>
#include <aknwaitdialog.h>
#include <aknexnote.rsg>
#include <apgtask.h>
#include <eikdll.h>
#include <aknnotewrappers.h>
#include <coemain.h>
#include <eikprogi.h>
#include <aknnotecontrol.h>

#include "AknExNoteContainer.h"
#include "AknExNoteView.h"
#include "AknExNote.hrh"
#include "AknExNoteBaseListEventHandler.h"
#include "AknExNoteGeneralListEventHandler.h"
#include "AknExNoteToneListEventHandler.h"
#include "AknExNoteAnimationListEventHandler.h"
#include "AknExNoteGlobalNoteListEventHandler.h"
#include "AknExNotePriorityNoteListEventHandler.h"
/**
* In Avkon R33, cannot define the own layout note.
*
#include "AknExNoteOwnLayoutListEventHandler.h"
**/
#include "AknExNoteTwoLabelsListEventHandler.h"


// CONSTANTS
#define KAknExNoteGray TRgb(0xaaaaaa)

#define AKNEXNOTE_LIST_BOX_RECT TRect( TPoint( 15, 15 ), TSize( 140, 120 ) )
const TInt KAknExNoteComponentCount = 1;
const TInt KAknExNoteMessageBufLength = 256;
const TInt KAknExNoteRandomNumberRange = 20;
const TInt KAknExNoteProgressbarFinalValue = 200;
const TInt KAknExNoteProgressbarIncrement = 5;
const TInt KAknExNoteProgressbarInterval = 20;
const TInt KAknExNoteNameColumnIndex = 0;
const TInt KAknExNoteNameGapColumnIndex = 1;
const TInt KAknExNoteInitializeTime = 0;
const TInt KAknExNoteInitializeResourceId = 0;
const TInt KAknExNoteTextBufLength = 256;

// Define show time of wait note and permanent note.
// Unit is microsecond. 
const TInt KMaxPermanentNoteShowTime(6 * 1000000); 
const TInt KMaxWaitNoteShowTime(6 * 1000000); 
const TInt KTimeForCancelNoteAfterOpen(1 * 1000000); 

const TInt KPermNoteCallBackPriority(CActive::EPriorityStandard);
const TInt KWaitNoteCallBackPriority(CActive::EPriorityStandard);


// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExNoteContainer::CAknExNoteContainer( CAknExNoteView* )
// Overload Constructor.
// ----------------------------------------------------------------------------
//
CAknExNoteContainer::CAknExNoteContainer( CAknExNoteView* aView )
:   iLabel( NULL ),
    iView( aView ),
    iListBox( NULL ),
    iHandler( NULL ),
    iTimer( NULL )
    {
    }

// ----------------------------------------------------------------------------
// void CAknExNoteContainer::ConstructL( const TRect& )
// EPOC constructor
// ----------------------------------------------------------------------------
//
void CAknExNoteContainer::ConstructL( const TRect& aRect )
    {
    // Creates window.
    CreateWindowL();

    // Creates label object.
    CreateLabelL();

    SetRect( aRect ); // Sets rectangle of frame.
    ActivateL(); // Activates the window. (Ready to draw)

    iPermanentTimer = CPeriodic::NewL(KPermNoteCallBackPriority);
    iWaitNoteTimer = CPeriodic::NewL(KWaitNoteCallBackPriority);
    }

// ----------------------------------------------------------------------------
// CAknExNoteContainer::~CAknExNoteContainer()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExNoteContainer::~CAknExNoteContainer()
    {
    delete iLabel;
    delete iListBox;
    delete iHandler;
    delete iTimer;
    delete iIdle;
    delete iPermanentTimer;
    delete iWaitNoteTimer;
    }

// ----------------------------------------------------------------------------
// void CAknExNoteContainer::SetTextToLabelL( TInt )
//
// ----------------------------------------------------------------------------
//
void CAknExNoteContainer::SetTextToLabelL( TInt aResourceId )
    {
    TBuf<KAknExNoteMessageBufLength> messageString( NULL );
    iCoeEnv->ReadResource( messageString, aResourceId );
    iLabel->SetTextL( messageString );
    }

// ----------------------------------------------------------------------------
// void CAknExNoteContainer::ShowGeneralNoteL(
//  TInt aResourceId,
//  const CAknNoteDialog::TTimeout,
//  const CAknNoteDialog::TTone )
// ----------------------------------------------------------------------------
//
void CAknExNoteContainer::ShowGeneralNoteL(
    TInt aResourceId,
    const CAknNoteDialog::TTimeout aTimeout,
    const CAknNoteDialog::TTone aTone )
    {
    CAknNoteDialog* dlg = new( ELeave ) CAknNoteDialog( aTone, aTimeout );
    dlg->ExecuteLD( aResourceId );
    }

// ----------------------------------------------------------------------------
// void CAknExNoteContainer::ShowGeneralNoteL(
//  TInt aResourceId,
//  TInt aControlId,
//  const CAknNoteDialog::TTimeout,
//  const CAknNoteDialog::TTone
//  TBool aPlural )
// ----------------------------------------------------------------------------
//
void CAknExNoteContainer::ShowGeneralNoteL(
    TInt aResourceId,
    TInt /* aControlId */,
    const CAknNoteDialog::TTimeout aTimeout,
    const CAknNoteDialog::TTone aTone,
    TBool aPlural )
    {
    CAknNoteDialog* dlg =
        new (ELeave) CAknNoteDialog( aTone, aTimeout );
    dlg->PrepareLC( aResourceId );
    dlg->SetTextPluralityL( aPlural );
    dlg->RunLD();
    }

// ----------------------------------------------------------------------------
// void CAknExNoteContainer::ShowDynamicNumberNoteL()
//
// ----------------------------------------------------------------------------
//
void CAknExNoteContainer::ShowDynamicNumberNoteL()
    {
    CAknNoteDialog* dlg = new ( ELeave ) CAknNoteDialog(
        CAknNoteDialog::EConfirmationTone, CAknNoteDialog::ELongTimeout );
    dlg->PrepareLC( R_AKNEXNOTE_DYNAMIC_TEXT );
    TTime theTime( KAknExNoteInitializeTime );
    theTime.UniversalTime();
    TInt64 randSeed( theTime.Int64() );
    TInt number( Math::Rand( randSeed ) % KAknExNoteRandomNumberRange );
    dlg->SetTextPluralityL( EFalse );
    dlg->SetTextNumberL( number );
    dlg->RunLD();
    }

// ----------------------------------------------------------------------------
// void CAknExNoteContainer::ShowProgressNoteL(
//  TInt aResourceId,
//  TInt aControlId )
//
// ----------------------------------------------------------------------------
//
void CAknExNoteContainer::ShowProgressNoteL(
    TInt aResourceId,
    TInt /* aControlId */)
    {
    CAknProgressDialog* dlg = new( ELeave ) CAknProgressDialog(
        KAknExNoteProgressbarFinalValue, KAknExNoteProgressbarIncrement,
        KAknExNoteProgressbarInterval, NULL);
    dlg->ExecuteLD(aResourceId);
    }

// ----------------------------------------------------------------------------
// void CAknExNoteContainer::ShowWaitNoteL
// Indicates wait note.
// ----------------------------------------------------------------------------
//
void CAknExNoteContainer::ShowWaitNoteL(
            TInt aResourceId,
            TInt /* aControlId */)
    {
    if (iWaitNoteTimer->IsActive())
        {
        iWaitNoteTimer->Cancel();
        }
    
    // Timer for deleting note is set if user cannot delete the note
    if (aResourceId == R_AKNEXNOTE_WAIT_NOTE_SOFTKEY_EMPTY)
        {
        TCallBack callback(WaitNoteTimeoutL, this);
        iWaitNoteTimer->Start(
            (TTimeIntervalMicroSeconds32) KMaxWaitNoteShowTime,
            (TTimeIntervalMicroSeconds32) KMaxWaitNoteShowTime, 
            callback);
        }
    
    CAknWaitDialog* waitDialog = 
        new (ELeave) CAknWaitDialog(NULL, ETrue);
    waitDialog->ExecuteLD(aResourceId); 

    }



// ----------------------------------------------------------------------------
// void CAknExNoteContainer::ShowPermanentNoteL( TInt aResourceId )
//
// ----------------------------------------------------------------------------
//
void CAknExNoteContainer::ShowPermanentNoteL( TInt aResourceId )
    {
    TBuf<KAknExNoteTextBufLength> text(NULL);
    CEikonEnv::Static()->ReadResource(text, aResourceId);
    TPtrC noteText( text );
    ShowGlobalNoteL(EAknGlobalPermanentNote, noteText);
    }

// ----------------------------------------------------------------------------
// void CAknExNoteContainer::ShowGlobalNoteL(
//     TAknGlobalNoteType aType,
//     TPtrC aNoteText )
//
// ----------------------------------------------------------------------------
//
void CAknExNoteContainer::ShowGlobalNoteL(
    TAknGlobalNoteType aType,
    TPtrC aNoteText )
    {
    CAknGlobalNote* globalNote = CAknGlobalNote::NewL();
    CleanupStack::PushL(globalNote);
    iPermanentNoteId = globalNote->ShowNoteL( aType, aNoteText );

    if (aType == EAknGlobalPermanentNote)
        {
        TCallBack callback(PermanentNoteTimeoutL, this);
        iPermanentTimer->Start(
            (TTimeIntervalMicroSeconds32) KMaxPermanentNoteShowTime,
            (TTimeIntervalMicroSeconds32) KMaxPermanentNoteShowTime, 
            callback);
        }
    CleanupStack::PopAndDestroy(); // globalNote
    }

// ----------------------------------------------------------------------------
// void CAknExNoteContainer::PopoutListBoxL( TInt aCommand )
//
// ----------------------------------------------------------------------------
//
void CAknExNoteContainer::PopoutListBoxL( TInt aCommand )
    {
    if ( CreateListBoxL( aCommand ) )
        {
        iHandler->HandleListBoxEventL(
            iListBox, MEikListBoxObserver::EEventEnterKeyPressed );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExNoteContainer::DiscardListboxAndTimer( TInt aCommand )
//
// ----------------------------------------------------------------------------
//
void CAknExNoteContainer::DiscardListboxAndTimer()
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
    if ( iTimer )
        {
        delete iTimer;
        iTimer = NULL;
        }
    }

// ----------------------------------------------------------------------------
// TBool CAknExNoteContainer::CreateTimerL(
//     TCallBack aCallBack,
//     TInt aPriorityTimer,
//     TInt aDelayTime,
//     TInt aIntervalTime)
// Creates timer object.
// ----------------------------------------------------------------------------
//
void CAknExNoteContainer::CreateTimerL(
    const TCallBack& aCallBack,
    TInt aPriorityTimer,
    TInt aDelayTime,
    TInt aIntervalTime )
    {
    if (iTimer)
        {
        delete iTimer;
        iTimer = NULL;
        }
    // Create timer.
    iTimer = CPeriodic::NewL( aPriorityTimer );
    // Start timer.
    iTimer->Start( aDelayTime, aIntervalTime, aCallBack );
    }

// ----------------------------------------------------------------------------
// void CAknExNoteContainer::ForwardOtherApplicationL(
//     TApaAppFileName aApplicationName )
// The other application are made forward.
// ----------------------------------------------------------------------------
//
void CAknExNoteContainer::ForwardOtherApplicationL(
    TApaAppFileName& aApplicationName )
    {
    TApaTaskList taskList( iCoeEnv->WsSession() );
    TApaTask task( taskList.FindApp( aApplicationName ) );
    if ( !task.Exists() )
        {
        CApaCommandLine* commandLine = CApaCommandLine::NewLC();
        commandLine->SetLibraryNameL( aApplicationName );
        commandLine->SetCommandL( EApaCommandRun );
        EikDll::StartAppL( *commandLine );
        CleanupStack::PopAndDestroy(); // commandLine
        }
    else
        {
        task.BringToForeground();
        }
    }


// ----------------------------------------------------------------------------
// voidÅ@CAknExNoteContainer::ShowNoteWrappersConfirmationL()
// Indicates Note Warappers
// ----------------------------------------------------------------------------
//
void CAknExNoteContainer::ShowNoteWrappersConfirmationL()
	{
	CAknConfirmationNote* dialog = new(ELeave)CAknConfirmationNote();
	TBuf<64> aDes;
	iCoeEnv->ReadResource(aDes, R_AKNEXNOTE_CONFIRMATIONNOTE_TEXT);
			 
	dialog->ExecuteLD(aDes);
	}

// ----------------------------------------------------------------------------
// void CAknExNoteContainer::ShowNoteWrappersInformationL()
// Indicates Note Warappers
// ----------------------------------------------------------------------------
//
void CAknExNoteContainer::ShowNoteWrappersInformationL()
	{
	CAknInformationNote* dialog = new(ELeave)CAknInformationNote();
	TBuf<64> aDes;
	iCoeEnv->ReadResource(aDes, R_AKNEXNOTE_INFORMATIONNOTE_TEXT);
	dialog->ExecuteLD(aDes);
	}

// ----------------------------------------------------------------------------
// void CAknExNoteContainer::ShowNoteWrappersWarningL()
// Indicates Note Warappers
// ----------------------------------------------------------------------------
//
void CAknExNoteContainer::ShowNoteWrappersWarningL()
	{
	CAknWarningNote* dialog = new(ELeave)CAknWarningNote();
	TBuf<64> aDes;
	iCoeEnv->ReadResource(aDes, R_AKNEXNOTE_WARNINGNOTE_TEXT);
	dialog->ExecuteLD(aDes);
	}

// ----------------------------------------------------------------------------
// void CAknExNoteContainer::ShowNoteWrappersErrorL()
// Indicates Note Warappers
// ----------------------------------------------------------------------------
//
void CAknExNoteContainer::ShowNoteWrappersErrorL()
	{
	CAknErrorNote* dialog = new(ELeave)CAknErrorNote();
	TBuf<64> aDes;
	iCoeEnv->ReadResource(aDes, R_AKNEXNOTE_ERRORNOTE_TEXT);
	dialog->ExecuteLD(aDes);
	}

// ----------------------------------------------------------------------------
// void CAknExNoteContainer::ShowProgressNoteUnderSingleProcessL(
//  TInt aResourceId,
//  TInt aControlId )
//
// ----------------------------------------------------------------------------
//
void CAknExNoteContainer::ShowProgressNoteUnderSingleProcessL(
    TInt aResourceId, TInt /* aControlId */)
    { 
    delete iProgressDialog;
    iProgressDialog = new (ELeave) CAknProgressDialog( 
                REINTERPRET_CAST(CEikDialog**, &iProgressDialog));

    iProgressDialog->SetCallback(this);
    iProgressDialog->PrepareLC(aResourceId);
    
    iProgressInfo = iProgressDialog->GetProgressInfoL();
    iProgressInfo->SetFinalValue( KAknExNoteProgressbarFinalValue );
    iProgressDialog->RunLD();

    delete iIdle;
    iIdle = CIdle::NewL(CActive::EPriorityStandard);
    TCallBack callback(CallbackIncrementProgressNoteL, this);
    iIdle->Start(callback);
    }

void CAknExNoteContainer::ShowSetNewImageL(
     const TDesC& aFileName, TInt aBitmapId, TInt aMaskId)
    {
    CAknNoteDialog* dlg = new (ELeave) CAknNoteDialog( 
        CAknNoteDialog::EConfirmationTone, CAknNoteDialog::EShortTimeout );
    dlg->PrepareLC( R_AKNEXNOTE_IMAGE_NOTE );
    CEikImage* image = NULL;
    if (aBitmapId > 0)
        {
        image = new (ELeave) CEikImage;
        CleanupStack::PushL(image);   
        CFbsBitmap* bitmap = iEikonEnv->CreateBitmapL(aFileName, aBitmapId);
        CleanupStack::PushL(bitmap);
        CFbsBitmap* bitmapM = NULL;
        
        if (aMaskId > 0)
            {
            bitmapM = iEikonEnv->CreateBitmapL(
                                  aFileName, aMaskId);
            }

        image->SetPicture(bitmap, bitmapM);
        CleanupStack::Pop(); // bitmap
        }
    if (image)
        {
        // SetNewImageL() is replaced to SetImageL() on Sw 2.10.
        dlg->SetImageL(image);
        CleanupStack::Pop(); // image
        }
    dlg->SetTextPluralityL( ETrue );
    dlg->RunLD();
    }

void CAknExNoteContainer::ShowSetNewIconL(
     const TDesC& aFileName, TInt aBitmapId, TInt aMaskId)
    {
    CAknNoteDialog* dlg = new (ELeave) CAknNoteDialog(
         CAknNoteDialog::EConfirmationTone, CAknNoteDialog::EShortTimeout);
    dlg->PrepareLC( R_AKNEXNOTE_IMAGE_NOTE );
    CEikImage* icon = NULL;
    if (aBitmapId > 0)
        {
        icon = new (ELeave) CEikImage;
        CleanupStack::PushL(icon);   
        CFbsBitmap* bitmap = iEikonEnv->CreateBitmapL(aFileName, aBitmapId);
        CleanupStack::PushL(bitmap);
        CFbsBitmap* bitmapM = NULL;
        
        if (aMaskId > 0)
            {
            bitmapM = iEikonEnv->CreateBitmapL(
                                  aFileName, aMaskId);
            }

        icon->SetPicture(bitmap, bitmapM);
        CleanupStack::Pop(); // bitmap
        }

    dlg->SetTextPluralityL( EFalse );
    if (icon)
        {
        // SetNewIconL() is replaced to SetIconL() on Sw2.10.
        dlg->SetIconL(icon);
        CleanupStack::Pop(); // icon
        }
    dlg->RunLD();
    }

void CAknExNoteContainer::ShowSetDynamicNumberL(TInt aNumber, TBool aFlag)
    {
    CAknNoteDialog* dlg = new ( ELeave ) CAknNoteDialog(
         CAknNoteDialog::EConfirmationTone, CAknNoteDialog::ELongTimeout);
    dlg->PrepareLC( R_AKNEXNOTE_DYNAMIC_TEXT );
    if (aFlag)
        {
        // SetDynamicNumberL() is replaced to SetTextNumberL() on Sw2.10.
        dlg->SetTextNumberL( aNumber );
        }
    // SetPluralL is replaced to SetTextPluralityL on Sw2.10.
    dlg->SetTextPluralityL( EFalse );
    if (!aFlag)
        {
        dlg->SetTextNumberL( aNumber );
        }
    dlg->RunLD();
    }

void CAknExNoteContainer::ShowSetCurrentLabelL(TInt aResourceId)
    {
    CAknNoteDialog* dlg = new( ELeave ) CAknNoteDialog( 
        CAknNoteDialog::EConfirmationTone, CAknNoteDialog::ELongTimeout);
    dlg->PrepareLC( R_AKNEXNOTE_NO_ICON );
    TBuf<KAknExNoteMessageBufLength> label(NULL);
    iEikonEnv->ReadResource(label, aResourceId);
    dlg->SetTextPluralityL( EFalse );
    dlg->SetTextL( label );
    dlg->RunLD();
    }

void CAknExNoteContainer::ShowLayoutAndDraw()
    {
    CAknNoteDialog* dlg = new( ELeave ) CAknNoteDialog( 
        CAknNoteDialog::EConfirmationTone, CAknNoteDialog::ELongTimeout );
    dlg->PrepareLC( R_AKNEXNOTE_NO_ICON );

    CAknNoteControl* note = STATIC_CAST(CAknNoteControl*,dlg->Control(EAknExNoteCtrlIdNoImageNote));
    note->SetTextPluralityL(EFalse);
    dlg->LayoutAndDraw();

    dlg->RunLD();
    }

void CAknExNoteContainer::ShowShowNoteL(TAknGlobalNoteType aType, TInt aResourceId, TBool aFlag)
    {
    TBuf<KAknExNoteTextBufLength> text(NULL);
    CEikonEnv::Static()->ReadResource(text, aResourceId);
    TPtrC noteText( text );
    CAknGlobalNote* globalNote = CAknGlobalNote::NewL();
    CleanupStack::PushL(globalNote);

    if (aFlag)
        {
        iPermanentNoteId = globalNote->ShowNoteL( iStatus, aType, noteText );
        if(aType != EAknCancelGlobalNote)
            User::WaitForRequest(iStatus);
        }
    else
        iPermanentNoteId = globalNote->ShowNoteL( aType, noteText );

    if (aType == EAknGlobalPermanentNote)
        {
        TCallBack callback(PermanentNoteTimeoutL, this);
        iPermanentTimer->Start(
            (TTimeIntervalMicroSeconds32) KMaxPermanentNoteShowTime,
            (TTimeIntervalMicroSeconds32) KMaxPermanentNoteShowTime, 
            callback);
        }

    CleanupStack::PopAndDestroy(); // globalNote
    }

void CAknExNoteContainer::ShowCancelNoteL(TBool aFlag)
    {
    TBuf<KAknExNoteTextBufLength> text(NULL);
    CEikonEnv::Static()->ReadResource(text, R_AKNEXNOTE_CANCELNOTEL_TEXT);
    TPtrC noteText( text );
    CAknGlobalNote* globalNote = CAknGlobalNote::NewL();
    CleanupStack::PushL(globalNote);
    iPermanentNoteId = globalNote->ShowNoteL( EAknGlobalInformationNote, noteText );
    if (!aFlag)
        {   
        iPermanentNoteId = -1;
        }

    TCallBack callback(PermanentNoteTimeoutL, this);
    iPermanentTimer->Start(
        (TTimeIntervalMicroSeconds32) KTimeForCancelNoteAfterOpen,
        (TTimeIntervalMicroSeconds32) KTimeForCancelNoteAfterOpen, 
        callback);

    CleanupStack::PopAndDestroy(); // globalNote
    }

void CAknExNoteContainer::ShowSetPriority(TBool aFlag)
    {
    TBuf<KAknExNoteTextBufLength> text(NULL);
    CEikonEnv::Static()->ReadResource(text, R_AKNEXNOTE_SETPRIORITY_LABEL);
    CAknGlobalNote* globalNote = CAknGlobalNote::NewL();
    CleanupStack::PushL(globalNote);
    TPtrC noteText( text );
    if (aFlag)
        {
        globalNote->SetPriority(0);
        }
    else
        {
        globalNote->SetPriority(999);
        }
    globalNote->SetSoftkeys(R_AVKON_SOFTKEYS_OK_CANCEL);
    iPermanentNoteId = globalNote->ShowNoteL( EAknGlobalWaitNote, noteText );

    CleanupStack::PopAndDestroy(); // globalNote
    }

void CAknExNoteContainer::ShowSetSoftkeys(TInt aId)
    {
    TBuf<KAknExNoteTextBufLength> text(NULL);
    CEikonEnv::Static()->ReadResource(text, R_AKNEXNOTE_SETSOFTKEY_LABEL);
    TPtrC noteText( text );
    CAknGlobalNote* globalNote = CAknGlobalNote::NewL();
    CleanupStack::PushL(globalNote);
    globalNote->SetSoftkeys(aId);
    // Global permanent note cannot be closed by any keypresses.
    // Therefore, permanent note cannot have softkey. 
    // Because of it, note type is changed from permanent note.
    iPermanentNoteId = globalNote->ShowNoteL( 
        EAknGlobalConfirmationNote, noteText );

    CleanupStack::PopAndDestroy(); // globalNote
    }

void CAknExNoteContainer::ShowSetGraphic(TInt aBitmapId, TInt aMaskId)
    {
    TBuf<KAknExNoteTextBufLength> text(NULL);
    CEikonEnv::Static()->ReadResource(text, R_AKNEXNOTE_SETGRAPHIC_LABEL);
    TPtrC noteText( text );
    CAknGlobalNote* globalNote = CAknGlobalNote::NewL();
    CleanupStack::PushL(globalNote);
    globalNote->SetGraphic(aBitmapId, aMaskId);
    globalNote->SetSoftkeys(R_AVKON_SOFTKEYS_OK_CANCEL);
    iPermanentNoteId = globalNote->ShowNoteL( EAknGlobalWaitNote, noteText );
    CleanupStack::PopAndDestroy(); //globalNote
    }

void CAknExNoteContainer::ShowSetAnimation(TInt aResourceId)
    {
    TBuf<KAknExNoteTextBufLength> text(NULL);
    CEikonEnv::Static()->ReadResource(text, R_AKNEXNOTE_SETANIMATION_LABEL);
    TPtrC noteText( text );
    CAknGlobalNote* globalNote = CAknGlobalNote::NewL();
    CleanupStack::PushL(globalNote);
    globalNote->SetAnimation(aResourceId);
    iPermanentNoteId = globalNote->ShowNoteL( EAknGlobalInformationNote, noteText );

    CleanupStack::PopAndDestroy(); // globalNote
    }

void CAknExNoteContainer::ShowProgressSetCurrentLabelL(
     TInt /* aId */, TInt aResourceId)
    {
    delete iProgressDialog;
    iProgressDialog = NULL;
    iProgressDialog = new( ELeave ) CAknProgressDialog(
        (REINTERPRET_CAST(CEikDialog**, &iProgressDialog)));
    iProgressDialog->PrepareLC(R_AKNEXNOTE_PROGRESS_NOTE);    

    TBuf<KAknExNoteTextBufLength> text(NULL);
    CEikonEnv::Static()->ReadResource(text, aResourceId);
    TPtrC label( text );
    iProgressDialog->SetTextL(/* aId, */label);

    iProgressDialog->RunLD();
    
    iProgressInfo = iProgressDialog->GetProgressInfoL();

    const TInt KFinalValue( 100 );
    iProgressInfo->SetFinalValue( KFinalValue );

    do
		{

		TTime intervalTime;
        intervalTime.HomeTime();
		intervalTime += TTimeIntervalMicroSeconds(20000);
		TTime currentLoopTime;

		do
			{
			currentLoopTime.HomeTime();
			}
		while ( currentLoopTime <= intervalTime );
		
	    iProgressInfo->IncrementAndDraw( 10 );
		}
	while ( iProgressInfo->CurrentValue() < KFinalValue );

//	iProgressDialog->ProcessFinishedL();
    }

// ----------------------------------------------------------------------------
// CAknExNoteContainer::ShowNoteByCAknWaitDialogL
// Show wait dialog by using CAknWaitDialog class.
// ----------------------------------------------------------------------------
//
void CAknExNoteContainer::ShowNoteByCAknWaitDialogL(
     TInt /* aNoteControlId */, TBool aVisibilityDelayOff, TInt aResourceId)
    {
    // 1st parameter is used by only ASSERT in Sw 4.0.16.
    // If NULL is passed as the perameter, crash does not occur.
    CAknWaitDialog* waitDialog = new (ELeave) CAknWaitDialog
            (NULL, aVisibilityDelayOff);
        
    waitDialog->ExecuteLD(aResourceId);
    }


// ----------------------------------------------------------------------------
// TInt CAknExNoteContainer::CallbackIncrementProgressNoteL( TAny* aThis )
// Just call UpdateProgressNote() function.
// If return 1(ETrue), CIdle calls this again.
// If retrun 0(EFalse), CIdle does not call this.
// ----------------------------------------------------------------------------
//
TInt CAknExNoteContainer::CallbackIncrementProgressNoteL( TAny* aThis )
    {
    return STATIC_CAST(CAknExNoteContainer*, aThis)->UpdateProgressNote();
    }

// ----------------------------------------------------------------------------
// TInt CAknExNoteContainer::UpdateProgressNote()
// ----------------------------------------------------------------------------
//
TInt CAknExNoteContainer::UpdateProgressNote()
    {
    // Do one step of work, This program just kills time.
    TTime intervalTime;
    intervalTime.HomeTime();
    intervalTime += TTimeIntervalMicroSeconds(50000);
    TTime currentTime;
    currentTime.HomeTime();
    while (intervalTime > currentTime)
        {
        currentTime.HomeTime();
        }


    iProgressInfo->IncrementAndDraw(1);
    if ( KAknExNoteProgressbarFinalValue <= iProgressInfo->CurrentValue() )
        {
        iProgressDialog->ProcessFinishedL();
        delete iProgressDialog;
        iProgressDialog = NULL;
        return 0;
        }
    return 1;
    }

// ----------------------------------------------------------------------------
// TInt CAknExNoteContainer::CallbackShowGlobalGeneralNoteL( TAny* aThis )
// Callback function for displaying the global general note.
// ----------------------------------------------------------------------------
//
TInt CAknExNoteContainer::CallbackShowGlobalGeneralNoteL( TAny* aThis )
    {
    CAknExNoteContainer* self = STATIC_CAST( CAknExNoteContainer*, aThis );
    if ( self->iTimer )
        {
        delete self->iTimer;
        self->iTimer = NULL;
        }
    TBuf<KAknExNoteTextBufLength> text( NULL );
    CEikonEnv::Static()->ReadResource(
        text, R_AKNEXNOTE_GLOBAL_GENERAL_NOTE_TEXT );
    TPtrC noteText( text );
    self->ShowGlobalNoteL(EAknGlobalInformationNote, noteText);
    return( ETrue );
    }

// ----------------------------------------------------------------------------
// TInt CAknExNoteContainer::CallbackShowGlobalWarningNoteL( TAny* aThis )
// Callback function for displaying the global warning note.
// ----------------------------------------------------------------------------
//
TInt CAknExNoteContainer::CallbackShowGlobalWarningNoteL( TAny* aThis )
    {
    CAknExNoteContainer* self = STATIC_CAST( CAknExNoteContainer*, aThis );
    if ( self->iTimer )
        {
        delete self->iTimer;
        self->iTimer = NULL;
        }
    TBuf<KAknExNoteTextBufLength> text( NULL );
    CEikonEnv::Static()->ReadResource(
        text, R_AKNEXNOTE_GLOBAL_WARNING_NOTE_TEXT );
    TPtrC noteText( text );
    self->ShowGlobalNoteL( EAknGlobalWarningNote, noteText );
    return( ETrue );
    }

// ----------------------------------------------------------------------------
// TInt CAknExNoteContainer::CallbackShowGlobalConfirmationNoteL( TAny* aThis )
// Callback function for displaying the global confirmation note.
// ----------------------------------------------------------------------------
//
TInt CAknExNoteContainer::CallbackShowGlobalConfirmationNoteL( TAny* aThis )
    {
    CAknExNoteContainer* self = STATIC_CAST( CAknExNoteContainer*, aThis );
    if ( self->iTimer )
        {
        delete self->iTimer;
        self->iTimer = NULL;
        }
    TBuf<KAknExNoteTextBufLength> text( NULL );
    CEikonEnv::Static()->ReadResource(
        text, R_AKNEXNOTE_GLOBAL_CONFIRMATION_NOTE_TEXT );
    TPtrC noteText( text );
    self->ShowGlobalNoteL( EAknGlobalConfirmationNote, noteText );
    return( ETrue );
    }

// ----------------------------------------------------------------------------
// TInt CAknExNoteContainer::CallbackShowGlobalErrorNoteL( TAny* aThis )
// Callback function for displaying the global error note.
// ----------------------------------------------------------------------------
//
TInt CAknExNoteContainer::CallbackShowGlobalErrorNoteL( TAny* aThis )
    {
    CAknExNoteContainer* self = STATIC_CAST( CAknExNoteContainer*, aThis );
    if ( self->iTimer )
        {
        delete self->iTimer;
        self->iTimer = NULL;
        }
    TBuf<KAknExNoteTextBufLength> text( NULL );
    CEikonEnv::Static()->ReadResource(
        text, R_AKNEXNOTE_GLOBAL_ERROR_NOTE_TEXT );
    TPtrC noteText( text );
    self->ShowGlobalNoteL( EAknGlobalErrorNote, noteText );
    return( ETrue );
    }

// ----------------------------------------------------------------------------
// TInt CAknExNoteContainer::CallbackShowGlobalChargingNoteL( TAny* aThis )
// Callback function for displaying the global charging note.
// ----------------------------------------------------------------------------
//
TInt CAknExNoteContainer::CallbackShowGlobalChargingNoteL( TAny* aThis )
    {
    CAknExNoteContainer* self = STATIC_CAST( CAknExNoteContainer*, aThis );
    if ( self->iTimer )
        {
        delete self->iTimer;
        self->iTimer = NULL;
        }
    TPtrC noteText;
    self->ShowGlobalNoteL( EAknGlobalChargingNote, noteText );
    return( ETrue );
    }

// ----------------------------------------------------------------------------
// TInt CAknExNoteContainer::CallbackShowGlobalNotChargingNoteL( TAny* aThis )
// Callback function for displaying the global not charging note.
// ----------------------------------------------------------------------------
//
TInt CAknExNoteContainer::CallbackShowGlobalNotChargingNoteL( TAny* aThis )
    {
    CAknExNoteContainer* self = STATIC_CAST( CAknExNoteContainer*, aThis );
    if ( self->iTimer )
        {
        delete self->iTimer;
        self->iTimer = NULL;
        }
    TPtrC noteText;
    self->ShowGlobalNoteL( EAknGlobalNotChargingNote, noteText );
    return( ETrue );
    }

// ----------------------------------------------------------------------------
// TInt CAknExNoteContainer::CallbackShowGlobalBatteryFullNoteL( TAny* aThis )
// Callback function for displaying the global battery full note.
// ----------------------------------------------------------------------------
//
TInt CAknExNoteContainer::CallbackShowGlobalBatteryFullNoteL( TAny* aThis )
    {
    CAknExNoteContainer* self = STATIC_CAST( CAknExNoteContainer*, aThis );
    if ( self->iTimer )
        {
        delete self->iTimer;
        self->iTimer = NULL;
        }
    TPtrC noteText;
    self->ShowGlobalNoteL( EAknGlobalBatteryFullNote, noteText );
    return( ETrue );
    }

// ----------------------------------------------------------------------------
// TInt CAknExNoteContainer::CallbackShowGlobalBatteryLowNoteL( TAny* aThis )
// Callback function for displaying the global battery low note.
// ----------------------------------------------------------------------------
//
TInt CAknExNoteContainer::CallbackShowGlobalBatteryLowNoteL( TAny* aThis )
    {
    CAknExNoteContainer* self = STATIC_CAST( CAknExNoteContainer*, aThis );
    if ( self->iTimer )
        {
        delete self->iTimer;
        self->iTimer = NULL;
        }
    TPtrC noteText;
    self->ShowGlobalNoteL( EAknGlobalBatteryLowNote, noteText );
    return( ETrue );
    }

// ----------------------------------------------------------------------------
// TInt CAknExNoteContainer::CallbackShowGlobalRechargeBatteryNoteL(
//     TAny* aThis )
// Callback function for displaying the global recharge battery low note.
// ----------------------------------------------------------------------------
//
TInt CAknExNoteContainer::CallbackShowGlobalRechargeBatteryNoteL( TAny* aThis )
    {
    CAknExNoteContainer* self = STATIC_CAST( CAknExNoteContainer*, aThis );
    if ( self->iTimer )
        {
        delete self->iTimer;
        self->iTimer = NULL;
        }
    TPtrC noteText;
    self->ShowGlobalNoteL( EAknGlobalRechargeBatteryNote, noteText );
    return( ETrue );
    }

// ----------------------------------------------------------------------------
// TInt CAknExNoteContainer::CallbackShowPriorityLocalNoteL( TAny* aThis )
// Callback function for creating local note for priority test.
// ----------------------------------------------------------------------------
//
TInt CAknExNoteContainer::CallbackShowPriorityLocalNoteL( TAny* aThis )
    {
    CAknExNoteContainer* self = STATIC_CAST( CAknExNoteContainer*, aThis );
    if ( self->iTimer )
        {
        delete self->iTimer;
        self->iTimer = NULL;
        }
    self->ShowGeneralNoteL( R_AKNEXNOTE_PRIORITY_LOCAL_WARNING_NOTE,
                            CAknNoteDialog::ELongTimeout,
                            CAknNoteDialog::EWarningTone );
    return( ETrue );
    }

// ----------------------------------------------------------------------------
// TInt CAknExNoteContainer::CallbackShowGlobalLocalNoteL( TAny* aThis )
// CallBack function.
// ----------------------------------------------------------------------------
//
TInt CAknExNoteContainer::CallbackShowPriorityGlobalNoteL( TAny* aThis )
    {
    CAknExNoteContainer* self = STATIC_CAST( CAknExNoteContainer*, aThis );
    if ( self->iTimer )
        {
        delete self->iTimer;
        self->iTimer = NULL;
        }
    TBuf<KAknExNoteTextBufLength> text( NULL );
    CEikonEnv::Static()->ReadResource(
        text, R_AKNEXNOTE_PRIORITY_GLOBAL_WARNING_TEXT );
    TPtrC noteText( text );
    self->ShowGlobalNoteL( EAknGlobalWarningNote, noteText );
    return( ETrue );
    }

// ----------------------------------------------------------------------------
// CAknExNoteContainer::PermanentNoteTimeoutL
// Callback function for deleting permanent note.
// ----------------------------------------------------------------------------
//
TInt CAknExNoteContainer::PermanentNoteTimeoutL( TAny* aThis )
    {
    CAknGlobalNote * note = CAknGlobalNote::NewL();
    CleanupStack::PushL(note);
    CAknExNoteContainer* container = 
        STATIC_CAST(CAknExNoteContainer*, aThis);
    note->CancelNoteL(container->iPermanentNoteId);
    CleanupStack::PopAndDestroy();  // note
    container->iPermanentTimer->Cancel();
                                    
    /*
    container->iGlobalNote->CancelNoteL(container->iGlobalNoteId);
    delete container->iGlobalNote;
    container->iGlobalNote = NULL;
    container->iPermanentTimer->Cancel();
    */
    return 0;
    }

// ----------------------------------------------------------------------------
// CAknExNoteContainer::WaitNoteTimeoutL
// Callback function for deleting wait note.
// ----------------------------------------------------------------------------
//
TInt CAknExNoteContainer::WaitNoteTimeoutL( TAny* aThis )
    {
    CAknExNoteContainer* container = 
        STATIC_CAST(CAknExNoteContainer*, aThis);
    
    container->iWaitNoteTimer->Cancel();
    CCoeAppUi* ui = STATIC_CAST(CCoeAppUi*, container->iCoeEnv->AppUi()); 
    
    if (ui->IsDisplayingMenuOrDialog()) // Check whether wait note is displayed.
        {
        TKeyEvent key;
        key.iCode = EKeyEscape;
        key.iModifiers = 0;
        container->iCoeEnv->SimulateKeyEventL(key, EEventKey);
        }

    return 0; 
    }

// ----------------------------------------------------------------------------
// void CAknExNoteContainer::DialogDismissedL(TInt aButtonId)
// Called when/if the dialog has been dismissed.
// iIdle must be canceled when cancel button is pressed.
// ----------------------------------------------------------------------------
//
void CAknExNoteContainer::DialogDismissedL(TInt aButtonId)
    {
    if (aButtonId == -1)
        { // when pressing cancel button.
        delete iIdle;
        iIdle = NULL;
        }
    }

// ----------------------------------------------------------------------------
// void CAknExNoteContainer::CreateLabelL()
// Creates label object.
// ----------------------------------------------------------------------------
//
void CAknExNoteContainer::CreateLabelL()
    {
    if ( iLabel )
        {
        delete iLabel;
        iLabel = NULL;
        }
    iLabel = new( ELeave ) CEikLabel;
    iLabel->SetContainerWindowL( *this );
    iLabel->SetAlignment( EHCenterVCenter );
    iLabel->SetFont( LatinBold19() );
    SetTextToLabelL( R_AKNEXNOTE_TEXT_LABEL_TITLE );
    }

// ----------------------------------------------------------------------------
// TBool CAknExNoteContainer::CreateListBoxL( TInt aCommand )
// Creates list object.
// ----------------------------------------------------------------------------
//
TBool CAknExNoteContainer::CreateListBoxL( TInt )
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
    TInt resourceId( KAknExNoteInitializeResourceId );
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
    TRect rect( AKNEXNOTE_LIST_BOX_RECT );
    CColumnListBoxData* columnData = iListBox->ItemDrawer()->ColumnData();
    columnData->SetColumnWidthPixelL( KAknExNoteNameColumnIndex,
                                      rect.Width() );
    columnData->SetColumnWidthPixelL( KAknExNoteNameGapColumnIndex,
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
// TKeyResponse CAknExNoteContainer::OfferKeyEventL( const TKeyEvent&,
//  TEventCode )
// Handles the key events.
// ----------------------------------------------------------------------------
//
TKeyResponse CAknExNoteContainer::OfferKeyEventL(
    const TKeyEvent& aKeyEvent,
    TEventCode aType )
    {
    if ( aType != EEventKey ) // Is not key event?
        {
        return EKeyWasNotConsumed;
        }

    switch ( aKeyEvent.iCode )
        {
        case EKeySpace: // Space key.
            // Requires to display next outline screen.
            iView->DisplayNextOutlineL();
            DrawNow();
            break;
        default:
            if ( iListBox ) // Is list box created?
                {
                // Offers the key event to list box.
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
// void CAknExNoteContainer::SizeChanged()
// Called by framework when the view size is changed.
// ----------------------------------------------------------------------------
//
void CAknExNoteContainer::SizeChanged()
    {
    iLabel->SetRect( Rect() );
    }

// ----------------------------------------------------------------------------
// TInt CAknExNoteContainer::CountComponentControls() const
// Returns number of component.
// ----------------------------------------------------------------------------
//
TInt CAknExNoteContainer::CountComponentControls() const
    {
    // return nbr of controls inside this container
    TInt count( KAknExNoteComponentCount );
    if ( iListBox )
        {
        count++;
        }
    return count;
    }

// ----------------------------------------------------------------------------
// CCoeControl* CAknExNoteContainer::ComponentControl( TInt ) const
// Returns pointer to particular component.
// ----------------------------------------------------------------------------
//
CCoeControl* CAknExNoteContainer::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex )
        {
        case EAknExNoteComponentLabel: // Label object.
            return iLabel;
        case EAknExNoteComponentListbox: // Listbox object.
            return iListBox;
        default: // Exception : returns NULL value.
            return NULL;
        }
    }

// ----------------------------------------------------------------------------
// void CAknExNoteContainer::Draw( const TRect& ) const
// Clears the window's rectangle.
// ----------------------------------------------------------------------------
//
void CAknExNoteContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAknExNoteGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// End of File