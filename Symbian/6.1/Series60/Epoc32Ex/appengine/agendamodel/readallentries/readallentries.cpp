// ReadAllEntries.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// This example program opens an Agenda document and
// reads all the entries in the model.

#include <apparc.h>
#include <txtrich.h>
#include <e32cons.h>

#include <agmmiter.h>
#include <agmcallb.h>

#include "literals.h"


LOCAL_D const TTimeIntervalMinutes KDefaultTimeForEvents(9 * 60); // 9.00 pm
LOCAL_D const TTimeIntervalMinutes KDefaultTimeForAnnivs(13 * 60); // 1.00 am

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
	void ExecuteLD();
	void ReadEntryListL();
private:
	~CAgendaFileReader();
private:
	RFs			iFs;
	CAgnEntryModel*	iModel;
	RAgendaServ* iAgenServ;
	CAgnEntry* iEntry;
	TBuf<256>	iText;
};



///////////////////////////////////////////////////////
//
// Function implementations
//
///////////////////////////////////////////////////////



//-----------------------------------------------------
// CAgendaFileReader functions 
//-----------------------------------------------------


//	Destructor


CAgendaFileReader::~CAgendaFileReader()
	{
	iFs.Close();
	delete iModel;
	iAgenServ->Close();
	delete iAgenServ;
	}


//	ReadEntryListL()	- Read all entries and prints their text.



void CAgendaFileReader::ReadEntryListL()
	{
	
	TBool available = iAgenServ->CreateEntryIterator();
	
		while (available)
		{
			TAgnEntryId id = iAgenServ->EntryIteratorPosition();
			iEntry = iModel->FetchEntryL(id);
			
			iEntry->RichTextL()->Extract(iText,0,iEntry->RichTextL()->DocumentLength());
			console->Printf(KFormat1, &iText);
			
			available = iAgenServ->EntryIteratorNext();
			delete iEntry;
		}
	}


//	ExecuteLD()	Called by test harness.

void CAgendaFileReader::ExecuteLD()
{
	CleanupStack::PushL(this);
    
	iAgenServ = RAgendaServ::NewL();
	iAgenServ->Connect();

	User::LeaveIfError(iFs.Connect());
	
//	Create a CAgnEntryModel. This is en entry model and cannot be used with a user
//	interface. Unlike an instance model, it does not require a state callback.
	iModel = CAgnEntryModel::NewL();
	iModel->SetServer(iAgenServ);
	iModel->SetMode(CAgnEntryModel::EClient); 

	TRAPD(error,(iModel->OpenL(_L("C:\\agendata.dat"),
		KDefaultTimeForEvents,KDefaultTimeForAnnivs,1234)));

	iAgenServ->WaitUntilLoaded();

	ReadEntryListL();

	if(iAgenServ->FileLoaded())
	{
		iAgenServ->CloseAgenda();
	}

	CleanupStack::PopAndDestroy();
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
	CAgendaFileReader* reader=new (ELeave) CAgendaFileReader();
	reader->ExecuteLD();
	console->Printf(KTxtPressKey1);
	console->Getch();
	CleanupStack::PopAndDestroy(); // console
	}

GLDEF_C TInt E32Main() // main function called by E32
    {
	__UHEAP_MARK; // mark heap state
	CTrapCleanup* cleanup=CTrapCleanup::New(); // get clean-up stack
	TRAPD(error,executeReaderL()); // do most stuff under cleanup stack
	__ASSERT_ALWAYS(!error,User::Panic(KtxtAgendaRdrPanic,error));
	delete cleanup; // destroy clean-up stack
	__UHEAP_MARKEND; // check no memory leak
	return 0; // and return
    }

