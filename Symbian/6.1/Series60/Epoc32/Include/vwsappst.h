// VWSAPPST.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

#ifndef __VWSAPPST_H__
#define __VWSAPPST_H__

/**
 * The MVwsAppStarter class specifies an interface through which the view server makes callbacks to start applications.
 * 
 * If a view has not been registered in the server when an activation request arrives, the server will try to start
 * the application associated with that view.
 *
 * @internal
 * Internal to Symbian
 */ 
class MVwsAppStarter
	{
public:	// Internal to Symbian

	/**
	 * Starts the application identified by aAppUid.
	 */
	virtual void StartAppL(TUid aAppUid,TThreadId& aThreadId)=0;
	};

#endif
