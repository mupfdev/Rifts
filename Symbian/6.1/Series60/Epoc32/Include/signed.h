// SIGNED.H
//
// Copyright (c) 1998-2000 Symbian Ltd.  All rights reserved.
//

#if !defined (__SIGNED_H__)
#define __SIGNED_H__

#include <e32base.h>
#include <e32std.h>
#include <s32std.h>

class CRSAPublicKey;
class CDSAPublicKey;
class CDSASignature;
class CDSAParameters;

enum TAlgorithmId
	{
	ERSA,
	EDSA,
	EDH,
	EMD2,
	EMD5,
	ESHA1
	};

class CValidityPeriod : public CBase
	{
public:
	IMPORT_C TBool Valid(const TTime& aTime) const;
	IMPORT_C const TTime& Start() const;
	IMPORT_C const TTime& Finish() const;
	IMPORT_C CValidityPeriod(const CValidityPeriod& aValidityPeriod);
protected:
	IMPORT_C CValidityPeriod();
	TTime iStart;
	TTime iFinish;
	};

class CAlgorithmIdentifier : public CBase
	{
public:
	IMPORT_C static CAlgorithmIdentifier* NewL(const CAlgorithmIdentifier& aAlgorithmIdentifier);
	IMPORT_C static CAlgorithmIdentifier* NewLC(const CAlgorithmIdentifier& aAlgorithmIdentifier);
	IMPORT_C static CAlgorithmIdentifier* NewL(TAlgorithmId& aAlgorithmId, const TDesC8& aEncodedParams);
	IMPORT_C static CAlgorithmIdentifier* NewLC(TAlgorithmId& aAlgorithmId, const TDesC8& aEncodedParams);
	IMPORT_C TBool operator == (const CAlgorithmIdentifier& aAlgorithmIdentifier) const;
	IMPORT_C TAlgorithmId Algorithm() const;	//ID for the algorithm
	IMPORT_C TPtrC8 EncodedParams() const;				//the encoded parameters
	IMPORT_C ~CAlgorithmIdentifier();
protected:
	IMPORT_C CAlgorithmIdentifier();
	IMPORT_C CAlgorithmIdentifier(TAlgorithmId& aAlgorithmId);
	IMPORT_C virtual void ConstructL(const CAlgorithmIdentifier& aAlgorithmIdentifier);
	IMPORT_C virtual void ConstructL(const TDesC8& aEncodedParams);
	TAlgorithmId iAlgorithmId;
	HBufC8* iEncodedParams;
	};

class CSigningAlgorithmIdentifier : public CBase
	{
public:
	IMPORT_C static CSigningAlgorithmIdentifier* NewL(const CSigningAlgorithmIdentifier& aSigningAlgorithmIdentifier);
	IMPORT_C static CSigningAlgorithmIdentifier* NewLC(const CSigningAlgorithmIdentifier& aSigningAlgorithmIdentifier);
	IMPORT_C TBool operator == (const CSigningAlgorithmIdentifier& aSigningAlgorithmIdentifier) const;
	IMPORT_C const CAlgorithmIdentifier& AsymmetricAlgorithm() const;
	IMPORT_C const CAlgorithmIdentifier& DigestAlgorithm() const;
	IMPORT_C ~CSigningAlgorithmIdentifier();
protected:
	void ConstructL(const CSigningAlgorithmIdentifier& aSigningAlgorithmIdentifier);
	CAlgorithmIdentifier* iAsymmetricAlgorithm;
	CAlgorithmIdentifier* iDigestAlgorithm;
	};

//algorithm ID + encoded public key + encoded parameters
class CSubjectPublicKeyInfo : public CBase
	{
public:
	IMPORT_C static CSubjectPublicKeyInfo* NewL(const CSubjectPublicKeyInfo& aSubjectPublicKeyInfo);
	IMPORT_C static CSubjectPublicKeyInfo* NewLC(const CSubjectPublicKeyInfo& aSubjectPublicKeyInfo);
	IMPORT_C TAlgorithmId AlgorithmId() const;
	IMPORT_C const TPtrC8 EncodedParams() const;
	IMPORT_C const TPtrC8 KeyData() const;
	IMPORT_C ~CSubjectPublicKeyInfo();
protected:
	IMPORT_C virtual void ConstructL(const CSubjectPublicKeyInfo& aSubjectPublicKeyInfo);
	CAlgorithmIdentifier* iAlgId;
	HBufC8* iEncodedKeyData;
	};

class CRSASignatureResult : public CBase
	{
public:
	IMPORT_C virtual TBool VerifyL(const TDesC8& aResult) = 0;
	IMPORT_C ~CRSASignatureResult();
protected:
	IMPORT_C TBool operator == (const CRSASignatureResult& aResult) const;
	CAlgorithmIdentifier* iDigestAlgorithm;
	HBufC8* iDigest;
	};

//signed object
class TKeyFactory
	{
public:
	virtual CRSAPublicKey* RSAPublicKeyL(const TDesC8& aEncoding) const = 0;
	virtual CRSASignatureResult* RSASignatureResultL(const CAlgorithmIdentifier& aDigestAlgorithm, TDesC8& aDigest) const = 0;
	virtual CDSAPublicKey* DSAPublicKeyL(const CDSAParameters& aParams, const TDesC8& aEncoding) const = 0;
	virtual CDSASignature* DSASignatureL(const TDesC8& aEncoding) const = 0;
	virtual CDSAParameters* DSAParametersL(const TDesC8& aEncoding) const = 0;
	};

class CSigningKeyParameters : public CBase
	{
public:
	IMPORT_C static CSigningKeyParameters* NewL();
	IMPORT_C static CSigningKeyParameters* NewLC();
	IMPORT_C static CSigningKeyParameters* NewL(const CSigningKeyParameters& aParameters);
	IMPORT_C static CSigningKeyParameters* NewLC(const CSigningKeyParameters& aParameters);
	IMPORT_C ~CSigningKeyParameters();
	IMPORT_C void SetDSAParamsL(const CDSAParameters& aParams);
	const CDSAParameters* DSAParams() const;
private:
	CSigningKeyParameters();
	void ConstructL(const CSigningKeyParameters& aParameters);
	CDSAParameters* iDSAParams;
	};

class CSignedObject : public CBase
	{
public:	
	IMPORT_C TBool VerifySignatureL(const TDesC8& aEncodedKey) const;
	IMPORT_C const TPtrC8 Signature() const;
	IMPORT_C virtual const TPtrC8 SignedDataL() const = 0;
	IMPORT_C const TPtrC8 Fingerprint() const;
	IMPORT_C const TPtrC8 Encoding() const;
	IMPORT_C const CSigningAlgorithmIdentifier& SigningAlgorithm() const;
	IMPORT_C virtual void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C virtual void InternalizeL(RReadStream& aStream) = 0;
	IMPORT_C void SetParametersL(const CSigningKeyParameters& aParameters);
	IMPORT_C virtual const TPtrC8* DataElementEncoding(const TUint aIndex) const = 0;
	IMPORT_C ~CSignedObject();
protected:
	TBool VerifyRSASignatureL(const TDesC8& aEncodedKey) const;
	TKeyFactory* iKeyFactory;
	HBufC8* iEncoding;
	HBufC8* iSignature;
	HBufC8* iFingerprint;
	CSigningKeyParameters* iParameters;
	CSigningAlgorithmIdentifier* iSigningAlgorithm;
	};

class CCertificate : public CSignedObject
	{
public:
	IMPORT_C ~CCertificate();
	IMPORT_C const CSubjectPublicKeyInfo& PublicKey() const;
	IMPORT_C const TPtrC8 SerialNumber() const;
	IMPORT_C const CValidityPeriod& ValidityPeriod() const;
	IMPORT_C virtual TBool IsSelfSignedL() const = 0;
	IMPORT_C virtual HBufC* SubjectL() const = 0;
	IMPORT_C virtual HBufC* IssuerL() const = 0;
protected:
	HBufC8* iSerialNumber;
	CValidityPeriod* iValidityPeriod;
	CSubjectPublicKeyInfo* iSubjectPublicKeyInfo;
	};

#endif
