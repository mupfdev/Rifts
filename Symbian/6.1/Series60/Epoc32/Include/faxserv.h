// FAXSERV.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__FaxServ_H__)
#define __FaxServ_H__

#include <f32file.h>
#include <s32file.h>
#include <s32mem.h>

#if !defined(__FAXSTORE_H__)
#include <faxstore.h>
#endif
	  
#if !defined(__FAXHUFF_H__)
#include <faxhuff.h>
#endif

#if !defined(__ETEL_H__)
#include "etel.h"
#endif

#include "FaxStd.h"

const TUint KUidDynamicFaxServer = 0x10004C88;		
const TUint KUidUnicodeDynamicFaxServer = 0x10004C89;

TInt FaxServerThread (TAny * session);  // function declaration needed here

#define KMaxDialLength		50		
#define KConfigStringLength 32		


//**********************************
// TFaxServerSessionSettings
//**********************************
	   
struct TFaxServerSessionSettings
	{
	TFaxServerSessionSettings& operator=(const TFaxServerSessionSettings& aSettings);
	TBuf8<KMaxDialLength> iPhoneNumber;
	TBool iLogging;
	TBuf8<KConfigStringLength> iFaxInitString;
	TFaxMode iMode;
	TFaxClass iFaxClass;
	TFileName iPortDriverName;
	TName iCommPortName;
	TBuf<RCall::KFaxIdUserNameMaxSize> iFaxId;
	TInt iMaxSpeed;
	TInt iMinSpeed;
	TInt iPreferredECM;
	TInt iFaxOnDemandDelay;
// Tx Settings
	TFaxResolution iTxResolution;
	TFaxCompression iTxCompression;
	TInt iTxPages;
// Rx Settings
	TFaxResolution iRxResolution;
	TFaxCompression iRxCompression;
	};

class MFaxCompletionBase
	{
public:
	virtual void RxConnectComplete(TInt aError)=0;		
	virtual void RxFaxDataComplete(TInt aError)=0;		
	virtual void RxPostPageComplete(TInt aError)=0;
	virtual void TxConnectComplete(TInt aError)=0;
    virtual void TxFaxDataComplete(TInt aError)=0;
	virtual void TxPostPageComplete(TInt aError)=0;		

	virtual void GetCadenceAndTimeOfLastRing(TTimeIntervalMicroSeconds& aCadence,TTime& aTime)=0;
	};	


class CFaxModemDriver;
class CFaxSession : public CBase
   {
 public:
     virtual TInt FxOpen(TFaxServerSessionSettings&,RFax::TProgress* aProgress);
	 virtual TInt FxClose();
	 virtual void RxConnect();
	 virtual void RxFaxData(TDes8 & aData);
	 virtual void RxPostPage();
	 virtual void TxConnect();
	 virtual void TxFaxData(const TDesC8 & aData);
	 virtual void TxPostPage();
	 virtual void Cancel();
	 virtual void SetCallBack(MFaxCompletionBase* aBase);

     static CFaxSession * NewL ();
     static CFaxSession * NewLC ();
     ~CFaxSession ();

	 MFaxCompletionBase* ReturnCompletionBase(void);		// added by JerryC
     void StartModemL ();


  enum TFaxThreadRequest
     {
     ERxConnect,
     ERxFaxData,
     ERxPostPage,
     ETxConnect,
     ETxFaxData,
     ETxPostPage,
     EFxClose
     };

	/********************************************************************/
	// CFaxRequest active object
	/********************************************************************/

  class CFaxRequest : public CActive
     {
   public:
     CFaxRequest();
     ~CFaxRequest ();
     static CFaxRequest * NewL (CFaxSession *);
     static CFaxRequest * NewLC (CFaxSession *);
     void ConstructL (CFaxSession *);
     void DoCancel();
     void FaxRequest (TFaxThreadRequest);
     void RunL ();
  
   public:
     RThread iChildThread;
     TRequestStatus iThreadStat;
     TInt iCancel;

   private:
     CFaxSession  * iFaxSession;
     TFaxThreadRequest iFaxThreadRequest;
     };

 public:
   RThread iParentThread;
   CFaxModemDriver * iModemDriver;
   TDes8 * iRxData;
   const TDesC8 * iTxData;
   CFaxRequest * iFaxRequest;
   TFaxServerSessionSettings iFaxServerSessionSettings;
   RFax::TProgress* iProgress;
 private:
   TRequestStatus iChildDeath;
   MFaxCompletionBase* iCompletionBase;					// added by JerryC
   TBool iAmDestructing;
   };


/********************************************************************/

/* 
class MFaxSession 
	{
public:
     virtual TInt FxOpen(TFaxServerSessionSettings&,RFax::TProgress* aProgress)=0;
	 virtual TInt FxClose()=0;

	 virtual void RxConnect()=0;
	 virtual void RxFaxData(TDes8 & aData)=0;
	 virtual void RxPostPage()=0;

	 virtual void TxConnect()=0;
	 virtual void TxFaxData(const TDesC8 & aData)=0;
	 virtual void TxPostPage()=0;

	 virtual void Cancel()=0;

	 virtual void SetCallBack(MFaxCompletionBase* aCompletionBase)=0;
	};

  */


#endif
