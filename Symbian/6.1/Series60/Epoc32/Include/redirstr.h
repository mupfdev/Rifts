// redirstr.h
//
// Copyright (c) 1999-1999 Symbian Ltd.  All rights reserved.
//

//  Abstract stream classes for Stdio Redirection app
//
#ifndef _REDIRSTR_H_
#define _REDIRSTR_H_

#include <e32base.h>
#include <e32std.h>

const TInt KMaxStatusTextLength = 128;

// CStreamBase  abstract base class  for stream-like classes 

class CStreamBase : public CBase
	{
public:
	virtual void Write(TDes8& aDes) = 0;
	virtual void Read(const RMessage& aMessage) = 0;
protected:	
	TBuf8<256> iBuf; // buffer for holding stdin characters
	IMPORT_C void CompleteRead(const RMessage &aMessage);
	};

// CStreamFactoryBase  abstract Factory class  for creating stream-like classes 

class CStreamFactoryBase : public CBase
	{
public:
	virtual CStreamBase* GetStream() = 0;
	virtual void Configure() = 0;
	IMPORT_C virtual const TDesC& GetStatus() const;
protected:
	IMPORT_C void AppendToStatus(const TDesC& aMsg);
private:
	TBuf<KMaxStatusTextLength> iStatusMsg;
	};

#endif
