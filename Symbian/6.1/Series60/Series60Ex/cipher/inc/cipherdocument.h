/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __CIPHER_DOCUMENT_H__
#define __CIPHER_DOCUMENT_H__


#include <akndoc.h>

// Forward references
class CCipherAppUi;
class CEikApplication;


/*! 
  @class CCipherDocument
  
  @discussion An instance of class CCipherDocument is the Document part of the AVKON
  application framework for the Cipher example application
  */
class CCipherDocument : public CAknDocument
    {
public:

/*!
  @function NewL
  
  @discussion Construct a CCipherDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CCipherDocument
  */
    static CCipherDocument* NewL(CEikApplication& aApp);

/*!
  @function NewLC
  
  @discussion Construct a CCipherDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CCipherDocument
  */
    static CCipherDocument* NewLC(CEikApplication& aApp);

/*!
  @function ~CCipherDocument
  
  @discussion Destroy the object and release all memory objects
  */
    ~CCipherDocument();

public: // from CAknDocument
/*!
  @function CreateAppUiL 
  
  @discussion Create a CCipherAppUi object and return a pointer to it
  @result a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL();

private:

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CCipherDocument object
  */
    void ConstructL();

/*!
  @function CCipherDocument
  
  @discussion Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
    CCipherDocument(CEikApplication& aApp);

    };


#endif // __CIPHER_DOCUMENT_H__
