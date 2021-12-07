// AGMVCAL.H
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMVCAL_H__
#define __AGMVCAL_H__


#include <vcal.h>
#include <apgdoor.h>
#include <concnf.h>
#include <confndr.h>
#include <conlist.h>
#include "agmentry.h"
#include "agmmodel.h"




const TUid KUidApaDoorStateStream={0x1000012a};
//const TUid KUidApaDoorDocStream={0x10000144};
const TUid KPlainTextToWordConverterUid={0x10001823};
const TUid KWordToPlainTextConverterUid={0x10001824};

#define KConverterBufferSize 1024

// Extended VCal fields

_LIT(KVCalTokenENTRYTYPE,"AGENDAENTRYTYPE"); // for externalizing
_LIT(KVCalTokenXDASHENTRYTYPE,"X-EPOCAGENDAENTRYTYPE"); // for internalizing
_LIT8(KVCalToken8ENTRYTYPE,"AGENDAENTRYTYPE"); // for externalizing
_LIT8(KVCalToken8XDASHENTRYTYPE,"X-EPOCAGENDAENTRYTYPE"); // for internalizing

_LIT(KVCalTokenTypeAPPT,"APPOINTMENT");
_LIT(KVCalTokenTypeANNIV,"ANNIVERSARY");
_LIT(KVCalTokenTypeEVENT,"EVENT");
_LIT(KVCalTokenTypeTODO,"TODO");

_LIT(KVCalTokenPUBLIC,"PUBLIC");
_LIT(KVCalTokenPRIVATE,"PRIVATE");
_LIT(KVCalTokenCONFIDENTIAL,"CONFIDENTIAL");

_LIT(KVCalTokenTYPE,"TYPE");
_LIT8(KVCalToken8TYPE,"TYPE");
_LIT(KVCalValueEPOCSOUND,"X-EPOCSOUND");
_LIT8(KVCalValue8EPOCSOUND,"X-EPOCSOUND");


// Attendee defines
_LIT(KVCalAttendeeROLE,"ROLE");
_LIT(KVCalAttendeeSTATUS,"STATUS");
_LIT(KVCalAttendeeRSVP,"RSVP");
_LIT(KVCalAttendeeEXPECT,"EXPECT");
_LIT8(KVCalAttendee8ROLE,"ROLE");
_LIT8(KVCalAttendee8STATUS,"STATUS");
_LIT8(KVCalAttendee8RSVP,"RSVP");
_LIT8(KVCalAttendee8EXPECT,"EXPECT");

_LIT(KVCalAttendeeRoleATTENDEE,"ATTENDEE");
_LIT(KVCalAttendeeRoleORGANIZER,"ORGANIZER");
_LIT(KVCalAttendeeRoleOWNER,"OWNER");
_LIT(KVCalAttendeeRoleDELEGATE,"DELEGATE");
_LIT8(KVCalAttendee8RoleATTENDEE,"ATTENDEE");
_LIT8(KVCalAttendee8RoleORGANIZER,"ORGANIZER");
_LIT8(KVCalAttendee8RoleOWNER,"OWNER");
_LIT8(KVCalAttendee8RoleDELEGATE,"DELEGATE");

_LIT(KVCalAttendeeStatusACCEPTED,"ACCEPTED");
_LIT(KVCalAttendeeStatusNEEDSACTION,"NEEDSACTION");
_LIT(KVCalAttendeeStatusSENT,"SENT");
_LIT(KVCalAttendeeStatusTENTATIVE,"TENTATIVE");
_LIT(KVCalAttendeeStatusCONFIRMED,"CONFIRMED");
_LIT(KVCalAttendeeStatusDECLINED,"DECLINED");
_LIT(KVCalAttendeeStatusCOMPLETED,"COMPLETED");
_LIT(KVCalAttendeeStatusDELEGATED,"DELEGATED");
_LIT(KVCalAttendeeStatusXDASHRECEIVED,"X-RECEIVED"); // Epoc extension for received vCalendars
_LIT8(KVCalAttendeeStatus8ACCEPTED,"ACCEPTED");
_LIT8(KVCalAttendeeStatus8NEEDSACTION,"NEEDSACTION");
_LIT8(KVCalAttendeeStatus8SENT,"SENT");
_LIT8(KVCalAttendeeStatus8TENTATIVE,"TENTATIVE");
_LIT8(KVCalAttendeeStatus8CONFIRMED,"CONFIRMED");
_LIT8(KVCalAttendeeStatus8DECLINED,"DECLINED");
_LIT8(KVCalAttendeeStatus8COMPLETED,"COMPLETED");
_LIT8(KVCalAttendeeStatus8DELEGATED,"DELEGATED");
_LIT8(KVCalAttendeeStatus8XDASHRECEIVED,"X-RECEIVED"); // Epoc extension for received vCalendars

_LIT(KVCalAttendeeRsvpYES,"YES");
_LIT(KVCalAttendeeRsvpNO,"NO");
_LIT8(KVCalAttendeeRsvp8YES,"YES");
_LIT8(KVCalAttendeeRsvp8NO,"NO");

_LIT(KVCalAttendeeExpectFYI,"FYI");
_LIT(KVCalAttendeeExpectREQUIRE,"REQUIRE");
_LIT(KVCalAttendeeExpectREQUEST,"REQUEST");
_LIT(KVCalAttendeeExpectIMMEDIATE,"IMMEDIATE");
_LIT8(KVCalAttendeeExpect8FYI,"FYI");
_LIT8(KVCalAttendeeExpect8REQUIRE,"REQUIRE");
_LIT8(KVCalAttendeeExpect8REQUEST,"REQUEST");
_LIT8(KVCalAttendeeExpect8IMMEDIATE,"IMMEDIATE");

// Categories property definitions
_LIT(KVCalCategoriesAPPOINTMENT,"APPOINTMENT");
_LIT(KVCalCategoriesBUSINESS,"BUSINESS");
_LIT(KVCalCategoriesEDUCATION,"EDUCATION");
_LIT(KVCalCategoriesHOLIDAY,"HOLIDAY");
_LIT(KVCalCategoriesMEETING,"MEETING");
_LIT(KVCalCategoriesMISCELLANEOUS,"MISCELLANEOUS");
_LIT(KVCalCategoriesPERSONAL,"PERSONAL");
_LIT(KVCalCategoriesPHONECALL,"PHONECALL");
_LIT(KVCalCategoriesSICKDAY,"SICKDAY");
_LIT(KVCalCategoriesSPECIALOCCASION,"SPECIALOCCASION");
_LIT(KVCalCategoriesTRAVEL,"TRAVEL");
_LIT(KVCalCategoriesVACATION,"VACATION");
_LIT(KVCalTokenXDash,"X-"); // same as KVersitTokenXDash but not explicitly narrow

_LIT(KVCalTokenXDASHEPOCTODOLIST,"X-EPOCTODOLIST"); // Epoc extension for To-Do lists (for internalizing).
_LIT(KVCalTokenEPOCTODOLIST,"TODOLIST");		// for externalizing
_LIT8(KVCalToken8XDASHEPOCTODOLIST,"X-EPOCTODOLIST"); // Epoc extension for To-Do lists (for internalizing).
_LIT8(KVCalToken8EPOCTODOLIST,"TODOLIST");		// for externalizing




// Picture type for adding document data to a CRichText

class CMemoPicture : public CApaDoorBase
	{
public:
	CMemoPicture(CBufFlat* aBuffer);
	~CMemoPicture();

	static CMemoPicture* NewL(CBufFlat* aBuffer);
// from CPicture
	void Draw(CGraphicsContext& aGc,const TPoint& aTopLeft,const TRect& aClipRect,
						MGraphicsDeviceMap* aMap)const; // draws according to current iPicFormat
	void GetOriginalSizeInTwips(TSize& aSize)const;
	TStreamId StoreL(CStreamStore& aStore) const;
private:
	// required so CPicture's can be swizzled
	void ExternalizeL(RWriteStream& aStream)const;
	// from CApaDoorBase
	virtual TSize GlassDoorSize()const;
	void ExternalizeStateStreamL(CStreamStore& aStore,CStreamDictionary& aStreamDict)const;
	void StoreDocumentDataL(CEmbeddedStore& aStore)const;
private:
	CBufFlat*	iBuffer;
	};


// Agenda Entry to VCal conversion

class CAgendaEntryToVCalConverter : public CBase
	{
public:
	void ExportEntryL(CAgnEntry* aEntry, CVersitParser* aParser, CAgnTodoListNames* aTodoNameList, CAgnEntryModel* aModel);
private:
	void AddEntryPropertiesL(CAgnEntry* aEntry, CVersitParser* aParser,CAgnTodoListNames* aTodoNameList, CAgnEntryModel* aModel);
	void AddApptPropertiesL(CVersitParser* aParser, CAgnAppt* aEntry);
	void AddAnnivPropertiesL(CVersitParser* aParser, CAgnAnniv* aEntry);
	void AddEventPropertiesL(CVersitParser* aParser, CAgnEvent* aEntry);
	void AddTodoPropertiesL(CVersitParser* aParser, CAgnTodo* aEntry, CAgnTodoListNames* aTodoNameList);

	void AddRichTextPropertyL(CVersitParser* aParser, const TDesC8& aToken, CRichText* aText, CAgnEntryModel* aModel = NULL, TStreamId aRichTextStreamId = KNullStreamId);
	void AddIntegerPropertyL(CVersitParser* aParser, const TDesC8& aToken, TInt aInt);
	void AddDateTimePropertyL(CVersitParser* aParser, const TDesC8& aToken, const TTime& aTime, const TVersitDateTime::TRelativeTime aRelativeTime);
	void AddDesPropertyL(CVersitParser* aParser, const TDesC8& aToken, const TDesC& aDes);
	void AddAlarmPropertyL(CVersitParser* aParser, const TDesC8& aToken, const TTime& aAlarmTime, const TDesC& aAlarmName);
	void AddAttendeePropertyL(CVersitParser* aParser, CAgnAttendee* aAttendee);
	void AddRepeatPropertiesL(CVersitParser* aParser, CAgnRptDef* aRpt);
	void AddRepeatExceptionPropertiesL(CVersitParser* aParser, CAgnRptDef* aRpt);

	void ExportAttachmentL(CVersitParser* aParser, const TDesC8& aToken, CAgnEntryModel* aModel, const TPictureHeader& aHeader, TStreamId aRichTextStreamId);
	void ConvertAttachmentL(CVersitParser* aParser, const TDesC8& aToken, RStoreReadStream& aDocStream);
	CStreamDictionary* CreateDictionaryLC(CEmbeddedStore& aEmbeddedStore, TStreamId& aId);
	void AddCategoryPropertyL(CVersitParser* aParser, CAgnEntry* aEntry);

	// Repeat properties
	CVersitRecurrence* CreateWeeklyRepeatL(CAgnRptDef* aRpt, TInt aDuration, TVersitDateTime* aEndTime);
	CVersitRecurrence* CreateMonthlyByDaysRepeatL(CAgnRptDef* aRpt, TInt aDuration, TVersitDateTime* aEndTime);
	CVersitRecurrence* CreateMonthlyByDateRepeatL(CAgnRptDef* aRpt, TInt aDuration, TVersitDateTime* aEndTime);
	CVersitRecurrence* CreateYearlyByDaysRepeatL(CAgnRptDef* aRpt, TInt aDuration, TVersitDateTime* aEndTime);
	CVersitRecurrence* CreateYearlyByDateRepeatL(CAgnRptDef* aRpt, TInt aDuration, TVersitDateTime* aEndTime, TMonth aMonth);
	static void ResetAndDestroyArrayOfParams(TAny* aObject);
	void ReadResourceFileL();
	TVersitDateTime* CreateVersitDateTimeAndSetFlagL(const TDateTime& aDateTime,TVersitDateTime::TRelativeTime aRelativeTime);
private:
	CParserVCal *iVCal;
	TBool iExportUTCDesignator; 
	};


// VCal to Agenda Entry conversion

class CVCalToAgendaEntryConverter : public CBase
	{
public:
	void ImportVCalL(CVersitParser& aParser, CAgnEntryModel& aModel, CArrayPtr<CAgnEntry>& aEntryArray, CAgnTodoListNames& aTodoNameList);
	CAgnEntry* UpdateVCalL(CVersitParser* aParser, CAgnEntryModel* aModel, TBool& aEntryWasDeleted, CAgnTodoListNames* aTodoNameList=NULL);
private:
	CAgnEntry::TType GetEntryTypeL(CVersitParser& aParser);
	TBool GetStartAndEndDatesL(CVersitParser& aParser, TTime& aStartDate, TTime& aEndDate);

	TBool ImportApptPropertiesL(CVersitParser& aParser, CAgnAppt* aEntry);
	TBool ImportEventPropertiesL(CVersitParser& aParser, CAgnEvent* aEntry);
	TBool ImportAnnivPropertiesL(CVersitParser& aParser, CAgnAnniv* aEntry);
	TBool ImportTodoPropertiesL(CVersitParser& aParser, CAgnTodo* aEntry, CAgnTodoListNames& aTodoNameList, CAgnEntryModel& aModel);

	TBool ImportDateTimePropertyL(CVersitParser& aParser, const TDesC8& aToken, TTime& aValue);
	TBool ImportIntegerPropertyL(CVersitParser& aParser, const TDesC8& aToken, TInt& aValue);
	HBufC* ImportDesPropertyL(CVersitParser& aParser, const TDesC8& aToken);

	TBool ImportAlarmPropertyL(CVersitParser& aParser, const TDesC8& aToken, const TTime& aStartTime);
	void ImportAttendeePropertiesL(CVersitParser& aParser, const TDesC8& aToken);
	void ImportCategoriesPropertyL(CVersitParser& aParser, const TDesC8& aToken);
	
	void ImportRepeatPropertyL(CVersitParser& aParser, const TDesC8& aToken, const TTime& aStartDate);
	void ImportDailyRepeatPropertiesL(CAgnRptDef* aRpt);
	void ImportWeeklyRepeatPropertiesL(CVersitRecurrenceWeekly* aRepeat, CAgnRptDef* aRpt, TDay aDefaultDayOfWeek);
	void ImportMonthlyByDayRepeatPropertiesL(CVersitRecurrenceMonthlyByDay* aRepeat, CAgnRptDef* aRpt, TInt aDefaultDayOfMonth);
	void ImportMonthlyByPosRepeatPropertiesL(CVersitRecurrenceMonthlyByPos* aRepeat, CAgnRptDef* aRpt);
	void ImportYearlyByMonthRepeatPropertiesL(CVersitRecurrenceYearlyByMonth* aRepeat, CAgnRptDef* aRpt);
	void ImportRepeatExceptionPropertiesL(CVersitParser& aParser, const TDesC8& aToken, CAgnRptDef* aRpt);

	void ImportAttachmentsL(CVersitParser& aParser, const TDesC8& aToken, CRichText* aText, CAgnEntryModel& aModel);
	void AddAttachmentL(const TDesC& aAttachment, CRichText* aText, CAgnEntryModel& aModel);
	TBool FindCategoryPropertyL(CArrayPtrFlat<CAgnCategory>* aCategoryList, CAgnCategory::TAgnCategoryType aCategoryType);
	void UpdateCategoriesPropertyL(CVersitParser& aParser);
	void UpdateAttendeePropertiesL(CVersitParser& aParser);
	void MergeVCalL(CVersitParser& aParser, CAgnEntryModel& aModel, const TAgnUniqueId& aUid, CAgnTodoListNames& aTodoNameList);
private:
	CAgnEntry*	iEntry; //for convenience
	};

#endif
