// GSMUMSG.H
//
// Copyright (c) 1999-2001 Symbian Ltd.  All rights reserved.
// 

/**
 *
 * @file gsmumsg.h  This file defines the class CSmsMessage
 *
 */

#if !defined (__GSMUMSG_H__)
#define __GSMUMSG_H__


#if !defined (__F32FILE_H__)
#include <f32file.h>
#endif

#if !defined (__ETELBGSM_H__)
#include <etelbgsm.h>
#endif

#if !defined (__CHARCONV_H__)
#include <charconv.h>
#endif

#if !defined (__GSMUPDU_H__)
#include "gsmupdu.h"
#endif

#if !defined (__GSMUCOMP_H__)
#include "gsmucomp.h"
#endif

class CSmsBufferBase;
class CSmsCompressedBuffer;
class TSmsUserDataSettings;
class CGsmCompressionBase;

class CSmsMessage : public CBase
	{
public:
	enum TSmsOptimizationFlags
		{
		ESmsFlagOptimizeAlphabet=0x01,
		ESmsFlagOptimizeCompressionSettings=0x02,
		ESmsFlagOptimizeCompression=0x04,
		ESmsFlagOptimizeConcatenation=0x08,
		ESmsFlagOptimizeConcatenation16BitReference=0x10,
		};
	enum TSmsStorage
		{
		ESmsNoStorage=0x00,
		ESmsSIMStorage=0x04,
		ESmsPhoneStorage=0x08,
		ESmsModemStorage=0x0C
		};
public:
	IMPORT_C static CSmsMessage* NewL(const TSms& aSms,CSmsBufferBase* aBuffer,TBool aServiceCenterAddressPresent=EFalse,TBool aIsRPError=EFalse,TBool aIsMobileTerminated=ETrue);
	IMPORT_C static CSmsMessage* NewL(CSmsPDU::TSmsPDUType aType,CSmsBufferBase* aBuffer,TBool aIsRPError=EFalse);
	IMPORT_C ~CSmsMessage();

	inline CSmsPDU::TSmsPDUType Type() const;
	inline TBool IsComplete() const;
	inline TBool IsDecoded() const;
	inline TSmsStorage Storage() const;
	inline void SetStorage(TSmsStorage aStorage);
	inline RSmsStorage::TStatus Status() const;
	inline void SetStatus(RSmsStorage::TStatus aStatus);
	inline TInt LogServerId() const;
	inline void SetLogServerId(TInt aId);
	inline const TTime& Time() const;
	inline void SetTime(const TTime& aTime);

	inline CSmsPDU& SmsPDU(); 
	inline const CSmsPDU& SmsPDU() const; 

	inline TPtrC ServiceCenterAddress() const;
	inline void SetServiceCenterAddressL(const TDesC& aAddress);
	inline void ParsedServiceCenterAddress(TGsmTelNumber& aParsedAddress) const;
	inline void SetParsedServiceCenterAddressL(const TGsmTelNumber& aParsedAddress);

	inline TPtrC ToFromAddress() const;
	inline void SetToFromAddressL(const TDesC& aAddress);
	inline void ParsedToFromAddress(TGsmTelNumber& aParsedAddress) const;
	inline void SetParsedToFromAddressL(const TGsmTelNumber& aParsedAddress);

	IMPORT_C void InternalizeWithoutBufferL(RReadStream& aStream);
	IMPORT_C void ExternalizeWithoutBufferL(RWriteStream& aStream) const;

	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;

	inline CSmsBufferBase& Buffer();
	inline const CSmsBufferBase& Buffer() const;

//  Functions related to encoding/decoding the text buffer
	IMPORT_C TBool TextPresent() const;
	IMPORT_C TInt NumMessagePDUsL();
	IMPORT_C TInt MaxMessageLength() const;
	IMPORT_C TInt MessageLengthL();

	IMPORT_C void UserDataSettings(TSmsUserDataSettings& aSettings) const;
	IMPORT_C void SetUserDataSettingsL(const TSmsUserDataSettings& aSettings);
	IMPORT_C void CompressionSettings(TGsmCompressionSettings& aCompressionSettings) const;
	IMPORT_C void SetCompressionSettings(const TGsmCompressionSettings& aCompressionSettings);
	IMPORT_C void OptimizeSettingsL(TInt aOptions);

	IMPORT_C static TBool CompressionSupportedL(RFs& aFs);
	IMPORT_C TBool IsSupportedL(const TDesC& aDes,TInt& aNumberOfUnconvertibleCharacters, TInt& aIndexOfFirstUnconvertibleCharacter);

	IMPORT_C void EncodeMessagePDUsL(CArrayFix<TSms>& aSmsArray,TBool aServiceCenterAddressPresent=ETrue,TInt aReference=0);
	IMPORT_C void DecodeMessagePDUsL(const CArrayFix<TSms>& aSmsArray,TBool aServiceCenterAddressPresent=ETrue);

private:
	CSmsMessage(CSmsBufferBase* aBuffer);
	void ConstructL(const TSms& aSms,TBool aServiceCenterAddressPresent,TBool aIsRPError,TBool aIsMobileTerminated);
	void ConstructL(CSmsPDU::TSmsPDUType aType,TBool aIsRPError);

	inline void SetIsComplete(TBool aIsComplete);
	inline void SetIsDecoded(TBool aIsDecoded);

	void ConstructConverterL();
	void CreateGsmCompressionL();
	void DoCreateGsmCompressionL();
	static TInt FindGsmCompressionDll(RFs& aFs,TDes& aFullName);
	CSmsCompressedBuffer* NewCompressedBufferL();

	inline TBool BinaryData() const;
	TInt ConvertedBufferLengthL(const CSmsBufferBase& aBuffer);	
	void EncodeBufferL(CArrayFix<TSms>& aSmsArray,TBool aServiceCenterAddressPresent,TInt aReference,const CSmsBufferBase& aBuffer);
	void DecodeBufferL(CArrayPtr<CSmsPDU>& aSmsPDUArray,CSmsBufferBase& aBuffer);

private:
	enum TSmsMessageFlags
		{
		ESmsFlagIsComplete=0x01,
		ESmsFlagIsDecoded=0x02,

		ESmsStorageMask=0x0C,
		};

private:
	CLASSNAMEDECL(CSmsMessage);
	TInt iFlags;
	RSmsStorage::TStatus iStatus;
	TInt iLogServerId;
	TTime iTime;

	CSmsPDU* iSmsPDU;
	TGsmCompressionSettings iCompressionSettings;

	CSmsBufferBase* iBuffer;

	RFs iFs;
	RLibrary iGsmLibrary;
	CGsmCompressionBase* iGsmCompression;
	CCnvCharacterSetConverter* iCharacterSetConverter;
	};

#include "gsmumsg.inl"

#endif // !defined __GSMUMSG_H__

