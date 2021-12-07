// 
// PiHand.h
// Copyright (C) 1997-1998 Symbian Ltd. All rights reserved.
// 
// Created at: 31-Dec-98 9:52:34 AM
// Comments: Defines all the DataHandler plugin classes contained within this plugin DLL
// 


#if !defined(__PIHAND_H__)
#define __PIHAND_H__


#if !defined(__E32DEF_H__)
#include <e32def.h>
#endif
#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif


#include "DHand.h"		// The base CDataHandler definition

enum DataHandlingPluginIndex
	{
	EDefaultDocHandlerIndex = KDefaultIndex,
	EWMLScriptDataHandlerIndex
	} ;

// The count of the number of plugins defined for this DLL
#define KDataHandlerPluginCount	EWMLScriptDataHandlerIndex		// Two only in this DLL so far

// Literals defined for the plugin information
const TInt KDefaultDataHandlerMajorVN=1;
const TInt KDefaultDataHandlerMinorVN=0;
const TInt KDefaultDataHandlerBuildVN=0;
_LIT(KDefaultHandlerName,"CDefaultDataHandler||Comment : Default handler for all text mime types||Author : B.D.Evans.||Copyright (C) 1997-1999 Symbian Ltd. All rights reserved.");
_LIT(KDefaultHandlerData,"*/*||ISO-LATIN1");

const TInt KWMLScriptDataHandlerMajorVN=1;
const TInt KWMLScriptDataHandlerMinorVN=0;
const TInt KWMLScriptDataHandlerBuildVN=0;
_LIT(KWMLScriptHandlerName,"CWMLScriptDataHandler||Comment : WML 1.1 Script handler for all application/vnd.wap.wmlscriptc mime types||Author : B.D.Evans.");
_LIT(KWMLScriptHandlerData,"application/vnd.wap.wmlscriptc||ISO-LATIN1");

class CDefaultDataHandler : public CDataHandler
// CDefaultDataHandler provides the default plugin when the 
// specific plugin for a data type cannot be matched: 
// 
	{
	// Methods
public:
	static CDefaultDataHandler* NewL(RFs& aFs, const RLibrary& aLibrary, TInt aIndex);
	static CDefaultDataHandler* NewLC(RFs& aFs, const RLibrary& aLibrary, TInt aIndex);
	virtual ~CDefaultDataHandler();

	// Data Received here
	void ProcessDataL ( HBufC8& aBuffer );
	void SetDataExpected(TInt);
	void CommitL();

	// from CPluginBase
	TVersion Version() const;
	HBufC* NameL() const;
	HBufC* DataL() const;

	// MDataProviderObserver method : Status reciever from the DataProvider
	virtual void SetStatus ( TInt aStatusCode = KErrNone );

protected:
	CDefaultDataHandler(RFs& aFs, const RLibrary& aLibrary, TInt aIndex);

private:
	void ConstructL();

// Attributes / Properties
public:

protected:

private:

	CBufFlat* iBuffer;
	TInt iMark;

};  // CDefaultDataHandler

class CWMLScriptDataHandler : public CDataHandler
// CDefaultDataHandler provides the default plugin when the 
// specific plugin for a data type cannot be matched: 
// 
	{
	// Methods
public:
	static CWMLScriptDataHandler* NewL(RFs& aFs, const RLibrary& aLibrary, TInt aIndex);
	static CWMLScriptDataHandler* NewLC(RFs& aFs, const RLibrary& aLibrary, TInt aIndex);
	virtual ~CWMLScriptDataHandler();

	// Data Received here
	void ProcessDataL ( HBufC8& aBuffer );

	// from CPluginBase
	TVersion Version() const;
	HBufC* NameL() const;
	HBufC* DataL() const;

	// MDataProviderObserver method : Status reciever from the DataProvider
	virtual void SetStatus ( TInt aStatusCode = KErrNone );

protected:
	CWMLScriptDataHandler(RFs& aFs, const RLibrary& aLibrary, TInt aIndex);
	virtual void CommitL();

private:
	void ConstructL();

// Attributes / Properties
public:

protected:

private:
	TFileName iScriptFilePath;		// Location for the script storage
	RFile	  iScriptFile;
	RFs		  iFs;

};  // CWMLScriptDataHandler

#endif    // __PIHAND_H__

