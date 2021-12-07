/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __CMESSAGE_SERVICE_ADVERTISER__
#define __CMESSAGE_SERVICE_ADVERTISER__

#include <e32base.h>
#include <btsdp.h>
#include <btmanclient.h>

#include "BTServiceAdvertiser.h"

/*! 
  @class CMessageServiceAdvertiser
  
  @discussion Advertises the message service using the SDP database.
  */
class CMessageServiceAdvertiser : public CBTServiceAdvertiser
    {
public:
/*!
  @function NewL
   
  @discussion Create a CMessageServiceAdvertiser object
  @result a pointer to the created instance of CMessageServiceAdvertiser
  */
    static CMessageServiceAdvertiser* NewL();

/*!
  @function NewLC
   
  @discussion Create a CMessageServiceAdvertiser object, which will draw itself to aRect
  @result a pointer to the created instance of CMessageServiceAdvertiser
  */
    static CMessageServiceAdvertiser* NewLC();

/*!
  @function ~CMessageServiceAdvertiser
  
  @discussion Destroy the object and release all memory objects. Close any open sockets
  */
    ~CMessageServiceAdvertiser();

protected: // from CBTServiceAdvertiser
/*!
  @function BuildProtocolDescriptionL
  
  @discussion Builds the protocol description
  @param aProtocolDescriptor the protocol descriptor
  @param aPort the service port
  */
    void BuildProtocolDescriptionL(CSdpAttrValueDES* aProtocolDescriptor, TInt aPort);

/*!
  @function ServiceClass
  
  @result the service class
  */    
    const TInt ServiceClass();

/*!
  @function ServiceName
  
  @result the service name
  */
    const TDesC& ServiceName();

/*!
  @function ServiceDescription
  
  @result the service description
  */
    const TDesC& ServiceDescription();

private:

    CMessageServiceAdvertiser();
    };

#endif // __CMESSAGE_SERVICE_ADVERTISER__
