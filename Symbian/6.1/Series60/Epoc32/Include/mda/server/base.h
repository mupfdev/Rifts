// Mda\Server\Base.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// *********** All classes Internal to Symbian *************//

#ifndef __MDA_SERVER_BASE_H__
#define __MDA_SERVER_BASE_H__

/*
Notes:
Base classes used throughout Media Server framework

  CMdaObject->CObject
This is the base of all objects that can be created by Media Server libraries. 
Includes support for message passing through OperationL/OperationCancel

  CMdaMessage->CBase
Used for communication between objects with framework. Supports data passing and return
and asynchronous completion

  MMdaMessage
Mixin for objects sending messages. Used for negotiation and signalling of completion

  CMdaLibrary
Base class of all libraries e.g. the registry. 
Supplies interface for opening (creating) objects.

*/

// Standard EPOC32 includes required by this header file
#include <E32Base.h>

// Public Media Server includes
#include <Mda\Common\Base.h>

class CMdaObject; // Forward definition

// Internal to Symbian
class MMdaMessage
	{
public:
	virtual void MessageDoComplete(TInt aVal)=0;
	IMPORT_C virtual void MessageDoPanic(const TDesC& aCategory, TInt aReason);
	IMPORT_C virtual CMdaObject* MessageDoGetObjectL(TInt aArg);
	IMPORT_C virtual void MessageDoReadDesL(TInt aArg, TDes8& aDes);
	IMPORT_C virtual void MessageDoWriteDesL(TInt aArg, const TDesC8& aDes);
	IMPORT_C virtual void MessageDoReturnObjectL(TInt aArg, CMdaObject* aObject);
	};

// Internal to Symbian
class CMdaMessage : public CBase
	{
public:
	IMPORT_C CMdaMessage();
	IMPORT_C CMdaMessage(TInt aPriority);
	IMPORT_C CMdaMessage(MMdaMessage* aMessage);
	IMPORT_C CMdaMessage(TInt aPriority, MMdaMessage* aMessage);
	IMPORT_C ~CMdaMessage();
	//
	inline void PostL(CMdaObject* aTarget);
	virtual void Cancel()=0;
	IMPORT_C virtual void Complete(TInt aVal);
	inline void Panic(const TDesC& aCategory, TInt aReason);
	//
	inline CMdaObject* GetObjectL(TInt aArg);
	inline void ReadDesL(TInt aArg, TDes8& aDes);
	inline void WriteDesL(TInt aArg, const TDesC8& aDes);
	inline void ReturnObjectL(TInt aArg, CMdaObject* aObject);
	//
	inline TBool IsPackage();
	inline TInt PackageLength();
	IMPORT_C void GetPackageL(TMdaRawPackage& aPackage);
	IMPORT_C TMdaRawPackage* GetPackageAllocL();
	IMPORT_C TMdaRawPackage* GetPackageAllocLC();
	IMPORT_C void ReturnPackageL(const TMdaRawPackage& aPackage);
	//
	inline void SetPriority(TInt aPriority);
	//
	inline TBool IsCanceling();
protected: 
	static inline MMdaMessage* Message(CMdaMessage* aMessage);
	//
	inline void DoOperationL(CMdaObject* aObject);
	inline void DoCancel(CMdaObject* aObject);
	virtual void DoPostL(CMdaObject* aTarget) = 0;
public:
	TPriQueLink iLink; 
public:
	TInt16 iFlags;
	TInt16 iFunction;
	TInt iArg[4];
protected:
	MMdaMessage* iMessage;
	};

// Internal to Symbian
class MMdaEventListener
	{
public:
	virtual void Event(const TMdaEvent& aEvent)=0;
public:
	TSglQueLink iListenerLink;
	};

// Internal to Symbian
class CMdaObject : public CObject
	{
public:
	// from CBase
	IMPORT_C virtual ~CMdaObject();
	// Event Listeners
	IMPORT_C virtual void AddEventListenerL(MMdaEventListener& aListener);
	IMPORT_C virtual void RemoveEventListener(MMdaEventListener& aListener);
protected:
	IMPORT_C CMdaObject();
	// Message passing
	IMPORT_C virtual void OperationL(CMdaMessage* aMessage);
	IMPORT_C virtual void OperationCancel(CMdaMessage* aMessage);
	// Utility functions
	static inline CMdaObject* Cast(CObject* aObject);
	//
	IMPORT_C void ReturnCreatedObjectArgL(CMdaObject* aObject, CMdaMessage* aMessage, TInt aArg);
	inline void ReturnCreatedObjectL(CMdaObject* aObject, CMdaMessage* aMessage); // aArg[1]
	//
	friend CMdaMessage;
	};

// Internal to Symbian
class CMdaLibrary: public CMdaObject
	{
public:		// Interface for callers
	inline static void OpenObject(CMdaMessage* aMessage, TUid aObjectUid);
protected:	// Interface for derived classes
	IMPORT_C virtual void OperationL(CMdaMessage* aMessage);
	IMPORT_C virtual void OperationCancel(CMdaMessage* aMessage);
	virtual void OpenObjectL(CMdaMessage* aRequest)=0;
	IMPORT_C virtual void CancelOpenObject(CMdaMessage* aRequest);
	inline TUid GetOpenObjectUid(CMdaMessage* aMessage);
	IMPORT_C CMdaLibrary();
	};

#include <Mda\Server\Base.inl>

#endif
