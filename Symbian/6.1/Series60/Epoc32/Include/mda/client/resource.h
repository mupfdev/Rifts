// Mda\Client\Resource.h 
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __MDA_CLIENT_RESOURCE_H__
#define __MDA_CLIENT_RESOURCE_H__

// Standard EPOC32 includes
#include <e32base.h>

// Public Media Server includes
#include <Mda\Common\Resource.h>
#include <Mda\Client\Base.h>
#include <Mda\Client\Port.h>

template <class T>
class RMdaResourcePort : public T
	{
public:
	MDA_OBJECT_FUNCTIONPACK(ResourceConfig,EMLbResourceHandleConfig,TMdaPackage)
protected:
	inline RMdaResourcePort(); // Cannot instantiate
	};

class RMdaSourceClipPort : public RMdaResourcePort<RMdaSrcPort>
	{
public:
	MDA_OBJECT_OPENREG(KUidMdaSourceClipValue)
	};

class RMdaDestinationClipPort : public RMdaResourcePort<RMdaDstPort>
	{
public:
	MDA_OBJECT_OPENREG(KUidMdaDestinationClipValue)
	};

class RMdaSourceStreamPort : public RMdaResourcePort<RMdaSrcPort>
	{
public:
	MDA_OBJECT_OPENREG(KUidMdaSourceStreamValue)
	};

class RMdaDestinationStreamPort : public RMdaResourcePort<RMdaDstPort>
	{
public:
	MDA_OBJECT_OPENREG(KUidMdaDestinationStreamValue)
	};

// Inline functions

template <class T> inline RMdaResourcePort<T>::RMdaResourcePort()
	{}

#endif
