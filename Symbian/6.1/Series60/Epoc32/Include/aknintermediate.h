/*
*	Name : AknIntermediate.h
*	Part of : Avkon
*   Version:
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
*/
#ifndef __AKNINTERMEDIATE__
#define __AKNINTERMEDIATE__

/** Intermediate state
 *
 * To implement intermediate states:
 * 1) add iAvkonEnv->RegisterIntermediateState(this) to dialog's ActivateL()
 * 2) add iAvkonEnv->UnRegisterIntermediateState(this) to destructor
 * 3) derive your control from MAknIntermediateState.
 * 4) implement CloseState() method. It should call TryExitL() or something.
 * (NOTE, the method is NOT L-method, so use T_RAPD(err, TryExitL(buttonid));
 *
 * This will cause your intermediate states to close automatically when
 * you swap to another application.
 */

class MAknIntermediateState
    {
public:
    virtual void CloseState() = 0;
    };

#endif
