/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __TESTFRAMEDOCUMENT_H__
#define __TESTFRAMEDOCUMENT_H__


#include <eikdoc.h>

// Forward references
class CTestframeAppUi;
class CEikApplication;


/*! 
  @class CTestframeDocument
  
  @discussion An instance of class CTestframeDocument is the Document part of the AVKON
  application framework for the test framework example application
  */
class CTestframeDocument : public CEikDocument
    {
public:

/*!
  @function NewL
  
  @discussion Construct a CTestframeDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CTestframeDocument
  */
    static CTestframeDocument* NewL(CEikApplication& aApp);

/*!
  @function NewLC
  
  @discussion Construct a CTestframeDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CTestframeDocument
  */
	static CTestframeDocument* NewLC(CEikApplication& aApp);

/*!
  @function ~CTestframeDocument
  
  @discussion Destroy the object and release all memory objects
  */
    ~CTestframeDocument();

public: //From CEikDocument

/*!
  @function CreateAppUiL 
  
  @discussion Create a CTestframeDocument object and return a pointer to it
  @result a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL();

private:

/*!
  @function CTestframeDocument
  
  @discussion Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
    CTestframeDocument(CEikApplication& aApp);

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CTestframeDocument object
  */
    void ConstructL();
	};


#endif // __TESTFRAMEDOCUMENT_H__
