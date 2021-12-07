/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __BTDISCOVERY_PAN__
#define __BTDISCOVERY_PAN__

/** BTDiscovery application panic codes */
enum TBTDiscoveryPanics 
    {
    EBTDiscoveryBasicUi = 1,
	EBTDiscoveryUnrecognisedMenuCommand,
	EBTDiscoveryAttributeRequest,
	EBTDiscoveryAttributeAcceptVisitor,
	EBTDiscoveryNextRecordRequest,
	EBTDiscoveryInvalidComponentIndex,
	EBTDiscoveryViewPrintNewLine,
	EBTDiscoveryView
	};

inline void Panic(TBTDiscoveryPanics aReason)
	{ 
	User::Panic(_L("BTDiscovery"), aReason);
	}

#endif // __BTDISCOVERY_PAN__
