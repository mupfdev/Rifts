// ETBSCBUF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__ET_BSCBUF_H__)
#define __ET_BSCBUF_H__

//
//	Number of server-side slots for each notification (greater than 1)
//

//
//	RBasicGsmCall
//
const TUint KSlotNumbersGsmCallCapsChange	= 2;

//
//	RBasicGsmPhone
//
const TUint KSlotNumbersPhoneCurrentNetworkChange				= 2;
const TUint KSlotNumbersPhoneNetworkRegistrationStatusChange	= 3;
const TUint KSlotNumbersPhoneIndicatorChange					= 3;

//
//	RGsmPhoneBook
//
const TUint KSlotNumbersPhoneBookEntryChange =5;

//
//	RSmsStorage
//
const TUint KSlotNumbersSmsStorageWrite		= 5;

//
//	RSmsMessaging
//
const TUint KSlotNumbersSmsMessageArrived	= 5;
const TUint KSlotNumbersSmsMessagingRead	= 5;


#endif	  
