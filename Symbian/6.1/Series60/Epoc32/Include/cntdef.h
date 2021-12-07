// CNTDEF.H
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//

#ifndef __CNTDEF_H__
#define __CNTDEF_H__

#include <e32base.h>
#include <d32dbms.h>
//
#include "cntdef.hrh"

// Constants
const TInt KSpeedDialPhoneLength = 32;
const TInt KCntMinSpeedDialIndex = 1;
const TInt KCntMaxSpeedDialIndex = 9;
//Phone Match Length
const TInt KMaxPhoneMatchLength = 7;

//used for firstname, lastname, companyname and e-mail address
const TInt KCntMaxTextFieldLength=255;

// Type definitions
typedef TBuf<KSpeedDialPhoneLength> TSpeedDialPhoneNumber;

/**
 * Contact item ID.
 *
 * These are used to uniquely identify contact items within a contacts
 * database. Contact items include contact cards, contact card templates,
 * contact card groups and own cards. Contact item IDs are also used to
 * uniquely identify agents.
 *
 * @since 5.0
 * @lib ""
 */
typedef TInt32 TContactItemId; 

/**
 * A UID which identifies a contact item field's type.
 *
 * The possible values are defined as UIDs in file cntdef.h. See the
 * <code>KUidContactFieldXxx</code> values.
 *
 * @since 5.0
 * @lib ""
 */
typedef TUid TFieldType;

/**
 * The storage type is an unsigned integer value which identifies the
 * type of data stored in a contact item field.
 *
 * The possible values for the storage type are defined in cntdef.hrh
 * as:<code>KStorageTypeText</code> (used by
 * <code>CContactTextField</code>s)<code>KStorageTypeStore</code> (used
 * by <code>CContactStoreField</code>s)<code>KStorageTypeContactItemId</-
 * code> (used by
 * <code>CContactAgentField</code>s)<code>KStorageTypeDateTime</code>
 * (used by <code>CContactDateField</code>s)Note that numeric fields are
 * not currently supported. Numbers (e.g. telephone numbers) are stored
 * in the database using text fields.
 *
 * @since 5.0
 * @lib ""
 */
typedef TUint TStorageType;

/**
 * Machine identifier.
 *
 * Used when syncronising the contact database, for instance with a PC
 * scheduler application see
 * <code>CContactDatabase::SetLastSyncDateL()</code> and
 * <code>GetLastSyncDateL()</code>. Identifies the machine with which the
 * database has been synchronised.
 *
 * @since 5.0
 * @lib ""
 */
typedef TInt32 TContactSyncId;

/**
 * The third UID of the contacts database file, c:\system\data\contacts.cdb, 
 * is defined as KUidContactsDbFile. This should be used by file recogniser
 * implementations.
 */
const TInt KUidContactsDbFileValue=0x100065FF;
const TUid KUidContactsDbFile={KUidContactsDbFileValue};


const TContactItemId KNullContactId=-1;
const TContactItemId KGoldenTemplateId=0;

const TUid KClipboardUidTypeVCard={0x100038f6};

const TUid KUidContactCard={0x10001309};
const TUid KUidContactGroup={0x1000130A};
const TUid KUidContactTemplate={0x1000130B};
const TUid KUidContactOwnCard={0x10004F95}; 
const TUid KUidContactCardTemplate={0x10004FF1};

/** KUidContactItem refers to any CContactItem derived class */
const TUid KUidContactItem={0x10005673}; 
/** KUidContactCardOrGroup includes CContactCard and CContactGroup classes */
const TUid KUidContactCardOrGroup={0x10005F71};  


/** 
 * Speed-dial UIDs. 
 * These are used to indicate the speed-dial position for a particular field.
 * They are added to the content type of a phone number field set as a 
 * speed-dial using CContactDatabase::SetFieldAsSpeedDialL().
 */
const TUid KUidSpeedDialOne={KUidSpeedDialOneValue}; 
const TUid KUidSpeedDialTwo={KUidSpeedDialTwoValue};
const TUid KUidSpeedDialThree={KUidSpeedDialThreeValue};
const TUid KUidSpeedDialFour={KUidSpeedDialFourValue};
const TUid KUidSpeedDialFive={KUidSpeedDialFiveValue};
const TUid KUidSpeedDialSix={KUidSpeedDialSixValue};
const TUid KUidSpeedDialSeven={KUidSpeedDialSevenValue};
const TUid KUidSpeedDialEight={KUidSpeedDialEightValue};
const TUid KUidSpeedDialNine={KUidSpeedDialNineValue};

/** 
 * Contact field type UIDs.
 */
const TUid KUidContactFieldAddress={KUidContactFieldAddressValue};
const TUid KUidContactFieldPostOffice={KUidContactFieldPostOfficeValue};
const TUid KUidContactFieldExtendedAddress={KUidContactFieldExtendedAddressValue};
const TUid KUidContactFieldLocality={KUidContactFieldLocalityValue};
const TUid KUidContactFieldRegion={KUidContactFieldRegionValue};
const TUid KUidContactFieldPostcode={KUidContactFieldPostCodeValue};
const TUid KUidContactFieldCountry={KUidContactFieldCountryValue};

const TUid KUidContactFieldCompanyName={KUidContactFieldCompanyNameValue};
const TUid KUidContactFieldPhoneNumber={KUidContactFieldPhoneNumberValue};
const TUid KUidContactFieldGivenName={KUidContactFieldGivenNameValue};
const TUid KUidContactFieldFamilyName={KUidContactFieldFamilyNameValue};
const TUid KUidContactFieldAdditionalName={KUidContactFieldAdditionalNameValue};
const TUid KUidContactFieldSuffixName={KUidContactFieldSuffixNameValue};
const TUid KUidContactFieldPrefixName={KUidContactFieldPrefixNameValue};
const TUid KUidContactFieldHidden={KUidContactFieldHiddenValue};
const TUid KUidContactFieldDefinedText={KUidContactFieldDefinedTextValue};
const TUid KUidContactFieldEMail={KUidContactFieldEMailValue};
const TUid KUidContactFieldMsg={KUidContactFieldMsgValue};
const TUid KUidContactFieldSms={KUidContactFieldSmsValue};
const TUid KUidContactFieldFax={KUidContactFieldFaxValue};
const TUid KUidContactFieldNote={KUidContactFieldNoteValue};
const TUid KUidContactStorageInline={KUidContactFieldStorageInlineValue};
const TUid KUidContactFieldBirthday={KUidContactFieldBirthdayValue};
const TUid KUidContactFieldUrl={KUidContactFieldUrlValue};
const TUid KUidContactFieldTemplateLabel={KUidContactFieldTemplateLabelValue};
const TUid KUidContactFieldPicture={KUidContactFieldPictureValue};
const TUid KUidContactFieldDTMF={KUidContactFieldDTMFValue};
const TUid KUidContactFieldRingTone={KUidContactFieldRingToneValue};
const TUid KUidContactFieldJobTitle={KUidContactFieldJobTitleValue};

/**
 * Voice-tag UID. 
 * Indicates that the field supports voice-tag dialling.
 */
const TUid KUidContactsVoiceDialField={KUidContactsVoiceDialFieldValue};

const TUid KUidContactFieldNone={KUidContactFieldNoneValue};
const TUid KUidContactFieldMatchAll={0x110FFF22};

/**
 * Contact field type vCard mappings.
 * The vCard mapping describes how the field should be handled by the 
 * vCard import/export code. 
 */
const TUid KUidContactFieldVCardMapPOSTOFFICE={KIntContactFieldVCardMapPOSTOFFICE};
const TUid KUidContactFieldVCardMapEXTENDEDADR={KIntContactFieldVCardMapEXTENDEDADR};
const TUid KUidContactFieldVCardMapADR={KIntContactFieldVCardMapADR};
const TUid KUidContactFieldVCardMapLOCALITY={KIntContactFieldVCardMapLOCALITY};
const TUid KUidContactFieldVCardMapREGION={KIntContactFieldVCardMapREGION};
const TUid KUidContactFieldVCardMapPOSTCODE={KIntContactFieldVCardMapPOSTCODE};
const TUid KUidContactFieldVCardMapCOUNTRY={KIntContactFieldVCardMapCOUNTRY};

const TUid KUidContactFieldVCardMapAGENT={KIntContactFieldVCardMapAGENT};
const TUid KUidContactFieldVCardMapBDAY={KIntContactFieldVCardMapBDAY};
const TUid KUidContactFieldVCardMapEMAILINTERNET={KIntContactFieldVCardMapEMAILINTERNET};
const TUid KUidContactFieldVCardMapGEO={KIntContactFieldVCardMapGEO};
const TUid KUidContactFieldVCardMapLABEL={KIntContactFieldVCardMapLABEL};
const TUid KUidContactFieldVCardMapLOGO={KIntContactFieldVCardMapLOGO};
const TUid KUidContactFieldVCardMapMAILER={KIntContactFieldVCardMapMAILER};
const TUid KUidContactFieldVCardMapNOTE={KIntContactFieldVCardMapNOTE};
const TUid KUidContactFieldVCardMapORG={KIntContactFieldVCardMapORG};
const TUid KUidContactFieldVCardMapPHOTO={KIntContactFieldVCardMapPHOTO};
const TUid KUidContactFieldVCardMapROLE={KIntContactFieldVCardMapROLE};
const TUid KUidContactFieldVCardMapSOUND={KIntContactFieldVCardMapSOUND};
const TUid KUidContactFieldVCardMapTEL={KIntContactFieldVCardMapTEL};
const TUid KUidContactFieldVCardMapTELFAX={KIntContactFieldVCardMapTELFAX};
const TUid KUidContactFieldVCardMapTITLE={KIntContactFieldVCardMapTITLE};
const TUid KUidContactFieldVCardMapURL={KIntContactFieldVCardMapURL};
const TUid KUidContactFieldVCardMapUnusedN={KIntContactFieldVCardMapUnusedN};
const TUid KUidContactFieldVCardMapUnusedFN={KIntContactFieldVCardMapUnusedFN};
const TUid KUidContactFieldVCardMapNotRequired={KIntContactFieldVCardMapNotRequired};
const TUid KUidContactFieldVCardMapUnknownXDash={KIntContactFieldVCardMapUnknownXDash};
const TUid KUidContactFieldVCardMapUnknown={KIntContactFieldVCardMapUnknown};
const TUid KUidContactFieldVCardMapUID={KIntContactFieldVCardMapUID};
const TUid KUidContactFieldVCardMapWORK={KIntContactFieldVCardMapWORK};
const TUid KUidContactFieldVCardMapHOME={KIntContactFieldVCardMapHOME};
const TUid KUidContactFieldVCardMapMSG={KIntContactFieldVCardMapMSG};
const TUid KUidContactFieldVCardMapVOICE={KIntContactFieldVCardMapVOICE};
const TUid KUidContactFieldVCardMapFAX={KIntContactFieldVCardMapFAX};
const TUid KUidContactFieldVCardMapPREF={KIntContactFieldVCardMapPREF};
const TUid KUidContactFieldVCardMapCELL={KIntContactFieldVCardMapCELL};
const TUid KUidContactFieldVCardMapPAGER={KIntContactFieldVCardMapPAGER};
const TUid KUidContactFieldVCardMapBBS={KIntContactFieldVCardMapBBS};
const TUid KUidContactFieldVCardMapMODEM={KIntContactFieldVCardMapMODEM};
const TUid KUidContactFieldVCardMapCAR={KIntContactFieldVCardMapCAR};
const TUid KUidContactFieldVCardMapISDN={KIntContactFieldVCardMapISDN};
const TUid KUidContactFieldVCardMapVIDEO={KIntContactFieldVCardMapVIDEO};
const TUid KUidContactFieldVCardMapDOM={KIntContactFieldVCardMapDOM};
const TUid KUidContactFieldVCardMapINTL={KIntContactFieldVCardMapINTL};
const TUid KUidContactFieldVCardMapPOSTAL={KIntContactFieldVCardMapPOSTAL};
const TUid KUidContactFieldVCardMapPARCEL={KIntContactFieldVCardMapPARCEL};
const TUid KUidContactFieldVCardMapGIF={KIntContactFieldVCardMapGIF};
const TUid KUidContactFieldVCardMapCGM={KIntContactFieldVCardMapCGM};
const TUid KUidContactFieldVCardMapWMF={KIntContactFieldVCardMapWMF};
const TUid KUidContactFieldVCardMapBMP={KIntContactFieldVCardMapBMP};
const TUid KUidContactFieldVCardMapMET={KIntContactFieldVCardMapMET};
const TUid KUidContactFieldVCardMapPMB={KIntContactFieldVCardMapPMB};
const TUid KUidContactFieldVCardMapDIB={KIntContactFieldVCardMapDIB};
const TUid KUidContactFieldVCardMapPICT={KIntContactFieldVCardMapPICT};
const TUid KUidContactFieldVCardMapTIFF={KIntContactFieldVCardMapTIFF};
const TUid KUidContactFieldVCardMapPDF={KIntContactFieldVCardMapPDF};
const TUid KUidContactFieldVCardMapPS={KIntContactFieldVCardMapPS};
const TUid KUidContactFieldVCardMapJPEG={KIntContactFieldVCardMapJPEG};
const TUid KUidContactFieldVCardMapMPEG={KIntContactFieldVCardMapMPEG};
const TUid KUidContactFieldVCardMapMPEG2={KIntContactFieldVCardMapMPEG2};
const TUid KUidContactFieldVCardMapAVI={KIntContactFieldVCardMapAVI};
const TUid KUidContactFieldVCardMapQTIME={KIntContactFieldVCardMapQTIME};
const TUid KUidContactFieldVCardMapTZ={KIntContactFieldVCardMapTZ};
const TUid KUidContactFieldVCardMapKEY={KIntContactFieldVCardMapKEY};
const TUid KUidContactFieldVCardMapX509={KIntContactFieldVCardMapX509};
const TUid KUidContactFieldVCardMapPGP={KIntContactFieldVCardMapPGP};
const TUid KUidContactFieldVCardMapSMIME={KIntContactFieldVCardMapSMIME};



_LIT(KVersitParamWork,"WORK");
_LIT(KVersitParamHome,"HOME");
_LIT(KVersitParamMsg,"MSG");
_LIT(KVersitParamVoice,"VOICE");
_LIT(KVersitParamFax,"FAX");
_LIT(KVersitParamPref,"PREF");
_LIT(KVersitParamCell,"CELL");
_LIT(KVersitParamPager,"PAGER");
_LIT(KVersitParamBbs,"BBS");
_LIT(KVersitParamModem,"MODEM");
_LIT(KVersitParamCar,"CAR");
_LIT(KVersitParamIsdn,"ISDN");
_LIT(KVersitParamVideo,"VIDEO");
_LIT(KVersitParamDom,"DOM");
_LIT(KVersitParamGif,"GIF");
_LIT(KVersitParamCgm,"CGM");
_LIT(KVersitParamWmf,"WMF");
_LIT(KVersitParamBmp,"BMP");
_LIT(KVersitParamMet,"MET");
_LIT(KVersitParamPmb,"PMB");
_LIT(KVersitParamDib,"DIB");
_LIT(KVersitParamPict,"PICT");
_LIT(KVersitParamTiff,"TIFF");
_LIT(KVersitParamPdf,"PDF");
_LIT(KVersitParamPs,"PS");
_LIT(KVersitParamJpeg,"JPEG");
_LIT(KVersitParamMpeg,"MPEG");
_LIT(KVersitParamMpeg2,"MPEG2");
_LIT(KVersitParamAvi,"AVI");
_LIT(KVersitParamQtime,"QTIME");
_LIT(KVersitParamX509,"X509");
_LIT(KVersitParamPGP,"PGP");

_LIT8(KVersitParam8Work,"WORK");
_LIT8(KVersitParam8Home,"HOME");
_LIT8(KVersitParam8Msg,"MSG");
_LIT8(KVersitParam8Voice,"VOICE");
_LIT8(KVersitParam8Fax,"FAX");
_LIT8(KVersitParam8Pref,"PREF");
_LIT8(KVersitParam8Cell,"CELL");
_LIT8(KVersitParam8Pager,"PAGER");
_LIT8(KVersitParam8Bbs,"BBS");
_LIT8(KVersitParam8Modem,"MODEM");
_LIT8(KVersitParam8Car,"CAR");
_LIT8(KVersitParam8Isdn,"ISDN");
_LIT8(KVersitParam8Video,"VIDEO");
_LIT8(KVersitParam8Dom,"DOM");
_LIT8(KVersitParam8Gif,"GIF");
_LIT8(KVersitParam8Cgm,"CGM");
_LIT8(KVersitParam8Wmf,"WMF");
_LIT8(KVersitParam8Bmp,"BMP");
_LIT8(KVersitParam8Met,"MET");
_LIT8(KVersitParam8Pmb,"PMB");
_LIT8(KVersitParam8Dib,"DIB");
_LIT8(KVersitParam8Pict,"PICT");
_LIT8(KVersitParam8Tiff,"TIFF");
_LIT8(KVersitParam8Pdf,"PDF");
_LIT8(KVersitParam8Ps,"PS");
_LIT8(KVersitParam8Jpeg,"JPEG");
_LIT8(KVersitParam8Mpeg,"MPEG");
_LIT8(KVersitParam8Mpeg2,"MPEG2");
_LIT8(KVersitParam8Avi,"AVI");
_LIT8(KVersitParam8Qtime,"QTIME");
_LIT8(KVersitParam8X509,"X509");
_LIT8(KVersitParam8PGP,"PGP");

/**
 * Array of contact item IDs (<code>TContactItemId</code>s).
 *
 * Instances of this class are passed to several contact database
 * functions, for instance
 * <code>CContactDatabase::DeleteContactsL()</code>.
 *
 * @since 5.0
 * @lib "cntmodel.lib"
 */
class CContactIdArray : public CBase
	{
public:
	IMPORT_C static CContactIdArray* NewL();
	IMPORT_C static CContactIdArray* NewLC();
	IMPORT_C static CContactIdArray* NewL(const CContactIdArray* aArray);
	IMPORT_C static CContactIdArray* NewLC(const CContactIdArray* aArray);
	IMPORT_C ~CContactIdArray();
	inline const TContactItemId& operator[](TInt aIndex) const;
	inline TContactItemId& operator[](TInt aIndex);
	inline TInt Count() const;
	inline void Reset();
	IMPORT_C TInt Find(TContactItemId aId) const;
	IMPORT_C void AddL(TContactItemId aId);

	inline void Remove(TInt aIndex);
	inline void Remove(TInt aIndex,TInt aCount);
	inline void InsertL(TInt aIndex,TContactItemId aId);
	IMPORT_C void MoveL(TInt aOldIndex,TInt aNewIndex);
	IMPORT_C void ReverseOrder();
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
private:
	CContactIdArray();
	void ConstructL();
	void CloneL(const CContactIdArray* aArray);
private:
	CArrayFixFlat<TContactItemId> *iIds;
	};
inline const TContactItemId& CContactIdArray::operator[](TInt aIndex) const
	{ return (*iIds)[aIndex]; }
inline TContactItemId& CContactIdArray::operator[](TInt aIndex)
	{ return (*iIds)[aIndex]; }
/**
 * Gets the number of contact IDs in the array.
 *
 * @returns   "TInt"
 *            The number of contact IDs in the array.
 */
inline TInt CContactIdArray::Count() const
	{ return iIds->Count(); }
/** Removes all contact IDs from the array. */
inline void CContactIdArray::Reset()
	{ iIds->Reset(); }
/**
 * Removes the indexed contact ID from the array.
 *
 * Note:The index value must not be negative and must not be greater than
 * the number of elements currently in the array, otherwise the function
 * raises a panic.
 *
 * @param     "TInt aIndex"
 *            The index of the contact ID to remove.
 */
inline void CContactIdArray::Remove(TInt aIndex)
	{ iIds->Delete(aIndex); }
inline void CContactIdArray::Remove(TInt aIndex,TInt aCount)
	{ iIds->Delete(aIndex,aCount); }
/**
 * Inserts a contact ID into the array.
 *
 * Note:The index must be valid or a panic occurs.
 *
 * @param     "TInt aIndex"
 *            The index at which to insert the contact ID.
 * @param     "TContactItemId aId"
 *            The contact ID to insert.
 */
inline void CContactIdArray::InsertL(TInt aIndex,TContactItemId aId)
	{ iIds->InsertL(aIndex,aId); }

#endif
