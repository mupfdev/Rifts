// ReadAppt.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

/////////////////////////////////////////////////////
//
// This example program opens an Agenda document and
// reads the appointments for a specified day.
//
//
//		
//		Open the Agenda model
//		Read the insances for the given day into  a day instance list
//		Extract and print the text from the	instances
//
//		N.B. An instance is similar to an entry, except
//		that for repeating entries, an instance exists
//		for each day/time on which the entry occurs.
//		For non-repeating entries, a single instance
//		exists. User interfaces views always deal with
//		instances, not entries.
/////////////////////////////////////////////////////

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
	void ReadEntriesL();
	void FindNextEntryL();
private:
	~CAgendaFileReader();
private:
	RFs			iFs;
	CAgnModel*	iModel;
	RAgendaServ* iAgnServ;
	TTime		iDay;
	TTime		iDateWithEntries;
	CAgnDayList<TAgnInstanceId>* iDayList;
	TInt		iCount;
	TBuf<60>	iText;

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
	iFs.Close();
	delete iDayList;
	iAgnServ->Close();
	delete iAgnServ;
	}



//	ReadDayListL()	- Read instances into a day instance list.

void CAgendaFileReader::ReadDayListL()
	{
	// create a day list 
	iDayList=CAgnDayList<TAgnInstanceId>::NewL(iDay.DateTime()); 

	// fill the day list
	// filter allows particular types of instance to be excluded/included
	TAgnFilter filter;
	filter.SetIncludeEvents(EFalse);
	filter.SetIncludeTodos(EFalse);
	iModel->PopulateDayInstanceListL(iDayList,filter,iDay.DateTime());

	// Count() returns the number of instances in the list
	iCount=iDayList->Count();
	if (iCount > 0)
		{
    	ReadEntriesL();
		}
	else // iCount<0
		{
		FindNextEntryL();
		}
	}


//	ReadEntriesL()	- Read text from entries and print.


_LIT(KDfagndayFormat1,"%E%D%X%N%Y %1 %2 %3");
_LIT(KDfagndayFormat2,"Appointments for %S:\n");

void CAgendaFileReader::ReadEntriesL()
	{
	// Print the date of the entries.
	TBuf<30> dateString;
    iDay.FormatL(dateString,KDfagndayFormat1);
   	console->Printf(KDfagndayFormat2, &dateString);
	// get the entries off the list
	for (TInt ii=iCount; ii>0; --ii)
	{
		// Get each instance from the list, one at a time.
		CAgnEntry* entry=iModel->FetchInstanceL((*iDayList)[ii-1]);
		// Get the rich text into a descriptor so we can print it to the console.
		// Pass the length of the descriptor as the number of characters to extract,
		// as CEditableText::Extract() will cause a panic if the descriptor is 
		// too small. To find out the length of the rich text, use
		// entry->RichTextL()->DocumentLength();
		entry->RichTextL()->Extract(iText,0,entry->RichTextL()->DocumentLength());
		console->Printf(KFormat1, &iText);

		_LIT(KDfagndayFormat3,"%-B%:0%J%:1%T%+B");
		_LIT(KDfagndayFormat4,"Start time is %S\n");

		switch(entry->Type())
		{
			case CAgnEntry::EAppt:
				{
				// If the entry is an appointment, get the start time and print it
				CAgnAppt* appt= entry->CastToAppt(); // See also CastToAnniv(), etc.
				TTime startTime=appt->StartDateTime();
				TBuf<30> timeString;
				startTime.FormatL(timeString,KDfagndayFormat3);
				console->Printf(KDfagndayFormat4, &timeString);
				break;
				}

			case CAgnEntry::ETodo: case CAgnEntry::EEvent: case CAgnEntry::EAnniv:
				{
				break;
				}	
		}
		delete entry;					
	}

	}


//	FindNextEntryL()	If there are no entries on the day specified, finds the
//						next day that does contain entries.


_LIT(KDfagndayFormat5,"The next appointment or anniversary is on %S:\n");

void CAgendaFileReader::FindNextEntryL()
	{
	TAgnFilter filter;
	filter.SetIncludeEvents(EFalse);
	filter.SetIncludeTodos(EFalse);
	// Get the next date that has an entry (appointment or anniversary). To start 
	// the search at the beginning of the range for agenda entries, use 
	// AgnDateTime::MinDateAsTTime() in parameter three.
	iDateWithEntries=iModel->NextDayWithInstance(iDay,filter,iDay);
	TBuf<30> dateString;
	iDateWithEntries.FormatL(dateString,KDfagndayFormat1);
	console->Printf(KDfagndayFormat5, &dateString);
	}


//	ExecuteLD()	Called by test harness.

//Create, connect, and set the server


void CAgendaFileReader::ExecuteLD()
{
	
	CleanupStack::PushL(this);//this
	
	iAgnServ = RAgendaServ::NewL();
	iAgnServ->Connect();
	
	User::LeaveIfError(iFs.Connect());

    CView* view = CView::NewL();
	CleanupStack::PushL(view);//view
	
	iModel = view->Model();
    iModel->SetServer(iAgnServ);
	//The agenda model can operate either in client or normal mode. Here we use client mode
	iModel->SetMode(CAgnEntryModel::EClient); 
	TRAPD(error,(iModel->OpenL(_L("C:\\agendata.dat"),KDefaultTimeForEvents,KDefaultTimeForAnnivs,
												KDefaultTimeForDayNote,view,EFalse)));
	iAgnServ->WaitUntilLoaded();
	
	
	CActiveScheduler::Start();
	ReadDayListL();

	if(iAgnServ->FileLoaded())
	{
		iAgnServ->CloseAgenda();
	}

	CleanupStack::PopAndDestroy();//view
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
// This function is called at intervals while an activity on an 
// Agenda model (in this case OpenL()) is in progress. If the 
// activity completes quickly this function may not be called at all.
*/
void CView::Progress(TInt aPercentageCompleted)
	{
	console->Printf(KFormat3, aPercentageCompleted);
	}

/*
	NewL()	Create a new CView.
*/
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
		(TDateTime(2000,EMarch,1,0,0,0,0));
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

