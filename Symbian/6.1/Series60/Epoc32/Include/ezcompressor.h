// EZLib: COMPRESSOR.H
// Copyright (C) Symbian LTD 1999
//
// Declaration for Compression class
//

#ifndef __EZCOMPRESSOR_H__
#define __EZCOMPRESSOR_H__

#include <e32base.h>
#include <EZStream.h>
#include <EZBufman.h>

class CEZCompressor : public CEZZStream
	{
public:
	enum TStrategy
		{
		EDefaultStrategy = Z_DEFAULT_STRATEGY, 
		EFiltered = Z_FILTERED, 
		EHuffmanOnly = Z_HUFFMAN_ONLY
		};

	enum 
		{
		EDefaultCompression = Z_DEFAULT_COMPRESSION,
		ENoCompression = Z_NO_COMPRESSION,
		EBestSpeed = Z_BEST_SPEED,
		EBestCompression = Z_BEST_COMPRESSION
		};

	enum
		{
		EMaxWBits = MAX_WBITS
		};

	enum
		{
		EDefMemLevel = MAX_MEM_LEVEL
		};

	enum
		{
		EDeflateInitlialiserError = EUnexpected + 1,
		EDeflateTerminated
		};

	public:
		~CEZCompressor();

		IMPORT_C static CEZCompressor* NewLC(MEZBufferManager& aInit, TInt aLevel = EDefaultCompression,
			TInt aWindowBits = EMaxWBits, TInt aMemLevel = EDefMemLevel, TStrategy aStrategy = EDefaultStrategy);
		IMPORT_C static CEZCompressor* NewL(MEZBufferManager& aInit, TInt aLevel = EDefaultCompression,
			TInt aWindowBits = EMaxWBits, TInt aMemLevel = EDefMemLevel, TStrategy aStrategy = EDefaultStrategy);
		IMPORT_C static CEZCompressor* NewLC(MEZBufferManager& aInit, const TDesC8 &aDictionary, 
			TInt aLevel = EDefaultCompression, TInt aWindowBits = EMaxWBits, TInt aMemLevel = EDefMemLevel, 
			TStrategy aStrategy = EDefaultStrategy);
		IMPORT_C static CEZCompressor* NewL(MEZBufferManager& aInit, const TDesC8 &aDictionary,  
			TInt aLevel = EDefaultCompression, TInt aWindowBits = EMaxWBits, TInt aMemLevel = EDefMemLevel, 
			TStrategy aStrategy = EDefaultStrategy);

		IMPORT_C void ResetL(MEZBufferManager& aInit);

		IMPORT_C TBool DeflateL();

		IMPORT_C static void CompressL(TDes8 &aDestination, const TDesC8 &aSource, TInt aLevel = EDefaultCompression);

	private:
		enum TDeflationState
			{
			ENoFlush,
			EFinish,
			EFinalize,
			ETerminated
			};

	private:
		CEZCompressor(MEZBufferManager* aInit);
		void ConstructL(TInt aLevel, const TUint8* aDictionary, TInt aLength, TInt aWindowBits, TInt aMemLevel, TStrategy aStrategy);
		void ConstructL(TInt aLevel, TInt aWindowBits, TInt aMemLevel, TStrategy aStrategy);

	private:
		MEZBufferManager* iBufferInit;
		TDeflationState iDeflationState;
	};

#endif


