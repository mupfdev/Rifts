// EIKLBX.PAN
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKLBX_PAN__)
#define __EIKLBX_PAN__

enum TEikListBoxPanic
	{
	EEikPanicListBoxNoMatchTextArray,
	EEikPanicListBoxNoMatchBuffer,
	EEikPanicListBoxNoModel,
	EEikPanicListBoxNoView,
	EEikPanicListBoxInvalidTopItemIndexSpecified,
	EEikPanicListBoxInvalidCurrentItemIndexSpecified,
	EEikPanicListBoxInvalidItemIndexSpecified,
	EEikPanicListBoxInvalidModelSpecified,
	EEikPanicListBoxInvalidItemDrawerSpecified,
	EEikPanicListBoxInvalidFlagsSpecified,
	EEikPanicListBoxInvalidItemHeightSpecified,	
	EEikPanicListBoxInvalidItemFontSpecified,	
	EEikPanicListBoxCalledFuncNotValidForSingleSelectionLBX,
	EEikPanicListBoxNoSelIndexArray,
	EEikPanicListBoxInvalidSelIndexArraySpecified,
	EEikPanicListBoxInvalidRowIndexSpecified,
	EEikPanicListBoxInvalidColIndexSpecified,
	EEikPanicListBoxInvalidColumnWidthSpecified,
	EEikPanicListBoxInvalidGcSpecified,
	EEikPanicListBoxInvalidFontSpecified,
	EEikPanicListBoxNoGc,
	EEikPanicListBoxNoFont,
	EEikPanicListBoxNoHierArray,
	EEikPanicListBoxItemIsNull
	};

GLREF_C void Panic(TEikListBoxPanic aPanic);

#endif
