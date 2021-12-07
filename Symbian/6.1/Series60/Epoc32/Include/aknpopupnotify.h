/*
* ============================================================================
*  Name     : AknPopupNotify.h
*  Part of  : Avkon
*
*  Description:
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
#ifndef __AKNPOPUPNOTIFY_H__
#define __AKNPOPUPNOTIFY_H__

#include <AknNotify.h>


class CAknPopupNotify : public CAknNotifyBase
    {
public:
	IMPORT_C static CAknPopupNotify* NewL();
	IMPORT_C static CAknPopupNotify* NewLC();
	IMPORT_C ~CAknPopupNotify();

	IMPORT_C void PopupMessageL(const TDesC& aMessage);

private:
	CAknPopupNotify();
	void ConstructL();
private:
	IMPORT_C void CAknNotifyBase_Reserved();
    };


#endif
