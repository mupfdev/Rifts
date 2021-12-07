/////////////////////////////////////////////////////////////////////////////
//
//	MsvSendErrorAction.H
//
//	Copyright (c) 1999 Symbian Ltd.  All rights reserved. 
//
/////////////////////////////////////////////////////////////////////////////

#ifndef MSV_SEND_ERROR_ACTION_H_
#define MSV_SEND_ERROR_ACTION_H_

/////////////////////////////////////////////////////////////////////////////
//
//	Includes
//
/////////////////////////////////////////////////////////////////////////////

#include "schsend.hrh"
#include <barsread.h>
#include <msvstore.h>

/////////////////////////////////////////////////////////////////////////////
//
//	Constants
//
/////////////////////////////////////////////////////////////////////////////

const TUid KUidMsvFileSendErrorActions		= {0x10005711};	//Used by CMsvSendErrorActions

const TInt16 KMsvSendErrorActionVersion		= 1;
const TInt16 KMsvSendErrorActionsVersion	= 1;

/////////////////////////////////////////////////////////////////////////////
//
//	TMsvSendErrorAction Declaration
//
/////////////////////////////////////////////////////////////////////////////

class TMsvSendErrorAction
	{
public:
	IMPORT_C TMsvSendErrorAction();

	IMPORT_C void InternalizeL(RReadStream& aReadStream);
	IMPORT_C void ExternalizeL(RWriteStream& aWriteStream) const;
	IMPORT_C void Reset();

	IMPORT_C void SetMaxRetries(const TInt16 aMaxRetries);
	IMPORT_C TInt16 MaxRetries() const;

	TInt					iError;
	TMsvSendAction			iAction;
	TMsvSendRetries			iRetries;
	TMsvSendRetrySpacing	iRetrySpacing;

private:
	TInt16	iMaxRetries;
	TInt16	iVersion;
	};


/////////////////////////////////////////////////////////////////////////////
//
// CMsvSendErrorActions
//
/////////////////////////////////////////////////////////////////////////////

class CMsvSendErrorActions : public CBase
	{
public:
	IMPORT_C static CMsvSendErrorActions* NewL();
	IMPORT_C ~CMsvSendErrorActions();

	IMPORT_C void AddSendErrorActionL(const TMsvSendErrorAction& aAction);
	IMPORT_C const TInt RemoveSendErrorAction(const TInt aError);
	IMPORT_C const TInt GetSendErrorAction(const TInt aError, TMsvSendErrorAction& aAction) const;

	IMPORT_C void StoreL(CMsvStore& aStore) const;
	IMPORT_C void RestoreL(CMsvStore& aStore);
	IMPORT_C void RestoreFromResourceL(TResourceReader& aReader);

	IMPORT_C void SetErrorsL(const CArrayFixFlat<TMsvSendErrorAction>& aActions);
	IMPORT_C const CArrayFixFlat<TMsvSendErrorAction>& Errors() const;

	IMPORT_C const TMsvSendErrorAction& Default() const;
	IMPORT_C void SetDefault(const TMsvSendErrorAction& aAction);

private:
	CMsvSendErrorActions();
	void ConstructL();
	void RestoreErrorActionL(TResourceReader& aReader, TInt aActionCount, const TBool aDefault);

	void InternalizeL(RReadStream& aReadStream);
	void ExternalizeL(RWriteStream& aWriteStream) const;

	const TInt Find(const TInt aError, TInt& aIndex) const;

	TInt16 iVersion;
	
	CArrayFixFlat<TMsvSendErrorAction>* iErrors;
	TMsvSendErrorAction iDefault;
	};

#endif