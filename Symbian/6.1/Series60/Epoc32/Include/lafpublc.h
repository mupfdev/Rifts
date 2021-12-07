// LAFPUBLC.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __LAFPUBLC_H__
#define __LAFPUBLC_H__

#include <e32std.h>

const TInt KLafScrollBarButtonPositionMask = 0x00C0;	// sets all bits in EButtonsXxx range for SLafScrollBar::TEikScrollBarFlags

struct SLafScrollButton
	{
	enum TType
		{
		ENudgeLeft,
		ENudgeUp,
		ENudgeRight,
		ENudgeDown,
		EPageLeft,
		EPageUp,
		EPageRight,
		EPageDown,
		EHome,
		ETop,
		EEnd,
		EBottom
		};
	};

struct SLafScrollBar
	{
	enum TEikScrollBarFlags
		{
		EEikScrollBarDefaultBehaviour	=0x0000,
		EEikScrollBarNoNudgeButtons		=0x0001,
		EEikScrollBarHasPageButtons		=0x0002,
		EEikScrollBarHasHomeEndButtons  =0x0004,
		EEikScrollBarNoShaftOrThumb 	=0x0008,
		EEikScrollBarShaftButNoThumb 	=0x0010,
		EButtonsAtStartOfShaft  		=0x0040,
		EButtonsAtEndOfShaft 			=0x0080,
		EButtonsEitherSideOfShaft 		=EButtonsAtStartOfShaft|EButtonsAtEndOfShaft,
		ENoAutoDimming					=0x0100
		};

	enum TOrientation
		{
		EVertical,
		EHorizontal
		};

	};

struct SLafListBox
	{
	enum TFlags
		{
		EMultipleSelection			= 0x0001,
		ENoExtendedSelection		= 0x0002,
		EIncrementalMatching		= 0x0004,
		EPopout						= 0x0008,
		ELeftDownInViewRect			= 0x0010,
		EItemDoubleClicked			= 0x0020,
		EKeepModel					= 0x0040,
		EScrollBarSizeExcluded		= 0x0080,
		EStateChanged				= 0x0100,
		ECreateOwnWindow			= 0x0200,
        ENoFirstLetterMatching      = 0x0400,
		EPaintedSelection			= 0x0800
		};
    enum TListItemAttribute
        {
		ECurrent    = 0x0001,		// may be drawn with a frame
		EEmphasized = 0x0002,		// special highlight (not selected)
		ESelected   = 0x0004,		// usually different than emphasized
		// This last attribute is used to control that one can use only
		// valid attributes above. So do not use it at all.
		EMask		= 0x0007 // sum of all others attributes
        };
	enum TListItemFlags
		{
		EItemDrawMarkSelection			= 0x0001,
		EItemPaintedSelection			= 0x0002,
		EItemDrawOnlyActiveSelection	= 0x0004
		};
	};

struct SLafScrollThumb
	{
	enum TOrientation
		{
		EVertical,
		EHorizontal
		};
	};

struct SLafScrollBarFrame
	{
	enum TScrollBarVisibility
		{
		EOff,
		EOn,
		EAuto
		};

	enum TScrollBarSide
		{
		EBottomOrRight,
		ETopOrLeft
		};

	enum TScrollBarManagement
		{
		EComponent,
		EFloating,
		EApplicationScrollBar
		};
	};

struct SLafControlGroup
	{
	enum TStartCorner
		{
		EFromTopLeft=0x1,
		EFromTopRight=0x2,
		EFromBottomLeft=0x3,
		EFromBottomRight=0x4
		};
	enum TOrientation
		{
		ELayHorizontally=0x10,
		ELayVertically=0x20
		};
	};

struct SLafButtonGroupContainer
	{
	enum TUse
		{
		EView,
		EDialog,
		EToolbar,
		ECba,
		EDialogButtons
		};
	enum TOrientation
		{
		EVertical,
		EHorizontal
		};
	enum TLocation
		{
		EInternal,	// E.g. dialog buttons.
		EExternal	// E.g. toolbar or cba.
		};
	};

struct SLafMenuBar
	{
	enum { ENominalTextLength = 40 };
	};

struct SLafMenuPane
	{
	enum THighlightType
		{
		ENoHighlight,
		EDrawHighlight,
		ERemoveHighlight
		};
	};

struct SLafButtonBase
	{
	enum TDrawState
		{
		EDrawClear					=0x00,
		EDrawSet					=0x01,
		EDrawIndeterminate			=0x02,
		EDrawClearPressed			=0x10,
		EDrawSetPressed				=0x11,
		EDrawIndeterminatePressed	=0x12
		};
	};


#endif // __LAFPUBLC_H__
