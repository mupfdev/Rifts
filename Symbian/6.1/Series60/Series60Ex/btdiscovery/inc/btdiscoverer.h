/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __CBTDISCOVERER_H__
#define __CBTDISCOVERER_H__

#include <coecntrl.h>
#include <btmanclient.h>
#include <btextnotifiers.h>
#include <aknlists.h>
#include <btsdp.h>
#include <aknglobalprogressdialog.h> 

#include "Reporter.h"

/*! 
  @class CBTDiscoverer
  
  @discussion Finds a BT Device and displays its services.
  */

class CBTDiscoverer : public CBase, public MSdpAgentNotifier
    {
public:
/*!
  @function NewL

  @discussion Create a CBTDiscoverer object
  @param aReporter Reporter used for log
  @result a pointer to the created instance of CBTDiscoverer
  */

    static CBTDiscoverer* NewL(MReporter& aReporter);
    
/*!
  @function NewLC

  @discussion Create a CBTDiscoverer object
  @param aReporter Reporter used for log
  @result a pointer to the created instance of CBTDiscoverer
  */
    
    static CBTDiscoverer* NewLC(MReporter& aReporter);

/*!
  @function ~CBTDiscoverer

  @discussion Destroy the object and release all memory objects
*/

    ~CBTDiscoverer();

private:
/*!
  @function CBTDiscoverer

  @discussion Perform the first phase of two phase construction 
  @param aReporter logs the output from this class
  */

    CBTDiscoverer(MReporter& aReporter);

/*!
  @function ConstructL

  @discussion  Perform the second phase construction of a CBTDiscoverer object
  */

    void ConstructL();

public: // From MSdpAgentNotifier
/*!
  @function NextRecordRequestComplete

  @discussion Called when an service record request 
              (CSdpAgent::NextRecordRequestComplete()) operation completes.
  @param aError KErrNone, or an SDP error
  @param aHandle Service record for which the query was made
  @param aTotalRecordsCount Total number of matching records
  */

    void NextRecordRequestComplete(TInt aError, 
                                   TSdpServRecordHandle aHandle, 
                                   TInt aTotalRecordsCount);
/*!
  @function AttributeRequestResult
  
  @discussion Called by the attribute request function 
              (CSdpAgent::AttributeRequestL()) to pass the results of 
              a successful attribute request.
  @param aHandle Service record for which the query was made
  @param aAttrID ID of the attribute obtained
  @param aAttrValue Attribute value obtained
  */

    void AttributeRequestResult(TSdpServRecordHandle aHandle, 
                                TSdpAttributeID aAttrID, 
                                CSdpAttrValue* aAttrValue);

/*!
  @function AttributeRequestComplete

  @discussion Called when an service record request 
              (CSdpAgent::NextRecordRequestComplete()) 
              operation completes.
  @param aHandle Service record for which the query was made
  @param aError KErrNone, or an SDP error
  */

    void AttributeRequestComplete(TSdpServRecordHandle aHandle, TInt aError);

public:

/*! 
  @function ListServicesL 

  @discussion lists the services advertised from a specified bluetooth
                device
  @param aAddress the bluetooth address to query for services
 */
    void ListServicesL(const TBTDevAddr& aAddress);

/*! 
  @function SelectDeviceL
    
  @discussion offers the user the opportunity to select a bluetooth
                device
  @param aResponse the details of the selected device.
  @result ETrue if a device is selected
 */
    TBool SelectDeviceL(TBTDeviceResponseParamsPckg& aResponse);

private:
/*! 
  @function PrintSDPError
    
  @discussion prints a description of the SDP error
  @param aError the error code.
  */
    void PrintSDPError(TInt aError);

private:
    /*! @var iAgent used to search the SDP database */
    CSdpAgent* iAgent;

    /*! @var iSdpSearchPattern used to filter the SDP database search */
    CSdpSearchPattern* iSdpSearchPattern;

    /*! @var iMatchList used to filter the list of attributes */
    CSdpAttrIdMatchList* iMatchList;

    /*! @var iReporter used to log results */
    MReporter& iReporter;

    /*! @var iPrintRecordNumber print the number of records */
    TBool iHasPrintedRecordNumber;

    /*! @var iPrintHandle print the handle */
    TBool iHasPrintedHandle;
    };

#endif //__CBTDISCOVERER_H__