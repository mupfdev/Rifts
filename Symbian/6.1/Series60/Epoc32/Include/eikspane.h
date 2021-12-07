// EIKSPANE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKSPANE_H__)
#define __EIKSPANE_H__

#if !defined(__EIKSPMOD_H__)
#include <eikspmod.h>
#endif

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

#if !defined(__COECOBS_H__)
#include <coecobs.h>
#endif

class CCoeBrushAndPenContext;
class CEikStatusPaneContainer;
class TEikStatusPaneSyncDrawer;

const TInt KStatusPaneCapsPresentBit = 1;
const TInt KStatusPaneCapsAppOwnedBit = 2;
const TInt KStatusPaneCapsInCurrentLayoutBit = 4;


/**
 * The MEikStatusPaneObserver interface allows a status pane observer to pick up
 * changes in the size or position of the status pane. Such events will be as a
 * result of layout changes which cause an actual change in the status pane
 * rectangle.
 */
class MEikStatusPaneObserver
	{
public:
	virtual void HandleStatusPaneSizeChange() = 0;
	};

/**
 * CEikStatusPaneBase is the base class for the concrete status pane classes
 * CEikStatusPane and CEikServStatusPane.
 */
class CEikStatusPaneBase : public CBase
	{
public:
	class TPaneCapabilities
		{
	public:
		TPaneCapabilities();
		inline TBool IsPresent() const;
		inline TBool IsAppOwned() const;
		inline TBool IsInCurrentLayout() const;
	private:
		inline void SetPresent();
		inline void SetAppOwned();
		inline void SetInCurrentLayout();
	private:
		TInt iFlags;
	private:
		friend class CEikStatusPaneBase;
		};

public:
	IMPORT_C ~CEikStatusPaneBase();

	IMPORT_C static CEikStatusPaneBase* Current();
	
	inline   void SetObserver(MEikStatusPaneObserver* aObserver);
	IMPORT_C void ReduceRect(TRect& aBoundingRect) const;
	IMPORT_C void GetShapeL(TRegion& aRegion, TBool aIncludeAppPanes, TBool aIncludeServerPanes) const;

	IMPORT_C virtual void SwitchLayoutL(TInt aLayoutResourceId);
	IMPORT_C virtual void MakeVisible(TBool aVisible);
	IMPORT_C virtual void SetDimmed(TBool aDimmed);
	IMPORT_C virtual void SetFaded(TBool aFaded);
	IMPORT_C virtual void HandleResourceChange(TInt aType);
	IMPORT_C virtual TBool OkToChangeStatusPaneNow();

	IMPORT_C void SetFlags(TInt aFlags);
	IMPORT_C TInt Flags() const;
	IMPORT_C TBool IsVisible() const;
	IMPORT_C TBool IsDimmed() const;
	IMPORT_C TBool IsFaded() const;

	IMPORT_C TPaneCapabilities PaneCapabilities(TPaneId aPaneId) const;
	IMPORT_C TRect PaneRectL(TPaneId aPaneId) const;
	IMPORT_C CCoeControl* ControlL(TPaneId aPaneId) const;
	IMPORT_C CCoeControl* SwapControlL(TPaneId aPaneId, CCoeControl* aNewControl);
	IMPORT_C CCoeControl* ContainerControlL(TPaneId aPaneId) const;
	inline RWindowGroup* WindowGroup() const;
	IMPORT_C void DrawNow();
	IMPORT_C TInt CurrentLayoutResId() const;

protected:
	IMPORT_C CEikStatusPaneBase(CEikonEnv& aEikEnv, RWindowGroup* aParent);
	IMPORT_C void BaseConstructL(TInt aCoreResId);

	virtual CEikStatusPaneModelBase* CreateModelL(TInt aCoreResId) const = 0;
	void CreatePanesL();
	void CreatePaneL(const TEikStatusPaneInit& aPaneInit);
	CEikStatusPaneContainer* Find(TPaneId aPaneId) const;

	virtual TBool IsApp() const = 0;
	inline TRect Rect() const;

private:
	void ApplyLayoutL(CEikStatusPaneLayout* aLayout);
	void SetAllInvisible();
	void ReportSizeChange();

private:
	class TSetRectAndVisibility : public MEikStatusPaneLayoutTreeVisitor
		{
	public:
		TSetRectAndVisibility(TBool aIsApp, CEikStatusPaneBase* aStatusPane);
		void VisitL(CEikStatusPaneLayoutTree* aNode);
	private:
		TBool iIsApp;
		CEikStatusPaneBase* iStatusPane;
		};
	friend class TSetRectAndVisibility;

protected:
	CEikonEnv& iEikEnv;
	CEikStatusPaneModelBase* iModel;

	TInt iFlags;

private:
	typedef CArrayPtrFlat<CEikStatusPaneContainer> CContainerControls;
	CContainerControls* iControls;
	MEikStatusPaneObserver* iObserver;
	RWindowGroup* iParentWindowGroup;
	TInt iSpbSpare;
	};

/**
 * CEikStatusPane is the interface through which applications use the status pane.
 * This class synchronises the status pane layout with the server side status pane
 * object. To do this, the ApplyCurrentSettingsL() method must be called whenever
 * the owner application switches to the foreground.
 */
class CEikStatusPane : public CEikStatusPaneBase, public MCoeForegroundObserver
	{
public:
	IMPORT_C static CEikStatusPane* NewL(CEikonEnv& aEikEnv, RWindowGroup* aParent, TInt aCoreStatusPaneModelResId, TInt aAppStatusPaneModelResId=EEikStatusPaneUseDefaults);
	IMPORT_C ~CEikStatusPane();

	IMPORT_C void ApplyCurrentSettingsL();
	IMPORT_C void PrepareForAppExit();

	// from CEikStatusPaneBase
	IMPORT_C virtual void MakeVisible(TBool aVisible);
	IMPORT_C virtual void SetDimmed(TBool aDimmed);
	IMPORT_C virtual void SetFaded(TBool aFaded);
	IMPORT_C virtual void HandleResourceChange(TInt aType);
	IMPORT_C virtual TBool OkToChangeStatusPaneNow();

private:
	CEikStatusPane(CEikonEnv& aEikEnv, RWindowGroup* aParent, TInt aAppStatusPaneModelId);
	void ConstructL(TInt aCoreStatusPaneModelResId);

	virtual CEikStatusPaneModelBase* CreateModelL(TInt aCoreResId) const;
	TBool IsApp() const;

	void ApplyCurrentFlags();

private: // from MCoeForegroundObserver
	void HandleGainingForeground();
	void HandleLosingForeground();

private:
	TInt iAppDeclId;
	TEikStatusPaneSyncDrawer* iSyncDrawer;	// formerly CPeriodic* iTimer;
	TInt iSpare;	// formerly iServerSpWgId;
	};






/**
 * Does the pane exist in this status pane?
 * Note: this will return true if the pane can be used, even if it is not visible.
 */
inline TBool CEikStatusPaneBase::TPaneCapabilities::IsPresent() const { return iFlags & KStatusPaneCapsPresentBit; }
/**
 * Is this pane owned by applications rather than the server?
 * Applications can only interact directly with application owned panes.
 */
inline TBool CEikStatusPaneBase::TPaneCapabilities::IsAppOwned() const { return iFlags & KStatusPaneCapsAppOwnedBit; }
/**
 * Is this pane part of the current status pane layout?
 */
inline TBool CEikStatusPaneBase::TPaneCapabilities::IsInCurrentLayout() const { return iFlags & KStatusPaneCapsInCurrentLayoutBit; }
/**
 * Set the status pane observer.
 */
inline void CEikStatusPaneBase::SetObserver(MEikStatusPaneObserver* aObserver) { iObserver = aObserver; }
inline TRect CEikStatusPaneBase::Rect() const { return iModel->CurrentLayout()->Rect(); }
inline RWindowGroup* CEikStatusPaneBase::WindowGroup() const { return iParentWindowGroup; }

#endif
