// VUID.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//
 
#ifndef __VUID_H__
#define __VUID_H__

#define KVersitDefaultBufferSize 32
#define KVersitMaxDateTimeLength 16
#define KVersitMaxVersionLength 16
_LIT8(KVersitQuestionMark, "?");

//
// Uid's
// 268440459-268440508 have been allocated to Versit initially
//

#define KVersitTokenBeginUid							268440459
#define KVersitTokenEndUid								268440460
#define KVersitTokenUnknownUid							268440461
#define KVersitTokenVersionUid							270490587

#define KVCardPropertyAgentUid							268440471
#define KVCalPropertyAlarmUid							268440472
#define KVCalEntityUidVEvent							268440473
#define KVCalEntityUidVTodo								268440474
#define KVersitGroupedPropertyUid						268440475
#define KVersitPropertyTimeZoneUid						268440476
#define KVersitPropertyDateUid							268440477
#define KVersitTimePropertyUid							268440478

#define KVersitEntityUidVCard							268440483		//Used by cntmodel and not by versit
#define KVCalPropertyRecurrenceUid						268440484
#define KVersitPropertyDaylightUid						268440485
#define KVersitParamCharsetUid							268440488


/**
 * Various ConArc uids
 */
#define KQuotedPrintableToTextConverter					268441637
#define KTextToQuotedPrintableConverter					268441638
#define KBase64ToTextConverter							268440005
#define KTextToBase64Converter							268437281 


/**
 * Encoding uids used to uniquely identify an encoding property parameter
 */
#define KVersitParamEncodingUid							268440463
#define KVersitParamEncodingQuotedPrintableUid			268440464
#define KVersitParamEncodingBase64Uid					268440465


/**
 * Theser are versit data-type uids for property values. They
 * are versit-internal.
 */
#define KVersitPropertyHBufCUid							268440466
#define KVersitPropertyBinaryUid						268470833
#define KVersitPropertyCDesCArrayUid					268440467
#define KVersitPropertyMultiDateTimeUid					268440468
#define KVersitPropertyDateTimeUid						268440469
#define KVersitPropertyIntUid							268440470


/**
 * The following is list of UID's that were used by versit but are not now
 */
//UID's for tokens
//268440462
//UID's used for character sets
//268440489, 268440499-506, 268457255-6, 268457654-8, 268478097
//UID's used for Quoted Printable with a character set
//268440486, 268440490-8, 268457253-4, 268457801-5
//UID's used for Base64 with a character set
//268440479-82, 268440487, 268440508, 268456960, 268457257-62, 268470904-6, 268479493

#endif
