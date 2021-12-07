/**
 * @file
 *
 * Contains declaration of TSmsUtilities and KUidMsgTypeSMS
 *
 * Copyright (c) 2000-2002 Symbian Ltd.  All rights reserved.
 */

#ifndef SMUT_H_
#define SMUT_H_

// Sms Utilities

#include <msvstd.h>
#include <msvids.h>
#include <barsc.h>

//	Forward Declarations

class CSmsMessage;
class CContactItemField;
class TResourceReader;
class CMsvSession;

//	Constants

const TUid KUidMsgTypeSMS			= {0x1000102C}; 
const TInt KSmsDescriptionLength	= 32;
const TInt KSmsDetailsLength		= 32;

_LIT(KSmsResourceFile, "\\system\\data\\SMSS.RSC");


class TSmsUtilities
/**
 * SMS Messaging utility functions
 *
 * @ToDo 27/2/2002 Should change to C-Type class because of member iResFile
 */
	{
	friend class CSmsClientMtm;
	friend class CSmsSettings;
	friend class CSmsHeader;
	friend class CSmsNumber;

public:

	enum TSmsUtilitiesSpecialMessageType
	/**
	 * Special SMS Message Indication Type
	 */
		{
		EVoiceMessageWaiting = 0,		///< 0000 0000 Voice Message Waiting
		EFaxMessageWaiting,				///< 0000 0001 Fax Message Waiting
		EEmailMessageWaiting,			///< 0000 0010 Electronic Mail Message Waiting
		EOtherMessageWaiting,			///< 0000 0011 Other Message Waiting (see 3GPP TS 23.038 [9] for definition of "other")
		ESpecialMessageTypeMask = 0x7F	///< 0111 1111
		};

	IMPORT_C TSmsUtilities();
	IMPORT_C ~TSmsUtilities();

	IMPORT_C static void ServiceIdL(CMsvServerEntry& aEntry, TMsvId& arFirstId, TUid aMtm = KUidMsgTypeSMS, CMsvEntrySelection* arServiceIds = NULL);
	IMPORT_C static void ServiceIdL(CMsvEntry& aEntry, TMsvId& arFirstId, TUid aMtm = KUidMsgTypeSMS, CMsvEntrySelection* arServiceIds = NULL);
	IMPORT_C static void ServiceIdL(CMsvSession& aSession, TMsvId& arFirstId, TUid aMtm = KUidMsgTypeSMS, CMsvEntrySelection* arServiceIds = NULL); //more efficient version of the previous one

	IMPORT_C static void PopulateMsgEntry(TMsvEntry& arEntry, const CSmsMessage& aMessage, TMsvId aServiceId, TUid aMtm = KUidMsgTypeSMS);

	IMPORT_C static TInt GetDetails(RFs& aFs, const CSmsMessage& aMessage, TDes& arDetails, TInt aMaxLength = KSmsDetailsLength);
	IMPORT_C static TInt GetDetails(RFs& aFs, const TDesC& aFromAddress, TDes& arDetails, TInt aMaxLength = KSmsDetailsLength);
	IMPORT_C static void GetDescription(const CSmsMessage& aMessage, TDes& arDescription, TInt aMaxLength = KSmsDescriptionLength);


private:
	void OpenResourceFileL(RFs& aFs, const TDesC& aResFileName);
	inline void CloseResourceFile();

	void ReadResourceStringL(TInt aId, TDes& rString);
	void GetResourceReaderLC(TInt aResourceId, TResourceReader& rReader);

	static void CompareEntryL(const TMsvEntry& aEntry, TUid aMtm, TMsvId& arFirstId, CMsvEntrySelection* arServiceIds);
	static void GetName(CContactItemField& aField, TUid aFieldType, TDes& aName);
	static void DoGetDetailsL(RFs& aFs, const TDesC& aFromAddress, TDes& arDetails, TInt aMaxLength);
	static void Replace(const TDesC& aOld, const TDesC& aNew, TDes& rString);

	static TInt GetSpecialMessageDescription(const CSmsMessage& aMessage, TDes& arDescription, TInt aMaxLength);
	static void DoGetSpecialMessageDescriptionL(const CSmsMessage& aMessage, TDes& arDescription, TInt aMaxLength);
	static void ExtractDescriptionFromMessage(const CSmsMessage& aMessage, TDes& arDescription, TInt aMaxLength);

	static TBool ValidGsmNumber(const TDesC& aTelephone);
	static void ReadResourceStringL(const TDesC& aResFileName, TInt aResourceId, TDes& aString);
	static void ReadResourceStringL(RFs& aFs, const TDesC& aResFileName, TInt aResourceId, TDes& aString);
	
private:
	RResourceFile iResFile;
	};

#include "smut.inl"

#endif
