/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __BTOBJECTEXCHANGE_DOCUMENT_H__
#define __BTOBJECTEXCHANGE_DOCUMENT_H__


#include <akndoc.h>

// Forward references
class CBTObjectExchangeAppUi;
class CEikApplication;


/*! 
  @class CBTObjectExchangeDocument
  
  @discussion An instance of class CBTObjectExchangeDocument is the Document part of the AVKON
  application framework for the BTObjectExchange example application
  */
class CBTObjectExchangeDocument : public CAknDocument
    {
public:

/*!
  @function NewL
  
  @discussion Construct a CBTObjectExchangeDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CBTObjectExchangeDocument
  */
    static CBTObjectExchangeDocument* NewL(CEikApplication& aApp);

/*!
  @function NewLC
  
  @discussion Construct a CBTObjectExchangeDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CBTObjectExchangeDocument
  */
    static CBTObjectExchangeDocument* NewLC(CEikApplication& aApp);

/*!
  @function ~CBTObjectExchangeDocument
  
  @discussion Destroy the object and release all memory objects
  */
    ~CBTObjectExchangeDocument();

public: // from CEikDocument
/*!
  @function CreateAppUiL 
  
  @discussion Create a CBTObjectExchangeAppUi object and return a pointer to it
  @result a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL();
private:

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CBTObjectExchangeDocument object
  */
    void ConstructL();

/*!
  @function CBTObjectExchangeDocument
  
  @discussion Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
    CBTObjectExchangeDocument(CEikApplication& aApp);

    };


#endif // __BTOBJECTEXCHANGE_DOCUMENT_H__
