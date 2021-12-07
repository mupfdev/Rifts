/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __HELLOWORLD_DOCUMENT_H__
#define __HELLOWORLD_DOCUMENT_H__


#include <akndoc.h>

// Forward references
class CHelloWorldAppUi;
class CEikApplication;


/*! 
  @class CHelloWorldDocument
  
  @discussion An instance of class CHelloWorldDocument is the Document part of the AVKON
  application framework for the HelloWorld example application
  */
class CHelloWorldDocument : public CAknDocument
    {
public:

/*!
  @function NewL
  
  @discussion Construct a CHelloWorldDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CHelloWorldDocument
  */
    static CHelloWorldDocument* NewL(CEikApplication& aApp);

/*!
  @function NewLC
  
  @discussion Construct a CHelloWorldDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CHelloWorldDocument
  */
    static CHelloWorldDocument* NewLC(CEikApplication& aApp);

/*!
  @function ~CHelloWorldDocument
  
  @discussion Destroy the object and release all memory objects
  */
    ~CHelloWorldDocument();

public: // from CAknDocument
/*!
  @function CreateAppUiL 
  
  @discussion Create a CHelloWorldAppUi object and return a pointer to it
  @result a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL();

private:

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CHelloWorldDocument object
  */
    void ConstructL();

/*!
  @function CHelloWorldDocument
  
  @discussion Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
    CHelloWorldDocument(CEikApplication& aApp);

    };


#endif // __HELLOWORLD_DOCUMENT_H__
