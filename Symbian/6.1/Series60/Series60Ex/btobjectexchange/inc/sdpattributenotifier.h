/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __SDP_ATTRIBUTE_NOTIFIER_H__
#define __SDP_ATTRIBUTE_NOTIFIER_H__

class CSdpAttrValue;


/*! 
  @class MSdpAttributeNotifier
  
  @discussion An instance of MSdpAttributeNotifier is used to read selected SDP Attribute
  elements from an attribute value.
  */
class MSdpAttributeNotifier
    {
public:
/*!
  @function FoundElementL
  
  @discussion Read the data element
  @param aKey a key that identifies the element
  @param aValue the data element
  */
    virtual void FoundElementL(TInt aKey, CSdpAttrValue& aValue) = 0;

    };


#endif // __SDP_ATTRIBUTE_NOTIFIER_H__