/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __ANIMATIONDOCUMENT_H__
#define __ANIMATIONDOCUMENT_H__


#include <eikdoc.h>

// Forward references
class CAnimationAppUi;
class CEikApplication;


/*! 
  @class CCSSyncDocument
  
  @discussion An instance of class CAnimationDocument is the Document part of the AVKON
  application framework for the Animation example application
  */
class CAnimationDocument : public CEikDocument
    {
public: // New methods

/*!
  @function NewL
  
  @discussion Construct a CAnimationDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CAnimationDocument
  */
    static CAnimationDocument* NewL(CEikApplication& aApp);

/*!
  @function NewLC
  
  @discussion Construct a CAnimationDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CAnimationDocument
  */
    static CAnimationDocument* NewLC(CEikApplication& aApp);

/*!
  @function ~CCSSyncDocument
  
  @discussion Destroy the object and release all memory objects
  */
    ~CAnimationDocument();

public: // from CEikDocument
/*!
  @function CreateAppUiL 
  
  @discussion Create a CAnimationAppUi object and return a pointer to it
  @result a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL(); 

private: // New methods

/*!
  @function CAnimationDocument
  
  @discussion Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
    CAnimationDocument(CEikApplication& aApp): CEikDocument(aApp)     {    }

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CAnimationDocument object
  */
    void ConstructL();

    };


#endif // __ANIMATIONDOCUMENT_H__
