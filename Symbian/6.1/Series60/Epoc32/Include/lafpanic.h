// LAFPANIC.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __LAFPANIC_H__
#define __LAFPANIC_H__

enum TLafPanic
	{
	ELafPanicPointerCursorIndexOutOfRange,
	ELafPanicFontIndexOutOfRange,//Zam: wish I could remove this but needed in lafmenub.cpp, lafmenup.cpp
	ELafPanicConstantNotKnown,
	ELafPanicMsgWinBadHorizontalAlignment,
	ELafPanicMsgWinBadVerticalAlignment,
	ELafPanicBitmapIndexOutOfRange,
	ELafPanicNotificationWithoutRequest,
    ELafPanicFontUidUnknownOrMissing,
	ELafPanicUsingFontFromWrongVariant
	};

#endif //__LAFPANIC_H__
