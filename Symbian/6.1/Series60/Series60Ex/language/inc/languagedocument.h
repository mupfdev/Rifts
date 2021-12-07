/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __LANGUAGE_DOCUMENT_H__
#define __LANGUAGE_DOCUMENT_H__

#include <AknDoc.h> 

// Forward references
class CLanguageAppUi;
class CEikApplication;

/*! 
  @class CLanguageDocument
  
  @discussion An instance of class CLanguageDocument is the Document part of the AVKON
  application framework for the Language example application
  */
class CLanguageDocument : public CAknDocument
    {
public:

/*!
  @function NewL
  
  @discussion Construct a CLanguageDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CLanguageDocument
  */
    static CLanguageDocument* NewL(CEikApplication& aApp);

/*!
  @function NewLC
  
  @discussion Construct a CLanguageDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CLanguageDocument
  */
    static CLanguageDocument* NewLC(CEikApplication& aApp);

/*!
  @function ~CLanguageDocument
  
  @discussion Destroy the object and release all memory objects
  */
    ~CLanguageDocument();

public: // from CEikDocument
/*!
  @function CreateAppUiL 

  @discussion Create a CLanguageAppUi object and return a pointer to it
  @result a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL();
    
private:

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CLanguageDocument object
  */
    void ConstructL();

/*!
  @function CLanguageDocument
  
  @discussion Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
    CLanguageDocument(CEikApplication& aApp);
    };


#endif // __LANGUAGE_DOCUMENT_H__
