/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __OBJECTEXCHANGESERVICESEARCHER_H__
#define __OBJECTEXCHANGESERVICESEARCHER_H__

#include <e32base.h>
#include "BTServiceSearcher.h"
#include "ObjectExchangeProtocolConstants.h"
#include "Log.h"

/*! 
  @class CObjectExchangeServiceSearcher
  
  @discussion Searches the remote SDP database for suitable OBEX servers.
  */
class CObjectExchangeServiceSearcher : public CBTServiceSearcher
    {
public:
/*!
  @function NewL
  
  @discussion Construct a CObjectExchangeServiceSearcher
  @param aLog the log to send output to
  @result a pointer to the created instance of CObjectExchangeServiceSearcher
  */
    static CObjectExchangeServiceSearcher* NewL(MLog& aLog);

/*!
  @function NewLC
  
  @discussion Construct a CObjectExchangeServiceSearcher
  @param aLog the log to send output to
  @result a pointer to the created instance of CObjectExchangeServiceSearcher
  */
    static CObjectExchangeServiceSearcher* NewLC(MLog& aLog);

/*!
  @function ~CObjectExchangeServiceSearcher
  
  @discussion Destroy the object and release all memory objects
  */
    ~CObjectExchangeServiceSearcher();

/*!
  @function Port
  
  @result the port to connect to on the remote machine
  */
    TInt Port();

protected:

/*!
  @function ServiceClass
  
  @discussion The service class to search for
  @result the service class UUID
  */
    const TUUID& ServiceClass() const;

/*!
  @function ProtocolList
  
  @discussion The list of Protocols required by the service.
  */
    const TSdpAttributeParser::TSdpAttributeList& ProtocolList() const;

/*!
  @function FoundElementL
  
  @discussion Read the data element
  @param aKey a key that identifies the element
  @param aValue the data element
  */
    virtual void FoundElementL(TInt aKey, CSdpAttrValue& aValue);

private:
/*!
  @function CObjectExchangeServer
  
  @param aLog the log to send output to
  @discussion Constructs this object
  */
    CObjectExchangeServiceSearcher(MLog& aLog);

/*!
  @function ConstructL
  
  @discussion 2nd phase construction of this object
  */
    void ConstructL();

private:
    /*! @var iServiceClass the service class to search for */
    TUUID iServiceClass;

    /*! @var iPort the port to connect to on the remote machine */
    TInt iPort;
    };

#endif // __OBJECTEXCHANGESERVICESEARCHER_H__

