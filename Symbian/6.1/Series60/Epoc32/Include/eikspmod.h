// EIKSPMOD.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKSPMOD_H__)
#define __EIKSPMOD_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__EIKON_HRH__)
#include <uikon.hrh>
#endif

#if !defined(__EIKSRVC_H__)
#include <eiksrvc.h>
#endif


class TResourceReader;
class CEikStatusPaneLayoutTree;
class CEikonEnv;
class CAknSgcClient;


// Extra bit flags not defined in hrh file.
const TInt KEikStatusPaneDirectionBit		= 0x04;
const TInt KEikStatusPaneHiddenBit			= 0x08;
const TInt KEikStatusPaneInitInitializedBit	= 0x80000000;


typedef TUid TPaneId;

class TEikStatusPaneInit
	{
public:
	TEikStatusPaneInit();
	TEikStatusPaneInit(const TEikStatusPaneInit& aCopy);
	TEikStatusPaneInit& operator=(const TEikStatusPaneInit& aCopy);
	
	inline TPaneId Id() const;
	void LoadDefaults(TResourceReader& aResource);

	inline TBool AppOwned() const;
	inline TInt ControlTypeId() const;
	inline TInt ControlResourceId() const;

	inline void SetHidden();
	inline void ClearHidden();
	inline TBool IsHidden() const;

private:
	inline TBool Initialized();
	inline void SetInitialized();

private:
	TPaneId iId;
	TInt iControlId;
	TInt iControlResource;
	TInt iFlags;
	};


class CEikStatusPaneSetInit : public CArrayFixFlat<TEikStatusPaneInit>
	{
public:
	static CEikStatusPaneSetInit* NewL();
	~CEikStatusPaneSetInit();

	void LoadDefaultsL(TResourceReader& aResource);
	TEikStatusPaneInit& FindL(const TPaneId& aPaneId);

private:
	CEikStatusPaneSetInit();
	};


class MEikStatusPaneLayoutTreeVisitor
	{
public:
	virtual void VisitL(CEikStatusPaneLayoutTree* aNode) = 0;
	};


class CEikStatusPaneLayoutTree : public CBase
	{
public:
	enum TDirection
		{
		EHorizontal,
		EVertical
		};

public:
	~CEikStatusPaneLayoutTree();
	static CEikStatusPaneLayoutTree* NewL(TResourceReader& aResource, TDirection aDefaultDirection = EHorizontal);

	CEikStatusPaneLayoutTree* Find(const TPaneId& aPaneId);
	void AcceptL(MEikStatusPaneLayoutTreeVisitor* aVisitor);

	inline TPaneId Id() const;
	inline TRect Rect() const;

private:
	CEikStatusPaneLayoutTree(TDirection aDefaultDirection);
	void ConstructL(TResourceReader& aResource);

	void SetRect(const TRect& aRect);
	inline TDirection Direction();
	void SetDirection(TDirection aDirection);
	inline TInt Size();
	inline TBool Stretchable();
	void SetStretchable(TBool aStretchable);
	void Layout();

private:
	TPaneId iId;
	TInt iFlags;
	TRect iRect;
	TInt iSize;

	typedef CArrayPtrFlat<CEikStatusPaneLayoutTree> CSubPaneArray;
	CSubPaneArray* iSubPanes;

private:
	friend class CEikStatusPaneLayout;
	};


class CEikStatusPaneLayout : public CBase
	{
public:
	static CEikStatusPaneLayout* NewL(TResourceReader& aResource, const TRect& aScreenRect);
	~CEikStatusPaneLayout();

	inline CEikStatusPaneLayoutTree* Find(const TPaneId& aPaneId) const;
	inline void AcceptL(MEikStatusPaneLayoutTreeVisitor* aVisitor);
	inline TRect Rect() const;

private:
	CEikStatusPaneLayout();
	void ConstructL(TResourceReader& aResource, const TRect& aScreenRect);

private:
	CEikStatusPaneLayoutTree* iRoot;
	};


class CEikStatusPaneModelBase : public CBase
	{
public:
	IMPORT_C ~CEikStatusPaneModelBase();

	inline CEikStatusPaneSetInit* PaneInits() const;
	IMPORT_C virtual void SetLayoutL(TInt aLayoutResId, TBool aChangeStatusPaneNow = ETrue);
	inline CEikStatusPaneLayout* CurrentLayout() const;
	IMPORT_C TInt CurrentLayoutResId() const;

protected:
	class CIdLayoutPair : public CBase
		{
	public:
		CIdLayoutPair(TInt aResId, CEikStatusPaneLayout* aLayout);
		~CIdLayoutPair();
	public:
		TInt iResId;
		CEikStatusPaneLayout* iLayout;
		};
	typedef CArrayPtrFlat<CIdLayoutPair> CLayoutIdSet;
	typedef CArrayFixFlat<TInt> CIdSet;

protected:
	IMPORT_C CEikStatusPaneModelBase(CEikonEnv& aEikEnv);
	IMPORT_C void BaseConstructL(TInt aCoreResId);

	IMPORT_C CEikStatusPaneLayout* LoadLayoutL(TInt aLayoutResId);

	inline CIdSet* LegalIds() const;
	TBool IsLegalId(TInt aLayoutResId) const;

private:
	CEikStatusPaneLayout* Layout(TInt aLayoutResId);
	void CheckLayoutL(CEikStatusPaneLayout* aLayout);

private:
	IMPORT_C virtual void Reserved_1();

private:
	class TLayoutChecker : public MEikStatusPaneLayoutTreeVisitor
		{
	public:
		TLayoutChecker(CEikStatusPaneSetInit* aPanes);
		void VisitL(CEikStatusPaneLayoutTree* aNode);
	private:
		CEikStatusPaneSetInit* iPanes;	
		};

protected:
	CLayoutIdSet* iLayouts;
	TInt iCurrentResId;
	CEikonEnv& iEikEnv;

private:
	CEikStatusPaneSetInit* iPanes;
	CEikStatusPaneLayout* iCurrentLayout;
	CIdSet* iLegalIds;
	};


class CEikAppStatusPaneModel : public CEikStatusPaneModelBase
	{
public:
	static CEikAppStatusPaneModel* NewL(CEikonEnv& aEikEnv, /*REikSrvSession,*/ TInt aCoreResId, TInt aAppResId = EEikStatusPaneUseDefaults, TBool aChangeStatusPaneNow = ETrue);
	~CEikAppStatusPaneModel();
	void ApplyCurrentLayoutL();
public:	// from CEikStatusPaneModelBase
	void SetLayoutL(TInt aLayoutResId, TBool aChangeStatusPaneNow = ETrue);
private:
	CEikAppStatusPaneModel(CEikonEnv& aEikEnv);
	void ConstructL(TInt aCoreResId, TInt aAppResId, TBool aChangeStatusPaneNow = ETrue);
	};


inline TPaneId TEikStatusPaneInit::Id() const { return iId; }
inline TBool TEikStatusPaneInit::AppOwned() const { return iFlags & EEikStatusPaneAppOwned; }
inline TInt TEikStatusPaneInit::ControlTypeId() const { return iControlId; }
inline TInt TEikStatusPaneInit::ControlResourceId() const { return iControlResource; }
inline void TEikStatusPaneInit::SetHidden() {iFlags|=KEikStatusPaneHiddenBit;}
inline void TEikStatusPaneInit::ClearHidden() {iFlags&=~KEikStatusPaneHiddenBit;}
inline TBool TEikStatusPaneInit::IsHidden() const {return iFlags&KEikStatusPaneHiddenBit;}

inline CEikStatusPaneLayoutTree* CEikStatusPaneLayout::Find(const TPaneId& aPaneId) const { return iRoot->Find(aPaneId); }
inline void CEikStatusPaneLayout::AcceptL(MEikStatusPaneLayoutTreeVisitor* aVisitor) { iRoot->AcceptL(aVisitor); }
inline TRect CEikStatusPaneLayout::Rect() const { return iRoot->Rect(); }

inline TPaneId CEikStatusPaneLayoutTree::Id() const { return iId; }
inline TRect CEikStatusPaneLayoutTree::Rect() const { return iRect; }


inline CEikStatusPaneSetInit* CEikStatusPaneModelBase::PaneInits() const { return iPanes; }
inline CEikStatusPaneLayout* CEikStatusPaneModelBase::CurrentLayout() const { return iCurrentLayout; }
inline CEikStatusPaneModelBase::CIdSet* CEikStatusPaneModelBase::LegalIds() const { return iLegalIds; }

#endif
