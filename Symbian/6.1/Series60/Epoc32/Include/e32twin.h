// E32TWIN.H
//
// Copyright (c) 1995-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __E32TWIN_H__
#define __E32TWIN_H__
#include <e32cons.h>
//

enum TEventType
    {
    EKeyPress,
    EMouseClick
    };

enum TVideoMode
	{
	EMono=1,
	EGray4=2,
	EGray16=4,
	EColor256=8
	};

struct SConsoleKey
	{
 	TKeyCode iCode;
	TUint iModifiers;
    TPoint iMousePos;
    TInt iType;
	};
//
class TConsoleKey : public TPckgBuf<SConsoleKey>
	{
public:
	IMPORT_C TKeyCode Code() const;
	IMPORT_C TInt Modifiers() const;
    IMPORT_C TInt Type() const;
    IMPORT_C TPoint MousePos() const;
	};
//
class RConsole : public RSessionBase
	{
public:
	IMPORT_C TVersion Version();
	IMPORT_C TInt Create();
	IMPORT_C TInt Init(const TDesC &aName,const TSize &aSize);
	IMPORT_C TInt Write(const TDesC &aDes);
	IMPORT_C TInt ClearScreen();
	IMPORT_C TInt ClearToEndOfLine();
	IMPORT_C TInt Destroy();
	IMPORT_C TInt SetTitle(const TDesC &aName);
	IMPORT_C TInt SetSize(const TSize &aSize);
	IMPORT_C TInt SetWindowPosAbs(const TPoint &aPosition);
	IMPORT_C TInt SetCursorHeight(TInt aPercentage);
	IMPORT_C TInt SetCursorPosAbs(const TPoint &aPosition);
	IMPORT_C TInt SetCursorPosRel(const TPoint &aVector);
	IMPORT_C TInt Size(TSize &aSize) const;
	IMPORT_C TInt ScreenSize(TSize &aSize) const;
	IMPORT_C TInt CursorPos(TPoint &aPosition) const;
	IMPORT_C TInt Control(const TDesC &aDes);
	IMPORT_C TInt Read(TConsoleKey &aKeystroke);
	IMPORT_C void Read(TConsoleKey &aKeystroke,TRequestStatus &aStatus);
	IMPORT_C TInt ReadCancel();
	IMPORT_C TInt SetMode(TVideoMode aMode);
	IMPORT_C void SetPaletteEntry(TUint anIndex,TUint8 aRed,TUint8 aGreen,TUint8 aBlue);
	IMPORT_C void GetPaletteEntry(TUint anIndex,TUint8 &aRed,TUint8 &aGreen,TUint8 &aBlue);
	IMPORT_C void SetTextColors(TUint anFgColor,TUint aBgColor);
	IMPORT_C void SetUIColors(TUint aWindowBgColor,TUint aBorderColor,TUint aScreenColor);
	IMPORT_C void SetTextAttribute(TTextAttribute anAttribute);
	};
//
class CConsoleTextWin : public CConsoleBase
	{
public:
	static CConsoleTextWin *NewL(const TDesC &aTitle,TSize aSize);
	CConsoleTextWin();
	virtual ~CConsoleTextWin();
	virtual TInt Create(const TDesC &aTitle,TSize aSize);
	virtual void Read(TRequestStatus &aStatus);
	virtual void ReadCancel();
	virtual void Write(const TDesC &aDes);
	virtual TPoint CursorPos() const;
	virtual void SetCursorPosAbs(const TPoint &aPoint);
	virtual void SetCursorPosRel(const TPoint &aPoint);
	virtual void SetCursorHeight(TInt aPercentage);
	virtual void SetTitle(const TDesC &aTitle);
	virtual void ClearScreen();
	virtual void ClearToEndOfLine();
	virtual TSize ScreenSize() const;
	virtual TKeyCode KeyCode() const;
	virtual TUint KeyModifiers() const;
	virtual void SetTextAttribute(TTextAttribute anAttribute);
	RConsole &Console();
private:
	TConsoleKey iKey;
	RConsole iConsole;
	};
#endif

