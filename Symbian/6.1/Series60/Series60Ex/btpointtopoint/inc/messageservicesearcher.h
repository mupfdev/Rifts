/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __MESSAGESERVICESEARCHER_H__
#define __MESSAGESERVICESEARCHER_H__

#include <e32base.h>
#include "BTServiceSearcher.h"
#include "Log.h"

/*! 
  @class CMessageServiceSearcher
  
  @discussion Searches for a message service.
  */
class CMessageServiceSearcher : public CBTServiceSearcher
    {
public:
/*!
  @function NewL
   
  @discussion Create a CMessageServiceSearcher object
  @param aLog the log to send output to
  @result a pointer to the created instance of CMessageServiceSearcher
  */
    static CMessageServiceSearcher* NewL(MLog& aLog);

/*!
  @function NewLC
   
  @discussion Create a CMessageServiceSearcher object
  @param aLog the log to send output to
  @result a pointer to the created instance of CMessageServiceSearcher
  */
    static CMessageServiceSearcher* NewLC(MLog& aLog);

/*!
  @function ~CMessageServiceSearcher
  
  @discussion Destroy the object and release all memory objects. Close any open sockets
  */
    ~CMessageServiceSearcher();

/*!
  @function Port
   
  @discussion Retrieve the port on which the service is installed
  @result the port number
  */
    TInt Port();

protected:

/*!
  @function ServiceClass

  @result the service class uid.
  */
    const TUUID& ServiceClass() const;

/*!
  @function ProtocolList

  @result the attribute list.
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
  @function CMessageServiceSearcher

  @discussion Constructs this object
  @param aLog the log to send output to
  */
    CMessageServiceSearcher(MLog& aLog);

/*!
  @function ConstructL

  @discussion Performs second phase construction of this object
  */
    void ConstructL();

private:
    /*! @var iServiceClass the service class UUID to search for */
    TUUID iServiceClass;

    /*! @var iPort the port number that the remote service is installed */
    TInt iPort;
    };

#endif // __MESSAGESERVICESEARCHER_H__

