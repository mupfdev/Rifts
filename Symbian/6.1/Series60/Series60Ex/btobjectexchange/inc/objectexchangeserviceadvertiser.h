/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __COBJECTEXCHANGE_SERVICE_ADVERTISER__
#define __COBJECTEXCHANGE_SERVICE_ADVERTISER__ 

#include <e32base.h>
#include <btsdp.h>
#include <btmanclient.h>

#include "BTServiceAdvertiser.h"

/*! 
  @class CObjectExchangeServiceAdvertiser
  
  @discussion Advertises the OBEX service using the SDP database.
  */
class CObjectExchangeServiceAdvertiser : public CBTServiceAdvertiser
    {
public:
/*!
  @function NewL
   
  @discussion Create a CObjectExchangeServiceAdvertiser object
  @result a pointer to the created instance of CObjectExchangeServiceAdvertiser
  */
    static CObjectExchangeServiceAdvertiser* NewL();

/*!
  @function NewLC
   
  @discussion Create a CObjectExchangeServiceAdvertiser object
  @result a pointer to the created instance of CObjectExchangeServiceAdvertiser
  */
    static CObjectExchangeServiceAdvertiser* NewLC();

/*!
  @function ~CObjectExchangeServiceAdvertiser
  
  @discussion Destroy the object and release all memory objects
  */
    ~CObjectExchangeServiceAdvertiser();

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
/*!
  @function CObjectExchangeServiceAdvertiser
  
  @discussion Constructs this object
  */
    CObjectExchangeServiceAdvertiser();

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CObjectExchangeServiceAdvertiser object
  */
    void ConstructL();
    };

#endif // __COBJECTEXCHANGE_SERVICE_ADVERTISER__