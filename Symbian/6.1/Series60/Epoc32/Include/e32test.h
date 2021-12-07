// E32TEST.H
//
// Copyright (c) 1994-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __E32TEST_H__
#define __E32TEST_H__
#include <e32std.h>
#include <e32base.h>
#include <e32cons.h>
#include <e32ver.h>

class RTest
	{
public:
	IMPORT_C RTest(const TDesC &aTitle,TInt aThrowaway);
	IMPORT_C RTest(const TDesC &aTitle);
	IMPORT_C void Close();
	IMPORT_C void Title();
	IMPORT_C void Start(const TDesC &aHeading);
	IMPORT_C void Next(const TDesC &aHeading);
	IMPORT_C void End();
	IMPORT_C void operator()(TInt aResult,TInt aLineNum);
	IMPORT_C void operator()(TInt aResult);
	IMPORT_C void Panic(TInt anError,TRefByValue<const TDesC> aFmt,...);
	IMPORT_C void Panic(TRefByValue<const TDesC> aFmt,...);
	IMPORT_C void Printf(TRefByValue<const TDesC> aFmt,...);
	IMPORT_C TKeyCode Getch();
	inline static const TAny* String(TInt aSel,const TText8 *aBuf1,const TText16 *aBuf2);
	inline CConsoleBase* Console() const;
	inline void SetConsole(CConsoleBase* aConsole);
	inline TBool Logged() const;
	inline void SetLogged(TBool aToLog);
protected:
	void CheckConsoleCreated();
	void DisplayLevel();
	inline void Push();
	inline void Pop();
private:
	enum {EMaxStack=0x100,EMaxBuffer=0x100};
private:
	TInt	iTest;
	TInt	iCheck;
	TInt	iLevel;
	TBool	iLogging;
	CConsoleBase *iConsole;
	TBuf<0x40> iTitle;
	TInt iStack[EMaxStack];
	TText iBuf[EMaxBuffer];
	};

inline CConsoleBase* RTest::Console() const
	{ return(iConsole); }
inline const TAny *RTest::String(TInt aSel,const TText8 *aBuf1,const TText16 *aBuf2)
	{ return(aSel == sizeof(TText8) ? (TAny *)aBuf1 : (TAny *)aBuf2); }
inline void RTest::Push()
	{ iStack[iLevel++] = iTest; iTest = 0; }
inline void RTest::Pop()
	{ iTest = iStack[--iLevel]; }
inline void RTest::SetConsole(CConsoleBase* aConsole)
    { iConsole = aConsole; }
inline TBool RTest::Logged() const
	{ return(iLogging); }
inline void RTest::SetLogged(TBool aToLog)
	{ iLogging = aToLog; }

// test equivalent of _L
#define _TL(a) (S*)RTest::String(sizeof(S),(TText8*)a,(TText16*)L ## a) 
#define test(x) test(x,__LINE__)
#endif

