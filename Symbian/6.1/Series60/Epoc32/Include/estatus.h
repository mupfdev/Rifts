// 
// EStatus.h
// Copyright (C) 1997-1999 Symbian Ltd. All rights reserved.
//

// 
// Created at: 04-Jan-99 10:35:54 AM
// Comments: Status enumeration for Data Collectors, Data Providers and Data Handlers.
// 


#if !defined(__ESTATUS_H__)
#define __ESTATUS_H__

#ifndef __E32DEF_H__
#include <e32def.h> // for TInt
#endif

// 
// values < 0 are error codes
//			0 - 100 are % processed
//		  > 100 are the enum values below...
//
enum TPluginStatus {	
					EPluginComplete=100,
					EPluginInitialised,
					EPluginWaitingForChild,
					EPluginProcessing,
					EPluginSuspend,
					EPluginCancelled,
					EConnectionChanged
				   };

#endif    // __ESTATUS_H__
