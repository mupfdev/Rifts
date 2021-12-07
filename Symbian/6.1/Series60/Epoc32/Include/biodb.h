// BioDB.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

//
// BIO-message Database Reader and Writer Classes
// 
//
#ifndef BIODB_H_
#define BIODB_H_

#include <bif.h>				// the bif reader
#include <f32file.h>


// Constants
const TUid KUidBioDBDll ={0x10005542};	


//
// Data types
typedef TBuf<KMaxBioIdText> TBioMsgIdText;




//---------------------------------------------------------------------------
// class CBIODatabase
//---------------------------------------------------------------------------
class CBIODatabase : public CBase
{
public:
	// Data types
	enum TSearchList
		{
		EStart, ENext
		};
public:
	//--------------------------------------
	//     Construction & Destruction
	//--------------------------------------
	IMPORT_C static CBIODatabase* NewLC(RFs& afileSystem);
	IMPORT_C static CBIODatabase* NewL(RFs& afileSystem);
	IMPORT_C ~CBIODatabase();


public:
	//--------------------------------------
	//     Registration Methods
	//--------------------------------------

	// BIF files contain all the information that needs to be registered
	// for each BIO Message type

	// Completely refresh the database will all the BIF Files in the
	// default directory
	IMPORT_C void AddAllBifsL(RFs& afileSystem);

	// Add one bifFile using the file name, then using Neil's handy 
	// class to read it
	// This will add the Parser
	IMPORT_C void AddBifL(CBioInfoFileReader* bifReader);
	IMPORT_C void RemoveBifL(TUid BioID);
	IMPORT_C void RemoveBifL(TInt aIndex);

	//--------------------------------------
	//     Search Methods 
	//--------------------------------------
	// BIO Messages are determined to of a BIO type if we have the BIO
	// Parser identified by a WAP/NBS port, IANA MIME type or a Pattern
	IMPORT_C TInt BIOCount();



	// Get the BioEntry at this index
	// Return Index if found, NULL if not
	IMPORT_C const CArrayFix<TBioMsgId>* BIOEntryLC(TInt index);
	

	// Get the whole bif file class
	IMPORT_C const CBioInfoFileReader& BifReader(TInt aIndex) const;
     

	// Get the BIO Entry based on what type it is, pos indicates where to start looking 
	// after, and will get updated to current pos
	IMPORT_C const CArrayFix<TBioMsgId>* BioEntryByTypeLC(
								TSearchList aSearchType,
								TBioMsgIdType portType, 
								TInt& aIndex);

	



	////////////////////////////////////////////////////////////////////////////////////////////////////
	// Get the Index for the BioMessageID
	IMPORT_C void GetBioIndexWithMsgIDL(TUid aMsgID, TInt& rIndex);

	// Get the Index for the BioParserID
	IMPORT_C void GetBioIndexWithParserIDL(TUid aParserID, TInt& rIndex);

	// Get the BioMessageID for the Index
	IMPORT_C void GetBioMsgID(TInt aIndex, TUid& rMsgID);
	
	// Get the BioParserID for the Index
	IMPORT_C void GetBioParserID(TInt aIndex, TUid& rParserID);
	
	// Get the BioParserID for the BioMessageID
	IMPORT_C void GetBioParserIDL(TUid aMsgID, TUid& rParserID);

	// Get the ControlID for the Index
	IMPORT_C void GetBioControlID(TInt aIndex, TUid& rControlID);
	
	// Get the ControlID for the BioMessageID
	IMPORT_C void GetBioControlIDL(TUid aMsgID, TUid& rControlID);

	// Get the String Extension for the BioMessageID
	IMPORT_C const TPtrC GetFileExtL(TUid aMsgID);

	//--------------------------------------
	//     Search Methods for Sending
	//--------------------------------------
	IMPORT_C void GetDefaultSendBearerL(TUid aBioUID, TBioMsgId& rBioMsgIdentifier);
	IMPORT_C void GetDefaultSendBearerTypeL(TUid aBioUID, TBioMsgIdType& rPortType);
	IMPORT_C void GetDefaultSendBearerByTypeL(TUid aBioUID, TBioMsgIdType aPortType, TBioMsgId& rBioMsgIdentifier);



	//--------------------------------------
	//     Search Methods based on Ports Info
	//--------------------------------------
	// BIO Messages are determined to of a BIO type if we have the BIO
	// Parser identified by a WAP/NBS port, IANA MIME type or a Pattern
	// Return an Index

	// Get the Port# or Identifying string for sending
	IMPORT_C void GetPortNumberL(TUid aMsgID, TBioMsgIdType aPortType, TInt& aPortNumber);
	IMPORT_C void GetIdentifierTextL(TUid aMsgID, TBioMsgIdType aPortType, TBioMsgIdText& aText);

	//--------------------------------------
	//     Is A Bio Message?	
	//--------------------------------------
	// Test to see if this is a BioMessage
	// Pass in the type ... if its NBS or IANA pass in the string pattern
	//						if its WAP or SecureWap, pass in the port number
	// return kErrNone if success, kErrNotFound if it fails
	IMPORT_C TInt IsBioMessageL(TBioMsgIdType aPortType, const TDesC& aPattern, TUint16 aPort, TUid& rBioMsgUID);

	IMPORT_C TInt IsBioMessageL(TBioMsgId bioMessageData, TUid& rBioMsgUID);

protected:
	CBIODatabase();
	void ConstructL(RFs& afileSystem);

private:
	//Utilities
	const void GetTransportIDL(TInt aIndex, TBioMsgIdType aPortType, TBioMsgId& aBioMsgID);
	TBool IsMbmFileL(const TDesC& aFileName) const;

	// If Persistence is required...
	// void InternalizeL(RReadStream& aStream);		
	// void ExternalizeL(RWriteStream& aStream) const;	
	
private:

	CArrayPtrFlat<CBioInfoFileReader>* iBifReaders;

};

//---------------------------------------------------------------------------
// class MBifChangeObserver
//---------------------------------------------------------------------------

class MBifChangeObserver 
	{
public:
	enum TBifChangeEvent	{
							EBifChangeUnknown = 0,
							EBifAdded,
							EBifDeleted,
							EBifChanged
							};
public: 
	virtual void HandleBifChangeL(TBifChangeEvent aEvent, TUid aBioID)=0;
	};

//---------------------------------------------------------------------------
// class CBifChangeObserver
//---------------------------------------------------------------------------

class CBifChangeObserver : public CActive
	{
public: 
	IMPORT_C static CBifChangeObserver* NewL(MBifChangeObserver& aObserver, RFs& afileSystem);
	IMPORT_C void Start();
	~CBifChangeObserver();

protected:
	// from CActive
	void RunL();
	void DoCancel();

private:
	CBifChangeObserver(MBifChangeObserver& aObserver, RFs& afileSystem);
	void ConstructL();
	
	void NotifyObserverL();
	void WaitForFileNotification();
	void DoRunL();
	void CopyEntriesL(const CDir& aDir, CArrayFixFlat<TEntry>& aEntries);
	TBool CompareEntries(const TEntry& aEntry1, const TEntry& aEntry2) const;
	TBool CompareReaders(const CBioInfoFileReader& aReader1, const CBioInfoFileReader& aReader2) const;

	TInt FindEntry(const TEntry& aEntry, const CArrayFixFlat<TEntry>& aEntries, TInt& rIndex) const;
	
	// Data
	MBifChangeObserver&	iChangeObserver;
	RFs&			iRFs;

	CArrayFixFlat<TEntry>* iEntries;

	CBIODatabase*	iBioDB;
	RTimer	iTimer;
	};

#endif
