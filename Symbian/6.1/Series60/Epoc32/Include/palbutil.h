/*
* ============================================================================
*  Name     : PAlbUtil from PhotoAlbum
*  Part of  : PhotoAlbum
*
*  Description:       
*          
*  Version  :
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
* ============================================================================
*/

#ifndef __PALBUTIL_H
#define __PALBUTIL_H

//  INCLUDES
#include <e32svr.h>

// FORWARD DECLARATIONS
class CPAlbPublisher;
class MPAlbSubscriber;
class TPAlbAutoSubscriber;

// CLASS DECLARATION
// ----------------------------------------------------------------------------
// MPAlbSubscriber
// ----------------------------------------------------------------------------
/**
 * The subscriber in the Publisher-Subscriber-Pattern.
 * The publisher calls the update method with the calling publisher
 * and a reason, why it gets called. The method than can decide what 
 * to do.
 */
class MPAlbSubscriber
    {        
    public:
    /**
     * This method is called by the publisher
     * @param aModel the calling publisher
     * @param aEvent the event why it is called
     */
    virtual void Update( const CPAlbPublisher* aModel, TInt aEvent ) = 0;
    };

// ----------------------------------------------------------------------------
// CPAlbPublisher
// ----------------------------------------------------------------------------
/**
 * The publisher in the Publisher-Subscriber-Pattern.
 * The publisher maintains a list of subscribers which get notify
 * if a event occurs (a reason).
 * This is an abstract class.
 * @see MSubscriber
 */
class CPAlbPublisher: public CBase
    {
public: // Constructors and destructors

        //           *** DEPRECATED - DO NOT USE ***
    /**
     * Default constructor
     */
    IMPORT_C CPAlbPublisher();

    /**
     * Destructor
     */
    IMPORT_C virtual ~CPAlbPublisher();

    /**
     * Second Phase constructor
     */
    IMPORT_C void ConstructL();

    public:
    /**
     * Attach a subscriber to the list.
     * @param aSubscriber the subscriber to attach
     */
    IMPORT_C void AttachL( MPAlbSubscriber* aSubscriber );

    /**
     * Detach a subscriber from the list
     * @param aSubscriber the subscriber to detach
     */
    IMPORT_C void Detach( MPAlbSubscriber* aSubscriber );

    /**
     * Notify all subscriber with a reason
     */
    IMPORT_C void Notify( TInt aReason );

private:    // Data
    // own: array for holding all subscribers
    CArrayPtrFlat<MPAlbSubscriber> iSubscribers;   
    };


// ----------------------------------------------------------------------------
// TPAlbAutoSubscriber
// ----------------------------------------------------------------------------

/**
 * Attach/Detach a subscriber to a publisher by creation/destruction. 
 */
class TPAlbAutoSubscriber
    {

public:  // Constructors and destructor
    /**
     * The default constructor
     */
     IMPORT_C TPAlbAutoSubscriber(); 

    /**
     * Destructor
     */
     IMPORT_C virtual ~TPAlbAutoSubscriber();

    public:
    /**
     * has to be called for connecting subscriber to publisher.
     */
     IMPORT_C void ConnectL( CPAlbPublisher* aPublisher, 
                             MPAlbSubscriber* aSubscriber );

private:    // Data

    // The publisher to connect to
    CPAlbPublisher* iPublisher;
    
    /// The subscriber which want to connect
    MPAlbSubscriber* iSubscriber;
    
    /// Flag for if connection was made
    TBool iIsConnected;
    };

#endif      // __PALBUTIL_H

// End of File
