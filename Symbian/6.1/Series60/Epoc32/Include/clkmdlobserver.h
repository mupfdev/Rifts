/*
* ==============================================================================
*  Name        : ClkMdlObserver.h
*  Part of     : ClkWldAlmMdl / ClkWldAlmMdl.dll
*  Interface   : 
*  Description : 
*  Version     : 
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/

#ifndef MCLKMDLOBSERVER_H
#define MCLKMDLOBSERVER_H

//  INCLUDES

/**
* Interface attached to concrete observer
*
*/
class MClkModelObserver
    {

    public: // New functions

        /**
        * Get the notification that must be forwarded.
        * @param aNotification The cause of the notification.
        */
        virtual void HandleUpdateL(TInt aNotification)=0;
    };

#endif  // MCLKMDLOBSERVER_H
// End of file