/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __FOCUSEVENTDOCUMENT_H__
#define __FOCUSEVENTDOCUMENT_H__


#include <eikdoc.h>

// Forward references
class CFocusEventAppUi;
class CEikApplication;


/*! 
  @class CFocusEventDocument
  
  @discussion An instance of class CFocusEventDocument is the Document part of the AVKON
  application framework for the FocusEvent example application
  */
class CFocusEventDocument : public CEikDocument
    {
public:

/*!
  @function NewL
  
  @discussion Construct a CFocusEventDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CFocusEventDocument
  */
    static CFocusEventDocument* NewL(CEikApplication& aApp);

/*!
  @function NewLC
  
  @discussion Construct a CFocusEventDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CFocusEventDocument
  */
    static CFocusEventDocument* NewLC(CEikApplication& aApp);

/*!
  @function ~CFocusEventDocument
  
  @discussion Destroy the object and release all memory objects
  */
    ~CFocusEventDocument();

private:

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CFocusEventDocument object
  */
    void ConstructL();

/*!
  @function CFocusEventDocument
  
  @discussion Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
    CFocusEventDocument(CEikApplication& aApp);

/*!
  @function CreateAppUiL 
  
  @discussion Create a CFocusEventAppUi object and return a pointer to it
  @result a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL();
    };


#endif // __FOCUSEVENTDOCUMENT_H__
