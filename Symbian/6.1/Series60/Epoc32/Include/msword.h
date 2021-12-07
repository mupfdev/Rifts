// MSWORD.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

//
// Stub headers for converter calling
// awaiting defined converter architecture
//

#ifndef __MSWORD_H__
#define __MSWORD_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif

#if !defined(__FLDBLTIN_H__)
#include <fldbltin.h>
#endif

//#define _LOGGING

class CFieldThings;
class CWordModel;
class CFileStore;
class CStreamDictionary;
class COleFilePropertySetDir;

class CMsWordConverter : public CBase
	{
public:
	IMPORT_C CMsWordConverter();
	IMPORT_C ~CMsWordConverter();
	IMPORT_C void ConvertL(const TDesC& aSourceFile, const TDesC& aTargetFile);
private:
	void NewDocumentL(const TDesC& aTargetFile);
	void ConstructPrintL();
private:
	CFieldThings* iFieldThings;
	CWordModel* iModel;
	RFs iFs;
	};

class CFieldThings : public MFieldNumPagesInfo, public MFieldFileNameInfo, public CBase
	{
public:
	CFieldThings();
	~CFieldThings();
	TInt UpdateFieldNumPages() const;
	TInt UpdateFieldFileName(TPtr& aValueText) const;
	void SetFileName(const TDesC& aFileName);
private:
	TFileName iFileName;
	};

#endif
