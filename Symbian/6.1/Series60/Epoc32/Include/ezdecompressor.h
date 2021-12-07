// EZLib: DECOMPRESSOR.H
// Copyright (C) Symbian LTD 1999
//
// Declaration for Decompression class
//

#ifndef __EZDECOMPRESSOR_H__
#define __EZDECOMPRESSOR_H__

#include <e32base.h>
#include <EZStream.h>
#include <EZBufman.h>

class CEZDecompressor : public CEZZStream
	{
public:
	
	enum 
		{
		EInflateInitlialiserError = EUnexpected + 1,
		EInflateVersionError,
		EInflateTerminated,
		EInflateDictionaryError
		};

	enum
		{
		EMaxWBits = MAX_WBITS
		};

public:
	~CEZDecompressor();

	IMPORT_C static CEZDecompressor* NewLC(MEZBufferManager& aInit, TInt aWindowBits = EMaxWBits);
	IMPORT_C static CEZDecompressor* NewL(MEZBufferManager& aInit, TInt aWindowBits = EMaxWBits);

	IMPORT_C static CEZDecompressor* NewLC(MEZBufferManager& aInit, const TDesC8& aDictionary, TInt aWindowBits = EMaxWBits);
	IMPORT_C static CEZDecompressor* NewL(MEZBufferManager& aInit, const TDesC8& aDictionary, TInt aWindowBits = EMaxWBits);


	IMPORT_C void ResetL(MEZBufferManager& aInit);
	IMPORT_C TBool InflateL();

	IMPORT_C static void DecompressL(TDes8 &aDestination, const TDesC8 &aSource);

	private:
		enum TInflationState
			{
			ENoFlush,
			EFinalize,
			ETerminated
			};

	private:
		void SetDictionaryL();
		CEZDecompressor(MEZBufferManager* aInit);
		CEZDecompressor(MEZBufferManager* aInit, const TUint8 *aDictionary, TInt aLength);
		void ConstructL(TInt aWindowBits);

	private:
		MEZBufferManager* iBufferInit;
		TInflationState iInflationState;
		const TUint8* iDictionary;
		TInt iDictionaryLength;
	};

#endif


