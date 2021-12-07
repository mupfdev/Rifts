// DBMS Interface to Databases - Basic Creation and Use
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.


// Example to demonstrate basic database creation and use


#include "CommonToDBMSEx.h"
	
				// Create a database and its structure
LOCAL_C void doMakeDatabaseL(const TDesC& aDatabaseFileName);

				// Add some records to the database
LOCAL_C void doAddDataL(const TDesC& aDatabaseFileName);

				// Display the rows
LOCAL_C void doShowL(const TDesC& aHeading,RDbRowSet& aSet);

				// Create the CDs table
LOCAL_C void doCreateTableL(RDbDatabase& aDatabase);

				// Create the CDs index
LOCAL_C void doCreateIndexL(RDbDatabase& aDatabase);


//  Do the example
LOCAL_C void doExampleL()
    {
	_LIT(KDbCreateDb,"dbcreate.db");
	_LIT(KCEpoc32exData,"C:\\epoc32ex\\data\\");

				// The database is contained in a permanent file store:
				// "C:\epoc32ex\data\dbcreate.db"
	TParse		name;
	fsSession.MkDirAll(KCEpoc32exData);
	fsSession.Parse(KDbCreateDb,KCEpoc32exData,name);
				// 
	doMakeDatabaseL(name.FullName());
				//
	doAddDataL(name.FullName());
	}


LOCAL_C void doMakeDatabaseL(const TDesC& aDatabaseFileName)
	{
				// construct a file store object - the file to contain the
				// database replaces any existing file of the same name.
	CFileStore* store = CPermanentFileStore::ReplaceLC(fsSession,aDatabaseFileName,EFileRead|EFileWrite);
				// Complete file store creation
	store->SetTypeL(store->Layout());

				// Create a database in the store
	RDbStoreDatabase database;
	TStreamId id=database.CreateL(store);
				// NB. The database won't be closed on failure
				//     Cleanup can be done; more usually database objects
				//     are not automatic variables.

				// Keep database id as root of store
	store->SetRootL(id);

				// Complete database creation by commiting the store
	store->CommitL();

				// create the CDs table
	doCreateTableL(database);

				// create an index
	doCreateIndexL(database);

				// close the database
	database.Close();

				// Do not commit store: database has taken control of commit
	CleanupStack::PopAndDestroy();
	}


LOCAL_C void doAddDataL(const TDesC& aDatabaseFileName)
	{
	_LIT(KSQLStatement,"select title,artist,price from CDs order by artist,title");
	_LIT(KComposition1, "Enigma Variations");
	_LIT(KComposer1, "Elgar");
	_LIT(KComposition2, "Symphony no. 5");
	_LIT(KComposer2, "Beethoven");

				// Open the file store
	CFileStore* store = CFileStore::OpenLC(fsSession,aDatabaseFileName,EFileRead|EFileWrite);

				// open the database from the root stream
	RDbStoreDatabase database;
	database.OpenL(store,store->Root());

				// create a view on the database
	RDbView view;
	User::LeaveIfError(view.Prepare(database,TDbQuery(KSQLStatement,EDbCompareNormal)));
	User::LeaveIfError(view.EvaluateAll());
				// NB. a similar caveat about cleanup applies as mentioned above

				// insert a row
	view.InsertL();
				// column numbers match the order specified in the select statement
				// data type must match almost exactly (a few exceptions)
	
	view.SetColL(1,KComposition1);
	view.SetColL(2,KComposer1);
	view.SetColL(3,1299);
				// complete the insertion
	view.PutL();

				// insert another row
	view.InsertL();


	view.SetColL(1,KComposition2);
	view.SetColL(2,KComposer2);
	view.SetColL(3,1499);
				// complete the insertion
	view.PutL();

				// show the records
	_LIT(KShowInfo, "Rowset contents...");
	doShowL(KShowInfo, view);

				// close the view
	view.Close();
				
				// close the database
	database.Close();

				// Do not commit store: database has taken control of commit
	CleanupStack::PopAndDestroy();
	}


LOCAL_C void doShowL(const TDesC& aHeading,RDbRowSet& aSet)
	{
	_LIT(KNewline, "\n") ;
	_LIT(KRowHeadingFormatter, "\n%d row(s):");
	_LIT(KRowFormatter, "\n  %S, %S:  %d.%02.2d");

	console->Printf(KNewline);
	console->Printf(aHeading);

	console->Printf(KRowHeadingFormatter,aSet.CountL());
				// iterate across the row set
	for (aSet.FirstL();aSet.AtRow();aSet.NextL())
		{
				// retrieve the row
		aSet.GetL();
				// while the rowset is on this row, can use a TPtrC to
				// refer to any text columns
		TPtrC title=aSet.ColDes(1);
		TPtrC artist=aSet.ColDes(2);

				// simple currency formatting; not locale-dependent
		TInt pricePounds=(aSet.ColInt(3)/100);
		TInt pricePence=(aSet.ColInt(3)-(pricePounds*100));
		console->Printf(KRowFormatter,&artist,&title,pricePounds,pricePence);
		}
	console->Printf(KNewline);
	}


LOCAL_C void doCreateTableL(RDbDatabase& aDatabase)
	{
	_LIT(KCol1, "Artist");
	_LIT(KCol2, "Title");
	_LIT(KCol3, "Price");
	_LIT(KTable, "CDs");

				// Create a table definition
	CDbColSet* columns=CDbColSet::NewLC();

				// add the columns
				// text columns default to 50 characters (variable length)
	columns->AddL(TDbCol(KCol1,EDbColText));

				// specify an alternative length
	TDbCol title(KCol2,EDbColText,60);
	title.iAttributes=TDbCol::ENotNull;
	columns->AddL(title);

	TDbCol price(KCol3,EDbColInt32);

				// columns are Nullable by default
	price.iAttributes=TDbCol::ENotNull;
	columns->AddL(price);

				// Create a table
	User::LeaveIfError(aDatabase.CreateTable(KTable,*columns));
				
		// cleanup the column set
	CleanupStack::PopAndDestroy();
	}


LOCAL_C void doCreateIndexL(RDbDatabase& aDatabase)
	{
	_LIT(KCol1, "Artist");
	_LIT(KCol2, "Title");
	_LIT(KTable, "CDs");

				// create the index key
	CDbKey* key=CDbKey::NewLC();

				// add the key columns
	TDbKeyCol artist(KCol1);
	key->AddL(artist);
	TDbKeyCol title(KCol2);
	key->AddL(title);

				// create the index
	User::LeaveIfError(aDatabase.CreateIndex(KTable,KTable,*key));

				// cleanup the key
	CleanupStack::PopAndDestroy();
	}
