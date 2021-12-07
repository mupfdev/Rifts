/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __BTADVERTISER_DOCUMENT_H__
#define __BTADVERTISER_DOCUMENT_H__


#include <akndoc.h>

// Forward references
class CBTAdvertiserAppUi;
class CEikApplication;


/*! 
  @class CBTAdvertiserDocument
  
  @discussion An instance of class CBTAdvertiserDocument is the Document part of the AVKON
  application framework for the BTAdvertiser example application
  */
class CBTAdvertiserDocument : public CAknDocument
    {
public:

/*!
  @function NewL
  
  @discussion Construct a CBTAdvertiserDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CBTAdvertiserDocument
  */
    static CBTAdvertiserDocument* NewL(CEikApplication& aApp);

/*!
  @function NewLC
  
  @discussion Construct a CBTAdvertiserDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CBTAdvertiserDocument
  */
    static CBTAdvertiserDocument* NewLC(CEikApplication& aApp);

/*!
  @function ~CBTAdvertiserDocument
  
  @discussion Destroy the object and release all memory objects
  */
    ~CBTAdvertiserDocument();

public: // from CEikDocument
/*!
  @function CreateAppUiL 
  
  @discussion Create a CBTAdvertiserAppUi object and return a pointer to it
  @result a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL();

private:

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CBTAdvertiserDocument object
  */
    void ConstructL();

/*!
  @function CBTAdvertiserDocument
  
  @discussion Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
    CBTAdvertiserDocument(CEikApplication& aApp);

    };


#endif // __BTADVERTISER_DOCUMENT_H__
