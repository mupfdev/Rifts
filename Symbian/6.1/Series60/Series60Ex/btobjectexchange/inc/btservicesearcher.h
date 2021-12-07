/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __BTSERVICESEARCHER_H__
#define __BTSERVICESEARCHER_H__

#include <e32base.h>
#include <bttypes.h>
#include <btextnotifiers.h>

#include "SdpAttributeParser.h"
#include "SdpAttributeNotifier.h"
#include "Log.h"

/*! 
  @class CBTServiceSearcher
  
  @discussion Searches for a service on a remote machine
  */

class CBTServiceSearcher : public CBase,
                           public MSdpAgentNotifier,
                           public MSdpAttributeNotifier
    {
public:
/*!
  @function ~CBTServiceSearcher
  
  @discussion Destroy the object and release all memory objects
  */
    ~CBTServiceSearcher();

/*!
  @function SelectDeviceByDiscoveryL
  
  @discussion Select a device
  @param aObserverRequestStatus the observer that is to be notified when the device selection is complete
  */
    void SelectDeviceByDiscoveryL(TRequestStatus& aObserverRequestStatus);
    
/*!
  @function FindServiceL
  
  @discussion Find a service on the specified device
  @param aObserverRequestStatus the observer that is to be notified when the service search is complete
  */    
    void FindServiceL(TRequestStatus& iObserverRequestStatus);

/*!
  @function BTDevAddr
  
  @result the bluetooth device address
  */    
    const TBTDevAddr& BTDevAddr();

/*!
  @function ResponseParams
  
  @result Information about the device selected by the user
  */
    const TBTDeviceResponseParams& ResponseParams();

protected:
/*!
  @function CBTServiceSearcher
  
  @param aLog the log to send output to
  @discussion Constructs this object
  */
    CBTServiceSearcher(MLog& aLog);

/*!
  @function Finished
  
  @discussion The search has finished. Notify the observer that the process is complete.
  */
    virtual void Finished(TInt aError = KErrNone);

/*!
  @function HasFinishedSearching
  
  @discussion Is the instance still wanting to search.
  @result EFalse if the instance wants searching to continue.
  */
    virtual TBool HasFinishedSearching() const;

/*!
  @function HasFoundService
  
  @result ETrue if a service has been found
  */
    TBool HasFoundService() const;

protected: // abstract methods

/*!
  @function ProtocolList
  
  @discussion The list of Protocols required by the service.
  */
    virtual const TSdpAttributeParser::TSdpAttributeList& ProtocolList() const = 0;

/*!
  @function ServiceClass
  
  @discussion The service class to search for
  @result the service class UUID
  */
    virtual const TUUID& ServiceClass() const = 0;

/*!
  @function FoundElementL
  
  @discussion Read the data element
  @param aKey a key that identifies the element
  @param aValue the data element
  */
    virtual void FoundElementL(TInt aKey, CSdpAttrValue& aValue) = 0;

public: // from MSdpAgentNotifier
/*!
  @function NextRecordRequestComplete
  
  @discussion Process the result of the next record request
  @param aError the error code
  @param aHandle the handle of the service record
  @param aTotalRecordsCount the total number of matching service records
  */
    void NextRecordRequestComplete(TInt aError, TSdpServRecordHandle aHandle, TInt aTotalRecordsCount);

/*!
  @function AttributeRequestResult
  
  @discussion Process the next attribute requested
  @param aHandle the handle of the service record
  @param aAttrID the id of the attribute
  @parma aAttrValue the value of the attribute
  */
    void AttributeRequestResult(TSdpServRecordHandle aHandle, TSdpAttributeID aAttrID, CSdpAttrValue* aAttrValue);

/*!
  @function AttributeRequestComplete
  
  @discussion Process the arrtibute request completion
  @param aHandle the handle of the service record
  @param aError the error code
  */
    void AttributeRequestComplete(TSdpServRecordHandle aHandle, TInt aError);

private:

/*!
  @function NextRecordRequestCompleteL
  
  @discussion Process the result of the next record request
  @param aError the error code
  @param aHandle the handle of the service record
  @param aTotalRecordsCount the total number of matching service records
  */
    void NextRecordRequestCompleteL(TInt aError, TSdpServRecordHandle aHandle, TInt aTotalRecordsCount);

/*!
  @function AttributeRequestResultL
  
  @discussion Process the next attribute requested
  @param aHandle the handle of the service record
  @param aAttrID the id of the attribute
  @parma aAttrValue the value of the attribute
  */
    void AttributeRequestResultL(TSdpServRecordHandle aHandle, TSdpAttributeID aAttrID, CSdpAttrValue* aAttrValue);

/*!
  @function AttributeRequestCompleteL
  
  @discussion Process the arrtibute request completion
  @param aHandle the handle of the service record
  @param aError the error code
  */
    void AttributeRequestCompleteL(TSdpServRecordHandle, TInt aError);

private:
    /*! @var iStatusObserver pointer to the request status observer */
    TRequestStatus* iStatusObserver;
    
    /*! @var iIsDeviceSelectorConnected is the device selector connected ? */
    TBool iIsDeviceSelectorConnected;

    /*! @var iDeviceSelector a handle to the bluetooth device selector notifier */
    RNotifier iDeviceSelector;

    /*! @var iResponse the response of the device selection */
    TBTDeviceResponseParamsPckg iResponse;

    /*! @var iAgent a connetction to the SDP client */
    CSdpAgent* iAgent;

    /*! @var iSdpSearchPattern a search pattern */
    CSdpSearchPattern* iSdpSearchPattern;

    /*! @var iHasFoundService has the service been found ? */
    TBool iHasFoundService;

    /*! @var iLog the log to send output to */
    MLog& iLog;
    };

#endif // __BTSERVICESEARCHER_H__

