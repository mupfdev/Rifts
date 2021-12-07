// EIKHGDLG.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKHGDLG_H__)
#define __EIKHGDLG_H__

#if !defined(__EIKDIALG_H__)
#include <eikdialg.h>
#endif

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

#if !defined(__EIKENV_H__)
#include <eikenv.h>
#endif


class CCoeRedrawer;
class CSchedulerShaker;

class TEikHeapFailModel
	{
public:
	TInt iHeapFailRate;
	TInt iHeapFailType;
	TInt iWservFailRate;
	TInt iWservFailType;
	TInt iFileFailRate;
	TInt iFileFailType;
	};


//
//	class CEikDebugKeys
//

class CEikDebugKeys : public CCoeControl, public MEikDebugKeys
	{
private: // from MEikDebugKeys
	void ConstructL();
	void Release();
private: // framework
	virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
private:
	friend class CEikonEnv;
//	friend class CDebugKeysDlg;
//	friend class CDebugKeysAppUi;
	TEikHeapFailModel iModel;
	TBool iVerbose;
	CCoeRedrawer* iPhantomBorderDrawer;
	CSchedulerShaker* iSchedulerShaker;
	};


//
//	class CEikDebugWin
//

class CEikDebugWin : public CCoeControl
    {
public:
    void ConstructL();
private:
	void Draw(const TRect& aRect) const;
    };


#endif
