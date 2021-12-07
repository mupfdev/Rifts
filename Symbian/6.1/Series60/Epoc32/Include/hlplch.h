#ifndef __HLPLCH_H__
#define __HLPLCH_H__

#if !defined(__APGTASK_H__)
#include <apgtask.h>
#endif

#if !defined(__EIKDLL_H__)
#include <eikdll.h>
#endif

#if !defined(__WSERV_H__)
#include <w32std.h>
#endif

#if !defined(__COEHELP_H__)
#include <coehelp.h>
#endif

const TUid KHlpAppUid={ 0x10005234 };
const TUid KHlpAppWsMsg={ 0x100055c7 };
const TInt KMaxCmdLineLength = 512;

_LIT(KHlpAppPath, "z:\\System\\Apps\\CsHelp\\CsHelp.app");

class CHlpCmdLine : public CBase
	{
public:
	static CHlpCmdLine* NewL(CArrayFix<TCoeHelpContext>* aContextList);
	static CHlpCmdLine* NewLC(CArrayFix<TCoeHelpContext>* aContextList);
	~CHlpCmdLine();
public:
	TPtr8 CmdLine();
private:
	void BuildCmdLineL();
	void AddContextL(TCoeHelpContext& aContext);
private:
	void ConstructL();
	CHlpCmdLine(CArrayFix<TCoeHelpContext>* aContextList);
private:
	CArrayFix<TCoeHelpContext>* iContextList;
	CBufFlat* iCmdLine;
	};

class HlpLauncher
	{
public:
	IMPORT_C	static void LaunchHelpApplicationL(RWsSession& aWsSession, CArrayFix<TCoeHelpContext>* aContextList);
	IMPORT_C	static void LaunchHelpApplicationL(RWsSession& aWsSession, TUid aUid);
	IMPORT_C	static void LaunchHelpApplicationL(RWsSession& aWsSession);
private:
	static void DoLaunchHelpApplicationL(RWsSession& aWsSession, const TDesC8& aCmdLine);
	};

#endif