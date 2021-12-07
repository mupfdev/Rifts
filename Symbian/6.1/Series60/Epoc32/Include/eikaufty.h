// EIKAUFTY.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
// Defines mix-in interace to break dependencey of Eikon Application UI 
// on controls

#if !defined(__EIKAUFTY_H__)
#define __EIKAUFTY_H__

#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__EIKDEF_H__)
#include <eikdef.h>
#endif

#include <coemop.h>

class CEikHotKeyTable;
class CEikMenuBar;
class CEikMenuPane;
class CEikCommandButton;
class CEikToolBar;
class CEikButtonGroupContainer;
class CEikAppUi;
class CEikonEnv;
class CEikStatusPane;

class MEikAppUiFactory : public MObjectProvider
	{
public:
	virtual void CreateResourceIndependentFurnitureL(CEikAppUi* aAppUi) =0;
	virtual TRect ClientRect() = 0;
	virtual void ReadAppInfoResourceL(TInt aResourceFileOffset,CEikAppUi* aAppUi) = 0;
	virtual void LaunchPopupMenuL(
									TInt aResourceId,
									const TPoint& aTargetPos,
									TPopupTargetPosType aTargetType,
									const CEikHotKeyTable* aHotKeyTable,
									CEikAppUi* aAppUi) = 0;

	virtual void DoLaunchPopupL(
									TInt aResourceId,
									const TPoint& aTargetPos, 
									const CEikHotKeyTable* aHotKeyTable, 
									TPopupTargetPosType aTargetType,
									CEikAppUi* aAppUi) = 0;

   	virtual void ClosePopup(CEikAppUi* aAppUi) = 0;
	virtual void StopDisplayingMenuBar() = 0;
	virtual void HandleSideBarMenuL(
									TInt aResourceId,
									const TPoint& aPos,
									const CEikHotKeyTable* aHotKeyTable,
									CEikAppUi* aAppUi) = 0;
	virtual void CreateHotKeyControlL(TInt aResourceId, CEikAppUi* aAppUi) = 0;
	virtual CEikMenuBar* MenuBar() const = 0;
	virtual CEikMenuBar* SwapMenuBar(CEikMenuBar* aMenu) = 0;
	virtual CEikMenuPane* Popup() const = 0;
	virtual CEikButtonGroupContainer* ToolBar() const = 0;
	virtual CEikButtonGroupContainer* SwapButtonGroup(CEikButtonGroupContainer* aNewGroup) = 0;
	virtual CEikToolBar* ToolBand() const = 0;
	virtual CEikToolBar* TitleBand() const = 0;
	virtual CEikStatusPane* StatusPane() const = 0;
	virtual CEikButtonGroupContainer* Cba() const = 0;
	inline CEikToolBar* SwapToolBand(CEikToolBar* aToolBand);
	inline CEikToolBar* SwapTitleBand(CEikToolBar* aTitleBand);

	virtual CEikCommandButton*  CreateStandardTabButtonL() const = 0;
	virtual void CreateEmbeddedL(CEikonEnv& aEikonEnv) = 0;
	virtual void DestroyEmbedded(CEikonEnv& aEikonEnv) = 0;
	virtual void HandleResourceChangeL(TInt aType) = 0;
protected:
	enum TToolBarType {EBand,ETitle};
private:
	virtual CEikToolBar* SwapToolBar(CEikToolBar* aToolBar,TToolBarType aType) = 0;
	};

inline CEikToolBar* MEikAppUiFactory::SwapToolBand(CEikToolBar* aToolBand)
	{return SwapToolBar(aToolBand,EBand);}
inline CEikToolBar* MEikAppUiFactory::SwapTitleBand(CEikToolBar* aTitleBand)
	{return SwapToolBar(aTitleBand,ETitle);}

#endif
