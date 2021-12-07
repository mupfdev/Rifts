// E32CONS.H
//
// Copyright (c) 1995-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __E32CONS_H__
#define __E32CONS_H__
#include <e32base.h>
#include <e32keys.h>
//
const TInt KDefaultConsWidth=78;
const TInt KDefaultConsHeight=18;
const TInt KConsFullScreen=-1;
//
enum TTextAttribute
	{
	ETextAttributeNormal,
	ETextAttributeBold,
	ETextAttributeInverse,
	ETextAttributeHighlight
	};
//
class CConsoleBase : public CBase
	{
public:
	IMPORT_C virtual ~CConsoleBase();
	IMPORT_C TKeyCode Getch();
	IMPORT_C void Printf(TRefByValue<const TDesC> aFmt,...);
	IMPORT_C void SetPos(TInt aX);
	IMPORT_C void SetPos(TInt aX,TInt aY);
	IMPORT_C TInt WhereX() const;
	IMPORT_C TInt WhereY() const;
// Pure virtual
	virtual TInt Create(const TDesC &aTitle,TSize aSize) =0;
	virtual void Read(TRequestStatus &aStatus) =0;
	virtual void ReadCancel() =0;
	virtual void Write(const TDesC &aDes) =0;
	virtual TPoint CursorPos() const =0;
	virtual void SetCursorPosAbs(const TPoint &aPoint) =0;
	virtual void SetCursorPosRel(const TPoint &aPoint) =0;
	virtual void SetCursorHeight(TInt aPercentage) =0;
	virtual void SetTitle(const TDesC &aTitle) =0;
	virtual void ClearScreen() =0;
	virtual void ClearToEndOfLine() =0;
	virtual TSize ScreenSize() const =0;
	virtual TKeyCode KeyCode() const =0;
	virtual TUint KeyModifiers() const =0;
protected:
	IMPORT_C CConsoleBase();
	};

class CColorConsoleBase : public CConsoleBase
	{
public:
	virtual void SetTextAttribute(TTextAttribute /*anAttribute*/); 
	};
//
extern "C" {
IMPORT_C TAny *NewConsole();
}
#endif

