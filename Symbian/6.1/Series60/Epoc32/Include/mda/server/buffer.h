// Mda\Server\Buffer.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// *********** All classes Internal to Symbian *************//

#ifndef __MDA_SERVER_BUFFER_H__
#define __MDA_SERVER_BUFFER_H__

#include <Mda\Server\Base.h>
#include <Mda\Server\Io.h>
#include <Mda\Server\IoFactory.h>
#include <Mda\Server\Machine.h>

// Internal to Symbian
enum TMdaDatatypePanic
	{
	EIOCountNotZero=0
	};

// Buffers

// Flags

const TUint32 KMdaBufferDataEnd				=0x00000001;
const TUint32 KMdaBufferRepeatLastValue		=0x00000100;
const TUint32 KMdaBufferErrorOnUnderFlow	=0x00010000;	
const TUint32 KMdaBufferErrorOnOverFlow		=0x00020000;	

// Internal to Symbian
class CMdaBuffer : public CBase
	{
public:
	inline TInt32 Flags() const;
	inline void SetFlag(TInt32 aFlag);
	inline void ClearFlag(TInt32 aFlag);
	// For derived classes to supply
	IMPORT_C virtual void Release();
	virtual TUid MediaType() const=0; // Must supply
protected:
	TUint32	iFlags;
	};

// Internal to Symbian
class CMdaTimedBuffer : public CMdaBuffer
	{
public:
	inline const TTimeIntervalMicroSeconds& Duration();
	inline const TTimeIntervalMicroSeconds& Position();
protected:
	TTimeIntervalMicroSeconds iDuration;
	TTimeIntervalMicroSeconds iPosition;	// ..in this data stream
	};

// Datatype

// Internal to Symbian
class CMdaDatatype : public CMdaObject
	{
public:
	inline void IOClosed();
	inline CMdaDatatype();
	IMPORT_C virtual ~CMdaDatatype();
	//
	IMPORT_C CMdaIO& CreateIOL(CMdaPort& aPort);
protected:
	virtual CMdaIO& DoCreateIOL(CMdaPort& aPort)=0;
	inline TInt IOCount();
protected: 
	// IO management
   	TDblQue<CMdaIO> iIOList;
	TInt iIOCount;
	};

// Inlines

inline TInt32 CMdaBuffer::Flags() const
	{ return iFlags; }
inline void CMdaBuffer::SetFlag(TInt32 aFlag)
	{ iFlags |= aFlag; }
inline void CMdaBuffer::ClearFlag(TInt32 aFlag)
	{ iFlags &= !aFlag; }

inline CMdaDatatype::CMdaDatatype() :
iIOList(_FOFF(CMdaIO,iDatatypeLink)) {}

inline void CMdaDatatype::IOClosed()
	{ iIOCount--; ASSERT(iIOCount>=0); }
inline TInt CMdaDatatype::IOCount()
	{ return iIOCount; }

#endif
