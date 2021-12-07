// LAFMAIN.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __LAFMAIN_H__
#define __LAFMAIN_H__

#include <e32std.h>
#include <e32base.h>
#include <gulbordr.h>
#include <gulcolor.h>
#include <frmtlay.h>

class CCoeControl;
class CFont;
class TLogicalFont;
class MLafEnv;

/**
 * class CLafEdwinCustomDrawBase
 *
 * FORM custom draw class used by CEikEdwin to draw lines in plain text editors
 * Does not work in rich text editors as it assumes the line spacing is constant
 */
class CLafEdwinCustomDrawBase : public CBase, public MFormCustomDraw
	{
public:
	IMPORT_C static CLafEdwinCustomDrawBase* NewL(const MLafEnv& aEnv,const CCoeControl& aControl);
public: // from MFormCustomDraw
	IMPORT_C void DrawBackground(const TParam& aParam,const TRgb& aBackground,TRect& aDrawn) const;
	IMPORT_C TRgb SystemColor(TUint aColorIndex,TRgb aDefaultColor) const;
public:
	IMPORT_C virtual void LineSpacingChanged();
protected:
	IMPORT_C CLafEdwinCustomDrawBase(const MLafEnv& aEnv,const CCoeControl& aControl);
protected:
	const MLafEnv& iEnv;
	const CCoeControl& iControl;
private:
	TInt iSpare;
	};

class MLafEnv
	{
public:
	virtual const CFont* Font(const TLogicalFont& aLogicalFont) const=0;
	virtual const CFbsBitmap* Bitmap( TUid aBmpUid) const=0;
	virtual TRgb ControlColor(TLogicalColor aLogicalColor, const CCoeControl& aControl) const=0;
	virtual TRgb Color(TLogicalColor aLogicalColor, TUid aColorListUid=KNullUid) const=0;
	virtual TDisplayMode DefaultDisplayMode() const=0; 
	};

/**
 * @internal
 * Do not use
 */
class MLafClientRectResolver
	{
public:
	enum TScreenFurniture
		{ EMenuBar, EButtonGroup, EToolBand, ETitleBand, EStatusPane, ECba };
public:
	virtual void ReduceRect(TScreenFurniture aScreenFurniture,TRect& aRect) const=0;
	};

#endif //__LAFMAIN_H__
