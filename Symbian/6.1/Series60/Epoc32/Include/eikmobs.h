// EIKMOBS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKMOBS_H__)
#define __EIKMOBS_H__

#if !defined(__EIKCMOBS_H__)
#include <eikcmobs.h>
#endif

#if !defined(__W32STD_H__)
#include <w32std.h>
#endif

#if !defined(__COEDEF_H__)
#include <coedef.h>
#endif

class CCoeControl;
class CEikMenuPane;
class CEikMenuBar;
class CEikHotKeyTable;
class TPoint;

class MEikMenuObserver : public MEikCommandObserver
	{
public:
	enum TMenuType
		{
		EMenuPane,
		EMenuBar
		};
public:
	IMPORT_C virtual void HandleAttemptDimmedSelectionL(TInt aCommandId);
	IMPORT_C virtual TBool CheckHotKeyNotDimmedL(TInt aCommandId);
	IMPORT_C virtual void RestoreMenuL(CCoeControl* aMenuControl,TInt aResourceId,TMenuType aType);
	IMPORT_C virtual void DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane);
	IMPORT_C virtual void DynInitMenuBarL(TInt aResourceId,CEikMenuBar* aMenuBar);
	IMPORT_C virtual void HandleSideBarMenuL(TInt aResourceId,const TPoint& aPos,TInt aModifiers,const CEikHotKeyTable* aTable);
	IMPORT_C virtual void OfferKeyToAppL(const TKeyEvent& aKeyEvent,TEventCode aType);
	virtual void SetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis)=0;
private:
	IMPORT_C virtual void Reserved_1_MenuObserver();
	};

class MEikAutoMenuObserver : public MEikMenuObserver
	{
public:
	virtual TKeyResponse OfferHotKeyL(const TKeyEvent& aKeyEvent,TEventCode aType)=0;
public: // from MEikMenuObserver
	IMPORT_C void SetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis);
private:
	IMPORT_C virtual void Reserved_1_MenuObserver();
	};

#endif
