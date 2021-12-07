////////////////////////////////////////////////////////////////////////////////
//
//	FAXS.H
//
//	Copyright © 1999 Symbian Ltd.  All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef FAXS_H_
#define FAXS_H_

////////////////////////////////////////////////////////////////////////////////
//
//	Includes
//
////////////////////////////////////////////////////////////////////////////////

#include <mtsr.h>
#include <ScheduleBaseServerMtm.h>
#include <msvipc.h>
#include "msfxtran.h"
#include "fxsendop.h"   

////////////////////////////////////////////////////////////////////////////////
//
//	CFaxServerMtm Declaration
//
////////////////////////////////////////////////////////////////////////////////

class CFont;
class CFbsBitmapDevice;
class CGraphicsContext;
class RFbsSession;

class CFaxServerMtm : public CScheduleBaseServerMtm
	{
public:

//	--- Class Factory ---

   IMPORT_C static CFaxServerMtm* NewL(CRegisteredMtmDll& aFaxServerMtmDll, CMsvServerEntry* aServerEntry);

//	--- Destruction ---

   ~CFaxServerMtm();

//	--- Functions derived from CBaseServerMtm ---
   
	void CopyFromLocalL(const CMsvEntrySelection& aSelection, TMsvId aDestination, TRequestStatus& aStatus);
	void CopyToLocalL(const CMsvEntrySelection& aSelection, TMsvId aDestination, TRequestStatus& aStatus);
	void CopyWithinServiceL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
	void MoveToLocalL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
	void MoveFromLocalL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
	void MoveWithinServiceL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);

	void DeleteL(const CMsvEntrySelection& aSelection , TRequestStatus& aStatus);
	void DeleteAllL(const CMsvEntrySelection& aSelection, TRequestStatus& aStatus);
	void CreateL(TMsvEntry aNewEntry , TRequestStatus& aStatus);
	void ChangeL(TMsvEntry aNewEntry , TRequestStatus& aStatus);

	void StartCommandL(CMsvEntrySelection&  aSelection , TInt  aCommand , const TDesC8&  aParameter , TRequestStatus& aStatus);
	const TDesC8& Progress();		//Changed temporarily
	TBool CommandExpected();

protected:

//	--- Construction ---

	CFaxServerMtm(CRegisteredMtmDll& aEntry, CMsvServerEntry* aServerEntry);
	void LoadResourceFileL();

//	--- Active Object functions ---

	void DoCancel();
	void DoRunL();

//	--- Function derived from CBaseServerMtm ---

	void DoComplete(TInt aError);

//	--- Functions derived from CScheduleBaseServerMtm ---

	void ConstructL();
	void RestoreScheduleSettingsL();
	void PopulateSchedulePackage(const TDesC8& aParameter, const TBool aMove, TMsvSchedulePackage& aPackage) const;

private:

//	--- Private FAX Functions ---

//	--- Send and Receive ---

	TBool SendFaxesL(const CMsvEntrySelection& aSelection);
	void ReceiveFaxesL(TMsvId aDestination, TFaxMode aFaxMode, TRequestStatus& aStatus);
	void ReceiveFaxesL(TMsvId aDestination, TFaxMode aFaxMode, TRequestStatus& aStatus, const TDesC8& aFaxBackNumber);
	void WatcherReceiveL(TMsvId aDestination, TRequestStatus& aStatus);

//	--- Rendering Functions ---

	void RenderFaxToFileL(const CMsvEntrySelection& aSelection, TRequestStatus& aStatus);
	void RenderFaxAndSendL(const CMsvEntrySelection& aSelection, TFaxMode aFaxMode, TBool aMove, TRequestStatus& aStatus);

	void PrepareHeaderLinesL();
	CFont* GetFontL(CFbsBitmapDevice& aBitmapDevice);
	void DrawAndSetTime(CGraphicsContext& aGc, TFaxHeaderInfo& aFaxHeaderInfo, const TLocale& aLocale, TInt aTimePos, TInt aFontWidth, TInt aBaseLine);
	void DrawAndSetDate(CGraphicsContext& aGc, TFaxHeaderInfo& aFaxHeaderInfo, const TLocale& aLocale, TInt aDatePos, TInt aFontWidth, TInt aBaseLine);
	void RestoreFaxSettingsL();
	void LoadOomStringsL();
	void UpdateEntriesL(TInt aError);

private:

//	--- Private Members ---

	CSendFaxSession* iFaxSendSession;
	CRecvFaxSession* iFaxReceiveSession;
	TBool iOOMState;
	TMTMFaxSettings iFaxSettings;
	HBufC* iOomLine1;
	HBufC* iOomLine2;
	HBufC* iOomButton1;
	HBufC* iOomButton2;
	TInt iButtonChosen;
	RNotifier iNotifier;
	CFaxPrepare* iFaxPrepare;
	TFaxMode iFaxMode;
	TBool iMove;
	TBuf8<KMsvProgressBufferLength> iProgressBuffer;
	TBool iSendFaxes;
	TMsvId iOldId;
	CMsvEntrySelection* iSelection;
	TInt iLastCommand;
	TBool iConditionsNotMet;
	TMsvSendErrorAction iErrorAction;
	};

#endif
