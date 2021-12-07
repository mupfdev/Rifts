// GSMUSAR.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

//
// Declares segmentation and reassembly utility classes GSMU dll
// These are exported for use by WAPPROT
//

#if !defined(__GSMUSAR_H__)
#define __GSMUSAR_H__

#include <charconv.h>
#include "gsmubuf.h"
#include "gsmuelem.h"

//
// CSmsBufferSegmenter - segments (unpacked) data from CSmsBufferBase
//

class CSmsBufferSegmenter : public CBase
	{
public:
// Construction / destruction methods
	IMPORT_C static CSmsBufferSegmenter* NewLC(CSmsAlphabetConverter& aAlphabetConverter,const CSmsBufferBase& aBuffer,TInt aSegmentSize=0);
	IMPORT_C ~CSmsBufferSegmenter();

// Segmentation methods
	void Reset();
	IMPORT_C TBool SegmentNextL(TDes8& aSegmentBuffer);
	IMPORT_C TInt TotalConvertedLengthL();

// Constants
	enum
		{
		ESms7BitAlphabetEscapeChar=0x1b
		};

protected:
// Protected construction methods
	CSmsBufferSegmenter(CSmsAlphabetConverter& aAlphabetConverter,const CSmsBufferBase& aBuffer,TInt aSegmentSize);
	void ConstructL();

// Protected helper methods
	TBool DoSegmentNextL(TDes8& aSegmentBuffer,TInt aSegmentSize);
	void CheckConvertedBufferAllocL(TInt aMaxLength);
	TInt ElementsToReturnFromConvertedBufferL(TInt aSegmentSize);

private:
// Private data
	CSmsAlphabetConverter& iAlphabetConverter;
	const CSmsBufferBase& iSmsBuffer;
	TInt iElementsExtracted;
	TInt iSegmentSize;
	HBufC8* iConvertedBuffer;
	TPtr8 iConvertedBufferPtr;
	};

//
// TSmsBufferReassembler - reassembles (unpacked) data to CSmsBufferBase
//

class TSmsBufferReassembler
	{
public:
// Construction / destruction methods
	IMPORT_C TSmsBufferReassembler(CSmsAlphabetConverter& aAlphabetConverter,CSmsBufferBase& aBuffer);

// Reassembly methods
	IMPORT_C void ReassembleNextL(const TDesC8& aSegmentBuffer,TBool aIsLast);

private:
	CSmsAlphabetConverter& iAlphabetConverter;
	CSmsBufferBase& iSmsBuffer;
	};

#endif
