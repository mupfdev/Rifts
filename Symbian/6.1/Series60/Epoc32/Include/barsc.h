// BARSC.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __BARSC_H__
#define __BARSC_H__

#include <e32std.h>
#include <f32file.h>


struct SDictRec
	{
	TUint8 iVersion;
	TUint8 iDictEntryDiff;
	TInt16   iResourceIndex;
	TInt16	 iResourceSize;
	TUint8	 iDictionaryBits;
	};


class TResourceExtra
	{
public:
	TResourceExtra();
public:
	const TUint8* iRomAddress;
	SDictRec iDict;
	TInt iDictionaryData;
	TInt iResourceData;
	TInt iIndexPos;
	TInt iCount;
	TInt iFileIndex;
	};

class RResourceFile
	{
public:
	IMPORT_C RResourceFile();
    IMPORT_C void Close();
	IMPORT_C void OpenL(RFs &aFs,const TDesC &aName);
	IMPORT_C void ReadL(TDes8 &aDes,TInt aResourceId) const;
	IMPORT_C HBufC8 *AllocReadL(TInt aResourceId) const;
	IMPORT_C HBufC8 *AllocReadLC(TInt aResourceId) const;
    IMPORT_C void ConfirmSignatureL(TInt aSignature);
	IMPORT_C TInt SignatureL() const; // not available before Release 005
	IMPORT_C TBool OwnsResourceId(TInt aResourceId) const;
    inline TInt Offset() const { return(iOffset); }
	IMPORT_C TUidType UidType() const;
private:
	struct SIndexRec
		{
		TUint16 iPos;
		TUint16 iLen;
		};
	struct SSigRecord
		{
		TInt signature;
		TInt offset;
		};
private:
	void ReadL(TInt aPos,TDes8& aDes,TInt aLength) const;
	TInt PositionToResourceL(TInt aResourceId,TInt &aDecodedLen,TInt& aSeekPos) const;
	void ReadResourceDataL(TDes8 &aDes,TInt aReadLen,TInt aDecodedLen,TInt aSeekPos) const;
	void static Leave(TInt aClassSpecificError);
	SSigRecord FirstRecordL() const;
	void SeekToBitIndexL(TInt aIndex);
	TInt ReadBitsL(TInt aBits);
	TUint8* DecodeString(TInt aIndexOffset, TInt aDataOffset, TInt aIndex, TUint8* aAdr);
private:
	RFile iFile;
	TResourceExtra* iExtra;
	TInt iOffset;
	TInt iBitIndex;
	TUint iBitValue;
private:
	enum
		{
		EOffsetBits=0xfffff000,
		EIdBits=0x00000fff
		};
	};

#endif
