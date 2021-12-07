/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __CBTSERVICE_ADVERTISER__
#define __CBTSERVICE_ADVERTISER__

#include <e32base.h>
#include <btsdp.h>
#include <btmanclient.h>

#include "BTServiceAdvertiser.h"

/*! 
  @class CBTServiceAdvertiser
  
  @discussion Advertises a service in the SDP database.
  */
class CBTServiceAdvertiser : public CBase
    {
public:
/*!
  @function ~CBTServiceAdvertiser
  
  @discussion Destroy the object, close all open handles and remove the advertised service.
  */
    ~CBTServiceAdvertiser();

/*!
  @function StartAdvertisingL

  @discussion Start the advertising of this service
  @param aPort the port being used by the service 
  */
    void StartAdvertisingL(TInt aPort);

/*!
  @function StopAdvertisingL

  @discussion Stop advertising this service. Remove the record from the sdp database
  */
    void StopAdvertisingL();

/*!
  @function IsAdvertising

  @discussion Does the SDP database contain a record for this service
  @result ETRUE whether the service is being advertised
  */
    TBool IsAdvertising();

/*!
  @function UpdateAvailabilityL
  
  @discussion Update the service availability field of the service record
  @param aIsAvailable ETrue is the service is not busy.
  */
    void UpdateAvailabilityL(TBool aIsAvailable);

protected:
/*!
  @function CBTServiceAdvertiser
  
  @discussion Construct this object 
  */
    CBTServiceAdvertiser();

/*!
  @function BuildProtocolDescriptionL
  
  @discussion Builds the protocol description
  @param aProtocolDescriptor the protocol descriptor
  @param aPort the service port
  */
    virtual void BuildProtocolDescriptionL(CSdpAttrValueDES* aProtocolDescriptor, TInt aPort) = 0;

/*!
  @function ServiceClass
  
  @result the service class
  */
    virtual const TInt ServiceClass() = 0;

/*!
  @function ServiceName
  
  @result the service name
  */
    virtual const TDesC& ServiceName() = 0;

/*!
  @function ServiceDescription
  
  @result the service description
  */
    virtual const TDesC& ServiceDescription() = 0;
        
private:
/*!
  @function ConnectL
  
  @discussion Connect to the SDP database
  */    
    void ConnectL();

private:

    /*! @var iSdpSession a handle to the SDP session */
    RSdp iSdpSession;

    /*! @var iSdpDatabase a connection to the SDP database */
    RSdpDatabase iSdpDatabase;

    /*! @var iRecord the record handle of the service record for this server */
    TSdpServRecordHandle iRecord;

    /*! @var iRecordState the current record state - change number */
    TInt iRecordState;

    /*! @var iIsConnected has a connection been made to the SDP Database */
    TBool iIsConnected;
    };

#endif // __CBTSERVICE_ADVERTISER__
