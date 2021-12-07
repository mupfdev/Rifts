/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __BTPOINTTOPOINT_DOCUMENT_H__
#define __BTPOINTTOPOINT_DOCUMENT_H__


#include <akndoc.h>

// Forward references
class CBTPointToPointAppUi;
class CEikApplication;


/*! 
  @class CBTPointToPointDocument
  
  @discussion An instance of class CBTPointToPointDocument is the Document part of the AVKON
  application framework for the BTPointToPoint example application
  */
class CBTPointToPointDocument : public CAknDocument
    {
public:

/*!
  @function NewL
  
  @discussion Construct a CBTPointToPointDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CBTPointToPointDocument
  */
    static CBTPointToPointDocument* NewL(CEikApplication& aApp);

/*!
  @function NewLC
  
  @discussion Construct a CBTPointToPointDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CBTPointToPointDocument
  */
    static CBTPointToPointDocument* NewLC(CEikApplication& aApp);

/*!
  @function ~CBTPointToPointDocument
  
  @discussion Destroy the object and release all memory objects
  */
    ~CBTPointToPointDocument();

public: // from CEikDocument
/*!
  @function CreateAppUiL 
  
  @discussion Create a CBTPointToPointAppUi object and return a pointer to it
  @result a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL();

private:

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CBTPointToPointDocument object
  */
    void ConstructL();

/*!
  @function CBTPointToPointDocument
  
  @discussion Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
    CBTPointToPointDocument(CEikApplication& aApp);

    };


#endif // __BTPOINTTOPOINTDOCUMENT_H__
