/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __HELLOWORLDPLUS_DOCUMENT_H__
#define __HELLOWORLDPLUS_DOCUMENT_H__


#include <akndoc.h>

// Forward references
class CHelloWorldPlusAppUi;
class CEikApplication;


/*! 
  @class CHelloWorldPlusDocument
  
  @discussion An instance of class CHelloWorldPlusDocument is the Document part of the AVKON
  application framework for the HelloWorldPlus example application
  */
class CHelloWorldPlusDocument : public CAknDocument
    {
public:

/*!
  @function NewL
  
  @discussion Construct a CHelloWorldPlusDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CHelloWorldPlusDocument
  */
    static CHelloWorldPlusDocument* NewL(CEikApplication& aApp);

/*!
  @function NewLC
  
  @discussion Construct a CHelloWorldPlusDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CHelloWorldPlusDocument
  */
    static CHelloWorldPlusDocument* NewLC(CEikApplication& aApp);

/*!
  @function ~CHelloWorldPlusDocument
  
  @discussion Destroy the object and release all memory objects
  */
    ~CHelloWorldPlusDocument();

/*!
  @function CreateAppUiL 
  
  @discussion Create a CHelloWorldPlusAppUi object and return a pointer to it
  @result a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL();
private:

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CHelloWorldPlusDocument object
  */
    void ConstructL();

/*!
  @function CHelloWorldPlusDocument
  
  @discussion Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
    CHelloWorldPlusDocument(CEikApplication& aApp);

    };


#endif // __HELLOWORLDPLUS_DOCUMENT_H__
