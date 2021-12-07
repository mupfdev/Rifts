/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __DIALERDOCUMENT_H__
#define __DIALERDOCUMENT_H__


#include <eikdoc.h>

// Forward references
class CDialerAppUi;
class CEikApplication;


/*! 
  @class CDialerDocument
  
  @discussion An instance of class CDialerDocument is the Document part of the AVKON
  application framework for the Dialer example application
  */
class CDialerDocument : public CEikDocument
    {
public:

/*!
  @function NewL
  
  @discussion Construct a CDialerDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CDialerDocument
  */
    static CDialerDocument* NewL(CEikApplication& aApp);

/*!
  @function NewLC
  
  @discussion Construct a CDialerDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CDialerDocument
  */
    static CDialerDocument* NewLC(CEikApplication& aApp);

/*!
  @function ~CDialerDocument
  
  @discussion Destroy the object and release all memory objects
  */
    ~CDialerDocument();

private:

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CDialerDocument object
  */
    void ConstructL();

/*!
  @function CDialerDocument
  
  @discussion Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
    CDialerDocument(CEikApplication& aApp);

/*!
  @function CreateAppUiL 
  
  @discussion Create a CDialerAppUi object and return a pointer to it
  @result a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL();
    };


#endif // __DIALERDOCUMENT_H__
