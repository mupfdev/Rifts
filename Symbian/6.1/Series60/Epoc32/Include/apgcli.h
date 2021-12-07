// APGCLI.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__APGCLI_H__)
#define __APGCLI_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__APMSTD_H__)
#include <apmstd.h>
#endif
#if !defined(__APMREC_H__)
#include <apmrec.h>
#endif
#if !defined(__APAID_H__)
#include <apaid.h>
#endif
#if !defined(__BADESCA_H__)
#include <badesca.h>
#endif

// classes referenced
class CApaCommandLine;
class CApaMaskedBitmap;
//

////////////////////////////////////
// RApaLsSession
////////////////////////////////////

class RApaLsSession : public RSessionBase
	{
public:
	enum {
		ENoMoreAppsInList=1,
		EAppListInvalid
		};
	enum TLaunchType {
		ELaunchNewApp=1,
		ESwitchFiles
		};
public:
	IMPORT_C RApaLsSession();
	//
	IMPORT_C TInt Connect();
	IMPORT_C TVersion Version() const;
	//
	IMPORT_C TInt AppCount(TInt& aCount) const; // returns error
	IMPORT_C TInt EmbeddableAppCount(TInt& aCount) const; // returns error
	//
	IMPORT_C TInt GetAllApps() const; // Call to initialize
	IMPORT_C TInt GetAllApps(TInt aScreenMode) const; // Call to initialize
	IMPORT_C TInt GetEmbeddableApps() const; // Call to initialize
	IMPORT_C TInt GetEmbeddableApps(TInt aScreenMode) const; // Call to initialize
	IMPORT_C TInt GetNextApp(TApaAppInfo& aInfo) const; // call repeatedly, returns err (inc ENoMoreAppsInList,EAppListInvalid)
	IMPORT_C TInt GetNextApp(TApaAppInfo& aInfo,TInt aScreenMode) const; // call repeatedly, returns err (inc ENoMoreAppsInList,EAppListInvalid)
	//
	IMPORT_C TInt GetAppInfo(TApaAppInfo& aInfo,TUid aAppUid) const;
	IMPORT_C TInt GetAppCapability(TDes8& aCapabilityBuf,TUid aAppUid) const;
	IMPORT_C TInt StartApp(const CApaCommandLine& aCommandLine); // This is only recommended for non document based apps
	IMPORT_C TInt StartApp(const CApaCommandLine& aCommandLine,TThreadId& aId);
	//
	// ER5 additions
	IMPORT_C TInt RecognizeData(const TDesC& aName, const TDesC8& aBuffer, TDataRecognitionResult& aDataType) const;
	IMPORT_C TInt RecognizeSpecificData(const TDesC& aName, const TDesC8& aBuffer, const TDataType& aDataType, TBool& aResult) const;
	//
	IMPORT_C TInt AppForDataType(const TDataType& aDataType, TUid& aAppUid) const;
	IMPORT_C TInt StartDocument(const TDesC& aFileName, TThreadId& aId, TLaunchType aLaunchType=ELaunchNewApp);
	IMPORT_C TInt StartDocument(const TDesC& aFileName, const TDataType& aDataType, TThreadId& aId, TLaunchType aLaunchType=ELaunchNewApp);
	IMPORT_C TInt StartDocument(const TDesC& aFileName, TUid aAppUid, TThreadId& aId, TLaunchType aLaunchType=ELaunchNewApp);
	IMPORT_C TInt CreateDocument(const TDesC& aFileName, TUid aAppUid, TThreadId& aId, TLaunchType aLaunchType=ELaunchNewApp);
	//
	IMPORT_C TInt GetAppIcon(TUid aAppUid, TInt aSize, CApaMaskedBitmap& aAppBitmap) const;
	//
	IMPORT_C TInt AppForDocument(const TDesC& aFileName, TUid& aUid, TDataType& aDataType) const;
	IMPORT_C TInt IsProgram(const TDesC& aFileName, TBool& aProgram) const;
	IMPORT_C TInt GetAcceptedConfidence(TInt& aConfidence) const;
	IMPORT_C TInt SetAcceptedConfidence(TInt aConfidence);
	IMPORT_C TInt GetMaxDataBufSize(TInt& aBufSize) const;
	IMPORT_C TInt SetMaxDataBufSize(TInt aBufSize);
	IMPORT_C TInt GetSupportedDataTypesL(CDataTypeArray& aDataTypes) const;
	//
	// ER6 Additions
	IMPORT_C TInt GetAppIconSizes(TUid aAppUid, CArrayFixFlat<TSize>& aArrayToFill) const;
	IMPORT_C TInt GetAppIcon(TUid aAppUid, TSize aSize, CApaMaskedBitmap& aAppBitmap) const;
	// ER6.1
	IMPORT_C TInt GetAppViews(CApaAppViewArray& aAppViews, TUid aAppUid) const;
	IMPORT_C TInt GetAppViewIcon(TUid aAppUid, TUid aViewUid, const TSize& aSize, CApaMaskedBitmap& aViewBitmap) const;
	IMPORT_C TInt GetAppOwnedFiles(CDesCArray& aAppOwnedFiles, TUid aAppUid) const;
	//
public:
	// internal to the DLL
	void CancelNotify() const;
	void SetNotify(TRequestStatus& aStatus);
private:
	void DoGetAppOwnedFilesL(CDesCArray& aArrayToFill, TUid aAppUid) const;
	void DoGetAppViewsL(CApaAppViewArray& aArrayToFill, TUid aAppUid) const;
	void DoGetAppIconSizesL(TUid aAppUid, CArrayFixFlat<TSize>& aArrayToFill) const;
	TInt DoAppCount(TInt& aCount,TInt aCommand) const;
	TInt DoGetApps(TInt aCommand,TInt aScreenMode) const;
	TInt StartAndCreate(TInt aRqst,const TDesC& aFileName, TUid aAppUid, TThreadId& aId, TLaunchType aLaunchType);
	TInt ReconnectToServer(TInt aErr,TBool& aTriedOnce) const;
	TInt SendReceiveWithReconnect(TInt aFunction, TAny* aPtr) const;
	};


#endif

