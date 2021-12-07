// GSMUBUF.H
//
// Copyright (c) 1999-2001 Symbian Ltd.  All rights reserved.
//
/**
 *
 * @file gsmubuf.h    This file contains the header file of the CSmsBuffers.
 *
 */

#if !defined (__GSMUBUF_H__)
#define __GSMUBUF_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__S32STRM_H__)
#include <s32strm.h>
#endif

#include "etools.h"


class CEditableText;
class RReadStream;
class RWriteStream;
class CGsmCompressionBase;
class TGsmCompressionSettings;


class CSmsBufferBase : public CBase
	{
public:
	enum
		{
		EMaxBufLength=0x100
		};
public:
	virtual TInt Length() const=0;
	virtual void Extract(TDes& aBuf,TInt aPos,TInt aLength) const=0;
	virtual void InsertL(TInt aPos,const TDesC& aBuf)=0;
	virtual void DeleteL(TInt aPos,TInt aLength)=0;
	virtual void Reset()=0;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	};

class CSmsBuffer : public CSmsBufferBase
	{
public:
	IMPORT_C static CSmsBuffer* NewL();
	IMPORT_C ~CSmsBuffer();
	IMPORT_C TInt Length() const;
	IMPORT_C void Extract(TDes& aBuf,TInt aPos,TInt aLength) const;
	IMPORT_C void InsertL(TInt aPos,const TDesC& aBuf);
	IMPORT_C void DeleteL(TInt aPos,TInt aLength);
	IMPORT_C void Reset();
private:
	CSmsBuffer();
private:
	CLASSNAMEDECL(CSmsBuffer);
	CArrayFix<TText>* iBuffer;
	};

//  Wrapper over CBufSeg produced from CGsmCompressionBase or from compressed CSmsMessage
class CSmsCompressedBuffer : public CSmsBufferBase
	{
public:
	static CSmsCompressedBuffer* NewL(CGsmCompressionBase& aGsmCompression,TInt aSegSize);
	~CSmsCompressedBuffer();
	TInt Length() const;
	void Extract(TDes& aBuf,TInt aPos,TInt aLength) const;
	void InsertL(TInt aPos,const TDesC& aBuf);
	void DeleteL(TInt aPos,TInt aLength);
	void Reset();
	void CompressL(const CSmsBufferBase& aUncompressedBuffer,const TGsmCompressionSettings& aCompressionSettings);
	void DecompressL(CSmsBufferBase& aUncompressedBuffer,TGsmCompressionSettings& aCompressionSettings);
private:
	CSmsCompressedBuffer(CGsmCompressionBase& aGsmCompression);
	void ConstructL(TInt aSegSize);
//	TInt TextHeaderLength() const;
//	void SetTextHeaderL(const TDesC& aTextHeader);
private:
	CLASSNAMEDECL(CSmsCompressedBuffer);
	CGsmCompressionBase& iGsmCompression;
	CBufSeg* iBuf;
	HBufC8* iCopyBuf;
	};

class CSmsEditorBuffer : public CSmsBufferBase
	{
public:
	IMPORT_C static CSmsEditorBuffer* NewL(CEditableText& aText);
	IMPORT_C ~CSmsEditorBuffer();
	IMPORT_C TInt Length() const;
	IMPORT_C void Extract(TDes& aBuf,TInt aPos,TInt aLength) const;
	IMPORT_C void InsertL(TInt aPos,const TDesC& aBuf);
	IMPORT_C void DeleteL(TInt aPos,TInt aLength);
	IMPORT_C void Reset();
private:
	CSmsEditorBuffer(CEditableText& aText);
private:
	CEditableText& iText;
	CLASSNAMEDECL(CSmsEditorBuffer);
	};


#endif // !defined __GSMUBUF_H__
