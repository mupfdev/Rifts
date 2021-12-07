/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __BTDISCOVERYDOCUMENT_H__
#define __BTDISCOVERYDOCUMENT_H__


#include <AknDoc.h> 

// Forward references
class CBTDiscoveryAppUi;
class CEikApplication;


/*! 
  @class CBTDiscoveryDocument
  
  @discussion An instance of class CBTDiscoveryDocument is the Document part of the AVKON
  application framework for the BTDiscovery example application
  */
class CBTDiscoveryDocument : public CAknDocument
    {
public:

/*!
  @function NewL
  
  @discussion Construct a CBTDiscoveryDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CBTDiscoveryDocument
  */
    static CBTDiscoveryDocument* NewL(CEikApplication& aApp);

/*!
  @function NewLC
  
  @discussion Construct a CBTDiscoveryDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CBTDiscoveryDocument
  */
    static CBTDiscoveryDocument* NewLC(CEikApplication& aApp);

/*!
  @function ~CBTDiscoveryDocument
  
  @discussion Destroy the object and release all memory objects
  */
    ~CBTDiscoveryDocument();

public: // from CAknDocument
/*!
  @function CreateAppUiL 
  
  @discussion Create a CBTDiscoveryAppUi object and return a pointer to it
  @result a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL();

private:

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CBTDiscoveryDocument object
  */
    void ConstructL();

/*!
  @function CBTDiscoveryDocument
  
  @discussion Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
    CBTDiscoveryDocument(CEikApplication& aApp);

    };


#endif // __BTDISCOVERYDOCUMENT_H__
