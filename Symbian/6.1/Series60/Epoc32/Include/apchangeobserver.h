/*
* ============================================================================
*  Name     : MApChangeObserver from ApChangeObserver.h
*  Part of  : ConnectionManager
*
*  Description:
*     This interface class defines the protocolconnection/session
*	  handling.
*	
*  Version:
*
*  Copyright (C) 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
*
* ============================================================================
*/

#ifndef AP_CHANGE_OBSERVER_H
#define AP_CHANGE_OBSERVER_H

//This class specifies a protocol for observing the AP changes
class MApChangeObserver
	{
	public:
	virtual void ApChangedL( TUint32 aNewAPId ) = 0;
	};

#endif;//AP_CHANGE_OBSERVER_H// End of File
