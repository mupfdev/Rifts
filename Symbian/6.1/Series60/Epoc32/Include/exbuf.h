// EXBUF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EXBUF_H__)
#define __EXBUF_H__


class CExportBufferBase : public CBase
	{
	// The purpose of this class is to provide a method of
	// abstracting the destination of an output through a buffer
	// The class is intended to be used for a single output then destroyed
public:
	IMPORT_C CExportBufferBase(TInt aMaxSize);
	IMPORT_C ~CExportBufferBase();
	IMPORT_C void ConstructL();
	virtual void CommitExportBufferL()=0;
	IMPORT_C void ResetExportBuffer();
	IMPORT_C void ResetWritePtr();
	IMPORT_C void FinalizeExport();
	IMPORT_C void InsertL(TText aText); // !! TText should be TText8 - do I need an overload here for Unicode?
protected:
	TInt iExportBufferLength; 
	HBufC* iExportBuffer;
private:
	TText* iWritePtr;
	TText* iTBase;
	TInt iMaxSize;
	};


class CExportDynamicBuffer : public CExportBufferBase
	{
public:
	IMPORT_C static CExportDynamicBuffer* NewL(TInt aSize, CBufBase& aDynamicBuffer);
	IMPORT_C void ConstructL();
public:  // from CExportBufferBase
	IMPORT_C void CommitExportBufferL();
private:
	CExportDynamicBuffer(TInt aSize, CBufBase& aDynamicBuffer);
private:
	CBufBase& iOutput;
	};

#endif // __EXBUF_H__
