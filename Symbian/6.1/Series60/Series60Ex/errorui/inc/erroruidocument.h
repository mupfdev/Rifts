/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __ERRORUI_DOCUMENT_H__
#define __ERRORUI_DOCUMENT_H__


#include <akndoc.h>

// Forward references
class CErrorUiAppUi;
class CEikApplication;


/*! 
  @class CErrorUiDocument
  
  @discussion An instance of class CErrorUiDocument is the Document part of the AVKON
  application framework for the ErrorUi example application
  */
class CErrorUiDocument : public CAknDocument
    {
public:

/*!
  @function NewL
  
  @discussion Construct a CErrorUiDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CErrorUiDocument
  */
    static CErrorUiDocument* NewL(CEikApplication& aApp);

/*!
  @function NewLC
  
  @discussion Construct a CErrorUiDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CErrorUiDocument
  */
    static CErrorUiDocument* NewLC(CEikApplication& aApp);

/*!
  @function ~CErrorUiDocument
  
  @discussion Destroy the object and release all memory objects
  */
    ~CErrorUiDocument();

public: // from CAknDocument
/*!
  @function CreateAppUiL 
  
  @discussion Create a CErrorUiAppUi object and return a pointer to it
  @result a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL();

private:

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CErrorUiDocument object
  */
    void ConstructL();

/*!
  @function CErrorUiDocument
  
  @discussion Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
    CErrorUiDocument(CEikApplication& aApp);

    };


#endif // __ERRORUI_DOCUMENT_H__
