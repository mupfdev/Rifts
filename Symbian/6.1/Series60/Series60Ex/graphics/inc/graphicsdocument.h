/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __GRAPHICSDOCUMENT_H__
#define __GRAPHICSDOCUMENT_H__


#include <eikdoc.h>

// Forward references
class CGraphicsAppUi;
class CEikApplication;


/*! 
  @class CGraphicsDocument
  
  @discussion An instance of class CGraphicsDocument is the Document part of the AVKON
  application framework for the Graphics example application
  */
class CGraphicsDocument : public CEikDocument
    {
public:

/*!
  @function NewL
  
  @discussion Construct a CGraphicsDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CGraphicsDocument
  */
    static CGraphicsDocument* NewL(CEikApplication& aApp);

/*!
  @function NewLC
  
  @discussion Construct a CGraphicsDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CGraphicsDocument
  */
    static CGraphicsDocument* NewLC(CEikApplication& aApp);

/*!
  @function ~CGraphicsDocument
  
  @discussion Destroy the object and release all memory objects
  */
    ~CGraphicsDocument();

private:

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CGraphicsDocument object
  */
    void ConstructL();

/*!
  @function CGraphicsDocument
  
  @discussion Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
    CGraphicsDocument(CEikApplication& aApp);

/*!
  @function CreateAppUiL 
  
  @discussion Create a CGraphicsAppUi object and return a pointer to it
  @result a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL();
    };


#endif // __GRAPHICSDOCUMENT_H__
