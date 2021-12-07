/*
* ============================================================================
*  Name     : CAknExPbarContainer from CCoeControl
*  Part of  : AknExPbar
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include    <coemain.h>
#include    <barsread.h>
#include    <aknappui.h>
#include    <eikprogi.h>

#include    <AknExPbar.rsg>
#include    "AknExPbarContainer.h"

#include <avkon.hrh>
#include <akntitle.h>

// CONSTANTS
const TInt KProgressBarResetValue = 0;

//#define KAknExPbarBlack TRgb(0x000000)
#define KAknExPbarBlack TRgb(0xffffff)

#define PROGRESS_BAR_POSITION_0  TPoint( 4, 20 )
#define PROGRESS_BAR_POSITION_1  TPoint( 4, 40 )
#define PROGRESS_BAR_POSITION_2  TPoint( 4, 60 )
#define PROGRESS_BAR_POSITION_3  TPoint( 4, 80 )

const TInt KProgressBarHeight = 10;
const TInt KProgressBarSplitsInBlock = 0;

const TInt KProgressBar2Width = 120;
const TInt KProgressBar3Width = 114;
//const TInt KProgressBar3Width = 60;

const TInt KProgressBar0FinalValue = 15;
const TInt KProgressBar1FinalValue = 20;
const TInt KProgressBar2FinalValue = 30;
const TInt KProgressBar3FinalValue = 50;
//const TInt KProgressBar3FinalValue = 20;

const TInt KLengthOfTempString = 100;

const TInt KStepBackValue = ( -8 );
const TInt KJumpBackValue = ( -15 );

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor
CAknExPbarContainer::CAknExPbarContainer()
    {
    for ( TInt ii = 0; ii < KNumberOfBars; ii++ )
        {
        iPBar[ ii ] = NULL;
        }
    }

// EPOC default constructor can leave.
void CAknExPbarContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();

    iTestNumber=0;

    Window().SetShadowDisabled( EFalse );
    CreateProgressBarsL(EEikProgressTextNone);

    CEikStatusPane *sp = ((CAknAppUi*)iEikonEnv->EikAppUi())->StatusPane();
    iTitlePane = (CAknTitlePane *)sp->ControlL(TUid::Uid(EEikStatusPaneUidTitle));

    SetRect( aRect );
    ActivateL();
    }


// Destructor
CAknExPbarContainer::~CAknExPbarContainer()
    {
    for ( TInt ii = 0; ii < KNumberOfBars; ii++ )
        {
        delete( iPBar[ ii ] );
        iPBar[ ii ] = NULL;
        }
    }


// ---------------------------------------------------------
// CAknExPbarContainer::IncrementBarsAndDraw( TInt aIncrement )
// Increase progress bar length
// ---------------------------------------------------------
//
void CAknExPbarContainer::IncrementBarsAndDraw( TInt aIncrement )
    {
    switch(aIncrement)
        {
        case KStepBackValue:
            {
            TBuf<KLengthOfTempString> string;
            iEikonEnv->ReadResource(string, R_AKNEXPBAR_TITLE_STEPBACK);
            iTitlePane->SetTextL(string);
            }
            break;
        case KJumpBackValue:
            {
            TBuf<KLengthOfTempString> string;
            iEikonEnv->ReadResource(string, R_AKNEXPBAR_TITLE_JUMPBACK);
            iTitlePane->SetTextL(string);
            }
            break;
        default:
            break;
        }

    TInt index = 0;
    while ( index < KNumberOfBars )
        {
        iPBar[ index ]->IncrementAndDraw( aIncrement );
        index++;
        }
    }


// ---------------------------------------------------------
// CAknExPbarContainer::ResetAllValues()
// Reset progress bar length
// ---------------------------------------------------------
//
void CAknExPbarContainer::ResetAllValues()
    {
    TBuf<KLengthOfTempString> string;
    iEikonEnv->ReadResource(string, R_AKNEXPBAR_TITLE_RESETALLVALUES);
    iTitlePane->SetTextL(string);

    for ( TInt ii = 0; ii < KNumberOfBars; ii++ )
        iPBar[ ii ]->SetAndDraw( KProgressBarResetValue );
    }


// ---------------------------------------------------------
// CAknExPbarContainer::CountComponentControls() const
// amount of component controls
// ---------------------------------------------------------
//
TInt CAknExPbarContainer::CountComponentControls() const
    {
    return KNumberOfBars; // return nbr of controls inside this container
    }


// ---------------------------------------------------------
// CAknExPbarContainer::ComponentControl( TInt aIndex ) const
// Ptr to each component controls
// ---------------------------------------------------------
//
CCoeControl* CAknExPbarContainer::ComponentControl( TInt aIndex ) const
    {
    return ( iPBar[ aIndex ] );
    }


// ---------------------------------------------------------
// CAknExPbarContainer::Draw( const TRect& aRect ) const
// Draw function
// ---------------------------------------------------------
//
void CAknExPbarContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KAknExPbarBlack );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
    }

// ---------------------------------------------------------
// CAknExPopListContainer::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CAknExPbarContainer::HandleControlEventL(
    CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
    {
    }


// ---------------------------------------------------------
// CAknExPbarContainer::CreateProgressBarsL()
// Create progress bars
// ---------------------------------------------------------
//
void CAknExPbarContainer::CreateProgressBarsL(TEikProgressTextType aType)
    {
    TResourceReader reader;

    switch(aType)
        {
        case EEikProgressTextNone:
            {
            // Set Progress Bar property, using resource
            iCoeEnv->CreateResourceReaderLC( reader, R_AKNEXPBAR_PROGRESS_BAR_1 );
            iPBar[ 0 ] = new( ELeave ) CEikProgressInfo();
            iPBar[ 0 ]->ConstructFromResourceL( reader );
            CleanupStack::PopAndDestroy(); // reader
            iPBar[ 0 ]->SetPosition( PROGRESS_BAR_POSITION_0 );
            iPBar[ 0 ]->SetContainerWindowL( *this );

            iCoeEnv->CreateResourceReaderLC( reader, R_AKNEXPBAR_PROGRESS_BAR_2 );
            iPBar[ 1 ] = new(ELeave) CEikProgressInfo();
            iPBar[ 1 ]->ConstructFromResourceL( reader );
            CleanupStack::PopAndDestroy(); // reader
            iPBar[ 1 ]->SetPosition( PROGRESS_BAR_POSITION_1 );
            iPBar[ 1 ]->SetContainerWindowL( *this );
            break;
            }
        case EEikProgressTextPercentage:
            {
            // Set Progress Bar property, using resource
            iCoeEnv->CreateResourceReaderLC( reader, R_AKNEXPBAR_PROGRESS_BAR_1_TEXTPERCENTAGE );
            iPBar[ 0 ] = new( ELeave ) CEikProgressInfo();
            iPBar[ 0 ]->ConstructFromResourceL( reader );
            CleanupStack::PopAndDestroy(); // reader
            iPBar[ 0 ]->SetPosition( PROGRESS_BAR_POSITION_0 );
            iPBar[ 0 ]->SetContainerWindowL( *this );

            iCoeEnv->CreateResourceReaderLC( reader, R_AKNEXPBAR_PROGRESS_BAR_2_TEXTPERCENTAGE );
            iPBar[ 1 ] = new(ELeave) CEikProgressInfo();
            iPBar[ 1 ]->ConstructFromResourceL( reader );
            CleanupStack::PopAndDestroy(); // reader
            iPBar[ 1 ]->SetPosition( PROGRESS_BAR_POSITION_1 );
            iPBar[ 1 ]->SetContainerWindowL( *this );
            break;
            }
        case EEikProgressTextFraction:
            {
            // Set Progress Bar property, using resource
            iCoeEnv->CreateResourceReaderLC( reader, R_AKNEXPBAR_PROGRESS_BAR_1_TEXTFRACTION );
            iPBar[ 0 ] = new( ELeave ) CEikProgressInfo();
            iPBar[ 0 ]->ConstructFromResourceL( reader );
            CleanupStack::PopAndDestroy(); // reader
            iPBar[ 0 ]->SetPosition( PROGRESS_BAR_POSITION_0 );
            iPBar[ 0 ]->SetContainerWindowL( *this );

            iCoeEnv->CreateResourceReaderLC( reader, R_AKNEXPBAR_PROGRESS_BAR_2_TEXTFRACTION );
            iPBar[ 1 ] = new(ELeave) CEikProgressInfo();
            iPBar[ 1 ]->ConstructFromResourceL( reader );
            CleanupStack::PopAndDestroy(); // reader
            iPBar[ 1 ]->SetPosition( PROGRESS_BAR_POSITION_1 );
            iPBar[ 1 ]->SetContainerWindowL( *this );
            break;
            }
        }

    // Set Progress Bar property, coding directly
    CEikProgressInfo::SInfo info;
    info.iHeight = KProgressBarHeight;
    info.iSplitsInBlock = KProgressBarSplitsInBlock;
    info.iTextType = aType;

    info.iWidth = KProgressBar2Width;
    info.iFinalValue = KProgressBar2FinalValue;
    iPBar[ 2 ] = new( ELeave ) CEikProgressInfo( info );
    iPBar[ 2 ]->ConstructL();
    iPBar[ 2 ]->SetPosition( PROGRESS_BAR_POSITION_2 );
    iPBar[ 2 ]->SetContainerWindowL( *this );
    
    info.iWidth = KProgressBar3Width;
    info.iFinalValue = KProgressBar3FinalValue;
    iPBar[ 3 ] = new( ELeave ) CEikProgressInfo( info );
    iPBar[ 3 ]->ConstructL();
    iPBar[ 3 ]->SetPosition( PROGRESS_BAR_POSITION_3 );
    iPBar[ 3 ]->SetContainerWindowL( *this );
    }

// ---------------------------------------------------------
// CAknExPbarContainer::ChangeTextType(TEikProgressTextType aType)
// 
// ---------------------------------------------------------
//
void CAknExPbarContainer::ChangeTextType(TEikProgressTextType aType)
    {
    switch(aType)
        {
        case EEikProgressTextNone:
            {
            TBuf<KLengthOfTempString> string;
            iEikonEnv->ReadResource(string, R_AKNEXPBAR_TITLE_PROGRESSTEXTNONE);
            iTitlePane->SetTextL(string);
            }
            break;
        case EEikProgressTextPercentage:
            {
            TBuf<KLengthOfTempString> string;
            iEikonEnv->ReadResource(string, R_AKNEXPBAR_TITLE_PROGRESSTEXTPERCENTAGE);
            iTitlePane->SetTextL(string);
            }
            break;
        case EEikProgressTextFraction:
            {
            TBuf<KLengthOfTempString> string;
            iEikonEnv->ReadResource(string, R_AKNEXPBAR_TITLE_PROGRESSTEXTFRACTION);
            iTitlePane->SetTextL(string);
            }
            break;
        }

    for ( TInt ii = 0; ii < KNumberOfBars; ii++ )
        {
        delete( iPBar[ ii ] );
        iPBar[ ii ] = NULL;
        }
    CreateProgressBarsL(aType);
    ActivateL();
    }

// ---------------------------------------------------------
// CAknExPbarContainer::SetFinalValue(TBool aFlag)
// 
// ---------------------------------------------------------
//
void CAknExPbarContainer::SetFinalValue(TBool aFlag)
    {
    if(aFlag)
        {
        TBuf<KLengthOfTempString> string;
        iEikonEnv->ReadResource(string, R_AKNEXPBAR_TITLE_SETFINALVALUE2);
        iTitlePane->SetTextL(string);

        iPBar[0]->SetFinalValue(KProgressBar0FinalValue);
        iPBar[1]->SetFinalValue(KProgressBar1FinalValue);
        iPBar[2]->SetFinalValue(KProgressBar2FinalValue);
        iPBar[3]->SetFinalValue(KProgressBar3FinalValue);
        }
    else
        {
        TBuf<KLengthOfTempString> string;
        iEikonEnv->ReadResource(string, R_AKNEXPBAR_TITLE_SETFINALVALUE1);
        iTitlePane->SetTextL(string);

        iPBar[0]->SetFinalValue(KProgressBar3FinalValue);
        iPBar[1]->SetFinalValue(KProgressBar2FinalValue);
        iPBar[2]->SetFinalValue(KProgressBar1FinalValue);
        iPBar[3]->SetFinalValue(KProgressBar0FinalValue);
        }

    for ( TInt ii = 0; ii < KNumberOfBars; ii++ )
        iPBar[ ii ]->SetAndDraw( KProgressBarResetValue );
    }

// ---------------------------------------------------------
// CAknExPbarContainer::ShowInfo(TInt aBarNo)
// 
// ---------------------------------------------------------
//
void CAknExPbarContainer::ShowInfo(TInt aBarNo)
    {
    TBuf<KLengthOfTempString> string;
    TBuf<KLengthOfTempString> text;
    iEikonEnv->ReadResource(text, R_AKNEXPBAR_TITLE_SHOWINFO);
    string.Format(text, aBarNo+1);
    iTitlePane->SetTextL(string);

    TBuf<KLengthOfTempString> str;
    TBuf<KLengthOfTempString> format;
    iCoeEnv->ReadResource(format, R_AKNEXPBAR_FORMATSTRING_INFO);
    str.Format(format, iPBar[aBarNo]->Info().iTextType, iPBar[aBarNo]->Info().iSplitsInBlock,
        iPBar[aBarNo]->Info().iFinalValue, iPBar[aBarNo]->Info().iWidth, iPBar[aBarNo]->Info().iHeight,
        iPBar[aBarNo]->CurrentValue());
    iEikonEnv->AlertWin(str);
    }

// ---------------------------------------------------------
// CAknExPbarContainer::AutoTest()
// 
// ---------------------------------------------------------
//
void CAknExPbarContainer::AutoTest()
    {
    iTestNumber++;
    switch(iTestNumber)
        {
        case EProgCmdStepBackwards:
            IncrementBarsAndDraw(KStepBackValue);
            break;
        case EProgCmdReset:
            ResetAllValues();
            break;
        case EProgCmdChangeSetFinalValue1:
            SetFinalValue(EFalse);
            break;
        case EProgCmdChangeSetFinalValue2:
            SetFinalValue(ETrue);
            break;
        case EProgCmdChangeShowInfo1:
            ShowInfo(EAknExpBarBar1);
            break;
        case EProgCmdChangeShowInfo2:
            ShowInfo(EAknExpBarBar2);
            break;
        case EProgCmdChangeShowInfo3:
            ShowInfo(EAknExpBarBar3);
            break;
        case EProgCmdChangeShowInfo4:
        default:
            ShowInfo(EAknExpBarBar4);
            iTestNumber=0;
            break;
        }
    }

// ---------------------------------------------------------
// CAknExPbarContainer::SetTestNumber(TInt aTestNo)
// 
// ---------------------------------------------------------
//
void CAknExPbarContainer::SetTestNumber(TInt aTestNo)
    {
    iTestNumber = aTestNo;
    }

// End of File  
