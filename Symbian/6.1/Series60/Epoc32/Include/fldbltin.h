// FLDBLTIN.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __FLDBLTIN_H__
#define __FLDBLTIN_H__

#include <e32std.h>
#include <fldbase.h>


// Classes declared in this file
class MFieldPageNumInfo;
class MFieldNumPagesInfo;
class MFieldFileNameInfo;
// the built-in field types
class CDateTimeField;
class CPageNumField;
class CNumPagesField;
class CFileNameField;
class TRomanNumeral;
//
// Classes referenced
class RReadStream;
class RWriteStream;


class MFieldPageNumInfo
	{
public:
	virtual TInt UpdateFieldPageNum()const=0;
	};


class MFieldNumPagesInfo
	{
public:
	virtual TInt UpdateFieldNumPages()const=0;
	};


class MFieldFileNameInfo
	{
public:
	virtual TInt UpdateFieldFileName(TPtr& aValueText)const=0;
	};


class CDateTimeField : public CTextField
	{
public:
	IMPORT_C CDateTimeField();
	IMPORT_C void SetFormat(const TDesC& aFormat);
	// from TTextField
	IMPORT_C virtual TInt Value(TPtr& aValueText);
	IMPORT_C virtual void InternalizeL(RReadStream& aStream);
	IMPORT_C virtual void ExternalizeL(RWriteStream& aStream)const;
	//
	// Getters
	IMPORT_C const TDesC& FormatString()const;
	IMPORT_C TUid Type()const;
protected:
	TBuf<64> iFormatString;
	};


class CPageFieldBase : public CTextField
	{
public:
	enum TNumberStyle {
		EArabic,			// 1,2,3
		ERomanUpper,		// I,II,III
		ERomanLower,		// i,ii,iii
		EAlphabeticUpper,	// A,B,C
		EAlphabeticLower	// a,b,c
		};
public:
	inline void SetNumberStyle(TNumberStyle aStyle) { iStyle = aStyle; } 
	// from TTextField
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream)const;
	//
	// Getters
	IMPORT_C TNumberStyle NumberStyle()const;
protected:
	TInt InsertValue(TPtr& aValueText,TInt aValue);
protected:
	TNumberStyle iStyle;
	};


class CPageNumField : public CPageFieldBase
	{
public:
	inline void SetPageNumInfo(MFieldPageNumInfo* aInfo) { iPageNumInfo=aInfo; }
	// from TTextField
	IMPORT_C TInt Value(TPtr& aValueText);
	IMPORT_C TUid Type()const;
protected:
	MFieldPageNumInfo* iPageNumInfo;
	};


class CNumPagesField : public CPageFieldBase
	{
public:
	inline void SetNumPagesInfo(MFieldNumPagesInfo* aInfo) { iNumPagesInfo=aInfo; }
	// from TTextField
	IMPORT_C TInt Value(TPtr& aValueText);
	IMPORT_C TUid Type()const;
protected:
	MFieldNumPagesInfo* iNumPagesInfo;
	};


class CFileNameField : public CTextField
	{
public:
	inline void SetFileNameInfo(MFieldFileNameInfo* aInfo) { iFileNameInfo=aInfo; }
	// from TTextField
	IMPORT_C virtual TStreamId StoreL(CStreamStore& aStore)const;  // returns KNullStreamId
	IMPORT_C virtual void RestoreL(const CStreamStore& aStore,TStreamId aId); // does nothing.
	IMPORT_C virtual TInt Value(TPtr& aValueText);
	inline virtual void InternalizeL(RReadStream& /*aStream*/) {}; // stream the formatting
	IMPORT_C TUid Type()const;
protected:
	MFieldFileNameInfo* iFileNameInfo;
	};


#endif
