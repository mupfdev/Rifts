//  BITSIDS.H
//
//  Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//
//  Started by AHF at Teleca Ltd.
//
//  Common header file which lists enumerated type for use in 
//	other files of the BITS projects

#if !defined(_BITSID_H_)
#define _BITSID_H_


//  BIO messaging Uids
const TInt32	KUidBIOInternetAccessPointMsg= {0x1000552F};	// IAP Settings
const TInt32	KUidBIOEmailNotificationMsg	=  {0x10005530};	// Correct???
const TInt32	KUidBIOBusinessCardMsg		=  {0x10005531};	// Compact Business Cards
const TInt32	KUidBIOWAPAccessPointMsg	=  {0x10005532};	// WAP Access Point Settings
const TInt32	KUidBIOVCalenderMsg			=  {0x10005533};    // VCalender diary
const TInt32	KUidBIOVCardMsg				=  {0x10005534};    // VCard contact entries
const TInt32	KUidBIORingingTonesMsg		=  {0x10005535};    // Telephone Ringing Tones
const TInt32	KUidBIOOperatorLogoMsg		=  {0x10005536};	// Operator Logo
const TInt32	KUidBIOWPRVMsg				=  {0x1000125D};	// WAP Provisioning

const TInt32    KUidBIOCLILogoMsg			=  {0x10005269};    // To be done!

//  Type of message that we're dealing with
typedef enum
	{							//	GENERATE A MESSAGE USING....
    ENoMessage,                 //  .. error cases
    EBioIapSettingsMessage,     //  .. IAP grammar, includes Internet settings 
								//		Email settings, and logon scripts, 
	EBioEnpMessage,				//	.. Email Notification grammar.
	EBioRingTonesMessage,		//	.. Ringing Tones binary data
	EBioOpLogoMessage,			//	.. Logo for Operator service
	EBioCompBusCardMessage,		//	.. Compact Business Card data
	EBiovCardMessage,			//	.. virtual business card data
	EBiovCalenderMessage,		//	.. vCalender data
	EBioWAPSettingsMessage,		//  .. wap settings
	EBioWPRVSettingsMessage		//	.. wprv settings
	} TBIOMessageType;


#endif //_BITSID_H_
