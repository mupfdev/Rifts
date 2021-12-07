// AKNEDSTS.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//
 
#if !defined(__EIKEDSTS_H__)
#define __EIKEDSTS_H__

#if !defined(__FEPBASE_H__)
#include <FEPBASE.H>
#endif

#if !defined(__AKNEDSTSOBS_H__)
#include <AKNEDSTSOBS.H>
#endif

#if !defined(__UIKON_HRH__)
#include <UIKON.HRH>
#endif

#include <frmtlay.h>

//
//	class TAknEditorCaseState - data structure to store current state of case
//  modes
//
class TAknEditorCaseState
	{
public:
	enum TCaseStateFlags
		{
		EFlagTextEnteredInCurrentCase	=0x00000001,
		EFlagInitialiseRequired			=0x00000002,
		EFlagSupressAutoUpdateCase		=0x00000004
		};
public:
	IMPORT_C TAknEditorCaseState();
	IMPORT_C void SetCurrentCase(TUint aCase);
	IMPORT_C void SetPreviousCase(TUint aCase);
	IMPORT_C void SetPreviousCaseUsedToEnterText(TUint aCase);

	IMPORT_C TUint CurrentCase() const;
	IMPORT_C TUint PreviousCase() const;
	IMPORT_C TUint PreviousCaseUsedToEnterText() const;

	// flags
	IMPORT_C void SetFlag(TCaseStateFlags aFlag);
	IMPORT_C void ClearFlag(TCaseStateFlags aFlag);
	IMPORT_C TBool IsFlagSet(TCaseStateFlags aFlag) const;

private:
	TUint8 iCurrentCase;
	TUint8 iPreviousCase;
	TUint8 iPreviousCaseUsedToEnterText;
	TUint8 iFlags;
	};


class MEikCcpuEditor;
class CEikButtonGroupContainer;
class CEikMenuBar;
class MObjectProvider;
//
// class CAknEdwinState
//
class CAknEdwinState : public MCoeFepAwareTextEditor_Extension1::CState
	{
public:
	struct SEditorCbaState
		{
		CEikButtonGroupContainer* iCurrentCba;
		TInt iLeftSoftkeyCommandId;
		TInt iRightSoftkeyCommandId;
		};
public:
	virtual ~CAknEdwinState();
	CAknEdwinState(MEikCcpuEditor* aCcpuState);
	IMPORT_C CAknEdwinState();
public:
	IMPORT_C void SetObserver(MAknEdStateObserver* aObserver);
	IMPORT_C void ReportAknEdStateEventL(MAknEdStateObserver::EAknEdwinStateEvent aEventType);
public:
	// Accessors
	IMPORT_C TInt Flags() const;
	IMPORT_C TInt DefaultInputMode() const;
	IMPORT_C TInt CurrentInputMode() const;
	IMPORT_C TInt PermittedInputModes() const;
	IMPORT_C TInt DefaultCase() const;
	IMPORT_C TInt CurrentCase() const;
	IMPORT_C TInt PermittedCases() const;
	IMPORT_C TInt DefaultLanguage() const;
	IMPORT_C TInt SpecialCharacterTableResourceId() const;
	IMPORT_C TAknEditorNumericKeymap NumericKeymap() const;
	IMPORT_C TCursorSelection CurrentInlineEditSpan() const;
	IMPORT_C SEditorCbaState& CbaState();
	IMPORT_C CEikMenuBar* MenuBar() const;
	IMPORT_C MEikCcpuEditor* CcpuState() const;
	IMPORT_C MObjectProvider* ObjectProvider() const;
	IMPORT_C TLanguage LocalLanguage() const;

	// Setters
	IMPORT_C void SetFlags(TInt aFlags);
	IMPORT_C void SetDefaultInputMode(TInt aInputMode);
	IMPORT_C void SetCurrentInputMode(TInt aInputMode);
	IMPORT_C void SetPermittedInputModes(TInt aInputModes);
	IMPORT_C void SetDefaultCase(TInt aCase);
	IMPORT_C void SetCurrentCase(TInt aCase);
	IMPORT_C void SetPermittedCases(TInt aCases);
	IMPORT_C void SetDefaultLanguage(TInt aLanguage);
	IMPORT_C void SetSpecialCharacterTableResourceId(TInt aResourceId);
	IMPORT_C void SetNumericKeymap(TAknEditorNumericKeymap aKeymap);
	IMPORT_C void SetInlineEditSpan(TCursorSelection aCurrentInlineEditSpan);
	IMPORT_C void SetCba();
	IMPORT_C void SetMenu();
	IMPORT_C void SetObjectProvider(MObjectProvider* aObjectProvider);
	IMPORT_C void SetLocalLanguage(TLanguage aLanguage);

	// non exported setters
	void SetCcpuState(MEikCcpuEditor* aCcpuEditor);

private:
	IMPORT_C void SetCurrentCaseWithNoInitialisation(TInt aCase);
	IMPORT_C TAknEditorCaseState& CaseState();

private:
	void CheckLRCursorAndT9Consistency();

private:
	friend class CT9FepControl;  // dependency to be removed?
	friend class CT9FepCaseManager;  // dependency to be removed?

private:
	TInt iFlags;
	TInt iDefaultInputMode;
	TInt iCurrentInputMode;
	TInt iPermittedInputModes;
	
	TInt iDefaultCase;
	TAknEditorCaseState iCaseState;
	TInt iPermittedCases;

	TLanguage iLocalLanguage;
	TInt iSpecialCharacterTableResourceId;
	TAknEditorNumericKeymap iNumericKeymap;
	TCursorSelection iCurrentInlineEditSpan;

	SEditorCbaState iCbaState;
	CEikMenuBar* iMenu;

	// to hold c/c/p/u info about an editor
	MEikCcpuEditor* iCcpuState;
	MObjectProvider* iObjectProvider;

	MAknEdStateObserver* iObserver;

	// Spare member data for keeping BC
	TInt iSpare_1;
	TInt iSpare_2; // Unused
	};


#endif





