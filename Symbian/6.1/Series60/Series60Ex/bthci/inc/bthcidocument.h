/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __BTHCIDOCUMENT_H__
#define __BTHCIDOCUMENT_H__


#include <AknDoc.h> 

// Forward references
class CBTHCIAppUi;
class CEikApplication;


/*! 
  @class CBTHCIDocument
  
  @discussion An instance of class CBTHCIDocument is the Document part of the AVKON
  application framework for the BTHCI example application
  */
class CBTHCIDocument : public CAknDocument
    {
public:

/*!
  @function NewL
  
  @discussion Construct a CBTHCIDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CBTHCIDocument
  */
    static CBTHCIDocument* NewL(CEikApplication& aApp);

/*!
  @function NewLC
  
  @discussion Construct a CBTHCIDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CBTHCIDocument
  */
    static CBTHCIDocument* NewLC(CEikApplication& aApp);

/*!
  @function ~CBTHCIDocument
  
  @discussion Destroy the object and release all memory objects
  */
    ~CBTHCIDocument();

public: // from CAknDocument
/*!
  @function CreateAppUiL 
  
  @discussion Create a CBTHCIAppUi object and return a pointer to it
  @result a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL();

private:

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CBTHCIDocument object
  */
    void ConstructL();

/*!
  @function CBTHCIDocument
  
  @discussion Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
    CBTHCIDocument(CEikApplication& aApp);

    };


#endif // __BTHCIDOCUMENT_H__
