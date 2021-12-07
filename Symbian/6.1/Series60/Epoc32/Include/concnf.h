// CONCNF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__CONCNF_H__)
#define __CONCNF_H__

#include <e32base.h>
#include <f32file.h>
#include <s32stor.h>
#include <apmstd.h>

#define KMaxTranslation 50
typedef TBuf<KMaxTranslation> TTranslation;

class TLanguageInfo
	{
public:
	TLanguageInfo();
	IMPORT_C TLanguageInfo(TLanguage aLanguage,TTranslation aTranslation);
public:
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
	TLanguage Language();
	TTranslation Translation();
public:
	TLanguage	iLanguage;
	TTranslation iTranslation;
	};

/**
 *Holds the type of each mime and translations for each language
 */
class CMimeInfo : public CBase
	{
public:
	IMPORT_C ~CMimeInfo();
	IMPORT_C static CMimeInfo* NewLC(TDataType& aMime);
	static CMimeInfo* NewL();
	static CMimeInfo* NewLC(const CMimeInfo* aInfo);
public:
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
	TDataType Mime();
	TTranslation Text();
	IMPORT_C void AddLanguageL(TLanguageInfo aLang);
private:
	void ConstructL();
private:
	TDataType iMime;
	CArrayFixFlat<TLanguageInfo> *iLanguageInfo;
	};

/**
 *Holds inherent properties of a converter
 *these are Uid, and the mime types it supports
 */
class CCnaConverter : public CBase
	{
public:
	static CCnaConverter* NewL();
	IMPORT_C static CCnaConverter* NewL(TUid aUid);
	IMPORT_C static CCnaConverter* NewLC(TUid aUid);
	IMPORT_C static CCnaConverter* NewL(const CCnaConverter& aConverter);
	IMPORT_C static CCnaConverter* NewLC(const CCnaConverter& aConverter);
	IMPORT_C ~CCnaConverter();
	IMPORT_C void AddMimeFromL(const CMimeInfo* aMimeInfo);
	IMPORT_C void AddMimeToL(const CMimeInfo* aMimeInfo);
	IMPORT_C void SetUid(TUid aUid);
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C TBool MimeFrom(const TDataType& aMimeType) const;
	IMPORT_C TBool MimeTo(const TDataType& aMimeType) const;
	IMPORT_C TTranslation MimeFromText(const TDataType& aMimeType) const;
	IMPORT_C TTranslation MimeToText(const TDataType& aMimeType) const;
	IMPORT_C TInt CountFrom() const;
	IMPORT_C TInt CountTo() const;
	IMPORT_C TDataType MimeFrom(TInt aIndex) const;
	IMPORT_C TDataType MimeTo(TInt aIndex) const;
	IMPORT_C TTranslation MimeFromText(TInt aIndex) const;
	IMPORT_C TTranslation MimeToText(TInt aIndex) const;
	inline TUid Uid() const;
private:
	CCnaConverter();
	void ConstructL();
	TBool FindMime(const TDataType& aMimeType, const CArrayPtrFlat<CMimeInfo>* aList) const;
	TTranslation FindMimeText(const TDataType& aMimeType, const CArrayPtrFlat<CMimeInfo>* aList) const;
private:
	TUid iUid;
	CArrayPtrFlat<CMimeInfo>* iMimeFrom;
	CArrayPtrFlat<CMimeInfo>* iMimeTo;
	};

class CCnaConvInfoFile : public CBase
// implementation class
	{
public:
	~CCnaConvInfoFile();
	//
protected:
	void ConstructL();
protected:
	RFs iFs;
	CPersistentStore* iStore;
	CArrayPtr<CCnaConverter>* iConverters;
	};

/**
 * classes CCnaConvInfoFileReader and CCnaConvInfoFileWriter are collection classes
 * for CCnaConverter.  
 *
 * Each CNF file contains CCnaConverter information for each
 * available CConverterBase derived class in it's associated DLL.
 * 
 * In addition there may be INI files for each converter which supply run time extended
 * CCnaConverter information such as additional mime types.
 */
class CCnaConvInfoFileReader : public CCnaConvInfoFile
	{
public:
	IMPORT_C static CCnaConvInfoFileReader* NewLC(const TDesC& aFileName,TUid aDllUid=KNullUid);
	IMPORT_C static CCnaConvInfoFileReader* NewL(const TDesC& aFileName,TUid aDllUid=KNullUid);
	IMPORT_C TInt Count();
	IMPORT_C CCnaConverter* AtL(TInt anIndex);
	//
	IMPORT_C void RestoreL();
private:
	void RestoreConverterL(TUid aUid, const CStreamDictionary& aDict);
	void ConstructL(const TDesC& aFileName,TUid aUid);
	};


class CCnaConvInfoFileWriter : public CCnaConvInfoFile
	{
public:
	IMPORT_C static CCnaConvInfoFileWriter* NewLC(const TDesC& aFileName,TUid aUid);
	IMPORT_C static CCnaConvInfoFileWriter* NewL(const TDesC& aFileName,TUid aUid);
	IMPORT_C ~CCnaConvInfoFileWriter();
	//
	IMPORT_C void AddConverterL(const CCnaConverter& aConverter);
	//
	IMPORT_C void StoreL() const;
private:
	TStreamId StoreConverterL(const CCnaConverter& aConverter)const;
	TStreamId StoreHeaderL()const;
	void ConstructL(const TDesC& aFileName,TUid aUid);
private:
	CStoreMap* iMap;
	};


inline TUid CCnaConverter::Uid() const
	{return iUid;}

#endif
