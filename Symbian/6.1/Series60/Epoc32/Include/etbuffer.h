// ETBUFFER.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__ET_BUFFER_H__)
#define __ET_BUFFER_H__

//
//	Number of server-side slots for each notification (greater than 1)
//

const TUint KSlotNumbersDefault				= 1;
//
//	RCall
//
const TUint KSlotNumbersCallCapsChange		= 2;
const TUint KSlotNumbersCallStatusChange	= 4;


//
//	RLine
//
const TUint KSlotNumbersLineStatusChange	= 4;
const TUint KSlotNumbersLineCallAddedChange = 4;



#endif