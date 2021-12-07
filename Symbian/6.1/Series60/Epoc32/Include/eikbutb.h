// EIKBUTB.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKBUTB_H__)
#define __EIKBUTB_H__

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#if !defined(__UIKON_HRH__)
#include <uikon.hrh>
#endif
#include <lafpublc.h>

class TEikButtonCoordinator;

enum TButtonBehavior
	{
	EEikButtonStaysClear=EEikButStaysClear,
	EEikButtonStaysSet=EEikButStaysSet,
	EEikButtonLatches=EEikButLatches,
	EEikButtonReportsOnPointerDown=EEikButReportOnPointerDown
	};

class CEikButtonBase : public CEikBorderedControl
	{
public:
	IMPORT_C CEikButtonBase();
	IMPORT_C ~CEikButtonBase();
public:
	enum TState
		{
		EClear		  	=0,
		ESet			=1,
		EIndeterminate  =2
		};
public: // new functions
	IMPORT_C TState State() const;
	IMPORT_C void SetState(TState aState);
	IMPORT_C virtual void Animate();
	IMPORT_C void SetCoordinator(TEikButtonCoordinator* aButCoord);
	IMPORT_C void SetBehavior(TButtonBehavior aBehavior);
	IMPORT_C void SetIgnoreNextPointerUp();
protected:
	enum TDrawState
		{
		EDrawClear					=SLafButtonBase::EDrawClear,
		EDrawSet					=SLafButtonBase::EDrawSet,
		EDrawIndeterminate			=SLafButtonBase::EDrawIndeterminate,
		EDrawClearPressed			=SLafButtonBase::EDrawClearPressed,
		EDrawSetPressed				=SLafButtonBase::EDrawSetPressed,
		EDrawIndeterminatePressed	=SLafButtonBase::EDrawIndeterminatePressed
		};
protected: // new functions
	IMPORT_C void SetReportOnPointerDown();
	IMPORT_C TDrawState DrawState() const;
	IMPORT_C TBool IsPressed() const;
	IMPORT_C void SetAllowTristate();
	IMPORT_C void CopyDrawStateTo(CEikButtonBase* aTargetButton) const;
public:	// from CCoeControl
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // new function
	IMPORT_C virtual void StateChanged();
	IMPORT_C virtual void Reserved_3();
public: // framework
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C TCoeInputCapabilities InputCapabilities() const; // not available before Release 006
private: // internal use only
	TBool ClickCompleted();
private:
	enum { EIgnoreNextPointerUp=0x1000 };
protected:
	TInt iButFlags;
private:
	TEikButtonCoordinator* iButCoord;
	TInt iSpare;
	};

//
// Button coordinator class
//

class TEikButtonCoordinator
	{
public:
	IMPORT_C TEikButtonCoordinator();
	IMPORT_C void SetChosenButton(CEikButtonBase* aChosenButton);		
private:
	CEikButtonBase* iChosenButton;
	};		 

#endif
