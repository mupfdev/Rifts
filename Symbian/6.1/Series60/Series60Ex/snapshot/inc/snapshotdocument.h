/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __SNAPSHOTDOCUMENT_H__
#define __SNAPSHOTDOCUMENT_H__


#include <eikdoc.h>

// Forward references
class CSnapShotAppUi;
class CEikApplication;


/*! 
  @class CSnapShotDocument
  
  @discussion An instance of class CSnapShotDocument is the Document part of the AVKON
  application framework for the SnapShot example application
  */
class CSnapShotDocument : public CEikDocument
    {
public:

/*!
  @function NewL
  
  @discussion Construct a CSnapShotDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CSnapShotDocument
  */
    static CSnapShotDocument* NewL(CEikApplication& aApp);

/*!
  @function NewLC
  
  @discussion Construct a CSnapShotDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CSnapShotDocument
  */
    static CSnapShotDocument* NewLC(CEikApplication& aApp);

/*!
  @function ~CSnapShotDocument
  
  @discussion Destroy the object and release all memory objects
  */
    ~CSnapShotDocument();

private:

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CSnapShotDocument object
  */
    void ConstructL();

/*!
  @function CSnapShotDocument
  
  @discussion Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
    CSnapShotDocument(CEikApplication& aApp);

/*!
  @function CreateAppUiL 
  
  @discussion Create a CSnapShotAppUi object and return a pointer to it
  @result a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL();
    };


#endif // __SNAPSHOTDOCUMENT_H__
