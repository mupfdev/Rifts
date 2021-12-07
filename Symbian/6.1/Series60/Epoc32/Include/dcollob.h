// 
// DCollOb.h
// Copyright (C) 1997-1998 Symbian Ltd. All rights reserved.
//

// 
// Created at: 22-Dec-98 10:54:39 AM
// Comments: Define the abstract base class for all objects which
//			wish to provide status handling services for the CDataCollector
//			class.
// 


#if !defined(__DCOLLOB_H__)
#define __DCOLLOB_H__

class CDataCollector;
class CNode;

class MDataCollectorObserver
// MDataCollectorObserver provides a virtual interface for any class to observe
// CDataCollector, and provide a status recieving service. 
// 
	{
// Methods
public:
	// A status reciever for CDataCollector status messages
	virtual void OnChildStatus(const CDataCollector& aChild, CNode& aNode, TInt aStatus) = 0;

private:
	// Reserved for future expansion
	IMPORT_C virtual void MDataCollectorObserverReserved1();
	IMPORT_C virtual void MDataCollectorObserverReserved1() const;
	};  // MDataCollectorObserver

#endif    // __DCOLLOB_H__
