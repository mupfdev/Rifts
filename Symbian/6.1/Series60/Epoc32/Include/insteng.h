// INSTENG.H
// Copyright (c) 1997-1999 Symbian Ltd. All rights reserved.
//
// Installer engine, (handles installation & removal of SIS files)
//

#if !defined(__INSTENG_H__)
#define __INSTENG_H__

// ===========================================================================
// INCLUDES
// ===========================================================================

#include <e32base.h>
#include <badesca.h>

#include <instenum.h>
#include <instform.h>

class CPKIXValidationResult;
class CPKIXCertChain;

// ===========================================================================
// CONSTANTS
// ===========================================================================

// default to use as engine priority for CIdle initialisation
const TInt KInstallEnginePriority=-101;
// location of SIS stub files
_LIT(KInstallSystemPath,"c:\\system\\install\\");
_LIT(KWildcards,"*.*");

#ifdef _UNICODE
	const TUid KInstengUid = { 0x100042AB };
#else
	const TUid KInstengUid = { 0x100005b9 };
#endif


// ===========================================================================
// INTERFACES
// ===========================================================================

class CInstallationSignatureInfoReader;


class MInstUIHandler
// This represents the User Interface handler for the install engine
// The higher code should provide one of these interfaces for the engine
// to use for a UI
	{
	public:
		virtual TBool DisplayInstallDialogL(const TDesC& aAppName, TSISType aType,
			TInt aMajor,TInt aMinor,TInt build,
			TBool aValidationProblem, 
			const CInstallationSignatureInfoReader* aSigReader)=0;
		virtual TInt DisplayLanguageDialogL(const TDesC& aAppName,
			const CArrayFix<TLanguage>& aLanguages)=0;
		virtual TChar DisplayDriveDialogL(const TDesC& aAppName,TInt aSize,
										  const CArrayFix<TChar>& aDriveLetters,
										  const CArrayFix<TInt>& aDriveSpaces)=0;
		virtual TInstFileTextOption DisplayTextDialogL(
			TInstFileTextOption aOption,
			const TDesC& aAppName,TPtr& aText)=0;
		virtual TBool DisplayQuestionDialogL(TInstQuestionDialogType aType,
											 const TDesC& aAppName,
											 TInt aMajor=0,
											 TInt aMinor=0,
											 TInt aExistMajor=0,
											 TInt aExistMinor=0)=0;
		virtual TBool DisplayOptionsDialogL(const TDesC& aAppName,
			const CDesCArray& aOptions,
			CArrayFix<TBool>& aSelections)=0;
		virtual void DisplayErrorDialogL(TInstErrorDialogType aMsgType,
			const TDesC& aAppName=_L(""),
			TInt aMajor=0,TInt aMinor=0,
			TInt aReqMajor=0,TInt aReqMinor=0)=0;
		virtual void HandleInstallEventL(TInstallEngineEvent aEvent, TInt aValue=0)=0;
		virtual TBool DisplaySecurityWarningDialogL(TSignatureValidationResult aSigValidationResult,
			const CPKIXValidationResult* aCertValidationResult, const CInstallationSignatureInfoReader* aSigReader, 
			TBool aInstallAnyway) = 0;
		virtual TInstAbortRetrySkip DisplayAbortRetrySkipDialogL(const TDesC& aAppName,
											 TInt error) = 0;
		virtual TBool DisplayInUseDialogL(const TDesC& aAppName,
			const CDesCArray& aComponents) = 0;
	};

class CResult;

class MInstallCondVariableSupplier
// This supplies variables to the CInstallationConditionInfoReader class
// which are used when evaluating IF condition statements
	{
	public:
		virtual CResult* GetVariableLC(TVariableToken aVariableId)=0;
		virtual CResult* GetCapabilityLC(TInt aCapID)=0;
		virtual CResult* GetCapabilityLC(TInt aAppUID, TInt aCapID)=0;
	};

// ===========================================================================
// CLASS DEFINITIONS
// ===========================================================================

class CInstaller;
class CUninstaller;
class CInstallationFile;
class CInstVarSupplier;

class CInstallEngine : public CBase, public MInstallCondVariableSupplier
// The main install engine class for installing & removing SIS files
	{
	public:	// public methods available at DLL interface
		IMPORT_C static CInstallEngine* NewForInstallL(TInt aPriority,
			const TDesC& aFileName,
			MInstUIHandler& aUIHandler,TBool aAutoDelete,
			TLanguage aLanguage);
		IMPORT_C static CInstallEngine* NewForUnInstallL(TInt aPriority,
			const TDesC& aFileName,
			MInstUIHandler& aUIHandler);
		IMPORT_C void StartL();
		IMPORT_C void Halt();
		IMPORT_C void RestartL();
		IMPORT_C void CancelL();
		IMPORT_C TBool InstallationInProgress() const;
		IMPORT_C CInstallationFile& InstallationFile() const;
	public: // from MInstallCondVariableSupplier
		CResult* GetVariableLC(TVariableToken aVariableId);
		CResult* GetCapabilityLC(TInt aCapID);
		CResult* GetCapabilityLC(TInt aAppUID, TInt aCapID);
	public: // public methods available to other objects within insteng.dll
		~CInstallEngine();
		void SetOptionL(TInt aOptionNumber, TBool aValue);
		void SetAbortFlag(TBool aAbort);
		TInt AbortFlag();
		void HandleFinishL(TInstallEngineEvent aValue);
		inline TBool IsRecursive() const;
		inline void SetParentInstaller(CInstaller* parent);
		inline CInstaller* ParentInstaller();
		inline CInstVarSupplier* InstVarSupplier();
	public:
		MInstUIHandler* iUIHandler;
	private: // private enums
		enum TInstallEngineState
			{
			EInstallCheckForPartialInstall,
			EInstallCheckInstallerVersion,
			EInstallCheckFlags,
			EInstallCheckDigitalSignature,
			EInstallShowAppName,
			EInstallCheckAppVersion,
			EInstallCheckDependencies,
			EInstallChooseLanguage,
			EInstallSelectDrive,
			EInstallShutdownApps,
			EInstallStartFiles,
			EInstallContinueWithFiles,
			EInstallHandleFinish
			};
	private: // private methods
		CInstallEngine();
		void ConstructL(TInt aPriority,const TDesC& aFileName,MInstUIHandler& aUIHandler,TBool aInstalling, TBool aAutoDelete=EFalse,TLanguage aLanguage=ELangEnglish);
		// idle object methods
		static TInt IdleCallBack(TAny *anObj);
		TBool DoRun();
		void DoNotifyObserverL(TInstallEngineEvent aEvent, TInt aValue=0);
		MInstUIHandler* TopLevelObserver() const;
		void HandleLeaveErrorL(TInt aError);
	private:
		enum TInstEngWaitState
			{
			EInstEngReady,
			EInstEngInputRequested,
			EInstEngWaitingForInput,
			};
	private: // private members
		CIdle* iIdler;
		CInstaller* iInstaller;
		CUninstaller* iUninstaller;
		CInstaller* iParentInstaller;
		TInstallEngineState iState;
		TBool iInstallInProgress;
		TBool iContinuingPartial;
		CInstVarSupplier* iInstVarSupplier;
		TInt iAppsToShutdown;
		TInt iShutdownCount;
		CInstallationSignatureInfoReader* iSigReader;
		CPKIXValidationResult* iCertValidationResult;
	};

#include <insteng.inl>

#endif
