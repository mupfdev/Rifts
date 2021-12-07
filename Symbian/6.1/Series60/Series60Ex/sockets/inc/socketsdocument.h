/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __SOCKETSDOCUMENT_H__
#define __SOCKETSDOCUMENT_H__


#include <eikdoc.h>

// Forward references
class CSocketsAppUi;
class CEikApplication;


/*! 
  @class CSocketsDocument
  
  @discussion An instance of class CSocketsDocument is the Document part of the AVKON
  application framework for the Sockets example application
  */
class CSocketsDocument : public CEikDocument
    {
public:

/*!
  @function NewL
  
  @discussion Construct a CSocketsDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CSocketsDocument
  */
    static CSocketsDocument* NewL(CEikApplication& aApp);

/*!
  @function NewLC
  
  @discussion Construct a CSocketsDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CSocketsDocument
  */
    static CSocketsDocument* NewLC(CEikApplication& aApp);

/*!
  @function ~CSocketsDocument
  
  @discussion Destroy the object and release all memory objects
  */
    ~CSocketsDocument();

private:

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CSocketsDocument object
  */
    void ConstructL();

/*!
  @function CSocketsDocument
  
  @discussion Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
    CSocketsDocument(CEikApplication& aApp);

/*!
  @function CreateAppUiL 
  
  @discussion Create a CSocketsAppUi object and return a pointer to it
  @result a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL();
    };


#endif // __SOCKETSDOCUMENT_H__
