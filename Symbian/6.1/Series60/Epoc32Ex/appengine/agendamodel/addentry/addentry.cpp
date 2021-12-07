// AddEntry.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// This example program opens an Agenda document and
// adds an entry.


#include <apparc.h>
#include <txtrich.h>
#include <e32cons.h>

#include <agmmiter.h>
#include <agmcallb.h>

#include "literals.h"

LOCAL_D const TTimeIntervalMinutes KDefaultTimeForEvents(9 * 60); // 9.00 pm
LOCAL_D const TTimeIntervalMinutes KDefaultTimeForAnnivs(13 * 60); // 1.00 am
LOCAL_D const TTimeIntervalMinutes KDefaultTimeForDayNote(13 * 60); // 1.00 am

LOCAL_D TTime startDateTime(TDateTime(1997,ENovember,2,1,0,0,0));
LOCAL_D TTime endDateTime(TDateTime(1997,ENovember,2,2,15,0,0));

LOCAL_D CConsoleBase* console;

///////////////////////////////////////////////////////
//
// Class Definitions
//
///////////////////////////////////////////////////////

//-----------------------------------------------------
// CAgendaFileWriter
//
// The main class for the example. CAgendaFileWriter 
// contains all the functions for reading the Agenda document
//-----------------------------------------------------
class CAgendaFileWriter : public CBase
{
public:
	void ExecuteLD();
	void AddEntryL();
private:
	~CAgendaFileWriter();
private:
	RFs			iFs;
	CAgnModel*	iModel;	// Instance model
	RAgendaServ* iAgenServ;
	CAgnDayList<TAgnInstanceId>* iDayList;
	CParaFormatLayer* iParaFormatLayer;
	CCharFormatLayer* iCharFormatLayer;
};

//-----------------------------------------------------
// CMyScheduler
//
// We need an active scheduler so we can open the Agenda
// model asynchronously.
// We create a derived class so we can override 
// CActiveScheduler::Error().
//-----------------------------------------------------
class CMyScheduler : public  CActiveScheduler
	{
public:
	virtual void Error(TInt aError) const;
	};

//-----------------------------------------------------
// CView
//
// When the Agenda model is opened asynchronously we can 
// monitor its progress and state by deriving a class from 
// MAgnModelProgressCallBack and MAgnModelStateCallBack 
// respectively. In a real application this is typically 
// done by the view in the UI which can then given progress 
// information to the user. As this is a simplified example, 
// we create a dummy class to act as a view.
//-----------------------------------------------------
class CView: public CBase, public MAgnModelStateCallBack, public MAgnProgressCallBack
	{
public:
	static CView* NewL();
	virtual ~CView() {delete iModel;};
	virtual void StateCallBack(CAgnEntryModel::TState aState); // inherited from MAgnModelStateCallBack
	virtual void Progress(TInt aPercentageCompleted); // inherited from MAgnProgressCallBack
	virtual void Completed(TInt aError) ; // inherited from MAgnProgressCallBack
	inline CAgnModel* Model() const {return iModel;};
protected:
	CAgnModel* iModel;
private:
	//CConsoleBase* iLocalConsole;
	};

///////////////////////////////////////////////////////
//
// Function implementations
//
///////////////////////////////////////////////////////

//-----------------------------------------------------
// CAgendaFileWriter functions 
//-----------------------------------------------------


//	Destructor

CAgendaFileWriter::~CAgendaFileWriter()
	{
	delete iDayList;
	delete iParaFormatLayer;
	delete iCharFormatLayer;
	iFs.Close();
	iAgenServ->Close();
	delete iAgenServ;
	}


_LIT(KTxtApptWithAlarm,"An appt with an alarm");

void CAgendaFileWriter::AddEntryL()
	{
	iParaFormatLayer = CParaFormatLayer::NewL();
	iCharFormatLayer = CCharFormatLayer::NewL();

	CAgnAppt* appt=CAgnAppt::NewL(iParaFormatLayer,iCharFormatLayer);
	appt->RichTextL()->InsertL(0,KTxtApptWithAlarm);
	appt->SetStartAndEndDateTime(startDateTime,endDateTime);
	appt->SetAlarm(TTimeIntervalDays(2),TTimeIntervalMinutes(615));

//	iModel->SetState(CAgnEntryModel::ENoFile);

	iModel->AddEntryL(appt);
	delete appt;
	}



//	ExecuteLD()	Called by test harness.

void CAgendaFileWriter::ExecuteLD()
{
	CleanupStack::PushL(this);//this
	
	iAgenServ = RAgendaServ::NewL();
	iAgenServ->Connect();
	
	User::LeaveIfError(iFs.Connect());
	
//	Create a CAgnModel. A CAgnModel must have an associated user interface view, 
//	which is passed as an argument to CAgnModel::NewL() (see CView::NewL() below).
//	In this example, we use CView as a dummy class for the view.
	CView* view = CView::NewL();
	CleanupStack::PushL(view);

	iModel = view->Model();

	iModel->SetServer(iAgenServ);
	iModel->SetMode(CAgnEntryModel::EClient); 

//	Open the instance model asynchronously. It can also be opened synchronously 
//	by setting aOpenSynchronously to ETrue.
	TRAPD(error,(iModel->OpenL(_L("C:\\agendata3.dat"),KDefaultTimeForEvents,KDefaultTimeForAnnivs,KDefaultTimeForDayNote,view,EFalse)));
	
	iAgenServ->WaitUntilLoaded();

	CActiveScheduler::Start();

	AddEntryL();

    CleanupStack::PopAndDestroy();//view
	
	if(iAgenServ->FileLoaded())
	{
		iAgenServ->CloseAgenda();
	}

	CleanupStack::PopAndDestroy();//this
}


//-----------------------------------------------------
// CMyScheduler functions
//-----------------------------------------------------
/*
	Error()	Inherited from CActiveScheduler.
			Called if the active scheduler returns an error.
*/
void CMyScheduler::Error(TInt aError) const
	{
	console->Printf(KFormat4,aError);
	}

//-----------------------------------------------------
// CView functions
//-----------------------------------------------------
/*
	Completed()	Inherited from MAgnProgressCallBack.
				Called from CAgnFileActive::RunL() when the 
				activity has completed
*/
void CView::Completed(TInt aError) 
	{ 
	if (aError != KErrNone)
		console->Printf(KFormat2,aError);
	}; 

/*
	StateCallBack()	Inherited from MAgnProgressCallBack.
					This function is called whenever the state
					of the Agenda model changes into or out of
					a blocked state. This happens when some
					prolonged activity is about to start or has
					just finished - the purpose of the callback
					is to allow the application to inform users
					of this.
*/
void CView::StateCallBack(CAgnEntryModel::TState aState) 
	{
	
	switch (aState)
		{
	case CAgnModel::ENoFile: 
			{
			console->Printf(KTxtStateCallBackENoFile);
			CActiveScheduler::Stop();
			break;
			}
	case CAgnModel::EBlocked: 
			{
			console->Printf(KTxtStateCallBackEBlocked);
			break;
			}
	case CAgnModel::EOk: 
			{
			console->Printf(KTxtStateCallBackEOk);
			CActiveScheduler::Stop();
			break;
			}
	default: console->Printf(KTxtUnknownState);
		}
	
	}

/* 
   Progress()	Inherited from MAgnModelStateCallBack.
   This function is called at intervals while an activity on an 
   Agenda model (in this case OpenL()) is in progress. If the 
   activity completes quickly this function may not be called at all.
*/
void CView::Progress(TInt aPercentageCompleted)
	{
	console->Printf(KFormat3, aPercentageCompleted);
	}


//	NewL()	Create a new CView.

CView* CView::NewL()
	{
	CView* self = new(ELeave) CView;
	CleanupStack::PushL(self);
	self->iModel = CAgnModel::NewL(self);

	CleanupStack::Pop();
	return self;
	}


///////////////////////////////////////////////////////
//
//	Test harness
//
///////////////////////////////////////////////////////


LOCAL_C void executeReaderL()
	{
	console=Console::NewL(KTxtTitle,TSize(KConsFullScreen,KConsFullScreen));
	CleanupStack::PushL(console);
	CAgendaFileWriter* reader=new (ELeave) CAgendaFileWriter();
	reader->ExecuteLD();
	console->Printf(KTxtPressKey1);
	console->Getch();
	CleanupStack::PopAndDestroy(); // console
	}


GLDEF_C TInt E32Main() // main function called by E32
    {
	__UHEAP_MARK; // mark heap state
	CTrapCleanup* cleanup=CTrapCleanup::New(); // get clean-up stack
	CActiveScheduler* scheduler = new(ELeave)CMyScheduler;
	CActiveScheduler::Install(scheduler);
	TRAPD(r, for (TInt i=0; i<10; i++) CleanupStack::PushL((TAny*) 0); CleanupStack::Pop(10));
		// allocate some cleanup stack cells, which removes disturbance from nested mark/end pairs
	TRAPD(error,executeReaderL()); // do most stuff under cleanup stack
	delete scheduler;		
	__ASSERT_ALWAYS(!error,User::Panic(KtxtAgendaRdrPanic,error));
	delete cleanup; // destroy clean-up stack
	__UHEAP_MARKEND; // check no memory leak
	return 0; // and return
    }

