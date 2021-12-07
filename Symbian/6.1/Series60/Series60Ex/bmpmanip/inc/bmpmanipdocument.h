/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __BMPMANIPDOCUMENT_H__
#define __BMPMANIPDOCUMENT_H__


#include <eikdoc.h>

// Forward references
class CBmpmanipAppUi;
class CEikApplication;


/*! 
  @class CBmpmanipDocument
  
  @discussion An instance of class CBmpmanipDocument is the Document part of the AVKON
  application framework for the Bmpmanip example application
  */
class CBmpmanipDocument : public CEikDocument
    {
public:

/*!
  @function NewL
  
  @discussion Construct a CBmpmanipDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CBmpmanipDocument
  */
    static CBmpmanipDocument* NewL(CEikApplication& aApp);

/*!
  @function NewLC
  
  @discussion Construct a CBmpmanipDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CBmpmanipDocument
  */
    static CBmpmanipDocument* NewLC(CEikApplication& aApp);

/*!
  @function ~CBmpmanipDocument
  
  @discussion Destroy the object and release all memory objects
  */
    ~CBmpmanipDocument();

private:

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CBmpmanipDocument object
  */
    void ConstructL();

/*!
  @function CBmpmanipDocument
  
  @discussion Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
    CBmpmanipDocument(CEikApplication& aApp);

/*!
  @function CreateAppUiL 
  
  @discussion Create a CBmpmanipAppUi object and return a pointer to it
  @result a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL();
    };


#endif // __BMPMANIPDOCUMENT_H__
