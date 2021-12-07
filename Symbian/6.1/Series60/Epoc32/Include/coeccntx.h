// COECCNTX.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COECCNTX_H__)
#define __COECCNTX_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__W32STD_H__)
#include <w32std.h>
#endif


/**
 * The MCoeControlContext class specifies the interface to prepare the
 * graphics context of a control before drawing. Normally, controls prepare their graphics
 * context in their draw functions.
 *
 * Controls which use the extension can share the same procedure for preparing their
 * graphics context. The control context used by a control can be set externally or copied
 * from another control.
 */
class MCoeControlContext
	{
public:
	IMPORT_C virtual void ActivateContext(CWindowGc& aGc,RDrawableWindow& aWindow) const;
	IMPORT_C virtual void ResetContext(CWindowGc& aGc) const;
	IMPORT_C virtual void PrepareContext(CWindowGc& aGc) const;
	};


/**
 * The CCoeBrushAndPenContext class allows an MCoeControlContext to be instantiated
 * and used to set brush and pen properties before drawing a control.
 *
 * @since ER5U
 */
class CCoeBrushAndPenContext : public CBase, public MCoeControlContext
	{
public:
	IMPORT_C static CCoeBrushAndPenContext* NewL();
	//
	IMPORT_C void SetBrushStyle(CWindowGc::TBrushStyle aBrushStyle);
	IMPORT_C void SetBrushColor(TRgb aColor);
	IMPORT_C void SetBrushBitmap(const CFbsBitmap& aBitmap);
	IMPORT_C void SetPenColor(TRgb aColor);
	//
	IMPORT_C CWindowGc::TBrushStyle BrushStyle() const;
	IMPORT_C TRgb BrushColor() const;
	IMPORT_C const CFbsBitmap& BrushBitmap() const;
	IMPORT_C TRgb PenColor() const;
protected: // from MCoeControlContext
	IMPORT_C void PrepareContext(CWindowGc& aGc) const;
private:
	CCoeBrushAndPenContext();
private:
	CWindowGc::TBrushStyle iBrushStyle;
	TRgb iBrushColor;
	const CFbsBitmap* iBitmap;
	TRgb iPenColor;
	};


/**
 * The MCoeControlBrushContext class can be used to set brush and pen properties
 * before drawing a control.
 *
 * @deprecated
 */
class MCoeControlBrushContext : public MCoeControlContext
	{
protected: // from MCoeControlContext
	IMPORT_C void PrepareContext(CWindowGc& aGc) const;
public:
	CWindowGc::TBrushStyle iBrushStyle;
	TRgb iBrushColor;
	const CFbsBitmap* iBitmap;
	};

#endif
