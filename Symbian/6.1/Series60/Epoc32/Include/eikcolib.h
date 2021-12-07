//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
// Static functions called by CEikDllInitializer setting EikCoCtl
// library resources in Cone and giving access to its controls
// via ControlFactoryFuncArray() in EikonEnv

#if !defined(__EIKCOLIB_H__)
#define __EIKCOLIB_H__

#include <eikaufty.h>
#include <f32file.h>
#include <e32base.h>
#include <eiklibry.h>
#include <eikbtgpc.h>
#include <Eikspane.h>
#include <eikbgfty.h>
#include <lafmain.h>



class CEikAppUiFactory;
class CEikAppUi;

/**
 * @internal
 * Do not use
 */
class CEikCoCtlLibrary : public CBase
	{
public:
	IMPORT_C static TFileName				ResourceFile();
	IMPORT_C static TCreateByTypeFunction	ControlFactory();
	IMPORT_C static TCreateButtonGroupByTypeFunction ButtonGroupFactory();
public:
	static SEikControlInfo CreateByTypeL(TInt aControlType);
	static MEikButtonGroup* CreateButtonGroupByTypeL(TInt aButtonGroupType,EikButtonGroupFactory::TCreationData& aCreationData,TBool& aAddToButtonGroupStack);
private:
	CEikCoCtlLibrary();
	};

class CEikToolBar;
class CEikMenuBar;
class CEikMenuPane;
class CEikCommandButton;

/**
 * @internal
 * Do not use
 */
class CEikAppUiFactory : public CBase, public MEikAppUiFactory, public MLafClientRectResolver
	{
public:
	IMPORT_C CEikAppUiFactory();
	~CEikAppUiFactory();
public: // from MEikAppUiFactory
	void CreateResourceIndependentFurnitureL(CEikAppUi* aAppUi);
	TRect ClientRect();
	void ReadAppInfoResourceL(TInt aResourceFileOffset, CEikAppUi* aAppUi);
	void LaunchPopupMenuL(
							TInt aResourceId,
							const TPoint& aTargetPos,
							TPopupTargetPosType aTargetType,
							const CEikHotKeyTable* aHotKeyTable,
							CEikAppUi* aAppUi);
	void DoLaunchPopupL(
							TInt aResourceId,
							const TPoint& aTargetPos, 
							const CEikHotKeyTable* aHotKeyTable, 
							TPopupTargetPosType aTargetType,
							CEikAppUi* aAppUi);
	void ClosePopup(CEikAppUi* aAppUi);
	void StopDisplayingMenuBar();
	void HandleSideBarMenuL(
							TInt aResourceId,
							const TPoint& aPos,
							const CEikHotKeyTable* aHotKeyTable,
							CEikAppUi* aAppUi);

	void CreateHotKeyControlL(TInt aResourceId, CEikAppUi* aAppUi);
	CEikMenuBar* MenuBar() const;
	CEikMenuBar* SwapMenuBar(CEikMenuBar* aMenu);
	CEikMenuPane* Popup() const;
	CEikButtonGroupContainer* SwapButtonGroup(CEikButtonGroupContainer* aNewGroup);
	CEikButtonGroupContainer* ToolBar() const;
	CEikToolBar* ToolBand() const;
	CEikToolBar* TitleBand() const;
	CEikToolBar* SwapToolBar(CEikToolBar* aToolBar,TToolBarType aType);
	CEikStatusPane* StatusPane() const;
	CEikButtonGroupContainer* Cba() const;

	CEikCommandButton* CreateStandardTabButtonL() const;
	void CreateEmbeddedL(CEikonEnv& aEikonEnv);
	void DestroyEmbedded(CEikonEnv& aEikonEnv);
	void HandleResourceChangeL(TInt aType);
private: // from MLafClientRectResolver
	void ReduceRect(TScreenFurniture aScreenFurniture,TRect& aRect) const;
private:
	void AddTitleBandL(CEikAppUi* aAppUi);
private: // from MObjectProvider
	TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
private:
	struct SEikAppInfo
		{
		TInt iHotKeysId;
		TInt iMenuBarId;
		TInt iToolBarId;
		TInt iToolBandId;
		TInt iCbaId;
		TInt iStatusPaneId;
		};
	struct SRssSignature
		{
		TInt iSignature;
		TInt iSelf;
		};
private:
	CEikButtonGroupContainer* iToolBar;
	CEikToolBar* iToolBand;
	CEikToolBar* iTitleBand;
	CEikMenuBar* iMenuBar;
	CEikMenuPane* iPopup;
	TInt iSidebarPopupId;
	CEikStatusPane* iStatusPane;
	CEikButtonGroupContainer* iCba;
	};

#endif
