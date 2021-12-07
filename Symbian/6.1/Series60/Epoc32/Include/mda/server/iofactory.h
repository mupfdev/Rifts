// Mda\Server\IoFactory.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// *********** All classes Internal to Symbian *************//

#ifndef __MDA_SERVER_IOFACTORY_H__
#define __MDA_SERVER_IOFACTORY_H__

// Standard EPOC32 includes required by this header file
#include <E32Base.h>
// Public Media Server includes
#include <Mda\Server\Base.h>

enum 
	{
	EMdaIoFactoryNewIO=0
	};

class CMdaIO; // Forward reference
// Internal to Symbian
class CMdaIOFactory : public CMdaObject
	{
public:
	static inline void NewIO(CMdaMessage* aMessage, TUid aMediaType);
	//
	IMPORT_C virtual void OperationL(CMdaMessage* aMessage);
	IMPORT_C virtual void OperationCancel(CMdaMessage* aMessage);
	//
	static inline TUid GetNewIOMediaType(CMdaMessage* aMessage);
protected:
	IMPORT_C virtual void NewIOL(CMdaMessage* aMessage);
	IMPORT_C virtual void CancelNewIO(CMdaMessage* aMessage);
	};

inline void CMdaIOFactory::NewIO(CMdaMessage* aMessage, TUid aMediaType)
	{
	aMessage->iFunction = EMdaIoFactoryNewIO;
	aMessage->iArg[1] = aMediaType.iUid;
	}
inline TUid CMdaIOFactory::GetNewIOMediaType(CMdaMessage* aMessage)
	{
	return TUid::Uid(aMessage->iArg[1]);
	}

#endif
