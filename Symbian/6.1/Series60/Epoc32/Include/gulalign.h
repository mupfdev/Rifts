// GULALIGN.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__GULALIGN_H__)
#define __GULALIGN_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__GDI_H__)
#include <gdi.h>
#endif

enum TGulHAlignment
	{
	EHLeft=CGraphicsContext::ELeft,
	EHCenter=CGraphicsContext::ECenter,
	EHRight=CGraphicsContext::ERight
	};

enum TGulVAlignment
	{
	EVTop=0x00,
	EVCenter=0x10,
	EVBottom=0x20
	};

enum TGulAlignmentValue
	{
	EHLeftVTop=EHLeft|EVTop,	EHLeftVCenter=EHLeft|EVCenter,		EHLeftVBottom=EHLeft|EVBottom,
	EHCenterVTop=EHCenter|EVTop,EHCenterVCenter=EHCenter|EVCenter,	EHCenterVBottom=EHCenter|EVBottom,
	EHRightVTop=EHRight|EVTop,	EHRightVCenter=EHRight|EVCenter,	EHRightVBottom=EHRight|EVBottom
	};

/**
 * The TGulAlignment class provides a convenient way to describe horizontal and vertical layouts of
 * rectangular objects and to enquire how they occupy an area given their alignment.
 */
class TGulAlignment
	{
private:
	enum {EHMask=0x03, EVMask=0x30};
public:
	inline TGulAlignment();
	inline TGulAlignment(TGulAlignmentValue aValue);
	inline operator TGulAlignmentValue() const;
	inline TGulVAlignment VAlignment() const;
	inline TGulHAlignment HAlignment() const;

	/**
	 * Returns the horizontal text alignment. 
	 */
	inline CGraphicsContext::TTextAlign TextAlign() const;

	IMPORT_C void SetVAlignment(TGulVAlignment aVAlign);
	IMPORT_C void SetHAlignment(TGulHAlignment aHAlign);
	IMPORT_C TPoint InnerTopLeft(const TRect& aOuter,const TSize& aInnerSize) const;
	IMPORT_C TRect InnerRect(const TRect& aOuter,const TSize& aInnerSize) const;
private:
	TGulAlignmentValue iValue;
	};

inline TGulAlignment::TGulAlignment()
	{};
inline TGulAlignment::TGulAlignment(TGulAlignmentValue aValue)
	{iValue=aValue;}
inline TGulAlignment::operator TGulAlignmentValue() const
	{return(iValue);}
inline TGulVAlignment TGulAlignment::VAlignment() const
	{return((TGulVAlignment)(iValue&EVMask));}
inline TGulHAlignment TGulAlignment::HAlignment() const
	{return((TGulHAlignment)(iValue&EHMask));}
inline CGraphicsContext::TTextAlign TGulAlignment::TextAlign() const
	{return((CGraphicsContext::TTextAlign)(HAlignment()));}

#endif
