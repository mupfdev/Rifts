// VTOKEN.H
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//
 
#ifndef __VTOKEN_H__
#define __VTOKEN_H__

#include <e32base.h>

#define KMaxExternalizedTokenLength			70
#define KMinLineLengthToWriteTo				1

_LIT8(KVersitTokenColon,					":");
_LIT(KVersitTokenColonUnicode,				":");
_LIT8(KVersitTokenSemiColon,				";");
_LIT(KVersitTokenSemiColonUnicode,			";");
_LIT8(KVersitBackSlash,						"\\");
_LIT8(KVersitEscapedSemiColon,				"\\;");
_LIT(KVersitEscapedSemiColonUnicode,		"\\;");
_LIT8(KVersitTokenEquals,					"=");
_LIT8(KVersitTokenPeriod,					".");
_LIT8(KVersitTokenSpace,					" ");
_LIT8(KVersitTokenMinus,					"-");
_LIT8(KVersitTokenPlus,						"+");

_LIT8(KVersitLineBreak,						"\r\n  ");
_LIT8(KVersitTimePeriodBegin,				"P");
_LIT8(KVersitTimePeriodYear,				"Y");
_LIT8(KVersitTimePeriodMonth,				"M");
_LIT8(KVersitTimePeriodWeek,				"W");		//unused
_LIT8(KVersitTimePeriodDay,					"D");
_LIT8(KVersitTimePeriodTime,				"T");
_LIT8(KVersitTimePeriodHour,				"H");
_LIT8(KVersitTimePeriodMinute,				"M");
_LIT8(KVersitTimePeriodSecond,				"S");
_LIT8(KVersitTokenUniversalTime,			"Z");

const TUint KVersitTokenColonVal			=':';
const TUint KVersitTokenSemiColonVal		=';';
const TUint KVersitTokenBackslashVal		='\\';
const TUint KVersitTokenEqualsVal			='=';
const TUint KVersitTokenPeriodVal			='.';
const TUint KVersitTokenCommaVal			=',';
const TUint KVersitTokenLSquareBracketVal	='[';
const TUint KVersitTokenRSquareBracketVal	=']';
const TUint KVersitTokenMinusVal			='-';
const TUint KVersitTokenPlusVal				='+';
const TUint KVersitTokenYenVal				=0xa5;

const TUint KVersitTimePeriodBeginVal		='P';
const TUint KVersitTimePeriodYearVal		='Y';
const TUint KVersitTimePeriodMonthVal		='M';
const TUint KVersitTimePeriodWeekVal		='W';
const TUint KVersitTimePeriodDayVal			='D';
const TUint KVersitTimePeriodTimeVal		='T';
const TUint KVersitTimePeriodHourVal		='H';
const TUint KVersitTimePeriodMinuteVal		='M';
const TUint KVersitTimePeriodSecondVal		='S';
const TUint KVersitTokenUniversalTimeVal	='Z';

const TUint KVersitRecurrenceDailyVal		='D';
const TUint KVersitRecurrenceWeeklyVal		='W';
const TUint KVersitRecurrenceNumberOfVal	='#';

_LIT(KVersitRecurrenceMonthlyByPos,		"MP");
_LIT(KVersitRecurrenceMonthlyByDay,		"MD");		//Unused
_LIT(KVersitRecurrenceYearlyByMonth,		"YM");	//Unused
_LIT(KVersitRecurrenceYearlyByDay,			"YD");
_LIT(KVersitRecurrenceMonday,				"MO");
_LIT(KVersitRecurrenceTuesday,				"TU");
_LIT(KVersitRecurrenceWednesday,			"WE");
_LIT(KVersitRecurrenceThursday,				"TH");
_LIT(KVersitRecurrenceFriday,				"FR");
_LIT(KVersitRecurrenceSaturday,				"SA");
_LIT(KVersitRecurrenceSunday,				"SU");
_LIT(KVersitRecurrenceLastDay,				"LD");

_LIT8(KVersitRecurrenceDaily,				"D");
_LIT8(KVersitRecurrenceWeekly,				"W");
_LIT8(KVersitRecurrenceNumberOf,			"#");
_LIT8(KVersitRecurrenceMonthlyByPos8,		"MP");
_LIT8(KVersitRecurrenceMonthlyByDay8,		"MD");
_LIT8(KVersitRecurrenceYearlyByMonth8,		"YM");
_LIT8(KVersitRecurrenceYearlyByDay8,			"YD");
_LIT8(KVersitRecurrenceMonday8,				"MO");
_LIT8(KVersitRecurrenceTuesday8,				"TU");
_LIT8(KVersitRecurrenceWednesday8,			"WE");
_LIT8(KVersitRecurrenceThursday8,				"TH");
_LIT8(KVersitRecurrenceFriday8,				"FR");
_LIT8(KVersitRecurrenceSaturday8,				"SA");
_LIT8(KVersitRecurrenceSunday8,				"SU");
_LIT8(KVersitRecurrenceLastDay8,				"LD");


_LIT8(KVersitTokenBEGIN,					"BEGIN");
_LIT(KVersitVarTokenBEGIN,					"BEGIN");
_LIT8(KVersitTokenEND,						"END");
_LIT8(KVersitTokenCRLF,						"\r\n"); // carriage return, line feed
_LIT8(KVersitTokenTRUE,						"TRUE");
_LIT(KVersitVarTokenTRUE,					"TRUE");
_LIT8(KVersitTokenFALSE,					"FALSE");
_LIT(KVersitVarTokenFALSE,					"FALSE");
_LIT8(KVersitTokenXDashEPOC,				"X-EPOC");
_LIT8(KVersitTokenXDash,					"X-");
_LIT8(KVersitTokenEmptyNarrow,				"");
_LIT(KVersitTokenEmpty,						"");

//The following names should not be used, versit now uses CharConv character set names.
// params
_LIT8(KVersitTokenENCODING,					"ENCODING");
_LIT8(KVersitTokenBASE64,					"BASE64");
_LIT8(KVersitTokenQUOTEDPRINTABLE,			"QUOTED-PRINTABLE");
_LIT8(KVersitToken8BIT,						"8-BIT");
_LIT8(KVersitTokenCHARSET,					"CHARSET");
_LIT8(KVersitTokenUTF8,						"UTF-8");
_LIT8(KVersitTokenUTF7,						"UTF-7");
_LIT8(KVersitTokenISO1,						"ISO-8859-1");
_LIT8(KVersitTokenISO2,						"ISO-8859-2");
_LIT8(KVersitTokenISO4,						"ISO-8859-4");
_LIT8(KVersitTokenISO5,						"ISO-8859-5");
_LIT8(KVersitTokenISO7,						"ISO-8859-7");
_LIT8(KVersitTokenISO9,						"ISO-8859-9");
// additional character sets
_LIT8(KVersitTokenISO3,						"ISO-8859-3");
_LIT8(KVersitTokenISO10,					"ISO-8859-10");
_LIT8(KVersitTokenShiftJIS,					"SHIFT_JIS");
_LIT8(KVersitTokenGB2312,					"GB 2312-80");		//This and the following contain the wrong name.
_LIT8(KVersitTokenGBK,						"GBK");
_LIT8(KVersitTokenBIG5,						"BIG5 level 1 and 2");
_LIT8(KVersitTokenISO2022JP,				"ISO 2022-JP");
_LIT8(KVersitTokenEUCJP,					"EUC-JP");
_LIT8(KVersitTokenJIS,						"JIS");


// entities
_LIT8(KVersitTokenVCALENDAR,				"VCALENDAR");
_LIT8(KVersitTokenVCARD,					"VCARD");
_LIT(KVersitVarTokenVCALENDAR,				"VCALENDAR");
_LIT(KVersitVarTokenVCARD,					"VCARD");
_LIT(KVersitVarTokenVEVENT,					"VEVENT");
_LIT(KVersitVarTokenVTODO,					"VTODO");

// properties
_LIT8(KVersitTokenAALARM,					"AALARM");
_LIT8(KVersitTokenDALARM,					"DALARM");
_LIT8(KVersitTokenPALARM,					"PALARM");
_LIT8(KVersitTokenMALARM,					"MALARM");
_LIT8(KVersitTokenDAYLIGHT,					"DAYLIGHT");
_LIT(KVersitVarTokenDAYLIGHT,				"DAYLIGHT");

_LIT8(KVersitTokenVERSION,					"VERSION");
_LIT8(KVersitTokenCATEGORIES,				"CATEGORIES");
_LIT8(KVersitTokenRESOURCES,				"RESOURCES");
_LIT8(KVersitTokenDCREATED,					"DCREATED");
_LIT8(KVersitTokenDTSTART,					"DTSTART");
_LIT8(KVersitTokenDTEND,					"DTEND");
_LIT8(KVersitTokenLASTMODIFIED,				"LAST-MODIFIED");
_LIT8(KVersitTokenCOMPLETED,				"COMPLETED");
_LIT8(KVersitTokenDUE,						"DUE");
_LIT8(KVersitTokenEXDATE,					"EXDATE");
_LIT8(KVersitTokenEXRULE,					"EXRULE");
_LIT8(KVersitTokenRDATE,					"RDATE");
_LIT8(KVersitTokenRRULE,					"RRULE");
_LIT8(KVersitTokenRNUM,						"RNUM");
_LIT8(KVersitTokenPRIORITY,					"PRIORITY");
_LIT8(KVersitTokenSEQUENCE,					"SEQUENCE");
_LIT8(KVersitTokenTRANSP,					"TRANSP");
_LIT8(KVersitTokenBDAY,						"BDAY");
_LIT8(KVersitTokenAGENT,					"AGENT");
_LIT8(KVersitTokenLABEL,					"LABEL");
_LIT8(KVersitTokenPHOTO,					"PHOTO");
_LIT8(KVersitTokenEMAIL,					"EMAIL");
_LIT8(KVersitTokenINTERNET,					"INTERNET");
_LIT8(KVersitTokenTITLE,					"TITLE");
_LIT8(KVersitTokenROLE,						"ROLE");
_LIT8(KVersitTokenLOGO,						"LOGO");
_LIT8(KVersitTokenNOTE,						"NOTE");
_LIT8(KVersitTokenSOUND,					"SOUND");
_LIT8(KVersitTokenMAILER,					"MAILER");
_LIT8(KVersitTokenPRODID,					"PRODID");
_LIT8(KVersitTokenATTACH,					"ATTACH");
_LIT8(KVersitTokenATTENDEE,					"ATTENDEE");
_LIT8(KVersitTokenCLASS,					"CLASS");
_LIT8(KVersitTokenDESCRIPTION,				"DESCRIPTION");
_LIT8(KVersitTokenLOCATION,					"LOCATION");
_LIT8(KVersitTokenRELATEDTO,				"RELATED-TO");
_LIT8(KVersitTokenSTATUS,					"STATUS");
_LIT8(KVersitTokenSUMMARY,					"SUMMARY");
_LIT8(KVersitTokenN,						"N");
_LIT8(KVersitTokenTZ,						"TZ");
_LIT8(KVersitTokenADR,						"ADR");
_LIT8(KVersitTokenORG,						"ORG");
_LIT8(KVersitTokenREV,						"REV");
_LIT8(KVersitTokenFN,						"FN");
_LIT8(KVersitTokenTEL,						"TEL");
_LIT8(KVersitTokenURL,						"URL");
_LIT8(KVersitTokenGEO,						"GEO");
_LIT8(KVersitTokenUID,						"UID");
_LIT8(KVersitTokenKEY,						"KEY");

_LIT(KVersitVarTokenINTERNET,				"INTERNET");		//Used by Jave Phone and not by versit

#endif
