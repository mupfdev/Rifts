/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __TBTATTRIBUTEVALUELISTER_H__
#define __TBTATTRIBUTEVALUELISTER_H__

#include <btsdp.h>
#include "Reporter.h"

/*! 
  @class TBTAttributeValueLister
  
  @discussion An instance of TBTAttributeValueLister is used to log an SDP 
              Attribute value
  */

class TBTAttributeValueLister : public MSdpAttributeValueVisitor 
    {
public:
/*!
  @function TBTAttributeValueLister

  @discussion constructs instance and uses aReporter to list output
  @param reporter the logging class instance
  */
    TBTAttributeValueLister(MReporter& aReporter);

public: // from MSdpAttributeValueVisitor
/*!
  @function VisitAttributeValueL

  @discussion prints attribute value and type to the log
  @param aValue Attribute value
  @param aType Attribute type
  */
    void VisitAttributeValueL(CSdpAttrValue& aValue, TSdpElementType aType);

/*!
  @function StartListL

  @discussion increases the indentation
  @param aList Attribute value list
  */
    void StartListL(CSdpAttrValueList& aList);

/*!
  @function EndListL
  
  @discussion decreases the indentation
  */
    void EndListL();

private: // methods
/*!
  @function Print
  
  @discussion prints the str to the log
  @param str the string to print
  */
    void Print(const TDesC8& aStr);

private: // data
    
    /*! @var iReporter reporting instance. */    
    MReporter& iReporter;
    
    /*! @var iIndentationLevel level of indentation required in logging. */    
    TInt iIndentationLevel;
    };


#endif // __TBTATTRIBUTEVALUELISTER_H__
