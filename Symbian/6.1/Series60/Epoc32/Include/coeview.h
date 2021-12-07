// COEVIEW.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COEVIEW_H__)
#define __COEVIEW_H__

#if !defined(__VWSDEF_H__)
#include <vwsdef.h>
#endif


class CCoeAppUi;

/**
 * The MCoeView class specifies an interface for views.
 *
 * @since Uikon1.2
 */
class MCoeView
	{
public:
	/**
	 * Returns the id of the view.
	 */
	virtual TVwsViewId ViewId() const=0;
private:
	/**
	 * Takes any action required on activation of the view. Reimplemented versions should read the message text
	 * aCustomMessage for any message type identified by aCustomMessageId that the view understands.
	 *
	 * The id of the previously active view aPrevViewId is supplied so that the view may switch back to its caller
	 * at some later stage
	 */
	virtual void ViewActivatedL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage)=0;

	/**
	 * Takes any action required on deactivation of the view e.g. to make the controls owned by the view non-visible
	 * (thereby saving the window server uneccessary work).
	 */
	virtual void ViewDeactivated()=0;

	IMPORT_C virtual TVwsViewIdAndMessage ViewScreenDeviceChangedL();
	IMPORT_C virtual void ViewConstructL();
private:
	friend class CCoeViewManager;
	IMPORT_C virtual void MCoeView_Reserved_1();
	IMPORT_C virtual void MCoeView_Reserved_2();
	};


#endif
