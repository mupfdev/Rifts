// EIKENV.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKENV_H__)
#define __EIKENV_H__

#include <uikon.hrh>
#include <coemain.h>
#include <coedef.h>
#include <eikdef.h>
#include <gulalign.h>
#include <apaflrec.h>
#include <apacmdln.h>
#include <badesca.h>
#include <baerrhan.h>
#include <gulcolor.h>
#include <eikdgfty.h>
#include <eikaufty.h>
#include <eiklibry.h>
#include <eikamnt.h>
#include <lafmain.h>
#include "eikvcurs.h"
//#include <lafenv.h>

class CEikProcess;
class CEikInfoMsgWin;
class CEikBusyMsgWin;
class CEikAppUi;
class CEikHotKeyTable;
class CCoeControl;
class CParaFormatLayer;
class CCharFormatLayer;
class CCoeBrushAndPenContext;
class CEikCommandButton;
class CPrintSetup;
class CDictionaryStore;
class CApaWindowGroupName;
class CEikErrorIdler;
class CEikApplication;
class MEikInfoDialog;
class MEikAlertWin;
class CEikDialog;
class MEikDebugKeys;
class CEikLibrary;
class MEikAppUiFactory;
class MEikIrFactory;
class CGulIcon;
class CApaMaskedBitmap;
class CEikLogicalBorder;
class CEikLafEnv;
class TLogicalFont;
class CEikPictureFactory;
class CEikEnvExtra;
class TAknSystemFont; //defined in lafenv.h


// The following constant values are internal to Symbian.
const TInt KTimeBetweenClicks=1000000;	 // in Microseconds			 
const TInt KDoubleClickDistance=10;

const TInt KKeyboardRepeatRate=50000;
const TInt KKeyboardRepeatInitialDelay=800000;

const TUid KSystemIniFileUid = {0x1000010C};
const TUid KUikonLibraryUid = {KUidUikonLibraryValue};
// End of internal constant values.

typedef void (*TRequestDialogFunc)();

/** Color indirection macros
 *
 * This macro takes number from LAF specification and converts it to TRgb for use to draw things.
 */

// Color macros 
#define AKN_LAF_COLOR_ENV(env,nn)	CEikonEnv::AvkonColor(nn)
#define AKN_LAF_COLOR(nn)			CEikonEnv::AvkonColor(nn)
#define AKN_LAF_COLOR_STATIC(nn)	CEikonEnv::AvkonColor(nn)


class MEikPictureFactory
	{
public:
	IMPORT_C virtual TUid Id() const;
	/**
	 * Returns ETrue if the factory supports the specified picture type
	 */
	virtual TBool SupportsPictureType(TUid aPictureType) const=0;
	/**
	 * Returns a pointer to the real picture factory which is required by EText.
	 * Doesn't transfer ownership
	 */
	virtual const MPictureFactory* PictureFactory(TUid aPictureType) const=0;
	/**
	 * Insert a new object.  Ownership of aData transfers immediately the function is called.
	 */
	virtual TPictureHeader InsertL(TUid aPictureType,CBase* aData)=0;
	/**
	 * Edit/view an object
	 */
	virtual void EditL(const TPictureHeader& aPictureHeader,TBool aReadOnly)=0;
private:
	IMPORT_C virtual void MEikPictureFactory_Reserved_1();
	IMPORT_C virtual void MEikPictureFactory_Reserved_2();
	};


class CEikonEnv : public CCoeEnv, public MApaAppStarter
	{
public:
	IMPORT_C ~CEikonEnv();
	IMPORT_C CEikonEnv();
	IMPORT_C void ConstructL();
	IMPORT_C void ConstructL(TBool aInitialFocusState);
	IMPORT_C void ConstructAppFromCommandLineL(const CApaCommandLine& aCommandLine);
	IMPORT_C void ControlStackReadyL();
	IMPORT_C static TVersion Version();
	//
	inline static CEikonEnv* CEikonEnv::Static();
	IMPORT_C const CFont* AnnotationFont() const;
	IMPORT_C const CFont* TitleFont() const;
	IMPORT_C const CFont* LegendFont() const;
	IMPORT_C const CFont* SymbolFont() const;
	IMPORT_C const CFont* DenseFont() const;
	IMPORT_C const CFont* Font(const TLogicalFont& aLogicalFont) const;
	//
public: // internal to Symbian
	IMPORT_C const CFbsBitmap* TexturedBitmap() const;
public: // Do not use
	IMPORT_C const CFbsBitmap* GrayBitmap() const;
	IMPORT_C const CFbsBitmap* OptionBitmap() const;
	IMPORT_C const CFbsBitmap* HighlightedOptionBitmap() const;
	IMPORT_C const CFbsBitmap* OptionMaskBitmap() const;
public:
	IMPORT_C const CFbsBitmap* Bitmap(TUid aUidBmp) const;
	void InitSystemBitmapsL();
public: // Internal to Symbian
	IMPORT_C MLafEnv& LafEnv() const;
	inline TInt EditableControlStandardHeight() const;
public:
	inline CEikProcess* Process() const;
	inline const MEikAlertWin* Alert() const;
	IMPORT_C MPictureFactory* PictureFactory()const;
	IMPORT_C MEikPictureFactory* ExtendedPictureFactory(TUid aPictureType) const;
	IMPORT_C void AddPictureFactoryL(MEikPictureFactory& aFactory);
	IMPORT_C void RemovePictureFactory(TUid aFactoryId);
	IMPORT_C void SetAlertWin(MEikAlertWin* aAlertWin);
	IMPORT_C void AlertWin(const TDesC& aMsg);
	IMPORT_C void AlertWin(const TDesC& aMsg1,const TDesC& aMsg2);
	IMPORT_C void LeaveWithInfoMsg(TInt aResourceId,...);
public: // Internal to Symbian
	IMPORT_C void LeaveWithErrorContext(TInt aError,const TDesC& aContextText);
	IMPORT_C void GetErrorText(TDes& aDes,TInt aError) const;
public:
	IMPORT_C void InfoMsg(const TDesC& aDes);
	IMPORT_C void InfoMsgWithAlignment(TGulAlignment aCorner,const TDesC& aDes);
	IMPORT_C void InfoMsg(TInt aResourceId,...);
	IMPORT_C void InfoMsg(TInt aResourceId,VA_LIST aList);
	IMPORT_C void InfoMsgWithAlignment(TGulAlignment aCorner,TInt aResourceId,...);
	IMPORT_C void InfoMsgWithAlignment(TGulAlignment aCorner,TInt aResourceId,VA_LIST aList);
	IMPORT_C void InfoMsgWithDuration(const TDesC& aDes, TTimeIntervalMicroSeconds32 aDuration);
	IMPORT_C void InfoMsgWithDuration(TInt aResourceId, TTimeIntervalMicroSeconds32 aDuration,...);
	IMPORT_C void InfoMsgWithDuration(TInt aResourceId, TTimeIntervalMicroSeconds32 aDuration, VA_LIST aList);
	IMPORT_C void InfoMsgWithAlignmentAndDuration(TGulAlignment aCorner,const TDesC& aDes, TTimeIntervalMicroSeconds32 aDuration);
	IMPORT_C void InfoMsgWithAlignmentAndDuration(TGulAlignment aCorner,TInt aResourceId, TTimeIntervalMicroSeconds32 aDuration,...);
	IMPORT_C void InfoMsgWithAlignmentAndDuration(TGulAlignment aCorner,TInt aResourceId, TTimeIntervalMicroSeconds32 aDuration,VA_LIST aList);
	IMPORT_C void InfoMsgCancel();
	IMPORT_C void VerboseInfoMsg(const TDesC& aDes);
public: // Internal to Symbian
	IMPORT_C void SetVerboseInfoReporting(TBool aVerbose);
public:
	IMPORT_C void BusyMsgL(const TDesC& aDes);
	IMPORT_C void BusyMsgL(const TDesC& aDes,TGulAlignment aCorner);
	IMPORT_C void BusyMsgL(TInt aResourceId);
	IMPORT_C void BusyMsgL(const TDesC& aDes,TTimeIntervalMicroSeconds32 aInitialDelay);
	IMPORT_C void BusyMsgL(const TDesC& aDes,TGulAlignment aCorner,TTimeIntervalMicroSeconds32 aInitialDelay);
	IMPORT_C void BusyMsgL(TInt aResourceId,TTimeIntervalMicroSeconds32 aInitialDelay);
	IMPORT_C void BusyMsgCancel();
	
	IMPORT_C TBool ConfirmLossOfAllChangesL() const;
	IMPORT_C static TBool QueryWinL(const TDesC& aFirstLine,const TDesC& aSecondLine);
	IMPORT_C TBool QueryWinL(TInt aFirstLineId,TInt aSecondLineId=0) const;
	IMPORT_C static void InfoWinL(const TDesC& aFirstLine,const TDesC& aSecondLine);
	IMPORT_C void InfoWinL(TInt aFirstLineId,TInt aSecondLineId=0) const;
	IMPORT_C void SetQueryDialog(MEikInfoDialog* aQueryDialog);
	IMPORT_C void SetInfoDialog(MEikInfoDialog* aInfoDialog);
	IMPORT_C void SetRequestQueryDialogFunc(TRequestDialogFunc aQueryDialogFunc);
	IMPORT_C void SetRequestInfoDialogFunc(TRequestDialogFunc aInfoDialogFunc);

	IMPORT_C void AllocInfoMsg();
	IMPORT_C void WservAllocInfoMsg();
	IMPORT_C void FservAllocInfoMsg();
	//
	IMPORT_C static void Beep();

/**
 * Creates a bitmap, loading the image bitmap from aFileName and identified by aId.
 * Returns a pointer to the bitmap and transfers ownership.
 * If a zero length descriptor is passed as aFileName the Avkon resource file will be used.
 * If the wildcard '*' is passed as aFileName the default application resource file will be
 * used.
 *
 * @param aFilename		nme of bitmap ".mbm" file to use (see above)
 * @param aId			mbm file identifier (from corresponding .mbg file)
 * @return				bitmap pointer (client obtains ownership)
 */
	IMPORT_C CWsBitmap* CreateBitmapL(const TDesC& aFileName,TInt aId);
	IMPORT_C CGulIcon* CreateIconL(const TDesC& aFileName,TInt aBitmapId,TInt aMaskId=-1);
	IMPORT_C static CGulIcon* CreateIconFromMaskedBitmapL(const CApaMaskedBitmap& aApaMaskedBitmap);
public: // Internal to Symbian
	IMPORT_C void SetDebugKeys(MEikDebugKeys* aDebugKeys);
	IMPORT_C void LaunchPopupMenuL(TInt aResourceId,const TPoint& aTargetPos,TPopupTargetPosType aTargetType=EPopupTargetTopLeft,const CEikHotKeyTable* aHotKeyTable=NULL);
public:
	IMPORT_C static void AddWindowShadow(CCoeControl* aWinArea);
	IMPORT_C RAnimDll& ClockDllL();
	//
	IMPORT_C CParaFormatLayer* SystemSingleLineParaFormatLayerL();
	IMPORT_C CParaFormatLayer* SystemParaFormatLayerL();
	IMPORT_C CCharFormatLayer* SystemCharFormatLayerL();
	IMPORT_C static CParaFormatLayer* NewDefaultSingleLineParaFormatLayerL();
	IMPORT_C static CParaFormatLayer* NewDefaultParaFormatLayerL();
	IMPORT_C static CCharFormatLayer* NewDefaultCharFormatLayerL();
	IMPORT_C static void GetPrinterNamesL(CPrinterModelList* aModelNameList,CDesCArray& aPrinterNameList);
  	//
	inline CEikAppUi* EikAppUi() const;
	IMPORT_C void AddDialogLikeControlToStackL(CCoeControl* aControl);
	IMPORT_C void AddAlertDialogLikeControlToStackL(CCoeControl* aControl);
	IMPORT_C void RemoveFromStack(CCoeControl* aControl);
	IMPORT_C void AddSleepingDialogToStackL(CCoeControl* aControl);
	IMPORT_C void AddSleepingAlertDialogToStackL(CCoeControl* aControl);
	IMPORT_C void RouseSleepingDialog(CCoeControl* aControl,TBool aRoused);
	//
	IMPORT_C void DrawCursor(const CCoeControl* aControl,const TPoint& aPosition,TInt aWidth);
	IMPORT_C void DrawCursor(const CCoeControl* aControl,const TPoint& aPosition,TInt aWidth,TInt aAscent,TInt aHeight);
	IMPORT_C void HideCursor(const CCoeControl* aControl);
	//
	IMPORT_C void UpdateTaskNameL();
	//
	IMPORT_C void BringForwards(TBool aForwards,TInt aPriority=ECoeWinPriorityAlwaysAtFront);
	IMPORT_C void SetAutoForwarding(TBool aForwarding);
public: // Internal to Symbian
	IMPORT_C TPtrC KeyPressLabel(TInt aIndex) const;
public:
	IMPORT_C CPrintSetup* NewDefaultPrintSetupL();
public: // Internal to Symbian
	IMPORT_C void DisplayTaskList();
	IMPORT_C void DismissTaskList();
	IMPORT_C void SendEventToEikonServer(TInt aEvent,const TAny* aPtr,TInt aLength);
public:
	IMPORT_C void SetBusy(TBool aBusy);
	IMPORT_C TBool IsBusy() const;
	IMPORT_C void SetSystem(TBool aSystem);
	IMPORT_C TBool IsSystem() const;
	IMPORT_C void SetDocNameIsAFile(TBool aDocNameIsAFile);
	IMPORT_C TBool DocNameIsAFile() const;
	IMPORT_C void SetRespondsToShutdownEvent(TBool aRespondsToShutdownEvent);
	IMPORT_C TBool RespondsToShutdownEvent() const;
	IMPORT_C void SetRespondsToSwitchFilesEvent(TBool aRespondsToSwitchFilesEvent);
	IMPORT_C TBool RespondsToSwitchFilesEvent() const;
	
	IMPORT_C TEikVirtualCursor& VirtualCursor();

	IMPORT_C void NotifyIdleErrorWhileRedrawing(TInt aError);
	IMPORT_C void NotifyIdleError(TInt aError,TInt aContextRid);
	IMPORT_C void HandleErrorWithContext(TInt aError,TInt aContextRid);

	IMPORT_C MEikAppUiFactory* AppUiFactory() const;
	IMPORT_C MEikAppUiFactory* AppUiFactory(const CEikAppUi& aAppUi) const;
public: // Internal to Symbian
	IMPORT_C void SetAppUiFactoryL(MEikAppUiFactory* aAppUiFactory); // DLL decoupling between core and core controls
	IMPORT_C void AddAppUiFactoryL(MEikAppUiFactory* aAppUiFactory);
	IMPORT_C void RemoveAppUiFactory();

public:
	IMPORT_C TInt AddLibraryL(TCreateByTypeFunction aControlFactory, TFileName* aResourceFile);
	inline TInt AddLibraryL(TCreateByTypeFunction aControlFactory);
	inline TInt AddLibraryL(TFileName* aResourceFile);
	IMPORT_C void RemoveLibrary(TCreateByTypeFunction aControlFactory, TInt aResourceFileOffset);
	inline void RemoveLibrary(TCreateByTypeFunction aControlFactory);
	inline void RemoveLibrary(TInt aResourceFileOffset);

	inline TChar NudgeCharMinus() const;
	inline TChar NudgeCharPlus() const;

	inline CColorList& ColorList() const;
	inline TRgb Color(TLogicalColor aLogicalColor) const;
	inline void SetColor(TLogicalColor aLogicalColor, TRgb aColor);
	IMPORT_C TRgb ControlColor(TLogicalColor aLogicalColor,const CCoeControl& aControl) const;
	inline CColorArray& CustomColorArray() const;

	// Avkon color support
	IMPORT_C static TRgb AvkonColor(TInt aIndex);

public: // Internal to Symbian
	inline void SetCDlgDialogFactory(MEikCDlgDialogFactory* aDialogFactory);// DLL decoupling between Controls and Common Dialogs
																			// Pass hot keys to the factory
																			// which launches the appropriate dialog
	inline void SetPrintDialogFactory(MEikPrintDialogFactory* aDialogFactory);	// DLL decoupling between Controls and Print Dialogs
	inline void SetFileDialogFactory(MEikFileDialogFactory* aDialogFactory);	// DLL decoupling between Controls and File Dialogs
	inline void SetIrFactory(MEikIrFactory* aIrFactory); // DLL decoupling between core and Ir send / receive
	inline MEikCDlgDialogFactory* CDlgDialogFactory() const;
	inline MEikPrintDialogFactory* PrintDialogFactory() const;
	inline MEikFileDialogFactory* FileDialogFactory() const;
	inline MEikIrFactory* IrFactory() const;
	CArrayFix<TCreateByTypeFunction>* ControlFactoryFuncArray() const;
	inline void SetZoomFactor(TZoomFactor& aZoomFactor);
	inline TZoomFactor ZoomFactor() const;
	inline TInt StatusPaneCoreResId() const;
	inline void SetStatusPaneCoreResId(TInt aStatusPaneCoreResId);
	IMPORT_C void AddAutoMenuTitleL(CEikAutoMenuTitle* aTitle);
	inline CEikAutoMenuTitleArray* AutoMenuTitleArray() const;
	//
public:
	IMPORT_C TDisplayMode DefaultDisplayMode() const;
public: // Do not use
	IMPORT_C void SetExtension(CBase* aExtension);
	inline CBase* Extension() const;
public: // Internal to Symbian
	// framework functions
	IMPORT_C void HandleError(TInt aError);
public: // internal
	IMPORT_C void WriteInternalStateOfStackedControlsL();
public:
	void UpdateColorListL();
	void PostAppUiDestroy();
	void PostAppUiInitializeL();
protected: // Internal to Symbian
	// framework functions
	IMPORT_C void DestroyEnvironment();
private: // framework functions
	IMPORT_C void DestroyScreen();
	IMPORT_C void InitSystemFontsL();
	IMPORT_C TInt ResourceFileVersionNumber() const;
	IMPORT_C void Reserved_1();
	IMPORT_C void Reserved_2();
private: // from MApaAppStarter
	IMPORT_C TThreadId StartAppL(const CApaCommandLine& aCommandLine);
protected:
	friend class CEikServAppUi;
private: // new functions
	void InitSystemResourceFileL();
	void InitPrivateResourceFileL();
	void InitInfoMsgL();
	void PrepareBusyMsgL();
	void InitAlertWinL();
	void SetUpFepL();
	TErrorHandlerResponse PrepareToHandleError(TInt aError);
	void DoHandleError(TErrorHandlerResponse aType);
	static TInt IdleErrorCallBack(TAny* aThis);
	void InitColorsL();
	void LoadParserListL();
	void LoadLibrariesL();
	void CloseLibraries();
	MEikInfoDialog* QueryDialog();
	MEikInfoDialog* InfoDialog();
	TRequestDialogFunc RequestQueryDialogFunc();
	TRequestDialogFunc RequestInfoDialogFunc();
	void SetAppReady();
	void DisplayGlobalNote(const TDesC& aMsg1, const TDesC& aMsg2);
	void SetCommandLineDebugMemFail(TPtrC8& aTail);
private:
	class TEikAppUiFactory
		{
	public:
		MEikAppUiFactory*	iFactory;
		CEikAppUi*			iAppUi;
		};
private:
	TInt iEikonEnvFlags;
	TInt iForwardsCount;
	TInt iBusyCount;
	CEikProcess* iProcess;
	RAnimDll* iClockDll;
//	CArrayPtr<CFont>* iFontArray;
	CArrayFixFlat<TAknSystemFont>* iFontArray;
	CEikInfoMsgWin* iInfoMsgWin;
	CEikBusyMsgWin* iBusyMsgWin;
	MEikAlertWin* iAlertWin;
	TInt iSystemResourceFileOffset;
	HBufC8* iKeyPressLabels;
	CParaFormatLayer* iSingleLineParaFormatLayer;
	CParaFormatLayer* iParaFormatLayer;
	CCharFormatLayer* iCharFormatLayer;
	const CCoeControl* iCursorWindow;
	TInt iEditableControlStandardHeight;
	CApaWindowGroupName* iWgName;
	CEikErrorIdler* iErrorIdler;
	TInt iPrivateResourceFileOffset;
	CColorList* iColorList;
	CEikPictureFactory* iPictureFactory;
	TBuf<2> iNudgeChars;
	MEikInfoDialog* iQueryDialog;
	MEikInfoDialog* iInfoDialog;
	TRequestDialogFunc	iQueryDialogFunc;
	TRequestDialogFunc	iInfoDialogFunc;
	CArrayFix<RLibrary>* iLibArray;
	CArrayFix<TCreateByTypeFunction>* iControlFactoryFuncArray;
	CArrayFix<TInt>* iResourceFileOffsetArray;
	TBool iAlertWinInitialized;
	MEikDebugKeys* iDebugKeys;
	MEikCDlgDialogFactory* iCDlgDialogFactory;
	MEikPrintDialogFactory* iPrintDialogFactory;
	MEikFileDialogFactory* iFileDialogFactory;
	CArrayFix<TEikAppUiFactory>* iAppUiFactoryArray;
	MEikIrFactory* iIrFactory;
	CArrayPtr<CEikLibrary>* iLibraries;
	TInt iEmbeddedAppLevel;
	TInt iAutoLoadedResourceFiles;
	TInt iAutoLoadedControlFactories;
	TZoomFactor iZoomFactor;
	CBase* iExtension;
	TInt iStatusPaneCoreResId;
	CEikAutoMenuTitleArray* iAutoMenuTitleArray;
	TEikVirtualCursor iVirtualCursor;
	CEikLogicalBorder* iLogicalBorder;
	CEikLafEnv* iLafEnv;
	CArrayPtrFlat<CFbsBitmap>* iBitmapArray;
	CEikEnvExtra* iEikEnvExtra; // used to be TInt iSpare1;
	HBufC* iOOMErrorText;		// used to be TInt iSpare2;
	TInt iSpare3;
	TInt iSpare4;
	};

class MEikInfoDialog
	{
public:
	virtual TBool RunDlgLD(TInt aResource, const TDesC& aTitle, const TDesC& aMsg) = 0;
	};

class MEikAlertWin
	{
public:
	virtual void ConstructL() = 0;
	virtual void RunAlert(const TDesC& aTitle, const TDesC& aMsg) = 0;
	virtual void Release() = 0;
	virtual CEikDialog* AsEikDialog() = 0;
	inline const CEikDialog* AsEikDialog() const;
	};

class MEikDebugKeys
	{
public:
	virtual void ConstructL() = 0;
	virtual void Release() = 0;
	};

inline CEikonEnv* CEikonEnv::Static()
	{ return((CEikonEnv*)(CCoeEnv::Static())); }
inline TInt CEikonEnv::EditableControlStandardHeight() const
	{ return(iEditableControlStandardHeight); }
inline CEikProcess* CEikonEnv::Process() const
	{ return(iProcess); }
inline CEikAppUi* CEikonEnv::EikAppUi() const
	{ return((CEikAppUi*)iAppUi); }
inline const MEikAlertWin* CEikonEnv::Alert() const
	{ return(iAlertWin); }
inline TChar CEikonEnv::NudgeCharMinus() const
	{return(iNudgeChars[0]);}
inline TChar CEikonEnv::NudgeCharPlus() const
	{return(iNudgeChars[1]);}
inline TRgb CEikonEnv::Color(TLogicalColor aLogicalColor) const
	{return ColorList().Color(aLogicalColor); }
inline CColorArray& CEikonEnv::CustomColorArray() const
	{return *(ColorList().ColorArray(TUid::Uid(KEikCustomColorsArrayValue)));}
inline CColorList& CEikonEnv::ColorList() const
	{__ASSERT_DEBUG(iColorList,User::Invariant()); return *iColorList; }
inline void CEikonEnv::SetColor(TLogicalColor aLogicalColor, TRgb aColor)
	{ ColorList().SetColor(aLogicalColor, aColor); }
inline void CEikonEnv::SetCDlgDialogFactory(MEikCDlgDialogFactory* aDialogFactory)
	{iCDlgDialogFactory=aDialogFactory;}
inline void CEikonEnv::SetPrintDialogFactory(MEikPrintDialogFactory* aDialogFactory)
	{iPrintDialogFactory=aDialogFactory;}
inline void CEikonEnv::SetFileDialogFactory(MEikFileDialogFactory* aDialogFactory)
	{iFileDialogFactory=aDialogFactory;}
inline void CEikonEnv::SetIrFactory(MEikIrFactory* aIrFactory)
	{iIrFactory=aIrFactory;}
inline MEikCDlgDialogFactory* CEikonEnv::CDlgDialogFactory() const
	{return iCDlgDialogFactory;}
inline MEikPrintDialogFactory* CEikonEnv::PrintDialogFactory() const
	{return iPrintDialogFactory;}
inline MEikFileDialogFactory* CEikonEnv::FileDialogFactory() const
	{return iFileDialogFactory;}
inline MEikIrFactory* CEikonEnv::IrFactory() const
	{return iIrFactory;}
inline TInt CEikonEnv::AddLibraryL(TCreateByTypeFunction aControlFactory)
	{return(AddLibraryL(aControlFactory, NULL));}
inline TInt CEikonEnv::AddLibraryL(TFileName* aResourceFile)
	{return(AddLibraryL(NULL, aResourceFile));}
inline void CEikonEnv::RemoveLibrary(TCreateByTypeFunction aControlFactory)
	{RemoveLibrary(aControlFactory, NULL);}
inline void CEikonEnv::RemoveLibrary(TInt aResourceFileOffset)
	{RemoveLibrary(NULL, aResourceFileOffset);}
inline void CEikonEnv::SetZoomFactor(TZoomFactor& aZoomFactor)
	{iZoomFactor=aZoomFactor;}
inline TZoomFactor CEikonEnv::ZoomFactor() const
	{return iZoomFactor;}
/**
 * @internal
 * @deprecated
 */
inline CBase* CEikonEnv::Extension() const
	{return iExtension;}
/**
 * @internal
 */
inline TInt CEikonEnv::StatusPaneCoreResId() const
	{return iStatusPaneCoreResId;}
/**
 * @internal
 */
inline void CEikonEnv::SetStatusPaneCoreResId(TInt aStatusPaneCoreResId)
	{iStatusPaneCoreResId=aStatusPaneCoreResId;}
inline CEikAutoMenuTitleArray* CEikonEnv::AutoMenuTitleArray() const
	{return iAutoMenuTitleArray;}

inline const CEikDialog* MEikAlertWin::AsEikDialog() const
	{return (const CEikDialog*)const_cast<MEikAlertWin*>(this)->AsEikDialog();}


//this is to save the printer port in inifile.  This is used by eikon print dialogs and shell's default printer dialog
enum TEikPortFlag
	{
	ESerialPort =0x01,
	EParallelPort =0x02,
	EIrdaPort= 0x04,
	EFilePort=0x08,
	EViaPCPort=0x10
	};

IMPORT_C void InternalizeL(TEikPortFlag& aThing,RReadStream& aStream);
inline RWriteStream& operator<<(RWriteStream& aStream,const TEikPortFlag& aThing)
	{aStream.WriteUint8L(aThing);return aStream;}
inline RReadStream& operator>>(RReadStream& aStream,TEikPortFlag& aThing)
	{InternalizeL(aThing,aStream);return aStream;}

#endif
