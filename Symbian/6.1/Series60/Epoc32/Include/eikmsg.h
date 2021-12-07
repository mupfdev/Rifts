// EIKMSG.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKMSG_H__)
#define __EIKMSG_H__

#if !defined(__CLOCK_H__)
#include <clock.h>
#endif

#if !defined(__GULALIGN_H__)
#include <gulalign.h>
#endif

class CCoeControl;
class CEikonEnv;
class RWindowGroup;

class CEikMsgWin : public CBase
	{
protected:
	IMPORT_C CEikMsgWin(CEikonEnv& aEikonEnv);
public:
	IMPORT_C void ConstructL(RWindowGroup& aWindowGroup);
	IMPORT_C virtual ~CEikMsgWin();
	IMPORT_C void StartDisplay(const TDesC& aText, TGulAlignment aCorner);
	IMPORT_C void CancelDisplay();
protected:
	TDes& PrepareDisplay(TDes& aText, TGulAlignment aCorner);
private:
	virtual void DoStartDisplay(const TDesC& aText)=0;
protected:
	CEikonEnv& iEikonEnv_; // the underscore is to prevent a name clash with the iEikonEnv #define
	CCoeControl* iDummy;
	RBlankWindow* iBlankWindow;
	RMessageWindow* iMessageWindow;
private:
	TInt iSpare;
	};

const TInt KEikInfoMsgMaxLen=RMessageWindow::EMaxTextLength;
typedef TBuf<KEikInfoMsgMaxLen> TEikInfoMsgBuf;

class CEikInfoMsgWin : public CEikMsgWin
	{
public:
	IMPORT_C CEikInfoMsgWin(CEikonEnv& aEikonEnv);
	IMPORT_C void StartDisplaySpecifyingDuration(const TDesC& aText, TGulAlignment aCorner, TTimeIntervalMicroSeconds32 aDuration);
private:
	virtual void DoStartDisplay(const TDesC& aText);
	};

//

const TInt KEikBusyMsgMaxLen=RMessageWindow::EMaxTextLength;
typedef TBuf<KEikBusyMsgMaxLen> TEikBusyMsgBuf;

class CEikBusyMsgWin : public CEikMsgWin
	{
public:
	IMPORT_C CEikBusyMsgWin(CEikonEnv& aEikonEnv);
	IMPORT_C void StartDisplaySpecifyingInitialDelay(const TDesC& aText, TGulAlignment aCorner, TTimeIntervalMicroSeconds32 aInitialDelay);
private:
	virtual void DoStartDisplay(const TDesC& aText);
private:
	TTimeIntervalMicroSeconds32 iInitialDelay;
	};

#endif

