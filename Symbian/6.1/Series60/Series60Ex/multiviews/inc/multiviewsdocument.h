/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __MULTIVIEWS_DOCUMENT_H__
#define __MULTIVIEWS_DOCUMENT_H__


#include <akndoc.h>

// Forward references
class CMultiViewsAppUi;
class CEikApplication;


/*! 
  @class CMultiViewsDocument
  
  @discussion An instance of class CMultiViewsDocument is the Document part of the AVKON
  application framework for the MultiViews example application
  */
class CMultiViewsDocument : public CAknDocument
    {
public:

/*!
  @function NewL
  
  @discussion Construct a CMultiViewsDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CMultiViewsDocument
  */
    static CMultiViewsDocument* NewL(CEikApplication& aApp);

/*!
  @function NewLC
  
  @discussion Construct a CMultiViewsDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CMultiViewsDocument
  */
    static CMultiViewsDocument* NewLC(CEikApplication& aApp);

/*!
  @function ~CMultiViewsDocument
  
  @discussion Destroy the object and release all memory objects
  */
    ~CMultiViewsDocument();

public: // from CAknDocument
/*!
  @function CreateAppUiL 
  
  @discussion Create a CMultiViewsAppUi object and return a pointer to it
  @result a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL();

private:

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CMultiViewsDocument object
  */
    void ConstructL();

/*!
  @function CMultiViewsDocument
  
  @discussion Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
    CMultiViewsDocument(CEikApplication& aApp);

    };


#endif // __MULTIVIEWS_DOCUMENT_H__
