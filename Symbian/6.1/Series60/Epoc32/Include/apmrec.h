// APMREC.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__APMREC_H__)
#define __APMREC_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__APMSTD_H__)
#include <apmstd.h>
#endif

// classes defined
class CApaDataRecognizerType;
// classes referenced
class RFs;

class TDataRecognitionResult
	{
public:
	IMPORT_C void Reset();
public:
	TDataType iDataType;
	TInt iConfidence;
	};

const TInt KDataArrayGranularity=5;
typedef CArrayFixFlat<TDataType> CDataTypeArray;

class CApaDataRecognizer : public CBase
	{
public:
	IMPORT_C TDataRecognitionResult RecognizeL(const TDesC& aName, const TDesC8& aBuffer);
	IMPORT_C TBool RecognizeL(const TDesC& aName, const TDesC8& aBuffer, const TDataType& aDataType);
	IMPORT_C ~CApaDataRecognizer();
	IMPORT_C TInt PreferredBufSize();
	IMPORT_C void DataTypeL(CDataTypeArray& aArray);
	IMPORT_C void UpdateDataTypesL();
	IMPORT_C TInt AcceptedConfidence();
	IMPORT_C void SetAcceptedConfidence(TInt aConfidence);
protected:
	IMPORT_C CApaDataRecognizer(RFs& aFs);
	IMPORT_C void AddDataRecognizerType(CApaDataRecognizerType* aDataRecognizerType);
	IMPORT_C TInt RemoveDataRecognizerType(const CApaDataRecognizerType* aDataRecognizerType);
	IMPORT_C void DestroyRecognizerList();
private:
	void AddDataTypeL(const TDataType& aDataType);
	TBool DoRecognizeL(CApaDataRecognizerType* aDataRecognizerType, const TDesC& aName,
		const TDesC8& aBuffer, const TDataType& aDataType);
protected:
	RFs& iFs;
private:
	IMPORT_C virtual void CApaDataRecognizer_Reserved_1();
private:
	CArrayPtrFlat<CApaDataRecognizerType> iDataRecognizerList;
	CDataTypeArray iDataArray;
	TInt iAcceptedConfidence;
	TDataRecognitionResult iResult;
	TInt iSpare;
	};

class CApaDataRecognizerType : public CBase
	{
public:
	enum TRecognizerPriority
		{
		EHigh=100,
		ENormal=0,
		ELow=-100
		};
	enum TRecognitionConfidence
		{
		ECertain=KMaxTInt,
		EProbable=100,
		EPossible=0,
		EUnlikely=-100,
		ENotRecognized=KMinTInt
		};
public:
	inline TInt MimeTypesCount() const;
	inline TUid TypeUid() const;
	inline TInt Priority() const;
	inline TInt Confidence() const;
	inline TInt Locked() const;
	IMPORT_C TDataRecognitionResult RecognizeL(const TDesC& aName, const TDesC8& aBuffer);
	IMPORT_C TDataType MimeType();
	IMPORT_C void Lock();
	IMPORT_C void Unlock();
	IMPORT_C void UpdateDataTypesL();
	IMPORT_C ~CApaDataRecognizerType();
	IMPORT_C virtual TUint PreferredBufSize();
	IMPORT_C virtual TDataType SupportedDataTypeL(TInt aIndex) const = 0;
protected:
	IMPORT_C CApaDataRecognizerType(TUid aUid, TInt aPriority);
private:
	IMPORT_C virtual void DoRecognizeL(const TDesC& aName, const TDesC8& aBuffer);
	// Reserved virtual functions...
	IMPORT_C virtual void Reserved_1();
protected:
	const TUid iTypeUid;
	const TInt iPriority;
	TInt iCountDataTypes;
	TInt iConfidence;
	TDataType iDataType;
private:
	TInt iLock;
	TInt iSpare;
	};

#include <apmrec.inl>

#endif
