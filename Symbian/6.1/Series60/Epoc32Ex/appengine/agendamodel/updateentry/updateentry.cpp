// UpdateEntry.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.


// This example program opens an Agenda document and
// updates (modifies) one of its entries, flipping 
// the entry's crossed-out status.
//
//		N.B. An instance is similar to an entry, except
//		that for repeating entries, an instance exists
//		for each day/time on which the entry occurs.
//		For non-repeating entries, a single instance
//		exists. User interfaces views always deal with
//		instances, not entries.


#include <apparc.h>
#include <txtrich.h>
#include <e32cons.h>

#include <agmmiter.h>
#include <agmcallb.h>

#include "literals.h"

LOCAL_D const TTimeIntervalMinutes KDefaultTimeForEvents(9 * 60); // 9.00 pm
LOCAL_D const TTimeIntervalMinutes KDefaultTimeForAnnivs(13 * 60); // 1.00 am
LOCAL_D const TTimeIntervalMinutes KDefaultTimeForDayNote(13 * 60); // 1.00 am
LOCAL_D CConsoleBase* console;

///////////////////////////////////////////////////////
//
// Class Definitions
//
///////////////////////////////////////////////////////

//-----------------------------------------------------
// CAgendaFileReader
//
// The main class for the example. CAgendaFileReader 
// contains all the functions for reading the Agenda document
//-----------------------------------------------------

class CAgendaFileReader : public CBase
{
public:
	CAgendaFileReader(const TDateTime& aDateTime);
	void ExecuteLD();
	void ReadDayListL();
	void UpdateEntryL();
private:
	~CAgendaFileReader();
private:
	RFs			iFs;
	CAgnModel*	iModel;
	RAgendaServ* iAgenServ;
	TTime		iDay;
	CAgnDayList<TAgnInstanceId>* iDayList;
	TInt		iCount;
	TBuf<256>	iText;
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
	};

///////////////////////////////////////////////////////
//
// Function implementations
//
///////////////////////////////////////////////////////

//-----------------------------------------------------
// CAgendaFileReader functions 
//-----------------------------------------------------


//	Constructor and destructor


CAgendaFileReader::CAgendaFileReader(const TDateTime& aDateTime) : iDay((TTime)aDateTime)
	{
	}


CAgendaFileReader::~CAgendaFileReader()
	{
	delete iDayList;
	iFs.Close();
	iAgenServ->Close();
	delete iAgenServ;
	}


//	ReadDayListL()	Read instances into a day instance list.


_LIT(KTxtNoEntriesOnDay,"There are no entries on the specified day\n");

void CAgendaFileReader::ReadDayListL()
	{
	
	// create a day list 
	iDayList=CAgnDayList<TAgnInstanceId>::NewL(iDay.DateTime()); 

	// fill the day list
	// filter allows particular types of instance to be excluded/included
	// Default is to include all types of entry.
	TAgnFilter filter;
	iModel->PopulateDayInstanceListL(iDayList,filter,iDay.DateTime());

	// Count() returns the number of instances in the list
	iCount=iDayList->Count();
	if (iCount > 0)
	{
		UpdateEntryL();
	}
	else // iCount<0
	{
		console->Printf(KTxtNoEntriesOnDay);
	}

	}


//	ReadEntriesL()	Performs steps 6, 7 and 8 - Get an instance, update it,
//									and update the instance in the model.

void CAgendaFileReader::UpdateEntryL()
	{
	// Get first entry in list
	// (Note that todo entries are ordered with the un-crossed out entries first.)
	CAgnEntry* entry=iModel->FetchInstanceL((*iDayList)[0]);
	CleanupStack::PushL(entry);

	if (entry->Type() == CAgnEntry::ETodo)
	{
		CAgnTodo* todo=entry->CastToTodo(); 
		
		if (todo->IsCrossedOut())
		{
			todo->UnCrossOut();
		}
		else
		{
			todo->CrossOut(iDay);
		}
	}
	else
	{
		entry->SetIsCrossedOut(!entry->IsCrossedOut());
	}

	_LIT(KTxtChangedCrossedOut,"Changed crossed-out status for the following entry:\n");
	_LIT(KTxtDfagnupdFormat1,"Status changed to: %S\n");
	_LIT(KtxtCrossedOut,"crossed out");
	_LIT(KtxtNotCrossedOut,"not crossed out");

	iModel->UpdateInstanceL(entry);
   	console->Printf(KTxtChangedCrossedOut);
	entry->RichTextL()->Extract(iText,0);
	console->Printf(KFormat1, &iText);
	console->Printf(KTxtDfagnupdFormat1, 
	entry->IsCrossedOut() ? &KtxtCrossedOut : &KtxtNotCrossedOut);
	
	CleanupStack::PopAndDestroy();
	}


//	ExecuteLD()	Called by test harness.

void CAgendaFileReader::ExecuteLD()
{
	CleanupStack::PushL(this);

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
	
	TRAPD(error,(iModel->OpenL(_L("C:\\agendata2.dat"),KDefaultTimeForEvents,
		            KDefaultTimeForAnnivs,KDefaultTimeForDayNote,view,EFalse)));

	iAgenServ->WaitUntilLoaded();//wait until the file is loaded

	CActiveScheduler::Start();

	ReadDayListL();

	CleanupStack::PopAndDestroy();//view
	
	if(iAgenServ->FileLoaded())//if the file is open close it
	{
		iAgenServ->CloseAgenda();
	}
	
	CleanupStack::PopAndDestroy();//this
}


//-----------------------------------------------------
// CMyScheduler functions
//-----------------------------------------------------

//	Error()	Inherited from CActiveScheduler.
//			Called if the active scheduler returns an error.

void CMyScheduler::Error(TInt aError) const
	{
	console->Printf(KFormat4,aError);
	}

//-----------------------------------------------------
// CView functions
//-----------------------------------------------------

//	Completed()	Inherited from MAgnProgressCallBack.
//				Called from CAgnFileActive::RunL() when the 
//				activity has completed

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
	CAgendaFileReader* reader=new (ELeave) CAgendaFileReader 
		                                   (TDateTime(2000,EMarch,14,0,0,0,0));
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
	TRAPD(error,executeReaderL()); // do most stuff under cleanup stack
	delete scheduler;		
	__ASSERT_ALWAYS(!error,User::Panic(KtxtAgendaRdrPanic,error));
	delete cleanup; // destroy clean-up stack
	__UHEAP_MARKEND; // check no memory leak
	return 0; // and return
    }

